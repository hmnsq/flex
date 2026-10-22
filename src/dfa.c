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

#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tables.h"

/* declare functions that have forward references */

ਸਥਿਰ ਖਾਲੀ dump_associated_ਨਿਯਮਾਂ(FILE *, ਪੂਰਨ);
ਸਥਿਰ ਖਾਲੀ dump_transitions(FILE *, ਪੂਰਨ[]);
ਸਥਿਰ ਪੂਰਨ  snstods(ਪੂਰਨ[], ਪੂਰਨ, ਪੂਰਨ[], ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ *);
ਸਥਿਰ ਖਾਲੀ sympartition(ਪੂਰਨ[], ਪੂਰਨ, ਪੂਰਨ[], ਪੂਰਨ[]);
ਸਥਿਰ ਪੂਰਨ  symfollowset(ਪੂਰਨ[], ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ[]);


/* check_for_backing_up - check a DFA state for backing up
 *
 * synopsis
 *     void check_for_backing_up( int ds, int state[numecs] );
 *
 * ds is the number of the state to check and state[] is its out-transitions,
 * indexed by equivalence class.
 */

ਸਥਿਰ ਖਾਲੀ check_for_backing_ਉੱਪਰ(ਪੂਰਨ ds, ਪੂਰਨ state[])
{
	ਜੇ ((reject && !dfaacc[ds].dfaacc_ਸੈੱਟ) || (!reject && !dfaacc[ds].dfaacc_state)) {	/* state is non-accepting */
		++ਅੰਕ_backing_ਉੱਪਰ;

		ਜੇ (env.backing_ਉੱਪਰ_report) {
			fprintf (ctrl.backing_ਉੱਪਰ_file,
				 _("State #%d is non-accepting -\n"), ds);

			/* identify the state */
			dump_associated_ਨਿਯਮਾਂ (ctrl.backing_ਉੱਪਰ_file, ds);

			/* Now identify it further using the out- and
			 * jam-transitions.
			 */
			dump_transitions (ctrl.backing_ਉੱਪਰ_file, state);

			putc ('\n', ctrl.backing_ਉੱਪਰ_file);
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

ਸਥਿਰ ਖਾਲੀ check_trailing_context(ਪੂਰਨ *nfa_ਹਾਲਤਾਂ, ਪੂਰਨ ਅੰਕ_ਹਾਲਤਾਂ, ਪੂਰਨ *accset, ਪੂਰਨ nacc)
{
	ਪੂਰਨ i, j;

	ਲਈ (i = 1; i <= ਅੰਕ_ਹਾਲਤਾਂ; ++i) {
		ਪੂਰਨ     ns = nfa_ਹਾਲਤਾਂ[i];
		ਪੂਰਨ type = state_type[ns];
		ਪੂਰਨ ar = assoc_ਨਿਯਮ[ns];

		ਜੇ (type == STATE_ਸਾਧਾਰਨ || ਨਿਯਮ_type[ar] != ਨਿਯਮ_VARIABLE) {	/* do nothing */
		}

		ਨਹੀਂਤਾਂ ਜੇ (type == STATE_TRAILING_CONTEXT) {
			/* Potential trouble.  Scan set of accepting numbers
			 * for the one marking the end of the "head".  We
			 * assume that this looping will be fairly cheap
			 * since it's rare that an accepting number set
			 * is large.
			 */
			ਲਈ (j = 1; j <= nacc; ++j)
				ਜੇ (accset[j] & YY_TRAILING_ਸਿਰ_ਨਕਾਬ) {
					ਸਤਰ_warning (_
						      ("dangerous trailing context"),
						      ਨਿਯਮ_linenum[ar]);
					ਵਾਪਸ;
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

ਸਥਿਰ ਖਾਲੀ dump_associated_ਨਿਯਮਾਂ(FILE *file, ਪੂਰਨ ds)
{
	ਪੂਰਨ i, j;
	ਪੂਰਨ ਅੰਕ_associated_ਨਿਯਮਾਂ = 0;
	ਪੂਰਨ ਨਿਯਮ_ਸੈੱਟ[MAX_ASSOC_ਨਿਯਮਾਂ + 1];
	ਪੂਰਨ *dset = dss[ds];
	ਪੂਰਨ ਮਾਪ = dfasiz[ds];

	ਲਈ (i = 1; i <= ਮਾਪ; ++i) {
		ਪੂਰਨ ਨਿਯਮ_ਅੰਕ = ਨਿਯਮ_linenum[assoc_ਨਿਯਮ[dset[i]]];

		ਲਈ (j = 1; j <= ਅੰਕ_associated_ਨਿਯਮਾਂ; ++j)
			ਜੇ (ਨਿਯਮ_ਅੰਕ == ਨਿਯਮ_ਸੈੱਟ[j])
				ਰੋਕੋ;

		ਜੇ (j > ਅੰਕ_associated_ਨਿਯਮਾਂ) {	/* new rule */
			ਜੇ (ਅੰਕ_associated_ਨਿਯਮਾਂ < MAX_ASSOC_ਨਿਯਮਾਂ)
				ਨਿਯਮ_ਸੈੱਟ[++ਅੰਕ_associated_ਨਿਯਮਾਂ] =
					ਨਿਯਮ_ਅੰਕ;
		}
	}

	qsort (&ਨਿਯਮ_ਸੈੱਟ [1], (size_t) ਅੰਕ_associated_ਨਿਯਮਾਂ, ਆਕਾਰ (ਨਿਯਮ_ਸੈੱਟ [1]), intcmp);

	fprintf (file, _(" associated rule line numbers:"));

	ਲਈ (i = 1; i <= ਅੰਕ_associated_ਨਿਯਮਾਂ; ++i) {
		ਜੇ (i % 8 == 1)
			putc ('\n', file);

		fprintf (file, "\t%d", ਨਿਯਮ_ਸੈੱਟ[i]);
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

ਸਥਿਰ ਖਾਲੀ dump_transitions(FILE *file, ਪੂਰਨ state[])
{
	ਪੂਰਨ i, ec;
	ਪੂਰਨ ਬਾਹਰਲਾ_char_ਸੈੱਟ[CSIZE];

	ਲਈ (i = 0; i < ctrl.csize; ++i) {
		ec = ABS (ecgroup[i]);
		ਬਾਹਰਲਾ_char_ਸੈੱਟ[i] = state[ec];
	}

	fprintf (file, _(" out-transitions: "));

	list_character_ਸੈੱਟ (file, ਬਾਹਰਲਾ_char_ਸੈੱਟ);

	/* now invert the members of the set to get the jam transitions */
	ਲਈ (i = 0; i < ctrl.csize; ++i)
		ਬਾਹਰਲਾ_char_ਸੈੱਟ[i] = !ਬਾਹਰਲਾ_char_ਸੈੱਟ[i];

	fprintf (file, _("\n jam-transitions: EOF "));

	list_character_ਸੈੱਟ (file, ਬਾਹਰਲਾ_char_ਸੈੱਟ);

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

ਸਥਿਰ ਪੂਰਨ *epsclosure(ਪੂਰਨ *t, ਪੂਰਨ *ns_addr, ਪੂਰਨ accset[], ਪੂਰਨ *nacc_addr, ਪੂਰਨ *hv_addr)
{
	ਪੂਰਨ     stkpos, ns, tsp;
	ਪੂਰਨ     numstates = *ns_addr, nacc, hashval, transsym, nfaccnum;
	ਪੂਰਨ     stkend, nstate;
	ਸਥਿਰ ਪੂਰਨ did_stk_init = false, *stk;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MARK_STATE(state) \
ਕਰੋ{ trans1[state] = trans1[state] - MARKER_DIFFERENCE;} ਜਦੋਂ(0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_MARKED(state) (trans1[state] < 0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UNMARK_STATE(state) \
ਕਰੋ{ trans1[state] = trans1[state] + MARKER_DIFFERENCE;} ਜਦੋਂ(0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_ACCEPT(state) \
ਕਰੋ{ \
nfaccnum = accptnum[state]; \
ਜੇ ( nfaccnum != NIL ) \
accset[++nacc] = nfaccnum; \
}ਜਦੋਂ(0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DO_REALLOCATION() \
ਕਰੋ { \
current_max_dfa_ਮਾਪ += MAX_DFA_ਮਾਪ_INCREMENT; \
++ਅੰਕ_reallocs; \
t = reallocate_integer_array( t, current_max_dfa_ਮਾਪ ); \
stk = reallocate_integer_array( stk, current_max_dfa_ਮਾਪ ); \
}ਜਦੋਂ(0) \

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PUT_ON_ਢੇਰ(state) \
ਕਰੋ { \
ਜੇ ( ++stkend >= current_max_dfa_ਮਾਪ ) \
DO_REALLOCATION(); \
stk[stkend] = state; \
MARK_STATE(state); \
}ਜਦੋਂ(0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਜੋੜੋ_STATE(state) \
ਕਰੋ { \
ਜੇ ( ++numstates >= current_max_dfa_ਮਾਪ ) \
DO_REALLOCATION(); \
t[numstates] = state; \
hashval += state; \
}ਜਦੋਂ(0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_STATE(state) \
ਕਰੋ { \
PUT_ON_ਢੇਰ(state); \
CHECK_ACCEPT(state); \
ਜੇ ( nfaccnum != NIL || transchar[state] != SYM_EPSILON ) \
ਜੋੜੋ_STATE(state); \
}ਜਦੋਂ(0)


	ਜੇ (!did_stk_init) {
		stk = allocate_integer_array (current_max_dfa_ਮਾਪ);
		did_stk_init = true;
	}

	nacc = stkend = hashval = 0;

	ਲਈ (nstate = 1; nstate <= numstates; ++nstate) {
		ns = t[nstate];

		/* The state could be marked if we've already pushed it onto
		 * the stack.
		 */
		ਜੇ (!IS_MARKED (ns)) {
			PUT_ON_ਢੇਰ (ns);
			CHECK_ACCEPT (ns);
			hashval += ns;
		}
	}

	ਲਈ (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ns = stk[stkpos];
		transsym = transchar[ns];

		ਜੇ (transsym == SYM_EPSILON) {
			tsp = trans1[ns] + MARKER_DIFFERENCE;

			ਜੇ (tsp != NO_TRANSITION) {
				ਜੇ (!IS_MARKED (tsp))
					ਢੇਰ_STATE (tsp);

				tsp = trans2[ns];

				ਜੇ (tsp != NO_TRANSITION
				    && !IS_MARKED (tsp))
					ਢੇਰ_STATE (tsp);
			}
		}
	}

	/* Clear out "visit" markers. */

	ਲਈ (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ਜੇ (IS_MARKED (stk[stkpos]))
			UNMARK_STATE (stk[stkpos]);
		ਨਹੀਂਤਾਂ
			flexfatal (_
				   ("consistency check failed in epsclosure()"));
	}

	*ns_addr = numstates;
	*hv_addr = hashval;
	*nacc_addr = nacc;

	ਵਾਪਸ t;
}


/* increase_max_dfas - increase the maximum number of DFAs */

ਖਾਲੀ increase_max_dfas (ਖਾਲੀ)
{
	current_max_dfas += MAX_DFAS_INCREMENT;

	++ਅੰਕ_reallocs;

	ਅਧਾਰ = reallocate_integer_array (ਅਧਾਰ, current_max_dfas);
	def = reallocate_integer_array (def, current_max_dfas);
	dfasiz = reallocate_integer_array (dfasiz, current_max_dfas);
	accsiz = reallocate_integer_array (accsiz, current_max_dfas);
	dhash = reallocate_integer_array (dhash, current_max_dfas);
	dss = reallocate_int_ptr_array (dss, current_max_dfas);
	dfaacc = reallocate_array(dfaacc, current_max_dfas,
		ਆਕਾਰ(ਸੰਘ dfaacc_union));

	ਜੇ (nultrans)
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

size_t ntod (ਖਾਲੀ)
{
	ਪੂਰਨ    *accset, ds, nacc, newds;
	ਪੂਰਨ     sym, hashval, numstates, dsize;
	ਪੂਰਨ     ਅੰਕ_ਭਰਿਆ_ਸਾਰਣੀ_ਪੰਕਤੀਆਂ=0;	/* used only for -f */
	ਪੂਰਨ    *nset, *dset;
	ਪੂਰਨ     targptr, totaltrans, i, comstate, comfreq, targ;
	ਪੂਰਨ     symlist[CSIZE + 1];
	ਪੂਰਨ     ਅੰਕ_ਸ਼ੁਰੂ_ਹਾਲਤਾਂ;
	ਪੂਰਨ     todo_ਸਿਰ, todo_ਅਗਲਾ;

	ਬਣਤਰ yytbl_ਅੰਕੜੇ *yynxt_tbl = 0;
	flex_int32_t *yynxt_ਅੰਕੜੇ = 0, yynxt_curr = 0;

	/* Note that the following are indexed by *equivalence classes*
	 * and not by characters.  Since equivalence classes are indexed
	 * beginning with 1, even if the scanner accepts NUL's, this
	 * means that (since every character is potentially in its own
	 * equivalence class) these arrays must have room for indices
	 * from 1 to CSIZE, so their size must be CSIZE + 1.
	 */
	ਪੂਰਨ     duplist[CSIZE + 1], state[CSIZE + 1];
	ਪੂਰਨ     targfreq[CSIZE + 1] = {0}, targstate[CSIZE + 1];

	/* accset needs to be large enough to hold all of the rules present
	 * in the input, *plus* their YY_TRAILING_HEAD_MASK variants.
	 */
	accset = allocate_integer_array ((ਅੰਕ_ਨਿਯਮਾਂ + 1) * 2);
	nset = allocate_integer_array (current_max_dfa_ਮਾਪ);

	/* The "todo" queue is represented by the head, which is the DFA
	 * state currently being processed, and the "next", which is the
	 * next DFA state number available (not in use).  We depend on the
	 * fact that snstods() returns DFA's \in increasing order/, and thus
	 * need only know the bounds of the dfas to be processed.
	 */
	todo_ਸਿਰ = todo_ਅਗਲਾ = 0;

	ਲਈ (i = 0; i <= ctrl.csize; ++i) {
		duplist[i] = NIL;
		symlist[i] = false;
	}

	ਲਈ (i = 0; i <= ਅੰਕ_ਨਿਯਮਾਂ; ++i)
		accset[i] = NIL;

	ਜੇ (env.trace) {
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
	ਜੇ (ctrl.fulltbl && ecgroup[0] == numecs && is_power_ਦਾ_2(numecs))
		nultrans = allocate_integer_array (current_max_dfas);

	ਜੇ (ctrl.fullspd) {
		ਲਈ (i = 0; i <= numecs; ++i)
			state[i] = 0;

		ਰੱਖੋ_state (state, 0, 0);
		dfaacc[0].dfaacc_state = 0;
	}

	ਨਹੀਂਤਾਂ ਜੇ (ctrl.fulltbl) {
		ਜੇ (nultrans)
			/* We won't be including NUL's transitions in the
			 * table, so build it for entries from 0 .. numecs - 1.
			 */
			ਅੰਕ_ਭਰਿਆ_ਸਾਰਣੀ_ਪੰਕਤੀਆਂ = numecs;

		ਨਹੀਂਤਾਂ
			/* Take into account the fact that we'll be including
			 * the NUL entries in the transition table.  Build it
			 * from 0 .. numecs.
			 */
			ਅੰਕ_ਭਰਿਆ_ਸਾਰਣੀ_ਪੰਕਤੀਆਂ = numecs + 1;

		/* Begin generating yy_nxt[][]
		 * This spans the entire LONG function.
		 * This table is tricky because we don't know how big it will be.
		 * So we'll have to realloc() on the way...
		 * we'll wait until we can calculate yynxt_tbl->td_hilen.
		 */
		yynxt_tbl = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(1, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
     
		yytbl_ਅੰਕੜੇ_init (yynxt_tbl, YYTD_ID_NXT);
		yynxt_tbl->td_hilen = 1;
		yynxt_tbl->td_lolen = (flex_uint32_t) ਅੰਕ_ਭਰਿਆ_ਸਾਰਣੀ_ਪੰਕਤੀਆਂ;
		yynxt_tbl->td_ਅੰਕੜੇ = yynxt_ਅੰਕੜੇ =
		    ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(yynxt_tbl->td_lolen *
			   yynxt_tbl->td_hilen,
			   ਆਕਾਰ (flex_int32_t));
		yynxt_curr = 0;

		ਬਣਤਰ packtype_t *ptype = optimize_pack(0);
		/* Note: Used when ctrl.fulltbl is on. Alternately defined elsewhere */
		ਬਾਹਰਲਾ_str ("m4_define([[M4_HOOK_NXT_TYPE]], [[%s]])", ptype->name);
		ਬਾਹਰਲਾ_dec ("m4_define([[M4_HOOK_NXT_ROWS]], [[%d]])", ਅੰਕ_ਭਰਿਆ_ਸਾਰਣੀ_ਪੰਕਤੀਆਂ);
		outn ("m4_define([[M4_HOOK_NXT_BODY]], [[m4_dnl");
		outn ("M4_HOOK_TABLE_OPENER");
		ਜੇ (gentables)
			outn ("M4_HOOK_TABLE_OPENER");

		/* Generate 0 entries for state #0. */
		ਲਈ (i = 0; i < ਅੰਕ_ਭਰਿਆ_ਸਾਰਣੀ_ਪੰਕਤੀਆਂ; ++i) {
			mk2data (0);
			yynxt_ਅੰਕੜੇ[yynxt_curr++] = 0;
		}

		ਜੇ (gentables) {
			dataflush ();
			outn ("M4_HOOK_TABLE_CONTINUE");
		}
	}

	/* Create the first states. */

	ਅੰਕ_ਸ਼ੁਰੂ_ਹਾਲਤਾਂ = lastsc * 2;

	ਲਈ (i = 1; i <= ਅੰਕ_ਸ਼ੁਰੂ_ਹਾਲਤਾਂ; ++i) {
		numstates = 1;

		/* For each start condition, make one state for the case when
		 * we're at the beginning of the line (the '^' operator) and
		 * one for the case when we're not.
		 */
		ਜੇ (i % 2 == 1)
			nset[numstates] = scset[(i / 2) + 1];
		ਨਹੀਂਤਾਂ
			nset[numstates] =
				mkbranch (scbol[i / 2], scset[i / 2]);

		nset = epsclosure (nset, &numstates, accset, &nacc,
				   &hashval);

		ਜੇ (snstods (nset, numstates, accset, nacc, hashval, &ds)) {
			numas += nacc;
			totnst += numstates;
			++todo_ਅਗਲਾ;

			ਜੇ (variable_trailing_context_ਨਿਯਮਾਂ && nacc > 0)
				check_trailing_context (nset, numstates,
							accset, nacc);
		}
	}

	ਜੇ (!ctrl.fullspd) {
		ਜੇ (!snstods (nset, 0, accset, 0, 0, &ਸਿਰਾ_ਦਾ_ਬਫਰ_state))
			flexfatal (_
				   ("could not create unique end-of-buffer state"));

		++numas;
		++ਅੰਕ_ਸ਼ੁਰੂ_ਹਾਲਤਾਂ;
		++todo_ਅਗਲਾ;
	}


	ਜਦੋਂ (todo_ਸਿਰ < todo_ਅਗਲਾ) {
		targptr = 0;
		totaltrans = 0;

		ਲਈ (i = 1; i <= numecs; ++i)
			state[i] = 0;

		ds = ++todo_ਸਿਰ;

		dset = dss[ds];
		dsize = dfasiz[ds];

		ਜੇ (env.trace)
			fprintf (stderr, _("state # %d:\n"), ds);

		sympartition (dset, dsize, symlist, duplist);

		ਲਈ (sym = 1; sym <= numecs; ++sym) {
			ਜੇ (symlist[sym]) {
				symlist[sym] = 0;

				ਜੇ (duplist[sym] == NIL) {
					/* Symbol has unique out-transitions. */
					numstates =
						symfollowset (dset, dsize,
							      sym, nset);
					nset = epsclosure (nset,
							   &numstates,
							   accset, &nacc,
							   &hashval);

					ਜੇ (snstods
					    (nset, numstates, accset, nacc,
					     hashval, &newds)) {
						totnst = totnst +
							numstates;
						++todo_ਅਗਲਾ;
						numas += nacc;

						ਜੇ (variable_trailing_context_ਨਿਯਮਾਂ && nacc > 0)
							check_trailing_context
								(nset,
								 numstates,
								 accset,
								 nacc);
					}

					state[sym] = newds;

					ਜੇ (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 newds);

					targfreq[++targptr] = 1;
					targstate[targptr] = newds;
					++numuniq;
				}

				ਨਹੀਂਤਾਂ {
					/* sym's equivalence class has the same
					 * transitions as duplist(sym)'s
					 * equivalence class.
					 */
					targ = state[duplist[sym]];
					state[sym] = targ;

					ਜੇ (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 targ);

					/* Update frequency count for
					 * destination state.
					 */

					i = 0;
					ਜਦੋਂ (targstate[++i] != targ) ;

					++targfreq[i];
					++numdup;
				}

				++totaltrans;
				duplist[sym] = NIL;
			}
		}


		numsnpairs += totaltrans;

		ਜੇ (ds > ਅੰਕ_ਸ਼ੁਰੂ_ਹਾਲਤਾਂ)
			check_for_backing_ਉੱਪਰ (ds, state);

		ਜੇ (nultrans) {
			nultrans[ds] = state[NUL_ec];
			state[NUL_ec] = 0;	/* remove transition */
		}

		ਜੇ (ctrl.fulltbl) {

			/* Each time we hit here, it's another td_hilen, so we realloc. */
			yynxt_tbl->td_hilen++;
			yynxt_tbl->td_ਅੰਕੜੇ = yynxt_ਅੰਕੜੇ =
				realloc (yynxt_ਅੰਕੜੇ,
						     yynxt_tbl->td_hilen *
						     yynxt_tbl->td_lolen *
						     ਆਕਾਰ (flex_int32_t));
			ਜੇ (gentables)
				outn ("M4_HOOK_TABLE_OPENER");

			/* Supply array's 0-element. */
			ਜੇ (ds == ਸਿਰਾ_ਦਾ_ਬਫਰ_state) {
				mk2data (-ਸਿਰਾ_ਦਾ_ਬਫਰ_state);
				yynxt_ਅੰਕੜੇ[yynxt_curr++] =
					-ਸਿਰਾ_ਦਾ_ਬਫਰ_state;
			}
			ਨਹੀਂਤਾਂ {
				mk2data (ਸਿਰਾ_ਦਾ_ਬਫਰ_state);
				yynxt_ਅੰਕੜੇ[yynxt_curr++] =
					ਸਿਰਾ_ਦਾ_ਬਫਰ_state;
			}

			ਲਈ (i = 1; i < ਅੰਕ_ਭਰਿਆ_ਸਾਰਣੀ_ਪੰਕਤੀਆਂ; ++i) {
				/* Jams are marked by negative of state
				 * number.
				 */
				mk2data (state[i] ? state[i] : -ds);
				yynxt_ਅੰਕੜੇ[yynxt_curr++] =
					state[i] ? state[i] : -ds;
			}

			ਜੇ (gentables) {
				dataflush ();
				outn ("M4_HOOK_TABLE_CONTINUE");
			}
		}

		ਨਹੀਂਤਾਂ ਜੇ (ctrl.fullspd)
			ਰੱਖੋ_state (state, ds, totaltrans);

		ਨਹੀਂਤਾਂ ਜੇ (ds == ਸਿਰਾ_ਦਾ_ਬਫਰ_state)
			/* Special case this state to make sure it does what
			 * it's supposed to, i.e., jam on end-of-buffer.
			 */
			stack1 (ds, 0, 0, JAMSTATE);

		ਨਹੀਂਤਾਂ {		/* normal, compressed state */

			/* Determine which destination state is the most
			 * common, and how many transitions to it there are.
			 */

			comfreq = 0;
			comstate = 0;

			ਲਈ (i = 1; i <= targptr; ++i)
				ਜੇ (targfreq[i] > comfreq) {
					comfreq = targfreq[i];
					comstate = targstate[i];
				}

			bldtbl (state, ds, totaltrans, comstate, comfreq);
		}
	}

	ਜੇ (ctrl.fulltbl) {
		dataend ("M4_HOOK_TABLE_CLOSER");
		outn("/* body */]])");
		ਜੇ (tablesext) {
			yytbl_ਅੰਕੜੇ_compress (yynxt_tbl);
			ਜੇ (yytbl_ਅੰਕੜੇ_fwrite (&tableswr, yynxt_tbl) < 0)
				flexerror (_
					   ("Could not write yynxt_tbl[][]"));
		}
		ਜੇ (yynxt_tbl) {
			yytbl_ਅੰਕੜੇ_destroy (yynxt_tbl);
			yynxt_tbl = 0;
		}
	}

	ਨਹੀਂਤਾਂ ਜੇ (!ctrl.fullspd) {
		cmptmps ();	/* create compressed template entries */

		/* Create tables for all the states with only one
		 * out-transition.
		 */
		ਜਦੋਂ (onesp > 0) {
			mk1tbl (onestate[onesp], onesym[onesp],
				onenext[onesp], onedef[onesp]);
			--onesp;
		}

		mkdeftbl ();
	}


	ਮੁਕਤ(accset);
	ਮੁਕਤ(nset);

	ਵਾਪਸ (yynxt_tbl != ਨਿਰਾ) ? (yynxt_tbl->td_hilen * ਆਕਾਰ(int32_t)) : 0;
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

ਸਥਿਰ ਪੂਰਨ snstods(ਪੂਰਨ sns[], ਪੂਰਨ numstates, ਪੂਰਨ accset[], ਪੂਰਨ nacc, ਪੂਰਨ hashval, ਪੂਰਨ *newds_addr)
{
	ਪੂਰਨ didsort = 0;
	ਪੂਰਨ i, j;
	ਪੂਰਨ newds, *oldsns;

	ਲਈ (i = 1; i <= lastdfa; ++i)
		ਜੇ (hashval == dhash[i]) {
			ਜੇ (numstates == dfasiz[i]) {
				oldsns = dss[i];

				ਜੇ (!didsort) {
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 */
					qsort (&sns [1], (size_t) numstates, ਆਕਾਰ (sns [1]), intcmp);
					didsort = 1;
				}

				ਲਈ (j = 1; j <= numstates; ++j)
					ਜੇ (sns[j] != oldsns[j])
						ਰੋਕੋ;

				ਜੇ (j > numstates) {
					++dfaeql;
					*newds_addr = i;
					ਵਾਪਸ 0;
				}

				++hshcol;
			}

			ਨਹੀਂਤਾਂ
				++hshsave;
		}

	/* Make a new dfa. */

	ਜੇ (++lastdfa >= current_max_dfas)
		increase_max_dfas ();

	newds = lastdfa;

	dss[newds] = allocate_integer_array (numstates + 1);

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	ਜੇ (!didsort)
          	qsort (&sns [1], (size_t) numstates, ਆਕਾਰ (sns [1]), intcmp);

	ਲਈ (i = 1; i <= numstates; ++i)
		dss[newds][i] = sns[i];

	dfasiz[newds] = numstates;
	dhash[newds] = hashval;

	ਜੇ (nacc == 0) {
		ਜੇ (reject)
			dfaacc[newds].dfaacc_ਸੈੱਟ = ਨਿਰਾ;
		ਨਹੀਂਤਾਂ
			dfaacc[newds].dfaacc_state = 0;

		accsiz[newds] = 0;
	}

	ਨਹੀਂਤਾਂ ਜੇ (reject) {
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.
		 */

		qsort (&accset [1], (size_t) nacc, ਆਕਾਰ (accset [1]), intcmp);

		dfaacc[newds].dfaacc_ਸੈੱਟ =
			allocate_integer_array (nacc + 1);

		/* Save the accepting set for later */
		ਲਈ (i = 1; i <= nacc; ++i) {
			dfaacc[newds].dfaacc_ਸੈੱਟ[i] = accset[i];

			ਜੇ (accset[i] <= ਅੰਕ_ਨਿਯਮਾਂ)
				/* Who knows, perhaps a REJECT can yield
				 * this rule.
				 */
				ਨਿਯਮ_useful[accset[i]] = true;
		}

		accsiz[newds] = nacc;
	}

	ਨਹੀਂਤਾਂ {
		/* Find lowest numbered rule so the disambiguating rule
		 * will work.
		 */
		j = ਅੰਕ_ਨਿਯਮਾਂ + 1;

		ਲਈ (i = 1; i <= nacc; ++i)
			ਜੇ (accset[i] < j)
				j = accset[i];

		dfaacc[newds].dfaacc_state = j;

		ਜੇ (j <= ਅੰਕ_ਨਿਯਮਾਂ)
			ਨਿਯਮ_useful[j] = true;
	}

	*newds_addr = newds;

	ਵਾਪਸ 1;
}


/* symfollowset - follow the symbol transitions one step
 *
 * synopsis
 *    numstates = symfollowset( int ds[current_max_dfa_size], int dsize,
 *				int transsym, int nset[current_max_dfa_size] );
 */

ਸਥਿਰ ਪੂਰਨ symfollowset(ਪੂਰਨ ds[], ਪੂਰਨ dsize, ਪੂਰਨ transsym, ਪੂਰਨ nset[])
{
	ਪੂਰਨ     ns, tsp, sym, i, j, lenccl, ch, numstates, ccllist;

	numstates = 0;

	ਲਈ (i = 1; i <= dsize; ++i) {	/* for each nfa state ns in the state set of ds */
		ns = ds[i];
		sym = transchar[ns];
		tsp = trans1[ns];

		ਜੇ (sym < 0) {	/* it's a character class */
			sym = -sym;
			ccllist = cclmap[sym];
			lenccl = ccllen[sym];

			ਜੇ (cclng[sym]) {
				ਲਈ (j = 0; j < lenccl; ++j) {
					/* Loop through negated character
					 * class.
					 */
					ch = ccltbl[ccllist + j];

					ਜੇ (ch == 0)
						ch = NUL_ec;

					ਜੇ (ch > transsym)
						/* Transsym isn't in negated
						 * ccl.
						 */
						ਰੋਕੋ;

					ਨਹੀਂਤਾਂ ਜੇ (ch == transsym)
						/* next 2 */
						ਜਾਓ bottom;
				}

				/* Didn't find transsym in ccl. */
				nset[++numstates] = tsp;
			}

			ਨਹੀਂਤਾਂ
				ਲਈ (j = 0; j < lenccl; ++j) {
					ch = ccltbl[ccllist + j];

					ਜੇ (ch == 0)
						ch = NUL_ec;

					ਜੇ (ch > transsym)
						ਰੋਕੋ;
					ਨਹੀਂਤਾਂ ਜੇ (ch == transsym) {
						nset[++numstates] = tsp;
						ਰੋਕੋ;
					}
				}
		}

		ਨਹੀਂਤਾਂ ਜੇ (sym == SYM_EPSILON) {	/* do nothing */
		}

		ਨਹੀਂਤਾਂ ਜੇ (ABS (ecgroup[sym]) == transsym)
			nset[++numstates] = tsp;

	      bottom:;
	}

	ਵਾਪਸ numstates;
}


/* sympartition - partition characters with same out-transitions
 *
 * synopsis
 *    sympartition( int ds[current_max_dfa_size], int numstates,
 *			int symlist[numecs], int duplist[numecs] );
 */

ਸਥਿਰ ਖਾਲੀ sympartition(ਪੂਰਨ ds[], ਪੂਰਨ numstates, ਪੂਰਨ symlist[], ਪੂਰਨ duplist[])
{
	ਪੂਰਨ     tch, i, j, k, ns, dupfwd[CSIZE + 1], lenccl, cclp, ich;

	/* Partitioning is done by creating equivalence classes for those
	 * characters which have out-transitions from the given state.  Thus
	 * we are really creating equivalence classes of equivalence classes.
	 */

	ਲਈ (i = 1; i <= numecs; ++i) {	/* initialize equivalence class list */
		duplist[i] = i - 1;
		dupfwd[i] = i + 1;
	}

	duplist[1] = NIL;
	dupfwd[numecs] = NIL;

	ਲਈ (i = 1; i <= numstates; ++i) {
		ns = ds[i];
		tch = transchar[ns];

		ਜੇ (tch != SYM_EPSILON) {
			ਜੇ (tch < -lastccl || tch >= ctrl.csize) {
				flexfatal (_
					   ("bad transition character detected in sympartition()"));
			}

			ਜੇ (tch >= 0) {	/* character transition */
				ਪੂਰਨ     ec = ecgroup[tch];

				mkechar (ec, dupfwd, duplist);
				symlist[ec] = 1;
			}

			ਨਹੀਂਤਾਂ {	/* character class */
				tch = -tch;

				lenccl = ccllen[tch];
				cclp = cclmap[tch];
				mkeccl (ccltbl + cclp, lenccl, dupfwd,
					duplist, numecs, NUL_ec);

				ਜੇ (cclng[tch]) {
					j = 0;

					ਲਈ (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						ਜੇ (ich == 0)
							ich = NUL_ec;

						ਲਈ (++j; j < ich; ++j)
							symlist[j] = 1;
					}

					ਲਈ (++j; j <= numecs; ++j)
						symlist[j] = 1;
				}

				ਨਹੀਂਤਾਂ
					ਲਈ (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						ਜੇ (ich == 0)
							ich = NUL_ec;

						symlist[ich] = 1;
					}
			}
		}
	}
}
