/* flex - tool to generate fast lexical analyzers */

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
#అన్తర్భావ "version.h"
#అన్తర్భావ "options.h"
#అన్తర్భావ "tables.h"
#అన్తర్భావ "parse.h"

స్థిర అక్షరం flex_సంస్కరణ[] = FLEX_సంస్కరణ;

/* declare functions that have forward references */

శూన్య flexinit(పూర్ణాంకం, అక్షరం **);
శూన్య readin(శూన్య);
శూన్య సమితి_పైకి_initial_allocations(శూన్య);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
పూర్ణాంకం     yymore_వాడిన, reject, real_reject, continued_action, లోపల_నియమం;
పూర్ణాంకం     datapos, dataline, linenum;
FILE   *skelfile = ఖాళీ;
పూర్ణాంకం     skel_ind = 0;
అక్షరం   *action_array;
పూర్ణాంకం     action_కొలత, defs1_స్థానభ్రంశం, prolog_స్థానభ్రంశం, action_స్థానభ్రంశం,
	action_సూచీ;
అక్షరం   *infilename = ఖాళీ;
అక్షరం   *extra_type = ఖాళీ;
పూర్ణాంకం     onestate[ONE_దొంతర_కొలత], onesym[ONE_దొంతర_కొలత];
పూర్ణాంకం     onenext[ONE_దొంతర_కొలత], onedef[ONE_దొంతర_కొలత], onesp;
పూర్ణాంకం     గరిష్ఠ_mns, current_mns, current_max_నియమాలు;
పూర్ణాంకం     అంకె_నియమాలు, అంకె_eof_నియమాలు, default_నియమం, lastnfa;
పూర్ణాంకం    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
పూర్ణాంకం    *accptnum, *assoc_నియమం, *state_type;
పూర్ణాంకం    *నియమం_type, *నియమం_linenum;
పూర్ణాంకం     current_state_type;
bool    variable_trailing_context_నియమాలు;
పూర్ణాంకం     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
పూర్ణాంకం     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_కొలత];
పూర్ణాంకం     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
పూర్ణాంకం     tecbck[CSIZE + 1];
పూర్ణాంకం     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
అక్షరం   *scxclu, *sceof;
పూర్ణాంకం     current_max_scs;
స్థిరరాశి అక్షరం **scname;
పూర్ణాంకం     current_max_dfa_కొలత, current_max_xpairs;
పూర్ణాంకం     current_max_template_xpairs, current_max_dfas;
పూర్ణాంకం     lastdfa, *nxt, *chk, *tnxt;
పూర్ణాంకం    *పునాది, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
సంఘం dfaacc_union *dfaacc;
పూర్ణాంకం    *accsiz, *dhash, numas;
పూర్ణాంకం     numsnpairs, jambase, jamstate;
పూర్ణాంకం     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
పూర్ణాంకం     current_maxccls, current_max_ccl_tbl_కొలత;
గుర్తులేని అక్షరం   *ccltbl;
అక్షరం    nmstr[MAXLINE];
పూర్ణాంకం     sectnum, nummt, hshcol, dfaeql, numeps, eps2, అంకె_reallocs, nmval;
పూర్ణాంకం     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
పూర్ణాంకం     అంకె_backing_పైకి, bol_needed;
పూర్ణాంకం     చివర_యొక్క_బఫరు_state;
అక్షరం  **ఆదానం_files;
పూర్ణాంకం     అంకె_ఆదానం_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
అక్షరం   *నియమం_useful, *నియమం_has_nl, *ccl_has_nl;
పూర్ణాంకం     nlch = '\n';

bool    tablesext, tablesverify, gentables;
అక్షరం   *tablesfilename=0,*tablesname=0;
నిర్మాణం yytbl_writer tableswr;
size_t footprint;

నిర్మాణం ctrl_bundle_t ctrl;
నిర్మాణం env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
అక్షరం   *కార్యక్రమం_name = "flex";

స్థిర స్థిరరాశి అక్షరం outfile_template[] = "lex.%s.%s";
స్థిర స్థిరరాశి అక్షరం *backing_name = "lex.backup";
స్థిర స్థిరరాశి అక్షరం tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
బాహ్య FILE* yyout;

స్థిర అక్షరం outfile_మార్గం[MAXLINE];
స్థిర పూర్ణాంకం outfile_created = 0;
స్థిర పూర్ణాంకం _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
స్థిరరాశి అక్షరం *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
స్థిరరాశి అక్షరం *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
స్థిర పూర్ణాంకం preproc_level = 1000;

పూర్ణాంకం flex_main (పూర్ణాంకం argc, అక్షరం *argv[]);

పూర్ణాంకం flex_main (పూర్ణాంకం argc, అక్షరం *argv[])
{
	పూర్ణాంకం     i, exit_స్థితి, బిడ్డ_స్థితి;
	పూర్ణాంకం	did_eof_నియమం = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_స్థితి = setjmp (flex_main_jmp_buf);
	ఒకవేళ (exit_స్థితి){
		ఒకవేళ (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		అయితే (wait(&బిడ్డ_స్థితి) > 0){
			ఒకవేళ (!WIFEXITED (బిడ్డ_స్థితి)
			    || WEXITSTATUS (బిడ్డ_స్థితి) != 0){
				/* report an error of a child
				 */
				ఒకవేళ( exit_స్థితి <= 1 )
					exit_స్థితి = 2;

			}
		}
		తిరిగి exit_స్థితి - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	కొరకు (i = 1; i <= అంకె_నియమాలు; ++i)
		ఒకవేళ (!నియమం_useful[i] && i != default_నియమం)
			పంక్తి_warning (_("rule cannot be matched"),
				      నియమం_linenum[i]);

	ఒకవేళ (ctrl.spprdflt && !reject && నియమం_useful[default_నియమం])
		పంక్తి_warning (_
			      ("-s option given but default rule can be matched"),
			      నియమం_linenum[default_నియమం]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	ఒకవేళ (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	లేకపోతే {
		visible_define ( "M4_MODE_NO_NULTRANS");
		ఒకవేళ (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		లేకపోతే
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		ఒకవేళ (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		లేకపోతే
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	బహిర్గతం ("\n");

	comment("START of Flex-generated definitions\n");
	బహిర్గతం_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", అంకె_నియమాలు);
	బహిర్గతం_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", అంకె_నియమాలు + 1);
	బహిర్గతం_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_JAMBASE", jambase);
	బహిర్గతం_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_JAMSTATE", jamstate);
	బహిర్గతం_str_dec ("M4_HOOK_CONST_DEFINE_BYTE(%s, %d)", "YY_NUL_EC", NUL_ec);
	/* Need to define the transet type as a size large
	 * enough to hold the biggest offset.
	 */
	బహిర్గతం_str ("M4_HOOK_SET_OFFSET_TYPE(%s)", optimize_pack(tblend + numecs + 1)->name);
	comment("END of Flex-generated definitions\n");

	skelout (true);		/* %% [2.0] - tables get dumped here */

	/* Generate the C state transition tables from the DFA. */
	make_tables ();

	skelout (true);		/* %% [3.0] - mode-dependent static declarations get dumped here */

	బహిర్గతం (&action_array[defs1_స్థానభ్రంశం]);

	పంక్తి_directive_బహిర్గతం (stdout, ఖాళీ, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	బహిర్గతం (&action_array[prolog_స్థానభ్రంశం]);

	పంక్తి_directive_బహిర్గతం (stdout, ఖాళీ, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	బహిర్గతం (&action_array[action_స్థానభ్రంశం]);

	పంక్తి_directive_బహిర్గతం (stdout, ఖాళీ, linenum);

	/* generate cases for any missing EOF rules */
	కొరకు (i = 1; i <= lastsc; ++i)
		ఒకవేళ (!sceof[i]) {
			బహిర్గతం_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			బహిర్గతం ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_నియమం = true;
		}

	ఒకవేళ (did_eof_నియమం) {
		బహిర్గతం ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	పంక్తి_directive_బహిర్గతం (stdout, infilename, linenum);

	ఒకవేళ (sectnum == 3) {
		బహిర్గతం_BEGIN_సంకేతం ();
                ఒకవేళ (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(శూన్య) flexscan ();	/* copy remainder of input to output */
                ఒకవేళ (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		బహిర్గతం_చివర_సంకేతం ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	తిరిగి 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
పూర్ణాంకం ప్రధాన (పూర్ణాంకం argc, అక్షరం *argv[])
{
#ఒకవేళ defined(ENABLE_NLS) && ENABLE_NLS
#ఒకవేళ HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#అయితే_ముగింపు
#అయితే_ముగింపు

	తిరిగి flex_main (argc, argv);
}

/* Set up the output filter chain. */

శూన్య initialize_output_filters(శూన్య)
{
	స్థిరరాశి అక్షరం * m4 = ఖాళీ;

	output_chain = filter_create_int(ఖాళీ, filter_tee_శీర్షిక, env.headerfilename);
	ఒకవేళ ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (అక్షరం *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, ఖాళీ);

	/* For debugging, only run the requested number of filters. */
	ఒకవేళ (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

శూన్య check_options (శూన్య)
{
	పూర్ణాంకం     i;

	ఒకవేళ (ctrl.lex_compat) {
		ఒకవేళ (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		ఒకవేళ (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		ఒకవేళ (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#ఒకవేళ 0
	/* This makes no sense whatsoever. I'm removing it. */
	ఒకవేళ (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_వాడిన = true;
#అయితే_ముగింపు

	ఒకవేళ (ctrl.csize == trit_unspecified) {
		ఒకవేళ ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		లేకపోతే
			ctrl.csize = CSIZE;
	}

	ఒకవేళ (ctrl.interactive == trit_unspecified) {
		ఒకవేళ (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		లేకపోతే
			ctrl.interactive = trit_true;
	}

	ఒకవేళ (ctrl.fulltbl || ctrl.fullspd) {
		ఒకవేళ (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		ఒకవేళ (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		ఒకవేళ (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		ఒకవేళ (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	ఒకవేళ (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	ఒకవేళ (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	ఒకవేళ (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	ఒకవేళ (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	ఒకవేళ (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		కొరకు (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	లేకపోతే {
		/* Put everything in its own equivalence class. */
		కొరకు (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	ఒకవేళ (!env.use_stdout) {
		FILE   *prev_stdout;

		ఒకవేళ (!env.did_outfilename) {
			snprintf (outfile_మార్గం, పరిమాణం(outfile_మార్గం), outfile_template,
				  ctrl.ఉపసర్గ, suffix());

			env.outfilename = outfile_మార్గం;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		ఒకవేళ (prev_stdout == ఖాళీ)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

శూన్య flexend (పూర్ణాంకం exit_స్థితి)
{
	స్థిర పూర్ణాంకం called_before = -1;	/* prevent infinite recursion. */
	పూర్ణాంకం     tblsiz;

	ఒకవేళ (++called_before)
		FLEX_EXIT (exit_స్థితి);

	ఒకవేళ (ctrl.yyclass != ఖాళీ && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	ఒకవేళ (skelfile != ఖాళీ) {
		ఒకవేళ (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		లేకపోతే ఒకవేళ (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	ఒకవేళ (exit_స్థితి != 0 && outfile_created) {
		ఒకవేళ (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		లేకపోతే ఒకవేళ ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		లేకపోతే ఒకవేళ (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	ఒకవేళ (env.backing_పైకి_report && ctrl.backing_పైకి_file) {
		ఒకవేళ (అంకె_backing_పైకి == 0)
			fprintf (ctrl.backing_పైకి_file, _("No backing up.\n"));
		లేకపోతే ఒకవేళ (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_పైకి_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 అంకె_backing_పైకి);
		లేకపోతే
			fprintf (ctrl.backing_పైకి_file,
				 _("Compressed tables always back up.\n"));

		ఒకవేళ (ferror (ctrl.backing_పైకి_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		లేకపోతే ఒకవేళ (fclose (ctrl.backing_పైకి_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	ఒకవేళ (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 కార్యక్రమం_name, flex_సంస్కరణ);

		fprintf (stderr, _("  scanner options: -"));

		ఒకవేళ (ctrl.C_plus_plus)
			putc ('+', stderr);
		ఒకవేళ (env.backing_పైకి_report)
			putc ('b', stderr);
		ఒకవేళ (ctrl.ddebug)
			putc ('d', stderr);
		ఒకవేళ (sf_case_ins())
			putc ('i', stderr);
		ఒకవేళ (ctrl.lex_compat)
			putc ('l', stderr);
		ఒకవేళ (ctrl.posix_compat)
			putc ('X', stderr);
		ఒకవేళ (env.performance_hint > 0)
			putc ('p', stderr);
		ఒకవేళ (env.performance_hint > 1)
			putc ('p', stderr);
		ఒకవేళ (ctrl.spprdflt)
			putc ('s', stderr);
		ఒకవేళ (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        ఒకవేళ (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        ఒకవేళ (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		ఒకవేళ (env.use_stdout)
			putc ('t', stderr);
		ఒకవేళ (env.printstats)
			putc ('v', stderr);	/* always true! */
		ఒకవేళ (env.nowarn)
			putc ('w', stderr);
		ఒకవేళ (ctrl.interactive == trit_false)
			putc ('B', stderr);
		ఒకవేళ (ctrl.interactive == trit_true)
			putc ('I', stderr);
		ఒకవేళ (!ctrl.gen_పంక్తి_dirs)
			putc ('L', stderr);
		ఒకవేళ (env.trace)
			putc ('T', stderr);

		ఒకవేళ (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		ఒకవేళ (ctrl.csize == 128)
			putc ('7', stderr);
		లేకపోతే
			putc ('8', stderr);

		fprintf (stderr, " -C");

		ఒకవేళ (ctrl.long_align)
			putc ('a', stderr);
		ఒకవేళ (ctrl.fulltbl)
			putc ('f', stderr);
		ఒకవేళ (ctrl.fullspd)
			putc ('F', stderr);
		ఒకవేళ (ctrl.useecs)
			putc ('e', stderr);
		ఒకవేళ (ctrl.usemecs)
			putc ('m', stderr);
		ఒకవేళ (ctrl.use_read)
			putc ('r', stderr);

		ఒకవేళ (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		ఒకవేళ (env.skelname != ఖాళీ)
			fprintf (stderr, " -S%s", env.skelname);

		ఒకవేళ (strcmp (ctrl.ఉపసర్గ, "yy"))
			fprintf (stderr, " -P%s", ctrl.ఉపసర్గ);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 అంకె_నియమాలు + అంకె_eof_నియమాలు -
			 1 /* - 1 for def. rule */ );

		ఒకవేళ (అంకె_backing_పైకి == 0)
			fprintf (stderr, _("  No backing up\n"));
		లేకపోతే ఒకవేళ (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 అంకె_backing_పైకి);
		లేకపోతే
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		ఒకవేళ (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		ఒకవేళ (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		లేకపోతే
			fprintf (stderr,
				 _
				 ("  %d/%d character classes needed %d/%d words of storage, %d reused\n"),
				 lastccl, current_maxccls,
				 cclmap[lastccl] + ccllen[lastccl],
				 current_max_ccl_tbl_కొలత, cclreuse);

		fprintf (stderr, _("  %d state/nextstate pairs created\n"),
			 numsnpairs);
		fprintf (stderr,
			 _("  %d/%d unique/duplicate transitions\n"),
			 numuniq, numdup);

		ఒకవేళ (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		లేకపోతే {
			tblsiz = 2 * (lastdfa + numtemps) + 2 * tblend;

			fprintf (stderr,
				 _("  %d/%d base-def entries created\n"),
				 lastdfa + numtemps, current_max_dfas);
			fprintf (stderr,
				 _
				 ("  %d/%d (peak %d) nxt-chk entries created\n"),
				 tblend, current_max_xpairs, peakpairs);
			fprintf (stderr,
				 _
				 ("  %d/%d (peak %d) template nxt-chk entries created\n"),
				 numtemps * nummecs,
				 current_max_template_xpairs,
				 numtemps * numecs);
			fprintf (stderr, _("  %d empty table entries\n"),
				 nummt);
			fprintf (stderr, _("  %d protos created\n"),
				 numprots);
			fprintf (stderr,
				 _("  %d templates created, %d uses\n"),
				 numtemps, tmpuses);
		}

		ఒకవేళ (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		ఒకవేళ (ctrl.usemecs) {
			tblsiz = tblsiz + numecs;
			fprintf (stderr,
				 _
				 ("  %d/%d meta-equivalence classes created\n"),
				 nummecs, ctrl.csize);
		}

		fprintf (stderr,
			 _
			 ("  %d (%d saved) hash collisions, %d DFAs equal\n"),
			 hshcol, hshsave, dfaeql);
		fprintf (stderr, _("  %d sets of reallocations needed\n"),
			 అంకె_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_స్థితి);
}


/* flexinit - initialize flex */

శూన్య flexinit (పూర్ణాంకం argc, అక్షరం **argv)
{
	పూర్ణాంకం     i, sawcmpflag, rv, optind;
	అక్షరం   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', పరిమాణం(ctrl));
	syntaxerror = false;
	yymore_వాడిన = continued_action = false;
	లోపల_నియమం = reject = false;
	ctrl.yymore_really_వాడిన = ctrl.reject_really_వాడిన = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_పంక్తి_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.ఉపసర్గ = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = ఖాళీ;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_కొలత = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_కొలత);
	defs1_స్థానభ్రంశం = prolog_స్థానభ్రంశం = action_స్థానభ్రంశం = action_సూచీ = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, పరిమాణం (అక్షరం));	/* one long string */
	buf_init (&శిఖరం_buf, పరిమాణం (అక్షరం));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	కార్యక్రమం_name = argv[0];

	ఒకవేళ (కార్యక్రమం_name != ఖాళీ &&
	    కార్యక్రమం_name[అక్షరశ్రేణి_పొడవు (కార్యక్రమం_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	ఒకవేళ (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	అయితే ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		ఒకవేళ (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 కార్యక్రమం_name);
			FLEX_EXIT (1);
		}

		ఎంపిక ((గణన flexopt_flag_t) rv) {
		    స్థితి OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			ఆపు;

		    స్థితి OPT_BATCH:
			ctrl.interactive = trit_false;
			ఆపు;

		    స్థితి OPT_BACKUP:
			env.backing_పైకి_report = trit_true;
			ఆపు;

		    స్థితి OPT_BACKUP_FILE:
			env.backing_పైకి_report = true;
                        backing_name = arg;
			ఆపు;

		    స్థితి OPT_DONOTHING:
			ఆపు;

		    స్థితి OPT_COMPRESSION:
			ఒకవేళ (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			కొరకు (i = 0; arg && arg[i] != '\0'; i++)
				ఎంపిక (arg[i]) {
				    స్థితి 'a':
					ctrl.long_align = true;
					ఆపు;

				    స్థితి 'e':
					ctrl.useecs = true;
					ఆపు;

				    స్థితి 'F':
					ctrl.fullspd = true;
					ఆపు;

				    స్థితి 'f':
					ctrl.fulltbl = true;
					ఆపు;

				    స్థితి 'm':
					ctrl.usemecs = true;
					ఆపు;

				    స్థితి 'r':
					ctrl.use_read = true;
					ఆపు;

				    అప్రమేయ:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					ఆపు;
				}
			ఆపు;

		    స్థితి OPT_DEBUG:
			ctrl.ddebug = true;
			ఆపు;

		    స్థితి OPT_NO_DEBUG:
			ctrl.ddebug = false;
			ఆపు;

		    స్థితి OPT_నిండిన:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			ఆపు;

		    స్థితి OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			ఆపు;

		    స్థితి OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    స్థితి OPT_INTERACTIVE:
			ctrl.interactive = true;
			ఆపు;

		    స్థితి OPT_CASE_INSENSITIVE:
			sf_సమితి_case_ins(true);
			ఆపు;

		    స్థితి OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			ఆపు;

		    స్థితి OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			ఆపు;

		    స్థితి OPT_PREPROC_LEVEL:
			preproc_level = (పూర్ణాంకం) strtol(arg,ఖాళీ,0);
			ఆపు;

		    స్థితి OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			ఆపు;

		    స్థితి OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			ఆపు;

		    స్థితి OPT_NO_పంక్తి:
			ctrl.gen_పంక్తి_dirs = false;
			ఆపు;

		    స్థితి OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			ఆపు;

		    స్థితి OPT_ఉపసర్గ:
			ctrl.ఉపసర్గ = arg;
			ఆపు;

		    స్థితి OPT_PERF_REPORT:
			++env.performance_hint;
			ఆపు;

		    స్థితి OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			ఆపు;

		    స్థితి OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			ఆపు;

		    స్థితి OPT_REENTRANT:
			ctrl.reentrant = true;
			ఆపు;

		    స్థితి OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			ఆపు;

		    స్థితి OPT_SKEL:
			env.skelname = arg;
			ఆపు;

		    స్థితి OPT_DEFAULT:
			ctrl.spprdflt = false;
			ఆపు;

		    స్థితి OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			ఆపు;

		    స్థితి OPT_STDOUT:
			env.use_stdout = true;
			ఆపు;

		    స్థితి OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			ఆపు;

		    స్థితి OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			ఆపు;

		    స్థితి OPT_TABLES_VERIFY:
			tablesverify = true;
			ఆపు;

		    స్థితి OPT_TRACE:
			env.trace = true;
			ఆపు;

		    స్థితి OPT_VERBOSE:
			env.printstats = true;
			ఆపు;

		    స్థితి OPT_సంస్కరణ:
			రాయి ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_సంస్కరణ);
			FLEX_EXIT (0);

		    స్థితి OPT_WARN:
			env.nowarn = false;
			ఆపు;

		    స్థితి OPT_NO_WARN:
			env.nowarn = true;
			ఆపు;

		    స్థితి OPT_7_బిట్టు:
			ctrl.csize = 128;
			ఆపు;

		    స్థితి OPT_8_బిట్టు:
			ctrl.csize = CSIZE;
			ఆపు;

		    స్థితి OPT_ALIGN:
			ctrl.long_align = true;
			ఆపు;

		    స్థితి OPT_NO_ALIGN:
			ctrl.long_align = false;
			ఆపు;

		    స్థితి OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			ఆపు;

		    స్థితి OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			ఆపు;

		    స్థితి OPT_ARRAY:
			ctrl.yytext_is_array = true;
			ఆపు;

		    స్థితి OPT_సూచిక:
			ctrl.yytext_is_array = false;
			ఆపు;

		    స్థితి OPT_ECS:
			ctrl.useecs = true;
			ఆపు;

		    స్థితి OPT_NO_ECS:
			ctrl.useecs = false;
			ఆపు;

		    స్థితి OPT_EMIT:
			ctrl.emit = arg;
			ఆపు;

		    స్థితి OPT_శీర్షిక_FILE:
			env.headerfilename = arg;
			ఆపు;

		    స్థితి OPT_META_ECS:
			ctrl.usemecs = true;
			ఆపు;

		    స్థితి OPT_NO_META_ECS:
			ctrl.usemecs = false;
			ఆపు;

		    స్థితి OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    అక్షరం   *def;
			    అక్షరం buf2[4096];

			    కొరకు (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    కొనసాగు;
			    ఒకవేళ (*def == '\0')
				    def = "1";

			    snprintf(buf2, పరిమాణం(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    ఆపు;

		    స్థితి OPT_READ:
			ctrl.use_read = true;
			ఆపు;

		    స్థితి OPT_దొంతర:
			ctrl.దొంతర_వాడిన = true;
			ఆపు;

		    స్థితి OPT_STDINIT:
			ctrl.do_stdinit = true;
			ఆపు;

		    స్థితి OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			ఆపు;

		    స్థితి OPT_YYCLASS:
			ctrl.yyclass = arg;
			ఆపు;

		    స్థితి OPT_YYLINENO:
			ctrl.do_yylineno = true;
			ఆపు;

		    స్థితి OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			ఆపు;

		    స్థితి OPT_YYWRAP:
			ctrl.do_yywrap = true;
			ఆపు;

		    స్థితి OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			ఆపు;

		    స్థితి OPT_YYMORE:
			ctrl.yymore_really_వాడిన = true;
			ఆపు;

		    స్థితి OPT_NO_YYMORE:
			ctrl.yymore_really_వాడిన = false;
			ఆపు;

		    స్థితి OPT_REJECT:
			ctrl.reject_really_వాడిన = true;
			ఆపు;

		    స్థితి OPT_NO_REJECT:
			ctrl.reject_really_వాడిన = false;
			ఆపు;

		    స్థితి OPT_NO_YY_నెట్టు_STATE:
			ctrl.no_yy_నెట్టు_state = true;
			ఆపు;
		    స్థితి OPT_NO_YY_తీయి_STATE:
			ctrl.no_yy_తీయి_state = true;
			ఆపు;
		    స్థితి OPT_NO_YY_శిఖరం_STATE:
			ctrl.no_yy_శిఖరం_state = true;
			ఆపు;
		    స్థితి OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			ఆపు;
		    స్థితి OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			ఆపు;
		    స్థితి OPT_NO_YY_పరిశీలన_బఫరు:
			ctrl.no_yy_పరిశీలన_బఫరు = true;
			ఆపు;
		    స్థితి OPT_NO_YY_పరిశీలన_బైట్లు:
			ctrl.no_yy_పరిశీలన_బైట్లు = true;
			ఆపు;
		    స్థితి OPT_NO_YY_పరిశీలన_STRING:
			ctrl.no_yy_పరిశీలన_string = true;
			ఆపు;
		    స్థితి OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			ఆపు;
		    స్థితి OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			ఆపు;
		    స్థితి OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			ఆపు;
		    స్థితి OPT_NO_YYGET_పాఠ్యం:
			ctrl.no_yyget_పాఠ్యం = true;
			ఆపు;
		    స్థితి OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			ఆపు;
		    స్థితి OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			ఆపు;
		    స్థితి OPT_NO_YYGET_స్తంభం:
			ctrl.no_yyget_స్తంభం = true;
			ఆపు;
		    స్థితి OPT_NO_YYSET_స్తంభం:
			ctrl.no_yyset_స్తంభం = true;
			ఆపు;
		    స్థితి OPT_NO_YYGET_లోపల:
			ctrl.no_yyget_లోపల = true;
			ఆపు;
		    స్థితి OPT_NO_YYSET_లోపల:
			ctrl.no_yyset_లోపల = true;
			ఆపు;
		    స్థితి OPT_NO_YYGET_బహిర్గతం:
			ctrl.no_yyget_బహిర్గతం = true;
			ఆపు;
		    స్థితి OPT_NO_YYSET_బహిర్గతం:
			ctrl.no_yyset_బహిర్గతం = true;
			ఆపు;
		    స్థితి OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			ఆపు;
		    స్థితి OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			ఆపు;
		    స్థితి OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			ఆపు;
		    స్థితి OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			ఆపు;
		    స్థితి OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			ఆపు;
		    స్థితి OPT_NO_YYSET_DEBUG:
			ctrl.no_సమితి_debug = true;
			ఆపు;

		    స్థితి OPT_HEX:
			env.trace_hex = true;
                        ఆపు;
		    స్థితి OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        ఆపు;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	అంకె_ఆదానం_files = argc - optind;
	ఆదానం_files = argv + optind;
	సమితి_ఆదానం_file (అంకె_ఆదానం_files > 0 ? ఆదానం_files[0] : ఖాళీ);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	అంకె_నియమాలు = అంకె_eof_నియమాలు = default_నియమం = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = అంకె_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	అంకె_backing_పైకి = onesp = numprots = 0;
	variable_trailing_context_నియమాలు = bol_needed = false;

	linenum = sectnum = 1;
	firstprot = NIL;

	/* Used in mkprot() so that the first proto goes in slot 1
	 * of the proto queue.
	 */
	lastprot = 1;

	సమితి_పైకి_initial_allocations ();
}


/* readin - read in the rules section of the input file(s) */

శూన్య readin (శూన్య)
{
	అక్షరం buf[256];

	పంక్తి_directive_బహిర్గతం(ఖాళీ, infilename, linenum);

	ఒకవేళ (yyparse ()) {
		pinpoint_సందేశం (_("fatal parse error"));
		flexend (1);
	}

	ఒకవేళ (syntaxerror)
		flexend (1);

	/* On --emit, -e, or change backends This is where backend
	 * properties are collected, which means they can't be set
	 * from a custom skelfile.  Note: might have been called sooner
	 * when %option emit was evaluated; this catches command-line
	 * optiins and the default case.
	 */
	backend_by_name(ctrl.emit);

	initialize_output_filters();

	yyout = stdout;

	ఒకవేళ (tablesext)
		gentables = false;

	ఒకవేళ (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	ఒకవేళ (tablesext) {
		FILE   *tablesout;
		నిర్మాణం yytbl_hdr hdr;
		అక్షరం   *pname = 0;
		size_t  nbytes = 0;

		ఒకవేళ (!tablesfilename) {
			nbytes = అక్షరశ్రేణి_పొడవు (ctrl.ఉపసర్గ) + అక్షరశ్రేణి_పొడవు (tablesfile_template) + 2;
			tablesfilename = pname = సున్నా_జ్ఞాపకం_ఇవ్వు(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.ఉపసర్గ);
		}

		ఒకవేళ ((tablesout = fopen (tablesfilename, "w")) == ఖాళీ)
			lerr (_("could not create %s"), tablesfilename);
		విడుదల(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = అక్షరశ్రేణి_పొడవు (ctrl.ఉపసర్గ) + అక్షరశ్రేణి_పొడవు ("tables") + 2;
		tablesname = సున్నా_జ్ఞాపకం_ఇవ్వు(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.ఉపసర్గ);
		yytbl_hdr_init (&hdr, flex_సంస్కరణ, tablesname);

		ఒకవేళ (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	ఒకవేళ (env.skelname && (skelfile = fopen (env.skelname, "r")) == ఖాళీ)
		lerr (_("can't open skeleton file %s"), env.skelname);

	ఒకవేళ (strchr(ctrl.ఉపసర్గ, '[') || strchr(ctrl.ఉపసర్గ, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	ఒకవేళ (env.did_outfilename)
		పంక్తి_directive_బహిర్గతం (stdout, ఖాళీ, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	ఒకవేళ( శిఖరం_buf.elts)
		outn((అక్షరం*) శిఖరం_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	పంక్తి_directive_బహిర్గతం(ఖాళీ, ఖాళీ, 0);

	/* User may want to set the scanner prototype */
	ఒకవేళ (ctrl.yydecl != ఖాళీ) {
		బహిర్గతం_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	ఒకవేళ (ctrl.userinit != ఖాళీ) {
		బహిర్గతం_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	ఒకవేళ (ctrl.preaction != ఖాళీ) {
		బహిర్గతం_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	ఒకవేళ (ctrl.postaction != ఖాళీ) {
		బహిర్గతం_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	బహిర్గతం_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	ఒకవేళ (userdef_buf.elts)
		outn ((అక్షరం *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	ఒకవేళ (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	ఒకవేళ (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	ఒకవేళ (env.backing_పైకి_report) {
		ctrl.backing_పైకి_file = fopen (backing_name, "w");
		ఒకవేళ (ctrl.backing_పైకి_file == ఖాళీ)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	లేకపోతే
		ctrl.backing_పైకి_file = ఖాళీ;

	ఒకవేళ (ctrl.yymore_really_వాడిన == true)
		yymore_వాడిన = true;
	లేకపోతే ఒకవేళ (ctrl.yymore_really_వాడిన == false)
		yymore_వాడిన = false;

	ఒకవేళ (ctrl.reject_really_వాడిన == true)
		reject = true;
	లేకపోతే ఒకవేళ (ctrl.reject_really_వాడిన == false)
		reject = false;

	ఒకవేళ (env.performance_hint > 0) {
		ఒకవేళ (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		లేకపోతే ఒకవేళ (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		ఒకవేళ (env.performance_hint > 1) {
			ఒకవేళ (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			ఒకవేళ (yymore_వాడిన)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		ఒకవేళ (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		ఒకవేళ (variable_trailing_context_నియమాలు)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	ఒకవేళ (reject)
		real_reject = true;

	ఒకవేళ (variable_trailing_context_నియమాలు)
		reject = true;

	ఒకవేళ ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		ఒకవేళ (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		లేకపోతే ఒకవేళ (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		లేకపోతే
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	ఒకవేళ (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	లేకపోతే
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	ఒకవేళ (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, పరిమాణం(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		నిర్మాణం Buf tmpbuf;
		పూర్ణాంకం i;
		buf_init(&tmpbuf, పరిమాణం(అక్షరం));
		కొరకు (i = 1; i <= lastsc; i++) {
			అక్షరం *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = అక్షరశ్రేణి_పొడవు(fmt) + అక్షరశ్రేణి_పొడవు(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = జ్ఞాపకం_ఇవ్వు(strsz);
			ఒకవేళ (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			విడుదల(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		బహిర్గతం_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	ఒకవేళ (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	ఒకవేళ (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	ఒకవేళ (extra_type != ఖాళీ)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	ఒకవేళ (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		ఒకవేళ (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	ఒకవేళ (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	లేకపోతే ఒకవేళ (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	ఒకవేళ (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	లేకపోతే
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	ఒకవేళ (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	లేకపోతే
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	ఒకవేళ (yymore_వాడిన)
		visible_define ( "M4_MODE_YYMORE_USED");
	లేకపోతే
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	ఒకవేళ (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	లేకపోతే
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	ఒకవేళ (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	లేకపోతే
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	ఒకవేళ (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	లేకపోతే
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	ఒకవేళ (variable_trailing_context_నియమాలు) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} లేకపోతే {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	ఒకవేళ (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	ఒకవేళ (ctrl.reject_really_వాడిన)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	ఒకవేళ (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	లేకపోతే
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	ఒకవేళ (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	ఒకవేళ (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	లేకపోతే ఒకవేళ (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	లేకపోతే ఒకవేళ (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	లేకపోతే
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	ఒకవేళ (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	ఒకవేళ (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	లేకపోతే
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	ఒకవేళ (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	ఒకవేళ (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	లేకపోతే
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	ఒకవేళ (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	లేకపోతే
		visible_define ( "M4_MODE_NO_GENTABLES");
	ఒకవేళ (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	లేకపోతే
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	ఒకవేళ (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	ఒకవేళ (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	ఒకవేళ (ctrl.yyclass != ఖాళీ) {
		visible_define ( "M4_MODE_YYCLASS");
		బహిర్గతం_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	ఒకవేళ (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	ఒకవేళ (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	ఒకవేళ (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	లేకపోతే
		visible_define ( "M4_MODE_NO_YYWRAP");

	ఒకవేళ (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	ఒకవేళ (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	ఒకవేళ (is_default_backend()) {
		ఒకవేళ (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} లేకపోతే {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	ఒకవేళ (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	ఒకవేళ (ctrl.ఉపసర్గ != ఖాళీ)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.ఉపసర్గ);

	ఒకవేళ (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	ఒకవేళ (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	ఒకవేళ (ctrl.yyterminate != ఖాళీ)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	ఒకవేళ (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	ఒకవేళ (ctrl.no_yy_నెట్టు_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	ఒకవేళ (ctrl.no_yy_తీయి_state)
		visible_define("M4_YY_NO_POP_STATE");
	ఒకవేళ (ctrl.no_yy_శిఖరం_state)
		visible_define("M4_YY_NO_TOP_STATE");
	ఒకవేళ (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	ఒకవేళ (ctrl.no_yy_పరిశీలన_బఫరు)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	ఒకవేళ (ctrl.no_yy_పరిశీలన_బైట్లు)
		visible_define("M4_YY_NO_SCAN_BYTES");
	ఒకవేళ (ctrl.no_yy_పరిశీలన_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	ఒకవేళ (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	ఒకవేళ (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	ఒకవేళ (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	ఒకవేళ (ctrl.no_yyget_పాఠ్యం)
		visible_define("M4_YY_NO_GET_TEXT");
	ఒకవేళ (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	ఒకవేళ (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	ఒకవేళ (ctrl.no_yyget_స్తంభం)
		visible_define("M4_YY_NO_GET_COLUMN");
	ఒకవేళ (ctrl.no_yyset_స్తంభం)
		visible_define("M4_YY_NO_SET_COLUMN");
	ఒకవేళ (ctrl.no_yyget_లోపల)
		visible_define("M4_YY_NO_GET_IN");
	ఒకవేళ (ctrl.no_yyset_లోపల)
		visible_define("M4_YY_NO_SET_IN");
	ఒకవేళ (ctrl.no_yyget_బహిర్గతం)
		visible_define("M4_YY_NO_GET_OUT");
	ఒకవేళ (ctrl.no_yyset_బహిర్గతం)
		visible_define("M4_YY_NO_SET_OUT");
	ఒకవేళ (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	ఒకవేళ (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	ఒకవేళ (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	ఒకవేళ (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	ఒకవేళ (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	ఒకవేళ (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	ఒకవేళ (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	ఒకవేళ (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	ఒకవేళ (ctrl.no_సమితి_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	ఒకవేళ (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	ఒకవేళ (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	ఒకవేళ (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	ఒకవేళ (ctrl.దొంతర_వాడిన)
		visible_define("M4_YY_STACK_USED");

	ఒకవేళ (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	లేకపోతే
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	బహిర్గతం ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

శూన్య సమితి_పైకి_initial_allocations (శూన్య)
{
	గరిష్ఠ_mns = (ctrl.long_align ? గరిష్ఠ_MNS_LONG : గరిష్ఠ_MNS);
	current_mns = INITIAL_MNS;
	firstst = allocate_integer_array (current_mns);
	lastst = allocate_integer_array (current_mns);
	finalst = allocate_integer_array (current_mns);
	transchar = allocate_integer_array (current_mns);
	trans1 = allocate_integer_array (current_mns);
	trans2 = allocate_integer_array (current_mns);
	accptnum = allocate_integer_array (current_mns);
	assoc_నియమం = allocate_integer_array (current_mns);
	state_type = allocate_integer_array (current_mns);

	current_max_నియమాలు = INITIAL_MAX_నియమాలు;
	నియమం_type = allocate_integer_array (current_max_నియమాలు);
	నియమం_linenum = allocate_integer_array (current_max_నియమాలు);
	నియమం_useful = allocate_array(current_max_నియమాలు, పరిమాణం(అక్షరం));
	నియమం_has_nl = allocate_array(current_max_నియమాలు, పరిమాణం(అక్షరం));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, పరిమాణం(అక్షరం));
	sceof = allocate_array(current_max_scs, పరిమాణం(అక్షరం));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, పరిమాణం(అక్షరం));

	current_max_ccl_tbl_కొలత = INITIAL_MAX_CCL_TBL_కొలత;
	ccltbl = allocate_Character_array (current_max_ccl_tbl_కొలత);

	current_max_dfa_కొలత = INITIAL_MAX_DFA_కొలత;

	current_max_xpairs = INITIAL_MAX_XPAIRS;
	nxt = allocate_integer_array (current_max_xpairs);
	chk = allocate_integer_array (current_max_xpairs);

	current_max_template_xpairs = INITIAL_MAX_TEMPLATE_XPAIRS;
	tnxt = allocate_integer_array (current_max_template_xpairs);

	current_max_dfas = INITIAL_MAX_DFAS;
	పునాది = allocate_integer_array (current_max_dfas);
	def = allocate_integer_array (current_max_dfas);
	dfasiz = allocate_integer_array (current_max_dfas);
	accsiz = allocate_integer_array (current_max_dfas);
	dhash = allocate_integer_array (current_max_dfas);
	dss = allocate_int_ptr_array (current_max_dfas);
	dfaacc = allocate_array(current_max_dfas,
		పరిమాణం(సంఘం dfaacc_union));

	nultrans = ఖాళీ;
}


శూన్య usage (శూన్య)
{
	FILE   *f = stdout;

	ఒకవేళ (!env.did_outfilename) {
		snprintf (outfile_మార్గం, పరిమాణం(outfile_మార్గం), outfile_template,
			  ctrl.ఉపసర్గ, suffix());
		env.outfilename = outfile_మార్గం;
	}

	fprintf (f, _("Usage: %s [OPTIONS] [FILE]...\n"), కార్యక్రమం_name);
	fprintf (f,
		 _
		 ("Generates programs that perform pattern-matching on text.\n"
		  "\n" "Table Compression:\n"
		  "  -Ca, --align      trade off larger tables for better memory alignment\n"
		  "  -Ce, --ecs        construct equivalence classes\n"
		  "  -Cf               do not compress tables; use -f representation\n"
		  "  -CF               do not compress tables; use -F representation\n"
		  "  -Cm, --meta-ecs   construct meta-equivalence classes\n"
		  "  -Cr, --read       use read() instead of stdio for scanner input\n"
		  "  -f, --full        generate fast, large scanner. Same as -Cfr\n"
		  "  -F, --fast        use alternate table representation. Same as -CFr\n"
		  "  -Cem              default compression (same as --ecs --meta-ecs)\n"
		  "\n" "Debugging:\n"
		  "  -d, --debug             enable debug mode in scanner\n"
		  "  -b, --backup            write backing-up information to %s\n"
		  "  -p, --perf-report       write performance report to stderr\n"
		  "  -s, --nodefault         suppress default rule to ECHO unmatched text\n"
		  "  -T, --env.trace             %s should run in env.trace mode\n"
		  "  -w, --nowarn            do not generate warnings\n"
		  "  -v, --verbose           write summary of scanner statistics to stdout\n"
		  "      --hex               use hexadecimal numbers instead of octal in debug outputs\n"
		  "\n" "Files:\n"
		  "  -o, --outfile=FILE      specify output filename\n"
		  "  -S, --skel=FILE         specify skeleton file\n"
		  "  -t, --stdout            write scanner on stdout instead of %s\n"
		  "      --yyclass=NAME      name of C++ class\n"
		  "      --header-file=FILE   create a C header file in addition to the scanner\n"
		  "      --tables-file[=FILE] write tables to FILE\n"
		  "      --backup-file=FILE  write backing-up information to FILE\n" "\n"
		  "Scanner behavior:\n"
		  "  -7, --7bit              generate 7-bit scanner\n"
		  "  -8, --8bit              generate 8-bit scanner\n"
		  "  -B, --batch             generate batch scanner (opposite of -I)\n"
		  "  -i, --case-insensitive  ignore case in patterns\n"
		  "  -l, --lex-compat        maximal compatibility with original lex\n"
		  "  -X, --posix-compat      maximal compatibility with POSIX lex\n"
		  "  -I, --interactive       generate interactive scanner (opposite of -B)\n"
		  "      --yylineno          track line count in yylineno\n"
		  "\n" "Generated code:\n"
		  "  -+,  --c++               generate C++ scanner class\n"
		  "  -Dmacro[=defn]           #define macro defn  (default defn is '1')\n"
		  "  -e,  --emit=LANG         Specify target language\n"
		  "  -L,  --noline            suppress #line directives in scanner\n"
		  "  -P,  --prefix=STRING     use STRING as prefix instead of \"yy\"\n"
		  "  -R,  --reentrant         generate a reentrant scanner\n"
		  "       --bison-bridge      scanner for Bison pure parser.\n"
		  "       --bison-locations   include yylloc support.\n"
		  "       --stdinit           initialize yyin/yyout to stdin/stdout\n"
		  "       --nounistd          do not include <unistd.h>\n"
		  "       --noFUNCTION        do not generate a particular FUNCTION\n"
		  "\n" "Miscellaneous:\n"
		  "  -c                      do-nothing POSIX option\n"
		  "  -n                      do-nothing POSIX option\n"
		  "  -?\n"
		  "  -h, --help              produce this help message\n"
		  "  -V, --version           report %s version\n"),
		 backing_name, "flex", outfile_మార్గం, "flex");

}
