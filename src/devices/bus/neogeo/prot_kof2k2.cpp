// license:BSD-3-Clause
// copyright-holders:S. Smith,David Haywood,Fabio Priuli

#include "emu.h"
#include "prot_kof2k2.h"

DEFINE_DEVICE_TYPE(NG_KOF2002_PROT, kof2002_prot_device, "ng_kof2002_prot", "Neo Geo KoF 2002 Protection")


kof2002_prot_device::kof2002_prot_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, NG_KOF2002_PROT, tag, owner, clock)
{
}


void kof2002_prot_device::device_start()
{
}

void kof2002_prot_device::device_reset()
{
}


/* kof2002, matrim, samsho5, samsh5sp have some simple block swapping */
void kof2002_prot_device::kof2002_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size)
{
	static const int sec[]={0x100000,0x280000,0x300000,0x180000,0x000000,0x380000,0x200000,0x080000};
	uint8_t *src = cpurom + 0x100000;
	std::vector<uint8_t> dst(0x400000);
	memcpy(&dst[0], src, 0x400000);

	for (int i = 0; i < 8; ++i)
		memcpy(src + i * 0x80000, &dst[sec[i]], 0x80000);
}


void kof2002_prot_device::matrim_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size)
{
	static const int sec[]={0x100000,0x280000,0x300000,0x180000,0x000000,0x380000,0x200000,0x080000};
	uint8_t *src = cpurom + 0x100000;
	std::vector<uint8_t> dst(0x400000);
	memcpy(&dst[0], src, 0x400000);

	for (int i = 0; i < 8; ++i)
		memcpy(src + i * 0x80000, &dst[sec[i]], 0x80000);
}


void kof2002_prot_device::samsho5_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size)
{
	static const int sec[]={0x000000,0x080000,0x700000,0x680000,0x500000,0x180000,0x200000,0x480000,0x300000,0x780000,0x600000,0x280000,0x100000,0x580000,0x400000,0x380000};
	uint8_t *src = cpurom;
	std::vector<uint8_t> dst(0x800000);
	memcpy(&dst[0], src, 0x800000);
	for (int i = 0; i < 16; ++i)
		memcpy(src + i * 0x80000, &dst[sec[i]], 0x80000);
}


void kof2002_prot_device::samsh5sp_decrypt_68k(uint8_t* cpurom, uint32_t cpurom_size)
{
	static const int sec[]={0x000000,0x080000,0x500000,0x480000,0x600000,0x580000,0x700000,0x280000,0x100000,0x680000,0x400000,0x780000,0x200000,0x380000,0x300000,0x180000};
	uint8_t *src = cpurom;
	std::vector<uint8_t> dst(0x800000);

	memcpy(&dst[0], src, 0x800000);
	for (int i = 0; i < 16; ++i)
		memcpy(src + i * 0x80000, &dst[sec[i]], 0x80000);
}

/* The King of Fighters 2002 Magic Plus (bootleg) */


void kof2002_prot_device::kf2k2mp_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	int i,j;

	uint8_t *src = cpurom;
	uint8_t dst[0x80];

	memmove(src, src + 0x300000, 0x500000);

	for (i = 0; i < 0x800000; i+=0x80)
	{
		for (j = 0; j < 0x80 / 2; j++)
		{
			int ofst = bitswap<8>( j, 6, 7, 2, 3, 4, 5, 0, 1 );
			memcpy(dst + j * 2, src + i + ofst * 2, 2);
		}
		memcpy(src + i, dst, 0x80);
	}
}


/* The King of Fighters 2002 Magic Plus II (bootleg) */


void kof2002_prot_device::kf2k2mp2_px_decrypt(uint8_t* cpurom, uint32_t cpurom_size)
{
	uint8_t *src = cpurom;
	std::vector<uint8_t> dst(0x600000);

	memcpy (&dst[0x000000], &src[0x1C0000], 0x040000);
	memcpy (&dst[0x040000], &src[0x140000], 0x080000);
	memcpy (&dst[0x0C0000], &src[0x100000], 0x040000);
	memcpy (&dst[0x100000], &src[0x200000], 0x400000);
	memcpy (&src[0x000000], &dst[0x000000], 0x600000);
}

