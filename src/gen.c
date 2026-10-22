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

#ضمن "flexdef.h"
#ضمن "tables.h"

/* These typedefs are only used for computing footprint sizes,
 * You need to make sure they match reality in the skeleton file to
 * get accurate numbers, but they don't otherwise matter.
 */
تعريفنوع حرف YY_CHAR;
بنية yy_trans_info {int32_t yy_verify; int32_t yy_nxt;};

/* declare functions that have forward references */

ساكن فراغ genecs(فراغ);

بنية packtype_t *optimize_pack(size_t sz)
{
	/* FIXME: There's a 32-bit assumption lurking here */
	ساكن بنية packtype_t بهر;
	إذا (sz == 0) {
		بهر.name  = ctrl.long_align ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		بهر.پلنوالی = ctrl.long_align ? 32 : 16;
	} وإلا {
		بهر.name = (ctrl.long_align || sz >= INT16_MAX) ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		بهر.پلنوالی = (ctrl.long_align || sz >= INT16_MAX) ? 32 : 16;
	}
	أرجع &بهر;
}

/* Almost everything is done in terms of arrays starting at 1, so provide
 * a null entry for the zero element of all C arrays.  (The exception
 * to this is that the fast table representation generally uses the
 * 0 elements of its arrays, too.)
 */

/** Make the table for possible eol matches.
 *  @return the newly allocated rule_can_match_eol table
 */
ساكن بنية yytbl_معلومات *mkeoltbl (فراغ)
{
	صحيح     i;
	flex_int8_t *tdata = 0;
	بنية yytbl_معلومات *tbl;

	tbl = حافظه_صفر_ورکړه(1, حجم (بنية yytbl_معلومات));
	yytbl_معلومات_init (tbl, YYTD_ID_قاعده_CAN_سمون_EOL);
	tbl->td_flags = YYTD_DATA8;
	tbl->td_lolen = (flex_uint32_t) (عدد_قواعد + 1);
	tbl->td_معلومات = tdata =
		حافظه_صفر_ورکړه(tbl->td_lolen, حجم (flex_int8_t));

	لكل (i = 1; i <= عدد_قواعد; i++)
		tdata[i] = قاعده_has_nl[i] ? 1 : 0;

	أرجع tbl;
}

/* Generate the table for possible eol matches. */
ساكن فراغ geneoltbl (فراغ)
{
	صحيح     i;
	بنية packtype_t *ptype = optimize_pack(عدد_قواعد);

	outn ("m4_ifdef( [[M4_MODE_YYLINENO]],[[");
	بهر_str ("m4_define([[M4_HOOK_EOLTABLE_TYPE]], [[%s]])\n", ptype->name);
	بهر_dec ("m4_define([[M4_HOOK_EOLTABLE_SIZE]], [[%d]])", عدد_قواعد + 1);
	outn ("m4_define([[M4_HOOK_EOLTABLE_BODY]], [[m4_dnl");

	إذا (gentables) {
		لكل (i = 1; i <= عدد_قواعد; i++) {
			بهر_dec ("%d, ", قاعده_has_nl[i] ? 1 : 0);
			/* format nicely, 20 numbers per line. */
			إذا ((i % 20) == 19)
				بهر ("\n    ");
		}
	}
	footprint += عدد_قواعد * ptype->پلنوالی;
	outn ("]])");
	outn ("]])");
}


/** mkctbl - make full speed compressed transition table
 * This is an array of structs; each struct a pair of integers.
 * You should call mkssltbl() immediately after this.
 * Then, I think, mkecstbl(). Arrrg.
 * @return the newly allocated trans table
 */

ساكن بنية yytbl_معلومات *mkctbl (فراغ)
{
	صحيح i;
	بنية yytbl_معلومات *tbl = 0;
	flex_int32_t *tdata = 0, curr = 0;
	صحيح     پای_ټکی_د_بفر_action = عدد_قواعد + 1;

	بنية packtype_t *ptype = optimize_pack(tblend + 2 + 1);
	بهر_str ("m4_define([[M4_HOOK_MKCTBL_TYPE]], [[%s]])", ptype->name);

	tbl = حافظه_صفر_ورکړه(1, حجم (بنية yytbl_معلومات));
	yytbl_معلومات_init (tbl, YYTD_ID_TRANSITION);
	tbl->td_flags = YYTD_DATA32 | YYTD_STRUCT;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (tblend + 2 + 1);	/* number of structs */

	tbl->td_معلومات = tdata =
		حافظه_صفر_ورکړه(tbl->td_lolen * 2, حجم (flex_int32_t));

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

	طالما (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	طالما (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	بنسټ[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = پای_ټکی_د_بفر_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	لكل (i = 0; i <= lastdfa; ++i) {
		صحيح     anum = dfaacc[i].dfaacc_state;
		صحيح     دننه_واټن = بنسټ[i];

		chk[دننه_واټن] = EOB_POSITION;
		chk[دننه_واټن - 1] = ACTION_POSITION;
		nxt[دننه_واټن - 1] = anum;	/* action number */
	}

	لكل (i = 0; i <= tblend; ++i) {
		إذا (chk[i] == EOB_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = بنسټ[lastdfa + 1] - i;
		}

		وإلا إذا (chk[i] == ACTION_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = nxt[i];
		}

		وإلا إذا (chk[i] > numecs || chk[i] == 0) {
			tdata[curr++] = 0;
			tdata[curr++] = 0;
		}
		وإلا {		/* verify, transition */

			tdata[curr++] = chk[i];
			tdata[curr++] = بنسټ[nxt[i]] - (i - chk[i]);
		}
	}

	/* Here's the final, end-of-buffer state. */
	tdata[curr++] = chk[tblend + 1];
	tdata[curr++] = nxt[tblend + 1];

	tdata[curr++] = chk[tblend + 2];
	tdata[curr++] = nxt[tblend + 2];

	أرجع tbl;
}


/** Make start_state_list table.
 *  @return the newly allocated start_state_list table
 */
ساكن بنية yytbl_معلومات *mkssltbl (فراغ)
{
	بنية yytbl_معلومات *tbl = 0;
	flex_int32_t *tdata = 0;
	flex_int32_t i;

	tbl = حافظه_صفر_ورکړه(1, حجم (بنية yytbl_معلومات));
	yytbl_معلومات_init (tbl, YYTD_ID_پیل_STATE_LIST);
	tbl->td_flags = YYTD_DATA32 | YYTD_PTRANS;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (lastsc * 2 + 1);

	tbl->td_معلومات = tdata =
		حافظه_صفر_ورکړه(tbl->td_lolen, حجم (flex_int32_t));

	لكل (i = 0; i <= lastsc * 2; ++i)
		tdata[i] = بنسټ[i];

	أرجع tbl;
}



/* genctbl - generates full speed compressed transition table */

ساكن فراغ genctbl(فراغ)
{
	صحيح i;
	صحيح     پای_ټکی_د_بفر_action = عدد_قواعد + 1;

	/* Table of verify for transition and offset to next state. */
	بهر_dec ("m4_define([[M4_HOOK_TRANSTABLE_SIZE]], [[%d]])", tblend + 2 + 1);
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

	طالما (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	طالما (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	بنسټ[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = پای_ټکی_د_بفر_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	لكل (i = 0; i <= lastdfa; ++i) {
		صحيح     anum = dfaacc[i].dfaacc_state;
		صحيح     دننه_واټن = بنسټ[i];

		chk[دننه_واټن] = EOB_POSITION;
		chk[دننه_واټن - 1] = ACTION_POSITION;
		nxt[دننه_واټن - 1] = anum;	/* action number */
	}

	لكل (i = 0; i <= tblend; ++i) {
		إذا (chk[i] == EOB_POSITION)
			transition_struct_بهر (0, بنسټ[lastdfa + 1] - i);

		وإلا إذا (chk[i] == ACTION_POSITION)
			transition_struct_بهر (0, nxt[i]);

		وإلا إذا (chk[i] > numecs || chk[i] == 0)
			transition_struct_بهر (0, 0);	/* unused slot */

		وإلا		/* verify, transition */
			transition_struct_بهر (chk[i],
					       بنسټ[nxt[i]] - (i -
							       chk[i]));
	}


	/* Here's the final, end-of-buffer state. */
	transition_struct_بهر (chk[tblend + 1], nxt[tblend + 1]);
	transition_struct_بهر (chk[tblend + 2], nxt[tblend + 2]);

	outn ("]])");
	footprint += حجم(بنية yy_trans_info) * (tblend + 2 + 1);

	بهر_dec ("m4_define([[M4_HOOK_STARTTABLE_SIZE]], [[%d]])", lastsc * 2 + 1);
	إذا (gentables) {
		outn ("m4_define([[M4_HOOK_STARTTABLE_BODY]], [[m4_dnl");
		لكل (i = 0; i <= lastsc * 2; ++i)
			بهر_dec ("M4_HOOK_STATE_ENTRY_FORMAT(%d)", بنسټ[i]);

		dataend (عدم);
		outn("]])");
		footprint +=  حجم(بنية yy_trans_info *) * (lastsc * 2 + 1);
	}

	إذا (ctrl.useecs)
		genecs ();
}


/* mkecstbl - Make equivalence-class tables.  */

ساكن بنية yytbl_معلومات *mkecstbl (فراغ)
{
	صحيح i;
	بنية yytbl_معلومات *tbl = 0;
	flex_int32_t *tdata = 0;

	tbl = حافظه_صفر_ورکړه(1, حجم (بنية yytbl_معلومات));
	yytbl_معلومات_init (tbl, YYTD_ID_EC);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) ctrl.csize;

	tbl->td_معلومات = tdata =
		حافظه_صفر_ورکړه(tbl->td_lolen, حجم (flex_int32_t));

	لكل (i = 1; i < ctrl.csize; ++i) {
		ecgroup[i] = ABS (ecgroup[i]);
		tdata[i] = ecgroup[i];
	}

	أرجع tbl;
}

/* Generate equivalence-class tables. */

ساكن فراغ genecs(فراغ)
{
	صحيح ch, لیکه;
	صحيح     numrows;

	بهر_dec ("m4_define([[M4_HOOK_ECSTABLE_SIZE]], [[%d]])", ctrl.csize);
	outn ("m4_define([[M4_HOOK_ECSTABLE_BODY]], [[m4_dnl");

	لكل (ch = 1; ch < ctrl.csize; ++ch) {
		ecgroup[ch] = ABS (ecgroup[ch]);
		mkdata (ecgroup[ch]);
	}

	dataend (عدم);
	outn("]])");
	footprint += حجم(YY_CHAR) * ctrl.csize;

	إذا (env.trace) {
		fputs (_("\n\nEquivalence Classes:\n\n"), stderr);

		/* Print in 8 columns */
		numrows = ctrl.csize / 8;

		لكل (لیکه = 0; لیکه < numrows; ++لیکه) {
			لكل (ch = لیکه; ch < ctrl.csize; ch += numrows) {
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

ساكن بنية yytbl_معلومات *mkftbl(فراغ)
{
	صحيح i;
	صحيح     پای_ټکی_د_بفر_action = عدد_قواعد + 1;
	بنية yytbl_معلومات *tbl;
	flex_int32_t *tdata = 0;

	tbl = حافظه_صفر_ورکړه(1, حجم (بنية yytbl_معلومات));
	yytbl_معلومات_init (tbl, YYTD_ID_ACCEPT);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;	/* it's a one-dimensional array */
	tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);

	tbl->td_معلومات = tdata =
		حافظه_صفر_ورکړه(tbl->td_lolen, حجم (flex_int32_t));

	dfaacc[پای_ټکی_د_بفر_state].dfaacc_state = پای_ټکی_د_بفر_action;

	لكل (i = 1; i <= lastdfa; ++i) {
		صحيح anum = dfaacc[i].dfaacc_state;

		tdata[i] = anum;

		إذا (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	أرجع tbl;
}


/* genftbl - generate full transition table */

ساكن فراغ genftbl(فراغ)
{
	صحيح i;
	صحيح     پای_ټکی_د_بفر_action = عدد_قواعد + 1;
	بنية packtype_t *ptype = optimize_pack(عدد_قواعد + 1);

	dfaacc[پای_ټکی_د_بفر_state].dfaacc_state = پای_ټکی_د_بفر_action;

	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	بهر_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	بهر_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", lastdfa + 1);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	لكل (i = 1; i <= lastdfa; ++i) {
		صحيح anum = dfaacc[i].dfaacc_state;

		mkdata (anum);

		إذا (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	dataend (عدم);
	outn("]])");
	footprint += (lastdfa + 1) * ptype->پلنوالی;

	إذا (ctrl.useecs)
		genecs ();

	/* Don't have to dump the actual full table entries - they were
	 * created on-the-fly.
	 */
}

/* gentabs - generate data statements for the transition tables */

ساكن فراغ gentabs(فراغ)
{
	صحيح     sz, i, j, k, *accset, nacc, *acc_array, ټول_حالتونه;
	صحيح     پای_ټکی_د_بفر_action = عدد_قواعد + 1;
	بنية yytbl_معلومات *yyacc_tbl = 0, *yymeta_tbl = 0, *yybase_tbl = 0,
	    *yydef_tbl = 0, *yynxt_tbl = 0, *yychk_tbl = 0, *yyacclist_tbl=0;
	flex_int32_t *yyacc_معلومات = 0, *yybase_معلومات = 0, *yydef_معلومات = 0,
	    *yynxt_معلومات = 0, *yychk_معلومات = 0, *yyacclist_معلومات=0;
	flex_int32_t yybase_curr = 0, yyacclist_curr=0,yyacc_curr=0;
	بنية packtype_t *ptype;

	acc_array = allocate_integer_array (current_max_dfas);
	nummt = 0;

	/* The compressed table format jams by entering the "jam state",
	 * losing information about the previous state in the process.
	 * In order to recover the previous state, we effectively need
	 * to keep backing-up information.
	 */
	++عدد_backing_پورته;

	إذا (reject) {
		/* Write out accepting list and pointer list.

		 * First we generate the "yy_acclist" array.  In the process,
		 * we compute the indices that will go into the "yy_accept"
		 * array, and save the indices in the dfaacc array.
		 */
		صحيح     EOB_accepting_list[2];

		/* Set up accepting structures for the End Of Buffer state. */
		EOB_accepting_list[0] = 0;
		EOB_accepting_list[1] = پای_ټکی_د_بفر_action;
		accsiz[پای_ټکی_د_بفر_state] = 1;
		dfaacc[پای_ټکی_د_بفر_state].dfaacc_سېټ =
		    EOB_accepting_list;

		sz = MAX (numas, 1) + 1;
		ptype = optimize_pack(sz);
		بهر_str ("m4_define([[M4_HOOK_ACCLIST_TYPE]], [[%s]])", ptype->name);
		بهر_dec ("m4_define([[M4_HOOK_ACCLIST_SIZE]], [[%d]])", sz);
		outn ("m4_define([[M4_HOOK_ACCLIST_BODY]], [[m4_dnl");

		yyacclist_tbl = حافظه_صفر_ورکړه(1,حجم(بنية yytbl_معلومات));
		yytbl_معلومات_init (yyacclist_tbl, YYTD_ID_ACCLIST);
		yyacclist_tbl->td_lolen  = (flex_uint32_t) (MAX(numas,1) + 1);
		yyacclist_tbl->td_معلومات = yyacclist_معلومات =
		    حافظه_صفر_ورکړه(yyacclist_tbl->td_lolen, حجم (flex_int32_t));
		yyacclist_curr = 1;

		j = 1;		/* index into "yy_acclist" array */

		لكل (i = 1; i <= lastdfa; ++i) {
			acc_array[i] = j;

			إذا (accsiz[i] != 0) {
				accset = dfaacc[i].dfaacc_سېټ;
				nacc = accsiz[i];

				إذا (env.trace)
					fprintf (stderr,
						 _("state # %d accepts: "),
						 i);

				لكل (k = 1; k <= nacc; ++k) {
					صحيح     accnum = accset[k];

					++j;

					إذا (variable_trailing_context_قواعد
					    && !(accnum &
						 YY_TRAILING_سر_ماسک)
					    && accnum > 0
					    && accnum <= عدد_قواعد
					    && قاعده_type[accnum] ==
					    قاعده_VARIABLE) {
						/* Special hack to flag
						 * accepting number as part
						 * of trailing context rule.
						 */
						accnum |= YY_TRAILING_ماسک;
					}

					mkdata (accnum);
					yyacclist_معلومات[yyacclist_curr++] = accnum;

					إذا (env.trace) {
						fprintf (stderr, "[%d]",
							 accset[k]);

						إذا (k < nacc)
							fputs (", ",
							       stderr);
						وإلا
							putc ('\n',
							      stderr);
					}
				}
			}
		}

		/* add accepting number for the "jam" state */
		acc_array[i] = j;

		dataend (عدم);
		outn("]])");
		footprint += sz * ptype->پلنوالی;
		إذا (tablesext) {
			yytbl_معلومات_compress (yyacclist_tbl);
			إذا (yytbl_معلومات_fwrite (&tableswr, yyacclist_tbl) < 0)
				flexerror (_("Could not write yyacclist_tbl"));
			yytbl_معلومات_destroy (yyacclist_tbl);
			yyacclist_tbl = عدم;
		}
	}

	وإلا {
		dfaacc[پای_ټکی_د_بفر_state].dfaacc_state =
		    پای_ټکی_د_بفر_action;

		لكل (i = 1; i <= lastdfa; ++i)
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

	إذا (reject)
		/* We put a "cap" on the table associating lists of accepting
		 * numbers with state numbers.  This is needed because we tell
		 * where the end of an accepting list is by looking at where
		 * the list for the next state starts.
		 */
		++sz;

	/* Note that this table is alternately defined if ctrl.fulltbl */
	ptype = optimize_pack(sz);
	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	بهر_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	بهر_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	yyacc_tbl = حافظه_صفر_ورکړه(1, حجم (بنية yytbl_معلومات));
	yytbl_معلومات_init (yyacc_tbl, YYTD_ID_ACCEPT);
	yyacc_tbl->td_lolen = (flex_uint32_t) sz;
	yyacc_tbl->td_معلومات = yyacc_معلومات =
	    حافظه_صفر_ورکړه(yyacc_tbl->td_lolen, حجم (flex_int32_t));
	yyacc_curr=1;

	لكل (i = 1; i <= lastdfa; ++i) {
		mkdata (acc_array[i]);
		yyacc_معلومات[yyacc_curr++] = acc_array[i];

		إذا (!reject && env.trace && acc_array[i])
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, acc_array[i]);
	}

	/* Add entry for "jam" state. */
	mkdata (acc_array[i]);
	yyacc_معلومات[yyacc_curr++] = acc_array[i];

	إذا (reject) {
		/* Add "cap" for the list. */
		mkdata (acc_array[i]);
		yyacc_معلومات[yyacc_curr++] = acc_array[i];
	}

	dataend (عدم);
	outn ("]])");
	footprint += sz * ptype->پلنوالی;

	إذا (tablesext) {
		yytbl_معلومات_compress (yyacc_tbl);
		إذا (yytbl_معلومات_fwrite (&tableswr, yyacc_tbl) < 0)
			flexerror (_("Could not write yyacc_tbl"));
	}
	yytbl_معلومات_destroy (yyacc_tbl);
	yyacc_tbl = عدم;
	/* End generating yy_accept */

	إذا (ctrl.useecs) {

		genecs ();
		إذا (tablesext) {
			بنية yytbl_معلومات *tbl;

			tbl = mkecstbl ();
			yytbl_معلومات_compress (tbl);
			إذا (yytbl_معلومات_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ecstbl"));
			yytbl_معلومات_destroy (tbl);
			tbl = 0;
		}
	}

	إذا (ctrl.usemecs) {
		/* Begin generating yy_meta */
		/* Write out meta-equivalence classes (used to index
		 * templates with).
		 */
		flex_int32_t *yymecs_معلومات = 0;
		yymeta_tbl = حافظه_صفر_ورکړه(1, حجم (بنية yytbl_معلومات));
		yytbl_معلومات_init (yymeta_tbl, YYTD_ID_META);
		yymeta_tbl->td_lolen = (flex_uint32_t) (numecs + 1);
		yymeta_tbl->td_معلومات = yymecs_معلومات =
		    حافظه_صفر_ورکړه(yymeta_tbl->td_lolen,
			   حجم (flex_int32_t));

		إذا (env.trace)
			fputs (_("\n\nMeta-Equivalence Classes:\n"),
			       stderr);
		بهر_dec ("m4_define([[M4_HOOK_MECSTABLE_SIZE]], [[%d]])", numecs+1);
		outn ("m4_define([[M4_HOOK_MECSTABLE_BODY]], [[m4_dnl");
 	
		لكل (i = 1; i <= numecs; ++i) {
			إذا (env.trace)
				fprintf (stderr, "%d = %d\n",
					 i, ABS (tecbck[i]));

			mkdata (ABS (tecbck[i]));
			yymecs_معلومات[i] = ABS (tecbck[i]);
		}

		dataend (عدم);
		outn ("]])");
		footprint += حجم(YY_CHAR) * (numecs + 1);
		إذا (tablesext) {
			yytbl_معلومات_compress (yymeta_tbl);
			إذا (yytbl_معلومات_fwrite (&tableswr, yymeta_tbl) < 0)
				flexerror (_("Could not write yymeta_tbl"));
		}
		yytbl_معلومات_destroy (yymeta_tbl);
		yymeta_tbl = عدم;
		/* End generating yy_meta */
	}

	ټول_حالتونه = lastdfa + numtemps;

	/* Begin generating yy_base */
	sz = ټول_حالتونه + 1;
	ptype = optimize_pack(sz);
	بهر_str ("m4_define([[M4_HOOK_BASE_TYPE]], [[%s]])", ptype->name);
	بهر_dec ("m4_define([[M4_HOOK_BASE_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_BASE_BODY]], [[m4_dnl");

	yybase_tbl = حافظه_صفر_ورکړه (1, حجم (بنية yytbl_معلومات));
	yytbl_معلومات_init (yybase_tbl, YYTD_ID_بنسټ);
	yybase_tbl->td_lolen = (flex_uint32_t) (ټول_حالتونه + 1);
	yybase_tbl->td_معلومات = yybase_معلومات =
	    حافظه_صفر_ورکړه(yybase_tbl->td_lolen,
		   حجم (flex_int32_t));
	yybase_curr = 1;

	لكل (i = 1; i <= lastdfa; ++i) {
		صحيح d = def[i];

		إذا (بنسټ[i] == JAMSTATE)
			بنسټ[i] = jambase;

		إذا (d == JAMSTATE)
			def[i] = jamstate;

		وإلا إذا (d < 0) {
			/* Template reference. */
			++tmpuses;
			def[i] = lastdfa - d + 1;
		}

		mkdata (بنسټ[i]);
		yybase_معلومات[yybase_curr++] = بنسټ[i];
	}

	/* Generate jam state's base index. */
	mkdata (بنسټ[i]);
	yybase_معلومات[yybase_curr++] = بنسټ[i];

	لكل (++i /* skip jam state */ ; i <= ټول_حالتونه; ++i) {
		mkdata (بنسټ[i]);
		yybase_معلومات[yybase_curr++] = بنسټ[i];
		def[i] = jamstate;
	}

	dataend (عدم);
	outn ("]])");
	footprint += sz * ptype->پلنوالی;

	إذا (tablesext) {
		yytbl_معلومات_compress (yybase_tbl);
		إذا (yytbl_معلومات_fwrite (&tableswr, yybase_tbl) < 0)
			flexerror (_("Could not write yybase_tbl"));
	}
	yytbl_معلومات_destroy (yybase_tbl);
	yybase_tbl = عدم;
	/* End generating yy_base */


	/* Begin generating yy_def */
	ptype = optimize_pack(ټول_حالتونه + 1);
	بهر_str ("m4_define([[M4_HOOK_DEF_TYPE]], [[%s]])", ptype->name);
	بهر_dec ("m4_define([[M4_HOOK_DEF_SIZE]], [[%d]])", ټول_حالتونه + 1);
	outn ("m4_define([[M4_HOOK_DEF_BODY]], [[m4_dnl");

	yydef_tbl = حافظه_صفر_ورکړه(1, حجم (بنية yytbl_معلومات));
	yytbl_معلومات_init (yydef_tbl, YYTD_ID_DEF);
	yydef_tbl->td_lolen = (flex_uint32_t)(ټول_حالتونه + 1);
	yydef_tbl->td_معلومات = yydef_معلومات =
	    حافظه_صفر_ورکړه(yydef_tbl->td_lolen, حجم (flex_int32_t));

	لكل (i = 1; i <= ټول_حالتونه; ++i) {
		mkdata (def[i]);
		yydef_معلومات[i] = def[i];
	}

	dataend (عدم);
	outn ("]])");
	footprint += (ټول_حالتونه + 1) * ptype->پلنوالی;

	إذا (tablesext) {
		yytbl_معلومات_compress (yydef_tbl);
		إذا (yytbl_معلومات_fwrite (&tableswr, yydef_tbl) < 0)
			flexerror (_("Could not write yydef_tbl"));
	}
	yytbl_معلومات_destroy (yydef_tbl);
	yydef_tbl = عدم;
	/* End generating yy_def */


	ptype = optimize_pack(tblend + 1);
	/* Note: Used when !ctrl.fulltbl && !ctrl.fullspd).
	 * (Alternately defined when ctrl.fullspd)
	 */
	بهر_str ("m4_define([[M4_HOOK_YYNXT_TYPE]], [[%s]])", ptype->name);
	بهر_dec ("m4_define([[M4_HOOK_YYNXT_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_YYNXT_BODY]], [[m4_dnl");

	yynxt_tbl = حافظه_صفر_ورکړه (1, حجم (بنية yytbl_معلومات));
	yytbl_معلومات_init (yynxt_tbl, YYTD_ID_NXT);
	yynxt_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yynxt_tbl->td_معلومات = yynxt_معلومات =
	    حافظه_صفر_ورکړه (yynxt_tbl->td_lolen, حجم (flex_int32_t));

	لكل (i = 1; i <= tblend; ++i) {
		/* Note, the order of the following test is important.
		 * If chk[i] is 0, then nxt[i] is undefined.
		 */
		إذا (chk[i] == 0 || nxt[i] == 0)
			nxt[i] = jamstate;	/* new state is the JAM state */

		mkdata (nxt[i]);
		yynxt_معلومات[i] = nxt[i];
	}

	dataend (عدم);
	outn("]])");
	footprint += ptype->پلنوالی * (tblend + 1);

	إذا (tablesext) {
		yytbl_معلومات_compress (yynxt_tbl);
		إذا (yytbl_معلومات_fwrite (&tableswr, yynxt_tbl) < 0)
			flexerror (_("Could not write yynxt_tbl"));
	}
	yytbl_معلومات_destroy (yynxt_tbl);
	yynxt_tbl = عدم;
	/* End generating yy_nxt */

	/* Begin generating yy_chk */
	ptype = optimize_pack(tblend + 1);
	بهر_str ("m4_define([[M4_HOOK_CHK_TYPE]], [[%s]])", ptype->name);
	بهر_dec ("m4_define([[M4_HOOK_CHK_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_CHK_BODY]], [[m4_dnl");
	
	yychk_tbl = حافظه_صفر_ورکړه (1, حجم (بنية yytbl_معلومات));
	yytbl_معلومات_init (yychk_tbl, YYTD_ID_CHK);
	yychk_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yychk_tbl->td_معلومات = yychk_معلومات =
	    حافظه_صفر_ورکړه(yychk_tbl->td_lolen, حجم (flex_int32_t));

	لكل (i = 1; i <= tblend; ++i) {
		إذا (chk[i] == 0)
			++nummt;

		mkdata (chk[i]);
		yychk_معلومات[i] = chk[i];
	}

	dataend (عدم);
	outn ("]])");
	footprint += ptype->پلنوالی * (tblend + 1);

	إذا (tablesext) {
		yytbl_معلومات_compress (yychk_tbl);
		إذا (yytbl_معلومات_fwrite (&tableswr, yychk_tbl) < 0)
			flexerror (_("Could not write yychk_tbl"));
	}
	yytbl_معلومات_destroy (yychk_tbl);
	yychk_tbl = عدم;
	/* End generating yy_chk */

	حرر(acc_array);
}


فراغ visible_define (ثابت حرف *symname)
{
	بهر_m4_define(symname, عدم);
	comment(symname);
	outc ('\n');
}

فراغ visible_define_str (ثابت حرف *symname, ثابت حرف *val)
{
	حرف buf[128];
	بهر_m4_define(symname, val);
	snprintf(buf, حجم(buf), "%s = %s", symname, val);
	comment(buf);
	outc ('\n');
}

فراغ visible_define_int (ثابت حرف *symname, ثابت صحيح val)
{
	حرف nbuf[24], buf[128];
	snprintf(nbuf, حجم(nbuf), "%d", val);
	بهر_m4_define(symname, nbuf);
	snprintf(buf, حجم(buf), "%s = %d", symname, val);
	comment(buf);
	outc ('\n');
}

/* make_tables - generate transition tables
 */

فراغ make_tables (فراغ)
{
	حرف buf[128];
	صحيح i;
	بنية yytbl_معلومات *yynultrans_tbl = عدم;

	/* This is where we REALLY begin generating the tables. */

	إذا (ctrl.fullspd) {
		genctbl ();
		إذا (tablesext) {
			بنية yytbl_معلومات *tbl;

			tbl = mkctbl ();
			yytbl_معلومات_compress (tbl);
			إذا (yytbl_معلومات_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_معلومات_destroy (tbl);

			tbl = mkssltbl ();
			yytbl_معلومات_compress (tbl);
			إذا (yytbl_معلومات_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ssltbl"));
			yytbl_معلومات_destroy (tbl);
			tbl = 0;

			إذا (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_معلومات_compress (tbl);
				إذا (yytbl_معلومات_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_معلومات_destroy (tbl);
				tbl = 0;
			}
		}
	}
	وإلا إذا (ctrl.fulltbl) {
		genftbl ();
		إذا (tablesext) {
			بنية yytbl_معلومات *tbl;

			/* Alternately defined if !ctrl.ffullspd && !ctrl.fulltbl */
			بنية packtype_t *ptype;
			tbl = mkftbl ();
			yytbl_معلومات_compress (tbl);
			ptype = optimize_pack(tbl->td_lolen);
			بهر_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
			إذا (yytbl_معلومات_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_معلومات_destroy (tbl);
			tbl = 0;

			إذا (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_معلومات_compress (tbl);
				إذا (yytbl_معلومات_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_معلومات_destroy (tbl);
				tbl = 0;
			}
		}
	}
	وإلا {
		gentabs ();
	}

	snprintf(buf, حجم(buf), "footprint: %ld bytes\n", footprint);
	comment(buf);
	snprintf(buf, حجم(buf), "tblend: %d\n", tblend);
	comment(buf);
	snprintf(buf, حجم(buf), "numecs: %d\n", numecs);
	comment(buf);
	snprintf(buf, حجم(buf), "num_rules: %d\n", عدد_قواعد);
	comment(buf);
	snprintf(buf, حجم(buf), "lastdfa: %d\n", lastdfa);
	comment(buf);
	outc ('\n');
	
	// Only at this point do we know if the automaton has backups.
	// Some m4 conditionals require this information.

	comment("m4 controls begin\n");

	إذا (عدد_backing_پورته > 0)
		visible_define ( "M4_MODE_HAS_BACKING_UP");

	// These are used for NUL transitions
	إذا ((عدد_backing_پورته > 0 && !reject) && (!nultrans || ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NEED_YY_CP");
	إذا ((عدد_backing_پورته > 0 && !reject) && (ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NULTRANS_WRAP");

	comment("m4 controls end\n");
	بهر ("\n");

	إذا (ctrl.do_yylineno) {

		geneoltbl ();

		إذا (tablesext) {
			بنية yytbl_معلومات *tbl;

			tbl = mkeoltbl ();
			yytbl_معلومات_compress (tbl);
			إذا (yytbl_معلومات_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write eoltbl"));
			yytbl_معلومات_destroy (tbl);
			tbl = 0;
		}
	}

	إذا (nultrans) {
		flex_int32_t *yynultrans_معلومات = 0;

		/* Begin generating yy_NUL_trans */
		بهر_str ("m4_define([[M4_HOOK_NULTRANS_TYPE]], [[%s]])", (ctrl.fullspd) ? "struct yy_trans_info*" : "M4_HOOK_INT32");
		بهر_dec ("m4_define([[M4_HOOK_NULTRANS_SIZE]], [[%d]])", lastdfa + 1);
		outn ("m4_define([[M4_HOOK_NULTRANS_BODY]], [[m4_dnl");

		yynultrans_tbl = حافظه_صفر_ورکړه(1, حجم (بنية yytbl_معلومات));
		yytbl_معلومات_init (yynultrans_tbl, YYTD_ID_NUL_TRANS);
		// Performance kludge for C. Gives a small improvement
		// in table loading time.
		إذا (ctrl.fullspd && ctrl.have_state_ثبت_format)
			yynultrans_tbl->td_flags |= YYTD_PTRANS;
		yynultrans_tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);
		yynultrans_tbl->td_معلومات = yynultrans_معلومات =
		    حافظه_صفر_ورکړه(yynultrans_tbl->td_lolen,
			   حجم (flex_int32_t));

		لكل (i = 1; i <= lastdfa; ++i) {
			إذا ((yynultrans_tbl->td_flags & YYTD_PTRANS) != 0) {
				// Only works in very C-like languages  
				بهر_dec ("    &yy_transition[%d],\n",
					 بنسټ[i]);
				yynultrans_معلومات[i] = بنسټ[i];
			}
			وإلا {
				// This will work anywhere
				mkdata (nultrans[i]);
				yynultrans_معلومات[i] = nultrans[i];
			}
		}

		dataend (عدم);
		outn("]])");
		footprint += (lastdfa + 1) * (ctrl.fullspd ? حجم(بنية yy_trans_info *) : حجم(int32_t));
		إذا (tablesext) {
			yytbl_معلومات_compress (yynultrans_tbl);
			إذا (yytbl_معلومات_fwrite (&tableswr, yynultrans_tbl) <
			    0)
				flexerror (_
					   ("Could not write yynultrans_tbl"));
		}

		إذا (yynultrans_tbl != عدم) {
			yytbl_معلومات_destroy (yynultrans_tbl);
			yynultrans_tbl = عدم;
		}

		/* End generating yy_NUL_trans */
	}

	إذا (ctrl.ddebug) {		/* Spit out table mapping rules to line numbers. */
		/* Policy choice: we don't include this space
		 * in the table metering.
		 */
		بنية packtype_t *ptype = optimize_pack(عدد_قواعد);
		بهر_str ("m4_define([[M4_HOOK_DEBUGTABLE_TYPE]], [[%s]])", ptype->name);
		بهر_dec ("m4_define([[M4_HOOK_DEBUGTABLE_SIZE]], [[%d]])", عدد_قواعد);
		outn ("m4_define([[M4_HOOK_DEBUGTABLE_BODY]], [[m4_dnl");

		لكل (i = 1; i < عدد_قواعد; ++i)
			mkdata (قاعده_linenum[i]);
		dataend (عدم);
		outn("]])");
	}
}
