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


#ಅನ್ತರ್ಭಾವ "flexdef.h"
#ಅನ್ತರ್ಭಾವ "version.h"
#ಅನ್ತರ್ಭಾವ "options.h"
#ಅನ್ತರ್ಭಾವ "tables.h"
#ಅನ್ತರ್ಭಾವ "parse.h"

ಸ್ಥಿರ ಅಕ್ಷರ flex_ಆವೃತ್ತಿ[] = FLEX_ಆವೃತ್ತಿ;

/* declare functions that have forward references */

ಶೂನ್ಯ flexinit(ಪೂರ್ಣಾಂಕ, ಅಕ್ಷರ **);
ಶೂನ್ಯ readin(ಶೂನ್ಯ);
ಶೂನ್ಯ ಗಣ_ಮೇಲೆ_initial_allocations(ಶೂನ್ಯ);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
ಪೂರ್ಣಾಂಕ     yymore_ಬಳಸಿದ, reject, real_reject, continued_action, ಒಳ_ನಿಯಮ;
ಪೂರ್ಣಾಂಕ     datapos, dataline, linenum;
FILE   *skelfile = ಖಾಲಿ;
ಪೂರ್ಣಾಂಕ     skel_ind = 0;
ಅಕ್ಷರ   *action_array;
ಪೂರ್ಣಾಂಕ     action_ಗಾತ್ರ, defs1_ಸ್ಥಾನಾಂತರ, prolog_ಸ್ಥಾನಾಂತರ, action_ಸ್ಥಾನಾಂತರ,
	action_ಸೂಚ್ಯಂಕ;
ಅಕ್ಷರ   *infilename = ಖಾಲಿ;
ಅಕ್ಷರ   *extra_type = ಖಾಲಿ;
ಪೂರ್ಣಾಂಕ     onestate[ONE_ರಾಶಿ_ಗಾತ್ರ], onesym[ONE_ರಾಶಿ_ಗಾತ್ರ];
ಪೂರ್ಣಾಂಕ     onenext[ONE_ರಾಶಿ_ಗಾತ್ರ], onedef[ONE_ರಾಶಿ_ಗಾತ್ರ], onesp;
ಪೂರ್ಣಾಂಕ     ಗರಿಷ್ಠ_mns, current_mns, current_max_ನಿಯಮಗಳು;
ಪೂರ್ಣಾಂಕ     ಅಂಕೆ_ನಿಯಮಗಳು, ಅಂಕೆ_eof_ನಿಯಮಗಳು, default_ನಿಯಮ, lastnfa;
ಪೂರ್ಣಾಂಕ    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
ಪೂರ್ಣಾಂಕ    *accptnum, *assoc_ನಿಯಮ, *state_type;
ಪೂರ್ಣಾಂಕ    *ನಿಯಮ_type, *ನಿಯಮ_linenum;
ಪೂರ್ಣಾಂಕ     current_state_type;
bool    variable_trailing_context_ನಿಯಮಗಳು;
ಪೂರ್ಣಾಂಕ     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
ಪೂರ್ಣಾಂಕ     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_ಗಾತ್ರ];
ಪೂರ್ಣಾಂಕ     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
ಪೂರ್ಣಾಂಕ     tecbck[CSIZE + 1];
ಪೂರ್ಣಾಂಕ     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
ಅಕ್ಷರ   *scxclu, *sceof;
ಪೂರ್ಣಾಂಕ     current_max_scs;
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **scname;
ಪೂರ್ಣಾಂಕ     current_max_dfa_ಗಾತ್ರ, current_max_xpairs;
ಪೂರ್ಣಾಂಕ     current_max_template_xpairs, current_max_dfas;
ಪೂರ್ಣಾಂಕ     lastdfa, *nxt, *chk, *tnxt;
ಪೂರ್ಣಾಂಕ    *ತಳ, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
ಒಕ್ಕೂಟ dfaacc_union *dfaacc;
ಪೂರ್ಣಾಂಕ    *accsiz, *dhash, numas;
ಪೂರ್ಣಾಂಕ     numsnpairs, jambase, jamstate;
ಪೂರ್ಣಾಂಕ     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
ಪೂರ್ಣಾಂಕ     current_maxccls, current_max_ccl_tbl_ಗಾತ್ರ;
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ   *ccltbl;
ಅಕ್ಷರ    nmstr[MAXLINE];
ಪೂರ್ಣಾಂಕ     sectnum, nummt, hshcol, dfaeql, numeps, eps2, ಅಂಕೆ_reallocs, nmval;
ಪೂರ್ಣಾಂಕ     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
ಪೂರ್ಣಾಂಕ     ಅಂಕೆ_backing_ಮೇಲೆ, bol_needed;
ಪೂರ್ಣಾಂಕ     ಕೊನೆ_ದ_ಬಫರ್_state;
ಅಕ್ಷರ  **ಒಳಹರಿವು_files;
ಪೂರ್ಣಾಂಕ     ಅಂಕೆ_ಒಳಹರಿವು_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
ಅಕ್ಷರ   *ನಿಯಮ_useful, *ನಿಯಮ_has_nl, *ccl_has_nl;
ಪೂರ್ಣಾಂಕ     nlch = '\n';

bool    tablesext, tablesverify, gentables;
ಅಕ್ಷರ   *tablesfilename=0,*tablesname=0;
ರಚನೆ yytbl_writer tableswr;
size_t footprint;

ರಚನೆ ctrl_bundle_t ctrl;
ರಚನೆ env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
ಅಕ್ಷರ   *ಕಾರ್ಯಕ್ರಮ_name = "flex";

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ outfile_template[] = "lex.%s.%s";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *backing_name = "lex.backup";
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
ಬಾಹ್ಯ FILE* yyout;

ಸ್ಥಿರ ಅಕ್ಷರ outfile_ಮಾರ್ಗ[MAXLINE];
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ outfile_created = 0;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ preproc_level = 1000;

ಪೂರ್ಣಾಂಕ flex_main (ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ *argv[]);

ಪೂರ್ಣಾಂಕ flex_main (ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ *argv[])
{
	ಪೂರ್ಣಾಂಕ     i, exit_ಸ್ಥಿತಿ, ಮಗು_ಸ್ಥಿತಿ;
	ಪೂರ್ಣಾಂಕ	did_eof_ನಿಯಮ = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_ಸ್ಥಿತಿ = setjmp (flex_main_jmp_buf);
	ಆದರೆ (exit_ಸ್ಥಿತಿ){
		ಆದರೆ (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		ಆಗ (wait(&ಮಗು_ಸ್ಥಿತಿ) > 0){
			ಆದರೆ (!WIFEXITED (ಮಗು_ಸ್ಥಿತಿ)
			    || WEXITSTATUS (ಮಗು_ಸ್ಥಿತಿ) != 0){
				/* report an error of a child
				 */
				ಆದರೆ( exit_ಸ್ಥಿತಿ <= 1 )
					exit_ಸ್ಥಿತಿ = 2;

			}
		}
		ಹಿಂತಿರುಗಿ exit_ಸ್ಥಿತಿ - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	ಗಾಗಿ (i = 1; i <= ಅಂಕೆ_ನಿಯಮಗಳು; ++i)
		ಆದರೆ (!ನಿಯಮ_useful[i] && i != default_ನಿಯಮ)
			ಸಾಲು_warning (_("rule cannot be matched"),
				      ನಿಯಮ_linenum[i]);

	ಆದರೆ (ctrl.spprdflt && !reject && ನಿಯಮ_useful[default_ನಿಯಮ])
		ಸಾಲು_warning (_
			      ("-s option given but default rule can be matched"),
			      ನಿಯಮ_linenum[default_ನಿಯಮ]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	ಆದರೆ (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	ಇಲ್ಲದಿದ್ದರೆ {
		visible_define ( "M4_MODE_NO_NULTRANS");
		ಆದರೆ (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		ಇಲ್ಲದಿದ್ದರೆ
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		ಆದರೆ (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		ಇಲ್ಲದಿದ್ದರೆ
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	ಹೊರಹೋಗು ("\n");

	comment("START of Flex-generated definitions\n");
	ಹೊರಹೋಗು_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", ಅಂಕೆ_ನಿಯಮಗಳು);
	ಹೊರಹೋಗು_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", ಅಂಕೆ_ನಿಯಮಗಳು + 1);
	ಹೊರಹೋಗು_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_JAMBASE", jambase);
	ಹೊರಹೋಗು_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_JAMSTATE", jamstate);
	ಹೊರಹೋಗು_str_dec ("M4_HOOK_CONST_DEFINE_BYTE(%s, %d)", "YY_NUL_EC", NUL_ec);
	/* Need to define the transet type as a size large
	 * enough to hold the biggest offset.
	 */
	ಹೊರಹೋಗು_str ("M4_HOOK_SET_OFFSET_TYPE(%s)", optimize_pack(tblend + numecs + 1)->name);
	comment("END of Flex-generated definitions\n");

	skelout (true);		/* %% [2.0] - tables get dumped here */

	/* Generate the C state transition tables from the DFA. */
	make_tables ();

	skelout (true);		/* %% [3.0] - mode-dependent static declarations get dumped here */

	ಹೊರಹೋಗು (&action_array[defs1_ಸ್ಥಾನಾಂತರ]);

	ಸಾಲು_directive_ಹೊರಹೋಗು (stdout, ಖಾಲಿ, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	ಹೊರಹೋಗು (&action_array[prolog_ಸ್ಥಾನಾಂತರ]);

	ಸಾಲು_directive_ಹೊರಹೋಗು (stdout, ಖಾಲಿ, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	ಹೊರಹೋಗು (&action_array[action_ಸ್ಥಾನಾಂತರ]);

	ಸಾಲು_directive_ಹೊರಹೋಗು (stdout, ಖಾಲಿ, linenum);

	/* generate cases for any missing EOF rules */
	ಗಾಗಿ (i = 1; i <= lastsc; ++i)
		ಆದರೆ (!sceof[i]) {
			ಹೊರಹೋಗು_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			ಹೊರಹೋಗು ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_ನಿಯಮ = true;
		}

	ಆದರೆ (did_eof_ನಿಯಮ) {
		ಹೊರಹೋಗು ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	ಸಾಲು_directive_ಹೊರಹೋಗು (stdout, infilename, linenum);

	ಆದರೆ (sectnum == 3) {
		ಹೊರಹೋಗು_BEGIN_ಸಂಕೇತ ();
                ಆದರೆ (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(ಶೂನ್ಯ) flexscan ();	/* copy remainder of input to output */
                ಆದರೆ (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		ಹೊರಹೋಗು_ಕೊನೆ_ಸಂಕೇತ ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	ಹಿಂತಿರುಗಿ 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ (ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ *argv[])
{
#ಆದರೆ defined(ENABLE_NLS) && ENABLE_NLS
#ಆದರೆ HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

	ಹಿಂತಿರುಗಿ flex_main (argc, argv);
}

/* Set up the output filter chain. */

ಶೂನ್ಯ initialize_output_filters(ಶೂನ್ಯ)
{
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * m4 = ಖಾಲಿ;

	output_chain = filter_create_int(ಖಾಲಿ, filter_tee_ಶೀರ್ಷಿಕೆ, env.headerfilename);
	ಆದರೆ ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (ಅಕ್ಷರ *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, ಖಾಲಿ);

	/* For debugging, only run the requested number of filters. */
	ಆದರೆ (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

ಶೂನ್ಯ check_options (ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ     i;

	ಆದರೆ (ctrl.lex_compat) {
		ಆದರೆ (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		ಆದರೆ (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		ಆದರೆ (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#ಆದರೆ 0
	/* This makes no sense whatsoever. I'm removing it. */
	ಆದರೆ (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_ಬಳಸಿದ = true;
#ಆದರೆ_ಅಂತ್ಯ

	ಆದರೆ (ctrl.csize == trit_unspecified) {
		ಆದರೆ ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		ಇಲ್ಲದಿದ್ದರೆ
			ctrl.csize = CSIZE;
	}

	ಆದರೆ (ctrl.interactive == trit_unspecified) {
		ಆದರೆ (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		ಇಲ್ಲದಿದ್ದರೆ
			ctrl.interactive = trit_true;
	}

	ಆದರೆ (ctrl.fulltbl || ctrl.fullspd) {
		ಆದರೆ (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		ಆದರೆ (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		ಆದರೆ (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		ಆದರೆ (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	ಆದರೆ (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	ಆದರೆ (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	ಆದರೆ (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	ಆದರೆ (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	ಆದರೆ (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		ಗಾಗಿ (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	ಇಲ್ಲದಿದ್ದರೆ {
		/* Put everything in its own equivalence class. */
		ಗಾಗಿ (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	ಆದರೆ (!env.use_stdout) {
		FILE   *prev_stdout;

		ಆದರೆ (!env.did_outfilename) {
			snprintf (outfile_ಮಾರ್ಗ, ಗಾತ್ರ(outfile_ಮಾರ್ಗ), outfile_template,
				  ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ, suffix());

			env.outfilename = outfile_ಮಾರ್ಗ;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		ಆದರೆ (prev_stdout == ಖಾಲಿ)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

ಶೂನ್ಯ flexend (ಪೂರ್ಣಾಂಕ exit_ಸ್ಥಿತಿ)
{
	ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ called_before = -1;	/* prevent infinite recursion. */
	ಪೂರ್ಣಾಂಕ     tblsiz;

	ಆದರೆ (++called_before)
		FLEX_EXIT (exit_ಸ್ಥಿತಿ);

	ಆದರೆ (ctrl.yyclass != ಖಾಲಿ && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	ಆದರೆ (skelfile != ಖಾಲಿ) {
		ಆದರೆ (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	ಆದರೆ (exit_ಸ್ಥಿತಿ != 0 && outfile_created) {
		ಆದರೆ (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	ಆದರೆ (env.backing_ಮೇಲೆ_report && ctrl.backing_ಮೇಲೆ_file) {
		ಆದರೆ (ಅಂಕೆ_backing_ಮೇಲೆ == 0)
			fprintf (ctrl.backing_ಮೇಲೆ_file, _("No backing up.\n"));
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_ಮೇಲೆ_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 ಅಂಕೆ_backing_ಮೇಲೆ);
		ಇಲ್ಲದಿದ್ದರೆ
			fprintf (ctrl.backing_ಮೇಲೆ_file,
				 _("Compressed tables always back up.\n"));

		ಆದರೆ (ferror (ctrl.backing_ಮೇಲೆ_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fclose (ctrl.backing_ಮೇಲೆ_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	ಆದರೆ (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 ಕಾರ್ಯಕ್ರಮ_name, flex_ಆವೃತ್ತಿ);

		fprintf (stderr, _("  scanner options: -"));

		ಆದರೆ (ctrl.C_plus_plus)
			putc ('+', stderr);
		ಆದರೆ (env.backing_ಮೇಲೆ_report)
			putc ('b', stderr);
		ಆದರೆ (ctrl.ddebug)
			putc ('d', stderr);
		ಆದರೆ (sf_case_ins())
			putc ('i', stderr);
		ಆದರೆ (ctrl.lex_compat)
			putc ('l', stderr);
		ಆದರೆ (ctrl.posix_compat)
			putc ('X', stderr);
		ಆದರೆ (env.performance_hint > 0)
			putc ('p', stderr);
		ಆದರೆ (env.performance_hint > 1)
			putc ('p', stderr);
		ಆದರೆ (ctrl.spprdflt)
			putc ('s', stderr);
		ಆದರೆ (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        ಆದರೆ (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        ಆದರೆ (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		ಆದರೆ (env.use_stdout)
			putc ('t', stderr);
		ಆದರೆ (env.printstats)
			putc ('v', stderr);	/* always true! */
		ಆದರೆ (env.nowarn)
			putc ('w', stderr);
		ಆದರೆ (ctrl.interactive == trit_false)
			putc ('B', stderr);
		ಆದರೆ (ctrl.interactive == trit_true)
			putc ('I', stderr);
		ಆದರೆ (!ctrl.gen_ಸಾಲು_dirs)
			putc ('L', stderr);
		ಆದರೆ (env.trace)
			putc ('T', stderr);

		ಆದರೆ (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		ಆದರೆ (ctrl.csize == 128)
			putc ('7', stderr);
		ಇಲ್ಲದಿದ್ದರೆ
			putc ('8', stderr);

		fprintf (stderr, " -C");

		ಆದರೆ (ctrl.long_align)
			putc ('a', stderr);
		ಆದರೆ (ctrl.fulltbl)
			putc ('f', stderr);
		ಆದರೆ (ctrl.fullspd)
			putc ('F', stderr);
		ಆದರೆ (ctrl.useecs)
			putc ('e', stderr);
		ಆದರೆ (ctrl.usemecs)
			putc ('m', stderr);
		ಆದರೆ (ctrl.use_read)
			putc ('r', stderr);

		ಆದರೆ (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		ಆದರೆ (env.skelname != ಖಾಲಿ)
			fprintf (stderr, " -S%s", env.skelname);

		ಆದರೆ (strcmp (ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ, "yy"))
			fprintf (stderr, " -P%s", ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 ಅಂಕೆ_ನಿಯಮಗಳು + ಅಂಕೆ_eof_ನಿಯಮಗಳು -
			 1 /* - 1 for def. rule */ );

		ಆದರೆ (ಅಂಕೆ_backing_ಮೇಲೆ == 0)
			fprintf (stderr, _("  No backing up\n"));
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 ಅಂಕೆ_backing_ಮೇಲೆ);
		ಇಲ್ಲದಿದ್ದರೆ
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		ಆದರೆ (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		ಆದರೆ (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		ಇಲ್ಲದಿದ್ದರೆ
			fprintf (stderr,
				 _
				 ("  %d/%d character classes needed %d/%d words of storage, %d reused\n"),
				 lastccl, current_maxccls,
				 cclmap[lastccl] + ccllen[lastccl],
				 current_max_ccl_tbl_ಗಾತ್ರ, cclreuse);

		fprintf (stderr, _("  %d state/nextstate pairs created\n"),
			 numsnpairs);
		fprintf (stderr,
			 _("  %d/%d unique/duplicate transitions\n"),
			 numuniq, numdup);

		ಆದರೆ (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		ಇಲ್ಲದಿದ್ದರೆ {
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

		ಆದರೆ (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		ಆದರೆ (ctrl.usemecs) {
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
			 ಅಂಕೆ_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_ಸ್ಥಿತಿ);
}


/* flexinit - initialize flex */

ಶೂನ್ಯ flexinit (ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ **argv)
{
	ಪೂರ್ಣಾಂಕ     i, sawcmpflag, rv, optind;
	ಅಕ್ಷರ   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', ಗಾತ್ರ(ctrl));
	syntaxerror = false;
	yymore_ಬಳಸಿದ = continued_action = false;
	ಒಳ_ನಿಯಮ = reject = false;
	ctrl.yymore_really_ಬಳಸಿದ = ctrl.reject_really_ಬಳಸಿದ = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_ಸಾಲು_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = ಖಾಲಿ;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_ಗಾತ್ರ = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_ಗಾತ್ರ);
	defs1_ಸ್ಥಾನಾಂತರ = prolog_ಸ್ಥಾನಾಂತರ = action_ಸ್ಥಾನಾಂತರ = action_ಸೂಚ್ಯಂಕ = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, ಗಾತ್ರ (ಅಕ್ಷರ));	/* one long string */
	buf_init (&ತುದಿ_buf, ಗಾತ್ರ (ಅಕ್ಷರ));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	ಕಾರ್ಯಕ್ರಮ_name = argv[0];

	ಆದರೆ (ಕಾರ್ಯಕ್ರಮ_name != ಖಾಲಿ &&
	    ಕಾರ್ಯಕ್ರಮ_name[ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಕಾರ್ಯಕ್ರಮ_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	ಆದರೆ (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	ಆಗ ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		ಆದರೆ (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 ಕಾರ್ಯಕ್ರಮ_name);
			FLEX_EXIT (1);
		}

		ಆಯ್ಕೆ ((ಎಣಿಕೆ flexopt_flag_t) rv) {
		    ಸ್ಥಿತಿ OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_BATCH:
			ctrl.interactive = trit_false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_BACKUP:
			env.backing_ಮೇಲೆ_report = trit_true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_BACKUP_FILE:
			env.backing_ಮೇಲೆ_report = true;
                        backing_name = arg;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_DONOTHING:
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_COMPRESSION:
			ಆದರೆ (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			ಗಾಗಿ (i = 0; arg && arg[i] != '\0'; i++)
				ಆಯ್ಕೆ (arg[i]) {
				    ಸ್ಥಿತಿ 'a':
					ctrl.long_align = true;
					ನಿಲ್ಲಿಸು;

				    ಸ್ಥಿತಿ 'e':
					ctrl.useecs = true;
					ನಿಲ್ಲಿಸು;

				    ಸ್ಥಿತಿ 'F':
					ctrl.fullspd = true;
					ನಿಲ್ಲಿಸು;

				    ಸ್ಥಿತಿ 'f':
					ctrl.fulltbl = true;
					ನಿಲ್ಲಿಸು;

				    ಸ್ಥಿತಿ 'm':
					ctrl.usemecs = true;
					ನಿಲ್ಲಿಸು;

				    ಸ್ಥಿತಿ 'r':
					ctrl.use_read = true;
					ನಿಲ್ಲಿಸು;

				    ಪೂರ್ವನಿಯೋಜಿತ:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					ನಿಲ್ಲಿಸು;
				}
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_DEBUG:
			ctrl.ddebug = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_DEBUG:
			ctrl.ddebug = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_ತುಂಬಿದ:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    ಸ್ಥಿತಿ OPT_INTERACTIVE:
			ctrl.interactive = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_CASE_INSENSITIVE:
			sf_ಗಣ_case_ins(true);
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_PREPROC_LEVEL:
			preproc_level = (ಪೂರ್ಣಾಂಕ) strtol(arg,ಖಾಲಿ,0);
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_ಸಾಲು:
			ctrl.gen_ಸಾಲು_dirs = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_ಪೂರ್ವಪ್ರತ್ಯಯ:
			ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ = arg;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_PERF_REPORT:
			++env.performance_hint;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_REENTRANT:
			ctrl.reentrant = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_SKEL:
			env.skelname = arg;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_DEFAULT:
			ctrl.spprdflt = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_STDOUT:
			env.use_stdout = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_TABLES_VERIFY:
			tablesverify = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_TRACE:
			env.trace = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_VERBOSE:
			env.printstats = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_ಆವೃತ್ತಿ:
			ಬರೆ ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_ಆವೃತ್ತಿ);
			FLEX_EXIT (0);

		    ಸ್ಥಿತಿ OPT_WARN:
			env.nowarn = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_WARN:
			env.nowarn = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_7_ಬಿಟ್:
			ctrl.csize = 128;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_8_ಬಿಟ್:
			ctrl.csize = CSIZE;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_ALIGN:
			ctrl.long_align = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_ALIGN:
			ctrl.long_align = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_ARRAY:
			ctrl.yytext_is_array = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_ಸೂಚಕ:
			ctrl.yytext_is_array = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_ECS:
			ctrl.useecs = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_ECS:
			ctrl.useecs = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_EMIT:
			ctrl.emit = arg;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_ಶೀರ್ಷಿಕೆ_FILE:
			env.headerfilename = arg;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_META_ECS:
			ctrl.usemecs = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_META_ECS:
			ctrl.usemecs = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    ಅಕ್ಷರ   *def;
			    ಅಕ್ಷರ buf2[4096];

			    ಗಾಗಿ (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    ಮುಂದುವರಿ;
			    ಆದರೆ (*def == '\0')
				    def = "1";

			    snprintf(buf2, ಗಾತ್ರ(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_READ:
			ctrl.use_read = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_ರಾಶಿ:
			ctrl.ರಾಶಿ_ಬಳಸಿದ = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_STDINIT:
			ctrl.do_stdinit = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_YYCLASS:
			ctrl.yyclass = arg;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_YYLINENO:
			ctrl.do_yylineno = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_YYWRAP:
			ctrl.do_yywrap = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_YYMORE:
			ctrl.yymore_really_ಬಳಸಿದ = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_YYMORE:
			ctrl.yymore_really_ಬಳಸಿದ = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_REJECT:
			ctrl.reject_really_ಬಳಸಿದ = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_REJECT:
			ctrl.reject_really_ಬಳಸಿದ = false;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_NO_YY_ತಳ್ಳು_STATE:
			ctrl.no_yy_ತಳ್ಳು_state = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YY_ತೆಗೆ_STATE:
			ctrl.no_yy_ತೆಗೆ_state = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YY_ತುದಿ_STATE:
			ctrl.no_yy_ತುದಿ_state = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YY_ಪರಿಶೀಲನೆ_ಬಫರ್:
			ctrl.no_yy_ಪರಿಶೀಲನೆ_ಬಫರ್ = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YY_ಪರಿಶೀಲನೆ_ಬೈಟುಗಳು:
			ctrl.no_yy_ಪರಿಶೀಲನೆ_ಬೈಟುಗಳು = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YY_ಪರಿಶೀಲನೆ_STRING:
			ctrl.no_yy_ಪರಿಶೀಲನೆ_string = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYGET_ಪಠ್ಯ:
			ctrl.no_yyget_ಪಠ್ಯ = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYGET_ಸ್ತಂಭ:
			ctrl.no_yyget_ಸ್ತಂಭ = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYSET_ಸ್ತಂಭ:
			ctrl.no_yyset_ಸ್ತಂಭ = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYGET_ಒಳ:
			ctrl.no_yyget_ಒಳ = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYSET_ಒಳ:
			ctrl.no_yyset_ಒಳ = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYGET_ಹೊರಹೋಗು:
			ctrl.no_yyget_ಹೊರಹೋಗು = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYSET_ಹೊರಹೋಗು:
			ctrl.no_yyset_ಹೊರಹೋಗು = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_YYSET_DEBUG:
			ctrl.no_ಗಣ_debug = true;
			ನಿಲ್ಲಿಸು;

		    ಸ್ಥಿತಿ OPT_HEX:
			env.trace_hex = true;
                        ನಿಲ್ಲಿಸು;
		    ಸ್ಥಿತಿ OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        ನಿಲ್ಲಿಸು;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	ಅಂಕೆ_ಒಳಹರಿವು_files = argc - optind;
	ಒಳಹರಿವು_files = argv + optind;
	ಗಣ_ಒಳಹರಿವು_file (ಅಂಕೆ_ಒಳಹರಿವು_files > 0 ? ಒಳಹರಿವು_files[0] : ಖಾಲಿ);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	ಅಂಕೆ_ನಿಯಮಗಳು = ಅಂಕೆ_eof_ನಿಯಮಗಳು = default_ನಿಯಮ = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = ಅಂಕೆ_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	ಅಂಕೆ_backing_ಮೇಲೆ = onesp = numprots = 0;
	variable_trailing_context_ನಿಯಮಗಳು = bol_needed = false;

	linenum = sectnum = 1;
	firstprot = NIL;

	/* Used in mkprot() so that the first proto goes in slot 1
	 * of the proto queue.
	 */
	lastprot = 1;

	ಗಣ_ಮೇಲೆ_initial_allocations ();
}


/* readin - read in the rules section of the input file(s) */

ಶೂನ್ಯ readin (ಶೂನ್ಯ)
{
	ಅಕ್ಷರ buf[256];

	ಸಾಲು_directive_ಹೊರಹೋಗು(ಖಾಲಿ, infilename, linenum);

	ಆದರೆ (yyparse ()) {
		pinpoint_ಸಂದೇಶ (_("fatal parse error"));
		flexend (1);
	}

	ಆದರೆ (syntaxerror)
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

	ಆದರೆ (tablesext)
		gentables = false;

	ಆದರೆ (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	ಆದರೆ (tablesext) {
		FILE   *tablesout;
		ರಚನೆ yytbl_hdr hdr;
		ಅಕ್ಷರ   *pname = 0;
		size_t  nbytes = 0;

		ಆದರೆ (!tablesfilename) {
			nbytes = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ) + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (tablesfile_template) + 2;
			tablesfilename = pname = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ);
		}

		ಆದರೆ ((tablesout = fopen (tablesfilename, "w")) == ಖಾಲಿ)
			lerr (_("could not create %s"), tablesfilename);
		ಬಿಡುಗಡೆ(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ) + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ ("tables") + 2;
		tablesname = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ);
		yytbl_hdr_init (&hdr, flex_ಆವೃತ್ತಿ, tablesname);

		ಆದರೆ (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	ಆದರೆ (env.skelname && (skelfile = fopen (env.skelname, "r")) == ಖಾಲಿ)
		lerr (_("can't open skeleton file %s"), env.skelname);

	ಆದರೆ (strchr(ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ, '[') || strchr(ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	ಆದರೆ (env.did_outfilename)
		ಸಾಲು_directive_ಹೊರಹೋಗು (stdout, ಖಾಲಿ, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	ಆದರೆ( ತುದಿ_buf.elts)
		outn((ಅಕ್ಷರ*) ತುದಿ_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	ಸಾಲು_directive_ಹೊರಹೋಗು(ಖಾಲಿ, ಖಾಲಿ, 0);

	/* User may want to set the scanner prototype */
	ಆದರೆ (ctrl.yydecl != ಖಾಲಿ) {
		ಹೊರಹೋಗು_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	ಆದರೆ (ctrl.userinit != ಖಾಲಿ) {
		ಹೊರಹೋಗು_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	ಆದರೆ (ctrl.preaction != ಖಾಲಿ) {
		ಹೊರಹೋಗು_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	ಆದರೆ (ctrl.postaction != ಖಾಲಿ) {
		ಹೊರಹೋಗು_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	ಹೊರಹೋಗು_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	ಆದರೆ (userdef_buf.elts)
		outn ((ಅಕ್ಷರ *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	ಆದರೆ (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	ಆದರೆ (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	ಆದರೆ (env.backing_ಮೇಲೆ_report) {
		ctrl.backing_ಮೇಲೆ_file = fopen (backing_name, "w");
		ಆದರೆ (ctrl.backing_ಮೇಲೆ_file == ಖಾಲಿ)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	ಇಲ್ಲದಿದ್ದರೆ
		ctrl.backing_ಮೇಲೆ_file = ಖಾಲಿ;

	ಆದರೆ (ctrl.yymore_really_ಬಳಸಿದ == true)
		yymore_ಬಳಸಿದ = true;
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.yymore_really_ಬಳಸಿದ == false)
		yymore_ಬಳಸಿದ = false;

	ಆದರೆ (ctrl.reject_really_ಬಳಸಿದ == true)
		reject = true;
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.reject_really_ಬಳಸಿದ == false)
		reject = false;

	ಆದರೆ (env.performance_hint > 0) {
		ಆದರೆ (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		ಆದರೆ (env.performance_hint > 1) {
			ಆದರೆ (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			ಆದರೆ (yymore_ಬಳಸಿದ)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		ಆದರೆ (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		ಆದರೆ (variable_trailing_context_ನಿಯಮಗಳು)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	ಆದರೆ (reject)
		real_reject = true;

	ಆದರೆ (variable_trailing_context_ನಿಯಮಗಳು)
		reject = true;

	ಆದರೆ ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		ಆದರೆ (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		ಇಲ್ಲದಿದ್ದರೆ
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	ಆದರೆ (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	ಇಲ್ಲದಿದ್ದರೆ
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	ಆದರೆ (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, ಗಾತ್ರ(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		ರಚನೆ Buf tmpbuf;
		ಪೂರ್ಣಾಂಕ i;
		buf_init(&tmpbuf, ಗಾತ್ರ(ಅಕ್ಷರ));
		ಗಾಗಿ (i = 1; i <= lastsc; i++) {
			ಅಕ್ಷರ *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(fmt) + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = ಸ್ಮರಣೆ_ಕೊಡು(strsz);
			ಆದರೆ (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			ಬಿಡುಗಡೆ(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		ಹೊರಹೋಗು_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	ಆದರೆ (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	ಆದರೆ (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	ಆದರೆ (extra_type != ಖಾಲಿ)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	ಆದರೆ (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		ಆದರೆ (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	ಆದರೆ (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	ಆದರೆ (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	ಆದರೆ (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	ಆದರೆ (yymore_ಬಳಸಿದ)
		visible_define ( "M4_MODE_YYMORE_USED");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	ಆದರೆ (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	ಆದರೆ (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	ಆದರೆ (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	ಆದರೆ (variable_trailing_context_ನಿಯಮಗಳು) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} ಇಲ್ಲದಿದ್ದರೆ {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	ಆದರೆ (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	ಆದರೆ (ctrl.reject_really_ಬಳಸಿದ)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	ಆದರೆ (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	ಆದರೆ (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	ಆದರೆ (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	ಇಲ್ಲದಿದ್ದರೆ
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	ಆದರೆ (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	ಆದರೆ (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	ಆದರೆ (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	ಆದರೆ (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	ಆದರೆ (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_GENTABLES");
	ಆದರೆ (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	ಆದರೆ (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	ಆದರೆ (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	ಆದರೆ (ctrl.yyclass != ಖಾಲಿ) {
		visible_define ( "M4_MODE_YYCLASS");
		ಹೊರಹೋಗು_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	ಆದರೆ (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	ಆದರೆ (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	ಆದರೆ (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_YYWRAP");

	ಆದರೆ (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	ಆದರೆ (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	ಆದರೆ (is_default_backend()) {
		ಆದರೆ (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} ಇಲ್ಲದಿದ್ದರೆ {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	ಆದರೆ (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	ಆದರೆ (ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ != ಖಾಲಿ)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ);

	ಆದರೆ (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	ಆದರೆ (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	ಆದರೆ (ctrl.yyterminate != ಖಾಲಿ)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	ಆದರೆ (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	ಆದರೆ (ctrl.no_yy_ತಳ್ಳು_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	ಆದರೆ (ctrl.no_yy_ತೆಗೆ_state)
		visible_define("M4_YY_NO_POP_STATE");
	ಆದರೆ (ctrl.no_yy_ತುದಿ_state)
		visible_define("M4_YY_NO_TOP_STATE");
	ಆದರೆ (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	ಆದರೆ (ctrl.no_yy_ಪರಿಶೀಲನೆ_ಬಫರ್)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	ಆದರೆ (ctrl.no_yy_ಪರಿಶೀಲನೆ_ಬೈಟುಗಳು)
		visible_define("M4_YY_NO_SCAN_BYTES");
	ಆದರೆ (ctrl.no_yy_ಪರಿಶೀಲನೆ_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	ಆದರೆ (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	ಆದರೆ (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	ಆದರೆ (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	ಆದರೆ (ctrl.no_yyget_ಪಠ್ಯ)
		visible_define("M4_YY_NO_GET_TEXT");
	ಆದರೆ (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	ಆದರೆ (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	ಆದರೆ (ctrl.no_yyget_ಸ್ತಂಭ)
		visible_define("M4_YY_NO_GET_COLUMN");
	ಆದರೆ (ctrl.no_yyset_ಸ್ತಂಭ)
		visible_define("M4_YY_NO_SET_COLUMN");
	ಆದರೆ (ctrl.no_yyget_ಒಳ)
		visible_define("M4_YY_NO_GET_IN");
	ಆದರೆ (ctrl.no_yyset_ಒಳ)
		visible_define("M4_YY_NO_SET_IN");
	ಆದರೆ (ctrl.no_yyget_ಹೊರಹೋಗು)
		visible_define("M4_YY_NO_GET_OUT");
	ಆದರೆ (ctrl.no_yyset_ಹೊರಹೋಗು)
		visible_define("M4_YY_NO_SET_OUT");
	ಆದರೆ (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	ಆದರೆ (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	ಆದರೆ (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	ಆದರೆ (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	ಆದರೆ (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	ಆದರೆ (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	ಆದರೆ (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	ಆದರೆ (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	ಆದರೆ (ctrl.no_ಗಣ_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	ಆದರೆ (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	ಆದರೆ (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	ಆದರೆ (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	ಆದರೆ (ctrl.ರಾಶಿ_ಬಳಸಿದ)
		visible_define("M4_YY_STACK_USED");

	ಆದರೆ (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	ಇಲ್ಲದಿದ್ದರೆ
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	ಹೊರಹೋಗು ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

ಶೂನ್ಯ ಗಣ_ಮೇಲೆ_initial_allocations (ಶೂನ್ಯ)
{
	ಗರಿಷ್ಠ_mns = (ctrl.long_align ? ಗರಿಷ್ಠ_MNS_LONG : ಗರಿಷ್ಠ_MNS);
	current_mns = INITIAL_MNS;
	firstst = allocate_integer_array (current_mns);
	lastst = allocate_integer_array (current_mns);
	finalst = allocate_integer_array (current_mns);
	transchar = allocate_integer_array (current_mns);
	trans1 = allocate_integer_array (current_mns);
	trans2 = allocate_integer_array (current_mns);
	accptnum = allocate_integer_array (current_mns);
	assoc_ನಿಯಮ = allocate_integer_array (current_mns);
	state_type = allocate_integer_array (current_mns);

	current_max_ನಿಯಮಗಳು = INITIAL_MAX_ನಿಯಮಗಳು;
	ನಿಯಮ_type = allocate_integer_array (current_max_ನಿಯಮಗಳು);
	ನಿಯಮ_linenum = allocate_integer_array (current_max_ನಿಯಮಗಳು);
	ನಿಯಮ_useful = allocate_array(current_max_ನಿಯಮಗಳು, ಗಾತ್ರ(ಅಕ್ಷರ));
	ನಿಯಮ_has_nl = allocate_array(current_max_ನಿಯಮಗಳು, ಗಾತ್ರ(ಅಕ್ಷರ));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, ಗಾತ್ರ(ಅಕ್ಷರ));
	sceof = allocate_array(current_max_scs, ಗಾತ್ರ(ಅಕ್ಷರ));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, ಗಾತ್ರ(ಅಕ್ಷರ));

	current_max_ccl_tbl_ಗಾತ್ರ = INITIAL_MAX_CCL_TBL_ಗಾತ್ರ;
	ccltbl = allocate_Character_array (current_max_ccl_tbl_ಗಾತ್ರ);

	current_max_dfa_ಗಾತ್ರ = INITIAL_MAX_DFA_ಗಾತ್ರ;

	current_max_xpairs = INITIAL_MAX_XPAIRS;
	nxt = allocate_integer_array (current_max_xpairs);
	chk = allocate_integer_array (current_max_xpairs);

	current_max_template_xpairs = INITIAL_MAX_TEMPLATE_XPAIRS;
	tnxt = allocate_integer_array (current_max_template_xpairs);

	current_max_dfas = INITIAL_MAX_DFAS;
	ತಳ = allocate_integer_array (current_max_dfas);
	def = allocate_integer_array (current_max_dfas);
	dfasiz = allocate_integer_array (current_max_dfas);
	accsiz = allocate_integer_array (current_max_dfas);
	dhash = allocate_integer_array (current_max_dfas);
	dss = allocate_int_ptr_array (current_max_dfas);
	dfaacc = allocate_array(current_max_dfas,
		ಗಾತ್ರ(ಒಕ್ಕೂಟ dfaacc_union));

	nultrans = ಖಾಲಿ;
}


ಶೂನ್ಯ usage (ಶೂನ್ಯ)
{
	FILE   *f = stdout;

	ಆದರೆ (!env.did_outfilename) {
		snprintf (outfile_ಮಾರ್ಗ, ಗಾತ್ರ(outfile_ಮಾರ್ಗ), outfile_template,
			  ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ, suffix());
		env.outfilename = outfile_ಮಾರ್ಗ;
	}

	fprintf (f, _("Usage: %s [OPTIONS] [FILE]...\n"), ಕಾರ್ಯಕ್ರಮ_name);
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
		 backing_name, "flex", outfile_ಮಾರ್ಗ, "flex");

}
