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


#अन्तर्भाव "flexdef.h"
#अन्तर्भाव "version.h"
#अन्तर्भाव "options.h"
#अन्तर्भाव "tables.h"
#अन्तर्भाव "parse.h"

स्थिर वर्ण flex_version[] = FLEX_VERSION;

/* declare functions that have forward references */

शून्य flexinit(पूर्णाङ्क, वर्ण **);
शून्य readin(शून्य);
शून्य set_up_initial_allocations(शून्य);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
पूर्णाङ्क     yymore_used, reject, real_reject, continued_action, in_rule;
पूर्णाङ्क     datapos, dataline, linenum;
FILE   *skelfile = रिक्त;
पूर्णाङ्क     skel_ind = 0;
वर्ण   *action_array;
पूर्णाङ्क     action_size, defs1_offset, prolog_offset, action_offset,
	action_index;
वर्ण   *infilename = रिक्त;
वर्ण   *extra_type = रिक्त;
पूर्णाङ्क     onestate[ONE_राशिः_SIZE], onesym[ONE_राशिः_SIZE];
पूर्णाङ्क     onenext[ONE_राशिः_SIZE], onedef[ONE_राशिः_SIZE], onesp;
पूर्णाङ्क     maximum_mns, current_mns, current_max_rules;
पूर्णाङ्क     अङ्कः_rules, अङ्कः_eof_rules, default_rule, lastnfa;
पूर्णाङ्क    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
पूर्णाङ्क    *accptnum, *assoc_rule, *state_type;
पूर्णाङ्क    *rule_type, *rule_linenum;
पूर्णाङ्क     current_state_type;
bool    variable_trailing_context_rules;
पूर्णाङ्क     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
पूर्णाङ्क     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];
पूर्णाङ्क     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
पूर्णाङ्क     tecbck[CSIZE + 1];
पूर्णाङ्क     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
वर्ण   *scxclu, *sceof;
पूर्णाङ्क     current_max_scs;
ध्रुव वर्ण **scname;
पूर्णाङ्क     current_max_dfa_size, current_max_xpairs;
पूर्णाङ्क     current_max_template_xpairs, current_max_dfas;
पूर्णाङ्क     lastdfa, *nxt, *chk, *tnxt;
पूर्णाङ्क    *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
सङ्घ dfaacc_union *dfaacc;
पूर्णाङ्क    *accsiz, *dhash, numas;
पूर्णाङ्क     numsnpairs, jambase, jamstate;
पूर्णाङ्क     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
पूर्णाङ्क     current_maxccls, current_max_ccl_tbl_size;
unsigned वर्ण   *ccltbl;
वर्ण    nmstr[MAXLINE];
पूर्णाङ्क     sectnum, nummt, hshcol, dfaeql, numeps, eps2, अङ्कः_reallocs, nmval;
पूर्णाङ्क     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
पूर्णाङ्क     अङ्कः_backing_up, bol_needed;
पूर्णाङ्क     end_of_buffer_state;
वर्ण  **निवेशः_files;
पूर्णाङ्क     अङ्कः_निवेशः_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
वर्ण   *rule_useful, *rule_has_nl, *ccl_has_nl;
पूर्णाङ्क     nlch = '\n';

bool    tablesext, tablesverify, gentables;
वर्ण   *tablesfilename=0,*tablesname=0;
संरचना yytbl_writer tableswr;
size_t footprint;

संरचना ctrl_bundle_t ctrl;
संरचना env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
वर्ण   *program_name = "flex";

स्थिर ध्रुव वर्ण outfile_template[] = "lex.%s.%s";
स्थिर ध्रुव वर्ण *backing_name = "lex.backup";
स्थिर ध्रुव वर्ण tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
बाह्य FILE* yyout;

स्थिर वर्ण outfile_path[MAXLINE];
स्थिर पूर्णाङ्क outfile_created = 0;
स्थिर पूर्णाङ्क _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
ध्रुव वर्ण *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
ध्रुव वर्ण *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
स्थिर पूर्णाङ्क preproc_level = 1000;

पूर्णाङ्क flex_main (पूर्णाङ्क argc, वर्ण *argv[]);

पूर्णाङ्क flex_main (पूर्णाङ्क argc, वर्ण *argv[])
{
	पूर्णाङ्क     i, exit_status, child_status;
	पूर्णाङ्क	did_eof_rule = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_status = setjmp (flex_main_jmp_buf);
	सचे (exit_status){
		सचे (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		याव (wait(&child_status) > 0){
			सचे (!WIFEXITED (child_status)
			    || WEXITSTATUS (child_status) != 0){
				/* report an error of a child
				 */
				सचे( exit_status <= 1 )
					exit_status = 2;

			}
		}
		पटिनिवत्त exit_status - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	अत्थाय (i = 1; i <= अङ्कः_rules; ++i)
		सचे (!rule_useful[i] && i != default_rule)
			पङ्क्तिः_warning (_("rule cannot be matched"),
				      rule_linenum[i]);

	सचे (ctrl.spprdflt && !reject && rule_useful[default_rule])
		पङ्क्तिः_warning (_
			      ("-s option given but default rule can be matched"),
			      rule_linenum[default_rule]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	सचे (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	अञ्ञथा {
		visible_define ( "M4_MODE_NO_NULTRANS");
		सचे (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		अञ्ञथा
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		सचे (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		अञ्ञथा
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	out ("\n");

	comment("START of Flex-generated definitions\n");
	out_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", अङ्कः_rules);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", अङ्कः_rules + 1);
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

	पङ्क्तिः_directive_out (stdout, रिक्त, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	out (&action_array[prolog_offset]);

	पङ्क्तिः_directive_out (stdout, रिक्त, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	out (&action_array[action_offset]);

	पङ्क्तिः_directive_out (stdout, रिक्त, linenum);

	/* generate cases for any missing EOF rules */
	अत्थाय (i = 1; i <= lastsc; ++i)
		सचे (!sceof[i]) {
			out_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			out ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_rule = true;
		}

	सचे (did_eof_rule) {
		out ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	पङ्क्तिः_directive_out (stdout, infilename, linenum);

	सचे (sectnum == 3) {
		OUT_BEGIN_CODE ();
                सचे (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(शून्य) flexscan ();	/* copy remainder of input to output */
                सचे (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		OUT_END_CODE ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	पटिनिवत्त 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
पूर्णाङ्क main (पूर्णाङ्क argc, वर्ण *argv[])
{
#सचे defined(ENABLE_NLS) && ENABLE_NLS
#सचे HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif
#endif

	पटिनिवत्त flex_main (argc, argv);
}

/* Set up the output filter chain. */

शून्य initialize_output_filters(शून्य)
{
	ध्रुव वर्ण * m4 = रिक्त;

	output_chain = filter_create_int(रिक्त, filter_tee_header, env.headerfilename);
	सचे ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (वर्ण *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, रिक्त);

	/* For debugging, only run the requested number of filters. */
	सचे (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

शून्य check_options (शून्य)
{
	पूर्णाङ्क     i;

	सचे (ctrl.lex_compat) {
		सचे (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		सचे (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		सचे (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#सचे 0
	/* This makes no sense whatsoever. I'm removing it. */
	सचे (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_used = true;
#endif

	सचे (ctrl.csize == trit_unspecified) {
		सचे ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		अञ्ञथा
			ctrl.csize = CSIZE;
	}

	सचे (ctrl.interactive == trit_unspecified) {
		सचे (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		अञ्ञथा
			ctrl.interactive = trit_true;
	}

	सचे (ctrl.fulltbl || ctrl.fullspd) {
		सचे (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		सचे (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		सचे (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		सचे (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	सचे (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	सचे (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	सचे (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	सचे (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	सचे (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		अत्थाय (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	अञ्ञथा {
		/* Put everything in its own equivalence class. */
		अत्थाय (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	सचे (!env.use_stdout) {
		FILE   *prev_stdout;

		सचे (!env.did_outfilename) {
			snprintf (outfile_path, परिमाण(outfile_path), outfile_template,
				  ctrl.prefix, suffix());

			env.outfilename = outfile_path;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		सचे (prev_stdout == रिक्त)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

शून्य flexend (पूर्णाङ्क exit_status)
{
	स्थिर पूर्णाङ्क called_before = -1;	/* prevent infinite recursion. */
	पूर्णाङ्क     tblsiz;

	सचे (++called_before)
		FLEX_EXIT (exit_status);

	सचे (ctrl.yyclass != रिक्त && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	सचे (skelfile != रिक्त) {
		सचे (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		अञ्ञथा सचे (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	सचे (exit_status != 0 && outfile_created) {
		सचे (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		अञ्ञथा सचे ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		अञ्ञथा सचे (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	सचे (env.backing_up_report && ctrl.backing_up_file) {
		सचे (अङ्कः_backing_up == 0)
			fprintf (ctrl.backing_up_file, _("No backing up.\n"));
		अञ्ञथा सचे (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_up_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 अङ्कः_backing_up);
		अञ्ञथा
			fprintf (ctrl.backing_up_file,
				 _("Compressed tables always back up.\n"));

		सचे (ferror (ctrl.backing_up_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		अञ्ञथा सचे (fclose (ctrl.backing_up_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	सचे (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 program_name, flex_version);

		fprintf (stderr, _("  scanner options: -"));

		सचे (ctrl.C_plus_plus)
			putc ('+', stderr);
		सचे (env.backing_up_report)
			putc ('b', stderr);
		सचे (ctrl.ddebug)
			putc ('d', stderr);
		सचे (sf_case_ins())
			putc ('i', stderr);
		सचे (ctrl.lex_compat)
			putc ('l', stderr);
		सचे (ctrl.posix_compat)
			putc ('X', stderr);
		सचे (env.performance_hint > 0)
			putc ('p', stderr);
		सचे (env.performance_hint > 1)
			putc ('p', stderr);
		सचे (ctrl.spprdflt)
			putc ('s', stderr);
		सचे (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        सचे (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        सचे (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		सचे (env.use_stdout)
			putc ('t', stderr);
		सचे (env.printstats)
			putc ('v', stderr);	/* always true! */
		सचे (env.nowarn)
			putc ('w', stderr);
		सचे (ctrl.interactive == trit_false)
			putc ('B', stderr);
		सचे (ctrl.interactive == trit_true)
			putc ('I', stderr);
		सचे (!ctrl.gen_पङ्क्तिः_dirs)
			putc ('L', stderr);
		सचे (env.trace)
			putc ('T', stderr);

		सचे (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		सचे (ctrl.csize == 128)
			putc ('7', stderr);
		अञ्ञथा
			putc ('8', stderr);

		fprintf (stderr, " -C");

		सचे (ctrl.long_align)
			putc ('a', stderr);
		सचे (ctrl.fulltbl)
			putc ('f', stderr);
		सचे (ctrl.fullspd)
			putc ('F', stderr);
		सचे (ctrl.useecs)
			putc ('e', stderr);
		सचे (ctrl.usemecs)
			putc ('m', stderr);
		सचे (ctrl.use_read)
			putc ('r', stderr);

		सचे (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		सचे (env.skelname != रिक्त)
			fprintf (stderr, " -S%s", env.skelname);

		सचे (strcmp (ctrl.prefix, "yy"))
			fprintf (stderr, " -P%s", ctrl.prefix);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 अङ्कः_rules + अङ्कः_eof_rules -
			 1 /* - 1 for def. rule */ );

		सचे (अङ्कः_backing_up == 0)
			fprintf (stderr, _("  No backing up\n"));
		अञ्ञथा सचे (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 अङ्कः_backing_up);
		अञ्ञथा
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		सचे (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		सचे (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		अञ्ञथा
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

		सचे (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		अञ्ञथा {
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

		सचे (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		सचे (ctrl.usemecs) {
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
			 अङ्कः_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_status);
}


/* flexinit - initialize flex */

शून्य flexinit (पूर्णाङ्क argc, वर्ण **argv)
{
	पूर्णाङ्क     i, sawcmpflag, rv, optind;
	वर्ण   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', परिमाण(ctrl));
	syntaxerror = false;
	yymore_used = continued_action = false;
	in_rule = reject = false;
	ctrl.yymore_really_used = ctrl.reject_really_used = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_पङ्क्तिः_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.prefix = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = रिक्त;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_size = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_size);
	defs1_offset = prolog_offset = action_offset = action_index = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, परिमाण (वर्ण));	/* one long string */
	buf_init (&शिखरम्_buf, परिमाण (वर्ण));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	program_name = argv[0];

	सचे (program_name != रिक्त &&
	    program_name[strlen (program_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	सचे (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	याव ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		सचे (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 program_name);
			FLEX_EXIT (1);
		}

		विकल्प ((गणना flexopt_flag_t) rv) {
		    पक्ष OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			भङ्ग;

		    पक्ष OPT_BATCH:
			ctrl.interactive = trit_false;
			भङ्ग;

		    पक्ष OPT_BACKUP:
			env.backing_up_report = trit_true;
			भङ्ग;

		    पक्ष OPT_BACKUP_FILE:
			env.backing_up_report = true;
                        backing_name = arg;
			भङ्ग;

		    पक्ष OPT_DONOTHING:
			भङ्ग;

		    पक्ष OPT_COMPRESSION:
			सचे (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			अत्थाय (i = 0; arg && arg[i] != '\0'; i++)
				विकल्प (arg[i]) {
				    पक्ष 'a':
					ctrl.long_align = true;
					भङ्ग;

				    पक्ष 'e':
					ctrl.useecs = true;
					भङ्ग;

				    पक्ष 'F':
					ctrl.fullspd = true;
					भङ्ग;

				    पक्ष 'f':
					ctrl.fulltbl = true;
					भङ्ग;

				    पक्ष 'm':
					ctrl.usemecs = true;
					भङ्ग;

				    पक्ष 'r':
					ctrl.use_read = true;
					भङ्ग;

				    स्वभाव:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					भङ्ग;
				}
			भङ्ग;

		    पक्ष OPT_DEBUG:
			ctrl.ddebug = true;
			भङ्ग;

		    पक्ष OPT_NO_DEBUG:
			ctrl.ddebug = false;
			भङ्ग;

		    पक्ष OPT_FULL:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			भङ्ग;

		    पक्ष OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			भङ्ग;

		    पक्ष OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    पक्ष OPT_INTERACTIVE:
			ctrl.interactive = true;
			भङ्ग;

		    पक्ष OPT_CASE_INSENSITIVE:
			sf_set_case_ins(true);
			भङ्ग;

		    पक्ष OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			भङ्ग;

		    पक्ष OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			भङ्ग;

		    पक्ष OPT_PREPROC_LEVEL:
			preproc_level = (पूर्णाङ्क) strtol(arg,रिक्त,0);
			भङ्ग;

		    पक्ष OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			भङ्ग;

		    पक्ष OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			भङ्ग;

		    पक्ष OPT_NO_पङ्क्तिः:
			ctrl.gen_पङ्क्तिः_dirs = false;
			भङ्ग;

		    पक्ष OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			भङ्ग;

		    पक्ष OPT_PREFIX:
			ctrl.prefix = arg;
			भङ्ग;

		    पक्ष OPT_PERF_REPORT:
			++env.performance_hint;
			भङ्ग;

		    पक्ष OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			भङ्ग;

		    पक्ष OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			भङ्ग;

		    पक्ष OPT_REENTRANT:
			ctrl.reentrant = true;
			भङ्ग;

		    पक्ष OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			भङ्ग;

		    पक्ष OPT_SKEL:
			env.skelname = arg;
			भङ्ग;

		    पक्ष OPT_DEFAULT:
			ctrl.spprdflt = false;
			भङ्ग;

		    पक्ष OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			भङ्ग;

		    पक्ष OPT_STDOUT:
			env.use_stdout = true;
			भङ्ग;

		    पक्ष OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			भङ्ग;

		    पक्ष OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			भङ्ग;

		    पक्ष OPT_TABLES_VERIFY:
			tablesverify = true;
			भङ्ग;

		    पक्ष OPT_TRACE:
			env.trace = true;
			भङ्ग;

		    पक्ष OPT_VERBOSE:
			env.printstats = true;
			भङ्ग;

		    पक्ष OPT_VERSION:
			printf ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_version);
			FLEX_EXIT (0);

		    पक्ष OPT_WARN:
			env.nowarn = false;
			भङ्ग;

		    पक्ष OPT_NO_WARN:
			env.nowarn = true;
			भङ्ग;

		    पक्ष OPT_7BIT:
			ctrl.csize = 128;
			भङ्ग;

		    पक्ष OPT_8BIT:
			ctrl.csize = CSIZE;
			भङ्ग;

		    पक्ष OPT_ALIGN:
			ctrl.long_align = true;
			भङ्ग;

		    पक्ष OPT_NO_ALIGN:
			ctrl.long_align = false;
			भङ्ग;

		    पक्ष OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			भङ्ग;

		    पक्ष OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			भङ्ग;

		    पक्ष OPT_ARRAY:
			ctrl.yytext_is_array = true;
			भङ्ग;

		    पक्ष OPT_POINTER:
			ctrl.yytext_is_array = false;
			भङ्ग;

		    पक्ष OPT_ECS:
			ctrl.useecs = true;
			भङ्ग;

		    पक्ष OPT_NO_ECS:
			ctrl.useecs = false;
			भङ्ग;

		    पक्ष OPT_EMIT:
			ctrl.emit = arg;
			भङ्ग;

		    पक्ष OPT_HEADER_FILE:
			env.headerfilename = arg;
			भङ्ग;

		    पक्ष OPT_META_ECS:
			ctrl.usemecs = true;
			भङ्ग;

		    पक्ष OPT_NO_META_ECS:
			ctrl.usemecs = false;
			भङ्ग;

		    पक्ष OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    वर्ण   *def;
			    वर्ण buf2[4096];

			    अत्थाय (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    अनुवर्त;
			    सचे (*def == '\0')
				    def = "1";

			    snprintf(buf2, परिमाण(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    भङ्ग;

		    पक्ष OPT_READ:
			ctrl.use_read = true;
			भङ्ग;

		    पक्ष OPT_राशिः:
			ctrl.राशिः_used = true;
			भङ्ग;

		    पक्ष OPT_STDINIT:
			ctrl.do_stdinit = true;
			भङ्ग;

		    पक्ष OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			भङ्ग;

		    पक्ष OPT_YYCLASS:
			ctrl.yyclass = arg;
			भङ्ग;

		    पक्ष OPT_YYLINENO:
			ctrl.do_yylineno = true;
			भङ्ग;

		    पक्ष OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			भङ्ग;

		    पक्ष OPT_YYWRAP:
			ctrl.do_yywrap = true;
			भङ्ग;

		    पक्ष OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			भङ्ग;

		    पक्ष OPT_YYMORE:
			ctrl.yymore_really_used = true;
			भङ्ग;

		    पक्ष OPT_NO_YYMORE:
			ctrl.yymore_really_used = false;
			भङ्ग;

		    पक्ष OPT_REJECT:
			ctrl.reject_really_used = true;
			भङ्ग;

		    पक्ष OPT_NO_REJECT:
			ctrl.reject_really_used = false;
			भङ्ग;

		    पक्ष OPT_NO_YY_प्रक्षिप_STATE:
			ctrl.no_yy_प्रक्षिप_state = true;
			भङ्ग;
		    पक्ष OPT_NO_YY_निष्कासय_STATE:
			ctrl.no_yy_निष्कासय_state = true;
			भङ्ग;
		    पक्ष OPT_NO_YY_शिखरम्_STATE:
			ctrl.no_yy_शिखरम्_state = true;
			भङ्ग;
		    पक्ष OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			भङ्ग;
		    पक्ष OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			भङ्ग;
		    पक्ष OPT_NO_YY_SCAN_BUFFER:
			ctrl.no_yy_scan_buffer = true;
			भङ्ग;
		    पक्ष OPT_NO_YY_SCAN_BYTES:
			ctrl.no_yy_scan_bytes = true;
			भङ्ग;
		    पक्ष OPT_NO_YY_SCAN_STRING:
			ctrl.no_yy_scan_string = true;
			भङ्ग;
		    पक्ष OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			भङ्ग;
		    पक्ष OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			भङ्ग;
		    पक्ष OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			भङ्ग;
		    पक्ष OPT_NO_YYGET_TEXT:
			ctrl.no_yyget_text = true;
			भङ्ग;
		    पक्ष OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			भङ्ग;
		    पक्ष OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			भङ्ग;
		    पक्ष OPT_NO_YYGET_COLUMN:
			ctrl.no_yyget_column = true;
			भङ्ग;
		    पक्ष OPT_NO_YYSET_COLUMN:
			ctrl.no_yyset_column = true;
			भङ्ग;
		    पक्ष OPT_NO_YYGET_IN:
			ctrl.no_yyget_in = true;
			भङ्ग;
		    पक्ष OPT_NO_YYSET_IN:
			ctrl.no_yyset_in = true;
			भङ्ग;
		    पक्ष OPT_NO_YYGET_OUT:
			ctrl.no_yyget_out = true;
			भङ्ग;
		    पक्ष OPT_NO_YYSET_OUT:
			ctrl.no_yyset_out = true;
			भङ्ग;
		    पक्ष OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			भङ्ग;
		    पक्ष OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			भङ्ग;
		    पक्ष OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			भङ्ग;
		    पक्ष OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			भङ्ग;
		    पक्ष OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			भङ्ग;
		    पक्ष OPT_NO_YYSET_DEBUG:
			ctrl.no_set_debug = true;
			भङ्ग;

		    पक्ष OPT_HEX:
			env.trace_hex = true;
                        भङ्ग;
		    पक्ष OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        भङ्ग;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	अङ्कः_निवेशः_files = argc - optind;
	निवेशः_files = argv + optind;
	set_निवेशः_file (अङ्कः_निवेशः_files > 0 ? निवेशः_files[0] : रिक्त);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	अङ्कः_rules = अङ्कः_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = अङ्कः_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	अङ्कः_backing_up = onesp = numprots = 0;
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

शून्य readin (शून्य)
{
	वर्ण buf[256];

	पङ्क्तिः_directive_out(रिक्त, infilename, linenum);

	सचे (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
		flexend (1);
	}

	सचे (syntaxerror)
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

	सचे (tablesext)
		gentables = false;

	सचे (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	सचे (tablesext) {
		FILE   *tablesout;
		संरचना yytbl_hdr hdr;
		वर्ण   *pname = 0;
		size_t  nbytes = 0;

		सचे (!tablesfilename) {
			nbytes = strlen (ctrl.prefix) + strlen (tablesfile_template) + 2;
			tablesfilename = pname = calloc(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.prefix);
		}

		सचे ((tablesout = fopen (tablesfilename, "w")) == रिक्त)
			lerr (_("could not create %s"), tablesfilename);
		मुक्त(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = strlen (ctrl.prefix) + strlen ("tables") + 2;
		tablesname = calloc(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.prefix);
		yytbl_hdr_init (&hdr, flex_version, tablesname);

		सचे (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	सचे (env.skelname && (skelfile = fopen (env.skelname, "r")) == रिक्त)
		lerr (_("can't open skeleton file %s"), env.skelname);

	सचे (strchr(ctrl.prefix, '[') || strchr(ctrl.prefix, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	सचे (env.did_outfilename)
		पङ्क्तिः_directive_out (stdout, रिक्त, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	सचे( शिखरम्_buf.elts)
		outn((वर्ण*) शिखरम्_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	पङ्क्तिः_directive_out(रिक्त, रिक्त, 0);

	/* User may want to set the scanner prototype */
	सचे (ctrl.yydecl != रिक्त) {
		out_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	सचे (ctrl.userinit != रिक्त) {
		out_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	सचे (ctrl.preaction != रिक्त) {
		out_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	सचे (ctrl.postaction != रिक्त) {
		out_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	out_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	सचे (userdef_buf.elts)
		outn ((वर्ण *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	सचे (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	सचे (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	सचे (env.backing_up_report) {
		ctrl.backing_up_file = fopen (backing_name, "w");
		सचे (ctrl.backing_up_file == रिक्त)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	अञ्ञथा
		ctrl.backing_up_file = रिक्त;

	सचे (ctrl.yymore_really_used == true)
		yymore_used = true;
	अञ्ञथा सचे (ctrl.yymore_really_used == false)
		yymore_used = false;

	सचे (ctrl.reject_really_used == true)
		reject = true;
	अञ्ञथा सचे (ctrl.reject_really_used == false)
		reject = false;

	सचे (env.performance_hint > 0) {
		सचे (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		अञ्ञथा सचे (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		सचे (env.performance_hint > 1) {
			सचे (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			सचे (yymore_used)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		सचे (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		सचे (variable_trailing_context_rules)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	सचे (reject)
		real_reject = true;

	सचे (variable_trailing_context_rules)
		reject = true;

	सचे ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		सचे (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		अञ्ञथा सचे (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		अञ्ञथा
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	सचे (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	अञ्ञथा
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	सचे (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, परिमाण(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		संरचना Buf tmpbuf;
		पूर्णाङ्क i;
		buf_init(&tmpbuf, परिमाण(वर्ण));
		अत्थाय (i = 1; i <= lastsc; i++) {
			वर्ण *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = strlen(fmt) + strlen(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = malloc(strsz);
			सचे (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			मुक्त(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		out_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	सचे (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	सचे (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	सचे (extra_type != रिक्त)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	सचे (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		सचे (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	सचे (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	अञ्ञथा सचे (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	सचे (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	सचे (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	सचे (yymore_used)
		visible_define ( "M4_MODE_YYMORE_USED");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	सचे (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	सचे (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	सचे (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	सचे (variable_trailing_context_rules) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} अञ्ञथा {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	सचे (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	सचे (ctrl.reject_really_used)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	सचे (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	सचे (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	सचे (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	अञ्ञथा सचे (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	अञ्ञथा सचे (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	अञ्ञथा
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	सचे (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	सचे (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	सचे (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	सचे (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	सचे (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_GENTABLES");
	सचे (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	सचे (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	सचे (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	सचे (ctrl.yyclass != रिक्त) {
		visible_define ( "M4_MODE_YYCLASS");
		out_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	सचे (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	सचे (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	सचे (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_YYWRAP");

	सचे (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	सचे (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	सचे (is_default_backend()) {
		सचे (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} अञ्ञथा {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	सचे (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	सचे (ctrl.prefix != रिक्त)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.prefix);

	सचे (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	सचे (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	सचे (ctrl.yyterminate != रिक्त)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	सचे (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	सचे (ctrl.no_yy_प्रक्षिप_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	सचे (ctrl.no_yy_निष्कासय_state)
		visible_define("M4_YY_NO_POP_STATE");
	सचे (ctrl.no_yy_शिखरम्_state)
		visible_define("M4_YY_NO_TOP_STATE");
	सचे (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	सचे (ctrl.no_yy_scan_buffer)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	सचे (ctrl.no_yy_scan_bytes)
		visible_define("M4_YY_NO_SCAN_BYTES");
	सचे (ctrl.no_yy_scan_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	सचे (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	सचे (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	सचे (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	सचे (ctrl.no_yyget_text)
		visible_define("M4_YY_NO_GET_TEXT");
	सचे (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	सचे (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	सचे (ctrl.no_yyget_column)
		visible_define("M4_YY_NO_GET_COLUMN");
	सचे (ctrl.no_yyset_column)
		visible_define("M4_YY_NO_SET_COLUMN");
	सचे (ctrl.no_yyget_in)
		visible_define("M4_YY_NO_GET_IN");
	सचे (ctrl.no_yyset_in)
		visible_define("M4_YY_NO_SET_IN");
	सचे (ctrl.no_yyget_out)
		visible_define("M4_YY_NO_GET_OUT");
	सचे (ctrl.no_yyset_out)
		visible_define("M4_YY_NO_SET_OUT");
	सचे (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	सचे (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	सचे (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	सचे (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	सचे (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	सचे (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	सचे (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	सचे (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	सचे (ctrl.no_set_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	सचे (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	सचे (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	सचे (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	सचे (ctrl.राशिः_used)
		visible_define("M4_YY_STACK_USED");

	सचे (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	अञ्ञथा
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	out ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

शून्य set_up_initial_allocations (शून्य)
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
	rule_useful = allocate_array(current_max_rules, परिमाण(वर्ण));
	rule_has_nl = allocate_array(current_max_rules, परिमाण(वर्ण));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, परिमाण(वर्ण));
	sceof = allocate_array(current_max_scs, परिमाण(वर्ण));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, परिमाण(वर्ण));

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
		परिमाण(सङ्घ dfaacc_union));

	nultrans = रिक्त;
}


शून्य usage (शून्य)
{
	FILE   *f = stdout;

	सचे (!env.did_outfilename) {
		snprintf (outfile_path, परिमाण(outfile_path), outfile_template,
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
