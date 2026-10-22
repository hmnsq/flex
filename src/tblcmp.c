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

#شامل "flexdef.h"


/* declarations for functions that have forward references */

خالی mkentry(صحیح *, صحیح, صحیح, صحیح, صحیح);
خالی mkprot(صحیح[], صحیح, صحیح);
خالی mktemplate(صحیح[], صحیح, صحیح);
خالی mv2front(صحیح);
صحیح tbldiff(صحیح[], صحیح, صحیح[]);


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

خالی    bldtbl (صحیح state[], صحیح statenum, صحیح totaltrans, صحیح comstate, صحیح comfreq)
{
	صحیح     extptr, extrct[2][CSIZE + 1];
	صحیح     mindiff, minprot, i, d;

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

	اگر ((totaltrans * 100) < (numecs * PROTO_سائز_PERCENTAGE))
		mkentry (state, numecs, statenum, JAMSTATE, totaltrans);

	ورنہ {
		/* "checkcom" is true if we should only check "state" against
		 * protos which have the same "comstate" value.
		 */
		صحیح     checkcom =

			comfreq * 100 > totaltrans * CHECK_COM_PERCENTAGE;

		minprot = firstprot;
		mindiff = totaltrans;

		اگر (checkcom) {
			/* Find first proto which has the same "comstate". */
			برائے (i = firstprot; i != NIL; i = protnext[i])
				اگر (protcomst[i] == comstate) {
					minprot = i;
					mindiff = tbldiff (state, minprot,
							   extrct[extptr]);
					توڑو;
				}
		}

		ورنہ {
			/* Since we've decided that the most common destination
			 * out of "state" does not occur with a high enough
			 * frequency, we set the "comstate" to zero, assuring
			 * that if this state is entered into the proto list,
			 * it will not be considered a template.
			 */
			comstate = 0;

			اگر (firstprot != NIL) {
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

		اگر (mindiff * 100 >
		    totaltrans * پہلا_مطابقت_DIFF_PERCENTAGE) {
			/* Not a good enough match.  Scan the rest of the
			 * protos.
			 */
			برائے (i = minprot; i != NIL; i = protnext[i]) {
				d = tbldiff (state, i, extrct[1 - extptr]);
				اگر (d < mindiff) {
					extptr = 1 - extptr;
					mindiff = d;
					minprot = i;
				}
			}
		}

		/* Check if the proto we've decided on as our best bet is close
		 * enough to the state we want to match to be usable.
		 */

		اگر (mindiff * 100 >
		    totaltrans * ACCEPTABLE_DIFF_PERCENTAGE) {
			/* No good.  If the state is homogeneous enough,
			 * we make a template out of it.  Otherwise, we
			 * make a proto.
			 */

			اگر (comfreq * 100 >=
			    totaltrans * TEMPLATE_SAME_PERCENTAGE)
					mktemplate (state, statenum,
						    comstate);

			ورنہ {
				mkprot (state, statenum, comstate);
				mkentry (state, numecs, statenum,
					 JAMSTATE, totaltrans);
			}
		}

		ورنہ {		/* use the proto */
			mkentry (extrct[extptr], numecs, statenum,
				 prottbl[minprot], mindiff);

			/* If this state was sufficiently different from the
			 * proto we built it from, make it, too, a proto.
			 */

			اگر (mindiff * 100 >=
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

خالی    cmptmps (خالی)
{
	صحیح tmpstorage[CSIZE + 1];
	صحیح *tmp = tmpstorage, i, j;
	صحیح totaltrans, trans;

	peakpairs = numtemps * numecs + tblend;

	اگر (ctrl.usemecs) {
		/* Create equivalence classes based on data gathered on
		 * template transitions.
		 */
		nummecs = cre8ecs (tecfwd, tecbck, numecs);
	}

	ورنہ
		nummecs = numecs;

	جب (lastdfa + numtemps + 1 >= current_max_dfas)
		increase_max_dfas ();

	/* Loop through each template. */

	برائے (i = 1; i <= numtemps; ++i) {
		/* Number of non-jam transitions out of this template. */
		totaltrans = 0;

		برائے (j = 1; j <= numecs; ++j) {
			trans = tnxt[numecs * i + j];

			اگر (ctrl.usemecs) {
				/* The absolute value of tecbck is the
				 * meta-equivalence class of a given
				 * equivalence class, as set up by cre8ecs().
				 */
				اگر (tecbck[j] > 0) {
					tmp[tecbck[j]] = trans;

					اگر (trans > 0)
						++totaltrans;
				}
			}

			ورنہ {
				tmp[j] = trans;

				اگر (trans > 0)
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

خالی    expand_nxt_chk (خالی)
{
	صحیح old_max = current_max_xpairs;

	current_max_xpairs += MAX_XPAIRS_INCREMENT;

	++عدد_reallocs;

	nxt = reallocate_integer_array (nxt, current_max_xpairs);
	chk = reallocate_integer_array (chk, current_max_xpairs);

	memset(chk + old_max, 0, MAX_XPAIRS_INCREMENT * حجم(صحیح));
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

صحیح     ڈھونڈو_جدول_space (صحیح *state, صحیح numtrans)
{
	/* Firstfree is the position of the first possible occurrence of two
	 * consecutive unused records in the chk and nxt arrays.
	 */
	صحیح i;
	صحیح *state_ptr, *chk_ptr;
	صحیح *ptr_مقصد_آخری_اندراج_اندر_state;

	/* If there are too many out-transitions, put the state at the end of
	 * nxt and chk.
	 */
	اگر (numtrans > MAX_XTIONS_بھرا_INTERIOR_FIT) {
		/* If table is empty, return the first available spot in
		 * chk/nxt, which should be 1.
		 */
		اگر (tblend < 2)
			واپس 1;

		/* Start searching for table space near the end of
		 * chk/nxt arrays.
		 */
		i = tblend - numecs;
	}

	ورنہ
		/* Start searching for table space from the beginning
		 * (skipping only the elements which will definitely not
		 * hold the new state).
		 */
		i = firstfree;

	جب (1) {		/* loops until a space is found */
		جب (i + numecs >= current_max_xpairs)
			expand_nxt_chk ();

		/* Loops until space for end-of-buffer and action number
		 * are found.
		 */
		جب (1) {
			/* Check for action number space. */
			اگر (chk[i - 1] == 0) {
				/* Check for end-of-buffer space. */
				اگر (chk[i] == 0)
					توڑو;

				ورنہ
					/* Since i != 0, there is no use
					 * checking to see if (++i) - 1 == 0,
					 * because that's the same as i == 0,
					 * so we skip a space.
					 */
					i += 2;
			}

			ورنہ
				++i;

			جب (i + numecs >= current_max_xpairs)
				expand_nxt_chk ();
		}

		/* If we started search from the beginning, store the new
		 * firstfree for the next call of find_table_space().
		 */
		اگر (numtrans <= MAX_XTIONS_بھرا_INTERIOR_FIT)
			firstfree = i + 1;

		/* Check to see if all elements in chk (and therefore nxt)
		 * that are needed for the new state have not yet been taken.
		 */

		state_ptr = &state[1];
		ptr_مقصد_آخری_اندراج_اندر_state = &chk[i + numecs + 1];

		برائے (chk_ptr = &chk[i + 1];
		     chk_ptr != ptr_مقصد_آخری_اندراج_اندر_state; ++chk_ptr)
			اگر (*(state_ptr++) != 0 && *chk_ptr != 0)
				توڑو;

		اگر (chk_ptr == ptr_مقصد_آخری_اندراج_اندر_state)
			واپس i;

		ورنہ
			++i;
	}
}


/* inittbl - initialize transition tables
 *
 * Initializes "firstfree" to be one beyond the end of the table.  Initializes
 * all "chk" entries to be zero.
 */
خالی    inittbl (خالی)
{
	صحیح i;

	memset(chk, 0, (size_t) current_max_xpairs * حجم(صحیح));

	tblend = 0;
	firstfree = tblend + 1;
	numtemps = 0;

	اگر (ctrl.usemecs) {
		/* Set up doubly-linked meta-equivalence classes; these
		 * are sets of equivalence classes which all have identical
		 * transitions out of TEMPLATES.
		 */

		tecbck[1] = NIL;

		برائے (i = 2; i <= numecs; ++i) {
			tecbck[i] = i - 1;
			tecfwd[i - 1] = i;
		}

		tecfwd[numecs] = NIL;
	}
}


/* mkdeftbl - make the default, "jam" table entries */

خالی    mkdeftbl (خالی)
{
	صحیح     i;

	jamstate = lastdfa + 1;

	++tblend;		/* room for transition on end-of-buffer character */

	جب (tblend + numecs >= current_max_xpairs)
		expand_nxt_chk ();

	/* Add in default end-of-buffer transition. */
	nxt[tblend] = انتہا_کا_بفر_state;
	chk[tblend] = jamstate;

	برائے (i = 1; i <= numecs; ++i) {
		nxt[tblend + i] = 0;
		chk[tblend + i] = jamstate;
	}

	jambase = tblend;

	بنیاد[jamstate] = jambase;
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

خالی    mkentry (صحیح *state, صحیح numchars, صحیح statenum, صحیح deflink,
		 صحیح totaltrans)
{
	صحیح minec, maxec, i, baseaddr;
	صحیح tblbase, tbllast;

	اگر (totaltrans == 0) {	/* there are no out-transitions */
		اگر (deflink == JAMSTATE)
			بنیاد[statenum] = JAMSTATE;
		ورنہ
			بنیاد[statenum] = 0;

		def[statenum] = deflink;
		واپس;
	}

	برائے (minec = 1; minec <= numchars; ++minec) {
		اگر (state[minec] != SAME_TRANS)
			اگر (state[minec] != 0 || deflink != JAMSTATE)
				توڑو;
	}

	اگر (totaltrans == 1) {
		/* There's only one out-transition.  Save it for later to fill
		 * in holes in the tables.
		 */
		stack1 (statenum, minec, state[minec], deflink);
		واپس;
	}

	برائے (maxec = numchars; maxec > 0; --maxec) {
		اگر (state[maxec] != SAME_TRANS)
			اگر (state[maxec] != 0 || deflink != JAMSTATE)
				توڑو;
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
	اگر (totaltrans * 100 <= numchars * INTERIOR_FIT_PERCENTAGE) {
		/* Attempt to squeeze it into the middle of the tables. */
		baseaddr = firstfree;

		جب (baseaddr < minec) {
			/* Using baseaddr would result in a negative base
			 * address below; find the next free slot.
			 */
			برائے (++baseaddr; chk[baseaddr] != 0; ++baseaddr) ;
		}

		جب (baseaddr + maxec - minec + 1 >= current_max_xpairs)
			expand_nxt_chk ();

		برائے (i = minec; i <= maxec; ++i)
			اگر (state[i] != SAME_TRANS &&
			    (state[i] != 0 || deflink != JAMSTATE) &&
			    chk[baseaddr + i - minec] != 0) {	/* baseaddr unsuitable - find another */
				برائے (++baseaddr;
				     baseaddr < current_max_xpairs &&
				     chk[baseaddr] != 0; ++baseaddr) ;

				جب (baseaddr + maxec - minec + 1 >=
				       current_max_xpairs)
						expand_nxt_chk ();

				/* Reset the loop counter so we'll start all
				 * over again next time it's incremented.
				 */

				i = minec - 1;
			}
	}

	ورنہ {
		/* Ensure that the base address we eventually generate is
		 * non-negative.
		 */
		baseaddr = MAX (tblend + 1, minec);
	}

	tblbase = baseaddr - minec;
	tbllast = tblbase + maxec;

	جب (tbllast + 1 >= current_max_xpairs)
		expand_nxt_chk ();

	بنیاد[statenum] = tblbase;
	def[statenum] = deflink;

	برائے (i = minec; i <= maxec; ++i)
		اگر (state[i] != SAME_TRANS)
			اگر (state[i] != 0 || deflink != JAMSTATE) {
				nxt[tblbase + i] = state[i];
				chk[tblbase + i] = statenum;
			}

	اگر (baseaddr == firstfree)
		/* Find next free slot in tables. */
		برائے (++firstfree; chk[firstfree] != 0; ++firstfree) ;

	tblend = MAX (tblend, tbllast);
}


/* mk1tbl - create table entries for a state (or state fragment) which
 *            has only one out-transition
 */

خالی    mk1tbl (صحیح state, صحیح sym, صحیح onenxt, صحیح onedef)
{
	اگر (firstfree < sym)
		firstfree = sym;

	جب (chk[firstfree] != 0)
		اگر (++firstfree >= current_max_xpairs)
			expand_nxt_chk ();

	بنیاد[state] = firstfree - sym;
	def[state] = onedef;
	chk[firstfree] = state;
	nxt[firstfree] = onenxt;

	اگر (firstfree > tblend) {
		tblend = firstfree++;

		اگر (firstfree >= current_max_xpairs)
			expand_nxt_chk ();
	}
}


/* mkprot - create new proto entry */

خالی    mkprot (صحیح state[], صحیح statenum, صحیح comstate)
{
	صحیح     i, خانہ, tblbase;

	اگر (++numprots >= MSP || numecs * numprots >= PROT_SAVE_سائز) {
		/* Gotta make room for the new proto by dropping last entry in
		 * the queue.
		 */
		خانہ = lastprot;
		lastprot = protprev[lastprot];
		protnext[lastprot] = NIL;
	}

	ورنہ
		خانہ = numprots;

	protnext[خانہ] = firstprot;

	اگر (firstprot != NIL)
		protprev[firstprot] = خانہ;

	firstprot = خانہ;
	prottbl[خانہ] = statenum;
	protcomst[خانہ] = comstate;

	/* Copy state into save area so it can be compared with rapidly. */
	tblbase = numecs * (خانہ - 1);

	برائے (i = 1; i <= numecs; ++i)
		protsave[tblbase + i] = state[i];
}


/* mktemplate - create a template entry based on a state, and connect the state
 *              to it
 */

خالی    mktemplate (صحیح state[], صحیح statenum, صحیح comstate)
{
	صحیح     i, numdiff, tmpbase, tmp[CSIZE + 1];
	غیرعلامتی حرف    transset[CSIZE + 1];
	صحیح     tsptr;

	++numtemps;

	tsptr = 0;

	/* Calculate where we will temporarily store the transition table
	 * of the template in the tnxt[] array.  The final transition table
	 * gets created by cmptmps().
	 */

	tmpbase = numtemps * numecs;

	اگر (tmpbase + numecs >= current_max_template_xpairs) {
		current_max_template_xpairs +=
			MAX_TEMPLATE_XPAIRS_INCREMENT;

		++عدد_reallocs;

		tnxt = reallocate_integer_array (tnxt,
						 current_max_template_xpairs);
	}

	برائے (i = 1; i <= numecs; ++i)
		اگر (state[i] == 0)
			tnxt[tmpbase + i] = 0;
		ورنہ {
			/* Note: range 1..256 is mapped to 1..255,0 */
			transset[tsptr++] = (غیرعلامتی حرف) i;
			tnxt[tmpbase + i] = comstate;
		}

	اگر (ctrl.usemecs)
		mkeccl (transset, tsptr, tecfwd, tecbck, numecs, 0);

	mkprot (tnxt + tmpbase, -numtemps, comstate);

	/* We rely on the fact that mkprot adds things to the beginning
	 * of the proto queue.
	 */

	numdiff = tbldiff (state, firstprot, tmp);
	mkentry (tmp, numecs, statenum, -numtemps, numdiff);
}


/* mv2front - move proto queue element to front of queue */

خالی    mv2front (صحیح qelm)
{
	اگر (firstprot != qelm) {
		اگر (qelm == lastprot)
			lastprot = protprev[lastprot];

		protnext[protprev[qelm]] = protnext[qelm];

		اگر (protnext[qelm] != NIL)
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

خالی    رکھو_state (صحیح *state, صحیح statenum, صحیح transnum)
{
	صحیح i;
	صحیح *state_ptr;
	صحیح position = ڈھونڈو_جدول_space (state, transnum);

	/* "base" is the table of start positions. */
	بنیاد[statenum] = position;

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

	برائے (i = 1; i <= numecs; ++i, ++state_ptr)
		اگر (*state_ptr != 0) {
			chk[position + i] = i;
			nxt[position + i] = *state_ptr;
		}

	اگر (position + numecs > tblend)
		tblend = position + numecs;
}


/* stack1 - save states with only one out-transition to be processed later
 *
 * If there's room for another state on the "one-transition" stack, the
 * state is pushed onto it, to be processed later by mk1tbl.  If there's
 * no room, we process the sucker right now.
 */

خالی    stack1 (صحیح statenum, صحیح sym, صحیح nextstate, صحیح deflink)
{
	اگر (onesp >= ONE_ڈھیر_سائز - 1)
		mk1tbl (statenum, sym, nextstate, deflink);

	ورنہ {
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

صحیح     tbldiff (صحیح state[], صحیح pr, صحیح ext[])
{
	صحیح i, *sp = state, *ep = ext, *protp;
	صحیح numdiff = 0;

	protp = &protsave[numecs * (pr - 1)];

	برائے (i = numecs; i > 0; --i) {
		اگر (*++protp == *++sp)
			*++ep = SAME_TRANS;
		ورنہ {
			*++ep = *sp;
			++numdiff;
		}
	}

	واپس numdiff;
}
