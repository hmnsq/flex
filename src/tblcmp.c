/* tblcmp - table compression routines */

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


/* declarations for functions that have forward references */

ਖਾਲੀ mkentry(ਪੂਰਨ *, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ);
ਖਾਲੀ mkprot(ਪੂਰਨ[], ਪੂਰਨ, ਪੂਰਨ);
ਖਾਲੀ mktemplate(ਪੂਰਨ[], ਪੂਰਨ, ਪੂਰਨ);
ਖਾਲੀ mv2front(ਪੂਰਨ);
ਪੂਰਨ tbldiff(ਪੂਰਨ[], ਪੂਰਨ, ਪੂਰਨ[]);


/* bldtbl - build table entries for dfa state
 *
 * synopsis
 *   int state[numecs], statenum, totaltrans, comstate, comfreq;
 *   bldtbl( state, statenum, totaltrans, comstate, comfreq );
 *
 * State is the statenum'th dfa state.  It is indexed by equivalence class and
 * gives the number of the state to enter for a given equivalence class.
 * totaltrans is the total number of transitions out of the state.  Comstate
 * is that state which is the destination of the most transitions out of State.
 * Comfreq is how many transitions there are out of State to Comstate.
 *
 * A note on terminology:
 *    "protos" are transition tables which have a high probability of
 * either being redundant (a state processed later will have an identical
 * transition table) or nearly redundant (a state processed later will have
 * many of the same out-transitions).  A "most recently used" queue of
 * protos is kept around with the hope that most states will find a proto
 * which is similar enough to be usable, and therefore compacting the
 * output tables.
 *    "templates" are a special type of proto.  If a transition table is
 * homogeneous or nearly homogeneous (all transitions go to the same
 * destination) then the odds are good that future states will also go
 * to the same destination state on basically the same character set.
 * These homogeneous states are so common when dealing with large rule
 * sets that they merit special attention.  If the transition table were
 * simply made into a proto, then (typically) each subsequent, similar
 * state will differ from the proto for two out-transitions.  One of these
 * out-transitions will be that character on which the proto does not go
 * to the common destination, and one will be that character on which the
 * state does not go to the common destination.  Templates, on the other
 * hand, go to the common state on EVERY transition character, and therefore
 * cost only one difference.
 */

ਖਾਲੀ    bldtbl (ਪੂਰਨ state[], ਪੂਰਨ statenum, ਪੂਰਨ totaltrans, ਪੂਰਨ comstate, ਪੂਰਨ comfreq)
{
	ਪੂਰਨ     extptr, extrct[2][CSIZE + 1];
	ਪੂਰਨ     mindiff, minprot, i, d;

	/* If extptr is 0 then the first array of extrct holds the result
	 * of the "best difference" to date, which is those transitions
	 * which occur in "state" but not in the proto which, to date,
	 * has the fewest differences between itself and "state".  If
	 * extptr is 1 then the second array of extrct hold the best
	 * difference.  The two arrays are toggled between so that the
	 * best difference to date can be kept around and also a difference
	 * just created by checking against a candidate "best" proto.
	 */

	extptr = 0;

	/* If the state has too few out-transitions, don't bother trying to
	 * compact its tables.
	 */

	ਜੇ ((totaltrans * 100) < (numecs * PROTO_ਮਾਪ_PERCENTAGE))
		mkentry (state, numecs, statenum, JAMSTATE, totaltrans);

	ਨਹੀਂਤਾਂ {
		/* "checkcom" is true if we should only check "state" against
		 * protos which have the same "comstate" value.
		 */
		ਪੂਰਨ     checkcom =

			comfreq * 100 > totaltrans * CHECK_COM_PERCENTAGE;

		minprot = firstprot;
		mindiff = totaltrans;

		ਜੇ (checkcom) {
			/* Find first proto which has the same "comstate". */
			ਲਈ (i = firstprot; i != NIL; i = protnext[i])
				ਜੇ (protcomst[i] == comstate) {
					minprot = i;
					mindiff = tbldiff (state, minprot,
							   extrct[extptr]);
					ਰੋਕੋ;
				}
		}

		ਨਹੀਂਤਾਂ {
			/* Since we've decided that the most common destination
			 * out of "state" does not occur with a high enough
			 * frequency, we set the "comstate" to zero, assuring
			 * that if this state is entered into the proto list,
			 * it will not be considered a template.
			 */
			comstate = 0;

			ਜੇ (firstprot != NIL) {
				minprot = firstprot;
				mindiff = tbldiff (state, minprot,
						   extrct[extptr]);
			}
		}

		/* We now have the first interesting proto in "minprot".  If
		 * it matches within the tolerances set for the first proto,
		 * we don't want to bother scanning the rest of the proto list
		 * to see if we have any other reasonable matches.
		 */

		ਜੇ (mindiff * 100 >
		    totaltrans * ਪਹਿਲਾ_ਮੇਲ_DIFF_PERCENTAGE) {
			/* Not a good enough match.  Scan the rest of the
			 * protos.
			 */
			ਲਈ (i = minprot; i != NIL; i = protnext[i]) {
				d = tbldiff (state, i, extrct[1 - extptr]);
				ਜੇ (d < mindiff) {
					extptr = 1 - extptr;
					mindiff = d;
					minprot = i;
				}
			}
		}

		/* Check if the proto we've decided on as our best bet is close
		 * enough to the state we want to match to be usable.
		 */

		ਜੇ (mindiff * 100 >
		    totaltrans * ACCEPTABLE_DIFF_PERCENTAGE) {
			/* No good.  If the state is homogeneous enough,
			 * we make a template out of it.  Otherwise, we
			 * make a proto.
			 */

			ਜੇ (comfreq * 100 >=
			    totaltrans * TEMPLATE_SAME_PERCENTAGE)
					mktemplate (state, statenum,
						    comstate);

			ਨਹੀਂਤਾਂ {
				mkprot (state, statenum, comstate);
				mkentry (state, numecs, statenum,
					 JAMSTATE, totaltrans);
			}
		}

		ਨਹੀਂਤਾਂ {		/* use the proto */
			mkentry (extrct[extptr], numecs, statenum,
				 prottbl[minprot], mindiff);

			/* If this state was sufficiently different from the
			 * proto we built it from, make it, too, a proto.
			 */

			ਜੇ (mindiff * 100 >=
			    totaltrans * NEW_PROTO_DIFF_PERCENTAGE)
					mkprot (state, statenum, comstate);

			/* Since mkprot added a new proto to the proto queue,
			 * it's possible that "minprot" is no longer on the
			 * proto queue (if it happened to have been the last
			 * entry, it would have been bumped off).  If it's
			 * not there, then the new proto took its physical
			 * place (though logically the new proto is at the
			 * beginning of the queue), so in that case the
			 * following call will do nothing.
			 */

			mv2front (minprot);
		}
	}
}


/* cmptmps - compress template table entries
 *
 * Template tables are compressed by using the 'template equivalence
 * classes', which are collections of transition character equivalence
 * classes which always appear together in templates - really meta-equivalence
 * classes.
 */

ਖਾਲੀ    cmptmps (ਖਾਲੀ)
{
	ਪੂਰਨ tmpstorage[CSIZE + 1];
	ਪੂਰਨ *tmp = tmpstorage, i, j;
	ਪੂਰਨ totaltrans, trans;

	peakpairs = numtemps * numecs + tblend;

	ਜੇ (ctrl.usemecs) {
		/* Create equivalence classes based on data gathered on
		 * template transitions.
		 */
		nummecs = cre8ecs (tecfwd, tecbck, numecs);
	}

	ਨਹੀਂਤਾਂ
		nummecs = numecs;

	ਜਦੋਂ (lastdfa + numtemps + 1 >= current_max_dfas)
		increase_max_dfas ();

	/* Loop through each template. */

	ਲਈ (i = 1; i <= numtemps; ++i) {
		/* Number of non-jam transitions out of this template. */
		totaltrans = 0;

		ਲਈ (j = 1; j <= numecs; ++j) {
			trans = tnxt[numecs * i + j];

			ਜੇ (ctrl.usemecs) {
				/* The absolute value of tecbck is the
				 * meta-equivalence class of a given
				 * equivalence class, as set up by cre8ecs().
				 */
				ਜੇ (tecbck[j] > 0) {
					tmp[tecbck[j]] = trans;

					ਜੇ (trans > 0)
						++totaltrans;
				}
			}

			ਨਹੀਂਤਾਂ {
				tmp[j] = trans;

				ਜੇ (trans > 0)
					++totaltrans;
			}
		}

		/* It is assumed (in a rather subtle way) in the skeleton
		 * that if we're using meta-equivalence classes, the def[]
		 * entry for all templates is the jam template, i.e.,
		 * templates never default to other non-jam table entries
		 * (e.g., another template)
		 */

		/* Leave room for the jam-state after the last real state. */
		mkentry (tmp, nummecs, lastdfa + i + 1, JAMSTATE,
			 totaltrans);
	}
}



/* expand_nxt_chk - expand the next check arrays */

ਖਾਲੀ    expand_nxt_chk (ਖਾਲੀ)
{
	ਪੂਰਨ old_max = current_max_xpairs;

	current_max_xpairs += MAX_XPAIRS_INCREMENT;

	++ਅੰਕ_reallocs;

	nxt = reallocate_integer_array (nxt, current_max_xpairs);
	chk = reallocate_integer_array (chk, current_max_xpairs);

	memset(chk + old_max, 0, MAX_XPAIRS_INCREMENT * ਆਕਾਰ(ਪੂਰਨ));
}


/* find_table_space - finds a space in the table for a state to be placed
 *
 * synopsis
 *     int *state, numtrans, block_start;
 *     int find_table_space();
 *
 *     block_start = find_table_space( state, numtrans );
 *
 * State is the state to be added to the full speed transition table.
 * Numtrans is the number of out-transitions for the state.
 *
 * find_table_space() returns the position of the start of the first block (in
 * chk) able to accommodate the state
 *
 * In determining if a state will or will not fit, find_table_space() must take
 * into account the fact that an end-of-buffer state will be added at [0],
 * and an action number will be added in [-1].
 */

ਪੂਰਨ     ਲੱਭੋ_ਸਾਰਣੀ_space (ਪੂਰਨ *state, ਪੂਰਨ numtrans)
{
	/* Firstfree is the position of the first possible occurrence of two
	 * consecutive unused records in the chk and nxt arrays.
	 */
	ਪੂਰਨ i;
	ਪੂਰਨ *state_ptr, *chk_ptr;
	ਪੂਰਨ *ptr_ਮੰਜ਼ਿਲ_ਆਖਰੀ_ਇੰਦਰਾਜ_ਵਿੱਚ_state;

	/* If there are too many out-transitions, put the state at the end of
	 * nxt and chk.
	 */
	ਜੇ (numtrans > MAX_XTIONS_ਭਰਿਆ_INTERIOR_FIT) {
		/* If table is empty, return the first available spot in
		 * chk/nxt, which should be 1.
		 */
		ਜੇ (tblend < 2)
			ਵਾਪਸ 1;

		/* Start searching for table space near the end of
		 * chk/nxt arrays.
		 */
		i = tblend - numecs;
	}

	ਨਹੀਂਤਾਂ
		/* Start searching for table space from the beginning
		 * (skipping only the elements which will definitely not
		 * hold the new state).
		 */
		i = firstfree;

	ਜਦੋਂ (1) {		/* loops until a space is found */
		ਜਦੋਂ (i + numecs >= current_max_xpairs)
			expand_nxt_chk ();

		/* Loops until space for end-of-buffer and action number
		 * are found.
		 */
		ਜਦੋਂ (1) {
			/* Check for action number space. */
			ਜੇ (chk[i - 1] == 0) {
				/* Check for end-of-buffer space. */
				ਜੇ (chk[i] == 0)
					ਰੋਕੋ;

				ਨਹੀਂਤਾਂ
					/* Since i != 0, there is no use
					 * checking to see if (++i) - 1 == 0,
					 * because that's the same as i == 0,
					 * so we skip a space.
					 */
					i += 2;
			}

			ਨਹੀਂਤਾਂ
				++i;

			ਜਦੋਂ (i + numecs >= current_max_xpairs)
				expand_nxt_chk ();
		}

		/* If we started search from the beginning, store the new
		 * firstfree for the next call of find_table_space().
		 */
		ਜੇ (numtrans <= MAX_XTIONS_ਭਰਿਆ_INTERIOR_FIT)
			firstfree = i + 1;

		/* Check to see if all elements in chk (and therefore nxt)
		 * that are needed for the new state have not yet been taken.
		 */

		state_ptr = &state[1];
		ptr_ਮੰਜ਼ਿਲ_ਆਖਰੀ_ਇੰਦਰਾਜ_ਵਿੱਚ_state = &chk[i + numecs + 1];

		ਲਈ (chk_ptr = &chk[i + 1];
		     chk_ptr != ptr_ਮੰਜ਼ਿਲ_ਆਖਰੀ_ਇੰਦਰਾਜ_ਵਿੱਚ_state; ++chk_ptr)
			ਜੇ (*(state_ptr++) != 0 && *chk_ptr != 0)
				ਰੋਕੋ;

		ਜੇ (chk_ptr == ptr_ਮੰਜ਼ਿਲ_ਆਖਰੀ_ਇੰਦਰਾਜ_ਵਿੱਚ_state)
			ਵਾਪਸ i;

		ਨਹੀਂਤਾਂ
			++i;
	}
}


/* inittbl - initialize transition tables
 *
 * Initializes "firstfree" to be one beyond the end of the table.  Initializes
 * all "chk" entries to be zero.
 */
ਖਾਲੀ    inittbl (ਖਾਲੀ)
{
	ਪੂਰਨ i;

	memset(chk, 0, (size_t) current_max_xpairs * ਆਕਾਰ(ਪੂਰਨ));

	tblend = 0;
	firstfree = tblend + 1;
	numtemps = 0;

	ਜੇ (ctrl.usemecs) {
		/* Set up doubly-linked meta-equivalence classes; these
		 * are sets of equivalence classes which all have identical
		 * transitions out of TEMPLATES.
		 */

		tecbck[1] = NIL;

		ਲਈ (i = 2; i <= numecs; ++i) {
			tecbck[i] = i - 1;
			tecfwd[i - 1] = i;
		}

		tecfwd[numecs] = NIL;
	}
}


/* mkdeftbl - make the default, "jam" table entries */

ਖਾਲੀ    mkdeftbl (ਖਾਲੀ)
{
	ਪੂਰਨ     i;

	jamstate = lastdfa + 1;

	++tblend;		/* room for transition on end-of-buffer character */

	ਜਦੋਂ (tblend + numecs >= current_max_xpairs)
		expand_nxt_chk ();

	/* Add in default end-of-buffer transition. */
	nxt[tblend] = ਸਿਰਾ_ਦਾ_ਬਫਰ_state;
	chk[tblend] = jamstate;

	ਲਈ (i = 1; i <= numecs; ++i) {
		nxt[tblend + i] = 0;
		chk[tblend + i] = jamstate;
	}

	jambase = tblend;

	ਅਧਾਰ[jamstate] = jambase;
	def[jamstate] = 0;

	tblend += numecs;
	++numtemps;
}


/* mkentry - create base/def and nxt/chk entries for transition array
 *
 * synopsis
 *   int state[numchars + 1], numchars, statenum, deflink, totaltrans;
 *   mkentry( state, numchars, statenum, deflink, totaltrans );
 *
 * "state" is a transition array "numchars" characters in size, "statenum"
 * is the offset to be used into the base/def tables, and "deflink" is the
 * entry to put in the "def" table entry.  If "deflink" is equal to
 * "JAMSTATE", then no attempt will be made to fit zero entries of "state"
 * (i.e., jam entries) into the table.  It is assumed that by linking to
 * "JAMSTATE" they will be taken care of.  In any case, entries in "state"
 * marking transitions to "SAME_TRANS" are treated as though they will be
 * taken care of by wherever "deflink" points.  "totaltrans" is the total
 * number of transitions out of the state.  If it is below a certain threshold,
 * the tables are searched for an interior spot that will accommodate the
 * state array.
 */

ਖਾਲੀ    mkentry (ਪੂਰਨ *state, ਪੂਰਨ numchars, ਪੂਰਨ statenum, ਪੂਰਨ deflink,
		 ਪੂਰਨ totaltrans)
{
	ਪੂਰਨ minec, maxec, i, baseaddr;
	ਪੂਰਨ tblbase, tbllast;

	ਜੇ (totaltrans == 0) {	/* there are no out-transitions */
		ਜੇ (deflink == JAMSTATE)
			ਅਧਾਰ[statenum] = JAMSTATE;
		ਨਹੀਂਤਾਂ
			ਅਧਾਰ[statenum] = 0;

		def[statenum] = deflink;
		ਵਾਪਸ;
	}

	ਲਈ (minec = 1; minec <= numchars; ++minec) {
		ਜੇ (state[minec] != SAME_TRANS)
			ਜੇ (state[minec] != 0 || deflink != JAMSTATE)
				ਰੋਕੋ;
	}

	ਜੇ (totaltrans == 1) {
		/* There's only one out-transition.  Save it for later to fill
		 * in holes in the tables.
		 */
		stack1 (statenum, minec, state[minec], deflink);
		ਵਾਪਸ;
	}

	ਲਈ (maxec = numchars; maxec > 0; --maxec) {
		ਜੇ (state[maxec] != SAME_TRANS)
			ਜੇ (state[maxec] != 0 || deflink != JAMSTATE)
				ਰੋਕੋ;
	}

	/* Whether we try to fit the state table in the middle of the table
	 * entries we have already generated, or if we just take the state
	 * table at the end of the nxt/chk tables, we must make sure that we
	 * have a valid base address (i.e., non-negative).  Note that
	 * negative base addresses dangerous at run-time (because indexing
	 * the nxt array with one and a low-valued character will access
	 * memory before the start of the array.
	 */

	/* Find the first transition of state that we need to worry about. */
	ਜੇ (totaltrans * 100 <= numchars * INTERIOR_FIT_PERCENTAGE) {
		/* Attempt to squeeze it into the middle of the tables. */
		baseaddr = firstfree;

		ਜਦੋਂ (baseaddr < minec) {
			/* Using baseaddr would result in a negative base
			 * address below; find the next free slot.
			 */
			ਲਈ (++baseaddr; chk[baseaddr] != 0; ++baseaddr) ;
		}

		ਜਦੋਂ (baseaddr + maxec - minec + 1 >= current_max_xpairs)
			expand_nxt_chk ();

		ਲਈ (i = minec; i <= maxec; ++i)
			ਜੇ (state[i] != SAME_TRANS &&
			    (state[i] != 0 || deflink != JAMSTATE) &&
			    chk[baseaddr + i - minec] != 0) {	/* baseaddr unsuitable - find another */
				ਲਈ (++baseaddr;
				     baseaddr < current_max_xpairs &&
				     chk[baseaddr] != 0; ++baseaddr) ;

				ਜਦੋਂ (baseaddr + maxec - minec + 1 >=
				       current_max_xpairs)
						expand_nxt_chk ();

				/* Reset the loop counter so we'll start all
				 * over again next time it's incremented.
				 */

				i = minec - 1;
			}
	}

	ਨਹੀਂਤਾਂ {
		/* Ensure that the base address we eventually generate is
		 * non-negative.
		 */
		baseaddr = MAX (tblend + 1, minec);
	}

	tblbase = baseaddr - minec;
	tbllast = tblbase + maxec;

	ਜਦੋਂ (tbllast + 1 >= current_max_xpairs)
		expand_nxt_chk ();

	ਅਧਾਰ[statenum] = tblbase;
	def[statenum] = deflink;

	ਲਈ (i = minec; i <= maxec; ++i)
		ਜੇ (state[i] != SAME_TRANS)
			ਜੇ (state[i] != 0 || deflink != JAMSTATE) {
				nxt[tblbase + i] = state[i];
				chk[tblbase + i] = statenum;
			}

	ਜੇ (baseaddr == firstfree)
		/* Find next free slot in tables. */
		ਲਈ (++firstfree; chk[firstfree] != 0; ++firstfree) ;

	tblend = MAX (tblend, tbllast);
}


/* mk1tbl - create table entries for a state (or state fragment) which
 *            has only one out-transition
 */

ਖਾਲੀ    mk1tbl (ਪੂਰਨ state, ਪੂਰਨ sym, ਪੂਰਨ onenxt, ਪੂਰਨ onedef)
{
	ਜੇ (firstfree < sym)
		firstfree = sym;

	ਜਦੋਂ (chk[firstfree] != 0)
		ਜੇ (++firstfree >= current_max_xpairs)
			expand_nxt_chk ();

	ਅਧਾਰ[state] = firstfree - sym;
	def[state] = onedef;
	chk[firstfree] = state;
	nxt[firstfree] = onenxt;

	ਜੇ (firstfree > tblend) {
		tblend = firstfree++;

		ਜੇ (firstfree >= current_max_xpairs)
			expand_nxt_chk ();
	}
}


/* mkprot - create new proto entry */

ਖਾਲੀ    mkprot (ਪੂਰਨ state[], ਪੂਰਨ statenum, ਪੂਰਨ comstate)
{
	ਪੂਰਨ     i, ਥਾਂ, tblbase;

	ਜੇ (++numprots >= MSP || numecs * numprots >= PROT_SAVE_ਮਾਪ) {
		/* Gotta make room for the new proto by dropping last entry in
		 * the queue.
		 */
		ਥਾਂ = lastprot;
		lastprot = protprev[lastprot];
		protnext[lastprot] = NIL;
	}

	ਨਹੀਂਤਾਂ
		ਥਾਂ = numprots;

	protnext[ਥਾਂ] = firstprot;

	ਜੇ (firstprot != NIL)
		protprev[firstprot] = ਥਾਂ;

	firstprot = ਥਾਂ;
	prottbl[ਥਾਂ] = statenum;
	protcomst[ਥਾਂ] = comstate;

	/* Copy state into save area so it can be compared with rapidly. */
	tblbase = numecs * (ਥਾਂ - 1);

	ਲਈ (i = 1; i <= numecs; ++i)
		protsave[tblbase + i] = state[i];
}


/* mktemplate - create a template entry based on a state, and connect the state
 *              to it
 */

ਖਾਲੀ    mktemplate (ਪੂਰਨ state[], ਪੂਰਨ statenum, ਪੂਰਨ comstate)
{
	ਪੂਰਨ     i, numdiff, tmpbase, tmp[CSIZE + 1];
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ    transset[CSIZE + 1];
	ਪੂਰਨ     tsptr;

	++numtemps;

	tsptr = 0;

	/* Calculate where we will temporarily store the transition table
	 * of the template in the tnxt[] array.  The final transition table
	 * gets created by cmptmps().
	 */

	tmpbase = numtemps * numecs;

	ਜੇ (tmpbase + numecs >= current_max_template_xpairs) {
		current_max_template_xpairs +=
			MAX_TEMPLATE_XPAIRS_INCREMENT;

		++ਅੰਕ_reallocs;

		tnxt = reallocate_integer_array (tnxt,
						 current_max_template_xpairs);
	}

	ਲਈ (i = 1; i <= numecs; ++i)
		ਜੇ (state[i] == 0)
			tnxt[tmpbase + i] = 0;
		ਨਹੀਂਤਾਂ {
			/* Note: range 1..256 is mapped to 1..255,0 */
			transset[tsptr++] = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) i;
			tnxt[tmpbase + i] = comstate;
		}

	ਜੇ (ctrl.usemecs)
		mkeccl (transset, tsptr, tecfwd, tecbck, numecs, 0);

	mkprot (tnxt + tmpbase, -numtemps, comstate);

	/* We rely on the fact that mkprot adds things to the beginning
	 * of the proto queue.
	 */

	numdiff = tbldiff (state, firstprot, tmp);
	mkentry (tmp, numecs, statenum, -numtemps, numdiff);
}


/* mv2front - move proto queue element to front of queue */

ਖਾਲੀ    mv2front (ਪੂਰਨ qelm)
{
	ਜੇ (firstprot != qelm) {
		ਜੇ (qelm == lastprot)
			lastprot = protprev[lastprot];

		protnext[protprev[qelm]] = protnext[qelm];

		ਜੇ (protnext[qelm] != NIL)
			protprev[protnext[qelm]] = protprev[qelm];

		protprev[qelm] = NIL;
		protnext[qelm] = firstprot;
		protprev[firstprot] = qelm;
		firstprot = qelm;
	}
}


/* place_state - place a state into full speed transition table
 *
 * State is the statenum'th state.  It is indexed by equivalence class and
 * gives the number of the state to enter for a given equivalence class.
 * Transnum is the number of out-transitions for the state.
 */

ਖਾਲੀ    ਰੱਖੋ_state (ਪੂਰਨ *state, ਪੂਰਨ statenum, ਪੂਰਨ transnum)
{
	ਪੂਰਨ i;
	ਪੂਰਨ *state_ptr;
	ਪੂਰਨ position = ਲੱਭੋ_ਸਾਰਣੀ_space (state, transnum);

	/* "base" is the table of start positions. */
	ਅਧਾਰ[statenum] = position;

	/* Put in action number marker; this non-zero number makes sure that
	 * find_table_space() knows that this position in chk/nxt is taken
	 * and should not be used for another accepting number in another
	 * state.
	 */
	chk[position - 1] = 1;

	/* Put in end-of-buffer marker; this is for the same purposes as
	 * above.
	 */
	chk[position] = 1;

	/* Place the state into chk and nxt. */
	state_ptr = &state[1];

	ਲਈ (i = 1; i <= numecs; ++i, ++state_ptr)
		ਜੇ (*state_ptr != 0) {
			chk[position + i] = i;
			nxt[position + i] = *state_ptr;
		}

	ਜੇ (position + numecs > tblend)
		tblend = position + numecs;
}


/* stack1 - save states with only one out-transition to be processed later
 *
 * If there's room for another state on the "one-transition" stack, the
 * state is pushed onto it, to be processed later by mk1tbl.  If there's
 * no room, we process the sucker right now.
 */

ਖਾਲੀ    stack1 (ਪੂਰਨ statenum, ਪੂਰਨ sym, ਪੂਰਨ nextstate, ਪੂਰਨ deflink)
{
	ਜੇ (onesp >= ONE_ਢੇਰ_ਮਾਪ - 1)
		mk1tbl (statenum, sym, nextstate, deflink);

	ਨਹੀਂਤਾਂ {
		++onesp;
		onestate[onesp] = statenum;
		onesym[onesp] = sym;
		onenext[onesp] = nextstate;
		onedef[onesp] = deflink;
	}
}


/* tbldiff - compute differences between two state tables
 *
 * "state" is the state array which is to be extracted from the pr'th
 * proto.  "pr" is both the number of the proto we are extracting from
 * and an index into the save area where we can find the proto's complete
 * state table.  Each entry in "state" which differs from the corresponding
 * entry of "pr" will appear in "ext".
 *
 * Entries which are the same in both "state" and "pr" will be marked
 * as transitions to "SAME_TRANS" in "ext".  The total number of differences
 * between "state" and "pr" is returned as function value.  Note that this
 * number is "numecs" minus the number of "SAME_TRANS" entries in "ext".
 */

ਪੂਰਨ     tbldiff (ਪੂਰਨ state[], ਪੂਰਨ pr, ਪੂਰਨ ext[])
{
	ਪੂਰਨ i, *sp = state, *ep = ext, *protp;
	ਪੂਰਨ numdiff = 0;

	protp = &protsave[numecs * (pr - 1)];

	ਲਈ (i = numecs; i > 0; --i) {
		ਜੇ (*++protp == *++sp)
			*++ep = SAME_TRANS;
		ਨਹੀਂਤਾਂ {
			*++ep = *sp;
			++numdiff;
		}
	}

	ਵਾਪਸ numdiff;
}
