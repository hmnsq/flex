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

ایستا نویسه flex_version[] = FLEX_VERSION;

/* declare functions that have forward references */

تهی flexinit(صحیح, نویسه **);
تهی readin(تهی);
تهی set_up_initial_allocations(تهی);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
صحیح     yymore_used, reject, real_reject, continued_action, in_rule;
صحیح     datapos, dataline, linenum;
FILE   *skelfile = پوچ;
صحیح     skel_ind = 0;
نویسه   *action_array;
صحیح     action_size, defs1_offset, prolog_offset, action_offset,
	action_index;
نویسه   *infilename = پوچ;
نویسه   *extra_type = پوچ;
صحیح     onestate[ONE_پشته_SIZE], onesym[ONE_پشته_SIZE];
صحیح     onenext[ONE_پشته_SIZE], onedef[ONE_پشته_SIZE], onesp;
صحیح     maximum_mns, current_mns, current_max_rules;
صحیح     رقم_rules, رقم_eof_rules, default_rule, lastnfa;
صحیح    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
صحیح    *accptnum, *assoc_rule, *state_type;
صحیح    *rule_type, *rule_linenum;
صحیح     current_state_type;
bool    variable_trailing_context_rules;
صحیح     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
صحیح     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];
صحیح     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
صحیح     tecbck[CSIZE + 1];
صحیح     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
نویسه   *scxclu, *sceof;
صحیح     current_max_scs;
ثابت نویسه **scname;
صحیح     current_max_dfa_size, current_max_xpairs;
صحیح     current_max_template_xpairs, current_max_dfas;
صحیح     lastdfa, *nxt, *chk, *tnxt;
صحیح    *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
اجتماع dfaacc_union *dfaacc;
صحیح    *accsiz, *dhash, numas;
صحیح     numsnpairs, jambase, jamstate;
صحیح     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
صحیح     current_maxccls, current_max_ccl_tbl_size;
unsigned نویسه   *ccltbl;
نویسه    nmstr[MAXLINE];
صحیح     sectnum, nummt, hshcol, dfaeql, numeps, eps2, رقم_reallocs, nmval;
صحیح     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
صحیح     رقم_backing_up, bol_needed;
صحیح     end_of_buffer_state;
نویسه  **درون_داد_files;
صحیح     رقم_درون_داد_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
نویسه   *rule_useful, *rule_has_nl, *ccl_has_nl;
صحیح     nlch = '\n';

bool    tablesext, tablesverify, gentables;
نویسه   *tablesfilename=0,*tablesname=0;
ساختار yytbl_writer tableswr;
size_t footprint;

ساختار ctrl_bundle_t ctrl;
ساختار env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
نویسه   *program_name = "flex";

ایستا ثابت نویسه outfile_template[] = "lex.%s.%s";
ایستا ثابت نویسه *backing_name = "lex.backup";
ایستا ثابت نویسه tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
بیرونی FILE* yyout;

ایستا نویسه outfile_path[MAXLINE];
ایستا صحیح outfile_created = 0;
ایستا صحیح _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
ثابت نویسه *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
ثابت نویسه *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
ایستا صحیح preproc_level = 1000;

صحیح flex_main (صحیح argc, نویسه *argv[]);

صحیح flex_main (صحیح argc, نویسه *argv[])
{
	صحیح     i, exit_status, child_status;
	صحیح	did_eof_rule = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_status = setjmp (flex_main_jmp_buf);
	اگر (exit_status){
		اگر (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		وقتی (wait(&child_status) > 0){
			اگر (!WIFEXITED (child_status)
			    || WEXITSTATUS (child_status) != 0){
				/* report an error of a child
				 */
				اگر( exit_status <= 1 )
					exit_status = 2;

			}
		}
		بازگشت exit_status - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	برای (i = 1; i <= رقم_rules; ++i)
		اگر (!rule_useful[i] && i != default_rule)
			سطر_warning (_("rule cannot be matched"),
				      rule_linenum[i]);

	اگر (ctrl.spprdflt && !reject && rule_useful[default_rule])
		سطر_warning (_
			      ("-s option given but default rule can be matched"),
			      rule_linenum[default_rule]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	اگر (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	وگرنه {
		visible_define ( "M4_MODE_NO_NULTRANS");
		اگر (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		وگرنه
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		اگر (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		وگرنه
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	out ("\n");

	comment("START of Flex-generated definitions\n");
	out_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", رقم_rules);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", رقم_rules + 1);
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

	سطر_directive_out (stdout, پوچ, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	out (&action_array[prolog_offset]);

	سطر_directive_out (stdout, پوچ, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	out (&action_array[action_offset]);

	سطر_directive_out (stdout, پوچ, linenum);

	/* generate cases for any missing EOF rules */
	برای (i = 1; i <= lastsc; ++i)
		اگر (!sceof[i]) {
			out_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			out ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_rule = true;
		}

	اگر (did_eof_rule) {
		out ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	سطر_directive_out (stdout, infilename, linenum);

	اگر (sectnum == 3) {
		OUT_BEGIN_CODE ();
                اگر (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(تهی) flexscan ();	/* copy remainder of input to output */
                اگر (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		OUT_END_CODE ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	بازگشت 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
صحیح اصلی (صحیح argc, نویسه *argv[])
{
#اگر defined(ENABLE_NLS) && ENABLE_NLS
#اگر HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif
#endif

	بازگشت flex_main (argc, argv);
}

/* Set up the output filter chain. */

تهی initialize_output_filters(تهی)
{
	ثابت نویسه * m4 = پوچ;

	output_chain = filter_create_int(پوچ, filter_tee_header, env.headerfilename);
	اگر ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (نویسه *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, پوچ);

	/* For debugging, only run the requested number of filters. */
	اگر (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

تهی check_options (تهی)
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
		ctrl.reject_really_used = true;
#endif

	اگر (ctrl.csize == trit_unspecified) {
		اگر ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		وگرنه
			ctrl.csize = CSIZE;
	}

	اگر (ctrl.interactive == trit_unspecified) {
		اگر (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		وگرنه
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

		برای (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	وگرنه {
		/* Put everything in its own equivalence class. */
		برای (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	اگر (!env.use_stdout) {
		FILE   *prev_stdout;

		اگر (!env.did_outfilename) {
			snprintf (outfile_path, اندازه(outfile_path), outfile_template,
				  ctrl.prefix, suffix());

			env.outfilename = outfile_path;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		اگر (prev_stdout == پوچ)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

تهی flexend (صحیح exit_status)
{
	ایستا صحیح called_before = -1;	/* prevent infinite recursion. */
	صحیح     tblsiz;

	اگر (++called_before)
		FLEX_EXIT (exit_status);

	اگر (ctrl.yyclass != پوچ && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	اگر (skelfile != پوچ) {
		اگر (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		وگرنه اگر (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	اگر (exit_status != 0 && outfile_created) {
		اگر (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		وگرنه اگر ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		وگرنه اگر (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	اگر (env.backing_up_report && ctrl.backing_up_file) {
		اگر (رقم_backing_up == 0)
			fprintf (ctrl.backing_up_file, _("No backing up.\n"));
		وگرنه اگر (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_up_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 رقم_backing_up);
		وگرنه
			fprintf (ctrl.backing_up_file,
				 _("Compressed tables always back up.\n"));

		اگر (ferror (ctrl.backing_up_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		وگرنه اگر (fclose (ctrl.backing_up_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	اگر (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 program_name, flex_version);

		fprintf (stderr, _("  scanner options: -"));

		اگر (ctrl.C_plus_plus)
			putc ('+', stderr);
		اگر (env.backing_up_report)
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
		وگرنه
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

		اگر (env.skelname != پوچ)
			fprintf (stderr, " -S%s", env.skelname);

		اگر (strcmp (ctrl.prefix, "yy"))
			fprintf (stderr, " -P%s", ctrl.prefix);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 رقم_rules + رقم_eof_rules -
			 1 /* - 1 for def. rule */ );

		اگر (رقم_backing_up == 0)
			fprintf (stderr, _("  No backing up\n"));
		وگرنه اگر (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 رقم_backing_up);
		وگرنه
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
		وگرنه
			fprintf (stderr,
				 _
				 ("  %d/%d character classes needed %d/%d words of storage, %d reused\n"),
				 lastccl, current_maxccls,
				 cclmap[lastccl] + ccllen[lastccl],
				 current_max_ccl_tbl_size, cclreuse);

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

		وگرنه {
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
			 رقم_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_status);
}


/* flexinit - initialize flex */

تهی flexinit (صحیح argc, نویسه **argv)
{
	صحیح     i, sawcmpflag, rv, optind;
	نویسه   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', اندازه(ctrl));
	syntaxerror = false;
	yymore_used = continued_action = false;
	in_rule = reject = false;
	ctrl.yymore_really_used = ctrl.reject_really_used = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_سطر_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.prefix = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = پوچ;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_size = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_size);
	defs1_offset = prolog_offset = action_offset = action_index = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, اندازه (نویسه));	/* one long string */
	buf_init (&بالاترین_buf, اندازه (نویسه));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	program_name = argv[0];

	اگر (program_name != پوچ &&
	    program_name[strlen (program_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	اگر (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	وقتی ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		اگر (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 program_name);
			FLEX_EXIT (1);
		}

		انتخاب ((شمارش flexopt_flag_t) rv) {
		    حالت OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			بشکن;

		    حالت OPT_BATCH:
			ctrl.interactive = trit_false;
			بشکن;

		    حالت OPT_BACKUP:
			env.backing_up_report = trit_true;
			بشکن;

		    حالت OPT_BACKUP_FILE:
			env.backing_up_report = true;
                        backing_name = arg;
			بشکن;

		    حالت OPT_DONOTHING:
			بشکن;

		    حالت OPT_COMPRESSION:
			اگر (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			برای (i = 0; arg && arg[i] != '\0'; i++)
				انتخاب (arg[i]) {
				    حالت 'a':
					ctrl.long_align = true;
					بشکن;

				    حالت 'e':
					ctrl.useecs = true;
					بشکن;

				    حالت 'F':
					ctrl.fullspd = true;
					بشکن;

				    حالت 'f':
					ctrl.fulltbl = true;
					بشکن;

				    حالت 'm':
					ctrl.usemecs = true;
					بشکن;

				    حالت 'r':
					ctrl.use_read = true;
					بشکن;

				    پیشفرض:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					بشکن;
				}
			بشکن;

		    حالت OPT_DEBUG:
			ctrl.ddebug = true;
			بشکن;

		    حالت OPT_NO_DEBUG:
			ctrl.ddebug = false;
			بشکن;

		    حالت OPT_FULL:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			بشکن;

		    حالت OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			بشکن;

		    حالت OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    حالت OPT_INTERACTIVE:
			ctrl.interactive = true;
			بشکن;

		    حالت OPT_CASE_INSENSITIVE:
			sf_set_case_ins(true);
			بشکن;

		    حالت OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			بشکن;

		    حالت OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			بشکن;

		    حالت OPT_PREPROC_LEVEL:
			preproc_level = (صحیح) strtol(arg,پوچ,0);
			بشکن;

		    حالت OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			بشکن;

		    حالت OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			بشکن;

		    حالت OPT_NO_سطر:
			ctrl.gen_سطر_dirs = false;
			بشکن;

		    حالت OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			بشکن;

		    حالت OPT_PREFIX:
			ctrl.prefix = arg;
			بشکن;

		    حالت OPT_PERF_REPORT:
			++env.performance_hint;
			بشکن;

		    حالت OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			بشکن;

		    حالت OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			بشکن;

		    حالت OPT_REENTRANT:
			ctrl.reentrant = true;
			بشکن;

		    حالت OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			بشکن;

		    حالت OPT_SKEL:
			env.skelname = arg;
			بشکن;

		    حالت OPT_DEFAULT:
			ctrl.spprdflt = false;
			بشکن;

		    حالت OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			بشکن;

		    حالت OPT_STDOUT:
			env.use_stdout = true;
			بشکن;

		    حالت OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			بشکن;

		    حالت OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			بشکن;

		    حالت OPT_TABLES_VERIFY:
			tablesverify = true;
			بشکن;

		    حالت OPT_TRACE:
			env.trace = true;
			بشکن;

		    حالت OPT_VERBOSE:
			env.printstats = true;
			بشکن;

		    حالت OPT_VERSION:
			printf ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_version);
			FLEX_EXIT (0);

		    حالت OPT_WARN:
			env.nowarn = false;
			بشکن;

		    حالت OPT_NO_WARN:
			env.nowarn = true;
			بشکن;

		    حالت OPT_7BIT:
			ctrl.csize = 128;
			بشکن;

		    حالت OPT_8BIT:
			ctrl.csize = CSIZE;
			بشکن;

		    حالت OPT_ALIGN:
			ctrl.long_align = true;
			بشکن;

		    حالت OPT_NO_ALIGN:
			ctrl.long_align = false;
			بشکن;

		    حالت OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			بشکن;

		    حالت OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			بشکن;

		    حالت OPT_ARRAY:
			ctrl.yytext_is_array = true;
			بشکن;

		    حالت OPT_POINTER:
			ctrl.yytext_is_array = false;
			بشکن;

		    حالت OPT_ECS:
			ctrl.useecs = true;
			بشکن;

		    حالت OPT_NO_ECS:
			ctrl.useecs = false;
			بشکن;

		    حالت OPT_EMIT:
			ctrl.emit = arg;
			بشکن;

		    حالت OPT_HEADER_FILE:
			env.headerfilename = arg;
			بشکن;

		    حالت OPT_META_ECS:
			ctrl.usemecs = true;
			بشکن;

		    حالت OPT_NO_META_ECS:
			ctrl.usemecs = false;
			بشکن;

		    حالت OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    نویسه   *def;
			    نویسه buf2[4096];

			    برای (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    ادامه;
			    اگر (*def == '\0')
				    def = "1";

			    snprintf(buf2, اندازه(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    بشکن;

		    حالت OPT_READ:
			ctrl.use_read = true;
			بشکن;

		    حالت OPT_پشته:
			ctrl.پشته_used = true;
			بشکن;

		    حالت OPT_STDINIT:
			ctrl.do_stdinit = true;
			بشکن;

		    حالت OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			بشکن;

		    حالت OPT_YYCLASS:
			ctrl.yyclass = arg;
			بشکن;

		    حالت OPT_YYLINENO:
			ctrl.do_yylineno = true;
			بشکن;

		    حالت OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			بشکن;

		    حالت OPT_YYWRAP:
			ctrl.do_yywrap = true;
			بشکن;

		    حالت OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			بشکن;

		    حالت OPT_YYMORE:
			ctrl.yymore_really_used = true;
			بشکن;

		    حالت OPT_NO_YYMORE:
			ctrl.yymore_really_used = false;
			بشکن;

		    حالت OPT_REJECT:
			ctrl.reject_really_used = true;
			بشکن;

		    حالت OPT_NO_REJECT:
			ctrl.reject_really_used = false;
			بشکن;

		    حالت OPT_NO_YY_افزودن_STATE:
			ctrl.no_yy_افزودن_state = true;
			بشکن;
		    حالت OPT_NO_YY_برداشت_STATE:
			ctrl.no_yy_برداشت_state = true;
			بشکن;
		    حالت OPT_NO_YY_بالاترین_STATE:
			ctrl.no_yy_بالاترین_state = true;
			بشکن;
		    حالت OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			بشکن;
		    حالت OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			بشکن;
		    حالت OPT_NO_YY_SCAN_BUFFER:
			ctrl.no_yy_scan_buffer = true;
			بشکن;
		    حالت OPT_NO_YY_SCAN_BYTES:
			ctrl.no_yy_scan_bytes = true;
			بشکن;
		    حالت OPT_NO_YY_SCAN_STRING:
			ctrl.no_yy_scan_string = true;
			بشکن;
		    حالت OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			بشکن;
		    حالت OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			بشکن;
		    حالت OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			بشکن;
		    حالت OPT_NO_YYGET_TEXT:
			ctrl.no_yyget_text = true;
			بشکن;
		    حالت OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			بشکن;
		    حالت OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			بشکن;
		    حالت OPT_NO_YYGET_COLUMN:
			ctrl.no_yyget_column = true;
			بشکن;
		    حالت OPT_NO_YYSET_COLUMN:
			ctrl.no_yyset_column = true;
			بشکن;
		    حالت OPT_NO_YYGET_IN:
			ctrl.no_yyget_in = true;
			بشکن;
		    حالت OPT_NO_YYSET_IN:
			ctrl.no_yyset_in = true;
			بشکن;
		    حالت OPT_NO_YYGET_OUT:
			ctrl.no_yyget_out = true;
			بشکن;
		    حالت OPT_NO_YYSET_OUT:
			ctrl.no_yyset_out = true;
			بشکن;
		    حالت OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			بشکن;
		    حالت OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			بشکن;
		    حالت OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			بشکن;
		    حالت OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			بشکن;
		    حالت OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			بشکن;
		    حالت OPT_NO_YYSET_DEBUG:
			ctrl.no_set_debug = true;
			بشکن;

		    حالت OPT_HEX:
			env.trace_hex = true;
                        بشکن;
		    حالت OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        بشکن;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	رقم_درون_داد_files = argc - optind;
	درون_داد_files = argv + optind;
	set_درون_داد_file (رقم_درون_داد_files > 0 ? درون_داد_files[0] : پوچ);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	رقم_rules = رقم_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = رقم_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	رقم_backing_up = onesp = numprots = 0;
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

تهی readin (تهی)
{
	نویسه buf[256];

	سطر_directive_out(پوچ, infilename, linenum);

	اگر (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
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
		ساختار yytbl_hdr hdr;
		نویسه   *pname = 0;
		size_t  nbytes = 0;

		اگر (!tablesfilename) {
			nbytes = strlen (ctrl.prefix) + strlen (tablesfile_template) + 2;
			tablesfilename = pname = calloc(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.prefix);
		}

		اگر ((tablesout = fopen (tablesfilename, "w")) == پوچ)
			lerr (_("could not create %s"), tablesfilename);
		آزاد(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = strlen (ctrl.prefix) + strlen ("tables") + 2;
		tablesname = calloc(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.prefix);
		yytbl_hdr_init (&hdr, flex_version, tablesname);

		اگر (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	اگر (env.skelname && (skelfile = fopen (env.skelname, "r")) == پوچ)
		lerr (_("can't open skeleton file %s"), env.skelname);

	اگر (strchr(ctrl.prefix, '[') || strchr(ctrl.prefix, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	اگر (env.did_outfilename)
		سطر_directive_out (stdout, پوچ, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	اگر( بالاترین_buf.elts)
		outn((نویسه*) بالاترین_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	سطر_directive_out(پوچ, پوچ, 0);

	/* User may want to set the scanner prototype */
	اگر (ctrl.yydecl != پوچ) {
		out_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	اگر (ctrl.userinit != پوچ) {
		out_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	اگر (ctrl.preaction != پوچ) {
		out_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	اگر (ctrl.postaction != پوچ) {
		out_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	out_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	اگر (userdef_buf.elts)
		outn ((نویسه *) (userdef_buf.elts));

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

	اگر (env.backing_up_report) {
		ctrl.backing_up_file = fopen (backing_name, "w");
		اگر (ctrl.backing_up_file == پوچ)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	وگرنه
		ctrl.backing_up_file = پوچ;

	اگر (ctrl.yymore_really_used == true)
		yymore_used = true;
	وگرنه اگر (ctrl.yymore_really_used == false)
		yymore_used = false;

	اگر (ctrl.reject_really_used == true)
		reject = true;
	وگرنه اگر (ctrl.reject_really_used == false)
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

		وگرنه اگر (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		اگر (env.performance_hint > 1) {
			اگر (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			اگر (yymore_used)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		اگر (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		اگر (variable_trailing_context_rules)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	اگر (reject)
		real_reject = true;

	اگر (variable_trailing_context_rules)
		reject = true;

	اگر ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		اگر (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		وگرنه اگر (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		وگرنه
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	اگر (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	وگرنه
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
	snprintf(buf, اندازه(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		ساختار Buf tmpbuf;
		صحیح i;
		buf_init(&tmpbuf, اندازه(نویسه));
		برای (i = 1; i <= lastsc; i++) {
			نویسه *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = strlen(fmt) + strlen(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = malloc(strsz);
			اگر (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			آزاد(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		out_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	اگر (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	اگر (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	اگر (extra_type != پوچ)
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
	وگرنه اگر (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	اگر (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	وگرنه
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	اگر (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	وگرنه
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	اگر (yymore_used)
		visible_define ( "M4_MODE_YYMORE_USED");
	وگرنه
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	اگر (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	وگرنه
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	اگر (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	وگرنه
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	اگر (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	وگرنه
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	اگر (variable_trailing_context_rules) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} وگرنه {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	اگر (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	اگر (ctrl.reject_really_used)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	اگر (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	وگرنه
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	اگر (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	اگر (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	وگرنه اگر (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	وگرنه اگر (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	وگرنه
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	اگر (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	اگر (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	وگرنه
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	اگر (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	اگر (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	وگرنه
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	اگر (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	وگرنه
		visible_define ( "M4_MODE_NO_GENTABLES");
	اگر (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	وگرنه
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	اگر (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	اگر (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	اگر (ctrl.yyclass != پوچ) {
		visible_define ( "M4_MODE_YYCLASS");
		out_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	اگر (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	اگر (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	اگر (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	وگرنه
		visible_define ( "M4_MODE_NO_YYWRAP");

	اگر (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	اگر (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	اگر (is_default_backend()) {
		اگر (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} وگرنه {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	اگر (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	اگر (ctrl.prefix != پوچ)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.prefix);

	اگر (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	اگر (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	اگر (ctrl.yyterminate != پوچ)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	اگر (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	اگر (ctrl.no_yy_افزودن_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	اگر (ctrl.no_yy_برداشت_state)
		visible_define("M4_YY_NO_POP_STATE");
	اگر (ctrl.no_yy_بالاترین_state)
		visible_define("M4_YY_NO_TOP_STATE");
	اگر (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	اگر (ctrl.no_yy_scan_buffer)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	اگر (ctrl.no_yy_scan_bytes)
		visible_define("M4_YY_NO_SCAN_BYTES");
	اگر (ctrl.no_yy_scan_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	اگر (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	اگر (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	اگر (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	اگر (ctrl.no_yyget_text)
		visible_define("M4_YY_NO_GET_TEXT");
	اگر (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	اگر (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	اگر (ctrl.no_yyget_column)
		visible_define("M4_YY_NO_GET_COLUMN");
	اگر (ctrl.no_yyset_column)
		visible_define("M4_YY_NO_SET_COLUMN");
	اگر (ctrl.no_yyget_in)
		visible_define("M4_YY_NO_GET_IN");
	اگر (ctrl.no_yyset_in)
		visible_define("M4_YY_NO_SET_IN");
	اگر (ctrl.no_yyget_out)
		visible_define("M4_YY_NO_GET_OUT");
	اگر (ctrl.no_yyset_out)
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
	اگر (ctrl.no_set_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	اگر (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	اگر (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	اگر (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	اگر (ctrl.پشته_used)
		visible_define("M4_YY_STACK_USED");

	اگر (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	وگرنه
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	out ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

تهی set_up_initial_allocations (تهی)
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
	rule_useful = allocate_array(current_max_rules, اندازه(نویسه));
	rule_has_nl = allocate_array(current_max_rules, اندازه(نویسه));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, اندازه(نویسه));
	sceof = allocate_array(current_max_scs, اندازه(نویسه));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, اندازه(نویسه));

	current_max_ccl_tbl_size = INITIAL_MAX_CCL_TBL_SIZE;
	ccltbl = allocate_Character_array (current_max_ccl_tbl_size);

	current_max_dfa_size = INITIAL_MAX_DFA_SIZE;

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
		اندازه(اجتماع dfaacc_union));

	nultrans = پوچ;
}


تهی usage (تهی)
{
	FILE   *f = stdout;

	اگر (!env.did_outfilename) {
		snprintf (outfile_path, اندازه(outfile_path), outfile_template,
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
