/* gen - actual generation (writing) of flex scanners */

/* SPDX-License-Identifier: BSD-3-Clause-flex */

/*  Copyright (c) 1990 The Regents of the University of California. */
/*  All rights reserved. */

/*  This code is derived from software contributed to Berkeley by */
/*  Vern Paxson. */

/*  The United States Government has rights in this work pursuant */
/*  to contract no. DE-AC03-76SF00098 between the United States */
/*  Department of Energy and the University of California. */

/*  This file is part of flex. */

/*  Redistribution and use in source and binary forms, with or without */
/*  modification, are permitted provided that the following conditions */
/*  are met: */

/*  1. Redistributions of source code must retain the above copyright */
/*     notice, this list of conditions and the following disclaimer. */
/*  2. Redistributions in binary form must reproduce the above copyright */
/*     notice, this list of conditions and the following disclaimer in the */
/*     documentation and/or other materials provided with the distribution. */

/*  Neither the name of the University nor the names of its contributors */
/*  may be used to endorse or promote products derived from this software */
/*  without specific prior written permission. */

/*  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR */
/*  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED */
/*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR */
/*  PURPOSE. */

#ಅನ್ತರ್ಭಾವ "flexdef.h"
#ಅನ್ತರ್ಭಾವ "tables.h"

/* These typedefs are only used for computing footprint sizes,
 * You need to make sure they match reality in the skeleton file to
 * get accurate numbers, but they don't otherwise matter.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ YY_CHAR;
ರಚನೆ yy_trans_info {int32_t yy_verify; int32_t yy_nxt;};

/* declare functions that have forward references */

ಸ್ಥಿರ ಶೂನ್ಯ genecs(ಶೂನ್ಯ);

ರಚನೆ packtype_t *optimize_pack(size_t sz)
{
	/* FIXME: There's a 32-bit assumption lurking here */
	ಸ್ಥಿರ ರಚನೆ packtype_t ಹೊರಹೋಗು;
	ಆದರೆ (sz == 0) {
		ಹೊರಹೋಗು.name  = ctrl.long_align ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		ಹೊರಹೋಗು.ಅಗಲ = ctrl.long_align ? 32 : 16;
	} ಇಲ್ಲದಿದ್ದರೆ {
		ಹೊರಹೋಗು.name = (ctrl.long_align || sz >= INT16_MAX) ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		ಹೊರಹೋಗು.ಅಗಲ = (ctrl.long_align || sz >= INT16_MAX) ? 32 : 16;
	}
	ಹಿಂತಿರುಗಿ &ಹೊರಹೋಗು;
}

/* Almost everything is done in terms of arrays starting at 1, so provide
 * a null entry for the zero element of all C arrays.  (The exception
 * to this is that the fast table representation generally uses the
 * 0 elements of its arrays, too.)
 */

/** Make the table for possible eol matches.
 *  @return the newly allocated rule_can_match_eol table
 */
ಸ್ಥಿರ ರಚನೆ yytbl_ದತ್ತಾಂಶ *mkeoltbl (ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ     i;
	flex_int8_t *tdata = 0;
	ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl;

	tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	yytbl_ದತ್ತಾಂಶ_init (tbl, YYTD_ID_ನಿಯಮ_CAN_ಹೊಂದಿಕೆ_EOL);
	tbl->td_flags = YYTD_DATA8;
	tbl->td_lolen = (flex_uint32_t) (ಅಂಕೆ_ನಿಯಮಗಳು + 1);
	tbl->td_ದತ್ತಾಂಶ = tdata =
		ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(tbl->td_lolen, ಗಾತ್ರ (flex_int8_t));

	ಗಾಗಿ (i = 1; i <= ಅಂಕೆ_ನಿಯಮಗಳು; i++)
		tdata[i] = ನಿಯಮ_has_nl[i] ? 1 : 0;

	ಹಿಂತಿರುಗಿ tbl;
}

/* Generate the table for possible eol matches. */
ಸ್ಥಿರ ಶೂನ್ಯ geneoltbl (ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ     i;
	ರಚನೆ packtype_t *ptype = optimize_pack(ಅಂಕೆ_ನಿಯಮಗಳು);

	outn ("m4_ifdef( [[M4_MODE_YYLINENO]],[[");
	ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_EOLTABLE_TYPE]], [[%s]])\n", ptype->name);
	ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_EOLTABLE_SIZE]], [[%d]])", ಅಂಕೆ_ನಿಯಮಗಳು + 1);
	outn ("m4_define([[M4_HOOK_EOLTABLE_BODY]], [[m4_dnl");

	ಆದರೆ (gentables) {
		ಗಾಗಿ (i = 1; i <= ಅಂಕೆ_ನಿಯಮಗಳು; i++) {
			ಹೊರಹೋಗು_dec ("%d, ", ನಿಯಮ_has_nl[i] ? 1 : 0);
			/* format nicely, 20 numbers per line. */
			ಆದರೆ ((i % 20) == 19)
				ಹೊರಹೋಗು ("\n    ");
		}
	}
	footprint += ಅಂಕೆ_ನಿಯಮಗಳು * ptype->ಅಗಲ;
	outn ("]])");
	outn ("]])");
}


/** mkctbl - make full speed compressed transition table
 * This is an array of structs; each struct a pair of integers.
 * You should call mkssltbl() immediately after this.
 * Then, I think, mkecstbl(). Arrrg.
 * @return the newly allocated trans table
 */

ಸ್ಥಿರ ರಚನೆ yytbl_ದತ್ತಾಂಶ *mkctbl (ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ i;
	ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl = 0;
	flex_int32_t *tdata = 0, curr = 0;
	ಪೂರ್ಣಾಂಕ     ಕೊನೆ_ದ_ಬಫರ್_action = ಅಂಕೆ_ನಿಯಮಗಳು + 1;

	ರಚನೆ packtype_t *ptype = optimize_pack(tblend + 2 + 1);
	ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_MKCTBL_TYPE]], [[%s]])", ptype->name);

	tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	yytbl_ದತ್ತಾಂಶ_init (tbl, YYTD_ID_TRANSITION);
	tbl->td_flags = YYTD_DATA32 | YYTD_STRUCT;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (tblend + 2 + 1);	/* number of structs */

	tbl->td_ದತ್ತಾಂಶ = tdata =
		ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(tbl->td_lolen * 2, ಗಾತ್ರ (flex_int32_t));

	/* We want the transition to be represented as the offset to the
	 * next state, not the actual state number, which is what it currently
	 * is.  The offset is base[nxt[i]] - (base of current state)].  That's
	 * just the difference between the starting points of the two involved
	 * states (to - from).
	 *
	 * First, though, we need to find some way to put in our end-of-buffer
	 * flags and states.  We do this by making a state with absolutely no
	 * transitions.  We put it at the end of the table.
	 */

	/* We need to have room in nxt/chk for two more slots: One for the
	 * action and one for the end-of-buffer transition.  We now *assume*
	 * that we're guaranteed the only character we'll try to index this
	 * nxt/chk pair with is EOB, i.e., 0, so we don't have to make sure
	 * there's room for jam entries for other characters.
	 */

	ಆಗ (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	ಆಗ (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	ತಳ[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = ಕೊನೆ_ದ_ಬಫರ್_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	ಗಾಗಿ (i = 0; i <= lastdfa; ++i) {
		ಪೂರ್ಣಾಂಕ     anum = dfaacc[i].dfaacc_state;
		ಪೂರ್ಣಾಂಕ     ಸ್ಥಾನಾಂತರ = ತಳ[i];

		chk[ಸ್ಥಾನಾಂತರ] = EOB_POSITION;
		chk[ಸ್ಥಾನಾಂತರ - 1] = ACTION_POSITION;
		nxt[ಸ್ಥಾನಾಂತರ - 1] = anum;	/* action number */
	}

	ಗಾಗಿ (i = 0; i <= tblend; ++i) {
		ಆದರೆ (chk[i] == EOB_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = ತಳ[lastdfa + 1] - i;
		}

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (chk[i] == ACTION_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = nxt[i];
		}

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (chk[i] > numecs || chk[i] == 0) {
			tdata[curr++] = 0;
			tdata[curr++] = 0;
		}
		ಇಲ್ಲದಿದ್ದರೆ {		/* verify, transition */

			tdata[curr++] = chk[i];
			tdata[curr++] = ತಳ[nxt[i]] - (i - chk[i]);
		}
	}

	/* Here's the final, end-of-buffer state. */
	tdata[curr++] = chk[tblend + 1];
	tdata[curr++] = nxt[tblend + 1];

	tdata[curr++] = chk[tblend + 2];
	tdata[curr++] = nxt[tblend + 2];

	ಹಿಂತಿರುಗಿ tbl;
}


/** Make start_state_list table.
 *  @return the newly allocated start_state_list table
 */
ಸ್ಥಿರ ರಚನೆ yytbl_ದತ್ತಾಂಶ *mkssltbl (ಶೂನ್ಯ)
{
	ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl = 0;
	flex_int32_t *tdata = 0;
	flex_int32_t i;

	tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	yytbl_ದತ್ತಾಂಶ_init (tbl, YYTD_ID_ಆರಂಭ_STATE_LIST);
	tbl->td_flags = YYTD_DATA32 | YYTD_PTRANS;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (lastsc * 2 + 1);

	tbl->td_ದತ್ತಾಂಶ = tdata =
		ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(tbl->td_lolen, ಗಾತ್ರ (flex_int32_t));

	ಗಾಗಿ (i = 0; i <= lastsc * 2; ++i)
		tdata[i] = ತಳ[i];

	ಹಿಂತಿರುಗಿ tbl;
}



/* genctbl - generates full speed compressed transition table */

ಸ್ಥಿರ ಶೂನ್ಯ genctbl(ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ i;
	ಪೂರ್ಣಾಂಕ     ಕೊನೆ_ದ_ಬಫರ್_action = ಅಂಕೆ_ನಿಯಮಗಳು + 1;

	/* Table of verify for transition and offset to next state. */
	ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_TRANSTABLE_SIZE]], [[%d]])", tblend + 2 + 1);
	outn ("m4_define([[M4_HOOK_TRANSTABLE_BODY]], [[m4_dnl");

	/* We want the transition to be represented as the offset to the
	 * next state, not the actual state number, which is what it currently
	 * is.  The offset is base[nxt[i]] - (base of current state)].  That's
	 * just the difference between the starting points of the two involved
	 * states (to - from).
	 *
	 * First, though, we need to find some way to put in our end-of-buffer
	 * flags and states.  We do this by making a state with absolutely no
	 * transitions.  We put it at the end of the table.
	 */

	/* We need to have room in nxt/chk for two more slots: One for the
	 * action and one for the end-of-buffer transition.  We now *assume*
	 * that we're guaranteed the only character we'll try to index this
	 * nxt/chk pair with is EOB, i.e., 0, so we don't have to make sure
	 * there's room for jam entries for other characters.
	 */

	ಆಗ (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	ಆಗ (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	ತಳ[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = ಕೊನೆ_ದ_ಬಫರ್_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	ಗಾಗಿ (i = 0; i <= lastdfa; ++i) {
		ಪೂರ್ಣಾಂಕ     anum = dfaacc[i].dfaacc_state;
		ಪೂರ್ಣಾಂಕ     ಸ್ಥಾನಾಂತರ = ತಳ[i];

		chk[ಸ್ಥಾನಾಂತರ] = EOB_POSITION;
		chk[ಸ್ಥಾನಾಂತರ - 1] = ACTION_POSITION;
		nxt[ಸ್ಥಾನಾಂತರ - 1] = anum;	/* action number */
	}

	ಗಾಗಿ (i = 0; i <= tblend; ++i) {
		ಆದರೆ (chk[i] == EOB_POSITION)
			transition_struct_ಹೊರಹೋಗು (0, ತಳ[lastdfa + 1] - i);

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (chk[i] == ACTION_POSITION)
			transition_struct_ಹೊರಹೋಗು (0, nxt[i]);

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (chk[i] > numecs || chk[i] == 0)
			transition_struct_ಹೊರಹೋಗು (0, 0);	/* unused slot */

		ಇಲ್ಲದಿದ್ದರೆ		/* verify, transition */
			transition_struct_ಹೊರಹೋಗು (chk[i],
					       ತಳ[nxt[i]] - (i -
							       chk[i]));
	}


	/* Here's the final, end-of-buffer state. */
	transition_struct_ಹೊರಹೋಗು (chk[tblend + 1], nxt[tblend + 1]);
	transition_struct_ಹೊರಹೋಗು (chk[tblend + 2], nxt[tblend + 2]);

	outn ("]])");
	footprint += ಗಾತ್ರ(ರಚನೆ yy_trans_info) * (tblend + 2 + 1);

	ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_STARTTABLE_SIZE]], [[%d]])", lastsc * 2 + 1);
	ಆದರೆ (gentables) {
		outn ("m4_define([[M4_HOOK_STARTTABLE_BODY]], [[m4_dnl");
		ಗಾಗಿ (i = 0; i <= lastsc * 2; ++i)
			ಹೊರಹೋಗು_dec ("M4_HOOK_STATE_ENTRY_FORMAT(%d)", ತಳ[i]);

		dataend (ಖಾಲಿ);
		outn("]])");
		footprint +=  ಗಾತ್ರ(ರಚನೆ yy_trans_info *) * (lastsc * 2 + 1);
	}

	ಆದರೆ (ctrl.useecs)
		genecs ();
}


/* mkecstbl - Make equivalence-class tables.  */

ಸ್ಥಿರ ರಚನೆ yytbl_ದತ್ತಾಂಶ *mkecstbl (ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ i;
	ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl = 0;
	flex_int32_t *tdata = 0;

	tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	yytbl_ದತ್ತಾಂಶ_init (tbl, YYTD_ID_EC);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) ctrl.csize;

	tbl->td_ದತ್ತಾಂಶ = tdata =
		ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(tbl->td_lolen, ಗಾತ್ರ (flex_int32_t));

	ಗಾಗಿ (i = 1; i < ctrl.csize; ++i) {
		ecgroup[i] = ABS (ecgroup[i]);
		tdata[i] = ecgroup[i];
	}

	ಹಿಂತಿರುಗಿ tbl;
}

/* Generate equivalence-class tables. */

ಸ್ಥಿರ ಶೂನ್ಯ genecs(ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ ch, ಅಡ್ಡಸಾಲು;
	ಪೂರ್ಣಾಂಕ     numrows;

	ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_ECSTABLE_SIZE]], [[%d]])", ctrl.csize);
	outn ("m4_define([[M4_HOOK_ECSTABLE_BODY]], [[m4_dnl");

	ಗಾಗಿ (ch = 1; ch < ctrl.csize; ++ch) {
		ecgroup[ch] = ABS (ecgroup[ch]);
		mkdata (ecgroup[ch]);
	}

	dataend (ಖಾಲಿ);
	outn("]])");
	footprint += ಗಾತ್ರ(YY_CHAR) * ctrl.csize;

	ಆದರೆ (env.trace) {
		fputs (_("\n\nEquivalence Classes:\n\n"), stderr);

		/* Print in 8 columns */
		numrows = ctrl.csize / 8;

		ಗಾಗಿ (ಅಡ್ಡಸಾಲು = 0; ಅಡ್ಡಸಾಲು < numrows; ++ಅಡ್ಡಸಾಲು) {
			ಗಾಗಿ (ch = ಅಡ್ಡಸಾಲು; ch < ctrl.csize; ch += numrows) {
				fprintf (stderr, "%4s = %-2d",
					 readable_form (ch), ecgroup[ch]);

				putc (' ', stderr);
			}

			putc ('\n', stderr);
		}
	}
}

/* mkftbl - make the full table and return the struct .
 * you should call mkecstbl() after this.
 */

ಸ್ಥಿರ ರಚನೆ yytbl_ದತ್ತಾಂಶ *mkftbl(ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ i;
	ಪೂರ್ಣಾಂಕ     ಕೊನೆ_ದ_ಬಫರ್_action = ಅಂಕೆ_ನಿಯಮಗಳು + 1;
	ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl;
	flex_int32_t *tdata = 0;

	tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	yytbl_ದತ್ತಾಂಶ_init (tbl, YYTD_ID_ACCEPT);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;	/* it's a one-dimensional array */
	tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);

	tbl->td_ದತ್ತಾಂಶ = tdata =
		ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(tbl->td_lolen, ಗಾತ್ರ (flex_int32_t));

	dfaacc[ಕೊನೆ_ದ_ಬಫರ್_state].dfaacc_state = ಕೊನೆ_ದ_ಬಫರ್_action;

	ಗಾಗಿ (i = 1; i <= lastdfa; ++i) {
		ಪೂರ್ಣಾಂಕ anum = dfaacc[i].dfaacc_state;

		tdata[i] = anum;

		ಆದರೆ (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	ಹಿಂತಿರುಗಿ tbl;
}


/* genftbl - generate full transition table */

ಸ್ಥಿರ ಶೂನ್ಯ genftbl(ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ i;
	ಪೂರ್ಣಾಂಕ     ಕೊನೆ_ದ_ಬಫರ್_action = ಅಂಕೆ_ನಿಯಮಗಳು + 1;
	ರಚನೆ packtype_t *ptype = optimize_pack(ಅಂಕೆ_ನಿಯಮಗಳು + 1);

	dfaacc[ಕೊನೆ_ದ_ಬಫರ್_state].dfaacc_state = ಕೊನೆ_ದ_ಬಫರ್_action;

	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", lastdfa + 1);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	ಗಾಗಿ (i = 1; i <= lastdfa; ++i) {
		ಪೂರ್ಣಾಂಕ anum = dfaacc[i].dfaacc_state;

		mkdata (anum);

		ಆದರೆ (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	dataend (ಖಾಲಿ);
	outn("]])");
	footprint += (lastdfa + 1) * ptype->ಅಗಲ;

	ಆದರೆ (ctrl.useecs)
		genecs ();

	/* Don't have to dump the actual full table entries - they were
	 * created on-the-fly.
	 */
}

/* gentabs - generate data statements for the transition tables */

ಸ್ಥಿರ ಶೂನ್ಯ gentabs(ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ     sz, i, j, k, *accset, nacc, *acc_array, ಒಟ್ಟು_ಸ್ಥಿತಿಗಳು;
	ಪೂರ್ಣಾಂಕ     ಕೊನೆ_ದ_ಬಫರ್_action = ಅಂಕೆ_ನಿಯಮಗಳು + 1;
	ರಚನೆ yytbl_ದತ್ತಾಂಶ *yyacc_tbl = 0, *yymeta_tbl = 0, *yybase_tbl = 0,
	    *yydef_tbl = 0, *yynxt_tbl = 0, *yychk_tbl = 0, *yyacclist_tbl=0;
	flex_int32_t *yyacc_ದತ್ತಾಂಶ = 0, *yybase_ದತ್ತಾಂಶ = 0, *yydef_ದತ್ತಾಂಶ = 0,
	    *yynxt_ದತ್ತಾಂಶ = 0, *yychk_ದತ್ತಾಂಶ = 0, *yyacclist_ದತ್ತಾಂಶ=0;
	flex_int32_t yybase_curr = 0, yyacclist_curr=0,yyacc_curr=0;
	ರಚನೆ packtype_t *ptype;

	acc_array = allocate_integer_array (current_max_dfas);
	nummt = 0;

	/* The compressed table format jams by entering the "jam state",
	 * losing information about the previous state in the process.
	 * In order to recover the previous state, we effectively need
	 * to keep backing-up information.
	 */
	++ಅಂಕೆ_backing_ಮೇಲೆ;

	ಆದರೆ (reject) {
		/* Write out accepting list and pointer list.

		 * First we generate the "yy_acclist" array.  In the process,
		 * we compute the indices that will go into the "yy_accept"
		 * array, and save the indices in the dfaacc array.
		 */
		ಪೂರ್ಣಾಂಕ     EOB_accepting_list[2];

		/* Set up accepting structures for the End Of Buffer state. */
		EOB_accepting_list[0] = 0;
		EOB_accepting_list[1] = ಕೊನೆ_ದ_ಬಫರ್_action;
		accsiz[ಕೊನೆ_ದ_ಬಫರ್_state] = 1;
		dfaacc[ಕೊನೆ_ದ_ಬಫರ್_state].dfaacc_ಗಣ =
		    EOB_accepting_list;

		sz = MAX (numas, 1) + 1;
		ptype = optimize_pack(sz);
		ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_ACCLIST_TYPE]], [[%s]])", ptype->name);
		ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_ACCLIST_SIZE]], [[%d]])", sz);
		outn ("m4_define([[M4_HOOK_ACCLIST_BODY]], [[m4_dnl");

		yyacclist_tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1,ಗಾತ್ರ(ರಚನೆ yytbl_ದತ್ತಾಂಶ));
		yytbl_ದತ್ತಾಂಶ_init (yyacclist_tbl, YYTD_ID_ACCLIST);
		yyacclist_tbl->td_lolen  = (flex_uint32_t) (MAX(numas,1) + 1);
		yyacclist_tbl->td_ದತ್ತಾಂಶ = yyacclist_ದತ್ತಾಂಶ =
		    ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(yyacclist_tbl->td_lolen, ಗಾತ್ರ (flex_int32_t));
		yyacclist_curr = 1;

		j = 1;		/* index into "yy_acclist" array */

		ಗಾಗಿ (i = 1; i <= lastdfa; ++i) {
			acc_array[i] = j;

			ಆದರೆ (accsiz[i] != 0) {
				accset = dfaacc[i].dfaacc_ಗಣ;
				nacc = accsiz[i];

				ಆದರೆ (env.trace)
					fprintf (stderr,
						 _("state # %d accepts: "),
						 i);

				ಗಾಗಿ (k = 1; k <= nacc; ++k) {
					ಪೂರ್ಣಾಂಕ     accnum = accset[k];

					++j;

					ಆದರೆ (variable_trailing_context_ನಿಯಮಗಳು
					    && !(accnum &
						 YY_TRAILING_ತಲೆ_ಮುಖವಾಡ)
					    && accnum > 0
					    && accnum <= ಅಂಕೆ_ನಿಯಮಗಳು
					    && ನಿಯಮ_type[accnum] ==
					    ನಿಯಮ_VARIABLE) {
						/* Special hack to flag
						 * accepting number as part
						 * of trailing context rule.
						 */
						accnum |= YY_TRAILING_ಮುಖವಾಡ;
					}

					mkdata (accnum);
					yyacclist_ದತ್ತಾಂಶ[yyacclist_curr++] = accnum;

					ಆದರೆ (env.trace) {
						fprintf (stderr, "[%d]",
							 accset[k]);

						ಆದರೆ (k < nacc)
							fputs (", ",
							       stderr);
						ಇಲ್ಲದಿದ್ದರೆ
							putc ('\n',
							      stderr);
					}
				}
			}
		}

		/* add accepting number for the "jam" state */
		acc_array[i] = j;

		dataend (ಖಾಲಿ);
		outn("]])");
		footprint += sz * ptype->ಅಗಲ;
		ಆದರೆ (tablesext) {
			yytbl_ದತ್ತಾಂಶ_compress (yyacclist_tbl);
			ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, yyacclist_tbl) < 0)
				flexerror (_("Could not write yyacclist_tbl"));
			yytbl_ದತ್ತಾಂಶ_destroy (yyacclist_tbl);
			yyacclist_tbl = ಖಾಲಿ;
		}
	}

	ಇಲ್ಲದಿದ್ದರೆ {
		dfaacc[ಕೊನೆ_ದ_ಬಫರ್_state].dfaacc_state =
		    ಕೊನೆ_ದ_ಬಫರ್_action;

		ಗಾಗಿ (i = 1; i <= lastdfa; ++i)
			acc_array[i] = dfaacc[i].dfaacc_state;

		/* add accepting number for jam state */
		acc_array[i] = 0;
	}

	/* Begin generating yy_accept */

	/* Spit out "yy_accept" array.  If we're doing "reject", it'll be
	 * pointers into the "yy_acclist" array.  Otherwise it's actual
	 * accepting numbers.  In either case, we just dump the numbers.
	 */

	/* "lastdfa + 2" is the size of "yy_accept"; includes room for C arrays
	 * beginning at 0 and for "jam" state.
	 */
	sz = lastdfa + 2;

	ಆದರೆ (reject)
		/* We put a "cap" on the table associating lists of accepting
		 * numbers with state numbers.  This is needed because we tell
		 * where the end of an accepting list is by looking at where
		 * the list for the next state starts.
		 */
		++sz;

	/* Note that this table is alternately defined if ctrl.fulltbl */
	ptype = optimize_pack(sz);
	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	yyacc_tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	yytbl_ದತ್ತಾಂಶ_init (yyacc_tbl, YYTD_ID_ACCEPT);
	yyacc_tbl->td_lolen = (flex_uint32_t) sz;
	yyacc_tbl->td_ದತ್ತಾಂಶ = yyacc_ದತ್ತಾಂಶ =
	    ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(yyacc_tbl->td_lolen, ಗಾತ್ರ (flex_int32_t));
	yyacc_curr=1;

	ಗಾಗಿ (i = 1; i <= lastdfa; ++i) {
		mkdata (acc_array[i]);
		yyacc_ದತ್ತಾಂಶ[yyacc_curr++] = acc_array[i];

		ಆದರೆ (!reject && env.trace && acc_array[i])
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, acc_array[i]);
	}

	/* Add entry for "jam" state. */
	mkdata (acc_array[i]);
	yyacc_ದತ್ತಾಂಶ[yyacc_curr++] = acc_array[i];

	ಆದರೆ (reject) {
		/* Add "cap" for the list. */
		mkdata (acc_array[i]);
		yyacc_ದತ್ತಾಂಶ[yyacc_curr++] = acc_array[i];
	}

	dataend (ಖಾಲಿ);
	outn ("]])");
	footprint += sz * ptype->ಅಗಲ;

	ಆದರೆ (tablesext) {
		yytbl_ದತ್ತಾಂಶ_compress (yyacc_tbl);
		ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, yyacc_tbl) < 0)
			flexerror (_("Could not write yyacc_tbl"));
	}
	yytbl_ದತ್ತಾಂಶ_destroy (yyacc_tbl);
	yyacc_tbl = ಖಾಲಿ;
	/* End generating yy_accept */

	ಆದರೆ (ctrl.useecs) {

		genecs ();
		ಆದರೆ (tablesext) {
			ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl;

			tbl = mkecstbl ();
			yytbl_ದತ್ತಾಂಶ_compress (tbl);
			ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ecstbl"));
			yytbl_ದತ್ತಾಂಶ_destroy (tbl);
			tbl = 0;
		}
	}

	ಆದರೆ (ctrl.usemecs) {
		/* Begin generating yy_meta */
		/* Write out meta-equivalence classes (used to index
		 * templates with).
		 */
		flex_int32_t *yymecs_ದತ್ತಾಂಶ = 0;
		yymeta_tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
		yytbl_ದತ್ತಾಂಶ_init (yymeta_tbl, YYTD_ID_META);
		yymeta_tbl->td_lolen = (flex_uint32_t) (numecs + 1);
		yymeta_tbl->td_ದತ್ತಾಂಶ = yymecs_ದತ್ತಾಂಶ =
		    ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(yymeta_tbl->td_lolen,
			   ಗಾತ್ರ (flex_int32_t));

		ಆದರೆ (env.trace)
			fputs (_("\n\nMeta-Equivalence Classes:\n"),
			       stderr);
		ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_MECSTABLE_SIZE]], [[%d]])", numecs+1);
		outn ("m4_define([[M4_HOOK_MECSTABLE_BODY]], [[m4_dnl");
 	
		ಗಾಗಿ (i = 1; i <= numecs; ++i) {
			ಆದರೆ (env.trace)
				fprintf (stderr, "%d = %d\n",
					 i, ABS (tecbck[i]));

			mkdata (ABS (tecbck[i]));
			yymecs_ದತ್ತಾಂಶ[i] = ABS (tecbck[i]);
		}

		dataend (ಖಾಲಿ);
		outn ("]])");
		footprint += ಗಾತ್ರ(YY_CHAR) * (numecs + 1);
		ಆದರೆ (tablesext) {
			yytbl_ದತ್ತಾಂಶ_compress (yymeta_tbl);
			ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, yymeta_tbl) < 0)
				flexerror (_("Could not write yymeta_tbl"));
		}
		yytbl_ದತ್ತಾಂಶ_destroy (yymeta_tbl);
		yymeta_tbl = ಖಾಲಿ;
		/* End generating yy_meta */
	}

	ಒಟ್ಟು_ಸ್ಥಿತಿಗಳು = lastdfa + numtemps;

	/* Begin generating yy_base */
	sz = ಒಟ್ಟು_ಸ್ಥಿತಿಗಳು + 1;
	ptype = optimize_pack(sz);
	ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_BASE_TYPE]], [[%s]])", ptype->name);
	ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_BASE_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_BASE_BODY]], [[m4_dnl");

	yybase_tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು (1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	yytbl_ದತ್ತಾಂಶ_init (yybase_tbl, YYTD_ID_ತಳ);
	yybase_tbl->td_lolen = (flex_uint32_t) (ಒಟ್ಟು_ಸ್ಥಿತಿಗಳು + 1);
	yybase_tbl->td_ದತ್ತಾಂಶ = yybase_ದತ್ತಾಂಶ =
	    ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(yybase_tbl->td_lolen,
		   ಗಾತ್ರ (flex_int32_t));
	yybase_curr = 1;

	ಗಾಗಿ (i = 1; i <= lastdfa; ++i) {
		ಪೂರ್ಣಾಂಕ d = def[i];

		ಆದರೆ (ತಳ[i] == JAMSTATE)
			ತಳ[i] = jambase;

		ಆದರೆ (d == JAMSTATE)
			def[i] = jamstate;

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d < 0) {
			/* Template reference. */
			++tmpuses;
			def[i] = lastdfa - d + 1;
		}

		mkdata (ತಳ[i]);
		yybase_ದತ್ತಾಂಶ[yybase_curr++] = ತಳ[i];
	}

	/* Generate jam state's base index. */
	mkdata (ತಳ[i]);
	yybase_ದತ್ತಾಂಶ[yybase_curr++] = ತಳ[i];

	ಗಾಗಿ (++i /* skip jam state */ ; i <= ಒಟ್ಟು_ಸ್ಥಿತಿಗಳು; ++i) {
		mkdata (ತಳ[i]);
		yybase_ದತ್ತಾಂಶ[yybase_curr++] = ತಳ[i];
		def[i] = jamstate;
	}

	dataend (ಖಾಲಿ);
	outn ("]])");
	footprint += sz * ptype->ಅಗಲ;

	ಆದರೆ (tablesext) {
		yytbl_ದತ್ತಾಂಶ_compress (yybase_tbl);
		ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, yybase_tbl) < 0)
			flexerror (_("Could not write yybase_tbl"));
	}
	yytbl_ದತ್ತಾಂಶ_destroy (yybase_tbl);
	yybase_tbl = ಖಾಲಿ;
	/* End generating yy_base */


	/* Begin generating yy_def */
	ptype = optimize_pack(ಒಟ್ಟು_ಸ್ಥಿತಿಗಳು + 1);
	ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_DEF_TYPE]], [[%s]])", ptype->name);
	ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_DEF_SIZE]], [[%d]])", ಒಟ್ಟು_ಸ್ಥಿತಿಗಳು + 1);
	outn ("m4_define([[M4_HOOK_DEF_BODY]], [[m4_dnl");

	yydef_tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	yytbl_ದತ್ತಾಂಶ_init (yydef_tbl, YYTD_ID_DEF);
	yydef_tbl->td_lolen = (flex_uint32_t)(ಒಟ್ಟು_ಸ್ಥಿತಿಗಳು + 1);
	yydef_tbl->td_ದತ್ತಾಂಶ = yydef_ದತ್ತಾಂಶ =
	    ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(yydef_tbl->td_lolen, ಗಾತ್ರ (flex_int32_t));

	ಗಾಗಿ (i = 1; i <= ಒಟ್ಟು_ಸ್ಥಿತಿಗಳು; ++i) {
		mkdata (def[i]);
		yydef_ದತ್ತಾಂಶ[i] = def[i];
	}

	dataend (ಖಾಲಿ);
	outn ("]])");
	footprint += (ಒಟ್ಟು_ಸ್ಥಿತಿಗಳು + 1) * ptype->ಅಗಲ;

	ಆದರೆ (tablesext) {
		yytbl_ದತ್ತಾಂಶ_compress (yydef_tbl);
		ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, yydef_tbl) < 0)
			flexerror (_("Could not write yydef_tbl"));
	}
	yytbl_ದತ್ತಾಂಶ_destroy (yydef_tbl);
	yydef_tbl = ಖಾಲಿ;
	/* End generating yy_def */


	ptype = optimize_pack(tblend + 1);
	/* Note: Used when !ctrl.fulltbl && !ctrl.fullspd).
	 * (Alternately defined when ctrl.fullspd)
	 */
	ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_YYNXT_TYPE]], [[%s]])", ptype->name);
	ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_YYNXT_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_YYNXT_BODY]], [[m4_dnl");

	yynxt_tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು (1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	yytbl_ದತ್ತಾಂಶ_init (yynxt_tbl, YYTD_ID_NXT);
	yynxt_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yynxt_tbl->td_ದತ್ತಾಂಶ = yynxt_ದತ್ತಾಂಶ =
	    ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು (yynxt_tbl->td_lolen, ಗಾತ್ರ (flex_int32_t));

	ಗಾಗಿ (i = 1; i <= tblend; ++i) {
		/* Note, the order of the following test is important.
		 * If chk[i] is 0, then nxt[i] is undefined.
		 */
		ಆದರೆ (chk[i] == 0 || nxt[i] == 0)
			nxt[i] = jamstate;	/* new state is the JAM state */

		mkdata (nxt[i]);
		yynxt_ದತ್ತಾಂಶ[i] = nxt[i];
	}

	dataend (ಖಾಲಿ);
	outn("]])");
	footprint += ptype->ಅಗಲ * (tblend + 1);

	ಆದರೆ (tablesext) {
		yytbl_ದತ್ತಾಂಶ_compress (yynxt_tbl);
		ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, yynxt_tbl) < 0)
			flexerror (_("Could not write yynxt_tbl"));
	}
	yytbl_ದತ್ತಾಂಶ_destroy (yynxt_tbl);
	yynxt_tbl = ಖಾಲಿ;
	/* End generating yy_nxt */

	/* Begin generating yy_chk */
	ptype = optimize_pack(tblend + 1);
	ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_CHK_TYPE]], [[%s]])", ptype->name);
	ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_CHK_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_CHK_BODY]], [[m4_dnl");
	
	yychk_tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು (1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	yytbl_ದತ್ತಾಂಶ_init (yychk_tbl, YYTD_ID_CHK);
	yychk_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yychk_tbl->td_ದತ್ತಾಂಶ = yychk_ದತ್ತಾಂಶ =
	    ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(yychk_tbl->td_lolen, ಗಾತ್ರ (flex_int32_t));

	ಗಾಗಿ (i = 1; i <= tblend; ++i) {
		ಆದರೆ (chk[i] == 0)
			++nummt;

		mkdata (chk[i]);
		yychk_ದತ್ತಾಂಶ[i] = chk[i];
	}

	dataend (ಖಾಲಿ);
	outn ("]])");
	footprint += ptype->ಅಗಲ * (tblend + 1);

	ಆದರೆ (tablesext) {
		yytbl_ದತ್ತಾಂಶ_compress (yychk_tbl);
		ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, yychk_tbl) < 0)
			flexerror (_("Could not write yychk_tbl"));
	}
	yytbl_ದತ್ತಾಂಶ_destroy (yychk_tbl);
	yychk_tbl = ಖಾಲಿ;
	/* End generating yy_chk */

	ಬಿಡುಗಡೆ(acc_array);
}


ಶೂನ್ಯ visible_define (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *symname)
{
	ಹೊರಹೋಗು_m4_define(symname, ಖಾಲಿ);
	comment(symname);
	outc ('\n');
}

ಶೂನ್ಯ visible_define_str (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *symname, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val)
{
	ಅಕ್ಷರ buf[128];
	ಹೊರಹೋಗು_m4_define(symname, val);
	snprintf(buf, ಗಾತ್ರ(buf), "%s = %s", symname, val);
	comment(buf);
	outc ('\n');
}

ಶೂನ್ಯ visible_define_int (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *symname, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ val)
{
	ಅಕ್ಷರ nbuf[24], buf[128];
	snprintf(nbuf, ಗಾತ್ರ(nbuf), "%d", val);
	ಹೊರಹೋಗು_m4_define(symname, nbuf);
	snprintf(buf, ಗಾತ್ರ(buf), "%s = %d", symname, val);
	comment(buf);
	outc ('\n');
}

/* make_tables - generate transition tables
 */

ಶೂನ್ಯ make_tables (ಶೂನ್ಯ)
{
	ಅಕ್ಷರ buf[128];
	ಪೂರ್ಣಾಂಕ i;
	ರಚನೆ yytbl_ದತ್ತಾಂಶ *yynultrans_tbl = ಖಾಲಿ;

	/* This is where we REALLY begin generating the tables. */

	ಆದರೆ (ctrl.fullspd) {
		genctbl ();
		ಆದರೆ (tablesext) {
			ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl;

			tbl = mkctbl ();
			yytbl_ದತ್ತಾಂಶ_compress (tbl);
			ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_ದತ್ತಾಂಶ_destroy (tbl);

			tbl = mkssltbl ();
			yytbl_ದತ್ತಾಂಶ_compress (tbl);
			ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ssltbl"));
			yytbl_ದತ್ತಾಂಶ_destroy (tbl);
			tbl = 0;

			ಆದರೆ (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_ದತ್ತಾಂಶ_compress (tbl);
				ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_ದತ್ತಾಂಶ_destroy (tbl);
				tbl = 0;
			}
		}
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.fulltbl) {
		genftbl ();
		ಆದರೆ (tablesext) {
			ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl;

			/* Alternately defined if !ctrl.ffullspd && !ctrl.fulltbl */
			ರಚನೆ packtype_t *ptype;
			tbl = mkftbl ();
			yytbl_ದತ್ತಾಂಶ_compress (tbl);
			ptype = optimize_pack(tbl->td_lolen);
			ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
			ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_ದತ್ತಾಂಶ_destroy (tbl);
			tbl = 0;

			ಆದರೆ (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_ದತ್ತಾಂಶ_compress (tbl);
				ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_ದತ್ತಾಂಶ_destroy (tbl);
				tbl = 0;
			}
		}
	}
	ಇಲ್ಲದಿದ್ದರೆ {
		gentabs ();
	}

	snprintf(buf, ಗಾತ್ರ(buf), "footprint: %ld bytes\n", footprint);
	comment(buf);
	snprintf(buf, ಗಾತ್ರ(buf), "tblend: %d\n", tblend);
	comment(buf);
	snprintf(buf, ಗಾತ್ರ(buf), "numecs: %d\n", numecs);
	comment(buf);
	snprintf(buf, ಗಾತ್ರ(buf), "num_rules: %d\n", ಅಂಕೆ_ನಿಯಮಗಳು);
	comment(buf);
	snprintf(buf, ಗಾತ್ರ(buf), "lastdfa: %d\n", lastdfa);
	comment(buf);
	outc ('\n');
	
	// Only at this point do we know if the automaton has backups.
	// Some m4 conditionals require this information.

	comment("m4 controls begin\n");

	ಆದರೆ (ಅಂಕೆ_backing_ಮೇಲೆ > 0)
		visible_define ( "M4_MODE_HAS_BACKING_UP");

	// These are used for NUL transitions
	ಆದರೆ ((ಅಂಕೆ_backing_ಮೇಲೆ > 0 && !reject) && (!nultrans || ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NEED_YY_CP");
	ಆದರೆ ((ಅಂಕೆ_backing_ಮೇಲೆ > 0 && !reject) && (ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NULTRANS_WRAP");

	comment("m4 controls end\n");
	ಹೊರಹೋಗು ("\n");

	ಆದರೆ (ctrl.do_yylineno) {

		geneoltbl ();

		ಆದರೆ (tablesext) {
			ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl;

			tbl = mkeoltbl ();
			yytbl_ದತ್ತಾಂಶ_compress (tbl);
			ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write eoltbl"));
			yytbl_ದತ್ತಾಂಶ_destroy (tbl);
			tbl = 0;
		}
	}

	ಆದರೆ (nultrans) {
		flex_int32_t *yynultrans_ದತ್ತಾಂಶ = 0;

		/* Begin generating yy_NUL_trans */
		ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_NULTRANS_TYPE]], [[%s]])", (ctrl.fullspd) ? "struct yy_trans_info*" : "M4_HOOK_INT32");
		ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_NULTRANS_SIZE]], [[%d]])", lastdfa + 1);
		outn ("m4_define([[M4_HOOK_NULTRANS_BODY]], [[m4_dnl");

		yynultrans_tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
		yytbl_ದತ್ತಾಂಶ_init (yynultrans_tbl, YYTD_ID_NUL_TRANS);
		// Performance kludge for C. Gives a small improvement
		// in table loading time.
		ಆದರೆ (ctrl.fullspd && ctrl.have_state_ನಮೂದು_format)
			yynultrans_tbl->td_flags |= YYTD_PTRANS;
		yynultrans_tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);
		yynultrans_tbl->td_ದತ್ತಾಂಶ = yynultrans_ದತ್ತಾಂಶ =
		    ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(yynultrans_tbl->td_lolen,
			   ಗಾತ್ರ (flex_int32_t));

		ಗಾಗಿ (i = 1; i <= lastdfa; ++i) {
			ಆದರೆ ((yynultrans_tbl->td_flags & YYTD_PTRANS) != 0) {
				// Only works in very C-like languages  
				ಹೊರಹೋಗು_dec ("    &yy_transition[%d],\n",
					 ತಳ[i]);
				yynultrans_ದತ್ತಾಂಶ[i] = ತಳ[i];
			}
			ಇಲ್ಲದಿದ್ದರೆ {
				// This will work anywhere
				mkdata (nultrans[i]);
				yynultrans_ದತ್ತಾಂಶ[i] = nultrans[i];
			}
		}

		dataend (ಖಾಲಿ);
		outn("]])");
		footprint += (lastdfa + 1) * (ctrl.fullspd ? ಗಾತ್ರ(ರಚನೆ yy_trans_info *) : ಗಾತ್ರ(int32_t));
		ಆದರೆ (tablesext) {
			yytbl_ದತ್ತಾಂಶ_compress (yynultrans_tbl);
			ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, yynultrans_tbl) <
			    0)
				flexerror (_
					   ("Could not write yynultrans_tbl"));
		}

		ಆದರೆ (yynultrans_tbl != ಖಾಲಿ) {
			yytbl_ದತ್ತಾಂಶ_destroy (yynultrans_tbl);
			yynultrans_tbl = ಖಾಲಿ;
		}

		/* End generating yy_NUL_trans */
	}

	ಆದರೆ (ctrl.ddebug) {		/* Spit out table mapping rules to line numbers. */
		/* Policy choice: we don't include this space
		 * in the table metering.
		 */
		ರಚನೆ packtype_t *ptype = optimize_pack(ಅಂಕೆ_ನಿಯಮಗಳು);
		ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_DEBUGTABLE_TYPE]], [[%s]])", ptype->name);
		ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_DEBUGTABLE_SIZE]], [[%d]])", ಅಂಕೆ_ನಿಯಮಗಳು);
		outn ("m4_define([[M4_HOOK_DEBUGTABLE_BODY]], [[m4_dnl");

		ಗಾಗಿ (i = 1; i < ಅಂಕೆ_ನಿಯಮಗಳು; ++i)
			mkdata (ನಿಯಮ_linenum[i]);
		dataend (ಖಾಲಿ);
		outn("]])");
	}
}
