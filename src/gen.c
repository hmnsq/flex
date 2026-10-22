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

#समावेश "flexdef.h"
#समावेश "tables.h"

/* These typedefs are only used for computing footprint sizes,
 * You need to make sure they match reality in the skeleton file to
 * get accurate numbers, but they don't otherwise matter.
 */
प्रकार अक्षर YY_CHAR;
काष्ठा yy_trans_info {int32_t yy_verify; int32_t yy_nxt;};

/* declare functions that have forward references */

अटल व्योम genecs(व्योम);

काष्ठा packtype_t *optimize_pack(माप_प्रकार sz)
{
	/* FIXME: There's a 32-bit assumption lurking here */
	अटल काष्ठा packtype_t out;
	अगर (sz == 0) {
		out.name  = ctrl.long_align ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		out.width = ctrl.long_align ? 32 : 16;
	} अन्यथा {
		out.name = (ctrl.long_align || sz >= INT16_MAX) ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		out.width = (ctrl.long_align || sz >= INT16_MAX) ? 32 : 16;
	}
	वापस &out;
}

/* Almost everything is done in terms of arrays starting at 1, so provide
 * a null entry for the zero element of all C arrays.  (The exception
 * to this is that the fast table representation generally uses the
 * 0 elements of its arrays, too.)
 */

/** Make the table for possible eol matches.
 *  @return the newly allocated rule_can_match_eol table
 */
अटल काष्ठा yytbl_तथ्य *mkeoltbl (व्योम)
{
	पूर्णांक     i;
	flex_int8_t *tdata = 0;
	काष्ठा yytbl_तथ्य *tbl;

	tbl = सुस्मृति(1, माप (काष्ठा yytbl_तथ्य));
	yytbl_तथ्य_init (tbl, YYTD_ID_RULE_CAN_MATCH_EOL);
	tbl->td_flags = YYTD_DATA8;
	tbl->td_lolen = (flex_uint32_t) (अंक_rules + 1);
	tbl->td_तथ्य = tdata =
		सुस्मृति(tbl->td_lolen, माप (flex_int8_t));

	क्रम (i = 1; i <= अंक_rules; i++)
		tdata[i] = rule_has_nl[i] ? 1 : 0;

	वापस tbl;
}

/* Generate the table for possible eol matches. */
अटल व्योम geneoltbl (व्योम)
{
	पूर्णांक     i;
	काष्ठा packtype_t *ptype = optimize_pack(अंक_rules);

	outn ("m4_ifdef( [[M4_MODE_YYLINENO]],[[");
	out_str ("m4_define([[M4_HOOK_EOLTABLE_TYPE]], [[%s]])\n", ptype->name);
	out_dec ("m4_define([[M4_HOOK_EOLTABLE_SIZE]], [[%d]])", अंक_rules + 1);
	outn ("m4_define([[M4_HOOK_EOLTABLE_BODY]], [[m4_dnl");

	अगर (gentables) {
		क्रम (i = 1; i <= अंक_rules; i++) {
			out_dec ("%d, ", rule_has_nl[i] ? 1 : 0);
			/* format nicely, 20 numbers per line. */
			अगर ((i % 20) == 19)
				out ("\n    ");
		}
	}
	footprint += अंक_rules * ptype->width;
	outn ("]])");
	outn ("]])");
}


/** mkctbl - make full speed compressed transition table
 * This is an array of structs; each struct a pair of integers.
 * You should call mkssltbl() immediately after this.
 * Then, I think, mkecstbl(). Arrrg.
 * @return the newly allocated trans table
 */

अटल काष्ठा yytbl_तथ्य *mkctbl (व्योम)
{
	पूर्णांक i;
	काष्ठा yytbl_तथ्य *tbl = 0;
	flex_int32_t *tdata = 0, curr = 0;
	पूर्णांक     end_of_बफर_action = अंक_rules + 1;

	काष्ठा packtype_t *ptype = optimize_pack(tblend + 2 + 1);
	out_str ("m4_define([[M4_HOOK_MKCTBL_TYPE]], [[%s]])", ptype->name);

	tbl = सुस्मृति(1, माप (काष्ठा yytbl_तथ्य));
	yytbl_तथ्य_init (tbl, YYTD_ID_TRANSITION);
	tbl->td_flags = YYTD_DATA32 | YYTD_STRUCT;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (tblend + 2 + 1);	/* number of structs */

	tbl->td_तथ्य = tdata =
		सुस्मृति(tbl->td_lolen * 2, माप (flex_int32_t));

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

	जबतक (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	जबतक (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	base[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = end_of_बफर_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	क्रम (i = 0; i <= lastdfa; ++i) {
		पूर्णांक     anum = dfaacc[i].dfaacc_state;
		पूर्णांक     offset = base[i];

		chk[offset] = EOB_POSITION;
		chk[offset - 1] = ACTION_POSITION;
		nxt[offset - 1] = anum;	/* action number */
	}

	क्रम (i = 0; i <= tblend; ++i) {
		अगर (chk[i] == EOB_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = base[lastdfa + 1] - i;
		}

		अन्यथा अगर (chk[i] == ACTION_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = nxt[i];
		}

		अन्यथा अगर (chk[i] > numecs || chk[i] == 0) {
			tdata[curr++] = 0;
			tdata[curr++] = 0;
		}
		अन्यथा {		/* verify, transition */

			tdata[curr++] = chk[i];
			tdata[curr++] = base[nxt[i]] - (i - chk[i]);
		}
	}

	/* Here's the final, end-of-buffer state. */
	tdata[curr++] = chk[tblend + 1];
	tdata[curr++] = nxt[tblend + 1];

	tdata[curr++] = chk[tblend + 2];
	tdata[curr++] = nxt[tblend + 2];

	वापस tbl;
}


/** Make start_state_list table.
 *  @return the newly allocated start_state_list table
 */
अटल काष्ठा yytbl_तथ्य *mkssltbl (व्योम)
{
	काष्ठा yytbl_तथ्य *tbl = 0;
	flex_int32_t *tdata = 0;
	flex_int32_t i;

	tbl = सुस्मृति(1, माप (काष्ठा yytbl_तथ्य));
	yytbl_तथ्य_init (tbl, YYTD_ID_START_STATE_LIST);
	tbl->td_flags = YYTD_DATA32 | YYTD_PTRANS;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (lastsc * 2 + 1);

	tbl->td_तथ्य = tdata =
		सुस्मृति(tbl->td_lolen, माप (flex_int32_t));

	क्रम (i = 0; i <= lastsc * 2; ++i)
		tdata[i] = base[i];

	वापस tbl;
}



/* genctbl - generates full speed compressed transition table */

अटल व्योम genctbl(व्योम)
{
	पूर्णांक i;
	पूर्णांक     end_of_बफर_action = अंक_rules + 1;

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

	जबतक (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	जबतक (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	base[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = end_of_बफर_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	क्रम (i = 0; i <= lastdfa; ++i) {
		पूर्णांक     anum = dfaacc[i].dfaacc_state;
		पूर्णांक     offset = base[i];

		chk[offset] = EOB_POSITION;
		chk[offset - 1] = ACTION_POSITION;
		nxt[offset - 1] = anum;	/* action number */
	}

	क्रम (i = 0; i <= tblend; ++i) {
		अगर (chk[i] == EOB_POSITION)
			transition_struct_out (0, base[lastdfa + 1] - i);

		अन्यथा अगर (chk[i] == ACTION_POSITION)
			transition_struct_out (0, nxt[i]);

		अन्यथा अगर (chk[i] > numecs || chk[i] == 0)
			transition_struct_out (0, 0);	/* unused slot */

		अन्यथा		/* verify, transition */
			transition_struct_out (chk[i],
					       base[nxt[i]] - (i -
							       chk[i]));
	}


	/* Here's the final, end-of-buffer state. */
	transition_struct_out (chk[tblend + 1], nxt[tblend + 1]);
	transition_struct_out (chk[tblend + 2], nxt[tblend + 2]);

	outn ("]])");
	footprint += माप(काष्ठा yy_trans_info) * (tblend + 2 + 1);

	out_dec ("m4_define([[M4_HOOK_STARTTABLE_SIZE]], [[%d]])", lastsc * 2 + 1);
	अगर (gentables) {
		outn ("m4_define([[M4_HOOK_STARTTABLE_BODY]], [[m4_dnl");
		क्रम (i = 0; i <= lastsc * 2; ++i)
			out_dec ("M4_HOOK_STATE_ENTRY_FORMAT(%d)", base[i]);

		dataend (शून्य);
		outn("]])");
		footprint +=  माप(काष्ठा yy_trans_info *) * (lastsc * 2 + 1);
	}

	अगर (ctrl.useecs)
		genecs ();
}


/* mkecstbl - Make equivalence-class tables.  */

अटल काष्ठा yytbl_तथ्य *mkecstbl (व्योम)
{
	पूर्णांक i;
	काष्ठा yytbl_तथ्य *tbl = 0;
	flex_int32_t *tdata = 0;

	tbl = सुस्मृति(1, माप (काष्ठा yytbl_तथ्य));
	yytbl_तथ्य_init (tbl, YYTD_ID_EC);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) ctrl.csize;

	tbl->td_तथ्य = tdata =
		सुस्मृति(tbl->td_lolen, माप (flex_int32_t));

	क्रम (i = 1; i < ctrl.csize; ++i) {
		ecgroup[i] = ABS (ecgroup[i]);
		tdata[i] = ecgroup[i];
	}

	वापस tbl;
}

/* Generate equivalence-class tables. */

अटल व्योम genecs(व्योम)
{
	पूर्णांक ch, row;
	पूर्णांक     numrows;

	out_dec ("m4_define([[M4_HOOK_ECSTABLE_SIZE]], [[%d]])", ctrl.csize);
	outn ("m4_define([[M4_HOOK_ECSTABLE_BODY]], [[m4_dnl");

	क्रम (ch = 1; ch < ctrl.csize; ++ch) {
		ecgroup[ch] = ABS (ecgroup[ch]);
		mkdata (ecgroup[ch]);
	}

	dataend (शून्य);
	outn("]])");
	footprint += माप(YY_CHAR) * ctrl.csize;

	अगर (env.trace) {
		ख_माला_दो (_("\n\nEquivalence Classes:\n\n"), मानक_त्रुटि);

		/* Print in 8 columns */
		numrows = ctrl.csize / 8;

		क्रम (row = 0; row < numrows; ++row) {
			क्रम (ch = row; ch < ctrl.csize; ch += numrows) {
				ख_लिखो (मानक_त्रुटि, "%4s = %-2d",
					 readable_form (ch), ecgroup[ch]);

				अ_दो (' ', मानक_त्रुटि);
			}

			अ_दो ('\n', मानक_त्रुटि);
		}
	}
}

/* mkftbl - make the full table and return the struct .
 * you should call mkecstbl() after this.
 */

अटल काष्ठा yytbl_तथ्य *mkftbl(व्योम)
{
	पूर्णांक i;
	पूर्णांक     end_of_बफर_action = अंक_rules + 1;
	काष्ठा yytbl_तथ्य *tbl;
	flex_int32_t *tdata = 0;

	tbl = सुस्मृति(1, माप (काष्ठा yytbl_तथ्य));
	yytbl_तथ्य_init (tbl, YYTD_ID_ACCEPT);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;	/* it's a one-dimensional array */
	tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);

	tbl->td_तथ्य = tdata =
		सुस्मृति(tbl->td_lolen, माप (flex_int32_t));

	dfaacc[end_of_बफर_state].dfaacc_state = end_of_बफर_action;

	क्रम (i = 1; i <= lastdfa; ++i) {
		पूर्णांक anum = dfaacc[i].dfaacc_state;

		tdata[i] = anum;

		अगर (env.trace && anum)
			ख_लिखो (मानक_त्रुटि, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	वापस tbl;
}


/* genftbl - generate full transition table */

अटल व्योम genftbl(व्योम)
{
	पूर्णांक i;
	पूर्णांक     end_of_बफर_action = अंक_rules + 1;
	काष्ठा packtype_t *ptype = optimize_pack(अंक_rules + 1);

	dfaacc[end_of_बफर_state].dfaacc_state = end_of_बफर_action;

	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	out_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", lastdfa + 1);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	क्रम (i = 1; i <= lastdfa; ++i) {
		पूर्णांक anum = dfaacc[i].dfaacc_state;

		mkdata (anum);

		अगर (env.trace && anum)
			ख_लिखो (मानक_त्रुटि, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	dataend (शून्य);
	outn("]])");
	footprint += (lastdfa + 1) * ptype->width;

	अगर (ctrl.useecs)
		genecs ();

	/* Don't have to dump the actual full table entries - they were
	 * created on-the-fly.
	 */
}

/* gentabs - generate data statements for the transition tables */

अटल व्योम gentabs(व्योम)
{
	पूर्णांक     sz, i, j, k, *accset, nacc, *acc_array, योग_states;
	पूर्णांक     end_of_बफर_action = अंक_rules + 1;
	काष्ठा yytbl_तथ्य *yyacc_tbl = 0, *yymeta_tbl = 0, *yybase_tbl = 0,
	    *yydef_tbl = 0, *yynxt_tbl = 0, *yychk_tbl = 0, *yyacclist_tbl=0;
	flex_int32_t *yyacc_तथ्य = 0, *yybase_तथ्य = 0, *yydef_तथ्य = 0,
	    *yynxt_तथ्य = 0, *yychk_तथ्य = 0, *yyacclist_तथ्य=0;
	flex_int32_t yybase_curr = 0, yyacclist_curr=0,yyacc_curr=0;
	काष्ठा packtype_t *ptype;

	acc_array = allocate_integer_array (current_max_dfas);
	nummt = 0;

	/* The compressed table format jams by entering the "jam state",
	 * losing information about the previous state in the process.
	 * In order to recover the previous state, we effectively need
	 * to keep backing-up information.
	 */
	++अंक_backing_up;

	अगर (reject) {
		/* Write out accepting list and pointer list.

		 * First we generate the "yy_acclist" array.  In the process,
		 * we compute the indices that will go into the "yy_accept"
		 * array, and save the indices in the dfaacc array.
		 */
		पूर्णांक     EOB_accepting_list[2];

		/* Set up accepting structures for the End Of Buffer state. */
		EOB_accepting_list[0] = 0;
		EOB_accepting_list[1] = end_of_बफर_action;
		accsiz[end_of_बफर_state] = 1;
		dfaacc[end_of_बफर_state].dfaacc_set =
		    EOB_accepting_list;

		sz = MAX (numas, 1) + 1;
		ptype = optimize_pack(sz);
		out_str ("m4_define([[M4_HOOK_ACCLIST_TYPE]], [[%s]])", ptype->name);
		out_dec ("m4_define([[M4_HOOK_ACCLIST_SIZE]], [[%d]])", sz);
		outn ("m4_define([[M4_HOOK_ACCLIST_BODY]], [[m4_dnl");

		yyacclist_tbl = सुस्मृति(1,माप(काष्ठा yytbl_तथ्य));
		yytbl_तथ्य_init (yyacclist_tbl, YYTD_ID_ACCLIST);
		yyacclist_tbl->td_lolen  = (flex_uint32_t) (MAX(numas,1) + 1);
		yyacclist_tbl->td_तथ्य = yyacclist_तथ्य =
		    सुस्मृति(yyacclist_tbl->td_lolen, माप (flex_int32_t));
		yyacclist_curr = 1;

		j = 1;		/* index into "yy_acclist" array */

		क्रम (i = 1; i <= lastdfa; ++i) {
			acc_array[i] = j;

			अगर (accsiz[i] != 0) {
				accset = dfaacc[i].dfaacc_set;
				nacc = accsiz[i];

				अगर (env.trace)
					ख_लिखो (मानक_त्रुटि,
						 _("state # %d accepts: "),
						 i);

				क्रम (k = 1; k <= nacc; ++k) {
					पूर्णांक     accnum = accset[k];

					++j;

					अगर (variable_trailing_context_rules
					    && !(accnum &
						 YY_TRAILING_शीर्ष_MASK)
					    && accnum > 0
					    && accnum <= अंक_rules
					    && rule_type[accnum] ==
					    RULE_VARIABLE) {
						/* Special hack to flag
						 * accepting number as part
						 * of trailing context rule.
						 */
						accnum |= YY_TRAILING_MASK;
					}

					mkdata (accnum);
					yyacclist_तथ्य[yyacclist_curr++] = accnum;

					अगर (env.trace) {
						ख_लिखो (मानक_त्रुटि, "[%d]",
							 accset[k]);

						अगर (k < nacc)
							ख_माला_दो (", ",
							       मानक_त्रुटि);
						अन्यथा
							अ_दो ('\n',
							      मानक_त्रुटि);
					}
				}
			}
		}

		/* add accepting number for the "jam" state */
		acc_array[i] = j;

		dataend (शून्य);
		outn("]])");
		footprint += sz * ptype->width;
		अगर (tablesext) {
			yytbl_तथ्य_compress (yyacclist_tbl);
			अगर (yytbl_तथ्य_fwrite (&tableswr, yyacclist_tbl) < 0)
				flexerror (_("Could not write yyacclist_tbl"));
			yytbl_तथ्य_destroy (yyacclist_tbl);
			yyacclist_tbl = शून्य;
		}
	}

	अन्यथा {
		dfaacc[end_of_बफर_state].dfaacc_state =
		    end_of_बफर_action;

		क्रम (i = 1; i <= lastdfa; ++i)
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

	अगर (reject)
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

	yyacc_tbl = सुस्मृति(1, माप (काष्ठा yytbl_तथ्य));
	yytbl_तथ्य_init (yyacc_tbl, YYTD_ID_ACCEPT);
	yyacc_tbl->td_lolen = (flex_uint32_t) sz;
	yyacc_tbl->td_तथ्य = yyacc_तथ्य =
	    सुस्मृति(yyacc_tbl->td_lolen, माप (flex_int32_t));
	yyacc_curr=1;

	क्रम (i = 1; i <= lastdfa; ++i) {
		mkdata (acc_array[i]);
		yyacc_तथ्य[yyacc_curr++] = acc_array[i];

		अगर (!reject && env.trace && acc_array[i])
			ख_लिखो (मानक_त्रुटि, _("state # %d accepts: [%d]\n"),
				 i, acc_array[i]);
	}

	/* Add entry for "jam" state. */
	mkdata (acc_array[i]);
	yyacc_तथ्य[yyacc_curr++] = acc_array[i];

	अगर (reject) {
		/* Add "cap" for the list. */
		mkdata (acc_array[i]);
		yyacc_तथ्य[yyacc_curr++] = acc_array[i];
	}

	dataend (शून्य);
	outn ("]])");
	footprint += sz * ptype->width;

	अगर (tablesext) {
		yytbl_तथ्य_compress (yyacc_tbl);
		अगर (yytbl_तथ्य_fwrite (&tableswr, yyacc_tbl) < 0)
			flexerror (_("Could not write yyacc_tbl"));
	}
	yytbl_तथ्य_destroy (yyacc_tbl);
	yyacc_tbl = शून्य;
	/* End generating yy_accept */

	अगर (ctrl.useecs) {

		genecs ();
		अगर (tablesext) {
			काष्ठा yytbl_तथ्य *tbl;

			tbl = mkecstbl ();
			yytbl_तथ्य_compress (tbl);
			अगर (yytbl_तथ्य_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ecstbl"));
			yytbl_तथ्य_destroy (tbl);
			tbl = 0;
		}
	}

	अगर (ctrl.usemecs) {
		/* Begin generating yy_meta */
		/* Write out meta-equivalence classes (used to index
		 * templates with).
		 */
		flex_int32_t *yymecs_तथ्य = 0;
		yymeta_tbl = सुस्मृति(1, माप (काष्ठा yytbl_तथ्य));
		yytbl_तथ्य_init (yymeta_tbl, YYTD_ID_META);
		yymeta_tbl->td_lolen = (flex_uint32_t) (numecs + 1);
		yymeta_tbl->td_तथ्य = yymecs_तथ्य =
		    सुस्मृति(yymeta_tbl->td_lolen,
			   माप (flex_int32_t));

		अगर (env.trace)
			ख_माला_दो (_("\n\nMeta-Equivalence Classes:\n"),
			       मानक_त्रुटि);
		out_dec ("m4_define([[M4_HOOK_MECSTABLE_SIZE]], [[%d]])", numecs+1);
		outn ("m4_define([[M4_HOOK_MECSTABLE_BODY]], [[m4_dnl");
 	
		क्रम (i = 1; i <= numecs; ++i) {
			अगर (env.trace)
				ख_लिखो (मानक_त्रुटि, "%d = %d\n",
					 i, ABS (tecbck[i]));

			mkdata (ABS (tecbck[i]));
			yymecs_तथ्य[i] = ABS (tecbck[i]);
		}

		dataend (शून्य);
		outn ("]])");
		footprint += माप(YY_CHAR) * (numecs + 1);
		अगर (tablesext) {
			yytbl_तथ्य_compress (yymeta_tbl);
			अगर (yytbl_तथ्य_fwrite (&tableswr, yymeta_tbl) < 0)
				flexerror (_("Could not write yymeta_tbl"));
		}
		yytbl_तथ्य_destroy (yymeta_tbl);
		yymeta_tbl = शून्य;
		/* End generating yy_meta */
	}

	योग_states = lastdfa + numtemps;

	/* Begin generating yy_base */
	sz = योग_states + 1;
	ptype = optimize_pack(sz);
	out_str ("m4_define([[M4_HOOK_BASE_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_BASE_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_BASE_BODY]], [[m4_dnl");

	yybase_tbl = सुस्मृति (1, माप (काष्ठा yytbl_तथ्य));
	yytbl_तथ्य_init (yybase_tbl, YYTD_ID_BASE);
	yybase_tbl->td_lolen = (flex_uint32_t) (योग_states + 1);
	yybase_tbl->td_तथ्य = yybase_तथ्य =
	    सुस्मृति(yybase_tbl->td_lolen,
		   माप (flex_int32_t));
	yybase_curr = 1;

	क्रम (i = 1; i <= lastdfa; ++i) {
		पूर्णांक d = def[i];

		अगर (base[i] == JAMSTATE)
			base[i] = jambase;

		अगर (d == JAMSTATE)
			def[i] = jamstate;

		अन्यथा अगर (d < 0) {
			/* Template reference. */
			++tmpuses;
			def[i] = lastdfa - d + 1;
		}

		mkdata (base[i]);
		yybase_तथ्य[yybase_curr++] = base[i];
	}

	/* Generate jam state's base index. */
	mkdata (base[i]);
	yybase_तथ्य[yybase_curr++] = base[i];

	क्रम (++i /* skip jam state */ ; i <= योग_states; ++i) {
		mkdata (base[i]);
		yybase_तथ्य[yybase_curr++] = base[i];
		def[i] = jamstate;
	}

	dataend (शून्य);
	outn ("]])");
	footprint += sz * ptype->width;

	अगर (tablesext) {
		yytbl_तथ्य_compress (yybase_tbl);
		अगर (yytbl_तथ्य_fwrite (&tableswr, yybase_tbl) < 0)
			flexerror (_("Could not write yybase_tbl"));
	}
	yytbl_तथ्य_destroy (yybase_tbl);
	yybase_tbl = शून्य;
	/* End generating yy_base */


	/* Begin generating yy_def */
	ptype = optimize_pack(योग_states + 1);
	out_str ("m4_define([[M4_HOOK_DEF_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_DEF_SIZE]], [[%d]])", योग_states + 1);
	outn ("m4_define([[M4_HOOK_DEF_BODY]], [[m4_dnl");

	yydef_tbl = सुस्मृति(1, माप (काष्ठा yytbl_तथ्य));
	yytbl_तथ्य_init (yydef_tbl, YYTD_ID_DEF);
	yydef_tbl->td_lolen = (flex_uint32_t)(योग_states + 1);
	yydef_tbl->td_तथ्य = yydef_तथ्य =
	    सुस्मृति(yydef_tbl->td_lolen, माप (flex_int32_t));

	क्रम (i = 1; i <= योग_states; ++i) {
		mkdata (def[i]);
		yydef_तथ्य[i] = def[i];
	}

	dataend (शून्य);
	outn ("]])");
	footprint += (योग_states + 1) * ptype->width;

	अगर (tablesext) {
		yytbl_तथ्य_compress (yydef_tbl);
		अगर (yytbl_तथ्य_fwrite (&tableswr, yydef_tbl) < 0)
			flexerror (_("Could not write yydef_tbl"));
	}
	yytbl_तथ्य_destroy (yydef_tbl);
	yydef_tbl = शून्य;
	/* End generating yy_def */


	ptype = optimize_pack(tblend + 1);
	/* Note: Used when !ctrl.fulltbl && !ctrl.fullspd).
	 * (Alternately defined when ctrl.fullspd)
	 */
	out_str ("m4_define([[M4_HOOK_YYNXT_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_YYNXT_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_YYNXT_BODY]], [[m4_dnl");

	yynxt_tbl = सुस्मृति (1, माप (काष्ठा yytbl_तथ्य));
	yytbl_तथ्य_init (yynxt_tbl, YYTD_ID_NXT);
	yynxt_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yynxt_tbl->td_तथ्य = yynxt_तथ्य =
	    सुस्मृति (yynxt_tbl->td_lolen, माप (flex_int32_t));

	क्रम (i = 1; i <= tblend; ++i) {
		/* Note, the order of the following test is important.
		 * If chk[i] is 0, then nxt[i] is undefined.
		 */
		अगर (chk[i] == 0 || nxt[i] == 0)
			nxt[i] = jamstate;	/* new state is the JAM state */

		mkdata (nxt[i]);
		yynxt_तथ्य[i] = nxt[i];
	}

	dataend (शून्य);
	outn("]])");
	footprint += ptype->width * (tblend + 1);

	अगर (tablesext) {
		yytbl_तथ्य_compress (yynxt_tbl);
		अगर (yytbl_तथ्य_fwrite (&tableswr, yynxt_tbl) < 0)
			flexerror (_("Could not write yynxt_tbl"));
	}
	yytbl_तथ्य_destroy (yynxt_tbl);
	yynxt_tbl = शून्य;
	/* End generating yy_nxt */

	/* Begin generating yy_chk */
	ptype = optimize_pack(tblend + 1);
	out_str ("m4_define([[M4_HOOK_CHK_TYPE]], [[%s]])", ptype->name);
	out_dec ("m4_define([[M4_HOOK_CHK_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_CHK_BODY]], [[m4_dnl");
	
	yychk_tbl = सुस्मृति (1, माप (काष्ठा yytbl_तथ्य));
	yytbl_तथ्य_init (yychk_tbl, YYTD_ID_CHK);
	yychk_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yychk_tbl->td_तथ्य = yychk_तथ्य =
	    सुस्मृति(yychk_tbl->td_lolen, माप (flex_int32_t));

	क्रम (i = 1; i <= tblend; ++i) {
		अगर (chk[i] == 0)
			++nummt;

		mkdata (chk[i]);
		yychk_तथ्य[i] = chk[i];
	}

	dataend (शून्य);
	outn ("]])");
	footprint += ptype->width * (tblend + 1);

	अगर (tablesext) {
		yytbl_तथ्य_compress (yychk_tbl);
		अगर (yytbl_तथ्य_fwrite (&tableswr, yychk_tbl) < 0)
			flexerror (_("Could not write yychk_tbl"));
	}
	yytbl_तथ्य_destroy (yychk_tbl);
	yychk_tbl = शून्य;
	/* End generating yy_chk */

	मुक्त(acc_array);
}


व्योम visible_define (स्थिर अक्षर *symname)
{
	out_m4_define(symname, शून्य);
	comment(symname);
	outc ('\n');
}

व्योम visible_define_str (स्थिर अक्षर *symname, स्थिर अक्षर *val)
{
	अक्षर buf[128];
	out_m4_define(symname, val);
	snprintf(buf, माप(buf), "%s = %s", symname, val);
	comment(buf);
	outc ('\n');
}

व्योम visible_define_int (स्थिर अक्षर *symname, स्थिर पूर्णांक val)
{
	अक्षर nbuf[24], buf[128];
	snprintf(nbuf, माप(nbuf), "%d", val);
	out_m4_define(symname, nbuf);
	snprintf(buf, माप(buf), "%s = %d", symname, val);
	comment(buf);
	outc ('\n');
}

/* make_tables - generate transition tables
 */

व्योम make_tables (व्योम)
{
	अक्षर buf[128];
	पूर्णांक i;
	काष्ठा yytbl_तथ्य *yynultrans_tbl = शून्य;

	/* This is where we REALLY begin generating the tables. */

	अगर (ctrl.fullspd) {
		genctbl ();
		अगर (tablesext) {
			काष्ठा yytbl_तथ्य *tbl;

			tbl = mkctbl ();
			yytbl_तथ्य_compress (tbl);
			अगर (yytbl_तथ्य_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_तथ्य_destroy (tbl);

			tbl = mkssltbl ();
			yytbl_तथ्य_compress (tbl);
			अगर (yytbl_तथ्य_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ssltbl"));
			yytbl_तथ्य_destroy (tbl);
			tbl = 0;

			अगर (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_तथ्य_compress (tbl);
				अगर (yytbl_तथ्य_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_तथ्य_destroy (tbl);
				tbl = 0;
			}
		}
	}
	अन्यथा अगर (ctrl.fulltbl) {
		genftbl ();
		अगर (tablesext) {
			काष्ठा yytbl_तथ्य *tbl;

			/* Alternately defined if !ctrl.ffullspd && !ctrl.fulltbl */
			काष्ठा packtype_t *ptype;
			tbl = mkftbl ();
			yytbl_तथ्य_compress (tbl);
			ptype = optimize_pack(tbl->td_lolen);
			out_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
			अगर (yytbl_तथ्य_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_तथ्य_destroy (tbl);
			tbl = 0;

			अगर (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_तथ्य_compress (tbl);
				अगर (yytbl_तथ्य_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_तथ्य_destroy (tbl);
				tbl = 0;
			}
		}
	}
	अन्यथा {
		gentabs ();
	}

	snprintf(buf, माप(buf), "footprint: %ld bytes\n", footprint);
	comment(buf);
	snprintf(buf, माप(buf), "tblend: %d\n", tblend);
	comment(buf);
	snprintf(buf, माप(buf), "numecs: %d\n", numecs);
	comment(buf);
	snprintf(buf, माप(buf), "num_rules: %d\n", अंक_rules);
	comment(buf);
	snprintf(buf, माप(buf), "lastdfa: %d\n", lastdfa);
	comment(buf);
	outc ('\n');
	
	// Only at this point do we know if the automaton has backups.
	// Some m4 conditionals require this information.

	comment("m4 controls begin\n");

	अगर (अंक_backing_up > 0)
		visible_define ( "M4_MODE_HAS_BACKING_UP");

	// These are used for NUL transitions
	अगर ((अंक_backing_up > 0 && !reject) && (!nultrans || ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NEED_YY_CP");
	अगर ((अंक_backing_up > 0 && !reject) && (ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NULTRANS_WRAP");

	comment("m4 controls end\n");
	out ("\n");

	अगर (ctrl.do_yylineno) {

		geneoltbl ();

		अगर (tablesext) {
			काष्ठा yytbl_तथ्य *tbl;

			tbl = mkeoltbl ();
			yytbl_तथ्य_compress (tbl);
			अगर (yytbl_तथ्य_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write eoltbl"));
			yytbl_तथ्य_destroy (tbl);
			tbl = 0;
		}
	}

	अगर (nultrans) {
		flex_int32_t *yynultrans_तथ्य = 0;

		/* Begin generating yy_NUL_trans */
		out_str ("m4_define([[M4_HOOK_NULTRANS_TYPE]], [[%s]])", (ctrl.fullspd) ? "struct yy_trans_info*" : "M4_HOOK_INT32");
		out_dec ("m4_define([[M4_HOOK_NULTRANS_SIZE]], [[%d]])", lastdfa + 1);
		outn ("m4_define([[M4_HOOK_NULTRANS_BODY]], [[m4_dnl");

		yynultrans_tbl = सुस्मृति(1, माप (काष्ठा yytbl_तथ्य));
		yytbl_तथ्य_init (yynultrans_tbl, YYTD_ID_NUL_TRANS);
		// Performance kludge for C. Gives a small improvement
		// in table loading time.
		अगर (ctrl.fullspd && ctrl.have_state_entry_format)
			yynultrans_tbl->td_flags |= YYTD_PTRANS;
		yynultrans_tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);
		yynultrans_tbl->td_तथ्य = yynultrans_तथ्य =
		    सुस्मृति(yynultrans_tbl->td_lolen,
			   माप (flex_int32_t));

		क्रम (i = 1; i <= lastdfa; ++i) {
			अगर ((yynultrans_tbl->td_flags & YYTD_PTRANS) != 0) {
				// Only works in very C-like languages  
				out_dec ("    &yy_transition[%d],\n",
					 base[i]);
				yynultrans_तथ्य[i] = base[i];
			}
			अन्यथा {
				// This will work anywhere
				mkdata (nultrans[i]);
				yynultrans_तथ्य[i] = nultrans[i];
			}
		}

		dataend (शून्य);
		outn("]])");
		footprint += (lastdfa + 1) * (ctrl.fullspd ? माप(काष्ठा yy_trans_info *) : माप(int32_t));
		अगर (tablesext) {
			yytbl_तथ्य_compress (yynultrans_tbl);
			अगर (yytbl_तथ्य_fwrite (&tableswr, yynultrans_tbl) <
			    0)
				flexerror (_
					   ("Could not write yynultrans_tbl"));
		}

		अगर (yynultrans_tbl != शून्य) {
			yytbl_तथ्य_destroy (yynultrans_tbl);
			yynultrans_tbl = शून्य;
		}

		/* End generating yy_NUL_trans */
	}

	अगर (ctrl.ddebug) {		/* Spit out table mapping rules to line numbers. */
		/* Policy choice: we don't include this space
		 * in the table metering.
		 */
		काष्ठा packtype_t *ptype = optimize_pack(अंक_rules);
		out_str ("m4_define([[M4_HOOK_DEBUGTABLE_TYPE]], [[%s]])", ptype->name);
		out_dec ("m4_define([[M4_HOOK_DEBUGTABLE_SIZE]], [[%d]])", अंक_rules);
		outn ("m4_define([[M4_HOOK_DEBUGTABLE_BODY]], [[m4_dnl");

		क्रम (i = 1; i < अंक_rules; ++i)
			mkdata (rule_linenum[i]);
		dataend (शून्य);
		outn("]])");
	}
}
