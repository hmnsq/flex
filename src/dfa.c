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

#include "flexdef.h"
#include "tables.h"

/* declare functions that have forward references */

static void dump_associated_rules(FILE *, 정수);
static void dump_transitions(FILE *, 정수[]);
static 정수  snstods(정수[], 정수, 정수[], 정수, 정수, 정수 *);
static void sympartition(정수[], 정수, 정수[], 정수[]);
static 정수  symfollowset(정수[], 정수, 정수, 정수[]);


/* check_for_backing_up - check a DFA state for backing up
 *
 * synopsis
 *     void check_for_backing_up( int ds, int state[numecs] );
 *
 * ds is the number of the state to check and state[] is its out-transitions,
 * indexed by equivalence class.
 */

static void check_for_backing_up(정수 ds, 정수 state[])
{
	만약 ((reject && !dfaacc[ds].dfaacc_set) || (!reject && !dfaacc[ds].dfaacc_state)) {	/* state is non-accepting */
		++num_backing_up;

		만약 (env.backing_up_report) {
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

static void check_trailing_context(정수 *nfa_states, 정수 num_states, 정수 *accset, 정수 nacc)
{
	정수 i, j;

	위해 (i = 1; i <= num_states; ++i) {
		정수     ns = nfa_states[i];
		정수 type = state_type[ns];
		정수 ar = assoc_rule[ns];

		만약 (type == STATE_NORMAL || rule_type[ar] != RULE_VARIABLE) {	/* do nothing */
		}

		아니면 만약 (type == STATE_TRAILING_CONTEXT) {
			/* Potential trouble.  Scan set of accepting numbers
			 * for the one marking the end of the "head".  We
			 * assume that this looping will be fairly cheap
			 * since it's rare that an accepting number set
			 * is large.
			 */
			위해 (j = 1; j <= nacc; ++j)
				만약 (accset[j] & YY_TRAILING_HEAD_MASK) {
					line_warning (_
						      ("dangerous trailing context"),
						      rule_linenum[ar]);
					반환;
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

static void dump_associated_rules(FILE *file, 정수 ds)
{
	정수 i, j;
	정수 num_associated_rules = 0;
	정수 rule_set[MAX_ASSOC_RULES + 1];
	정수 *dset = dss[ds];
	정수 size = dfasiz[ds];

	위해 (i = 1; i <= size; ++i) {
		정수 rule_num = rule_linenum[assoc_rule[dset[i]]];

		위해 (j = 1; j <= num_associated_rules; ++j)
			만약 (rule_num == rule_set[j])
				break;

		만약 (j > num_associated_rules) {	/* new rule */
			만약 (num_associated_rules < MAX_ASSOC_RULES)
				rule_set[++num_associated_rules] =
					rule_num;
		}
	}

	qsort (&rule_set [1], (size_t) num_associated_rules, sizeof (rule_set [1]), intcmp);

	fprintf (file, _(" associated rule line numbers:"));

	위해 (i = 1; i <= num_associated_rules; ++i) {
		만약 (i % 8 == 1)
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

static void dump_transitions(FILE *file, 정수 state[])
{
	정수 i, ec;
	정수 out_char_set[CSIZE];

	위해 (i = 0; i < ctrl.csize; ++i) {
		ec = ABS (ecgroup[i]);
		out_char_set[i] = state[ec];
	}

	fprintf (file, _(" out-transitions: "));

	list_character_set (file, out_char_set);

	/* now invert the members of the set to get the jam transitions */
	위해 (i = 0; i < ctrl.csize; ++i)
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

static 정수 *epsclosure(정수 *t, 정수 *ns_addr, 정수 accset[], 정수 *nacc_addr, 정수 *hv_addr)
{
	정수     stkpos, ns, tsp;
	정수     numstates = *ns_addr, nacc, hashval, transsym, nfaccnum;
	정수     stkend, nstate;
	static 정수 did_stk_init = false, *stk;

#define MARK_STATE(state) \
do{ trans1[state] = trans1[state] - MARKER_DIFFERENCE;} 동안(0)

#define IS_MARKED(state) (trans1[state] < 0)

#define UNMARK_STATE(state) \
do{ trans1[state] = trans1[state] + MARKER_DIFFERENCE;} 동안(0)

#define CHECK_ACCEPT(state) \
do{ \
nfaccnum = accptnum[state]; \
만약 ( nfaccnum != NIL ) \
accset[++nacc] = nfaccnum; \
}동안(0)

#define DO_REALLOCATION() \
do { \
current_max_dfa_size += MAX_DFA_SIZE_INCREMENT; \
++num_reallocs; \
t = reallocate_integer_array( t, current_max_dfa_size ); \
stk = reallocate_integer_array( stk, current_max_dfa_size ); \
}동안(0) \

#define PUT_ON_STACK(state) \
do { \
만약 ( ++stkend >= current_max_dfa_size ) \
DO_REALLOCATION(); \
stk[stkend] = state; \
MARK_STATE(state); \
}동안(0)

#define ADD_STATE(state) \
do { \
만약 ( ++numstates >= current_max_dfa_size ) \
DO_REALLOCATION(); \
t[numstates] = state; \
hashval += state; \
}동안(0)

#define STACK_STATE(state) \
do { \
PUT_ON_STACK(state); \
CHECK_ACCEPT(state); \
만약 ( nfaccnum != NIL || transchar[state] != SYM_EPSILON ) \
ADD_STATE(state); \
}동안(0)


	만약 (!did_stk_init) {
		stk = allocate_integer_array (current_max_dfa_size);
		did_stk_init = true;
	}

	nacc = stkend = hashval = 0;

	위해 (nstate = 1; nstate <= numstates; ++nstate) {
		ns = t[nstate];

		/* The state could be marked if we've already pushed it onto
		 * the stack.
		 */
		만약 (!IS_MARKED (ns)) {
			PUT_ON_STACK (ns);
			CHECK_ACCEPT (ns);
			hashval += ns;
		}
	}

	위해 (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ns = stk[stkpos];
		transsym = transchar[ns];

		만약 (transsym == SYM_EPSILON) {
			tsp = trans1[ns] + MARKER_DIFFERENCE;

			만약 (tsp != NO_TRANSITION) {
				만약 (!IS_MARKED (tsp))
					STACK_STATE (tsp);

				tsp = trans2[ns];

				만약 (tsp != NO_TRANSITION
				    && !IS_MARKED (tsp))
					STACK_STATE (tsp);
			}
		}
	}

	/* Clear out "visit" markers. */

	위해 (stkpos = 1; stkpos <= stkend; ++stkpos) {
		만약 (IS_MARKED (stk[stkpos]))
			UNMARK_STATE (stk[stkpos]);
		아니면
			flexfatal (_
				   ("consistency check failed in epsclosure()"));
	}

	*ns_addr = numstates;
	*hv_addr = hashval;
	*nacc_addr = nacc;

	반환 t;
}


/* increase_max_dfas - increase the maximum number of DFAs */

void increase_max_dfas (void)
{
	current_max_dfas += MAX_DFAS_INCREMENT;

	++num_reallocs;

	base = reallocate_integer_array (base, current_max_dfas);
	def = reallocate_integer_array (def, current_max_dfas);
	dfasiz = reallocate_integer_array (dfasiz, current_max_dfas);
	accsiz = reallocate_integer_array (accsiz, current_max_dfas);
	dhash = reallocate_integer_array (dhash, current_max_dfas);
	dss = reallocate_int_ptr_array (dss, current_max_dfas);
	dfaacc = reallocate_array(dfaacc, current_max_dfas,
		sizeof(union dfaacc_union));

	만약 (nultrans)
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

size_t ntod (void)
{
	정수    *accset, ds, nacc, newds;
	정수     sym, hashval, numstates, dsize;
	정수     num_full_table_rows=0;	/* used only for -f */
	정수    *nset, *dset;
	정수     targptr, totaltrans, i, comstate, comfreq, targ;
	정수     symlist[CSIZE + 1];
	정수     num_start_states;
	정수     todo_head, todo_next;

	struct yytbl_data *yynxt_tbl = 0;
	flex_int32_t *yynxt_data = 0, yynxt_curr = 0;

	/* Note that the following are indexed by *equivalence classes*
	 * and not by characters.  Since equivalence classes are indexed
	 * beginning with 1, even if the scanner accepts NUL's, this
	 * means that (since every character is potentially in its own
	 * equivalence class) these arrays must have room for indices
	 * from 1 to CSIZE, so their size must be CSIZE + 1.
	 */
	정수     duplist[CSIZE + 1], state[CSIZE + 1];
	정수     targfreq[CSIZE + 1] = {0}, targstate[CSIZE + 1];

	/* accset needs to be large enough to hold all of the rules present
	 * in the input, *plus* their YY_TRAILING_HEAD_MASK variants.
	 */
	accset = allocate_integer_array ((num_rules + 1) * 2);
	nset = allocate_integer_array (current_max_dfa_size);

	/* The "todo" queue is represented by the head, which is the DFA
	 * state currently being processed, and the "next", which is the
	 * next DFA state number available (not in use).  We depend on the
	 * fact that snstods() returns DFA's \in increasing order/, and thus
	 * need only know the bounds of the dfas to be processed.
	 */
	todo_head = todo_next = 0;

	위해 (i = 0; i <= ctrl.csize; ++i) {
		duplist[i] = NIL;
		symlist[i] = false;
	}

	위해 (i = 0; i <= num_rules; ++i)
		accset[i] = NIL;

	만약 (env.trace) {
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
	만약 (ctrl.fulltbl && ecgroup[0] == numecs && is_power_of_2(numecs))
		nultrans = allocate_integer_array (current_max_dfas);

	만약 (ctrl.fullspd) {
		위해 (i = 0; i <= numecs; ++i)
			state[i] = 0;

		place_state (state, 0, 0);
		dfaacc[0].dfaacc_state = 0;
	}

	아니면 만약 (ctrl.fulltbl) {
		만약 (nultrans)
			/* We won't be including NUL's transitions in the
			 * table, so build it for entries from 0 .. numecs - 1.
			 */
			num_full_table_rows = numecs;

		아니면
			/* Take into account the fact that we'll be including
			 * the NUL entries in the transition table.  Build it
			 * from 0 .. numecs.
			 */
			num_full_table_rows = numecs + 1;

		/* Begin generating yy_nxt[][]
		 * This spans the entire LONG function.
		 * This table is tricky because we don't know how big it will be.
		 * So we'll have to realloc() on the way...
		 * we'll wait until we can calculate yynxt_tbl->td_hilen.
		 */
		yynxt_tbl = calloc(1, sizeof (struct yytbl_data));
     
		yytbl_data_init (yynxt_tbl, YYTD_ID_NXT);
		yynxt_tbl->td_hilen = 1;
		yynxt_tbl->td_lolen = (flex_uint32_t) num_full_table_rows;
		yynxt_tbl->td_data = yynxt_data =
		    calloc(yynxt_tbl->td_lolen *
			   yynxt_tbl->td_hilen,
			   sizeof (flex_int32_t));
		yynxt_curr = 0;

		struct packtype_t *ptype = optimize_pack(0);
		/* Note: Used when ctrl.fulltbl is on. Alternately defined elsewhere */
		out_str ("m4_define([[M4_HOOK_NXT_TYPE]], [[%s]])", ptype->name);
		out_dec ("m4_define([[M4_HOOK_NXT_ROWS]], [[%d]])", num_full_table_rows);
		outn ("m4_define([[M4_HOOK_NXT_BODY]], [[m4_dnl");
		outn ("M4_HOOK_TABLE_OPENER");
		만약 (gentables)
			outn ("M4_HOOK_TABLE_OPENER");

		/* Generate 0 entries for state #0. */
		위해 (i = 0; i < num_full_table_rows; ++i) {
			mk2data (0);
			yynxt_data[yynxt_curr++] = 0;
		}

		만약 (gentables) {
			dataflush ();
			outn ("M4_HOOK_TABLE_CONTINUE");
		}
	}

	/* Create the first states. */

	num_start_states = lastsc * 2;

	위해 (i = 1; i <= num_start_states; ++i) {
		numstates = 1;

		/* For each start condition, make one state for the case when
		 * we're at the beginning of the line (the '^' operator) and
		 * one for the case when we're not.
		 */
		만약 (i % 2 == 1)
			nset[numstates] = scset[(i / 2) + 1];
		아니면
			nset[numstates] =
				mkbranch (scbol[i / 2], scset[i / 2]);

		nset = epsclosure (nset, &numstates, accset, &nacc,
				   &hashval);

		만약 (snstods (nset, numstates, accset, nacc, hashval, &ds)) {
			numas += nacc;
			totnst += numstates;
			++todo_next;

			만약 (variable_trailing_context_rules && nacc > 0)
				check_trailing_context (nset, numstates,
							accset, nacc);
		}
	}

	만약 (!ctrl.fullspd) {
		만약 (!snstods (nset, 0, accset, 0, 0, &end_of_buffer_state))
			flexfatal (_
				   ("could not create unique end-of-buffer state"));

		++numas;
		++num_start_states;
		++todo_next;
	}


	동안 (todo_head < todo_next) {
		targptr = 0;
		totaltrans = 0;

		위해 (i = 1; i <= numecs; ++i)
			state[i] = 0;

		ds = ++todo_head;

		dset = dss[ds];
		dsize = dfasiz[ds];

		만약 (env.trace)
			fprintf (stderr, _("state # %d:\n"), ds);

		sympartition (dset, dsize, symlist, duplist);

		위해 (sym = 1; sym <= numecs; ++sym) {
			만약 (symlist[sym]) {
				symlist[sym] = 0;

				만약 (duplist[sym] == NIL) {
					/* Symbol has unique out-transitions. */
					numstates =
						symfollowset (dset, dsize,
							      sym, nset);
					nset = epsclosure (nset,
							   &numstates,
							   accset, &nacc,
							   &hashval);

					만약 (snstods
					    (nset, numstates, accset, nacc,
					     hashval, &newds)) {
						totnst = totnst +
							numstates;
						++todo_next;
						numas += nacc;

						만약 (variable_trailing_context_rules && nacc > 0)
							check_trailing_context
								(nset,
								 numstates,
								 accset,
								 nacc);
					}

					state[sym] = newds;

					만약 (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 newds);

					targfreq[++targptr] = 1;
					targstate[targptr] = newds;
					++numuniq;
				}

				아니면 {
					/* sym's equivalence class has the same
					 * transitions as duplist(sym)'s
					 * equivalence class.
					 */
					targ = state[duplist[sym]];
					state[sym] = targ;

					만약 (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 targ);

					/* Update frequency count for
					 * destination state.
					 */

					i = 0;
					동안 (targstate[++i] != targ) ;

					++targfreq[i];
					++numdup;
				}

				++totaltrans;
				duplist[sym] = NIL;
			}
		}


		numsnpairs += totaltrans;

		만약 (ds > num_start_states)
			check_for_backing_up (ds, state);

		만약 (nultrans) {
			nultrans[ds] = state[NUL_ec];
			state[NUL_ec] = 0;	/* remove transition */
		}

		만약 (ctrl.fulltbl) {

			/* Each time we hit here, it's another td_hilen, so we realloc. */
			yynxt_tbl->td_hilen++;
			yynxt_tbl->td_data = yynxt_data =
				realloc (yynxt_data,
						     yynxt_tbl->td_hilen *
						     yynxt_tbl->td_lolen *
						     sizeof (flex_int32_t));
			만약 (gentables)
				outn ("M4_HOOK_TABLE_OPENER");

			/* Supply array's 0-element. */
			만약 (ds == end_of_buffer_state) {
				mk2data (-end_of_buffer_state);
				yynxt_data[yynxt_curr++] =
					-end_of_buffer_state;
			}
			아니면 {
				mk2data (end_of_buffer_state);
				yynxt_data[yynxt_curr++] =
					end_of_buffer_state;
			}

			위해 (i = 1; i < num_full_table_rows; ++i) {
				/* Jams are marked by negative of state
				 * number.
				 */
				mk2data (state[i] ? state[i] : -ds);
				yynxt_data[yynxt_curr++] =
					state[i] ? state[i] : -ds;
			}

			만약 (gentables) {
				dataflush ();
				outn ("M4_HOOK_TABLE_CONTINUE");
			}
		}

		아니면 만약 (ctrl.fullspd)
			place_state (state, ds, totaltrans);

		아니면 만약 (ds == end_of_buffer_state)
			/* Special case this state to make sure it does what
			 * it's supposed to, i.e., jam on end-of-buffer.
			 */
			stack1 (ds, 0, 0, JAMSTATE);

		아니면 {		/* normal, compressed state */

			/* Determine which destination state is the most
			 * common, and how many transitions to it there are.
			 */

			comfreq = 0;
			comstate = 0;

			위해 (i = 1; i <= targptr; ++i)
				만약 (targfreq[i] > comfreq) {
					comfreq = targfreq[i];
					comstate = targstate[i];
				}

			bldtbl (state, ds, totaltrans, comstate, comfreq);
		}
	}

	만약 (ctrl.fulltbl) {
		dataend ("M4_HOOK_TABLE_CLOSER");
		outn("/* body */]])");
		만약 (tablesext) {
			yytbl_data_compress (yynxt_tbl);
			만약 (yytbl_data_fwrite (&tableswr, yynxt_tbl) < 0)
				flexerror (_
					   ("Could not write yynxt_tbl[][]"));
		}
		만약 (yynxt_tbl) {
			yytbl_data_destroy (yynxt_tbl);
			yynxt_tbl = 0;
		}
	}

	아니면 만약 (!ctrl.fullspd) {
		cmptmps ();	/* create compressed template entries */

		/* Create tables for all the states with only one
		 * out-transition.
		 */
		동안 (onesp > 0) {
			mk1tbl (onestate[onesp], onesym[onesp],
				onenext[onesp], onedef[onesp]);
			--onesp;
		}

		mkdeftbl ();
	}


	free(accset);
	free(nset);

	반환 (yynxt_tbl != NULL) ? (yynxt_tbl->td_hilen * sizeof(int32_t)) : 0;
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

static 정수 snstods(정수 sns[], 정수 numstates, 정수 accset[], 정수 nacc, 정수 hashval, 정수 *newds_addr)
{
	정수 didsort = 0;
	정수 i, j;
	정수 newds, *oldsns;

	위해 (i = 1; i <= lastdfa; ++i)
		만약 (hashval == dhash[i]) {
			만약 (numstates == dfasiz[i]) {
				oldsns = dss[i];

				만약 (!didsort) {
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 */
					qsort (&sns [1], (size_t) numstates, sizeof (sns [1]), intcmp);
					didsort = 1;
				}

				위해 (j = 1; j <= numstates; ++j)
					만약 (sns[j] != oldsns[j])
						break;

				만약 (j > numstates) {
					++dfaeql;
					*newds_addr = i;
					반환 0;
				}

				++hshcol;
			}

			아니면
				++hshsave;
		}

	/* Make a new dfa. */

	만약 (++lastdfa >= current_max_dfas)
		increase_max_dfas ();

	newds = lastdfa;

	dss[newds] = allocate_integer_array (numstates + 1);

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	만약 (!didsort)
          	qsort (&sns [1], (size_t) numstates, sizeof (sns [1]), intcmp);

	위해 (i = 1; i <= numstates; ++i)
		dss[newds][i] = sns[i];

	dfasiz[newds] = numstates;
	dhash[newds] = hashval;

	만약 (nacc == 0) {
		만약 (reject)
			dfaacc[newds].dfaacc_set = NULL;
		아니면
			dfaacc[newds].dfaacc_state = 0;

		accsiz[newds] = 0;
	}

	아니면 만약 (reject) {
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.
		 */

		qsort (&accset [1], (size_t) nacc, sizeof (accset [1]), intcmp);

		dfaacc[newds].dfaacc_set =
			allocate_integer_array (nacc + 1);

		/* Save the accepting set for later */
		위해 (i = 1; i <= nacc; ++i) {
			dfaacc[newds].dfaacc_set[i] = accset[i];

			만약 (accset[i] <= num_rules)
				/* Who knows, perhaps a REJECT can yield
				 * this rule.
				 */
				rule_useful[accset[i]] = true;
		}

		accsiz[newds] = nacc;
	}

	아니면 {
		/* Find lowest numbered rule so the disambiguating rule
		 * will work.
		 */
		j = num_rules + 1;

		위해 (i = 1; i <= nacc; ++i)
			만약 (accset[i] < j)
				j = accset[i];

		dfaacc[newds].dfaacc_state = j;

		만약 (j <= num_rules)
			rule_useful[j] = true;
	}

	*newds_addr = newds;

	반환 1;
}


/* symfollowset - follow the symbol transitions one step
 *
 * synopsis
 *    numstates = symfollowset( int ds[current_max_dfa_size], int dsize,
 *				int transsym, int nset[current_max_dfa_size] );
 */

static 정수 symfollowset(정수 ds[], 정수 dsize, 정수 transsym, 정수 nset[])
{
	정수     ns, tsp, sym, i, j, lenccl, ch, numstates, ccllist;

	numstates = 0;

	위해 (i = 1; i <= dsize; ++i) {	/* for each nfa state ns in the state set of ds */
		ns = ds[i];
		sym = transchar[ns];
		tsp = trans1[ns];

		만약 (sym < 0) {	/* it's a character class */
			sym = -sym;
			ccllist = cclmap[sym];
			lenccl = ccllen[sym];

			만약 (cclng[sym]) {
				위해 (j = 0; j < lenccl; ++j) {
					/* Loop through negated character
					 * class.
					 */
					ch = ccltbl[ccllist + j];

					만약 (ch == 0)
						ch = NUL_ec;

					만약 (ch > transsym)
						/* Transsym isn't in negated
						 * ccl.
						 */
						break;

					아니면 만약 (ch == transsym)
						/* next 2 */
						goto bottom;
				}

				/* Didn't find transsym in ccl. */
				nset[++numstates] = tsp;
			}

			아니면
				위해 (j = 0; j < lenccl; ++j) {
					ch = ccltbl[ccllist + j];

					만약 (ch == 0)
						ch = NUL_ec;

					만약 (ch > transsym)
						break;
					아니면 만약 (ch == transsym) {
						nset[++numstates] = tsp;
						break;
					}
				}
		}

		아니면 만약 (sym == SYM_EPSILON) {	/* do nothing */
		}

		아니면 만약 (ABS (ecgroup[sym]) == transsym)
			nset[++numstates] = tsp;

	      bottom:;
	}

	반환 numstates;
}


/* sympartition - partition characters with same out-transitions
 *
 * synopsis
 *    sympartition( int ds[current_max_dfa_size], int numstates,
 *			int symlist[numecs], int duplist[numecs] );
 */

static void sympartition(정수 ds[], 정수 numstates, 정수 symlist[], 정수 duplist[])
{
	정수     tch, i, j, k, ns, dupfwd[CSIZE + 1], lenccl, cclp, ich;

	/* Partitioning is done by creating equivalence classes for those
	 * characters which have out-transitions from the given state.  Thus
	 * we are really creating equivalence classes of equivalence classes.
	 */

	위해 (i = 1; i <= numecs; ++i) {	/* initialize equivalence class list */
		duplist[i] = i - 1;
		dupfwd[i] = i + 1;
	}

	duplist[1] = NIL;
	dupfwd[numecs] = NIL;

	위해 (i = 1; i <= numstates; ++i) {
		ns = ds[i];
		tch = transchar[ns];

		만약 (tch != SYM_EPSILON) {
			만약 (tch < -lastccl || tch >= ctrl.csize) {
				flexfatal (_
					   ("bad transition character detected in sympartition()"));
			}

			만약 (tch >= 0) {	/* character transition */
				정수     ec = ecgroup[tch];

				mkechar (ec, dupfwd, duplist);
				symlist[ec] = 1;
			}

			아니면 {	/* character class */
				tch = -tch;

				lenccl = ccllen[tch];
				cclp = cclmap[tch];
				mkeccl (ccltbl + cclp, lenccl, dupfwd,
					duplist, numecs, NUL_ec);

				만약 (cclng[tch]) {
					j = 0;

					위해 (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						만약 (ich == 0)
							ich = NUL_ec;

						위해 (++j; j < ich; ++j)
							symlist[j] = 1;
					}

					위해 (++j; j <= numecs; ++j)
						symlist[j] = 1;
				}

				아니면
					위해 (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						만약 (ich == 0)
							ich = NUL_ec;

						symlist[ich] = 1;
					}
			}
		}
	}
}
