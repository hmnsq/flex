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


#અન્તર્ભાવ "flexdef.h"
#અન્તર્ભાવ "version.h"
#અન્તર્ભાવ "options.h"
#અન્તર્ભાવ "tables.h"
#અન્તર્ભાવ "parse.h"

સ્થિર અક્ષર flex_version[] = FLEX_VERSION;

/* declare functions that have forward references */

શૂન્ય flexinit(પૂર્ણાંક, અક્ષર **);
શૂન્ય readin(શૂન્ય);
શૂન્ય set_up_initial_allocations(શૂન્ય);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
પૂર્ણાંક     yymore_used, reject, real_reject, continued_action, in_rule;
પૂર્ણાંક     datapos, dataline, linenum;
FILE   *skelfile = ખાલી;
પૂર્ણાંક     skel_ind = 0;
અક્ષર   *action_array;
પૂર્ણાંક     action_size, defs1_offset, prolog_offset, action_offset,
	action_index;
અક્ષર   *infilename = ખાલી;
અક્ષર   *extra_type = ખાલી;
પૂર્ણાંક     onestate[ONE_ઢગલો_SIZE], onesym[ONE_ઢગલો_SIZE];
પૂર્ણાંક     onenext[ONE_ઢગલો_SIZE], onedef[ONE_ઢગલો_SIZE], onesp;
પૂર્ણાંક     maximum_mns, current_mns, current_max_rules;
પૂર્ણાંક     અંક_rules, અંક_eof_rules, default_rule, lastnfa;
પૂર્ણાંક    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
પૂર્ણાંક    *accptnum, *assoc_rule, *state_type;
પૂર્ણાંક    *rule_type, *rule_linenum;
પૂર્ણાંક     current_state_type;
bool    variable_trailing_context_rules;
પૂર્ણાંક     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
પૂર્ણાંક     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];
પૂર્ણાંક     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
પૂર્ણાંક     tecbck[CSIZE + 1];
પૂર્ણાંક     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
અક્ષર   *scxclu, *sceof;
પૂર્ણાંક     current_max_scs;
અચલ અક્ષર **scname;
પૂર્ણાંક     current_max_dfa_size, current_max_xpairs;
પૂર્ણાંક     current_max_template_xpairs, current_max_dfas;
પૂર્ણાંક     lastdfa, *nxt, *chk, *tnxt;
પૂર્ણાંક    *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
સંઘ dfaacc_union *dfaacc;
પૂર્ણાંક    *accsiz, *dhash, numas;
પૂર્ણાંક     numsnpairs, jambase, jamstate;
પૂર્ણાંક     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
પૂર્ણાંક     current_maxccls, current_max_ccl_tbl_size;
unsigned અક્ષર   *ccltbl;
અક્ષર    nmstr[MAXLINE];
પૂર્ણાંક     sectnum, nummt, hshcol, dfaeql, numeps, eps2, અંક_reallocs, nmval;
પૂર્ણાંક     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
પૂર્ણાંક     અંક_backing_up, bol_needed;
પૂર્ણાંક     end_of_buffer_state;
અક્ષર  **આગત_files;
પૂર્ણાંક     અંક_આગત_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
અક્ષર   *rule_useful, *rule_has_nl, *ccl_has_nl;
પૂર્ણાંક     nlch = '\n';

bool    tablesext, tablesverify, gentables;
અક્ષર   *tablesfilename=0,*tablesname=0;
સંરચના yytbl_writer tableswr;
size_t footprint;

સંરચના ctrl_bundle_t ctrl;
સંરચના env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
અક્ષર   *program_name = "flex";

સ્થિર અચલ અક્ષર outfile_template[] = "lex.%s.%s";
સ્થિર અચલ અક્ષર *backing_name = "lex.backup";
સ્થિર અચલ અક્ષર tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
બાહ્ય FILE* yyout;

સ્થિર અક્ષર outfile_path[MAXLINE];
સ્થિર પૂર્ણાંક outfile_created = 0;
સ્થિર પૂર્ણાંક _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
અચલ અક્ષર *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
અચલ અક્ષર *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
સ્થિર પૂર્ણાંક preproc_level = 1000;

પૂર્ણાંક flex_main (પૂર્ણાંક argc, અક્ષર *argv[]);

પૂર્ણાંક flex_main (પૂર્ણાંક argc, અક્ષર *argv[])
{
	પૂર્ણાંક     i, exit_status, child_status;
	પૂર્ણાંક	did_eof_rule = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_status = setjmp (flex_main_jmp_buf);
	જો (exit_status){
		જો (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		જ્યારે (wait(&child_status) > 0){
			જો (!WIFEXITED (child_status)
			    || WEXITSTATUS (child_status) != 0){
				/* report an error of a child
				 */
				જો( exit_status <= 1 )
					exit_status = 2;

			}
		}
		પાછા exit_status - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	માટે (i = 1; i <= અંક_rules; ++i)
		જો (!rule_useful[i] && i != default_rule)
			લીટી_warning (_("rule cannot be matched"),
				      rule_linenum[i]);

	જો (ctrl.spprdflt && !reject && rule_useful[default_rule])
		લીટી_warning (_
			      ("-s option given but default rule can be matched"),
			      rule_linenum[default_rule]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	જો (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	નહીંતર {
		visible_define ( "M4_MODE_NO_NULTRANS");
		જો (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		નહીંતર
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		જો (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		નહીંતર
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	out ("\n");

	comment("START of Flex-generated definitions\n");
	out_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", અંક_rules);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", અંક_rules + 1);
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

	લીટી_directive_out (stdout, ખાલી, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	out (&action_array[prolog_offset]);

	લીટી_directive_out (stdout, ખાલી, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	out (&action_array[action_offset]);

	લીટી_directive_out (stdout, ખાલી, linenum);

	/* generate cases for any missing EOF rules */
	માટે (i = 1; i <= lastsc; ++i)
		જો (!sceof[i]) {
			out_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			out ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_rule = true;
		}

	જો (did_eof_rule) {
		out ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	લીટી_directive_out (stdout, infilename, linenum);

	જો (sectnum == 3) {
		OUT_BEGIN_CODE ();
                જો (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(શૂન્ય) flexscan ();	/* copy remainder of input to output */
                જો (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		OUT_END_CODE ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	પાછા 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
પૂર્ણાંક મુખ્ય (પૂર્ણાંક argc, અક્ષર *argv[])
{
#જો defined(ENABLE_NLS) && ENABLE_NLS
#જો HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif
#endif

	પાછા flex_main (argc, argv);
}

/* Set up the output filter chain. */

શૂન્ય initialize_output_filters(શૂન્ય)
{
	અચલ અક્ષર * m4 = ખાલી;

	output_chain = filter_create_int(ખાલી, filter_tee_header, env.headerfilename);
	જો ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (અક્ષર *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, ખાલી);

	/* For debugging, only run the requested number of filters. */
	જો (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

શૂન્ય check_options (શૂન્ય)
{
	પૂર્ણાંક     i;

	જો (ctrl.lex_compat) {
		જો (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		જો (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		જો (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#જો 0
	/* This makes no sense whatsoever. I'm removing it. */
	જો (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_used = true;
#endif

	જો (ctrl.csize == trit_unspecified) {
		જો ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		નહીંતર
			ctrl.csize = CSIZE;
	}

	જો (ctrl.interactive == trit_unspecified) {
		જો (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		નહીંતર
			ctrl.interactive = trit_true;
	}

	જો (ctrl.fulltbl || ctrl.fullspd) {
		જો (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		જો (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		જો (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		જો (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	જો (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	જો (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	જો (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	જો (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	જો (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		માટે (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	નહીંતર {
		/* Put everything in its own equivalence class. */
		માટે (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	જો (!env.use_stdout) {
		FILE   *prev_stdout;

		જો (!env.did_outfilename) {
			snprintf (outfile_path, કદ(outfile_path), outfile_template,
				  ctrl.prefix, suffix());

			env.outfilename = outfile_path;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		જો (prev_stdout == ખાલી)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

શૂન્ય flexend (પૂર્ણાંક exit_status)
{
	સ્થિર પૂર્ણાંક called_before = -1;	/* prevent infinite recursion. */
	પૂર્ણાંક     tblsiz;

	જો (++called_before)
		FLEX_EXIT (exit_status);

	જો (ctrl.yyclass != ખાલી && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	જો (skelfile != ખાલી) {
		જો (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		નહીંતર જો (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	જો (exit_status != 0 && outfile_created) {
		જો (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		નહીંતર જો ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		નહીંતર જો (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	જો (env.backing_up_report && ctrl.backing_up_file) {
		જો (અંક_backing_up == 0)
			fprintf (ctrl.backing_up_file, _("No backing up.\n"));
		નહીંતર જો (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_up_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 અંક_backing_up);
		નહીંતર
			fprintf (ctrl.backing_up_file,
				 _("Compressed tables always back up.\n"));

		જો (ferror (ctrl.backing_up_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		નહીંતર જો (fclose (ctrl.backing_up_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	જો (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 program_name, flex_version);

		fprintf (stderr, _("  scanner options: -"));

		જો (ctrl.C_plus_plus)
			putc ('+', stderr);
		જો (env.backing_up_report)
			putc ('b', stderr);
		જો (ctrl.ddebug)
			putc ('d', stderr);
		જો (sf_case_ins())
			putc ('i', stderr);
		જો (ctrl.lex_compat)
			putc ('l', stderr);
		જો (ctrl.posix_compat)
			putc ('X', stderr);
		જો (env.performance_hint > 0)
			putc ('p', stderr);
		જો (env.performance_hint > 1)
			putc ('p', stderr);
		જો (ctrl.spprdflt)
			putc ('s', stderr);
		જો (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        જો (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        જો (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		જો (env.use_stdout)
			putc ('t', stderr);
		જો (env.printstats)
			putc ('v', stderr);	/* always true! */
		જો (env.nowarn)
			putc ('w', stderr);
		જો (ctrl.interactive == trit_false)
			putc ('B', stderr);
		જો (ctrl.interactive == trit_true)
			putc ('I', stderr);
		જો (!ctrl.gen_લીટી_dirs)
			putc ('L', stderr);
		જો (env.trace)
			putc ('T', stderr);

		જો (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		જો (ctrl.csize == 128)
			putc ('7', stderr);
		નહીંતર
			putc ('8', stderr);

		fprintf (stderr, " -C");

		જો (ctrl.long_align)
			putc ('a', stderr);
		જો (ctrl.fulltbl)
			putc ('f', stderr);
		જો (ctrl.fullspd)
			putc ('F', stderr);
		જો (ctrl.useecs)
			putc ('e', stderr);
		જો (ctrl.usemecs)
			putc ('m', stderr);
		જો (ctrl.use_read)
			putc ('r', stderr);

		જો (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		જો (env.skelname != ખાલી)
			fprintf (stderr, " -S%s", env.skelname);

		જો (strcmp (ctrl.prefix, "yy"))
			fprintf (stderr, " -P%s", ctrl.prefix);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 અંક_rules + અંક_eof_rules -
			 1 /* - 1 for def. rule */ );

		જો (અંક_backing_up == 0)
			fprintf (stderr, _("  No backing up\n"));
		નહીંતર જો (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 અંક_backing_up);
		નહીંતર
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		જો (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		જો (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		નહીંતર
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

		જો (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		નહીંતર {
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

		જો (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		જો (ctrl.usemecs) {
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
			 અંક_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_status);
}


/* flexinit - initialize flex */

શૂન્ય flexinit (પૂર્ણાંક argc, અક્ષર **argv)
{
	પૂર્ણાંક     i, sawcmpflag, rv, optind;
	અક્ષર   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', કદ(ctrl));
	syntaxerror = false;
	yymore_used = continued_action = false;
	in_rule = reject = false;
	ctrl.yymore_really_used = ctrl.reject_really_used = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_લીટી_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.prefix = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = ખાલી;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_size = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_size);
	defs1_offset = prolog_offset = action_offset = action_index = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, કદ (અક્ષર));	/* one long string */
	buf_init (&ટોચ_buf, કદ (અક્ષર));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	program_name = argv[0];

	જો (program_name != ખાલી &&
	    program_name[strlen (program_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	જો (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	જ્યારે ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		જો (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 program_name);
			FLEX_EXIT (1);
		}

		પસંદગી ((ગણના flexopt_flag_t) rv) {
		    સ્થિતિ OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			તોડો;

		    સ્થિતિ OPT_BATCH:
			ctrl.interactive = trit_false;
			તોડો;

		    સ્થિતિ OPT_BACKUP:
			env.backing_up_report = trit_true;
			તોડો;

		    સ્થિતિ OPT_BACKUP_FILE:
			env.backing_up_report = true;
                        backing_name = arg;
			તોડો;

		    સ્થિતિ OPT_DONOTHING:
			તોડો;

		    સ્થિતિ OPT_COMPRESSION:
			જો (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			માટે (i = 0; arg && arg[i] != '\0'; i++)
				પસંદગી (arg[i]) {
				    સ્થિતિ 'a':
					ctrl.long_align = true;
					તોડો;

				    સ્થિતિ 'e':
					ctrl.useecs = true;
					તોડો;

				    સ્થિતિ 'F':
					ctrl.fullspd = true;
					તોડો;

				    સ્થિતિ 'f':
					ctrl.fulltbl = true;
					તોડો;

				    સ્થિતિ 'm':
					ctrl.usemecs = true;
					તોડો;

				    સ્થિતિ 'r':
					ctrl.use_read = true;
					તોડો;

				    મૂળભૂત:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					તોડો;
				}
			તોડો;

		    સ્થિતિ OPT_DEBUG:
			ctrl.ddebug = true;
			તોડો;

		    સ્થિતિ OPT_NO_DEBUG:
			ctrl.ddebug = false;
			તોડો;

		    સ્થિતિ OPT_FULL:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			તોડો;

		    સ્થિતિ OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			તોડો;

		    સ્થિતિ OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    સ્થિતિ OPT_INTERACTIVE:
			ctrl.interactive = true;
			તોડો;

		    સ્થિતિ OPT_CASE_INSENSITIVE:
			sf_set_case_ins(true);
			તોડો;

		    સ્થિતિ OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			તોડો;

		    સ્થિતિ OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			તોડો;

		    સ્થિતિ OPT_PREPROC_LEVEL:
			preproc_level = (પૂર્ણાંક) strtol(arg,ખાલી,0);
			તોડો;

		    સ્થિતિ OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			તોડો;

		    સ્થિતિ OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			તોડો;

		    સ્થિતિ OPT_NO_લીટી:
			ctrl.gen_લીટી_dirs = false;
			તોડો;

		    સ્થિતિ OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			તોડો;

		    સ્થિતિ OPT_PREFIX:
			ctrl.prefix = arg;
			તોડો;

		    સ્થિતિ OPT_PERF_REPORT:
			++env.performance_hint;
			તોડો;

		    સ્થિતિ OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			તોડો;

		    સ્થિતિ OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			તોડો;

		    સ્થિતિ OPT_REENTRANT:
			ctrl.reentrant = true;
			તોડો;

		    સ્થિતિ OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			તોડો;

		    સ્થિતિ OPT_SKEL:
			env.skelname = arg;
			તોડો;

		    સ્થિતિ OPT_DEFAULT:
			ctrl.spprdflt = false;
			તોડો;

		    સ્થિતિ OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			તોડો;

		    સ્થિતિ OPT_STDOUT:
			env.use_stdout = true;
			તોડો;

		    સ્થિતિ OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			તોડો;

		    સ્થિતિ OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			તોડો;

		    સ્થિતિ OPT_TABLES_VERIFY:
			tablesverify = true;
			તોડો;

		    સ્થિતિ OPT_TRACE:
			env.trace = true;
			તોડો;

		    સ્થિતિ OPT_VERBOSE:
			env.printstats = true;
			તોડો;

		    સ્થિતિ OPT_VERSION:
			printf ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_version);
			FLEX_EXIT (0);

		    સ્થિતિ OPT_WARN:
			env.nowarn = false;
			તોડો;

		    સ્થિતિ OPT_NO_WARN:
			env.nowarn = true;
			તોડો;

		    સ્થિતિ OPT_7BIT:
			ctrl.csize = 128;
			તોડો;

		    સ્થિતિ OPT_8BIT:
			ctrl.csize = CSIZE;
			તોડો;

		    સ્થિતિ OPT_ALIGN:
			ctrl.long_align = true;
			તોડો;

		    સ્થિતિ OPT_NO_ALIGN:
			ctrl.long_align = false;
			તોડો;

		    સ્થિતિ OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			તોડો;

		    સ્થિતિ OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			તોડો;

		    સ્થિતિ OPT_ARRAY:
			ctrl.yytext_is_array = true;
			તોડો;

		    સ્થિતિ OPT_POINTER:
			ctrl.yytext_is_array = false;
			તોડો;

		    સ્થિતિ OPT_ECS:
			ctrl.useecs = true;
			તોડો;

		    સ્થિતિ OPT_NO_ECS:
			ctrl.useecs = false;
			તોડો;

		    સ્થિતિ OPT_EMIT:
			ctrl.emit = arg;
			તોડો;

		    સ્થિતિ OPT_HEADER_FILE:
			env.headerfilename = arg;
			તોડો;

		    સ્થિતિ OPT_META_ECS:
			ctrl.usemecs = true;
			તોડો;

		    સ્થિતિ OPT_NO_META_ECS:
			ctrl.usemecs = false;
			તોડો;

		    સ્થિતિ OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    અક્ષર   *def;
			    અક્ષર buf2[4096];

			    માટે (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    ચાલુ;
			    જો (*def == '\0')
				    def = "1";

			    snprintf(buf2, કદ(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    તોડો;

		    સ્થિતિ OPT_READ:
			ctrl.use_read = true;
			તોડો;

		    સ્થિતિ OPT_ઢગલો:
			ctrl.ઢગલો_used = true;
			તોડો;

		    સ્થિતિ OPT_STDINIT:
			ctrl.do_stdinit = true;
			તોડો;

		    સ્થિતિ OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			તોડો;

		    સ્થિતિ OPT_YYCLASS:
			ctrl.yyclass = arg;
			તોડો;

		    સ્થિતિ OPT_YYLINENO:
			ctrl.do_yylineno = true;
			તોડો;

		    સ્થિતિ OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			તોડો;

		    સ્થિતિ OPT_YYWRAP:
			ctrl.do_yywrap = true;
			તોડો;

		    સ્થિતિ OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			તોડો;

		    સ્થિતિ OPT_YYMORE:
			ctrl.yymore_really_used = true;
			તોડો;

		    સ્થિતિ OPT_NO_YYMORE:
			ctrl.yymore_really_used = false;
			તોડો;

		    સ્થિતિ OPT_REJECT:
			ctrl.reject_really_used = true;
			તોડો;

		    સ્થિતિ OPT_NO_REJECT:
			ctrl.reject_really_used = false;
			તોડો;

		    સ્થિતિ OPT_NO_YY_ધકેલો_STATE:
			ctrl.no_yy_ધકેલો_state = true;
			તોડો;
		    સ્થિતિ OPT_NO_YY_કાઢો_STATE:
			ctrl.no_yy_કાઢો_state = true;
			તોડો;
		    સ્થિતિ OPT_NO_YY_ટોચ_STATE:
			ctrl.no_yy_ટોચ_state = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			તોડો;
		    સ્થિતિ OPT_NO_YY_SCAN_BUFFER:
			ctrl.no_yy_scan_buffer = true;
			તોડો;
		    સ્થિતિ OPT_NO_YY_SCAN_BYTES:
			ctrl.no_yy_scan_bytes = true;
			તોડો;
		    સ્થિતિ OPT_NO_YY_SCAN_STRING:
			ctrl.no_yy_scan_string = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYGET_TEXT:
			ctrl.no_yyget_text = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYGET_COLUMN:
			ctrl.no_yyget_column = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYSET_COLUMN:
			ctrl.no_yyset_column = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYGET_IN:
			ctrl.no_yyget_in = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYSET_IN:
			ctrl.no_yyset_in = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYGET_OUT:
			ctrl.no_yyget_out = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYSET_OUT:
			ctrl.no_yyset_out = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			તોડો;
		    સ્થિતિ OPT_NO_YYSET_DEBUG:
			ctrl.no_set_debug = true;
			તોડો;

		    સ્થિતિ OPT_HEX:
			env.trace_hex = true;
                        તોડો;
		    સ્થિતિ OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        તોડો;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	અંક_આગત_files = argc - optind;
	આગત_files = argv + optind;
	set_આગત_file (અંક_આગત_files > 0 ? આગત_files[0] : ખાલી);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	અંક_rules = અંક_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = અંક_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	અંક_backing_up = onesp = numprots = 0;
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

શૂન્ય readin (શૂન્ય)
{
	અક્ષર buf[256];

	લીટી_directive_out(ખાલી, infilename, linenum);

	જો (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
		flexend (1);
	}

	જો (syntaxerror)
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

	જો (tablesext)
		gentables = false;

	જો (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	જો (tablesext) {
		FILE   *tablesout;
		સંરચના yytbl_hdr hdr;
		અક્ષર   *pname = 0;
		size_t  nbytes = 0;

		જો (!tablesfilename) {
			nbytes = strlen (ctrl.prefix) + strlen (tablesfile_template) + 2;
			tablesfilename = pname = calloc(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.prefix);
		}

		જો ((tablesout = fopen (tablesfilename, "w")) == ખાલી)
			lerr (_("could not create %s"), tablesfilename);
		મુક્ત(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = strlen (ctrl.prefix) + strlen ("tables") + 2;
		tablesname = calloc(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.prefix);
		yytbl_hdr_init (&hdr, flex_version, tablesname);

		જો (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	જો (env.skelname && (skelfile = fopen (env.skelname, "r")) == ખાલી)
		lerr (_("can't open skeleton file %s"), env.skelname);

	જો (strchr(ctrl.prefix, '[') || strchr(ctrl.prefix, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	જો (env.did_outfilename)
		લીટી_directive_out (stdout, ખાલી, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	જો( ટોચ_buf.elts)
		outn((અક્ષર*) ટોચ_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	લીટી_directive_out(ખાલી, ખાલી, 0);

	/* User may want to set the scanner prototype */
	જો (ctrl.yydecl != ખાલી) {
		out_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	જો (ctrl.userinit != ખાલી) {
		out_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	જો (ctrl.preaction != ખાલી) {
		out_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	જો (ctrl.postaction != ખાલી) {
		out_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	out_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	જો (userdef_buf.elts)
		outn ((અક્ષર *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	જો (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	જો (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	જો (env.backing_up_report) {
		ctrl.backing_up_file = fopen (backing_name, "w");
		જો (ctrl.backing_up_file == ખાલી)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	નહીંતર
		ctrl.backing_up_file = ખાલી;

	જો (ctrl.yymore_really_used == true)
		yymore_used = true;
	નહીંતર જો (ctrl.yymore_really_used == false)
		yymore_used = false;

	જો (ctrl.reject_really_used == true)
		reject = true;
	નહીંતર જો (ctrl.reject_really_used == false)
		reject = false;

	જો (env.performance_hint > 0) {
		જો (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		નહીંતર જો (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		જો (env.performance_hint > 1) {
			જો (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			જો (yymore_used)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		જો (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		જો (variable_trailing_context_rules)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	જો (reject)
		real_reject = true;

	જો (variable_trailing_context_rules)
		reject = true;

	જો ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		જો (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		નહીંતર જો (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		નહીંતર
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	જો (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	નહીંતર
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	જો (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, કદ(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		સંરચના Buf tmpbuf;
		પૂર્ણાંક i;
		buf_init(&tmpbuf, કદ(અક્ષર));
		માટે (i = 1; i <= lastsc; i++) {
			અક્ષર *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = strlen(fmt) + strlen(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = malloc(strsz);
			જો (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			મુક્ત(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		out_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	જો (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	જો (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	જો (extra_type != ખાલી)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	જો (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		જો (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	જો (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	નહીંતર જો (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	જો (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	નહીંતર
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	જો (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	નહીંતર
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	જો (yymore_used)
		visible_define ( "M4_MODE_YYMORE_USED");
	નહીંતર
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	જો (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	નહીંતર
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	જો (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	નહીંતર
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	જો (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	નહીંતર
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	જો (variable_trailing_context_rules) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} નહીંતર {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	જો (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	જો (ctrl.reject_really_used)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	જો (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	નહીંતર
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	જો (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	જો (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	નહીંતર જો (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	નહીંતર જો (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	નહીંતર
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	જો (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	જો (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	નહીંતર
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	જો (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	જો (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	નહીંતર
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	જો (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	નહીંતર
		visible_define ( "M4_MODE_NO_GENTABLES");
	જો (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	નહીંતર
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	જો (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	જો (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	જો (ctrl.yyclass != ખાલી) {
		visible_define ( "M4_MODE_YYCLASS");
		out_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	જો (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	જો (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	જો (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	નહીંતર
		visible_define ( "M4_MODE_NO_YYWRAP");

	જો (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	જો (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	જો (is_default_backend()) {
		જો (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} નહીંતર {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	જો (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	જો (ctrl.prefix != ખાલી)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.prefix);

	જો (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	જો (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	જો (ctrl.yyterminate != ખાલી)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	જો (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	જો (ctrl.no_yy_ધકેલો_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	જો (ctrl.no_yy_કાઢો_state)
		visible_define("M4_YY_NO_POP_STATE");
	જો (ctrl.no_yy_ટોચ_state)
		visible_define("M4_YY_NO_TOP_STATE");
	જો (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	જો (ctrl.no_yy_scan_buffer)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	જો (ctrl.no_yy_scan_bytes)
		visible_define("M4_YY_NO_SCAN_BYTES");
	જો (ctrl.no_yy_scan_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	જો (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	જો (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	જો (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	જો (ctrl.no_yyget_text)
		visible_define("M4_YY_NO_GET_TEXT");
	જો (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	જો (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	જો (ctrl.no_yyget_column)
		visible_define("M4_YY_NO_GET_COLUMN");
	જો (ctrl.no_yyset_column)
		visible_define("M4_YY_NO_SET_COLUMN");
	જો (ctrl.no_yyget_in)
		visible_define("M4_YY_NO_GET_IN");
	જો (ctrl.no_yyset_in)
		visible_define("M4_YY_NO_SET_IN");
	જો (ctrl.no_yyget_out)
		visible_define("M4_YY_NO_GET_OUT");
	જો (ctrl.no_yyset_out)
		visible_define("M4_YY_NO_SET_OUT");
	જો (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	જો (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	જો (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	જો (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	જો (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	જો (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	જો (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	જો (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	જો (ctrl.no_set_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	જો (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	જો (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	જો (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	જો (ctrl.ઢગલો_used)
		visible_define("M4_YY_STACK_USED");

	જો (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	નહીંતર
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	out ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

શૂન્ય set_up_initial_allocations (શૂન્ય)
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
	rule_useful = allocate_array(current_max_rules, કદ(અક્ષર));
	rule_has_nl = allocate_array(current_max_rules, કદ(અક્ષર));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, કદ(અક્ષર));
	sceof = allocate_array(current_max_scs, કદ(અક્ષર));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, કદ(અક્ષર));

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
		કદ(સંઘ dfaacc_union));

	nultrans = ખાલી;
}


શૂન્ય usage (શૂન્ય)
{
	FILE   *f = stdout;

	જો (!env.did_outfilename) {
		snprintf (outfile_path, કદ(outfile_path), outfile_template,
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
