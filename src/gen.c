/* gen - actual generation (writing) of flex scanners */

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
#అన్తర్భావ "tables.h"

/* These typedefs are only used for computing footprint sizes,
 * You need to make sure they match reality in the skeleton file to
 * get accurate numbers, but they don't otherwise matter.
 */
రకనిర్వచనం అక్షరం YY_CHAR;
నిర్మాణం yy_trans_info {int32_t yy_verify; int32_t yy_nxt;};

/* declare functions that have forward references */

స్థిర శూన్య genecs(శూన్య);

నిర్మాణం packtype_t *optimize_pack(size_t sz)
{
	/* FIXME: There's a 32-bit assumption lurking here */
	స్థిర నిర్మాణం packtype_t బహిర్గతం;
	ఒకవేళ (sz == 0) {
		బహిర్గతం.name  = ctrl.long_align ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		బహిర్గతం.వెడల్పు = ctrl.long_align ? 32 : 16;
	} లేకపోతే {
		బహిర్గతం.name = (ctrl.long_align || sz >= INT16_MAX) ? "M4_HOOK_INT32" : "M4_HOOK_INT16";
		బహిర్గతం.వెడల్పు = (ctrl.long_align || sz >= INT16_MAX) ? 32 : 16;
	}
	తిరిగి &బహిర్గతం;
}

/* Almost everything is done in terms of arrays starting at 1, so provide
 * a null entry for the zero element of all C arrays.  (The exception
 * to this is that the fast table representation generally uses the
 * 0 elements of its arrays, too.)
 */

/** Make the table for possible eol matches.
 *  @return the newly allocated rule_can_match_eol table
 */
స్థిర నిర్మాణం yytbl_దత్తాంశం *mkeoltbl (శూన్య)
{
	పూర్ణాంకం     i;
	flex_int8_t *tdata = 0;
	నిర్మాణం yytbl_దత్తాంశం *tbl;

	tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	yytbl_దత్తాంశం_init (tbl, YYTD_ID_నియమం_CAN_సరిపోలిక_EOL);
	tbl->td_flags = YYTD_DATA8;
	tbl->td_lolen = (flex_uint32_t) (అంకె_నియమాలు + 1);
	tbl->td_దత్తాంశం = tdata =
		సున్నా_జ్ఞాపకం_ఇవ్వు(tbl->td_lolen, పరిమాణం (flex_int8_t));

	కొరకు (i = 1; i <= అంకె_నియమాలు; i++)
		tdata[i] = నియమం_has_nl[i] ? 1 : 0;

	తిరిగి tbl;
}

/* Generate the table for possible eol matches. */
స్థిర శూన్య geneoltbl (శూన్య)
{
	పూర్ణాంకం     i;
	నిర్మాణం packtype_t *ptype = optimize_pack(అంకె_నియమాలు);

	outn ("m4_ifdef( [[M4_MODE_YYLINENO]],[[");
	బహిర్గతం_str ("m4_define([[M4_HOOK_EOLTABLE_TYPE]], [[%s]])\n", ptype->name);
	బహిర్గతం_dec ("m4_define([[M4_HOOK_EOLTABLE_SIZE]], [[%d]])", అంకె_నియమాలు + 1);
	outn ("m4_define([[M4_HOOK_EOLTABLE_BODY]], [[m4_dnl");

	ఒకవేళ (gentables) {
		కొరకు (i = 1; i <= అంకె_నియమాలు; i++) {
			బహిర్గతం_dec ("%d, ", నియమం_has_nl[i] ? 1 : 0);
			/* format nicely, 20 numbers per line. */
			ఒకవేళ ((i % 20) == 19)
				బహిర్గతం ("\n    ");
		}
	}
	footprint += అంకె_నియమాలు * ptype->వెడల్పు;
	outn ("]])");
	outn ("]])");
}


/** mkctbl - make full speed compressed transition table
 * This is an array of structs; each struct a pair of integers.
 * You should call mkssltbl() immediately after this.
 * Then, I think, mkecstbl(). Arrrg.
 * @return the newly allocated trans table
 */

స్థిర నిర్మాణం yytbl_దత్తాంశం *mkctbl (శూన్య)
{
	పూర్ణాంకం i;
	నిర్మాణం yytbl_దత్తాంశం *tbl = 0;
	flex_int32_t *tdata = 0, curr = 0;
	పూర్ణాంకం     చివర_యొక్క_బఫరు_action = అంకె_నియమాలు + 1;

	నిర్మాణం packtype_t *ptype = optimize_pack(tblend + 2 + 1);
	బహిర్గతం_str ("m4_define([[M4_HOOK_MKCTBL_TYPE]], [[%s]])", ptype->name);

	tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	yytbl_దత్తాంశం_init (tbl, YYTD_ID_TRANSITION);
	tbl->td_flags = YYTD_DATA32 | YYTD_STRUCT;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (tblend + 2 + 1);	/* number of structs */

	tbl->td_దత్తాంశం = tdata =
		సున్నా_జ్ఞాపకం_ఇవ్వు(tbl->td_lolen * 2, పరిమాణం (flex_int32_t));

	/* We want the transition to be represented as the offset to the
	 * next state, not the actual state number, which is what it currently
	 * is.  The offset is base[nxt[i]] - (base of current state)].  That's
	 * just the difference between the starting points of the two involved
	 * states (to - from).
	 *
	 * First, though, we need to find some way to put in our end-of-buffer
	 * flags and states.  We do this by making a state with absolutely no
	 * transitions.  We put it at the end of the table.
	 */

	/* We need to have room in nxt/chk for two more slots: One for the
	 * action and one for the end-of-buffer transition.  We now *assume*
	 * that we're guaranteed the only character we'll try to index this
	 * nxt/chk pair with is EOB, i.e., 0, so we don't have to make sure
	 * there's room for jam entries for other characters.
	 */

	అయితే (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	అయితే (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	పునాది[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = చివర_యొక్క_బఫరు_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	కొరకు (i = 0; i <= lastdfa; ++i) {
		పూర్ణాంకం     anum = dfaacc[i].dfaacc_state;
		పూర్ణాంకం     స్థానభ్రంశం = పునాది[i];

		chk[స్థానభ్రంశం] = EOB_POSITION;
		chk[స్థానభ్రంశం - 1] = ACTION_POSITION;
		nxt[స్థానభ్రంశం - 1] = anum;	/* action number */
	}

	కొరకు (i = 0; i <= tblend; ++i) {
		ఒకవేళ (chk[i] == EOB_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = పునాది[lastdfa + 1] - i;
		}

		లేకపోతే ఒకవేళ (chk[i] == ACTION_POSITION) {
			tdata[curr++] = 0;
			tdata[curr++] = nxt[i];
		}

		లేకపోతే ఒకవేళ (chk[i] > numecs || chk[i] == 0) {
			tdata[curr++] = 0;
			tdata[curr++] = 0;
		}
		లేకపోతే {		/* verify, transition */

			tdata[curr++] = chk[i];
			tdata[curr++] = పునాది[nxt[i]] - (i - chk[i]);
		}
	}

	/* Here's the final, end-of-buffer state. */
	tdata[curr++] = chk[tblend + 1];
	tdata[curr++] = nxt[tblend + 1];

	tdata[curr++] = chk[tblend + 2];
	tdata[curr++] = nxt[tblend + 2];

	తిరిగి tbl;
}


/** Make start_state_list table.
 *  @return the newly allocated start_state_list table
 */
స్థిర నిర్మాణం yytbl_దత్తాంశం *mkssltbl (శూన్య)
{
	నిర్మాణం yytbl_దత్తాంశం *tbl = 0;
	flex_int32_t *tdata = 0;
	flex_int32_t i;

	tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	yytbl_దత్తాంశం_init (tbl, YYTD_ID_ప్రారంభం_STATE_LIST);
	tbl->td_flags = YYTD_DATA32 | YYTD_PTRANS;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) (lastsc * 2 + 1);

	tbl->td_దత్తాంశం = tdata =
		సున్నా_జ్ఞాపకం_ఇవ్వు(tbl->td_lolen, పరిమాణం (flex_int32_t));

	కొరకు (i = 0; i <= lastsc * 2; ++i)
		tdata[i] = పునాది[i];

	తిరిగి tbl;
}



/* genctbl - generates full speed compressed transition table */

స్థిర శూన్య genctbl(శూన్య)
{
	పూర్ణాంకం i;
	పూర్ణాంకం     చివర_యొక్క_బఫరు_action = అంకె_నియమాలు + 1;

	/* Table of verify for transition and offset to next state. */
	బహిర్గతం_dec ("m4_define([[M4_HOOK_TRANSTABLE_SIZE]], [[%d]])", tblend + 2 + 1);
	outn ("m4_define([[M4_HOOK_TRANSTABLE_BODY]], [[m4_dnl");

	/* We want the transition to be represented as the offset to the
	 * next state, not the actual state number, which is what it currently
	 * is.  The offset is base[nxt[i]] - (base of current state)].  That's
	 * just the difference between the starting points of the two involved
	 * states (to - from).
	 *
	 * First, though, we need to find some way to put in our end-of-buffer
	 * flags and states.  We do this by making a state with absolutely no
	 * transitions.  We put it at the end of the table.
	 */

	/* We need to have room in nxt/chk for two more slots: One for the
	 * action and one for the end-of-buffer transition.  We now *assume*
	 * that we're guaranteed the only character we'll try to index this
	 * nxt/chk pair with is EOB, i.e., 0, so we don't have to make sure
	 * there's room for jam entries for other characters.
	 */

	అయితే (tblend + 2 >= current_max_xpairs)
		expand_nxt_chk ();

	అయితే (lastdfa + 1 >= current_max_dfas)
		increase_max_dfas ();

	పునాది[lastdfa + 1] = tblend + 2;
	nxt[tblend + 1] = చివర_యొక్క_బఫరు_action;
	chk[tblend + 1] = numecs + 1;
	chk[tblend + 2] = 1;	/* anything but EOB */

	/* So that "make test" won't show arb. differences. */
	nxt[tblend + 2] = 0;

	/* Make sure every state has an end-of-buffer transition and an
	 * action #.
	 */
	కొరకు (i = 0; i <= lastdfa; ++i) {
		పూర్ణాంకం     anum = dfaacc[i].dfaacc_state;
		పూర్ణాంకం     స్థానభ్రంశం = పునాది[i];

		chk[స్థానభ్రంశం] = EOB_POSITION;
		chk[స్థానభ్రంశం - 1] = ACTION_POSITION;
		nxt[స్థానభ్రంశం - 1] = anum;	/* action number */
	}

	కొరకు (i = 0; i <= tblend; ++i) {
		ఒకవేళ (chk[i] == EOB_POSITION)
			transition_struct_బహిర్గతం (0, పునాది[lastdfa + 1] - i);

		లేకపోతే ఒకవేళ (chk[i] == ACTION_POSITION)
			transition_struct_బహిర్గతం (0, nxt[i]);

		లేకపోతే ఒకవేళ (chk[i] > numecs || chk[i] == 0)
			transition_struct_బహిర్గతం (0, 0);	/* unused slot */

		లేకపోతే		/* verify, transition */
			transition_struct_బహిర్గతం (chk[i],
					       పునాది[nxt[i]] - (i -
							       chk[i]));
	}


	/* Here's the final, end-of-buffer state. */
	transition_struct_బహిర్గతం (chk[tblend + 1], nxt[tblend + 1]);
	transition_struct_బహిర్గతం (chk[tblend + 2], nxt[tblend + 2]);

	outn ("]])");
	footprint += పరిమాణం(నిర్మాణం yy_trans_info) * (tblend + 2 + 1);

	బహిర్గతం_dec ("m4_define([[M4_HOOK_STARTTABLE_SIZE]], [[%d]])", lastsc * 2 + 1);
	ఒకవేళ (gentables) {
		outn ("m4_define([[M4_HOOK_STARTTABLE_BODY]], [[m4_dnl");
		కొరకు (i = 0; i <= lastsc * 2; ++i)
			బహిర్గతం_dec ("M4_HOOK_STATE_ENTRY_FORMAT(%d)", పునాది[i]);

		dataend (ఖాళీ);
		outn("]])");
		footprint +=  పరిమాణం(నిర్మాణం yy_trans_info *) * (lastsc * 2 + 1);
	}

	ఒకవేళ (ctrl.useecs)
		genecs ();
}


/* mkecstbl - Make equivalence-class tables.  */

స్థిర నిర్మాణం yytbl_దత్తాంశం *mkecstbl (శూన్య)
{
	పూర్ణాంకం i;
	నిర్మాణం yytbl_దత్తాంశం *tbl = 0;
	flex_int32_t *tdata = 0;

	tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	yytbl_దత్తాంశం_init (tbl, YYTD_ID_EC);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;
	tbl->td_lolen = (flex_uint32_t) ctrl.csize;

	tbl->td_దత్తాంశం = tdata =
		సున్నా_జ్ఞాపకం_ఇవ్వు(tbl->td_lolen, పరిమాణం (flex_int32_t));

	కొరకు (i = 1; i < ctrl.csize; ++i) {
		ecgroup[i] = ABS (ecgroup[i]);
		tdata[i] = ecgroup[i];
	}

	తిరిగి tbl;
}

/* Generate equivalence-class tables. */

స్థిర శూన్య genecs(శూన్య)
{
	పూర్ణాంకం ch, అడ్డువరుస;
	పూర్ణాంకం     numrows;

	బహిర్గతం_dec ("m4_define([[M4_HOOK_ECSTABLE_SIZE]], [[%d]])", ctrl.csize);
	outn ("m4_define([[M4_HOOK_ECSTABLE_BODY]], [[m4_dnl");

	కొరకు (ch = 1; ch < ctrl.csize; ++ch) {
		ecgroup[ch] = ABS (ecgroup[ch]);
		mkdata (ecgroup[ch]);
	}

	dataend (ఖాళీ);
	outn("]])");
	footprint += పరిమాణం(YY_CHAR) * ctrl.csize;

	ఒకవేళ (env.trace) {
		fputs (_("\n\nEquivalence Classes:\n\n"), stderr);

		/* Print in 8 columns */
		numrows = ctrl.csize / 8;

		కొరకు (అడ్డువరుస = 0; అడ్డువరుస < numrows; ++అడ్డువరుస) {
			కొరకు (ch = అడ్డువరుస; ch < ctrl.csize; ch += numrows) {
				fprintf (stderr, "%4s = %-2d",
					 readable_form (ch), ecgroup[ch]);

				putc (' ', stderr);
			}

			putc ('\n', stderr);
		}
	}
}

/* mkftbl - make the full table and return the struct .
 * you should call mkecstbl() after this.
 */

స్థిర నిర్మాణం yytbl_దత్తాంశం *mkftbl(శూన్య)
{
	పూర్ణాంకం i;
	పూర్ణాంకం     చివర_యొక్క_బఫరు_action = అంకె_నియమాలు + 1;
	నిర్మాణం yytbl_దత్తాంశం *tbl;
	flex_int32_t *tdata = 0;

	tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	yytbl_దత్తాంశం_init (tbl, YYTD_ID_ACCEPT);
	tbl->td_flags |= YYTD_DATA32;
	tbl->td_hilen = 0;	/* it's a one-dimensional array */
	tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);

	tbl->td_దత్తాంశం = tdata =
		సున్నా_జ్ఞాపకం_ఇవ్వు(tbl->td_lolen, పరిమాణం (flex_int32_t));

	dfaacc[చివర_యొక్క_బఫరు_state].dfaacc_state = చివర_యొక్క_బఫరు_action;

	కొరకు (i = 1; i <= lastdfa; ++i) {
		పూర్ణాంకం anum = dfaacc[i].dfaacc_state;

		tdata[i] = anum;

		ఒకవేళ (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	తిరిగి tbl;
}


/* genftbl - generate full transition table */

స్థిర శూన్య genftbl(శూన్య)
{
	పూర్ణాంకం i;
	పూర్ణాంకం     చివర_యొక్క_బఫరు_action = అంకె_నియమాలు + 1;
	నిర్మాణం packtype_t *ptype = optimize_pack(అంకె_నియమాలు + 1);

	dfaacc[చివర_యొక్క_బఫరు_state].dfaacc_state = చివర_యొక్క_బఫరు_action;

	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	బహిర్గతం_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	బహిర్గతం_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", lastdfa + 1);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	కొరకు (i = 1; i <= lastdfa; ++i) {
		పూర్ణాంకం anum = dfaacc[i].dfaacc_state;

		mkdata (anum);

		ఒకవేళ (env.trace && anum)
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, anum);
	}

	dataend (ఖాళీ);
	outn("]])");
	footprint += (lastdfa + 1) * ptype->వెడల్పు;

	ఒకవేళ (ctrl.useecs)
		genecs ();

	/* Don't have to dump the actual full table entries - they were
	 * created on-the-fly.
	 */
}

/* gentabs - generate data statements for the transition tables */

స్థిర శూన్య gentabs(శూన్య)
{
	పూర్ణాంకం     sz, i, j, k, *accset, nacc, *acc_array, మొత్తం_స్థితులు;
	పూర్ణాంకం     చివర_యొక్క_బఫరు_action = అంకె_నియమాలు + 1;
	నిర్మాణం yytbl_దత్తాంశం *yyacc_tbl = 0, *yymeta_tbl = 0, *yybase_tbl = 0,
	    *yydef_tbl = 0, *yynxt_tbl = 0, *yychk_tbl = 0, *yyacclist_tbl=0;
	flex_int32_t *yyacc_దత్తాంశం = 0, *yybase_దత్తాంశం = 0, *yydef_దత్తాంశం = 0,
	    *yynxt_దత్తాంశం = 0, *yychk_దత్తాంశం = 0, *yyacclist_దత్తాంశం=0;
	flex_int32_t yybase_curr = 0, yyacclist_curr=0,yyacc_curr=0;
	నిర్మాణం packtype_t *ptype;

	acc_array = allocate_integer_array (current_max_dfas);
	nummt = 0;

	/* The compressed table format jams by entering the "jam state",
	 * losing information about the previous state in the process.
	 * In order to recover the previous state, we effectively need
	 * to keep backing-up information.
	 */
	++అంకె_backing_పైకి;

	ఒకవేళ (reject) {
		/* Write out accepting list and pointer list.

		 * First we generate the "yy_acclist" array.  In the process,
		 * we compute the indices that will go into the "yy_accept"
		 * array, and save the indices in the dfaacc array.
		 */
		పూర్ణాంకం     EOB_accepting_list[2];

		/* Set up accepting structures for the End Of Buffer state. */
		EOB_accepting_list[0] = 0;
		EOB_accepting_list[1] = చివర_యొక్క_బఫరు_action;
		accsiz[చివర_యొక్క_బఫరు_state] = 1;
		dfaacc[చివర_యొక్క_బఫరు_state].dfaacc_సమితి =
		    EOB_accepting_list;

		sz = MAX (numas, 1) + 1;
		ptype = optimize_pack(sz);
		బహిర్గతం_str ("m4_define([[M4_HOOK_ACCLIST_TYPE]], [[%s]])", ptype->name);
		బహిర్గతం_dec ("m4_define([[M4_HOOK_ACCLIST_SIZE]], [[%d]])", sz);
		outn ("m4_define([[M4_HOOK_ACCLIST_BODY]], [[m4_dnl");

		yyacclist_tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1,పరిమాణం(నిర్మాణం yytbl_దత్తాంశం));
		yytbl_దత్తాంశం_init (yyacclist_tbl, YYTD_ID_ACCLIST);
		yyacclist_tbl->td_lolen  = (flex_uint32_t) (MAX(numas,1) + 1);
		yyacclist_tbl->td_దత్తాంశం = yyacclist_దత్తాంశం =
		    సున్నా_జ్ఞాపకం_ఇవ్వు(yyacclist_tbl->td_lolen, పరిమాణం (flex_int32_t));
		yyacclist_curr = 1;

		j = 1;		/* index into "yy_acclist" array */

		కొరకు (i = 1; i <= lastdfa; ++i) {
			acc_array[i] = j;

			ఒకవేళ (accsiz[i] != 0) {
				accset = dfaacc[i].dfaacc_సమితి;
				nacc = accsiz[i];

				ఒకవేళ (env.trace)
					fprintf (stderr,
						 _("state # %d accepts: "),
						 i);

				కొరకు (k = 1; k <= nacc; ++k) {
					పూర్ణాంకం     accnum = accset[k];

					++j;

					ఒకవేళ (variable_trailing_context_నియమాలు
					    && !(accnum &
						 YY_TRAILING_తల_ముసుగు)
					    && accnum > 0
					    && accnum <= అంకె_నియమాలు
					    && నియమం_type[accnum] ==
					    నియమం_VARIABLE) {
						/* Special hack to flag
						 * accepting number as part
						 * of trailing context rule.
						 */
						accnum |= YY_TRAILING_ముసుగు;
					}

					mkdata (accnum);
					yyacclist_దత్తాంశం[yyacclist_curr++] = accnum;

					ఒకవేళ (env.trace) {
						fprintf (stderr, "[%d]",
							 accset[k]);

						ఒకవేళ (k < nacc)
							fputs (", ",
							       stderr);
						లేకపోతే
							putc ('\n',
							      stderr);
					}
				}
			}
		}

		/* add accepting number for the "jam" state */
		acc_array[i] = j;

		dataend (ఖాళీ);
		outn("]])");
		footprint += sz * ptype->వెడల్పు;
		ఒకవేళ (tablesext) {
			yytbl_దత్తాంశం_compress (yyacclist_tbl);
			ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, yyacclist_tbl) < 0)
				flexerror (_("Could not write yyacclist_tbl"));
			yytbl_దత్తాంశం_destroy (yyacclist_tbl);
			yyacclist_tbl = ఖాళీ;
		}
	}

	లేకపోతే {
		dfaacc[చివర_యొక్క_బఫరు_state].dfaacc_state =
		    చివర_యొక్క_బఫరు_action;

		కొరకు (i = 1; i <= lastdfa; ++i)
			acc_array[i] = dfaacc[i].dfaacc_state;

		/* add accepting number for jam state */
		acc_array[i] = 0;
	}

	/* Begin generating yy_accept */

	/* Spit out "yy_accept" array.  If we're doing "reject", it'll be
	 * pointers into the "yy_acclist" array.  Otherwise it's actual
	 * accepting numbers.  In either case, we just dump the numbers.
	 */

	/* "lastdfa + 2" is the size of "yy_accept"; includes room for C arrays
	 * beginning at 0 and for "jam" state.
	 */
	sz = lastdfa + 2;

	ఒకవేళ (reject)
		/* We put a "cap" on the table associating lists of accepting
		 * numbers with state numbers.  This is needed because we tell
		 * where the end of an accepting list is by looking at where
		 * the list for the next state starts.
		 */
		++sz;

	/* Note that this table is alternately defined if ctrl.fulltbl */
	ptype = optimize_pack(sz);
	outn ("m4_define([[M4_HOOK_NEED_ACCEPT]], 1)");
	బహిర్గతం_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
	బహిర్గతం_dec ("m4_define([[M4_HOOK_ACCEPT_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_ACCEPT_BODY]], [[m4_dnl");

	yyacc_tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	yytbl_దత్తాంశం_init (yyacc_tbl, YYTD_ID_ACCEPT);
	yyacc_tbl->td_lolen = (flex_uint32_t) sz;
	yyacc_tbl->td_దత్తాంశం = yyacc_దత్తాంశం =
	    సున్నా_జ్ఞాపకం_ఇవ్వు(yyacc_tbl->td_lolen, పరిమాణం (flex_int32_t));
	yyacc_curr=1;

	కొరకు (i = 1; i <= lastdfa; ++i) {
		mkdata (acc_array[i]);
		yyacc_దత్తాంశం[yyacc_curr++] = acc_array[i];

		ఒకవేళ (!reject && env.trace && acc_array[i])
			fprintf (stderr, _("state # %d accepts: [%d]\n"),
				 i, acc_array[i]);
	}

	/* Add entry for "jam" state. */
	mkdata (acc_array[i]);
	yyacc_దత్తాంశం[yyacc_curr++] = acc_array[i];

	ఒకవేళ (reject) {
		/* Add "cap" for the list. */
		mkdata (acc_array[i]);
		yyacc_దత్తాంశం[yyacc_curr++] = acc_array[i];
	}

	dataend (ఖాళీ);
	outn ("]])");
	footprint += sz * ptype->వెడల్పు;

	ఒకవేళ (tablesext) {
		yytbl_దత్తాంశం_compress (yyacc_tbl);
		ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, yyacc_tbl) < 0)
			flexerror (_("Could not write yyacc_tbl"));
	}
	yytbl_దత్తాంశం_destroy (yyacc_tbl);
	yyacc_tbl = ఖాళీ;
	/* End generating yy_accept */

	ఒకవేళ (ctrl.useecs) {

		genecs ();
		ఒకవేళ (tablesext) {
			నిర్మాణం yytbl_దత్తాంశం *tbl;

			tbl = mkecstbl ();
			yytbl_దత్తాంశం_compress (tbl);
			ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ecstbl"));
			yytbl_దత్తాంశం_destroy (tbl);
			tbl = 0;
		}
	}

	ఒకవేళ (ctrl.usemecs) {
		/* Begin generating yy_meta */
		/* Write out meta-equivalence classes (used to index
		 * templates with).
		 */
		flex_int32_t *yymecs_దత్తాంశం = 0;
		yymeta_tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
		yytbl_దత్తాంశం_init (yymeta_tbl, YYTD_ID_META);
		yymeta_tbl->td_lolen = (flex_uint32_t) (numecs + 1);
		yymeta_tbl->td_దత్తాంశం = yymecs_దత్తాంశం =
		    సున్నా_జ్ఞాపకం_ఇవ్వు(yymeta_tbl->td_lolen,
			   పరిమాణం (flex_int32_t));

		ఒకవేళ (env.trace)
			fputs (_("\n\nMeta-Equivalence Classes:\n"),
			       stderr);
		బహిర్గతం_dec ("m4_define([[M4_HOOK_MECSTABLE_SIZE]], [[%d]])", numecs+1);
		outn ("m4_define([[M4_HOOK_MECSTABLE_BODY]], [[m4_dnl");
 	
		కొరకు (i = 1; i <= numecs; ++i) {
			ఒకవేళ (env.trace)
				fprintf (stderr, "%d = %d\n",
					 i, ABS (tecbck[i]));

			mkdata (ABS (tecbck[i]));
			yymecs_దత్తాంశం[i] = ABS (tecbck[i]);
		}

		dataend (ఖాళీ);
		outn ("]])");
		footprint += పరిమాణం(YY_CHAR) * (numecs + 1);
		ఒకవేళ (tablesext) {
			yytbl_దత్తాంశం_compress (yymeta_tbl);
			ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, yymeta_tbl) < 0)
				flexerror (_("Could not write yymeta_tbl"));
		}
		yytbl_దత్తాంశం_destroy (yymeta_tbl);
		yymeta_tbl = ఖాళీ;
		/* End generating yy_meta */
	}

	మొత్తం_స్థితులు = lastdfa + numtemps;

	/* Begin generating yy_base */
	sz = మొత్తం_స్థితులు + 1;
	ptype = optimize_pack(sz);
	బహిర్గతం_str ("m4_define([[M4_HOOK_BASE_TYPE]], [[%s]])", ptype->name);
	బహిర్గతం_dec ("m4_define([[M4_HOOK_BASE_SIZE]], [[%d]])", sz);
	outn ("m4_define([[M4_HOOK_BASE_BODY]], [[m4_dnl");

	yybase_tbl = సున్నా_జ్ఞాపకం_ఇవ్వు (1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	yytbl_దత్తాంశం_init (yybase_tbl, YYTD_ID_పునాది);
	yybase_tbl->td_lolen = (flex_uint32_t) (మొత్తం_స్థితులు + 1);
	yybase_tbl->td_దత్తాంశం = yybase_దత్తాంశం =
	    సున్నా_జ్ఞాపకం_ఇవ్వు(yybase_tbl->td_lolen,
		   పరిమాణం (flex_int32_t));
	yybase_curr = 1;

	కొరకు (i = 1; i <= lastdfa; ++i) {
		పూర్ణాంకం d = def[i];

		ఒకవేళ (పునాది[i] == JAMSTATE)
			పునాది[i] = jambase;

		ఒకవేళ (d == JAMSTATE)
			def[i] = jamstate;

		లేకపోతే ఒకవేళ (d < 0) {
			/* Template reference. */
			++tmpuses;
			def[i] = lastdfa - d + 1;
		}

		mkdata (పునాది[i]);
		yybase_దత్తాంశం[yybase_curr++] = పునాది[i];
	}

	/* Generate jam state's base index. */
	mkdata (పునాది[i]);
	yybase_దత్తాంశం[yybase_curr++] = పునాది[i];

	కొరకు (++i /* skip jam state */ ; i <= మొత్తం_స్థితులు; ++i) {
		mkdata (పునాది[i]);
		yybase_దత్తాంశం[yybase_curr++] = పునాది[i];
		def[i] = jamstate;
	}

	dataend (ఖాళీ);
	outn ("]])");
	footprint += sz * ptype->వెడల్పు;

	ఒకవేళ (tablesext) {
		yytbl_దత్తాంశం_compress (yybase_tbl);
		ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, yybase_tbl) < 0)
			flexerror (_("Could not write yybase_tbl"));
	}
	yytbl_దత్తాంశం_destroy (yybase_tbl);
	yybase_tbl = ఖాళీ;
	/* End generating yy_base */


	/* Begin generating yy_def */
	ptype = optimize_pack(మొత్తం_స్థితులు + 1);
	బహిర్గతం_str ("m4_define([[M4_HOOK_DEF_TYPE]], [[%s]])", ptype->name);
	బహిర్గతం_dec ("m4_define([[M4_HOOK_DEF_SIZE]], [[%d]])", మొత్తం_స్థితులు + 1);
	outn ("m4_define([[M4_HOOK_DEF_BODY]], [[m4_dnl");

	yydef_tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	yytbl_దత్తాంశం_init (yydef_tbl, YYTD_ID_DEF);
	yydef_tbl->td_lolen = (flex_uint32_t)(మొత్తం_స్థితులు + 1);
	yydef_tbl->td_దత్తాంశం = yydef_దత్తాంశం =
	    సున్నా_జ్ఞాపకం_ఇవ్వు(yydef_tbl->td_lolen, పరిమాణం (flex_int32_t));

	కొరకు (i = 1; i <= మొత్తం_స్థితులు; ++i) {
		mkdata (def[i]);
		yydef_దత్తాంశం[i] = def[i];
	}

	dataend (ఖాళీ);
	outn ("]])");
	footprint += (మొత్తం_స్థితులు + 1) * ptype->వెడల్పు;

	ఒకవేళ (tablesext) {
		yytbl_దత్తాంశం_compress (yydef_tbl);
		ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, yydef_tbl) < 0)
			flexerror (_("Could not write yydef_tbl"));
	}
	yytbl_దత్తాంశం_destroy (yydef_tbl);
	yydef_tbl = ఖాళీ;
	/* End generating yy_def */


	ptype = optimize_pack(tblend + 1);
	/* Note: Used when !ctrl.fulltbl && !ctrl.fullspd).
	 * (Alternately defined when ctrl.fullspd)
	 */
	బహిర్గతం_str ("m4_define([[M4_HOOK_YYNXT_TYPE]], [[%s]])", ptype->name);
	బహిర్గతం_dec ("m4_define([[M4_HOOK_YYNXT_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_YYNXT_BODY]], [[m4_dnl");

	yynxt_tbl = సున్నా_జ్ఞాపకం_ఇవ్వు (1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	yytbl_దత్తాంశం_init (yynxt_tbl, YYTD_ID_NXT);
	yynxt_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yynxt_tbl->td_దత్తాంశం = yynxt_దత్తాంశం =
	    సున్నా_జ్ఞాపకం_ఇవ్వు (yynxt_tbl->td_lolen, పరిమాణం (flex_int32_t));

	కొరకు (i = 1; i <= tblend; ++i) {
		/* Note, the order of the following test is important.
		 * If chk[i] is 0, then nxt[i] is undefined.
		 */
		ఒకవేళ (chk[i] == 0 || nxt[i] == 0)
			nxt[i] = jamstate;	/* new state is the JAM state */

		mkdata (nxt[i]);
		yynxt_దత్తాంశం[i] = nxt[i];
	}

	dataend (ఖాళీ);
	outn("]])");
	footprint += ptype->వెడల్పు * (tblend + 1);

	ఒకవేళ (tablesext) {
		yytbl_దత్తాంశం_compress (yynxt_tbl);
		ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, yynxt_tbl) < 0)
			flexerror (_("Could not write yynxt_tbl"));
	}
	yytbl_దత్తాంశం_destroy (yynxt_tbl);
	yynxt_tbl = ఖాళీ;
	/* End generating yy_nxt */

	/* Begin generating yy_chk */
	ptype = optimize_pack(tblend + 1);
	బహిర్గతం_str ("m4_define([[M4_HOOK_CHK_TYPE]], [[%s]])", ptype->name);
	బహిర్గతం_dec ("m4_define([[M4_HOOK_CHK_SIZE]], [[%d]])", tblend + 1);
	outn ("m4_define([[M4_HOOK_CHK_BODY]], [[m4_dnl");
	
	yychk_tbl = సున్నా_జ్ఞాపకం_ఇవ్వు (1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	yytbl_దత్తాంశం_init (yychk_tbl, YYTD_ID_CHK);
	yychk_tbl->td_lolen = (flex_uint32_t) (tblend + 1);
	yychk_tbl->td_దత్తాంశం = yychk_దత్తాంశం =
	    సున్నా_జ్ఞాపకం_ఇవ్వు(yychk_tbl->td_lolen, పరిమాణం (flex_int32_t));

	కొరకు (i = 1; i <= tblend; ++i) {
		ఒకవేళ (chk[i] == 0)
			++nummt;

		mkdata (chk[i]);
		yychk_దత్తాంశం[i] = chk[i];
	}

	dataend (ఖాళీ);
	outn ("]])");
	footprint += ptype->వెడల్పు * (tblend + 1);

	ఒకవేళ (tablesext) {
		yytbl_దత్తాంశం_compress (yychk_tbl);
		ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, yychk_tbl) < 0)
			flexerror (_("Could not write yychk_tbl"));
	}
	yytbl_దత్తాంశం_destroy (yychk_tbl);
	yychk_tbl = ఖాళీ;
	/* End generating yy_chk */

	విడుదల(acc_array);
}


శూన్య visible_define (స్థిరరాశి అక్షరం *symname)
{
	బహిర్గతం_m4_define(symname, ఖాళీ);
	comment(symname);
	outc ('\n');
}

శూన్య visible_define_str (స్థిరరాశి అక్షరం *symname, స్థిరరాశి అక్షరం *val)
{
	అక్షరం buf[128];
	బహిర్గతం_m4_define(symname, val);
	snprintf(buf, పరిమాణం(buf), "%s = %s", symname, val);
	comment(buf);
	outc ('\n');
}

శూన్య visible_define_int (స్థిరరాశి అక్షరం *symname, స్థిరరాశి పూర్ణాంకం val)
{
	అక్షరం nbuf[24], buf[128];
	snprintf(nbuf, పరిమాణం(nbuf), "%d", val);
	బహిర్గతం_m4_define(symname, nbuf);
	snprintf(buf, పరిమాణం(buf), "%s = %d", symname, val);
	comment(buf);
	outc ('\n');
}

/* make_tables - generate transition tables
 */

శూన్య make_tables (శూన్య)
{
	అక్షరం buf[128];
	పూర్ణాంకం i;
	నిర్మాణం yytbl_దత్తాంశం *yynultrans_tbl = ఖాళీ;

	/* This is where we REALLY begin generating the tables. */

	ఒకవేళ (ctrl.fullspd) {
		genctbl ();
		ఒకవేళ (tablesext) {
			నిర్మాణం yytbl_దత్తాంశం *tbl;

			tbl = mkctbl ();
			yytbl_దత్తాంశం_compress (tbl);
			ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_దత్తాంశం_destroy (tbl);

			tbl = mkssltbl ();
			yytbl_దత్తాంశం_compress (tbl);
			ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ssltbl"));
			yytbl_దత్తాంశం_destroy (tbl);
			tbl = 0;

			ఒకవేళ (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_దత్తాంశం_compress (tbl);
				ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_దత్తాంశం_destroy (tbl);
				tbl = 0;
			}
		}
	}
	లేకపోతే ఒకవేళ (ctrl.fulltbl) {
		genftbl ();
		ఒకవేళ (tablesext) {
			నిర్మాణం yytbl_దత్తాంశం *tbl;

			/* Alternately defined if !ctrl.ffullspd && !ctrl.fulltbl */
			నిర్మాణం packtype_t *ptype;
			tbl = mkftbl ();
			yytbl_దత్తాంశం_compress (tbl);
			ptype = optimize_pack(tbl->td_lolen);
			బహిర్గతం_str ("m4_define([[M4_HOOK_ACCEPT_TYPE]], [[%s]])", ptype->name);
			ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write ftbl"));
			yytbl_దత్తాంశం_destroy (tbl);
			tbl = 0;

			ఒకవేళ (ctrl.useecs) {
				tbl = mkecstbl ();
				yytbl_దత్తాంశం_compress (tbl);
				ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, tbl) < 0)
					flexerror (_
						   ("Could not write ecstbl"));
				yytbl_దత్తాంశం_destroy (tbl);
				tbl = 0;
			}
		}
	}
	లేకపోతే {
		gentabs ();
	}

	snprintf(buf, పరిమాణం(buf), "footprint: %ld bytes\n", footprint);
	comment(buf);
	snprintf(buf, పరిమాణం(buf), "tblend: %d\n", tblend);
	comment(buf);
	snprintf(buf, పరిమాణం(buf), "numecs: %d\n", numecs);
	comment(buf);
	snprintf(buf, పరిమాణం(buf), "num_rules: %d\n", అంకె_నియమాలు);
	comment(buf);
	snprintf(buf, పరిమాణం(buf), "lastdfa: %d\n", lastdfa);
	comment(buf);
	outc ('\n');
	
	// Only at this point do we know if the automaton has backups.
	// Some m4 conditionals require this information.

	comment("m4 controls begin\n");

	ఒకవేళ (అంకె_backing_పైకి > 0)
		visible_define ( "M4_MODE_HAS_BACKING_UP");

	// These are used for NUL transitions
	ఒకవేళ ((అంకె_backing_పైకి > 0 && !reject) && (!nultrans || ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NEED_YY_CP");
	ఒకవేళ ((అంకె_backing_పైకి > 0 && !reject) && (ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NULTRANS_WRAP");

	comment("m4 controls end\n");
	బహిర్గతం ("\n");

	ఒకవేళ (ctrl.do_yylineno) {

		geneoltbl ();

		ఒకవేళ (tablesext) {
			నిర్మాణం yytbl_దత్తాంశం *tbl;

			tbl = mkeoltbl ();
			yytbl_దత్తాంశం_compress (tbl);
			ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, tbl) < 0)
				flexerror (_("Could not write eoltbl"));
			yytbl_దత్తాంశం_destroy (tbl);
			tbl = 0;
		}
	}

	ఒకవేళ (nultrans) {
		flex_int32_t *yynultrans_దత్తాంశం = 0;

		/* Begin generating yy_NUL_trans */
		బహిర్గతం_str ("m4_define([[M4_HOOK_NULTRANS_TYPE]], [[%s]])", (ctrl.fullspd) ? "struct yy_trans_info*" : "M4_HOOK_INT32");
		బహిర్గతం_dec ("m4_define([[M4_HOOK_NULTRANS_SIZE]], [[%d]])", lastdfa + 1);
		outn ("m4_define([[M4_HOOK_NULTRANS_BODY]], [[m4_dnl");

		yynultrans_tbl = సున్నా_జ్ఞాపకం_ఇవ్వు(1, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
		yytbl_దత్తాంశం_init (yynultrans_tbl, YYTD_ID_NUL_TRANS);
		// Performance kludge for C. Gives a small improvement
		// in table loading time.
		ఒకవేళ (ctrl.fullspd && ctrl.have_state_నమోదు_format)
			yynultrans_tbl->td_flags |= YYTD_PTRANS;
		yynultrans_tbl->td_lolen = (flex_uint32_t) (lastdfa + 1);
		yynultrans_tbl->td_దత్తాంశం = yynultrans_దత్తాంశం =
		    సున్నా_జ్ఞాపకం_ఇవ్వు(yynultrans_tbl->td_lolen,
			   పరిమాణం (flex_int32_t));

		కొరకు (i = 1; i <= lastdfa; ++i) {
			ఒకవేళ ((yynultrans_tbl->td_flags & YYTD_PTRANS) != 0) {
				// Only works in very C-like languages  
				బహిర్గతం_dec ("    &yy_transition[%d],\n",
					 పునాది[i]);
				yynultrans_దత్తాంశం[i] = పునాది[i];
			}
			లేకపోతే {
				// This will work anywhere
				mkdata (nultrans[i]);
				yynultrans_దత్తాంశం[i] = nultrans[i];
			}
		}

		dataend (ఖాళీ);
		outn("]])");
		footprint += (lastdfa + 1) * (ctrl.fullspd ? పరిమాణం(నిర్మాణం yy_trans_info *) : పరిమాణం(int32_t));
		ఒకవేళ (tablesext) {
			yytbl_దత్తాంశం_compress (yynultrans_tbl);
			ఒకవేళ (yytbl_దత్తాంశం_fwrite (&tableswr, yynultrans_tbl) <
			    0)
				flexerror (_
					   ("Could not write yynultrans_tbl"));
		}

		ఒకవేళ (yynultrans_tbl != ఖాళీ) {
			yytbl_దత్తాంశం_destroy (yynultrans_tbl);
			yynultrans_tbl = ఖాళీ;
		}

		/* End generating yy_NUL_trans */
	}

	ఒకవేళ (ctrl.ddebug) {		/* Spit out table mapping rules to line numbers. */
		/* Policy choice: we don't include this space
		 * in the table metering.
		 */
		నిర్మాణం packtype_t *ptype = optimize_pack(అంకె_నియమాలు);
		బహిర్గతం_str ("m4_define([[M4_HOOK_DEBUGTABLE_TYPE]], [[%s]])", ptype->name);
		బహిర్గతం_dec ("m4_define([[M4_HOOK_DEBUGTABLE_SIZE]], [[%d]])", అంకె_నియమాలు);
		outn ("m4_define([[M4_HOOK_DEBUGTABLE_BODY]], [[m4_dnl");

		కొరకు (i = 1; i < అంకె_నియమాలు; ++i)
			mkdata (నియమం_linenum[i]);
		dataend (ఖాళీ);
		outn("]])");
	}
}
