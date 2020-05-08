// license:BSD-3-Clause
// copyright-holders:Bryan McPhail,Ernesto Corvi,Andrew Prime,Zsolt Vasvari
// thanks-to:Fuzz
/*************************************************************************

    Neo-Geo hardware

*************************************************************************/
#ifndef MAME_INCLUDES_NEOGEO_H
#define MAME_INCLUDES_NEOGEO_H

#pragma once

#include "emu.h"

#include "cpu/m68000/m68000.h"
#include "cpu/z80/z80.h"
#include "sound/2610intf.h"
#include "machine/74259.h"
#include "machine/gen_latch.h"
#include "machine/input_merger.h"
#include "machine/upd1990a.h"
#include "machine/ng_memcard.h"
#include "video/neogeo_spr.h"

#include "bus/neogeo/slot.h"
#include "bus/neogeo/carts.h"
#include "bus/neogeo_ctrl/ctrl.h"

#include "emupal.h"
#include "screen.h"

#include "machine/nvram.h"
#include "machine/watchdog.h"
#include "softlist.h"
#include "speaker.h"

// On scanline 224, /VBLANK goes low 56 mclks (14 pixels) from the rising edge of /HSYNC.
// Two mclks after /VBLANK goes low, the hardware sets a pending IRQ1 flip-flop.
#define NEOGEO_VBLANK_IRQ_HTIM (attotime::from_ticks(56+2, NEOGEO_MASTER_CLOCK))
/*************************************
 *
 *  Neo-Geo bios
 *
 *************************************

    These are the known Bios Roms, Set options.bios to the one you want.

    The Universe bios roms are supported because they're now used on enough PCBs
    to be considered 'in active arcade use' rather than just homebrew hacks.
    Some may be missing, there have been multiple CRCs reported for the same
    revision in some cases (the Universe bios has an option for entering / displaying
    a serial number; these should be noted as such if they're added).
    Universe bios prior to version 1.3 was incompatible with AES.

    The 'japan-hotel' BIOS is a dump of an MVS which could be found in some japanese
    hotels. it is a custom MVS mobo which uses MVS carts but it hasn't jamma
    connector and it's similar to a console with a coin mechanism, so it's a sort
    of little coin op console installed in hotels.

    The sp-45.sp1 bios is the latest 'ASIA' revision. Japan-j3.bin is the latest 'JAPAN'
    revision. Both of them are also used in the sp-4x.sp1 bios of the Jamma PCB boards.

    The current Neo-Geo MVS system set (SFIX/SM1/000-LO) used is from a NEO-MVH MV1FS board.
    Other boards (MV1xx / MV2x / MV4x /MV6x) other system sets?

    Zoom ROM (LO)    128K   TC531000CP      1x 128Kx8   Zoom look-up table ROM
    Fix ROM (SFIX)   128K   27C1000         1x 128Kx8   Text layer graphics ROM
    Sound ROM (SM1)  128K   27C1000/23C1000 1x 128Kx8   Z80 program ROM

*/

#define ROM_LOAD16_WORD_SWAP_BIOS(bios,name,offset,length,hash) \
		ROMX_LOAD(name, offset, length, hash, ROM_GROUPWORD | ROM_REVERSE | ROM_BIOS(bios))

#define NEOGEO_UNIBIOS(x) \
	ROM_SYSTEM_BIOS( x+ 0, "unibios40", "Universe Bios (Hack, Ver. 4.0)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 0, "uni-bios_4_0.rom",  0x00000, 0x020000, CRC(a7aab458) SHA1(938a0bda7d9a357240718c2cec319878d36b8f72) ) /* Universe Bios v4.0 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 1, "unibios33", "Universe Bios (Hack, Ver. 3.3)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 1, "uni-bios_3_3.rom",  0x00000, 0x020000, CRC(24858466) SHA1(0ad92efb0c2338426635e0159d1f60b4473d0785) ) /* Universe Bios v3.3 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 2, "unibios32", "Universe Bios (Hack, Ver. 3.2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 2, "uni-bios_3_2.rom",  0x00000, 0x020000, CRC(a4e8b9b3) SHA1(c92f18c3f1edda543d264ecd0ea915240e7c8258) ) /* Universe Bios v3.2 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 3, "unibios31", "Universe Bios (Hack, Ver. 3.1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 3, "uni-bios_3_1.rom",  0x00000, 0x020000, CRC(0c58093f) SHA1(29329a3448c2505e1ff45ffa75e61e9693165153) ) /* Universe Bios v3.1 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 4, "unibios30", "Universe Bios (Hack, Ver. 3.0)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 4, "uni-bios_3_0.rom",  0x00000, 0x020000, CRC(a97c89a9) SHA1(97a5eff3b119062f10e31ad6f04fe4b90d366e7f) ) /* Universe Bios v3.0 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 5, "unibios23", "Universe Bios (Hack, Ver. 2.3)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 5, "uni-bios_2_3.rom",  0x00000, 0x020000, CRC(27664eb5) SHA1(5b02900a3ccf3df168bdcfc98458136fd2b92ac0) ) /* Universe Bios v2.3 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 6, "unibios23o", "Universe Bios (Hack, Ver. 2.3, older?)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 6, "uni-bios_2_3o.rom", 0x00000, 0x020000, CRC(601720ae) SHA1(1b8a72c720cdb5ee3f1d735bbcf447b09204b8d9) ) /* Universe Bios v2.3 (hack) alt version, withdrawn? */ \
	ROM_SYSTEM_BIOS( x+ 7, "unibios22", "Universe Bios (Hack, Ver. 2.2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 7, "uni-bios_2_2.rom",  0x00000, 0x020000, CRC(2d50996a) SHA1(5241a4fb0c63b1a23fd1da8efa9c9a9bd3b4279c) ) /* Universe Bios v2.2 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 8, "unibios21", "Universe Bios (Hack, Ver. 2.1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 8, "uni-bios_2_1.rom",  0x00000, 0x020000, CRC(8dabf76b) SHA1(c23732c4491d966cf0373c65c83c7a4e88f0082c) ) /* Universe Bios v2.1 (hack) */ \
	ROM_SYSTEM_BIOS( x+ 9, "unibios20", "Universe Bios (Hack, Ver. 2.0)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+ 9, "uni-bios_2_0.rom",  0x00000, 0x020000, CRC(0c12c2ad) SHA1(37bcd4d30f3892078b46841d895a6eff16dc921e) ) /* Universe Bios v2.0 (hack) */ \
	ROM_SYSTEM_BIOS( x+10, "unibios13", "Universe Bios (Hack, Ver. 1.3)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+10, "uni-bios_1_3.rom",  0x00000, 0x020000, CRC(b24b44a0) SHA1(eca8851d30557b97c309a0d9f4a9d20e5b14af4e) ) /* Universe Bios v1.3 (hack) */
#define NEOGEO_UNIBIOS_1_2_AND_OLDER(x) \
	ROM_SYSTEM_BIOS( x+11, "unibios12", "Universe Bios (Hack, Ver. 1.2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+11, "uni-bios_1_2.rom",  0x00000, 0x020000, CRC(4fa698e9) SHA1(682e13ec1c42beaa2d04473967840c88fd52c75a) ) /* Universe Bios v1.2 (hack) */ \
	ROM_SYSTEM_BIOS( x+12, "unibios12o", "Universe Bios (Hack, Ver. 1.2, older)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+12, "uni-bios_1_2o.rom", 0x00000, 0x020000, CRC(e19d3ce9) SHA1(af88ef837f44a3af2d7144bb46a37c8512b67770) ) /* Universe Bios v1.2 (hack) alt version */ \
	ROM_SYSTEM_BIOS( x+13, "unibios11", "Universe Bios (Hack, Ver. 1.1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+13, "uni-bios_1_1.rom",  0x00000, 0x020000, CRC(5dda0d84) SHA1(4153d533c02926a2577e49c32657214781ff29b7) ) /* Universe Bios v1.1 (hack) */ \
	ROM_SYSTEM_BIOS( x+14, "unibios10", "Universe Bios (Hack, Ver. 1.0)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( x+14, "uni-bios_1_0.rom",  0x00000, 0x020000, CRC(0ce453a0) SHA1(3b4c0cd26c176fc6b26c3a2f95143dd478f6abf9) ) /* Universe Bios v1.0 (hack) */

/* the number shown in the top right corner (only displayed on the colour test in early versions) should be connected to the revision, the actual numbering / naming here is a mess, possibly due to upgrades where stickers weren't replaced
   also is the colour of the outside of the test grid connected to the region? / cabinet type? (if so, why so many colours for US ones, but not other regions and are Asia + Europe really just the same thing?)

   these details have been added to the comments */

#define NEOGEO_BIOS \
	ROM_REGION16_BE( 0x80000, "mainbios", 0 ) \
	ROM_SYSTEM_BIOS( 0, "euro", "Europe MVS (Ver. 2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 0, "sp-s2.sp1",         0x00000, 0x020000, CRC(9036d879) SHA1(4f5ed7105b7128794654ce82b51723e16e389543) ) /* 5 Dark Blue - Europe, 1 Slot, has also been found on 2 Slot and 4 Slot (the old hacks were designed for this one) */ \
	ROM_SYSTEM_BIOS( 1, "euro-s1", "Europe MVS (Ver. 1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 1, "sp-s.sp1",          0x00000, 0x020000, CRC(c7f2fa45) SHA1(09576ff20b4d6b365e78e6a5698ea450262697cd) ) /* 3 Dark Blue - Europe, 4 Slot */ \
	ROM_SYSTEM_BIOS( 2, "asia-mv1c", "Asia NEO-MVH MV1C" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 2, "sp-45.sp1",         0x00000, 0x080000, CRC(03cc9f6a) SHA1(cdf1f49e3ff2bac528c21ed28449cf35b7957dc1) ) /* 6 Dark Blue - Latest Asia bios (MV1C - mask ROM) */ \
	ROM_SYSTEM_BIOS( 3, "asia-mv1b", "Asia MV1B" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 3, "sp-s3.sp1",         0x00000, 0x020000, CRC(91b64be3) SHA1(720a3e20d26818632aedf2c2fd16c54f213543e1) ) /* 6 Dark Blue - Asia (MV1B) */ \
	\
	ROM_SYSTEM_BIOS( 4, "us", "US MVS (Ver. 2?)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 4, "sp-u2.sp1",         0x00000, 0x020000, CRC(e72943de) SHA1(5c6bba07d2ec8ac95776aa3511109f5e1e2e92eb) ) /* 5 Cyan - US, 2 Slot */ \
	ROM_SYSTEM_BIOS( 5, "us-e", "US MVS (Ver. 1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 5, "sp-e.sp1",          0x00000, 0x020000, CRC(2723a5b5) SHA1(5dbff7531cf04886cde3ef022fb5ca687573dcb8) ) /* 5 Yellow - US, 6 Slot (V5?) */ \
	ROM_SYSTEM_BIOS( 6, "us-v2", "US MVS (4 slot, Ver 2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 6, "sp1-u2",            0x00000, 0x020000, CRC(62f021f4) SHA1(62d372269e1b3161c64ae21123655a0a22ffd1bb) ) /* 3 Cyan - US, 4 slot - also seen with "v2" label*/ \
	ROM_SYSTEM_BIOS( 7, "us-u4", "US MVS (U4)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 7, "sp1-u4.bin",        0x00000, 0x020000, CRC(1179a30f) SHA1(866817f47aa84d903d0b819d61f6ef356893d16a) ) /* 3 Green - 4 Slot (MV-4F) */ \
	ROM_SYSTEM_BIOS( 8, "us-u3", "US MVS (U3)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 8, "sp1-u3.bin",        0x00000, 0x020000, CRC(2025b7a2) SHA1(73d774746196f377111cd7aa051cc8bb5dd948b3) ) /* 2 Green - 6 Slot */ \
	\
	ROM_SYSTEM_BIOS( 9, "japan", "Japan MVS (Ver. 3)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 9, "vs-bios.rom",       0x00000, 0x020000, CRC(f0e8f27d) SHA1(ecf01eda815909f1facec62abf3594eaa8d11075) ) /* 6 Red - Japan, Ver 6 VS Bios */ \
	ROM_SYSTEM_BIOS( 10, "japan-s2", "Japan MVS (Ver. 2)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 10, "sp-j2.sp1",        0x00000, 0x020000, CRC(acede59c) SHA1(b6f97acd282fd7e94d9426078a90f059b5e9dd91) ) /* 5 Red - Japan, Older */ \
	ROM_SYSTEM_BIOS( 11, "japan-s1", "Japan MVS (Ver. 1)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 11, "sp1.jipan.1024",   0x00000, 0x020000, CRC(9fb0abe4) SHA1(18a987ce2229df79a8cf6a84f968f0e42ce4e59d) ) /* 3 Red - Japan, Older */ \
	ROM_SYSTEM_BIOS( 12, "japan-mv1b", "Japan MV1B" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 12, "japan-j3.bin",     0x00000, 0x020000, CRC(dff6d41f) SHA1(e92910e20092577a4523a6b39d578a71d4de7085) ) /* 6 Red - Latest Japan bios (MV1B) */ \
	ROM_SYSTEM_BIOS( 13, "japan-j3a", "Japan MVS (J3, alt)" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 13, "sp1-j3.bin",       0x00000, 0x020000, CRC(fbc6d469) SHA1(46b2b409b5b68869e367b40c846373623edb632a) ) /* 2 Red - 6 Slot */ \
	ROM_SYSTEM_BIOS( 14, "japan-mv1c", "Japan NEO-MVH MV1C" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 14, "sp-j3.sp1",        0x00000, 0x080000, CRC(486cb450) SHA1(52c21ea817928904b80745a8c8d15cbad61e1dc1) ) /* 6 Red - Latest Japan bios (MV1C - mask ROM) */ \
	\
	ROM_SYSTEM_BIOS( 15, "japan-hotel", "Custom Japanese Hotel" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 15, "sp-1v1_3db8c.bin", 0x00000, 0x020000, CRC(162f0ebe) SHA1(fe1c6dd3dfcf97d960065b1bb46c1e11cb7bf271) ) /* 6 Red - 'rare MVS found in japanese hotels' shows v1.3 in test mode */ \
	\
	NEOGEO_UNIBIOS(16) \
	NEOGEO_UNIBIOS_1_2_AND_OLDER(16)


#define NEO_BIOS_AUDIO_64K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x20000, "cslot1:audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, 0x10000, hash ) \
	ROM_RELOAD(     0x10000, 0x10000 ) 

#define NEO_BIOS_AUDIO_128K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x30000, "cslot1:audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, 0x20000, hash ) \
	ROM_RELOAD(     0x10000, 0x20000 ) 

#define NEO_BIOS_AUDIO_256K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x50000, "cslot1:audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, 0x40000, hash ) \
	ROM_RELOAD(     0x10000, 0x40000 )

#define NEO_BIOS_AUDIO_512K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "cslot1:audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, 0x80000, hash ) \
	ROM_RELOAD(     0x10000, 0x80000 ) 


#define NEO_BIOS_AUDIO_ENCRYPTED_128K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "cslot1:audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "cslot1:audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, 0x20000, hash ) 
	
#define NEO_BIOS_AUDIO_ENCRYPTED_256K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "cslot1:audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "cslot1:audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, 0x40000, hash )
	
#define NEO_BIOS_AUDIO_ENCRYPTED_512K(name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "cslot1:audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "cslot1:audiocrypt", 0 ) \
	ROM_LOAD( name,      0x00000, 0x80000, hash )

#define NEO_SFIX_64K(name, hash) \
	ROM_REGION( 0x10000, "cslot1:fixed", 0 ) \
	ROM_LOAD( name, 0x000000, 0x10000, hash ) \
	ROM_REGION( 0x20000, "fixedbios", 0 ) \
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) ) \
	ROM_Y_ZOOM

#define NEO_SFIX_128K(name, hash) \
	ROM_REGION( 0x20000, "cslot1:fixed", 0 ) \
	ROM_LOAD( name, 0x000000, 0x20000, hash ) \
	ROM_REGION( 0x20000, "fixedbios", 0 ) \
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) ) \
	ROM_Y_ZOOM

#define NEO_SFIX_512K(name, hash) \
	ROM_REGION( 0x80000, "cslot1:fixed", 0 ) \
	ROM_LOAD( name, 0x000000, 0x80000, hash ) \
	ROM_REGION( 0x20000, "fixedbios", 0 ) \
	ROM_LOAD( "sfix.sfx",  0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) ) \
	ROM_Y_ZOOM

#define ROM_Y_ZOOM \
	ROM_REGION( 0x20000, "spritegen:zoomy", 0 ) \
	ROM_LOAD( "000-lo.lo", 0x00000, 0x20000, CRC(5a86cff2) SHA1(5992277debadeb64d1c1c64b0a92d9293eaf7e4a) )

#define NEO_SFIX_MT(bytes) \
	ROM_Y_ZOOM \
	ROM_REGION( 0x20000, "fixedbios", 0 ) \
	ROM_LOAD( "sfix.sfix",  0, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) ) \
	ROM_REGION( bytes, "cslot1:fixed", ROMREGION_ERASE00 )

#define NEO_SFIX_MT_128K \
	NEO_SFIX_MT( 0x20000 )

#define NEO_SFIX_MT_512K \
	NEO_SFIX_MT( 0x80000 )

#define NEO_SFIX_MSLUG(name, hash) \
	NEO_SFIX_MT( 0x80000 ) \
	ROM_LOAD( name, 0x00000, 0x20000, hash ) \
	ROM_RELOAD( 0x20000, 0x20000 ) \
	ROM_RELOAD( 0x40000, 0x20000 ) \
	ROM_RELOAD( 0x60000, 0x20000 )

#define NEO_SFIX(bytes, name, hash) \
	NEO_SFIX_MT( bytes ) \
	ROM_LOAD( name, 0x00000, bytes, hash )

// dummy entry for the dummy bios driver
ROM_START( neogeo )
	NEOGEO_BIOS

	ROM_REGION( 0x100000, "maincpu", ROMREGION_ERASEFF )

	ROM_REGION( 0x20000, "audiobios", 0 )
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) )

	ROM_REGION( 0x50000, "audiocpu", 0 )
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) )

	ROM_Y_ZOOM

	ROM_REGION( 0x20000, "fixed", ROMREGION_ERASEFF )

	ROM_REGION( 0x20000, "fixedbios", 0 )
	ROM_LOAD( "sfix.sfix", 0x000000, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) )

	ROM_REGION( 0x100000, "sprites", ROMREGION_ERASEFF )
ROM_END

#define rom_ng_mv4f rom_neogeo
#define rom_ng_mv2f rom_neogeo
#define rom_ng_mv1 rom_neogeo
#define rom_ng_mv1f rom_neogeo
#define rom_ng_mv1fz rom_neogeo


class neogeo_base_state : public driver_device
{
public:
	DECLARE_CUSTOM_INPUT_MEMBER(get_memcard_status);
	DECLARE_CUSTOM_INPUT_MEMBER(get_audio_result);

protected:
	neogeo_base_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_audiocpu(*this, "audiocpu")
		, m_ym(*this, "ymsnd")
		, m_sprgen(*this, "spritegen")
		, m_screen(*this, "screen")
		, m_palette(*this, "palette")
		, m_memcard(*this, "memcard")
		, m_systemlatch(*this, "systemlatch")
		, m_soundlatch(*this, "soundlatch")
		, m_soundlatch2(*this, "soundlatch2")
		, m_region_maincpu(*this, "maincpu")
		, m_region_sprites(*this, "sprites")
		, m_region_fixed(*this, "fixed")
		, m_region_fixedbios(*this, "fixedbios")
		, m_region_mainbios(*this, "mainbios")
		, m_region_audiobios(*this, "audiobios")
		, m_region_audiocpu(*this, "audiocpu")
		, m_bank_audio_main(*this, "audio_main")
		, m_edge(*this, "edge")
		, m_ctrl1(*this, "ctrl1")
		, m_ctrl2(*this, "ctrl2")
		, m_use_cart_vectors(0)
		, m_use_cart_audio(0)
		, m_slots(*this, "cslot%u", 1U)
		, m_audionmi(*this, "audionmi")
	{ }

	DECLARE_READ16_MEMBER(memcard_r);
	DECLARE_WRITE16_MEMBER(memcard_w);
	DECLARE_READ8_MEMBER(audio_cpu_bank_select_r);
	DECLARE_WRITE8_MEMBER(audio_cpu_enable_nmi_w);
	DECLARE_READ16_MEMBER(unmapped_r);
	DECLARE_READ16_MEMBER(paletteram_r);
	DECLARE_WRITE16_MEMBER(paletteram_w);
	DECLARE_READ16_MEMBER(video_register_r);
	DECLARE_WRITE16_MEMBER(video_register_w);

	TIMER_CALLBACK_MEMBER(display_position_interrupt_callback);
	TIMER_CALLBACK_MEMBER(display_position_vblank_callback);
	TIMER_CALLBACK_MEMBER(vblank_interrupt_callback);

	uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	virtual DECLARE_WRITE8_MEMBER(io_control_w);
	DECLARE_WRITE8_MEMBER(audio_command_w);
	DECLARE_WRITE_LINE_MEMBER(set_use_cart_vectors);
	DECLARE_WRITE_LINE_MEMBER(set_use_cart_audio);
	DECLARE_READ16_MEMBER(banked_vectors_r);
	DECLARE_WRITE16_MEMBER(write_banksel);
	DECLARE_WRITE16_MEMBER(write_bankprot);
	DECLARE_WRITE16_MEMBER(write_bankprot_pvc);
	DECLARE_WRITE16_MEMBER(write_bankprot_ms5p);
	DECLARE_WRITE16_MEMBER(write_bankprot_kf2k3bl);
	DECLARE_WRITE16_MEMBER(write_bankprot_kof10th);
	DECLARE_READ16_MEMBER(read_lorom_kof10th);

	DECLARE_WRITE_LINE_MEMBER(set_screen_shadow);
	DECLARE_WRITE_LINE_MEMBER(set_palette_bank);

	void neogeo_base(machine_config &config);
	void neogeo_stereo(machine_config &config);

	void base_main_map(address_map &map);
	void base_ek_main_map(address_map &map);//EKMAME
//>>>>>>> upstream/master
	void audio_io_map(address_map &map);
	void audio_map(address_map &map);

	// device overrides
	virtual void machine_start() override;
	virtual void machine_reset() override;

	virtual void device_post_load() override;

	// devices
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	// MVS-specific devices
	optional_device<ym2610_device> m_ym;
	required_device<neosprite_optimized_device> m_sprgen;

	required_device<screen_device> m_screen;
	optional_device<palette_device> m_palette;
	optional_device<ng_memcard_device> m_memcard;
	required_device<hc259_device> m_systemlatch;
	required_device<generic_latch_8_device> m_soundlatch;
	required_device<generic_latch_8_device> m_soundlatch2;

	// memory
	optional_memory_region m_region_maincpu;
	optional_memory_region m_region_sprites;
	optional_memory_region m_region_fixed;
	optional_memory_region m_region_fixedbios;
	optional_memory_region m_region_mainbios;
	optional_memory_region m_region_audiobios;
	optional_memory_region m_region_audiocpu;
	optional_memory_bank   m_bank_audio_main; // optional because of neocd
	memory_bank           *m_bank_audio_cart[4];
	memory_bank           *m_bank_cartridge;

	optional_device<neogeo_ctrl_edge_port_device> m_edge;
	optional_device<neogeo_control_port_device> m_ctrl1;
	optional_device<neogeo_control_port_device> m_ctrl2;

	// video hardware, including maincpu interrupts
	// TODO: make into a device
	virtual void video_start() override;
	virtual void video_reset() override;

	const pen_t *m_bg_pen;
	uint8_t      m_vblank_level;
	uint8_t      m_raster_level;

	int m_use_cart_vectors;
	int m_use_cart_audio;

	void set_slot_idx(int slot);

	// cart slots
	void init_cpu();
	void init_audio();
	void init_ym();
	void init_sprites();
	// temporary helper to restore memory banking while bankswitch is handled in the driver...
	uint32_t m_bank_base;

	optional_device_array<neogeo_cart_slot_device, 6> m_slots;

	int m_curr_slot;

private:
	void update_interrupts();
	void create_interrupt_timers();
	void start_interrupt_timers();
	void acknowledge_interrupt(uint16_t data);

	void adjust_display_position_interrupt_timer();
	void set_display_position_interrupt_control(uint16_t data);
	void set_display_counter_msb(uint16_t data);
	void set_display_counter_lsb(uint16_t data);
	void set_video_control(uint16_t data);

	void create_rgb_lookups();
	void set_pens();

	// internal state
	bool       m_recurse;

	emu_timer  *m_display_position_interrupt_timer;
	emu_timer  *m_display_position_vblank_timer;
	emu_timer  *m_vblank_interrupt_timer;
	uint32_t     m_display_counter;
	uint8_t      m_vblank_interrupt_pending;
	uint8_t      m_display_position_interrupt_pending;
	uint8_t      m_irq3_pending;
	uint8_t      m_display_position_interrupt_control;

	uint16_t get_video_control();

	required_device<input_merger_device> m_audionmi;

	// color/palette related
	std::vector<uint16_t> m_paletteram;
	uint8_t        m_palette_lookup[32][4];
	int          m_screen_shadow;
	int          m_palette_bank;
};


class ngarcade_base_state : public neogeo_base_state
{
public:
	DECLARE_CUSTOM_INPUT_MEMBER(startsel_edge_joy_r);

protected:
	ngarcade_base_state(const machine_config &mconfig, device_type type, const char *tag)
		: neogeo_base_state(mconfig, type, tag)
		, m_save_ram(*this, "saveram")
		, m_upd4990a(*this, "upd4990a")
		, m_dsw(*this, "DSW")
	{
	}

	virtual void machine_start() override;
	virtual void machine_reset() override;

	virtual DECLARE_WRITE8_MEMBER(io_control_w) override;
	DECLARE_WRITE_LINE_MEMBER(set_save_ram_unlock);
	DECLARE_WRITE16_MEMBER(save_ram_w);
	DECLARE_READ16_MEMBER(in0_edge_r);
	DECLARE_READ16_MEMBER(in0_edge_joy_r);
	DECLARE_READ16_MEMBER(in1_edge_r);
	DECLARE_READ16_MEMBER(in1_edge_joy_r);

	void neogeo_arcade(machine_config &config);
	void neogeo_gsc_arcade(machine_config &config);//EKMAME
	void neogeo_noslot_arcade(machine_config &config);//EKMAME
	void neogeo_ek_arcade(machine_config &config);//EKMAME
	void neogeo_mono(machine_config &config);

	void neogeo_main_map(address_map &map);
	void neogeo_gsc_map(address_map &map);//EKMAME
	void neogeo_noslot_map(address_map &map);//EKMAME
	void neogeo_ek_main_map(address_map &map);//EKMAME

private:
	required_shared_ptr<uint16_t> m_save_ram;
	required_device<upd4990a_device> m_upd4990a;
	required_ioport m_dsw;

	uint8_t m_save_ram_unlocked;
};


class aes_base_state : public neogeo_base_state
{
public:
	DECLARE_INPUT_CHANGED_MEMBER(aes_jp1);

protected:
	aes_base_state(const machine_config &mconfig, device_type type, const char *tag)
		: neogeo_base_state(mconfig, type, tag)
		, m_io_in2(*this, "IN2")
	{
	}

	DECLARE_READ16_MEMBER(aes_in2_r);

	virtual void machine_start() override;

	void aes_base_main_map(address_map &map);

private:
	required_ioport m_io_in2;
};

class mvs_state : public ngarcade_base_state
{
public:
	mvs_state(const machine_config &mconfig, device_type type, const char *tag)
		: ngarcade_base_state(mconfig, type, tag)
	{
	}

	// mainboard configurations
	void cartslot_config(machine_config &config, unsigned count);
	void cartslot_fixed(machine_config &config, char const *dflt);
	void mv1fz(machine_config &config);

	// fixed software configurations
	void kizuna4p(machine_config &config);
	void irrmaze(machine_config &config);

protected:
	virtual void machine_start() override;
	virtual void device_post_load() override;
	virtual void output_strobe(uint8_t bits, uint8_t data) { }
	virtual void set_outputs() { }

	virtual DECLARE_WRITE8_MEMBER(io_control_w) override;

private:
	uint8_t m_output_data;
	uint8_t m_output_latch;
};


class mvs_led_state : public mvs_state
{
public:
	mvs_led_state(const machine_config &mconfig, device_type type, const char *tag)
		: mvs_state(mconfig, type, tag)
		, m_digits(*this, "digit%u", 1U)
	{
	}

	// mainboard configurations
	void mv1(machine_config &config);
	void mv1f(machine_config &config);

	// fixed software configurations
	void neobase(machine_config &config);
	void fatfur2(machine_config &config);
	void kof97oro(machine_config &config);
	void kog(machine_config &config);
	void kof98(machine_config &config);
	void mslugx(machine_config &config);
	void kof99(machine_config &config);
	void kof99k(machine_config &config);
	void garou(machine_config &config);
	void garouh(machine_config &config);
	void garoubl(machine_config &config);
	void mslug3(machine_config &config);
	void mslug3a(machine_config &config);
	void mslug3h(machine_config &config);
	void mslug3b6(machine_config &config);
	void ms6s16(machine_config &config);
	void kof2000(machine_config &config);
	void kof2000n(machine_config &config);
	void zupapa(machine_config &config);
	void sengoku3(machine_config &config);
	void kof2001(machine_config &config);
	void cthd2k3(machine_config &config);
	void ct2k3sp(machine_config &config);
	void ct2k3sa(machine_config &config);
	void kof2002(machine_config &config);
	void kof2002b(machine_config &config);
	void kf2k2pls(machine_config &config);
	void kf2k2mp(machine_config &config);
	void kf2k2mp2(machine_config &config);
	void kof10th(machine_config &config);
	void kf10thep(machine_config &config);
	void kf2k5uni(machine_config &config);
	void kof2k4se(machine_config &config);
	void mslug5(machine_config &config);
	void mslug5hb(machine_config &config);
	void ms5plus(machine_config &config);
	void mslug5b(machine_config &config);
	void svc(machine_config &config);
	void svcboot(machine_config &config);
	void svcplus(machine_config &config);
	void svcplusa(machine_config &config);
	void svcsplus(machine_config &config);
	void samsho5(machine_config &config);
	void samsho5b(machine_config &config);
	void kof2003(machine_config &config);
	void kof2003h(machine_config &config);
	void kf2k3bl(machine_config &config);
	void kf2k3pl(machine_config &config);
	void kf2k3upl(machine_config &config);
	void samsh5sp(machine_config &config);
	void neogeo_mj(machine_config &config);
	void preisle2(machine_config &config);
	void nitd(machine_config &config);
	void s1945p(machine_config &config);
	void lans2004(machine_config &config);
	void pnyaa(machine_config &config);
	void popbounc(machine_config &config);
	void ganryu(machine_config &config);
	void bangbead(machine_config &config);
	void mslug4(machine_config &config);
	void ms4plus(machine_config &config);
	void rotd(machine_config &config);
	void matrim(machine_config &config);
	void matrimbl(machine_config &config);
	void jockeygp(machine_config &config);
	void vliner(machine_config &config);
	void sbp(machine_config &config);
	void neo304h(machine_config &config); //MAMEFX
	void neo288h(machine_config &config); //MAMEFX
	void cyberlip(machine_config &config); //MAMEFX
	
	void neo_ek(machine_config &config);//EKMAME	
	void neo_gsc_ek(machine_config &config);//EKMAME	
	void neo_noslot_ek(machine_config &config);//EKMAME	
	void neobase_ek(machine_config &config);
	void cmc42sfix_ek(machine_config &config);
	void cmc50sfix_ek(machine_config &config);
	void kof2k2sr_ek(machine_config &config);
	void kof2000d_ek(machine_config &config);
	void kof2knd(machine_config &config);
	void kof2000m(machine_config &config);
	void cthd2003(machine_config &config);
	void cthd2003a(machine_config &config);
protected:
	virtual void machine_start() override;

	virtual void output_strobe(uint8_t bits, uint8_t data) override;
	virtual void set_outputs() override;

	void mv1_fixed(machine_config &config);
	void mv1_gsc_fixed(machine_config &config);//EKMAME
	void mv1_noslot_fixed(machine_config &config);//EKMAME
	void mv1_ek_fixed(machine_config &config);//EKMAME
private:
	output_finder<4> m_digits;

	uint8_t m_led1_value;
	uint8_t m_led2_value;
};


class mvs_led_el_state : public mvs_led_state
{
public:
	mvs_led_el_state(const machine_config &mconfig, device_type type, const char *tag)
		: mvs_led_state(mconfig, type, tag)
		, m_lamps(*this, "lamp%u", 1U)
	{
	}

	// mainboard configurations
	void mv2f(machine_config &config);
	void mv4f(machine_config &config);
	void mv6f(machine_config &config);

protected:
	virtual void machine_start() override;

	virtual void output_strobe(uint8_t bits, uint8_t data) override;
	virtual void set_outputs() override;

private:
	output_finder<6> m_lamps;

	uint8_t m_el_value;
};


class aes_state : public aes_base_state
{
public:
	aes_state(const machine_config &mconfig, device_type type, const char *tag)
		: aes_base_state(mconfig, type, tag)
	{
	}

	void aes(machine_config &config);

protected:
	virtual void machine_start() override;

	virtual void device_post_load() override;

	void aes_main_map(address_map &map);
};

/*----------- defined in drivers/neogeo.c -----------*/

INPUT_PORTS_EXTERN(neogeo);
INPUT_PORTS_EXTERN(aes);

#endif // MAME_INCLUDES_NEOGEO_H
