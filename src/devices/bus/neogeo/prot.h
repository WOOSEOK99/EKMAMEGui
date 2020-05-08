// license:BSD-3-Clause
// copyright-holders:S. Smith,David Haywood


#pragma once

#include "banked_cart.h"

#ifndef __NEOGEO_PROT__
#define __NEOGEO_PROT__

DECLARE_DEVICE_TYPE(NGBOOTLEG_PROT, ngbootleg_prot_device)


class ngbootleg_prot_device :  public device_t
{
public:
	// construction/destruction
	ngbootleg_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);

	void neogeo_bootleg_cx_decrypt(uint8_t*sprrom, uint32_t sprrom_size);
	void neogeo_bootleg_sx_decrypt(uint8_t* fixed, uint32_t fixed_size, int value);
	void kof97oro_px_decode(uint8_t* cpurom, uint32_t cpurom_size);
	void kof10thBankswitch(address_space &space, uint16_t nBank);
	DECLARE_READ16_MEMBER(kof10th_RAM2_r);
	DECLARE_READ16_MEMBER(kof10th_RAMB_r);
	DECLARE_WRITE16_MEMBER(kof10th_custom_w);
	DECLARE_WRITE16_MEMBER(kof10th_bankswitch_w);
	void install_kof10th_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev, uint8_t* cpurom, uint32_t cpurom_size, uint8_t* fixedrom, uint32_t fixedrom_size);
	void decrypt_kof10th(uint8_t* cpurom, uint32_t cpurom_size);
	void kf10thep_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void kf2k5uni_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void kf2k5uni_sx_decrypt(uint8_t* fixedrom, uint32_t fixedrom_size);
	void kf2k5uni_mx_decrypt(uint8_t* audiorom, uint32_t audiorom_size);
	void decrypt_kf2k5uni(uint8_t* cpurom, uint32_t cpurom_size, uint8_t* audiorom, uint32_t audiorom_size, uint8_t* fixedrom, uint32_t fixedrom_size);
	void kof2002b_gfx_decrypt(uint8_t *src, int size);
	void kf2k2mp_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void kf2k2mp2_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void cthd2003_neogeo_gfx_address_fix_do(uint8_t* sprrom, uint32_t sprrom_size, int start, int end, int bit3shift, int bit2shift, int bit1shift, int bit0shift);
	void cthd2003_neogeo_gfx_address_fix(uint8_t* sprrom, uint32_t sprrom_size, int start, int end);
	void cthd2003_c(uint8_t* sprrom, uint32_t sprrom_size, int pow);
	void decrypt_cthd2003(uint8_t* sprrom, uint32_t sprrom_size, uint8_t* audiorom, uint32_t audiorom_size, uint8_t* fixedrom, uint32_t fixedrom_size);
	DECLARE_WRITE16_MEMBER(cthd2003_bankswitch_w);
	void patch_cthd2003(cpu_device* maincpu, neogeo_banked_cart_device* bankdev, uint8_t* cpurom, uint32_t cpurom_size);
	void ct2k3sp_sx_decrypt(uint8_t* fixedrom, uint32_t fixedrom_size);
	void decrypt_ct2k3sp(uint8_t* sprrom, uint32_t sprrom_size, uint8_t* audiorom, uint32_t audiorom_size, uint8_t* fixedrom, uint32_t fixedrom_size);
	void decrypt_ct2k3sa(uint8_t* sprrom, uint32_t sprrom_size, uint8_t* audiorom, uint32_t audiorom_size);
	void patch_ct2k3sa(uint8_t* cpurom, uint32_t cpurom_size);
	void decrypt_kof2k4se_68k(uint8_t* cpurom, uint32_t cpurom_size);
	void lans2004_vx_decrypt(uint8_t* ymsndrom, uint32_t ymsndrom_size);
	void lans2004_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size);
	DECLARE_READ16_MEMBER(mslug5_prot_r);
	DECLARE_WRITE16_MEMBER(ms5plus_bankswitch_w);
	void install_ms5plus_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev);
	void svcboot_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void svcboot_cx_decrypt(uint8_t*sprrom, uint32_t sprrom_size);
	void svcplus_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void svcplus_px_hack(uint8_t* cpurom, uint32_t cpurom_size);
	void svcplusa_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void svcsplus_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void svcsplus_px_hack(uint8_t* cpurom, uint32_t cpurom_size);
	DECLARE_READ16_MEMBER(kof2003_r);
	DECLARE_WRITE16_MEMBER(kof2003_w);
	DECLARE_WRITE16_MEMBER(kof2003p_w);
	DECLARE_READ16_MEMBER(kof2003_overlay_r);
	void kf2k3bl_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void kf2k3bl_install_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev, uint8_t* cpurom, uint32_t cpurom_size);
	void kf2k3pl_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void kf2k3pl_install_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev, uint8_t* cpurom, uint32_t cpurom_size);
	uint16_t kof2k3_overlay;

	void kf2k3upl_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void samsho5b_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	void samsho5b_vx_decrypt(uint8_t* ymsndrom, uint32_t ymsndrom_size);
	void matrimbl_decrypt(uint8_t* sprrom, uint32_t sprrom_size, uint8_t* audiorom, uint32_t audiorom_size);

	uint16_t m_cartridge_ram[0x1000]; // bootlegs

	// for kof10th
	uint8_t* m_mainrom;
	uint8_t* m_fixedrom;
	neogeo_banked_cart_device* m_bankdev;
	uint16_t m_cartridge_ram2[0x10000];

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};


DECLARE_DEVICE_TYPE(KOG_PROT, kog_prot_device)


class kog_prot_device :  public device_t
{
public:
	// construction/destruction
	kog_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);

	void kog_install_protection(cpu_device* maincpu);
	void kog_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size);
	READ16_MEMBER(read_jumper);

	required_ioport m_jumper;

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual ioport_constructor device_input_ports() const override;
};



DECLARE_DEVICE_TYPE(FATFURY2_PROT, fatfury2_prot_device)


class fatfury2_prot_device :  public device_t
{
public:
	// construction/destruction
	fatfury2_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);

	DECLARE_READ16_MEMBER( fatfury2_protection_16_r );
	DECLARE_WRITE16_MEMBER( fatfury2_protection_16_w );
	void fatfury2_install_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev);


	neogeo_banked_cart_device* m_bankdev;
	uint32_t     m_fatfury2_prot_data;

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};


DECLARE_DEVICE_TYPE(KOF2002_PROT, kof2002_prot_device)


class kof2002_prot_device :  public device_t
{
public:
	// construction/destruction
	kof2002_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);

	void kof2002_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size);
	void matrim_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size);
	void samsho5_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size);
	void samsh5sp_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};


DECLARE_DEVICE_TYPE(KOF98_PROT, kof98_prot_device)


class kof98_prot_device :  public device_t
{
public:
	// construction/destruction
	kof98_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);

	void kof98_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size);
	void install_kof98_protection(cpu_device* maincpu);
	DECLARE_WRITE16_MEMBER(kof98_prot_w);
	DECLARE_READ16_MEMBER(kof98_prot_r);
	int kof98_prot_state;
	uint16_t m_default_rom[2];

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};


DECLARE_DEVICE_TYPE(MSLUGX_PROT, mslugx_prot_device)


class mslugx_prot_device :  public device_t
{
public:
	// construction/destruction
	mslugx_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);


	DECLARE_WRITE16_MEMBER( mslugx_protection_16_w );
	DECLARE_READ16_MEMBER( mslugx_protection_16_r );
	void mslugx_install_protection(cpu_device* maincpu);

	uint16_t     m_mslugx_counter;
	uint16_t     m_mslugx_command;

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};


DECLARE_DEVICE_TYPE(PVC_PROT, pvc_prot_device)


class pvc_prot_device :  public device_t
{
public:
	// construction/destruction
	pvc_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);

	void pvc_write_unpack_color();
	void pvc_write_pack_color();
	void pvc_write_bankswitch(address_space &space);
	DECLARE_READ16_MEMBER(pvc_prot_r);
	DECLARE_WRITE16_MEMBER(pvc_prot_w);
	void install_pvc_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev);
	neogeo_banked_cart_device* m_bankdev;

	uint16_t m_cartridge_ram[0x1000];

	void mslug5_decrypt_68k(uint8_t* rom, uint32_t size);
	void svc_px_decrypt(uint8_t* rom, uint32_t size);
	void kf2k3pcb_decrypt_68k(uint8_t* rom, uint32_t size);
	void kof2003_decrypt_68k(uint8_t* rom, uint32_t size);
	void kof2003h_decrypt_68k(uint8_t* rom, uint32_t size);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};


DECLARE_DEVICE_TYPE(SBP_PROT, sbp_prot_device)


class sbp_prot_device :  public device_t
{
public:
	// construction/destruction
	sbp_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);


	uint8_t* m_mainrom;

	void sbp_install_protection(cpu_device* maincpu, uint8_t* cpurom, uint32_t cpurom_size);
	DECLARE_WRITE16_MEMBER(sbp_lowerrom_w);
	DECLARE_READ16_MEMBER(sbp_lowerrom_r);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};

DECLARE_DEVICE_TYPE(SMA_PROT, sma_prot_device)


class sma_prot_device :  public device_t
{
public:
	// construction/destruction
	sma_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 0);


	DECLARE_WRITE16_MEMBER( kof99_bankswitch_w );
	DECLARE_WRITE16_MEMBER( garou_bankswitch_w );
	DECLARE_WRITE16_MEMBER( garouh_bankswitch_w );
	DECLARE_WRITE16_MEMBER( mslug3_bankswitch_w );
	DECLARE_WRITE16_MEMBER( kof2000_bankswitch_w );
	DECLARE_READ16_MEMBER( prot_9a37_r );
	DECLARE_READ16_MEMBER( sma_random_r );
	void reset_sma_rng();
	void sma_install_random_read_handler(cpu_device* maincpu, int addr1, int addr2 );
	void kof99_install_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev);
	void garou_install_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev);
	void garouh_install_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev);
	void mslug3_install_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev);
	void kof2000_install_protection(cpu_device* maincpu, neogeo_banked_cart_device* bankdev);
	neogeo_banked_cart_device* m_bankdev;
	void kof99_decrypt_68k(uint8_t* base);
	void garou_decrypt_68k(uint8_t* base);
	void garouh_decrypt_68k(uint8_t* base);
	void mslug3_decrypt_68k(uint8_t* base);
	void kof2000_decrypt_68k(uint8_t* base);

	// PCB decrypts (not sma)
	void svcpcb_gfx_decrypt(uint8_t* rom, uint32_t rom_size);
	void svcpcb_s1data_decrypt(uint8_t* rom, uint32_t rom_size);
	void kf2k3pcb_gfx_decrypt(uint8_t* rom, uint32_t rom_size);
	void kf2k3pcb_decrypt_s1data(uint8_t* rom, uint32_t rom_size, uint8_t* fixed, uint32_t fixed_size);
	void kf2k3pcb_sp1_decrypt(uint16_t* rom);

	uint16_t     m_sma_rng;
protected:
	virtual void device_start() override;
	virtual void device_reset() override;
};

#endif
