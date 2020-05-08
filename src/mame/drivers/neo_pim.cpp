#include "includes/neogeo_hack.h"

#include "neogeo.lh"



static INPUT_PORTS_START( neo_ek )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP )
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN )
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT )
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x1000)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x2000)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x4000)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x8000)
	PORT_BIT( 0x3000, IP_ACTIVE_LOW, IPT_BUTTON_AB ) PORT_NAME("@P1 버튼 조합 (@Button1@Button2)") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x3000)	
	PORT_BIT( 0x5000, IP_ACTIVE_LOW, IPT_BUTTON_AC ) PORT_NAME("@P1 버튼 조합 (@Button1@Button3)") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x5000)
	PORT_BIT( 0x9000, IP_ACTIVE_LOW, IPT_BUTTON_AD ) PORT_NAME("@P1 버튼 조합 (@Button1@Button4)") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x9000)	
	PORT_BIT( 0x2000+0x4000, IP_ACTIVE_LOW, IPT_BUTTON_BC ) PORT_NAME("@P1 버튼 조합 (@Button2@Button3)") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x6000)
	PORT_BIT( 0x2000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_BD ) PORT_NAME("@P1 버튼 조합 (@Button2@Button4)") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0xA000)
	PORT_BIT( 0x4000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_CD ) PORT_NAME("@P1 버튼 조합 (@Button3@Button4)") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0xC000)
	PORT_BIT( 0x1000+0x2000+0x4000, IP_ACTIVE_LOW, IPT_BUTTON_ABC ) PORT_NAME("@P1 버튼 조합 (@Button1@Button2@Button3)") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0x7000)	
	PORT_BIT( 0x1000+0x2000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_ABD ) PORT_NAME("@P1 버튼 조합 (@Button1@Button2@Button4)") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0xB000)
	PORT_BIT( 0x1000+0x4000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_ACD ) PORT_NAME("@P1 버튼 조합 (@Button1@Button3@Button4)") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0xD000)
	PORT_BIT( 0x2000+0x4000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_BCD ) PORT_NAME("@P1 버튼 조합 (@Button2@Button3@Button4)") PORT_CONDITION("DSW", 0xF000, NOTEQUALS, 0xE000)
	PORT_BIT( 0x1000+0x2000+0x4000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_ABCD ) PORT_NAME("@P1 버튼 조합 (@Button1@Button2@Button3@Button4)") PORT_CONDITION("DSW", 0xF000, EQUALS, 0xF000)

	PORT_START("P2")
	PORT_BIT( 0x00ff, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_JOYSTICK_UP ) PORT_PLAYER(2)
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_JOYSTICK_DOWN ) PORT_PLAYER(2)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_JOYSTICK_LEFT ) PORT_PLAYER(2)
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_JOYSTICK_RIGHT ) PORT_PLAYER(2)
	PORT_BIT( 0x1000, IP_ACTIVE_LOW, IPT_BUTTON1 ) PORT_PLAYER(2) PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x1000)
	PORT_BIT( 0x2000, IP_ACTIVE_LOW, IPT_BUTTON2 ) PORT_PLAYER(2) PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x2000)
	PORT_BIT( 0x4000, IP_ACTIVE_LOW, IPT_BUTTON3 ) PORT_PLAYER(2) PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x4000)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_BUTTON4 ) PORT_PLAYER(2) PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x8000)
	PORT_BIT( 0x3000, IP_ACTIVE_LOW, IPT_BUTTON_AB ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button1@Button2)") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x3000)
	PORT_BIT( 0x5000, IP_ACTIVE_LOW, IPT_BUTTON_AC ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button1@Button3)") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x5000)
	PORT_BIT( 0x9000, IP_ACTIVE_LOW, IPT_BUTTON_AD ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button1@Button4)") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x9000)	
	PORT_BIT( 0x2000+0x4000, IP_ACTIVE_LOW, IPT_BUTTON_BC ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button2@Button3)") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x6000)
	PORT_BIT( 0x2000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_BD ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button2@Button4)") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0xA000)
	PORT_BIT( 0x4000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_CD ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button3@Button4)") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0xC000)
	PORT_BIT( 0x1000+0x2000+0x4000, IP_ACTIVE_LOW, IPT_BUTTON_ABC ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button1@Button2@Button3)") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0x7000)
	PORT_BIT( 0x1000+0x2000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_ABD ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button1@Button2@Button4)") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0xB000)
	PORT_BIT( 0x1000+0x4000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_ACD ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button1@Button3@Button4)") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0xD000)
	PORT_BIT( 0x2000+0x4000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_BCD ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button2@Button3@Button4)") PORT_CONDITION("P2", 0xF000, NOTEQUALS, 0xE000)
	PORT_BIT( 0x1000+0x2000+0x4000+0x8000, IP_ACTIVE_LOW, IPT_BUTTON_ABCD ) PORT_PLAYER(2) PORT_NAME("@P2 버튼 조합 (@Button1@Button2@Button3@Button4)") PORT_CONDITION("P2", 0xF000, EQUALS, 0xF000)


	PORT_MODIFY("SYSTEM")
	PORT_BIT( 0x00ff, IP_ACTIVE_LOW, IPT_UNUSED )
	PORT_BIT( 0x0100, IP_ACTIVE_LOW, IPT_START1 )
	PORT_BIT( 0x0200, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("Next Game") PORT_CODE(KEYCODE_3)
	PORT_BIT( 0x0400, IP_ACTIVE_LOW, IPT_START2 )
	PORT_BIT( 0x0800, IP_ACTIVE_LOW, IPT_OTHER ) PORT_NAME("Previous Game") PORT_CODE(KEYCODE_4)
	PORT_BIT( 0x7000, IP_ACTIVE_HIGH, IPT_CUSTOM ) PORT_CUSTOM_MEMBER(neogeo_base_state, get_memcard_status)
	PORT_BIT( 0x8000, IP_ACTIVE_LOW, IPT_CUSTOM ) /* Hardware type (AES=0, MVS=1). Some games check this and show a piracy warning screen if the hardware and BIOS don't match */
INPUT_PORTS_END

/***********************************************************************************************************************
 POWER INSTINCT MATRIMELEE
*************************************************************************************************************************/
ROM_START( matrimn )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266-p1d.bin", 0x000000, 0x100000, CRC(7be60e6b))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END

ROM_START( matrimh2 )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266h2-p1d.bin", 0x000000, 0x100000, CRC(1e59c746))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END
 
ROM_START( matrimeh )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266eh-p1d.bin", 0x000000, 0x100000, CRC(993257bb))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

         

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END
 
ROM_START( matrimb )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266-p1b.bin", 0x000000, 0x100000, CRC(4a218dee))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))
	 
//	 NEO_BIOS_AUDIO_64K( "266-m1n.bin", CRC(09327db8) )
	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END

ROM_START( pima )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266a-p1d.bin", 0x000000, 0x100000, CRC(f6d1639e))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END

ROM_START( pimbd )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266bd-p1d.bin", 0x000000, 0x100000, CRC(70815d65))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END

ROM_START( pimehc )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266ehc-p1d.bin", 0x000000, 0x100000, CRC(090fbe25))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END

ROM_START( pimehh )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266ehh-p1d.bin", 0x000000, 0x100000, CRC(5710d0cf))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END


ROM_START( pimh )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266h-p1d.bin", 0x000000, 0x100000, CRC(7f33f402))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END

ROM_START( pimhad )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266had-p1d.bin", 0x000000, 0x100000, CRC(a2a92936))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END

ROM_START( pimhar )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266har-p1d.bin", 0x000000, 0x100000, CRC(24f917cd))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END

ROM_START( pimsc )
   ROM_REGION( 0x500000, "cslot1:maincpu", ROMREGION_BE|ROMREGION_16BIT )
   ROM_LOAD16_WORD_SWAP( "266sc-p1d.bin", 0x000000, 0x100000, CRC(b1117376))
   ROM_LOAD16_WORD_SWAP( "266-p2d.bin", 0x100000, 0x400000, CRC(b0132cef))

   NEO_SFIX_128K( "266-s1.bin", CRC(aff2a3be))

	 NEO_BIOS_AUDIO_128K( "266-m1d.bin", CRC(d2f3742d) )
	
	 ROM_REGION( 0x1000000, "cslot1:ymsnd", 0 )
	 ROM_LOAD            ( "266-v1d.bin", 0x000000, 0x400000, CRC(352b0a07) )
	 ROM_LOAD16_WORD_SWAP( "266-v2d.bin", 0x400000, 0x400000, CRC(1e9bd59e) )
	 ROM_LOAD            ( "266-v3d.bin", 0x800000, 0x400000, CRC(e8362fcc) )
	 ROM_LOAD16_WORD_SWAP( "266-v4d.bin", 0xc00000, 0x400000, CRC(c8c79b19) )

   

   ROM_REGION( 0x4000000, "cslot1:sprites", 0 )
   ROM_LOAD16_BYTE( "266-c1d.bin", 0x0000000, 0x800000, CRC(1db1837e))
   ROM_LOAD16_BYTE( "266-c2d.bin", 0x0000001, 0x800000, CRC(b834dd89))
   ROM_LOAD16_BYTE( "266-c3d.bin", 0x1000000, 0x800000, CRC(f31d68d4))
   ROM_LOAD16_BYTE( "266-c4d.bin", 0x1000001, 0x800000, CRC(58cfb6e9))
   ROM_LOAD16_BYTE( "266-c5d.bin", 0x2000000, 0x800000, CRC(f3c0e3fd))
   ROM_LOAD16_BYTE( "266-c6d.bin", 0x2000001, 0x800000, CRC(b53c8dcf))
   ROM_LOAD16_BYTE( "266-c7d.bin", 0x3000000, 0x800000, CRC(7866197c))
   ROM_LOAD16_BYTE( "266-c8d.bin", 0x3000001, 0x800000, CRC(a9ff5b5c))
ROM_END

GAME( 2002, matrimn,   neogeo, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (Decrypted)" , MACHINE_SUPPORTS_SAVE)
GAME( 2002, matrimh2, matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (Debug & Quick Menu in Home-Mode)", MACHINE_SUPPORTS_SAVE)
GAME( 2002, matrimeh, matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (Max Power)" , MACHINE_SUPPORTS_SAVE)
GAME( 2002, matrimb,  matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (Hero)" , MACHINE_SUPPORTS_SAVE)
GAME( 2002, pima,     matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (MVS protection removed and NrX freeze problem fixed)" , MACHINE_SUPPORTS_SAVE)
GAME( 2002, pimbd,    matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (Can choose Sissy, Jimmy, Jones, Lynn and Elias)" , MACHINE_SUPPORTS_SAVE)
GAME( 2002, pimehc,   matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (Power always max - MVS protection removed)" , MACHINE_SUPPORTS_SAVE)
GAME( 2002, pimehh,   matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (Can choose Jimmy, Jones, Lynn and Elias - power always max - MVS protection removed)" , MACHINE_SUPPORTS_SAVE)
GAME( 2002, pimh,     matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (MVS protection removed - debug menues enabled - bug fix - can choose rotd chars)" , MACHINE_SUPPORTS_SAVE)
GAME( 2002, pimhad,   matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (MVS protection removed - debug menues enabled - bug fix - can choose rotd chars + Sissy)" , MACHINE_SUPPORTS_SAVE)
GAME( 2002, pimhar,   matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (MVS protection removed - useless data removed - debug menues enabled - bug fix - NRX demo loop freeze fixed)" , MACHINE_SUPPORTS_SAVE)
GAME( 2002, pimsc,    matrimn, neobase_ek, 	neo_ek, mvs_led_state,          empty_init, ROT0, "Noise Factory / Atlus Corporation", "Power Instinct Matrimelee (Can choose Jimmy, Jones, Lynn and Elias - MVS protection removed)" , MACHINE_SUPPORTS_SAVE)

