/****************************************************
                    Metamoqester
*****************************************************/

ROM_START( metmqstrs01 )
	ROM_REGION( 0x280000, "maincpu", 0 )        /* 68000 code */
	ROM_LOAD16_WORD_SWAP( "bp947hc01.u25", 0x000000, 0x80000, CRC(748cc514) SHA1(11d882e77a539407c314f087386e50d691a6bc0b) )
	ROM_LOAD16_WORD_SWAP( "bp947a.u28", 0x100000, 0x80000, CRC(8c55decf) SHA1(76c6ce4c8e621273258d31ceb9ec4442fcf1a393) )
	ROM_LOAD16_WORD_SWAP( "bp947a.u29", 0x200000, 0x80000, CRC(cf0f3f3b) SHA1(49a3c0e7536edd53bbf09353e43e9166d736b3f4) )

	ROM_REGION( 0x40000, "audiocpu", 0 )        /* Z80 code */
	ROM_LOAD( "bp947a.u20",  0x00000, 0x40000, CRC(a4a36170) SHA1(ae55094518bd968ea0d04613a133c1421e412012) )

	ROM_REGION( 0x800000 * 2, "sprites0", 0 )        /* Sprites: * 2 */
	ROM_LOAD( "bp947a.u49", 0x000000, 0x200000, CRC(09749531) SHA1(6deeed2712241611ec3202c49a66beed28698af8) )
	ROM_LOAD( "bp947a.u50", 0x200000, 0x200000, CRC(19cea8b2) SHA1(87fb29458074f0e4852237e0184b8b3b44b0eb29) )
	ROM_LOAD( "bp947a.u51", 0x400000, 0x200000, CRC(c19bed67) SHA1(ac664a15512c0e8c8b701833aede95f53cd46a45) )
	ROM_LOAD( "bp947a.u52", 0x600000, 0x200000, CRC(70c64875) SHA1(1c20ab100ccfdf42c97a25e4deb9041b83f5ca8d) )

	ROM_REGION( 0x100000, "layer0", 0 ) /* Layer 0 */
	ROM_LOAD( "bp947a.u48", 0x000000, 0x100000, CRC(04ff6a3d) SHA1(7187db436f7a2ab59a3f5c6ab297b3d740e20f1d) )  // FIRST AND SECOND HALF IDENTICAL
	ROM_CONTINUE(           0x000000, 0x100000             )

	ROM_REGION( 0x100000, "layer1", 0 ) /* Layer 1 */
	ROM_LOAD( "bp947hc01.u47", 0x000000, 0x100000, CRC(b479e5e1) SHA1(311abcdaf56c0e79f7e24e53c72d1242edbfb245) )  // FIRST AND SECOND HALF IDENTICAL
	ROM_CONTINUE(           0x000000, 0x100000             )

	ROM_REGION( 0x100000, "layer2", 0 ) /* Layer 2 */
	ROM_LOAD( "bp947a.u46", 0x000000, 0x100000, CRC(0f9c906e) SHA1(03872e8be28637df66373bddb04ed91de4f9db75) )  // FIRST AND SECOND HALF IDENTICAL
	ROM_CONTINUE(           0x000000, 0x100000             )

	ROM_REGION( 0x100000, "oki1", 0 )   /* OKIM6295 #1 Samples */
	ROM_LOAD( "bp947a.u42", 0x000000, 0x100000, CRC(2ce8ff2a) SHA1(8ef8c5b7d4a0e60c980c2962e75f7977faafa311) )  // FIRST AND SECOND HALF IDENTICAL
	ROM_CONTINUE(           0x000000, 0x100000             )

	ROM_REGION( 0x100000, "oki2", 0 )   /* OKIM6295 #2 Samples */
	ROM_LOAD( "bp947a.u37", 0x000000, 0x100000, CRC(c3077c8f) SHA1(0a76316a81b7de78279b859549eb5161a721ac71) )  // FIRST AND SECOND HALF IDENTICAL
	ROM_CONTINUE(           0x000000, 0x100000             )
ROM_END

/*************************************
 *
 *  Game driver(s)
 *
 *************************************/
// Proyecto Shadows Mame Build Plus
/*    YEAR  NAME           PARENT    MACHINE     INPUT     INIT            MONITOR COMPANY         FULLNAME FLAGS */
// Metamoqester
GAME( 1995, metmqstrs01,   metmqstr, metmqstr,   metmqstr, cave_state, init_metmqstr,  ROT0,   "Banpresto / Pandorabox",  "Metamoqester (Korean Translator)",   MACHINE_SUPPORTS_SAVE )
