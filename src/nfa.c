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

#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"


/* declare functions that have forward references */

ਪੂਰਨ	dupmachine(ਪੂਰਨ);
ਖਾਲੀ	mkxtion(ਪੂਰਨ, ਪੂਰਨ);


/* add_accept - add an accepting state to a machine
 *
 * accepting_number becomes mach's accepting number.
 */

ਖਾਲੀ    ਜੋੜੋ_accept (ਪੂਰਨ mach, ਪੂਰਨ accepting_ਸੰਖਿਆ)
{
	/* Hang the accepting number off an epsilon state.  if it is associated
	 * with a state that has a non-epsilon out-transition, then the state
	 * will accept BEFORE it makes that transition, i.e., one character
	 * too soon.
	 */

	ਜੇ (transchar[finalst[mach]] == SYM_EPSILON)
		accptnum[finalst[mach]] = accepting_ਸੰਖਿਆ;

	ਨਹੀਂਤਾਂ {
		ਪੂਰਨ     astate = mkstate (SYM_EPSILON);

		accptnum[astate] = accepting_ਸੰਖਿਆ;
		(ਖਾਲੀ) link_machines (mach, astate);
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

ਪੂਰਨ     copysingl (ਪੂਰਨ singl, ਪੂਰਨ ਅੰਕ)
{
	ਪੂਰਨ     copy, i;

	copy = mkstate (SYM_EPSILON);

	ਲਈ (i = 1; i <= ਅੰਕ; ++i)
		copy = link_machines (copy, dupmachine (singl));

	ਵਾਪਸ copy;
}


/* dumpnfa - debugging routine to write out an nfa */

ਖਾਲੀ    dumpnfa (ਪੂਰਨ state1)
{
	ਪੂਰਨ     sym, tsp1, tsp2, anum, ns;

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
	ਲਈ (ns = 1; ns <= lastnfa; ++ns) {
		fprintf (stderr, _("state # %4d\t"), ns);

		sym = transchar[ns];
		tsp1 = trans1[ns];
		tsp2 = trans2[ns];
		anum = accptnum[ns];

		fprintf (stderr, "%3d:  %4d, %4d", sym, tsp1, tsp2);

		ਜੇ (anum != NIL)
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

ਪੂਰਨ     dupmachine (ਪੂਰਨ mach)
{
	ਪੂਰਨ     i, init, state_ਵਿੱਥ;
	ਪੂਰਨ     state = 0;
	ਪੂਰਨ     ਆਖਰੀ = lastst[mach];

	ਲਈ (i = firstst[mach]; i <= ਆਖਰੀ; ++i) {
		state = mkstate (transchar[i]);

		ਜੇ (trans1[i] != NO_TRANSITION) {
			mkxtion (finalst[state], trans1[i] + state - i);

			ਜੇ (transchar[i] == SYM_EPSILON &&
			    trans2[i] != NO_TRANSITION)
					mkxtion (finalst[state],
						 trans2[i] + state - i);
		}

		accptnum[state] = accptnum[i];
	}

	ਜੇ (state == 0)
		flexfatal (_("empty machine in dupmachine()"));

	state_ਵਿੱਥ = state - i + 1;

	init = mach + state_ਵਿੱਥ;
	firstst[init] = firstst[mach] + state_ਵਿੱਥ;
	finalst[init] = finalst[mach] + state_ਵਿੱਥ;
	lastst[init] = lastst[mach] + state_ਵਿੱਥ;

	ਵਾਪਸ init;
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

ਖਾਲੀ    ਅੰਤ_ਨਿਯਮ (ਪੂਰਨ mach, bool variable_trail_ਨਿਯਮ, ਪੂਰਨ headcnt, ਪੂਰਨ trailcnt,
		     ਪੂਰਨ pcont_act)
{
	ਅੱਖਰ    action_ਪਾਠ[MAXLINE];

	ਜੋੜੋ_accept (mach, ਅੰਕ_ਨਿਯਮਾਂ);

	/* We did this in new_rule(), but it often gets the wrong
	 * number because we do it before we start parsing the current rule.
	 */
	ਨਿਯਮ_linenum[ਅੰਕ_ਨਿਯਮਾਂ] = linenum;

	/* If this is a continued action, then the line-number has already
	 * been updated, giving us the wrong number.
	 */
	ਜੇ (continued_action)
		--ਨਿਯਮ_linenum[ਅੰਕ_ਨਿਯਮਾਂ];


	/* If the previous rule was continued action, then we inherit the
	 * previous newline flag, possibly overriding the current one.
	 */
	ਜੇ (pcont_act && ਨਿਯਮ_has_nl[ਅੰਕ_ਨਿਯਮਾਂ - 1])
		ਨਿਯਮ_has_nl[ਅੰਕ_ਨਿਯਮਾਂ] = true;

	snprintf (action_ਪਾਠ, ਆਕਾਰ(action_ਪਾਠ), "M4_HOOK_NORMAL_STATE_CASE_ARM(%d)\n", ਅੰਕ_ਨਿਯਮਾਂ);
	ਜੋੜੋ_action (action_ਪਾਠ);
	ਜੇ (ਨਿਯਮ_has_nl[ਅੰਕ_ਨਿਯਮਾਂ]) {
		snprintf (action_ਪਾਠ, ਆਕਾਰ(action_ਪਾਠ), "M4_HOOK_COMMENT_OPEN rule %d can match eol M4_HOOK_COMMENT_CLOSE\n",
			 ਅੰਕ_ਨਿਯਮਾਂ);
		ਜੋੜੋ_action (action_ਪਾਠ);
	}


	ਜੇ (variable_trail_ਨਿਯਮ) {
		ਨਿਯਮ_type[ਅੰਕ_ਨਿਯਮਾਂ] = ਨਿਯਮ_VARIABLE;

		ਜੇ (env.performance_hint > 0)
			fprintf (stderr,
				 _
				 ("Variable trailing context rule at line %d\n"),
				 ਨਿਯਮ_linenum[ਅੰਕ_ਨਿਯਮਾਂ]);

		variable_trailing_context_ਨਿਯਮਾਂ = true;
	}

	ਨਹੀਂਤਾਂ {
		ਨਿਯਮ_type[ਅੰਕ_ਨਿਯਮਾਂ] = ਨਿਯਮ_ਸਾਧਾਰਨ;

		ਜੇ (headcnt > 0 || trailcnt > 0) {
			/* Do trailing context magic to not match the trailing
			 * characters.
			 */
			ਜੋੜੋ_action ("M4_HOOK_RELEASE_YYTEXT\n");

			ਜੇ (headcnt > 0) {
				ਜੇ (ਨਿਯਮ_has_nl[ਅੰਕ_ਨਿਯਮਾਂ]) {
					snprintf (action_ਪਾਠ, ਆਕਾਰ(action_ਪਾਠ),
						"M4_HOOK_LINE_FORWARD(%d)\n", headcnt);
					ਜੋੜੋ_action (action_ਪਾਠ);
				}
				snprintf (action_ਪਾਠ, ਆਕਾਰ(action_ਪਾਠ), "M4_HOOK_CHAR_FORWARD(%d)\n",
					 headcnt);
				ਜੋੜੋ_action (action_ਪਾਠ);
			}

			ਨਹੀਂਤਾਂ {
				ਜੇ (ਨਿਯਮ_has_nl[ਅੰਕ_ਨਿਯਮਾਂ]) {
					snprintf (action_ਪਾਠ, ਆਕਾਰ(action_ਪਾਠ),
						 "M4_HOOK_LINE_REWIND(%d)\n", trailcnt);
					ਜੋੜੋ_action (action_ਪਾਠ);
				}

				snprintf (action_ਪਾਠ, ਆਕਾਰ(action_ਪਾਠ), "M4_HOOK_CHAR_REWIND(%d)\n",
					 trailcnt);
				ਜੋੜੋ_action (action_ਪਾਠ);
			}

			ਜੋੜੋ_action
				("M4_HOOK_TAKE_YYTEXT\n");
		}
	}

	/* Okay, in the action code at this point yytext and yyleng have
	 * their proper final values for this rule, so here's the point
	 * to do any user action.  But don't do it for continued actions,
	 * as that'll result in multiple rule-setup calls.
	 */
	ਜੇ (!continued_action)
		ਜੋੜੋ_action ("M4_HOOK_SET_RULE_SETUP\n");

	ਸਤਰ_directive_ਬਾਹਰਲਾ(ਨਿਰਾ, infilename, linenum);
        ਜੋੜੋ_action("[[");
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

ਪੂਰਨ     link_machines (ਪੂਰਨ ਪਹਿਲਾ, ਪੂਰਨ ਆਖਰੀ)
{
	ਜੇ (ਪਹਿਲਾ == NIL)
		ਵਾਪਸ ਆਖਰੀ;

	ਨਹੀਂਤਾਂ ਜੇ (ਆਖਰੀ == NIL)
		ਵਾਪਸ ਪਹਿਲਾ;

	ਨਹੀਂਤਾਂ {
		mkxtion (finalst[ਪਹਿਲਾ], ਆਖਰੀ);
		finalst[ਪਹਿਲਾ] = finalst[ਆਖਰੀ];
		lastst[ਪਹਿਲਾ] = MAX (lastst[ਪਹਿਲਾ], lastst[ਆਖਰੀ]);
		firstst[ਪਹਿਲਾ] = MIN (firstst[ਪਹਿਲਾ], firstst[ਆਖਰੀ]);

		ਵਾਪਸ ਪਹਿਲਾ;
	}
}


/* mark_beginning_as_normal - mark each "beginning" state in a machine
 *                            as being a "normal" (i.e., not trailing context-
 *                            associated) states
 *
 * The "beginning" states are the epsilon closure of the first state
 */

ਖਾਲੀ    mark_beginning_as_ਸਾਧਾਰਨ (ਪੂਰਨ mach)
{
	ਚੋਣ (state_type[mach]) {
	ਹਾਲਤ STATE_ਸਾਧਾਰਨ:
		/* Oh, we've already visited here. */
		ਵਾਪਸ;

	ਹਾਲਤ STATE_TRAILING_CONTEXT:
		state_type[mach] = STATE_ਸਾਧਾਰਨ;

		ਜੇ (transchar[mach] == SYM_EPSILON) {
			ਜੇ (trans1[mach] != NO_TRANSITION)
				mark_beginning_as_ਸਾਧਾਰਨ (trans1[mach]);

			ਜੇ (trans2[mach] != NO_TRANSITION)
				mark_beginning_as_ਸਾਧਾਰਨ (trans2[mach]);
		}
		ਰੋਕੋ;

	ਮੂਲ:
		flexerror (_
			   ("bad state type in mark_beginning_as_normal()"));
		ਰੋਕੋ;
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

ਪੂਰਨ     mkbranch (ਪੂਰਨ ਪਹਿਲਾ, ਪੂਰਨ ਦੂਜਾ)
{
	ਪੂਰਨ     eps;

	ਜੇ (ਪਹਿਲਾ == NO_TRANSITION)
		ਵਾਪਸ ਦੂਜਾ;

	ਨਹੀਂਤਾਂ ਜੇ (ਦੂਜਾ == NO_TRANSITION)
		ਵਾਪਸ ਪਹਿਲਾ;

	eps = mkstate (SYM_EPSILON);

	mkxtion (eps, ਪਹਿਲਾ);
	mkxtion (eps, ਦੂਜਾ);

	ਵਾਪਸ eps;
}


/* mkclos - convert a machine into a closure
 *
 * synopsis
 *   new = mkclos( state );
 *
 * new - a new state which matches the closure of "state"
 */

ਪੂਰਨ     mkclos (ਪੂਰਨ state)
{
	ਵਾਪਸ mkopt (mkposcl (state));
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

ਪੂਰਨ     mkopt (ਪੂਰਨ mach)
{
	ਪੂਰਨ     eps;

	ਜੇ (!SUPER_FREE_EPSILON (finalst[mach])) {
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

	ਵਾਪਸ mach;
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

ਪੂਰਨ     mkor (ਪੂਰਨ ਪਹਿਲਾ, ਪੂਰਨ ਦੂਜਾ)
{
	ਪੂਰਨ     eps, orend;

	ਜੇ (ਪਹਿਲਾ == NIL)
		ਵਾਪਸ ਦੂਜਾ;

	ਨਹੀਂਤਾਂ ਜੇ (ਦੂਜਾ == NIL)
		ਵਾਪਸ ਪਹਿਲਾ;

	ਨਹੀਂਤਾਂ {
		/* See comment in mkopt() about why we can't use the first
		 * state of "first" or "second" if they satisfy "FREE_EPSILON".
		 */
		eps = mkstate (SYM_EPSILON);

		ਪਹਿਲਾ = link_machines (eps, ਪਹਿਲਾ);

		mkxtion (ਪਹਿਲਾ, ਦੂਜਾ);

		ਜੇ (SUPER_FREE_EPSILON (finalst[ਪਹਿਲਾ]) &&
		    accptnum[finalst[ਪਹਿਲਾ]] == NIL) {
			orend = finalst[ਪਹਿਲਾ];
			mkxtion (finalst[ਦੂਜਾ], orend);
		}

		ਨਹੀਂਤਾਂ ਜੇ (SUPER_FREE_EPSILON (finalst[ਦੂਜਾ]) &&
			 accptnum[finalst[ਦੂਜਾ]] == NIL) {
			orend = finalst[ਦੂਜਾ];
			mkxtion (finalst[ਪਹਿਲਾ], orend);
		}

		ਨਹੀਂਤਾਂ {
			eps = mkstate (SYM_EPSILON);

			ਪਹਿਲਾ = link_machines (ਪਹਿਲਾ, eps);
			orend = finalst[ਪਹਿਲਾ];

			mkxtion (finalst[ਦੂਜਾ], orend);
		}
	}

	firstst[ਪਹਿਲਾ] = MIN(firstst[ਪਹਿਲਾ], firstst[ਦੂਜਾ]);

	finalst[ਪਹਿਲਾ] = orend;
	ਵਾਪਸ ਪਹਿਲਾ;
}


/* mkposcl - convert a machine into a positive closure
 *
 * synopsis
 *   new = mkposcl( state );
 *
 *    new - a machine matching the positive closure of "state"
 */

ਪੂਰਨ     mkposcl (ਪੂਰਨ state)
{
	ਪੂਰਨ     eps;

	ਜੇ (SUPER_FREE_EPSILON (finalst[state])) {
		mkxtion (finalst[state], state);
		ਵਾਪਸ state;
	}

	ਨਹੀਂਤਾਂ {
		eps = mkstate (SYM_EPSILON);
		mkxtion (eps, state);
		ਵਾਪਸ link_machines (state, eps);
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

ਪੂਰਨ     mkrep (ਪੂਰਨ mach, ਪੂਰਨ lb, ਪੂਰਨ ub)
{
	ਪੂਰਨ     ਅਧਾਰ_mach, ਪੂਛ, copy, i;

	ਅਧਾਰ_mach = copysingl (mach, lb - 1);

	ਜੇ (ub == INFINITE_REPEAT) {
		copy = dupmachine (mach);
		mach = link_machines (mach,
				      link_machines (ਅਧਾਰ_mach,
						     mkclos (copy)));
	}

	ਨਹੀਂਤਾਂ {
		ਪੂਛ = mkstate (SYM_EPSILON);

		ਲਈ (i = lb; i < ub; ++i) {
			copy = dupmachine (mach);
			ਪੂਛ = mkopt (link_machines (copy, ਪੂਛ));
		}

		mach =
			link_machines (mach,
				       link_machines (ਅਧਾਰ_mach, ਪੂਛ));
	}

	ਵਾਪਸ mach;
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

ਪੂਰਨ     mkstate (ਪੂਰਨ sym)
{
	ਜੇ (++lastnfa >= current_mns) {
		ਜੇ ((current_mns += MNS_INCREMENT) >= ਵੱਧ_ਤੋਂ_ਵੱਧ_mns)
			lerr(_
				("input rules are too complicated (>= %d NFA states)"),
current_mns);

		++ਅੰਕ_reallocs;

		firstst = reallocate_integer_array (firstst, current_mns);
		lastst = reallocate_integer_array (lastst, current_mns);
		finalst = reallocate_integer_array (finalst, current_mns);
		transchar =
			reallocate_integer_array (transchar, current_mns);
		trans1 = reallocate_integer_array (trans1, current_mns);
		trans2 = reallocate_integer_array (trans2, current_mns);
		accptnum =
			reallocate_integer_array (accptnum, current_mns);
		assoc_ਨਿਯਮ =
			reallocate_integer_array (assoc_ਨਿਯਮ, current_mns);
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
	assoc_ਨਿਯਮ[lastnfa] = ਅੰਕ_ਨਿਯਮਾਂ;
	state_type[lastnfa] = current_state_type;

	/* Fix up equivalence classes base on this transition.  Note that any
	 * character which has its own transition gets its own equivalence
	 * class.  Thus only characters which are only in character classes
	 * have a chance at being in the same equivalence class.  E.g. "a|b"
	 * puts 'a' and 'b' into two different equivalence classes.  "[ab]"
	 * puts them in the same equivalence class (barring other differences
	 * elsewhere in the input).
	 */

	ਜੇ (sym < 0) {
		/* We don't have to update the equivalence classes since
		 * that was already done when the ccl was created for the
		 * first time.
		 */
	}

	ਨਹੀਂਤਾਂ ਜੇ (sym == SYM_EPSILON)
		++numeps;

	ਨਹੀਂਤਾਂ {
		check_char (sym);

		ਜੇ (ctrl.useecs)
			/* Map NUL's to csize. */
			mkechar (sym ? sym : ctrl.csize, nextecm, ecgroup);
	}

	ਵਾਪਸ lastnfa;
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

ਖਾਲੀ    mkxtion (ਪੂਰਨ statefrom, ਪੂਰਨ stateto)
{
	ਜੇ (trans1[statefrom] == NO_TRANSITION)
		trans1[statefrom] = stateto;

	ਨਹੀਂਤਾਂ ਜੇ ((transchar[statefrom] != SYM_EPSILON) ||
		 (trans2[statefrom] != NO_TRANSITION))
		flexfatal (_("found too many transitions in mkxtion()"));

	ਨਹੀਂਤਾਂ {			/* second out-transition for an epsilon state */
		++eps2;
		trans2[statefrom] = stateto;
	}
}

/* new_rule - initialize for a new rule */

ਖਾਲੀ    new_ਨਿਯਮ (ਖਾਲੀ)
{
	ਜੇ (++ਅੰਕ_ਨਿਯਮਾਂ >= current_max_ਨਿਯਮਾਂ) {
		++ਅੰਕ_reallocs;
		current_max_ਨਿਯਮਾਂ += MAX_ਨਿਯਮਾਂ_INCREMENT;
		ਨਿਯਮ_type = reallocate_integer_array (ਨਿਯਮ_type,
						      current_max_ਨਿਯਮਾਂ);
		ਨਿਯਮ_linenum = reallocate_integer_array (ਨਿਯਮ_linenum,
							 current_max_ਨਿਯਮਾਂ);
		ਨਿਯਮ_useful = reallocate_array(ਨਿਯਮ_useful,
					current_max_ਨਿਯਮਾਂ, ਆਕਾਰ(ਅੱਖਰ));
		ਨਿਯਮ_has_nl = reallocate_array(ਨਿਯਮ_has_nl,
					current_max_ਨਿਯਮਾਂ, ਆਕਾਰ(ਅੱਖਰ));
	}

	ਜੇ (ਅੰਕ_ਨਿਯਮਾਂ > MAX_ਨਿਯਮ)
		lerr (_("too many rules (> %d)!"), MAX_ਨਿਯਮ);

	ਨਿਯਮ_linenum[ਅੰਕ_ਨਿਯਮਾਂ] = linenum;
	ਨਿਯਮ_useful[ਅੰਕ_ਨਿਯਮਾਂ] = false;
	ਨਿਯਮ_has_nl[ਅੰਕ_ਨਿਯਮਾਂ] = false;
}
