/* dfa - DFA construction routines */

/* SPDX-License-Identifier: BSD-3-Clause-flex */

/*  Copyright (c) 1990 The Regents of the University of California. */
/*  All rights reserved. */

/*  This code is derived from software contributed to Berkeley by */
/*  Vern Paxson. */

/*  The United States Government has rights in this work pursuant */
/*  to contract no. DE-AC03-76SF00098 between the United States */
/*  Department of Energy and the University of California. */

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

#అన్తర్భావ "flexdef.h"
#అన్తర్భావ "tables.h"

/* declare functions that have forward references */

స్థిర శూన్య dump_associated_నియమాలు(FILE *, పూర్ణాంకం);
స్థిర శూన్య dump_transitions(FILE *, పూర్ణాంకం[]);
స్థిర పూర్ణాంకం  snstods(పూర్ణాంకం[], పూర్ణాంకం, పూర్ణాంకం[], పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం *);
స్థిర శూన్య sympartition(పూర్ణాంకం[], పూర్ణాంకం, పూర్ణాంకం[], పూర్ణాంకం[]);
స్థిర పూర్ణాంకం  symfollowset(పూర్ణాంకం[], పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం[]);


/* check_for_backing_up - check a DFA state for backing up
 *
 * synopsis
 *     void check_for_backing_up( int ds, int state[numecs] );
 *
 * ds is the number of the state to check and state[] is its out-transitions,
 * indexed by equivalence class.
 */

స్థిర శూన్య check_for_backing_పైకి(పూర్ణాంకం ds, పూర్ణాంకం state[])
{
	ఒకవేళ ((reject && !dfaacc[ds].dfaacc_సమితి) || (!reject && !dfaacc[ds].dfaacc_state)) {	/* state is non-accepting */
		++అంకె_backing_పైకి;

		ఒకవేళ (env.backing_పైకి_report) {
			fprintf (ctrl.backing_పైకి_file,
				 _("State #%d is non-accepting -\n"), ds);

			/* identify the state */
			dump_associated_నియమాలు (ctrl.backing_పైకి_file, ds);

			/* Now identify it further using the out- and
			 * jam-transitions.
			 */
			dump_transitions (ctrl.backing_పైకి_file, state);

			putc ('\n', ctrl.backing_పైకి_file);
		}
	}
}


/* check_trailing_context - check to see if NFA state set constitutes
 *                          "dangerous" trailing context
 *
 * synopsis
 *    void check_trailing_context( int nfa_states[num_states+1], int num_states,
 *				int accset[nacc+1], int nacc );
 *
 * NOTES
 *  Trailing context is "dangerous" if both the head and the trailing
 *  part are of variable size \and/ there's a DFA state which contains
 *  both an accepting state for the head part of the rule and NFA states
 *  which occur after the beginning of the trailing context.
 *
 *  When such a rule is matched, it's impossible to tell if having been
 *  in the DFA state indicates the beginning of the trailing context or
 *  further-along scanning of the pattern.  In these cases, a warning
 *  message is issued.
 *
 *    nfa_states[1 .. num_states] is the list of NFA states in the DFA.
 *    accset[1 .. nacc] is the list of accepting numbers for the DFA state.
 */

స్థిర శూన్య check_trailing_context(పూర్ణాంకం *nfa_స్థితులు, పూర్ణాంకం అంకె_స్థితులు, పూర్ణాంకం *accset, పూర్ణాంకం nacc)
{
	పూర్ణాంకం i, j;

	కొరకు (i = 1; i <= అంకె_స్థితులు; ++i) {
		పూర్ణాంకం     ns = nfa_స్థితులు[i];
		పూర్ణాంకం type = state_type[ns];
		పూర్ణాంకం ar = assoc_నియమం[ns];

		ఒకవేళ (type == STATE_సాధారణ || నియమం_type[ar] != నియమం_VARIABLE) {	/* do nothing */
		}

		లేకపోతే ఒకవేళ (type == STATE_TRAILING_CONTEXT) {
			/* Potential trouble.  Scan set of accepting numbers
			 * for the one marking the end of the "head".  We
			 * assume that this looping will be fairly cheap
			 * since it's rare that an accepting number set
			 * is large.
			 */
			కొరకు (j = 1; j <= nacc; ++j)
				ఒకవేళ (accset[j] & YY_TRAILING_తల_ముసుగు) {
					పంక్తి_warning (_
						      ("dangerous trailing context"),
						      నియమం_linenum[ar]);
					తిరిగి;
				}
		}
	}
}


/* dump_associated_rules - list the rules associated with a DFA state
 *
 * Goes through the set of NFA states associated with the DFA and
 * extracts the first MAX_ASSOC_RULES unique rules, sorts them,
 * and writes a report to the given file.
 */

స్థిర శూన్య dump_associated_నియమాలు(FILE *file, పూర్ణాంకం ds)
{
	పూర్ణాంకం i, j;
	పూర్ణాంకం అంకె_associated_నియమాలు = 0;
	పూర్ణాంకం నియమం_సమితి[MAX_ASSOC_నియమాలు + 1];
	పూర్ణాంకం *dset = dss[ds];
	పూర్ణాంకం కొలత = dfasiz[ds];

	కొరకు (i = 1; i <= కొలత; ++i) {
		పూర్ణాంకం నియమం_అంకె = నియమం_linenum[assoc_నియమం[dset[i]]];

		కొరకు (j = 1; j <= అంకె_associated_నియమాలు; ++j)
			ఒకవేళ (నియమం_అంకె == నియమం_సమితి[j])
				ఆపు;

		ఒకవేళ (j > అంకె_associated_నియమాలు) {	/* new rule */
			ఒకవేళ (అంకె_associated_నియమాలు < MAX_ASSOC_నియమాలు)
				నియమం_సమితి[++అంకె_associated_నియమాలు] =
					నియమం_అంకె;
		}
	}

	qsort (&నియమం_సమితి [1], (size_t) అంకె_associated_నియమాలు, పరిమాణం (నియమం_సమితి [1]), intcmp);

	fprintf (file, _(" associated rule line numbers:"));

	కొరకు (i = 1; i <= అంకె_associated_నియమాలు; ++i) {
		ఒకవేళ (i % 8 == 1)
			putc ('\n', file);

		fprintf (file, "\t%d", నియమం_సమితి[i]);
	}

	putc ('\n', file);
}


/* dump_transitions - list the transitions associated with a DFA state
 *
 * synopsis
 *     dump_transitions( FILE *file, int state[numecs] );
 *
 * Goes through the set of out-transitions and lists them in human-readable
 * form (i.e., not as equivalence classes); also lists jam transitions
 * (i.e., all those which are not out-transitions, plus EOF).  The dump
 * is done to the given file.
 */

స్థిర శూన్య dump_transitions(FILE *file, పూర్ణాంకం state[])
{
	పూర్ణాంకం i, ec;
	పూర్ణాంకం బహిర్గతం_char_సమితి[CSIZE];

	కొరకు (i = 0; i < ctrl.csize; ++i) {
		ec = ABS (ecgroup[i]);
		బహిర్గతం_char_సమితి[i] = state[ec];
	}

	fprintf (file, _(" out-transitions: "));

	list_character_సమితి (file, బహిర్గతం_char_సమితి);

	/* now invert the members of the set to get the jam transitions */
	కొరకు (i = 0; i < ctrl.csize; ++i)
		బహిర్గతం_char_సమితి[i] = !బహిర్గతం_char_సమితి[i];

	fprintf (file, _("\n jam-transitions: EOF "));

	list_character_సమితి (file, బహిర్గతం_char_సమితి);

	putc ('\n', file);
}


/* epsclosure - construct the epsilon closure of a set of ndfa states
 *
 * synopsis
 *    int *epsclosure( int t[num_states], int *numstates_addr,
 *			int accset[num_rules+1], int *nacc_addr,
 *			int *hashval_addr );
 *
 * NOTES
 *  The epsilon closure is the set of all states reachable by an arbitrary
 *  number of epsilon transitions, which themselves do not have epsilon
 *  transitions going out, unioned with the set of states which have non-null
 *  accepting numbers.  t is an array of size numstates of nfa state numbers.
 *  Upon return, t holds the epsilon closure and *numstates_addr is updated.
 *  accset holds a list of the accepting numbers, and the size of accset is
 *  given by *nacc_addr.  t may be subjected to reallocation if it is not
 *  large enough to hold the epsilon closure.
 *
 *  hashval is the hash value for the dfa corresponding to the state set.
 */

స్థిర పూర్ణాంకం *epsclosure(పూర్ణాంకం *t, పూర్ణాంకం *ns_addr, పూర్ణాంకం accset[], పూర్ణాంకం *nacc_addr, పూర్ణాంకం *hv_addr)
{
	పూర్ణాంకం     stkpos, ns, tsp;
	పూర్ణాంకం     numstates = *ns_addr, nacc, hashval, transsym, nfaccnum;
	పూర్ణాంకం     stkend, nstate;
	స్థిర పూర్ణాంకం did_stk_init = false, *stk;

#నిర్వచించు MARK_STATE(state) \
చేయి{ trans1[state] = trans1[state] - MARKER_DIFFERENCE;} అయితే(0)

#నిర్వచించు IS_MARKED(state) (trans1[state] < 0)

#నిర్వచించు UNMARK_STATE(state) \
చేయి{ trans1[state] = trans1[state] + MARKER_DIFFERENCE;} అయితే(0)

#నిర్వచించు CHECK_ACCEPT(state) \
చేయి{ \
nfaccnum = accptnum[state]; \
ఒకవేళ ( nfaccnum != NIL ) \
accset[++nacc] = nfaccnum; \
}అయితే(0)

#నిర్వచించు DO_REALLOCATION() \
చేయి { \
current_max_dfa_కొలత += MAX_DFA_కొలత_INCREMENT; \
++అంకె_reallocs; \
t = reallocate_integer_array( t, current_max_dfa_కొలత ); \
stk = reallocate_integer_array( stk, current_max_dfa_కొలత ); \
}అయితే(0) \

#నిర్వచించు PUT_ON_దొంతర(state) \
చేయి { \
ఒకవేళ ( ++stkend >= current_max_dfa_కొలత ) \
DO_REALLOCATION(); \
stk[stkend] = state; \
MARK_STATE(state); \
}అయితే(0)

#నిర్వచించు కూడు_STATE(state) \
చేయి { \
ఒకవేళ ( ++numstates >= current_max_dfa_కొలత ) \
DO_REALLOCATION(); \
t[numstates] = state; \
hashval += state; \
}అయితే(0)

#నిర్వచించు దొంతర_STATE(state) \
చేయి { \
PUT_ON_దొంతర(state); \
CHECK_ACCEPT(state); \
ఒకవేళ ( nfaccnum != NIL || transchar[state] != SYM_EPSILON ) \
కూడు_STATE(state); \
}అయితే(0)


	ఒకవేళ (!did_stk_init) {
		stk = allocate_integer_array (current_max_dfa_కొలత);
		did_stk_init = true;
	}

	nacc = stkend = hashval = 0;

	కొరకు (nstate = 1; nstate <= numstates; ++nstate) {
		ns = t[nstate];

		/* The state could be marked if we've already pushed it onto
		 * the stack.
		 */
		ఒకవేళ (!IS_MARKED (ns)) {
			PUT_ON_దొంతర (ns);
			CHECK_ACCEPT (ns);
			hashval += ns;
		}
	}

	కొరకు (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ns = stk[stkpos];
		transsym = transchar[ns];

		ఒకవేళ (transsym == SYM_EPSILON) {
			tsp = trans1[ns] + MARKER_DIFFERENCE;

			ఒకవేళ (tsp != NO_TRANSITION) {
				ఒకవేళ (!IS_MARKED (tsp))
					దొంతర_STATE (tsp);

				tsp = trans2[ns];

				ఒకవేళ (tsp != NO_TRANSITION
				    && !IS_MARKED (tsp))
					దొంతర_STATE (tsp);
			}
		}
	}

	/* Clear out "visit" markers. */

	కొరకు (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ఒకవేళ (IS_MARKED (stk[stkpos]))
			UNMARK_STATE (stk[stkpos]);
		లేకపోతే
			flexfatal (_
				   ("consistency check failed in epsclosure()"));
	}

	*ns_addr = numstates;
	*hv_addr = hashval;
	*nacc_addr = nacc;

	తిరిగి t;
}


/* increase_max_dfas - increase the maximum number of DFAs */

శూన్య increase_max_dfas (శూన్య)
{
	current_max_dfas += MAX_DFAS_INCREMENT;

	++అంకె_reallocs;

	పునాది = reallocate_integer_array (పునాది, current_max_dfas);
	def = reallocate_integer_array (def, current_max_dfas);
	dfasiz = reallocate_integer_array (dfasiz, current_max_dfas);
	accsiz = reallocate_integer_array (accsiz, current_max_dfas);
	dhash = reallocate_integer_array (dhash, current_max_dfas);
	dss = reallocate_int_ptr_array (dss, current_max_dfas);
	dfaacc = reallocate_array(dfaacc, current_max_dfas,
		పరిమాణం(సంఘం dfaacc_union));

	ఒకవేళ (nultrans)
		nultrans =
			reallocate_integer_array (nultrans,
						  current_max_dfas);
}


/* ntod - convert an ndfa to a dfa
 *
 * Creates the dfa corresponding to the ndfa we've constructed.  The
 * dfa starts out in state #1.
 *
 * Return the amount of space, in bytes, allocated for the next table.
 * In some modes this can be zero.
 */

size_t ntod (శూన్య)
{
	పూర్ణాంకం    *accset, ds, nacc, newds;
	పూర్ణాంకం     sym, hashval, numstates, dsize;
	పూర్ణాంకం     అంకె_నిండిన_పట్టిక_అడ్డువరుసలు=0;	/* used only for -f */
	పూర్ణాంకం    *nset, *dset;
	పూర్ణాంకం     targptr, totaltrans, i, comstate, comfreq, targ;
	పూర్ణాంకం     symlist[CSIZE + 1];
	పూర్ణాంకం     అంకె_ప్రారంభం_స్థితులు;
	పూర్ణాంకం     todo_తల, todo_తదుపరి;

	నిర్మాణం yytbl_దత్తాంశం *yynxt_tbl = 0;
	flex_int32_t *yynxt_దత్తాంశం = 0, yynxt_curr = 0;

	/* Note that the following are indexed by *equivalence classes*
	 * and not by characters.  Since equivalence classes are indexed
	 * beginning with 1, even if the scanner accepts NUL's, this
	 * means that (since every character is potentially in its own
	 * equivalence class) these arrays must have room for indices
	 * from 1 to CSIZE, so their size must be CSIZE + 1.
	 */
	పూర్ణాంకం     duplist[CSIZE + 1], state[CSIZE + 1];
	పూర్ణాంకం     targfreq[CSIZE + 1] = {0}, targstate[CSIZE + 1];

	/* accset needs to be large enough to hold all of the rules present
	 * in the input, *plus* their YY_TRAILING_HEAD_MASK variants.
	 */
	accset = allocate_integer_array ((అంకె_నియమాలు + 1) * 2);
	nset = allocate_integer_array (current_max_dfa_కొలత);

	/* The "todo" queue is represented by the head, which is the DFA
	 * state currently being processed, and the "next", which is the
	 * next DFA state number available (not in use).  We depend on the
	 * fact that snstods() returns DFA's \in increasing order/, and thus
	 * need only know the bounds of the dfas to be processed.
	 */
	todo_తల = todo_తదుపరి = 0;

	కొరకు (i = 0; i <= ctrl.csize; ++i) {
		duplist[i] = NIL;
		symlist[i] = false;
	}

	కొరకు (i = 0; i <= అంకె_నియమాలు; ++i)
		accset[i] = NIL;

	ఒకవేళ (env.trace) {
		dumpnfa (scset[1]);
		fputs (_("\n\nDFA Dump:\n\n"), stderr);
	}

	inittbl ();

	/* Check to see whether we should build a separate table for
	 * transitions on NUL characters.  We don't do this for full-speed
	 * (-F) scanners, since for them we don't have a simple state
	 * number lying around with which to index the table.  We also
	 * don't bother doing it for scanners unless (1) NUL is in its own
	 * equivalence class (indicated by a positive value of
	 * ecgroup[NUL]), (2) NUL's equivalence class is the last
	 * equivalence class, and (3) the number of equivalence classes is
	 * the same as the number of characters.  This latter case comes
	 * about when useecs is false or when it's true but every character
	 * still manages to land in its own class (unlikely, but it's
	 * cheap to check for).  If all these things are true then the
	 * character code needed to represent NUL's equivalence class for
	 * indexing the tables is going to take one more bit than the
	 * number of characters, and therefore we won't be assured of
	 * being able to fit it into a YY_CHAR variable.  This rules out
	 * storing the transitions in a compressed table, since the code
	 * for interpreting them uses a YY_CHAR variable (perhaps it
	 * should just use an integer, though; this is worth pondering ...
	 * ###).
	 *
	 * Finally, for full tables, we want the number of entries in the
	 * table to be a power of two so the array references go fast (it
	 * will just take a shift to compute the major index).  If
	 * encoding NUL's transitions in the table will spoil this, we
	 * give it its own table (note that this will be the case if we're
	 * not using equivalence classes).
	 */

	/* Note that the test for ecgroup[0] == numecs below accomplishes
	 * both (1) and (2) above
	 *
	 * New way: we will only use NUL table for fulltbl, because the
	 * scanner will use an integer instead of YY_CHAR as noted above
	 */
	ఒకవేళ (ctrl.fulltbl && ecgroup[0] == numecs && is_power_యొక్క_2(numecs))
		nultrans = allocate_integer_array (current_max_dfas);

	ఒకవేళ (ctrl.fullspd) {
		కొరకు (i = 0; i <= numecs; ++i)
			state[i] = 0;

		ఉంచు_state (state, 0, 0);
		dfaacc[0].dfaacc_state = 0;
	}

	లేకపోతే ఒకవేళ (ctrl.fulltbl) {
		ఒకవేళ (nultrans)
			/* We won't be including NUL's transitions in the
			 * table, so build it for entries from 0 .. numecs - 1.
			 */
			అంకె_నిండిన_పట్టిక_అడ్డువరుసలు = numecs;

		లేకపోతే
			/* Take into account the fact that we'll be including
			 * the NUL entries in the transition table.  Build it
			 * from 0 .. numecs.
			 */
			అంకె_నిండిన_పట్టిక_అడ్డువరుసలు = numecs + 1;

		/* Begin generating yy_nxt[][]
		 * This spans the entire LONG function.
		 * This table is tricky because we don't know how big it will be.
		 * So we'll have to realloc() on the way...
		 * we'll wait until we can calculate yynxt_tbl->td_hilen.
		 */
		yynxt_tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
     
		yytbl_దత్తాంశం_init (yynxt_tbl, YYTD_ID_NXT);
		yynxt_tbl->td_hilen = 1;
		yynxt_tbl->td_lolen = (flex_uint32_t) అంకె_నిండిన_పట్టిక_అడ్డువరుసలు;
		yynxt_tbl->td_దత్తాంశం = yynxt_దత్తాంశం =
		    సున్నా_జ్ఞాపకం_ఇవ్వు(yynxt_tbl->td_lolen *
			   yynxt_tbl->td_hilen,
			   పరిమాణం (flex_int32_t));
		yynxt_curr = 0;

		నిర్మాణం packtype_t *ptype = optimize_pack(0);
		/* Note: Used when ctrl.fulltbl is on. Alternately defined elsewhere */
		బహిర్గతం_str ("m4_define([[M4_HOOK_NXT_TYPE]], [[%s]])", ptype->name);
		బహిర్గతం_dec ("m4_define([[M4_HOOK_NXT_ROWS]], [[%d]])", అంకె_నిండిన_పట్టిక_అడ్డువరుసలు);
		outn ("m4_define([[M4_HOOK_NXT_BODY]], [[m4_dnl");
		outn ("M4_HOOK_TABLE_OPENER");
		ఒకవేళ (gentables)
			outn ("M4_HOOK_TABLE_OPENER");

		/* Generate 0 entries for state #0. */
		కొరకు (i = 0; i < అంకె_నిండిన_పట్టిక_అడ్డువరుసలు; ++i) {
			mk2data (0);
			yynxt_దత్తాంశం[yynxt_curr++] = 0;
		}

		ఒకవేళ (gentables) {
			dataflush ();
			outn ("M4_HOOK_TABLE_CONTINUE");
		}
	}

	/* Create the first states. */

	అంకె_ప్రారంభం_స్థితులు = lastsc * 2;

	కొరకు (i = 1; i <= అంకె_ప్రారంభం_స్థితులు; ++i) {
		numstates = 1;

		/* For each start condition, make one state for the case when
		 * we're at the beginning of the line (the '^' operator) and
		 * one for the case when we're not.
		 */
		ఒకవేళ (i % 2 == 1)
			nset[numstates] = scset[(i / 2) + 1];
		లేకపోతే
			nset[numstates] =
				mkbranch (scbol[i / 2], scset[i / 2]);

		nset = epsclosure (nset, &numstates, accset, &nacc,
				   &hashval);

		ఒకవేళ (snstods (nset, numstates, accset, nacc, hashval, &ds)) {
			numas += nacc;
			totnst += numstates;
			++todo_తదుపరి;

			ఒకవేళ (variable_trailing_context_నియమాలు && nacc > 0)
				check_trailing_context (nset, numstates,
							accset, nacc);
		}
	}

	ఒకవేళ (!ctrl.fullspd) {
		ఒకవేళ (!snstods (nset, 0, accset, 0, 0, &చివర_యొక్క_బఫరు_state))
			flexfatal (_
				   ("could not create unique end-of-buffer state"));

		++numas;
		++అంకె_ప్రారంభం_స్థితులు;
		++todo_తదుపరి;
	}


	అయితే (todo_తల < todo_తదుపరి) {
		targptr = 0;
		totaltrans = 0;

		కొరకు (i = 1; i <= numecs; ++i)
			state[i] = 0;

		ds = ++todo_తల;

		dset = dss[ds];
		dsize = dfasiz[ds];

		ఒకవేళ (env.trace)
			fprintf (stderr, _("state # %d:\n"), ds);

		sympartition (dset, dsize, symlist, duplist);

		కొరకు (sym = 1; sym <= numecs; ++sym) {
			ఒకవేళ (symlist[sym]) {
				symlist[sym] = 0;

				ఒకవేళ (duplist[sym] == NIL) {
					/* Symbol has unique out-transitions. */
					numstates =
						symfollowset (dset, dsize,
							      sym, nset);
					nset = epsclosure (nset,
							   &numstates,
							   accset, &nacc,
							   &hashval);

					ఒకవేళ (snstods
					    (nset, numstates, accset, nacc,
					     hashval, &newds)) {
						totnst = totnst +
							numstates;
						++todo_తదుపరి;
						numas += nacc;

						ఒకవేళ (variable_trailing_context_నియమాలు && nacc > 0)
							check_trailing_context
								(nset,
								 numstates,
								 accset,
								 nacc);
					}

					state[sym] = newds;

					ఒకవేళ (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 newds);

					targfreq[++targptr] = 1;
					targstate[targptr] = newds;
					++numuniq;
				}

				లేకపోతే {
					/* sym's equivalence class has the same
					 * transitions as duplist(sym)'s
					 * equivalence class.
					 */
					targ = state[duplist[sym]];
					state[sym] = targ;

					ఒకవేళ (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 targ);

					/* Update frequency count for
					 * destination state.
					 */

					i = 0;
					అయితే (targstate[++i] != targ) ;

					++targfreq[i];
					++numdup;
				}

				++totaltrans;
				duplist[sym] = NIL;
			}
		}


		numsnpairs += totaltrans;

		ఒకవేళ (ds > అంకె_ప్రారంభం_స్థితులు)
			check_for_backing_పైకి (ds, state);

		ఒకవేళ (nultrans) {
			nultrans[ds] = state[NUL_ec];
			state[NUL_ec] = 0;	/* remove transition */
		}

		ఒకవేళ (ctrl.fulltbl) {

			/* Each time we hit here, it's another td_hilen, so we realloc. */
			yynxt_tbl->td_hilen++;
			yynxt_tbl->td_దత్తాంశం = yynxt_దత్తాంశం =
				realloc (yynxt_దత్తాంశం,
						     yynxt_tbl->td_hilen *
						     yynxt_tbl->td_lolen *
						     పరిమాణం (flex_int32_t));
			ఒకవేళ (gentables)
				outn ("M4_HOOK_TABLE_OPENER");

			/* Supply array's 0-element. */
			ఒకవేళ (ds == చివర_యొక్క_బఫరు_state) {
				mk2data (-చివర_యొక్క_బఫరు_state);
				yynxt_దత్తాంశం[yynxt_curr++] =
					-చివర_యొక్క_బఫరు_state;
			}
			లేకపోతే {
				mk2data (చివర_యొక్క_బఫరు_state);
				yynxt_దత్తాంశం[yynxt_curr++] =
					చివర_యొక్క_బఫరు_state;
			}

			కొరకు (i = 1; i < అంకె_నిండిన_పట్టిక_అడ్డువరుసలు; ++i) {
				/* Jams are marked by negative of state
				 * number.
				 */
				mk2data (state[i] ? state[i] : -ds);
				yynxt_దత్తాంశం[yynxt_curr++] =
					state[i] ? state[i] : -ds;
			}

			ఒకవేళ (gentables) {
				dataflush ();
				outn ("M4_HOOK_TABLE_CONTINUE");
			}
		}

		లేకపోతే ఒకవేళ (ctrl.fullspd)
			ఉంచు_state (state, ds, totaltrans);

		లేకపోతే ఒకవేళ (ds == చివర_యొక్క_బఫరు_state)
			/* Special case this state to make sure it does what
			 * it's supposed to, i.e., jam on end-of-buffer.
			 */
			stack1 (ds, 0, 0, JAMSTATE);

		లేకపోతే {		/* normal, compressed state */

			/* Determine which destination state is the most
			 * common, and how many transitions to it there are.
			 */

			comfreq = 0;
			comstate = 0;

			కొరకు (i = 1; i <= targptr; ++i)
				ఒకవేళ (targfreq[i] > comfreq) {
					comfreq = targfreq[i];
					comstate = targstate[i];
				}

			bldtbl (state, ds, totaltrans, comstate, comfreq);
		}
	}

	ఒకవేళ (ctrl.fulltbl) {
		dataend ("M4_HOOK_TABLE_CLOSER");
		outn("/* body */]])");
		ఒకవేళ (tablesext) {
			yytbl_దత్తాంశం_compress (yynxt_tbl);
			ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, yynxt_tbl) < 0)
				flexerror (_
					   ("Could not write yynxt_tbl[][]"));
		}
		ఒకవేళ (yynxt_tbl) {
			yytbl_దత్తాంశం_destroy (yynxt_tbl);
			yynxt_tbl = 0;
		}
	}

	లేకపోతే ఒకవేళ (!ctrl.fullspd) {
		cmptmps ();	/* create compressed template entries */

		/* Create tables for all the states with only one
		 * out-transition.
		 */
		అయితే (onesp > 0) {
			mk1tbl (onestate[onesp], onesym[onesp],
				onenext[onesp], onedef[onesp]);
			--onesp;
		}

		mkdeftbl ();
	}


	విడుదల(accset);
	విడుదల(nset);

	తిరిగి (yynxt_tbl != ఖాళీ) ? (yynxt_tbl->td_hilen * పరిమాణం(int32_t)) : 0;
}


/* snstods - converts a set of ndfa states into a dfa state
 *
 * synopsis
 *    is_new_state = snstods( int sns[numstates], int numstates,
 *				int accset[num_rules+1], int nacc,
 *				int hashval, int *newds_addr );
 *
 * On return, the dfa state number is in newds.
 */

స్థిర పూర్ణాంకం snstods(పూర్ణాంకం sns[], పూర్ణాంకం numstates, పూర్ణాంకం accset[], పూర్ణాంకం nacc, పూర్ణాంకం hashval, పూర్ణాంకం *newds_addr)
{
	పూర్ణాంకం didsort = 0;
	పూర్ణాంకం i, j;
	పూర్ణాంకం newds, *oldsns;

	కొరకు (i = 1; i <= lastdfa; ++i)
		ఒకవేళ (hashval == dhash[i]) {
			ఒకవేళ (numstates == dfasiz[i]) {
				oldsns = dss[i];

				ఒకవేళ (!didsort) {
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 */
					qsort (&sns [1], (size_t) numstates, పరిమాణం (sns [1]), intcmp);
					didsort = 1;
				}

				కొరకు (j = 1; j <= numstates; ++j)
					ఒకవేళ (sns[j] != oldsns[j])
						ఆపు;

				ఒకవేళ (j > numstates) {
					++dfaeql;
					*newds_addr = i;
					తిరిగి 0;
				}

				++hshcol;
			}

			లేకపోతే
				++hshsave;
		}

	/* Make a new dfa. */

	ఒకవేళ (++lastdfa >= current_max_dfas)
		increase_max_dfas ();

	newds = lastdfa;

	dss[newds] = allocate_integer_array (numstates + 1);

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	ఒకవేళ (!didsort)
          	qsort (&sns [1], (size_t) numstates, పరిమాణం (sns [1]), intcmp);

	కొరకు (i = 1; i <= numstates; ++i)
		dss[newds][i] = sns[i];

	dfasiz[newds] = numstates;
	dhash[newds] = hashval;

	ఒకవేళ (nacc == 0) {
		ఒకవేళ (reject)
			dfaacc[newds].dfaacc_సమితి = ఖాళీ;
		లేకపోతే
			dfaacc[newds].dfaacc_state = 0;

		accsiz[newds] = 0;
	}

	లేకపోతే ఒకవేళ (reject) {
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.
		 */

		qsort (&accset [1], (size_t) nacc, పరిమాణం (accset [1]), intcmp);

		dfaacc[newds].dfaacc_సమితి =
			allocate_integer_array (nacc + 1);

		/* Save the accepting set for later */
		కొరకు (i = 1; i <= nacc; ++i) {
			dfaacc[newds].dfaacc_సమితి[i] = accset[i];

			ఒకవేళ (accset[i] <= అంకె_నియమాలు)
				/* Who knows, perhaps a REJECT can yield
				 * this rule.
				 */
				నియమం_useful[accset[i]] = true;
		}

		accsiz[newds] = nacc;
	}

	లేకపోతే {
		/* Find lowest numbered rule so the disambiguating rule
		 * will work.
		 */
		j = అంకె_నియమాలు + 1;

		కొరకు (i = 1; i <= nacc; ++i)
			ఒకవేళ (accset[i] < j)
				j = accset[i];

		dfaacc[newds].dfaacc_state = j;

		ఒకవేళ (j <= అంకె_నియమాలు)
			నియమం_useful[j] = true;
	}

	*newds_addr = newds;

	తిరిగి 1;
}


/* symfollowset - follow the symbol transitions one step
 *
 * synopsis
 *    numstates = symfollowset( int ds[current_max_dfa_size], int dsize,
 *				int transsym, int nset[current_max_dfa_size] );
 */

స్థిర పూర్ణాంకం symfollowset(పూర్ణాంకం ds[], పూర్ణాంకం dsize, పూర్ణాంకం transsym, పూర్ణాంకం nset[])
{
	పూర్ణాంకం     ns, tsp, sym, i, j, lenccl, ch, numstates, ccllist;

	numstates = 0;

	కొరకు (i = 1; i <= dsize; ++i) {	/* for each nfa state ns in the state set of ds */
		ns = ds[i];
		sym = transchar[ns];
		tsp = trans1[ns];

		ఒకవేళ (sym < 0) {	/* it's a character class */
			sym = -sym;
			ccllist = cclmap[sym];
			lenccl = ccllen[sym];

			ఒకవేళ (cclng[sym]) {
				కొరకు (j = 0; j < lenccl; ++j) {
					/* Loop through negated character
					 * class.
					 */
					ch = ccltbl[ccllist + j];

					ఒకవేళ (ch == 0)
						ch = NUL_ec;

					ఒకవేళ (ch > transsym)
						/* Transsym isn't in negated
						 * ccl.
						 */
						ఆపు;

					లేకపోతే ఒకవేళ (ch == transsym)
						/* next 2 */
						వెళ్ళు bottom;
				}

				/* Didn't find transsym in ccl. */
				nset[++numstates] = tsp;
			}

			లేకపోతే
				కొరకు (j = 0; j < lenccl; ++j) {
					ch = ccltbl[ccllist + j];

					ఒకవేళ (ch == 0)
						ch = NUL_ec;

					ఒకవేళ (ch > transsym)
						ఆపు;
					లేకపోతే ఒకవేళ (ch == transsym) {
						nset[++numstates] = tsp;
						ఆపు;
					}
				}
		}

		లేకపోతే ఒకవేళ (sym == SYM_EPSILON) {	/* do nothing */
		}

		లేకపోతే ఒకవేళ (ABS (ecgroup[sym]) == transsym)
			nset[++numstates] = tsp;

	      bottom:;
	}

	తిరిగి numstates;
}


/* sympartition - partition characters with same out-transitions
 *
 * synopsis
 *    sympartition( int ds[current_max_dfa_size], int numstates,
 *			int symlist[numecs], int duplist[numecs] );
 */

స్థిర శూన్య sympartition(పూర్ణాంకం ds[], పూర్ణాంకం numstates, పూర్ణాంకం symlist[], పూర్ణాంకం duplist[])
{
	పూర్ణాంకం     tch, i, j, k, ns, dupfwd[CSIZE + 1], lenccl, cclp, ich;

	/* Partitioning is done by creating equivalence classes for those
	 * characters which have out-transitions from the given state.  Thus
	 * we are really creating equivalence classes of equivalence classes.
	 */

	కొరకు (i = 1; i <= numecs; ++i) {	/* initialize equivalence class list */
		duplist[i] = i - 1;
		dupfwd[i] = i + 1;
	}

	duplist[1] = NIL;
	dupfwd[numecs] = NIL;

	కొరకు (i = 1; i <= numstates; ++i) {
		ns = ds[i];
		tch = transchar[ns];

		ఒకవేళ (tch != SYM_EPSILON) {
			ఒకవేళ (tch < -lastccl || tch >= ctrl.csize) {
				flexfatal (_
					   ("bad transition character detected in sympartition()"));
			}

			ఒకవేళ (tch >= 0) {	/* character transition */
				పూర్ణాంకం     ec = ecgroup[tch];

				mkechar (ec, dupfwd, duplist);
				symlist[ec] = 1;
			}

			లేకపోతే {	/* character class */
				tch = -tch;

				lenccl = ccllen[tch];
				cclp = cclmap[tch];
				mkeccl (ccltbl + cclp, lenccl, dupfwd,
					duplist, numecs, NUL_ec);

				ఒకవేళ (cclng[tch]) {
					j = 0;

					కొరకు (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						ఒకవేళ (ich == 0)
							ich = NUL_ec;

						కొరకు (++j; j < ich; ++j)
							symlist[j] = 1;
					}

					కొరకు (++j; j <= numecs; ++j)
						symlist[j] = 1;
				}

				లేకపోతే
					కొరకు (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						ఒకవేళ (ich == 0)
							ich = NUL_ec;

						symlist[ich] = 1;
					}
			}
		}
	}
}
