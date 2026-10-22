/* nfa - NFA construction routines */

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

#ضمن "flexdef.h"


/* declare functions that have forward references */

صحيح	dupmachine(صحيح);
فراغ	mkxtion(صحيح, صحيح);


/* add_accept - add an accepting state to a machine
 *
 * accepting_number becomes mach's accepting number.
 */

فراغ    جمع_کن_accept (صحيح mach, صحيح accepting_عدد)
{
	/* Hang the accepting number off an epsilon state.  if it is associated
	 * with a state that has a non-epsilon out-transition, then the state
	 * will accept BEFORE it makes that transition, i.e., one character
	 * too soon.
	 */

	إذا (transchar[finalst[mach]] == SYM_EPSILON)
		accptnum[finalst[mach]] = accepting_عدد;

	وإلا {
		صحيح     astate = mkstate (SYM_EPSILON);

		accptnum[astate] = accepting_عدد;
		(فراغ) link_machines (mach, astate);
	}
}


/* copysingl - make a given number of copies of a singleton machine
 *
 * synopsis
 *
 *   newsng = copysingl( singl, num );
 *
 *     newsng - a new singleton composed of num copies of singl
 *     singl  - a singleton machine
 *     num    - the number of copies of singl to be present in newsng
 */

صحيح     copysingl (صحيح singl, صحيح رقم)
{
	صحيح     copy, i;

	copy = mkstate (SYM_EPSILON);

	لكل (i = 1; i <= رقم; ++i)
		copy = link_machines (copy, dupmachine (singl));

	أرجع copy;
}


/* dumpnfa - debugging routine to write out an nfa */

فراغ    dumpnfa (صحيح state1)
{
	صحيح     sym, tsp1, tsp2, anum, ns;

	fprintf (stderr,
		 _
		 ("\n\n********** beginning dump of nfa with start state %d\n"),
		 state1);

	/* We probably should loop starting at firstst[state1] and going to
	 * lastst[state1], but they're not maintained properly when we "or"
	 * all of the rules together.  So we use our knowledge that the machine
	 * starts at state 1 and ends at lastnfa.
	 */

	/* for ( ns = firstst[state1]; ns <= lastst[state1]; ++ns ) */
	لكل (ns = 1; ns <= lastnfa; ++ns) {
		fprintf (stderr, _("state # %4d\t"), ns);

		sym = transchar[ns];
		tsp1 = trans1[ns];
		tsp2 = trans2[ns];
		anum = accptnum[ns];

		fprintf (stderr, "%3d:  %4d, %4d", sym, tsp1, tsp2);

		إذا (anum != NIL)
			fprintf (stderr, "  [%d]", anum);

		fprintf (stderr, "\n");
	}

	fprintf (stderr, _("********** end of dump\n"));
}


/* dupmachine - make a duplicate of a given machine
 *
 * synopsis
 *
 *   copy = dupmachine( mach );
 *
 *     copy - holds duplicate of mach
 *     mach - machine to be duplicated
 *
 * note that the copy of mach is NOT an exact duplicate; rather, all the
 * transition states values are adjusted so that the copy is self-contained,
 * as the original should have been.
 *
 * also note that the original MUST be contiguous, with its low and high
 * states accessible by the arrays firstst and lastst
 */

صحيح     dupmachine (صحيح mach)
{
	صحيح     i, init, state_جابه_جایی;
	صحيح     state = 0;
	صحيح     آخرین = lastst[mach];

	لكل (i = firstst[mach]; i <= آخرین; ++i) {
		state = mkstate (transchar[i]);

		إذا (trans1[i] != NO_TRANSITION) {
			mkxtion (finalst[state], trans1[i] + state - i);

			إذا (transchar[i] == SYM_EPSILON &&
			    trans2[i] != NO_TRANSITION)
					mkxtion (finalst[state],
						 trans2[i] + state - i);
		}

		accptnum[state] = accptnum[i];
	}

	إذا (state == 0)
		flexfatal (_("empty machine in dupmachine()"));

	state_جابه_جایی = state - i + 1;

	init = mach + state_جابه_جایی;
	firstst[init] = firstst[mach] + state_جابه_جایی;
	finalst[init] = finalst[mach] + state_جابه_جایی;
	lastst[init] = lastst[mach] + state_جابه_جایی;

	أرجع init;
}


/* finish_rule - finish up the processing for a rule
 *
 * An accepting number is added to the given machine.  If variable_trail_rule
 * is true then the rule has trailing context and both the head and trail
 * are variable size.  Otherwise if headcnt or trailcnt is non-zero then
 * the machine recognizes a pattern with trailing context and headcnt is
 * the number of characters in the matched part of the pattern, or zero
 * if the matched part has variable length.  trailcnt is the number of
 * trailing context characters in the pattern, or zero if the trailing
 * context has variable length.
 */

فراغ    پایان_قاعده (صحيح mach, bool variable_trail_قاعده, صحيح headcnt, صحيح trailcnt,
		     صحيح pcont_act)
{
	حرف    action_متن[MAXLINE];

	جمع_کن_accept (mach, رقم_قواعد);

	/* We did this in new_rule(), but it often gets the wrong
	 * number because we do it before we start parsing the current rule.
	 */
	قاعده_linenum[رقم_قواعد] = linenum;

	/* If this is a continued action, then the line-number has already
	 * been updated, giving us the wrong number.
	 */
	إذا (continued_action)
		--قاعده_linenum[رقم_قواعد];


	/* If the previous rule was continued action, then we inherit the
	 * previous newline flag, possibly overriding the current one.
	 */
	إذا (pcont_act && قاعده_has_nl[رقم_قواعد - 1])
		قاعده_has_nl[رقم_قواعد] = true;

	snprintf (action_متن, حجم(action_متن), "M4_HOOK_NORMAL_STATE_CASE_ARM(%d)\n", رقم_قواعد);
	جمع_کن_action (action_متن);
	إذا (قاعده_has_nl[رقم_قواعد]) {
		snprintf (action_متن, حجم(action_متن), "M4_HOOK_COMMENT_OPEN rule %d can match eol M4_HOOK_COMMENT_CLOSE\n",
			 رقم_قواعد);
		جمع_کن_action (action_متن);
	}


	إذا (variable_trail_قاعده) {
		قاعده_type[رقم_قواعد] = قاعده_VARIABLE;

		إذا (env.performance_hint > 0)
			fprintf (stderr,
				 _
				 ("Variable trailing context rule at line %d\n"),
				 قاعده_linenum[رقم_قواعد]);

		variable_trailing_context_قواعد = true;
	}

	وإلا {
		قاعده_type[رقم_قواعد] = قاعده_نرمال;

		إذا (headcnt > 0 || trailcnt > 0) {
			/* Do trailing context magic to not match the trailing
			 * characters.
			 */
			جمع_کن_action ("M4_HOOK_RELEASE_YYTEXT\n");

			إذا (headcnt > 0) {
				إذا (قاعده_has_nl[رقم_قواعد]) {
					snprintf (action_متن, حجم(action_متن),
						"M4_HOOK_LINE_FORWARD(%d)\n", headcnt);
					جمع_کن_action (action_متن);
				}
				snprintf (action_متن, حجم(action_متن), "M4_HOOK_CHAR_FORWARD(%d)\n",
					 headcnt);
				جمع_کن_action (action_متن);
			}

			وإلا {
				إذا (قاعده_has_nl[رقم_قواعد]) {
					snprintf (action_متن, حجم(action_متن),
						 "M4_HOOK_LINE_REWIND(%d)\n", trailcnt);
					جمع_کن_action (action_متن);
				}

				snprintf (action_متن, حجم(action_متن), "M4_HOOK_CHAR_REWIND(%d)\n",
					 trailcnt);
				جمع_کن_action (action_متن);
			}

			جمع_کن_action
				("M4_HOOK_TAKE_YYTEXT\n");
		}
	}

	/* Okay, in the action code at this point yytext and yyleng have
	 * their proper final values for this rule, so here's the point
	 * to do any user action.  But don't do it for continued actions,
	 * as that'll result in multiple rule-setup calls.
	 */
	إذا (!continued_action)
		جمع_کن_action ("M4_HOOK_SET_RULE_SETUP\n");

	سطر_directive_بیرون(عدم, infilename, linenum);
        جمع_کن_action("[[");
}


/* link_machines - connect two machines together
 *
 * synopsis
 *
 *   new = link_machines( first, last );
 *
 *     new    - a machine constructed by connecting first to last
 *     first  - the machine whose successor is to be last
 *     last   - the machine whose predecessor is to be first
 *
 * note: this routine concatenates the machine first with the machine
 *  last to produce a machine new which will pattern-match first first
 *  and then last, and will fail if either of the sub-patterns fails.
 *  FIRST is set to new by the operation.  last is unmolested.
 */

صحيح     link_machines (صحيح اولی, صحيح آخرین)
{
	إذا (اولی == NIL)
		أرجع آخرین;

	وإلا إذا (آخرین == NIL)
		أرجع اولی;

	وإلا {
		mkxtion (finalst[اولی], آخرین);
		finalst[اولی] = finalst[آخرین];
		lastst[اولی] = MAX (lastst[اولی], lastst[آخرین]);
		firstst[اولی] = MIN (firstst[اولی], firstst[آخرین]);

		أرجع اولی;
	}
}


/* mark_beginning_as_normal - mark each "beginning" state in a machine
 *                            as being a "normal" (i.e., not trailing context-
 *                            associated) states
 *
 * The "beginning" states are the epsilon closure of the first state
 */

فراغ    mark_beginning_as_نرمال (صحيح mach)
{
	بدل (state_type[mach]) {
	حالة STATE_نرمال:
		/* Oh, we've already visited here. */
		أرجع;

	حالة STATE_TRAILING_CONTEXT:
		state_type[mach] = STATE_نرمال;

		إذا (transchar[mach] == SYM_EPSILON) {
			إذا (trans1[mach] != NO_TRANSITION)
				mark_beginning_as_نرمال (trans1[mach]);

			إذا (trans2[mach] != NO_TRANSITION)
				mark_beginning_as_نرمال (trans2[mach]);
		}
		اكسر;

	افتراضي:
		flexerror (_
			   ("bad state type in mark_beginning_as_normal()"));
		اكسر;
	}
}


/* mkbranch - make a machine that branches to two machines
 *
 * synopsis
 *
 *   branch = mkbranch( first, second );
 *
 *     branch - a machine which matches either first's pattern or second's
 *     first, second - machines whose patterns are to be or'ed (the | operator)
 *
 * Note that first and second are NEITHER destroyed by the operation.  Also,
 * the resulting machine CANNOT be used with any other "mk" operation except
 * more mkbranch's.  Compare with mkor()
 */

صحيح     mkbranch (صحيح اولی, صحيح دومی)
{
	صحيح     eps;

	إذا (اولی == NO_TRANSITION)
		أرجع دومی;

	وإلا إذا (دومی == NO_TRANSITION)
		أرجع اولی;

	eps = mkstate (SYM_EPSILON);

	mkxtion (eps, اولی);
	mkxtion (eps, دومی);

	أرجع eps;
}


/* mkclos - convert a machine into a closure
 *
 * synopsis
 *   new = mkclos( state );
 *
 * new - a new state which matches the closure of "state"
 */

صحيح     mkclos (صحيح state)
{
	أرجع mkopt (mkposcl (state));
}


/* mkopt - make a machine optional
 *
 * synopsis
 *
 *   new = mkopt( mach );
 *
 *     new  - a machine which optionally matches whatever mach matched
 *     mach - the machine to make optional
 *
 * notes:
 *     1. mach must be the last machine created
 *     2. mach is destroyed by the call
 */

صحيح     mkopt (صحيح mach)
{
	صحيح     eps;

	إذا (!SUPER_FREE_EPSILON (finalst[mach])) {
		eps = mkstate (SYM_EPSILON);
		mach = link_machines (mach, eps);
	}

	/* Can't skimp on the following if FREE_EPSILON(mach) is true because
	 * some state interior to "mach" might point back to the beginning
	 * for a closure.
	 */
	eps = mkstate (SYM_EPSILON);
	mach = link_machines (eps, mach);

	mkxtion (mach, finalst[mach]);

	أرجع mach;
}


/* mkor - make a machine that matches either one of two machines
 *
 * synopsis
 *
 *   new = mkor( first, second );
 *
 *     new - a machine which matches either first's pattern or second's
 *     first, second - machines whose patterns are to be or'ed (the | operator)
 *
 * note that first and second are both destroyed by the operation
 * the code is rather convoluted because an attempt is made to minimize
 * the number of epsilon states needed
 */

صحيح     mkor (صحيح اولی, صحيح دومی)
{
	صحيح     eps, orend;

	إذا (اولی == NIL)
		أرجع دومی;

	وإلا إذا (دومی == NIL)
		أرجع اولی;

	وإلا {
		/* See comment in mkopt() about why we can't use the first
		 * state of "first" or "second" if they satisfy "FREE_EPSILON".
		 */
		eps = mkstate (SYM_EPSILON);

		اولی = link_machines (eps, اولی);

		mkxtion (اولی, دومی);

		إذا (SUPER_FREE_EPSILON (finalst[اولی]) &&
		    accptnum[finalst[اولی]] == NIL) {
			orend = finalst[اولی];
			mkxtion (finalst[دومی], orend);
		}

		وإلا إذا (SUPER_FREE_EPSILON (finalst[دومی]) &&
			 accptnum[finalst[دومی]] == NIL) {
			orend = finalst[دومی];
			mkxtion (finalst[اولی], orend);
		}

		وإلا {
			eps = mkstate (SYM_EPSILON);

			اولی = link_machines (اولی, eps);
			orend = finalst[اولی];

			mkxtion (finalst[دومی], orend);
		}
	}

	firstst[اولی] = MIN(firstst[اولی], firstst[دومی]);

	finalst[اولی] = orend;
	أرجع اولی;
}


/* mkposcl - convert a machine into a positive closure
 *
 * synopsis
 *   new = mkposcl( state );
 *
 *    new - a machine matching the positive closure of "state"
 */

صحيح     mkposcl (صحيح state)
{
	صحيح     eps;

	إذا (SUPER_FREE_EPSILON (finalst[state])) {
		mkxtion (finalst[state], state);
		أرجع state;
	}

	وإلا {
		eps = mkstate (SYM_EPSILON);
		mkxtion (eps, state);
		أرجع link_machines (state, eps);
	}
}


/* mkrep - make a replicated machine
 *
 * synopsis
 *   new = mkrep( mach, lb, ub );
 *
 *    new - a machine that matches whatever "mach" matched from "lb"
 *          number of times to "ub" number of times
 *
 * note
 *   if "ub" is INFINITE_REPEAT then "new" matches "lb" or more occurrences of "mach"
 */

صحيح     mkrep (صحيح mach, صحيح lb, صحيح ub)
{
	صحيح     پایه_mach, دم, copy, i;

	پایه_mach = copysingl (mach, lb - 1);

	إذا (ub == INFINITE_REPEAT) {
		copy = dupmachine (mach);
		mach = link_machines (mach,
				      link_machines (پایه_mach,
						     mkclos (copy)));
	}

	وإلا {
		دم = mkstate (SYM_EPSILON);

		لكل (i = lb; i < ub; ++i) {
			copy = dupmachine (mach);
			دم = mkopt (link_machines (copy, دم));
		}

		mach =
			link_machines (mach,
				       link_machines (پایه_mach, دم));
	}

	أرجع mach;
}


/* mkstate - create a state with a transition on a given symbol
 *
 * synopsis
 *
 *   state = mkstate( sym );
 *
 *     state - a new state matching sym
 *     sym   - the symbol the new state is to have an out-transition on
 *
 * note that this routine makes new states in ascending order through the
 * state array (and increments LASTNFA accordingly).  The routine DUPMACHINE
 * relies on machines being made in ascending order and that they are
 * CONTIGUOUS.  Change it and you will have to rewrite DUPMACHINE (kludge
 * that it admittedly is)
 */

صحيح     mkstate (صحيح sym)
{
	إذا (++lastnfa >= current_mns) {
		إذا ((current_mns += MNS_INCREMENT) >= بیشینه_mns)
			lerr(_
				("input rules are too complicated (>= %d NFA states)"),
current_mns);

		++رقم_reallocs;

		firstst = reallocate_integer_array (firstst, current_mns);
		lastst = reallocate_integer_array (lastst, current_mns);
		finalst = reallocate_integer_array (finalst, current_mns);
		transchar =
			reallocate_integer_array (transchar, current_mns);
		trans1 = reallocate_integer_array (trans1, current_mns);
		trans2 = reallocate_integer_array (trans2, current_mns);
		accptnum =
			reallocate_integer_array (accptnum, current_mns);
		assoc_قاعده =
			reallocate_integer_array (assoc_قاعده, current_mns);
		state_type =
			reallocate_integer_array (state_type, current_mns);
	}

	firstst[lastnfa] = lastnfa;
	finalst[lastnfa] = lastnfa;
	lastst[lastnfa] = lastnfa;
	transchar[lastnfa] = sym;
	trans1[lastnfa] = NO_TRANSITION;
	trans2[lastnfa] = NO_TRANSITION;
	accptnum[lastnfa] = NIL;
	assoc_قاعده[lastnfa] = رقم_قواعد;
	state_type[lastnfa] = current_state_type;

	/* Fix up equivalence classes base on this transition.  Note that any
	 * character which has its own transition gets its own equivalence
	 * class.  Thus only characters which are only in character classes
	 * have a chance at being in the same equivalence class.  E.g. "a|b"
	 * puts 'a' and 'b' into two different equivalence classes.  "[ab]"
	 * puts them in the same equivalence class (barring other differences
	 * elsewhere in the input).
	 */

	إذا (sym < 0) {
		/* We don't have to update the equivalence classes since
		 * that was already done when the ccl was created for the
		 * first time.
		 */
	}

	وإلا إذا (sym == SYM_EPSILON)
		++numeps;

	وإلا {
		check_char (sym);

		إذا (ctrl.useecs)
			/* Map NUL's to csize. */
			mkechar (sym ? sym : ctrl.csize, nextecm, ecgroup);
	}

	أرجع lastnfa;
}


/* mkxtion - make a transition from one state to another
 *
 * synopsis
 *
 *   mkxtion( statefrom, stateto );
 *
 *     statefrom - the state from which the transition is to be made
 *     stateto   - the state to which the transition is to be made
 */

فراغ    mkxtion (صحيح statefrom, صحيح stateto)
{
	إذا (trans1[statefrom] == NO_TRANSITION)
		trans1[statefrom] = stateto;

	وإلا إذا ((transchar[statefrom] != SYM_EPSILON) ||
		 (trans2[statefrom] != NO_TRANSITION))
		flexfatal (_("found too many transitions in mkxtion()"));

	وإلا {			/* second out-transition for an epsilon state */
		++eps2;
		trans2[statefrom] = stateto;
	}
}

/* new_rule - initialize for a new rule */

فراغ    new_قاعده (فراغ)
{
	إذا (++رقم_قواعد >= current_max_قواعد) {
		++رقم_reallocs;
		current_max_قواعد += MAX_قواعد_INCREMENT;
		قاعده_type = reallocate_integer_array (قاعده_type,
						      current_max_قواعد);
		قاعده_linenum = reallocate_integer_array (قاعده_linenum,
							 current_max_قواعد);
		قاعده_useful = reallocate_array(قاعده_useful,
					current_max_قواعد, حجم(حرف));
		قاعده_has_nl = reallocate_array(قاعده_has_nl,
					current_max_قواعد, حجم(حرف));
	}

	إذا (رقم_قواعد > MAX_قاعده)
		lerr (_("too many rules (> %d)!"), MAX_قاعده);

	قاعده_linenum[رقم_قواعد] = linenum;
	قاعده_useful[رقم_قواعد] = false;
	قاعده_has_nl[رقم_قواعد] = false;
}
