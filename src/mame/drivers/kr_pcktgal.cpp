// license:BSD-3-Clause
// copyright-holders:Robbbert

ROM_START( pcktgalk )
	ROM_REGION( 0x14000, "maincpu", 0 )
	ROM_LOAD( "eb04.j7",   0x10000, 0x4000, CRC(8215d60d) SHA1(ac26dfce7e215be21f2a17f864c5e966b8b8322e) )
	ROM_CONTINUE(   0x04000, 0xc000)

	ROM_REGION( 0x18000, "audiocpu", 0 )
	ROM_LOAD( "eb03.f2",   0x10000, 0x8000, CRC(cb029b02) SHA1(fbb3da08ed05ae73fbeeb13e0e2ff735aaf83db8) )
	ROM_CONTINUE(   0x08000, 0x8000 )

	ROM_REGION( 0x20000, "gfx1", 0 )
	ROM_LOAD( "eb01k.rom",   0x00000, 0x10000, CRC(3b9f8e29) SHA1(b7ae6d72b9fc1f4964b673346d76a9d24cd5606c) )
	ROM_LOAD( "eb02.d12",   0x10000, 0x10000, CRC(a9dcd339) SHA1(245824ab86cdfe4b842ce1be0af60f2ff4c6ae07) )

	ROM_REGION( 0x10000, "gfx2", 0 )
	ROM_LOAD( "eb00.a1",   0x00000, 0x10000, CRC(6c1a14a8) SHA1(03201197304c5f1d854b8c4f4a5c78336b51f872) )

	ROM_REGION( 0x0400, "proms", 0 )
	ROM_LOAD( "eb05.k14",     0x0000, 0x0200, CRC(3b6198cb) SHA1(d32b364cfce99637998ca83ad21783f80364dd65) )
	ROM_LOAD( "eb06.k15",     0x0200, 0x0200, CRC(1fbd4b59) SHA1(84e20329003cf09b849b49e1d83edc330d49f404) )
ROM_END

HACK( 1987, pcktgalk, pcktgal, pcktgal, pcktgal, pcktgal_state, pcktgal,  ROT0, "Hack", "Pocket Gal (Korean)", MACHINE_SUPPORTS_SAVE )

