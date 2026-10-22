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


#ଅନ୍ତର୍ଭାଵ "flexdef.h"
#ଅନ୍ତର୍ଭାଵ "version.h"
#ଅନ୍ତର୍ଭାଵ "options.h"
#ଅନ୍ତର୍ଭାଵ "tables.h"
#ଅନ୍ତର୍ଭାଵ "parse.h"

ସ୍ଥିର ଅକ୍ଷର flex_version[] = FLEX_VERSION;

/* declare functions that have forward references */

ଶୂନ୍ୟ flexinit(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ଅକ୍ଷର **);
ଶୂନ୍ୟ readin(ଶୂନ୍ୟ);
ଶୂନ୍ୟ set_up_initial_allocations(ଶୂନ୍ୟ);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     yymore_used, reject, real_reject, continued_action, in_rule;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     datapos, dataline, linenum;
FILE   *skelfile = ଖାଲି;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     skel_ind = 0;
ଅକ୍ଷର   *action_array;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     action_size, defs1_offset, prolog_offset, action_offset,
	action_index;
ଅକ୍ଷର   *infilename = ଖାଲି;
ଅକ୍ଷର   *extra_type = ଖାଲି;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     onestate[ONE_ଗଦା_SIZE], onesym[ONE_ଗଦା_SIZE];
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     onenext[ONE_ଗଦା_SIZE], onedef[ONE_ଗଦା_SIZE], onesp;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     maximum_mns, current_mns, current_max_rules;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     ଅଙ୍କ_rules, ଅଙ୍କ_eof_rules, default_rule, lastnfa;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା    *accptnum, *assoc_rule, *state_type;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା    *rule_type, *rule_linenum;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     current_state_type;
bool    variable_trailing_context_rules;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     tecbck[CSIZE + 1];
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
ଅକ୍ଷର   *scxclu, *sceof;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     current_max_scs;
ଅଚଳ ଅକ୍ଷର **scname;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     current_max_dfa_size, current_max_xpairs;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     current_max_template_xpairs, current_max_dfas;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     lastdfa, *nxt, *chk, *tnxt;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା    *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
ସଂଘ dfaacc_union *dfaacc;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା    *accsiz, *dhash, numas;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     numsnpairs, jambase, jamstate;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     current_maxccls, current_max_ccl_tbl_size;
unsigned ଅକ୍ଷର   *ccltbl;
ଅକ୍ଷର    nmstr[MAXLINE];
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     sectnum, nummt, hshcol, dfaeql, numeps, eps2, ଅଙ୍କ_reallocs, nmval;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     ଅଙ୍କ_backing_up, bol_needed;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     end_of_buffer_state;
ଅକ୍ଷର  **ନିବେଶ_files;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     ଅଙ୍କ_ନିବେଶ_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
ଅକ୍ଷର   *rule_useful, *rule_has_nl, *ccl_has_nl;
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     nlch = '\n';

bool    tablesext, tablesverify, gentables;
ଅକ୍ଷର   *tablesfilename=0,*tablesname=0;
ସଂରଚନା yytbl_writer tableswr;
size_t footprint;

ସଂରଚନା ctrl_bundle_t ctrl;
ସଂରଚନା env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
ଅକ୍ଷର   *program_name = "flex";

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର outfile_template[] = "lex.%s.%s";
ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *backing_name = "lex.backup";
ସ୍ଥିର ଅଚଳ ଅକ୍ଷର tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
ବାହ୍ୟ FILE* yyout;

ସ୍ଥିର ଅକ୍ଷର outfile_path[MAXLINE];
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା outfile_created = 0;
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
ଅଚଳ ଅକ୍ଷର *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
ଅଚଳ ଅକ୍ଷର *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା preproc_level = 1000;

ପୂର୍ଣ୍ଣସଂଖ୍ୟା flex_main (ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର *argv[]);

ପୂର୍ଣ୍ଣସଂଖ୍ୟା flex_main (ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର *argv[])
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     i, exit_status, child_status;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା	did_eof_rule = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_status = setjmp (flex_main_jmp_buf);
	ଯଦି (exit_status){
		ଯଦି (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		ଯେତେବେଳେ (wait(&child_status) > 0){
			ଯଦି (!WIFEXITED (child_status)
			    || WEXITSTATUS (child_status) != 0){
				/* report an error of a child
				 */
				ଯଦି( exit_status <= 1 )
					exit_status = 2;

			}
		}
		ଫେରନ୍ତୁ exit_status - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	ପାଇଁ (i = 1; i <= ଅଙ୍କ_rules; ++i)
		ଯଦି (!rule_useful[i] && i != default_rule)
			ଧାଡ଼ି_warning (_("rule cannot be matched"),
				      rule_linenum[i]);

	ଯଦି (ctrl.spprdflt && !reject && rule_useful[default_rule])
		ଧାଡ଼ି_warning (_
			      ("-s option given but default rule can be matched"),
			      rule_linenum[default_rule]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	ଯଦି (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	ଅନ୍ୟଥା {
		visible_define ( "M4_MODE_NO_NULTRANS");
		ଯଦି (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		ଅନ୍ୟଥା
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		ଯଦି (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		ଅନ୍ୟଥା
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	out ("\n");

	comment("START of Flex-generated definitions\n");
	out_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", ଅଙ୍କ_rules);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", ଅଙ୍କ_rules + 1);
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

	ଧାଡ଼ି_directive_out (stdout, ଖାଲି, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	out (&action_array[prolog_offset]);

	ଧାଡ଼ି_directive_out (stdout, ଖାଲି, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	out (&action_array[action_offset]);

	ଧାଡ଼ି_directive_out (stdout, ଖାଲି, linenum);

	/* generate cases for any missing EOF rules */
	ପାଇଁ (i = 1; i <= lastsc; ++i)
		ଯଦି (!sceof[i]) {
			out_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			out ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_rule = true;
		}

	ଯଦି (did_eof_rule) {
		out ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	ଧାଡ଼ି_directive_out (stdout, infilename, linenum);

	ଯଦି (sectnum == 3) {
		OUT_BEGIN_CODE ();
                ଯଦି (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(ଶୂନ୍ୟ) flexscan ();	/* copy remainder of input to output */
                ଯଦି (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		OUT_END_CODE ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	ଫେରନ୍ତୁ 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର *argv[])
{
#ଯଦି defined(ENABLE_NLS) && ENABLE_NLS
#ଯଦି HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif
#endif

	ଫେରନ୍ତୁ flex_main (argc, argv);
}

/* Set up the output filter chain. */

ଶୂନ୍ୟ initialize_output_filters(ଶୂନ୍ୟ)
{
	ଅଚଳ ଅକ୍ଷର * m4 = ଖାଲି;

	output_chain = filter_create_int(ଖାଲି, filter_tee_header, env.headerfilename);
	ଯଦି ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (ଅକ୍ଷର *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, ଖାଲି);

	/* For debugging, only run the requested number of filters. */
	ଯଦି (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

ଶୂନ୍ୟ check_options (ଶୂନ୍ୟ)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     i;

	ଯଦି (ctrl.lex_compat) {
		ଯଦି (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		ଯଦି (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		ଯଦି (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#ଯଦି 0
	/* This makes no sense whatsoever. I'm removing it. */
	ଯଦି (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_used = true;
#endif

	ଯଦି (ctrl.csize == trit_unspecified) {
		ଯଦି ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		ଅନ୍ୟଥା
			ctrl.csize = CSIZE;
	}

	ଯଦି (ctrl.interactive == trit_unspecified) {
		ଯଦି (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		ଅନ୍ୟଥା
			ctrl.interactive = trit_true;
	}

	ଯଦି (ctrl.fulltbl || ctrl.fullspd) {
		ଯଦି (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		ଯଦି (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		ଯଦି (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		ଯଦି (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	ଯଦି (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	ଯଦି (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	ଯଦି (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	ଯଦି (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	ଯଦି (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		ପାଇଁ (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	ଅନ୍ୟଥା {
		/* Put everything in its own equivalence class. */
		ପାଇଁ (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	ଯଦି (!env.use_stdout) {
		FILE   *prev_stdout;

		ଯଦି (!env.did_outfilename) {
			snprintf (outfile_path, ଆକାର(outfile_path), outfile_template,
				  ctrl.prefix, suffix());

			env.outfilename = outfile_path;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		ଯଦି (prev_stdout == ଖାଲି)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

ଶୂନ୍ୟ flexend (ପୂର୍ଣ୍ଣସଂଖ୍ୟା exit_status)
{
	ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା called_before = -1;	/* prevent infinite recursion. */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     tblsiz;

	ଯଦି (++called_before)
		FLEX_EXIT (exit_status);

	ଯଦି (ctrl.yyclass != ଖାଲି && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	ଯଦି (skelfile != ଖାଲି) {
		ଯଦି (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		ଅନ୍ୟଥା ଯଦି (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	ଯଦି (exit_status != 0 && outfile_created) {
		ଯଦି (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		ଅନ୍ୟଥା ଯଦି ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		ଅନ୍ୟଥା ଯଦି (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	ଯଦି (env.backing_up_report && ctrl.backing_up_file) {
		ଯଦି (ଅଙ୍କ_backing_up == 0)
			fprintf (ctrl.backing_up_file, _("No backing up.\n"));
		ଅନ୍ୟଥା ଯଦି (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_up_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 ଅଙ୍କ_backing_up);
		ଅନ୍ୟଥା
			fprintf (ctrl.backing_up_file,
				 _("Compressed tables always back up.\n"));

		ଯଦି (ferror (ctrl.backing_up_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		ଅନ୍ୟଥା ଯଦି (fclose (ctrl.backing_up_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	ଯଦି (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 program_name, flex_version);

		fprintf (stderr, _("  scanner options: -"));

		ଯଦି (ctrl.C_plus_plus)
			putc ('+', stderr);
		ଯଦି (env.backing_up_report)
			putc ('b', stderr);
		ଯଦି (ctrl.ddebug)
			putc ('d', stderr);
		ଯଦି (sf_case_ins())
			putc ('i', stderr);
		ଯଦି (ctrl.lex_compat)
			putc ('l', stderr);
		ଯଦି (ctrl.posix_compat)
			putc ('X', stderr);
		ଯଦି (env.performance_hint > 0)
			putc ('p', stderr);
		ଯଦି (env.performance_hint > 1)
			putc ('p', stderr);
		ଯଦି (ctrl.spprdflt)
			putc ('s', stderr);
		ଯଦି (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        ଯଦି (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        ଯଦି (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		ଯଦି (env.use_stdout)
			putc ('t', stderr);
		ଯଦି (env.printstats)
			putc ('v', stderr);	/* always true! */
		ଯଦି (env.nowarn)
			putc ('w', stderr);
		ଯଦି (ctrl.interactive == trit_false)
			putc ('B', stderr);
		ଯଦି (ctrl.interactive == trit_true)
			putc ('I', stderr);
		ଯଦି (!ctrl.gen_ଧାଡ଼ି_dirs)
			putc ('L', stderr);
		ଯଦି (env.trace)
			putc ('T', stderr);

		ଯଦି (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		ଯଦି (ctrl.csize == 128)
			putc ('7', stderr);
		ଅନ୍ୟଥା
			putc ('8', stderr);

		fprintf (stderr, " -C");

		ଯଦି (ctrl.long_align)
			putc ('a', stderr);
		ଯଦି (ctrl.fulltbl)
			putc ('f', stderr);
		ଯଦି (ctrl.fullspd)
			putc ('F', stderr);
		ଯଦି (ctrl.useecs)
			putc ('e', stderr);
		ଯଦି (ctrl.usemecs)
			putc ('m', stderr);
		ଯଦି (ctrl.use_read)
			putc ('r', stderr);

		ଯଦି (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		ଯଦି (env.skelname != ଖାଲି)
			fprintf (stderr, " -S%s", env.skelname);

		ଯଦି (strcmp (ctrl.prefix, "yy"))
			fprintf (stderr, " -P%s", ctrl.prefix);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 ଅଙ୍କ_rules + ଅଙ୍କ_eof_rules -
			 1 /* - 1 for def. rule */ );

		ଯଦି (ଅଙ୍କ_backing_up == 0)
			fprintf (stderr, _("  No backing up\n"));
		ଅନ୍ୟଥା ଯଦି (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 ଅଙ୍କ_backing_up);
		ଅନ୍ୟଥା
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		ଯଦି (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		ଯଦି (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		ଅନ୍ୟଥା
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

		ଯଦି (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		ଅନ୍ୟଥା {
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

		ଯଦି (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		ଯଦି (ctrl.usemecs) {
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
			 ଅଙ୍କ_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_status);
}


/* flexinit - initialize flex */

ଶୂନ୍ୟ flexinit (ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର **argv)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     i, sawcmpflag, rv, optind;
	ଅକ୍ଷର   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', ଆକାର(ctrl));
	syntaxerror = false;
	yymore_used = continued_action = false;
	in_rule = reject = false;
	ctrl.yymore_really_used = ctrl.reject_really_used = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_ଧାଡ଼ି_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.prefix = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = ଖାଲି;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_size = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_size);
	defs1_offset = prolog_offset = action_offset = action_index = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, ଆକାର (ଅକ୍ଷର));	/* one long string */
	buf_init (&ଶୀର୍ଷ_buf, ଆକାର (ଅକ୍ଷର));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	program_name = argv[0];

	ଯଦି (program_name != ଖାଲି &&
	    program_name[strlen (program_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	ଯଦି (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	ଯେତେବେଳେ ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		ଯଦି (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 program_name);
			FLEX_EXIT (1);
		}

		ବାଛ ((ଗଣନା flexopt_flag_t) rv) {
		    ସ୍ଥିତି OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_BATCH:
			ctrl.interactive = trit_false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_BACKUP:
			env.backing_up_report = trit_true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_BACKUP_FILE:
			env.backing_up_report = true;
                        backing_name = arg;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_DONOTHING:
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_COMPRESSION:
			ଯଦି (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			ପାଇଁ (i = 0; arg && arg[i] != '\0'; i++)
				ବାଛ (arg[i]) {
				    ସ୍ଥିତି 'a':
					ctrl.long_align = true;
					ଭାଙ୍ଗ;

				    ସ୍ଥିତି 'e':
					ctrl.useecs = true;
					ଭାଙ୍ଗ;

				    ସ୍ଥିତି 'F':
					ctrl.fullspd = true;
					ଭାଙ୍ଗ;

				    ସ୍ଥିତି 'f':
					ctrl.fulltbl = true;
					ଭାଙ୍ଗ;

				    ସ୍ଥିତି 'm':
					ctrl.usemecs = true;
					ଭାଙ୍ଗ;

				    ସ୍ଥିତି 'r':
					ctrl.use_read = true;
					ଭାଙ୍ଗ;

				    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					ଭାଙ୍ଗ;
				}
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_DEBUG:
			ctrl.ddebug = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_DEBUG:
			ctrl.ddebug = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_FULL:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    ସ୍ଥିତି OPT_INTERACTIVE:
			ctrl.interactive = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_CASE_INSENSITIVE:
			sf_set_case_ins(true);
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_PREPROC_LEVEL:
			preproc_level = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) strtol(arg,ଖାଲି,0);
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_ଧାଡ଼ି:
			ctrl.gen_ଧାଡ଼ି_dirs = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_PREFIX:
			ctrl.prefix = arg;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_PERF_REPORT:
			++env.performance_hint;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_REENTRANT:
			ctrl.reentrant = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_SKEL:
			env.skelname = arg;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_DEFAULT:
			ctrl.spprdflt = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_STDOUT:
			env.use_stdout = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_TABLES_VERIFY:
			tablesverify = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_TRACE:
			env.trace = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_VERBOSE:
			env.printstats = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_VERSION:
			printf ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_version);
			FLEX_EXIT (0);

		    ସ୍ଥିତି OPT_WARN:
			env.nowarn = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_WARN:
			env.nowarn = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_7BIT:
			ctrl.csize = 128;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_8BIT:
			ctrl.csize = CSIZE;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_ALIGN:
			ctrl.long_align = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_ALIGN:
			ctrl.long_align = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_ARRAY:
			ctrl.yytext_is_array = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_POINTER:
			ctrl.yytext_is_array = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_ECS:
			ctrl.useecs = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_ECS:
			ctrl.useecs = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_EMIT:
			ctrl.emit = arg;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_HEADER_FILE:
			env.headerfilename = arg;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_META_ECS:
			ctrl.usemecs = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_META_ECS:
			ctrl.usemecs = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    ଅକ୍ଷର   *def;
			    ଅକ୍ଷର buf2[4096];

			    ପାଇଁ (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    ଜାରି;
			    ଯଦି (*def == '\0')
				    def = "1";

			    snprintf(buf2, ଆକାର(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_READ:
			ctrl.use_read = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_ଗଦା:
			ctrl.ଗଦା_used = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_STDINIT:
			ctrl.do_stdinit = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_YYCLASS:
			ctrl.yyclass = arg;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_YYLINENO:
			ctrl.do_yylineno = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_YYWRAP:
			ctrl.do_yywrap = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_YYMORE:
			ctrl.yymore_really_used = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_YYMORE:
			ctrl.yymore_really_used = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_REJECT:
			ctrl.reject_really_used = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_REJECT:
			ctrl.reject_really_used = false;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_NO_YY_ଠେଲ_STATE:
			ctrl.no_yy_ଠେଲ_state = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YY_କାଢ଼_STATE:
			ctrl.no_yy_କାଢ଼_state = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YY_ଶୀର୍ଷ_STATE:
			ctrl.no_yy_ଶୀର୍ଷ_state = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YY_SCAN_BUFFER:
			ctrl.no_yy_scan_buffer = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YY_SCAN_BYTES:
			ctrl.no_yy_scan_bytes = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YY_SCAN_STRING:
			ctrl.no_yy_scan_string = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYGET_TEXT:
			ctrl.no_yyget_text = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYGET_COLUMN:
			ctrl.no_yyget_column = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYSET_COLUMN:
			ctrl.no_yyset_column = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYGET_IN:
			ctrl.no_yyget_in = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYSET_IN:
			ctrl.no_yyset_in = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYGET_OUT:
			ctrl.no_yyget_out = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYSET_OUT:
			ctrl.no_yyset_out = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_YYSET_DEBUG:
			ctrl.no_set_debug = true;
			ଭାଙ୍ଗ;

		    ସ୍ଥିତି OPT_HEX:
			env.trace_hex = true;
                        ଭାଙ୍ଗ;
		    ସ୍ଥିତି OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        ଭାଙ୍ଗ;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	ଅଙ୍କ_ନିବେଶ_files = argc - optind;
	ନିବେଶ_files = argv + optind;
	set_ନିବେଶ_file (ଅଙ୍କ_ନିବେଶ_files > 0 ? ନିବେଶ_files[0] : ଖାଲି);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	ଅଙ୍କ_rules = ଅଙ୍କ_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = ଅଙ୍କ_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	ଅଙ୍କ_backing_up = onesp = numprots = 0;
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

ଶୂନ୍ୟ readin (ଶୂନ୍ୟ)
{
	ଅକ୍ଷର buf[256];

	ଧାଡ଼ି_directive_out(ଖାଲି, infilename, linenum);

	ଯଦି (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
		flexend (1);
	}

	ଯଦି (syntaxerror)
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

	ଯଦି (tablesext)
		gentables = false;

	ଯଦି (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	ଯଦି (tablesext) {
		FILE   *tablesout;
		ସଂରଚନା yytbl_hdr hdr;
		ଅକ୍ଷର   *pname = 0;
		size_t  nbytes = 0;

		ଯଦି (!tablesfilename) {
			nbytes = strlen (ctrl.prefix) + strlen (tablesfile_template) + 2;
			tablesfilename = pname = calloc(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.prefix);
		}

		ଯଦି ((tablesout = fopen (tablesfilename, "w")) == ଖାଲି)
			lerr (_("could not create %s"), tablesfilename);
		ମୁକ୍ତ(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = strlen (ctrl.prefix) + strlen ("tables") + 2;
		tablesname = calloc(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.prefix);
		yytbl_hdr_init (&hdr, flex_version, tablesname);

		ଯଦି (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	ଯଦି (env.skelname && (skelfile = fopen (env.skelname, "r")) == ଖାଲି)
		lerr (_("can't open skeleton file %s"), env.skelname);

	ଯଦି (strchr(ctrl.prefix, '[') || strchr(ctrl.prefix, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	ଯଦି (env.did_outfilename)
		ଧାଡ଼ି_directive_out (stdout, ଖାଲି, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	ଯଦି( ଶୀର୍ଷ_buf.elts)
		outn((ଅକ୍ଷର*) ଶୀର୍ଷ_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	ଧାଡ଼ି_directive_out(ଖାଲି, ଖାଲି, 0);

	/* User may want to set the scanner prototype */
	ଯଦି (ctrl.yydecl != ଖାଲି) {
		out_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	ଯଦି (ctrl.userinit != ଖାଲି) {
		out_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	ଯଦି (ctrl.preaction != ଖାଲି) {
		out_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	ଯଦି (ctrl.postaction != ଖାଲି) {
		out_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	out_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	ଯଦି (userdef_buf.elts)
		outn ((ଅକ୍ଷର *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	ଯଦି (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	ଯଦି (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	ଯଦି (env.backing_up_report) {
		ctrl.backing_up_file = fopen (backing_name, "w");
		ଯଦି (ctrl.backing_up_file == ଖାଲି)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	ଅନ୍ୟଥା
		ctrl.backing_up_file = ଖାଲି;

	ଯଦି (ctrl.yymore_really_used == true)
		yymore_used = true;
	ଅନ୍ୟଥା ଯଦି (ctrl.yymore_really_used == false)
		yymore_used = false;

	ଯଦି (ctrl.reject_really_used == true)
		reject = true;
	ଅନ୍ୟଥା ଯଦି (ctrl.reject_really_used == false)
		reject = false;

	ଯଦି (env.performance_hint > 0) {
		ଯଦି (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		ଅନ୍ୟଥା ଯଦି (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		ଯଦି (env.performance_hint > 1) {
			ଯଦି (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			ଯଦି (yymore_used)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		ଯଦି (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		ଯଦି (variable_trailing_context_rules)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	ଯଦି (reject)
		real_reject = true;

	ଯଦି (variable_trailing_context_rules)
		reject = true;

	ଯଦି ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		ଯଦି (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		ଅନ୍ୟଥା ଯଦି (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		ଅନ୍ୟଥା
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	ଯଦି (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	ଅନ୍ୟଥା
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	ଯଦି (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, ଆକାର(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		ସଂରଚନା Buf tmpbuf;
		ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
		buf_init(&tmpbuf, ଆକାର(ଅକ୍ଷର));
		ପାଇଁ (i = 1; i <= lastsc; i++) {
			ଅକ୍ଷର *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = strlen(fmt) + strlen(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = malloc(strsz);
			ଯଦି (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			ମୁକ୍ତ(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		out_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	ଯଦି (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	ଯଦି (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	ଯଦି (extra_type != ଖାଲି)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	ଯଦି (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		ଯଦି (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	ଯଦି (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	ଅନ୍ୟଥା ଯଦି (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	ଯଦି (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	ଯଦି (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	ଯଦି (yymore_used)
		visible_define ( "M4_MODE_YYMORE_USED");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	ଯଦି (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	ଯଦି (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	ଯଦି (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	ଯଦି (variable_trailing_context_rules) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} ଅନ୍ୟଥା {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	ଯଦି (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	ଯଦି (ctrl.reject_really_used)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	ଯଦି (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	ଯଦି (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	ଯଦି (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	ଅନ୍ୟଥା ଯଦି (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	ଅନ୍ୟଥା ଯଦି (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	ଅନ୍ୟଥା
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	ଯଦି (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	ଯଦି (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	ଯଦି (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	ଯଦି (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	ଯଦି (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_GENTABLES");
	ଯଦି (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	ଯଦି (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	ଯଦି (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	ଯଦି (ctrl.yyclass != ଖାଲି) {
		visible_define ( "M4_MODE_YYCLASS");
		out_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	ଯଦି (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	ଯଦି (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	ଯଦି (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_YYWRAP");

	ଯଦି (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	ଯଦି (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	ଯଦି (is_default_backend()) {
		ଯଦି (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} ଅନ୍ୟଥା {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	ଯଦି (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	ଯଦି (ctrl.prefix != ଖାଲି)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.prefix);

	ଯଦି (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	ଯଦି (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	ଯଦି (ctrl.yyterminate != ଖାଲି)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	ଯଦି (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	ଯଦି (ctrl.no_yy_ଠେଲ_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	ଯଦି (ctrl.no_yy_କାଢ଼_state)
		visible_define("M4_YY_NO_POP_STATE");
	ଯଦି (ctrl.no_yy_ଶୀର୍ଷ_state)
		visible_define("M4_YY_NO_TOP_STATE");
	ଯଦି (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	ଯଦି (ctrl.no_yy_scan_buffer)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	ଯଦି (ctrl.no_yy_scan_bytes)
		visible_define("M4_YY_NO_SCAN_BYTES");
	ଯଦି (ctrl.no_yy_scan_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	ଯଦି (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	ଯଦି (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	ଯଦି (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	ଯଦି (ctrl.no_yyget_text)
		visible_define("M4_YY_NO_GET_TEXT");
	ଯଦି (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	ଯଦି (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	ଯଦି (ctrl.no_yyget_column)
		visible_define("M4_YY_NO_GET_COLUMN");
	ଯଦି (ctrl.no_yyset_column)
		visible_define("M4_YY_NO_SET_COLUMN");
	ଯଦି (ctrl.no_yyget_in)
		visible_define("M4_YY_NO_GET_IN");
	ଯଦି (ctrl.no_yyset_in)
		visible_define("M4_YY_NO_SET_IN");
	ଯଦି (ctrl.no_yyget_out)
		visible_define("M4_YY_NO_GET_OUT");
	ଯଦି (ctrl.no_yyset_out)
		visible_define("M4_YY_NO_SET_OUT");
	ଯଦି (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	ଯଦି (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	ଯଦି (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	ଯଦି (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	ଯଦି (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	ଯଦି (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	ଯଦି (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	ଯଦି (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	ଯଦି (ctrl.no_set_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	ଯଦି (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	ଯଦି (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	ଯଦି (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	ଯଦି (ctrl.ଗଦା_used)
		visible_define("M4_YY_STACK_USED");

	ଯଦି (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	ଅନ୍ୟଥା
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	out ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

ଶୂନ୍ୟ set_up_initial_allocations (ଶୂନ୍ୟ)
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
	rule_useful = allocate_array(current_max_rules, ଆକାର(ଅକ୍ଷର));
	rule_has_nl = allocate_array(current_max_rules, ଆକାର(ଅକ୍ଷର));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, ଆକାର(ଅକ୍ଷର));
	sceof = allocate_array(current_max_scs, ଆକାର(ଅକ୍ଷର));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, ଆକାର(ଅକ୍ଷର));

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
		ଆକାର(ସଂଘ dfaacc_union));

	nultrans = ଖାଲି;
}


ଶୂନ୍ୟ usage (ଶୂନ୍ୟ)
{
	FILE   *f = stdout;

	ଯଦି (!env.did_outfilename) {
		snprintf (outfile_path, ଆକାର(outfile_path), outfile_template,
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
