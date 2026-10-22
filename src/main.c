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


#அந்தர்பாவ "flexdef.h"
#அந்தர்பாவ "version.h"
#அந்தர்பாவ "options.h"
#அந்தர்பாவ "tables.h"
#அந்தர்பாவ "parse.h"

நிலையான எழுத்து flex_version[] = FLEX_VERSION;

/* declare functions that have forward references */

வெறுமை flexinit(முழு, எழுத்து **);
வெறுமை readin(வெறுமை);
வெறுமை set_up_initial_allocations(வெறுமை);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
முழு     yymore_used, reject, real_reject, continued_action, in_rule;
முழு     datapos, dataline, linenum;
FILE   *skelfile = வெற்று;
முழு     skel_ind = 0;
எழுத்து   *action_array;
முழு     action_size, defs1_offset, prolog_offset, action_offset,
	action_index;
எழுத்து   *infilename = வெற்று;
எழுத்து   *extra_type = வெற்று;
முழு     onestate[ONE_அடுக்கு_SIZE], onesym[ONE_அடுக்கு_SIZE];
முழு     onenext[ONE_அடுக்கு_SIZE], onedef[ONE_அடுக்கு_SIZE], onesp;
முழு     maximum_mns, current_mns, current_max_rules;
முழு     இலக்கம்_rules, இலக்கம்_eof_rules, default_rule, lastnfa;
முழு    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
முழு    *accptnum, *assoc_rule, *state_type;
முழு    *rule_type, *rule_linenum;
முழு     current_state_type;
bool    variable_trailing_context_rules;
முழு     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
முழு     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];
முழு     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
முழு     tecbck[CSIZE + 1];
முழு     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
எழுத்து   *scxclu, *sceof;
முழு     current_max_scs;
மாறிலி எழுத்து **scname;
முழு     current_max_dfa_size, current_max_xpairs;
முழு     current_max_template_xpairs, current_max_dfas;
முழு     lastdfa, *nxt, *chk, *tnxt;
முழு    *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
ஒன்றிப்பு dfaacc_union *dfaacc;
முழு    *accsiz, *dhash, numas;
முழு     numsnpairs, jambase, jamstate;
முழு     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
முழு     current_maxccls, current_max_ccl_tbl_size;
unsigned எழுத்து   *ccltbl;
எழுத்து    nmstr[MAXLINE];
முழு     sectnum, nummt, hshcol, dfaeql, numeps, eps2, இலக்கம்_reallocs, nmval;
முழு     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
முழு     இலக்கம்_backing_up, bol_needed;
முழு     end_of_buffer_state;
எழுத்து  **உள்ளீடு_files;
முழு     இலக்கம்_உள்ளீடு_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
எழுத்து   *rule_useful, *rule_has_nl, *ccl_has_nl;
முழு     nlch = '\n';

bool    tablesext, tablesverify, gentables;
எழுத்து   *tablesfilename=0,*tablesname=0;
கட்டமைப்பு yytbl_writer tableswr;
size_t footprint;

கட்டமைப்பு ctrl_bundle_t ctrl;
கட்டமைப்பு env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
எழுத்து   *program_name = "flex";

நிலையான மாறிலி எழுத்து outfile_template[] = "lex.%s.%s";
நிலையான மாறிலி எழுத்து *backing_name = "lex.backup";
நிலையான மாறிலி எழுத்து tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
வெளி FILE* yyout;

நிலையான எழுத்து outfile_path[MAXLINE];
நிலையான முழு outfile_created = 0;
நிலையான முழு _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
மாறிலி எழுத்து *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
மாறிலி எழுத்து *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
நிலையான முழு preproc_level = 1000;

முழு flex_main (முழு argc, எழுத்து *argv[]);

முழு flex_main (முழு argc, எழுத்து *argv[])
{
	முழு     i, exit_status, child_status;
	முழு	did_eof_rule = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_status = setjmp (flex_main_jmp_buf);
	எனில் (exit_status){
		எனில் (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		போது (wait(&child_status) > 0){
			எனில் (!WIFEXITED (child_status)
			    || WEXITSTATUS (child_status) != 0){
				/* report an error of a child
				 */
				எனில்( exit_status <= 1 )
					exit_status = 2;

			}
		}
		திரும்பு exit_status - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	க்கு (i = 1; i <= இலக்கம்_rules; ++i)
		எனில் (!rule_useful[i] && i != default_rule)
			வரி_warning (_("rule cannot be matched"),
				      rule_linenum[i]);

	எனில் (ctrl.spprdflt && !reject && rule_useful[default_rule])
		வரி_warning (_
			      ("-s option given but default rule can be matched"),
			      rule_linenum[default_rule]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	எனில் (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	இல்லையெனில் {
		visible_define ( "M4_MODE_NO_NULTRANS");
		எனில் (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		இல்லையெனில்
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		எனில் (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		இல்லையெனில்
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	out ("\n");

	comment("START of Flex-generated definitions\n");
	out_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", இலக்கம்_rules);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", இலக்கம்_rules + 1);
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

	வரி_directive_out (stdout, வெற்று, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	out (&action_array[prolog_offset]);

	வரி_directive_out (stdout, வெற்று, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	out (&action_array[action_offset]);

	வரி_directive_out (stdout, வெற்று, linenum);

	/* generate cases for any missing EOF rules */
	க்கு (i = 1; i <= lastsc; ++i)
		எனில் (!sceof[i]) {
			out_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			out ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_rule = true;
		}

	எனில் (did_eof_rule) {
		out ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	வரி_directive_out (stdout, infilename, linenum);

	எனில் (sectnum == 3) {
		OUT_BEGIN_CODE ();
                எனில் (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(வெறுமை) flexscan ();	/* copy remainder of input to output */
                எனில் (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		OUT_END_CODE ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	திரும்பு 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
முழு முதன்மை (முழு argc, எழுத்து *argv[])
{
#எனில் defined(ENABLE_NLS) && ENABLE_NLS
#எனில் HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif
#endif

	திரும்பு flex_main (argc, argv);
}

/* Set up the output filter chain. */

வெறுமை initialize_output_filters(வெறுமை)
{
	மாறிலி எழுத்து * m4 = வெற்று;

	output_chain = filter_create_int(வெற்று, filter_tee_header, env.headerfilename);
	எனில் ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (எழுத்து *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, வெற்று);

	/* For debugging, only run the requested number of filters. */
	எனில் (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

வெறுமை check_options (வெறுமை)
{
	முழு     i;

	எனில் (ctrl.lex_compat) {
		எனில் (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		எனில் (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		எனில் (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#எனில் 0
	/* This makes no sense whatsoever. I'm removing it. */
	எனில் (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_used = true;
#endif

	எனில் (ctrl.csize == trit_unspecified) {
		எனில் ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		இல்லையெனில்
			ctrl.csize = CSIZE;
	}

	எனில் (ctrl.interactive == trit_unspecified) {
		எனில் (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		இல்லையெனில்
			ctrl.interactive = trit_true;
	}

	எனில் (ctrl.fulltbl || ctrl.fullspd) {
		எனில் (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		எனில் (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		எனில் (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		எனில் (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	எனில் (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	எனில் (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	எனில் (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	எனில் (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	எனில் (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		க்கு (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	இல்லையெனில் {
		/* Put everything in its own equivalence class. */
		க்கு (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	எனில் (!env.use_stdout) {
		FILE   *prev_stdout;

		எனில் (!env.did_outfilename) {
			snprintf (outfile_path, அளவு(outfile_path), outfile_template,
				  ctrl.prefix, suffix());

			env.outfilename = outfile_path;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		எனில் (prev_stdout == வெற்று)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

வெறுமை flexend (முழு exit_status)
{
	நிலையான முழு called_before = -1;	/* prevent infinite recursion. */
	முழு     tblsiz;

	எனில் (++called_before)
		FLEX_EXIT (exit_status);

	எனில் (ctrl.yyclass != வெற்று && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	எனில் (skelfile != வெற்று) {
		எனில் (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		இல்லையெனில் எனில் (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	எனில் (exit_status != 0 && outfile_created) {
		எனில் (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		இல்லையெனில் எனில் ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		இல்லையெனில் எனில் (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	எனில் (env.backing_up_report && ctrl.backing_up_file) {
		எனில் (இலக்கம்_backing_up == 0)
			fprintf (ctrl.backing_up_file, _("No backing up.\n"));
		இல்லையெனில் எனில் (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_up_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 இலக்கம்_backing_up);
		இல்லையெனில்
			fprintf (ctrl.backing_up_file,
				 _("Compressed tables always back up.\n"));

		எனில் (ferror (ctrl.backing_up_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		இல்லையெனில் எனில் (fclose (ctrl.backing_up_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	எனில் (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 program_name, flex_version);

		fprintf (stderr, _("  scanner options: -"));

		எனில் (ctrl.C_plus_plus)
			putc ('+', stderr);
		எனில் (env.backing_up_report)
			putc ('b', stderr);
		எனில் (ctrl.ddebug)
			putc ('d', stderr);
		எனில் (sf_case_ins())
			putc ('i', stderr);
		எனில் (ctrl.lex_compat)
			putc ('l', stderr);
		எனில் (ctrl.posix_compat)
			putc ('X', stderr);
		எனில் (env.performance_hint > 0)
			putc ('p', stderr);
		எனில் (env.performance_hint > 1)
			putc ('p', stderr);
		எனில் (ctrl.spprdflt)
			putc ('s', stderr);
		எனில் (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        எனில் (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        எனில் (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		எனில் (env.use_stdout)
			putc ('t', stderr);
		எனில் (env.printstats)
			putc ('v', stderr);	/* always true! */
		எனில் (env.nowarn)
			putc ('w', stderr);
		எனில் (ctrl.interactive == trit_false)
			putc ('B', stderr);
		எனில் (ctrl.interactive == trit_true)
			putc ('I', stderr);
		எனில் (!ctrl.gen_வரி_dirs)
			putc ('L', stderr);
		எனில் (env.trace)
			putc ('T', stderr);

		எனில் (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		எனில் (ctrl.csize == 128)
			putc ('7', stderr);
		இல்லையெனில்
			putc ('8', stderr);

		fprintf (stderr, " -C");

		எனில் (ctrl.long_align)
			putc ('a', stderr);
		எனில் (ctrl.fulltbl)
			putc ('f', stderr);
		எனில் (ctrl.fullspd)
			putc ('F', stderr);
		எனில் (ctrl.useecs)
			putc ('e', stderr);
		எனில் (ctrl.usemecs)
			putc ('m', stderr);
		எனில் (ctrl.use_read)
			putc ('r', stderr);

		எனில் (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		எனில் (env.skelname != வெற்று)
			fprintf (stderr, " -S%s", env.skelname);

		எனில் (strcmp (ctrl.prefix, "yy"))
			fprintf (stderr, " -P%s", ctrl.prefix);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 இலக்கம்_rules + இலக்கம்_eof_rules -
			 1 /* - 1 for def. rule */ );

		எனில் (இலக்கம்_backing_up == 0)
			fprintf (stderr, _("  No backing up\n"));
		இல்லையெனில் எனில் (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 இலக்கம்_backing_up);
		இல்லையெனில்
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		எனில் (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		எனில் (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		இல்லையெனில்
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

		எனில் (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		இல்லையெனில் {
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

		எனில் (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		எனில் (ctrl.usemecs) {
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
			 இலக்கம்_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_status);
}


/* flexinit - initialize flex */

வெறுமை flexinit (முழு argc, எழுத்து **argv)
{
	முழு     i, sawcmpflag, rv, optind;
	எழுத்து   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', அளவு(ctrl));
	syntaxerror = false;
	yymore_used = continued_action = false;
	in_rule = reject = false;
	ctrl.yymore_really_used = ctrl.reject_really_used = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_வரி_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.prefix = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = வெற்று;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_size = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_size);
	defs1_offset = prolog_offset = action_offset = action_index = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, அளவு (எழுத்து));	/* one long string */
	buf_init (&உச்சி_buf, அளவு (எழுத்து));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	program_name = argv[0];

	எனில் (program_name != வெற்று &&
	    program_name[strlen (program_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	எனில் (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	போது ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		எனில் (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 program_name);
			FLEX_EXIT (1);
		}

		தேர்வு ((எண்ணிக்கை flexopt_flag_t) rv) {
		    நிலை OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			நிறுத்து;

		    நிலை OPT_BATCH:
			ctrl.interactive = trit_false;
			நிறுத்து;

		    நிலை OPT_BACKUP:
			env.backing_up_report = trit_true;
			நிறுத்து;

		    நிலை OPT_BACKUP_FILE:
			env.backing_up_report = true;
                        backing_name = arg;
			நிறுத்து;

		    நிலை OPT_DONOTHING:
			நிறுத்து;

		    நிலை OPT_COMPRESSION:
			எனில் (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			க்கு (i = 0; arg && arg[i] != '\0'; i++)
				தேர்வு (arg[i]) {
				    நிலை 'a':
					ctrl.long_align = true;
					நிறுத்து;

				    நிலை 'e':
					ctrl.useecs = true;
					நிறுத்து;

				    நிலை 'F':
					ctrl.fullspd = true;
					நிறுத்து;

				    நிலை 'f':
					ctrl.fulltbl = true;
					நிறுத்து;

				    நிலை 'm':
					ctrl.usemecs = true;
					நிறுத்து;

				    நிலை 'r':
					ctrl.use_read = true;
					நிறுத்து;

				    இயல்பு:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					நிறுத்து;
				}
			நிறுத்து;

		    நிலை OPT_DEBUG:
			ctrl.ddebug = true;
			நிறுத்து;

		    நிலை OPT_NO_DEBUG:
			ctrl.ddebug = false;
			நிறுத்து;

		    நிலை OPT_FULL:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			நிறுத்து;

		    நிலை OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			நிறுத்து;

		    நிலை OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    நிலை OPT_INTERACTIVE:
			ctrl.interactive = true;
			நிறுத்து;

		    நிலை OPT_CASE_INSENSITIVE:
			sf_set_case_ins(true);
			நிறுத்து;

		    நிலை OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			நிறுத்து;

		    நிலை OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			நிறுத்து;

		    நிலை OPT_PREPROC_LEVEL:
			preproc_level = (முழு) strtol(arg,வெற்று,0);
			நிறுத்து;

		    நிலை OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			நிறுத்து;

		    நிலை OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			நிறுத்து;

		    நிலை OPT_NO_வரி:
			ctrl.gen_வரி_dirs = false;
			நிறுத்து;

		    நிலை OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			நிறுத்து;

		    நிலை OPT_PREFIX:
			ctrl.prefix = arg;
			நிறுத்து;

		    நிலை OPT_PERF_REPORT:
			++env.performance_hint;
			நிறுத்து;

		    நிலை OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			நிறுத்து;

		    நிலை OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			நிறுத்து;

		    நிலை OPT_REENTRANT:
			ctrl.reentrant = true;
			நிறுத்து;

		    நிலை OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			நிறுத்து;

		    நிலை OPT_SKEL:
			env.skelname = arg;
			நிறுத்து;

		    நிலை OPT_DEFAULT:
			ctrl.spprdflt = false;
			நிறுத்து;

		    நிலை OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			நிறுத்து;

		    நிலை OPT_STDOUT:
			env.use_stdout = true;
			நிறுத்து;

		    நிலை OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			நிறுத்து;

		    நிலை OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			நிறுத்து;

		    நிலை OPT_TABLES_VERIFY:
			tablesverify = true;
			நிறுத்து;

		    நிலை OPT_TRACE:
			env.trace = true;
			நிறுத்து;

		    நிலை OPT_VERBOSE:
			env.printstats = true;
			நிறுத்து;

		    நிலை OPT_VERSION:
			printf ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_version);
			FLEX_EXIT (0);

		    நிலை OPT_WARN:
			env.nowarn = false;
			நிறுத்து;

		    நிலை OPT_NO_WARN:
			env.nowarn = true;
			நிறுத்து;

		    நிலை OPT_7BIT:
			ctrl.csize = 128;
			நிறுத்து;

		    நிலை OPT_8BIT:
			ctrl.csize = CSIZE;
			நிறுத்து;

		    நிலை OPT_ALIGN:
			ctrl.long_align = true;
			நிறுத்து;

		    நிலை OPT_NO_ALIGN:
			ctrl.long_align = false;
			நிறுத்து;

		    நிலை OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			நிறுத்து;

		    நிலை OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			நிறுத்து;

		    நிலை OPT_ARRAY:
			ctrl.yytext_is_array = true;
			நிறுத்து;

		    நிலை OPT_POINTER:
			ctrl.yytext_is_array = false;
			நிறுத்து;

		    நிலை OPT_ECS:
			ctrl.useecs = true;
			நிறுத்து;

		    நிலை OPT_NO_ECS:
			ctrl.useecs = false;
			நிறுத்து;

		    நிலை OPT_EMIT:
			ctrl.emit = arg;
			நிறுத்து;

		    நிலை OPT_HEADER_FILE:
			env.headerfilename = arg;
			நிறுத்து;

		    நிலை OPT_META_ECS:
			ctrl.usemecs = true;
			நிறுத்து;

		    நிலை OPT_NO_META_ECS:
			ctrl.usemecs = false;
			நிறுத்து;

		    நிலை OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    எழுத்து   *def;
			    எழுத்து buf2[4096];

			    க்கு (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    தொடர்;
			    எனில் (*def == '\0')
				    def = "1";

			    snprintf(buf2, அளவு(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    நிறுத்து;

		    நிலை OPT_READ:
			ctrl.use_read = true;
			நிறுத்து;

		    நிலை OPT_அடுக்கு:
			ctrl.அடுக்கு_used = true;
			நிறுத்து;

		    நிலை OPT_STDINIT:
			ctrl.do_stdinit = true;
			நிறுத்து;

		    நிலை OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			நிறுத்து;

		    நிலை OPT_YYCLASS:
			ctrl.yyclass = arg;
			நிறுத்து;

		    நிலை OPT_YYLINENO:
			ctrl.do_yylineno = true;
			நிறுத்து;

		    நிலை OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			நிறுத்து;

		    நிலை OPT_YYWRAP:
			ctrl.do_yywrap = true;
			நிறுத்து;

		    நிலை OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			நிறுத்து;

		    நிலை OPT_YYMORE:
			ctrl.yymore_really_used = true;
			நிறுத்து;

		    நிலை OPT_NO_YYMORE:
			ctrl.yymore_really_used = false;
			நிறுத்து;

		    நிலை OPT_REJECT:
			ctrl.reject_really_used = true;
			நிறுத்து;

		    நிலை OPT_NO_REJECT:
			ctrl.reject_really_used = false;
			நிறுத்து;

		    நிலை OPT_NO_YY_தள்ளு_STATE:
			ctrl.no_yy_தள்ளு_state = true;
			நிறுத்து;
		    நிலை OPT_NO_YY_எடு_STATE:
			ctrl.no_yy_எடு_state = true;
			நிறுத்து;
		    நிலை OPT_NO_YY_உச்சி_STATE:
			ctrl.no_yy_உச்சி_state = true;
			நிறுத்து;
		    நிலை OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			நிறுத்து;
		    நிலை OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			நிறுத்து;
		    நிலை OPT_NO_YY_SCAN_BUFFER:
			ctrl.no_yy_scan_buffer = true;
			நிறுத்து;
		    நிலை OPT_NO_YY_SCAN_BYTES:
			ctrl.no_yy_scan_bytes = true;
			நிறுத்து;
		    நிலை OPT_NO_YY_SCAN_STRING:
			ctrl.no_yy_scan_string = true;
			நிறுத்து;
		    நிலை OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			நிறுத்து;
		    நிலை OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			நிறுத்து;
		    நிலை OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			நிறுத்து;
		    நிலை OPT_NO_YYGET_TEXT:
			ctrl.no_yyget_text = true;
			நிறுத்து;
		    நிலை OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			நிறுத்து;
		    நிலை OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			நிறுத்து;
		    நிலை OPT_NO_YYGET_COLUMN:
			ctrl.no_yyget_column = true;
			நிறுத்து;
		    நிலை OPT_NO_YYSET_COLUMN:
			ctrl.no_yyset_column = true;
			நிறுத்து;
		    நிலை OPT_NO_YYGET_IN:
			ctrl.no_yyget_in = true;
			நிறுத்து;
		    நிலை OPT_NO_YYSET_IN:
			ctrl.no_yyset_in = true;
			நிறுத்து;
		    நிலை OPT_NO_YYGET_OUT:
			ctrl.no_yyget_out = true;
			நிறுத்து;
		    நிலை OPT_NO_YYSET_OUT:
			ctrl.no_yyset_out = true;
			நிறுத்து;
		    நிலை OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			நிறுத்து;
		    நிலை OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			நிறுத்து;
		    நிலை OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			நிறுத்து;
		    நிலை OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			நிறுத்து;
		    நிலை OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			நிறுத்து;
		    நிலை OPT_NO_YYSET_DEBUG:
			ctrl.no_set_debug = true;
			நிறுத்து;

		    நிலை OPT_HEX:
			env.trace_hex = true;
                        நிறுத்து;
		    நிலை OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        நிறுத்து;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	இலக்கம்_உள்ளீடு_files = argc - optind;
	உள்ளீடு_files = argv + optind;
	set_உள்ளீடு_file (இலக்கம்_உள்ளீடு_files > 0 ? உள்ளீடு_files[0] : வெற்று);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	இலக்கம்_rules = இலக்கம்_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = இலக்கம்_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	இலக்கம்_backing_up = onesp = numprots = 0;
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

வெறுமை readin (வெறுமை)
{
	எழுத்து buf[256];

	வரி_directive_out(வெற்று, infilename, linenum);

	எனில் (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
		flexend (1);
	}

	எனில் (syntaxerror)
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

	எனில் (tablesext)
		gentables = false;

	எனில் (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	எனில் (tablesext) {
		FILE   *tablesout;
		கட்டமைப்பு yytbl_hdr hdr;
		எழுத்து   *pname = 0;
		size_t  nbytes = 0;

		எனில் (!tablesfilename) {
			nbytes = strlen (ctrl.prefix) + strlen (tablesfile_template) + 2;
			tablesfilename = pname = calloc(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.prefix);
		}

		எனில் ((tablesout = fopen (tablesfilename, "w")) == வெற்று)
			lerr (_("could not create %s"), tablesfilename);
		விடுவி(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = strlen (ctrl.prefix) + strlen ("tables") + 2;
		tablesname = calloc(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.prefix);
		yytbl_hdr_init (&hdr, flex_version, tablesname);

		எனில் (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	எனில் (env.skelname && (skelfile = fopen (env.skelname, "r")) == வெற்று)
		lerr (_("can't open skeleton file %s"), env.skelname);

	எனில் (strchr(ctrl.prefix, '[') || strchr(ctrl.prefix, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	எனில் (env.did_outfilename)
		வரி_directive_out (stdout, வெற்று, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	எனில்( உச்சி_buf.elts)
		outn((எழுத்து*) உச்சி_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	வரி_directive_out(வெற்று, வெற்று, 0);

	/* User may want to set the scanner prototype */
	எனில் (ctrl.yydecl != வெற்று) {
		out_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	எனில் (ctrl.userinit != வெற்று) {
		out_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	எனில் (ctrl.preaction != வெற்று) {
		out_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	எனில் (ctrl.postaction != வெற்று) {
		out_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	out_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	எனில் (userdef_buf.elts)
		outn ((எழுத்து *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	எனில் (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	எனில் (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	எனில் (env.backing_up_report) {
		ctrl.backing_up_file = fopen (backing_name, "w");
		எனில் (ctrl.backing_up_file == வெற்று)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	இல்லையெனில்
		ctrl.backing_up_file = வெற்று;

	எனில் (ctrl.yymore_really_used == true)
		yymore_used = true;
	இல்லையெனில் எனில் (ctrl.yymore_really_used == false)
		yymore_used = false;

	எனில் (ctrl.reject_really_used == true)
		reject = true;
	இல்லையெனில் எனில் (ctrl.reject_really_used == false)
		reject = false;

	எனில் (env.performance_hint > 0) {
		எனில் (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		இல்லையெனில் எனில் (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		எனில் (env.performance_hint > 1) {
			எனில் (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			எனில் (yymore_used)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		எனில் (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		எனில் (variable_trailing_context_rules)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	எனில் (reject)
		real_reject = true;

	எனில் (variable_trailing_context_rules)
		reject = true;

	எனில் ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		எனில் (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		இல்லையெனில் எனில் (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		இல்லையெனில்
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	எனில் (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	இல்லையெனில்
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	எனில் (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, அளவு(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		கட்டமைப்பு Buf tmpbuf;
		முழு i;
		buf_init(&tmpbuf, அளவு(எழுத்து));
		க்கு (i = 1; i <= lastsc; i++) {
			எழுத்து *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = strlen(fmt) + strlen(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = malloc(strsz);
			எனில் (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			விடுவி(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		out_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	எனில் (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	எனில் (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	எனில் (extra_type != வெற்று)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	எனில் (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		எனில் (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	எனில் (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	இல்லையெனில் எனில் (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	எனில் (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	எனில் (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	எனில் (yymore_used)
		visible_define ( "M4_MODE_YYMORE_USED");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	எனில் (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	எனில் (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	எனில் (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	எனில் (variable_trailing_context_rules) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} இல்லையெனில் {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	எனில் (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	எனில் (ctrl.reject_really_used)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	எனில் (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	எனில் (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	எனில் (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	இல்லையெனில் எனில் (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	இல்லையெனில் எனில் (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	இல்லையெனில்
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	எனில் (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	எனில் (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	எனில் (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	எனில் (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	எனில் (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_GENTABLES");
	எனில் (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	எனில் (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	எனில் (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	எனில் (ctrl.yyclass != வெற்று) {
		visible_define ( "M4_MODE_YYCLASS");
		out_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	எனில் (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	எனில் (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	எனில் (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_YYWRAP");

	எனில் (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	எனில் (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	எனில் (is_default_backend()) {
		எனில் (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} இல்லையெனில் {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	எனில் (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	எனில் (ctrl.prefix != வெற்று)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.prefix);

	எனில் (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	எனில் (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	எனில் (ctrl.yyterminate != வெற்று)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	எனில் (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	எனில் (ctrl.no_yy_தள்ளு_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	எனில் (ctrl.no_yy_எடு_state)
		visible_define("M4_YY_NO_POP_STATE");
	எனில் (ctrl.no_yy_உச்சி_state)
		visible_define("M4_YY_NO_TOP_STATE");
	எனில் (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	எனில் (ctrl.no_yy_scan_buffer)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	எனில் (ctrl.no_yy_scan_bytes)
		visible_define("M4_YY_NO_SCAN_BYTES");
	எனில் (ctrl.no_yy_scan_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	எனில் (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	எனில் (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	எனில் (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	எனில் (ctrl.no_yyget_text)
		visible_define("M4_YY_NO_GET_TEXT");
	எனில் (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	எனில் (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	எனில் (ctrl.no_yyget_column)
		visible_define("M4_YY_NO_GET_COLUMN");
	எனில் (ctrl.no_yyset_column)
		visible_define("M4_YY_NO_SET_COLUMN");
	எனில் (ctrl.no_yyget_in)
		visible_define("M4_YY_NO_GET_IN");
	எனில் (ctrl.no_yyset_in)
		visible_define("M4_YY_NO_SET_IN");
	எனில் (ctrl.no_yyget_out)
		visible_define("M4_YY_NO_GET_OUT");
	எனில் (ctrl.no_yyset_out)
		visible_define("M4_YY_NO_SET_OUT");
	எனில் (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	எனில் (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	எனில் (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	எனில் (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	எனில் (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	எனில் (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	எனில் (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	எனில் (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	எனில் (ctrl.no_set_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	எனில் (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	எனில் (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	எனில் (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	எனில் (ctrl.அடுக்கு_used)
		visible_define("M4_YY_STACK_USED");

	எனில் (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	இல்லையெனில்
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	out ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

வெறுமை set_up_initial_allocations (வெறுமை)
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
	rule_useful = allocate_array(current_max_rules, அளவு(எழுத்து));
	rule_has_nl = allocate_array(current_max_rules, அளவு(எழுத்து));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, அளவு(எழுத்து));
	sceof = allocate_array(current_max_scs, அளவு(எழுத்து));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, அளவு(எழுத்து));

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
		அளவு(ஒன்றிப்பு dfaacc_union));

	nultrans = வெற்று;
}


வெறுமை usage (வெறுமை)
{
	FILE   *f = stdout;

	எனில் (!env.did_outfilename) {
		snprintf (outfile_path, அளவு(outfile_path), outfile_template,
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
