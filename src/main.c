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


#شامل "flexdef.h"
#شامل "version.h"
#شامل "options.h"
#شامل "tables.h"
#شامل "parse.h"

ساکن حرف flex_نسخہ[] = FLEX_نسخہ;

/* declare functions that have forward references */

خالی flexinit(صحیح, حرف **);
خالی readin(خالی);
خالی سیٹ_اوپر_initial_allocations(خالی);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
صحیح     yymore_مستعمل, reject, real_reject, continued_action, اندر_قاعدہ;
صحیح     datapos, dataline, linenum;
FILE   *skelfile = تہی;
صحیح     skel_ind = 0;
حرف   *action_array;
صحیح     action_سائز, defs1_انحراف, prolog_انحراف, action_انحراف,
	action_اشاریہ;
حرف   *infilename = تہی;
حرف   *extra_type = تہی;
صحیح     onestate[ONE_ڈھیر_سائز], onesym[ONE_ڈھیر_سائز];
صحیح     onenext[ONE_ڈھیر_سائز], onedef[ONE_ڈھیر_سائز], onesp;
صحیح     زیادہ_سے_زیادہ_mns, current_mns, current_max_قواعد;
صحیح     عدد_قواعد, عدد_eof_قواعد, default_قاعدہ, lastnfa;
صحیح    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
صحیح    *accptnum, *assoc_قاعدہ, *state_type;
صحیح    *قاعدہ_type, *قاعدہ_linenum;
صحیح     current_state_type;
bool    variable_trailing_context_قواعد;
صحیح     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
صحیح     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_سائز];
صحیح     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
صحیح     tecbck[CSIZE + 1];
صحیح     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
حرف   *scxclu, *sceof;
صحیح     current_max_scs;
ثابت حرف **scname;
صحیح     current_max_dfa_سائز, current_max_xpairs;
صحیح     current_max_template_xpairs, current_max_dfas;
صحیح     lastdfa, *nxt, *chk, *tnxt;
صحیح    *بنیاد, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
اتحاد dfaacc_union *dfaacc;
صحیح    *accsiz, *dhash, numas;
صحیح     numsnpairs, jambase, jamstate;
صحیح     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
صحیح     current_maxccls, current_max_ccl_tbl_سائز;
غیرعلامتی حرف   *ccltbl;
حرف    nmstr[MAXLINE];
صحیح     sectnum, nummt, hshcol, dfaeql, numeps, eps2, عدد_reallocs, nmval;
صحیح     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
صحیح     عدد_backing_اوپر, bol_needed;
صحیح     انتہا_کا_بفر_state;
حرف  **داخلہ_files;
صحیح     عدد_داخلہ_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
حرف   *قاعدہ_useful, *قاعدہ_has_nl, *ccl_has_nl;
صحیح     nlch = '\n';

bool    tablesext, tablesverify, gentables;
حرف   *tablesfilename=0,*tablesname=0;
ساخت yytbl_writer tableswr;
size_t footprint;

ساخت ctrl_bundle_t ctrl;
ساخت env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
حرف   *پروگرام_name = "flex";

ساکن ثابت حرف outfile_template[] = "lex.%s.%s";
ساکن ثابت حرف *backing_name = "lex.backup";
ساکن ثابت حرف tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
خارجی FILE* yyout;

ساکن حرف outfile_راستہ[MAXLINE];
ساکن صحیح outfile_created = 0;
ساکن صحیح _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
ثابت حرف *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
ثابت حرف *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
ساکن صحیح preproc_level = 1000;

صحیح flex_main (صحیح argc, حرف *argv[]);

صحیح flex_main (صحیح argc, حرف *argv[])
{
	صحیح     i, exit_حالت, بچہ_حالت;
	صحیح	did_eof_قاعدہ = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_حالت = setjmp (flex_main_jmp_buf);
	اگر (exit_حالت){
		اگر (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		جب (wait(&بچہ_حالت) > 0){
			اگر (!WIFEXITED (بچہ_حالت)
			    || WEXITSTATUS (بچہ_حالت) != 0){
				/* report an error of a child
				 */
				اگر( exit_حالت <= 1 )
					exit_حالت = 2;

			}
		}
		واپس exit_حالت - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	برائے (i = 1; i <= عدد_قواعد; ++i)
		اگر (!قاعدہ_useful[i] && i != default_قاعدہ)
			سطر_warning (_("rule cannot be matched"),
				      قاعدہ_linenum[i]);

	اگر (ctrl.spprdflt && !reject && قاعدہ_useful[default_قاعدہ])
		سطر_warning (_
			      ("-s option given but default rule can be matched"),
			      قاعدہ_linenum[default_قاعدہ]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	اگر (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	ورنہ {
		visible_define ( "M4_MODE_NO_NULTRANS");
		اگر (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		ورنہ
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		اگر (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		ورنہ
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	برآمد ("\n");

	comment("START of Flex-generated definitions\n");
	برآمد_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", عدد_قواعد);
	برآمد_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", عدد_قواعد + 1);
	برآمد_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_JAMBASE", jambase);
	برآمد_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_JAMSTATE", jamstate);
	برآمد_str_dec ("M4_HOOK_CONST_DEFINE_BYTE(%s, %d)", "YY_NUL_EC", NUL_ec);
	/* Need to define the transet type as a size large
	 * enough to hold the biggest offset.
	 */
	برآمد_str ("M4_HOOK_SET_OFFSET_TYPE(%s)", optimize_pack(tblend + numecs + 1)->name);
	comment("END of Flex-generated definitions\n");

	skelout (true);		/* %% [2.0] - tables get dumped here */

	/* Generate the C state transition tables from the DFA. */
	make_tables ();

	skelout (true);		/* %% [3.0] - mode-dependent static declarations get dumped here */

	برآمد (&action_array[defs1_انحراف]);

	سطر_directive_برآمد (stdout, تہی, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	برآمد (&action_array[prolog_انحراف]);

	سطر_directive_برآمد (stdout, تہی, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	برآمد (&action_array[action_انحراف]);

	سطر_directive_برآمد (stdout, تہی, linenum);

	/* generate cases for any missing EOF rules */
	برائے (i = 1; i <= lastsc; ++i)
		اگر (!sceof[i]) {
			برآمد_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			برآمد ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_قاعدہ = true;
		}

	اگر (did_eof_قاعدہ) {
		برآمد ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	سطر_directive_برآمد (stdout, infilename, linenum);

	اگر (sectnum == 3) {
		برآمد_BEGIN_رمز ();
                اگر (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(خالی) flexscan ();	/* copy remainder of input to output */
                اگر (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		برآمد_انتہا_رمز ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	واپس 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
صحیح مین (صحیح argc, حرف *argv[])
{
#اگر defined(ENABLE_NLS) && ENABLE_NLS
#اگر HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#اگر_ختم
#اگر_ختم

	واپس flex_main (argc, argv);
}

/* Set up the output filter chain. */

خالی initialize_output_filters(خالی)
{
	ثابت حرف * m4 = تہی;

	output_chain = filter_create_int(تہی, filter_tee_سرخی, env.headerfilename);
	اگر ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (حرف *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, تہی);

	/* For debugging, only run the requested number of filters. */
	اگر (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

خالی check_options (خالی)
{
	صحیح     i;

	اگر (ctrl.lex_compat) {
		اگر (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		اگر (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		اگر (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#اگر 0
	/* This makes no sense whatsoever. I'm removing it. */
	اگر (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_مستعمل = true;
#اگر_ختم

	اگر (ctrl.csize == trit_unspecified) {
		اگر ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		ورنہ
			ctrl.csize = CSIZE;
	}

	اگر (ctrl.interactive == trit_unspecified) {
		اگر (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		ورنہ
			ctrl.interactive = trit_true;
	}

	اگر (ctrl.fulltbl || ctrl.fullspd) {
		اگر (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		اگر (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		اگر (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		اگر (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	اگر (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	اگر (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	اگر (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	اگر (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	اگر (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		برائے (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	ورنہ {
		/* Put everything in its own equivalence class. */
		برائے (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	اگر (!env.use_stdout) {
		FILE   *پچھلا_stdout;

		اگر (!env.did_outfilename) {
			snprintf (outfile_راستہ, حجم(outfile_راستہ), outfile_template,
				  ctrl.سابقہ, suffix());

			env.outfilename = outfile_راستہ;
		}

		پچھلا_stdout = freopen (env.outfilename, "w+", stdout);

		اگر (پچھلا_stdout == تہی)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

خالی flexend (صحیح exit_حالت)
{
	ساکن صحیح called_before = -1;	/* prevent infinite recursion. */
	صحیح     tblsiz;

	اگر (++called_before)
		FLEX_EXIT (exit_حالت);

	اگر (ctrl.yyclass != تہی && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	اگر (skelfile != تہی) {
		اگر (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		ورنہ اگر (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	اگر (exit_حالت != 0 && outfile_created) {
		اگر (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		ورنہ اگر ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		ورنہ اگر (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	اگر (env.backing_اوپر_report && ctrl.backing_اوپر_file) {
		اگر (عدد_backing_اوپر == 0)
			fprintf (ctrl.backing_اوپر_file, _("No backing up.\n"));
		ورنہ اگر (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_اوپر_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 عدد_backing_اوپر);
		ورنہ
			fprintf (ctrl.backing_اوپر_file,
				 _("Compressed tables always back up.\n"));

		اگر (ferror (ctrl.backing_اوپر_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		ورنہ اگر (fclose (ctrl.backing_اوپر_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	اگر (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 پروگرام_name, flex_نسخہ);

		fprintf (stderr, _("  scanner options: -"));

		اگر (ctrl.C_plus_plus)
			putc ('+', stderr);
		اگر (env.backing_اوپر_report)
			putc ('b', stderr);
		اگر (ctrl.ddebug)
			putc ('d', stderr);
		اگر (sf_case_ins())
			putc ('i', stderr);
		اگر (ctrl.lex_compat)
			putc ('l', stderr);
		اگر (ctrl.posix_compat)
			putc ('X', stderr);
		اگر (env.performance_hint > 0)
			putc ('p', stderr);
		اگر (env.performance_hint > 1)
			putc ('p', stderr);
		اگر (ctrl.spprdflt)
			putc ('s', stderr);
		اگر (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        اگر (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        اگر (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		اگر (env.use_stdout)
			putc ('t', stderr);
		اگر (env.printstats)
			putc ('v', stderr);	/* always true! */
		اگر (env.nowarn)
			putc ('w', stderr);
		اگر (ctrl.interactive == trit_false)
			putc ('B', stderr);
		اگر (ctrl.interactive == trit_true)
			putc ('I', stderr);
		اگر (!ctrl.gen_سطر_dirs)
			putc ('L', stderr);
		اگر (env.trace)
			putc ('T', stderr);

		اگر (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		اگر (ctrl.csize == 128)
			putc ('7', stderr);
		ورنہ
			putc ('8', stderr);

		fprintf (stderr, " -C");

		اگر (ctrl.long_align)
			putc ('a', stderr);
		اگر (ctrl.fulltbl)
			putc ('f', stderr);
		اگر (ctrl.fullspd)
			putc ('F', stderr);
		اگر (ctrl.useecs)
			putc ('e', stderr);
		اگر (ctrl.usemecs)
			putc ('m', stderr);
		اگر (ctrl.use_read)
			putc ('r', stderr);

		اگر (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		اگر (env.skelname != تہی)
			fprintf (stderr, " -S%s", env.skelname);

		اگر (strcmp (ctrl.سابقہ, "yy"))
			fprintf (stderr, " -P%s", ctrl.سابقہ);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 عدد_قواعد + عدد_eof_قواعد -
			 1 /* - 1 for def. rule */ );

		اگر (عدد_backing_اوپر == 0)
			fprintf (stderr, _("  No backing up\n"));
		ورنہ اگر (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 عدد_backing_اوپر);
		ورنہ
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		اگر (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		اگر (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		ورنہ
			fprintf (stderr,
				 _
				 ("  %d/%d character classes needed %d/%d words of storage, %d reused\n"),
				 lastccl, current_maxccls,
				 cclmap[lastccl] + ccllen[lastccl],
				 current_max_ccl_tbl_سائز, cclreuse);

		fprintf (stderr, _("  %d state/nextstate pairs created\n"),
			 numsnpairs);
		fprintf (stderr,
			 _("  %d/%d unique/duplicate transitions\n"),
			 numuniq, numdup);

		اگر (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		ورنہ {
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

		اگر (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		اگر (ctrl.usemecs) {
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
			 عدد_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_حالت);
}


/* flexinit - initialize flex */

خالی flexinit (صحیح argc, حرف **argv)
{
	صحیح     i, sawcmpflag, rv, optind;
	حرف   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', حجم(ctrl));
	syntaxerror = false;
	yymore_مستعمل = continued_action = false;
	اندر_قاعدہ = reject = false;
	ctrl.yymore_really_مستعمل = ctrl.reject_really_مستعمل = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_سطر_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.سابقہ = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = تہی;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_سائز = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_سائز);
	defs1_انحراف = prolog_انحراف = action_انحراف = action_اشاریہ = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, حجم (حرف));	/* one long string */
	buf_init (&چوٹی_buf, حجم (حرف));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	پروگرام_name = argv[0];

	اگر (پروگرام_name != تہی &&
	    پروگرام_name[لڑی_لمبائی (پروگرام_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	اگر (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	جب ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		اگر (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 پروگرام_name);
			FLEX_EXIT (1);
		}

		انتخاب ((شمار flexopt_flag_t) rv) {
		    حالت OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			توڑو;

		    حالت OPT_BATCH:
			ctrl.interactive = trit_false;
			توڑو;

		    حالت OPT_BACKUP:
			env.backing_اوپر_report = trit_true;
			توڑو;

		    حالت OPT_BACKUP_FILE:
			env.backing_اوپر_report = true;
                        backing_name = arg;
			توڑو;

		    حالت OPT_DONOTHING:
			توڑو;

		    حالت OPT_COMPRESSION:
			اگر (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			برائے (i = 0; arg && arg[i] != '\0'; i++)
				انتخاب (arg[i]) {
				    حالت 'a':
					ctrl.long_align = true;
					توڑو;

				    حالت 'e':
					ctrl.useecs = true;
					توڑو;

				    حالت 'F':
					ctrl.fullspd = true;
					توڑو;

				    حالت 'f':
					ctrl.fulltbl = true;
					توڑو;

				    حالت 'm':
					ctrl.usemecs = true;
					توڑو;

				    حالت 'r':
					ctrl.use_read = true;
					توڑو;

				    طےشدہ:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					توڑو;
				}
			توڑو;

		    حالت OPT_DEBUG:
			ctrl.ddebug = true;
			توڑو;

		    حالت OPT_NO_DEBUG:
			ctrl.ddebug = false;
			توڑو;

		    حالت OPT_بھرا:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			توڑو;

		    حالت OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			توڑو;

		    حالت OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    حالت OPT_INTERACTIVE:
			ctrl.interactive = true;
			توڑو;

		    حالت OPT_CASE_INSENSITIVE:
			sf_سیٹ_case_ins(true);
			توڑو;

		    حالت OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			توڑو;

		    حالت OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			توڑو;

		    حالت OPT_PREPROC_LEVEL:
			preproc_level = (صحیح) strtol(arg,تہی,0);
			توڑو;

		    حالت OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			توڑو;

		    حالت OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			توڑو;

		    حالت OPT_NO_سطر:
			ctrl.gen_سطر_dirs = false;
			توڑو;

		    حالت OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			توڑو;

		    حالت OPT_سابقہ:
			ctrl.سابقہ = arg;
			توڑو;

		    حالت OPT_PERF_REPORT:
			++env.performance_hint;
			توڑو;

		    حالت OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			توڑو;

		    حالت OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			توڑو;

		    حالت OPT_REENTRANT:
			ctrl.reentrant = true;
			توڑو;

		    حالت OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			توڑو;

		    حالت OPT_SKEL:
			env.skelname = arg;
			توڑو;

		    حالت OPT_DEFAULT:
			ctrl.spprdflt = false;
			توڑو;

		    حالت OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			توڑو;

		    حالت OPT_STDOUT:
			env.use_stdout = true;
			توڑو;

		    حالت OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			توڑو;

		    حالت OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			توڑو;

		    حالت OPT_TABLES_VERIFY:
			tablesverify = true;
			توڑو;

		    حالت OPT_TRACE:
			env.trace = true;
			توڑو;

		    حالت OPT_VERBOSE:
			env.printstats = true;
			توڑو;

		    حالت OPT_نسخہ:
			لکھو ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_نسخہ);
			FLEX_EXIT (0);

		    حالت OPT_WARN:
			env.nowarn = false;
			توڑو;

		    حالت OPT_NO_WARN:
			env.nowarn = true;
			توڑو;

		    حالت OPT_7_ثنائی_ہندسہ:
			ctrl.csize = 128;
			توڑو;

		    حالت OPT_8_ثنائی_ہندسہ:
			ctrl.csize = CSIZE;
			توڑو;

		    حالت OPT_ALIGN:
			ctrl.long_align = true;
			توڑو;

		    حالت OPT_NO_ALIGN:
			ctrl.long_align = false;
			توڑو;

		    حالت OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			توڑو;

		    حالت OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			توڑو;

		    حالت OPT_ARRAY:
			ctrl.yytext_is_array = true;
			توڑو;

		    حالت OPT_اشارہ_گر:
			ctrl.yytext_is_array = false;
			توڑو;

		    حالت OPT_ECS:
			ctrl.useecs = true;
			توڑو;

		    حالت OPT_NO_ECS:
			ctrl.useecs = false;
			توڑو;

		    حالت OPT_EMIT:
			ctrl.emit = arg;
			توڑو;

		    حالت OPT_سرخی_FILE:
			env.headerfilename = arg;
			توڑو;

		    حالت OPT_META_ECS:
			ctrl.usemecs = true;
			توڑو;

		    حالت OPT_NO_META_ECS:
			ctrl.usemecs = false;
			توڑو;

		    حالت OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    حرف   *def;
			    حرف buf2[4096];

			    برائے (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    جاری;
			    اگر (*def == '\0')
				    def = "1";

			    snprintf(buf2, حجم(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    توڑو;

		    حالت OPT_READ:
			ctrl.use_read = true;
			توڑو;

		    حالت OPT_ڈھیر:
			ctrl.ڈھیر_مستعمل = true;
			توڑو;

		    حالت OPT_STDINIT:
			ctrl.do_stdinit = true;
			توڑو;

		    حالت OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			توڑو;

		    حالت OPT_YYCLASS:
			ctrl.yyclass = arg;
			توڑو;

		    حالت OPT_YYLINENO:
			ctrl.do_yylineno = true;
			توڑو;

		    حالت OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			توڑو;

		    حالت OPT_YYWRAP:
			ctrl.do_yywrap = true;
			توڑو;

		    حالت OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			توڑو;

		    حالت OPT_YYMORE:
			ctrl.yymore_really_مستعمل = true;
			توڑو;

		    حالت OPT_NO_YYMORE:
			ctrl.yymore_really_مستعمل = false;
			توڑو;

		    حالت OPT_REJECT:
			ctrl.reject_really_مستعمل = true;
			توڑو;

		    حالت OPT_NO_REJECT:
			ctrl.reject_really_مستعمل = false;
			توڑو;

		    حالت OPT_NO_YY_ڈالو_STATE:
			ctrl.no_yy_ڈالو_state = true;
			توڑو;
		    حالت OPT_NO_YY_نکالو_STATE:
			ctrl.no_yy_نکالو_state = true;
			توڑو;
		    حالت OPT_NO_YY_چوٹی_STATE:
			ctrl.no_yy_چوٹی_state = true;
			توڑو;
		    حالت OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			توڑو;
		    حالت OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			توڑو;
		    حالت OPT_NO_YY_جائزہ_بفر:
			ctrl.no_yy_جائزہ_بفر = true;
			توڑو;
		    حالت OPT_NO_YY_جائزہ_بائٹیں:
			ctrl.no_yy_جائزہ_بائٹیں = true;
			توڑو;
		    حالت OPT_NO_YY_جائزہ_STRING:
			ctrl.no_yy_جائزہ_string = true;
			توڑو;
		    حالت OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			توڑو;
		    حالت OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			توڑو;
		    حالت OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			توڑو;
		    حالت OPT_NO_YYGET_متن:
			ctrl.no_yyget_متن = true;
			توڑو;
		    حالت OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			توڑو;
		    حالت OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			توڑو;
		    حالت OPT_NO_YYGET_عمود:
			ctrl.no_yyget_عمود = true;
			توڑو;
		    حالت OPT_NO_YYSET_عمود:
			ctrl.no_yyset_عمود = true;
			توڑو;
		    حالت OPT_NO_YYGET_اندر:
			ctrl.no_yyget_اندر = true;
			توڑو;
		    حالت OPT_NO_YYSET_اندر:
			ctrl.no_yyset_اندر = true;
			توڑو;
		    حالت OPT_NO_YYGET_برآمد:
			ctrl.no_yyget_برآمد = true;
			توڑو;
		    حالت OPT_NO_YYSET_برآمد:
			ctrl.no_yyset_برآمد = true;
			توڑو;
		    حالت OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			توڑو;
		    حالت OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			توڑو;
		    حالت OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			توڑو;
		    حالت OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			توڑو;
		    حالت OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			توڑو;
		    حالت OPT_NO_YYSET_DEBUG:
			ctrl.no_سیٹ_debug = true;
			توڑو;

		    حالت OPT_HEX:
			env.trace_hex = true;
                        توڑو;
		    حالت OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        توڑو;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	عدد_داخلہ_files = argc - optind;
	داخلہ_files = argv + optind;
	سیٹ_داخلہ_file (عدد_داخلہ_files > 0 ? داخلہ_files[0] : تہی);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	عدد_قواعد = عدد_eof_قواعد = default_قاعدہ = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = عدد_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	عدد_backing_اوپر = onesp = numprots = 0;
	variable_trailing_context_قواعد = bol_needed = false;

	linenum = sectnum = 1;
	firstprot = NIL;

	/* Used in mkprot() so that the first proto goes in slot 1
	 * of the proto queue.
	 */
	lastprot = 1;

	سیٹ_اوپر_initial_allocations ();
}


/* readin - read in the rules section of the input file(s) */

خالی readin (خالی)
{
	حرف buf[256];

	سطر_directive_برآمد(تہی, infilename, linenum);

	اگر (yyparse ()) {
		pinpoint_پیغام (_("fatal parse error"));
		flexend (1);
	}

	اگر (syntaxerror)
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

	اگر (tablesext)
		gentables = false;

	اگر (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	اگر (tablesext) {
		FILE   *tablesout;
		ساخت yytbl_hdr hdr;
		حرف   *pname = 0;
		size_t  nbytes = 0;

		اگر (!tablesfilename) {
			nbytes = لڑی_لمبائی (ctrl.سابقہ) + لڑی_لمبائی (tablesfile_template) + 2;
			tablesfilename = pname = صفر_حافظہ_دو(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.سابقہ);
		}

		اگر ((tablesout = fopen (tablesfilename, "w")) == تہی)
			lerr (_("could not create %s"), tablesfilename);
		آزاد(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = لڑی_لمبائی (ctrl.سابقہ) + لڑی_لمبائی ("tables") + 2;
		tablesname = صفر_حافظہ_دو(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.سابقہ);
		yytbl_hdr_init (&hdr, flex_نسخہ, tablesname);

		اگر (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	اگر (env.skelname && (skelfile = fopen (env.skelname, "r")) == تہی)
		lerr (_("can't open skeleton file %s"), env.skelname);

	اگر (strchr(ctrl.سابقہ, '[') || strchr(ctrl.سابقہ, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	اگر (env.did_outfilename)
		سطر_directive_برآمد (stdout, تہی, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	اگر( چوٹی_buf.elts)
		outn((حرف*) چوٹی_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	سطر_directive_برآمد(تہی, تہی, 0);

	/* User may want to set the scanner prototype */
	اگر (ctrl.yydecl != تہی) {
		برآمد_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	اگر (ctrl.userinit != تہی) {
		برآمد_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	اگر (ctrl.preaction != تہی) {
		برآمد_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	اگر (ctrl.postaction != تہی) {
		برآمد_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	برآمد_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	اگر (userdef_buf.elts)
		outn ((حرف *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	اگر (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	اگر (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	اگر (env.backing_اوپر_report) {
		ctrl.backing_اوپر_file = fopen (backing_name, "w");
		اگر (ctrl.backing_اوپر_file == تہی)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	ورنہ
		ctrl.backing_اوپر_file = تہی;

	اگر (ctrl.yymore_really_مستعمل == true)
		yymore_مستعمل = true;
	ورنہ اگر (ctrl.yymore_really_مستعمل == false)
		yymore_مستعمل = false;

	اگر (ctrl.reject_really_مستعمل == true)
		reject = true;
	ورنہ اگر (ctrl.reject_really_مستعمل == false)
		reject = false;

	اگر (env.performance_hint > 0) {
		اگر (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		ورنہ اگر (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		اگر (env.performance_hint > 1) {
			اگر (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			اگر (yymore_مستعمل)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		اگر (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		اگر (variable_trailing_context_قواعد)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	اگر (reject)
		real_reject = true;

	اگر (variable_trailing_context_قواعد)
		reject = true;

	اگر ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		اگر (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		ورنہ اگر (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		ورنہ
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	اگر (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	ورنہ
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	اگر (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, حجم(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		ساخت Buf tmpbuf;
		صحیح i;
		buf_init(&tmpbuf, حجم(حرف));
		برائے (i = 1; i <= lastsc; i++) {
			حرف *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = لڑی_لمبائی(fmt) + لڑی_لمبائی(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = حافظہ_دو(strsz);
			اگر (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			آزاد(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		برآمد_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	اگر (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	اگر (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	اگر (extra_type != تہی)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	اگر (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		اگر (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	اگر (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	ورنہ اگر (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	اگر (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	ورنہ
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	اگر (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	ورنہ
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	اگر (yymore_مستعمل)
		visible_define ( "M4_MODE_YYMORE_USED");
	ورنہ
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	اگر (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	ورنہ
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	اگر (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	ورنہ
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	اگر (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	ورنہ
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	اگر (variable_trailing_context_قواعد) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} ورنہ {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	اگر (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	اگر (ctrl.reject_really_مستعمل)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	اگر (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	ورنہ
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	اگر (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	اگر (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	ورنہ اگر (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	ورنہ اگر (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	ورنہ
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	اگر (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	اگر (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	ورنہ
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	اگر (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	اگر (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	ورنہ
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	اگر (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	ورنہ
		visible_define ( "M4_MODE_NO_GENTABLES");
	اگر (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	ورنہ
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	اگر (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	اگر (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	اگر (ctrl.yyclass != تہی) {
		visible_define ( "M4_MODE_YYCLASS");
		برآمد_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	اگر (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	اگر (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	اگر (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	ورنہ
		visible_define ( "M4_MODE_NO_YYWRAP");

	اگر (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	اگر (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	اگر (is_default_backend()) {
		اگر (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} ورنہ {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	اگر (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	اگر (ctrl.سابقہ != تہی)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.سابقہ);

	اگر (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	اگر (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	اگر (ctrl.yyterminate != تہی)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	اگر (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	اگر (ctrl.no_yy_ڈالو_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	اگر (ctrl.no_yy_نکالو_state)
		visible_define("M4_YY_NO_POP_STATE");
	اگر (ctrl.no_yy_چوٹی_state)
		visible_define("M4_YY_NO_TOP_STATE");
	اگر (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	اگر (ctrl.no_yy_جائزہ_بفر)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	اگر (ctrl.no_yy_جائزہ_بائٹیں)
		visible_define("M4_YY_NO_SCAN_BYTES");
	اگر (ctrl.no_yy_جائزہ_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	اگر (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	اگر (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	اگر (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	اگر (ctrl.no_yyget_متن)
		visible_define("M4_YY_NO_GET_TEXT");
	اگر (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	اگر (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	اگر (ctrl.no_yyget_عمود)
		visible_define("M4_YY_NO_GET_COLUMN");
	اگر (ctrl.no_yyset_عمود)
		visible_define("M4_YY_NO_SET_COLUMN");
	اگر (ctrl.no_yyget_اندر)
		visible_define("M4_YY_NO_GET_IN");
	اگر (ctrl.no_yyset_اندر)
		visible_define("M4_YY_NO_SET_IN");
	اگر (ctrl.no_yyget_برآمد)
		visible_define("M4_YY_NO_GET_OUT");
	اگر (ctrl.no_yyset_برآمد)
		visible_define("M4_YY_NO_SET_OUT");
	اگر (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	اگر (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	اگر (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	اگر (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	اگر (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	اگر (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	اگر (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	اگر (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	اگر (ctrl.no_سیٹ_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	اگر (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	اگر (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	اگر (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	اگر (ctrl.ڈھیر_مستعمل)
		visible_define("M4_YY_STACK_USED");

	اگر (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	ورنہ
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	برآمد ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

خالی سیٹ_اوپر_initial_allocations (خالی)
{
	زیادہ_سے_زیادہ_mns = (ctrl.long_align ? زیادہ_سے_زیادہ_MNS_LONG : زیادہ_سے_زیادہ_MNS);
	current_mns = INITIAL_MNS;
	firstst = allocate_integer_array (current_mns);
	lastst = allocate_integer_array (current_mns);
	finalst = allocate_integer_array (current_mns);
	transchar = allocate_integer_array (current_mns);
	trans1 = allocate_integer_array (current_mns);
	trans2 = allocate_integer_array (current_mns);
	accptnum = allocate_integer_array (current_mns);
	assoc_قاعدہ = allocate_integer_array (current_mns);
	state_type = allocate_integer_array (current_mns);

	current_max_قواعد = INITIAL_MAX_قواعد;
	قاعدہ_type = allocate_integer_array (current_max_قواعد);
	قاعدہ_linenum = allocate_integer_array (current_max_قواعد);
	قاعدہ_useful = allocate_array(current_max_قواعد, حجم(حرف));
	قاعدہ_has_nl = allocate_array(current_max_قواعد, حجم(حرف));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, حجم(حرف));
	sceof = allocate_array(current_max_scs, حجم(حرف));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, حجم(حرف));

	current_max_ccl_tbl_سائز = INITIAL_MAX_CCL_TBL_سائز;
	ccltbl = allocate_Character_array (current_max_ccl_tbl_سائز);

	current_max_dfa_سائز = INITIAL_MAX_DFA_سائز;

	current_max_xpairs = INITIAL_MAX_XPAIRS;
	nxt = allocate_integer_array (current_max_xpairs);
	chk = allocate_integer_array (current_max_xpairs);

	current_max_template_xpairs = INITIAL_MAX_TEMPLATE_XPAIRS;
	tnxt = allocate_integer_array (current_max_template_xpairs);

	current_max_dfas = INITIAL_MAX_DFAS;
	بنیاد = allocate_integer_array (current_max_dfas);
	def = allocate_integer_array (current_max_dfas);
	dfasiz = allocate_integer_array (current_max_dfas);
	accsiz = allocate_integer_array (current_max_dfas);
	dhash = allocate_integer_array (current_max_dfas);
	dss = allocate_int_ptr_array (current_max_dfas);
	dfaacc = allocate_array(current_max_dfas,
		حجم(اتحاد dfaacc_union));

	nultrans = تہی;
}


خالی usage (خالی)
{
	FILE   *f = stdout;

	اگر (!env.did_outfilename) {
		snprintf (outfile_راستہ, حجم(outfile_راستہ), outfile_template,
			  ctrl.سابقہ, suffix());
		env.outfilename = outfile_راستہ;
	}

	fprintf (f, _("Usage: %s [OPTIONS] [FILE]...\n"), پروگرام_name);
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
		 backing_name, "flex", outfile_راستہ, "flex");

}
