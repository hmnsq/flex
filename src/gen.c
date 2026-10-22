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

#অন্তর্ভাৱ "flexdef.h"
#অন্তর্ভাৱ "tables.h"

/* These typedefs are only used for computing footprint sizes,
 * You need to make sure they match reality in the skeleton file to
 * get accurate numbers, but they don't otherwise matter.
 */
প্রকারনির্দেশ ৱর্ণ YY_CHAR;
সংরচনা yy_trans_info {int32_t yy_verify; int32_t yy_nxt;};

/* declare functions that have forward references */

স্থির শূন্য genecs(শূন্য);

সংরচনা packtype_t *optimize_pack(size_t sz)
{
	/* FIXME: There's a 32-bit assumption lurking here */
	স্থির সংরচনা packtype_t out;
	যদি (sz == 0) {
		out.name  = ctrl.long_align ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		out.width = ctrl.long_align ? 32 : 16;
	} অন্যথা {
		out.name = (ctrl.long_align || sz >= INT16_MAX) ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		out.width = (ctrl.long_align || sz >= INT16_MAX) ? 32 : 16;
	}
	ঘূৰাই &out;
}

/* Almost everything is done in terms of arrays starting at 1, so provide
 * a null entry for the zero element of all C arrays.  (The exception
 * to this is that the fast table representation generally uses the
 * 0 elements of its arrays, too.)
 */

/** Make the table for possible eol matches.
 *  @return the newly allocated rule_can_match_eol table
 */
স্থির সংরচনা yytbl_data *mkeoltbl (শূন্য)
{
	পূর্ণাঙ্ক     i;
	flex_int8_t *tdata = 0;
	সংরচনা yytbl_data *tbl;

	tbl = calloc(1, পরিমাণ (সংরচনা yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_RULE_CAN_MATCH_EOL);
	tbl->td_flags = YYTD_DATA8;
	tbl->td_lolen = (flex_uint32_t) (অঙ্ক_rules + 1);
	tbl->td_data = tdata =
		calloc(tbl->td_lolen, পরিমাণ (flex_int8_t));

	বাবে (i = 1; i <= অঙ্ক_rules; i++)
		tdata[i] = rule_has_nl[i] ? 1 : 0;

	ঘূৰাই tbl;
}

/* Generate the table for possible eol matches. */
স্থির শূন্য geneoltbl (শূন্য)
{
	পূর্ণাঙ্ক     i;
	সংরচনা packtype_t *ptype = optimize_pack(অঙ্ক_rules);

	outn ("m4_ifdef( [[M4_MODE_YYLINENO]],[[");
	out_str ("m4_define([[M4_HOOK_EOLTABLE_TYPE]], [[%s]])\n", ptype->name);
	out_dec ("m4_define([[M4_HOOK_EOLTABLE_SIZE]], [[%d]])", অঙ্ক_rules + 1);
	outn ("m4_define([[M4_HOOK_EOLTABLE_BODY]], [[m4_dnl");

	যদি (gentables) {
		বাবে (i = 1; i <= অঙ্ক_rules; i++) {
			out_dec ("%d, ", rule_has_nl[i] ? 1 : 0);
			/* format nicely, 20 numbers per line. */
			যদি ((i % 20) == 19)
				out ("\n    ");
		}
	}
	footprint += অঙ্ক_rules * ptype->width;
	outn ("]])");
	outn ("]])");
}


/** mkctbl - make full speed compressed transition table
 * This is an array of structs; each struct a pair of integers.
 * You should call mkssltbl() immediately after this.
 * Then, I think, mkecstbl(). Arrrg.
 * @return the newly allocated trans table
 */

স্থির সংরচনা yytbl_data *mkctbl (শূন্য)
{
	পূর্ণাঙ্ক i;
	সংরচনা yytbl_data *tbl = 0;
	flex_int32_t *tdata = 0, curr = 0;
	পূর্ণাঙ্ক     end_of_buffer_action = অঙ্ক_rules + 1;

	সংরচনা packtype_t *ptype = optimize_pack(tblend + 2 + 1);
	out_str ("m4_define([[M4_HOOK_MKCTBL_TYPE]], [[%s]])", ptype->name);

	tbl = calloc(1, পরিমাণ (সংরচনা yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_TRANSITION);
	tbl->td_flags = YYTD_DATA32 | YYTD_STRUCT;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (tblend + 2 + 1);	/* number of structs */

	tbl->td_data = tdata =
		calloc(tbl->td_lolen * 2, পরিমাণ (flex_int32_t));

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

	যেতিয়ালৈ (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	যেতিয়ালৈ (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	base[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = end_of_buffer_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	বাবে (i = 0; i <= lastdfa; ++i) {
		পূর্ণাঙ্ক     anum = dfaacc[i].dfaacc_state;
		পূর্ণাঙ্ক     offset = base[i];

		chk[offset] = EOB_POSITION;
		chk[offset - 1] = ACTION_POSITION;
		nxt[offset - 1] = anum;	/* action number */
	}

	বাবে (i = 0; i <= tblend; ++i) {
		যদি (chk[i] == EOB_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = base[lastdfa + 1] - i;
		}

		অন্যথা যদি (chk[i] == ACTION_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = nxt[i];
		}

		অন্যথা যদি (chk[i] > numecs || chk[i] == 0) {
			tdata[curr++] = 0;
			tdata[curr++] = 0;
		}
		অন্যথা {		/* verify, transition */

			tdata[curr++] = chk[i];
			tdata[curr++] = base[nxt[i]] - (i - chk[i]);
		}
	}

	/* Here's the final, end-of-buffer state. */
	tdata[curr++] = chk[tblend + 1];
	tdata[curr++] = nxt[tblend + 1];

	tdata[curr++] = chk[tblend + 2];
	tdata[curr++] = nxt[tblend + 2];

	ঘূৰাই tbl;
}


/** Make start_state_list table.
 *  @return the newly allocated start_state_list table
 */
স্থির সংরচনা yytbl_data *mkssltbl (শূন্য)
{
	সংরচনা yytbl_data *tbl = 0;
	flex_int32_t *tdata = 0;
	flex_int32_t i;

	tbl = calloc(1, পরিমাণ (সংরচনা yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_START_STATE_LIST);
	tbl->td_flags = YYTD_DATA32 | YYTD_PTRANS;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (lastsc * 2 + 1);

	tbl->td_data = tdata =
		calloc(tbl->td_lolen, পরিমাণ (flex_int32_t));

	বাবে (i = 0; i <= lastsc * 2; ++i)
		tdata[i] = base[i];

	ঘূৰাই tbl;
}



/* genctbl - generates full speed compressed transition table */

স্থির শূন্য genctbl(শূন্য)
{
	পূর্ণাঙ্ক i;
	পূর্ণাঙ্ক     end_of_buffer_action = অঙ্ক_rules + 1;

	/* Table of verify for transition and offset to next state. */
	out_dec ("m4_define([[M4_HOOK_TRANSTABLE_SIZE]], [[%d]])", tblend + 2 + 1);
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

	যেতিয়ালৈ (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	যেতিয়ালৈ (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	base[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = end_of_buffer_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	বাবে (i = 0; i <= lastdfa; ++i) {
		পূর্ণাঙ্ক     anum = dfaacc[i].dfaacc_state;
		পূর্ণাঙ্ক     offset = base[i];

		chk[offset] = EOB_POSITION;
		chk[offset - 1] = ACTION_POSITION;
		nxt[offset - 1] = anum;	/* action number */
	}

	বাবে (i = 0; i <= tblend; ++i) {
		যদি (chk[i] == EOB_POSITION)
			transition_struct_out (0, base[lastdfa + 1] - i);

		অন্যথা যদি (chk[i] == ACTION_POSITION)
			transition_struct_out (0, nxt[i]);

		অন্যথা যদি (chk[i] > numecs || chk[i] == 0)
			transition_struct_out (0, 0);	/* unused slot */

		অন্যথা		/* verify, transition */
			transition_struct_out (chk[i],
					       base[nxt[i]] - (i -
							       chk[i]));
	}


	/* Here's the final, end-of-buffer state. */
	transition_struct_out (chk[tblend + 1], nxt[tblend + 1]);
	transition_struct_out (chk[tblend + 2], nxt[tblend + 2]);

	outn ("]])");
	footprint += পরিমাণ(সংরচনা yy_trans_info) * (tblend + 2 + 1);

	out_dec ("m4_define([[M4_HOOK_STARTTABLE_SIZE]], [[%d]])", lastsc * 2 + 1);
	যদি (gentables) {
		outn ("m4_define([[M4_HOOK_STARTTABLE_BODY]], [[m4_dnl");
		বাবে (i = 0; i <= lastsc * 2; ++i)
			out_dec ("M4_HOOK_STATE_ENTRY_FORMAT(%d)", base[i]);

		dataend (রিক্ত);
		outn("]])");
		footprint +=  পরিমাণ(সংরচনা yy_trans_info *) * (lastsc * 2 + 1);
	}

	যদি (ctrl.useecs)
		genecs ();
}


/* mkecstbl - Make equivalence-class tables.  */

স্থির সংরচনা yytbl_data *mkecstbl (শূন্য)
{
	পূর্ণাঙ্ক i;
	সংরচনা yytbl_data *tbl = 0;
	flex_int32_t *tdata = 0;

	tbl = calloc(1, পরিমাণ (সংরচনা yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_EC);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) ctrl.csize;

	tbl->td_data = tdata =
		calloc(tbl->td_lolen, পরিমাণ (flex_int32_t));

	বাবে (i = 1; i < ctrl.csize; ++i) {
		ecgroup[i] = ABS (ecgroup[i]);
		tdata[i] = ecgroup[i];
	}

	ঘূৰাই tbl;
}

/* Generate equivalence-class tables. */

স্থির শূন্য genecs(শূন্য)
{
	পূর্ণাঙ্ক ch, row;
	পূর্ণাঙ্ক     numrows;

	out_dec ("m4_define([[M4_HOOK_ECSTABLE_SIZE]], [[%d]])", ctrl.csize);
	outn ("m4_define([[M4_HOOK_ECSTABLE_BODY]], [[m4_dnl");

	বাবে (ch = 1; ch < ctrl.csize; ++ch) {
		ecgroup[ch] = ABS (ecgroup[ch]);
		mkdata (ecgroup[ch]);
	}

	dataend (রিক্ত);
	outn("]])");
	footprint += পরিমাণ(YY_CHAR) * ctrl.csize;

	যদি (env.trace) {
		fputs (_("\n\nEquivalence Classes:\n\n"), stderr);

		/* Print in 8 columns */
		numrows = ctrl.csize / 8;

		বাবে (row = 0; row < numrows; ++row) {
			বাবে (ch = row; ch < ctrl.csize; ch += numrows) {
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

স্থির সংরচনা yytbl_data *mkftbl(শূন্য)
{
	পূর্ণাঙ্ক i;
	পূর্ণাঙ্ক     end_of_buffer_action = অঙ্ক_rules + 1;
	সংরচনা yytbl_data *tbl;
	flex_int32_t *tdata = 0;

	tbl = calloc(1, পরিমাণ (সংরচনা yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_ACCEPT);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;	/* it's a one-dimensional array */
	tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);

	tbl->td_data = tdata =
		calloc(tbl->td_lolen, পরিমাণ (flex_int32_t));

	dfaacc[end_of_buffer_state].dfaacc_state = end_of_buffer_action;

	বাবে (i = 1; i <= lastdfa; ++i) {
		পূর্ণাঙ্ক anum = dfaacc[i].dfaacc_state;

		tdata[i] = anum;

		যদি (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	ঘূৰাই tbl;
}


/* genftbl - generate full transition table */

স্থির শূন্য genftbl(শূন্য)
{
	পূর্ণাঙ্ক i;
	পূর্ণাঙ্ক     end_of_buffer_action = অঙ্ক_rules + 1;
	সংরচনা packtype_t *ptype = optimize_pack(অঙ্ক_rules + 1);

	dfaacc[end_of_buffer_state].dfaacc_state = end_of_buffer_action;

	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	out_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", lastdfa + 1);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	বাবে (i = 1; i <= lastdfa; ++i) {
		পূর্ণাঙ্ক anum = dfaacc[i].dfaacc_state;

		mkdata (anum);

		যদি (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	dataend (রিক্ত);
	outn("]])");
	footprint += (lastdfa + 1) * ptype->width;

	যদি (ctrl.useecs)
		genecs ();

	/* Don't have to dump the actual full table entries - they were
	 * created on-the-fly.
	 */
}

/* gentabs - generate data statements for the transition tables */

স্থির শূন্য gentabs(শূন্য)
{
	পূর্ণাঙ্ক     sz, i, j, k, *accset, nacc, *acc_array, total_states;
	পূর্ণাঙ্ক     end_of_buffer_action = অঙ্ক_rules + 1;
	সংরচনা yytbl_data *yyacc_tbl = 0, *yymeta_tbl = 0, *yybase_tbl = 0,
	    *yydef_tbl = 0, *yynxt_tbl = 0, *yychk_tbl = 0, *yyacclist_tbl=0;
	flex_int32_t *yyacc_data = 0, *yybase_data = 0, *yydef_data = 0,
	    *yynxt_data = 0, *yychk_data = 0, *yyacclist_data=0;
	flex_int32_t yybase_curr = 0, yyacclist_curr=0,yyacc_curr=0;
	সংরচনা packtype_t *ptype;

	acc_array = allocate_integer_array (current_max_dfas);
	nummt = 0;

	/* The compressed table format jams by entering the "jam state",
	 * losing information about the previous state in the process.
	 * In order to recover the previous state, we effectively need
	 * to keep backing-up information.
	 */
	++অঙ্ক_backing_up;

	যদি (reject) {
		/* Write out accepting list and pointer list.

		 * First we generate the "yy_acclist" array.  In the process,
		 * we compute the indices that will go into the "yy_accept"
		 * array, and save the indices in the dfaacc array.
		 */
		পূর্ণাঙ্ক     EOB_accepting_list[2];

		/* Set up accepting structures for the End Of Buffer state. */
		EOB_accepting_list[0] = 0;
		EOB_accepting_list[1] = end_of_buffer_action;
		accsiz[end_of_buffer_state] = 1;
		dfaacc[end_of_buffer_state].dfaacc_set =
		    EOB_accepting_list;

		sz = MAX (numas, 1) + 1;
		ptype = optimize_pack(sz);
		out_str ("m4_define([[M4_HOOK_ACCLIST_TYPE]], [[%s]])", ptype->name);
		out_dec ("m4_define([[M4_HOOK_ACCLIST_SIZE]], [[%d]])", sz);
		outn ("m4_define([[M4_HOOK_ACCLIST_BODY]], [[m4_dnl");

		yyacclist_tbl = calloc(1,পরিমাণ(সংরচনা yytbl_data));
		yytbl_data_init (yyacclist_tbl, YYTD_ID_ACCLIST);
		yyacclist_tbl->td_lolen  = (flex_uint32_t) (MAX(numas,1) + 1);
		yyacclist_tbl->td_data = yyacclist_data =
		    calloc(yyacclist_tbl->td_lolen, পরিমাণ (flex_int32_t));
		yyacclist_curr = 1;

		j = 1;		/* index into "yy_acclist" array */

		বাবে (i = 1; i <= lastdfa; ++i) {
			acc_array[i] = j;

			যদি (accsiz[i] != 0) {
				accset = dfaacc[i].dfaacc_set;
				nacc = accsiz[i];

				যদি (env.trace)
					fprintf (stderr,
						 _("state # %d accepts: "),
						 i);

				বাবে (k = 1; k <= nacc; ++k) {
					পূর্ণাঙ্ক     accnum = accset[k];

					++j;

					যদি (variable_trailing_context_rules
					    && !(accnum &
						 YY_TRAILING_HEAD_MASK)
					    && accnum > 0
					    && accnum <= অঙ্ক_rules
					    && rule_type[accnum] ==
					    RULE_VARIABLE) {
						/* Special hack to flag
						 * accepting number as part
						 * of trailing context rule.
						 */
						accnum |= YY_TRAILING_MASK;
					}

					mkdata (accnum);
					yyacclist_data[yyacclist_curr++] = accnum;

					যদি (env.trace) {
						fprintf (stderr, "[%d]",
							 accset[k]);

						যদি (k < nacc)
							fputs (", ",
							       stderr);
						অন্যথা
							putc ('\n',
							      stderr);
					}
				}
			}
		}

		/* add accepting number for the "jam" state */
		acc_array[i] = j;

		dataend (রিক্ত);
		outn("]])");
		footprint += sz * ptype->width;
		যদি (tablesext) {
			yytbl_data_compress (yyacclist_tbl);
			যদি (yytbl_data_fwrite (&tableswr, yyacclist_tbl) < 0)
				flexerror (_("Could not write yyacclist_tbl"));
			yytbl_data_destroy (yyacclist_tbl);
			yyacclist_tbl = রিক্ত;
		}
	}

	অন্যথা {
		dfaacc[end_of_buffer_state].dfaacc_state =
		    end_of_buffer_action;

		বাবে (i = 1; i <= lastdfa; ++i)
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

	যদি (reject)
		/* We put a "cap" on the table associating lists of accepting
		 * numbers with state numbers.  This is needed because we tell
		 * where the end of an accepting list is by looking at where
		 * the list for the next state starts.
		 */
		++sz;

	/* Note that this table is alternately defined if ctrl.fulltbl */
	ptype = optimize_pack(sz);
	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	out_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	yyacc_tbl = calloc(1, পরিমাণ (সংরচনা yytbl_data));
	yytbl_data_init (yyacc_tbl, YYTD_ID_ACCEPT);
	yyacc_tbl->td_lolen = (flex_uint32_t) sz;
	yyacc_tbl->td_data = yyacc_data =
	    calloc(yyacc_tbl->td_lolen, পরিমাণ (flex_int32_t));
	yyacc_curr=1;

	বাবে (i = 1; i <= lastdfa; ++i) {
		mkdata (acc_array[i]);
		yyacc_data[yyacc_curr++] = acc_array[i];

		যদি (!reject && env.trace && acc_array[i])
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, acc_array[i]);
	}

	/* Add entry for "jam" state. */
	mkdata (acc_array[i]);
	yyacc_data[yyacc_curr++] = acc_array[i];

	যদি (reject) {
		/* Add "cap" for the list. */
		mkdata (acc_array[i]);
		yyacc_data[yyacc_curr++] = acc_array[i];
	}

	dataend (রিক্ত);
	outn ("]])");
	footprint += sz * ptype->width;

	যদি (tablesext) {
		yytbl_data_compress (yyacc_tbl);
		যদি (yytbl_data_fwrite (&tableswr, yyacc_tbl) < 0)
			flexerror (_("Could not write yyacc_tbl"));
	}
	yytbl_data_destroy (yyacc_tbl);
	yyacc_tbl = রিক্ত;
	/* End generating yy_accept */

	যদি (ctrl.useecs) {

		genecs ();
		যদি (tablesext) {
			সংরচনা yytbl_data *tbl;

			tbl = mkecstbl ();
			yytbl_data_compress (tbl);
			যদি (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ecstbl"));
			yytbl_data_destroy (tbl);
			tbl = 0;
		}
	}

	যদি (ctrl.usemecs) {
		/* Begin generating yy_meta */
		/* Write out meta-equivalence classes (used to index
		 * templates with).
		 */
		flex_int32_t *yymecs_data = 0;
		yymeta_tbl = calloc(1, পরিমাণ (সংরচনা yytbl_data));
		yytbl_data_init (yymeta_tbl, YYTD_ID_META);
		yymeta_tbl->td_lolen = (flex_uint32_t) (numecs + 1);
		yymeta_tbl->td_data = yymecs_data =
		    calloc(yymeta_tbl->td_lolen,
			   পরিমাণ (flex_int32_t));

		যদি (env.trace)
			fputs (_("\n\nMeta-Equivalence Classes:\n"),
			       stderr);
		out_dec ("m4_define([[M4_HOOK_MECSTABLE_SIZE]], [[%d]])", numecs+1);
		outn ("m4_define([[M4_HOOK_MECSTABLE_BODY]], [[m4_dnl");
 	
		বাবে (i = 1; i <= numecs; ++i) {
			যদি (env.trace)
				fprintf (stderr, "%d = %d\n",
					 i, ABS (tecbck[i]));

			mkdata (ABS (tecbck[i]));
			yymecs_data[i] = ABS (tecbck[i]);
		}

		dataend (রিক্ত);
		outn ("]])");
		footprint += পরিমাণ(YY_CHAR) * (numecs + 1);
		যদি (tablesext) {
			yytbl_data_compress (yymeta_tbl);
			যদি (yytbl_data_fwrite (&tableswr, yymeta_tbl) < 0)
				flexerror (_("Could not write yymeta_tbl"));
		}
		yytbl_data_destroy (yymeta_tbl);
		yymeta_tbl = রিক্ত;
		/* End generating yy_meta */
	}

	total_states = lastdfa + numtemps;

	/* Begin generating yy_base */
	sz = total_states + 1;
	ptype = optimize_pack(sz);
	out_str ("m4_define([[M4_HOOK_BASE_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_BASE_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_BASE_BODY]], [[m4_dnl");

	yybase_tbl = calloc (1, পরিমাণ (সংরচনা yytbl_data));
	yytbl_data_init (yybase_tbl, YYTD_ID_BASE);
	yybase_tbl->td_lolen = (flex_uint32_t) (total_states + 1);
	yybase_tbl->td_data = yybase_data =
	    calloc(yybase_tbl->td_lolen,
		   পরিমাণ (flex_int32_t));
	yybase_curr = 1;

	বাবে (i = 1; i <= lastdfa; ++i) {
		পূর্ণাঙ্ক d = def[i];

		যদি (base[i] == JAMSTATE)
			base[i] = jambase;

		যদি (d == JAMSTATE)
			def[i] = jamstate;

		অন্যথা যদি (d < 0) {
			/* Template reference. */
			++tmpuses;
			def[i] = lastdfa - d + 1;
		}

		mkdata (base[i]);
		yybase_data[yybase_curr++] = base[i];
	}

	/* Generate jam state's base index. */
	mkdata (base[i]);
	yybase_data[yybase_curr++] = base[i];

	বাবে (++i /* skip jam state */ ; i <= total_states; ++i) {
		mkdata (base[i]);
		yybase_data[yybase_curr++] = base[i];
		def[i] = jamstate;
	}

	dataend (রিক্ত);
	outn ("]])");
	footprint += sz * ptype->width;

	যদি (tablesext) {
		yytbl_data_compress (yybase_tbl);
		যদি (yytbl_data_fwrite (&tableswr, yybase_tbl) < 0)
			flexerror (_("Could not write yybase_tbl"));
	}
	yytbl_data_destroy (yybase_tbl);
	yybase_tbl = রিক্ত;
	/* End generating yy_base */


	/* Begin generating yy_def */
	ptype = optimize_pack(total_states + 1);
	out_str ("m4_define([[M4_HOOK_DEF_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_DEF_SIZE]], [[%d]])", total_states + 1);
	outn ("m4_define([[M4_HOOK_DEF_BODY]], [[m4_dnl");

	yydef_tbl = calloc(1, পরিমাণ (সংরচনা yytbl_data));
	yytbl_data_init (yydef_tbl, YYTD_ID_DEF);
	yydef_tbl->td_lolen = (flex_uint32_t)(total_states + 1);
	yydef_tbl->td_data = yydef_data =
	    calloc(yydef_tbl->td_lolen, পরিমাণ (flex_int32_t));

	বাবে (i = 1; i <= total_states; ++i) {
		mkdata (def[i]);
		yydef_data[i] = def[i];
	}

	dataend (রিক্ত);
	outn ("]])");
	footprint += (total_states + 1) * ptype->width;

	যদি (tablesext) {
		yytbl_data_compress (yydef_tbl);
		যদি (yytbl_data_fwrite (&tableswr, yydef_tbl) < 0)
			flexerror (_("Could not write yydef_tbl"));
	}
	yytbl_data_destroy (yydef_tbl);
	yydef_tbl = রিক্ত;
	/* End generating yy_def */


	ptype = optimize_pack(tblend + 1);
	/* Note: Used when !ctrl.fulltbl && !ctrl.fullspd).
	 * (Alternately defined when ctrl.fullspd)
	 */
	out_str ("m4_define([[M4_HOOK_YYNXT_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_YYNXT_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_YYNXT_BODY]], [[m4_dnl");

	yynxt_tbl = calloc (1, পরিমাণ (সংরচনা yytbl_data));
	yytbl_data_init (yynxt_tbl, YYTD_ID_NXT);
	yynxt_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yynxt_tbl->td_data = yynxt_data =
	    calloc (yynxt_tbl->td_lolen, পরিমাণ (flex_int32_t));

	বাবে (i = 1; i <= tblend; ++i) {
		/* Note, the order of the following test is important.
		 * If chk[i] is 0, then nxt[i] is undefined.
		 */
		যদি (chk[i] == 0 || nxt[i] == 0)
			nxt[i] = jamstate;	/* new state is the JAM state */

		mkdata (nxt[i]);
		yynxt_data[i] = nxt[i];
	}

	dataend (রিক্ত);
	outn("]])");
	footprint += ptype->width * (tblend + 1);

	যদি (tablesext) {
		yytbl_data_compress (yynxt_tbl);
		যদি (yytbl_data_fwrite (&tableswr, yynxt_tbl) < 0)
			flexerror (_("Could not write yynxt_tbl"));
	}
	yytbl_data_destroy (yynxt_tbl);
	yynxt_tbl = রিক্ত;
	/* End generating yy_nxt */

	/* Begin generating yy_chk */
	ptype = optimize_pack(tblend + 1);
	out_str ("m4_define([[M4_HOOK_CHK_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_CHK_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_CHK_BODY]], [[m4_dnl");
	
	yychk_tbl = calloc (1, পরিমাণ (সংরচনা yytbl_data));
	yytbl_data_init (yychk_tbl, YYTD_ID_CHK);
	yychk_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yychk_tbl->td_data = yychk_data =
	    calloc(yychk_tbl->td_lolen, পরিমাণ (flex_int32_t));

	বাবে (i = 1; i <= tblend; ++i) {
		যদি (chk[i] == 0)
			++nummt;

		mkdata (chk[i]);
		yychk_data[i] = chk[i];
	}

	dataend (রিক্ত);
	outn ("]])");
	footprint += ptype->width * (tblend + 1);

	যদি (tablesext) {
		yytbl_data_compress (yychk_tbl);
		যদি (yytbl_data_fwrite (&tableswr, yychk_tbl) < 0)
			flexerror (_("Could not write yychk_tbl"));
	}
	yytbl_data_destroy (yychk_tbl);
	yychk_tbl = রিক্ত;
	/* End generating yy_chk */

	মুক্ত(acc_array);
}


শূন্য visible_define (ধ্রুৱ ৱর্ণ *symname)
{
	out_m4_define(symname, রিক্ত);
	comment(symname);
	outc ('\n');
}

শূন্য visible_define_str (ধ্রুৱ ৱর্ণ *symname, ধ্রুৱ ৱর্ণ *val)
{
	ৱর্ণ buf[128];
	out_m4_define(symname, val);
	snprintf(buf, পরিমাণ(buf), "%s = %s", symname, val);
	comment(buf);
	outc ('\n');
}

শূন্য visible_define_int (ধ্রুৱ ৱর্ণ *symname, ধ্রুৱ পূর্ণাঙ্ক val)
{
	ৱর্ণ nbuf[24], buf[128];
	snprintf(nbuf, পরিমাণ(nbuf), "%d", val);
	out_m4_define(symname, nbuf);
	snprintf(buf, পরিমাণ(buf), "%s = %d", symname, val);
	comment(buf);
	outc ('\n');
}

/* make_tables - generate transition tables
 */

শূন্য make_tables (শূন্য)
{
	ৱর্ণ buf[128];
	পূর্ণাঙ্ক i;
	সংরচনা yytbl_data *yynultrans_tbl = রিক্ত;

	/* This is where we REALLY begin generating the tables. */

	যদি (ctrl.fullspd) {
		genctbl ();
		যদি (tablesext) {
			সংরচনা yytbl_data *tbl;

			tbl = mkctbl ();
			yytbl_data_compress (tbl);
			যদি (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_data_destroy (tbl);

			tbl = mkssltbl ();
			yytbl_data_compress (tbl);
			যদি (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ssltbl"));
			yytbl_data_destroy (tbl);
			tbl = 0;

			যদি (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_data_compress (tbl);
				যদি (yytbl_data_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_data_destroy (tbl);
				tbl = 0;
			}
		}
	}
	অন্যথা যদি (ctrl.fulltbl) {
		genftbl ();
		যদি (tablesext) {
			সংরচনা yytbl_data *tbl;

			/* Alternately defined if !ctrl.ffullspd && !ctrl.fulltbl */
			সংরচনা packtype_t *ptype;
			tbl = mkftbl ();
			yytbl_data_compress (tbl);
			ptype = optimize_pack(tbl->td_lolen);
			out_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
			যদি (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_data_destroy (tbl);
			tbl = 0;

			যদি (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_data_compress (tbl);
				যদি (yytbl_data_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_data_destroy (tbl);
				tbl = 0;
			}
		}
	}
	অন্যথা {
		gentabs ();
	}

	snprintf(buf, পরিমাণ(buf), "footprint: %ld bytes\n", footprint);
	comment(buf);
	snprintf(buf, পরিমাণ(buf), "tblend: %d\n", tblend);
	comment(buf);
	snprintf(buf, পরিমাণ(buf), "numecs: %d\n", numecs);
	comment(buf);
	snprintf(buf, পরিমাণ(buf), "num_rules: %d\n", অঙ্ক_rules);
	comment(buf);
	snprintf(buf, পরিমাণ(buf), "lastdfa: %d\n", lastdfa);
	comment(buf);
	outc ('\n');
	
	// Only at this point do we know if the automaton has backups.
	// Some m4 conditionals require this information.

	comment("m4 controls begin\n");

	যদি (অঙ্ক_backing_up > 0)
		visible_define ( "M4_MODE_HAS_BACKING_UP");

	// These are used for NUL transitions
	যদি ((অঙ্ক_backing_up > 0 && !reject) && (!nultrans || ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NEED_YY_CP");
	যদি ((অঙ্ক_backing_up > 0 && !reject) && (ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NULTRANS_WRAP");

	comment("m4 controls end\n");
	out ("\n");

	যদি (ctrl.do_yylineno) {

		geneoltbl ();

		যদি (tablesext) {
			সংরচনা yytbl_data *tbl;

			tbl = mkeoltbl ();
			yytbl_data_compress (tbl);
			যদি (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write eoltbl"));
			yytbl_data_destroy (tbl);
			tbl = 0;
		}
	}

	যদি (nultrans) {
		flex_int32_t *yynultrans_data = 0;

		/* Begin generating yy_NUL_trans */
		out_str ("m4_define([[M4_HOOK_NULTRANS_TYPE]], [[%s]])", (ctrl.fullspd) ? "struct yy_trans_info*" : "M4_HOOK_INT32");
		out_dec ("m4_define([[M4_HOOK_NULTRANS_SIZE]], [[%d]])", lastdfa + 1);
		outn ("m4_define([[M4_HOOK_NULTRANS_BODY]], [[m4_dnl");

		yynultrans_tbl = calloc(1, পরিমাণ (সংরচনা yytbl_data));
		yytbl_data_init (yynultrans_tbl, YYTD_ID_NUL_TRANS);
		// Performance kludge for C. Gives a small improvement
		// in table loading time.
		যদি (ctrl.fullspd && ctrl.have_state_entry_format)
			yynultrans_tbl->td_flags |= YYTD_PTRANS;
		yynultrans_tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);
		yynultrans_tbl->td_data = yynultrans_data =
		    calloc(yynultrans_tbl->td_lolen,
			   পরিমাণ (flex_int32_t));

		বাবে (i = 1; i <= lastdfa; ++i) {
			যদি ((yynultrans_tbl->td_flags & YYTD_PTRANS) != 0) {
				// Only works in very C-like languages  
				out_dec ("    &yy_transition[%d],\n",
					 base[i]);
				yynultrans_data[i] = base[i];
			}
			অন্যথা {
				// This will work anywhere
				mkdata (nultrans[i]);
				yynultrans_data[i] = nultrans[i];
			}
		}

		dataend (রিক্ত);
		outn("]])");
		footprint += (lastdfa + 1) * (ctrl.fullspd ? পরিমাণ(সংরচনা yy_trans_info *) : পরিমাণ(int32_t));
		যদি (tablesext) {
			yytbl_data_compress (yynultrans_tbl);
			যদি (yytbl_data_fwrite (&tableswr, yynultrans_tbl) <
			    0)
				flexerror (_
					   ("Could not write yynultrans_tbl"));
		}

		যদি (yynultrans_tbl != রিক্ত) {
			yytbl_data_destroy (yynultrans_tbl);
			yynultrans_tbl = রিক্ত;
		}

		/* End generating yy_NUL_trans */
	}

	যদি (ctrl.ddebug) {		/* Spit out table mapping rules to line numbers. */
		/* Policy choice: we don't include this space
		 * in the table metering.
		 */
		সংরচনা packtype_t *ptype = optimize_pack(অঙ্ক_rules);
		out_str ("m4_define([[M4_HOOK_DEBUGTABLE_TYPE]], [[%s]])", ptype->name);
		out_dec ("m4_define([[M4_HOOK_DEBUGTABLE_SIZE]], [[%d]])", অঙ্ক_rules);
		outn ("m4_define([[M4_HOOK_DEBUGTABLE_BODY]], [[m4_dnl");

		বাবে (i = 1; i < অঙ্ক_rules; ++i)
			mkdata (rule_linenum[i]);
		dataend (রিক্ত);
		outn("]])");
	}
}
