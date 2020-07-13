// license:BSD-3-Clause
// copyright-holders:Ryan Holtz
/*
 * nld_74166.cpp
 *
 */

#include "nld_74166.h"
#include "netlist/nl_base.h"

namespace netlist
{
	namespace devices
	{
	NETLIB_OBJECT(74166)
	{
		NETLIB_CONSTRUCTOR(74166)
		, m_DATA(*this, { "H", "G", "F", "E", "D", "C", "B", "A" })
		, m_SER(*this, "SER")
		, m_CLRQ(*this, "CLRQ")
		, m_SH_LDQ(*this, "SH_LDQ")
		, m_CLK(*this, "CLK")
		, m_CLKINH(*this, "CLKINH")
		, m_QH(*this, "QH")
		, m_shifter(*this, "m_shifter", 0)
		, m_last_CLRQ(*this, "m_last_CLRQ", 0)
		, m_last_CLK(*this, "m_last_CLK", 0)
		, m_power_pins(*this)
		{
		}

		NETLIB_RESETI()
		{
			m_shifter = 0;
			m_last_CLRQ = 0;
			m_last_CLK = 0;
		}
		NETLIB_UPDATEI();

		friend class NETLIB_NAME(74166_dip);
	private:
		object_array_t<logic_input_t, 8> m_DATA;
		logic_input_t m_SER;
		logic_input_t m_CLRQ;
		logic_input_t m_SH_LDQ;
		logic_input_t m_CLK;
		logic_input_t m_CLKINH;
		logic_output_t m_QH;

		state_var<unsigned> m_shifter;
		state_var<unsigned> m_last_CLRQ;
		state_var<unsigned> m_last_CLK;
		nld_power_pins m_power_pins;
	};

	NETLIB_OBJECT(74166_dip)
	{
		NETLIB_CONSTRUCTOR(74166_dip)
		, A(*this, "A")
		{
			register_subalias("1", A.m_SER);
			register_subalias("2", A.m_DATA[7]);
			register_subalias("3", A.m_DATA[6]);
			register_subalias("4", A.m_DATA[5]);
			register_subalias("5", A.m_DATA[4]);
			register_subalias("6", A.m_CLKINH);
			register_subalias("7", A.m_CLK);
			register_subalias("8", "A.GND");

			register_subalias("9", A.m_CLRQ);
			register_subalias("10", A.m_DATA[3]);
			register_subalias("11", A.m_DATA[2]);
			register_subalias("12", A.m_DATA[1]);
			register_subalias("13", A.m_QH);
			register_subalias("14", A.m_DATA[0]);
			register_subalias("15", A.m_SH_LDQ);
			register_subalias("16", "A.VCC");
		}
		NETLIB_RESETI() {}
		NETLIB_UPDATEI() {}
	private:
		NETLIB_SUB(74166) A;
	};

	NETLIB_UPDATE(74166)
	{
		netlist_sig_t old_qh = m_QH.net().Q();
		netlist_sig_t qh = 0;

		netlist_time delay = NLTIME_FROM_NS(26);
		if (m_CLRQ())
		{
			bool clear_unset = !m_last_CLRQ;
			if (clear_unset)
			{
				delay = NLTIME_FROM_NS(35);
			}

			if (!m_CLK() || m_CLKINH())
			{
				qh = old_qh;
			}
			else if (!m_last_CLK)
			{
				if (!m_SH_LDQ())
				{
					m_shifter = 0;
					for (std::size_t i=0; i<8; i++)
						m_shifter |= (m_DATA[i]() << i);
				}
				else
				{
					unsigned high_bit = m_SER() ? 0x80 : 0;
					m_shifter = high_bit | (m_shifter >> 1);
				}

				qh = m_shifter & 1;
				if (!qh && !clear_unset)
				{
					delay = NLTIME_FROM_NS(30);
				}
			}
		}

		m_last_CLRQ = m_CLRQ();
		m_last_CLK = m_CLK();

		m_QH.push(qh, delay); //FIXME
	}

	NETLIB_DEVICE_IMPL(74166,    "TTL_74166", "+CLK,+CLKINH,+SH_LDQ,+SER,+A,+B,+C,+D,+E,+F,+G,+H,+CLRQ,@VCC,@GND")
	NETLIB_DEVICE_IMPL(74166_dip,"TTL_74166_DIP", "")

	} //namespace devices
} // namespace netlist
