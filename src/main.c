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


#অন্তর্ভাব "flexdef.h"
#অন্তর্ভাব "version.h"
#অন্তর্ভাব "options.h"
#অন্তর্ভাব "tables.h"
#অন্তর্ভাব "parse.h"

স্থির অক্ষর flex_version[] = FLEX_VERSION;

/* declare functions that have forward references */

শূন্য flexinit(পূর্ণসংখ্যা, অক্ষর **);
শূন্য readin(শূন্য);
শূন্য set_up_initial_allocations(শূন্য);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
পূর্ণসংখ্যা     yymore_used, reject, real_reject, continued_action, in_rule;
পূর্ণসংখ্যা     datapos, dataline, linenum;
FILE   *skelfile = ফাঁকা;
পূর্ণসংখ্যা     skel_ind = 0;
অক্ষর   *action_array;
পূর্ণসংখ্যা     action_আকার, defs1_offset, prolog_offset, action_offset,
	action_সূচক;
অক্ষর   *infilename = ফাঁকা;
অক্ষর   *extra_type = ফাঁকা;
পূর্ণসংখ্যা     onestate[ONE_স্তূপ_আকার], onesym[ONE_স্তূপ_আকার];
পূর্ণসংখ্যা     onenext[ONE_স্তূপ_আকার], onedef[ONE_স্তূপ_আকার], onesp;
পূর্ণসংখ্যা     maximum_mns, current_mns, current_max_rules;
পূর্ণসংখ্যা     অঙ্ক_rules, অঙ্ক_eof_rules, default_rule, lastnfa;
পূর্ণসংখ্যা    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
পূর্ণসংখ্যা    *accptnum, *assoc_rule, *state_type;
পূর্ণসংখ্যা    *rule_type, *rule_linenum;
পূর্ণসংখ্যা     current_state_type;
bool    variable_trailing_context_rules;
পূর্ণসংখ্যা     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
পূর্ণসংখ্যা     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_আকার];
পূর্ণসংখ্যা     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
পূর্ণসংখ্যা     tecbck[CSIZE + 1];
পূর্ণসংখ্যা     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
অক্ষর   *scxclu, *sceof;
পূর্ণসংখ্যা     current_max_scs;
ধ্রুবক অক্ষর **scname;
পূর্ণসংখ্যা     current_max_dfa_আকার, current_max_xpairs;
পূর্ণসংখ্যা     current_max_template_xpairs, current_max_dfas;
পূর্ণসংখ্যা     lastdfa, *nxt, *chk, *tnxt;
পূর্ণসংখ্যা    *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
সংঘ dfaacc_union *dfaacc;
পূর্ণসংখ্যা    *accsiz, *dhash, numas;
পূর্ণসংখ্যা     numsnpairs, jambase, jamstate;
পূর্ণসংখ্যা     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
পূর্ণসংখ্যা     current_maxccls, current_max_ccl_tbl_আকার;
unsigned অক্ষর   *ccltbl;
অক্ষর    nmstr[MAXLINE];
পূর্ণসংখ্যা     sectnum, nummt, hshcol, dfaeql, numeps, eps2, অঙ্ক_reallocs, nmval;
পূর্ণসংখ্যা     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
পূর্ণসংখ্যা     অঙ্ক_backing_up, bol_needed;
পূর্ণসংখ্যা     end_of_বাফার_state;
অক্ষর  **প্রবেশ_files;
পূর্ণসংখ্যা     অঙ্ক_প্রবেশ_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
অক্ষর   *rule_useful, *rule_has_nl, *ccl_has_nl;
পূর্ণসংখ্যা     nlch = '\n';

bool    tablesext, tablesverify, gentables;
অক্ষর   *tablesfilename=0,*tablesname=0;
কাঠামো yytbl_writer tableswr;
size_t footprint;

কাঠামো ctrl_bundle_t ctrl;
কাঠামো env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
অক্ষর   *program_name = "flex";

স্থির ধ্রুবক অক্ষর outfile_template[] = "lex.%s.%s";
স্থির ধ্রুবক অক্ষর *backing_name = "lex.backup";
স্থির ধ্রুবক অক্ষর tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
বাহ্যিক FILE* yyout;

স্থির অক্ষর outfile_path[MAXLINE];
স্থির পূর্ণসংখ্যা outfile_created = 0;
স্থির পূর্ণসংখ্যা _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
ধ্রুবক অক্ষর *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
ধ্রুবক অক্ষর *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
স্থির পূর্ণসংখ্যা preproc_level = 1000;

পূর্ণসংখ্যা flex_main (পূর্ণসংখ্যা argc, অক্ষর *argv[]);

পূর্ণসংখ্যা flex_main (পূর্ণসংখ্যা argc, অক্ষর *argv[])
{
	পূর্ণসংখ্যা     i, exit_status, child_status;
	পূর্ণসংখ্যা	did_eof_rule = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_status = setjmp (flex_main_jmp_buf);
	যদি (exit_status){
		যদি (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		যখন (wait(&child_status) > 0){
			যদি (!WIFEXITED (child_status)
			    || WEXITSTATUS (child_status) != 0){
				/* report an error of a child
				 */
				যদি( exit_status <= 1 )
					exit_status = 2;

			}
		}
		ফেরত exit_status - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	জন্য (i = 1; i <= অঙ্ক_rules; ++i)
		যদি (!rule_useful[i] && i != default_rule)
			সারি_warning (_("rule cannot be matched"),
				      rule_linenum[i]);

	যদি (ctrl.spprdflt && !reject && rule_useful[default_rule])
		সারি_warning (_
			      ("-s option given but default rule can be matched"),
			      rule_linenum[default_rule]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	যদি (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	অন্যথা {
		visible_define ( "M4_MODE_NO_NULTRANS");
		যদি (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		অন্যথা
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		যদি (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		অন্যথা
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	out ("\n");

	comment("START of Flex-generated definitions\n");
	out_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", অঙ্ক_rules);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", অঙ্ক_rules + 1);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_JAMBASE", jambase);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_JAMSTATE", jamstate);
	out_str_dec ("M4_HOOK_CONST_DEFINE_BYTE(%s, %d)", "YY_NUL_EC", NUL_ec);
	/* Need to define the transet type as a size large
	 * enough to hold the biggest offset.
	 */
	out_str ("M4_HOOK_SET_OFFSET_TYPE(%s)", optimize_pack(tblend + numecs + 1)->name);
	comment("END of Flex-generated definitions\n");

	skelout (true);		/* %% [2.0] - tables get dumped here */

	/* Generate the C state transition tables from the DFA. */
	make_tables ();

	skelout (true);		/* %% [3.0] - mode-dependent static declarations get dumped here */

	out (&action_array[defs1_offset]);

	সারি_directive_out (stdout, ফাঁকা, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	out (&action_array[prolog_offset]);

	সারি_directive_out (stdout, ফাঁকা, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	out (&action_array[action_offset]);

	সারি_directive_out (stdout, ফাঁকা, linenum);

	/* generate cases for any missing EOF rules */
	জন্য (i = 1; i <= lastsc; ++i)
		যদি (!sceof[i]) {
			out_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			out ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_rule = true;
		}

	যদি (did_eof_rule) {
		out ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	সারি_directive_out (stdout, infilename, linenum);

	যদি (sectnum == 3) {
		OUT_BEGIN_CODE ();
                যদি (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(শূন্য) flexscan ();	/* copy remainder of input to output */
                যদি (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		OUT_END_CODE ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	ফেরত 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
পূর্ণসংখ্যা প্রধান (পূর্ণসংখ্যা argc, অক্ষর *argv[])
{
#যদি defined(ENABLE_NLS) && ENABLE_NLS
#যদি HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif
#endif

	ফেরত flex_main (argc, argv);
}

/* Set up the output filter chain. */

শূন্য initialize_output_filters(শূন্য)
{
	ধ্রুবক অক্ষর * m4 = ফাঁকা;

	output_chain = filter_create_int(ফাঁকা, filter_tee_header, env.headerfilename);
	যদি ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (অক্ষর *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, ফাঁকা);

	/* For debugging, only run the requested number of filters. */
	যদি (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

শূন্য check_options (শূন্য)
{
	পূর্ণসংখ্যা     i;

	যদি (ctrl.lex_compat) {
		যদি (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		যদি (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		যদি (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#যদি 0
	/* This makes no sense whatsoever. I'm removing it. */
	যদি (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_used = true;
#endif

	যদি (ctrl.csize == trit_unspecified) {
		যদি ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		অন্যথা
			ctrl.csize = CSIZE;
	}

	যদি (ctrl.interactive == trit_unspecified) {
		যদি (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		অন্যথা
			ctrl.interactive = trit_true;
	}

	যদি (ctrl.fulltbl || ctrl.fullspd) {
		যদি (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		যদি (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		যদি (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		যদি (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	যদি (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	যদি (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	যদি (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	যদি (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	যদি (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		জন্য (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	অন্যথা {
		/* Put everything in its own equivalence class. */
		জন্য (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	যদি (!env.use_stdout) {
		FILE   *পূর্ব_stdout;

		যদি (!env.did_outfilename) {
			snprintf (outfile_path, আকার(outfile_path), outfile_template,
				  ctrl.prefix, suffix());

			env.outfilename = outfile_path;
		}

		পূর্ব_stdout = freopen (env.outfilename, "w+", stdout);

		যদি (পূর্ব_stdout == ফাঁকা)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

শূন্য flexend (পূর্ণসংখ্যা exit_status)
{
	স্থির পূর্ণসংখ্যা called_before = -1;	/* prevent infinite recursion. */
	পূর্ণসংখ্যা     tblsiz;

	যদি (++called_before)
		FLEX_EXIT (exit_status);

	যদি (ctrl.yyclass != ফাঁকা && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	যদি (skelfile != ফাঁকা) {
		যদি (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		অন্যথা যদি (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	যদি (exit_status != 0 && outfile_created) {
		যদি (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		অন্যথা যদি ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		অন্যথা যদি (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	যদি (env.backing_up_report && ctrl.backing_up_file) {
		যদি (অঙ্ক_backing_up == 0)
			fprintf (ctrl.backing_up_file, _("No backing up.\n"));
		অন্যথা যদি (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_up_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 অঙ্ক_backing_up);
		অন্যথা
			fprintf (ctrl.backing_up_file,
				 _("Compressed tables always back up.\n"));

		যদি (ferror (ctrl.backing_up_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		অন্যথা যদি (fclose (ctrl.backing_up_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	যদি (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 program_name, flex_version);

		fprintf (stderr, _("  scanner options: -"));

		যদি (ctrl.C_plus_plus)
			putc ('+', stderr);
		যদি (env.backing_up_report)
			putc ('b', stderr);
		যদি (ctrl.ddebug)
			putc ('d', stderr);
		যদি (sf_case_ins())
			putc ('i', stderr);
		যদি (ctrl.lex_compat)
			putc ('l', stderr);
		যদি (ctrl.posix_compat)
			putc ('X', stderr);
		যদি (env.performance_hint > 0)
			putc ('p', stderr);
		যদি (env.performance_hint > 1)
			putc ('p', stderr);
		যদি (ctrl.spprdflt)
			putc ('s', stderr);
		যদি (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        যদি (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        যদি (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		যদি (env.use_stdout)
			putc ('t', stderr);
		যদি (env.printstats)
			putc ('v', stderr);	/* always true! */
		যদি (env.nowarn)
			putc ('w', stderr);
		যদি (ctrl.interactive == trit_false)
			putc ('B', stderr);
		যদি (ctrl.interactive == trit_true)
			putc ('I', stderr);
		যদি (!ctrl.gen_সারি_dirs)
			putc ('L', stderr);
		যদি (env.trace)
			putc ('T', stderr);

		যদি (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		যদি (ctrl.csize == 128)
			putc ('7', stderr);
		অন্যথা
			putc ('8', stderr);

		fprintf (stderr, " -C");

		যদি (ctrl.long_align)
			putc ('a', stderr);
		যদি (ctrl.fulltbl)
			putc ('f', stderr);
		যদি (ctrl.fullspd)
			putc ('F', stderr);
		যদি (ctrl.useecs)
			putc ('e', stderr);
		যদি (ctrl.usemecs)
			putc ('m', stderr);
		যদি (ctrl.use_read)
			putc ('r', stderr);

		যদি (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		যদি (env.skelname != ফাঁকা)
			fprintf (stderr, " -S%s", env.skelname);

		যদি (strcmp (ctrl.prefix, "yy"))
			fprintf (stderr, " -P%s", ctrl.prefix);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 অঙ্ক_rules + অঙ্ক_eof_rules -
			 1 /* - 1 for def. rule */ );

		যদি (অঙ্ক_backing_up == 0)
			fprintf (stderr, _("  No backing up\n"));
		অন্যথা যদি (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 অঙ্ক_backing_up);
		অন্যথা
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		যদি (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		যদি (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		অন্যথা
			fprintf (stderr,
				 _
				 ("  %d/%d character classes needed %d/%d words of storage, %d reused\n"),
				 lastccl, current_maxccls,
				 cclmap[lastccl] + ccllen[lastccl],
				 current_max_ccl_tbl_আকার, cclreuse);

		fprintf (stderr, _("  %d state/nextstate pairs created\n"),
			 numsnpairs);
		fprintf (stderr,
			 _("  %d/%d unique/duplicate transitions\n"),
			 numuniq, numdup);

		যদি (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		অন্যথা {
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

		যদি (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		যদি (ctrl.usemecs) {
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
			 অঙ্ক_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_status);
}


/* flexinit - initialize flex */

শূন্য flexinit (পূর্ণসংখ্যা argc, অক্ষর **argv)
{
	পূর্ণসংখ্যা     i, sawcmpflag, rv, optind;
	অক্ষর   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', আকার(ctrl));
	syntaxerror = false;
	yymore_used = continued_action = false;
	in_rule = reject = false;
	ctrl.yymore_really_used = ctrl.reject_really_used = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_সারি_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.prefix = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = ফাঁকা;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_আকার = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_আকার);
	defs1_offset = prolog_offset = action_offset = action_সূচক = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, আকার (অক্ষর));	/* one long string */
	buf_init (&শীর্ষ_buf, আকার (অক্ষর));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	program_name = argv[0];

	যদি (program_name != ফাঁকা &&
	    program_name[strlen (program_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	যদি (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	যখন ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		যদি (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 program_name);
			FLEX_EXIT (1);
		}

		নির্বাচন ((গণনা flexopt_flag_t) rv) {
		    ক্ষেত্র OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			বিরতি;

		    ক্ষেত্র OPT_BATCH:
			ctrl.interactive = trit_false;
			বিরতি;

		    ক্ষেত্র OPT_BACKUP:
			env.backing_up_report = trit_true;
			বিরতি;

		    ক্ষেত্র OPT_BACKUP_FILE:
			env.backing_up_report = true;
                        backing_name = arg;
			বিরতি;

		    ক্ষেত্র OPT_DONOTHING:
			বিরতি;

		    ক্ষেত্র OPT_COMPRESSION:
			যদি (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			জন্য (i = 0; arg && arg[i] != '\0'; i++)
				নির্বাচন (arg[i]) {
				    ক্ষেত্র 'a':
					ctrl.long_align = true;
					বিরতি;

				    ক্ষেত্র 'e':
					ctrl.useecs = true;
					বিরতি;

				    ক্ষেত্র 'F':
					ctrl.fullspd = true;
					বিরতি;

				    ক্ষেত্র 'f':
					ctrl.fulltbl = true;
					বিরতি;

				    ক্ষেত্র 'm':
					ctrl.usemecs = true;
					বিরতি;

				    ক্ষেত্র 'r':
					ctrl.use_read = true;
					বিরতি;

				    পূর্বনির্ধারিত:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					বিরতি;
				}
			বিরতি;

		    ক্ষেত্র OPT_DEBUG:
			ctrl.ddebug = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_DEBUG:
			ctrl.ddebug = false;
			বিরতি;

		    ক্ষেত্র OPT_FULL:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			বিরতি;

		    ক্ষেত্র OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			বিরতি;

		    ক্ষেত্র OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    ক্ষেত্র OPT_INTERACTIVE:
			ctrl.interactive = true;
			বিরতি;

		    ক্ষেত্র OPT_CASE_INSENSITIVE:
			sf_set_case_ins(true);
			বিরতি;

		    ক্ষেত্র OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			বিরতি;

		    ক্ষেত্র OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			বিরতি;

		    ক্ষেত্র OPT_PREPROC_LEVEL:
			preproc_level = (পূর্ণসংখ্যা) strtol(arg,ফাঁকা,0);
			বিরতি;

		    ক্ষেত্র OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			বিরতি;

		    ক্ষেত্র OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			বিরতি;

		    ক্ষেত্র OPT_NO_সারি:
			ctrl.gen_সারি_dirs = false;
			বিরতি;

		    ক্ষেত্র OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			বিরতি;

		    ক্ষেত্র OPT_PREFIX:
			ctrl.prefix = arg;
			বিরতি;

		    ক্ষেত্র OPT_PERF_REPORT:
			++env.performance_hint;
			বিরতি;

		    ক্ষেত্র OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			বিরতি;

		    ক্ষেত্র OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			বিরতি;

		    ক্ষেত্র OPT_REENTRANT:
			ctrl.reentrant = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			বিরতি;

		    ক্ষেত্র OPT_SKEL:
			env.skelname = arg;
			বিরতি;

		    ক্ষেত্র OPT_DEFAULT:
			ctrl.spprdflt = false;
			বিরতি;

		    ক্ষেত্র OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			বিরতি;

		    ক্ষেত্র OPT_STDOUT:
			env.use_stdout = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			বিরতি;

		    ক্ষেত্র OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			বিরতি;

		    ক্ষেত্র OPT_TABLES_VERIFY:
			tablesverify = true;
			বিরতি;

		    ক্ষেত্র OPT_TRACE:
			env.trace = true;
			বিরতি;

		    ক্ষেত্র OPT_VERBOSE:
			env.printstats = true;
			বিরতি;

		    ক্ষেত্র OPT_VERSION:
			printf ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_version);
			FLEX_EXIT (0);

		    ক্ষেত্র OPT_WARN:
			env.nowarn = false;
			বিরতি;

		    ক্ষেত্র OPT_NO_WARN:
			env.nowarn = true;
			বিরতি;

		    ক্ষেত্র OPT_7BIT:
			ctrl.csize = 128;
			বিরতি;

		    ক্ষেত্র OPT_8BIT:
			ctrl.csize = CSIZE;
			বিরতি;

		    ক্ষেত্র OPT_ALIGN:
			ctrl.long_align = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_ALIGN:
			ctrl.long_align = false;
			বিরতি;

		    ক্ষেত্র OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			বিরতি;

		    ক্ষেত্র OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			বিরতি;

		    ক্ষেত্র OPT_ARRAY:
			ctrl.yytext_is_array = true;
			বিরতি;

		    ক্ষেত্র OPT_POINTER:
			ctrl.yytext_is_array = false;
			বিরতি;

		    ক্ষেত্র OPT_ECS:
			ctrl.useecs = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_ECS:
			ctrl.useecs = false;
			বিরতি;

		    ক্ষেত্র OPT_EMIT:
			ctrl.emit = arg;
			বিরতি;

		    ক্ষেত্র OPT_HEADER_FILE:
			env.headerfilename = arg;
			বিরতি;

		    ক্ষেত্র OPT_META_ECS:
			ctrl.usemecs = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_META_ECS:
			ctrl.usemecs = false;
			বিরতি;

		    ক্ষেত্র OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    অক্ষর   *def;
			    অক্ষর buf2[4096];

			    জন্য (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    চালু;
			    যদি (*def == '\0')
				    def = "1";

			    snprintf(buf2, আকার(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    বিরতি;

		    ক্ষেত্র OPT_READ:
			ctrl.use_read = true;
			বিরতি;

		    ক্ষেত্র OPT_স্তূপ:
			ctrl.স্তূপ_used = true;
			বিরতি;

		    ক্ষেত্র OPT_STDINIT:
			ctrl.do_stdinit = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			বিরতি;

		    ক্ষেত্র OPT_YYCLASS:
			ctrl.yyclass = arg;
			বিরতি;

		    ক্ষেত্র OPT_YYLINENO:
			ctrl.do_yylineno = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			বিরতি;

		    ক্ষেত্র OPT_YYWRAP:
			ctrl.do_yywrap = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			বিরতি;

		    ক্ষেত্র OPT_YYMORE:
			ctrl.yymore_really_used = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_YYMORE:
			ctrl.yymore_really_used = false;
			বিরতি;

		    ক্ষেত্র OPT_REJECT:
			ctrl.reject_really_used = true;
			বিরতি;

		    ক্ষেত্র OPT_NO_REJECT:
			ctrl.reject_really_used = false;
			বিরতি;

		    ক্ষেত্র OPT_NO_YY_ঠেলো_STATE:
			ctrl.no_yy_ঠেলো_state = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YY_বের_করো_STATE:
			ctrl.no_yy_বের_করো_state = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YY_শীর্ষ_STATE:
			ctrl.no_yy_শীর্ষ_state = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YY_SCAN_বাফার:
			ctrl.no_yy_scan_বাফার = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YY_SCAN_BYTES:
			ctrl.no_yy_scan_bytes = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YY_SCAN_STRING:
			ctrl.no_yy_scan_string = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYGET_TEXT:
			ctrl.no_yyget_text = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYGET_COLUMN:
			ctrl.no_yyget_column = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYSET_COLUMN:
			ctrl.no_yyset_column = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYGET_IN:
			ctrl.no_yyget_in = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYSET_IN:
			ctrl.no_yyset_in = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYGET_OUT:
			ctrl.no_yyget_out = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYSET_OUT:
			ctrl.no_yyset_out = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			বিরতি;
		    ক্ষেত্র OPT_NO_YYSET_DEBUG:
			ctrl.no_set_debug = true;
			বিরতি;

		    ক্ষেত্র OPT_HEX:
			env.trace_hex = true;
                        বিরতি;
		    ক্ষেত্র OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        বিরতি;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	অঙ্ক_প্রবেশ_files = argc - optind;
	প্রবেশ_files = argv + optind;
	set_প্রবেশ_file (অঙ্ক_প্রবেশ_files > 0 ? প্রবেশ_files[0] : ফাঁকা);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	অঙ্ক_rules = অঙ্ক_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = অঙ্ক_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	অঙ্ক_backing_up = onesp = numprots = 0;
	variable_trailing_context_rules = bol_needed = false;

	linenum = sectnum = 1;
	firstprot = NIL;

	/* Used in mkprot() so that the first proto goes in slot 1
	 * of the proto queue.
	 */
	lastprot = 1;

	set_up_initial_allocations ();
}


/* readin - read in the rules section of the input file(s) */

শূন্য readin (শূন্য)
{
	অক্ষর buf[256];

	সারি_directive_out(ফাঁকা, infilename, linenum);

	যদি (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
		flexend (1);
	}

	যদি (syntaxerror)
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

	যদি (tablesext)
		gentables = false;

	যদি (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	যদি (tablesext) {
		FILE   *tablesout;
		কাঠামো yytbl_hdr hdr;
		অক্ষর   *pname = 0;
		size_t  nbytes = 0;

		যদি (!tablesfilename) {
			nbytes = strlen (ctrl.prefix) + strlen (tablesfile_template) + 2;
			tablesfilename = pname = calloc(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.prefix);
		}

		যদি ((tablesout = fopen (tablesfilename, "w")) == ফাঁকা)
			lerr (_("could not create %s"), tablesfilename);
		মুক্ত(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = strlen (ctrl.prefix) + strlen ("tables") + 2;
		tablesname = calloc(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.prefix);
		yytbl_hdr_init (&hdr, flex_version, tablesname);

		যদি (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	যদি (env.skelname && (skelfile = fopen (env.skelname, "r")) == ফাঁকা)
		lerr (_("can't open skeleton file %s"), env.skelname);

	যদি (strchr(ctrl.prefix, '[') || strchr(ctrl.prefix, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	যদি (env.did_outfilename)
		সারি_directive_out (stdout, ফাঁকা, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	যদি( শীর্ষ_buf.elts)
		outn((অক্ষর*) শীর্ষ_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	সারি_directive_out(ফাঁকা, ফাঁকা, 0);

	/* User may want to set the scanner prototype */
	যদি (ctrl.yydecl != ফাঁকা) {
		out_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	যদি (ctrl.userinit != ফাঁকা) {
		out_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	যদি (ctrl.preaction != ফাঁকা) {
		out_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	যদি (ctrl.postaction != ফাঁকা) {
		out_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	out_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	যদি (userdef_buf.elts)
		outn ((অক্ষর *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	যদি (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	যদি (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	যদি (env.backing_up_report) {
		ctrl.backing_up_file = fopen (backing_name, "w");
		যদি (ctrl.backing_up_file == ফাঁকা)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	অন্যথা
		ctrl.backing_up_file = ফাঁকা;

	যদি (ctrl.yymore_really_used == true)
		yymore_used = true;
	অন্যথা যদি (ctrl.yymore_really_used == false)
		yymore_used = false;

	যদি (ctrl.reject_really_used == true)
		reject = true;
	অন্যথা যদি (ctrl.reject_really_used == false)
		reject = false;

	যদি (env.performance_hint > 0) {
		যদি (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		অন্যথা যদি (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		যদি (env.performance_hint > 1) {
			যদি (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			যদি (yymore_used)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		যদি (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		যদি (variable_trailing_context_rules)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	যদি (reject)
		real_reject = true;

	যদি (variable_trailing_context_rules)
		reject = true;

	যদি ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		যদি (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		অন্যথা যদি (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		অন্যথা
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	যদি (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	অন্যথা
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	যদি (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, আকার(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		কাঠামো Buf tmpbuf;
		পূর্ণসংখ্যা i;
		buf_init(&tmpbuf, আকার(অক্ষর));
		জন্য (i = 1; i <= lastsc; i++) {
			অক্ষর *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = strlen(fmt) + strlen(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = malloc(strsz);
			যদি (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			মুক্ত(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		out_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	যদি (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	যদি (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	যদি (extra_type != ফাঁকা)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	যদি (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		যদি (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	যদি (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	অন্যথা যদি (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	যদি (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	অন্যথা
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	যদি (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	অন্যথা
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	যদি (yymore_used)
		visible_define ( "M4_MODE_YYMORE_USED");
	অন্যথা
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	যদি (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	অন্যথা
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	যদি (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	অন্যথা
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	যদি (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	অন্যথা
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	যদি (variable_trailing_context_rules) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} অন্যথা {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	যদি (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	যদি (ctrl.reject_really_used)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	যদি (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	অন্যথা
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	যদি (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	যদি (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	অন্যথা যদি (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	অন্যথা যদি (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	অন্যথা
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	যদি (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	যদি (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	অন্যথা
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	যদি (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	যদি (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	অন্যথা
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	যদি (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	অন্যথা
		visible_define ( "M4_MODE_NO_GENTABLES");
	যদি (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	অন্যথা
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	যদি (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	যদি (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	যদি (ctrl.yyclass != ফাঁকা) {
		visible_define ( "M4_MODE_YYCLASS");
		out_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	যদি (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	যদি (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	যদি (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	অন্যথা
		visible_define ( "M4_MODE_NO_YYWRAP");

	যদি (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	যদি (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	যদি (is_default_backend()) {
		যদি (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} অন্যথা {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	যদি (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	যদি (ctrl.prefix != ফাঁকা)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.prefix);

	যদি (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	যদি (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	যদি (ctrl.yyterminate != ফাঁকা)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	যদি (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	যদি (ctrl.no_yy_ঠেলো_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	যদি (ctrl.no_yy_বের_করো_state)
		visible_define("M4_YY_NO_POP_STATE");
	যদি (ctrl.no_yy_শীর্ষ_state)
		visible_define("M4_YY_NO_TOP_STATE");
	যদি (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	যদি (ctrl.no_yy_scan_বাফার)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	যদি (ctrl.no_yy_scan_bytes)
		visible_define("M4_YY_NO_SCAN_BYTES");
	যদি (ctrl.no_yy_scan_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	যদি (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	যদি (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	যদি (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	যদি (ctrl.no_yyget_text)
		visible_define("M4_YY_NO_GET_TEXT");
	যদি (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	যদি (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	যদি (ctrl.no_yyget_column)
		visible_define("M4_YY_NO_GET_COLUMN");
	যদি (ctrl.no_yyset_column)
		visible_define("M4_YY_NO_SET_COLUMN");
	যদি (ctrl.no_yyget_in)
		visible_define("M4_YY_NO_GET_IN");
	যদি (ctrl.no_yyset_in)
		visible_define("M4_YY_NO_SET_IN");
	যদি (ctrl.no_yyget_out)
		visible_define("M4_YY_NO_GET_OUT");
	যদি (ctrl.no_yyset_out)
		visible_define("M4_YY_NO_SET_OUT");
	যদি (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	যদি (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	যদি (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	যদি (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	যদি (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	যদি (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	যদি (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	যদি (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	যদি (ctrl.no_set_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	যদি (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	যদি (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	যদি (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	যদি (ctrl.স্তূপ_used)
		visible_define("M4_YY_STACK_USED");

	যদি (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	অন্যথা
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	out ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

শূন্য set_up_initial_allocations (শূন্য)
{
	maximum_mns = (ctrl.long_align ? MAXIMUM_MNS_LONG : MAXIMUM_MNS);
	current_mns = INITIAL_MNS;
	firstst = allocate_integer_array (current_mns);
	lastst = allocate_integer_array (current_mns);
	finalst = allocate_integer_array (current_mns);
	transchar = allocate_integer_array (current_mns);
	trans1 = allocate_integer_array (current_mns);
	trans2 = allocate_integer_array (current_mns);
	accptnum = allocate_integer_array (current_mns);
	assoc_rule = allocate_integer_array (current_mns);
	state_type = allocate_integer_array (current_mns);

	current_max_rules = INITIAL_MAX_RULES;
	rule_type = allocate_integer_array (current_max_rules);
	rule_linenum = allocate_integer_array (current_max_rules);
	rule_useful = allocate_array(current_max_rules, আকার(অক্ষর));
	rule_has_nl = allocate_array(current_max_rules, আকার(অক্ষর));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, আকার(অক্ষর));
	sceof = allocate_array(current_max_scs, আকার(অক্ষর));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, আকার(অক্ষর));

	current_max_ccl_tbl_আকার = INITIAL_MAX_CCL_TBL_আকার;
	ccltbl = allocate_Character_array (current_max_ccl_tbl_আকার);

	current_max_dfa_আকার = INITIAL_MAX_DFA_আকার;

	current_max_xpairs = INITIAL_MAX_XPAIRS;
	nxt = allocate_integer_array (current_max_xpairs);
	chk = allocate_integer_array (current_max_xpairs);

	current_max_template_xpairs = INITIAL_MAX_TEMPLATE_XPAIRS;
	tnxt = allocate_integer_array (current_max_template_xpairs);

	current_max_dfas = INITIAL_MAX_DFAS;
	base = allocate_integer_array (current_max_dfas);
	def = allocate_integer_array (current_max_dfas);
	dfasiz = allocate_integer_array (current_max_dfas);
	accsiz = allocate_integer_array (current_max_dfas);
	dhash = allocate_integer_array (current_max_dfas);
	dss = allocate_int_ptr_array (current_max_dfas);
	dfaacc = allocate_array(current_max_dfas,
		আকার(সংঘ dfaacc_union));

	nultrans = ফাঁকা;
}


শূন্য usage (শূন্য)
{
	FILE   *f = stdout;

	যদি (!env.did_outfilename) {
		snprintf (outfile_path, আকার(outfile_path), outfile_template,
			  ctrl.prefix, suffix());
		env.outfilename = outfile_path;
	}

	fprintf (f, _("Usage: %s [OPTIONS] [FILE]...\n"), program_name);
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
		 backing_name, "flex", outfile_path, "flex");

}
