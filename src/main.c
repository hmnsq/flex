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


#include "flexdef.h"
#include "version.h"
#include "options.h"
#include "tables.h"
#include "parse.h"

static char flex_version[] = FLEX_VERSION;

/* declare functions that have forward references */

void flexinit(整数, char **);
void readin(void);
void set_up_initial_allocations(void);

/* these globals are all defined and commented in flexdef.h */
bool    syntaxerror, eofseen;
整数     yymore_used, reject, real_reject, continued_action, in_rule;
整数     datapos, dataline, linenum;
FILE   *skelfile = NULL;
整数     skel_ind = 0;
char   *action_array;
整数     action_size, defs1_offset, prolog_offset, action_offset,
	action_index;
char   *infilename = NULL;
char   *extra_type = NULL;
整数     onestate[ONE_STACK_SIZE], onesym[ONE_STACK_SIZE];
整数     onenext[ONE_STACK_SIZE], onedef[ONE_STACK_SIZE], onesp;
整数     maximum_mns, current_mns, current_max_rules;
整数     num_rules, num_eof_rules, default_rule, lastnfa;
整数    *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
整数    *accptnum, *assoc_rule, *state_type;
整数    *rule_type, *rule_linenum;
整数     current_state_type;
bool    variable_trailing_context_rules;
整数     numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
整数     protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];
整数     numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs,
	tecfwd[CSIZE + 1];
整数     tecbck[CSIZE + 1];
整数     lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
char   *scxclu, *sceof;
整数     current_max_scs;
const char **scname;
整数     current_max_dfa_size, current_max_xpairs;
整数     current_max_template_xpairs, current_max_dfas;
整数     lastdfa, *nxt, *chk, *tnxt;
整数    *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
union dfaacc_union *dfaacc;
整数    *accsiz, *dhash, numas;
整数     numsnpairs, jambase, jamstate;
整数     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
整数     current_maxccls, current_max_ccl_tbl_size;
unsigned char   *ccltbl;
char    nmstr[MAXLINE];
整数     sectnum, nummt, hshcol, dfaeql, numeps, eps2, num_reallocs, nmval;
整数     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
整数     num_backing_up, bol_needed;
整数     end_of_buffer_state;
char  **input_files;
整数     num_input_files;
jmp_buf flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
char   *rule_useful, *rule_has_nl, *ccl_has_nl;
整数     nlch = '\n';

bool    tablesext, tablesverify, gentables;
char   *tablesfilename=0,*tablesname=0;
struct yytbl_writer tableswr;
size_t footprint;

struct ctrl_bundle_t ctrl;
struct env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
char   *program_name = "flex";

static const char outfile_template[] = "lex.%s.%s";
static const char *backing_name = "lex.backup";
static const char tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
extern FILE* yyout;

static char outfile_path[MAXLINE];
static 整数 outfile_created = 0;
static 整数 _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
const char *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
const char *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

/* For debugging. The max number of filters to apply to skeleton. */
static 整数 preproc_level = 1000;

整数 flex_main (整数 argc, char *argv[]);

整数 flex_main (整数 argc, char *argv[])
{
	整数     i, exit_status, child_status;
	整数	did_eof_rule = false;

	/* Set a longjmp target. Yes, I know it's a hack, but it gets worse: The
	 * return value of setjmp, if non-zero, is the desired exit code PLUS ONE.
	 * For example, if you want 'main' to return with code '2', then call
	 * longjmp() with an argument of 3. This is because it is invalid to
	 * specify a value of 0 to longjmp. FLEX_EXIT(n) should be used instead of
	 * exit(n);
	 */
	exit_status = setjmp (flex_main_jmp_buf);
	如果 (exit_status){
		如果 (stdout && !_stdout_closed && !ferror(stdout)){
			fflush(stdout);
			fclose(stdout);
		}
		当 (wait(&child_status) > 0){
			如果 (!WIFEXITED (child_status)
			    || WEXITSTATUS (child_status) != 0){
				/* report an error of a child
				 */
				如果( exit_status <= 1 )
					exit_status = 2;

			}
		}
		返回 exit_status - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	为 (i = 1; i <= num_rules; ++i)
		如果 (!rule_useful[i] && i != default_rule)
			line_warning (_("rule cannot be matched"),
				      rule_linenum[i]);

	如果 (ctrl.spprdflt && !reject && rule_useful[default_rule])
		line_warning (_
			      ("-s option given but default rule can be matched"),
			      rule_linenum[default_rule]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	如果 (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	否则 {
		visible_define ( "M4_MODE_NO_NULTRANS");
		如果 (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		否则
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		如果 (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		否则
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	out ("\n");

	comment("START of Flex-generated definitions\n");
	out_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", num_rules);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", num_rules + 1);
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

	line_directive_out (stdout, NULL, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	out (&action_array[prolog_offset]);

	line_directive_out (stdout, NULL, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	out (&action_array[action_offset]);

	line_directive_out (stdout, NULL, linenum);

	/* generate cases for any missing EOF rules */
	为 (i = 1; i <= lastsc; ++i)
		如果 (!sceof[i]) {
			out_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			out ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_rule = true;
		}

	如果 (did_eof_rule) {
		out ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	line_directive_out (stdout, infilename, linenum);

	如果 (sectnum == 3) {
		OUT_BEGIN_CODE ();
                如果 (!ctrl.no_section3_escape)
                   fputs("[[", stdout);
		(void) flexscan ();	/* copy remainder of input to output */
                如果 (!ctrl.no_section3_escape)
                   fputs("]]", stdout);
		OUT_END_CODE ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	返回 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
整数 主要 (整数 argc, char *argv[])
{
#如果 defined(ENABLE_NLS) && ENABLE_NLS
#如果 HAVE_LOCALE_H
	setlocale (LC_MESSAGES, "");
        setlocale (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif
#endif

	返回 flex_main (argc, argv);
}

/* Set up the output filter chain. */

void initialize_output_filters(void)
{
	const char * m4 = NULL;

	output_chain = filter_create_int(NULL, filter_tee_header, env.headerfilename);
	如果 ( !(m4 = getenv("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (char *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, NULL);

	/* For debugging, only run the requested number of filters. */
	如果 (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

void check_options (void)
{
	整数     i;

	如果 (ctrl.lex_compat) {
		如果 (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		如果 (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		如果 (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#如果 0
	/* This makes no sense whatsoever. I'm removing it. */
	如果 (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_used = true;
#endif

	如果 (ctrl.csize == trit_unspecified) {
		如果 ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		否则
			ctrl.csize = CSIZE;
	}

	如果 (ctrl.interactive == trit_unspecified) {
		如果 (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		否则
			ctrl.interactive = trit_true;
	}

	如果 (ctrl.fulltbl || ctrl.fullspd) {
		如果 (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		如果 (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		如果 (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		如果 (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	如果 (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	如果 (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	如果 (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	如果 (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	如果 (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		为 (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	否则 {
		/* Put everything in its own equivalence class. */
		为 (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	如果 (!env.use_stdout) {
		FILE   *prev_stdout;

		如果 (!env.did_outfilename) {
			snprintf (outfile_path, sizeof(outfile_path), outfile_template,
				  ctrl.prefix, suffix());

			env.outfilename = outfile_path;
		}

		prev_stdout = freopen (env.outfilename, "w+", stdout);

		如果 (prev_stdout == NULL)
			lerr (_("could not create %s"), env.outfilename);

		outfile_created = 1;
	}
}

/* flexend - terminate flex
 *
 * note
 *    This routine does not return.
 */

void flexend (整数 exit_status)
{
	static 整数 called_before = -1;	/* prevent infinite recursion. */
	整数     tblsiz;

	如果 (++called_before)
		FLEX_EXIT (exit_status);

	如果 (ctrl.yyclass != NULL && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	如果 (skelfile != NULL) {
		如果 (ferror (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		否则 如果 (fclose (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	如果 (exit_status != 0 && outfile_created) {
		如果 (ferror (stdout))
			lerr (_("error writing output file %s"),
				env.outfilename);

		否则 如果 ((_stdout_closed = 1) && fclose (stdout))
			lerr (_("error closing output file %s"),
				env.outfilename);

		否则 如果 (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	如果 (env.backing_up_report && ctrl.backing_up_file) {
		如果 (num_backing_up == 0)
			fprintf (ctrl.backing_up_file, _("No backing up.\n"));
		否则 如果 (ctrl.fullspd || ctrl.fulltbl)
			fprintf (ctrl.backing_up_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 num_backing_up);
		否则
			fprintf (ctrl.backing_up_file,
				 _("Compressed tables always back up.\n"));

		如果 (ferror (ctrl.backing_up_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		否则 如果 (fclose (ctrl.backing_up_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	如果 (env.printstats) {
		fprintf (stderr, _("%s version %s usage statistics:\n"),
			 program_name, flex_version);

		fprintf (stderr, _("  scanner options: -"));

		如果 (ctrl.C_plus_plus)
			putc ('+', stderr);
		如果 (env.backing_up_report)
			putc ('b', stderr);
		如果 (ctrl.ddebug)
			putc ('d', stderr);
		如果 (sf_case_ins())
			putc ('i', stderr);
		如果 (ctrl.lex_compat)
			putc ('l', stderr);
		如果 (ctrl.posix_compat)
			putc ('X', stderr);
		如果 (env.performance_hint > 0)
			putc ('p', stderr);
		如果 (env.performance_hint > 1)
			putc ('p', stderr);
		如果 (ctrl.spprdflt)
			putc ('s', stderr);
		如果 (ctrl.reentrant)
			fputs ("--reentrant", stderr);
        如果 (ctrl.bison_bridge_lval)
            fputs ("--bison-bridge", stderr);
        如果 (ctrl.bison_bridge_lloc)
            fputs ("--bison-locations", stderr);
		如果 (env.use_stdout)
			putc ('t', stderr);
		如果 (env.printstats)
			putc ('v', stderr);	/* always true! */
		如果 (env.nowarn)
			putc ('w', stderr);
		如果 (ctrl.interactive == trit_false)
			putc ('B', stderr);
		如果 (ctrl.interactive == trit_true)
			putc ('I', stderr);
		如果 (!ctrl.gen_line_dirs)
			putc ('L', stderr);
		如果 (env.trace)
			putc ('T', stderr);

		如果 (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		如果 (ctrl.csize == 128)
			putc ('7', stderr);
		否则
			putc ('8', stderr);

		fprintf (stderr, " -C");

		如果 (ctrl.long_align)
			putc ('a', stderr);
		如果 (ctrl.fulltbl)
			putc ('f', stderr);
		如果 (ctrl.fullspd)
			putc ('F', stderr);
		如果 (ctrl.useecs)
			putc ('e', stderr);
		如果 (ctrl.usemecs)
			putc ('m', stderr);
		如果 (ctrl.use_read)
			putc ('r', stderr);

		如果 (env.did_outfilename)
			fprintf (stderr, " -o%s", env.outfilename);

		如果 (env.skelname != NULL)
			fprintf (stderr, " -S%s", env.skelname);

		如果 (strcmp (ctrl.prefix, "yy"))
			fprintf (stderr, " -P%s", ctrl.prefix);

		putc ('\n', stderr);

		fprintf (stderr, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		fprintf (stderr, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		fprintf (stderr, _("  %d rules\n"),
			 num_rules + num_eof_rules -
			 1 /* - 1 for def. rule */ );

		如果 (num_backing_up == 0)
			fprintf (stderr, _("  No backing up\n"));
		否则 如果 (ctrl.fullspd || ctrl.fulltbl)
			fprintf (stderr,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 num_backing_up);
		否则
			fprintf (stderr,
				 _
				 ("  Compressed tables always back-up\n"));

		如果 (bol_needed)
			fprintf (stderr,
				 _("  Beginning-of-line patterns used\n"));

		fprintf (stderr, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		fprintf (stderr,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		如果 (lastccl == 0)
			fprintf (stderr, _("  no character classes\n"));
		否则
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

		如果 (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			fprintf (stderr, _("  %d table entries\n"),
				 tblsiz);
		}

		否则 {
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

		如果 (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			fprintf (stderr,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		如果 (ctrl.usemecs) {
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
			 num_reallocs);
		fprintf (stderr, _("  %d total table entries needed\n"),
			 tblsiz);
	}

	FLEX_EXIT (exit_status);
}


/* flexinit - initialize flex */

void flexinit (整数 argc, char **argv)
{
	整数     i, sawcmpflag, rv, optind;
	char   *arg;
	scanopt_t sopt;

	memset(&ctrl, '\0', sizeof(ctrl));
	syntaxerror = false;
	yymore_used = continued_action = false;
	in_rule = reject = false;
	ctrl.yymore_really_used = ctrl.reject_really_used = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_line_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.prefix = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = BUFSIZ;

	tablesext = tablesverify = false;
	gentables = true;
	tablesfilename = tablesname = NULL;

	sawcmpflag = false;
	
	/* Initialize dynamic array for holding the rule actions. */
	action_size = 2048;	/* default size of action array in bytes */
	action_array = allocate_character_array (action_size);
	defs1_offset = prolog_offset = action_offset = action_index = 0;
	action_array[0] = '\0';

	/* Initialize any buffers. */
	buf_init (&userdef_buf, sizeof (char));	/* one long string */
	buf_init (&top_buf, sizeof (char));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	program_name = argv[0];

	如果 (program_name != NULL &&
	    program_name[strlen (program_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	如果 (!sopt) {
		/* This will only happen when flexopts array is altered. */
		fprintf (stderr,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	当 ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		如果 (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			fprintf (stderr,
				 _
				 ("Try `%s --help' for more information.\n"),
				 program_name);
			FLEX_EXIT (1);
		}

		switch ((enum flexopt_flag_t) rv) {
		    case OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			break;

		    case OPT_BATCH:
			ctrl.interactive = trit_false;
			break;

		    case OPT_BACKUP:
			env.backing_up_report = trit_true;
			break;

		    case OPT_BACKUP_FILE:
			env.backing_up_report = true;
                        backing_name = arg;
			break;

		    case OPT_DONOTHING:
			break;

		    case OPT_COMPRESSION:
			如果 (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			为 (i = 0; arg && arg[i] != '\0'; i++)
				switch (arg[i]) {
				    case 'a':
					ctrl.long_align = true;
					break;

				    case 'e':
					ctrl.useecs = true;
					break;

				    case 'F':
					ctrl.fullspd = true;
					break;

				    case 'f':
					ctrl.fulltbl = true;
					break;

				    case 'm':
					ctrl.usemecs = true;
					break;

				    case 'r':
					ctrl.use_read = true;
					break;

				    default:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					break;
				}
			break;

		    case OPT_DEBUG:
			ctrl.ddebug = true;
			break;

		    case OPT_NO_DEBUG:
			ctrl.ddebug = false;
			break;

		    case OPT_FULL:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			break;

		    case OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			break;

		    case OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    case OPT_INTERACTIVE:
			ctrl.interactive = true;
			break;

		    case OPT_CASE_INSENSITIVE:
			sf_set_case_ins(true);
			break;

		    case OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			break;

		    case OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			break;

		    case OPT_PREPROC_LEVEL:
			preproc_level = (整数) strtol(arg,NULL,0);
			break;

		    case OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			break;

		    case OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			break;

		    case OPT_NO_LINE:
			ctrl.gen_line_dirs = false;
			break;

		    case OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			break;

		    case OPT_PREFIX:
			ctrl.prefix = arg;
			break;

		    case OPT_PERF_REPORT:
			++env.performance_hint;
			break;

		    case OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			break;

		    case OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			break;

		    case OPT_REENTRANT:
			ctrl.reentrant = true;
			break;

		    case OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			break;

		    case OPT_SKEL:
			env.skelname = arg;
			break;

		    case OPT_DEFAULT:
			ctrl.spprdflt = false;
			break;

		    case OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			break;

		    case OPT_STDOUT:
			env.use_stdout = true;
			break;

		    case OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			break;

		    case OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			break;

		    case OPT_TABLES_VERIFY:
			tablesverify = true;
			break;

		    case OPT_TRACE:
			env.trace = true;
			break;

		    case OPT_VERBOSE:
			env.printstats = true;
			break;

		    case OPT_VERSION:
			printf ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_version);
			FLEX_EXIT (0);

		    case OPT_WARN:
			env.nowarn = false;
			break;

		    case OPT_NO_WARN:
			env.nowarn = true;
			break;

		    case OPT_7BIT:
			ctrl.csize = 128;
			break;

		    case OPT_8BIT:
			ctrl.csize = CSIZE;
			break;

		    case OPT_ALIGN:
			ctrl.long_align = true;
			break;

		    case OPT_NO_ALIGN:
			ctrl.long_align = false;
			break;

		    case OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			break;

		    case OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			break;

		    case OPT_ARRAY:
			ctrl.yytext_is_array = true;
			break;

		    case OPT_POINTER:
			ctrl.yytext_is_array = false;
			break;

		    case OPT_ECS:
			ctrl.useecs = true;
			break;

		    case OPT_NO_ECS:
			ctrl.useecs = false;
			break;

		    case OPT_EMIT:
			ctrl.emit = arg;
			break;

		    case OPT_HEADER_FILE:
			env.headerfilename = arg;
			break;

		    case OPT_META_ECS:
			ctrl.usemecs = true;
			break;

		    case OPT_NO_META_ECS:
			ctrl.usemecs = false;
			break;

		    case OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    char   *def;
			    char buf2[4096];

			    为 (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    continue;
			    如果 (*def == '\0')
				    def = "1";

			    snprintf(buf2, sizeof(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    break;

		    case OPT_READ:
			ctrl.use_read = true;
			break;

		    case OPT_STACK:
			ctrl.stack_used = true;
			break;

		    case OPT_STDINIT:
			ctrl.do_stdinit = true;
			break;

		    case OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			break;

		    case OPT_YYCLASS:
			ctrl.yyclass = arg;
			break;

		    case OPT_YYLINENO:
			ctrl.do_yylineno = true;
			break;

		    case OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			break;

		    case OPT_YYWRAP:
			ctrl.do_yywrap = true;
			break;

		    case OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			break;

		    case OPT_YYMORE:
			ctrl.yymore_really_used = true;
			break;

		    case OPT_NO_YYMORE:
			ctrl.yymore_really_used = false;
			break;

		    case OPT_REJECT:
			ctrl.reject_really_used = true;
			break;

		    case OPT_NO_REJECT:
			ctrl.reject_really_used = false;
			break;

		    case OPT_NO_YY_PUSH_STATE:
			ctrl.no_yy_push_state = true;
			break;
		    case OPT_NO_YY_POP_STATE:
			ctrl.no_yy_pop_state = true;
			break;
		    case OPT_NO_YY_TOP_STATE:
			ctrl.no_yy_top_state = true;
			break;
		    case OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			break;
		    case OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			break;
		    case OPT_NO_YY_SCAN_BUFFER:
			ctrl.no_yy_scan_buffer = true;
			break;
		    case OPT_NO_YY_SCAN_BYTES:
			ctrl.no_yy_scan_bytes = true;
			break;
		    case OPT_NO_YY_SCAN_STRING:
			ctrl.no_yy_scan_string = true;
			break;
		    case OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			break;
		    case OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			break;
		    case OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			break;
		    case OPT_NO_YYGET_TEXT:
			ctrl.no_yyget_text = true;
			break;
		    case OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			break;
		    case OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			break;
		    case OPT_NO_YYGET_COLUMN:
			ctrl.no_yyget_column = true;
			break;
		    case OPT_NO_YYSET_COLUMN:
			ctrl.no_yyset_column = true;
			break;
		    case OPT_NO_YYGET_IN:
			ctrl.no_yyget_in = true;
			break;
		    case OPT_NO_YYSET_IN:
			ctrl.no_yyset_in = true;
			break;
		    case OPT_NO_YYGET_OUT:
			ctrl.no_yyget_out = true;
			break;
		    case OPT_NO_YYSET_OUT:
			ctrl.no_yyset_out = true;
			break;
		    case OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			break;
		    case OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			break;
		    case OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			break;
		    case OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			break;
		    case OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			break;
		    case OPT_NO_YYSET_DEBUG:
			ctrl.no_set_debug = true;
			break;

		    case OPT_HEX:
			env.trace_hex = true;
                        break;
		    case OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        break;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	num_input_files = argc - optind;
	input_files = argv + optind;
	set_input_file (num_input_files > 0 ? input_files[0] : NULL);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	num_rules = num_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = num_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	num_backing_up = onesp = numprots = 0;
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

void readin (void)
{
	char buf[256];

	line_directive_out(NULL, infilename, linenum);

	如果 (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
		flexend (1);
	}

	如果 (syntaxerror)
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

	如果 (tablesext)
		gentables = false;

	如果 (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	如果 (tablesext) {
		FILE   *tablesout;
		struct yytbl_hdr hdr;
		char   *pname = 0;
		size_t  nbytes = 0;

		如果 (!tablesfilename) {
			nbytes = strlen (ctrl.prefix) + strlen (tablesfile_template) + 2;
			tablesfilename = pname = calloc(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.prefix);
		}

		如果 ((tablesout = fopen (tablesfilename, "w")) == NULL)
			lerr (_("could not create %s"), tablesfilename);
		free(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = strlen (ctrl.prefix) + strlen ("tables") + 2;
		tablesname = calloc(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.prefix);
		yytbl_hdr_init (&hdr, flex_version, tablesname);

		如果 (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	如果 (env.skelname && (skelfile = fopen (env.skelname, "r")) == NULL)
		lerr (_("can't open skeleton file %s"), env.skelname);

	如果 (strchr(ctrl.prefix, '[') || strchr(ctrl.prefix, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	如果 (env.did_outfilename)
		line_directive_out (stdout, NULL, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	如果( top_buf.elts)
		outn((char*) top_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	line_directive_out(NULL, NULL, 0);

	/* User may want to set the scanner prototype */
	如果 (ctrl.yydecl != NULL) {
		out_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	如果 (ctrl.userinit != NULL) {
		out_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	如果 (ctrl.preaction != NULL) {
		out_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	如果 (ctrl.postaction != NULL) {
		out_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	out_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	如果 (userdef_buf.elts)
		outn ((char *) (userdef_buf.elts));

	/* If the user explicitly requested posix compatibility by specifying the
	 * posix-compat option, then we check for conflicting options. However, if
	 * the POSIXLY_CORRECT variable is set, then we quietly make flex as
	 * posix-compatible as possible.  This is the recommended behavior
	 * according to the GNU Coding Standards.
	 *
	 * Note: The posix option was added to flex to provide the posix behavior
	 * of the repeat operator in regular expressions, e.g., `ab{3}'
	 */
	如果 (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	如果 (getenv ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	如果 (env.backing_up_report) {
		ctrl.backing_up_file = fopen (backing_name, "w");
		如果 (ctrl.backing_up_file == NULL)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	否则
		ctrl.backing_up_file = NULL;

	如果 (ctrl.yymore_really_used == true)
		yymore_used = true;
	否则 如果 (ctrl.yymore_really_used == false)
		yymore_used = false;

	如果 (ctrl.reject_really_used == true)
		reject = true;
	否则 如果 (ctrl.reject_really_used == false)
		reject = false;

	如果 (env.performance_hint > 0) {
		如果 (ctrl.lex_compat) {
			fprintf (stderr,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			fprintf (stderr,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		否则 如果 (ctrl.do_yylineno) {
			fprintf (stderr,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		如果 (env.performance_hint > 1) {
			如果 (ctrl.interactive == trit_true)
				fprintf (stderr,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			如果 (yymore_used)
				fprintf (stderr,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		如果 (reject)
			fprintf (stderr,
				 _
				 ("REJECT entails a large performance penalty\n"));

		如果 (variable_trailing_context_rules)
			fprintf (stderr,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	如果 (reject)
		real_reject = true;

	如果 (variable_trailing_context_rules)
		reject = true;

	如果 ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		如果 (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		否则 如果 (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		否则
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	如果 (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	否则
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	如果 (ctrl.useecs)
		ccl2ecl ();

	// These are used to conditionalize code in the lex skeleton
	// that historically used to be generated by C code in flex
	// itself; by shoving all this stuff out to the skeleton file
	// we make it easier to retarget the code generation.
	snprintf(buf, sizeof(buf), "Target: %s\n", ctrl.backend_name);
	comment(buf);
	comment("START of m4 controls\n");

	/* Define the start condition macros. */
	{
		struct Buf tmpbuf;
		整数 i;
		buf_init(&tmpbuf, sizeof(char));
		为 (i = 1; i <= lastsc; i++) {
			char *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			size_t strsz;

			strsz = strlen(fmt) + strlen(scname[i]) + (size_t)(1 + ceil (log10(i))) + 2;
			str = malloc(strsz);
			如果 (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			free(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		out_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	如果 (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	如果 (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	如果 (extra_type != NULL)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	如果 (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		如果 (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	如果 (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	否则 如果 (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	如果 (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	否则
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	如果 (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	否则
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	如果 (yymore_used)
		visible_define ( "M4_MODE_YYMORE_USED");
	否则
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	如果 (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	否则
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	如果 (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	否则
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	如果 (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	否则
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	如果 (variable_trailing_context_rules) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} 否则 {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	如果 (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	如果 (ctrl.reject_really_used)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	如果 (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	否则
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	如果 (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	如果 (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	否则 如果 (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	否则 如果 (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	否则
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	如果 (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	如果 (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	否则
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	如果 (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	如果 (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	否则
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	如果 (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	否则
		visible_define ( "M4_MODE_NO_GENTABLES");
	如果 (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	否则
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	如果 (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	如果 (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	如果 (ctrl.yyclass != NULL) {
		visible_define ( "M4_MODE_YYCLASS");
		out_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	如果 (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	如果 (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	如果 (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	否则
		visible_define ( "M4_MODE_NO_YYWRAP");

	如果 (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	如果 (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	如果 (is_default_backend()) {
		如果 (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} 否则 {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	如果 (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	如果 (ctrl.prefix != NULL)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.prefix);

	如果 (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	如果 (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	如果 (ctrl.yyterminate != NULL)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	如果 (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	如果 (ctrl.no_yy_push_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	如果 (ctrl.no_yy_pop_state)
		visible_define("M4_YY_NO_POP_STATE");
	如果 (ctrl.no_yy_top_state)
		visible_define("M4_YY_NO_TOP_STATE");
	如果 (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	如果 (ctrl.no_yy_scan_buffer)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	如果 (ctrl.no_yy_scan_bytes)
		visible_define("M4_YY_NO_SCAN_BYTES");
	如果 (ctrl.no_yy_scan_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	如果 (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	如果 (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	如果 (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	如果 (ctrl.no_yyget_text)
		visible_define("M4_YY_NO_GET_TEXT");
	如果 (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	如果 (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	如果 (ctrl.no_yyget_column)
		visible_define("M4_YY_NO_GET_COLUMN");
	如果 (ctrl.no_yyset_column)
		visible_define("M4_YY_NO_SET_COLUMN");
	如果 (ctrl.no_yyget_in)
		visible_define("M4_YY_NO_GET_IN");
	如果 (ctrl.no_yyset_in)
		visible_define("M4_YY_NO_SET_IN");
	如果 (ctrl.no_yyget_out)
		visible_define("M4_YY_NO_GET_OUT");
	如果 (ctrl.no_yyset_out)
		visible_define("M4_YY_NO_SET_OUT");
	如果 (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	如果 (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	如果 (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	如果 (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	如果 (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	如果 (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	如果 (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	如果 (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	如果 (ctrl.no_set_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	如果 (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	如果 (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	如果 (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	如果 (ctrl.stack_used)
		visible_define("M4_YY_STACK_USED");

	如果 (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	否则
		visible_define ( "M4_MODE_NO_REWRITE");

	comment("END of m4 controls\n");
	out ("\n");
}

/* set_up_initial_allocations - allocate memory for internal tables */

void set_up_initial_allocations (void)
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
	rule_useful = allocate_array(current_max_rules, sizeof(char));
	rule_has_nl = allocate_array(current_max_rules, sizeof(char));

	current_max_scs = INITIAL_MAX_SCS;
	scset = allocate_integer_array (current_max_scs);
	scbol = allocate_integer_array (current_max_scs);
	scxclu = allocate_array(current_max_scs, sizeof(char));
	sceof = allocate_array(current_max_scs, sizeof(char));
	scname = allocate_char_ptr_array (current_max_scs);

	current_maxccls = INITIAL_MAX_CCLS;
	cclmap = allocate_integer_array (current_maxccls);
	ccllen = allocate_integer_array (current_maxccls);
	cclng = allocate_integer_array (current_maxccls);
	ccl_has_nl = allocate_array(current_maxccls, sizeof(char));

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
		sizeof(union dfaacc_union));

	nultrans = NULL;
}


void usage (void)
{
	FILE   *f = stdout;

	如果 (!env.did_outfilename) {
		snprintf (outfile_path, sizeof(outfile_path), outfile_template,
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
