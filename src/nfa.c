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

#अन्तर्भाव "flexdef.h"


/* declare functions that have forward references */

पूर्णाङ्क	dupmachine(पूर्णाङ्क);
शून्य	mkxtion(पूर्णाङ्क, पूर्णाङ्क);


/* add_accept - add an accepting state to a machine
 *
 * accepting_number becomes mach's accepting number.
 */

शून्य    सङ्कलय_accept (पूर्णाङ्क mach, पूर्णाङ्क accepting_सङ्ख्या)
{
	/* Hang the accepting number off an epsilon state.  if it is associated
	 * with a state that has a non-epsilon out-transition, then the state
	 * will accept BEFORE it makes that transition, i.e., one character
	 * too soon.
	 */

	यदि (transchar[finalst[mach]] == SYM_EPSILON)
		accptnum[finalst[mach]] = accepting_सङ्ख्या;

	अन्यथा {
		पूर्णाङ्क     astate = mkstate (SYM_EPSILON);

		accptnum[astate] = accepting_सङ्ख्या;
		(शून्य) link_machines (mach, astate);
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

पूर्णाङ्क     copysingl (पूर्णाङ्क singl, पूर्णाङ्क अङ्कः)
{
	पूर्णाङ्क     copy, i;

	copy = mkstate (SYM_EPSILON);

	प्रति (i = 1; i <= अङ्कः; ++i)
		copy = link_machines (copy, dupmachine (singl));

	प्रत्यागम copy;
}


/* dumpnfa - debugging routine to write out an nfa */

शून्य    dumpnfa (पूर्णाङ्क state1)
{
	पूर्णाङ्क     sym, tsp1, tsp2, anum, ns;

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
	प्रति (ns = 1; ns <= lastnfa; ++ns) {
		fprintf (stderr, _("state # %4d\t"), ns);

		sym = transchar[ns];
		tsp1 = trans1[ns];
		tsp2 = trans2[ns];
		anum = accptnum[ns];

		fprintf (stderr, "%3d:  %4d, %4d", sym, tsp1, tsp2);

		यदि (anum != NIL)
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

पूर्णाङ्क     dupmachine (पूर्णाङ्क mach)
{
	पूर्णाङ्क     i, init, state_विस्थापनम्;
	पूर्णाङ्क     state = 0;
	पूर्णाङ्क     चरमः = lastst[mach];

	प्रति (i = firstst[mach]; i <= चरमः; ++i) {
		state = mkstate (transchar[i]);

		यदि (trans1[i] != NO_TRANSITION) {
			mkxtion (finalst[state], trans1[i] + state - i);

			यदि (transchar[i] == SYM_EPSILON &&
			    trans2[i] != NO_TRANSITION)
					mkxtion (finalst[state],
						 trans2[i] + state - i);
		}

		accptnum[state] = accptnum[i];
	}

	यदि (state == 0)
		flexfatal (_("empty machine in dupmachine()"));

	state_विस्थापनम् = state - i + 1;

	init = mach + state_विस्थापनम्;
	firstst[init] = firstst[mach] + state_विस्थापनम्;
	finalst[init] = finalst[mach] + state_विस्थापनम्;
	lastst[init] = lastst[mach] + state_विस्थापनम्;

	प्रत्यागम init;
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

शून्य    finish_नियमः (पूर्णाङ्क mach, bool variable_trail_नियमः, पूर्णाङ्क headcnt, पूर्णाङ्क trailcnt,
		     पूर्णाङ्क pcont_act)
{
	वर्ण    action_text[MAXLINE];

	सङ्कलय_accept (mach, अङ्कः_नियमाः);

	/* We did this in new_rule(), but it often gets the wrong
	 * number because we do it before we start parsing the current rule.
	 */
	नियमः_linenum[अङ्कः_नियमाः] = linenum;

	/* If this is a continued action, then the line-number has already
	 * been updated, giving us the wrong number.
	 */
	यदि (continued_action)
		--नियमः_linenum[अङ्कः_नियमाः];


	/* If the previous rule was continued action, then we inherit the
	 * previous newline flag, possibly overriding the current one.
	 */
	यदि (pcont_act && नियमः_has_nl[अङ्कः_नियमाः - 1])
		नियमः_has_nl[अङ्कः_नियमाः] = true;

	snprintf (action_text, परिमाण(action_text), "M4_HOOK_NORMAL_STATE_CASE_ARM(%d)\n", अङ्कः_नियमाः);
	सङ्कलय_action (action_text);
	यदि (नियमः_has_nl[अङ्कः_नियमाः]) {
		snprintf (action_text, परिमाण(action_text), "M4_HOOK_COMMENT_OPEN rule %d can match eol M4_HOOK_COMMENT_CLOSE\n",
			 अङ्कः_नियमाः);
		सङ्कलय_action (action_text);
	}


	यदि (variable_trail_नियमः) {
		नियमः_type[अङ्कः_नियमाः] = नियमः_VARIABLE;

		यदि (env.performance_hint > 0)
			fprintf (stderr,
				 _
				 ("Variable trailing context rule at line %d\n"),
				 नियमः_linenum[अङ्कः_नियमाः]);

		variable_trailing_context_नियमाः = true;
	}

	अन्यथा {
		नियमः_type[अङ्कः_नियमाः] = नियमः_प्रसामान्यम्;

		यदि (headcnt > 0 || trailcnt > 0) {
			/* Do trailing context magic to not match the trailing
			 * characters.
			 */
			सङ्कलय_action ("M4_HOOK_RELEASE_YYTEXT\n");

			यदि (headcnt > 0) {
				यदि (नियमः_has_nl[अङ्कः_नियमाः]) {
					snprintf (action_text, परिमाण(action_text),
						"M4_HOOK_LINE_FORWARD(%d)\n", headcnt);
					सङ्कलय_action (action_text);
				}
				snprintf (action_text, परिमाण(action_text), "M4_HOOK_CHAR_FORWARD(%d)\n",
					 headcnt);
				सङ्कलय_action (action_text);
			}

			अन्यथा {
				यदि (नियमः_has_nl[अङ्कः_नियमाः]) {
					snprintf (action_text, परिमाण(action_text),
						 "M4_HOOK_LINE_REWIND(%d)\n", trailcnt);
					सङ्कलय_action (action_text);
				}

				snprintf (action_text, परिमाण(action_text), "M4_HOOK_CHAR_REWIND(%d)\n",
					 trailcnt);
				सङ्कलय_action (action_text);
			}

			सङ्कलय_action
				("M4_HOOK_TAKE_YYTEXT\n");
		}
	}

	/* Okay, in the action code at this point yytext and yyleng have
	 * their proper final values for this rule, so here's the point
	 * to do any user action.  But don't do it for continued actions,
	 * as that'll result in multiple rule-setup calls.
	 */
	यदि (!continued_action)
		सङ्कलय_action ("M4_HOOK_SET_RULE_SETUP\n");

	पङ्क्तिः_directive_बहिर्गमनम्(रिक्त, infilename, linenum);
        सङ्कलय_action("[[");
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

पूर्णाङ्क     link_machines (पूर्णाङ्क first, पूर्णाङ्क चरमः)
{
	यदि (first == NIL)
		प्रत्यागम चरमः;

	अन्यथा यदि (चरमः == NIL)
		प्रत्यागम first;

	अन्यथा {
		mkxtion (finalst[first], चरमः);
		finalst[first] = finalst[चरमः];
		lastst[first] = MAX (lastst[first], lastst[चरमः]);
		firstst[first] = MIN (firstst[first], firstst[चरमः]);

		प्रत्यागम first;
	}
}


/* mark_beginning_as_normal - mark each "beginning" state in a machine
 *                            as being a "normal" (i.e., not trailing context-
 *                            associated) states
 *
 * The "beginning" states are the epsilon closure of the first state
 */

शून्य    mark_beginning_as_प्रसामान्यम् (पूर्णाङ्क mach)
{
	विकल्प (state_type[mach]) {
	पक्ष STATE_प्रसामान्यम्:
		/* Oh, we've already visited here. */
		प्रत्यागम;

	पक्ष STATE_TRAILING_CONTEXT:
		state_type[mach] = STATE_प्रसामान्यम्;

		यदि (transchar[mach] == SYM_EPSILON) {
			यदि (trans1[mach] != NO_TRANSITION)
				mark_beginning_as_प्रसामान्यम् (trans1[mach]);

			यदि (trans2[mach] != NO_TRANSITION)
				mark_beginning_as_प्रसामान्यम् (trans2[mach]);
		}
		भङ्ग;

	स्वभाव:
		flexerror (_
			   ("bad state type in mark_beginning_as_normal()"));
		भङ्ग;
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

पूर्णाङ्क     mkbranch (पूर्णाङ्क first, पूर्णाङ्क second)
{
	पूर्णाङ्क     eps;

	यदि (first == NO_TRANSITION)
		प्रत्यागम second;

	अन्यथा यदि (second == NO_TRANSITION)
		प्रत्यागम first;

	eps = mkstate (SYM_EPSILON);

	mkxtion (eps, first);
	mkxtion (eps, second);

	प्रत्यागम eps;
}


/* mkclos - convert a machine into a closure
 *
 * synopsis
 *   new = mkclos( state );
 *
 * new - a new state which matches the closure of "state"
 */

पूर्णाङ्क     mkclos (पूर्णाङ्क state)
{
	प्रत्यागम mkopt (mkposcl (state));
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

पूर्णाङ्क     mkopt (पूर्णाङ्क mach)
{
	पूर्णाङ्क     eps;

	यदि (!SUPER_FREE_EPSILON (finalst[mach])) {
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

	प्रत्यागम mach;
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

पूर्णाङ्क     mkor (पूर्णाङ्क first, पूर्णाङ्क second)
{
	पूर्णाङ्क     eps, orend;

	यदि (first == NIL)
		प्रत्यागम second;

	अन्यथा यदि (second == NIL)
		प्रत्यागम first;

	अन्यथा {
		/* See comment in mkopt() about why we can't use the first
		 * state of "first" or "second" if they satisfy "FREE_EPSILON".
		 */
		eps = mkstate (SYM_EPSILON);

		first = link_machines (eps, first);

		mkxtion (first, second);

		यदि (SUPER_FREE_EPSILON (finalst[first]) &&
		    accptnum[finalst[first]] == NIL) {
			orend = finalst[first];
			mkxtion (finalst[second], orend);
		}

		अन्यथा यदि (SUPER_FREE_EPSILON (finalst[second]) &&
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
	प्रत्यागम first;
}


/* mkposcl - convert a machine into a positive closure
 *
 * synopsis
 *   new = mkposcl( state );
 *
 *    new - a machine matching the positive closure of "state"
 */

पूर्णाङ्क     mkposcl (पूर्णाङ्क state)
{
	पूर्णाङ्क     eps;

	यदि (SUPER_FREE_EPSILON (finalst[state])) {
		mkxtion (finalst[state], state);
		प्रत्यागम state;
	}

	अन्यथा {
		eps = mkstate (SYM_EPSILON);
		mkxtion (eps, state);
		प्रत्यागम link_machines (state, eps);
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

पूर्णाङ्क     mkrep (पूर्णाङ्क mach, पूर्णाङ्क lb, पूर्णाङ्क ub)
{
	पूर्णाङ्क     आधारः_mach, पुच्छ, copy, i;

	आधारः_mach = copysingl (mach, lb - 1);

	यदि (ub == INFINITE_REPEAT) {
		copy = dupmachine (mach);
		mach = link_machines (mach,
				      link_machines (आधारः_mach,
						     mkclos (copy)));
	}

	अन्यथा {
		पुच्छ = mkstate (SYM_EPSILON);

		प्रति (i = lb; i < ub; ++i) {
			copy = dupmachine (mach);
			पुच्छ = mkopt (link_machines (copy, पुच्छ));
		}

		mach =
			link_machines (mach,
				       link_machines (आधारः_mach, पुच्छ));
	}

	प्रत्यागम mach;
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

पूर्णाङ्क     mkstate (पूर्णाङ्क sym)
{
	यदि (++lastnfa >= current_mns) {
		यदि ((current_mns += MNS_INCREMENT) >= अधिकतमम्_mns)
			lerr(_
				("input rules are too complicated (>= %d NFA states)"),
current_mns);

		++अङ्कः_reallocs;

		firstst = reallocate_integer_array (firstst, current_mns);
		lastst = reallocate_integer_array (lastst, current_mns);
		finalst = reallocate_integer_array (finalst, current_mns);
		transchar =
			reallocate_integer_array (transchar, current_mns);
		trans1 = reallocate_integer_array (trans1, current_mns);
		trans2 = reallocate_integer_array (trans2, current_mns);
		accptnum =
			reallocate_integer_array (accptnum, current_mns);
		assoc_नियमः =
			reallocate_integer_array (assoc_नियमः, current_mns);
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
	assoc_नियमः[lastnfa] = अङ्कः_नियमाः;
	state_type[lastnfa] = current_state_type;

	/* Fix up equivalence classes base on this transition.  Note that any
	 * character which has its own transition gets its own equivalence
	 * class.  Thus only characters which are only in character classes
	 * have a chance at being in the same equivalence class.  E.g. "a|b"
	 * puts 'a' and 'b' into two different equivalence classes.  "[ab]"
	 * puts them in the same equivalence class (barring other differences
	 * elsewhere in the input).
	 */

	यदि (sym < 0) {
		/* We don't have to update the equivalence classes since
		 * that was already done when the ccl was created for the
		 * first time.
		 */
	}

	अन्यथा यदि (sym == SYM_EPSILON)
		++numeps;

	अन्यथा {
		check_char (sym);

		यदि (ctrl.useecs)
			/* Map NUL's to csize. */
			mkechar (sym ? sym : ctrl.csize, nextecm, ecgroup);
	}

	प्रत्यागम lastnfa;
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

शून्य    mkxtion (पूर्णाङ्क statefrom, पूर्णाङ्क stateto)
{
	यदि (trans1[statefrom] == NO_TRANSITION)
		trans1[statefrom] = stateto;

	अन्यथा यदि ((transchar[statefrom] != SYM_EPSILON) ||
		 (trans2[statefrom] != NO_TRANSITION))
		flexfatal (_("found too many transitions in mkxtion()"));

	अन्यथा {			/* second out-transition for an epsilon state */
		++eps2;
		trans2[statefrom] = stateto;
	}
}

/* new_rule - initialize for a new rule */

शून्य    new_नियमः (शून्य)
{
	यदि (++अङ्कः_नियमाः >= current_max_नियमाः) {
		++अङ्कः_reallocs;
		current_max_नियमाः += MAX_नियमाः_INCREMENT;
		नियमः_type = reallocate_integer_array (नियमः_type,
						      current_max_नियमाः);
		नियमः_linenum = reallocate_integer_array (नियमः_linenum,
							 current_max_नियमाः);
		नियमः_useful = reallocate_array(नियमः_useful,
					current_max_नियमाः, परिमाण(वर्ण));
		नियमः_has_nl = reallocate_array(नियमः_has_nl,
					current_max_नियमाः, परिमाण(वर्ण));
	}

	यदि (अङ्कः_नियमाः > MAX_नियमः)
		lerr (_("too many rules (> %d)!"), MAX_नियमः);

	नियमः_linenum[अङ्कः_नियमाः] = linenum;
	नियमः_useful[अङ्कः_नियमाः] = false;
	नियमः_has_nl[अङ्कः_नियमाः] = false;
}
