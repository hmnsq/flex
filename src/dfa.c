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

#ಅನ್ತರ್ಭಾವ "flexdef.h"
#ಅನ್ತರ್ಭಾವ "tables.h"

/* declare functions that have forward references */

ಸ್ಥಿರ ಶೂನ್ಯ dump_associated_ನಿಯಮಗಳು(FILE *, ಪೂರ್ಣಾಂಕ);
ಸ್ಥಿರ ಶೂನ್ಯ dump_transitions(FILE *, ಪೂರ್ಣಾಂಕ[]);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ  snstods(ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ *);
ಸ್ಥಿರ ಶೂನ್ಯ sympartition(ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ[]);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ  symfollowset(ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ[]);


/* check_for_backing_up - check a DFA state for backing up
 *
 * synopsis
 *     void check_for_backing_up( int ds, int state[numecs] );
 *
 * ds is the number of the state to check and state[] is its out-transitions,
 * indexed by equivalence class.
 */

ಸ್ಥಿರ ಶೂನ್ಯ check_for_backing_ಮೇಲೆ(ಪೂರ್ಣಾಂಕ ds, ಪೂರ್ಣಾಂಕ state[])
{
	ಆದರೆ ((reject && !dfaacc[ds].dfaacc_ಗಣ) || (!reject && !dfaacc[ds].dfaacc_state)) {	/* state is non-accepting */
		++ಅಂಕೆ_backing_ಮೇಲೆ;

		ಆದರೆ (env.backing_ಮೇಲೆ_report) {
			fprintf (ctrl.backing_ಮೇಲೆ_file,
				 _("State #%d is non-accepting -\n"), ds);

			/* identify the state */
			dump_associated_ನಿಯಮಗಳು (ctrl.backing_ಮೇಲೆ_file, ds);

			/* Now identify it further using the out- and
			 * jam-transitions.
			 */
			dump_transitions (ctrl.backing_ಮೇಲೆ_file, state);

			putc ('\n', ctrl.backing_ಮೇಲೆ_file);
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

ಸ್ಥಿರ ಶೂನ್ಯ check_trailing_context(ಪೂರ್ಣಾಂಕ *nfa_ಸ್ಥಿತಿಗಳು, ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ಸ್ಥಿತಿಗಳು, ಪೂರ್ಣಾಂಕ *accset, ಪೂರ್ಣಾಂಕ nacc)
{
	ಪೂರ್ಣಾಂಕ i, j;

	ಗಾಗಿ (i = 1; i <= ಅಂಕೆ_ಸ್ಥಿತಿಗಳು; ++i) {
		ಪೂರ್ಣಾಂಕ     ns = nfa_ಸ್ಥಿತಿಗಳು[i];
		ಪೂರ್ಣಾಂಕ type = state_type[ns];
		ಪೂರ್ಣಾಂಕ ar = assoc_ನಿಯಮ[ns];

		ಆದರೆ (type == STATE_ಸಾಮಾನ್ಯ || ನಿಯಮ_type[ar] != ನಿಯಮ_VARIABLE) {	/* do nothing */
		}

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (type == STATE_TRAILING_CONTEXT) {
			/* Potential trouble.  Scan set of accepting numbers
			 * for the one marking the end of the "head".  We
			 * assume that this looping will be fairly cheap
			 * since it's rare that an accepting number set
			 * is large.
			 */
			ಗಾಗಿ (j = 1; j <= nacc; ++j)
				ಆದರೆ (accset[j] & YY_TRAILING_ತಲೆ_ಮುಖವಾಡ) {
					ಸಾಲು_warning (_
						      ("dangerous trailing context"),
						      ನಿಯಮ_linenum[ar]);
					ಹಿಂತಿರುಗಿ;
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

ಸ್ಥಿರ ಶೂನ್ಯ dump_associated_ನಿಯಮಗಳು(FILE *file, ಪೂರ್ಣಾಂಕ ds)
{
	ಪೂರ್ಣಾಂಕ i, j;
	ಪೂರ್ಣಾಂಕ ಅಂಕೆ_associated_ನಿಯಮಗಳು = 0;
	ಪೂರ್ಣಾಂಕ ನಿಯಮ_ಗಣ[MAX_ASSOC_ನಿಯಮಗಳು + 1];
	ಪೂರ್ಣಾಂಕ *dset = dss[ds];
	ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 = dfasiz[ds];

	ಗಾಗಿ (i = 1; i <= ಗಾತ್ರ_2; ++i) {
		ಪೂರ್ಣಾಂಕ ನಿಯಮ_ಅಂಕೆ = ನಿಯಮ_linenum[assoc_ನಿಯಮ[dset[i]]];

		ಗಾಗಿ (j = 1; j <= ಅಂಕೆ_associated_ನಿಯಮಗಳು; ++j)
			ಆದರೆ (ನಿಯಮ_ಅಂಕೆ == ನಿಯಮ_ಗಣ[j])
				ನಿಲ್ಲಿಸು;

		ಆದರೆ (j > ಅಂಕೆ_associated_ನಿಯಮಗಳು) {	/* new rule */
			ಆದರೆ (ಅಂಕೆ_associated_ನಿಯಮಗಳು < MAX_ASSOC_ನಿಯಮಗಳು)
				ನಿಯಮ_ಗಣ[++ಅಂಕೆ_associated_ನಿಯಮಗಳು] =
					ನಿಯಮ_ಅಂಕೆ;
		}
	}

	qsort (&ನಿಯಮ_ಗಣ [1], (size_t) ಅಂಕೆ_associated_ನಿಯಮಗಳು, ಗಾತ್ರ (ನಿಯಮ_ಗಣ [1]), intcmp);

	fprintf (file, _(" associated rule line numbers:"));

	ಗಾಗಿ (i = 1; i <= ಅಂಕೆ_associated_ನಿಯಮಗಳು; ++i) {
		ಆದರೆ (i % 8 == 1)
			putc ('\n', file);

		fprintf (file, "\t%d", ನಿಯಮ_ಗಣ[i]);
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

ಸ್ಥಿರ ಶೂನ್ಯ dump_transitions(FILE *file, ಪೂರ್ಣಾಂಕ state[])
{
	ಪೂರ್ಣಾಂಕ i, ec;
	ಪೂರ್ಣಾಂಕ ಹೊರಹೋಗು_char_ಗಣ[CSIZE];

	ಗಾಗಿ (i = 0; i < ctrl.csize; ++i) {
		ec = ABS (ecgroup[i]);
		ಹೊರಹೋಗು_char_ಗಣ[i] = state[ec];
	}

	fprintf (file, _(" out-transitions: "));

	list_character_ಗಣ (file, ಹೊರಹೋಗು_char_ಗಣ);

	/* now invert the members of the set to get the jam transitions */
	ಗಾಗಿ (i = 0; i < ctrl.csize; ++i)
		ಹೊರಹೋಗು_char_ಗಣ[i] = !ಹೊರಹೋಗು_char_ಗಣ[i];

	fprintf (file, _("\n jam-transitions: EOF "));

	list_character_ಗಣ (file, ಹೊರಹೋಗು_char_ಗಣ);

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

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ *epsclosure(ಪೂರ್ಣಾಂಕ *t, ಪೂರ್ಣಾಂಕ *ns_addr, ಪೂರ್ಣಾಂಕ accset[], ಪೂರ್ಣಾಂಕ *nacc_addr, ಪೂರ್ಣಾಂಕ *hv_addr)
{
	ಪೂರ್ಣಾಂಕ     stkpos, ns, tsp;
	ಪೂರ್ಣಾಂಕ     numstates = *ns_addr, nacc, hashval, transsym, nfaccnum;
	ಪೂರ್ಣಾಂಕ     stkend, nstate;
	ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ did_stk_init = false, *stk;

#ವ್ಯಾಖ್ಯಾನಿಸು MARK_STATE(state) \
ಮಾಡು{ trans1[state] = trans1[state] - MARKER_DIFFERENCE;} ಆಗ(0)

#ವ್ಯಾಖ್ಯಾನಿಸು IS_MARKED(state) (trans1[state] < 0)

#ವ್ಯಾಖ್ಯಾನಿಸು UNMARK_STATE(state) \
ಮಾಡು{ trans1[state] = trans1[state] + MARKER_DIFFERENCE;} ಆಗ(0)

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_ACCEPT(state) \
ಮಾಡು{ \
nfaccnum = accptnum[state]; \
ಆದರೆ ( nfaccnum != NIL ) \
accset[++nacc] = nfaccnum; \
}ಆಗ(0)

#ವ್ಯಾಖ್ಯಾನಿಸು DO_REALLOCATION() \
ಮಾಡು { \
current_max_dfa_ಗಾತ್ರ += MAX_DFA_ಗಾತ್ರ_INCREMENT; \
++ಅಂಕೆ_reallocs; \
t = reallocate_integer_array( t, current_max_dfa_ಗಾತ್ರ ); \
stk = reallocate_integer_array( stk, current_max_dfa_ಗಾತ್ರ ); \
}ಆಗ(0) \

#ವ್ಯಾಖ್ಯಾನಿಸು PUT_ON_ರಾಶಿ(state) \
ಮಾಡು { \
ಆದರೆ ( ++stkend >= current_max_dfa_ಗಾತ್ರ ) \
DO_REALLOCATION(); \
stk[stkend] = state; \
MARK_STATE(state); \
}ಆಗ(0)

#ವ್ಯಾಖ್ಯಾನಿಸು ಕೂಡಿಸು_STATE(state) \
ಮಾಡು { \
ಆದರೆ ( ++numstates >= current_max_dfa_ಗಾತ್ರ ) \
DO_REALLOCATION(); \
t[numstates] = state; \
hashval += state; \
}ಆಗ(0)

#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_STATE(state) \
ಮಾಡು { \
PUT_ON_ರಾಶಿ(state); \
CHECK_ACCEPT(state); \
ಆದರೆ ( nfaccnum != NIL || transchar[state] != SYM_EPSILON ) \
ಕೂಡಿಸು_STATE(state); \
}ಆಗ(0)


	ಆದರೆ (!did_stk_init) {
		stk = allocate_integer_array (current_max_dfa_ಗಾತ್ರ);
		did_stk_init = true;
	}

	nacc = stkend = hashval = 0;

	ಗಾಗಿ (nstate = 1; nstate <= numstates; ++nstate) {
		ns = t[nstate];

		/* The state could be marked if we've already pushed it onto
		 * the stack.
		 */
		ಆದರೆ (!IS_MARKED (ns)) {
			PUT_ON_ರಾಶಿ (ns);
			CHECK_ACCEPT (ns);
			hashval += ns;
		}
	}

	ಗಾಗಿ (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ns = stk[stkpos];
		transsym = transchar[ns];

		ಆದರೆ (transsym == SYM_EPSILON) {
			tsp = trans1[ns] + MARKER_DIFFERENCE;

			ಆದರೆ (tsp != NO_TRANSITION) {
				ಆದರೆ (!IS_MARKED (tsp))
					ರಾಶಿ_STATE (tsp);

				tsp = trans2[ns];

				ಆದರೆ (tsp != NO_TRANSITION
				    && !IS_MARKED (tsp))
					ರಾಶಿ_STATE (tsp);
			}
		}
	}

	/* Clear out "visit" markers. */

	ಗಾಗಿ (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ಆದರೆ (IS_MARKED (stk[stkpos]))
			UNMARK_STATE (stk[stkpos]);
		ಇಲ್ಲದಿದ್ದರೆ
			flexfatal (_
				   ("consistency check failed in epsclosure()"));
	}

	*ns_addr = numstates;
	*hv_addr = hashval;
	*nacc_addr = nacc;

	ಹಿಂತಿರುಗಿ t;
}


/* increase_max_dfas - increase the maximum number of DFAs */

ಶೂನ್ಯ increase_max_dfas (ಶೂನ್ಯ)
{
	current_max_dfas += MAX_DFAS_INCREMENT;

	++ಅಂಕೆ_reallocs;

	ತಳ = reallocate_integer_array (ತಳ, current_max_dfas);
	def = reallocate_integer_array (def, current_max_dfas);
	dfasiz = reallocate_integer_array (dfasiz, current_max_dfas);
	accsiz = reallocate_integer_array (accsiz, current_max_dfas);
	dhash = reallocate_integer_array (dhash, current_max_dfas);
	dss = reallocate_int_ptr_array (dss, current_max_dfas);
	dfaacc = reallocate_array(dfaacc, current_max_dfas,
		ಗಾತ್ರ(ಒಕ್ಕೂಟ dfaacc_union));

	ಆದರೆ (nultrans)
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

size_t ntod (ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ    *accset, ds, nacc, newds;
	ಪೂರ್ಣಾಂಕ     sym, hashval, numstates, dsize;
	ಪೂರ್ಣಾಂಕ     ಅಂಕೆ_ತುಂಬಿದ_ಕೋಷ್ಟಕ_ಅಡ್ಡಸಾಲುಗಳು=0;	/* used only for -f */
	ಪೂರ್ಣಾಂಕ    *nset, *dset;
	ಪೂರ್ಣಾಂಕ     targptr, totaltrans, i, comstate, comfreq, targ;
	ಪೂರ್ಣಾಂಕ     symlist[CSIZE + 1];
	ಪೂರ್ಣಾಂಕ     ಅಂಕೆ_ಆರಂಭ_ಸ್ಥಿತಿಗಳು;
	ಪೂರ್ಣಾಂಕ     todo_ತಲೆ, todo_ಮುಂದಿನ;

	ರಚನೆ yytbl_ದತ್ತಾಂಶ *yynxt_tbl = 0;
	flex_int32_t *yynxt_ದತ್ತಾಂಶ = 0, yynxt_curr = 0;

	/* Note that the following are indexed by *equivalence classes*
	 * and not by characters.  Since equivalence classes are indexed
	 * beginning with 1, even if the scanner accepts NUL's, this
	 * means that (since every character is potentially in its own
	 * equivalence class) these arrays must have room for indices
	 * from 1 to CSIZE, so their size must be CSIZE + 1.
	 */
	ಪೂರ್ಣಾಂಕ     duplist[CSIZE + 1], state[CSIZE + 1];
	ಪೂರ್ಣಾಂಕ     targfreq[CSIZE + 1] = {0}, targstate[CSIZE + 1];

	/* accset needs to be large enough to hold all of the rules present
	 * in the input, *plus* their YY_TRAILING_HEAD_MASK variants.
	 */
	accset = allocate_integer_array ((ಅಂಕೆ_ನಿಯಮಗಳು + 1) * 2);
	nset = allocate_integer_array (current_max_dfa_ಗಾತ್ರ);

	/* The "todo" queue is represented by the head, which is the DFA
	 * state currently being processed, and the "next", which is the
	 * next DFA state number available (not in use).  We depend on the
	 * fact that snstods() returns DFA's \in increasing order/, and thus
	 * need only know the bounds of the dfas to be processed.
	 */
	todo_ತಲೆ = todo_ಮುಂದಿನ = 0;

	ಗಾಗಿ (i = 0; i <= ctrl.csize; ++i) {
		duplist[i] = NIL;
		symlist[i] = false;
	}

	ಗಾಗಿ (i = 0; i <= ಅಂಕೆ_ನಿಯಮಗಳು; ++i)
		accset[i] = NIL;

	ಆದರೆ (env.trace) {
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
	ಆದರೆ (ctrl.fulltbl && ecgroup[0] == numecs && is_power_ದ_2(numecs))
		nultrans = allocate_integer_array (current_max_dfas);

	ಆದರೆ (ctrl.fullspd) {
		ಗಾಗಿ (i = 0; i <= numecs; ++i)
			state[i] = 0;

		ಇರಿಸು_state (state, 0, 0);
		dfaacc[0].dfaacc_state = 0;
	}

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.fulltbl) {
		ಆದರೆ (nultrans)
			/* We won't be including NUL's transitions in the
			 * table, so build it for entries from 0 .. numecs - 1.
			 */
			ಅಂಕೆ_ತುಂಬಿದ_ಕೋಷ್ಟಕ_ಅಡ್ಡಸಾಲುಗಳು = numecs;

		ಇಲ್ಲದಿದ್ದರೆ
			/* Take into account the fact that we'll be including
			 * the NUL entries in the transition table.  Build it
			 * from 0 .. numecs.
			 */
			ಅಂಕೆ_ತುಂಬಿದ_ಕೋಷ್ಟಕ_ಅಡ್ಡಸಾಲುಗಳು = numecs + 1;

		/* Begin generating yy_nxt[][]
		 * This spans the entire LONG function.
		 * This table is tricky because we don't know how big it will be.
		 * So we'll have to realloc() on the way...
		 * we'll wait until we can calculate yynxt_tbl->td_hilen.
		 */
		yynxt_tbl = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(1, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
     
		yytbl_ದತ್ತಾಂಶ_init (yynxt_tbl, YYTD_ID_NXT);
		yynxt_tbl->td_hilen = 1;
		yynxt_tbl->td_lolen = (flex_uint32_t) ಅಂಕೆ_ತುಂಬಿದ_ಕೋಷ್ಟಕ_ಅಡ್ಡಸಾಲುಗಳು;
		yynxt_tbl->td_ದತ್ತಾಂಶ = yynxt_ದತ್ತಾಂಶ =
		    ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(yynxt_tbl->td_lolen *
			   yynxt_tbl->td_hilen,
			   ಗಾತ್ರ (flex_int32_t));
		yynxt_curr = 0;

		ರಚನೆ packtype_t *ptype = optimize_pack(0);
		/* Note: Used when ctrl.fulltbl is on. Alternately defined elsewhere */
		ಹೊರಹೋಗು_str ("m4_define([[M4_HOOK_NXT_TYPE]], [[%s]])", ptype->name);
		ಹೊರಹೋಗು_dec ("m4_define([[M4_HOOK_NXT_ROWS]], [[%d]])", ಅಂಕೆ_ತುಂಬಿದ_ಕೋಷ್ಟಕ_ಅಡ್ಡಸಾಲುಗಳು);
		outn ("m4_define([[M4_HOOK_NXT_BODY]], [[m4_dnl");
		outn ("M4_HOOK_TABLE_OPENER");
		ಆದರೆ (gentables)
			outn ("M4_HOOK_TABLE_OPENER");

		/* Generate 0 entries for state #0. */
		ಗಾಗಿ (i = 0; i < ಅಂಕೆ_ತುಂಬಿದ_ಕೋಷ್ಟಕ_ಅಡ್ಡಸಾಲುಗಳು; ++i) {
			mk2data (0);
			yynxt_ದತ್ತಾಂಶ[yynxt_curr++] = 0;
		}

		ಆದರೆ (gentables) {
			dataflush ();
			outn ("M4_HOOK_TABLE_CONTINUE");
		}
	}

	/* Create the first states. */

	ಅಂಕೆ_ಆರಂಭ_ಸ್ಥಿತಿಗಳು = lastsc * 2;

	ಗಾಗಿ (i = 1; i <= ಅಂಕೆ_ಆರಂಭ_ಸ್ಥಿತಿಗಳು; ++i) {
		numstates = 1;

		/* For each start condition, make one state for the case when
		 * we're at the beginning of the line (the '^' operator) and
		 * one for the case when we're not.
		 */
		ಆದರೆ (i % 2 == 1)
			nset[numstates] = scset[(i / 2) + 1];
		ಇಲ್ಲದಿದ್ದರೆ
			nset[numstates] =
				mkbranch (scbol[i / 2], scset[i / 2]);

		nset = epsclosure (nset, &numstates, accset, &nacc,
				   &hashval);

		ಆದರೆ (snstods (nset, numstates, accset, nacc, hashval, &ds)) {
			numas += nacc;
			totnst += numstates;
			++todo_ಮುಂದಿನ;

			ಆದರೆ (variable_trailing_context_ನಿಯಮಗಳು && nacc > 0)
				check_trailing_context (nset, numstates,
							accset, nacc);
		}
	}

	ಆದರೆ (!ctrl.fullspd) {
		ಆದರೆ (!snstods (nset, 0, accset, 0, 0, &ಕೊನೆ_ದ_ಬಫರ್_state))
			flexfatal (_
				   ("could not create unique end-of-buffer state"));

		++numas;
		++ಅಂಕೆ_ಆರಂಭ_ಸ್ಥಿತಿಗಳು;
		++todo_ಮುಂದಿನ;
	}


	ಆಗ (todo_ತಲೆ < todo_ಮುಂದಿನ) {
		targptr = 0;
		totaltrans = 0;

		ಗಾಗಿ (i = 1; i <= numecs; ++i)
			state[i] = 0;

		ds = ++todo_ತಲೆ;

		dset = dss[ds];
		dsize = dfasiz[ds];

		ಆದರೆ (env.trace)
			fprintf (stderr, _("state # %d:\n"), ds);

		sympartition (dset, dsize, symlist, duplist);

		ಗಾಗಿ (sym = 1; sym <= numecs; ++sym) {
			ಆದರೆ (symlist[sym]) {
				symlist[sym] = 0;

				ಆದರೆ (duplist[sym] == NIL) {
					/* Symbol has unique out-transitions. */
					numstates =
						symfollowset (dset, dsize,
							      sym, nset);
					nset = epsclosure (nset,
							   &numstates,
							   accset, &nacc,
							   &hashval);

					ಆದರೆ (snstods
					    (nset, numstates, accset, nacc,
					     hashval, &newds)) {
						totnst = totnst +
							numstates;
						++todo_ಮುಂದಿನ;
						numas += nacc;

						ಆದರೆ (variable_trailing_context_ನಿಯಮಗಳು && nacc > 0)
							check_trailing_context
								(nset,
								 numstates,
								 accset,
								 nacc);
					}

					state[sym] = newds;

					ಆದರೆ (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 newds);

					targfreq[++targptr] = 1;
					targstate[targptr] = newds;
					++numuniq;
				}

				ಇಲ್ಲದಿದ್ದರೆ {
					/* sym's equivalence class has the same
					 * transitions as duplist(sym)'s
					 * equivalence class.
					 */
					targ = state[duplist[sym]];
					state[sym] = targ;

					ಆದರೆ (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 targ);

					/* Update frequency count for
					 * destination state.
					 */

					i = 0;
					ಆಗ (targstate[++i] != targ) ;

					++targfreq[i];
					++numdup;
				}

				++totaltrans;
				duplist[sym] = NIL;
			}
		}


		numsnpairs += totaltrans;

		ಆದರೆ (ds > ಅಂಕೆ_ಆರಂಭ_ಸ್ಥಿತಿಗಳು)
			check_for_backing_ಮೇಲೆ (ds, state);

		ಆದರೆ (nultrans) {
			nultrans[ds] = state[NUL_ec];
			state[NUL_ec] = 0;	/* remove transition */
		}

		ಆದರೆ (ctrl.fulltbl) {

			/* Each time we hit here, it's another td_hilen, so we realloc. */
			yynxt_tbl->td_hilen++;
			yynxt_tbl->td_ದತ್ತಾಂಶ = yynxt_ದತ್ತಾಂಶ =
				realloc (yynxt_ದತ್ತಾಂಶ,
						     yynxt_tbl->td_hilen *
						     yynxt_tbl->td_lolen *
						     ಗಾತ್ರ (flex_int32_t));
			ಆದರೆ (gentables)
				outn ("M4_HOOK_TABLE_OPENER");

			/* Supply array's 0-element. */
			ಆದರೆ (ds == ಕೊನೆ_ದ_ಬಫರ್_state) {
				mk2data (-ಕೊನೆ_ದ_ಬಫರ್_state);
				yynxt_ದತ್ತಾಂಶ[yynxt_curr++] =
					-ಕೊನೆ_ದ_ಬಫರ್_state;
			}
			ಇಲ್ಲದಿದ್ದರೆ {
				mk2data (ಕೊನೆ_ದ_ಬಫರ್_state);
				yynxt_ದತ್ತಾಂಶ[yynxt_curr++] =
					ಕೊನೆ_ದ_ಬಫರ್_state;
			}

			ಗಾಗಿ (i = 1; i < ಅಂಕೆ_ತುಂಬಿದ_ಕೋಷ್ಟಕ_ಅಡ್ಡಸಾಲುಗಳು; ++i) {
				/* Jams are marked by negative of state
				 * number.
				 */
				mk2data (state[i] ? state[i] : -ds);
				yynxt_ದತ್ತಾಂಶ[yynxt_curr++] =
					state[i] ? state[i] : -ds;
			}

			ಆದರೆ (gentables) {
				dataflush ();
				outn ("M4_HOOK_TABLE_CONTINUE");
			}
		}

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.fullspd)
			ಇರಿಸು_state (state, ds, totaltrans);

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ds == ಕೊನೆ_ದ_ಬಫರ್_state)
			/* Special case this state to make sure it does what
			 * it's supposed to, i.e., jam on end-of-buffer.
			 */
			stack1 (ds, 0, 0, JAMSTATE);

		ಇಲ್ಲದಿದ್ದರೆ {		/* normal, compressed state */

			/* Determine which destination state is the most
			 * common, and how many transitions to it there are.
			 */

			comfreq = 0;
			comstate = 0;

			ಗಾಗಿ (i = 1; i <= targptr; ++i)
				ಆದರೆ (targfreq[i] > comfreq) {
					comfreq = targfreq[i];
					comstate = targstate[i];
				}

			bldtbl (state, ds, totaltrans, comstate, comfreq);
		}
	}

	ಆದರೆ (ctrl.fulltbl) {
		dataend ("M4_HOOK_TABLE_CLOSER");
		outn("/* body */]])");
		ಆದರೆ (tablesext) {
			yytbl_ದತ್ತಾಂಶ_compress (yynxt_tbl);
			ಆದರೆ (yytbl_ದತ್ತಾಂಶ_fwrite (&tableswr, yynxt_tbl) < 0)
				flexerror (_
					   ("Could not write yynxt_tbl[][]"));
		}
		ಆದರೆ (yynxt_tbl) {
			yytbl_ದತ್ತಾಂಶ_destroy (yynxt_tbl);
			yynxt_tbl = 0;
		}
	}

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!ctrl.fullspd) {
		cmptmps ();	/* create compressed template entries */

		/* Create tables for all the states with only one
		 * out-transition.
		 */
		ಆಗ (onesp > 0) {
			mk1tbl (onestate[onesp], onesym[onesp],
				onenext[onesp], onedef[onesp]);
			--onesp;
		}

		mkdeftbl ();
	}


	ಬಿಡುಗಡೆ(accset);
	ಬಿಡುಗಡೆ(nset);

	ಹಿಂತಿರುಗಿ (yynxt_tbl != ಖಾಲಿ) ? (yynxt_tbl->td_hilen * ಗಾತ್ರ(int32_t)) : 0;
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

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ snstods(ಪೂರ್ಣಾಂಕ sns[], ಪೂರ್ಣಾಂಕ numstates, ಪೂರ್ಣಾಂಕ accset[], ಪೂರ್ಣಾಂಕ nacc, ಪೂರ್ಣಾಂಕ hashval, ಪೂರ್ಣಾಂಕ *newds_addr)
{
	ಪೂರ್ಣಾಂಕ didsort = 0;
	ಪೂರ್ಣಾಂಕ i, j;
	ಪೂರ್ಣಾಂಕ newds, *oldsns;

	ಗಾಗಿ (i = 1; i <= lastdfa; ++i)
		ಆದರೆ (hashval == dhash[i]) {
			ಆದರೆ (numstates == dfasiz[i]) {
				oldsns = dss[i];

				ಆದರೆ (!didsort) {
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 */
					qsort (&sns [1], (size_t) numstates, ಗಾತ್ರ (sns [1]), intcmp);
					didsort = 1;
				}

				ಗಾಗಿ (j = 1; j <= numstates; ++j)
					ಆದರೆ (sns[j] != oldsns[j])
						ನಿಲ್ಲಿಸು;

				ಆದರೆ (j > numstates) {
					++dfaeql;
					*newds_addr = i;
					ಹಿಂತಿರುಗಿ 0;
				}

				++hshcol;
			}

			ಇಲ್ಲದಿದ್ದರೆ
				++hshsave;
		}

	/* Make a new dfa. */

	ಆದರೆ (++lastdfa >= current_max_dfas)
		increase_max_dfas ();

	newds = lastdfa;

	dss[newds] = allocate_integer_array (numstates + 1);

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	ಆದರೆ (!didsort)
          	qsort (&sns [1], (size_t) numstates, ಗಾತ್ರ (sns [1]), intcmp);

	ಗಾಗಿ (i = 1; i <= numstates; ++i)
		dss[newds][i] = sns[i];

	dfasiz[newds] = numstates;
	dhash[newds] = hashval;

	ಆದರೆ (nacc == 0) {
		ಆದರೆ (reject)
			dfaacc[newds].dfaacc_ಗಣ = ಖಾಲಿ;
		ಇಲ್ಲದಿದ್ದರೆ
			dfaacc[newds].dfaacc_state = 0;

		accsiz[newds] = 0;
	}

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (reject) {
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.
		 */

		qsort (&accset [1], (size_t) nacc, ಗಾತ್ರ (accset [1]), intcmp);

		dfaacc[newds].dfaacc_ಗಣ =
			allocate_integer_array (nacc + 1);

		/* Save the accepting set for later */
		ಗಾಗಿ (i = 1; i <= nacc; ++i) {
			dfaacc[newds].dfaacc_ಗಣ[i] = accset[i];

			ಆದರೆ (accset[i] <= ಅಂಕೆ_ನಿಯಮಗಳು)
				/* Who knows, perhaps a REJECT can yield
				 * this rule.
				 */
				ನಿಯಮ_useful[accset[i]] = true;
		}

		accsiz[newds] = nacc;
	}

	ಇಲ್ಲದಿದ್ದರೆ {
		/* Find lowest numbered rule so the disambiguating rule
		 * will work.
		 */
		j = ಅಂಕೆ_ನಿಯಮಗಳು + 1;

		ಗಾಗಿ (i = 1; i <= nacc; ++i)
			ಆದರೆ (accset[i] < j)
				j = accset[i];

		dfaacc[newds].dfaacc_state = j;

		ಆದರೆ (j <= ಅಂಕೆ_ನಿಯಮಗಳು)
			ನಿಯಮ_useful[j] = true;
	}

	*newds_addr = newds;

	ಹಿಂತಿರುಗಿ 1;
}


/* symfollowset - follow the symbol transitions one step
 *
 * synopsis
 *    numstates = symfollowset( int ds[current_max_dfa_size], int dsize,
 *				int transsym, int nset[current_max_dfa_size] );
 */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ symfollowset(ಪೂರ್ಣಾಂಕ ds[], ಪೂರ್ಣಾಂಕ dsize, ಪೂರ್ಣಾಂಕ transsym, ಪೂರ್ಣಾಂಕ nset[])
{
	ಪೂರ್ಣಾಂಕ     ns, tsp, sym, i, j, lenccl, ch, numstates, ccllist;

	numstates = 0;

	ಗಾಗಿ (i = 1; i <= dsize; ++i) {	/* for each nfa state ns in the state set of ds */
		ns = ds[i];
		sym = transchar[ns];
		tsp = trans1[ns];

		ಆದರೆ (sym < 0) {	/* it's a character class */
			sym = -sym;
			ccllist = cclmap[sym];
			lenccl = ccllen[sym];

			ಆದರೆ (cclng[sym]) {
				ಗಾಗಿ (j = 0; j < lenccl; ++j) {
					/* Loop through negated character
					 * class.
					 */
					ch = ccltbl[ccllist + j];

					ಆದರೆ (ch == 0)
						ch = NUL_ec;

					ಆದರೆ (ch > transsym)
						/* Transsym isn't in negated
						 * ccl.
						 */
						ನಿಲ್ಲಿಸು;

					ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ch == transsym)
						/* next 2 */
						ಹೋಗು bottom;
				}

				/* Didn't find transsym in ccl. */
				nset[++numstates] = tsp;
			}

			ಇಲ್ಲದಿದ್ದರೆ
				ಗಾಗಿ (j = 0; j < lenccl; ++j) {
					ch = ccltbl[ccllist + j];

					ಆದರೆ (ch == 0)
						ch = NUL_ec;

					ಆದರೆ (ch > transsym)
						ನಿಲ್ಲಿಸು;
					ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ch == transsym) {
						nset[++numstates] = tsp;
						ನಿಲ್ಲಿಸು;
					}
				}
		}

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (sym == SYM_EPSILON) {	/* do nothing */
		}

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ABS (ecgroup[sym]) == transsym)
			nset[++numstates] = tsp;

	      bottom:;
	}

	ಹಿಂತಿರುಗಿ numstates;
}


/* sympartition - partition characters with same out-transitions
 *
 * synopsis
 *    sympartition( int ds[current_max_dfa_size], int numstates,
 *			int symlist[numecs], int duplist[numecs] );
 */

ಸ್ಥಿರ ಶೂನ್ಯ sympartition(ಪೂರ್ಣಾಂಕ ds[], ಪೂರ್ಣಾಂಕ numstates, ಪೂರ್ಣಾಂಕ symlist[], ಪೂರ್ಣಾಂಕ duplist[])
{
	ಪೂರ್ಣಾಂಕ     tch, i, j, k, ns, dupfwd[CSIZE + 1], lenccl, cclp, ich;

	/* Partitioning is done by creating equivalence classes for those
	 * characters which have out-transitions from the given state.  Thus
	 * we are really creating equivalence classes of equivalence classes.
	 */

	ಗಾಗಿ (i = 1; i <= numecs; ++i) {	/* initialize equivalence class list */
		duplist[i] = i - 1;
		dupfwd[i] = i + 1;
	}

	duplist[1] = NIL;
	dupfwd[numecs] = NIL;

	ಗಾಗಿ (i = 1; i <= numstates; ++i) {
		ns = ds[i];
		tch = transchar[ns];

		ಆದರೆ (tch != SYM_EPSILON) {
			ಆದರೆ (tch < -lastccl || tch >= ctrl.csize) {
				flexfatal (_
					   ("bad transition character detected in sympartition()"));
			}

			ಆದರೆ (tch >= 0) {	/* character transition */
				ಪೂರ್ಣಾಂಕ     ec = ecgroup[tch];

				mkechar (ec, dupfwd, duplist);
				symlist[ec] = 1;
			}

			ಇಲ್ಲದಿದ್ದರೆ {	/* character class */
				tch = -tch;

				lenccl = ccllen[tch];
				cclp = cclmap[tch];
				mkeccl (ccltbl + cclp, lenccl, dupfwd,
					duplist, numecs, NUL_ec);

				ಆದರೆ (cclng[tch]) {
					j = 0;

					ಗಾಗಿ (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						ಆದರೆ (ich == 0)
							ich = NUL_ec;

						ಗಾಗಿ (++j; j < ich; ++j)
							symlist[j] = 1;
					}

					ಗಾಗಿ (++j; j <= numecs; ++j)
						symlist[j] = 1;
				}

				ಇಲ್ಲದಿದ್ದರೆ
					ಗಾಗಿ (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						ಆದರೆ (ich == 0)
							ich = NUL_ec;

						symlist[ich] = 1;
					}
			}
		}
	}
}
