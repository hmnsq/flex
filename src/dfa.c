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

#شامل "flexdef.h"
#شامل "tables.h"

/* declare functions that have forward references */

ساکن خالی dump_associated_قواعد(FILE *, صحیح);
ساکن خالی dump_transitions(FILE *, صحیح[]);
ساکن صحیح  snstods(صحیح[], صحیح, صحیح[], صحیح, صحیح, صحیح *);
ساکن خالی sympartition(صحیح[], صحیح, صحیح[], صحیح[]);
ساکن صحیح  symfollowset(صحیح[], صحیح, صحیح, صحیح[]);


/* check_for_backing_up - check a DFA state for backing up
 *
 * synopsis
 *     void check_for_backing_up( int ds, int state[numecs] );
 *
 * ds is the number of the state to check and state[] is its out-transitions,
 * indexed by equivalence class.
 */

ساکن خالی check_for_backing_اوپر(صحیح ds, صحیح state[])
{
	اگر ((reject && !dfaacc[ds].dfaacc_سیٹ) || (!reject && !dfaacc[ds].dfaacc_state)) {	/* state is non-accepting */
		++عدد_backing_اوپر;

		اگر (env.backing_اوپر_report) {
			fprintf (ctrl.backing_اوپر_file,
				 _("State #%d is non-accepting -\n"), ds);

			/* identify the state */
			dump_associated_قواعد (ctrl.backing_اوپر_file, ds);

			/* Now identify it further using the out- and
			 * jam-transitions.
			 */
			dump_transitions (ctrl.backing_اوپر_file, state);

			putc ('\n', ctrl.backing_اوپر_file);
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

ساکن خالی check_trailing_context(صحیح *nfa_حالتیں, صحیح عدد_حالتیں, صحیح *accset, صحیح nacc)
{
	صحیح i, j;

	برائے (i = 1; i <= عدد_حالتیں; ++i) {
		صحیح     ns = nfa_حالتیں[i];
		صحیح type = state_type[ns];
		صحیح ar = assoc_قاعدہ[ns];

		اگر (type == STATE_معمول || قاعدہ_type[ar] != قاعدہ_VARIABLE) {	/* do nothing */
		}

		ورنہ اگر (type == STATE_TRAILING_CONTEXT) {
			/* Potential trouble.  Scan set of accepting numbers
			 * for the one marking the end of the "head".  We
			 * assume that this looping will be fairly cheap
			 * since it's rare that an accepting number set
			 * is large.
			 */
			برائے (j = 1; j <= nacc; ++j)
				اگر (accset[j] & YY_TRAILING_سر_نقاب) {
					سطر_warning (_
						      ("dangerous trailing context"),
						      قاعدہ_linenum[ar]);
					واپس;
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

ساکن خالی dump_associated_قواعد(FILE *file, صحیح ds)
{
	صحیح i, j;
	صحیح عدد_associated_قواعد = 0;
	صحیح قاعدہ_سیٹ[MAX_ASSOC_قواعد + 1];
	صحیح *dset = dss[ds];
	صحیح سائز = dfasiz[ds];

	برائے (i = 1; i <= سائز; ++i) {
		صحیح قاعدہ_عدد = قاعدہ_linenum[assoc_قاعدہ[dset[i]]];

		برائے (j = 1; j <= عدد_associated_قواعد; ++j)
			اگر (قاعدہ_عدد == قاعدہ_سیٹ[j])
				توڑو;

		اگر (j > عدد_associated_قواعد) {	/* new rule */
			اگر (عدد_associated_قواعد < MAX_ASSOC_قواعد)
				قاعدہ_سیٹ[++عدد_associated_قواعد] =
					قاعدہ_عدد;
		}
	}

	qsort (&قاعدہ_سیٹ [1], (size_t) عدد_associated_قواعد, حجم (قاعدہ_سیٹ [1]), intcmp);

	fprintf (file, _(" associated rule line numbers:"));

	برائے (i = 1; i <= عدد_associated_قواعد; ++i) {
		اگر (i % 8 == 1)
			putc ('\n', file);

		fprintf (file, "\t%d", قاعدہ_سیٹ[i]);
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

ساکن خالی dump_transitions(FILE *file, صحیح state[])
{
	صحیح i, ec;
	صحیح برآمد_char_سیٹ[CSIZE];

	برائے (i = 0; i < ctrl.csize; ++i) {
		ec = ABS (ecgroup[i]);
		برآمد_char_سیٹ[i] = state[ec];
	}

	fprintf (file, _(" out-transitions: "));

	list_character_سیٹ (file, برآمد_char_سیٹ);

	/* now invert the members of the set to get the jam transitions */
	برائے (i = 0; i < ctrl.csize; ++i)
		برآمد_char_سیٹ[i] = !برآمد_char_سیٹ[i];

	fprintf (file, _("\n jam-transitions: EOF "));

	list_character_سیٹ (file, برآمد_char_سیٹ);

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

ساکن صحیح *epsclosure(صحیح *t, صحیح *ns_addr, صحیح accset[], صحیح *nacc_addr, صحیح *hv_addr)
{
	صحیح     stkpos, ns, tsp;
	صحیح     numstates = *ns_addr, nacc, hashval, transsym, nfaccnum;
	صحیح     stkend, nstate;
	ساکن صحیح did_stk_init = false, *stk;

#تعریف_کرو MARK_STATE(state) \
کرو{ trans1[state] = trans1[state] - MARKER_DIFFERENCE;} جب(0)

#تعریف_کرو IS_MARKED(state) (trans1[state] < 0)

#تعریف_کرو UNMARK_STATE(state) \
کرو{ trans1[state] = trans1[state] + MARKER_DIFFERENCE;} جب(0)

#تعریف_کرو CHECK_ACCEPT(state) \
کرو{ \
nfaccnum = accptnum[state]; \
اگر ( nfaccnum != NIL ) \
accset[++nacc] = nfaccnum; \
}جب(0)

#تعریف_کرو DO_REALLOCATION() \
کرو { \
current_max_dfa_سائز += MAX_DFA_سائز_INCREMENT; \
++عدد_reallocs; \
t = reallocate_integer_array( t, current_max_dfa_سائز ); \
stk = reallocate_integer_array( stk, current_max_dfa_سائز ); \
}جب(0) \

#تعریف_کرو PUT_ON_ڈھیر(state) \
کرو { \
اگر ( ++stkend >= current_max_dfa_سائز ) \
DO_REALLOCATION(); \
stk[stkend] = state; \
MARK_STATE(state); \
}جب(0)

#تعریف_کرو جوڑو_STATE(state) \
کرو { \
اگر ( ++numstates >= current_max_dfa_سائز ) \
DO_REALLOCATION(); \
t[numstates] = state; \
hashval += state; \
}جب(0)

#تعریف_کرو ڈھیر_STATE(state) \
کرو { \
PUT_ON_ڈھیر(state); \
CHECK_ACCEPT(state); \
اگر ( nfaccnum != NIL || transchar[state] != SYM_EPSILON ) \
جوڑو_STATE(state); \
}جب(0)


	اگر (!did_stk_init) {
		stk = allocate_integer_array (current_max_dfa_سائز);
		did_stk_init = true;
	}

	nacc = stkend = hashval = 0;

	برائے (nstate = 1; nstate <= numstates; ++nstate) {
		ns = t[nstate];

		/* The state could be marked if we've already pushed it onto
		 * the stack.
		 */
		اگر (!IS_MARKED (ns)) {
			PUT_ON_ڈھیر (ns);
			CHECK_ACCEPT (ns);
			hashval += ns;
		}
	}

	برائے (stkpos = 1; stkpos <= stkend; ++stkpos) {
		ns = stk[stkpos];
		transsym = transchar[ns];

		اگر (transsym == SYM_EPSILON) {
			tsp = trans1[ns] + MARKER_DIFFERENCE;

			اگر (tsp != NO_TRANSITION) {
				اگر (!IS_MARKED (tsp))
					ڈھیر_STATE (tsp);

				tsp = trans2[ns];

				اگر (tsp != NO_TRANSITION
				    && !IS_MARKED (tsp))
					ڈھیر_STATE (tsp);
			}
		}
	}

	/* Clear out "visit" markers. */

	برائے (stkpos = 1; stkpos <= stkend; ++stkpos) {
		اگر (IS_MARKED (stk[stkpos]))
			UNMARK_STATE (stk[stkpos]);
		ورنہ
			flexfatal (_
				   ("consistency check failed in epsclosure()"));
	}

	*ns_addr = numstates;
	*hv_addr = hashval;
	*nacc_addr = nacc;

	واپس t;
}


/* increase_max_dfas - increase the maximum number of DFAs */

خالی increase_max_dfas (خالی)
{
	current_max_dfas += MAX_DFAS_INCREMENT;

	++عدد_reallocs;

	بنیاد = reallocate_integer_array (بنیاد, current_max_dfas);
	def = reallocate_integer_array (def, current_max_dfas);
	dfasiz = reallocate_integer_array (dfasiz, current_max_dfas);
	accsiz = reallocate_integer_array (accsiz, current_max_dfas);
	dhash = reallocate_integer_array (dhash, current_max_dfas);
	dss = reallocate_int_ptr_array (dss, current_max_dfas);
	dfaacc = reallocate_array(dfaacc, current_max_dfas,
		حجم(اتحاد dfaacc_union));

	اگر (nultrans)
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

size_t ntod (خالی)
{
	صحیح    *accset, ds, nacc, newds;
	صحیح     sym, hashval, numstates, dsize;
	صحیح     عدد_بھرا_جدول_صفیں=0;	/* used only for -f */
	صحیح    *nset, *dset;
	صحیح     targptr, totaltrans, i, comstate, comfreq, targ;
	صحیح     symlist[CSIZE + 1];
	صحیح     عدد_آغاز_حالتیں;
	صحیح     todo_سر, todo_اگلا;

	ساخت yytbl_ڈیٹا *yynxt_tbl = 0;
	flex_int32_t *yynxt_ڈیٹا = 0, yynxt_curr = 0;

	/* Note that the following are indexed by *equivalence classes*
	 * and not by characters.  Since equivalence classes are indexed
	 * beginning with 1, even if the scanner accepts NUL's, this
	 * means that (since every character is potentially in its own
	 * equivalence class) these arrays must have room for indices
	 * from 1 to CSIZE, so their size must be CSIZE + 1.
	 */
	صحیح     duplist[CSIZE + 1], state[CSIZE + 1];
	صحیح     targfreq[CSIZE + 1] = {0}, targstate[CSIZE + 1];

	/* accset needs to be large enough to hold all of the rules present
	 * in the input, *plus* their YY_TRAILING_HEAD_MASK variants.
	 */
	accset = allocate_integer_array ((عدد_قواعد + 1) * 2);
	nset = allocate_integer_array (current_max_dfa_سائز);

	/* The "todo" queue is represented by the head, which is the DFA
	 * state currently being processed, and the "next", which is the
	 * next DFA state number available (not in use).  We depend on the
	 * fact that snstods() returns DFA's \in increasing order/, and thus
	 * need only know the bounds of the dfas to be processed.
	 */
	todo_سر = todo_اگلا = 0;

	برائے (i = 0; i <= ctrl.csize; ++i) {
		duplist[i] = NIL;
		symlist[i] = false;
	}

	برائے (i = 0; i <= عدد_قواعد; ++i)
		accset[i] = NIL;

	اگر (env.trace) {
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
	اگر (ctrl.fulltbl && ecgroup[0] == numecs && is_power_کا_2(numecs))
		nultrans = allocate_integer_array (current_max_dfas);

	اگر (ctrl.fullspd) {
		برائے (i = 0; i <= numecs; ++i)
			state[i] = 0;

		رکھو_state (state, 0, 0);
		dfaacc[0].dfaacc_state = 0;
	}

	ورنہ اگر (ctrl.fulltbl) {
		اگر (nultrans)
			/* We won't be including NUL's transitions in the
			 * table, so build it for entries from 0 .. numecs - 1.
			 */
			عدد_بھرا_جدول_صفیں = numecs;

		ورنہ
			/* Take into account the fact that we'll be including
			 * the NUL entries in the transition table.  Build it
			 * from 0 .. numecs.
			 */
			عدد_بھرا_جدول_صفیں = numecs + 1;

		/* Begin generating yy_nxt[][]
		 * This spans the entire LONG function.
		 * This table is tricky because we don't know how big it will be.
		 * So we'll have to realloc() on the way...
		 * we'll wait until we can calculate yynxt_tbl->td_hilen.
		 */
		yynxt_tbl = صفر_حافظہ_دو(1, حجم (ساخت yytbl_ڈیٹا));
     
		yytbl_ڈیٹا_init (yynxt_tbl, YYTD_ID_NXT);
		yynxt_tbl->td_hilen = 1;
		yynxt_tbl->td_lolen = (flex_uint32_t) عدد_بھرا_جدول_صفیں;
		yynxt_tbl->td_ڈیٹا = yynxt_ڈیٹا =
		    صفر_حافظہ_دو(yynxt_tbl->td_lolen *
			   yynxt_tbl->td_hilen,
			   حجم (flex_int32_t));
		yynxt_curr = 0;

		ساخت packtype_t *ptype = optimize_pack(0);
		/* Note: Used when ctrl.fulltbl is on. Alternately defined elsewhere */
		برآمد_str ("m4_define([[M4_HOOK_NXT_TYPE]], [[%s]])", ptype->name);
		برآمد_dec ("m4_define([[M4_HOOK_NXT_ROWS]], [[%d]])", عدد_بھرا_جدول_صفیں);
		outn ("m4_define([[M4_HOOK_NXT_BODY]], [[m4_dnl");
		outn ("M4_HOOK_TABLE_OPENER");
		اگر (gentables)
			outn ("M4_HOOK_TABLE_OPENER");

		/* Generate 0 entries for state #0. */
		برائے (i = 0; i < عدد_بھرا_جدول_صفیں; ++i) {
			mk2data (0);
			yynxt_ڈیٹا[yynxt_curr++] = 0;
		}

		اگر (gentables) {
			dataflush ();
			outn ("M4_HOOK_TABLE_CONTINUE");
		}
	}

	/* Create the first states. */

	عدد_آغاز_حالتیں = lastsc * 2;

	برائے (i = 1; i <= عدد_آغاز_حالتیں; ++i) {
		numstates = 1;

		/* For each start condition, make one state for the case when
		 * we're at the beginning of the line (the '^' operator) and
		 * one for the case when we're not.
		 */
		اگر (i % 2 == 1)
			nset[numstates] = scset[(i / 2) + 1];
		ورنہ
			nset[numstates] =
				mkbranch (scbol[i / 2], scset[i / 2]);

		nset = epsclosure (nset, &numstates, accset, &nacc,
				   &hashval);

		اگر (snstods (nset, numstates, accset, nacc, hashval, &ds)) {
			numas += nacc;
			totnst += numstates;
			++todo_اگلا;

			اگر (variable_trailing_context_قواعد && nacc > 0)
				check_trailing_context (nset, numstates,
							accset, nacc);
		}
	}

	اگر (!ctrl.fullspd) {
		اگر (!snstods (nset, 0, accset, 0, 0, &انتہا_کا_بفر_state))
			flexfatal (_
				   ("could not create unique end-of-buffer state"));

		++numas;
		++عدد_آغاز_حالتیں;
		++todo_اگلا;
	}


	جب (todo_سر < todo_اگلا) {
		targptr = 0;
		totaltrans = 0;

		برائے (i = 1; i <= numecs; ++i)
			state[i] = 0;

		ds = ++todo_سر;

		dset = dss[ds];
		dsize = dfasiz[ds];

		اگر (env.trace)
			fprintf (stderr, _("state # %d:\n"), ds);

		sympartition (dset, dsize, symlist, duplist);

		برائے (sym = 1; sym <= numecs; ++sym) {
			اگر (symlist[sym]) {
				symlist[sym] = 0;

				اگر (duplist[sym] == NIL) {
					/* Symbol has unique out-transitions. */
					numstates =
						symfollowset (dset, dsize,
							      sym, nset);
					nset = epsclosure (nset,
							   &numstates,
							   accset, &nacc,
							   &hashval);

					اگر (snstods
					    (nset, numstates, accset, nacc,
					     hashval, &newds)) {
						totnst = totnst +
							numstates;
						++todo_اگلا;
						numas += nacc;

						اگر (variable_trailing_context_قواعد && nacc > 0)
							check_trailing_context
								(nset,
								 numstates,
								 accset,
								 nacc);
					}

					state[sym] = newds;

					اگر (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 newds);

					targfreq[++targptr] = 1;
					targstate[targptr] = newds;
					++numuniq;
				}

				ورنہ {
					/* sym's equivalence class has the same
					 * transitions as duplist(sym)'s
					 * equivalence class.
					 */
					targ = state[duplist[sym]];
					state[sym] = targ;

					اگر (env.trace)
						fprintf (stderr,
							 "\t%d\t%d\n", sym,
							 targ);

					/* Update frequency count for
					 * destination state.
					 */

					i = 0;
					جب (targstate[++i] != targ) ;

					++targfreq[i];
					++numdup;
				}

				++totaltrans;
				duplist[sym] = NIL;
			}
		}


		numsnpairs += totaltrans;

		اگر (ds > عدد_آغاز_حالتیں)
			check_for_backing_اوپر (ds, state);

		اگر (nultrans) {
			nultrans[ds] = state[NUL_ec];
			state[NUL_ec] = 0;	/* remove transition */
		}

		اگر (ctrl.fulltbl) {

			/* Each time we hit here, it's another td_hilen, so we realloc. */
			yynxt_tbl->td_hilen++;
			yynxt_tbl->td_ڈیٹا = yynxt_ڈیٹا =
				realloc (yynxt_ڈیٹا,
						     yynxt_tbl->td_hilen *
						     yynxt_tbl->td_lolen *
						     حجم (flex_int32_t));
			اگر (gentables)
				outn ("M4_HOOK_TABLE_OPENER");

			/* Supply array's 0-element. */
			اگر (ds == انتہا_کا_بفر_state) {
				mk2data (-انتہا_کا_بفر_state);
				yynxt_ڈیٹا[yynxt_curr++] =
					-انتہا_کا_بفر_state;
			}
			ورنہ {
				mk2data (انتہا_کا_بفر_state);
				yynxt_ڈیٹا[yynxt_curr++] =
					انتہا_کا_بفر_state;
			}

			برائے (i = 1; i < عدد_بھرا_جدول_صفیں; ++i) {
				/* Jams are marked by negative of state
				 * number.
				 */
				mk2data (state[i] ? state[i] : -ds);
				yynxt_ڈیٹا[yynxt_curr++] =
					state[i] ? state[i] : -ds;
			}

			اگر (gentables) {
				dataflush ();
				outn ("M4_HOOK_TABLE_CONTINUE");
			}
		}

		ورنہ اگر (ctrl.fullspd)
			رکھو_state (state, ds, totaltrans);

		ورنہ اگر (ds == انتہا_کا_بفر_state)
			/* Special case this state to make sure it does what
			 * it's supposed to, i.e., jam on end-of-buffer.
			 */
			stack1 (ds, 0, 0, JAMSTATE);

		ورنہ {		/* normal, compressed state */

			/* Determine which destination state is the most
			 * common, and how many transitions to it there are.
			 */

			comfreq = 0;
			comstate = 0;

			برائے (i = 1; i <= targptr; ++i)
				اگر (targfreq[i] > comfreq) {
					comfreq = targfreq[i];
					comstate = targstate[i];
				}

			bldtbl (state, ds, totaltrans, comstate, comfreq);
		}
	}

	اگر (ctrl.fulltbl) {
		dataend ("M4_HOOK_TABLE_CLOSER");
		outn("/* body */]])");
		اگر (tablesext) {
			yytbl_ڈیٹا_compress (yynxt_tbl);
			اگر (yytbl_ڈیٹا_fwrite (&tableswr, yynxt_tbl) < 0)
				flexerror (_
					   ("Could not write yynxt_tbl[][]"));
		}
		اگر (yynxt_tbl) {
			yytbl_ڈیٹا_destroy (yynxt_tbl);
			yynxt_tbl = 0;
		}
	}

	ورنہ اگر (!ctrl.fullspd) {
		cmptmps ();	/* create compressed template entries */

		/* Create tables for all the states with only one
		 * out-transition.
		 */
		جب (onesp > 0) {
			mk1tbl (onestate[onesp], onesym[onesp],
				onenext[onesp], onedef[onesp]);
			--onesp;
		}

		mkdeftbl ();
	}


	آزاد(accset);
	آزاد(nset);

	واپس (yynxt_tbl != تہی) ? (yynxt_tbl->td_hilen * حجم(int32_t)) : 0;
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

ساکن صحیح snstods(صحیح sns[], صحیح numstates, صحیح accset[], صحیح nacc, صحیح hashval, صحیح *newds_addr)
{
	صحیح didsort = 0;
	صحیح i, j;
	صحیح newds, *oldsns;

	برائے (i = 1; i <= lastdfa; ++i)
		اگر (hashval == dhash[i]) {
			اگر (numstates == dfasiz[i]) {
				oldsns = dss[i];

				اگر (!didsort) {
					/* We sort the states in sns so we
					 * can compare it to oldsns quickly.
					 */
					qsort (&sns [1], (size_t) numstates, حجم (sns [1]), intcmp);
					didsort = 1;
				}

				برائے (j = 1; j <= numstates; ++j)
					اگر (sns[j] != oldsns[j])
						توڑو;

				اگر (j > numstates) {
					++dfaeql;
					*newds_addr = i;
					واپس 0;
				}

				++hshcol;
			}

			ورنہ
				++hshsave;
		}

	/* Make a new dfa. */

	اگر (++lastdfa >= current_max_dfas)
		increase_max_dfas ();

	newds = lastdfa;

	dss[newds] = allocate_integer_array (numstates + 1);

	/* If we haven't already sorted the states in sns, we do so now,
	 * so that future comparisons with it can be made quickly.
	 */

	اگر (!didsort)
          	qsort (&sns [1], (size_t) numstates, حجم (sns [1]), intcmp);

	برائے (i = 1; i <= numstates; ++i)
		dss[newds][i] = sns[i];

	dfasiz[newds] = numstates;
	dhash[newds] = hashval;

	اگر (nacc == 0) {
		اگر (reject)
			dfaacc[newds].dfaacc_سیٹ = تہی;
		ورنہ
			dfaacc[newds].dfaacc_state = 0;

		accsiz[newds] = 0;
	}

	ورنہ اگر (reject) {
		/* We sort the accepting set in increasing order so the
		 * disambiguating rule that the first rule listed is considered
		 * match in the event of ties will work.
		 */

		qsort (&accset [1], (size_t) nacc, حجم (accset [1]), intcmp);

		dfaacc[newds].dfaacc_سیٹ =
			allocate_integer_array (nacc + 1);

		/* Save the accepting set for later */
		برائے (i = 1; i <= nacc; ++i) {
			dfaacc[newds].dfaacc_سیٹ[i] = accset[i];

			اگر (accset[i] <= عدد_قواعد)
				/* Who knows, perhaps a REJECT can yield
				 * this rule.
				 */
				قاعدہ_useful[accset[i]] = true;
		}

		accsiz[newds] = nacc;
	}

	ورنہ {
		/* Find lowest numbered rule so the disambiguating rule
		 * will work.
		 */
		j = عدد_قواعد + 1;

		برائے (i = 1; i <= nacc; ++i)
			اگر (accset[i] < j)
				j = accset[i];

		dfaacc[newds].dfaacc_state = j;

		اگر (j <= عدد_قواعد)
			قاعدہ_useful[j] = true;
	}

	*newds_addr = newds;

	واپس 1;
}


/* symfollowset - follow the symbol transitions one step
 *
 * synopsis
 *    numstates = symfollowset( int ds[current_max_dfa_size], int dsize,
 *				int transsym, int nset[current_max_dfa_size] );
 */

ساکن صحیح symfollowset(صحیح ds[], صحیح dsize, صحیح transsym, صحیح nset[])
{
	صحیح     ns, tsp, sym, i, j, lenccl, ch, numstates, ccllist;

	numstates = 0;

	برائے (i = 1; i <= dsize; ++i) {	/* for each nfa state ns in the state set of ds */
		ns = ds[i];
		sym = transchar[ns];
		tsp = trans1[ns];

		اگر (sym < 0) {	/* it's a character class */
			sym = -sym;
			ccllist = cclmap[sym];
			lenccl = ccllen[sym];

			اگر (cclng[sym]) {
				برائے (j = 0; j < lenccl; ++j) {
					/* Loop through negated character
					 * class.
					 */
					ch = ccltbl[ccllist + j];

					اگر (ch == 0)
						ch = NUL_ec;

					اگر (ch > transsym)
						/* Transsym isn't in negated
						 * ccl.
						 */
						توڑو;

					ورنہ اگر (ch == transsym)
						/* next 2 */
						جاؤ bottom;
				}

				/* Didn't find transsym in ccl. */
				nset[++numstates] = tsp;
			}

			ورنہ
				برائے (j = 0; j < lenccl; ++j) {
					ch = ccltbl[ccllist + j];

					اگر (ch == 0)
						ch = NUL_ec;

					اگر (ch > transsym)
						توڑو;
					ورنہ اگر (ch == transsym) {
						nset[++numstates] = tsp;
						توڑو;
					}
				}
		}

		ورنہ اگر (sym == SYM_EPSILON) {	/* do nothing */
		}

		ورنہ اگر (ABS (ecgroup[sym]) == transsym)
			nset[++numstates] = tsp;

	      bottom:;
	}

	واپس numstates;
}


/* sympartition - partition characters with same out-transitions
 *
 * synopsis
 *    sympartition( int ds[current_max_dfa_size], int numstates,
 *			int symlist[numecs], int duplist[numecs] );
 */

ساکن خالی sympartition(صحیح ds[], صحیح numstates, صحیح symlist[], صحیح duplist[])
{
	صحیح     tch, i, j, k, ns, dupfwd[CSIZE + 1], lenccl, cclp, ich;

	/* Partitioning is done by creating equivalence classes for those
	 * characters which have out-transitions from the given state.  Thus
	 * we are really creating equivalence classes of equivalence classes.
	 */

	برائے (i = 1; i <= numecs; ++i) {	/* initialize equivalence class list */
		duplist[i] = i - 1;
		dupfwd[i] = i + 1;
	}

	duplist[1] = NIL;
	dupfwd[numecs] = NIL;

	برائے (i = 1; i <= numstates; ++i) {
		ns = ds[i];
		tch = transchar[ns];

		اگر (tch != SYM_EPSILON) {
			اگر (tch < -lastccl || tch >= ctrl.csize) {
				flexfatal (_
					   ("bad transition character detected in sympartition()"));
			}

			اگر (tch >= 0) {	/* character transition */
				صحیح     ec = ecgroup[tch];

				mkechar (ec, dupfwd, duplist);
				symlist[ec] = 1;
			}

			ورنہ {	/* character class */
				tch = -tch;

				lenccl = ccllen[tch];
				cclp = cclmap[tch];
				mkeccl (ccltbl + cclp, lenccl, dupfwd,
					duplist, numecs, NUL_ec);

				اگر (cclng[tch]) {
					j = 0;

					برائے (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						اگر (ich == 0)
							ich = NUL_ec;

						برائے (++j; j < ich; ++j)
							symlist[j] = 1;
					}

					برائے (++j; j <= numecs; ++j)
						symlist[j] = 1;
				}

				ورنہ
					برائے (k = 0; k < lenccl; ++k) {
						ich = ccltbl[cclp + k];

						اگر (ich == 0)
							ich = NUL_ec;

						symlist[ich] = 1;
					}
			}
		}
	}
}
