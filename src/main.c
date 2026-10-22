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


#അന്തര്ഭാവ "flexdef.h"
#അന്തര്ഭാവ "version.h"
#അന്തര്ഭാവ "options.h"
#അന്തര്ഭാവ "tables.h"
#അന്തര്ഭാവ "parse.h"

സ്ഥിതം അക്ഷരം flex_version[] = FLEX_VERSION;

/* declare functions that have forward references */

ശൂന്യം flexinit(പൂർണ്ണസംഖ്യ, അക്ഷരം **);
ശൂന്യം readin(ശൂന്യം);
ശൂന്യം set_up_initial_allocations(ശൂന്യം);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
പൂർണ്ണസംഖ്യ     yymore_used, reject, real_reject, continued_action, in_rule;
പൂർണ്ണസംഖ്യ     datapos, dataline, linenum;
FILE   *skelfile = ശൂന്യ;
പൂർണ്ണസംഖ്യ     skel_ind = 0;
അക്ഷരം   *action_array;
പൂർണ്ണസംഖ്യ     action_size, defs1_offset, prolog_offset, action_offset,
	action_index;
അക്ഷരം   *infilename = ശൂന്യ;
അക്ഷരം   *extra_type = ശൂന്യ;
പൂർണ്ണസംഖ്യ     onestate[ONE_അട്ടി_SIZE], onesym[ONE_അട്ടി_SIZE];
പൂർണ്ണസംഖ്യ     onenext[ONE_അട്ടി_SIZE], onedef[ONE_അട്ടി_SIZE], onesp;
പൂർണ്ണസംഖ്യ     maximum_mns, current_mns, current_max_rules;
പൂർണ്ണസംഖ്യ     അക്കം_rules, അക്കം_eof_rules, default_rule, lastnfa;
പൂർണ്ണസംഖ്യ    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
പൂർണ്ണസംഖ്യ    *accptnum, *assoc_rule, *state_type;
പൂർണ്ണസംഖ്യ    *rule_type, *rule_linenum;
പൂർണ്ണസംഖ്യ     current_state_type;
bool    variable_trailing_context_rules;
പൂർണ്ണസംഖ്യ     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
പൂർണ്ണസംഖ്യ     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];
പൂർണ്ണസംഖ്യ     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
പൂർണ്ണസംഖ്യ     tecbck[CSIZE + 1];
പൂർണ്ണസംഖ്യ     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
അക്ഷരം   *scxclu, *sceof;
പൂർണ്ണസംഖ്യ     current_max_scs;
സ്ഥിരം അക്ഷരം **scname;
പൂർണ്ണസംഖ്യ     current_max_dfa_size, current_max_xpairs;
പൂർണ്ണസംഖ്യ     current_max_template_xpairs, current_max_dfas;
പൂർണ്ണസംഖ്യ     lastdfa, *nxt, *chk, *tnxt;
പൂർണ്ണസംഖ്യ    *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
സംഘം dfaacc_union *dfaacc;
പൂർണ്ണസംഖ്യ    *accsiz, *dhash, numas;
പൂർണ്ണസംഖ്യ     numsnpairs, jambase, jamstate;
പൂർണ്ണസംഖ്യ     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
പൂർണ്ണസംഖ്യ     current_maxccls, current_max_ccl_tbl_size;
unsigned അക്ഷരം   *ccltbl;
അക്ഷരം    nmstr[MAXLINE];
പൂർണ്ണസംഖ്യ     sectnum, nummt, hshcol, dfaeql, numeps, eps2, അക്കം_reallocs, nmval;
പൂർണ്ണസംഖ്യ     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
പൂർണ്ണസംഖ്യ     അക്കം_backing_up, bol_needed;
പൂർണ്ണസംഖ്യ     end_of_buffer_state;
അക്ഷരം  **നിവേശം_files;
പൂർണ്ണസംഖ്യ     അക്കം_നിവേശം_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
അക്ഷരം   *rule_useful, *rule_has_nl, *ccl_has_nl;
പൂർണ്ണസംഖ്യ     nlch = '\n';

bool    tablesext, tablesverify, gentables;
അക്ഷരം   *tablesfilename=0,*tablesname=0;
ഘടന yytbl_writer tableswr;
size_t footprint;

ഘടന ctrl_bundle_t ctrl;
ഘടന env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
അക്ഷരം   *program_name = "flex";

സ്ഥിതം സ്ഥിരം അക്ഷരം outfile_template[] = "lex.%s.%s";
സ്ഥിതം സ്ഥിരം അക്ഷരം *backing_name = "lex.backup";
സ്ഥിതം സ്ഥിരം അക്ഷരം tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
ബാഹ്യ FILE* yyout;

സ്ഥിതം അക്ഷരം outfile_path[MAXLINE];
സ്ഥിതം പൂർണ്ണസംഖ്യ outfile_created = 0;
സ്ഥിതം പൂർണ്ണസംഖ്യ _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
സ്ഥിരം അക്ഷരം *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
സ്ഥിരം അക്ഷരം *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
സ്ഥിതം പൂർണ്ണസംഖ്യ preproc_level = 1000;

പൂർണ്ണസംഖ്യ flex_main (പൂർണ്ണസംഖ്യ argc, അക്ഷരം *argv[]);

പൂർണ്ണസംഖ്യ flex_main (പൂർണ്ണസംഖ്യ argc, അക്ഷരം *argv[])
{
	പൂർണ്ണസംഖ്യ     i, exit_status, child_status;
	പൂർണ്ണസംഖ്യ	did_eof_rule = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_status = setjmp (flex_main_jmp_buf);
	എങ്കിൽ (exit_status){
		എങ്കിൽ (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		ആകുമ്പോൾ (wait(&child_status) > 0){
			എങ്കിൽ (!WIFEXITED (child_status)
			    || WEXITSTATUS (child_status) != 0){
				/* report an error of a child
				 */
				എങ്കിൽ( exit_status <= 1 )
					exit_status = 2;

			}
		}
		തിരികെ exit_status - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	വേണ്ടി (i = 1; i <= അക്കം_rules; ++i)
		എങ്കിൽ (!rule_useful[i] && i != default_rule)
			വരി_warning (_("rule cannot be matched"),
				      rule_linenum[i]);

	എങ്കിൽ (ctrl.spprdflt && !reject && rule_useful[default_rule])
		വരി_warning (_
			      ("-s option given but default rule can be matched"),
			      rule_linenum[default_rule]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	എങ്കിൽ (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	അല്ലെങ്കിൽ {
		visible_define ( "M4_MODE_NO_NULTRANS");
		എങ്കിൽ (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		അല്ലെങ്കിൽ
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		എങ്കിൽ (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		അല്ലെങ്കിൽ
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	out ("\n");

	comment("START of Flex-generated definitions\n");
	out_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", അക്കം_rules);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", അക്കം_rules + 1);
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

	വരി_directive_out (stdout, ശൂന്യ, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	out (&action_array[prolog_offset]);

	വരി_directive_out (stdout, ശൂന്യ, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	out (&action_array[action_offset]);

	വരി_directive_out (stdout, ശൂന്യ, linenum);

	/* generate cases for any missing EOF rules */
	വേണ്ടി (i = 1; i <= lastsc; ++i)
		എങ്കിൽ (!sceof[i]) {
			out_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			out ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_rule = true;
		}

	എങ്കിൽ (did_eof_rule) {
		out ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	വരി_directive_out (stdout, infilename, linenum);

	എങ്കിൽ (sectnum == 3) {
		OUT_BEGIN_CODE ();
                എങ്കിൽ (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(ശൂന്യം) flexscan ();	/* copy remainder of input to output */
                എങ്കിൽ (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		OUT_END_CODE ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	തിരികെ 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
പൂർണ്ണസംഖ്യ പ്രധാന (പൂർണ്ണസംഖ്യ argc, അക്ഷരം *argv[])
{
#എങ്കിൽ defined(ENABLE_NLS) && ENABLE_NLS
#എങ്കിൽ HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif
#endif

	തിരികെ flex_main (argc, argv);
}

/* Set up the output filter chain. */

ശൂന്യം initialize_output_filters(ശൂന്യം)
{
	സ്ഥിരം അക്ഷരം * m4 = ശൂന്യ;

	output_chain = filter_create_int(ശൂന്യ, filter_tee_header, env.headerfilename);
	എങ്കിൽ ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (അക്ഷരം *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, ശൂന്യ);

	/* For debugging, only run the requested number of filters. */
	എങ്കിൽ (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

ശൂന്യം check_options (ശൂന്യം)
{
	പൂർണ്ണസംഖ്യ     i;

	എങ്കിൽ (ctrl.lex_compat) {
		എങ്കിൽ (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		എങ്കിൽ (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		എങ്കിൽ (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#എങ്കിൽ 0
	/* This makes no sense whatsoever. I'm removing it. */
	എങ്കിൽ (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_used = true;
#endif

	എങ്കിൽ (ctrl.csize == trit_unspecified) {
		എങ്കിൽ ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		അല്ലെങ്കിൽ
			ctrl.csize = CSIZE;
	}

	എങ്കിൽ (ctrl.interactive == trit_unspecified) {
		എങ്കിൽ (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		അല്ലെങ്കിൽ
			ctrl.interactive = trit_true;
	}

	എങ്കിൽ (ctrl.fulltbl || ctrl.fullspd) {
		എങ്കിൽ (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		എങ്കിൽ (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		എങ്കിൽ (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		എങ്കിൽ (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	എങ്കിൽ (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	എങ്കിൽ (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	എങ്കിൽ (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	എങ്കിൽ (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	എങ്കിൽ (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		വേണ്ടി (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	അല്ലെങ്കിൽ {
		/* Put everything in its own equivalence class. */
		വേണ്ടി (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	എങ്കിൽ (!env.use_stdout) {
		FILE   *prev_stdout;

		എങ്കിൽ (!env.did_outfilename) {
			snprintf (outfile_path, വലുപ്പം(outfile_path), outfile_template,
				  ctrl.prefix, suffix());

			env.outfilename = outfile_path;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		എങ്കിൽ (prev_stdout == ശൂന്യ)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

ശൂന്യം flexend (പൂർണ്ണസംഖ്യ exit_status)
{
	സ്ഥിതം പൂർണ്ണസംഖ്യ called_before = -1;	/* prevent infinite recursion. */
	പൂർണ്ണസംഖ്യ     tblsiz;

	എങ്കിൽ (++called_before)
		FLEX_EXIT (exit_status);

	എങ്കിൽ (ctrl.yyclass != ശൂന്യ && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	എങ്കിൽ (skelfile != ശൂന്യ) {
		എങ്കിൽ (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		അല്ലെങ്കിൽ എങ്കിൽ (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	എങ്കിൽ (exit_status != 0 && outfile_created) {
		എങ്കിൽ (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		അല്ലെങ്കിൽ എങ്കിൽ ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		അല്ലെങ്കിൽ എങ്കിൽ (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	എങ്കിൽ (env.backing_up_report && ctrl.backing_up_file) {
		എങ്കിൽ (അക്കം_backing_up == 0)
			fprintf (ctrl.backing_up_file, _("No backing up.\n"));
		അല്ലെങ്കിൽ എങ്കിൽ (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_up_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 അക്കം_backing_up);
		അല്ലെങ്കിൽ
			fprintf (ctrl.backing_up_file,
				 _("Compressed tables always back up.\n"));

		എങ്കിൽ (ferror (ctrl.backing_up_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		അല്ലെങ്കിൽ എങ്കിൽ (fclose (ctrl.backing_up_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	എങ്കിൽ (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 program_name, flex_version);

		fprintf (stderr, _("  scanner options: -"));

		എങ്കിൽ (ctrl.C_plus_plus)
			putc ('+', stderr);
		എങ്കിൽ (env.backing_up_report)
			putc ('b', stderr);
		എങ്കിൽ (ctrl.ddebug)
			putc ('d', stderr);
		എങ്കിൽ (sf_case_ins())
			putc ('i', stderr);
		എങ്കിൽ (ctrl.lex_compat)
			putc ('l', stderr);
		എങ്കിൽ (ctrl.posix_compat)
			putc ('X', stderr);
		എങ്കിൽ (env.performance_hint > 0)
			putc ('p', stderr);
		എങ്കിൽ (env.performance_hint > 1)
			putc ('p', stderr);
		എങ്കിൽ (ctrl.spprdflt)
			putc ('s', stderr);
		എങ്കിൽ (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        എങ്കിൽ (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        എങ്കിൽ (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		എങ്കിൽ (env.use_stdout)
			putc ('t', stderr);
		എങ്കിൽ (env.printstats)
			putc ('v', stderr);	/* always true! */
		എങ്കിൽ (env.nowarn)
			putc ('w', stderr);
		എങ്കിൽ (ctrl.interactive == trit_false)
			putc ('B', stderr);
		എങ്കിൽ (ctrl.interactive == trit_true)
			putc ('I', stderr);
		എങ്കിൽ (!ctrl.gen_വരി_dirs)
			putc ('L', stderr);
		എങ്കിൽ (env.trace)
			putc ('T', stderr);

		എങ്കിൽ (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		എങ്കിൽ (ctrl.csize == 128)
			putc ('7', stderr);
		അല്ലെങ്കിൽ
			putc ('8', stderr);

		fprintf (stderr, " -C");

		എങ്കിൽ (ctrl.long_align)
			putc ('a', stderr);
		എങ്കിൽ (ctrl.fulltbl)
			putc ('f', stderr);
		എങ്കിൽ (ctrl.fullspd)
			putc ('F', stderr);
		എങ്കിൽ (ctrl.useecs)
			putc ('e', stderr);
		എങ്കിൽ (ctrl.usemecs)
			putc ('m', stderr);
		എങ്കിൽ (ctrl.use_read)
			putc ('r', stderr);

		എങ്കിൽ (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		എങ്കിൽ (env.skelname != ശൂന്യ)
			fprintf (stderr, " -S%s", env.skelname);

		എങ്കിൽ (strcmp (ctrl.prefix, "yy"))
			fprintf (stderr, " -P%s", ctrl.prefix);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 അക്കം_rules + അക്കം_eof_rules -
			 1 /* - 1 for def. rule */ );

		എങ്കിൽ (അക്കം_backing_up == 0)
			fprintf (stderr, _("  No backing up\n"));
		അല്ലെങ്കിൽ എങ്കിൽ (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 അക്കം_backing_up);
		അല്ലെങ്കിൽ
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		എങ്കിൽ (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		എങ്കിൽ (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		അല്ലെങ്കിൽ
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

		എങ്കിൽ (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		അല്ലെങ്കിൽ {
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

		എങ്കിൽ (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		എങ്കിൽ (ctrl.usemecs) {
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
			 അക്കം_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_status);
}


/* flexinit - initialize flex */

ശൂന്യം flexinit (പൂർണ്ണസംഖ്യ argc, അക്ഷരം **argv)
{
	പൂർണ്ണസംഖ്യ     i, sawcmpflag, rv, optind;
	അക്ഷരം   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', വലുപ്പം(ctrl));
	syntaxerror = false;
	yymore_used = continued_action = false;
	in_rule = reject = false;
	ctrl.yymore_really_used = ctrl.reject_really_used = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_വരി_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.prefix = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = ശൂന്യ;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_size = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_size);
	defs1_offset = prolog_offset = action_offset = action_index = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, വലുപ്പം (അക്ഷരം));	/* one long string */
	buf_init (&മുകൾ_buf, വലുപ്പം (അക്ഷരം));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	program_name = argv[0];

	എങ്കിൽ (program_name != ശൂന്യ &&
	    program_name[strlen (program_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	എങ്കിൽ (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	ആകുമ്പോൾ ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		എങ്കിൽ (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 program_name);
			FLEX_EXIT (1);
		}

		തിരഞ്ഞെടുപ്പ് ((എണ്ണൽ flexopt_flag_t) rv) {
		    അവസ്ഥ OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_BATCH:
			ctrl.interactive = trit_false;
			നിർത്തുക;

		    അവസ്ഥ OPT_BACKUP:
			env.backing_up_report = trit_true;
			നിർത്തുക;

		    അവസ്ഥ OPT_BACKUP_FILE:
			env.backing_up_report = true;
                        backing_name = arg;
			നിർത്തുക;

		    അവസ്ഥ OPT_DONOTHING:
			നിർത്തുക;

		    അവസ്ഥ OPT_COMPRESSION:
			എങ്കിൽ (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			വേണ്ടി (i = 0; arg && arg[i] != '\0'; i++)
				തിരഞ്ഞെടുപ്പ് (arg[i]) {
				    അവസ്ഥ 'a':
					ctrl.long_align = true;
					നിർത്തുക;

				    അവസ്ഥ 'e':
					ctrl.useecs = true;
					നിർത്തുക;

				    അവസ്ഥ 'F':
					ctrl.fullspd = true;
					നിർത്തുക;

				    അവസ്ഥ 'f':
					ctrl.fulltbl = true;
					നിർത്തുക;

				    അവസ്ഥ 'm':
					ctrl.usemecs = true;
					നിർത്തുക;

				    അവസ്ഥ 'r':
					ctrl.use_read = true;
					നിർത്തുക;

				    സ്ഥിരസ്ഥിതി:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					നിർത്തുക;
				}
			നിർത്തുക;

		    അവസ്ഥ OPT_DEBUG:
			ctrl.ddebug = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_DEBUG:
			ctrl.ddebug = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_FULL:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    അവസ്ഥ OPT_INTERACTIVE:
			ctrl.interactive = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_CASE_INSENSITIVE:
			sf_set_case_ins(true);
			നിർത്തുക;

		    അവസ്ഥ OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_PREPROC_LEVEL:
			preproc_level = (പൂർണ്ണസംഖ്യ) strtol(arg,ശൂന്യ,0);
			നിർത്തുക;

		    അവസ്ഥ OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_വരി:
			ctrl.gen_വരി_dirs = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			നിർത്തുക;

		    അവസ്ഥ OPT_PREFIX:
			ctrl.prefix = arg;
			നിർത്തുക;

		    അവസ്ഥ OPT_PERF_REPORT:
			++env.performance_hint;
			നിർത്തുക;

		    അവസ്ഥ OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_REENTRANT:
			ctrl.reentrant = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_SKEL:
			env.skelname = arg;
			നിർത്തുക;

		    അവസ്ഥ OPT_DEFAULT:
			ctrl.spprdflt = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_STDOUT:
			env.use_stdout = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			നിർത്തുക;

		    അവസ്ഥ OPT_TABLES_VERIFY:
			tablesverify = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_TRACE:
			env.trace = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_VERBOSE:
			env.printstats = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_VERSION:
			printf ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_version);
			FLEX_EXIT (0);

		    അവസ്ഥ OPT_WARN:
			env.nowarn = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_WARN:
			env.nowarn = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_7BIT:
			ctrl.csize = 128;
			നിർത്തുക;

		    അവസ്ഥ OPT_8BIT:
			ctrl.csize = CSIZE;
			നിർത്തുക;

		    അവസ്ഥ OPT_ALIGN:
			ctrl.long_align = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_ALIGN:
			ctrl.long_align = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_ARRAY:
			ctrl.yytext_is_array = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_POINTER:
			ctrl.yytext_is_array = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_ECS:
			ctrl.useecs = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_ECS:
			ctrl.useecs = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_EMIT:
			ctrl.emit = arg;
			നിർത്തുക;

		    അവസ്ഥ OPT_HEADER_FILE:
			env.headerfilename = arg;
			നിർത്തുക;

		    അവസ്ഥ OPT_META_ECS:
			ctrl.usemecs = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_META_ECS:
			ctrl.usemecs = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    അക്ഷരം   *def;
			    അക്ഷരം buf2[4096];

			    വേണ്ടി (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    തുടരുക;
			    എങ്കിൽ (*def == '\0')
				    def = "1";

			    snprintf(buf2, വലുപ്പം(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    നിർത്തുക;

		    അവസ്ഥ OPT_READ:
			ctrl.use_read = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_അട്ടി:
			ctrl.അട്ടി_used = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_STDINIT:
			ctrl.do_stdinit = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_YYCLASS:
			ctrl.yyclass = arg;
			നിർത്തുക;

		    അവസ്ഥ OPT_YYLINENO:
			ctrl.do_yylineno = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_YYWRAP:
			ctrl.do_yywrap = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_YYMORE:
			ctrl.yymore_really_used = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_YYMORE:
			ctrl.yymore_really_used = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_REJECT:
			ctrl.reject_really_used = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_REJECT:
			ctrl.reject_really_used = false;
			നിർത്തുക;

		    അവസ്ഥ OPT_NO_YY_തള്ളുക_STATE:
			ctrl.no_yy_തള്ളുക_state = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YY_എടുക്കുക_STATE:
			ctrl.no_yy_എടുക്കുക_state = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YY_മുകൾ_STATE:
			ctrl.no_yy_മുകൾ_state = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YY_SCAN_BUFFER:
			ctrl.no_yy_scan_buffer = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YY_SCAN_BYTES:
			ctrl.no_yy_scan_bytes = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YY_SCAN_STRING:
			ctrl.no_yy_scan_string = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYGET_TEXT:
			ctrl.no_yyget_text = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYGET_COLUMN:
			ctrl.no_yyget_column = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYSET_COLUMN:
			ctrl.no_yyset_column = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYGET_IN:
			ctrl.no_yyget_in = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYSET_IN:
			ctrl.no_yyset_in = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYGET_OUT:
			ctrl.no_yyget_out = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYSET_OUT:
			ctrl.no_yyset_out = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			നിർത്തുക;
		    അവസ്ഥ OPT_NO_YYSET_DEBUG:
			ctrl.no_set_debug = true;
			നിർത്തുക;

		    അവസ്ഥ OPT_HEX:
			env.trace_hex = true;
                        നിർത്തുക;
		    അവസ്ഥ OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        നിർത്തുക;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	അക്കം_നിവേശം_files = argc - optind;
	നിവേശം_files = argv + optind;
	set_നിവേശം_file (അക്കം_നിവേശം_files > 0 ? നിവേശം_files[0] : ശൂന്യ);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	അക്കം_rules = അക്കം_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = അക്കം_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	അക്കം_backing_up = onesp = numprots = 0;
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

ശൂന്യം readin (ശൂന്യം)
{
	അക്ഷരം buf[256];

	വരി_directive_out(ശൂന്യ, infilename, linenum);

	എങ്കിൽ (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
		flexend (1);
	}

	എങ്കിൽ (syntaxerror)
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

	എങ്കിൽ (tablesext)
		gentables = false;

	എങ്കിൽ (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	എങ്കിൽ (tablesext) {
		FILE   *tablesout;
		ഘടന yytbl_hdr hdr;
		അക്ഷരം   *pname = 0;
		size_t  nbytes = 0;

		എങ്കിൽ (!tablesfilename) {
			nbytes = strlen (ctrl.prefix) + strlen (tablesfile_template) + 2;
			tablesfilename = pname = calloc(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.prefix);
		}

		എങ്കിൽ ((tablesout = fopen (tablesfilename, "w")) == ശൂന്യ)
			lerr (_("could not create %s"), tablesfilename);
		സ്വതന്ത്രം(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = strlen (ctrl.prefix) + strlen ("tables") + 2;
		tablesname = calloc(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.prefix);
		yytbl_hdr_init (&hdr, flex_version, tablesname);

		എങ്കിൽ (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	എങ്കിൽ (env.skelname && (skelfile = fopen (env.skelname, "r")) == ശൂന്യ)
		lerr (_("can't open skeleton file %s"), env.skelname);

	എങ്കിൽ (strchr(ctrl.prefix, '[') || strchr(ctrl.prefix, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	എങ്കിൽ (env.did_outfilename)
		വരി_directive_out (stdout, ശൂന്യ, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	എങ്കിൽ( മുകൾ_buf.elts)
		outn((അക്ഷരം*) മുകൾ_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	വരി_directive_out(ശൂന്യ, ശൂന്യ, 0);

	/* User may want to set the scanner prototype */
	എങ്കിൽ (ctrl.yydecl != ശൂന്യ) {
		out_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	എങ്കിൽ (ctrl.userinit != ശൂന്യ) {
		out_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	എങ്കിൽ (ctrl.preaction != ശൂന്യ) {
		out_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	എങ്കിൽ (ctrl.postaction != ശൂന്യ) {
		out_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	out_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	എങ്കിൽ (userdef_buf.elts)
		outn ((അക്ഷരം *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	എങ്കിൽ (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	എങ്കിൽ (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	എങ്കിൽ (env.backing_up_report) {
		ctrl.backing_up_file = fopen (backing_name, "w");
		എങ്കിൽ (ctrl.backing_up_file == ശൂന്യ)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	അല്ലെങ്കിൽ
		ctrl.backing_up_file = ശൂന്യ;

	എങ്കിൽ (ctrl.yymore_really_used == true)
		yymore_used = true;
	അല്ലെങ്കിൽ എങ്കിൽ (ctrl.yymore_really_used == false)
		yymore_used = false;

	എങ്കിൽ (ctrl.reject_really_used == true)
		reject = true;
	അല്ലെങ്കിൽ എങ്കിൽ (ctrl.reject_really_used == false)
		reject = false;

	എങ്കിൽ (env.performance_hint > 0) {
		എങ്കിൽ (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		അല്ലെങ്കിൽ എങ്കിൽ (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		എങ്കിൽ (env.performance_hint > 1) {
			എങ്കിൽ (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			എങ്കിൽ (yymore_used)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		എങ്കിൽ (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		എങ്കിൽ (variable_trailing_context_rules)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	എങ്കിൽ (reject)
		real_reject = true;

	എങ്കിൽ (variable_trailing_context_rules)
		reject = true;

	എങ്കിൽ ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		എങ്കിൽ (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		അല്ലെങ്കിൽ എങ്കിൽ (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		അല്ലെങ്കിൽ
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	എങ്കിൽ (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	അല്ലെങ്കിൽ
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	എങ്കിൽ (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, വലുപ്പം(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		ഘടന Buf tmpbuf;
		പൂർണ്ണസംഖ്യ i;
		buf_init(&tmpbuf, വലുപ്പം(അക്ഷരം));
		വേണ്ടി (i = 1; i <= lastsc; i++) {
			അക്ഷരം *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = strlen(fmt) + strlen(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = malloc(strsz);
			എങ്കിൽ (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			സ്വതന്ത്രം(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		out_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	എങ്കിൽ (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	എങ്കിൽ (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	എങ്കിൽ (extra_type != ശൂന്യ)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	എങ്കിൽ (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		എങ്കിൽ (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	എങ്കിൽ (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	അല്ലെങ്കിൽ എങ്കിൽ (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	എങ്കിൽ (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	എങ്കിൽ (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	എങ്കിൽ (yymore_used)
		visible_define ( "M4_MODE_YYMORE_USED");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	എങ്കിൽ (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	എങ്കിൽ (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	എങ്കിൽ (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	എങ്കിൽ (variable_trailing_context_rules) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} അല്ലെങ്കിൽ {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	എങ്കിൽ (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	എങ്കിൽ (ctrl.reject_really_used)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	എങ്കിൽ (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	എങ്കിൽ (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	എങ്കിൽ (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	അല്ലെങ്കിൽ എങ്കിൽ (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	അല്ലെങ്കിൽ എങ്കിൽ (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	അല്ലെങ്കിൽ
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	എങ്കിൽ (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	എങ്കിൽ (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	എങ്കിൽ (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	എങ്കിൽ (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	എങ്കിൽ (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_GENTABLES");
	എങ്കിൽ (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	എങ്കിൽ (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	എങ്കിൽ (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	എങ്കിൽ (ctrl.yyclass != ശൂന്യ) {
		visible_define ( "M4_MODE_YYCLASS");
		out_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	എങ്കിൽ (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	എങ്കിൽ (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	എങ്കിൽ (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_YYWRAP");

	എങ്കിൽ (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	എങ്കിൽ (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	എങ്കിൽ (is_default_backend()) {
		എങ്കിൽ (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} അല്ലെങ്കിൽ {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	എങ്കിൽ (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	എങ്കിൽ (ctrl.prefix != ശൂന്യ)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.prefix);

	എങ്കിൽ (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	എങ്കിൽ (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	എങ്കിൽ (ctrl.yyterminate != ശൂന്യ)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	എങ്കിൽ (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	എങ്കിൽ (ctrl.no_yy_തള്ളുക_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	എങ്കിൽ (ctrl.no_yy_എടുക്കുക_state)
		visible_define("M4_YY_NO_POP_STATE");
	എങ്കിൽ (ctrl.no_yy_മുകൾ_state)
		visible_define("M4_YY_NO_TOP_STATE");
	എങ്കിൽ (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	എങ്കിൽ (ctrl.no_yy_scan_buffer)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	എങ്കിൽ (ctrl.no_yy_scan_bytes)
		visible_define("M4_YY_NO_SCAN_BYTES");
	എങ്കിൽ (ctrl.no_yy_scan_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	എങ്കിൽ (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	എങ്കിൽ (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	എങ്കിൽ (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	എങ്കിൽ (ctrl.no_yyget_text)
		visible_define("M4_YY_NO_GET_TEXT");
	എങ്കിൽ (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	എങ്കിൽ (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	എങ്കിൽ (ctrl.no_yyget_column)
		visible_define("M4_YY_NO_GET_COLUMN");
	എങ്കിൽ (ctrl.no_yyset_column)
		visible_define("M4_YY_NO_SET_COLUMN");
	എങ്കിൽ (ctrl.no_yyget_in)
		visible_define("M4_YY_NO_GET_IN");
	എങ്കിൽ (ctrl.no_yyset_in)
		visible_define("M4_YY_NO_SET_IN");
	എങ്കിൽ (ctrl.no_yyget_out)
		visible_define("M4_YY_NO_GET_OUT");
	എങ്കിൽ (ctrl.no_yyset_out)
		visible_define("M4_YY_NO_SET_OUT");
	എങ്കിൽ (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	എങ്കിൽ (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	എങ്കിൽ (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	എങ്കിൽ (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	എങ്കിൽ (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	എങ്കിൽ (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	എങ്കിൽ (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	എങ്കിൽ (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	എങ്കിൽ (ctrl.no_set_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	എങ്കിൽ (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	എങ്കിൽ (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	എങ്കിൽ (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	എങ്കിൽ (ctrl.അട്ടി_used)
		visible_define("M4_YY_STACK_USED");

	എങ്കിൽ (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	അല്ലെങ്കിൽ
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	out ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

ശൂന്യം set_up_initial_allocations (ശൂന്യം)
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
	rule_useful = allocate_array(current_max_rules, വലുപ്പം(അക്ഷരം));
	rule_has_nl = allocate_array(current_max_rules, വലുപ്പം(അക്ഷരം));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, വലുപ്പം(അക്ഷരം));
	sceof = allocate_array(current_max_scs, വലുപ്പം(അക്ഷരം));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, വലുപ്പം(അക്ഷരം));

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
		വലുപ്പം(സംഘം dfaacc_union));

	nultrans = ശൂന്യ;
}


ശൂന്യം usage (ശൂന്യം)
{
	FILE   *f = stdout;

	എങ്കിൽ (!env.did_outfilename) {
		snprintf (outfile_path, വലുപ്പം(outfile_path), outfile_template,
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
