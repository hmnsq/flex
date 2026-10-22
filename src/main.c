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


#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "version.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "options.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tables.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "parse.h"

ਸਥਿਰ ਅੱਖਰ flex_ਸੰਸਕਰਣ[] = FLEX_ਸੰਸਕਰਣ;

/* declare functions that have forward references */

ਖਾਲੀ flexinit(ਪੂਰਨ, ਅੱਖਰ **);
ਖਾਲੀ readin(ਖਾਲੀ);
ਖਾਲੀ ਸੈੱਟ_ਉੱਪਰ_initial_allocations(ਖਾਲੀ);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
ਪੂਰਨ     yymore_ਵਰਤਿਆ, reject, real_reject, continued_action, ਵਿੱਚ_ਨਿਯਮ;
ਪੂਰਨ     datapos, dataline, linenum;
FILE   *skelfile = ਨਿਰਾ;
ਪੂਰਨ     skel_ind = 0;
ਅੱਖਰ   *action_array;
ਪੂਰਨ     action_ਮਾਪ, defs1_ਵਿੱਥ, prolog_ਵਿੱਥ, action_ਵਿੱਥ,
	action_ਸੂਚਕਾਂਕ;
ਅੱਖਰ   *infilename = ਨਿਰਾ;
ਅੱਖਰ   *extra_type = ਨਿਰਾ;
ਪੂਰਨ     onestate[ONE_ਢੇਰ_ਮਾਪ], onesym[ONE_ਢੇਰ_ਮਾਪ];
ਪੂਰਨ     onenext[ONE_ਢੇਰ_ਮਾਪ], onedef[ONE_ਢੇਰ_ਮਾਪ], onesp;
ਪੂਰਨ     ਵੱਧ_ਤੋਂ_ਵੱਧ_mns, current_mns, current_max_ਨਿਯਮਾਂ;
ਪੂਰਨ     ਅੰਕ_ਨਿਯਮਾਂ, ਅੰਕ_eof_ਨਿਯਮਾਂ, default_ਨਿਯਮ, lastnfa;
ਪੂਰਨ    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
ਪੂਰਨ    *accptnum, *assoc_ਨਿਯਮ, *state_type;
ਪੂਰਨ    *ਨਿਯਮ_type, *ਨਿਯਮ_linenum;
ਪੂਰਨ     current_state_type;
bool    variable_trailing_context_ਨਿਯਮਾਂ;
ਪੂਰਨ     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
ਪੂਰਨ     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_ਮਾਪ];
ਪੂਰਨ     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
ਪੂਰਨ     tecbck[CSIZE + 1];
ਪੂਰਨ     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
ਅੱਖਰ   *scxclu, *sceof;
ਪੂਰਨ     current_max_scs;
ਅਚਲ ਅੱਖਰ **scname;
ਪੂਰਨ     current_max_dfa_ਮਾਪ, current_max_xpairs;
ਪੂਰਨ     current_max_template_xpairs, current_max_dfas;
ਪੂਰਨ     lastdfa, *nxt, *chk, *tnxt;
ਪੂਰਨ    *ਅਧਾਰ, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
ਸੰਘ dfaacc_union *dfaacc;
ਪੂਰਨ    *accsiz, *dhash, numas;
ਪੂਰਨ     numsnpairs, jambase, jamstate;
ਪੂਰਨ     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
ਪੂਰਨ     current_maxccls, current_max_ccl_tbl_ਮਾਪ;
ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ   *ccltbl;
ਅੱਖਰ    nmstr[MAXLINE];
ਪੂਰਨ     sectnum, nummt, hshcol, dfaeql, numeps, eps2, ਅੰਕ_reallocs, nmval;
ਪੂਰਨ     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
ਪੂਰਨ     ਅੰਕ_backing_ਉੱਪਰ, bol_needed;
ਪੂਰਨ     ਸਿਰਾ_ਦਾ_ਬਫਰ_state;
ਅੱਖਰ  **ਨਿਵੇਸ਼_files;
ਪੂਰਨ     ਅੰਕ_ਨਿਵੇਸ਼_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
ਅੱਖਰ   *ਨਿਯਮ_useful, *ਨਿਯਮ_has_nl, *ccl_has_nl;
ਪੂਰਨ     nlch = '\n';

bool    tablesext, tablesverify, gentables;
ਅੱਖਰ   *tablesfilename=0,*tablesname=0;
ਬਣਤਰ yytbl_writer tableswr;
size_t footprint;

ਬਣਤਰ ctrl_bundle_t ctrl;
ਬਣਤਰ env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
ਅੱਖਰ   *ਪ੍ਰੋਗਰਾਮ_name = "flex";

ਸਥਿਰ ਅਚਲ ਅੱਖਰ outfile_template[] = "lex.%s.%s";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ *backing_name = "lex.backup";
ਸਥਿਰ ਅਚਲ ਅੱਖਰ tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
ਬਾਹਰੀ FILE* yyout;

ਸਥਿਰ ਅੱਖਰ outfile_ਰਸਤਾ[MAXLINE];
ਸਥਿਰ ਪੂਰਨ outfile_created = 0;
ਸਥਿਰ ਪੂਰਨ _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
ਅਚਲ ਅੱਖਰ *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
ਅਚਲ ਅੱਖਰ *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
ਸਥਿਰ ਪੂਰਨ preproc_level = 1000;

ਪੂਰਨ flex_main (ਪੂਰਨ argc, ਅੱਖਰ *argv[]);

ਪੂਰਨ flex_main (ਪੂਰਨ argc, ਅੱਖਰ *argv[])
{
	ਪੂਰਨ     i, exit_ਸਥਿਤੀ, ਬੱਚਾ_ਸਥਿਤੀ;
	ਪੂਰਨ	did_eof_ਨਿਯਮ = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_ਸਥਿਤੀ = setjmp (flex_main_jmp_buf);
	ਜੇ (exit_ਸਥਿਤੀ){
		ਜੇ (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		ਜਦੋਂ (wait(&ਬੱਚਾ_ਸਥਿਤੀ) > 0){
			ਜੇ (!WIFEXITED (ਬੱਚਾ_ਸਥਿਤੀ)
			    || WEXITSTATUS (ਬੱਚਾ_ਸਥਿਤੀ) != 0){
				/* report an error of a child
				 */
				ਜੇ( exit_ਸਥਿਤੀ <= 1 )
					exit_ਸਥਿਤੀ = 2;

			}
		}
		ਵਾਪਸ exit_ਸਥਿਤੀ - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	ਲਈ (i = 1; i <= ਅੰਕ_ਨਿਯਮਾਂ; ++i)
		ਜੇ (!ਨਿਯਮ_useful[i] && i != default_ਨਿਯਮ)
			ਸਤਰ_warning (_("rule cannot be matched"),
				      ਨਿਯਮ_linenum[i]);

	ਜੇ (ctrl.spprdflt && !reject && ਨਿਯਮ_useful[default_ਨਿਯਮ])
		ਸਤਰ_warning (_
			      ("-s option given but default rule can be matched"),
			      ਨਿਯਮ_linenum[default_ਨਿਯਮ]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	ਜੇ (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	ਨਹੀਂਤਾਂ {
		visible_define ( "M4_MODE_NO_NULTRANS");
		ਜੇ (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		ਨਹੀਂਤਾਂ
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		ਜੇ (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		ਨਹੀਂਤਾਂ
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	ਬਾਹਰਲਾ ("\n");

	comment("START of Flex-generated definitions\n");
	ਬਾਹਰਲਾ_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", ਅੰਕ_ਨਿਯਮਾਂ);
	ਬਾਹਰਲਾ_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", ਅੰਕ_ਨਿਯਮਾਂ + 1);
	ਬਾਹਰਲਾ_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_JAMBASE", jambase);
	ਬਾਹਰਲਾ_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_JAMSTATE", jamstate);
	ਬਾਹਰਲਾ_str_dec ("M4_HOOK_CONST_DEFINE_BYTE(%s, %d)", "YY_NUL_EC", NUL_ec);
	/* Need to define the transet type as a size large
	 * enough to hold the biggest offset.
	 */
	ਬਾਹਰਲਾ_str ("M4_HOOK_SET_OFFSET_TYPE(%s)", optimize_pack(tblend + numecs + 1)->name);
	comment("END of Flex-generated definitions\n");

	skelout (true);		/* %% [2.0] - tables get dumped here */

	/* Generate the C state transition tables from the DFA. */
	make_tables ();

	skelout (true);		/* %% [3.0] - mode-dependent static declarations get dumped here */

	ਬਾਹਰਲਾ (&action_array[defs1_ਵਿੱਥ]);

	ਸਤਰ_directive_ਬਾਹਰਲਾ (stdout, ਨਿਰਾ, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	ਬਾਹਰਲਾ (&action_array[prolog_ਵਿੱਥ]);

	ਸਤਰ_directive_ਬਾਹਰਲਾ (stdout, ਨਿਰਾ, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	ਬਾਹਰਲਾ (&action_array[action_ਵਿੱਥ]);

	ਸਤਰ_directive_ਬਾਹਰਲਾ (stdout, ਨਿਰਾ, linenum);

	/* generate cases for any missing EOF rules */
	ਲਈ (i = 1; i <= lastsc; ++i)
		ਜੇ (!sceof[i]) {
			ਬਾਹਰਲਾ_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			ਬਾਹਰਲਾ ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_ਨਿਯਮ = true;
		}

	ਜੇ (did_eof_ਨਿਯਮ) {
		ਬਾਹਰਲਾ ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	ਸਤਰ_directive_ਬਾਹਰਲਾ (stdout, infilename, linenum);

	ਜੇ (sectnum == 3) {
		ਬਾਹਰਲਾ_BEGIN_ਕੋਡ ();
                ਜੇ (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(ਖਾਲੀ) flexscan ();	/* copy remainder of input to output */
                ਜੇ (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		ਬਾਹਰਲਾ_ਸਿਰਾ_ਕੋਡ ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	ਵਾਪਸ 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
ਪੂਰਨ ਮੁੱਖ (ਪੂਰਨ argc, ਅੱਖਰ *argv[])
{
#ਜੇ defined(ENABLE_NLS) && ENABLE_NLS
#ਜੇ HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

	ਵਾਪਸ flex_main (argc, argv);
}

/* Set up the output filter chain. */

ਖਾਲੀ initialize_output_filters(ਖਾਲੀ)
{
	ਅਚਲ ਅੱਖਰ * m4 = ਨਿਰਾ;

	output_chain = filter_create_int(ਨਿਰਾ, filter_tee_ਸਿਰਲੇਖ, env.headerfilename);
	ਜੇ ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (ਅੱਖਰ *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, ਨਿਰਾ);

	/* For debugging, only run the requested number of filters. */
	ਜੇ (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

ਖਾਲੀ check_options (ਖਾਲੀ)
{
	ਪੂਰਨ     i;

	ਜੇ (ctrl.lex_compat) {
		ਜੇ (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		ਜੇ (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		ਜੇ (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#ਜੇ 0
	/* This makes no sense whatsoever. I'm removing it. */
	ਜੇ (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_ਵਰਤਿਆ = true;
#ਜੇ_ਅੰਤ

	ਜੇ (ctrl.csize == trit_unspecified) {
		ਜੇ ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		ਨਹੀਂਤਾਂ
			ctrl.csize = CSIZE;
	}

	ਜੇ (ctrl.interactive == trit_unspecified) {
		ਜੇ (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		ਨਹੀਂਤਾਂ
			ctrl.interactive = trit_true;
	}

	ਜੇ (ctrl.fulltbl || ctrl.fullspd) {
		ਜੇ (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		ਜੇ (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		ਜੇ (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		ਜੇ (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	ਜੇ (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	ਜੇ (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	ਜੇ (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	ਜੇ (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	ਜੇ (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		ਲਈ (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	ਨਹੀਂਤਾਂ {
		/* Put everything in its own equivalence class. */
		ਲਈ (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	ਜੇ (!env.use_stdout) {
		FILE   *prev_stdout;

		ਜੇ (!env.did_outfilename) {
			snprintf (outfile_ਰਸਤਾ, ਆਕਾਰ(outfile_ਰਸਤਾ), outfile_template,
				  ctrl.ਅਗੇਤਰ, suffix());

			env.outfilename = outfile_ਰਸਤਾ;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		ਜੇ (prev_stdout == ਨਿਰਾ)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

ਖਾਲੀ flexend (ਪੂਰਨ exit_ਸਥਿਤੀ)
{
	ਸਥਿਰ ਪੂਰਨ called_before = -1;	/* prevent infinite recursion. */
	ਪੂਰਨ     tblsiz;

	ਜੇ (++called_before)
		FLEX_EXIT (exit_ਸਥਿਤੀ);

	ਜੇ (ctrl.yyclass != ਨਿਰਾ && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	ਜੇ (skelfile != ਨਿਰਾ) {
		ਜੇ (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		ਨਹੀਂਤਾਂ ਜੇ (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	ਜੇ (exit_ਸਥਿਤੀ != 0 && outfile_created) {
		ਜੇ (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		ਨਹੀਂਤਾਂ ਜੇ ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		ਨਹੀਂਤਾਂ ਜੇ (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	ਜੇ (env.backing_ਉੱਪਰ_report && ctrl.backing_ਉੱਪਰ_file) {
		ਜੇ (ਅੰਕ_backing_ਉੱਪਰ == 0)
			fprintf (ctrl.backing_ਉੱਪਰ_file, _("No backing up.\n"));
		ਨਹੀਂਤਾਂ ਜੇ (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_ਉੱਪਰ_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 ਅੰਕ_backing_ਉੱਪਰ);
		ਨਹੀਂਤਾਂ
			fprintf (ctrl.backing_ਉੱਪਰ_file,
				 _("Compressed tables always back up.\n"));

		ਜੇ (ferror (ctrl.backing_ਉੱਪਰ_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		ਨਹੀਂਤਾਂ ਜੇ (fclose (ctrl.backing_ਉੱਪਰ_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	ਜੇ (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 ਪ੍ਰੋਗਰਾਮ_name, flex_ਸੰਸਕਰਣ);

		fprintf (stderr, _("  scanner options: -"));

		ਜੇ (ctrl.C_plus_plus)
			putc ('+', stderr);
		ਜੇ (env.backing_ਉੱਪਰ_report)
			putc ('b', stderr);
		ਜੇ (ctrl.ddebug)
			putc ('d', stderr);
		ਜੇ (sf_case_ins())
			putc ('i', stderr);
		ਜੇ (ctrl.lex_compat)
			putc ('l', stderr);
		ਜੇ (ctrl.posix_compat)
			putc ('X', stderr);
		ਜੇ (env.performance_hint > 0)
			putc ('p', stderr);
		ਜੇ (env.performance_hint > 1)
			putc ('p', stderr);
		ਜੇ (ctrl.spprdflt)
			putc ('s', stderr);
		ਜੇ (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        ਜੇ (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        ਜੇ (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		ਜੇ (env.use_stdout)
			putc ('t', stderr);
		ਜੇ (env.printstats)
			putc ('v', stderr);	/* always true! */
		ਜੇ (env.nowarn)
			putc ('w', stderr);
		ਜੇ (ctrl.interactive == trit_false)
			putc ('B', stderr);
		ਜੇ (ctrl.interactive == trit_true)
			putc ('I', stderr);
		ਜੇ (!ctrl.gen_ਸਤਰ_dirs)
			putc ('L', stderr);
		ਜੇ (env.trace)
			putc ('T', stderr);

		ਜੇ (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		ਜੇ (ctrl.csize == 128)
			putc ('7', stderr);
		ਨਹੀਂਤਾਂ
			putc ('8', stderr);

		fprintf (stderr, " -C");

		ਜੇ (ctrl.long_align)
			putc ('a', stderr);
		ਜੇ (ctrl.fulltbl)
			putc ('f', stderr);
		ਜੇ (ctrl.fullspd)
			putc ('F', stderr);
		ਜੇ (ctrl.useecs)
			putc ('e', stderr);
		ਜੇ (ctrl.usemecs)
			putc ('m', stderr);
		ਜੇ (ctrl.use_read)
			putc ('r', stderr);

		ਜੇ (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		ਜੇ (env.skelname != ਨਿਰਾ)
			fprintf (stderr, " -S%s", env.skelname);

		ਜੇ (strcmp (ctrl.ਅਗੇਤਰ, "yy"))
			fprintf (stderr, " -P%s", ctrl.ਅਗੇਤਰ);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 ਅੰਕ_ਨਿਯਮਾਂ + ਅੰਕ_eof_ਨਿਯਮਾਂ -
			 1 /* - 1 for def. rule */ );

		ਜੇ (ਅੰਕ_backing_ਉੱਪਰ == 0)
			fprintf (stderr, _("  No backing up\n"));
		ਨਹੀਂਤਾਂ ਜੇ (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 ਅੰਕ_backing_ਉੱਪਰ);
		ਨਹੀਂਤਾਂ
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		ਜੇ (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		ਜੇ (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		ਨਹੀਂਤਾਂ
			fprintf (stderr,
				 _
				 ("  %d/%d character classes needed %d/%d words of storage, %d reused\n"),
				 lastccl, current_maxccls,
				 cclmap[lastccl] + ccllen[lastccl],
				 current_max_ccl_tbl_ਮਾਪ, cclreuse);

		fprintf (stderr, _("  %d state/nextstate pairs created\n"),
			 numsnpairs);
		fprintf (stderr,
			 _("  %d/%d unique/duplicate transitions\n"),
			 numuniq, numdup);

		ਜੇ (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		ਨਹੀਂਤਾਂ {
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

		ਜੇ (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		ਜੇ (ctrl.usemecs) {
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
			 ਅੰਕ_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_ਸਥਿਤੀ);
}


/* flexinit - initialize flex */

ਖਾਲੀ flexinit (ਪੂਰਨ argc, ਅੱਖਰ **argv)
{
	ਪੂਰਨ     i, sawcmpflag, rv, optind;
	ਅੱਖਰ   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', ਆਕਾਰ(ctrl));
	syntaxerror = false;
	yymore_ਵਰਤਿਆ = continued_action = false;
	ਵਿੱਚ_ਨਿਯਮ = reject = false;
	ctrl.yymore_really_ਵਰਤਿਆ = ctrl.reject_really_ਵਰਤਿਆ = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_ਸਤਰ_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.ਅਗੇਤਰ = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = ਨਿਰਾ;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_ਮਾਪ = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_ਮਾਪ);
	defs1_ਵਿੱਥ = prolog_ਵਿੱਥ = action_ਵਿੱਥ = action_ਸੂਚਕਾਂਕ = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, ਆਕਾਰ (ਅੱਖਰ));	/* one long string */
	buf_init (&ਸਿਖਰ_buf, ਆਕਾਰ (ਅੱਖਰ));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	ਪ੍ਰੋਗਰਾਮ_name = argv[0];

	ਜੇ (ਪ੍ਰੋਗਰਾਮ_name != ਨਿਰਾ &&
	    ਪ੍ਰੋਗਰਾਮ_name[ਲੜੀ_ਲੰਬਾਈ (ਪ੍ਰੋਗਰਾਮ_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	ਜੇ (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	ਜਦੋਂ ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		ਜੇ (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 ਪ੍ਰੋਗਰਾਮ_name);
			FLEX_EXIT (1);
		}

		ਚੋਣ ((ਗਿਣਤੀ flexopt_flag_t) rv) {
		    ਹਾਲਤ OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_BATCH:
			ctrl.interactive = trit_false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_BACKUP:
			env.backing_ਉੱਪਰ_report = trit_true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_BACKUP_FILE:
			env.backing_ਉੱਪਰ_report = true;
                        backing_name = arg;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_DONOTHING:
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_COMPRESSION:
			ਜੇ (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			ਲਈ (i = 0; arg && arg[i] != '\0'; i++)
				ਚੋਣ (arg[i]) {
				    ਹਾਲਤ 'a':
					ctrl.long_align = true;
					ਰੋਕੋ;

				    ਹਾਲਤ 'e':
					ctrl.useecs = true;
					ਰੋਕੋ;

				    ਹਾਲਤ 'F':
					ctrl.fullspd = true;
					ਰੋਕੋ;

				    ਹਾਲਤ 'f':
					ctrl.fulltbl = true;
					ਰੋਕੋ;

				    ਹਾਲਤ 'm':
					ctrl.usemecs = true;
					ਰੋਕੋ;

				    ਹਾਲਤ 'r':
					ctrl.use_read = true;
					ਰੋਕੋ;

				    ਮੂਲ:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					ਰੋਕੋ;
				}
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_DEBUG:
			ctrl.ddebug = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_DEBUG:
			ctrl.ddebug = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_ਭਰਿਆ:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    ਹਾਲਤ OPT_INTERACTIVE:
			ctrl.interactive = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_CASE_INSENSITIVE:
			sf_ਸੈੱਟ_case_ins(true);
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_PREPROC_LEVEL:
			preproc_level = (ਪੂਰਨ) strtol(arg,ਨਿਰਾ,0);
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_ਸਤਰ:
			ctrl.gen_ਸਤਰ_dirs = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_ਅਗੇਤਰ:
			ctrl.ਅਗੇਤਰ = arg;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_PERF_REPORT:
			++env.performance_hint;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_REENTRANT:
			ctrl.reentrant = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_SKEL:
			env.skelname = arg;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_DEFAULT:
			ctrl.spprdflt = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_STDOUT:
			env.use_stdout = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_TABLES_VERIFY:
			tablesverify = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_TRACE:
			env.trace = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_VERBOSE:
			env.printstats = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_ਸੰਸਕਰਣ:
			ਲਿਖੋ ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_ਸੰਸਕਰਣ);
			FLEX_EXIT (0);

		    ਹਾਲਤ OPT_WARN:
			env.nowarn = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_WARN:
			env.nowarn = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_7_ਦੋਆਧਾਰੀ_ਅੰਕ:
			ctrl.csize = 128;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_8_ਦੋਆਧਾਰੀ_ਅੰਕ:
			ctrl.csize = CSIZE;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_ALIGN:
			ctrl.long_align = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_ALIGN:
			ctrl.long_align = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_ARRAY:
			ctrl.yytext_is_array = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_ਸੂਚਕ:
			ctrl.yytext_is_array = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_ECS:
			ctrl.useecs = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_ECS:
			ctrl.useecs = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_EMIT:
			ctrl.emit = arg;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_ਸਿਰਲੇਖ_FILE:
			env.headerfilename = arg;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_META_ECS:
			ctrl.usemecs = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_META_ECS:
			ctrl.usemecs = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    ਅੱਖਰ   *def;
			    ਅੱਖਰ buf2[4096];

			    ਲਈ (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    ਜਾਰੀ;
			    ਜੇ (*def == '\0')
				    def = "1";

			    snprintf(buf2, ਆਕਾਰ(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    ਰੋਕੋ;

		    ਹਾਲਤ OPT_READ:
			ctrl.use_read = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_ਢੇਰ:
			ctrl.ਢੇਰ_ਵਰਤਿਆ = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_STDINIT:
			ctrl.do_stdinit = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_YYCLASS:
			ctrl.yyclass = arg;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_YYLINENO:
			ctrl.do_yylineno = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_YYWRAP:
			ctrl.do_yywrap = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_YYMORE:
			ctrl.yymore_really_ਵਰਤਿਆ = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_YYMORE:
			ctrl.yymore_really_ਵਰਤਿਆ = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_REJECT:
			ctrl.reject_really_ਵਰਤਿਆ = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_REJECT:
			ctrl.reject_really_ਵਰਤਿਆ = false;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_NO_YY_ਧੱਕੋ_STATE:
			ctrl.no_yy_ਧੱਕੋ_state = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YY_ਕੱਢੋ_STATE:
			ctrl.no_yy_ਕੱਢੋ_state = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YY_ਸਿਖਰ_STATE:
			ctrl.no_yy_ਸਿਖਰ_state = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YY_ਜਾਂਚ_ਬਫਰ:
			ctrl.no_yy_ਜਾਂਚ_ਬਫਰ = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YY_ਜਾਂਚ_ਬਾਈਟਾਂ:
			ctrl.no_yy_ਜਾਂਚ_ਬਾਈਟਾਂ = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YY_ਜਾਂਚ_STRING:
			ctrl.no_yy_ਜਾਂਚ_string = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYGET_ਪਾਠ:
			ctrl.no_yyget_ਪਾਠ = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYGET_ਕਾਲਮ:
			ctrl.no_yyget_ਕਾਲਮ = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYSET_ਕਾਲਮ:
			ctrl.no_yyset_ਕਾਲਮ = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYGET_ਵਿੱਚ:
			ctrl.no_yyget_ਵਿੱਚ = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYSET_ਵਿੱਚ:
			ctrl.no_yyset_ਵਿੱਚ = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYGET_ਬਾਹਰਲਾ:
			ctrl.no_yyget_ਬਾਹਰਲਾ = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYSET_ਬਾਹਰਲਾ:
			ctrl.no_yyset_ਬਾਹਰਲਾ = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_YYSET_DEBUG:
			ctrl.no_ਸੈੱਟ_debug = true;
			ਰੋਕੋ;

		    ਹਾਲਤ OPT_HEX:
			env.trace_hex = true;
                        ਰੋਕੋ;
		    ਹਾਲਤ OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        ਰੋਕੋ;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	ਅੰਕ_ਨਿਵੇਸ਼_files = argc - optind;
	ਨਿਵੇਸ਼_files = argv + optind;
	ਸੈੱਟ_ਨਿਵੇਸ਼_file (ਅੰਕ_ਨਿਵੇਸ਼_files > 0 ? ਨਿਵੇਸ਼_files[0] : ਨਿਰਾ);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	ਅੰਕ_ਨਿਯਮਾਂ = ਅੰਕ_eof_ਨਿਯਮਾਂ = default_ਨਿਯਮ = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = ਅੰਕ_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	ਅੰਕ_backing_ਉੱਪਰ = onesp = numprots = 0;
	variable_trailing_context_ਨਿਯਮਾਂ = bol_needed = false;

	linenum = sectnum = 1;
	firstprot = NIL;

	/* Used in mkprot() so that the first proto goes in slot 1
	 * of the proto queue.
	 */
	lastprot = 1;

	ਸੈੱਟ_ਉੱਪਰ_initial_allocations ();
}


/* readin - read in the rules section of the input file(s) */

ਖਾਲੀ readin (ਖਾਲੀ)
{
	ਅੱਖਰ buf[256];

	ਸਤਰ_directive_ਬਾਹਰਲਾ(ਨਿਰਾ, infilename, linenum);

	ਜੇ (yyparse ()) {
		pinpoint_ਸੁਨੇਹਾ (_("fatal parse error"));
		flexend (1);
	}

	ਜੇ (syntaxerror)
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

	ਜੇ (tablesext)
		gentables = false;

	ਜੇ (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	ਜੇ (tablesext) {
		FILE   *tablesout;
		ਬਣਤਰ yytbl_hdr hdr;
		ਅੱਖਰ   *pname = 0;
		size_t  nbytes = 0;

		ਜੇ (!tablesfilename) {
			nbytes = ਲੜੀ_ਲੰਬਾਈ (ctrl.ਅਗੇਤਰ) + ਲੜੀ_ਲੰਬਾਈ (tablesfile_template) + 2;
			tablesfilename = pname = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.ਅਗੇਤਰ);
		}

		ਜੇ ((tablesout = fopen (tablesfilename, "w")) == ਨਿਰਾ)
			lerr (_("could not create %s"), tablesfilename);
		ਮੁਕਤ(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = ਲੜੀ_ਲੰਬਾਈ (ctrl.ਅਗੇਤਰ) + ਲੜੀ_ਲੰਬਾਈ ("tables") + 2;
		tablesname = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.ਅਗੇਤਰ);
		yytbl_hdr_init (&hdr, flex_ਸੰਸਕਰਣ, tablesname);

		ਜੇ (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	ਜੇ (env.skelname && (skelfile = fopen (env.skelname, "r")) == ਨਿਰਾ)
		lerr (_("can't open skeleton file %s"), env.skelname);

	ਜੇ (strchr(ctrl.ਅਗੇਤਰ, '[') || strchr(ctrl.ਅਗੇਤਰ, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	ਜੇ (env.did_outfilename)
		ਸਤਰ_directive_ਬਾਹਰਲਾ (stdout, ਨਿਰਾ, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	ਜੇ( ਸਿਖਰ_buf.elts)
		outn((ਅੱਖਰ*) ਸਿਖਰ_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	ਸਤਰ_directive_ਬਾਹਰਲਾ(ਨਿਰਾ, ਨਿਰਾ, 0);

	/* User may want to set the scanner prototype */
	ਜੇ (ctrl.yydecl != ਨਿਰਾ) {
		ਬਾਹਰਲਾ_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	ਜੇ (ctrl.userinit != ਨਿਰਾ) {
		ਬਾਹਰਲਾ_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	ਜੇ (ctrl.preaction != ਨਿਰਾ) {
		ਬਾਹਰਲਾ_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	ਜੇ (ctrl.postaction != ਨਿਰਾ) {
		ਬਾਹਰਲਾ_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	ਬਾਹਰਲਾ_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	ਜੇ (userdef_buf.elts)
		outn ((ਅੱਖਰ *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	ਜੇ (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	ਜੇ (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	ਜੇ (env.backing_ਉੱਪਰ_report) {
		ctrl.backing_ਉੱਪਰ_file = fopen (backing_name, "w");
		ਜੇ (ctrl.backing_ਉੱਪਰ_file == ਨਿਰਾ)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	ਨਹੀਂਤਾਂ
		ctrl.backing_ਉੱਪਰ_file = ਨਿਰਾ;

	ਜੇ (ctrl.yymore_really_ਵਰਤਿਆ == true)
		yymore_ਵਰਤਿਆ = true;
	ਨਹੀਂਤਾਂ ਜੇ (ctrl.yymore_really_ਵਰਤਿਆ == false)
		yymore_ਵਰਤਿਆ = false;

	ਜੇ (ctrl.reject_really_ਵਰਤਿਆ == true)
		reject = true;
	ਨਹੀਂਤਾਂ ਜੇ (ctrl.reject_really_ਵਰਤਿਆ == false)
		reject = false;

	ਜੇ (env.performance_hint > 0) {
		ਜੇ (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		ਨਹੀਂਤਾਂ ਜੇ (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		ਜੇ (env.performance_hint > 1) {
			ਜੇ (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			ਜੇ (yymore_ਵਰਤਿਆ)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		ਜੇ (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		ਜੇ (variable_trailing_context_ਨਿਯਮਾਂ)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	ਜੇ (reject)
		real_reject = true;

	ਜੇ (variable_trailing_context_ਨਿਯਮਾਂ)
		reject = true;

	ਜੇ ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		ਜੇ (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		ਨਹੀਂਤਾਂ ਜੇ (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		ਨਹੀਂਤਾਂ
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	ਜੇ (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	ਨਹੀਂਤਾਂ
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	ਜੇ (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, ਆਕਾਰ(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		ਬਣਤਰ Buf tmpbuf;
		ਪੂਰਨ i;
		buf_init(&tmpbuf, ਆਕਾਰ(ਅੱਖਰ));
		ਲਈ (i = 1; i <= lastsc; i++) {
			ਅੱਖਰ *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = ਲੜੀ_ਲੰਬਾਈ(fmt) + ਲੜੀ_ਲੰਬਾਈ(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = ਸਮ੍ਰਿਤੀ_ਦਿਓ(strsz);
			ਜੇ (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			ਮੁਕਤ(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		ਬਾਹਰਲਾ_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	ਜੇ (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	ਜੇ (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	ਜੇ (extra_type != ਨਿਰਾ)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	ਜੇ (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		ਜੇ (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	ਜੇ (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	ਨਹੀਂਤਾਂ ਜੇ (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	ਜੇ (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	ਜੇ (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	ਜੇ (yymore_ਵਰਤਿਆ)
		visible_define ( "M4_MODE_YYMORE_USED");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	ਜੇ (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	ਜੇ (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	ਜੇ (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	ਜੇ (variable_trailing_context_ਨਿਯਮਾਂ) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} ਨਹੀਂਤਾਂ {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	ਜੇ (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	ਜੇ (ctrl.reject_really_ਵਰਤਿਆ)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	ਜੇ (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	ਜੇ (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	ਜੇ (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	ਨਹੀਂਤਾਂ ਜੇ (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	ਨਹੀਂਤਾਂ ਜੇ (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	ਨਹੀਂਤਾਂ
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	ਜੇ (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	ਜੇ (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	ਜੇ (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	ਜੇ (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	ਜੇ (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_GENTABLES");
	ਜੇ (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	ਜੇ (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	ਜੇ (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	ਜੇ (ctrl.yyclass != ਨਿਰਾ) {
		visible_define ( "M4_MODE_YYCLASS");
		ਬਾਹਰਲਾ_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	ਜੇ (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	ਜੇ (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	ਜੇ (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_YYWRAP");

	ਜੇ (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	ਜੇ (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	ਜੇ (is_default_backend()) {
		ਜੇ (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} ਨਹੀਂਤਾਂ {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	ਜੇ (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	ਜੇ (ctrl.ਅਗੇਤਰ != ਨਿਰਾ)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.ਅਗੇਤਰ);

	ਜੇ (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	ਜੇ (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	ਜੇ (ctrl.yyterminate != ਨਿਰਾ)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	ਜੇ (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	ਜੇ (ctrl.no_yy_ਧੱਕੋ_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	ਜੇ (ctrl.no_yy_ਕੱਢੋ_state)
		visible_define("M4_YY_NO_POP_STATE");
	ਜੇ (ctrl.no_yy_ਸਿਖਰ_state)
		visible_define("M4_YY_NO_TOP_STATE");
	ਜੇ (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	ਜੇ (ctrl.no_yy_ਜਾਂਚ_ਬਫਰ)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	ਜੇ (ctrl.no_yy_ਜਾਂਚ_ਬਾਈਟਾਂ)
		visible_define("M4_YY_NO_SCAN_BYTES");
	ਜੇ (ctrl.no_yy_ਜਾਂਚ_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	ਜੇ (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	ਜੇ (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	ਜੇ (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	ਜੇ (ctrl.no_yyget_ਪਾਠ)
		visible_define("M4_YY_NO_GET_TEXT");
	ਜੇ (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	ਜੇ (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	ਜੇ (ctrl.no_yyget_ਕਾਲਮ)
		visible_define("M4_YY_NO_GET_COLUMN");
	ਜੇ (ctrl.no_yyset_ਕਾਲਮ)
		visible_define("M4_YY_NO_SET_COLUMN");
	ਜੇ (ctrl.no_yyget_ਵਿੱਚ)
		visible_define("M4_YY_NO_GET_IN");
	ਜੇ (ctrl.no_yyset_ਵਿੱਚ)
		visible_define("M4_YY_NO_SET_IN");
	ਜੇ (ctrl.no_yyget_ਬਾਹਰਲਾ)
		visible_define("M4_YY_NO_GET_OUT");
	ਜੇ (ctrl.no_yyset_ਬਾਹਰਲਾ)
		visible_define("M4_YY_NO_SET_OUT");
	ਜੇ (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	ਜੇ (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	ਜੇ (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	ਜੇ (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	ਜੇ (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	ਜੇ (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	ਜੇ (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	ਜੇ (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	ਜੇ (ctrl.no_ਸੈੱਟ_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	ਜੇ (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	ਜੇ (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	ਜੇ (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	ਜੇ (ctrl.ਢੇਰ_ਵਰਤਿਆ)
		visible_define("M4_YY_STACK_USED");

	ਜੇ (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	ਨਹੀਂਤਾਂ
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	ਬਾਹਰਲਾ ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

ਖਾਲੀ ਸੈੱਟ_ਉੱਪਰ_initial_allocations (ਖਾਲੀ)
{
	ਵੱਧ_ਤੋਂ_ਵੱਧ_mns = (ctrl.long_align ? ਵੱਧ_ਤੋਂ_ਵੱਧ_MNS_LONG : ਵੱਧ_ਤੋਂ_ਵੱਧ_MNS);
	current_mns = INITIAL_MNS;
	firstst = allocate_integer_array (current_mns);
	lastst = allocate_integer_array (current_mns);
	finalst = allocate_integer_array (current_mns);
	transchar = allocate_integer_array (current_mns);
	trans1 = allocate_integer_array (current_mns);
	trans2 = allocate_integer_array (current_mns);
	accptnum = allocate_integer_array (current_mns);
	assoc_ਨਿਯਮ = allocate_integer_array (current_mns);
	state_type = allocate_integer_array (current_mns);

	current_max_ਨਿਯਮਾਂ = INITIAL_MAX_ਨਿਯਮਾਂ;
	ਨਿਯਮ_type = allocate_integer_array (current_max_ਨਿਯਮਾਂ);
	ਨਿਯਮ_linenum = allocate_integer_array (current_max_ਨਿਯਮਾਂ);
	ਨਿਯਮ_useful = allocate_array(current_max_ਨਿਯਮਾਂ, ਆਕਾਰ(ਅੱਖਰ));
	ਨਿਯਮ_has_nl = allocate_array(current_max_ਨਿਯਮਾਂ, ਆਕਾਰ(ਅੱਖਰ));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, ਆਕਾਰ(ਅੱਖਰ));
	sceof = allocate_array(current_max_scs, ਆਕਾਰ(ਅੱਖਰ));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, ਆਕਾਰ(ਅੱਖਰ));

	current_max_ccl_tbl_ਮਾਪ = INITIAL_MAX_CCL_TBL_ਮਾਪ;
	ccltbl = allocate_Character_array (current_max_ccl_tbl_ਮਾਪ);

	current_max_dfa_ਮਾਪ = INITIAL_MAX_DFA_ਮਾਪ;

	current_max_xpairs = INITIAL_MAX_XPAIRS;
	nxt = allocate_integer_array (current_max_xpairs);
	chk = allocate_integer_array (current_max_xpairs);

	current_max_template_xpairs = INITIAL_MAX_TEMPLATE_XPAIRS;
	tnxt = allocate_integer_array (current_max_template_xpairs);

	current_max_dfas = INITIAL_MAX_DFAS;
	ਅਧਾਰ = allocate_integer_array (current_max_dfas);
	def = allocate_integer_array (current_max_dfas);
	dfasiz = allocate_integer_array (current_max_dfas);
	accsiz = allocate_integer_array (current_max_dfas);
	dhash = allocate_integer_array (current_max_dfas);
	dss = allocate_int_ptr_array (current_max_dfas);
	dfaacc = allocate_array(current_max_dfas,
		ਆਕਾਰ(ਸੰਘ dfaacc_union));

	nultrans = ਨਿਰਾ;
}


ਖਾਲੀ usage (ਖਾਲੀ)
{
	FILE   *f = stdout;

	ਜੇ (!env.did_outfilename) {
		snprintf (outfile_ਰਸਤਾ, ਆਕਾਰ(outfile_ਰਸਤਾ), outfile_template,
			  ctrl.ਅਗੇਤਰ, suffix());
		env.outfilename = outfile_ਰਸਤਾ;
	}

	fprintf (f, _("Usage: %s [OPTIONS] [FILE]...\n"), ਪ੍ਰੋਗਰਾਮ_name);
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
		 backing_name, "flex", outfile_ਰਸਤਾ, "flex");

}
