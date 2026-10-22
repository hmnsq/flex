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

#ضمن "flexdef.h"
#ضمن "tables.h"

/* declare functions that have forward references */

ساكن فراغ dump_associated_قاعدا(FILE *, صحيح);
ساكن فراغ dump_transitions(FILE *, صحيح[]);
ساكن صحيح  snstods(صحيح[], صحيح, صحيح[], صحيح, صحيح, صحيح *);
ساكن فراغ sympartition(صحيح[], صحيح, صحيح[], صحيح[]);
ساكن صحيح  symfollowset(صحيح[], صحيح, صحيح, صحيح[]);


/* check_for_backing_up - check a DFA state for backing up
 *
 * synopsis
 *     void check_for_backing_up( int ds, int state[numecs] );
 *
 * ds is the number of the state to check and state[] is its out-transitions,
 * indexed by equivalence class.
 */

ساكن فراغ check_for_backing_مٿي(صحيح ds, صحيح state[])
{
	إذا ((reject && !dfaacc[ds].dfaacc_سيٽ) || (!reject && !dfaacc[ds].dfaacc_state)) {	/* state is non-accepting */
		++انگ_backing_مٿي;

		إذا (env.backing_مٿي_report) {
			fprintf (ctrl.backing_مٿي_file,
				 _("State #%d is non-accepting -\n"), ds);

			/* identify the state */
			dump_associated_قاعدا (ctrl.backing_مٿي_file, ds);

			/* Now identify it further using the out- and
			 * jam-transitions.
			 */
			dump_transitions (ctrl.backing_مٿي_file, state);

			putc ('\n', ctrl.backing_مٿي_file);
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

ساكن فراغ check_trailing_context(صحيح *nfa_حالتون, صحيح انگ_حالتون, صحيح *accset, صحيح nacc)
{
	صحيح i, j;

	لكل (i = 1; i <= انگ_حالتون; ++i) {
		صحيح     ns = nfa_حالتون[i];
		صحيح type = state_type[ns];
		صحيح ar = assoc_قاعدو[ns];

		إذا (type == STATE_عام || قاعدو_type[ar] != قاعدو_VARIABLE) {	/* do nothing */
		}

		وإلا إذا (type == STATE_TRAILING_CONTEXT) {
			/* Potential trouble.  Scan set of accepting numbers
			 * for the one marking the end of the "head".  We
			 * assume that this looping will be fairly cheap
			 * since it's rare that an accepting number set
			 * is large.
			 */
			لكل (j = 1; j <= nacc; ++j)
				إذا (accset[j] & YY_TRAILING_سر_نقاب) {
					سٽ_warning (_
						      ("dangerous trailing context"),
						      قاعدو_linenum[ar]);
					أرجع;
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

ساكن فراغ dump_associated_قاعدا(FILE *file, صحيح ds)
{
	صحيح i, j;
	صحيح انگ_associated_قاعدا = 0;
	صحيح قاعدو_سيٽ[MAX_ASSOC_قاعدا + 1];
	صحيح *dset = dss[ds];
	صحيح سائيز = dfasiz[ds];

	لكل (i = 1; i <= سائيز; ++i) {
		صحيح قاعدو_انگ = قاعدو_linenum[assoc_قاعدو[dset[i]]];

		لكل (j = 1; j <= انگ_associated_قاعدا; ++j)
			إذا (قاعدو_انگ == قاعدو_سيٽ[j])
				اكسر;

		إذا (j > انگ_associated_قاعدا) {	/* new rule */
			إذا (انگ_associated_قاعدا < MAX_ASSOC_قاعدا)
				قاعدو_سيٽ[++انگ_associated_قاعدا] =
					قاعدو_انگ;
		}
	}

	qsort (&قاعدو_سيٽ [1], (size_t) انگ_associated_قاعدا, حجم (قاعدو_سيٽ [1]), intcmp);

	fprintf (file, _(" associated rule line numbers:"));

	لكل (i = 1; i <= انگ_associated_قاعدا; ++i) {
		إذا (i % 8 == 1)
			putc ('\n', file);

		fprintf (file, "\t%d", قاعدو_سيٽ[i]);
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

ساكن فراغ dump_transitions(FILE *file, صحيح state[])
{
	صحيح i, ec;
	صحيح ٻاهريون_char_سيٽ[CSIZE];

	لكل (i = 0; i < ctrl.csize; ++i) {
		ec = ABS (ecgroup[i]);
		ٻاهريون_char_سيٽ[i] = state[ec];
	}

	fprintf (file, _(" out-transitions: "));

	list_character_سيٽ (file, ٻاهريون_char_سيٽ);

	/* now invert the members of the set to get the jam transitions */
	لكل (i = 0; i < ctrl.csize; ++i)
		ٻاهريون_char_سيٽ[i] = !ٻاهريون_char_سيٽ[i];

	fprintf (file, _("\n jam-transitions: EOF "));

	list_character_سيٽ (file, ٻاهريون_char_سيٽ);

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

ساكن صحيح *epsclosure(صحيح *t, صحيح *ns_addr, صحيح accset[], صحيح *nacc_addr, صحيح *hv_addr)
{
	صحيح     stkpos, ns, tsp;
	صحيح     numstates = *ns_addr, nacc, hashval, transsym, nfaccnum;
	صحيح     stkend, nstate;
	ساكن صحيح did_stk_init = false, *stk;

#وصف_ڪريو MARK_STATE(state) \
افعل{ trans1[state] = trans1[state] - MARKER_DIFFERENCE;} طالما(0)

#وصف_ڪريو IS_MARKED(state) (trans1[state] < 0)

#وصف_ڪريو UNMARK_STATE(state) \
افعل{ trans1[state] = trans1[state] + MARKER_DIFFERENCE;} طالما(0)

#وصف_ڪريو CHECK_ACCEPT(state) \
افعل{ \
nfaccnum = accptnum[state]; \
إذا ( nfaccnum != NIL ) \
accset[++nacc] = nfaccnum; \
}طالما(0)

#وصف_ڪريو DO_REALLOCATION() \
افعل { \
current_max_dfa_سائيز += MAX_DFA_سائيز_INCREMENT; \
++انگ_reallocs; \
t = reallocate_integer_array( t, current_max_dfa_سائيز ); \
stk = reallocate_integer_array( stk, current_max_dfa_سائيز ); \
}طالما(0) \

#وصف_ڪريو PUT_ON_ڍير(state) \
افعل { \
إذا ( ++stkend >= current_max_dfa_سائيز ) \
DO_REALLOCATION(); \
stk[stkend] = state; \
MARK_STATE(state); \
}طالما(0)

#وصف_ڪريو جوڙيو_STATE(state) \
افعل { \
إذا ( ++numstates >= current_max_dfa_سائيز ) \
DO_REALLOCATION(); \
t[numstates] = state; \
hashval += state; \
}طالما(0)

#وصف_ڪريو ڍير_STATE(state) \
افعل { \
PUT_ON_ڍير(state); \
CHECK_ACCEPT(state); \
إذا ( nfaccnum != NIL || transchar[state] != SYM_EPSILON ) \
جوڙيو_STATE(state); \
}طالما(0)


	إذا (!did_stk_init) {
		stk = allocate_integer_array (current_max_dfa_سائيز);
		did_stk_init = true;
	}

	nacc = stkend = hashval = 0;

	لكل (nstate = 1; nstate <= numstates; ++nstate) {
		ns = t[nstate];

		/* The state could be marked if we've already pushed it onto
		 * the stack.
		 */
		إذا (!IS_MARKED (ns)) {
			PUT_ON_ڍير (ns);
			CHECK_ACCEPT (ns);
			hashval += ns;
		}
	}

	لكل (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ns = stk[stkpos];
		transsym = transchar[ns];

		إذا (transsym == SYM_EPSILON) {
			tsp = trans1[ns] + MARKER_DIFFERENCE;

			إذا (tsp != NO_TRANSITION) {
				إذا (!IS_MARKED (tsp))
					ڍير_STATE (tsp);

				tsp = trans2[ns];

				إذا (tsp != NO_TRANSITION
				    && !IS_MARKED (tsp))
					ڍير_STATE (tsp);
			}
		}
	}

	/* Clear out "visit" markers. */

	لكل (stkpos = 1; stkpos <= stkend; ++stkpos) {
		إذا (IS_MARKED (stk[stkpos]))
			UNMARK_STATE (stk[stkpos]);
		وإلا
			flexfatal (_
				   ("consistency check failed in epsclosure()"));
	}

	*ns_addr = numstates;
	*hv_addr = hashval;
	*nacc_addr = nacc;

	أرجع t;
}


/* increase_max_dfas - increase the maximum number of DFAs */

فراغ increase_max_dfas (فراغ)
{
	current_max_dfas += MAX_DFAS_INCREMENT;

	++انگ_reallocs;

	بنياد = reallocate_integer_array (بنياد, current_max_dfas);
	def = reallocate_integer_array (def, current_max_dfas);
	dfasiz = reallocate_integer_array (dfasiz, current_max_dfas);
	accsiz = reallocate_integer_array (accsiz, current_max_dfas);
	dhash = reallocate_integer_array (dhash, current_max_dfas);
	dss = reallocate_int_ptr_array (dss, current_max_dfas);
	dfaacc = reallocate_array(dfaacc, current_max_dfas,
		حجم(اتحاد dfaacc_union));

	إذا (nultrans)
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

size_t ntod (فراغ)
{
	صحيح    *accset, ds, nacc, newds;
	صحيح     sym, hashval, numstates, dsize;
	صحيح     انگ_ڀريل_جدول_صفون=0;	/* used only for -f */
	صحيح    *nset, *dset;
	صحيح     targptr, totaltrans, i, comstate, comfreq, targ;
	صحيح     symlist[CSIZE + 1];
	صحيح     انگ_شروعات_حالتون;
	صحيح     todo_سر, todo_ايندڙ;

	بنية yytbl_معلومات *yynxt_tbl = 0;
	flex_int32_t *yynxt_معلومات = 0, yynxt_curr = 0;

	/* Note that the following are indexed by *equivalence classes*
	 * and not by characters.  Since equivalence classes are indexed
	 * beginning with 1, even if the scanner accepts NUL's, this
	 * means that (since every character is potentially in its own
	 * equivalence class) these arrays must have room for indices
	 * from 1 to CSIZE, so their size must be CSIZE + 1.
	 */
	صحيح     duplist[CSIZE + 1], state[CSIZE + 1];
	صحيح     targfreq[CSIZE + 1] = {0}, targstate[CSIZE + 1];

	/* accset needs to be large enough to hold all of the rules present
	 * in the input, *plus* their YY_TRAILING_HEAD_MASK variants.
	 */
	accset = allocate_integer_array ((انگ_قاعدا + 1) * 2);
	nset = allocate_integer_array (current_max_dfa_سائيز);

	/* The "todo" queue is represented by the head, which is the DFA
	 * state currently being processed, and the "next", which is the
	 * next DFA state number available (not in use).  We depend on the
	 * fact that snstods() returns DFA's \in increasing order/, and thus
	 * need only know the bounds of the dfas to be processed.
	 */
	todo_سر = todo_ايندڙ = 0;

	لكل (i = 0; i <= ctrl.csize; ++i) {
		duplist[i] = NIL;
		symlist[i] = false;
	}

	لكل (i = 0; i <= انگ_قاعدا; ++i)
		accset[i] = NIL;

	إذا (env.trace) {
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
	إذا (ctrl.fulltbl && ecgroup[0] == numecs && is_power_جو_2(numecs))
		nultrans = allocate_integer_array (current_max_dfas);

	إذا (ctrl.fullspd) {
		لكل (i = 0; i <= numecs; ++i)
			state[i] = 0;

		رکو_state (state, 0, 0);
		dfaacc[0].dfaacc_state = 0;
	}

	وإلا إذا (ctrl.fulltbl) {
		إذا (nultrans)
			/* We won't be including NUL's transitions in the
			 * table, so build it for entries from 0 .. numecs - 1.
			 */
			انگ_ڀريل_جدول_صفون = numecs;

		وإلا
			/* Take into account the fact that we'll be including
			 * the NUL entries in the transition table.  Build it
			 * from 0 .. numecs.
			 */
			انگ_ڀريل_جدول_صفون = numecs + 1;

		/* Begin generating yy_nxt[][]
		 * This spans the entire LONG function.
		 * This table is tricky because we don't know how big it will be.
		 * So we'll have to realloc() on the way...
		 * we'll wait until we can calculate yynxt_tbl->td_hilen.
		 */
		yynxt_tbl = صفر_يادگيري_ڏيو(1, حجم (بنية yytbl_معلومات));
     
		yytbl_معلومات_init (yynxt_tbl, YYTD_ID_NXT);
		yynxt_tbl->td_hilen = 1;
		yynxt_tbl->td_lolen = (flex_uint32_t) انگ_ڀريل_جدول_صفون;
		yynxt_tbl->td_معلومات = yynxt_معلومات =
		    صفر_يادگيري_ڏيو(yynxt_tbl->td_lolen *
			   yynxt_tbl->td_hilen,
			   حجم (flex_int32_t));
		yynxt_curr = 0;

		بنية packtype_t *ptype = optimize_pack(0);
		/* Note: Used when ctrl.fulltbl is on. Alternately defined elsewhere */
		ٻاهريون_str ("m4_define([[M4_HOOK_NXT_TYPE]], [[%s]])", ptype->name);
		ٻاهريون_dec ("m4_define([[M4_HOOK_NXT_ROWS]], [[%d]])", انگ_ڀريل_جدول_صفون);
		outn ("m4_define([[M4_HOOK_NXT_BODY]], [[m4_dnl");
		outn ("M4_HOOK_TABLE_OPENER");
		إذا (gentables)
			outn ("M4_HOOK_TABLE_OPENER");

		/* Generate 0 entries for state #0. */
		لكل (i = 0; i < انگ_ڀريل_جدول_صفون; ++i) {
			mk2data (0);
			yynxt_معلومات[yynxt_curr++] = 0;
		}

		إذا (gentables) {
			dataflush ();
			outn ("M4_HOOK_TABLE_CONTINUE");
		}
	}

	/* Create the first states. */

	انگ_شروعات_حالتون = lastsc * 2;

	لكل (i = 1; i <= انگ_شروعات_حالتون; ++i) {
		numstates = 1;

		/* For each start condition, make one state for the case when
		 * we're at the beginning of the line (the '^' operator) and
		 * one for the case when we're not.
		 */
		إذا (i % 2 == 1)
			nset[numstates] = scset[(i / 2) + 1];
		وإلا
			nset[numstates] =
				mkbranch (scbol[i / 2], scset[i / 2]);

		nset = epsclosure (nset, &numstates, accset, &nacc,
				   &hashval);

		إذا (snstods (nset, numstates, accset, nacc, hashval, &ds)) {
			numas += nacc;
			totnst += numstates;
			++todo_ايندڙ;

			إذا (variable_trailing_context_قاعدا && nacc > 0)
				check_trailing_context (nset, numstates,
							accset, nacc);
		}
	}

	إذا (!ctrl.fullspd) {
		إذا (!snstods (nset, 0, accset, 0, 0, &پڇاڙي_جو_بفر_state))
			flexfatal (_
				   ("could not create unique end-of-buffer state"));

		++numas;
		++انگ_شروعات_حالتون;
		++todo_ايندڙ;
	}


	طالما (todo_سر < todo_ايندڙ) {
		targptr = 0;
		totaltrans = 0;

		لكل (i = 1; i <= numecs; ++i)
			state[i] = 0;

		ds = ++todo_سر;

		dset = dss[ds];
		dsize = dfasiz[ds];

		إذا (env.trace)
			fprintf (stderr, _("state # %d:\n"), ds);

		sympartition (dset, dsize, symlist, duplist);

		لكل (sym = 1; sym <= numecs; ++sym) {
			إذا (symlist[sym]) {
				symlist[sym] = 0;

				إذا (duplist[sym] == NIL) {
					/* Symbol has unique out-transitions. */
					numstates =
						symfollowset (dset, dsize,
							      sym, nset);
					nset = epsclosure (nset,
							   &numstates,
							   accset, &nacc,
							   &hashval);

					إذا (snstods
					    (nset, numstates, accset, nacc,
					     hashval, &newds)) {
						totnst = totnst +
							numstates;
						++todo_ايندڙ;
						numas += nacc;

						إذا (variable_trailing_context_قاعدا && nacc > 0)
							check_trailing_context
								(nset,
								 numstates,
								 accset,
								 nacc);
					}

					state[sym] = newds;

					إذا (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 newds);

					targfreq[++targptr] = 1;
					targstate[targptr] = newds;
					++numuniq;
				}

				وإلا {
					/* sym's equivalence class has the same
					 * transitions as duplist(sym)'s
					 * equivalence class.
					 */
					targ = state[duplist[sym]];
					state[sym] = targ;

					إذا (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 targ);

					/* Update frequency count for
					 * destination state.
					 */

					i = 0;
					طالما (targstate[++i] != targ) ;

					++targfreq[i];
					++numdup;
				}

				++totaltrans;
				duplist[sym] = NIL;
			}
		}


		numsnpairs += totaltrans;

		إذا (ds > انگ_شروعات_حالتون)
			check_for_backing_مٿي (ds, state);

		إذا (nultrans) {
			nultrans[ds] = state[NUL_ec];
			state[NUL_ec] = 0;	/* remove transition */
		}

		إذا (ctrl.fulltbl) {

			/* Each time we hit here, it's another td_hilen, so we realloc. */
			yynxt_tbl->td_hilen++;
			yynxt_tbl->td_معلومات = yynxt_معلومات =
				realloc (yynxt_معلومات,
						     yynxt_tbl->td_hilen *
						     yynxt_tbl->td_lolen *
						     حجم (flex_int32_t));
			إذا (gentables)
				outn ("M4_HOOK_TABLE_OPENER");

			/* Supply array's 0-element. */
			إذا (ds == پڇاڙي_جو_بفر_state) {
				mk2data (-پڇاڙي_جو_بفر_state);
				yynxt_معلومات[yynxt_curr++] =
					-پڇاڙي_جو_بفر_state;
			}
			وإلا {
				mk2data (پڇاڙي_جو_بفر_state);
				yynxt_معلومات[yynxt_curr++] =
					پڇاڙي_جو_بفر_state;
			}

			لكل (i = 1; i < انگ_ڀريل_جدول_صفون; ++i) {
				/* Jams are marked by negative of state
				 * number.
				 */
				mk2data (state[i] ? state[i] : -ds);
				yynxt_معلومات[yynxt_curr++] =
					state[i] ? state[i] : -ds;
			}

			إذا (gentables) {
				dataflush ();
				outn ("M4_HOOK_TABLE_CONTINUE");
			}
		}

		وإلا إذا (ctrl.fullspd)
			رکو_state (state, ds, totaltrans);

		وإلا إذا (ds == پڇاڙي_جو_بفر_state)
			/* Special case this state to make sure it does what
			 * it's supposed to, i.e., jam on end-of-buffer.
			 */
			stack1 (ds, 0, 0, JAMSTATE);

		وإلا {		/* normal, compressed state */

			/* Determine which destination state is the most
			 * common, and how many transitions to it there are.
			 */

			comfreq = 0;
			comstate = 0;

			لكل (i = 1; i <= targptr; ++i)
				إذا (targfreq[i] > comfreq) {
					comfreq = targfreq[i];
					comstate = targstate[i];
				}

			bldtbl (state, ds, totaltrans, comstate, comfreq);
		}
	}

	إذا (ctrl.fulltbl) {
		dataend ("M4_HOOK_TABLE_CLOSER");
		outn("/* body */]])");
		إذا (tablesext) {
			yytbl_معلومات_compress (yynxt_tbl);
			إذا (yytbl_معلومات_fwrite (&tableswr, yynxt_tbl) < 0)
				flexerror (_
					   ("Could not write yynxt_tbl[][]"));
		}
		إذا (yynxt_tbl) {
			yytbl_معلومات_destroy (yynxt_tbl);
			yynxt_tbl = 0;
		}
	}

	وإلا إذا (!ctrl.fullspd) {
		cmptmps ();	/* create compressed template entries */

		/* Create tables for all the states with only one
		 * out-transition.
		 */
		طالما (onesp > 0) {
			mk1tbl (onestate[onesp], onesym[onesp],
				onenext[onesp], onedef[onesp]);
			--onesp;
		}

		mkdeftbl ();
	}


	حرر(accset);
	حرر(nset);

	أرجع (yynxt_tbl != عدم) ? (yynxt_tbl->td_hilen * حجم(int32_t)) : 0;
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

ساكن صحيح snstods(صحيح sns[], صحيح numstates, صحيح accset[], صحيح nacc, صحيح hashval, صحيح *newds_addr)
{
	صحيح didsort = 0;
	صحيح i, j;
	صحيح newds, *oldsns;

	لكل (i = 1; i <= lastdfa; ++i)
		إذا (hashval == dhash[i]) {
			إذا (numstates == dfasiz[i]) {
				oldsns = dss[i];

				إذا (!didsort) {
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 */
					qsort (&sns [1], (size_t) numstates, حجم (sns [1]), intcmp);
					didsort = 1;
				}

				لكل (j = 1; j <= numstates; ++j)
					إذا (sns[j] != oldsns[j])
						اكسر;

				إذا (j > numstates) {
					++dfaeql;
					*newds_addr = i;
					أرجع 0;
				}

				++hshcol;
			}

			وإلا
				++hshsave;
		}

	/* Make a new dfa. */

	إذا (++lastdfa >= current_max_dfas)
		increase_max_dfas ();

	newds = lastdfa;

	dss[newds] = allocate_integer_array (numstates + 1);

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	إذا (!didsort)
          	qsort (&sns [1], (size_t) numstates, حجم (sns [1]), intcmp);

	لكل (i = 1; i <= numstates; ++i)
		dss[newds][i] = sns[i];

	dfasiz[newds] = numstates;
	dhash[newds] = hashval;

	إذا (nacc == 0) {
		إذا (reject)
			dfaacc[newds].dfaacc_سيٽ = عدم;
		وإلا
			dfaacc[newds].dfaacc_state = 0;

		accsiz[newds] = 0;
	}

	وإلا إذا (reject) {
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.
		 */

		qsort (&accset [1], (size_t) nacc, حجم (accset [1]), intcmp);

		dfaacc[newds].dfaacc_سيٽ =
			allocate_integer_array (nacc + 1);

		/* Save the accepting set for later */
		لكل (i = 1; i <= nacc; ++i) {
			dfaacc[newds].dfaacc_سيٽ[i] = accset[i];

			إذا (accset[i] <= انگ_قاعدا)
				/* Who knows, perhaps a REJECT can yield
				 * this rule.
				 */
				قاعدو_useful[accset[i]] = true;
		}

		accsiz[newds] = nacc;
	}

	وإلا {
		/* Find lowest numbered rule so the disambiguating rule
		 * will work.
		 */
		j = انگ_قاعدا + 1;

		لكل (i = 1; i <= nacc; ++i)
			إذا (accset[i] < j)
				j = accset[i];

		dfaacc[newds].dfaacc_state = j;

		إذا (j <= انگ_قاعدا)
			قاعدو_useful[j] = true;
	}

	*newds_addr = newds;

	أرجع 1;
}


/* symfollowset - follow the symbol transitions one step
 *
 * synopsis
 *    numstates = symfollowset( int ds[current_max_dfa_size], int dsize,
 *				int transsym, int nset[current_max_dfa_size] );
 */

ساكن صحيح symfollowset(صحيح ds[], صحيح dsize, صحيح transsym, صحيح nset[])
{
	صحيح     ns, tsp, sym, i, j, lenccl, ch, numstates, ccllist;

	numstates = 0;

	لكل (i = 1; i <= dsize; ++i) {	/* for each nfa state ns in the state set of ds */
		ns = ds[i];
		sym = transchar[ns];
		tsp = trans1[ns];

		إذا (sym < 0) {	/* it's a character class */
			sym = -sym;
			ccllist = cclmap[sym];
			lenccl = ccllen[sym];

			إذا (cclng[sym]) {
				لكل (j = 0; j < lenccl; ++j) {
					/* Loop through negated character
					 * class.
					 */
					ch = ccltbl[ccllist + j];

					إذا (ch == 0)
						ch = NUL_ec;

					إذا (ch > transsym)
						/* Transsym isn't in negated
						 * ccl.
						 */
						اكسر;

					وإلا إذا (ch == transsym)
						/* next 2 */
						اذهب bottom;
				}

				/* Didn't find transsym in ccl. */
				nset[++numstates] = tsp;
			}

			وإلا
				لكل (j = 0; j < lenccl; ++j) {
					ch = ccltbl[ccllist + j];

					إذا (ch == 0)
						ch = NUL_ec;

					إذا (ch > transsym)
						اكسر;
					وإلا إذا (ch == transsym) {
						nset[++numstates] = tsp;
						اكسر;
					}
				}
		}

		وإلا إذا (sym == SYM_EPSILON) {	/* do nothing */
		}

		وإلا إذا (ABS (ecgroup[sym]) == transsym)
			nset[++numstates] = tsp;

	      bottom:;
	}

	أرجع numstates;
}


/* sympartition - partition characters with same out-transitions
 *
 * synopsis
 *    sympartition( int ds[current_max_dfa_size], int numstates,
 *			int symlist[numecs], int duplist[numecs] );
 */

ساكن فراغ sympartition(صحيح ds[], صحيح numstates, صحيح symlist[], صحيح duplist[])
{
	صحيح     tch, i, j, k, ns, dupfwd[CSIZE + 1], lenccl, cclp, ich;

	/* Partitioning is done by creating equivalence classes for those
	 * characters which have out-transitions from the given state.  Thus
	 * we are really creating equivalence classes of equivalence classes.
	 */

	لكل (i = 1; i <= numecs; ++i) {	/* initialize equivalence class list */
		duplist[i] = i - 1;
		dupfwd[i] = i + 1;
	}

	duplist[1] = NIL;
	dupfwd[numecs] = NIL;

	لكل (i = 1; i <= numstates; ++i) {
		ns = ds[i];
		tch = transchar[ns];

		إذا (tch != SYM_EPSILON) {
			إذا (tch < -lastccl || tch >= ctrl.csize) {
				flexfatal (_
					   ("bad transition character detected in sympartition()"));
			}

			إذا (tch >= 0) {	/* character transition */
				صحيح     ec = ecgroup[tch];

				mkechar (ec, dupfwd, duplist);
				symlist[ec] = 1;
			}

			وإلا {	/* character class */
				tch = -tch;

				lenccl = ccllen[tch];
				cclp = cclmap[tch];
				mkeccl (ccltbl + cclp, lenccl, dupfwd,
					duplist, numecs, NUL_ec);

				إذا (cclng[tch]) {
					j = 0;

					لكل (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						إذا (ich == 0)
							ich = NUL_ec;

						لكل (++j; j < ich; ++j)
							symlist[j] = 1;
					}

					لكل (++j; j <= numecs; ++j)
						symlist[j] = 1;
				}

				وإلا
					لكل (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						إذا (ich == 0)
							ich = NUL_ec;

						symlist[ich] = 1;
					}
			}
		}
	}
}
