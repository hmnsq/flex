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

#अन्तर्भाव "flexdef.h"
#अन्तर्भाव "tables.h"

/* declare functions that have forward references */

स्थिर शून्य dump_associated_rules(FILE *, पूर्णाङ्क);
स्थिर शून्य dump_transitions(FILE *, पूर्णाङ्क[]);
स्थिर पूर्णाङ्क  snstods(पूर्णाङ्क[], पूर्णाङ्क, पूर्णाङ्क[], पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क *);
स्थिर शून्य sympartition(पूर्णाङ्क[], पूर्णाङ्क, पूर्णाङ्क[], पूर्णाङ्क[]);
स्थिर पूर्णाङ्क  symfollowset(पूर्णाङ्क[], पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क[]);


/* check_for_backing_up - check a DFA state for backing up
 *
 * synopsis
 *     void check_for_backing_up( int ds, int state[numecs] );
 *
 * ds is the number of the state to check and state[] is its out-transitions,
 * indexed by equivalence class.
 */

स्थिर शून्य check_for_backing_up(पूर्णाङ्क ds, पूर्णाङ्क state[])
{
	यदि ((reject && !dfaacc[ds].dfaacc_set) || (!reject && !dfaacc[ds].dfaacc_state)) {	/* state is non-accepting */
		++अंक_backing_up;

		यदि (env.backing_up_report) {
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

स्थिर शून्य check_trailing_context(पूर्णाङ्क *nfa_states, पूर्णाङ्क अंक_states, पूर्णाङ्क *accset, पूर्णाङ्क nacc)
{
	पूर्णाङ्क i, j;

	प्रति (i = 1; i <= अंक_states; ++i) {
		पूर्णाङ्क     ns = nfa_states[i];
		पूर्णाङ्क type = state_type[ns];
		पूर्णाङ्क ar = assoc_rule[ns];

		यदि (type == STATE_NORMAL || rule_type[ar] != RULE_VARIABLE) {	/* do nothing */
		}

		अन्यथा यदि (type == STATE_TRAILING_CONTEXT) {
			/* Potential trouble.  Scan set of accepting numbers
			 * for the one marking the end of the "head".  We
			 * assume that this looping will be fairly cheap
			 * since it's rare that an accepting number set
			 * is large.
			 */
			प्रति (j = 1; j <= nacc; ++j)
				यदि (accset[j] & YY_TRAILING_HEAD_MASK) {
					पंक्ति_warning (_
						      ("dangerous trailing context"),
						      rule_linenum[ar]);
					प्रत्यागम;
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

स्थिर शून्य dump_associated_rules(FILE *file, पूर्णाङ्क ds)
{
	पूर्णाङ्क i, j;
	पूर्णाङ्क अंक_associated_rules = 0;
	पूर्णाङ्क rule_set[MAX_ASSOC_RULES + 1];
	पूर्णाङ्क *dset = dss[ds];
	पूर्णाङ्क size = dfasiz[ds];

	प्रति (i = 1; i <= size; ++i) {
		पूर्णाङ्क rule_अंक = rule_linenum[assoc_rule[dset[i]]];

		प्रति (j = 1; j <= अंक_associated_rules; ++j)
			यदि (rule_अंक == rule_set[j])
				भङ्ग;

		यदि (j > अंक_associated_rules) {	/* new rule */
			यदि (अंक_associated_rules < MAX_ASSOC_RULES)
				rule_set[++अंक_associated_rules] =
					rule_अंक;
		}
	}

	qsort (&rule_set [1], (size_t) अंक_associated_rules, परिमाण (rule_set [1]), intcmp);

	fprintf (file, _(" associated rule line numbers:"));

	प्रति (i = 1; i <= अंक_associated_rules; ++i) {
		यदि (i % 8 == 1)
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

स्थिर शून्य dump_transitions(FILE *file, पूर्णाङ्क state[])
{
	पूर्णाङ्क i, ec;
	पूर्णाङ्क out_char_set[CSIZE];

	प्रति (i = 0; i < ctrl.csize; ++i) {
		ec = ABS (ecgroup[i]);
		out_char_set[i] = state[ec];
	}

	fprintf (file, _(" out-transitions: "));

	list_character_set (file, out_char_set);

	/* now invert the members of the set to get the jam transitions */
	प्रति (i = 0; i < ctrl.csize; ++i)
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

स्थिर पूर्णाङ्क *epsclosure(पूर्णाङ्क *t, पूर्णाङ्क *ns_addr, पूर्णाङ्क accset[], पूर्णाङ्क *nacc_addr, पूर्णाङ्क *hv_addr)
{
	पूर्णाङ्क     stkpos, ns, tsp;
	पूर्णाङ्क     numstates = *ns_addr, nacc, hashval, transsym, nfaccnum;
	पूर्णाङ्क     stkend, nstate;
	स्थिर पूर्णाङ्क did_stk_init = false, *stk;

#define MARK_STATE(state) \
कुरु{ trans1[state] = trans1[state] - MARKER_DIFFERENCE;} यावत्(0)

#define IS_MARKED(state) (trans1[state] < 0)

#define UNMARK_STATE(state) \
कुरु{ trans1[state] = trans1[state] + MARKER_DIFFERENCE;} यावत्(0)

#define CHECK_ACCEPT(state) \
कुरु{ \
nfaccnum = accptnum[state]; \
यदि ( nfaccnum != NIL ) \
accset[++nacc] = nfaccnum; \
}यावत्(0)

#define DO_REALLOCATION() \
कुरु { \
current_max_dfa_size += MAX_DFA_SIZE_INCREMENT; \
++अंक_reallocs; \
t = reallocate_integer_array( t, current_max_dfa_size ); \
stk = reallocate_integer_array( stk, current_max_dfa_size ); \
}यावत्(0) \

#define PUT_ON_ढेर(state) \
कुरु { \
यदि ( ++stkend >= current_max_dfa_size ) \
DO_REALLOCATION(); \
stk[stkend] = state; \
MARK_STATE(state); \
}यावत्(0)

#define ADD_STATE(state) \
कुरु { \
यदि ( ++numstates >= current_max_dfa_size ) \
DO_REALLOCATION(); \
t[numstates] = state; \
hashval += state; \
}यावत्(0)

#define ढेर_STATE(state) \
कुरु { \
PUT_ON_ढेर(state); \
CHECK_ACCEPT(state); \
यदि ( nfaccnum != NIL || transchar[state] != SYM_EPSILON ) \
ADD_STATE(state); \
}यावत्(0)


	यदि (!did_stk_init) {
		stk = allocate_integer_array (current_max_dfa_size);
		did_stk_init = true;
	}

	nacc = stkend = hashval = 0;

	प्रति (nstate = 1; nstate <= numstates; ++nstate) {
		ns = t[nstate];

		/* The state could be marked if we've already pushed it onto
		 * the stack.
		 */
		यदि (!IS_MARKED (ns)) {
			PUT_ON_ढेर (ns);
			CHECK_ACCEPT (ns);
			hashval += ns;
		}
	}

	प्रति (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ns = stk[stkpos];
		transsym = transchar[ns];

		यदि (transsym == SYM_EPSILON) {
			tsp = trans1[ns] + MARKER_DIFFERENCE;

			यदि (tsp != NO_TRANSITION) {
				यदि (!IS_MARKED (tsp))
					ढेर_STATE (tsp);

				tsp = trans2[ns];

				यदि (tsp != NO_TRANSITION
				    && !IS_MARKED (tsp))
					ढेर_STATE (tsp);
			}
		}
	}

	/* Clear out "visit" markers. */

	प्रति (stkpos = 1; stkpos <= stkend; ++stkpos) {
		यदि (IS_MARKED (stk[stkpos]))
			UNMARK_STATE (stk[stkpos]);
		अन्यथा
			flexfatal (_
				   ("consistency check failed in epsclosure()"));
	}

	*ns_addr = numstates;
	*hv_addr = hashval;
	*nacc_addr = nacc;

	प्रत्यागम t;
}


/* increase_max_dfas - increase the maximum number of DFAs */

शून्य increase_max_dfas (शून्य)
{
	current_max_dfas += MAX_DFAS_INCREMENT;

	++अंक_reallocs;

	base = reallocate_integer_array (base, current_max_dfas);
	def = reallocate_integer_array (def, current_max_dfas);
	dfasiz = reallocate_integer_array (dfasiz, current_max_dfas);
	accsiz = reallocate_integer_array (accsiz, current_max_dfas);
	dhash = reallocate_integer_array (dhash, current_max_dfas);
	dss = reallocate_int_ptr_array (dss, current_max_dfas);
	dfaacc = reallocate_array(dfaacc, current_max_dfas,
		परिमाण(सङ्घ dfaacc_union));

	यदि (nultrans)
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

size_t ntod (शून्य)
{
	पूर्णाङ्क    *accset, ds, nacc, newds;
	पूर्णाङ्क     sym, hashval, numstates, dsize;
	पूर्णाङ्क     अंक_full_table_rows=0;	/* used only for -f */
	पूर्णाङ्क    *nset, *dset;
	पूर्णाङ्क     targptr, totaltrans, i, comstate, comfreq, targ;
	पूर्णाङ्क     symlist[CSIZE + 1];
	पूर्णाङ्क     अंक_start_states;
	पूर्णाङ्क     todo_head, todo_next;

	संरचना yytbl_data *yynxt_tbl = 0;
	flex_int32_t *yynxt_data = 0, yynxt_curr = 0;

	/* Note that the following are indexed by *equivalence classes*
	 * and not by characters.  Since equivalence classes are indexed
	 * beginning with 1, even if the scanner accepts NUL's, this
	 * means that (since every character is potentially in its own
	 * equivalence class) these arrays must have room for indices
	 * from 1 to CSIZE, so their size must be CSIZE + 1.
	 */
	पूर्णाङ्क     duplist[CSIZE + 1], state[CSIZE + 1];
	पूर्णाङ्क     targfreq[CSIZE + 1] = {0}, targstate[CSIZE + 1];

	/* accset needs to be large enough to hold all of the rules present
	 * in the input, *plus* their YY_TRAILING_HEAD_MASK variants.
	 */
	accset = allocate_integer_array ((अंक_rules + 1) * 2);
	nset = allocate_integer_array (current_max_dfa_size);

	/* The "todo" queue is represented by the head, which is the DFA
	 * state currently being processed, and the "next", which is the
	 * next DFA state number available (not in use).  We depend on the
	 * fact that snstods() returns DFA's \in increasing order/, and thus
	 * need only know the bounds of the dfas to be processed.
	 */
	todo_head = todo_next = 0;

	प्रति (i = 0; i <= ctrl.csize; ++i) {
		duplist[i] = NIL;
		symlist[i] = false;
	}

	प्रति (i = 0; i <= अंक_rules; ++i)
		accset[i] = NIL;

	यदि (env.trace) {
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
	यदि (ctrl.fulltbl && ecgroup[0] == numecs && is_power_of_2(numecs))
		nultrans = allocate_integer_array (current_max_dfas);

	यदि (ctrl.fullspd) {
		प्रति (i = 0; i <= numecs; ++i)
			state[i] = 0;

		place_state (state, 0, 0);
		dfaacc[0].dfaacc_state = 0;
	}

	अन्यथा यदि (ctrl.fulltbl) {
		यदि (nultrans)
			/* We won't be including NUL's transitions in the
			 * table, so build it for entries from 0 .. numecs - 1.
			 */
			अंक_full_table_rows = numecs;

		अन्यथा
			/* Take into account the fact that we'll be including
			 * the NUL entries in the transition table.  Build it
			 * from 0 .. numecs.
			 */
			अंक_full_table_rows = numecs + 1;

		/* Begin generating yy_nxt[][]
		 * This spans the entire LONG function.
		 * This table is tricky because we don't know how big it will be.
		 * So we'll have to realloc() on the way...
		 * we'll wait until we can calculate yynxt_tbl->td_hilen.
		 */
		yynxt_tbl = calloc(1, परिमाण (संरचना yytbl_data));
     
		yytbl_data_init (yynxt_tbl, YYTD_ID_NXT);
		yynxt_tbl->td_hilen = 1;
		yynxt_tbl->td_lolen = (flex_uint32_t) अंक_full_table_rows;
		yynxt_tbl->td_data = yynxt_data =
		    calloc(yynxt_tbl->td_lolen *
			   yynxt_tbl->td_hilen,
			   परिमाण (flex_int32_t));
		yynxt_curr = 0;

		संरचना packtype_t *ptype = optimize_pack(0);
		/* Note: Used when ctrl.fulltbl is on. Alternately defined elsewhere */
		out_str ("m4_define([[M4_HOOK_NXT_TYPE]], [[%s]])", ptype->name);
		out_dec ("m4_define([[M4_HOOK_NXT_ROWS]], [[%d]])", अंक_full_table_rows);
		outn ("m4_define([[M4_HOOK_NXT_BODY]], [[m4_dnl");
		outn ("M4_HOOK_TABLE_OPENER");
		यदि (gentables)
			outn ("M4_HOOK_TABLE_OPENER");

		/* Generate 0 entries for state #0. */
		प्रति (i = 0; i < अंक_full_table_rows; ++i) {
			mk2data (0);
			yynxt_data[yynxt_curr++] = 0;
		}

		यदि (gentables) {
			dataflush ();
			outn ("M4_HOOK_TABLE_CONTINUE");
		}
	}

	/* Create the first states. */

	अंक_start_states = lastsc * 2;

	प्रति (i = 1; i <= अंक_start_states; ++i) {
		numstates = 1;

		/* For each start condition, make one state for the case when
		 * we're at the beginning of the line (the '^' operator) and
		 * one for the case when we're not.
		 */
		यदि (i % 2 == 1)
			nset[numstates] = scset[(i / 2) + 1];
		अन्यथा
			nset[numstates] =
				mkbranch (scbol[i / 2], scset[i / 2]);

		nset = epsclosure (nset, &numstates, accset, &nacc,
				   &hashval);

		यदि (snstods (nset, numstates, accset, nacc, hashval, &ds)) {
			numas += nacc;
			totnst += numstates;
			++todo_next;

			यदि (variable_trailing_context_rules && nacc > 0)
				check_trailing_context (nset, numstates,
							accset, nacc);
		}
	}

	यदि (!ctrl.fullspd) {
		यदि (!snstods (nset, 0, accset, 0, 0, &end_of_buffer_state))
			flexfatal (_
				   ("could not create unique end-of-buffer state"));

		++numas;
		++अंक_start_states;
		++todo_next;
	}


	यावत् (todo_head < todo_next) {
		targptr = 0;
		totaltrans = 0;

		प्रति (i = 1; i <= numecs; ++i)
			state[i] = 0;

		ds = ++todo_head;

		dset = dss[ds];
		dsize = dfasiz[ds];

		यदि (env.trace)
			fprintf (stderr, _("state # %d:\n"), ds);

		sympartition (dset, dsize, symlist, duplist);

		प्रति (sym = 1; sym <= numecs; ++sym) {
			यदि (symlist[sym]) {
				symlist[sym] = 0;

				यदि (duplist[sym] == NIL) {
					/* Symbol has unique out-transitions. */
					numstates =
						symfollowset (dset, dsize,
							      sym, nset);
					nset = epsclosure (nset,
							   &numstates,
							   accset, &nacc,
							   &hashval);

					यदि (snstods
					    (nset, numstates, accset, nacc,
					     hashval, &newds)) {
						totnst = totnst +
							numstates;
						++todo_next;
						numas += nacc;

						यदि (variable_trailing_context_rules && nacc > 0)
							check_trailing_context
								(nset,
								 numstates,
								 accset,
								 nacc);
					}

					state[sym] = newds;

					यदि (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 newds);

					targfreq[++targptr] = 1;
					targstate[targptr] = newds;
					++numuniq;
				}

				अन्यथा {
					/* sym's equivalence class has the same
					 * transitions as duplist(sym)'s
					 * equivalence class.
					 */
					targ = state[duplist[sym]];
					state[sym] = targ;

					यदि (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 targ);

					/* Update frequency count for
					 * destination state.
					 */

					i = 0;
					यावत् (targstate[++i] != targ) ;

					++targfreq[i];
					++numdup;
				}

				++totaltrans;
				duplist[sym] = NIL;
			}
		}


		numsnpairs += totaltrans;

		यदि (ds > अंक_start_states)
			check_for_backing_up (ds, state);

		यदि (nultrans) {
			nultrans[ds] = state[NUL_ec];
			state[NUL_ec] = 0;	/* remove transition */
		}

		यदि (ctrl.fulltbl) {

			/* Each time we hit here, it's another td_hilen, so we realloc. */
			yynxt_tbl->td_hilen++;
			yynxt_tbl->td_data = yynxt_data =
				realloc (yynxt_data,
						     yynxt_tbl->td_hilen *
						     yynxt_tbl->td_lolen *
						     परिमाण (flex_int32_t));
			यदि (gentables)
				outn ("M4_HOOK_TABLE_OPENER");

			/* Supply array's 0-element. */
			यदि (ds == end_of_buffer_state) {
				mk2data (-end_of_buffer_state);
				yynxt_data[yynxt_curr++] =
					-end_of_buffer_state;
			}
			अन्यथा {
				mk2data (end_of_buffer_state);
				yynxt_data[yynxt_curr++] =
					end_of_buffer_state;
			}

			प्रति (i = 1; i < अंक_full_table_rows; ++i) {
				/* Jams are marked by negative of state
				 * number.
				 */
				mk2data (state[i] ? state[i] : -ds);
				yynxt_data[yynxt_curr++] =
					state[i] ? state[i] : -ds;
			}

			यदि (gentables) {
				dataflush ();
				outn ("M4_HOOK_TABLE_CONTINUE");
			}
		}

		अन्यथा यदि (ctrl.fullspd)
			place_state (state, ds, totaltrans);

		अन्यथा यदि (ds == end_of_buffer_state)
			/* Special case this state to make sure it does what
			 * it's supposed to, i.e., jam on end-of-buffer.
			 */
			stack1 (ds, 0, 0, JAMSTATE);

		अन्यथा {		/* normal, compressed state */

			/* Determine which destination state is the most
			 * common, and how many transitions to it there are.
			 */

			comfreq = 0;
			comstate = 0;

			प्रति (i = 1; i <= targptr; ++i)
				यदि (targfreq[i] > comfreq) {
					comfreq = targfreq[i];
					comstate = targstate[i];
				}

			bldtbl (state, ds, totaltrans, comstate, comfreq);
		}
	}

	यदि (ctrl.fulltbl) {
		dataend ("M4_HOOK_TABLE_CLOSER");
		outn("/* body */]])");
		यदि (tablesext) {
			yytbl_data_compress (yynxt_tbl);
			यदि (yytbl_data_fwrite (&tableswr, yynxt_tbl) < 0)
				flexerror (_
					   ("Could not write yynxt_tbl[][]"));
		}
		यदि (yynxt_tbl) {
			yytbl_data_destroy (yynxt_tbl);
			yynxt_tbl = 0;
		}
	}

	अन्यथा यदि (!ctrl.fullspd) {
		cmptmps ();	/* create compressed template entries */

		/* Create tables for all the states with only one
		 * out-transition.
		 */
		यावत् (onesp > 0) {
			mk1tbl (onestate[onesp], onesym[onesp],
				onenext[onesp], onedef[onesp]);
			--onesp;
		}

		mkdeftbl ();
	}


	मुक्त(accset);
	मुक्त(nset);

	प्रत्यागम (yynxt_tbl != रिक्त) ? (yynxt_tbl->td_hilen * परिमाण(int32_t)) : 0;
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

स्थिर पूर्णाङ्क snstods(पूर्णाङ्क sns[], पूर्णाङ्क numstates, पूर्णाङ्क accset[], पूर्णाङ्क nacc, पूर्णाङ्क hashval, पूर्णाङ्क *newds_addr)
{
	पूर्णाङ्क didsort = 0;
	पूर्णाङ्क i, j;
	पूर्णाङ्क newds, *oldsns;

	प्रति (i = 1; i <= lastdfa; ++i)
		यदि (hashval == dhash[i]) {
			यदि (numstates == dfasiz[i]) {
				oldsns = dss[i];

				यदि (!didsort) {
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 */
					qsort (&sns [1], (size_t) numstates, परिमाण (sns [1]), intcmp);
					didsort = 1;
				}

				प्रति (j = 1; j <= numstates; ++j)
					यदि (sns[j] != oldsns[j])
						भङ्ग;

				यदि (j > numstates) {
					++dfaeql;
					*newds_addr = i;
					प्रत्यागम 0;
				}

				++hshcol;
			}

			अन्यथा
				++hshsave;
		}

	/* Make a new dfa. */

	यदि (++lastdfa >= current_max_dfas)
		increase_max_dfas ();

	newds = lastdfa;

	dss[newds] = allocate_integer_array (numstates + 1);

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	यदि (!didsort)
          	qsort (&sns [1], (size_t) numstates, परिमाण (sns [1]), intcmp);

	प्रति (i = 1; i <= numstates; ++i)
		dss[newds][i] = sns[i];

	dfasiz[newds] = numstates;
	dhash[newds] = hashval;

	यदि (nacc == 0) {
		यदि (reject)
			dfaacc[newds].dfaacc_set = रिक्त;
		अन्यथा
			dfaacc[newds].dfaacc_state = 0;

		accsiz[newds] = 0;
	}

	अन्यथा यदि (reject) {
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.
		 */

		qsort (&accset [1], (size_t) nacc, परिमाण (accset [1]), intcmp);

		dfaacc[newds].dfaacc_set =
			allocate_integer_array (nacc + 1);

		/* Save the accepting set for later */
		प्रति (i = 1; i <= nacc; ++i) {
			dfaacc[newds].dfaacc_set[i] = accset[i];

			यदि (accset[i] <= अंक_rules)
				/* Who knows, perhaps a REJECT can yield
				 * this rule.
				 */
				rule_useful[accset[i]] = true;
		}

		accsiz[newds] = nacc;
	}

	अन्यथा {
		/* Find lowest numbered rule so the disambiguating rule
		 * will work.
		 */
		j = अंक_rules + 1;

		प्रति (i = 1; i <= nacc; ++i)
			यदि (accset[i] < j)
				j = accset[i];

		dfaacc[newds].dfaacc_state = j;

		यदि (j <= अंक_rules)
			rule_useful[j] = true;
	}

	*newds_addr = newds;

	प्रत्यागम 1;
}


/* symfollowset - follow the symbol transitions one step
 *
 * synopsis
 *    numstates = symfollowset( int ds[current_max_dfa_size], int dsize,
 *				int transsym, int nset[current_max_dfa_size] );
 */

स्थिर पूर्णाङ्क symfollowset(पूर्णाङ्क ds[], पूर्णाङ्क dsize, पूर्णाङ्क transsym, पूर्णाङ्क nset[])
{
	पूर्णाङ्क     ns, tsp, sym, i, j, lenccl, ch, numstates, ccllist;

	numstates = 0;

	प्रति (i = 1; i <= dsize; ++i) {	/* for each nfa state ns in the state set of ds */
		ns = ds[i];
		sym = transchar[ns];
		tsp = trans1[ns];

		यदि (sym < 0) {	/* it's a character class */
			sym = -sym;
			ccllist = cclmap[sym];
			lenccl = ccllen[sym];

			यदि (cclng[sym]) {
				प्रति (j = 0; j < lenccl; ++j) {
					/* Loop through negated character
					 * class.
					 */
					ch = ccltbl[ccllist + j];

					यदि (ch == 0)
						ch = NUL_ec;

					यदि (ch > transsym)
						/* Transsym isn't in negated
						 * ccl.
						 */
						भङ्ग;

					अन्यथा यदि (ch == transsym)
						/* next 2 */
						गच्छ bottom;
				}

				/* Didn't find transsym in ccl. */
				nset[++numstates] = tsp;
			}

			अन्यथा
				प्रति (j = 0; j < lenccl; ++j) {
					ch = ccltbl[ccllist + j];

					यदि (ch == 0)
						ch = NUL_ec;

					यदि (ch > transsym)
						भङ्ग;
					अन्यथा यदि (ch == transsym) {
						nset[++numstates] = tsp;
						भङ्ग;
					}
				}
		}

		अन्यथा यदि (sym == SYM_EPSILON) {	/* do nothing */
		}

		अन्यथा यदि (ABS (ecgroup[sym]) == transsym)
			nset[++numstates] = tsp;

	      bottom:;
	}

	प्रत्यागम numstates;
}


/* sympartition - partition characters with same out-transitions
 *
 * synopsis
 *    sympartition( int ds[current_max_dfa_size], int numstates,
 *			int symlist[numecs], int duplist[numecs] );
 */

स्थिर शून्य sympartition(पूर्णाङ्क ds[], पूर्णाङ्क numstates, पूर्णाङ्क symlist[], पूर्णाङ्क duplist[])
{
	पूर्णाङ्क     tch, i, j, k, ns, dupfwd[CSIZE + 1], lenccl, cclp, ich;

	/* Partitioning is done by creating equivalence classes for those
	 * characters which have out-transitions from the given state.  Thus
	 * we are really creating equivalence classes of equivalence classes.
	 */

	प्रति (i = 1; i <= numecs; ++i) {	/* initialize equivalence class list */
		duplist[i] = i - 1;
		dupfwd[i] = i + 1;
	}

	duplist[1] = NIL;
	dupfwd[numecs] = NIL;

	प्रति (i = 1; i <= numstates; ++i) {
		ns = ds[i];
		tch = transchar[ns];

		यदि (tch != SYM_EPSILON) {
			यदि (tch < -lastccl || tch >= ctrl.csize) {
				flexfatal (_
					   ("bad transition character detected in sympartition()"));
			}

			यदि (tch >= 0) {	/* character transition */
				पूर्णाङ्क     ec = ecgroup[tch];

				mkechar (ec, dupfwd, duplist);
				symlist[ec] = 1;
			}

			अन्यथा {	/* character class */
				tch = -tch;

				lenccl = ccllen[tch];
				cclp = cclmap[tch];
				mkeccl (ccltbl + cclp, lenccl, dupfwd,
					duplist, numecs, NUL_ec);

				यदि (cclng[tch]) {
					j = 0;

					प्रति (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						यदि (ich == 0)
							ich = NUL_ec;

						प्रति (++j; j < ich; ++j)
							symlist[j] = 1;
					}

					प्रति (++j; j <= numecs; ++j)
						symlist[j] = 1;
				}

				अन्यथा
					प्रति (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						यदि (ich == 0)
							ich = NUL_ec;

						symlist[ich] = 1;
					}
			}
		}
	}
}
