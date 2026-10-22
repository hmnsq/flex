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

#شامل "flexdef.h"
#شامل "tables.h"

/* These typedefs are only used for computing footprint sizes,
 * You need to make sure they match reality in the skeleton file to
 * get accurate numbers, but they don't otherwise matter.
 */
قسمتعریف حرف YY_CHAR;
ساخت yy_trans_info {int32_t yy_verify; int32_t yy_nxt;};

/* declare functions that have forward references */

ساکن خالی genecs(خالی);

ساخت packtype_t *optimize_pack(size_t sz)
{
	/* FIXME: There's a 32-bit assumption lurking here */
	ساکن ساخت packtype_t برآمد;
	اگر (sz == 0) {
		برآمد.name  = ctrl.long_align ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		برآمد.چوڑائی = ctrl.long_align ? 32 : 16;
	} ورنہ {
		برآمد.name = (ctrl.long_align || sz >= INT16_MAX) ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		برآمد.چوڑائی = (ctrl.long_align || sz >= INT16_MAX) ? 32 : 16;
	}
	واپس &برآمد;
}

/* Almost everything is done in terms of arrays starting at 1, so provide
 * a null entry for the zero element of all C arrays.  (The exception
 * to this is that the fast table representation generally uses the
 * 0 elements of its arrays, too.)
 */

/** Make the table for possible eol matches.
 *  @return the newly allocated rule_can_match_eol table
 */
ساکن ساخت yytbl_ڈیٹا *mkeoltbl (خالی)
{
	صحیح     i;
	flex_int8_t *tdata = 0;
	ساخت yytbl_ڈیٹا *tbl;

	tbl = صفر_حافظہ_دو(1, حجم (ساخت yytbl_ڈیٹا));
	yytbl_ڈیٹا_init (tbl, YYTD_ID_قاعدہ_CAN_مطابقت_EOL);
	tbl->td_flags = YYTD_DATA8;
	tbl->td_lolen = (flex_uint32_t) (عدد_قواعد + 1);
	tbl->td_ڈیٹا = tdata =
		صفر_حافظہ_دو(tbl->td_lolen, حجم (flex_int8_t));

	برائے (i = 1; i <= عدد_قواعد; i++)
		tdata[i] = قاعدہ_has_nl[i] ? 1 : 0;

	واپس tbl;
}

/* Generate the table for possible eol matches. */
ساکن خالی geneoltbl (خالی)
{
	صحیح     i;
	ساخت packtype_t *ptype = optimize_pack(عدد_قواعد);

	outn ("m4_ifdef( [[M4_MODE_YYLINENO]],[[");
	برآمد_str ("m4_define([[M4_HOOK_EOLTABLE_TYPE]], [[%s]])\n", ptype->name);
	برآمد_dec ("m4_define([[M4_HOOK_EOLTABLE_SIZE]], [[%d]])", عدد_قواعد + 1);
	outn ("m4_define([[M4_HOOK_EOLTABLE_BODY]], [[m4_dnl");

	اگر (gentables) {
		برائے (i = 1; i <= عدد_قواعد; i++) {
			برآمد_dec ("%d, ", قاعدہ_has_nl[i] ? 1 : 0);
			/* format nicely, 20 numbers per line. */
			اگر ((i % 20) == 19)
				برآمد ("\n    ");
		}
	}
	footprint += عدد_قواعد * ptype->چوڑائی;
	outn ("]])");
	outn ("]])");
}


/** mkctbl - make full speed compressed transition table
 * This is an array of structs; each struct a pair of integers.
 * You should call mkssltbl() immediately after this.
 * Then, I think, mkecstbl(). Arrrg.
 * @return the newly allocated trans table
 */

ساکن ساخت yytbl_ڈیٹا *mkctbl (خالی)
{
	صحیح i;
	ساخت yytbl_ڈیٹا *tbl = 0;
	flex_int32_t *tdata = 0, curr = 0;
	صحیح     انتہا_کا_بفر_action = عدد_قواعد + 1;

	ساخت packtype_t *ptype = optimize_pack(tblend + 2 + 1);
	برآمد_str ("m4_define([[M4_HOOK_MKCTBL_TYPE]], [[%s]])", ptype->name);

	tbl = صفر_حافظہ_دو(1, حجم (ساخت yytbl_ڈیٹا));
	yytbl_ڈیٹا_init (tbl, YYTD_ID_TRANSITION);
	tbl->td_flags = YYTD_DATA32 | YYTD_STRUCT;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (tblend + 2 + 1);	/* number of structs */

	tbl->td_ڈیٹا = tdata =
		صفر_حافظہ_دو(tbl->td_lolen * 2, حجم (flex_int32_t));

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

	جب (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	جب (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	بنیاد[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = انتہا_کا_بفر_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	برائے (i = 0; i <= lastdfa; ++i) {
		صحیح     anum = dfaacc[i].dfaacc_state;
		صحیح     انحراف = بنیاد[i];

		chk[انحراف] = EOB_POSITION;
		chk[انحراف - 1] = ACTION_POSITION;
		nxt[انحراف - 1] = anum;	/* action number */
	}

	برائے (i = 0; i <= tblend; ++i) {
		اگر (chk[i] == EOB_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = بنیاد[lastdfa + 1] - i;
		}

		ورنہ اگر (chk[i] == ACTION_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = nxt[i];
		}

		ورنہ اگر (chk[i] > numecs || chk[i] == 0) {
			tdata[curr++] = 0;
			tdata[curr++] = 0;
		}
		ورنہ {		/* verify, transition */

			tdata[curr++] = chk[i];
			tdata[curr++] = بنیاد[nxt[i]] - (i - chk[i]);
		}
	}

	/* Here's the final, end-of-buffer state. */
	tdata[curr++] = chk[tblend + 1];
	tdata[curr++] = nxt[tblend + 1];

	tdata[curr++] = chk[tblend + 2];
	tdata[curr++] = nxt[tblend + 2];

	واپس tbl;
}


/** Make start_state_list table.
 *  @return the newly allocated start_state_list table
 */
ساکن ساخت yytbl_ڈیٹا *mkssltbl (خالی)
{
	ساخت yytbl_ڈیٹا *tbl = 0;
	flex_int32_t *tdata = 0;
	flex_int32_t i;

	tbl = صفر_حافظہ_دو(1, حجم (ساخت yytbl_ڈیٹا));
	yytbl_ڈیٹا_init (tbl, YYTD_ID_آغاز_STATE_LIST);
	tbl->td_flags = YYTD_DATA32 | YYTD_PTRANS;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (lastsc * 2 + 1);

	tbl->td_ڈیٹا = tdata =
		صفر_حافظہ_دو(tbl->td_lolen, حجم (flex_int32_t));

	برائے (i = 0; i <= lastsc * 2; ++i)
		tdata[i] = بنیاد[i];

	واپس tbl;
}



/* genctbl - generates full speed compressed transition table */

ساکن خالی genctbl(خالی)
{
	صحیح i;
	صحیح     انتہا_کا_بفر_action = عدد_قواعد + 1;

	/* Table of verify for transition and offset to next state. */
	برآمد_dec ("m4_define([[M4_HOOK_TRANSTABLE_SIZE]], [[%d]])", tblend + 2 + 1);
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

	جب (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	جب (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	بنیاد[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = انتہا_کا_بفر_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	برائے (i = 0; i <= lastdfa; ++i) {
		صحیح     anum = dfaacc[i].dfaacc_state;
		صحیح     انحراف = بنیاد[i];

		chk[انحراف] = EOB_POSITION;
		chk[انحراف - 1] = ACTION_POSITION;
		nxt[انحراف - 1] = anum;	/* action number */
	}

	برائے (i = 0; i <= tblend; ++i) {
		اگر (chk[i] == EOB_POSITION)
			transition_struct_برآمد (0, بنیاد[lastdfa + 1] - i);

		ورنہ اگر (chk[i] == ACTION_POSITION)
			transition_struct_برآمد (0, nxt[i]);

		ورنہ اگر (chk[i] > numecs || chk[i] == 0)
			transition_struct_برآمد (0, 0);	/* unused slot */

		ورنہ		/* verify, transition */
			transition_struct_برآمد (chk[i],
					       بنیاد[nxt[i]] - (i -
							       chk[i]));
	}


	/* Here's the final, end-of-buffer state. */
	transition_struct_برآمد (chk[tblend + 1], nxt[tblend + 1]);
	transition_struct_برآمد (chk[tblend + 2], nxt[tblend + 2]);

	outn ("]])");
	footprint += حجم(ساخت yy_trans_info) * (tblend + 2 + 1);

	برآمد_dec ("m4_define([[M4_HOOK_STARTTABLE_SIZE]], [[%d]])", lastsc * 2 + 1);
	اگر (gentables) {
		outn ("m4_define([[M4_HOOK_STARTTABLE_BODY]], [[m4_dnl");
		برائے (i = 0; i <= lastsc * 2; ++i)
			برآمد_dec ("M4_HOOK_STATE_ENTRY_FORMAT(%d)", بنیاد[i]);

		dataend (تہی);
		outn("]])");
		footprint +=  حجم(ساخت yy_trans_info *) * (lastsc * 2 + 1);
	}

	اگر (ctrl.useecs)
		genecs ();
}


/* mkecstbl - Make equivalence-class tables.  */

ساکن ساخت yytbl_ڈیٹا *mkecstbl (خالی)
{
	صحیح i;
	ساخت yytbl_ڈیٹا *tbl = 0;
	flex_int32_t *tdata = 0;

	tbl = صفر_حافظہ_دو(1, حجم (ساخت yytbl_ڈیٹا));
	yytbl_ڈیٹا_init (tbl, YYTD_ID_EC);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) ctrl.csize;

	tbl->td_ڈیٹا = tdata =
		صفر_حافظہ_دو(tbl->td_lolen, حجم (flex_int32_t));

	برائے (i = 1; i < ctrl.csize; ++i) {
		ecgroup[i] = ABS (ecgroup[i]);
		tdata[i] = ecgroup[i];
	}

	واپس tbl;
}

/* Generate equivalence-class tables. */

ساکن خالی genecs(خالی)
{
	صحیح ch, صف;
	صحیح     numrows;

	برآمد_dec ("m4_define([[M4_HOOK_ECSTABLE_SIZE]], [[%d]])", ctrl.csize);
	outn ("m4_define([[M4_HOOK_ECSTABLE_BODY]], [[m4_dnl");

	برائے (ch = 1; ch < ctrl.csize; ++ch) {
		ecgroup[ch] = ABS (ecgroup[ch]);
		mkdata (ecgroup[ch]);
	}

	dataend (تہی);
	outn("]])");
	footprint += حجم(YY_CHAR) * ctrl.csize;

	اگر (env.trace) {
		fputs (_("\n\nEquivalence Classes:\n\n"), stderr);

		/* Print in 8 columns */
		numrows = ctrl.csize / 8;

		برائے (صف = 0; صف < numrows; ++صف) {
			برائے (ch = صف; ch < ctrl.csize; ch += numrows) {
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

ساکن ساخت yytbl_ڈیٹا *mkftbl(خالی)
{
	صحیح i;
	صحیح     انتہا_کا_بفر_action = عدد_قواعد + 1;
	ساخت yytbl_ڈیٹا *tbl;
	flex_int32_t *tdata = 0;

	tbl = صفر_حافظہ_دو(1, حجم (ساخت yytbl_ڈیٹا));
	yytbl_ڈیٹا_init (tbl, YYTD_ID_ACCEPT);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;	/* it's a one-dimensional array */
	tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);

	tbl->td_ڈیٹا = tdata =
		صفر_حافظہ_دو(tbl->td_lolen, حجم (flex_int32_t));

	dfaacc[انتہا_کا_بفر_state].dfaacc_state = انتہا_کا_بفر_action;

	برائے (i = 1; i <= lastdfa; ++i) {
		صحیح anum = dfaacc[i].dfaacc_state;

		tdata[i] = anum;

		اگر (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	واپس tbl;
}


/* genftbl - generate full transition table */

ساکن خالی genftbl(خالی)
{
	صحیح i;
	صحیح     انتہا_کا_بفر_action = عدد_قواعد + 1;
	ساخت packtype_t *ptype = optimize_pack(عدد_قواعد + 1);

	dfaacc[انتہا_کا_بفر_state].dfaacc_state = انتہا_کا_بفر_action;

	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	برآمد_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	برآمد_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", lastdfa + 1);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	برائے (i = 1; i <= lastdfa; ++i) {
		صحیح anum = dfaacc[i].dfaacc_state;

		mkdata (anum);

		اگر (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	dataend (تہی);
	outn("]])");
	footprint += (lastdfa + 1) * ptype->چوڑائی;

	اگر (ctrl.useecs)
		genecs ();

	/* Don't have to dump the actual full table entries - they were
	 * created on-the-fly.
	 */
}

/* gentabs - generate data statements for the transition tables */

ساکن خالی gentabs(خالی)
{
	صحیح     sz, i, j, k, *accset, nacc, *acc_array, کل_حالتیں;
	صحیح     انتہا_کا_بفر_action = عدد_قواعد + 1;
	ساخت yytbl_ڈیٹا *yyacc_tbl = 0, *yymeta_tbl = 0, *yybase_tbl = 0,
	    *yydef_tbl = 0, *yynxt_tbl = 0, *yychk_tbl = 0, *yyacclist_tbl=0;
	flex_int32_t *yyacc_ڈیٹا = 0, *yybase_ڈیٹا = 0, *yydef_ڈیٹا = 0,
	    *yynxt_ڈیٹا = 0, *yychk_ڈیٹا = 0, *yyacclist_ڈیٹا=0;
	flex_int32_t yybase_curr = 0, yyacclist_curr=0,yyacc_curr=0;
	ساخت packtype_t *ptype;

	acc_array = allocate_integer_array (current_max_dfas);
	nummt = 0;

	/* The compressed table format jams by entering the "jam state",
	 * losing information about the previous state in the process.
	 * In order to recover the previous state, we effectively need
	 * to keep backing-up information.
	 */
	++عدد_backing_اوپر;

	اگر (reject) {
		/* Write out accepting list and pointer list.

		 * First we generate the "yy_acclist" array.  In the process,
		 * we compute the indices that will go into the "yy_accept"
		 * array, and save the indices in the dfaacc array.
		 */
		صحیح     EOB_accepting_list[2];

		/* Set up accepting structures for the End Of Buffer state. */
		EOB_accepting_list[0] = 0;
		EOB_accepting_list[1] = انتہا_کا_بفر_action;
		accsiz[انتہا_کا_بفر_state] = 1;
		dfaacc[انتہا_کا_بفر_state].dfaacc_سیٹ =
		    EOB_accepting_list;

		sz = MAX (numas, 1) + 1;
		ptype = optimize_pack(sz);
		برآمد_str ("m4_define([[M4_HOOK_ACCLIST_TYPE]], [[%s]])", ptype->name);
		برآمد_dec ("m4_define([[M4_HOOK_ACCLIST_SIZE]], [[%d]])", sz);
		outn ("m4_define([[M4_HOOK_ACCLIST_BODY]], [[m4_dnl");

		yyacclist_tbl = صفر_حافظہ_دو(1,حجم(ساخت yytbl_ڈیٹا));
		yytbl_ڈیٹا_init (yyacclist_tbl, YYTD_ID_ACCLIST);
		yyacclist_tbl->td_lolen  = (flex_uint32_t) (MAX(numas,1) + 1);
		yyacclist_tbl->td_ڈیٹا = yyacclist_ڈیٹا =
		    صفر_حافظہ_دو(yyacclist_tbl->td_lolen, حجم (flex_int32_t));
		yyacclist_curr = 1;

		j = 1;		/* index into "yy_acclist" array */

		برائے (i = 1; i <= lastdfa; ++i) {
			acc_array[i] = j;

			اگر (accsiz[i] != 0) {
				accset = dfaacc[i].dfaacc_سیٹ;
				nacc = accsiz[i];

				اگر (env.trace)
					fprintf (stderr,
						 _("state # %d accepts: "),
						 i);

				برائے (k = 1; k <= nacc; ++k) {
					صحیح     accnum = accset[k];

					++j;

					اگر (variable_trailing_context_قواعد
					    && !(accnum &
						 YY_TRAILING_سر_نقاب)
					    && accnum > 0
					    && accnum <= عدد_قواعد
					    && قاعدہ_type[accnum] ==
					    قاعدہ_VARIABLE) {
						/* Special hack to flag
						 * accepting number as part
						 * of trailing context rule.
						 */
						accnum |= YY_TRAILING_نقاب;
					}

					mkdata (accnum);
					yyacclist_ڈیٹا[yyacclist_curr++] = accnum;

					اگر (env.trace) {
						fprintf (stderr, "[%d]",
							 accset[k]);

						اگر (k < nacc)
							fputs (", ",
							       stderr);
						ورنہ
							putc ('\n',
							      stderr);
					}
				}
			}
		}

		/* add accepting number for the "jam" state */
		acc_array[i] = j;

		dataend (تہی);
		outn("]])");
		footprint += sz * ptype->چوڑائی;
		اگر (tablesext) {
			yytbl_ڈیٹا_compress (yyacclist_tbl);
			اگر (yytbl_ڈیٹا_fwrite (&tableswr, yyacclist_tbl) < 0)
				flexerror (_("Could not write yyacclist_tbl"));
			yytbl_ڈیٹا_destroy (yyacclist_tbl);
			yyacclist_tbl = تہی;
		}
	}

	ورنہ {
		dfaacc[انتہا_کا_بفر_state].dfaacc_state =
		    انتہا_کا_بفر_action;

		برائے (i = 1; i <= lastdfa; ++i)
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

	اگر (reject)
		/* We put a "cap" on the table associating lists of accepting
		 * numbers with state numbers.  This is needed because we tell
		 * where the end of an accepting list is by looking at where
		 * the list for the next state starts.
		 */
		++sz;

	/* Note that this table is alternately defined if ctrl.fulltbl */
	ptype = optimize_pack(sz);
	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	برآمد_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	برآمد_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	yyacc_tbl = صفر_حافظہ_دو(1, حجم (ساخت yytbl_ڈیٹا));
	yytbl_ڈیٹا_init (yyacc_tbl, YYTD_ID_ACCEPT);
	yyacc_tbl->td_lolen = (flex_uint32_t) sz;
	yyacc_tbl->td_ڈیٹا = yyacc_ڈیٹا =
	    صفر_حافظہ_دو(yyacc_tbl->td_lolen, حجم (flex_int32_t));
	yyacc_curr=1;

	برائے (i = 1; i <= lastdfa; ++i) {
		mkdata (acc_array[i]);
		yyacc_ڈیٹا[yyacc_curr++] = acc_array[i];

		اگر (!reject && env.trace && acc_array[i])
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, acc_array[i]);
	}

	/* Add entry for "jam" state. */
	mkdata (acc_array[i]);
	yyacc_ڈیٹا[yyacc_curr++] = acc_array[i];

	اگر (reject) {
		/* Add "cap" for the list. */
		mkdata (acc_array[i]);
		yyacc_ڈیٹا[yyacc_curr++] = acc_array[i];
	}

	dataend (تہی);
	outn ("]])");
	footprint += sz * ptype->چوڑائی;

	اگر (tablesext) {
		yytbl_ڈیٹا_compress (yyacc_tbl);
		اگر (yytbl_ڈیٹا_fwrite (&tableswr, yyacc_tbl) < 0)
			flexerror (_("Could not write yyacc_tbl"));
	}
	yytbl_ڈیٹا_destroy (yyacc_tbl);
	yyacc_tbl = تہی;
	/* End generating yy_accept */

	اگر (ctrl.useecs) {

		genecs ();
		اگر (tablesext) {
			ساخت yytbl_ڈیٹا *tbl;

			tbl = mkecstbl ();
			yytbl_ڈیٹا_compress (tbl);
			اگر (yytbl_ڈیٹا_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ecstbl"));
			yytbl_ڈیٹا_destroy (tbl);
			tbl = 0;
		}
	}

	اگر (ctrl.usemecs) {
		/* Begin generating yy_meta */
		/* Write out meta-equivalence classes (used to index
		 * templates with).
		 */
		flex_int32_t *yymecs_ڈیٹا = 0;
		yymeta_tbl = صفر_حافظہ_دو(1, حجم (ساخت yytbl_ڈیٹا));
		yytbl_ڈیٹا_init (yymeta_tbl, YYTD_ID_META);
		yymeta_tbl->td_lolen = (flex_uint32_t) (numecs + 1);
		yymeta_tbl->td_ڈیٹا = yymecs_ڈیٹا =
		    صفر_حافظہ_دو(yymeta_tbl->td_lolen,
			   حجم (flex_int32_t));

		اگر (env.trace)
			fputs (_("\n\nMeta-Equivalence Classes:\n"),
			       stderr);
		برآمد_dec ("m4_define([[M4_HOOK_MECSTABLE_SIZE]], [[%d]])", numecs+1);
		outn ("m4_define([[M4_HOOK_MECSTABLE_BODY]], [[m4_dnl");
 	
		برائے (i = 1; i <= numecs; ++i) {
			اگر (env.trace)
				fprintf (stderr, "%d = %d\n",
					 i, ABS (tecbck[i]));

			mkdata (ABS (tecbck[i]));
			yymecs_ڈیٹا[i] = ABS (tecbck[i]);
		}

		dataend (تہی);
		outn ("]])");
		footprint += حجم(YY_CHAR) * (numecs + 1);
		اگر (tablesext) {
			yytbl_ڈیٹا_compress (yymeta_tbl);
			اگر (yytbl_ڈیٹا_fwrite (&tableswr, yymeta_tbl) < 0)
				flexerror (_("Could not write yymeta_tbl"));
		}
		yytbl_ڈیٹا_destroy (yymeta_tbl);
		yymeta_tbl = تہی;
		/* End generating yy_meta */
	}

	کل_حالتیں = lastdfa + numtemps;

	/* Begin generating yy_base */
	sz = کل_حالتیں + 1;
	ptype = optimize_pack(sz);
	برآمد_str ("m4_define([[M4_HOOK_BASE_TYPE]], [[%s]])", ptype->name);
	برآمد_dec ("m4_define([[M4_HOOK_BASE_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_BASE_BODY]], [[m4_dnl");

	yybase_tbl = صفر_حافظہ_دو (1, حجم (ساخت yytbl_ڈیٹا));
	yytbl_ڈیٹا_init (yybase_tbl, YYTD_ID_بنیاد);
	yybase_tbl->td_lolen = (flex_uint32_t) (کل_حالتیں + 1);
	yybase_tbl->td_ڈیٹا = yybase_ڈیٹا =
	    صفر_حافظہ_دو(yybase_tbl->td_lolen,
		   حجم (flex_int32_t));
	yybase_curr = 1;

	برائے (i = 1; i <= lastdfa; ++i) {
		صحیح d = def[i];

		اگر (بنیاد[i] == JAMSTATE)
			بنیاد[i] = jambase;

		اگر (d == JAMSTATE)
			def[i] = jamstate;

		ورنہ اگر (d < 0) {
			/* Template reference. */
			++tmpuses;
			def[i] = lastdfa - d + 1;
		}

		mkdata (بنیاد[i]);
		yybase_ڈیٹا[yybase_curr++] = بنیاد[i];
	}

	/* Generate jam state's base index. */
	mkdata (بنیاد[i]);
	yybase_ڈیٹا[yybase_curr++] = بنیاد[i];

	برائے (++i /* skip jam state */ ; i <= کل_حالتیں; ++i) {
		mkdata (بنیاد[i]);
		yybase_ڈیٹا[yybase_curr++] = بنیاد[i];
		def[i] = jamstate;
	}

	dataend (تہی);
	outn ("]])");
	footprint += sz * ptype->چوڑائی;

	اگر (tablesext) {
		yytbl_ڈیٹا_compress (yybase_tbl);
		اگر (yytbl_ڈیٹا_fwrite (&tableswr, yybase_tbl) < 0)
			flexerror (_("Could not write yybase_tbl"));
	}
	yytbl_ڈیٹا_destroy (yybase_tbl);
	yybase_tbl = تہی;
	/* End generating yy_base */


	/* Begin generating yy_def */
	ptype = optimize_pack(کل_حالتیں + 1);
	برآمد_str ("m4_define([[M4_HOOK_DEF_TYPE]], [[%s]])", ptype->name);
	برآمد_dec ("m4_define([[M4_HOOK_DEF_SIZE]], [[%d]])", کل_حالتیں + 1);
	outn ("m4_define([[M4_HOOK_DEF_BODY]], [[m4_dnl");

	yydef_tbl = صفر_حافظہ_دو(1, حجم (ساخت yytbl_ڈیٹا));
	yytbl_ڈیٹا_init (yydef_tbl, YYTD_ID_DEF);
	yydef_tbl->td_lolen = (flex_uint32_t)(کل_حالتیں + 1);
	yydef_tbl->td_ڈیٹا = yydef_ڈیٹا =
	    صفر_حافظہ_دو(yydef_tbl->td_lolen, حجم (flex_int32_t));

	برائے (i = 1; i <= کل_حالتیں; ++i) {
		mkdata (def[i]);
		yydef_ڈیٹا[i] = def[i];
	}

	dataend (تہی);
	outn ("]])");
	footprint += (کل_حالتیں + 1) * ptype->چوڑائی;

	اگر (tablesext) {
		yytbl_ڈیٹا_compress (yydef_tbl);
		اگر (yytbl_ڈیٹا_fwrite (&tableswr, yydef_tbl) < 0)
			flexerror (_("Could not write yydef_tbl"));
	}
	yytbl_ڈیٹا_destroy (yydef_tbl);
	yydef_tbl = تہی;
	/* End generating yy_def */


	ptype = optimize_pack(tblend + 1);
	/* Note: Used when !ctrl.fulltbl && !ctrl.fullspd).
	 * (Alternately defined when ctrl.fullspd)
	 */
	برآمد_str ("m4_define([[M4_HOOK_YYNXT_TYPE]], [[%s]])", ptype->name);
	برآمد_dec ("m4_define([[M4_HOOK_YYNXT_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_YYNXT_BODY]], [[m4_dnl");

	yynxt_tbl = صفر_حافظہ_دو (1, حجم (ساخت yytbl_ڈیٹا));
	yytbl_ڈیٹا_init (yynxt_tbl, YYTD_ID_NXT);
	yynxt_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yynxt_tbl->td_ڈیٹا = yynxt_ڈیٹا =
	    صفر_حافظہ_دو (yynxt_tbl->td_lolen, حجم (flex_int32_t));

	برائے (i = 1; i <= tblend; ++i) {
		/* Note, the order of the following test is important.
		 * If chk[i] is 0, then nxt[i] is undefined.
		 */
		اگر (chk[i] == 0 || nxt[i] == 0)
			nxt[i] = jamstate;	/* new state is the JAM state */

		mkdata (nxt[i]);
		yynxt_ڈیٹا[i] = nxt[i];
	}

	dataend (تہی);
	outn("]])");
	footprint += ptype->چوڑائی * (tblend + 1);

	اگر (tablesext) {
		yytbl_ڈیٹا_compress (yynxt_tbl);
		اگر (yytbl_ڈیٹا_fwrite (&tableswr, yynxt_tbl) < 0)
			flexerror (_("Could not write yynxt_tbl"));
	}
	yytbl_ڈیٹا_destroy (yynxt_tbl);
	yynxt_tbl = تہی;
	/* End generating yy_nxt */

	/* Begin generating yy_chk */
	ptype = optimize_pack(tblend + 1);
	برآمد_str ("m4_define([[M4_HOOK_CHK_TYPE]], [[%s]])", ptype->name);
	برآمد_dec ("m4_define([[M4_HOOK_CHK_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_CHK_BODY]], [[m4_dnl");
	
	yychk_tbl = صفر_حافظہ_دو (1, حجم (ساخت yytbl_ڈیٹا));
	yytbl_ڈیٹا_init (yychk_tbl, YYTD_ID_CHK);
	yychk_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yychk_tbl->td_ڈیٹا = yychk_ڈیٹا =
	    صفر_حافظہ_دو(yychk_tbl->td_lolen, حجم (flex_int32_t));

	برائے (i = 1; i <= tblend; ++i) {
		اگر (chk[i] == 0)
			++nummt;

		mkdata (chk[i]);
		yychk_ڈیٹا[i] = chk[i];
	}

	dataend (تہی);
	outn ("]])");
	footprint += ptype->چوڑائی * (tblend + 1);

	اگر (tablesext) {
		yytbl_ڈیٹا_compress (yychk_tbl);
		اگر (yytbl_ڈیٹا_fwrite (&tableswr, yychk_tbl) < 0)
			flexerror (_("Could not write yychk_tbl"));
	}
	yytbl_ڈیٹا_destroy (yychk_tbl);
	yychk_tbl = تہی;
	/* End generating yy_chk */

	آزاد(acc_array);
}


خالی visible_define (ثابت حرف *symname)
{
	برآمد_m4_define(symname, تہی);
	comment(symname);
	outc ('\n');
}

خالی visible_define_str (ثابت حرف *symname, ثابت حرف *val)
{
	حرف buf[128];
	برآمد_m4_define(symname, val);
	snprintf(buf, حجم(buf), "%s = %s", symname, val);
	comment(buf);
	outc ('\n');
}

خالی visible_define_int (ثابت حرف *symname, ثابت صحیح val)
{
	حرف nbuf[24], buf[128];
	snprintf(nbuf, حجم(nbuf), "%d", val);
	برآمد_m4_define(symname, nbuf);
	snprintf(buf, حجم(buf), "%s = %d", symname, val);
	comment(buf);
	outc ('\n');
}

/* make_tables - generate transition tables
 */

خالی make_tables (خالی)
{
	حرف buf[128];
	صحیح i;
	ساخت yytbl_ڈیٹا *yynultrans_tbl = تہی;

	/* This is where we REALLY begin generating the tables. */

	اگر (ctrl.fullspd) {
		genctbl ();
		اگر (tablesext) {
			ساخت yytbl_ڈیٹا *tbl;

			tbl = mkctbl ();
			yytbl_ڈیٹا_compress (tbl);
			اگر (yytbl_ڈیٹا_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_ڈیٹا_destroy (tbl);

			tbl = mkssltbl ();
			yytbl_ڈیٹا_compress (tbl);
			اگر (yytbl_ڈیٹا_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ssltbl"));
			yytbl_ڈیٹا_destroy (tbl);
			tbl = 0;

			اگر (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_ڈیٹا_compress (tbl);
				اگر (yytbl_ڈیٹا_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_ڈیٹا_destroy (tbl);
				tbl = 0;
			}
		}
	}
	ورنہ اگر (ctrl.fulltbl) {
		genftbl ();
		اگر (tablesext) {
			ساخت yytbl_ڈیٹا *tbl;

			/* Alternately defined if !ctrl.ffullspd && !ctrl.fulltbl */
			ساخت packtype_t *ptype;
			tbl = mkftbl ();
			yytbl_ڈیٹا_compress (tbl);
			ptype = optimize_pack(tbl->td_lolen);
			برآمد_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
			اگر (yytbl_ڈیٹا_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_ڈیٹا_destroy (tbl);
			tbl = 0;

			اگر (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_ڈیٹا_compress (tbl);
				اگر (yytbl_ڈیٹا_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_ڈیٹا_destroy (tbl);
				tbl = 0;
			}
		}
	}
	ورنہ {
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

	اگر (عدد_backing_اوپر > 0)
		visible_define ( "M4_MODE_HAS_BACKING_UP");

	// These are used for NUL transitions
	اگر ((عدد_backing_اوپر > 0 && !reject) && (!nultrans || ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NEED_YY_CP");
	اگر ((عدد_backing_اوپر > 0 && !reject) && (ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NULTRANS_WRAP");

	comment("m4 controls end\n");
	برآمد ("\n");

	اگر (ctrl.do_yylineno) {

		geneoltbl ();

		اگر (tablesext) {
			ساخت yytbl_ڈیٹا *tbl;

			tbl = mkeoltbl ();
			yytbl_ڈیٹا_compress (tbl);
			اگر (yytbl_ڈیٹا_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write eoltbl"));
			yytbl_ڈیٹا_destroy (tbl);
			tbl = 0;
		}
	}

	اگر (nultrans) {
		flex_int32_t *yynultrans_ڈیٹا = 0;

		/* Begin generating yy_NUL_trans */
		برآمد_str ("m4_define([[M4_HOOK_NULTRANS_TYPE]], [[%s]])", (ctrl.fullspd) ? "struct yy_trans_info*" : "M4_HOOK_INT32");
		برآمد_dec ("m4_define([[M4_HOOK_NULTRANS_SIZE]], [[%d]])", lastdfa + 1);
		outn ("m4_define([[M4_HOOK_NULTRANS_BODY]], [[m4_dnl");

		yynultrans_tbl = صفر_حافظہ_دو(1, حجم (ساخت yytbl_ڈیٹا));
		yytbl_ڈیٹا_init (yynultrans_tbl, YYTD_ID_NUL_TRANS);
		// Performance kludge for C. Gives a small improvement
		// in table loading time.
		اگر (ctrl.fullspd && ctrl.have_state_اندراج_format)
			yynultrans_tbl->td_flags |= YYTD_PTRANS;
		yynultrans_tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);
		yynultrans_tbl->td_ڈیٹا = yynultrans_ڈیٹا =
		    صفر_حافظہ_دو(yynultrans_tbl->td_lolen,
			   حجم (flex_int32_t));

		برائے (i = 1; i <= lastdfa; ++i) {
			اگر ((yynultrans_tbl->td_flags & YYTD_PTRANS) != 0) {
				// Only works in very C-like languages  
				برآمد_dec ("    &yy_transition[%d],\n",
					 بنیاد[i]);
				yynultrans_ڈیٹا[i] = بنیاد[i];
			}
			ورنہ {
				// This will work anywhere
				mkdata (nultrans[i]);
				yynultrans_ڈیٹا[i] = nultrans[i];
			}
		}

		dataend (تہی);
		outn("]])");
		footprint += (lastdfa + 1) * (ctrl.fullspd ? حجم(ساخت yy_trans_info *) : حجم(int32_t));
		اگر (tablesext) {
			yytbl_ڈیٹا_compress (yynultrans_tbl);
			اگر (yytbl_ڈیٹا_fwrite (&tableswr, yynultrans_tbl) <
			    0)
				flexerror (_
					   ("Could not write yynultrans_tbl"));
		}

		اگر (yynultrans_tbl != تہی) {
			yytbl_ڈیٹا_destroy (yynultrans_tbl);
			yynultrans_tbl = تہی;
		}

		/* End generating yy_NUL_trans */
	}

	اگر (ctrl.ddebug) {		/* Spit out table mapping rules to line numbers. */
		/* Policy choice: we don't include this space
		 * in the table metering.
		 */
		ساخت packtype_t *ptype = optimize_pack(عدد_قواعد);
		برآمد_str ("m4_define([[M4_HOOK_DEBUGTABLE_TYPE]], [[%s]])", ptype->name);
		برآمد_dec ("m4_define([[M4_HOOK_DEBUGTABLE_SIZE]], [[%d]])", عدد_قواعد);
		outn ("m4_define([[M4_HOOK_DEBUGTABLE_BODY]], [[m4_dnl");

		برائے (i = 1; i < عدد_قواعد; ++i)
			mkdata (قاعدہ_linenum[i]);
		dataend (تہی);
		outn("]])");
	}
}
