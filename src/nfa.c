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

#समावेश "flexdef.h"


/* declare functions that have forward references */

पूर्णांक	dupmachine(पूर्णांक);
व्योम	mkxtion(पूर्णांक, पूर्णांक);


/* add_accept - add an accepting state to a machine
 *
 * accepting_number becomes mach's accepting number.
 */

व्योम    add_accept (पूर्णांक mach, पूर्णांक accepting_संख्या)
{
	/* Hang the accepting number off an epsilon state.  if it is associated
	 * with a state that has a non-epsilon out-transition, then the state
	 * will accept BEFORE it makes that transition, i.e., one character
	 * too soon.
	 */

	अगर (transchar[finalst[mach]] == SYM_EPSILON)
		accptnum[finalst[mach]] = accepting_संख्या;

	अन्यथा {
		पूर्णांक     astate = mkstate (SYM_EPSILON);

		accptnum[astate] = accepting_संख्या;
		(व्योम) link_machines (mach, astate);
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

पूर्णांक     copysingl (पूर्णांक singl, पूर्णांक अंक)
{
	पूर्णांक     copy, i;

	copy = mkstate (SYM_EPSILON);

	क्रम (i = 1; i <= अंक; ++i)
		copy = link_machines (copy, dupmachine (singl));

	वापस copy;
}


/* dumpnfa - debugging routine to write out an nfa */

व्योम    dumpnfa (पूर्णांक state1)
{
	पूर्णांक     sym, tsp1, tsp2, anum, ns;

	ख_लिखो (मानक_त्रुटि,
		 _
		 ("\n\n********** beginning dump of nfa with start state %d\n"),
		 state1);

	/* We probably should loop starting at firstst[state1] and going to
	 * lastst[state1], but they're not maintained properly when we "or"
	 * all of the rules together.  So we use our knowledge that the machine
	 * starts at state 1 and ends at lastnfa.
	 */

	/* for ( ns = firstst[state1]; ns <= lastst[state1]; ++ns ) */
	क्रम (ns = 1; ns <= lastnfa; ++ns) {
		ख_लिखो (मानक_त्रुटि, _("state # %4d\t"), ns);

		sym = transchar[ns];
		tsp1 = trans1[ns];
		tsp2 = trans2[ns];
		anum = accptnum[ns];

		ख_लिखो (मानक_त्रुटि, "%3d:  %4d, %4d", sym, tsp1, tsp2);

		अगर (anum != NIL)
			ख_लिखो (मानक_त्रुटि, "  [%d]", anum);

		ख_लिखो (मानक_त्रुटि, "\n");
	}

	ख_लिखो (मानक_त्रुटि, _("********** end of dump\n"));
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

पूर्णांक     dupmachine (पूर्णांक mach)
{
	पूर्णांक     i, init, state_offset;
	पूर्णांक     state = 0;
	पूर्णांक     last = lastst[mach];

	क्रम (i = firstst[mach]; i <= last; ++i) {
		state = mkstate (transchar[i]);

		अगर (trans1[i] != NO_TRANSITION) {
			mkxtion (finalst[state], trans1[i] + state - i);

			अगर (transchar[i] == SYM_EPSILON &&
			    trans2[i] != NO_TRANSITION)
					mkxtion (finalst[state],
						 trans2[i] + state - i);
		}

		accptnum[state] = accptnum[i];
	}

	अगर (state == 0)
		flexfatal (_("empty machine in dupmachine()"));

	state_offset = state - i + 1;

	init = mach + state_offset;
	firstst[init] = firstst[mach] + state_offset;
	finalst[init] = finalst[mach] + state_offset;
	lastst[init] = lastst[mach] + state_offset;

	वापस init;
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

व्योम    finish_rule (पूर्णांक mach, bool variable_trail_rule, पूर्णांक headcnt, पूर्णांक trailcnt,
		     पूर्णांक pcont_act)
{
	अक्षर    action_text[MAXLINE];

	add_accept (mach, अंक_rules);

	/* We did this in new_rule(), but it often gets the wrong
	 * number because we do it before we start parsing the current rule.
	 */
	rule_linenum[अंक_rules] = linenum;

	/* If this is a continued action, then the line-number has already
	 * been updated, giving us the wrong number.
	 */
	अगर (continued_action)
		--rule_linenum[अंक_rules];


	/* If the previous rule was continued action, then we inherit the
	 * previous newline flag, possibly overriding the current one.
	 */
	अगर (pcont_act && rule_has_nl[अंक_rules - 1])
		rule_has_nl[अंक_rules] = true;

	snprintf (action_text, माप(action_text), "M4_HOOK_NORMAL_STATE_CASE_ARM(%d)\n", अंक_rules);
	add_action (action_text);
	अगर (rule_has_nl[अंक_rules]) {
		snprintf (action_text, माप(action_text), "M4_HOOK_COMMENT_OPEN rule %d can match eol M4_HOOK_COMMENT_CLOSE\n",
			 अंक_rules);
		add_action (action_text);
	}


	अगर (variable_trail_rule) {
		rule_type[अंक_rules] = RULE_VARIABLE;

		अगर (env.performance_hint > 0)
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("Variable trailing context rule at line %d\n"),
				 rule_linenum[अंक_rules]);

		variable_trailing_context_rules = true;
	}

	अन्यथा {
		rule_type[अंक_rules] = RULE_NORMAL;

		अगर (headcnt > 0 || trailcnt > 0) {
			/* Do trailing context magic to not match the trailing
			 * characters.
			 */
			add_action ("M4_HOOK_RELEASE_YYTEXT\n");

			अगर (headcnt > 0) {
				अगर (rule_has_nl[अंक_rules]) {
					snprintf (action_text, माप(action_text),
						"M4_HOOK_LINE_FORWARD(%d)\n", headcnt);
					add_action (action_text);
				}
				snprintf (action_text, माप(action_text), "M4_HOOK_CHAR_FORWARD(%d)\n",
					 headcnt);
				add_action (action_text);
			}

			अन्यथा {
				अगर (rule_has_nl[अंक_rules]) {
					snprintf (action_text, माप(action_text),
						 "M4_HOOK_LINE_REWIND(%d)\n", trailcnt);
					add_action (action_text);
				}

				snprintf (action_text, माप(action_text), "M4_HOOK_CHAR_REWIND(%d)\n",
					 trailcnt);
				add_action (action_text);
			}

			add_action
				("M4_HOOK_TAKE_YYTEXT\n");
		}
	}

	/* Okay, in the action code at this point yytext and yyleng have
	 * their proper final values for this rule, so here's the point
	 * to do any user action.  But don't do it for continued actions,
	 * as that'll result in multiple rule-setup calls.
	 */
	अगर (!continued_action)
		add_action ("M4_HOOK_SET_RULE_SETUP\n");

	पंक्ति_directive_out(शून्य, infilename, linenum);
        add_action("[[");
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

पूर्णांक     link_machines (पूर्णांक first, पूर्णांक last)
{
	अगर (first == NIL)
		वापस last;

	अन्यथा अगर (last == NIL)
		वापस first;

	अन्यथा {
		mkxtion (finalst[first], last);
		finalst[first] = finalst[last];
		lastst[first] = MAX (lastst[first], lastst[last]);
		firstst[first] = MIN (firstst[first], firstst[last]);

		वापस first;
	}
}


/* mark_beginning_as_normal - mark each "beginning" state in a machine
 *                            as being a "normal" (i.e., not trailing context-
 *                            associated) states
 *
 * The "beginning" states are the epsilon closure of the first state
 */

व्योम    mark_beginning_as_normal (पूर्णांक mach)
{
	चयन (state_type[mach]) {
	हाल STATE_NORMAL:
		/* Oh, we've already visited here. */
		वापस;

	हाल STATE_TRAILING_CONTEXT:
		state_type[mach] = STATE_NORMAL;

		अगर (transchar[mach] == SYM_EPSILON) {
			अगर (trans1[mach] != NO_TRANSITION)
				mark_beginning_as_normal (trans1[mach]);

			अगर (trans2[mach] != NO_TRANSITION)
				mark_beginning_as_normal (trans2[mach]);
		}
		अवरोध;

	शेष:
		flexerror (_
			   ("bad state type in mark_beginning_as_normal()"));
		अवरोध;
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

पूर्णांक     mkbranch (पूर्णांक first, पूर्णांक second)
{
	पूर्णांक     eps;

	अगर (first == NO_TRANSITION)
		वापस second;

	अन्यथा अगर (second == NO_TRANSITION)
		वापस first;

	eps = mkstate (SYM_EPSILON);

	mkxtion (eps, first);
	mkxtion (eps, second);

	वापस eps;
}


/* mkclos - convert a machine into a closure
 *
 * synopsis
 *   new = mkclos( state );
 *
 * new - a new state which matches the closure of "state"
 */

पूर्णांक     mkclos (पूर्णांक state)
{
	वापस mkopt (mkposcl (state));
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

पूर्णांक     mkopt (पूर्णांक mach)
{
	पूर्णांक     eps;

	अगर (!SUPER_FREE_EPSILON (finalst[mach])) {
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

	वापस mach;
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

पूर्णांक     mkor (पूर्णांक first, पूर्णांक second)
{
	पूर्णांक     eps, orend;

	अगर (first == NIL)
		वापस second;

	अन्यथा अगर (second == NIL)
		वापस first;

	अन्यथा {
		/* See comment in mkopt() about why we can't use the first
		 * state of "first" or "second" if they satisfy "FREE_EPSILON".
		 */
		eps = mkstate (SYM_EPSILON);

		first = link_machines (eps, first);

		mkxtion (first, second);

		अगर (SUPER_FREE_EPSILON (finalst[first]) &&
		    accptnum[finalst[first]] == NIL) {
			orend = finalst[first];
			mkxtion (finalst[second], orend);
		}

		अन्यथा अगर (SUPER_FREE_EPSILON (finalst[second]) &&
			 accptnum[finalst[second]] == NIL) {
			orend = finalst[second];
			mkxtion (finalst[first], orend);
		}

		अन्यथा {
			eps = mkstate (SYM_EPSILON);

			first = link_machines (first, eps);
			orend = finalst[first];

			mkxtion (finalst[second], orend);
		}
	}

	firstst[first] = MIN(firstst[first], firstst[second]);

	finalst[first] = orend;
	वापस first;
}


/* mkposcl - convert a machine into a positive closure
 *
 * synopsis
 *   new = mkposcl( state );
 *
 *    new - a machine matching the positive closure of "state"
 */

पूर्णांक     mkposcl (पूर्णांक state)
{
	पूर्णांक     eps;

	अगर (SUPER_FREE_EPSILON (finalst[state])) {
		mkxtion (finalst[state], state);
		वापस state;
	}

	अन्यथा {
		eps = mkstate (SYM_EPSILON);
		mkxtion (eps, state);
		वापस link_machines (state, eps);
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

पूर्णांक     mkrep (पूर्णांक mach, पूर्णांक lb, पूर्णांक ub)
{
	पूर्णांक     base_mach, पुच्छ, copy, i;

	base_mach = copysingl (mach, lb - 1);

	अगर (ub == INFINITE_REPEAT) {
		copy = dupmachine (mach);
		mach = link_machines (mach,
				      link_machines (base_mach,
						     mkclos (copy)));
	}

	अन्यथा {
		पुच्छ = mkstate (SYM_EPSILON);

		क्रम (i = lb; i < ub; ++i) {
			copy = dupmachine (mach);
			पुच्छ = mkopt (link_machines (copy, पुच्छ));
		}

		mach =
			link_machines (mach,
				       link_machines (base_mach, पुच्छ));
	}

	वापस mach;
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

पूर्णांक     mkstate (पूर्णांक sym)
{
	अगर (++lastnfa >= current_mns) {
		अगर ((current_mns += MNS_INCREMENT) >= maximum_mns)
			lerr(_
				("input rules are too complicated (>= %d NFA states)"),
current_mns);

		++अंक_reallocs;

		firstst = reallocate_integer_array (firstst, current_mns);
		lastst = reallocate_integer_array (lastst, current_mns);
		finalst = reallocate_integer_array (finalst, current_mns);
		transchar =
			reallocate_integer_array (transchar, current_mns);
		trans1 = reallocate_integer_array (trans1, current_mns);
		trans2 = reallocate_integer_array (trans2, current_mns);
		accptnum =
			reallocate_integer_array (accptnum, current_mns);
		assoc_rule =
			reallocate_integer_array (assoc_rule, current_mns);
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
	assoc_rule[lastnfa] = अंक_rules;
	state_type[lastnfa] = current_state_type;

	/* Fix up equivalence classes base on this transition.  Note that any
	 * character which has its own transition gets its own equivalence
	 * class.  Thus only characters which are only in character classes
	 * have a chance at being in the same equivalence class.  E.g. "a|b"
	 * puts 'a' and 'b' into two different equivalence classes.  "[ab]"
	 * puts them in the same equivalence class (barring other differences
	 * elsewhere in the input).
	 */

	अगर (sym < 0) {
		/* We don't have to update the equivalence classes since
		 * that was already done when the ccl was created for the
		 * first time.
		 */
	}

	अन्यथा अगर (sym == SYM_EPSILON)
		++numeps;

	अन्यथा {
		check_char (sym);

		अगर (ctrl.useecs)
			/* Map NUL's to csize. */
			mkechar (sym ? sym : ctrl.csize, nextecm, ecgroup);
	}

	वापस lastnfa;
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

व्योम    mkxtion (पूर्णांक statefrom, पूर्णांक stateto)
{
	अगर (trans1[statefrom] == NO_TRANSITION)
		trans1[statefrom] = stateto;

	अन्यथा अगर ((transchar[statefrom] != SYM_EPSILON) ||
		 (trans2[statefrom] != NO_TRANSITION))
		flexfatal (_("found too many transitions in mkxtion()"));

	अन्यथा {			/* second out-transition for an epsilon state */
		++eps2;
		trans2[statefrom] = stateto;
	}
}

/* new_rule - initialize for a new rule */

व्योम    new_rule (व्योम)
{
	अगर (++अंक_rules >= current_max_rules) {
		++अंक_reallocs;
		current_max_rules += MAX_RULES_INCREMENT;
		rule_type = reallocate_integer_array (rule_type,
						      current_max_rules);
		rule_linenum = reallocate_integer_array (rule_linenum,
							 current_max_rules);
		rule_useful = reallocate_array(rule_useful,
					current_max_rules, माप(अक्षर));
		rule_has_nl = reallocate_array(rule_has_nl,
					current_max_rules, माप(अक्षर));
	}

	अगर (अंक_rules > MAX_RULE)
		lerr (_("too many rules (> %d)!"), MAX_RULE);

	rule_linenum[अंक_rules] = linenum;
	rule_useful[अंक_rules] = false;
	rule_has_nl[अंक_rules] = false;
}
