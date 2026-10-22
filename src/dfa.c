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

#അന്തര്ഭാവ "flexdef.h"
#അന്തര്ഭാവ "tables.h"

/* declare functions that have forward references */

സ്ഥിതം ശൂന്യം dump_associated_rules(FILE *, പൂർണ്ണസംഖ്യ);
സ്ഥിതം ശൂന്യം dump_transitions(FILE *, പൂർണ്ണസംഖ്യ[]);
സ്ഥിതം പൂർണ്ണസംഖ്യ  snstods(പൂർണ്ണസംഖ്യ[], പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ[], പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ *);
സ്ഥിതം ശൂന്യം sympartition(പൂർണ്ണസംഖ്യ[], പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ[], പൂർണ്ണസംഖ്യ[]);
സ്ഥിതം പൂർണ്ണസംഖ്യ  symfollowset(പൂർണ്ണസംഖ്യ[], പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ[]);


/* check_for_backing_up - check a DFA state for backing up
 *
 * synopsis
 *     void check_for_backing_up( int ds, int state[numecs] );
 *
 * ds is the number of the state to check and state[] is its out-transitions,
 * indexed by equivalence class.
 */

സ്ഥിതം ശൂന്യം check_for_backing_up(പൂർണ്ണസംഖ്യ ds, പൂർണ്ണസംഖ്യ state[])
{
	എങ്കിൽ ((reject && !dfaacc[ds].dfaacc_set) || (!reject && !dfaacc[ds].dfaacc_state)) {	/* state is non-accepting */
		++അക്കം_backing_up;

		എങ്കിൽ (env.backing_up_report) {
			fprintf (ctrl.backing_up_file,
				 _("State #%d is non-accepting -\n"), ds);

			/* identify the state */
			dump_associated_rules (ctrl.backing_up_file, ds);

			/* Now identify it further using the out- and
			 * jam-transitions.
			 */
			dump_transitions (ctrl.backing_up_file, state);

			putc ('\n', ctrl.backing_up_file);
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

സ്ഥിതം ശൂന്യം check_trailing_context(പൂർണ്ണസംഖ്യ *nfa_states, പൂർണ്ണസംഖ്യ അക്കം_states, പൂർണ്ണസംഖ്യ *accset, പൂർണ്ണസംഖ്യ nacc)
{
	പൂർണ്ണസംഖ്യ i, j;

	വേണ്ടി (i = 1; i <= അക്കം_states; ++i) {
		പൂർണ്ണസംഖ്യ     ns = nfa_states[i];
		പൂർണ്ണസംഖ്യ type = state_type[ns];
		പൂർണ്ണസംഖ്യ ar = assoc_rule[ns];

		എങ്കിൽ (type == STATE_NORMAL || rule_type[ar] != RULE_VARIABLE) {	/* do nothing */
		}

		അല്ലെങ്കിൽ എങ്കിൽ (type == STATE_TRAILING_CONTEXT) {
			/* Potential trouble.  Scan set of accepting numbers
			 * for the one marking the end of the "head".  We
			 * assume that this looping will be fairly cheap
			 * since it's rare that an accepting number set
			 * is large.
			 */
			വേണ്ടി (j = 1; j <= nacc; ++j)
				എങ്കിൽ (accset[j] & YY_TRAILING_HEAD_MASK) {
					വരി_warning (_
						      ("dangerous trailing context"),
						      rule_linenum[ar]);
					തിരികെ;
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

സ്ഥിതം ശൂന്യം dump_associated_rules(FILE *file, പൂർണ്ണസംഖ്യ ds)
{
	പൂർണ്ണസംഖ്യ i, j;
	പൂർണ്ണസംഖ്യ അക്കം_associated_rules = 0;
	പൂർണ്ണസംഖ്യ rule_set[MAX_ASSOC_RULES + 1];
	പൂർണ്ണസംഖ്യ *dset = dss[ds];
	പൂർണ്ണസംഖ്യ size = dfasiz[ds];

	വേണ്ടി (i = 1; i <= size; ++i) {
		പൂർണ്ണസംഖ്യ rule_അക്കം = rule_linenum[assoc_rule[dset[i]]];

		വേണ്ടി (j = 1; j <= അക്കം_associated_rules; ++j)
			എങ്കിൽ (rule_അക്കം == rule_set[j])
				നിർത്തുക;

		എങ്കിൽ (j > അക്കം_associated_rules) {	/* new rule */
			എങ്കിൽ (അക്കം_associated_rules < MAX_ASSOC_RULES)
				rule_set[++അക്കം_associated_rules] =
					rule_അക്കം;
		}
	}

	qsort (&rule_set [1], (size_t) അക്കം_associated_rules, വലുപ്പം (rule_set [1]), intcmp);

	fprintf (file, _(" associated rule line numbers:"));

	വേണ്ടി (i = 1; i <= അക്കം_associated_rules; ++i) {
		എങ്കിൽ (i % 8 == 1)
			putc ('\n', file);

		fprintf (file, "\t%d", rule_set[i]);
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

സ്ഥിതം ശൂന്യം dump_transitions(FILE *file, പൂർണ്ണസംഖ്യ state[])
{
	പൂർണ്ണസംഖ്യ i, ec;
	പൂർണ്ണസംഖ്യ out_char_set[CSIZE];

	വേണ്ടി (i = 0; i < ctrl.csize; ++i) {
		ec = ABS (ecgroup[i]);
		out_char_set[i] = state[ec];
	}

	fprintf (file, _(" out-transitions: "));

	list_character_set (file, out_char_set);

	/* now invert the members of the set to get the jam transitions */
	വേണ്ടി (i = 0; i < ctrl.csize; ++i)
		out_char_set[i] = !out_char_set[i];

	fprintf (file, _("\n jam-transitions: EOF "));

	list_character_set (file, out_char_set);

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

സ്ഥിതം പൂർണ്ണസംഖ്യ *epsclosure(പൂർണ്ണസംഖ്യ *t, പൂർണ്ണസംഖ്യ *ns_addr, പൂർണ്ണസംഖ്യ accset[], പൂർണ്ണസംഖ്യ *nacc_addr, പൂർണ്ണസംഖ്യ *hv_addr)
{
	പൂർണ്ണസംഖ്യ     stkpos, ns, tsp;
	പൂർണ്ണസംഖ്യ     numstates = *ns_addr, nacc, hashval, transsym, nfaccnum;
	പൂർണ്ണസംഖ്യ     stkend, nstate;
	സ്ഥിതം പൂർണ്ണസംഖ്യ did_stk_init = false, *stk;

#define MARK_STATE(state) \
ചെയ്യുക{ trans1[state] = trans1[state] - MARKER_DIFFERENCE;} ആകുമ്പോൾ(0)

#define IS_MARKED(state) (trans1[state] < 0)

#define UNMARK_STATE(state) \
ചെയ്യുക{ trans1[state] = trans1[state] + MARKER_DIFFERENCE;} ആകുമ്പോൾ(0)

#define CHECK_ACCEPT(state) \
ചെയ്യുക{ \
nfaccnum = accptnum[state]; \
എങ്കിൽ ( nfaccnum != NIL ) \
accset[++nacc] = nfaccnum; \
}ആകുമ്പോൾ(0)

#define DO_REALLOCATION() \
ചെയ്യുക { \
current_max_dfa_size += MAX_DFA_SIZE_INCREMENT; \
++അക്കം_reallocs; \
t = reallocate_integer_array( t, current_max_dfa_size ); \
stk = reallocate_integer_array( stk, current_max_dfa_size ); \
}ആകുമ്പോൾ(0) \

#define PUT_ON_അട്ടി(state) \
ചെയ്യുക { \
എങ്കിൽ ( ++stkend >= current_max_dfa_size ) \
DO_REALLOCATION(); \
stk[stkend] = state; \
MARK_STATE(state); \
}ആകുമ്പോൾ(0)

#define ADD_STATE(state) \
ചെയ്യുക { \
എങ്കിൽ ( ++numstates >= current_max_dfa_size ) \
DO_REALLOCATION(); \
t[numstates] = state; \
hashval += state; \
}ആകുമ്പോൾ(0)

#define അട്ടി_STATE(state) \
ചെയ്യുക { \
PUT_ON_അട്ടി(state); \
CHECK_ACCEPT(state); \
എങ്കിൽ ( nfaccnum != NIL || transchar[state] != SYM_EPSILON ) \
ADD_STATE(state); \
}ആകുമ്പോൾ(0)


	എങ്കിൽ (!did_stk_init) {
		stk = allocate_integer_array (current_max_dfa_size);
		did_stk_init = true;
	}

	nacc = stkend = hashval = 0;

	വേണ്ടി (nstate = 1; nstate <= numstates; ++nstate) {
		ns = t[nstate];

		/* The state could be marked if we've already pushed it onto
		 * the stack.
		 */
		എങ്കിൽ (!IS_MARKED (ns)) {
			PUT_ON_അട്ടി (ns);
			CHECK_ACCEPT (ns);
			hashval += ns;
		}
	}

	വേണ്ടി (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ns = stk[stkpos];
		transsym = transchar[ns];

		എങ്കിൽ (transsym == SYM_EPSILON) {
			tsp = trans1[ns] + MARKER_DIFFERENCE;

			എങ്കിൽ (tsp != NO_TRANSITION) {
				എങ്കിൽ (!IS_MARKED (tsp))
					അട്ടി_STATE (tsp);

				tsp = trans2[ns];

				എങ്കിൽ (tsp != NO_TRANSITION
				    && !IS_MARKED (tsp))
					അട്ടി_STATE (tsp);
			}
		}
	}

	/* Clear out "visit" markers. */

	വേണ്ടി (stkpos = 1; stkpos <= stkend; ++stkpos) {
		എങ്കിൽ (IS_MARKED (stk[stkpos]))
			UNMARK_STATE (stk[stkpos]);
		അല്ലെങ്കിൽ
			flexfatal (_
				   ("consistency check failed in epsclosure()"));
	}

	*ns_addr = numstates;
	*hv_addr = hashval;
	*nacc_addr = nacc;

	തിരികെ t;
}


/* increase_max_dfas - increase the maximum number of DFAs */

ശൂന്യം increase_max_dfas (ശൂന്യം)
{
	current_max_dfas += MAX_DFAS_INCREMENT;

	++അക്കം_reallocs;

	base = reallocate_integer_array (base, current_max_dfas);
	def = reallocate_integer_array (def, current_max_dfas);
	dfasiz = reallocate_integer_array (dfasiz, current_max_dfas);
	accsiz = reallocate_integer_array (accsiz, current_max_dfas);
	dhash = reallocate_integer_array (dhash, current_max_dfas);
	dss = reallocate_int_ptr_array (dss, current_max_dfas);
	dfaacc = reallocate_array(dfaacc, current_max_dfas,
		വലുപ്പം(സംഘം dfaacc_union));

	എങ്കിൽ (nultrans)
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

size_t ntod (ശൂന്യം)
{
	പൂർണ്ണസംഖ്യ    *accset, ds, nacc, newds;
	പൂർണ്ണസംഖ്യ     sym, hashval, numstates, dsize;
	പൂർണ്ണസംഖ്യ     അക്കം_full_table_rows=0;	/* used only for -f */
	പൂർണ്ണസംഖ്യ    *nset, *dset;
	പൂർണ്ണസംഖ്യ     targptr, totaltrans, i, comstate, comfreq, targ;
	പൂർണ്ണസംഖ്യ     symlist[CSIZE + 1];
	പൂർണ്ണസംഖ്യ     അക്കം_start_states;
	പൂർണ്ണസംഖ്യ     todo_head, todo_next;

	ഘടന yytbl_data *yynxt_tbl = 0;
	flex_int32_t *yynxt_data = 0, yynxt_curr = 0;

	/* Note that the following are indexed by *equivalence classes*
	 * and not by characters.  Since equivalence classes are indexed
	 * beginning with 1, even if the scanner accepts NUL's, this
	 * means that (since every character is potentially in its own
	 * equivalence class) these arrays must have room for indices
	 * from 1 to CSIZE, so their size must be CSIZE + 1.
	 */
	പൂർണ്ണസംഖ്യ     duplist[CSIZE + 1], state[CSIZE + 1];
	പൂർണ്ണസംഖ്യ     targfreq[CSIZE + 1] = {0}, targstate[CSIZE + 1];

	/* accset needs to be large enough to hold all of the rules present
	 * in the input, *plus* their YY_TRAILING_HEAD_MASK variants.
	 */
	accset = allocate_integer_array ((അക്കം_rules + 1) * 2);
	nset = allocate_integer_array (current_max_dfa_size);

	/* The "todo" queue is represented by the head, which is the DFA
	 * state currently being processed, and the "next", which is the
	 * next DFA state number available (not in use).  We depend on the
	 * fact that snstods() returns DFA's \in increasing order/, and thus
	 * need only know the bounds of the dfas to be processed.
	 */
	todo_head = todo_next = 0;

	വേണ്ടി (i = 0; i <= ctrl.csize; ++i) {
		duplist[i] = NIL;
		symlist[i] = false;
	}

	വേണ്ടി (i = 0; i <= അക്കം_rules; ++i)
		accset[i] = NIL;

	എങ്കിൽ (env.trace) {
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
	എങ്കിൽ (ctrl.fulltbl && ecgroup[0] == numecs && is_power_of_2(numecs))
		nultrans = allocate_integer_array (current_max_dfas);

	എങ്കിൽ (ctrl.fullspd) {
		വേണ്ടി (i = 0; i <= numecs; ++i)
			state[i] = 0;

		place_state (state, 0, 0);
		dfaacc[0].dfaacc_state = 0;
	}

	അല്ലെങ്കിൽ എങ്കിൽ (ctrl.fulltbl) {
		എങ്കിൽ (nultrans)
			/* We won't be including NUL's transitions in the
			 * table, so build it for entries from 0 .. numecs - 1.
			 */
			അക്കം_full_table_rows = numecs;

		അല്ലെങ്കിൽ
			/* Take into account the fact that we'll be including
			 * the NUL entries in the transition table.  Build it
			 * from 0 .. numecs.
			 */
			അക്കം_full_table_rows = numecs + 1;

		/* Begin generating yy_nxt[][]
		 * This spans the entire LONG function.
		 * This table is tricky because we don't know how big it will be.
		 * So we'll have to realloc() on the way...
		 * we'll wait until we can calculate yynxt_tbl->td_hilen.
		 */
		yynxt_tbl = calloc(1, വലുപ്പം (ഘടന yytbl_data));
     
		yytbl_data_init (yynxt_tbl, YYTD_ID_NXT);
		yynxt_tbl->td_hilen = 1;
		yynxt_tbl->td_lolen = (flex_uint32_t) അക്കം_full_table_rows;
		yynxt_tbl->td_data = yynxt_data =
		    calloc(yynxt_tbl->td_lolen *
			   yynxt_tbl->td_hilen,
			   വലുപ്പം (flex_int32_t));
		yynxt_curr = 0;

		ഘടന packtype_t *ptype = optimize_pack(0);
		/* Note: Used when ctrl.fulltbl is on. Alternately defined elsewhere */
		out_str ("m4_define([[M4_HOOK_NXT_TYPE]], [[%s]])", ptype->name);
		out_dec ("m4_define([[M4_HOOK_NXT_ROWS]], [[%d]])", അക്കം_full_table_rows);
		outn ("m4_define([[M4_HOOK_NXT_BODY]], [[m4_dnl");
		outn ("M4_HOOK_TABLE_OPENER");
		എങ്കിൽ (gentables)
			outn ("M4_HOOK_TABLE_OPENER");

		/* Generate 0 entries for state #0. */
		വേണ്ടി (i = 0; i < അക്കം_full_table_rows; ++i) {
			mk2data (0);
			yynxt_data[yynxt_curr++] = 0;
		}

		എങ്കിൽ (gentables) {
			dataflush ();
			outn ("M4_HOOK_TABLE_CONTINUE");
		}
	}

	/* Create the first states. */

	അക്കം_start_states = lastsc * 2;

	വേണ്ടി (i = 1; i <= അക്കം_start_states; ++i) {
		numstates = 1;

		/* For each start condition, make one state for the case when
		 * we're at the beginning of the line (the '^' operator) and
		 * one for the case when we're not.
		 */
		എങ്കിൽ (i % 2 == 1)
			nset[numstates] = scset[(i / 2) + 1];
		അല്ലെങ്കിൽ
			nset[numstates] =
				mkbranch (scbol[i / 2], scset[i / 2]);

		nset = epsclosure (nset, &numstates, accset, &nacc,
				   &hashval);

		എങ്കിൽ (snstods (nset, numstates, accset, nacc, hashval, &ds)) {
			numas += nacc;
			totnst += numstates;
			++todo_next;

			എങ്കിൽ (variable_trailing_context_rules && nacc > 0)
				check_trailing_context (nset, numstates,
							accset, nacc);
		}
	}

	എങ്കിൽ (!ctrl.fullspd) {
		എങ്കിൽ (!snstods (nset, 0, accset, 0, 0, &end_of_buffer_state))
			flexfatal (_
				   ("could not create unique end-of-buffer state"));

		++numas;
		++അക്കം_start_states;
		++todo_next;
	}


	ആകുമ്പോൾ (todo_head < todo_next) {
		targptr = 0;
		totaltrans = 0;

		വേണ്ടി (i = 1; i <= numecs; ++i)
			state[i] = 0;

		ds = ++todo_head;

		dset = dss[ds];
		dsize = dfasiz[ds];

		എങ്കിൽ (env.trace)
			fprintf (stderr, _("state # %d:\n"), ds);

		sympartition (dset, dsize, symlist, duplist);

		വേണ്ടി (sym = 1; sym <= numecs; ++sym) {
			എങ്കിൽ (symlist[sym]) {
				symlist[sym] = 0;

				എങ്കിൽ (duplist[sym] == NIL) {
					/* Symbol has unique out-transitions. */
					numstates =
						symfollowset (dset, dsize,
							      sym, nset);
					nset = epsclosure (nset,
							   &numstates,
							   accset, &nacc,
							   &hashval);

					എങ്കിൽ (snstods
					    (nset, numstates, accset, nacc,
					     hashval, &newds)) {
						totnst = totnst +
							numstates;
						++todo_next;
						numas += nacc;

						എങ്കിൽ (variable_trailing_context_rules && nacc > 0)
							check_trailing_context
								(nset,
								 numstates,
								 accset,
								 nacc);
					}

					state[sym] = newds;

					എങ്കിൽ (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 newds);

					targfreq[++targptr] = 1;
					targstate[targptr] = newds;
					++numuniq;
				}

				അല്ലെങ്കിൽ {
					/* sym's equivalence class has the same
					 * transitions as duplist(sym)'s
					 * equivalence class.
					 */
					targ = state[duplist[sym]];
					state[sym] = targ;

					എങ്കിൽ (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 targ);

					/* Update frequency count for
					 * destination state.
					 */

					i = 0;
					ആകുമ്പോൾ (targstate[++i] != targ) ;

					++targfreq[i];
					++numdup;
				}

				++totaltrans;
				duplist[sym] = NIL;
			}
		}


		numsnpairs += totaltrans;

		എങ്കിൽ (ds > അക്കം_start_states)
			check_for_backing_up (ds, state);

		എങ്കിൽ (nultrans) {
			nultrans[ds] = state[NUL_ec];
			state[NUL_ec] = 0;	/* remove transition */
		}

		എങ്കിൽ (ctrl.fulltbl) {

			/* Each time we hit here, it's another td_hilen, so we realloc. */
			yynxt_tbl->td_hilen++;
			yynxt_tbl->td_data = yynxt_data =
				realloc (yynxt_data,
						     yynxt_tbl->td_hilen *
						     yynxt_tbl->td_lolen *
						     വലുപ്പം (flex_int32_t));
			എങ്കിൽ (gentables)
				outn ("M4_HOOK_TABLE_OPENER");

			/* Supply array's 0-element. */
			എങ്കിൽ (ds == end_of_buffer_state) {
				mk2data (-end_of_buffer_state);
				yynxt_data[yynxt_curr++] =
					-end_of_buffer_state;
			}
			അല്ലെങ്കിൽ {
				mk2data (end_of_buffer_state);
				yynxt_data[yynxt_curr++] =
					end_of_buffer_state;
			}

			വേണ്ടി (i = 1; i < അക്കം_full_table_rows; ++i) {
				/* Jams are marked by negative of state
				 * number.
				 */
				mk2data (state[i] ? state[i] : -ds);
				yynxt_data[yynxt_curr++] =
					state[i] ? state[i] : -ds;
			}

			എങ്കിൽ (gentables) {
				dataflush ();
				outn ("M4_HOOK_TABLE_CONTINUE");
			}
		}

		അല്ലെങ്കിൽ എങ്കിൽ (ctrl.fullspd)
			place_state (state, ds, totaltrans);

		അല്ലെങ്കിൽ എങ്കിൽ (ds == end_of_buffer_state)
			/* Special case this state to make sure it does what
			 * it's supposed to, i.e., jam on end-of-buffer.
			 */
			stack1 (ds, 0, 0, JAMSTATE);

		അല്ലെങ്കിൽ {		/* normal, compressed state */

			/* Determine which destination state is the most
			 * common, and how many transitions to it there are.
			 */

			comfreq = 0;
			comstate = 0;

			വേണ്ടി (i = 1; i <= targptr; ++i)
				എങ്കിൽ (targfreq[i] > comfreq) {
					comfreq = targfreq[i];
					comstate = targstate[i];
				}

			bldtbl (state, ds, totaltrans, comstate, comfreq);
		}
	}

	എങ്കിൽ (ctrl.fulltbl) {
		dataend ("M4_HOOK_TABLE_CLOSER");
		outn("/* body */]])");
		എങ്കിൽ (tablesext) {
			yytbl_data_compress (yynxt_tbl);
			എങ്കിൽ (yytbl_data_fwrite (&tableswr, yynxt_tbl) < 0)
				flexerror (_
					   ("Could not write yynxt_tbl[][]"));
		}
		എങ്കിൽ (yynxt_tbl) {
			yytbl_data_destroy (yynxt_tbl);
			yynxt_tbl = 0;
		}
	}

	അല്ലെങ്കിൽ എങ്കിൽ (!ctrl.fullspd) {
		cmptmps ();	/* create compressed template entries */

		/* Create tables for all the states with only one
		 * out-transition.
		 */
		ആകുമ്പോൾ (onesp > 0) {
			mk1tbl (onestate[onesp], onesym[onesp],
				onenext[onesp], onedef[onesp]);
			--onesp;
		}

		mkdeftbl ();
	}


	സ്വതന്ത്രം(accset);
	സ്വതന്ത്രം(nset);

	തിരികെ (yynxt_tbl != ശൂന്യ) ? (yynxt_tbl->td_hilen * വലുപ്പം(int32_t)) : 0;
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

സ്ഥിതം പൂർണ്ണസംഖ്യ snstods(പൂർണ്ണസംഖ്യ sns[], പൂർണ്ണസംഖ്യ numstates, പൂർണ്ണസംഖ്യ accset[], പൂർണ്ണസംഖ്യ nacc, പൂർണ്ണസംഖ്യ hashval, പൂർണ്ണസംഖ്യ *newds_addr)
{
	പൂർണ്ണസംഖ്യ didsort = 0;
	പൂർണ്ണസംഖ്യ i, j;
	പൂർണ്ണസംഖ്യ newds, *oldsns;

	വേണ്ടി (i = 1; i <= lastdfa; ++i)
		എങ്കിൽ (hashval == dhash[i]) {
			എങ്കിൽ (numstates == dfasiz[i]) {
				oldsns = dss[i];

				എങ്കിൽ (!didsort) {
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 */
					qsort (&sns [1], (size_t) numstates, വലുപ്പം (sns [1]), intcmp);
					didsort = 1;
				}

				വേണ്ടി (j = 1; j <= numstates; ++j)
					എങ്കിൽ (sns[j] != oldsns[j])
						നിർത്തുക;

				എങ്കിൽ (j > numstates) {
					++dfaeql;
					*newds_addr = i;
					തിരികെ 0;
				}

				++hshcol;
			}

			അല്ലെങ്കിൽ
				++hshsave;
		}

	/* Make a new dfa. */

	എങ്കിൽ (++lastdfa >= current_max_dfas)
		increase_max_dfas ();

	newds = lastdfa;

	dss[newds] = allocate_integer_array (numstates + 1);

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	എങ്കിൽ (!didsort)
          	qsort (&sns [1], (size_t) numstates, വലുപ്പം (sns [1]), intcmp);

	വേണ്ടി (i = 1; i <= numstates; ++i)
		dss[newds][i] = sns[i];

	dfasiz[newds] = numstates;
	dhash[newds] = hashval;

	എങ്കിൽ (nacc == 0) {
		എങ്കിൽ (reject)
			dfaacc[newds].dfaacc_set = ശൂന്യ;
		അല്ലെങ്കിൽ
			dfaacc[newds].dfaacc_state = 0;

		accsiz[newds] = 0;
	}

	അല്ലെങ്കിൽ എങ്കിൽ (reject) {
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.
		 */

		qsort (&accset [1], (size_t) nacc, വലുപ്പം (accset [1]), intcmp);

		dfaacc[newds].dfaacc_set =
			allocate_integer_array (nacc + 1);

		/* Save the accepting set for later */
		വേണ്ടി (i = 1; i <= nacc; ++i) {
			dfaacc[newds].dfaacc_set[i] = accset[i];

			എങ്കിൽ (accset[i] <= അക്കം_rules)
				/* Who knows, perhaps a REJECT can yield
				 * this rule.
				 */
				rule_useful[accset[i]] = true;
		}

		accsiz[newds] = nacc;
	}

	അല്ലെങ്കിൽ {
		/* Find lowest numbered rule so the disambiguating rule
		 * will work.
		 */
		j = അക്കം_rules + 1;

		വേണ്ടി (i = 1; i <= nacc; ++i)
			എങ്കിൽ (accset[i] < j)
				j = accset[i];

		dfaacc[newds].dfaacc_state = j;

		എങ്കിൽ (j <= അക്കം_rules)
			rule_useful[j] = true;
	}

	*newds_addr = newds;

	തിരികെ 1;
}


/* symfollowset - follow the symbol transitions one step
 *
 * synopsis
 *    numstates = symfollowset( int ds[current_max_dfa_size], int dsize,
 *				int transsym, int nset[current_max_dfa_size] );
 */

സ്ഥിതം പൂർണ്ണസംഖ്യ symfollowset(പൂർണ്ണസംഖ്യ ds[], പൂർണ്ണസംഖ്യ dsize, പൂർണ്ണസംഖ്യ transsym, പൂർണ്ണസംഖ്യ nset[])
{
	പൂർണ്ണസംഖ്യ     ns, tsp, sym, i, j, lenccl, ch, numstates, ccllist;

	numstates = 0;

	വേണ്ടി (i = 1; i <= dsize; ++i) {	/* for each nfa state ns in the state set of ds */
		ns = ds[i];
		sym = transchar[ns];
		tsp = trans1[ns];

		എങ്കിൽ (sym < 0) {	/* it's a character class */
			sym = -sym;
			ccllist = cclmap[sym];
			lenccl = ccllen[sym];

			എങ്കിൽ (cclng[sym]) {
				വേണ്ടി (j = 0; j < lenccl; ++j) {
					/* Loop through negated character
					 * class.
					 */
					ch = ccltbl[ccllist + j];

					എങ്കിൽ (ch == 0)
						ch = NUL_ec;

					എങ്കിൽ (ch > transsym)
						/* Transsym isn't in negated
						 * ccl.
						 */
						നിർത്തുക;

					അല്ലെങ്കിൽ എങ്കിൽ (ch == transsym)
						/* next 2 */
						പോകുക bottom;
				}

				/* Didn't find transsym in ccl. */
				nset[++numstates] = tsp;
			}

			അല്ലെങ്കിൽ
				വേണ്ടി (j = 0; j < lenccl; ++j) {
					ch = ccltbl[ccllist + j];

					എങ്കിൽ (ch == 0)
						ch = NUL_ec;

					എങ്കിൽ (ch > transsym)
						നിർത്തുക;
					അല്ലെങ്കിൽ എങ്കിൽ (ch == transsym) {
						nset[++numstates] = tsp;
						നിർത്തുക;
					}
				}
		}

		അല്ലെങ്കിൽ എങ്കിൽ (sym == SYM_EPSILON) {	/* do nothing */
		}

		അല്ലെങ്കിൽ എങ്കിൽ (ABS (ecgroup[sym]) == transsym)
			nset[++numstates] = tsp;

	      bottom:;
	}

	തിരികെ numstates;
}


/* sympartition - partition characters with same out-transitions
 *
 * synopsis
 *    sympartition( int ds[current_max_dfa_size], int numstates,
 *			int symlist[numecs], int duplist[numecs] );
 */

സ്ഥിതം ശൂന്യം sympartition(പൂർണ്ണസംഖ്യ ds[], പൂർണ്ണസംഖ്യ numstates, പൂർണ്ണസംഖ്യ symlist[], പൂർണ്ണസംഖ്യ duplist[])
{
	പൂർണ്ണസംഖ്യ     tch, i, j, k, ns, dupfwd[CSIZE + 1], lenccl, cclp, ich;

	/* Partitioning is done by creating equivalence classes for those
	 * characters which have out-transitions from the given state.  Thus
	 * we are really creating equivalence classes of equivalence classes.
	 */

	വേണ്ടി (i = 1; i <= numecs; ++i) {	/* initialize equivalence class list */
		duplist[i] = i - 1;
		dupfwd[i] = i + 1;
	}

	duplist[1] = NIL;
	dupfwd[numecs] = NIL;

	വേണ്ടി (i = 1; i <= numstates; ++i) {
		ns = ds[i];
		tch = transchar[ns];

		എങ്കിൽ (tch != SYM_EPSILON) {
			എങ്കിൽ (tch < -lastccl || tch >= ctrl.csize) {
				flexfatal (_
					   ("bad transition character detected in sympartition()"));
			}

			എങ്കിൽ (tch >= 0) {	/* character transition */
				പൂർണ്ണസംഖ്യ     ec = ecgroup[tch];

				mkechar (ec, dupfwd, duplist);
				symlist[ec] = 1;
			}

			അല്ലെങ്കിൽ {	/* character class */
				tch = -tch;

				lenccl = ccllen[tch];
				cclp = cclmap[tch];
				mkeccl (ccltbl + cclp, lenccl, dupfwd,
					duplist, numecs, NUL_ec);

				എങ്കിൽ (cclng[tch]) {
					j = 0;

					വേണ്ടി (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						എങ്കിൽ (ich == 0)
							ich = NUL_ec;

						വേണ്ടി (++j; j < ich; ++j)
							symlist[j] = 1;
					}

					വേണ്ടി (++j; j <= numecs; ++j)
						symlist[j] = 1;
				}

				അല്ലെങ്കിൽ
					വേണ്ടി (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						എങ്കിൽ (ich == 0)
							ich = NUL_ec;

						symlist[ich] = 1;
					}
			}
		}
	}
}
