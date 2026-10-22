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

#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tables.h"

/* These typedefs are only used for computing footprint sizes,
 * You need to make sure they match reality in the skeleton file to
 * get accurate numbers, but they don't otherwise matter.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ YY_CHAR;
ਬਣਤਰ yy_trans_info {int32_t yy_verify; int32_t yy_nxt;};

/* declare functions that have forward references */

ਸਥਿਰ ਖਾਲੀ genecs(ਖਾਲੀ);

ਬਣਤਰ packtype_t *optimize_pack(size_t sz)
{
	/* FIXME: There's a 32-bit assumption lurking here */
	ਸਥਿਰ ਬਣਤਰ packtype_t ਬਾਹਰਲਾ;
	ਜੇ (sz == 0) {
		ਬਾਹਰਲਾ.name  = ctrl.long_align ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		ਬਾਹਰਲਾ.ਚੌੜਾਈ = ctrl.long_align ? 32 : 16;
	} ਨਹੀਂਤਾਂ {
		ਬਾਹਰਲਾ.name = (ctrl.long_align || sz >= INT16_MAX) ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		ਬਾਹਰਲਾ.ਚੌੜਾਈ = (ctrl.long_align || sz >= INT16_MAX) ? 32 : 16;
	}
	ਵਾਪਸ &ਬਾਹਰਲਾ;
}

/* Almost everything is done in terms of arrays starting at 1, so provide
 * a null entry for the zero element of all C arrays.  (The exception
 * to this is that the fast table representation generally uses the
 * 0 elements of its arrays, too.)
 */

/** Make the table for possible eol matches.
 *  @return the newly allocated rule_can_match_eol table
 */
ਸਥਿਰ ਬਣਤਰ yytbl_ਅੰਕੜੇ *mkeoltbl (ਖਾਲੀ)
{
	ਪੂਰਨ     i;
	flex_int8_t *tdata = 0;
	ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl;

	tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	yytbl_ਅੰਕੜੇ_init (tbl, YYTD_ID_ਨਿਯਮ_CAN_ਮੇਲ_EOL);
	tbl->td_flags = YYTD_DATA8;
	tbl->td_lolen = (flex_uint32_t) (ਅੰਕ_ਨਿਯਮਾਂ + 1);
	tbl->td_ਅੰਕੜੇ = tdata =
		ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(tbl->td_lolen, ਆਕਾਰ (flex_int8_t));

	ਲਈ (i = 1; i <= ਅੰਕ_ਨਿਯਮਾਂ; i++)
		tdata[i] = ਨਿਯਮ_has_nl[i] ? 1 : 0;

	ਵਾਪਸ tbl;
}

/* Generate the table for possible eol matches. */
ਸਥਿਰ ਖਾਲੀ geneoltbl (ਖਾਲੀ)
{
	ਪੂਰਨ     i;
	ਬਣਤਰ packtype_t *ptype = optimize_pack(ਅੰਕ_ਨਿਯਮਾਂ);

	outn ("m4_ifdef( [[M4_MODE_YYLINENO]],[[");
	ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_EOLTABLE_TYPE]], [[%s]])\n", ptype->name);
	ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_EOLTABLE_SIZE]], [[%d]])", ਅੰਕ_ਨਿਯਮਾਂ + 1);
	outn ("m4_define([[M4_HOOK_EOLTABLE_BODY]], [[m4_dnl");

	ਜੇ (gentables) {
		ਲਈ (i = 1; i <= ਅੰਕ_ਨਿਯਮਾਂ; i++) {
			ਬਾਹਰਲਾ_dec ("%d, ", ਨਿਯਮ_has_nl[i] ? 1 : 0);
			/* format nicely, 20 numbers per line. */
			ਜੇ ((i % 20) == 19)
				ਬਾਹਰਲਾ ("\n    ");
		}
	}
	footprint += ਅੰਕ_ਨਿਯਮਾਂ * ptype->ਚੌੜਾਈ;
	outn ("]])");
	outn ("]])");
}


/** mkctbl - make full speed compressed transition table
 * This is an array of structs; each struct a pair of integers.
 * You should call mkssltbl() immediately after this.
 * Then, I think, mkecstbl(). Arrrg.
 * @return the newly allocated trans table
 */

ਸਥਿਰ ਬਣਤਰ yytbl_ਅੰਕੜੇ *mkctbl (ਖਾਲੀ)
{
	ਪੂਰਨ i;
	ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl = 0;
	flex_int32_t *tdata = 0, curr = 0;
	ਪੂਰਨ     ਸਿਰਾ_ਦਾ_ਬਫਰ_action = ਅੰਕ_ਨਿਯਮਾਂ + 1;

	ਬਣਤਰ packtype_t *ptype = optimize_pack(tblend + 2 + 1);
	ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_MKCTBL_TYPE]], [[%s]])", ptype->name);

	tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	yytbl_ਅੰਕੜੇ_init (tbl, YYTD_ID_TRANSITION);
	tbl->td_flags = YYTD_DATA32 | YYTD_STRUCT;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (tblend + 2 + 1);	/* number of structs */

	tbl->td_ਅੰਕੜੇ = tdata =
		ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(tbl->td_lolen * 2, ਆਕਾਰ (flex_int32_t));

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

	ਜਦੋਂ (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	ਜਦੋਂ (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	ਅਧਾਰ[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = ਸਿਰਾ_ਦਾ_ਬਫਰ_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	ਲਈ (i = 0; i <= lastdfa; ++i) {
		ਪੂਰਨ     anum = dfaacc[i].dfaacc_state;
		ਪੂਰਨ     ਵਿੱਥ = ਅਧਾਰ[i];

		chk[ਵਿੱਥ] = EOB_POSITION;
		chk[ਵਿੱਥ - 1] = ACTION_POSITION;
		nxt[ਵਿੱਥ - 1] = anum;	/* action number */
	}

	ਲਈ (i = 0; i <= tblend; ++i) {
		ਜੇ (chk[i] == EOB_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = ਅਧਾਰ[lastdfa + 1] - i;
		}

		ਨਹੀਂਤਾਂ ਜੇ (chk[i] == ACTION_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = nxt[i];
		}

		ਨਹੀਂਤਾਂ ਜੇ (chk[i] > numecs || chk[i] == 0) {
			tdata[curr++] = 0;
			tdata[curr++] = 0;
		}
		ਨਹੀਂਤਾਂ {		/* verify, transition */

			tdata[curr++] = chk[i];
			tdata[curr++] = ਅਧਾਰ[nxt[i]] - (i - chk[i]);
		}
	}

	/* Here's the final, end-of-buffer state. */
	tdata[curr++] = chk[tblend + 1];
	tdata[curr++] = nxt[tblend + 1];

	tdata[curr++] = chk[tblend + 2];
	tdata[curr++] = nxt[tblend + 2];

	ਵਾਪਸ tbl;
}


/** Make start_state_list table.
 *  @return the newly allocated start_state_list table
 */
ਸਥਿਰ ਬਣਤਰ yytbl_ਅੰਕੜੇ *mkssltbl (ਖਾਲੀ)
{
	ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl = 0;
	flex_int32_t *tdata = 0;
	flex_int32_t i;

	tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	yytbl_ਅੰਕੜੇ_init (tbl, YYTD_ID_ਸ਼ੁਰੂ_STATE_LIST);
	tbl->td_flags = YYTD_DATA32 | YYTD_PTRANS;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (lastsc * 2 + 1);

	tbl->td_ਅੰਕੜੇ = tdata =
		ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(tbl->td_lolen, ਆਕਾਰ (flex_int32_t));

	ਲਈ (i = 0; i <= lastsc * 2; ++i)
		tdata[i] = ਅਧਾਰ[i];

	ਵਾਪਸ tbl;
}



/* genctbl - generates full speed compressed transition table */

ਸਥਿਰ ਖਾਲੀ genctbl(ਖਾਲੀ)
{
	ਪੂਰਨ i;
	ਪੂਰਨ     ਸਿਰਾ_ਦਾ_ਬਫਰ_action = ਅੰਕ_ਨਿਯਮਾਂ + 1;

	/* Table of verify for transition and offset to next state. */
	ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_TRANSTABLE_SIZE]], [[%d]])", tblend + 2 + 1);
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

	ਜਦੋਂ (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	ਜਦੋਂ (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	ਅਧਾਰ[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = ਸਿਰਾ_ਦਾ_ਬਫਰ_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	ਲਈ (i = 0; i <= lastdfa; ++i) {
		ਪੂਰਨ     anum = dfaacc[i].dfaacc_state;
		ਪੂਰਨ     ਵਿੱਥ = ਅਧਾਰ[i];

		chk[ਵਿੱਥ] = EOB_POSITION;
		chk[ਵਿੱਥ - 1] = ACTION_POSITION;
		nxt[ਵਿੱਥ - 1] = anum;	/* action number */
	}

	ਲਈ (i = 0; i <= tblend; ++i) {
		ਜੇ (chk[i] == EOB_POSITION)
			transition_struct_ਬਾਹਰਲਾ (0, ਅਧਾਰ[lastdfa + 1] - i);

		ਨਹੀਂਤਾਂ ਜੇ (chk[i] == ACTION_POSITION)
			transition_struct_ਬਾਹਰਲਾ (0, nxt[i]);

		ਨਹੀਂਤਾਂ ਜੇ (chk[i] > numecs || chk[i] == 0)
			transition_struct_ਬਾਹਰਲਾ (0, 0);	/* unused slot */

		ਨਹੀਂਤਾਂ		/* verify, transition */
			transition_struct_ਬਾਹਰਲਾ (chk[i],
					       ਅਧਾਰ[nxt[i]] - (i -
							       chk[i]));
	}


	/* Here's the final, end-of-buffer state. */
	transition_struct_ਬਾਹਰਲਾ (chk[tblend + 1], nxt[tblend + 1]);
	transition_struct_ਬਾਹਰਲਾ (chk[tblend + 2], nxt[tblend + 2]);

	outn ("]])");
	footprint += ਆਕਾਰ(ਬਣਤਰ yy_trans_info) * (tblend + 2 + 1);

	ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_STARTTABLE_SIZE]], [[%d]])", lastsc * 2 + 1);
	ਜੇ (gentables) {
		outn ("m4_define([[M4_HOOK_STARTTABLE_BODY]], [[m4_dnl");
		ਲਈ (i = 0; i <= lastsc * 2; ++i)
			ਬਾਹਰਲਾ_dec ("M4_HOOK_STATE_ENTRY_FORMAT(%d)", ਅਧਾਰ[i]);

		dataend (ਨਿਰਾ);
		outn("]])");
		footprint +=  ਆਕਾਰ(ਬਣਤਰ yy_trans_info *) * (lastsc * 2 + 1);
	}

	ਜੇ (ctrl.useecs)
		genecs ();
}


/* mkecstbl - Make equivalence-class tables.  */

ਸਥਿਰ ਬਣਤਰ yytbl_ਅੰਕੜੇ *mkecstbl (ਖਾਲੀ)
{
	ਪੂਰਨ i;
	ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl = 0;
	flex_int32_t *tdata = 0;

	tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	yytbl_ਅੰਕੜੇ_init (tbl, YYTD_ID_EC);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) ctrl.csize;

	tbl->td_ਅੰਕੜੇ = tdata =
		ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(tbl->td_lolen, ਆਕਾਰ (flex_int32_t));

	ਲਈ (i = 1; i < ctrl.csize; ++i) {
		ecgroup[i] = ABS (ecgroup[i]);
		tdata[i] = ecgroup[i];
	}

	ਵਾਪਸ tbl;
}

/* Generate equivalence-class tables. */

ਸਥਿਰ ਖਾਲੀ genecs(ਖਾਲੀ)
{
	ਪੂਰਨ ch, ਪੰਕਤੀ;
	ਪੂਰਨ     numrows;

	ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_ECSTABLE_SIZE]], [[%d]])", ctrl.csize);
	outn ("m4_define([[M4_HOOK_ECSTABLE_BODY]], [[m4_dnl");

	ਲਈ (ch = 1; ch < ctrl.csize; ++ch) {
		ecgroup[ch] = ABS (ecgroup[ch]);
		mkdata (ecgroup[ch]);
	}

	dataend (ਨਿਰਾ);
	outn("]])");
	footprint += ਆਕਾਰ(YY_CHAR) * ctrl.csize;

	ਜੇ (env.trace) {
		fputs (_("\n\nEquivalence Classes:\n\n"), stderr);

		/* Print in 8 columns */
		numrows = ctrl.csize / 8;

		ਲਈ (ਪੰਕਤੀ = 0; ਪੰਕਤੀ < numrows; ++ਪੰਕਤੀ) {
			ਲਈ (ch = ਪੰਕਤੀ; ch < ctrl.csize; ch += numrows) {
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

ਸਥਿਰ ਬਣਤਰ yytbl_ਅੰਕੜੇ *mkftbl(ਖਾਲੀ)
{
	ਪੂਰਨ i;
	ਪੂਰਨ     ਸਿਰਾ_ਦਾ_ਬਫਰ_action = ਅੰਕ_ਨਿਯਮਾਂ + 1;
	ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl;
	flex_int32_t *tdata = 0;

	tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	yytbl_ਅੰਕੜੇ_init (tbl, YYTD_ID_ACCEPT);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;	/* it's a one-dimensional array */
	tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);

	tbl->td_ਅੰਕੜੇ = tdata =
		ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(tbl->td_lolen, ਆਕਾਰ (flex_int32_t));

	dfaacc[ਸਿਰਾ_ਦਾ_ਬਫਰ_state].dfaacc_state = ਸਿਰਾ_ਦਾ_ਬਫਰ_action;

	ਲਈ (i = 1; i <= lastdfa; ++i) {
		ਪੂਰਨ anum = dfaacc[i].dfaacc_state;

		tdata[i] = anum;

		ਜੇ (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	ਵਾਪਸ tbl;
}


/* genftbl - generate full transition table */

ਸਥਿਰ ਖਾਲੀ genftbl(ਖਾਲੀ)
{
	ਪੂਰਨ i;
	ਪੂਰਨ     ਸਿਰਾ_ਦਾ_ਬਫਰ_action = ਅੰਕ_ਨਿਯਮਾਂ + 1;
	ਬਣਤਰ packtype_t *ptype = optimize_pack(ਅੰਕ_ਨਿਯਮਾਂ + 1);

	dfaacc[ਸਿਰਾ_ਦਾ_ਬਫਰ_state].dfaacc_state = ਸਿਰਾ_ਦਾ_ਬਫਰ_action;

	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", lastdfa + 1);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	ਲਈ (i = 1; i <= lastdfa; ++i) {
		ਪੂਰਨ anum = dfaacc[i].dfaacc_state;

		mkdata (anum);

		ਜੇ (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	dataend (ਨਿਰਾ);
	outn("]])");
	footprint += (lastdfa + 1) * ptype->ਚੌੜਾਈ;

	ਜੇ (ctrl.useecs)
		genecs ();

	/* Don't have to dump the actual full table entries - they were
	 * created on-the-fly.
	 */
}

/* gentabs - generate data statements for the transition tables */

ਸਥਿਰ ਖਾਲੀ gentabs(ਖਾਲੀ)
{
	ਪੂਰਨ     sz, i, j, k, *accset, nacc, *acc_array, ਕੁੱਲ_ਹਾਲਤਾਂ;
	ਪੂਰਨ     ਸਿਰਾ_ਦਾ_ਬਫਰ_action = ਅੰਕ_ਨਿਯਮਾਂ + 1;
	ਬਣਤਰ yytbl_ਅੰਕੜੇ *yyacc_tbl = 0, *yymeta_tbl = 0, *yybase_tbl = 0,
	    *yydef_tbl = 0, *yynxt_tbl = 0, *yychk_tbl = 0, *yyacclist_tbl=0;
	flex_int32_t *yyacc_ਅੰਕੜੇ = 0, *yybase_ਅੰਕੜੇ = 0, *yydef_ਅੰਕੜੇ = 0,
	    *yynxt_ਅੰਕੜੇ = 0, *yychk_ਅੰਕੜੇ = 0, *yyacclist_ਅੰਕੜੇ=0;
	flex_int32_t yybase_curr = 0, yyacclist_curr=0,yyacc_curr=0;
	ਬਣਤਰ packtype_t *ptype;

	acc_array = allocate_integer_array (current_max_dfas);
	nummt = 0;

	/* The compressed table format jams by entering the "jam state",
	 * losing information about the previous state in the process.
	 * In order to recover the previous state, we effectively need
	 * to keep backing-up information.
	 */
	++ਅੰਕ_backing_ਉੱਪਰ;

	ਜੇ (reject) {
		/* Write out accepting list and pointer list.

		 * First we generate the "yy_acclist" array.  In the process,
		 * we compute the indices that will go into the "yy_accept"
		 * array, and save the indices in the dfaacc array.
		 */
		ਪੂਰਨ     EOB_accepting_list[2];

		/* Set up accepting structures for the End Of Buffer state. */
		EOB_accepting_list[0] = 0;
		EOB_accepting_list[1] = ਸਿਰਾ_ਦਾ_ਬਫਰ_action;
		accsiz[ਸਿਰਾ_ਦਾ_ਬਫਰ_state] = 1;
		dfaacc[ਸਿਰਾ_ਦਾ_ਬਫਰ_state].dfaacc_ਸੈੱਟ =
		    EOB_accepting_list;

		sz = MAX (numas, 1) + 1;
		ptype = optimize_pack(sz);
		ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_ACCLIST_TYPE]], [[%s]])", ptype->name);
		ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_ACCLIST_SIZE]], [[%d]])", sz);
		outn ("m4_define([[M4_HOOK_ACCLIST_BODY]], [[m4_dnl");

		yyacclist_tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1,ਆਕਾਰ(ਬਣਤਰ yytbl_ਅੰਕੜੇ));
		yytbl_ਅੰਕੜੇ_init (yyacclist_tbl, YYTD_ID_ACCLIST);
		yyacclist_tbl->td_lolen  = (flex_uint32_t) (MAX(numas,1) + 1);
		yyacclist_tbl->td_ਅੰਕੜੇ = yyacclist_ਅੰਕੜੇ =
		    ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(yyacclist_tbl->td_lolen, ਆਕਾਰ (flex_int32_t));
		yyacclist_curr = 1;

		j = 1;		/* index into "yy_acclist" array */

		ਲਈ (i = 1; i <= lastdfa; ++i) {
			acc_array[i] = j;

			ਜੇ (accsiz[i] != 0) {
				accset = dfaacc[i].dfaacc_ਸੈੱਟ;
				nacc = accsiz[i];

				ਜੇ (env.trace)
					fprintf (stderr,
						 _("state # %d accepts: "),
						 i);

				ਲਈ (k = 1; k <= nacc; ++k) {
					ਪੂਰਨ     accnum = accset[k];

					++j;

					ਜੇ (variable_trailing_context_ਨਿਯਮਾਂ
					    && !(accnum &
						 YY_TRAILING_ਸਿਰ_ਨਕਾਬ)
					    && accnum > 0
					    && accnum <= ਅੰਕ_ਨਿਯਮਾਂ
					    && ਨਿਯਮ_type[accnum] ==
					    ਨਿਯਮ_VARIABLE) {
						/* Special hack to flag
						 * accepting number as part
						 * of trailing context rule.
						 */
						accnum |= YY_TRAILING_ਨਕਾਬ;
					}

					mkdata (accnum);
					yyacclist_ਅੰਕੜੇ[yyacclist_curr++] = accnum;

					ਜੇ (env.trace) {
						fprintf (stderr, "[%d]",
							 accset[k]);

						ਜੇ (k < nacc)
							fputs (", ",
							       stderr);
						ਨਹੀਂਤਾਂ
							putc ('\n',
							      stderr);
					}
				}
			}
		}

		/* add accepting number for the "jam" state */
		acc_array[i] = j;

		dataend (ਨਿਰਾ);
		outn("]])");
		footprint += sz * ptype->ਚੌੜਾਈ;
		ਜੇ (tablesext) {
			yytbl_ਅੰਕੜੇ_compress (yyacclist_tbl);
			ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, yyacclist_tbl) < 0)
				flexerror (_("Could not write yyacclist_tbl"));
			yytbl_ਅੰਕੜੇ_destroy (yyacclist_tbl);
			yyacclist_tbl = ਨਿਰਾ;
		}
	}

	ਨਹੀਂਤਾਂ {
		dfaacc[ਸਿਰਾ_ਦਾ_ਬਫਰ_state].dfaacc_state =
		    ਸਿਰਾ_ਦਾ_ਬਫਰ_action;

		ਲਈ (i = 1; i <= lastdfa; ++i)
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

	ਜੇ (reject)
		/* We put a "cap" on the table associating lists of accepting
		 * numbers with state numbers.  This is needed because we tell
		 * where the end of an accepting list is by looking at where
		 * the list for the next state starts.
		 */
		++sz;

	/* Note that this table is alternately defined if ctrl.fulltbl */
	ptype = optimize_pack(sz);
	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	yyacc_tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	yytbl_ਅੰਕੜੇ_init (yyacc_tbl, YYTD_ID_ACCEPT);
	yyacc_tbl->td_lolen = (flex_uint32_t) sz;
	yyacc_tbl->td_ਅੰਕੜੇ = yyacc_ਅੰਕੜੇ =
	    ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(yyacc_tbl->td_lolen, ਆਕਾਰ (flex_int32_t));
	yyacc_curr=1;

	ਲਈ (i = 1; i <= lastdfa; ++i) {
		mkdata (acc_array[i]);
		yyacc_ਅੰਕੜੇ[yyacc_curr++] = acc_array[i];

		ਜੇ (!reject && env.trace && acc_array[i])
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, acc_array[i]);
	}

	/* Add entry for "jam" state. */
	mkdata (acc_array[i]);
	yyacc_ਅੰਕੜੇ[yyacc_curr++] = acc_array[i];

	ਜੇ (reject) {
		/* Add "cap" for the list. */
		mkdata (acc_array[i]);
		yyacc_ਅੰਕੜੇ[yyacc_curr++] = acc_array[i];
	}

	dataend (ਨਿਰਾ);
	outn ("]])");
	footprint += sz * ptype->ਚੌੜਾਈ;

	ਜੇ (tablesext) {
		yytbl_ਅੰਕੜੇ_compress (yyacc_tbl);
		ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, yyacc_tbl) < 0)
			flexerror (_("Could not write yyacc_tbl"));
	}
	yytbl_ਅੰਕੜੇ_destroy (yyacc_tbl);
	yyacc_tbl = ਨਿਰਾ;
	/* End generating yy_accept */

	ਜੇ (ctrl.useecs) {

		genecs ();
		ਜੇ (tablesext) {
			ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl;

			tbl = mkecstbl ();
			yytbl_ਅੰਕੜੇ_compress (tbl);
			ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ecstbl"));
			yytbl_ਅੰਕੜੇ_destroy (tbl);
			tbl = 0;
		}
	}

	ਜੇ (ctrl.usemecs) {
		/* Begin generating yy_meta */
		/* Write out meta-equivalence classes (used to index
		 * templates with).
		 */
		flex_int32_t *yymecs_ਅੰਕੜੇ = 0;
		yymeta_tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
		yytbl_ਅੰਕੜੇ_init (yymeta_tbl, YYTD_ID_META);
		yymeta_tbl->td_lolen = (flex_uint32_t) (numecs + 1);
		yymeta_tbl->td_ਅੰਕੜੇ = yymecs_ਅੰਕੜੇ =
		    ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(yymeta_tbl->td_lolen,
			   ਆਕਾਰ (flex_int32_t));

		ਜੇ (env.trace)
			fputs (_("\n\nMeta-Equivalence Classes:\n"),
			       stderr);
		ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_MECSTABLE_SIZE]], [[%d]])", numecs+1);
		outn ("m4_define([[M4_HOOK_MECSTABLE_BODY]], [[m4_dnl");
 	
		ਲਈ (i = 1; i <= numecs; ++i) {
			ਜੇ (env.trace)
				fprintf (stderr, "%d = %d\n",
					 i, ABS (tecbck[i]));

			mkdata (ABS (tecbck[i]));
			yymecs_ਅੰਕੜੇ[i] = ABS (tecbck[i]);
		}

		dataend (ਨਿਰਾ);
		outn ("]])");
		footprint += ਆਕਾਰ(YY_CHAR) * (numecs + 1);
		ਜੇ (tablesext) {
			yytbl_ਅੰਕੜੇ_compress (yymeta_tbl);
			ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, yymeta_tbl) < 0)
				flexerror (_("Could not write yymeta_tbl"));
		}
		yytbl_ਅੰਕੜੇ_destroy (yymeta_tbl);
		yymeta_tbl = ਨਿਰਾ;
		/* End generating yy_meta */
	}

	ਕੁੱਲ_ਹਾਲਤਾਂ = lastdfa + numtemps;

	/* Begin generating yy_base */
	sz = ਕੁੱਲ_ਹਾਲਤਾਂ + 1;
	ptype = optimize_pack(sz);
	ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_BASE_TYPE]], [[%s]])", ptype->name);
	ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_BASE_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_BASE_BODY]], [[m4_dnl");

	yybase_tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ (1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	yytbl_ਅੰਕੜੇ_init (yybase_tbl, YYTD_ID_ਅਧਾਰ);
	yybase_tbl->td_lolen = (flex_uint32_t) (ਕੁੱਲ_ਹਾਲਤਾਂ + 1);
	yybase_tbl->td_ਅੰਕੜੇ = yybase_ਅੰਕੜੇ =
	    ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(yybase_tbl->td_lolen,
		   ਆਕਾਰ (flex_int32_t));
	yybase_curr = 1;

	ਲਈ (i = 1; i <= lastdfa; ++i) {
		ਪੂਰਨ d = def[i];

		ਜੇ (ਅਧਾਰ[i] == JAMSTATE)
			ਅਧਾਰ[i] = jambase;

		ਜੇ (d == JAMSTATE)
			def[i] = jamstate;

		ਨਹੀਂਤਾਂ ਜੇ (d < 0) {
			/* Template reference. */
			++tmpuses;
			def[i] = lastdfa - d + 1;
		}

		mkdata (ਅਧਾਰ[i]);
		yybase_ਅੰਕੜੇ[yybase_curr++] = ਅਧਾਰ[i];
	}

	/* Generate jam state's base index. */
	mkdata (ਅਧਾਰ[i]);
	yybase_ਅੰਕੜੇ[yybase_curr++] = ਅਧਾਰ[i];

	ਲਈ (++i /* skip jam state */ ; i <= ਕੁੱਲ_ਹਾਲਤਾਂ; ++i) {
		mkdata (ਅਧਾਰ[i]);
		yybase_ਅੰਕੜੇ[yybase_curr++] = ਅਧਾਰ[i];
		def[i] = jamstate;
	}

	dataend (ਨਿਰਾ);
	outn ("]])");
	footprint += sz * ptype->ਚੌੜਾਈ;

	ਜੇ (tablesext) {
		yytbl_ਅੰਕੜੇ_compress (yybase_tbl);
		ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, yybase_tbl) < 0)
			flexerror (_("Could not write yybase_tbl"));
	}
	yytbl_ਅੰਕੜੇ_destroy (yybase_tbl);
	yybase_tbl = ਨਿਰਾ;
	/* End generating yy_base */


	/* Begin generating yy_def */
	ptype = optimize_pack(ਕੁੱਲ_ਹਾਲਤਾਂ + 1);
	ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_DEF_TYPE]], [[%s]])", ptype->name);
	ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_DEF_SIZE]], [[%d]])", ਕੁੱਲ_ਹਾਲਤਾਂ + 1);
	outn ("m4_define([[M4_HOOK_DEF_BODY]], [[m4_dnl");

	yydef_tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	yytbl_ਅੰਕੜੇ_init (yydef_tbl, YYTD_ID_DEF);
	yydef_tbl->td_lolen = (flex_uint32_t)(ਕੁੱਲ_ਹਾਲਤਾਂ + 1);
	yydef_tbl->td_ਅੰਕੜੇ = yydef_ਅੰਕੜੇ =
	    ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(yydef_tbl->td_lolen, ਆਕਾਰ (flex_int32_t));

	ਲਈ (i = 1; i <= ਕੁੱਲ_ਹਾਲਤਾਂ; ++i) {
		mkdata (def[i]);
		yydef_ਅੰਕੜੇ[i] = def[i];
	}

	dataend (ਨਿਰਾ);
	outn ("]])");
	footprint += (ਕੁੱਲ_ਹਾਲਤਾਂ + 1) * ptype->ਚੌੜਾਈ;

	ਜੇ (tablesext) {
		yytbl_ਅੰਕੜੇ_compress (yydef_tbl);
		ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, yydef_tbl) < 0)
			flexerror (_("Could not write yydef_tbl"));
	}
	yytbl_ਅੰਕੜੇ_destroy (yydef_tbl);
	yydef_tbl = ਨਿਰਾ;
	/* End generating yy_def */


	ptype = optimize_pack(tblend + 1);
	/* Note: Used when !ctrl.fulltbl && !ctrl.fullspd).
	 * (Alternately defined when ctrl.fullspd)
	 */
	ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_YYNXT_TYPE]], [[%s]])", ptype->name);
	ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_YYNXT_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_YYNXT_BODY]], [[m4_dnl");

	yynxt_tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ (1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	yytbl_ਅੰਕੜੇ_init (yynxt_tbl, YYTD_ID_NXT);
	yynxt_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yynxt_tbl->td_ਅੰਕੜੇ = yynxt_ਅੰਕੜੇ =
	    ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ (yynxt_tbl->td_lolen, ਆਕਾਰ (flex_int32_t));

	ਲਈ (i = 1; i <= tblend; ++i) {
		/* Note, the order of the following test is important.
		 * If chk[i] is 0, then nxt[i] is undefined.
		 */
		ਜੇ (chk[i] == 0 || nxt[i] == 0)
			nxt[i] = jamstate;	/* new state is the JAM state */

		mkdata (nxt[i]);
		yynxt_ਅੰਕੜੇ[i] = nxt[i];
	}

	dataend (ਨਿਰਾ);
	outn("]])");
	footprint += ptype->ਚੌੜਾਈ * (tblend + 1);

	ਜੇ (tablesext) {
		yytbl_ਅੰਕੜੇ_compress (yynxt_tbl);
		ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, yynxt_tbl) < 0)
			flexerror (_("Could not write yynxt_tbl"));
	}
	yytbl_ਅੰਕੜੇ_destroy (yynxt_tbl);
	yynxt_tbl = ਨਿਰਾ;
	/* End generating yy_nxt */

	/* Begin generating yy_chk */
	ptype = optimize_pack(tblend + 1);
	ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_CHK_TYPE]], [[%s]])", ptype->name);
	ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_CHK_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_CHK_BODY]], [[m4_dnl");
	
	yychk_tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ (1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	yytbl_ਅੰਕੜੇ_init (yychk_tbl, YYTD_ID_CHK);
	yychk_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yychk_tbl->td_ਅੰਕੜੇ = yychk_ਅੰਕੜੇ =
	    ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(yychk_tbl->td_lolen, ਆਕਾਰ (flex_int32_t));

	ਲਈ (i = 1; i <= tblend; ++i) {
		ਜੇ (chk[i] == 0)
			++nummt;

		mkdata (chk[i]);
		yychk_ਅੰਕੜੇ[i] = chk[i];
	}

	dataend (ਨਿਰਾ);
	outn ("]])");
	footprint += ptype->ਚੌੜਾਈ * (tblend + 1);

	ਜੇ (tablesext) {
		yytbl_ਅੰਕੜੇ_compress (yychk_tbl);
		ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, yychk_tbl) < 0)
			flexerror (_("Could not write yychk_tbl"));
	}
	yytbl_ਅੰਕੜੇ_destroy (yychk_tbl);
	yychk_tbl = ਨਿਰਾ;
	/* End generating yy_chk */

	ਮੁਕਤ(acc_array);
}


ਖਾਲੀ visible_define (ਅਚਲ ਅੱਖਰ *symname)
{
	ਬਾਹਰਲਾ_m4_define(symname, ਨਿਰਾ);
	comment(symname);
	outc ('\n');
}

ਖਾਲੀ visible_define_str (ਅਚਲ ਅੱਖਰ *symname, ਅਚਲ ਅੱਖਰ *val)
{
	ਅੱਖਰ buf[128];
	ਬਾਹਰਲਾ_m4_define(symname, val);
	snprintf(buf, ਆਕਾਰ(buf), "%s = %s", symname, val);
	comment(buf);
	outc ('\n');
}

ਖਾਲੀ visible_define_int (ਅਚਲ ਅੱਖਰ *symname, ਅਚਲ ਪੂਰਨ val)
{
	ਅੱਖਰ nbuf[24], buf[128];
	snprintf(nbuf, ਆਕਾਰ(nbuf), "%d", val);
	ਬਾਹਰਲਾ_m4_define(symname, nbuf);
	snprintf(buf, ਆਕਾਰ(buf), "%s = %d", symname, val);
	comment(buf);
	outc ('\n');
}

/* make_tables - generate transition tables
 */

ਖਾਲੀ make_tables (ਖਾਲੀ)
{
	ਅੱਖਰ buf[128];
	ਪੂਰਨ i;
	ਬਣਤਰ yytbl_ਅੰਕੜੇ *yynultrans_tbl = ਨਿਰਾ;

	/* This is where we REALLY begin generating the tables. */

	ਜੇ (ctrl.fullspd) {
		genctbl ();
		ਜੇ (tablesext) {
			ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl;

			tbl = mkctbl ();
			yytbl_ਅੰਕੜੇ_compress (tbl);
			ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_ਅੰਕੜੇ_destroy (tbl);

			tbl = mkssltbl ();
			yytbl_ਅੰਕੜੇ_compress (tbl);
			ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ssltbl"));
			yytbl_ਅੰਕੜੇ_destroy (tbl);
			tbl = 0;

			ਜੇ (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_ਅੰਕੜੇ_compress (tbl);
				ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_ਅੰਕੜੇ_destroy (tbl);
				tbl = 0;
			}
		}
	}
	ਨਹੀਂਤਾਂ ਜੇ (ctrl.fulltbl) {
		genftbl ();
		ਜੇ (tablesext) {
			ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl;

			/* Alternately defined if !ctrl.ffullspd && !ctrl.fulltbl */
			ਬਣਤਰ packtype_t *ptype;
			tbl = mkftbl ();
			yytbl_ਅੰਕੜੇ_compress (tbl);
			ptype = optimize_pack(tbl->td_lolen);
			ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
			ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_ਅੰਕੜੇ_destroy (tbl);
			tbl = 0;

			ਜੇ (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_ਅੰਕੜੇ_compress (tbl);
				ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_ਅੰਕੜੇ_destroy (tbl);
				tbl = 0;
			}
		}
	}
	ਨਹੀਂਤਾਂ {
		gentabs ();
	}

	snprintf(buf, ਆਕਾਰ(buf), "footprint: %ld bytes\n", footprint);
	comment(buf);
	snprintf(buf, ਆਕਾਰ(buf), "tblend: %d\n", tblend);
	comment(buf);
	snprintf(buf, ਆਕਾਰ(buf), "numecs: %d\n", numecs);
	comment(buf);
	snprintf(buf, ਆਕਾਰ(buf), "num_rules: %d\n", ਅੰਕ_ਨਿਯਮਾਂ);
	comment(buf);
	snprintf(buf, ਆਕਾਰ(buf), "lastdfa: %d\n", lastdfa);
	comment(buf);
	outc ('\n');
	
	// Only at this point do we know if the automaton has backups.
	// Some m4 conditionals require this information.

	comment("m4 controls begin\n");

	ਜੇ (ਅੰਕ_backing_ਉੱਪਰ > 0)
		visible_define ( "M4_MODE_HAS_BACKING_UP");

	// These are used for NUL transitions
	ਜੇ ((ਅੰਕ_backing_ਉੱਪਰ > 0 && !reject) && (!nultrans || ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NEED_YY_CP");
	ਜੇ ((ਅੰਕ_backing_ਉੱਪਰ > 0 && !reject) && (ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NULTRANS_WRAP");

	comment("m4 controls end\n");
	ਬਾਹਰਲਾ ("\n");

	ਜੇ (ctrl.do_yylineno) {

		geneoltbl ();

		ਜੇ (tablesext) {
			ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl;

			tbl = mkeoltbl ();
			yytbl_ਅੰਕੜੇ_compress (tbl);
			ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write eoltbl"));
			yytbl_ਅੰਕੜੇ_destroy (tbl);
			tbl = 0;
		}
	}

	ਜੇ (nultrans) {
		flex_int32_t *yynultrans_ਅੰਕੜੇ = 0;

		/* Begin generating yy_NUL_trans */
		ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_NULTRANS_TYPE]], [[%s]])", (ctrl.fullspd) ? "struct yy_trans_info*" : "M4_HOOK_INT32");
		ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_NULTRANS_SIZE]], [[%d]])", lastdfa + 1);
		outn ("m4_define([[M4_HOOK_NULTRANS_BODY]], [[m4_dnl");

		yynultrans_tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
		yytbl_ਅੰਕੜੇ_init (yynultrans_tbl, YYTD_ID_NUL_TRANS);
		// Performance kludge for C. Gives a small improvement
		// in table loading time.
		ਜੇ (ctrl.fullspd && ctrl.have_state_ਇੰਦਰਾਜ_format)
			yynultrans_tbl->td_flags |= YYTD_PTRANS;
		yynultrans_tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);
		yynultrans_tbl->td_ਅੰਕੜੇ = yynultrans_ਅੰਕੜੇ =
		    ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(yynultrans_tbl->td_lolen,
			   ਆਕਾਰ (flex_int32_t));

		ਲਈ (i = 1; i <= lastdfa; ++i) {
			ਜੇ ((yynultrans_tbl->td_flags & YYTD_PTRANS) != 0) {
				// Only works in very C-like languages  
				ਬਾਹਰਲਾ_dec ("    &yy_transition[%d],\n",
					 ਅਧਾਰ[i]);
				yynultrans_ਅੰਕੜੇ[i] = ਅਧਾਰ[i];
			}
			ਨਹੀਂਤਾਂ {
				// This will work anywhere
				mkdata (nultrans[i]);
				yynultrans_ਅੰਕੜੇ[i] = nultrans[i];
			}
		}

		dataend (ਨਿਰਾ);
		outn("]])");
		footprint += (lastdfa + 1) * (ctrl.fullspd ? ਆਕਾਰ(ਬਣਤਰ yy_trans_info *) : ਆਕਾਰ(int32_t));
		ਜੇ (tablesext) {
			yytbl_ਅੰਕੜੇ_compress (yynultrans_tbl);
			ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, yynultrans_tbl) <
			    0)
				flexerror (_
					   ("Could not write yynultrans_tbl"));
		}

		ਜੇ (yynultrans_tbl != ਨਿਰਾ) {
			yytbl_ਅੰਕੜੇ_destroy (yynultrans_tbl);
			yynultrans_tbl = ਨਿਰਾ;
		}

		/* End generating yy_NUL_trans */
	}

	ਜੇ (ctrl.ddebug) {		/* Spit out table mapping rules to line numbers. */
		/* Policy choice: we don't include this space
		 * in the table metering.
		 */
		ਬਣਤਰ packtype_t *ptype = optimize_pack(ਅੰਕ_ਨਿਯਮਾਂ);
		ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_DEBUGTABLE_TYPE]], [[%s]])", ptype->name);
		ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_DEBUGTABLE_SIZE]], [[%d]])", ਅੰਕ_ਨਿਯਮਾਂ);
		outn ("m4_define([[M4_HOOK_DEBUGTABLE_BODY]], [[m4_dnl");

		ਲਈ (i = 1; i < ਅੰਕ_ਨਿਯਮਾਂ; ++i)
			mkdata (ਨਿਯਮ_linenum[i]);
		dataend (ਨਿਰਾ);
		outn("]])");
	}
}
