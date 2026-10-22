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

#அந்தர்பாவ "flexdef.h"
#அந்தர்பாவ "tables.h"

/* These typedefs are only used for computing footprint sizes,
 * You need to make sure they match reality in the skeleton file to
 * get accurate numbers, but they don't otherwise matter.
 */
வகைவரை எழுத்து YY_CHAR;
கட்டமைப்பு yy_trans_info {int32_t yy_verify; int32_t yy_nxt;};

/* declare functions that have forward references */

நிலையான வெறுமை genecs(வெறுமை);

கட்டமைப்பு packtype_t *optimize_pack(size_t sz)
{
	/* FIXME: There's a 32-bit assumption lurking here */
	நிலையான கட்டமைப்பு packtype_t out;
	எனில் (sz == 0) {
		out.name  = ctrl.long_align ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		out.width = ctrl.long_align ? 32 : 16;
	} இல்லையெனில் {
		out.name = (ctrl.long_align || sz >= INT16_MAX) ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		out.width = (ctrl.long_align || sz >= INT16_MAX) ? 32 : 16;
	}
	திரும்பு &out;
}

/* Almost everything is done in terms of arrays starting at 1, so provide
 * a null entry for the zero element of all C arrays.  (The exception
 * to this is that the fast table representation generally uses the
 * 0 elements of its arrays, too.)
 */

/** Make the table for possible eol matches.
 *  @return the newly allocated rule_can_match_eol table
 */
நிலையான கட்டமைப்பு yytbl_data *mkeoltbl (வெறுமை)
{
	முழு     i;
	flex_int8_t *tdata = 0;
	கட்டமைப்பு yytbl_data *tbl;

	tbl = calloc(1, அளவு (கட்டமைப்பு yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_RULE_CAN_MATCH_EOL);
	tbl->td_flags = YYTD_DATA8;
	tbl->td_lolen = (flex_uint32_t) (இலக்கம்_rules + 1);
	tbl->td_data = tdata =
		calloc(tbl->td_lolen, அளவு (flex_int8_t));

	க்கு (i = 1; i <= இலக்கம்_rules; i++)
		tdata[i] = rule_has_nl[i] ? 1 : 0;

	திரும்பு tbl;
}

/* Generate the table for possible eol matches. */
நிலையான வெறுமை geneoltbl (வெறுமை)
{
	முழு     i;
	கட்டமைப்பு packtype_t *ptype = optimize_pack(இலக்கம்_rules);

	outn ("m4_ifdef( [[M4_MODE_YYLINENO]],[[");
	out_str ("m4_define([[M4_HOOK_EOLTABLE_TYPE]], [[%s]])\n", ptype->name);
	out_dec ("m4_define([[M4_HOOK_EOLTABLE_SIZE]], [[%d]])", இலக்கம்_rules + 1);
	outn ("m4_define([[M4_HOOK_EOLTABLE_BODY]], [[m4_dnl");

	எனில் (gentables) {
		க்கு (i = 1; i <= இலக்கம்_rules; i++) {
			out_dec ("%d, ", rule_has_nl[i] ? 1 : 0);
			/* format nicely, 20 numbers per line. */
			எனில் ((i % 20) == 19)
				out ("\n    ");
		}
	}
	footprint += இலக்கம்_rules * ptype->width;
	outn ("]])");
	outn ("]])");
}


/** mkctbl - make full speed compressed transition table
 * This is an array of structs; each struct a pair of integers.
 * You should call mkssltbl() immediately after this.
 * Then, I think, mkecstbl(). Arrrg.
 * @return the newly allocated trans table
 */

நிலையான கட்டமைப்பு yytbl_data *mkctbl (வெறுமை)
{
	முழு i;
	கட்டமைப்பு yytbl_data *tbl = 0;
	flex_int32_t *tdata = 0, curr = 0;
	முழு     end_of_buffer_action = இலக்கம்_rules + 1;

	கட்டமைப்பு packtype_t *ptype = optimize_pack(tblend + 2 + 1);
	out_str ("m4_define([[M4_HOOK_MKCTBL_TYPE]], [[%s]])", ptype->name);

	tbl = calloc(1, அளவு (கட்டமைப்பு yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_TRANSITION);
	tbl->td_flags = YYTD_DATA32 | YYTD_STRUCT;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (tblend + 2 + 1);	/* number of structs */

	tbl->td_data = tdata =
		calloc(tbl->td_lolen * 2, அளவு (flex_int32_t));

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

	போது (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	போது (lastdfa + 1 >= current_max_dfas)
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
	க்கு (i = 0; i <= lastdfa; ++i) {
		முழு     anum = dfaacc[i].dfaacc_state;
		முழு     offset = base[i];

		chk[offset] = EOB_POSITION;
		chk[offset - 1] = ACTION_POSITION;
		nxt[offset - 1] = anum;	/* action number */
	}

	க்கு (i = 0; i <= tblend; ++i) {
		எனில் (chk[i] == EOB_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = base[lastdfa + 1] - i;
		}

		இல்லையெனில் எனில் (chk[i] == ACTION_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = nxt[i];
		}

		இல்லையெனில் எனில் (chk[i] > numecs || chk[i] == 0) {
			tdata[curr++] = 0;
			tdata[curr++] = 0;
		}
		இல்லையெனில் {		/* verify, transition */

			tdata[curr++] = chk[i];
			tdata[curr++] = base[nxt[i]] - (i - chk[i]);
		}
	}

	/* Here's the final, end-of-buffer state. */
	tdata[curr++] = chk[tblend + 1];
	tdata[curr++] = nxt[tblend + 1];

	tdata[curr++] = chk[tblend + 2];
	tdata[curr++] = nxt[tblend + 2];

	திரும்பு tbl;
}


/** Make start_state_list table.
 *  @return the newly allocated start_state_list table
 */
நிலையான கட்டமைப்பு yytbl_data *mkssltbl (வெறுமை)
{
	கட்டமைப்பு yytbl_data *tbl = 0;
	flex_int32_t *tdata = 0;
	flex_int32_t i;

	tbl = calloc(1, அளவு (கட்டமைப்பு yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_START_STATE_LIST);
	tbl->td_flags = YYTD_DATA32 | YYTD_PTRANS;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (lastsc * 2 + 1);

	tbl->td_data = tdata =
		calloc(tbl->td_lolen, அளவு (flex_int32_t));

	க்கு (i = 0; i <= lastsc * 2; ++i)
		tdata[i] = base[i];

	திரும்பு tbl;
}



/* genctbl - generates full speed compressed transition table */

நிலையான வெறுமை genctbl(வெறுமை)
{
	முழு i;
	முழு     end_of_buffer_action = இலக்கம்_rules + 1;

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

	போது (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	போது (lastdfa + 1 >= current_max_dfas)
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
	க்கு (i = 0; i <= lastdfa; ++i) {
		முழு     anum = dfaacc[i].dfaacc_state;
		முழு     offset = base[i];

		chk[offset] = EOB_POSITION;
		chk[offset - 1] = ACTION_POSITION;
		nxt[offset - 1] = anum;	/* action number */
	}

	க்கு (i = 0; i <= tblend; ++i) {
		எனில் (chk[i] == EOB_POSITION)
			transition_struct_out (0, base[lastdfa + 1] - i);

		இல்லையெனில் எனில் (chk[i] == ACTION_POSITION)
			transition_struct_out (0, nxt[i]);

		இல்லையெனில் எனில் (chk[i] > numecs || chk[i] == 0)
			transition_struct_out (0, 0);	/* unused slot */

		இல்லையெனில்		/* verify, transition */
			transition_struct_out (chk[i],
					       base[nxt[i]] - (i -
							       chk[i]));
	}


	/* Here's the final, end-of-buffer state. */
	transition_struct_out (chk[tblend + 1], nxt[tblend + 1]);
	transition_struct_out (chk[tblend + 2], nxt[tblend + 2]);

	outn ("]])");
	footprint += அளவு(கட்டமைப்பு yy_trans_info) * (tblend + 2 + 1);

	out_dec ("m4_define([[M4_HOOK_STARTTABLE_SIZE]], [[%d]])", lastsc * 2 + 1);
	எனில் (gentables) {
		outn ("m4_define([[M4_HOOK_STARTTABLE_BODY]], [[m4_dnl");
		க்கு (i = 0; i <= lastsc * 2; ++i)
			out_dec ("M4_HOOK_STATE_ENTRY_FORMAT(%d)", base[i]);

		dataend (வெற்று);
		outn("]])");
		footprint +=  அளவு(கட்டமைப்பு yy_trans_info *) * (lastsc * 2 + 1);
	}

	எனில் (ctrl.useecs)
		genecs ();
}


/* mkecstbl - Make equivalence-class tables.  */

நிலையான கட்டமைப்பு yytbl_data *mkecstbl (வெறுமை)
{
	முழு i;
	கட்டமைப்பு yytbl_data *tbl = 0;
	flex_int32_t *tdata = 0;

	tbl = calloc(1, அளவு (கட்டமைப்பு yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_EC);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) ctrl.csize;

	tbl->td_data = tdata =
		calloc(tbl->td_lolen, அளவு (flex_int32_t));

	க்கு (i = 1; i < ctrl.csize; ++i) {
		ecgroup[i] = ABS (ecgroup[i]);
		tdata[i] = ecgroup[i];
	}

	திரும்பு tbl;
}

/* Generate equivalence-class tables. */

நிலையான வெறுமை genecs(வெறுமை)
{
	முழு ch, row;
	முழு     numrows;

	out_dec ("m4_define([[M4_HOOK_ECSTABLE_SIZE]], [[%d]])", ctrl.csize);
	outn ("m4_define([[M4_HOOK_ECSTABLE_BODY]], [[m4_dnl");

	க்கு (ch = 1; ch < ctrl.csize; ++ch) {
		ecgroup[ch] = ABS (ecgroup[ch]);
		mkdata (ecgroup[ch]);
	}

	dataend (வெற்று);
	outn("]])");
	footprint += அளவு(YY_CHAR) * ctrl.csize;

	எனில் (env.trace) {
		fputs (_("\n\nEquivalence Classes:\n\n"), stderr);

		/* Print in 8 columns */
		numrows = ctrl.csize / 8;

		க்கு (row = 0; row < numrows; ++row) {
			க்கு (ch = row; ch < ctrl.csize; ch += numrows) {
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

நிலையான கட்டமைப்பு yytbl_data *mkftbl(வெறுமை)
{
	முழு i;
	முழு     end_of_buffer_action = இலக்கம்_rules + 1;
	கட்டமைப்பு yytbl_data *tbl;
	flex_int32_t *tdata = 0;

	tbl = calloc(1, அளவு (கட்டமைப்பு yytbl_data));
	yytbl_data_init (tbl, YYTD_ID_ACCEPT);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;	/* it's a one-dimensional array */
	tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);

	tbl->td_data = tdata =
		calloc(tbl->td_lolen, அளவு (flex_int32_t));

	dfaacc[end_of_buffer_state].dfaacc_state = end_of_buffer_action;

	க்கு (i = 1; i <= lastdfa; ++i) {
		முழு anum = dfaacc[i].dfaacc_state;

		tdata[i] = anum;

		எனில் (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	திரும்பு tbl;
}


/* genftbl - generate full transition table */

நிலையான வெறுமை genftbl(வெறுமை)
{
	முழு i;
	முழு     end_of_buffer_action = இலக்கம்_rules + 1;
	கட்டமைப்பு packtype_t *ptype = optimize_pack(இலக்கம்_rules + 1);

	dfaacc[end_of_buffer_state].dfaacc_state = end_of_buffer_action;

	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	out_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", lastdfa + 1);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	க்கு (i = 1; i <= lastdfa; ++i) {
		முழு anum = dfaacc[i].dfaacc_state;

		mkdata (anum);

		எனில் (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	dataend (வெற்று);
	outn("]])");
	footprint += (lastdfa + 1) * ptype->width;

	எனில் (ctrl.useecs)
		genecs ();

	/* Don't have to dump the actual full table entries - they were
	 * created on-the-fly.
	 */
}

/* gentabs - generate data statements for the transition tables */

நிலையான வெறுமை gentabs(வெறுமை)
{
	முழு     sz, i, j, k, *accset, nacc, *acc_array, total_states;
	முழு     end_of_buffer_action = இலக்கம்_rules + 1;
	கட்டமைப்பு yytbl_data *yyacc_tbl = 0, *yymeta_tbl = 0, *yybase_tbl = 0,
	    *yydef_tbl = 0, *yynxt_tbl = 0, *yychk_tbl = 0, *yyacclist_tbl=0;
	flex_int32_t *yyacc_data = 0, *yybase_data = 0, *yydef_data = 0,
	    *yynxt_data = 0, *yychk_data = 0, *yyacclist_data=0;
	flex_int32_t yybase_curr = 0, yyacclist_curr=0,yyacc_curr=0;
	கட்டமைப்பு packtype_t *ptype;

	acc_array = allocate_integer_array (current_max_dfas);
	nummt = 0;

	/* The compressed table format jams by entering the "jam state",
	 * losing information about the previous state in the process.
	 * In order to recover the previous state, we effectively need
	 * to keep backing-up information.
	 */
	++இலக்கம்_backing_up;

	எனில் (reject) {
		/* Write out accepting list and pointer list.

		 * First we generate the "yy_acclist" array.  In the process,
		 * we compute the indices that will go into the "yy_accept"
		 * array, and save the indices in the dfaacc array.
		 */
		முழு     EOB_accepting_list[2];

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

		yyacclist_tbl = calloc(1,அளவு(கட்டமைப்பு yytbl_data));
		yytbl_data_init (yyacclist_tbl, YYTD_ID_ACCLIST);
		yyacclist_tbl->td_lolen  = (flex_uint32_t) (MAX(numas,1) + 1);
		yyacclist_tbl->td_data = yyacclist_data =
		    calloc(yyacclist_tbl->td_lolen, அளவு (flex_int32_t));
		yyacclist_curr = 1;

		j = 1;		/* index into "yy_acclist" array */

		க்கு (i = 1; i <= lastdfa; ++i) {
			acc_array[i] = j;

			எனில் (accsiz[i] != 0) {
				accset = dfaacc[i].dfaacc_set;
				nacc = accsiz[i];

				எனில் (env.trace)
					fprintf (stderr,
						 _("state # %d accepts: "),
						 i);

				க்கு (k = 1; k <= nacc; ++k) {
					முழு     accnum = accset[k];

					++j;

					எனில் (variable_trailing_context_rules
					    && !(accnum &
						 YY_TRAILING_HEAD_MASK)
					    && accnum > 0
					    && accnum <= இலக்கம்_rules
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

					எனில் (env.trace) {
						fprintf (stderr, "[%d]",
							 accset[k]);

						எனில் (k < nacc)
							fputs (", ",
							       stderr);
						இல்லையெனில்
							putc ('\n',
							      stderr);
					}
				}
			}
		}

		/* add accepting number for the "jam" state */
		acc_array[i] = j;

		dataend (வெற்று);
		outn("]])");
		footprint += sz * ptype->width;
		எனில் (tablesext) {
			yytbl_data_compress (yyacclist_tbl);
			எனில் (yytbl_data_fwrite (&tableswr, yyacclist_tbl) < 0)
				flexerror (_("Could not write yyacclist_tbl"));
			yytbl_data_destroy (yyacclist_tbl);
			yyacclist_tbl = வெற்று;
		}
	}

	இல்லையெனில் {
		dfaacc[end_of_buffer_state].dfaacc_state =
		    end_of_buffer_action;

		க்கு (i = 1; i <= lastdfa; ++i)
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

	எனில் (reject)
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

	yyacc_tbl = calloc(1, அளவு (கட்டமைப்பு yytbl_data));
	yytbl_data_init (yyacc_tbl, YYTD_ID_ACCEPT);
	yyacc_tbl->td_lolen = (flex_uint32_t) sz;
	yyacc_tbl->td_data = yyacc_data =
	    calloc(yyacc_tbl->td_lolen, அளவு (flex_int32_t));
	yyacc_curr=1;

	க்கு (i = 1; i <= lastdfa; ++i) {
		mkdata (acc_array[i]);
		yyacc_data[yyacc_curr++] = acc_array[i];

		எனில் (!reject && env.trace && acc_array[i])
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, acc_array[i]);
	}

	/* Add entry for "jam" state. */
	mkdata (acc_array[i]);
	yyacc_data[yyacc_curr++] = acc_array[i];

	எனில் (reject) {
		/* Add "cap" for the list. */
		mkdata (acc_array[i]);
		yyacc_data[yyacc_curr++] = acc_array[i];
	}

	dataend (வெற்று);
	outn ("]])");
	footprint += sz * ptype->width;

	எனில் (tablesext) {
		yytbl_data_compress (yyacc_tbl);
		எனில் (yytbl_data_fwrite (&tableswr, yyacc_tbl) < 0)
			flexerror (_("Could not write yyacc_tbl"));
	}
	yytbl_data_destroy (yyacc_tbl);
	yyacc_tbl = வெற்று;
	/* End generating yy_accept */

	எனில் (ctrl.useecs) {

		genecs ();
		எனில் (tablesext) {
			கட்டமைப்பு yytbl_data *tbl;

			tbl = mkecstbl ();
			yytbl_data_compress (tbl);
			எனில் (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ecstbl"));
			yytbl_data_destroy (tbl);
			tbl = 0;
		}
	}

	எனில் (ctrl.usemecs) {
		/* Begin generating yy_meta */
		/* Write out meta-equivalence classes (used to index
		 * templates with).
		 */
		flex_int32_t *yymecs_data = 0;
		yymeta_tbl = calloc(1, அளவு (கட்டமைப்பு yytbl_data));
		yytbl_data_init (yymeta_tbl, YYTD_ID_META);
		yymeta_tbl->td_lolen = (flex_uint32_t) (numecs + 1);
		yymeta_tbl->td_data = yymecs_data =
		    calloc(yymeta_tbl->td_lolen,
			   அளவு (flex_int32_t));

		எனில் (env.trace)
			fputs (_("\n\nMeta-Equivalence Classes:\n"),
			       stderr);
		out_dec ("m4_define([[M4_HOOK_MECSTABLE_SIZE]], [[%d]])", numecs+1);
		outn ("m4_define([[M4_HOOK_MECSTABLE_BODY]], [[m4_dnl");
 	
		க்கு (i = 1; i <= numecs; ++i) {
			எனில் (env.trace)
				fprintf (stderr, "%d = %d\n",
					 i, ABS (tecbck[i]));

			mkdata (ABS (tecbck[i]));
			yymecs_data[i] = ABS (tecbck[i]);
		}

		dataend (வெற்று);
		outn ("]])");
		footprint += அளவு(YY_CHAR) * (numecs + 1);
		எனில் (tablesext) {
			yytbl_data_compress (yymeta_tbl);
			எனில் (yytbl_data_fwrite (&tableswr, yymeta_tbl) < 0)
				flexerror (_("Could not write yymeta_tbl"));
		}
		yytbl_data_destroy (yymeta_tbl);
		yymeta_tbl = வெற்று;
		/* End generating yy_meta */
	}

	total_states = lastdfa + numtemps;

	/* Begin generating yy_base */
	sz = total_states + 1;
	ptype = optimize_pack(sz);
	out_str ("m4_define([[M4_HOOK_BASE_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_BASE_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_BASE_BODY]], [[m4_dnl");

	yybase_tbl = calloc (1, அளவு (கட்டமைப்பு yytbl_data));
	yytbl_data_init (yybase_tbl, YYTD_ID_BASE);
	yybase_tbl->td_lolen = (flex_uint32_t) (total_states + 1);
	yybase_tbl->td_data = yybase_data =
	    calloc(yybase_tbl->td_lolen,
		   அளவு (flex_int32_t));
	yybase_curr = 1;

	க்கு (i = 1; i <= lastdfa; ++i) {
		முழு d = def[i];

		எனில் (base[i] == JAMSTATE)
			base[i] = jambase;

		எனில் (d == JAMSTATE)
			def[i] = jamstate;

		இல்லையெனில் எனில் (d < 0) {
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

	க்கு (++i /* skip jam state */ ; i <= total_states; ++i) {
		mkdata (base[i]);
		yybase_data[yybase_curr++] = base[i];
		def[i] = jamstate;
	}

	dataend (வெற்று);
	outn ("]])");
	footprint += sz * ptype->width;

	எனில் (tablesext) {
		yytbl_data_compress (yybase_tbl);
		எனில் (yytbl_data_fwrite (&tableswr, yybase_tbl) < 0)
			flexerror (_("Could not write yybase_tbl"));
	}
	yytbl_data_destroy (yybase_tbl);
	yybase_tbl = வெற்று;
	/* End generating yy_base */


	/* Begin generating yy_def */
	ptype = optimize_pack(total_states + 1);
	out_str ("m4_define([[M4_HOOK_DEF_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_DEF_SIZE]], [[%d]])", total_states + 1);
	outn ("m4_define([[M4_HOOK_DEF_BODY]], [[m4_dnl");

	yydef_tbl = calloc(1, அளவு (கட்டமைப்பு yytbl_data));
	yytbl_data_init (yydef_tbl, YYTD_ID_DEF);
	yydef_tbl->td_lolen = (flex_uint32_t)(total_states + 1);
	yydef_tbl->td_data = yydef_data =
	    calloc(yydef_tbl->td_lolen, அளவு (flex_int32_t));

	க்கு (i = 1; i <= total_states; ++i) {
		mkdata (def[i]);
		yydef_data[i] = def[i];
	}

	dataend (வெற்று);
	outn ("]])");
	footprint += (total_states + 1) * ptype->width;

	எனில் (tablesext) {
		yytbl_data_compress (yydef_tbl);
		எனில் (yytbl_data_fwrite (&tableswr, yydef_tbl) < 0)
			flexerror (_("Could not write yydef_tbl"));
	}
	yytbl_data_destroy (yydef_tbl);
	yydef_tbl = வெற்று;
	/* End generating yy_def */


	ptype = optimize_pack(tblend + 1);
	/* Note: Used when !ctrl.fulltbl && !ctrl.fullspd).
	 * (Alternately defined when ctrl.fullspd)
	 */
	out_str ("m4_define([[M4_HOOK_YYNXT_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_YYNXT_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_YYNXT_BODY]], [[m4_dnl");

	yynxt_tbl = calloc (1, அளவு (கட்டமைப்பு yytbl_data));
	yytbl_data_init (yynxt_tbl, YYTD_ID_NXT);
	yynxt_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yynxt_tbl->td_data = yynxt_data =
	    calloc (yynxt_tbl->td_lolen, அளவு (flex_int32_t));

	க்கு (i = 1; i <= tblend; ++i) {
		/* Note, the order of the following test is important.
		 * If chk[i] is 0, then nxt[i] is undefined.
		 */
		எனில் (chk[i] == 0 || nxt[i] == 0)
			nxt[i] = jamstate;	/* new state is the JAM state */

		mkdata (nxt[i]);
		yynxt_data[i] = nxt[i];
	}

	dataend (வெற்று);
	outn("]])");
	footprint += ptype->width * (tblend + 1);

	எனில் (tablesext) {
		yytbl_data_compress (yynxt_tbl);
		எனில் (yytbl_data_fwrite (&tableswr, yynxt_tbl) < 0)
			flexerror (_("Could not write yynxt_tbl"));
	}
	yytbl_data_destroy (yynxt_tbl);
	yynxt_tbl = வெற்று;
	/* End generating yy_nxt */

	/* Begin generating yy_chk */
	ptype = optimize_pack(tblend + 1);
	out_str ("m4_define([[M4_HOOK_CHK_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_CHK_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_CHK_BODY]], [[m4_dnl");
	
	yychk_tbl = calloc (1, அளவு (கட்டமைப்பு yytbl_data));
	yytbl_data_init (yychk_tbl, YYTD_ID_CHK);
	yychk_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yychk_tbl->td_data = yychk_data =
	    calloc(yychk_tbl->td_lolen, அளவு (flex_int32_t));

	க்கு (i = 1; i <= tblend; ++i) {
		எனில் (chk[i] == 0)
			++nummt;

		mkdata (chk[i]);
		yychk_data[i] = chk[i];
	}

	dataend (வெற்று);
	outn ("]])");
	footprint += ptype->width * (tblend + 1);

	எனில் (tablesext) {
		yytbl_data_compress (yychk_tbl);
		எனில் (yytbl_data_fwrite (&tableswr, yychk_tbl) < 0)
			flexerror (_("Could not write yychk_tbl"));
	}
	yytbl_data_destroy (yychk_tbl);
	yychk_tbl = வெற்று;
	/* End generating yy_chk */

	விடுவி(acc_array);
}


வெறுமை visible_define (மாறிலி எழுத்து *symname)
{
	out_m4_define(symname, வெற்று);
	comment(symname);
	outc ('\n');
}

வெறுமை visible_define_str (மாறிலி எழுத்து *symname, மாறிலி எழுத்து *val)
{
	எழுத்து buf[128];
	out_m4_define(symname, val);
	snprintf(buf, அளவு(buf), "%s = %s", symname, val);
	comment(buf);
	outc ('\n');
}

வெறுமை visible_define_int (மாறிலி எழுத்து *symname, மாறிலி முழு val)
{
	எழுத்து nbuf[24], buf[128];
	snprintf(nbuf, அளவு(nbuf), "%d", val);
	out_m4_define(symname, nbuf);
	snprintf(buf, அளவு(buf), "%s = %d", symname, val);
	comment(buf);
	outc ('\n');
}

/* make_tables - generate transition tables
 */

வெறுமை make_tables (வெறுமை)
{
	எழுத்து buf[128];
	முழு i;
	கட்டமைப்பு yytbl_data *yynultrans_tbl = வெற்று;

	/* This is where we REALLY begin generating the tables. */

	எனில் (ctrl.fullspd) {
		genctbl ();
		எனில் (tablesext) {
			கட்டமைப்பு yytbl_data *tbl;

			tbl = mkctbl ();
			yytbl_data_compress (tbl);
			எனில் (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_data_destroy (tbl);

			tbl = mkssltbl ();
			yytbl_data_compress (tbl);
			எனில் (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ssltbl"));
			yytbl_data_destroy (tbl);
			tbl = 0;

			எனில் (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_data_compress (tbl);
				எனில் (yytbl_data_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_data_destroy (tbl);
				tbl = 0;
			}
		}
	}
	இல்லையெனில் எனில் (ctrl.fulltbl) {
		genftbl ();
		எனில் (tablesext) {
			கட்டமைப்பு yytbl_data *tbl;

			/* Alternately defined if !ctrl.ffullspd && !ctrl.fulltbl */
			கட்டமைப்பு packtype_t *ptype;
			tbl = mkftbl ();
			yytbl_data_compress (tbl);
			ptype = optimize_pack(tbl->td_lolen);
			out_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
			எனில் (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_data_destroy (tbl);
			tbl = 0;

			எனில் (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_data_compress (tbl);
				எனில் (yytbl_data_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_data_destroy (tbl);
				tbl = 0;
			}
		}
	}
	இல்லையெனில் {
		gentabs ();
	}

	snprintf(buf, அளவு(buf), "footprint: %ld bytes\n", footprint);
	comment(buf);
	snprintf(buf, அளவு(buf), "tblend: %d\n", tblend);
	comment(buf);
	snprintf(buf, அளவு(buf), "numecs: %d\n", numecs);
	comment(buf);
	snprintf(buf, அளவு(buf), "num_rules: %d\n", இலக்கம்_rules);
	comment(buf);
	snprintf(buf, அளவு(buf), "lastdfa: %d\n", lastdfa);
	comment(buf);
	outc ('\n');
	
	// Only at this point do we know if the automaton has backups.
	// Some m4 conditionals require this information.

	comment("m4 controls begin\n");

	எனில் (இலக்கம்_backing_up > 0)
		visible_define ( "M4_MODE_HAS_BACKING_UP");

	// These are used for NUL transitions
	எனில் ((இலக்கம்_backing_up > 0 && !reject) && (!nultrans || ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NEED_YY_CP");
	எனில் ((இலக்கம்_backing_up > 0 && !reject) && (ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NULTRANS_WRAP");

	comment("m4 controls end\n");
	out ("\n");

	எனில் (ctrl.do_yylineno) {

		geneoltbl ();

		எனில் (tablesext) {
			கட்டமைப்பு yytbl_data *tbl;

			tbl = mkeoltbl ();
			yytbl_data_compress (tbl);
			எனில் (yytbl_data_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write eoltbl"));
			yytbl_data_destroy (tbl);
			tbl = 0;
		}
	}

	எனில் (nultrans) {
		flex_int32_t *yynultrans_data = 0;

		/* Begin generating yy_NUL_trans */
		out_str ("m4_define([[M4_HOOK_NULTRANS_TYPE]], [[%s]])", (ctrl.fullspd) ? "struct yy_trans_info*" : "M4_HOOK_INT32");
		out_dec ("m4_define([[M4_HOOK_NULTRANS_SIZE]], [[%d]])", lastdfa + 1);
		outn ("m4_define([[M4_HOOK_NULTRANS_BODY]], [[m4_dnl");

		yynultrans_tbl = calloc(1, அளவு (கட்டமைப்பு yytbl_data));
		yytbl_data_init (yynultrans_tbl, YYTD_ID_NUL_TRANS);
		// Performance kludge for C. Gives a small improvement
		// in table loading time.
		எனில் (ctrl.fullspd && ctrl.have_state_entry_format)
			yynultrans_tbl->td_flags |= YYTD_PTRANS;
		yynultrans_tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);
		yynultrans_tbl->td_data = yynultrans_data =
		    calloc(yynultrans_tbl->td_lolen,
			   அளவு (flex_int32_t));

		க்கு (i = 1; i <= lastdfa; ++i) {
			எனில் ((yynultrans_tbl->td_flags & YYTD_PTRANS) != 0) {
				// Only works in very C-like languages  
				out_dec ("    &yy_transition[%d],\n",
					 base[i]);
				yynultrans_data[i] = base[i];
			}
			இல்லையெனில் {
				// This will work anywhere
				mkdata (nultrans[i]);
				yynultrans_data[i] = nultrans[i];
			}
		}

		dataend (வெற்று);
		outn("]])");
		footprint += (lastdfa + 1) * (ctrl.fullspd ? அளவு(கட்டமைப்பு yy_trans_info *) : அளவு(int32_t));
		எனில் (tablesext) {
			yytbl_data_compress (yynultrans_tbl);
			எனில் (yytbl_data_fwrite (&tableswr, yynultrans_tbl) <
			    0)
				flexerror (_
					   ("Could not write yynultrans_tbl"));
		}

		எனில் (yynultrans_tbl != வெற்று) {
			yytbl_data_destroy (yynultrans_tbl);
			yynultrans_tbl = வெற்று;
		}

		/* End generating yy_NUL_trans */
	}

	எனில் (ctrl.ddebug) {		/* Spit out table mapping rules to line numbers. */
		/* Policy choice: we don't include this space
		 * in the table metering.
		 */
		கட்டமைப்பு packtype_t *ptype = optimize_pack(இலக்கம்_rules);
		out_str ("m4_define([[M4_HOOK_DEBUGTABLE_TYPE]], [[%s]])", ptype->name);
		out_dec ("m4_define([[M4_HOOK_DEBUGTABLE_SIZE]], [[%d]])", இலக்கம்_rules);
		outn ("m4_define([[M4_HOOK_DEBUGTABLE_BODY]], [[m4_dnl");

		க்கு (i = 1; i < இலக்கம்_rules; ++i)
			mkdata (rule_linenum[i]);
		dataend (வெற்று);
		outn("]])");
	}
}
