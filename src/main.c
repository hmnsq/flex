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


#ضمن "flexdef.h"
#ضمن "version.h"
#ضمن "options.h"
#ضمن "tables.h"
#ضمن "parse.h"

ساكن حرف flex_version[] = FLEX_VERSION;

/* declare functions that have forward references */

فراغ flexinit(صحيح, حرف **);
فراغ readin(فراغ);
فراغ set_up_initial_allocations(فراغ);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
صحيح     yymore_used, reject, real_reject, continued_action, in_rule;
صحيح     datapos, dataline, linenum;
FILE   *skelfile = عدم;
صحيح     skel_ind = 0;
حرف   *action_array;
صحيح     action_size, defs1_offset, prolog_offset, action_offset,
	action_index;
حرف   *infilename = عدم;
حرف   *extra_type = عدم;
صحيح     onestate[ONE_تر_SIZE], onesym[ONE_تر_SIZE];
صحيح     onenext[ONE_تر_SIZE], onedef[ONE_تر_SIZE], onesp;
صحيح     maximum_mns, current_mns, current_max_rules;
صحيح     لمب_rules, لمب_eof_rules, default_rule, lastnfa;
صحيح    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
صحيح    *accptnum, *assoc_rule, *state_type;
صحيح    *rule_type, *rule_linenum;
صحيح     current_state_type;
bool    variable_trailing_context_rules;
صحيح     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
صحيح     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];
صحيح     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
صحيح     tecbck[CSIZE + 1];
صحيح     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
حرف   *scxclu, *sceof;
صحيح     current_max_scs;
ثابت حرف **scname;
صحيح     current_max_dfa_size, current_max_xpairs;
صحيح     current_max_template_xpairs, current_max_dfas;
صحيح     lastdfa, *nxt, *chk, *tnxt;
صحيح    *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
اتحاد dfaacc_union *dfaacc;
صحيح    *accsiz, *dhash, numas;
صحيح     numsnpairs, jambase, jamstate;
صحيح     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
صحيح     current_maxccls, current_max_ccl_tbl_size;
unsigned حرف   *ccltbl;
حرف    nmstr[MAXLINE];
صحيح     sectnum, nummt, hshcol, dfaeql, numeps, eps2, لمب_reallocs, nmval;
صحيح     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
صحيح     لمب_backing_up, bol_needed;
صحيح     end_of_buffer_state;
حرف  **شغرو_files;
صحيح     لمب_شغرو_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
حرف   *rule_useful, *rule_has_nl, *ccl_has_nl;
صحيح     nlch = '\n';

bool    tablesext, tablesverify, gentables;
حرف   *tablesfilename=0,*tablesname=0;
بنية yytbl_writer tableswr;
size_t footprint;

بنية ctrl_bundle_t ctrl;
بنية env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
حرف   *program_name = "flex";

ساكن ثابت حرف outfile_template[] = "lex.%s.%s";
ساكن ثابت حرف *backing_name = "lex.backup";
ساكن ثابت حرف tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
خارجي FILE* yyout;

ساكن حرف outfile_path[MAXLINE];
ساكن صحيح outfile_created = 0;
ساكن صحيح _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
ثابت حرف *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
ثابت حرف *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
ساكن صحيح preproc_level = 1000;

صحيح flex_main (صحيح argc, حرف *argv[]);

صحيح flex_main (صحيح argc, حرف *argv[])
{
	صحيح     i, exit_status, child_status;
	صحيح	did_eof_rule = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_status = setjmp (flex_main_jmp_buf);
	إذا (exit_status){
		إذا (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		طالما (wait(&child_status) > 0){
			إذا (!WIFEXITED (child_status)
			    || WEXITSTATUS (child_status) != 0){
				/* report an error of a child
				 */
				إذا( exit_status <= 1 )
					exit_status = 2;

			}
		}
		أرجع exit_status - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	لكل (i = 1; i <= لمب_rules; ++i)
		إذا (!rule_useful[i] && i != default_rule)
			لي_warning (_("rule cannot be matched"),
				      rule_linenum[i]);

	إذا (ctrl.spprdflt && !reject && rule_useful[default_rule])
		لي_warning (_
			      ("-s option given but default rule can be matched"),
			      rule_linenum[default_rule]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	إذا (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	وإلا {
		visible_define ( "M4_MODE_NO_NULTRANS");
		إذا (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		وإلا
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		إذا (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		وإلا
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	out ("\n");

	comment("START of Flex-generated definitions\n");
	out_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", لمب_rules);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", لمب_rules + 1);
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

	لي_directive_out (stdout, عدم, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	out (&action_array[prolog_offset]);

	لي_directive_out (stdout, عدم, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	out (&action_array[action_offset]);

	لي_directive_out (stdout, عدم, linenum);

	/* generate cases for any missing EOF rules */
	لكل (i = 1; i <= lastsc; ++i)
		إذا (!sceof[i]) {
			out_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			out ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_rule = true;
		}

	إذا (did_eof_rule) {
		out ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	لي_directive_out (stdout, infilename, linenum);

	إذا (sectnum == 3) {
		OUT_BEGIN_CODE ();
                إذا (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(فراغ) flexscan ();	/* copy remainder of input to output */
                إذا (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		OUT_END_CODE ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	أرجع 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
صحيح main (صحيح argc, حرف *argv[])
{
#إذا defined(ENABLE_NLS) && ENABLE_NLS
#إذا HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif
#endif

	أرجع flex_main (argc, argv);
}

/* Set up the output filter chain. */

فراغ initialize_output_filters(فراغ)
{
	ثابت حرف * m4 = عدم;

	output_chain = filter_create_int(عدم, filter_tee_header, env.headerfilename);
	إذا ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (حرف *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, عدم);

	/* For debugging, only run the requested number of filters. */
	إذا (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

فراغ check_options (فراغ)
{
	صحيح     i;

	إذا (ctrl.lex_compat) {
		إذا (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		إذا (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		إذا (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#إذا 0
	/* This makes no sense whatsoever. I'm removing it. */
	إذا (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_used = true;
#endif

	إذا (ctrl.csize == trit_unspecified) {
		إذا ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		وإلا
			ctrl.csize = CSIZE;
	}

	إذا (ctrl.interactive == trit_unspecified) {
		إذا (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		وإلا
			ctrl.interactive = trit_true;
	}

	إذا (ctrl.fulltbl || ctrl.fullspd) {
		إذا (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		إذا (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		إذا (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		إذا (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	إذا (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	إذا (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	إذا (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	إذا (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	إذا (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		لكل (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	وإلا {
		/* Put everything in its own equivalence class. */
		لكل (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	إذا (!env.use_stdout) {
		FILE   *prev_stdout;

		إذا (!env.did_outfilename) {
			snprintf (outfile_path, حجم(outfile_path), outfile_template,
				  ctrl.prefix, suffix());

			env.outfilename = outfile_path;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		إذا (prev_stdout == عدم)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

فراغ flexend (صحيح exit_status)
{
	ساكن صحيح called_before = -1;	/* prevent infinite recursion. */
	صحيح     tblsiz;

	إذا (++called_before)
		FLEX_EXIT (exit_status);

	إذا (ctrl.yyclass != عدم && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	إذا (skelfile != عدم) {
		إذا (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		وإلا إذا (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	إذا (exit_status != 0 && outfile_created) {
		إذا (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		وإلا إذا ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		وإلا إذا (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	إذا (env.backing_up_report && ctrl.backing_up_file) {
		إذا (لمب_backing_up == 0)
			fprintf (ctrl.backing_up_file, _("No backing up.\n"));
		وإلا إذا (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_up_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 لمب_backing_up);
		وإلا
			fprintf (ctrl.backing_up_file,
				 _("Compressed tables always back up.\n"));

		إذا (ferror (ctrl.backing_up_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		وإلا إذا (fclose (ctrl.backing_up_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	إذا (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 program_name, flex_version);

		fprintf (stderr, _("  scanner options: -"));

		إذا (ctrl.C_plus_plus)
			putc ('+', stderr);
		إذا (env.backing_up_report)
			putc ('b', stderr);
		إذا (ctrl.ddebug)
			putc ('d', stderr);
		إذا (sf_case_ins())
			putc ('i', stderr);
		إذا (ctrl.lex_compat)
			putc ('l', stderr);
		إذا (ctrl.posix_compat)
			putc ('X', stderr);
		إذا (env.performance_hint > 0)
			putc ('p', stderr);
		إذا (env.performance_hint > 1)
			putc ('p', stderr);
		إذا (ctrl.spprdflt)
			putc ('s', stderr);
		إذا (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        إذا (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        إذا (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		إذا (env.use_stdout)
			putc ('t', stderr);
		إذا (env.printstats)
			putc ('v', stderr);	/* always true! */
		إذا (env.nowarn)
			putc ('w', stderr);
		إذا (ctrl.interactive == trit_false)
			putc ('B', stderr);
		إذا (ctrl.interactive == trit_true)
			putc ('I', stderr);
		إذا (!ctrl.gen_لي_dirs)
			putc ('L', stderr);
		إذا (env.trace)
			putc ('T', stderr);

		إذا (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		إذا (ctrl.csize == 128)
			putc ('7', stderr);
		وإلا
			putc ('8', stderr);

		fprintf (stderr, " -C");

		إذا (ctrl.long_align)
			putc ('a', stderr);
		إذا (ctrl.fulltbl)
			putc ('f', stderr);
		إذا (ctrl.fullspd)
			putc ('F', stderr);
		إذا (ctrl.useecs)
			putc ('e', stderr);
		إذا (ctrl.usemecs)
			putc ('m', stderr);
		إذا (ctrl.use_read)
			putc ('r', stderr);

		إذا (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		إذا (env.skelname != عدم)
			fprintf (stderr, " -S%s", env.skelname);

		إذا (strcmp (ctrl.prefix, "yy"))
			fprintf (stderr, " -P%s", ctrl.prefix);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 لمب_rules + لمب_eof_rules -
			 1 /* - 1 for def. rule */ );

		إذا (لمب_backing_up == 0)
			fprintf (stderr, _("  No backing up\n"));
		وإلا إذا (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 لمب_backing_up);
		وإلا
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		إذا (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		إذا (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		وإلا
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

		إذا (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		وإلا {
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

		إذا (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		إذا (ctrl.usemecs) {
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
			 لمب_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_status);
}


/* flexinit - initialize flex */

فراغ flexinit (صحيح argc, حرف **argv)
{
	صحيح     i, sawcmpflag, rv, optind;
	حرف   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', حجم(ctrl));
	syntaxerror = false;
	yymore_used = continued_action = false;
	in_rule = reject = false;
	ctrl.yymore_really_used = ctrl.reject_really_used = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_لي_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.prefix = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = عدم;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_size = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_size);
	defs1_offset = prolog_offset = action_offset = action_index = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, حجم (حرف));	/* one long string */
	buf_init (&كولي_buf, حجم (حرف));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	program_name = argv[0];

	إذا (program_name != عدم &&
	    program_name[strlen (program_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	إذا (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	طالما ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		إذا (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 program_name);
			FLEX_EXIT (1);
		}

		بدل ((تعداد flexopt_flag_t) rv) {
		    حالة OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			اكسر;

		    حالة OPT_BATCH:
			ctrl.interactive = trit_false;
			اكسر;

		    حالة OPT_BACKUP:
			env.backing_up_report = trit_true;
			اكسر;

		    حالة OPT_BACKUP_FILE:
			env.backing_up_report = true;
                        backing_name = arg;
			اكسر;

		    حالة OPT_DONOTHING:
			اكسر;

		    حالة OPT_COMPRESSION:
			إذا (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			لكل (i = 0; arg && arg[i] != '\0'; i++)
				بدل (arg[i]) {
				    حالة 'a':
					ctrl.long_align = true;
					اكسر;

				    حالة 'e':
					ctrl.useecs = true;
					اكسر;

				    حالة 'F':
					ctrl.fullspd = true;
					اكسر;

				    حالة 'f':
					ctrl.fulltbl = true;
					اكسر;

				    حالة 'm':
					ctrl.usemecs = true;
					اكسر;

				    حالة 'r':
					ctrl.use_read = true;
					اكسر;

				    افتراضي:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					اكسر;
				}
			اكسر;

		    حالة OPT_DEBUG:
			ctrl.ddebug = true;
			اكسر;

		    حالة OPT_NO_DEBUG:
			ctrl.ddebug = false;
			اكسر;

		    حالة OPT_FULL:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			اكسر;

		    حالة OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			اكسر;

		    حالة OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    حالة OPT_INTERACTIVE:
			ctrl.interactive = true;
			اكسر;

		    حالة OPT_CASE_INSENSITIVE:
			sf_set_case_ins(true);
			اكسر;

		    حالة OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			اكسر;

		    حالة OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			اكسر;

		    حالة OPT_PREPROC_LEVEL:
			preproc_level = (صحيح) strtol(arg,عدم,0);
			اكسر;

		    حالة OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			اكسر;

		    حالة OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			اكسر;

		    حالة OPT_NO_لي:
			ctrl.gen_لي_dirs = false;
			اكسر;

		    حالة OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			اكسر;

		    حالة OPT_PREFIX:
			ctrl.prefix = arg;
			اكسر;

		    حالة OPT_PERF_REPORT:
			++env.performance_hint;
			اكسر;

		    حالة OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			اكسر;

		    حالة OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			اكسر;

		    حالة OPT_REENTRANT:
			ctrl.reentrant = true;
			اكسر;

		    حالة OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			اكسر;

		    حالة OPT_SKEL:
			env.skelname = arg;
			اكسر;

		    حالة OPT_DEFAULT:
			ctrl.spprdflt = false;
			اكسر;

		    حالة OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			اكسر;

		    حالة OPT_STDOUT:
			env.use_stdout = true;
			اكسر;

		    حالة OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			اكسر;

		    حالة OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			اكسر;

		    حالة OPT_TABLES_VERIFY:
			tablesverify = true;
			اكسر;

		    حالة OPT_TRACE:
			env.trace = true;
			اكسر;

		    حالة OPT_VERBOSE:
			env.printstats = true;
			اكسر;

		    حالة OPT_VERSION:
			printf ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_version);
			FLEX_EXIT (0);

		    حالة OPT_WARN:
			env.nowarn = false;
			اكسر;

		    حالة OPT_NO_WARN:
			env.nowarn = true;
			اكسر;

		    حالة OPT_7BIT:
			ctrl.csize = 128;
			اكسر;

		    حالة OPT_8BIT:
			ctrl.csize = CSIZE;
			اكسر;

		    حالة OPT_ALIGN:
			ctrl.long_align = true;
			اكسر;

		    حالة OPT_NO_ALIGN:
			ctrl.long_align = false;
			اكسر;

		    حالة OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			اكسر;

		    حالة OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			اكسر;

		    حالة OPT_ARRAY:
			ctrl.yytext_is_array = true;
			اكسر;

		    حالة OPT_POINTER:
			ctrl.yytext_is_array = false;
			اكسر;

		    حالة OPT_ECS:
			ctrl.useecs = true;
			اكسر;

		    حالة OPT_NO_ECS:
			ctrl.useecs = false;
			اكسر;

		    حالة OPT_EMIT:
			ctrl.emit = arg;
			اكسر;

		    حالة OPT_HEADER_FILE:
			env.headerfilename = arg;
			اكسر;

		    حالة OPT_META_ECS:
			ctrl.usemecs = true;
			اكسر;

		    حالة OPT_NO_META_ECS:
			ctrl.usemecs = false;
			اكسر;

		    حالة OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    حرف   *def;
			    حرف buf2[4096];

			    لكل (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    استمر;
			    إذا (*def == '\0')
				    def = "1";

			    snprintf(buf2, حجم(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    اكسر;

		    حالة OPT_READ:
			ctrl.use_read = true;
			اكسر;

		    حالة OPT_تر:
			ctrl.تر_used = true;
			اكسر;

		    حالة OPT_STDINIT:
			ctrl.do_stdinit = true;
			اكسر;

		    حالة OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			اكسر;

		    حالة OPT_YYCLASS:
			ctrl.yyclass = arg;
			اكسر;

		    حالة OPT_YYLINENO:
			ctrl.do_yylineno = true;
			اكسر;

		    حالة OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			اكسر;

		    حالة OPT_YYWRAP:
			ctrl.do_yywrap = true;
			اكسر;

		    حالة OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			اكسر;

		    حالة OPT_YYMORE:
			ctrl.yymore_really_used = true;
			اكسر;

		    حالة OPT_NO_YYMORE:
			ctrl.yymore_really_used = false;
			اكسر;

		    حالة OPT_REJECT:
			ctrl.reject_really_used = true;
			اكسر;

		    حالة OPT_NO_REJECT:
			ctrl.reject_really_used = false;
			اكسر;

		    حالة OPT_NO_YY_تور_STATE:
			ctrl.no_yy_تور_state = true;
			اكسر;
		    حالة OPT_NO_YY_چرو_STATE:
			ctrl.no_yy_چرو_state = true;
			اكسر;
		    حالة OPT_NO_YY_كولي_STATE:
			ctrl.no_yy_كولي_state = true;
			اكسر;
		    حالة OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			اكسر;
		    حالة OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			اكسر;
		    حالة OPT_NO_YY_SCAN_BUFFER:
			ctrl.no_yy_scan_buffer = true;
			اكسر;
		    حالة OPT_NO_YY_SCAN_BYTES:
			ctrl.no_yy_scan_bytes = true;
			اكسر;
		    حالة OPT_NO_YY_SCAN_STRING:
			ctrl.no_yy_scan_string = true;
			اكسر;
		    حالة OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			اكسر;
		    حالة OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			اكسر;
		    حالة OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			اكسر;
		    حالة OPT_NO_YYGET_TEXT:
			ctrl.no_yyget_text = true;
			اكسر;
		    حالة OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			اكسر;
		    حالة OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			اكسر;
		    حالة OPT_NO_YYGET_COLUMN:
			ctrl.no_yyget_column = true;
			اكسر;
		    حالة OPT_NO_YYSET_COLUMN:
			ctrl.no_yyset_column = true;
			اكسر;
		    حالة OPT_NO_YYGET_IN:
			ctrl.no_yyget_in = true;
			اكسر;
		    حالة OPT_NO_YYSET_IN:
			ctrl.no_yyset_in = true;
			اكسر;
		    حالة OPT_NO_YYGET_OUT:
			ctrl.no_yyget_out = true;
			اكسر;
		    حالة OPT_NO_YYSET_OUT:
			ctrl.no_yyset_out = true;
			اكسر;
		    حالة OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			اكسر;
		    حالة OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			اكسر;
		    حالة OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			اكسر;
		    حالة OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			اكسر;
		    حالة OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			اكسر;
		    حالة OPT_NO_YYSET_DEBUG:
			ctrl.no_set_debug = true;
			اكسر;

		    حالة OPT_HEX:
			env.trace_hex = true;
                        اكسر;
		    حالة OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        اكسر;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	لمب_شغرو_files = argc - optind;
	شغرو_files = argv + optind;
	set_شغرو_file (لمب_شغرو_files > 0 ? شغرو_files[0] : عدم);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	لمب_rules = لمب_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = لمب_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	لمب_backing_up = onesp = numprots = 0;
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

فراغ readin (فراغ)
{
	حرف buf[256];

	لي_directive_out(عدم, infilename, linenum);

	إذا (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
		flexend (1);
	}

	إذا (syntaxerror)
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

	إذا (tablesext)
		gentables = false;

	إذا (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	إذا (tablesext) {
		FILE   *tablesout;
		بنية yytbl_hdr hdr;
		حرف   *pname = 0;
		size_t  nbytes = 0;

		إذا (!tablesfilename) {
			nbytes = strlen (ctrl.prefix) + strlen (tablesfile_template) + 2;
			tablesfilename = pname = calloc(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.prefix);
		}

		إذا ((tablesout = fopen (tablesfilename, "w")) == عدم)
			lerr (_("could not create %s"), tablesfilename);
		حرر(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = strlen (ctrl.prefix) + strlen ("tables") + 2;
		tablesname = calloc(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.prefix);
		yytbl_hdr_init (&hdr, flex_version, tablesname);

		إذا (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	إذا (env.skelname && (skelfile = fopen (env.skelname, "r")) == عدم)
		lerr (_("can't open skeleton file %s"), env.skelname);

	إذا (strchr(ctrl.prefix, '[') || strchr(ctrl.prefix, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	إذا (env.did_outfilename)
		لي_directive_out (stdout, عدم, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	إذا( كولي_buf.elts)
		outn((حرف*) كولي_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	لي_directive_out(عدم, عدم, 0);

	/* User may want to set the scanner prototype */
	إذا (ctrl.yydecl != عدم) {
		out_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	إذا (ctrl.userinit != عدم) {
		out_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	إذا (ctrl.preaction != عدم) {
		out_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	إذا (ctrl.postaction != عدم) {
		out_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	out_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	إذا (userdef_buf.elts)
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
	إذا (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	إذا (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	إذا (env.backing_up_report) {
		ctrl.backing_up_file = fopen (backing_name, "w");
		إذا (ctrl.backing_up_file == عدم)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	وإلا
		ctrl.backing_up_file = عدم;

	إذا (ctrl.yymore_really_used == true)
		yymore_used = true;
	وإلا إذا (ctrl.yymore_really_used == false)
		yymore_used = false;

	إذا (ctrl.reject_really_used == true)
		reject = true;
	وإلا إذا (ctrl.reject_really_used == false)
		reject = false;

	إذا (env.performance_hint > 0) {
		إذا (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		وإلا إذا (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		إذا (env.performance_hint > 1) {
			إذا (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			إذا (yymore_used)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		إذا (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		إذا (variable_trailing_context_rules)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	إذا (reject)
		real_reject = true;

	إذا (variable_trailing_context_rules)
		reject = true;

	إذا ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		إذا (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		وإلا إذا (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		وإلا
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	إذا (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	وإلا
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	إذا (ctrl.useecs)
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
		بنية Buf tmpbuf;
		صحيح i;
		buf_init(&tmpbuf, حجم(حرف));
		لكل (i = 1; i <= lastsc; i++) {
			حرف *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = strlen(fmt) + strlen(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = malloc(strsz);
			إذا (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			حرر(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		out_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	إذا (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	إذا (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	إذا (extra_type != عدم)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	إذا (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		إذا (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	إذا (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	وإلا إذا (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	إذا (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	وإلا
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	إذا (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	وإلا
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	إذا (yymore_used)
		visible_define ( "M4_MODE_YYMORE_USED");
	وإلا
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	إذا (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	وإلا
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	إذا (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	وإلا
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	إذا (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	وإلا
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	إذا (variable_trailing_context_rules) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} وإلا {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	إذا (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	إذا (ctrl.reject_really_used)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	إذا (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	وإلا
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	إذا (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	إذا (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	وإلا إذا (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	وإلا إذا (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	وإلا
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	إذا (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	إذا (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	وإلا
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	إذا (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	إذا (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	وإلا
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	إذا (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	وإلا
		visible_define ( "M4_MODE_NO_GENTABLES");
	إذا (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	وإلا
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	إذا (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	إذا (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	إذا (ctrl.yyclass != عدم) {
		visible_define ( "M4_MODE_YYCLASS");
		out_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	إذا (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	إذا (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	إذا (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	وإلا
		visible_define ( "M4_MODE_NO_YYWRAP");

	إذا (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	إذا (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	إذا (is_default_backend()) {
		إذا (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} وإلا {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	إذا (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	إذا (ctrl.prefix != عدم)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.prefix);

	إذا (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	إذا (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	إذا (ctrl.yyterminate != عدم)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	إذا (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	إذا (ctrl.no_yy_تور_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	إذا (ctrl.no_yy_چرو_state)
		visible_define("M4_YY_NO_POP_STATE");
	إذا (ctrl.no_yy_كولي_state)
		visible_define("M4_YY_NO_TOP_STATE");
	إذا (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	إذا (ctrl.no_yy_scan_buffer)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	إذا (ctrl.no_yy_scan_bytes)
		visible_define("M4_YY_NO_SCAN_BYTES");
	إذا (ctrl.no_yy_scan_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	إذا (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	إذا (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	إذا (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	إذا (ctrl.no_yyget_text)
		visible_define("M4_YY_NO_GET_TEXT");
	إذا (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	إذا (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	إذا (ctrl.no_yyget_column)
		visible_define("M4_YY_NO_GET_COLUMN");
	إذا (ctrl.no_yyset_column)
		visible_define("M4_YY_NO_SET_COLUMN");
	إذا (ctrl.no_yyget_in)
		visible_define("M4_YY_NO_GET_IN");
	إذا (ctrl.no_yyset_in)
		visible_define("M4_YY_NO_SET_IN");
	إذا (ctrl.no_yyget_out)
		visible_define("M4_YY_NO_GET_OUT");
	إذا (ctrl.no_yyset_out)
		visible_define("M4_YY_NO_SET_OUT");
	إذا (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	إذا (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	إذا (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	إذا (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	إذا (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	إذا (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	إذا (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	إذا (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	إذا (ctrl.no_set_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	إذا (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	إذا (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	إذا (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	إذا (ctrl.تر_used)
		visible_define("M4_YY_STACK_USED");

	إذا (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	وإلا
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	out ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

فراغ set_up_initial_allocations (فراغ)
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
	rule_useful = allocate_array(current_max_rules, حجم(حرف));
	rule_has_nl = allocate_array(current_max_rules, حجم(حرف));

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
		حجم(اتحاد dfaacc_union));

	nultrans = عدم;
}


فراغ usage (فراغ)
{
	FILE   *f = stdout;

	إذا (!env.did_outfilename) {
		snprintf (outfile_path, حجم(outfile_path), outfile_template,
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
