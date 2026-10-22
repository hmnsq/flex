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

#ಅನ್ತರ್ಭಾವ "flexdef.h"


/* declare functions that have forward references */

ಪೂರ್ಣಾಂಕ	dupmachine(ಪೂರ್ಣಾಂಕ);
ಶೂನ್ಯ	mkxtion(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);


/* add_accept - add an accepting state to a machine
 *
 * accepting_number becomes mach's accepting number.
 */

ಶೂನ್ಯ    ಕೂಡಿಸು_accept (ಪೂರ್ಣಾಂಕ mach, ಪೂರ್ಣಾಂಕ accepting_ಸಂಖ್ಯೆ)
{
	/* Hang the accepting number off an epsilon state.  if it is associated
	 * with a state that has a non-epsilon out-transition, then the state
	 * will accept BEFORE it makes that transition, i.e., one character
	 * too soon.
	 */

	ಆದರೆ (transchar[finalst[mach]] == SYM_EPSILON)
		accptnum[finalst[mach]] = accepting_ಸಂಖ್ಯೆ;

	ಇಲ್ಲದಿದ್ದರೆ {
		ಪೂರ್ಣಾಂಕ     astate = mkstate (SYM_EPSILON);

		accptnum[astate] = accepting_ಸಂಖ್ಯೆ;
		(ಶೂನ್ಯ) link_machines (mach, astate);
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

ಪೂರ್ಣಾಂಕ     copysingl (ಪೂರ್ಣಾಂಕ singl, ಪೂರ್ಣಾಂಕ ಅಂಕೆ)
{
	ಪೂರ್ಣಾಂಕ     copy, i;

	copy = mkstate (SYM_EPSILON);

	ಗಾಗಿ (i = 1; i <= ಅಂಕೆ; ++i)
		copy = link_machines (copy, dupmachine (singl));

	ಹಿಂತಿರುಗಿ copy;
}


/* dumpnfa - debugging routine to write out an nfa */

ಶೂನ್ಯ    dumpnfa (ಪೂರ್ಣಾಂಕ state1)
{
	ಪೂರ್ಣಾಂಕ     sym, tsp1, tsp2, anum, ns;

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
	ಗಾಗಿ (ns = 1; ns <= lastnfa; ++ns) {
		fprintf (stderr, _("state # %4d\t"), ns);

		sym = transchar[ns];
		tsp1 = trans1[ns];
		tsp2 = trans2[ns];
		anum = accptnum[ns];

		fprintf (stderr, "%3d:  %4d, %4d", sym, tsp1, tsp2);

		ಆದರೆ (anum != NIL)
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

ಪೂರ್ಣಾಂಕ     dupmachine (ಪೂರ್ಣಾಂಕ mach)
{
	ಪೂರ್ಣಾಂಕ     i, init, state_ಸ್ಥಾನಾಂತರ;
	ಪೂರ್ಣಾಂಕ     state = 0;
	ಪೂರ್ಣಾಂಕ     ಕೊನೆಯ = lastst[mach];

	ಗಾಗಿ (i = firstst[mach]; i <= ಕೊನೆಯ; ++i) {
		state = mkstate (transchar[i]);

		ಆದರೆ (trans1[i] != NO_TRANSITION) {
			mkxtion (finalst[state], trans1[i] + state - i);

			ಆದರೆ (transchar[i] == SYM_EPSILON &&
			    trans2[i] != NO_TRANSITION)
					mkxtion (finalst[state],
						 trans2[i] + state - i);
		}

		accptnum[state] = accptnum[i];
	}

	ಆದರೆ (state == 0)
		flexfatal (_("empty machine in dupmachine()"));

	state_ಸ್ಥಾನಾಂತರ = state - i + 1;

	init = mach + state_ಸ್ಥಾನಾಂತರ;
	firstst[init] = firstst[mach] + state_ಸ್ಥಾನಾಂತರ;
	finalst[init] = finalst[mach] + state_ಸ್ಥಾನಾಂತರ;
	lastst[init] = lastst[mach] + state_ಸ್ಥಾನಾಂತರ;

	ಹಿಂತಿರುಗಿ init;
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

ಶೂನ್ಯ    ಮುಕ್ತಾಯ_ನಿಯಮ (ಪೂರ್ಣಾಂಕ mach, bool variable_trail_ನಿಯಮ, ಪೂರ್ಣಾಂಕ headcnt, ಪೂರ್ಣಾಂಕ trailcnt,
		     ಪೂರ್ಣಾಂಕ pcont_act)
{
	ಅಕ್ಷರ    action_ಪಠ್ಯ[MAXLINE];

	ಕೂಡಿಸು_accept (mach, ಅಂಕೆ_ನಿಯಮಗಳು);

	/* We did this in new_rule(), but it often gets the wrong
	 * number because we do it before we start parsing the current rule.
	 */
	ನಿಯಮ_linenum[ಅಂಕೆ_ನಿಯಮಗಳು] = linenum;

	/* If this is a continued action, then the line-number has already
	 * been updated, giving us the wrong number.
	 */
	ಆದರೆ (continued_action)
		--ನಿಯಮ_linenum[ಅಂಕೆ_ನಿಯಮಗಳು];


	/* If the previous rule was continued action, then we inherit the
	 * previous newline flag, possibly overriding the current one.
	 */
	ಆದರೆ (pcont_act && ನಿಯಮ_has_nl[ಅಂಕೆ_ನಿಯಮಗಳು - 1])
		ನಿಯಮ_has_nl[ಅಂಕೆ_ನಿಯಮಗಳು] = true;

	snprintf (action_ಪಠ್ಯ, ಗಾತ್ರ(action_ಪಠ್ಯ), "M4_HOOK_NORMAL_STATE_CASE_ARM(%d)\n", ಅಂಕೆ_ನಿಯಮಗಳು);
	ಕೂಡಿಸು_action (action_ಪಠ್ಯ);
	ಆದರೆ (ನಿಯಮ_has_nl[ಅಂಕೆ_ನಿಯಮಗಳು]) {
		snprintf (action_ಪಠ್ಯ, ಗಾತ್ರ(action_ಪಠ್ಯ), "M4_HOOK_COMMENT_OPEN rule %d can match eol M4_HOOK_COMMENT_CLOSE\n",
			 ಅಂಕೆ_ನಿಯಮಗಳು);
		ಕೂಡಿಸು_action (action_ಪಠ್ಯ);
	}


	ಆದರೆ (variable_trail_ನಿಯಮ) {
		ನಿಯಮ_type[ಅಂಕೆ_ನಿಯಮಗಳು] = ನಿಯಮ_VARIABLE;

		ಆದರೆ (env.performance_hint > 0)
			fprintf (stderr,
				 _
				 ("Variable trailing context rule at line %d\n"),
				 ನಿಯಮ_linenum[ಅಂಕೆ_ನಿಯಮಗಳು]);

		variable_trailing_context_ನಿಯಮಗಳು = true;
	}

	ಇಲ್ಲದಿದ್ದರೆ {
		ನಿಯಮ_type[ಅಂಕೆ_ನಿಯಮಗಳು] = ನಿಯಮ_ಸಾಮಾನ್ಯ;

		ಆದರೆ (headcnt > 0 || trailcnt > 0) {
			/* Do trailing context magic to not match the trailing
			 * characters.
			 */
			ಕೂಡಿಸು_action ("M4_HOOK_RELEASE_YYTEXT\n");

			ಆದರೆ (headcnt > 0) {
				ಆದರೆ (ನಿಯಮ_has_nl[ಅಂಕೆ_ನಿಯಮಗಳು]) {
					snprintf (action_ಪಠ್ಯ, ಗಾತ್ರ(action_ಪಠ್ಯ),
						"M4_HOOK_LINE_FORWARD(%d)\n", headcnt);
					ಕೂಡಿಸು_action (action_ಪಠ್ಯ);
				}
				snprintf (action_ಪಠ್ಯ, ಗಾತ್ರ(action_ಪಠ್ಯ), "M4_HOOK_CHAR_FORWARD(%d)\n",
					 headcnt);
				ಕೂಡಿಸು_action (action_ಪಠ್ಯ);
			}

			ಇಲ್ಲದಿದ್ದರೆ {
				ಆದರೆ (ನಿಯಮ_has_nl[ಅಂಕೆ_ನಿಯಮಗಳು]) {
					snprintf (action_ಪಠ್ಯ, ಗಾತ್ರ(action_ಪಠ್ಯ),
						 "M4_HOOK_LINE_REWIND(%d)\n", trailcnt);
					ಕೂಡಿಸು_action (action_ಪಠ್ಯ);
				}

				snprintf (action_ಪಠ್ಯ, ಗಾತ್ರ(action_ಪಠ್ಯ), "M4_HOOK_CHAR_REWIND(%d)\n",
					 trailcnt);
				ಕೂಡಿಸು_action (action_ಪಠ್ಯ);
			}

			ಕೂಡಿಸು_action
				("M4_HOOK_TAKE_YYTEXT\n");
		}
	}

	/* Okay, in the action code at this point yytext and yyleng have
	 * their proper final values for this rule, so here's the point
	 * to do any user action.  But don't do it for continued actions,
	 * as that'll result in multiple rule-setup calls.
	 */
	ಆದರೆ (!continued_action)
		ಕೂಡಿಸು_action ("M4_HOOK_SET_RULE_SETUP\n");

	ಸಾಲು_directive_ಹೊರಹೋಗು(ಖಾಲಿ, infilename, linenum);
        ಕೂಡಿಸು_action("[[");
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

ಪೂರ್ಣಾಂಕ     link_machines (ಪೂರ್ಣಾಂಕ ಮೊದಲ, ಪೂರ್ಣಾಂಕ ಕೊನೆಯ)
{
	ಆದರೆ (ಮೊದಲ == NIL)
		ಹಿಂತಿರುಗಿ ಕೊನೆಯ;

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕೊನೆಯ == NIL)
		ಹಿಂತಿರುಗಿ ಮೊದಲ;

	ಇಲ್ಲದಿದ್ದರೆ {
		mkxtion (finalst[ಮೊದಲ], ಕೊನೆಯ);
		finalst[ಮೊದಲ] = finalst[ಕೊನೆಯ];
		lastst[ಮೊದಲ] = MAX (lastst[ಮೊದಲ], lastst[ಕೊನೆಯ]);
		firstst[ಮೊದಲ] = MIN (firstst[ಮೊದಲ], firstst[ಕೊನೆಯ]);

		ಹಿಂತಿರುಗಿ ಮೊದಲ;
	}
}


/* mark_beginning_as_normal - mark each "beginning" state in a machine
 *                            as being a "normal" (i.e., not trailing context-
 *                            associated) states
 *
 * The "beginning" states are the epsilon closure of the first state
 */

ಶೂನ್ಯ    mark_beginning_as_ಸಾಮಾನ್ಯ (ಪೂರ್ಣಾಂಕ mach)
{
	ಆಯ್ಕೆ (state_type[mach]) {
	ಸ್ಥಿತಿ STATE_ಸಾಮಾನ್ಯ:
		/* Oh, we've already visited here. */
		ಹಿಂತಿರುಗಿ;

	ಸ್ಥಿತಿ STATE_TRAILING_CONTEXT:
		state_type[mach] = STATE_ಸಾಮಾನ್ಯ;

		ಆದರೆ (transchar[mach] == SYM_EPSILON) {
			ಆದರೆ (trans1[mach] != NO_TRANSITION)
				mark_beginning_as_ಸಾಮಾನ್ಯ (trans1[mach]);

			ಆದರೆ (trans2[mach] != NO_TRANSITION)
				mark_beginning_as_ಸಾಮಾನ್ಯ (trans2[mach]);
		}
		ನಿಲ್ಲಿಸು;

	ಪೂರ್ವನಿಯೋಜಿತ:
		flexerror (_
			   ("bad state type in mark_beginning_as_normal()"));
		ನಿಲ್ಲಿಸು;
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

ಪೂರ್ಣಾಂಕ     mkbranch (ಪೂರ್ಣಾಂಕ ಮೊದಲ, ಪೂರ್ಣಾಂಕ ಎರಡನೇ)
{
	ಪೂರ್ಣಾಂಕ     eps;

	ಆದರೆ (ಮೊದಲ == NO_TRANSITION)
		ಹಿಂತಿರುಗಿ ಎರಡನೇ;

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಎರಡನೇ == NO_TRANSITION)
		ಹಿಂತಿರುಗಿ ಮೊದಲ;

	eps = mkstate (SYM_EPSILON);

	mkxtion (eps, ಮೊದಲ);
	mkxtion (eps, ಎರಡನೇ);

	ಹಿಂತಿರುಗಿ eps;
}


/* mkclos - convert a machine into a closure
 *
 * synopsis
 *   new = mkclos( state );
 *
 * new - a new state which matches the closure of "state"
 */

ಪೂರ್ಣಾಂಕ     mkclos (ಪೂರ್ಣಾಂಕ state)
{
	ಹಿಂತಿರುಗಿ mkopt (mkposcl (state));
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

ಪೂರ್ಣಾಂಕ     mkopt (ಪೂರ್ಣಾಂಕ mach)
{
	ಪೂರ್ಣಾಂಕ     eps;

	ಆದರೆ (!SUPER_FREE_EPSILON (finalst[mach])) {
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

	ಹಿಂತಿರುಗಿ mach;
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

ಪೂರ್ಣಾಂಕ     mkor (ಪೂರ್ಣಾಂಕ ಮೊದಲ, ಪೂರ್ಣಾಂಕ ಎರಡನೇ)
{
	ಪೂರ್ಣಾಂಕ     eps, orend;

	ಆದರೆ (ಮೊದಲ == NIL)
		ಹಿಂತಿರುಗಿ ಎರಡನೇ;

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಎರಡನೇ == NIL)
		ಹಿಂತಿರುಗಿ ಮೊದಲ;

	ಇಲ್ಲದಿದ್ದರೆ {
		/* See comment in mkopt() about why we can't use the first
		 * state of "first" or "second" if they satisfy "FREE_EPSILON".
		 */
		eps = mkstate (SYM_EPSILON);

		ಮೊದಲ = link_machines (eps, ಮೊದಲ);

		mkxtion (ಮೊದಲ, ಎರಡನೇ);

		ಆದರೆ (SUPER_FREE_EPSILON (finalst[ಮೊದಲ]) &&
		    accptnum[finalst[ಮೊದಲ]] == NIL) {
			orend = finalst[ಮೊದಲ];
			mkxtion (finalst[ಎರಡನೇ], orend);
		}

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SUPER_FREE_EPSILON (finalst[ಎರಡನೇ]) &&
			 accptnum[finalst[ಎರಡನೇ]] == NIL) {
			orend = finalst[ಎರಡನೇ];
			mkxtion (finalst[ಮೊದಲ], orend);
		}

		ಇಲ್ಲದಿದ್ದರೆ {
			eps = mkstate (SYM_EPSILON);

			ಮೊದಲ = link_machines (ಮೊದಲ, eps);
			orend = finalst[ಮೊದಲ];

			mkxtion (finalst[ಎರಡನೇ], orend);
		}
	}

	firstst[ಮೊದಲ] = MIN(firstst[ಮೊದಲ], firstst[ಎರಡನೇ]);

	finalst[ಮೊದಲ] = orend;
	ಹಿಂತಿರುಗಿ ಮೊದಲ;
}


/* mkposcl - convert a machine into a positive closure
 *
 * synopsis
 *   new = mkposcl( state );
 *
 *    new - a machine matching the positive closure of "state"
 */

ಪೂರ್ಣಾಂಕ     mkposcl (ಪೂರ್ಣಾಂಕ state)
{
	ಪೂರ್ಣಾಂಕ     eps;

	ಆದರೆ (SUPER_FREE_EPSILON (finalst[state])) {
		mkxtion (finalst[state], state);
		ಹಿಂತಿರುಗಿ state;
	}

	ಇಲ್ಲದಿದ್ದರೆ {
		eps = mkstate (SYM_EPSILON);
		mkxtion (eps, state);
		ಹಿಂತಿರುಗಿ link_machines (state, eps);
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

ಪೂರ್ಣಾಂಕ     mkrep (ಪೂರ್ಣಾಂಕ mach, ಪೂರ್ಣಾಂಕ lb, ಪೂರ್ಣಾಂಕ ub)
{
	ಪೂರ್ಣಾಂಕ     ತಳ_mach, ಬಾಲ, copy, i;

	ತಳ_mach = copysingl (mach, lb - 1);

	ಆದರೆ (ub == INFINITE_REPEAT) {
		copy = dupmachine (mach);
		mach = link_machines (mach,
				      link_machines (ತಳ_mach,
						     mkclos (copy)));
	}

	ಇಲ್ಲದಿದ್ದರೆ {
		ಬಾಲ = mkstate (SYM_EPSILON);

		ಗಾಗಿ (i = lb; i < ub; ++i) {
			copy = dupmachine (mach);
			ಬಾಲ = mkopt (link_machines (copy, ಬಾಲ));
		}

		mach =
			link_machines (mach,
				       link_machines (ತಳ_mach, ಬಾಲ));
	}

	ಹಿಂತಿರುಗಿ mach;
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

ಪೂರ್ಣಾಂಕ     mkstate (ಪೂರ್ಣಾಂಕ sym)
{
	ಆದರೆ (++lastnfa >= current_mns) {
		ಆದರೆ ((current_mns += MNS_INCREMENT) >= ಗರಿಷ್ಠ_mns)
			lerr(_
				("input rules are too complicated (>= %d NFA states)"),
current_mns);

		++ಅಂಕೆ_reallocs;

		firstst = reallocate_integer_array (firstst, current_mns);
		lastst = reallocate_integer_array (lastst, current_mns);
		finalst = reallocate_integer_array (finalst, current_mns);
		transchar =
			reallocate_integer_array (transchar, current_mns);
		trans1 = reallocate_integer_array (trans1, current_mns);
		trans2 = reallocate_integer_array (trans2, current_mns);
		accptnum =
			reallocate_integer_array (accptnum, current_mns);
		assoc_ನಿಯಮ =
			reallocate_integer_array (assoc_ನಿಯಮ, current_mns);
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
	assoc_ನಿಯಮ[lastnfa] = ಅಂಕೆ_ನಿಯಮಗಳು;
	state_type[lastnfa] = current_state_type;

	/* Fix up equivalence classes base on this transition.  Note that any
	 * character which has its own transition gets its own equivalence
	 * class.  Thus only characters which are only in character classes
	 * have a chance at being in the same equivalence class.  E.g. "a|b"
	 * puts 'a' and 'b' into two different equivalence classes.  "[ab]"
	 * puts them in the same equivalence class (barring other differences
	 * elsewhere in the input).
	 */

	ಆದರೆ (sym < 0) {
		/* We don't have to update the equivalence classes since
		 * that was already done when the ccl was created for the
		 * first time.
		 */
	}

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (sym == SYM_EPSILON)
		++numeps;

	ಇಲ್ಲದಿದ್ದರೆ {
		check_char (sym);

		ಆದರೆ (ctrl.useecs)
			/* Map NUL's to csize. */
			mkechar (sym ? sym : ctrl.csize, nextecm, ecgroup);
	}

	ಹಿಂತಿರುಗಿ lastnfa;
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

ಶೂನ್ಯ    mkxtion (ಪೂರ್ಣಾಂಕ statefrom, ಪೂರ್ಣಾಂಕ stateto)
{
	ಆದರೆ (trans1[statefrom] == NO_TRANSITION)
		trans1[statefrom] = stateto;

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((transchar[statefrom] != SYM_EPSILON) ||
		 (trans2[statefrom] != NO_TRANSITION))
		flexfatal (_("found too many transitions in mkxtion()"));

	ಇಲ್ಲದಿದ್ದರೆ {			/* second out-transition for an epsilon state */
		++eps2;
		trans2[statefrom] = stateto;
	}
}

/* new_rule - initialize for a new rule */

ಶೂನ್ಯ    new_ನಿಯಮ (ಶೂನ್ಯ)
{
	ಆದರೆ (++ಅಂಕೆ_ನಿಯಮಗಳು >= current_max_ನಿಯಮಗಳು) {
		++ಅಂಕೆ_reallocs;
		current_max_ನಿಯಮಗಳು += MAX_ನಿಯಮಗಳು_INCREMENT;
		ನಿಯಮ_type = reallocate_integer_array (ನಿಯಮ_type,
						      current_max_ನಿಯಮಗಳು);
		ನಿಯಮ_linenum = reallocate_integer_array (ನಿಯಮ_linenum,
							 current_max_ನಿಯಮಗಳು);
		ನಿಯಮ_useful = reallocate_array(ನಿಯಮ_useful,
					current_max_ನಿಯಮಗಳು, ಗಾತ್ರ(ಅಕ್ಷರ));
		ನಿಯಮ_has_nl = reallocate_array(ನಿಯಮ_has_nl,
					current_max_ನಿಯಮಗಳು, ಗಾತ್ರ(ಅಕ್ಷರ));
	}

	ಆದರೆ (ಅಂಕೆ_ನಿಯಮಗಳು > MAX_ನಿಯಮ)
		lerr (_("too many rules (> %d)!"), MAX_ನಿಯಮ);

	ನಿಯಮ_linenum[ಅಂಕೆ_ನಿಯಮಗಳು] = linenum;
	ನಿಯಮ_useful[ಅಂಕೆ_ನಿಯಮಗಳು] = false;
	ನಿಯಮ_has_nl[ಅಂಕೆ_ನಿಯಮಗಳು] = false;
}
