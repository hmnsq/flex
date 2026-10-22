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

#അന്തര്ഭാവ "flexdef.h"


/* declare functions that have forward references */

പൂർണ്ണസംഖ്യ	dupmachine(പൂർണ്ണസംഖ്യ);
ശൂന്യം	mkxtion(പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ);


/* add_accept - add an accepting state to a machine
 *
 * accepting_number becomes mach's accepting number.
 */

ശൂന്യം    add_accept (പൂർണ്ണസംഖ്യ mach, പൂർണ്ണസംഖ്യ accepting_സംഖ്യ)
{
	/* Hang the accepting number off an epsilon state.  if it is associated
	 * with a state that has a non-epsilon out-transition, then the state
	 * will accept BEFORE it makes that transition, i.e., one character
	 * too soon.
	 */

	എങ്കിൽ (transchar[finalst[mach]] == SYM_EPSILON)
		accptnum[finalst[mach]] = accepting_സംഖ്യ;

	അല്ലെങ്കിൽ {
		പൂർണ്ണസംഖ്യ     astate = mkstate (SYM_EPSILON);

		accptnum[astate] = accepting_സംഖ്യ;
		(ശൂന്യം) link_machines (mach, astate);
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

പൂർണ്ണസംഖ്യ     copysingl (പൂർണ്ണസംഖ്യ singl, പൂർണ്ണസംഖ്യ അക്കം)
{
	പൂർണ്ണസംഖ്യ     copy, i;

	copy = mkstate (SYM_EPSILON);

	വേണ്ടി (i = 1; i <= അക്കം; ++i)
		copy = link_machines (copy, dupmachine (singl));

	തിരികെ copy;
}


/* dumpnfa - debugging routine to write out an nfa */

ശൂന്യം    dumpnfa (പൂർണ്ണസംഖ്യ state1)
{
	പൂർണ്ണസംഖ്യ     sym, tsp1, tsp2, anum, ns;

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
	വേണ്ടി (ns = 1; ns <= lastnfa; ++ns) {
		fprintf (stderr, _("state # %4d\t"), ns);

		sym = transchar[ns];
		tsp1 = trans1[ns];
		tsp2 = trans2[ns];
		anum = accptnum[ns];

		fprintf (stderr, "%3d:  %4d, %4d", sym, tsp1, tsp2);

		എങ്കിൽ (anum != NIL)
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

പൂർണ്ണസംഖ്യ     dupmachine (പൂർണ്ണസംഖ്യ mach)
{
	പൂർണ്ണസംഖ്യ     i, init, state_offset;
	പൂർണ്ണസംഖ്യ     state = 0;
	പൂർണ്ണസംഖ്യ     last = lastst[mach];

	വേണ്ടി (i = firstst[mach]; i <= last; ++i) {
		state = mkstate (transchar[i]);

		എങ്കിൽ (trans1[i] != NO_TRANSITION) {
			mkxtion (finalst[state], trans1[i] + state - i);

			എങ്കിൽ (transchar[i] == SYM_EPSILON &&
			    trans2[i] != NO_TRANSITION)
					mkxtion (finalst[state],
						 trans2[i] + state - i);
		}

		accptnum[state] = accptnum[i];
	}

	എങ്കിൽ (state == 0)
		flexfatal (_("empty machine in dupmachine()"));

	state_offset = state - i + 1;

	init = mach + state_offset;
	firstst[init] = firstst[mach] + state_offset;
	finalst[init] = finalst[mach] + state_offset;
	lastst[init] = lastst[mach] + state_offset;

	തിരികെ init;
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

ശൂന്യം    finish_rule (പൂർണ്ണസംഖ്യ mach, bool variable_trail_rule, പൂർണ്ണസംഖ്യ headcnt, പൂർണ്ണസംഖ്യ trailcnt,
		     പൂർണ്ണസംഖ്യ pcont_act)
{
	അക്ഷരം    action_text[MAXLINE];

	add_accept (mach, അക്കം_rules);

	/* We did this in new_rule(), but it often gets the wrong
	 * number because we do it before we start parsing the current rule.
	 */
	rule_linenum[അക്കം_rules] = linenum;

	/* If this is a continued action, then the line-number has already
	 * been updated, giving us the wrong number.
	 */
	എങ്കിൽ (continued_action)
		--rule_linenum[അക്കം_rules];


	/* If the previous rule was continued action, then we inherit the
	 * previous newline flag, possibly overriding the current one.
	 */
	എങ്കിൽ (pcont_act && rule_has_nl[അക്കം_rules - 1])
		rule_has_nl[അക്കം_rules] = true;

	snprintf (action_text, വലുപ്പം(action_text), "M4_HOOK_NORMAL_STATE_CASE_ARM(%d)\n", അക്കം_rules);
	add_action (action_text);
	എങ്കിൽ (rule_has_nl[അക്കം_rules]) {
		snprintf (action_text, വലുപ്പം(action_text), "M4_HOOK_COMMENT_OPEN rule %d can match eol M4_HOOK_COMMENT_CLOSE\n",
			 അക്കം_rules);
		add_action (action_text);
	}


	എങ്കിൽ (variable_trail_rule) {
		rule_type[അക്കം_rules] = RULE_VARIABLE;

		എങ്കിൽ (env.performance_hint > 0)
			fprintf (stderr,
				 _
				 ("Variable trailing context rule at line %d\n"),
				 rule_linenum[അക്കം_rules]);

		variable_trailing_context_rules = true;
	}

	അല്ലെങ്കിൽ {
		rule_type[അക്കം_rules] = RULE_NORMAL;

		എങ്കിൽ (headcnt > 0 || trailcnt > 0) {
			/* Do trailing context magic to not match the trailing
			 * characters.
			 */
			add_action ("M4_HOOK_RELEASE_YYTEXT\n");

			എങ്കിൽ (headcnt > 0) {
				എങ്കിൽ (rule_has_nl[അക്കം_rules]) {
					snprintf (action_text, വലുപ്പം(action_text),
						"M4_HOOK_LINE_FORWARD(%d)\n", headcnt);
					add_action (action_text);
				}
				snprintf (action_text, വലുപ്പം(action_text), "M4_HOOK_CHAR_FORWARD(%d)\n",
					 headcnt);
				add_action (action_text);
			}

			അല്ലെങ്കിൽ {
				എങ്കിൽ (rule_has_nl[അക്കം_rules]) {
					snprintf (action_text, വലുപ്പം(action_text),
						 "M4_HOOK_LINE_REWIND(%d)\n", trailcnt);
					add_action (action_text);
				}

				snprintf (action_text, വലുപ്പം(action_text), "M4_HOOK_CHAR_REWIND(%d)\n",
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
	എങ്കിൽ (!continued_action)
		add_action ("M4_HOOK_SET_RULE_SETUP\n");

	വരി_directive_out(ശൂന്യ, infilename, linenum);
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

പൂർണ്ണസംഖ്യ     link_machines (പൂർണ്ണസംഖ്യ first, പൂർണ്ണസംഖ്യ last)
{
	എങ്കിൽ (first == NIL)
		തിരികെ last;

	അല്ലെങ്കിൽ എങ്കിൽ (last == NIL)
		തിരികെ first;

	അല്ലെങ്കിൽ {
		mkxtion (finalst[first], last);
		finalst[first] = finalst[last];
		lastst[first] = MAX (lastst[first], lastst[last]);
		firstst[first] = MIN (firstst[first], firstst[last]);

		തിരികെ first;
	}
}


/* mark_beginning_as_normal - mark each "beginning" state in a machine
 *                            as being a "normal" (i.e., not trailing context-
 *                            associated) states
 *
 * The "beginning" states are the epsilon closure of the first state
 */

ശൂന്യം    mark_beginning_as_normal (പൂർണ്ണസംഖ്യ mach)
{
	തിരഞ്ഞെടുപ്പ് (state_type[mach]) {
	അവസ്ഥ STATE_NORMAL:
		/* Oh, we've already visited here. */
		തിരികെ;

	അവസ്ഥ STATE_TRAILING_CONTEXT:
		state_type[mach] = STATE_NORMAL;

		എങ്കിൽ (transchar[mach] == SYM_EPSILON) {
			എങ്കിൽ (trans1[mach] != NO_TRANSITION)
				mark_beginning_as_normal (trans1[mach]);

			എങ്കിൽ (trans2[mach] != NO_TRANSITION)
				mark_beginning_as_normal (trans2[mach]);
		}
		നിർത്തുക;

	സ്ഥിരസ്ഥിതി:
		flexerror (_
			   ("bad state type in mark_beginning_as_normal()"));
		നിർത്തുക;
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

പൂർണ്ണസംഖ്യ     mkbranch (പൂർണ്ണസംഖ്യ first, പൂർണ്ണസംഖ്യ second)
{
	പൂർണ്ണസംഖ്യ     eps;

	എങ്കിൽ (first == NO_TRANSITION)
		തിരികെ second;

	അല്ലെങ്കിൽ എങ്കിൽ (second == NO_TRANSITION)
		തിരികെ first;

	eps = mkstate (SYM_EPSILON);

	mkxtion (eps, first);
	mkxtion (eps, second);

	തിരികെ eps;
}


/* mkclos - convert a machine into a closure
 *
 * synopsis
 *   new = mkclos( state );
 *
 * new - a new state which matches the closure of "state"
 */

പൂർണ്ണസംഖ്യ     mkclos (പൂർണ്ണസംഖ്യ state)
{
	തിരികെ mkopt (mkposcl (state));
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

പൂർണ്ണസംഖ്യ     mkopt (പൂർണ്ണസംഖ്യ mach)
{
	പൂർണ്ണസംഖ്യ     eps;

	എങ്കിൽ (!SUPER_FREE_EPSILON (finalst[mach])) {
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

	തിരികെ mach;
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

പൂർണ്ണസംഖ്യ     mkor (പൂർണ്ണസംഖ്യ first, പൂർണ്ണസംഖ്യ second)
{
	പൂർണ്ണസംഖ്യ     eps, orend;

	എങ്കിൽ (first == NIL)
		തിരികെ second;

	അല്ലെങ്കിൽ എങ്കിൽ (second == NIL)
		തിരികെ first;

	അല്ലെങ്കിൽ {
		/* See comment in mkopt() about why we can't use the first
		 * state of "first" or "second" if they satisfy "FREE_EPSILON".
		 */
		eps = mkstate (SYM_EPSILON);

		first = link_machines (eps, first);

		mkxtion (first, second);

		എങ്കിൽ (SUPER_FREE_EPSILON (finalst[first]) &&
		    accptnum[finalst[first]] == NIL) {
			orend = finalst[first];
			mkxtion (finalst[second], orend);
		}

		അല്ലെങ്കിൽ എങ്കിൽ (SUPER_FREE_EPSILON (finalst[second]) &&
			 accptnum[finalst[second]] == NIL) {
			orend = finalst[second];
			mkxtion (finalst[first], orend);
		}

		അല്ലെങ്കിൽ {
			eps = mkstate (SYM_EPSILON);

			first = link_machines (first, eps);
			orend = finalst[first];

			mkxtion (finalst[second], orend);
		}
	}

	firstst[first] = MIN(firstst[first], firstst[second]);

	finalst[first] = orend;
	തിരികെ first;
}


/* mkposcl - convert a machine into a positive closure
 *
 * synopsis
 *   new = mkposcl( state );
 *
 *    new - a machine matching the positive closure of "state"
 */

പൂർണ്ണസംഖ്യ     mkposcl (പൂർണ്ണസംഖ്യ state)
{
	പൂർണ്ണസംഖ്യ     eps;

	എങ്കിൽ (SUPER_FREE_EPSILON (finalst[state])) {
		mkxtion (finalst[state], state);
		തിരികെ state;
	}

	അല്ലെങ്കിൽ {
		eps = mkstate (SYM_EPSILON);
		mkxtion (eps, state);
		തിരികെ link_machines (state, eps);
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

പൂർണ്ണസംഖ്യ     mkrep (പൂർണ്ണസംഖ്യ mach, പൂർണ്ണസംഖ്യ lb, പൂർണ്ണസംഖ്യ ub)
{
	പൂർണ്ണസംഖ്യ     base_mach, tail, copy, i;

	base_mach = copysingl (mach, lb - 1);

	എങ്കിൽ (ub == INFINITE_REPEAT) {
		copy = dupmachine (mach);
		mach = link_machines (mach,
				      link_machines (base_mach,
						     mkclos (copy)));
	}

	അല്ലെങ്കിൽ {
		tail = mkstate (SYM_EPSILON);

		വേണ്ടി (i = lb; i < ub; ++i) {
			copy = dupmachine (mach);
			tail = mkopt (link_machines (copy, tail));
		}

		mach =
			link_machines (mach,
				       link_machines (base_mach, tail));
	}

	തിരികെ mach;
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

പൂർണ്ണസംഖ്യ     mkstate (പൂർണ്ണസംഖ്യ sym)
{
	എങ്കിൽ (++lastnfa >= current_mns) {
		എങ്കിൽ ((current_mns += MNS_INCREMENT) >= maximum_mns)
			lerr(_
				("input rules are too complicated (>= %d NFA states)"),
current_mns);

		++അക്കം_reallocs;

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
	assoc_rule[lastnfa] = അക്കം_rules;
	state_type[lastnfa] = current_state_type;

	/* Fix up equivalence classes base on this transition.  Note that any
	 * character which has its own transition gets its own equivalence
	 * class.  Thus only characters which are only in character classes
	 * have a chance at being in the same equivalence class.  E.g. "a|b"
	 * puts 'a' and 'b' into two different equivalence classes.  "[ab]"
	 * puts them in the same equivalence class (barring other differences
	 * elsewhere in the input).
	 */

	എങ്കിൽ (sym < 0) {
		/* We don't have to update the equivalence classes since
		 * that was already done when the ccl was created for the
		 * first time.
		 */
	}

	അല്ലെങ്കിൽ എങ്കിൽ (sym == SYM_EPSILON)
		++numeps;

	അല്ലെങ്കിൽ {
		check_char (sym);

		എങ്കിൽ (ctrl.useecs)
			/* Map NUL's to csize. */
			mkechar (sym ? sym : ctrl.csize, nextecm, ecgroup);
	}

	തിരികെ lastnfa;
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

ശൂന്യം    mkxtion (പൂർണ്ണസംഖ്യ statefrom, പൂർണ്ണസംഖ്യ stateto)
{
	എങ്കിൽ (trans1[statefrom] == NO_TRANSITION)
		trans1[statefrom] = stateto;

	അല്ലെങ്കിൽ എങ്കിൽ ((transchar[statefrom] != SYM_EPSILON) ||
		 (trans2[statefrom] != NO_TRANSITION))
		flexfatal (_("found too many transitions in mkxtion()"));

	അല്ലെങ്കിൽ {			/* second out-transition for an epsilon state */
		++eps2;
		trans2[statefrom] = stateto;
	}
}

/* new_rule - initialize for a new rule */

ശൂന്യം    new_rule (ശൂന്യം)
{
	എങ്കിൽ (++അക്കം_rules >= current_max_rules) {
		++അക്കം_reallocs;
		current_max_rules += MAX_RULES_INCREMENT;
		rule_type = reallocate_integer_array (rule_type,
						      current_max_rules);
		rule_linenum = reallocate_integer_array (rule_linenum,
							 current_max_rules);
		rule_useful = reallocate_array(rule_useful,
					current_max_rules, വലുപ്പം(അക്ഷരം));
		rule_has_nl = reallocate_array(rule_has_nl,
					current_max_rules, വലുപ്പം(അക്ഷരം));
	}

	എങ്കിൽ (അക്കം_rules > MAX_RULE)
		lerr (_("too many rules (> %d)!"), MAX_RULE);

	rule_linenum[അക്കം_rules] = linenum;
	rule_useful[അക്കം_rules] = false;
	rule_has_nl[അക്കം_rules] = false;
}
