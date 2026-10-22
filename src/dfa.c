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

स्थिर शून्य dump_associated_rules(खाता *, पूर्णांक);
स्थिर शून्य dump_transitions(खाता *, पूर्णांक[]);
स्थिर पूर्णांक  snstods(पूर्णांक[], पूर्णांक, पूर्णांक[], पूर्णांक, पूर्णांक, पूर्णांक *);
स्थिर शून्य sympartition(पूर्णांक[], पूर्णांक, पूर्णांक[], पूर्णांक[]);
स्थिर पूर्णांक  symfollowset(पूर्णांक[], पूर्णांक, पूर्णांक, पूर्णांक[]);


/* check_for_backing_up - check a DFA state for backing up
 *
 * synopsis
 *     void check_for_backing_up( int ds, int state[numecs] );
 *
 * ds is the number of the state to check and state[] is its out-transitions,
 * indexed by equivalence class.
 */

स्थिर शून्य check_for_backing_up(पूर्णांक ds, पूर्णांक state[])
{
	जर ((reject && !dfaacc[ds].dfaacc_set) || (!reject && !dfaacc[ds].dfaacc_state)) {	/* state is non-accepting */
		++अंक_backing_up;

		जर (env.backing_up_report) {
			ख_लिखो (ctrl.backing_up_file,
				 _("State #%d is non-accepting -\n"), ds);

			/* identify the state */
			dump_associated_rules (ctrl.backing_up_file, ds);

			/* Now identify it further using the out- and
			 * jam-transitions.
			 */
			dump_transitions (ctrl.backing_up_file, state);

			अ_दो ('\n', ctrl.backing_up_file);
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

स्थिर शून्य check_trailing_context(पूर्णांक *nfa_states, पूर्णांक अंक_states, पूर्णांक *accset, पूर्णांक nacc)
{
	पूर्णांक i, j;

	साठी (i = 1; i <= अंक_states; ++i) {
		पूर्णांक     ns = nfa_states[i];
		पूर्णांक type = state_type[ns];
		पूर्णांक ar = assoc_rule[ns];

		जर (type == STATE_NORMAL || rule_type[ar] != RULE_VARIABLE) {	/* do nothing */
		}

		अन्यथा जर (type == STATE_TRAILING_CONTEXT) {
			/* Potential trouble.  Scan set of accepting numbers
			 * for the one marking the end of the "head".  We
			 * assume that this looping will be fairly cheap
			 * since it's rare that an accepting number set
			 * is large.
			 */
			साठी (j = 1; j <= nacc; ++j)
				जर (accset[j] & YY_TRAILING_HEAD_MASK) {
					ओळ_warning (_
						      ("dangerous trailing context"),
						      rule_linenum[ar]);
					परत;
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

स्थिर शून्य dump_associated_rules(खाता *file, पूर्णांक ds)
{
	पूर्णांक i, j;
	पूर्णांक अंक_associated_rules = 0;
	पूर्णांक rule_set[MAX_ASSOC_RULES + 1];
	पूर्णांक *dset = dss[ds];
	पूर्णांक size = dfasiz[ds];

	साठी (i = 1; i <= size; ++i) {
		पूर्णांक rule_अंक = rule_linenum[assoc_rule[dset[i]]];

		साठी (j = 1; j <= अंक_associated_rules; ++j)
			जर (rule_अंक == rule_set[j])
				थांबा;

		जर (j > अंक_associated_rules) {	/* new rule */
			जर (अंक_associated_rules < MAX_ASSOC_RULES)
				rule_set[++अंक_associated_rules] =
					rule_अंक;
		}
	}

	क्विक (&rule_set [1], (माप_प्रकार) अंक_associated_rules, आकार (rule_set [1]), intcmp);

	ख_लिखो (file, _(" associated rule line numbers:"));

	साठी (i = 1; i <= अंक_associated_rules; ++i) {
		जर (i % 8 == 1)
			अ_दो ('\n', file);

		ख_लिखो (file, "\t%d", rule_set[i]);
	}

	अ_दो ('\n', file);
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

स्थिर शून्य dump_transitions(खाता *file, पूर्णांक state[])
{
	पूर्णांक i, ec;
	पूर्णांक out_char_set[CSIZE];

	साठी (i = 0; i < ctrl.csize; ++i) {
		ec = ABS (ecgroup[i]);
		out_char_set[i] = state[ec];
	}

	ख_लिखो (file, _(" out-transitions: "));

	list_character_set (file, out_char_set);

	/* now invert the members of the set to get the jam transitions */
	साठी (i = 0; i < ctrl.csize; ++i)
		out_char_set[i] = !out_char_set[i];

	ख_लिखो (file, _("\n jam-transitions: EOF "));

	list_character_set (file, out_char_set);

	अ_दो ('\n', file);
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

स्थिर पूर्णांक *epsclosure(पूर्णांक *t, पूर्णांक *ns_addr, पूर्णांक accset[], पूर्णांक *nacc_addr, पूर्णांक *hv_addr)
{
	पूर्णांक     stkpos, ns, tsp;
	पूर्णांक     numstates = *ns_addr, nacc, hashval, transsym, nfaccnum;
	पूर्णांक     stkend, nstate;
	स्थिर पूर्णांक did_stk_init = false, *stk;

#define MARK_STATE(state) \
करा{ trans1[state] = trans1[state] - MARKER_DIFFERENCE;} पर्यंत(0)

#define IS_MARKED(state) (trans1[state] < 0)

#define UNMARK_STATE(state) \
करा{ trans1[state] = trans1[state] + MARKER_DIFFERENCE;} पर्यंत(0)

#define CHECK_ACCEPT(state) \
करा{ \
nfaccnum = accptnum[state]; \
जर ( nfaccnum != NIL ) \
accset[++nacc] = nfaccnum; \
}पर्यंत(0)

#define DO_REALLOCATION() \
करा { \
current_max_dfa_size += MAX_DFA_SIZE_INCREMENT; \
++अंक_reallocs; \
t = reallocate_integer_array( t, current_max_dfa_size ); \
stk = reallocate_integer_array( stk, current_max_dfa_size ); \
}पर्यंत(0) \

#define PUT_ON_चळत(state) \
करा { \
जर ( ++stkend >= current_max_dfa_size ) \
DO_REALLOCATION(); \
stk[stkend] = state; \
MARK_STATE(state); \
}पर्यंत(0)

#define ADD_STATE(state) \
करा { \
जर ( ++numstates >= current_max_dfa_size ) \
DO_REALLOCATION(); \
t[numstates] = state; \
hashval += state; \
}पर्यंत(0)

#define चळत_STATE(state) \
करा { \
PUT_ON_चळत(state); \
CHECK_ACCEPT(state); \
जर ( nfaccnum != NIL || transchar[state] != SYM_EPSILON ) \
ADD_STATE(state); \
}पर्यंत(0)


	जर (!did_stk_init) {
		stk = allocate_integer_array (current_max_dfa_size);
		did_stk_init = true;
	}

	nacc = stkend = hashval = 0;

	साठी (nstate = 1; nstate <= numstates; ++nstate) {
		ns = t[nstate];

		/* The state could be marked if we've already pushed it onto
		 * the stack.
		 */
		जर (!IS_MARKED (ns)) {
			PUT_ON_चळत (ns);
			CHECK_ACCEPT (ns);
			hashval += ns;
		}
	}

	साठी (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ns = stk[stkpos];
		transsym = transchar[ns];

		जर (transsym == SYM_EPSILON) {
			tsp = trans1[ns] + MARKER_DIFFERENCE;

			जर (tsp != NO_TRANSITION) {
				जर (!IS_MARKED (tsp))
					चळत_STATE (tsp);

				tsp = trans2[ns];

				जर (tsp != NO_TRANSITION
				    && !IS_MARKED (tsp))
					चळत_STATE (tsp);
			}
		}
	}

	/* Clear out "visit" markers. */

	साठी (stkpos = 1; stkpos <= stkend; ++stkpos) {
		जर (IS_MARKED (stk[stkpos]))
			UNMARK_STATE (stk[stkpos]);
		अन्यथा
			flexfatal (_
				   ("consistency check failed in epsclosure()"));
	}

	*ns_addr = numstates;
	*hv_addr = hashval;
	*nacc_addr = nacc;

	परत t;
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
		आकार(संघ dfaacc_union));

	जर (nultrans)
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

माप_प्रकार ntod (शून्य)
{
	पूर्णांक    *accset, ds, nacc, newds;
	पूर्णांक     sym, hashval, numstates, dsize;
	पूर्णांक     अंक_full_table_rows=0;	/* used only for -f */
	पूर्णांक    *nset, *dset;
	पूर्णांक     targptr, totaltrans, i, comstate, comfreq, targ;
	पूर्णांक     symlist[CSIZE + 1];
	पूर्णांक     अंक_start_states;
	पूर्णांक     todo_head, todo_next;

	संरचना yytbl_data *yynxt_tbl = 0;
	flex_int32_t *yynxt_data = 0, yynxt_curr = 0;

	/* Note that the following are indexed by *equivalence classes*
	 * and not by characters.  Since equivalence classes are indexed
	 * beginning with 1, even if the scanner accepts NUL's, this
	 * means that (since every character is potentially in its own
	 * equivalence class) these arrays must have room for indices
	 * from 1 to CSIZE, so their size must be CSIZE + 1.
	 */
	पूर्णांक     duplist[CSIZE + 1], state[CSIZE + 1];
	पूर्णांक     targfreq[CSIZE + 1] = {0}, targstate[CSIZE + 1];

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

	साठी (i = 0; i <= ctrl.csize; ++i) {
		duplist[i] = NIL;
		symlist[i] = false;
	}

	साठी (i = 0; i <= अंक_rules; ++i)
		accset[i] = NIL;

	जर (env.trace) {
		dumpnfa (scset[1]);
		ख_माला_दो (_("\n\nDFA Dump:\n\n"), मानक_त्रुटि);
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
	जर (ctrl.fulltbl && ecgroup[0] == numecs && is_power_of_2(numecs))
		nultrans = allocate_integer_array (current_max_dfas);

	जर (ctrl.fullspd) {
		साठी (i = 0; i <= numecs; ++i)
			state[i] = 0;

		place_state (state, 0, 0);
		dfaacc[0].dfaacc_state = 0;
	}

	अन्यथा जर (ctrl.fulltbl) {
		जर (nultrans)
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
		yynxt_tbl = सुस्मृति(1, आकार (संरचना yytbl_data));
     
		yytbl_data_init (yynxt_tbl, YYTD_ID_NXT);
		yynxt_tbl->td_hilen = 1;
		yynxt_tbl->td_lolen = (flex_uint32_t) अंक_full_table_rows;
		yynxt_tbl->td_data = yynxt_data =
		    सुस्मृति(yynxt_tbl->td_lolen *
			   yynxt_tbl->td_hilen,
			   आकार (flex_int32_t));
		yynxt_curr = 0;

		संरचना packtype_t *ptype = optimize_pack(0);
		/* Note: Used when ctrl.fulltbl is on. Alternately defined elsewhere */
		out_str ("m4_define([[M4_HOOK_NXT_TYPE]], [[%s]])", ptype->name);
		out_dec ("m4_define([[M4_HOOK_NXT_ROWS]], [[%d]])", अंक_full_table_rows);
		outn ("m4_define([[M4_HOOK_NXT_BODY]], [[m4_dnl");
		outn ("M4_HOOK_TABLE_OPENER");
		जर (gentables)
			outn ("M4_HOOK_TABLE_OPENER");

		/* Generate 0 entries for state #0. */
		साठी (i = 0; i < अंक_full_table_rows; ++i) {
			mk2data (0);
			yynxt_data[yynxt_curr++] = 0;
		}

		जर (gentables) {
			dataflush ();
			outn ("M4_HOOK_TABLE_CONTINUE");
		}
	}

	/* Create the first states. */

	अंक_start_states = lastsc * 2;

	साठी (i = 1; i <= अंक_start_states; ++i) {
		numstates = 1;

		/* For each start condition, make one state for the case when
		 * we're at the beginning of the line (the '^' operator) and
		 * one for the case when we're not.
		 */
		जर (i % 2 == 1)
			nset[numstates] = scset[(i / 2) + 1];
		अन्यथा
			nset[numstates] =
				mkbranch (scbol[i / 2], scset[i / 2]);

		nset = epsclosure (nset, &numstates, accset, &nacc,
				   &hashval);

		जर (snstods (nset, numstates, accset, nacc, hashval, &ds)) {
			numas += nacc;
			totnst += numstates;
			++todo_next;

			जर (variable_trailing_context_rules && nacc > 0)
				check_trailing_context (nset, numstates,
							accset, nacc);
		}
	}

	जर (!ctrl.fullspd) {
		जर (!snstods (nset, 0, accset, 0, 0, &end_of_buffer_state))
			flexfatal (_
				   ("could not create unique end-of-buffer state"));

		++numas;
		++अंक_start_states;
		++todo_next;
	}


	पर्यंत (todo_head < todo_next) {
		targptr = 0;
		totaltrans = 0;

		साठी (i = 1; i <= numecs; ++i)
			state[i] = 0;

		ds = ++todo_head;

		dset = dss[ds];
		dsize = dfasiz[ds];

		जर (env.trace)
			ख_लिखो (मानक_त्रुटि, _("state # %d:\n"), ds);

		sympartition (dset, dsize, symlist, duplist);

		साठी (sym = 1; sym <= numecs; ++sym) {
			जर (symlist[sym]) {
				symlist[sym] = 0;

				जर (duplist[sym] == NIL) {
					/* Symbol has unique out-transitions. */
					numstates =
						symfollowset (dset, dsize,
							      sym, nset);
					nset = epsclosure (nset,
							   &numstates,
							   accset, &nacc,
							   &hashval);

					जर (snstods
					    (nset, numstates, accset, nacc,
					     hashval, &newds)) {
						totnst = totnst +
							numstates;
						++todo_next;
						numas += nacc;

						जर (variable_trailing_context_rules && nacc > 0)
							check_trailing_context
								(nset,
								 numstates,
								 accset,
								 nacc);
					}

					state[sym] = newds;

					जर (env.trace)
						ख_लिखो (मानक_त्रुटि,
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

					जर (env.trace)
						ख_लिखो (मानक_त्रुटि,
							 "\t%d\t%d\n", sym,
							 targ);

					/* Update frequency count for
					 * destination state.
					 */

					i = 0;
					पर्यंत (targstate[++i] != targ) ;

					++targfreq[i];
					++numdup;
				}

				++totaltrans;
				duplist[sym] = NIL;
			}
		}


		numsnpairs += totaltrans;

		जर (ds > अंक_start_states)
			check_for_backing_up (ds, state);

		जर (nultrans) {
			nultrans[ds] = state[NUL_ec];
			state[NUL_ec] = 0;	/* remove transition */
		}

		जर (ctrl.fulltbl) {

			/* Each time we hit here, it's another td_hilen, so we realloc. */
			yynxt_tbl->td_hilen++;
			yynxt_tbl->td_data = yynxt_data =
				पुनः_स्मृति (yynxt_data,
						     yynxt_tbl->td_hilen *
						     yynxt_tbl->td_lolen *
						     आकार (flex_int32_t));
			जर (gentables)
				outn ("M4_HOOK_TABLE_OPENER");

			/* Supply array's 0-element. */
			जर (ds == end_of_buffer_state) {
				mk2data (-end_of_buffer_state);
				yynxt_data[yynxt_curr++] =
					-end_of_buffer_state;
			}
			अन्यथा {
				mk2data (end_of_buffer_state);
				yynxt_data[yynxt_curr++] =
					end_of_buffer_state;
			}

			साठी (i = 1; i < अंक_full_table_rows; ++i) {
				/* Jams are marked by negative of state
				 * number.
				 */
				mk2data (state[i] ? state[i] : -ds);
				yynxt_data[yynxt_curr++] =
					state[i] ? state[i] : -ds;
			}

			जर (gentables) {
				dataflush ();
				outn ("M4_HOOK_TABLE_CONTINUE");
			}
		}

		अन्यथा जर (ctrl.fullspd)
			place_state (state, ds, totaltrans);

		अन्यथा जर (ds == end_of_buffer_state)
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

			साठी (i = 1; i <= targptr; ++i)
				जर (targfreq[i] > comfreq) {
					comfreq = targfreq[i];
					comstate = targstate[i];
				}

			bldtbl (state, ds, totaltrans, comstate, comfreq);
		}
	}

	जर (ctrl.fulltbl) {
		dataend ("M4_HOOK_TABLE_CLOSER");
		outn("/* body */]])");
		जर (tablesext) {
			yytbl_data_compress (yynxt_tbl);
			जर (yytbl_data_fwrite (&tableswr, yynxt_tbl) < 0)
				flexerror (_
					   ("Could not write yynxt_tbl[][]"));
		}
		जर (yynxt_tbl) {
			yytbl_data_destroy (yynxt_tbl);
			yynxt_tbl = 0;
		}
	}

	अन्यथा जर (!ctrl.fullspd) {
		cmptmps ();	/* create compressed template entries */

		/* Create tables for all the states with only one
		 * out-transition.
		 */
		पर्यंत (onesp > 0) {
			mk1tbl (onestate[onesp], onesym[onesp],
				onenext[onesp], onedef[onesp]);
			--onesp;
		}

		mkdeftbl ();
	}


	मुक्त(accset);
	मुक्त(nset);

	परत (yynxt_tbl != रिक्त) ? (yynxt_tbl->td_hilen * आकार(int32_t)) : 0;
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

स्थिर पूर्णांक snstods(पूर्णांक sns[], पूर्णांक numstates, पूर्णांक accset[], पूर्णांक nacc, पूर्णांक hashval, पूर्णांक *newds_addr)
{
	पूर्णांक didsort = 0;
	पूर्णांक i, j;
	पूर्णांक newds, *oldsns;

	साठी (i = 1; i <= lastdfa; ++i)
		जर (hashval == dhash[i]) {
			जर (numstates == dfasiz[i]) {
				oldsns = dss[i];

				जर (!didsort) {
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 */
					क्विक (&sns [1], (माप_प्रकार) numstates, आकार (sns [1]), intcmp);
					didsort = 1;
				}

				साठी (j = 1; j <= numstates; ++j)
					जर (sns[j] != oldsns[j])
						थांबा;

				जर (j > numstates) {
					++dfaeql;
					*newds_addr = i;
					परत 0;
				}

				++hshcol;
			}

			अन्यथा
				++hshsave;
		}

	/* Make a new dfa. */

	जर (++lastdfa >= current_max_dfas)
		increase_max_dfas ();

	newds = lastdfa;

	dss[newds] = allocate_integer_array (numstates + 1);

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	जर (!didsort)
          	क्विक (&sns [1], (माप_प्रकार) numstates, आकार (sns [1]), intcmp);

	साठी (i = 1; i <= numstates; ++i)
		dss[newds][i] = sns[i];

	dfasiz[newds] = numstates;
	dhash[newds] = hashval;

	जर (nacc == 0) {
		जर (reject)
			dfaacc[newds].dfaacc_set = रिक्त;
		अन्यथा
			dfaacc[newds].dfaacc_state = 0;

		accsiz[newds] = 0;
	}

	अन्यथा जर (reject) {
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.
		 */

		क्विक (&accset [1], (माप_प्रकार) nacc, आकार (accset [1]), intcmp);

		dfaacc[newds].dfaacc_set =
			allocate_integer_array (nacc + 1);

		/* Save the accepting set for later */
		साठी (i = 1; i <= nacc; ++i) {
			dfaacc[newds].dfaacc_set[i] = accset[i];

			जर (accset[i] <= अंक_rules)
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

		साठी (i = 1; i <= nacc; ++i)
			जर (accset[i] < j)
				j = accset[i];

		dfaacc[newds].dfaacc_state = j;

		जर (j <= अंक_rules)
			rule_useful[j] = true;
	}

	*newds_addr = newds;

	परत 1;
}


/* symfollowset - follow the symbol transitions one step
 *
 * synopsis
 *    numstates = symfollowset( int ds[current_max_dfa_size], int dsize,
 *				int transsym, int nset[current_max_dfa_size] );
 */

स्थिर पूर्णांक symfollowset(पूर्णांक ds[], पूर्णांक dsize, पूर्णांक transsym, पूर्णांक nset[])
{
	पूर्णांक     ns, tsp, sym, i, j, lenccl, ch, numstates, ccllist;

	numstates = 0;

	साठी (i = 1; i <= dsize; ++i) {	/* for each nfa state ns in the state set of ds */
		ns = ds[i];
		sym = transchar[ns];
		tsp = trans1[ns];

		जर (sym < 0) {	/* it's a character class */
			sym = -sym;
			ccllist = cclmap[sym];
			lenccl = ccllen[sym];

			जर (cclng[sym]) {
				साठी (j = 0; j < lenccl; ++j) {
					/* Loop through negated character
					 * class.
					 */
					ch = ccltbl[ccllist + j];

					जर (ch == 0)
						ch = NUL_ec;

					जर (ch > transsym)
						/* Transsym isn't in negated
						 * ccl.
						 */
						थांबा;

					अन्यथा जर (ch == transsym)
						/* next 2 */
						जा bottom;
				}

				/* Didn't find transsym in ccl. */
				nset[++numstates] = tsp;
			}

			अन्यथा
				साठी (j = 0; j < lenccl; ++j) {
					ch = ccltbl[ccllist + j];

					जर (ch == 0)
						ch = NUL_ec;

					जर (ch > transsym)
						थांबा;
					अन्यथा जर (ch == transsym) {
						nset[++numstates] = tsp;
						थांबा;
					}
				}
		}

		अन्यथा जर (sym == SYM_EPSILON) {	/* do nothing */
		}

		अन्यथा जर (ABS (ecgroup[sym]) == transsym)
			nset[++numstates] = tsp;

	      bottom:;
	}

	परत numstates;
}


/* sympartition - partition characters with same out-transitions
 *
 * synopsis
 *    sympartition( int ds[current_max_dfa_size], int numstates,
 *			int symlist[numecs], int duplist[numecs] );
 */

स्थिर शून्य sympartition(पूर्णांक ds[], पूर्णांक numstates, पूर्णांक symlist[], पूर्णांक duplist[])
{
	पूर्णांक     tch, i, j, k, ns, dupfwd[CSIZE + 1], lenccl, cclp, ich;

	/* Partitioning is done by creating equivalence classes for those
	 * characters which have out-transitions from the given state.  Thus
	 * we are really creating equivalence classes of equivalence classes.
	 */

	साठी (i = 1; i <= numecs; ++i) {	/* initialize equivalence class list */
		duplist[i] = i - 1;
		dupfwd[i] = i + 1;
	}

	duplist[1] = NIL;
	dupfwd[numecs] = NIL;

	साठी (i = 1; i <= numstates; ++i) {
		ns = ds[i];
		tch = transchar[ns];

		जर (tch != SYM_EPSILON) {
			जर (tch < -lastccl || tch >= ctrl.csize) {
				flexfatal (_
					   ("bad transition character detected in sympartition()"));
			}

			जर (tch >= 0) {	/* character transition */
				पूर्णांक     ec = ecgroup[tch];

				mkechar (ec, dupfwd, duplist);
				symlist[ec] = 1;
			}

			अन्यथा {	/* character class */
				tch = -tch;

				lenccl = ccllen[tch];
				cclp = cclmap[tch];
				mkeccl (ccltbl + cclp, lenccl, dupfwd,
					duplist, numecs, NUL_ec);

				जर (cclng[tch]) {
					j = 0;

					साठी (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						जर (ich == 0)
							ich = NUL_ec;

						साठी (++j; j < ich; ++j)
							symlist[j] = 1;
					}

					साठी (++j; j <= numecs; ++j)
						symlist[j] = 1;
				}

				अन्यथा
					साठी (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						जर (ich == 0)
							ich = NUL_ec;

						symlist[ich] = 1;
					}
			}
		}
	}
}
