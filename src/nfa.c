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

#అన్తర్భావ "flexdef.h"


/* declare functions that have forward references */

పూర్ణాంకం	dupmachine(పూర్ణాంకం);
శూన్య	mkxtion(పూర్ణాంకం, పూర్ణాంకం);


/* add_accept - add an accepting state to a machine
 *
 * accepting_number becomes mach's accepting number.
 */

శూన్య    కూడు_accept (పూర్ణాంకం mach, పూర్ణాంకం accepting_సంఖ్య)
{
	/* Hang the accepting number off an epsilon state.  if it is associated
	 * with a state that has a non-epsilon out-transition, then the state
	 * will accept BEFORE it makes that transition, i.e., one character
	 * too soon.
	 */

	ఒకవేళ (transchar[finalst[mach]] == SYM_EPSILON)
		accptnum[finalst[mach]] = accepting_సంఖ్య;

	లేకపోతే {
		పూర్ణాంకం     astate = mkstate (SYM_EPSILON);

		accptnum[astate] = accepting_సంఖ్య;
		(శూన్య) link_machines (mach, astate);
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

పూర్ణాంకం     copysingl (పూర్ణాంకం singl, పూర్ణాంకం అంకె)
{
	పూర్ణాంకం     copy, i;

	copy = mkstate (SYM_EPSILON);

	కొరకు (i = 1; i <= అంకె; ++i)
		copy = link_machines (copy, dupmachine (singl));

	తిరిగి copy;
}


/* dumpnfa - debugging routine to write out an nfa */

శూన్య    dumpnfa (పూర్ణాంకం state1)
{
	పూర్ణాంకం     sym, tsp1, tsp2, anum, ns;

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
	కొరకు (ns = 1; ns <= lastnfa; ++ns) {
		fprintf (stderr, _("state # %4d\t"), ns);

		sym = transchar[ns];
		tsp1 = trans1[ns];
		tsp2 = trans2[ns];
		anum = accptnum[ns];

		fprintf (stderr, "%3d:  %4d, %4d", sym, tsp1, tsp2);

		ఒకవేళ (anum != NIL)
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

పూర్ణాంకం     dupmachine (పూర్ణాంకం mach)
{
	పూర్ణాంకం     i, init, state_స్థానభ్రంశం;
	పూర్ణాంకం     state = 0;
	పూర్ణాంకం     చివరి = lastst[mach];

	కొరకు (i = firstst[mach]; i <= చివరి; ++i) {
		state = mkstate (transchar[i]);

		ఒకవేళ (trans1[i] != NO_TRANSITION) {
			mkxtion (finalst[state], trans1[i] + state - i);

			ఒకవేళ (transchar[i] == SYM_EPSILON &&
			    trans2[i] != NO_TRANSITION)
					mkxtion (finalst[state],
						 trans2[i] + state - i);
		}

		accptnum[state] = accptnum[i];
	}

	ఒకవేళ (state == 0)
		flexfatal (_("empty machine in dupmachine()"));

	state_స్థానభ్రంశం = state - i + 1;

	init = mach + state_స్థానభ్రంశం;
	firstst[init] = firstst[mach] + state_స్థానభ్రంశం;
	finalst[init] = finalst[mach] + state_స్థానభ్రంశం;
	lastst[init] = lastst[mach] + state_స్థానభ్రంశం;

	తిరిగి init;
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

శూన్య    ముగింపు_నియమం (పూర్ణాంకం mach, bool variable_trail_నియమం, పూర్ణాంకం headcnt, పూర్ణాంకం trailcnt,
		     పూర్ణాంకం pcont_act)
{
	అక్షరం    action_పాఠ్యం[MAXLINE];

	కూడు_accept (mach, అంకె_నియమాలు);

	/* We did this in new_rule(), but it often gets the wrong
	 * number because we do it before we start parsing the current rule.
	 */
	నియమం_linenum[అంకె_నియమాలు] = linenum;

	/* If this is a continued action, then the line-number has already
	 * been updated, giving us the wrong number.
	 */
	ఒకవేళ (continued_action)
		--నియమం_linenum[అంకె_నియమాలు];


	/* If the previous rule was continued action, then we inherit the
	 * previous newline flag, possibly overriding the current one.
	 */
	ఒకవేళ (pcont_act && నియమం_has_nl[అంకె_నియమాలు - 1])
		నియమం_has_nl[అంకె_నియమాలు] = true;

	snprintf (action_పాఠ్యం, పరిమాణం(action_పాఠ్యం), "M4_HOOK_NORMAL_STATE_CASE_ARM(%d)\n", అంకె_నియమాలు);
	కూడు_action (action_పాఠ్యం);
	ఒకవేళ (నియమం_has_nl[అంకె_నియమాలు]) {
		snprintf (action_పాఠ్యం, పరిమాణం(action_పాఠ్యం), "M4_HOOK_COMMENT_OPEN rule %d can match eol M4_HOOK_COMMENT_CLOSE\n",
			 అంకె_నియమాలు);
		కూడు_action (action_పాఠ్యం);
	}


	ఒకవేళ (variable_trail_నియమం) {
		నియమం_type[అంకె_నియమాలు] = నియమం_VARIABLE;

		ఒకవేళ (env.performance_hint > 0)
			fprintf (stderr,
				 _
				 ("Variable trailing context rule at line %d\n"),
				 నియమం_linenum[అంకె_నియమాలు]);

		variable_trailing_context_నియమాలు = true;
	}

	లేకపోతే {
		నియమం_type[అంకె_నియమాలు] = నియమం_సాధారణ;

		ఒకవేళ (headcnt > 0 || trailcnt > 0) {
			/* Do trailing context magic to not match the trailing
			 * characters.
			 */
			కూడు_action ("M4_HOOK_RELEASE_YYTEXT\n");

			ఒకవేళ (headcnt > 0) {
				ఒకవేళ (నియమం_has_nl[అంకె_నియమాలు]) {
					snprintf (action_పాఠ్యం, పరిమాణం(action_పాఠ్యం),
						"M4_HOOK_LINE_FORWARD(%d)\n", headcnt);
					కూడు_action (action_పాఠ్యం);
				}
				snprintf (action_పాఠ్యం, పరిమాణం(action_పాఠ్యం), "M4_HOOK_CHAR_FORWARD(%d)\n",
					 headcnt);
				కూడు_action (action_పాఠ్యం);
			}

			లేకపోతే {
				ఒకవేళ (నియమం_has_nl[అంకె_నియమాలు]) {
					snprintf (action_పాఠ్యం, పరిమాణం(action_పాఠ్యం),
						 "M4_HOOK_LINE_REWIND(%d)\n", trailcnt);
					కూడు_action (action_పాఠ్యం);
				}

				snprintf (action_పాఠ్యం, పరిమాణం(action_పాఠ్యం), "M4_HOOK_CHAR_REWIND(%d)\n",
					 trailcnt);
				కూడు_action (action_పాఠ్యం);
			}

			కూడు_action
				("M4_HOOK_TAKE_YYTEXT\n");
		}
	}

	/* Okay, in the action code at this point yytext and yyleng have
	 * their proper final values for this rule, so here's the point
	 * to do any user action.  But don't do it for continued actions,
	 * as that'll result in multiple rule-setup calls.
	 */
	ఒకవేళ (!continued_action)
		కూడు_action ("M4_HOOK_SET_RULE_SETUP\n");

	పంక్తి_directive_బహిర్గతం(ఖాళీ, infilename, linenum);
        కూడు_action("[[");
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

పూర్ణాంకం     link_machines (పూర్ణాంకం మొదటి, పూర్ణాంకం చివరి)
{
	ఒకవేళ (మొదటి == NIL)
		తిరిగి చివరి;

	లేకపోతే ఒకవేళ (చివరి == NIL)
		తిరిగి మొదటి;

	లేకపోతే {
		mkxtion (finalst[మొదటి], చివరి);
		finalst[మొదటి] = finalst[చివరి];
		lastst[మొదటి] = MAX (lastst[మొదటి], lastst[చివరి]);
		firstst[మొదటి] = MIN (firstst[మొదటి], firstst[చివరి]);

		తిరిగి మొదటి;
	}
}


/* mark_beginning_as_normal - mark each "beginning" state in a machine
 *                            as being a "normal" (i.e., not trailing context-
 *                            associated) states
 *
 * The "beginning" states are the epsilon closure of the first state
 */

శూన్య    mark_beginning_as_సాధారణ (పూర్ణాంకం mach)
{
	ఎంపిక (state_type[mach]) {
	స్థితి STATE_సాధారణ:
		/* Oh, we've already visited here. */
		తిరిగి;

	స్థితి STATE_TRAILING_CONTEXT:
		state_type[mach] = STATE_సాధారణ;

		ఒకవేళ (transchar[mach] == SYM_EPSILON) {
			ఒకవేళ (trans1[mach] != NO_TRANSITION)
				mark_beginning_as_సాధారణ (trans1[mach]);

			ఒకవేళ (trans2[mach] != NO_TRANSITION)
				mark_beginning_as_సాధారణ (trans2[mach]);
		}
		ఆపు;

	అప్రమేయ:
		flexerror (_
			   ("bad state type in mark_beginning_as_normal()"));
		ఆపు;
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

పూర్ణాంకం     mkbranch (పూర్ణాంకం మొదటి, పూర్ణాంకం రెండవ)
{
	పూర్ణాంకం     eps;

	ఒకవేళ (మొదటి == NO_TRANSITION)
		తిరిగి రెండవ;

	లేకపోతే ఒకవేళ (రెండవ == NO_TRANSITION)
		తిరిగి మొదటి;

	eps = mkstate (SYM_EPSILON);

	mkxtion (eps, మొదటి);
	mkxtion (eps, రెండవ);

	తిరిగి eps;
}


/* mkclos - convert a machine into a closure
 *
 * synopsis
 *   new = mkclos( state );
 *
 * new - a new state which matches the closure of "state"
 */

పూర్ణాంకం     mkclos (పూర్ణాంకం state)
{
	తిరిగి mkopt (mkposcl (state));
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

పూర్ణాంకం     mkopt (పూర్ణాంకం mach)
{
	పూర్ణాంకం     eps;

	ఒకవేళ (!SUPER_FREE_EPSILON (finalst[mach])) {
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

	తిరిగి mach;
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

పూర్ణాంకం     mkor (పూర్ణాంకం మొదటి, పూర్ణాంకం రెండవ)
{
	పూర్ణాంకం     eps, orend;

	ఒకవేళ (మొదటి == NIL)
		తిరిగి రెండవ;

	లేకపోతే ఒకవేళ (రెండవ == NIL)
		తిరిగి మొదటి;

	లేకపోతే {
		/* See comment in mkopt() about why we can't use the first
		 * state of "first" or "second" if they satisfy "FREE_EPSILON".
		 */
		eps = mkstate (SYM_EPSILON);

		మొదటి = link_machines (eps, మొదటి);

		mkxtion (మొదటి, రెండవ);

		ఒకవేళ (SUPER_FREE_EPSILON (finalst[మొదటి]) &&
		    accptnum[finalst[మొదటి]] == NIL) {
			orend = finalst[మొదటి];
			mkxtion (finalst[రెండవ], orend);
		}

		లేకపోతే ఒకవేళ (SUPER_FREE_EPSILON (finalst[రెండవ]) &&
			 accptnum[finalst[రెండవ]] == NIL) {
			orend = finalst[రెండవ];
			mkxtion (finalst[మొదటి], orend);
		}

		లేకపోతే {
			eps = mkstate (SYM_EPSILON);

			మొదటి = link_machines (మొదటి, eps);
			orend = finalst[మొదటి];

			mkxtion (finalst[రెండవ], orend);
		}
	}

	firstst[మొదటి] = MIN(firstst[మొదటి], firstst[రెండవ]);

	finalst[మొదటి] = orend;
	తిరిగి మొదటి;
}


/* mkposcl - convert a machine into a positive closure
 *
 * synopsis
 *   new = mkposcl( state );
 *
 *    new - a machine matching the positive closure of "state"
 */

పూర్ణాంకం     mkposcl (పూర్ణాంకం state)
{
	పూర్ణాంకం     eps;

	ఒకవేళ (SUPER_FREE_EPSILON (finalst[state])) {
		mkxtion (finalst[state], state);
		తిరిగి state;
	}

	లేకపోతే {
		eps = mkstate (SYM_EPSILON);
		mkxtion (eps, state);
		తిరిగి link_machines (state, eps);
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

పూర్ణాంకం     mkrep (పూర్ణాంకం mach, పూర్ణాంకం lb, పూర్ణాంకం ub)
{
	పూర్ణాంకం     పునాది_mach, తోక, copy, i;

	పునాది_mach = copysingl (mach, lb - 1);

	ఒకవేళ (ub == INFINITE_REPEAT) {
		copy = dupmachine (mach);
		mach = link_machines (mach,
				      link_machines (పునాది_mach,
						     mkclos (copy)));
	}

	లేకపోతే {
		తోక = mkstate (SYM_EPSILON);

		కొరకు (i = lb; i < ub; ++i) {
			copy = dupmachine (mach);
			తోక = mkopt (link_machines (copy, తోక));
		}

		mach =
			link_machines (mach,
				       link_machines (పునాది_mach, తోక));
	}

	తిరిగి mach;
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

పూర్ణాంకం     mkstate (పూర్ణాంకం sym)
{
	ఒకవేళ (++lastnfa >= current_mns) {
		ఒకవేళ ((current_mns += MNS_INCREMENT) >= గరిష్ఠ_mns)
			lerr(_
				("input rules are too complicated (>= %d NFA states)"),
current_mns);

		++అంకె_reallocs;

		firstst = reallocate_integer_array (firstst, current_mns);
		lastst = reallocate_integer_array (lastst, current_mns);
		finalst = reallocate_integer_array (finalst, current_mns);
		transchar =
			reallocate_integer_array (transchar, current_mns);
		trans1 = reallocate_integer_array (trans1, current_mns);
		trans2 = reallocate_integer_array (trans2, current_mns);
		accptnum =
			reallocate_integer_array (accptnum, current_mns);
		assoc_నియమం =
			reallocate_integer_array (assoc_నియమం, current_mns);
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
	assoc_నియమం[lastnfa] = అంకె_నియమాలు;
	state_type[lastnfa] = current_state_type;

	/* Fix up equivalence classes base on this transition.  Note that any
	 * character which has its own transition gets its own equivalence
	 * class.  Thus only characters which are only in character classes
	 * have a chance at being in the same equivalence class.  E.g. "a|b"
	 * puts 'a' and 'b' into two different equivalence classes.  "[ab]"
	 * puts them in the same equivalence class (barring other differences
	 * elsewhere in the input).
	 */

	ఒకవేళ (sym < 0) {
		/* We don't have to update the equivalence classes since
		 * that was already done when the ccl was created for the
		 * first time.
		 */
	}

	లేకపోతే ఒకవేళ (sym == SYM_EPSILON)
		++numeps;

	లేకపోతే {
		check_char (sym);

		ఒకవేళ (ctrl.useecs)
			/* Map NUL's to csize. */
			mkechar (sym ? sym : ctrl.csize, nextecm, ecgroup);
	}

	తిరిగి lastnfa;
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

శూన్య    mkxtion (పూర్ణాంకం statefrom, పూర్ణాంకం stateto)
{
	ఒకవేళ (trans1[statefrom] == NO_TRANSITION)
		trans1[statefrom] = stateto;

	లేకపోతే ఒకవేళ ((transchar[statefrom] != SYM_EPSILON) ||
		 (trans2[statefrom] != NO_TRANSITION))
		flexfatal (_("found too many transitions in mkxtion()"));

	లేకపోతే {			/* second out-transition for an epsilon state */
		++eps2;
		trans2[statefrom] = stateto;
	}
}

/* new_rule - initialize for a new rule */

శూన్య    new_నియమం (శూన్య)
{
	ఒకవేళ (++అంకె_నియమాలు >= current_max_నియమాలు) {
		++అంకె_reallocs;
		current_max_నియమాలు += MAX_నియమాలు_INCREMENT;
		నియమం_type = reallocate_integer_array (నియమం_type,
						      current_max_నియమాలు);
		నియమం_linenum = reallocate_integer_array (నియమం_linenum,
							 current_max_నియమాలు);
		నియమం_useful = reallocate_array(నియమం_useful,
					current_max_నియమాలు, పరిమాణం(అక్షరం));
		నియమం_has_nl = reallocate_array(నియమం_has_nl,
					current_max_నియమాలు, పరిమాణం(అక్షరం));
	}

	ఒకవేళ (అంకె_నియమాలు > MAX_నియమం)
		lerr (_("too many rules (> %d)!"), MAX_నియమం);

	నియమం_linenum[అంకె_నియమాలు] = linenum;
	నియమం_useful[అంకె_నియమాలు] = false;
	నియమం_has_nl[అంకె_నియమాలు] = false;
}
