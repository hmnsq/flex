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
खाता   *skelfile = रिक्त;
पूर्णाङ्क     skel_ind = 0;
वर्ण   *action_array;
पूर्णाङ्क     action_size, defs1_offset, prolog_offset, action_offset,
	action_index;
वर्ण   *infilename = रिक्त;
वर्ण   *extra_type = रिक्त;
पूर्णाङ्क     onestate[ONE_थाक_SIZE], onesym[ONE_थाक_SIZE];
पूर्णाङ्क     onenext[ONE_थाक_SIZE], onedef[ONE_थाक_SIZE], onesp;
पूर्णाङ्क     maximum_mns, current_mns, current_max_rules;
पूर्णाङ्क     अङ्क_rules, अङ्क_eof_rules, default_rule, lastnfa;
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
अचर वर्ण **scname;
पूर्णाङ्क     current_max_dfa_size, current_max_xpairs;
पूर्णाङ्क     current_max_template_xpairs, current_max_dfas;
पूर्णाङ्क     lastdfa, *nxt, *chk, *tnxt;
पूर्णाङ्क    *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss, *dfasiz;
सङ्घ dfaacc_union *dfaacc;
पूर्णाङ्क    *accsiz, *dhash, numas;
पूर्णाङ्क     numsnpairs, jambase, jamstate;
पूर्णाङ्क     lastccl, *cclmap, *ccllen, *cclng, cclreuse;
पूर्णाङ्क     current_maxccls, current_max_ccl_tbl_size;
अचिन्हित वर्ण   *ccltbl;
वर्ण    nmstr[MAXLINE];
पूर्णाङ्क     sectnum, nummt, hshcol, dfaeql, numeps, eps2, अङ्क_reallocs, nmval;
पूर्णाङ्क     tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
पूर्णाङ्क     अङ्क_backing_up, bol_needed;
पूर्णाङ्क     end_of_buffer_state;
वर्ण  **आगत_files;
पूर्णाङ्क     अङ्क_आगत_files;
लाँघ_बफ flex_main_jmp_buf;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
वर्ण   *rule_useful, *rule_has_nl, *ccl_has_nl;
पूर्णाङ्क     nlch = '\n';

bool    tablesext, tablesverify, gentables;
वर्ण   *tablesfilename=0,*tablesname=0;
संरचना yytbl_writer tableswr;
माप_प्रकार footprint;

संरचना ctrl_bundle_t ctrl;
संरचना env_bundle_t env;

/* Make sure program_name is initialized so we don't crash if writing
 * out an error message before getting the program name from argv[0].
 */
वर्ण   *program_name = "flex";

स्थिर अचर वर्ण outfile_template[] = "lex.%s.%s";
स्थिर अचर वर्ण *backing_name = "lex.backup";
स्थिर अचर वर्ण tablesfile_template[] = "lex.%s.tables";

/* From scan.l */
बाह्य खाता* yyout;

स्थिर वर्ण outfile_path[MAXLINE];
स्थिर पूर्णाङ्क outfile_created = 0;
स्थिर पूर्णाङ्क _stdout_closed = 0; /* flag to prevent double-fclose() on stdout. */
अचर वर्ण *escaped_qstart = "]]M4_YY_NOOP[M4_YY_NOOP[M4_YY_NOOP[[";
अचर वर्ण *escaped_qend   = "]]M4_YY_NOOP]M4_YY_NOOP]M4_YY_NOOP[[";

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
	exit_status = बनाओ_लाँघ (flex_main_jmp_buf);
	यदि (exit_status){
		यदि (मानक_निकास && !_stdout_closed && !ख_त्रुटि(मानक_निकास)){
			ख_साफ(मानक_निकास);
			ख_बंद(मानक_निकास);
		}
		जबसम्म (रुको(&child_status) > 0){
			यदि (!WIFEXITED (child_status)
			    || WEXITSTATUS (child_status) != 0){
				/* report an error of a child
				 */
				यदि( exit_status <= 1 )
					exit_status = 2;

			}
		}
		फर्काऊ exit_status - 1;
	}

	flexinit (argc, argv);

	readin ();
	skelout (true);		/* %% [1.0] DFA */
	footprint += ntod ();

	लागि (i = 1; i <= अङ्क_rules; ++i)
		यदि (!rule_useful[i] && i != default_rule)
			पङ्क्ति_warning (_("rule cannot be matched"),
				      rule_linenum[i]);

	यदि (ctrl.spprdflt && !reject && rule_useful[default_rule])
		पङ्क्ति_warning (_
			      ("-s option given but default rule can be matched"),
			      rule_linenum[default_rule]);

	comment("START of m4 controls\n");

	// mode switches for yy_trans_info specification
	// nultrans
	यदि (nultrans)
		visible_define ( "M4_MODE_NULTRANS");
	अन्यथा {
		visible_define ( "M4_MODE_NO_NULTRANS");
		यदि (ctrl.fulltbl)
		    visible_define ( "M4_MODE_NULTRANS_FULLTBL");
		अन्यथा
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLTBL");
		यदि (ctrl.fullspd)
		    visible_define ( "M4_MODE_NULTRANS_FULLSPD");
		अन्यथा
		    visible_define ( "M4_MODE_NO_NULTRANS_FULLSPD");
	}
	
	comment("END of m4 controls\n");
	out ("\n");

	comment("START of Flex-generated definitions\n");
	out_str_dec ("M4_HOOK_CONST_DEFINE_UINT(%s, %d)", "YY_NUM_RULES", अङ्क_rules);
	out_str_dec ("M4_HOOK_CONST_DEFINE_STATE(%s, %d)", "YY_END_OF_BUFFER", अङ्क_rules + 1);
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

	पङ्क्ति_directive_out (मानक_निकास, रिक्त, linenum);

	skelout (true);		/* %% [4.0] - various random yylex internals get dumped here */

	/* Copy prolog to output file. */
	out (&action_array[prolog_offset]);

	पङ्क्ति_directive_out (मानक_निकास, रिक्त, linenum);

	skelout (true);		/* %% [5.0] - main loop of matching-engine code gets dumped here */

	/* Copy actions to output file. */
	out (&action_array[action_offset]);

	पङ्क्ति_directive_out (मानक_निकास, रिक्त, linenum);

	/* generate cases for any missing EOF rules */
	लागि (i = 1; i <= lastsc; ++i)
		यदि (!sceof[i]) {
			out_str ("M4_HOOK_EOF_STATE_CASE_ARM(%s)", scname[i]);
			outc('\n');
			out ("M4_HOOK_EOF_STATE_CASE_FALLTHROUGH");
			outc('\n');
			did_eof_rule = true;
		}

	यदि (did_eof_rule) {
		out ("M4_HOOK_EOF_STATE_CASE_TERMINATE");
	}

	skelout (true);

	/* Copy remainder of input to output. */

	पङ्क्ति_directive_out (मानक_निकास, infilename, linenum);

	यदि (sectnum == 3) {
		OUT_BEGIN_CODE ();
                यदि (!ctrl.no_section3_escape)
                   ख_माला_दो("[[", मानक_निकास);
		(शून्य) flexscan ();	/* copy remainder of input to output */
                यदि (!ctrl.no_section3_escape)
                   ख_माला_दो("]]", मानक_निकास);
		OUT_END_CODE ();
	}

	/* Note, flexend does not return.  It exits with its argument
	 * as status.
	 */
	flexend (0);

	फर्काऊ 0;		/* keep compilers/lint happy */
}

/* Wrapper around flex_main, so flex_main can be built as a library. */
पूर्णाङ्क main (पूर्णाङ्क argc, वर्ण *argv[])
{
#यदि defined(ENABLE_NLS) && ENABLE_NLS
#यदि HAVE_LOCALE_H
	रखो_क्षेत्र (LC_MESSAGES, "");
        रखो_क्षेत्र (LC_CTYPE, "");
	textdomain (PACKAGE);
	bindtextdomain (PACKAGE, LOCALEDIR);
#endif
#endif

	फर्काऊ flex_main (argc, argv);
}

/* Set up the output filter chain. */

शून्य initialize_output_filters(शून्य)
{
	अचर वर्ण * m4 = रिक्त;

	output_chain = filter_create_int(रिक्त, filter_tee_header, env.headerfilename);
	यदि ( !(m4 = दो_पर्या("M4"))) {
		m4 = M4;
	}
	filter_create_ext(output_chain, m4, "-P", (वर्ण *) 0);
	filter_create_int(output_chain, filter_fix_linedirs, रिक्त);

	/* For debugging, only run the requested number of filters. */
	यदि (preproc_level > 0) {
		filter_truncate(output_chain, preproc_level);
		filter_apply_chain(output_chain);
	}
}


/* check_options - check user-specified options */

शून्य check_options (शून्य)
{
	पूर्णाङ्क     i;

	यदि (ctrl.lex_compat) {
		यदि (ctrl.C_plus_plus)
			flexerror (_("Can't use -+ with -l option"));

		यदि (ctrl.fulltbl || ctrl.fullspd)
			flexerror (_("Can't use -f or -F with -l option"));

		यदि (ctrl.reentrant || ctrl.bison_bridge_lval)
			flexerror (_
				   ("Can't use --ctrl.reentrant or --bison-bridge with -l option"));

		ctrl.yytext_is_array = true;
		ctrl.do_yylineno = true;
		ctrl.use_read = false;
	}


#यदि 0
	/* This makes no sense whatsoever. I'm removing it. */
	यदि (ctrl.do_yylineno)
		/* This should really be "maintain_backup_tables = true" */
		ctrl.reject_really_used = true;
#endif

	यदि (ctrl.csize == trit_unspecified) {
		यदि ((ctrl.fulltbl || ctrl.fullspd) && !ctrl.useecs)
			ctrl.csize = DEFAULT_CSIZE;
		अन्यथा
			ctrl.csize = CSIZE;
	}

	यदि (ctrl.interactive == trit_unspecified) {
		यदि (ctrl.fulltbl || ctrl.fullspd)
			ctrl.interactive = trit_false;
		अन्यथा
			ctrl.interactive = trit_true;
	}

	यदि (ctrl.fulltbl || ctrl.fullspd) {
		यदि (ctrl.usemecs)
			flexerror (_
				   ("-Cf/-CF and -Cm don't make sense together"));

		यदि (ctrl.interactive != trit_false)
			flexerror (_("-Cf/-CF and -I are incompatible"));

		यदि (ctrl.lex_compat)
			flexerror (_
				   ("-Cf/-CF are incompatible with lex-compatibility mode"));


		यदि (ctrl.fulltbl && ctrl.fullspd)
			flexerror (_
				   ("-Cf and -CF are mutually exclusive"));
	}

	यदि (ctrl.C_plus_plus && ctrl.fullspd)
		flexerror (_("Can't use -+ with -CF option"));

	यदि (ctrl.C_plus_plus && ctrl.yytext_is_array) {
		lwarn (_("%array incompatible with -+ option"));
		ctrl.yytext_is_array = false;
	}

	यदि (ctrl.C_plus_plus && (ctrl.reentrant))
		flexerror (_("Options -+ and --reentrant are mutually exclusive."));

	यदि (ctrl.C_plus_plus && ctrl.bison_bridge_lval)
		flexerror (_("bison bridge not supported for the C++ scanner."));


	यदि (ctrl.useecs) {		/* Set up doubly-linked equivalence classes. */

		/* We loop all the way up to ctrl.csize, since ecgroup[ctrl.csize] is
		 * the position used for NUL characters.
		 */
		ecgroup[1] = NIL;

		लागि (i = 2; i <= ctrl.csize; ++i) {
			ecgroup[i] = i - 1;
			nextecm[i - 1] = i;
		}

		nextecm[ctrl.csize] = NIL;
	}

	अन्यथा {
		/* Put everything in its own equivalence class. */
		लागि (i = 1; i <= ctrl.csize; ++i) {
			ecgroup[i] = i;
			nextecm[i] = BAD_SUBSCRIPT;	/* to catch errors */
		}
	}

	यदि (!env.use_stdout) {
		खाता   *prev_stdout;

		यदि (!env.did_outfilename) {
			snprintf (outfile_path, परिमाण(outfile_path), outfile_template,
				  ctrl.prefix, suffix());

			env.outfilename = outfile_path;
		}

		prev_stdout = ख_व_खोलो (env.outfilename, "w+", मानक_निकास);

		यदि (prev_stdout == रिक्त)
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

	यदि (++called_before)
		FLEX_EXIT (exit_status);

	यदि (ctrl.yyclass != रिक्त && !ctrl.C_plus_plus)
		flexerror (_("%option yyclass only meaningful for C++ scanners"));

	यदि (skelfile != रिक्त) {
		यदि (ख_त्रुटि (skelfile))
			lerr (_("input error reading skeleton file %s"),
				env.skelname);

		अन्यथा यदि (ख_बंद (skelfile))
			lerr (_("error closing skeleton file %s"),
				env.skelname);
	}

	यदि (exit_status != 0 && outfile_created) {
		यदि (ख_त्रुटि (मानक_निकास))
			lerr (_("error writing output file %s"),
				env.outfilename);

		अन्यथा यदि ((_stdout_closed = 1) && ख_बंद (मानक_निकास))
			lerr (_("error closing output file %s"),
				env.outfilename);

		अन्यथा यदि (unlink (env.outfilename))
			lerr (_("error deleting output file %s"),
				env.outfilename);
	}


	यदि (env.backing_up_report && ctrl.backing_up_file) {
		यदि (अङ्क_backing_up == 0)
			ख_लिखो (ctrl.backing_up_file, _("No backing up.\n"));
		अन्यथा यदि (ctrl.fullspd || ctrl.fulltbl)
			ख_लिखो (ctrl.backing_up_file,
				 _
				 ("%d backing up (non-accepting) states.\n"),
				 अङ्क_backing_up);
		अन्यथा
			ख_लिखो (ctrl.backing_up_file,
				 _("Compressed tables always back up.\n"));

		यदि (ख_त्रुटि (ctrl.backing_up_file))
			lerr (_("error writing backup file %s"),
				backing_name);

		अन्यथा यदि (ख_बंद (ctrl.backing_up_file))
			lerr (_("error closing backup file %s"),
				backing_name);
	}

	यदि (env.printstats) {
		ख_लिखो (मानक_त्रुटि, _("%s version %s usage statistics:\n"),
			 program_name, flex_version);

		ख_लिखो (मानक_त्रुटि, _("  scanner options: -"));

		यदि (ctrl.C_plus_plus)
			अ_दो ('+', मानक_त्रुटि);
		यदि (env.backing_up_report)
			अ_दो ('b', मानक_त्रुटि);
		यदि (ctrl.ddebug)
			अ_दो ('d', मानक_त्रुटि);
		यदि (sf_case_ins())
			अ_दो ('i', मानक_त्रुटि);
		यदि (ctrl.lex_compat)
			अ_दो ('l', मानक_त्रुटि);
		यदि (ctrl.posix_compat)
			अ_दो ('X', मानक_त्रुटि);
		यदि (env.performance_hint > 0)
			अ_दो ('p', मानक_त्रुटि);
		यदि (env.performance_hint > 1)
			अ_दो ('p', मानक_त्रुटि);
		यदि (ctrl.spprdflt)
			अ_दो ('s', मानक_त्रुटि);
		यदि (ctrl.reentrant)
			ख_माला_दो ("--reentrant", मानक_त्रुटि);
        यदि (ctrl.bison_bridge_lval)
            ख_माला_दो ("--bison-bridge", मानक_त्रुटि);
        यदि (ctrl.bison_bridge_lloc)
            ख_माला_दो ("--bison-locations", मानक_त्रुटि);
		यदि (env.use_stdout)
			अ_दो ('t', मानक_त्रुटि);
		यदि (env.printstats)
			अ_दो ('v', मानक_त्रुटि);	/* always true! */
		यदि (env.nowarn)
			अ_दो ('w', मानक_त्रुटि);
		यदि (ctrl.interactive == trit_false)
			अ_दो ('B', मानक_त्रुटि);
		यदि (ctrl.interactive == trit_true)
			अ_दो ('I', मानक_त्रुटि);
		यदि (!ctrl.gen_पङ्क्ति_dirs)
			अ_दो ('L', मानक_त्रुटि);
		यदि (env.trace)
			अ_दो ('T', मानक_त्रुटि);

		यदि (ctrl.csize == trit_unspecified)
			/* We encountered an error fairly early on, so ctrl.csize
			 * never got specified.  Define it now, to prevent
			 * bogus table sizes being written out below.
			 */
			ctrl.csize = 256;

		यदि (ctrl.csize == 128)
			अ_दो ('7', मानक_त्रुटि);
		अन्यथा
			अ_दो ('8', मानक_त्रुटि);

		ख_लिखो (मानक_त्रुटि, " -C");

		यदि (ctrl.long_align)
			अ_दो ('a', मानक_त्रुटि);
		यदि (ctrl.fulltbl)
			अ_दो ('f', मानक_त्रुटि);
		यदि (ctrl.fullspd)
			अ_दो ('F', मानक_त्रुटि);
		यदि (ctrl.useecs)
			अ_दो ('e', मानक_त्रुटि);
		यदि (ctrl.usemecs)
			अ_दो ('m', मानक_त्रुटि);
		यदि (ctrl.use_read)
			अ_दो ('r', मानक_त्रुटि);

		यदि (env.did_outfilename)
			ख_लिखो (मानक_त्रुटि, " -o%s", env.outfilename);

		यदि (env.skelname != रिक्त)
			ख_लिखो (मानक_त्रुटि, " -S%s", env.skelname);

		यदि (म_भेद (ctrl.prefix, "yy"))
			ख_लिखो (मानक_त्रुटि, " -P%s", ctrl.prefix);

		अ_दो ('\n', मानक_त्रुटि);

		ख_लिखो (मानक_त्रुटि, _("  %d/%d NFA states\n"),
			 lastnfa, current_mns);
		ख_लिखो (मानक_त्रुटि, _("  %d/%d DFA states (%d words)\n"),
			 lastdfa, current_max_dfas, totnst);
		ख_लिखो (मानक_त्रुटि, _("  %d rules\n"),
			 अङ्क_rules + अङ्क_eof_rules -
			 1 /* - 1 for def. rule */ );

		यदि (अङ्क_backing_up == 0)
			ख_लिखो (मानक_त्रुटि, _("  No backing up\n"));
		अन्यथा यदि (ctrl.fullspd || ctrl.fulltbl)
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("  %d backing-up (non-accepting) states\n"),
				 अङ्क_backing_up);
		अन्यथा
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("  Compressed tables always back-up\n"));

		यदि (bol_needed)
			ख_लिखो (मानक_त्रुटि,
				 _("  Beginning-of-line patterns used\n"));

		ख_लिखो (मानक_त्रुटि, _("  %d/%d start conditions\n"), lastsc,
			 current_max_scs);
		ख_लिखो (मानक_त्रुटि,
			 _
			 ("  %d epsilon states, %d double epsilon states\n"),
			 numeps, eps2);

		यदि (lastccl == 0)
			ख_लिखो (मानक_त्रुटि, _("  no character classes\n"));
		अन्यथा
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("  %d/%d character classes needed %d/%d words of storage, %d reused\n"),
				 lastccl, current_maxccls,
				 cclmap[lastccl] + ccllen[lastccl],
				 current_max_ccl_tbl_size, cclreuse);

		ख_लिखो (मानक_त्रुटि, _("  %d state/nextstate pairs created\n"),
			 numsnpairs);
		ख_लिखो (मानक_त्रुटि,
			 _("  %d/%d unique/duplicate transitions\n"),
			 numuniq, numdup);

		यदि (ctrl.fulltbl) {
			tblsiz = lastdfa * numecs;
			ख_लिखो (मानक_त्रुटि, _("  %d table entries\n"),
				 tblsiz);
		}

		अन्यथा {
			tblsiz = 2 * (lastdfa + numtemps) + 2 * tblend;

			ख_लिखो (मानक_त्रुटि,
				 _("  %d/%d base-def entries created\n"),
				 lastdfa + numtemps, current_max_dfas);
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("  %d/%d (peak %d) nxt-chk entries created\n"),
				 tblend, current_max_xpairs, peakpairs);
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("  %d/%d (peak %d) template nxt-chk entries created\n"),
				 numtemps * nummecs,
				 current_max_template_xpairs,
				 numtemps * numecs);
			ख_लिखो (मानक_त्रुटि, _("  %d empty table entries\n"),
				 nummt);
			ख_लिखो (मानक_त्रुटि, _("  %d protos created\n"),
				 numprots);
			ख_लिखो (मानक_त्रुटि,
				 _("  %d templates created, %d uses\n"),
				 numtemps, tmpuses);
		}

		यदि (ctrl.useecs) {
			tblsiz = tblsiz + ctrl.csize;
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("  %d/%d equivalence classes created\n"),
				 numecs, ctrl.csize);
		}

		यदि (ctrl.usemecs) {
			tblsiz = tblsiz + numecs;
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("  %d/%d meta-equivalence classes created\n"),
				 nummecs, ctrl.csize);
		}

		ख_लिखो (मानक_त्रुटि,
			 _
			 ("  %d (%d saved) hash collisions, %d DFAs equal\n"),
			 hshcol, hshsave, dfaeql);
		ख_लिखो (मानक_त्रुटि, _("  %d sets of reallocations needed\n"),
			 अङ्क_reallocs);
		ख_लिखो (मानक_त्रुटि, _("  %d total table entries needed\n"),
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

	स_रखो(&ctrl, '\0', परिमाण(ctrl));
	syntaxerror = false;
	yymore_used = continued_action = false;
	in_rule = reject = false;
	ctrl.yymore_really_used = ctrl.reject_really_used = trit_unspecified;

	ctrl.do_main = trit_unspecified;
	ctrl.interactive = ctrl.csize = trit_unspecified;
	ctrl.do_yywrap = ctrl.gen_पङ्क्ति_dirs = ctrl.usemecs = ctrl.useecs = true;
	ctrl.reentrant = ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = false;
	env.performance_hint = 0;
	ctrl.prefix = "yy";
	ctrl.rewrite = false;
	ctrl.yylmax = बफ_मान;

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
	buf_init (&शीर्ष_buf, परिमाण (वर्ण));	    /* one long string */

	sf_init ();

	/* Enable C++ if program name ends with '+'. */
	program_name = argv[0];

	यदि (program_name != रिक्त &&
	    program_name[म_माप (program_name) - 1] == '+')
		ctrl.C_plus_plus = true;

	/* read flags */
	sopt = scanopt_init (flexopts, argc, argv, 0);
	यदि (!sopt) {
		/* This will only happen when flexopts array is altered. */
		ख_लिखो (मानक_त्रुटि,
			 _("Internal error. flexopts are malformed.\n"));
		FLEX_EXIT (1);
	}

	जबसम्म ((rv = scanopt (sopt, &arg, &optind)) != 0) {

		यदि (rv < 0) {
			/* Scanopt has already printed an option-specific error message. */
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("Try `%s --help' for more information.\n"),
				 program_name);
			FLEX_EXIT (1);
		}

		विकल्प ((गणना flexopt_flag_t) rv) {
		    पक्ष OPT_CPLUSPLUS:
			ctrl.C_plus_plus = true;
			रोक;

		    पक्ष OPT_BATCH:
			ctrl.interactive = trit_false;
			रोक;

		    पक्ष OPT_BACKUP:
			env.backing_up_report = trit_true;
			रोक;

		    पक्ष OPT_BACKUP_FILE:
			env.backing_up_report = true;
                        backing_name = arg;
			रोक;

		    पक्ष OPT_DONOTHING:
			रोक;

		    पक्ष OPT_COMPRESSION:
			यदि (!sawcmpflag) {
				ctrl.useecs = false;
				ctrl.usemecs = false;
				ctrl.fulltbl = false;
				sawcmpflag = true;
			}

			लागि (i = 0; arg && arg[i] != '\0'; i++)
				विकल्प (arg[i]) {
				    पक्ष 'a':
					ctrl.long_align = true;
					रोक;

				    पक्ष 'e':
					ctrl.useecs = true;
					रोक;

				    पक्ष 'F':
					ctrl.fullspd = true;
					रोक;

				    पक्ष 'f':
					ctrl.fulltbl = true;
					रोक;

				    पक्ष 'm':
					ctrl.usemecs = true;
					रोक;

				    पक्ष 'r':
					ctrl.use_read = true;
					रोक;

				    स्वभाव:
					lerr (_
					      ("unknown -C option '%c'"),
					      arg[i]);
					रोक;
				}
			रोक;

		    पक्ष OPT_DEBUG:
			ctrl.ddebug = true;
			रोक;

		    पक्ष OPT_NO_DEBUG:
			ctrl.ddebug = false;
			रोक;

		    पक्ष OPT_FULL:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			रोक;

		    पक्ष OPT_FAST:
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			रोक;

		    पक्ष OPT_HELP:
			usage ();
			FLEX_EXIT (0);

		    पक्ष OPT_INTERACTIVE:
			ctrl.interactive = true;
			रोक;

		    पक्ष OPT_CASE_INSENSITIVE:
			sf_set_case_ins(true);
			रोक;

		    पक्ष OPT_LEX_COMPAT:
			ctrl.lex_compat = true;
			रोक;

		    पक्ष OPT_POSIX_COMPAT:
			ctrl.posix_compat = true;
			रोक;

		    पक्ष OPT_PREPROC_LEVEL:
			preproc_level = (पूर्णाङ्क) म_से_दीर्घ(arg,रिक्त,0);
			रोक;

		    पक्ष OPT_MAIN:
			ctrl.do_yywrap = false;
			ctrl.do_main = trit_true;
			रोक;

		    पक्ष OPT_NO_MAIN:
			ctrl.do_main = trit_false;
			रोक;

		    पक्ष OPT_NO_पङ्क्ति:
			ctrl.gen_पङ्क्ति_dirs = false;
			रोक;

		    पक्ष OPT_OUTFILE:
			env.outfilename = arg;
			env.did_outfilename = 1;
			रोक;

		    पक्ष OPT_PREFIX:
			ctrl.prefix = arg;
			रोक;

		    पक्ष OPT_PERF_REPORT:
			++env.performance_hint;
			रोक;

		    पक्ष OPT_BISON_BRIDGE:
			ctrl.bison_bridge_lval = true;
			रोक;

		    पक्ष OPT_BISON_BRIDGE_LOCATIONS:
			ctrl.bison_bridge_lval = ctrl.bison_bridge_lloc = true;
			रोक;

		    पक्ष OPT_REENTRANT:
			ctrl.reentrant = true;
			रोक;

		    पक्ष OPT_NO_REENTRANT:
			ctrl.reentrant = false;
			रोक;

		    पक्ष OPT_SKEL:
			env.skelname = arg;
			रोक;

		    पक्ष OPT_DEFAULT:
			ctrl.spprdflt = false;
			रोक;

		    पक्ष OPT_NO_DEFAULT:
			ctrl.spprdflt = true;
			रोक;

		    पक्ष OPT_STDOUT:
			env.use_stdout = true;
			रोक;

		    पक्ष OPT_NO_UNISTD_H:
			ctrl.no_unistd = true;
			रोक;

		    पक्ष OPT_TABLES_FILE:
			tablesext = true;
			tablesfilename = arg;
			रोक;

		    पक्ष OPT_TABLES_VERIFY:
			tablesverify = true;
			रोक;

		    पक्ष OPT_TRACE:
			env.trace = true;
			रोक;

		    पक्ष OPT_VERBOSE:
			env.printstats = true;
			रोक;

		    पक्ष OPT_VERSION:
			म_लिखो ("%s %s\n", (ctrl.C_plus_plus ? "flex++" : "flex"), flex_version);
			FLEX_EXIT (0);

		    पक्ष OPT_WARN:
			env.nowarn = false;
			रोक;

		    पक्ष OPT_NO_WARN:
			env.nowarn = true;
			रोक;

		    पक्ष OPT_7BIT:
			ctrl.csize = 128;
			रोक;

		    पक्ष OPT_8BIT:
			ctrl.csize = CSIZE;
			रोक;

		    पक्ष OPT_ALIGN:
			ctrl.long_align = true;
			रोक;

		    पक्ष OPT_NO_ALIGN:
			ctrl.long_align = false;
			रोक;

		    पक्ष OPT_ALWAYS_INTERACTIVE:
			ctrl.always_interactive = true;
			रोक;

		    पक्ष OPT_NEVER_INTERACTIVE:
			ctrl.never_interactive = true;
			रोक;

		    पक्ष OPT_ARRAY:
			ctrl.yytext_is_array = true;
			रोक;

		    पक्ष OPT_POINTER:
			ctrl.yytext_is_array = false;
			रोक;

		    पक्ष OPT_ECS:
			ctrl.useecs = true;
			रोक;

		    पक्ष OPT_NO_ECS:
			ctrl.useecs = false;
			रोक;

		    पक्ष OPT_EMIT:
			ctrl.emit = arg;
			रोक;

		    पक्ष OPT_HEADER_FILE:
			env.headerfilename = arg;
			रोक;

		    पक्ष OPT_META_ECS:
			ctrl.usemecs = true;
			रोक;

		    पक्ष OPT_NO_META_ECS:
			ctrl.usemecs = false;
			रोक;

		    पक्ष OPT_PREPROCDEFINE:
		    {
			    /* arg is "symbol" or "symbol=definition". */
			    वर्ण   *def;
			    वर्ण buf2[4096];

			    लागि (def = arg;
				 *def != '\0' && *def != '='; ++def)
				    जारी;
			    यदि (*def == '\0')
				    def = "1";

			    snprintf(buf2, परिमाण(buf2), "M4_HOOK_CONST_DEFINE_UNKNOWN(%s, %s)", arg, def);
			    buf_strappend (&userdef_buf, buf2);
		    }
		    रोक;

		    पक्ष OPT_READ:
			ctrl.use_read = true;
			रोक;

		    पक्ष OPT_थाक:
			ctrl.थाक_used = true;
			रोक;

		    पक्ष OPT_STDINIT:
			ctrl.do_stdinit = true;
			रोक;

		    पक्ष OPT_NO_STDINIT:
			ctrl.do_stdinit = false;
			रोक;

		    पक्ष OPT_YYCLASS:
			ctrl.yyclass = arg;
			रोक;

		    पक्ष OPT_YYLINENO:
			ctrl.do_yylineno = true;
			रोक;

		    पक्ष OPT_NO_YYLINENO:
			ctrl.do_yylineno = false;
			रोक;

		    पक्ष OPT_YYWRAP:
			ctrl.do_yywrap = true;
			रोक;

		    पक्ष OPT_NO_YYWRAP:
			ctrl.do_yywrap = false;
			रोक;

		    पक्ष OPT_YYMORE:
			ctrl.yymore_really_used = true;
			रोक;

		    पक्ष OPT_NO_YYMORE:
			ctrl.yymore_really_used = false;
			रोक;

		    पक्ष OPT_REJECT:
			ctrl.reject_really_used = true;
			रोक;

		    पक्ष OPT_NO_REJECT:
			ctrl.reject_really_used = false;
			रोक;

		    पक्ष OPT_NO_YY_थप_STATE:
			ctrl.no_yy_थप_state = true;
			रोक;
		    पक्ष OPT_NO_YY_झिक_STATE:
			ctrl.no_yy_झिक_state = true;
			रोक;
		    पक्ष OPT_NO_YY_शीर्ष_STATE:
			ctrl.no_yy_शीर्ष_state = true;
			रोक;
		    पक्ष OPT_NO_YYINPUT:
			ctrl.no_yyinput = true;
			रोक;
		    पक्ष OPT_NO_YYUNPUT:
			ctrl.no_yyunput = true;
			रोक;
		    पक्ष OPT_NO_YY_SCAN_BUFFER:
			ctrl.no_yy_scan_buffer = true;
			रोक;
		    पक्ष OPT_NO_YY_SCAN_BYTES:
			ctrl.no_yy_scan_bytes = true;
			रोक;
		    पक्ष OPT_NO_YY_SCAN_STRING:
			ctrl.no_yy_scan_string = true;
			रोक;
		    पक्ष OPT_NO_YYGET_EXTRA:
			ctrl.no_yyget_extra = true;
			रोक;
		    पक्ष OPT_NO_YYSET_EXTRA:
			ctrl.no_yyset_extra = true;
			रोक;
		    पक्ष OPT_NO_YYGET_LENG:
			ctrl.no_yyget_leng = true;
			रोक;
		    पक्ष OPT_NO_YYGET_TEXT:
			ctrl.no_yyget_text = true;
			रोक;
		    पक्ष OPT_NO_YYGET_LINENO:
			ctrl.no_yyget_lineno = true;
			रोक;
		    पक्ष OPT_NO_YYSET_LINENO:
			ctrl.no_yyset_lineno = true;
			रोक;
		    पक्ष OPT_NO_YYGET_COLUMN:
			ctrl.no_yyget_column = true;
			रोक;
		    पक्ष OPT_NO_YYSET_COLUMN:
			ctrl.no_yyset_column = true;
			रोक;
		    पक्ष OPT_NO_YYGET_IN:
			ctrl.no_yyget_in = true;
			रोक;
		    पक्ष OPT_NO_YYSET_IN:
			ctrl.no_yyset_in = true;
			रोक;
		    पक्ष OPT_NO_YYGET_OUT:
			ctrl.no_yyget_out = true;
			रोक;
		    पक्ष OPT_NO_YYSET_OUT:
			ctrl.no_yyset_out = true;
			रोक;
		    पक्ष OPT_NO_YYGET_LVAL:
			ctrl.no_yyget_lval = true;
			रोक;
		    पक्ष OPT_NO_YYSET_LVAL:
			ctrl.no_yyset_lval = true;
			रोक;
		    पक्ष OPT_NO_YYGET_LLOC:
			ctrl.no_yyget_lloc = true;
			रोक;
		    पक्ष OPT_NO_YYSET_LLOC:
			ctrl.no_yyset_lloc = true;
			रोक;
		    पक्ष OPT_NO_YYGET_DEBUG:
			ctrl.no_get_debug = true;
			रोक;
		    पक्ष OPT_NO_YYSET_DEBUG:
			ctrl.no_set_debug = true;
			रोक;

		    पक्ष OPT_HEX:
			env.trace_hex = true;
                        रोक;
		    पक्ष OPT_NO_SECT3_ESCAPE:
                        ctrl.no_section3_escape = true;
                        रोक;
		}		/* switch */
	}			/* while scanopt() */

	scanopt_destroy (sopt);

	अङ्क_आगत_files = argc - optind;
	आगत_files = argv + optind;
	set_आगत_file (अङ्क_आगत_files > 0 ? आगत_files[0] : रिक्त);

	lastccl = lastsc = lastdfa = lastnfa = 0;
	अङ्क_rules = अङ्क_eof_rules = default_rule = 0;
	numas = numsnpairs = tmpuses = 0;
	numecs = numeps = eps2 = अङ्क_reallocs = hshcol = dfaeql = totnst =
	    0;
	numuniq = numdup = hshsave = datapos = dataline = 0;
	eofseen = false;
	अङ्क_backing_up = onesp = numprots = 0;
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

	पङ्क्ति_directive_out(रिक्त, infilename, linenum);

	यदि (yyparse ()) {
		pinpoint_message (_("fatal parse error"));
		flexend (1);
	}

	यदि (syntaxerror)
		flexend (1);

	/* On --emit, -e, or change backends This is where backend
	 * properties are collected, which means they can't be set
	 * from a custom skelfile.  Note: might have been called sooner
	 * when %option emit was evaluated; this catches command-line
	 * optiins and the default case.
	 */
	backend_by_name(ctrl.emit);

	initialize_output_filters();

	yyout = मानक_निकास;

	यदि (tablesext)
		gentables = false;

	यदि (tablesverify)
		/* force generation of C tables. */
		gentables = true;


	यदि (tablesext) {
		खाता   *tablesout;
		संरचना yytbl_hdr hdr;
		वर्ण   *pname = 0;
		माप_प्रकार  nbytes = 0;

		यदि (!tablesfilename) {
			nbytes = म_माप (ctrl.prefix) + म_माप (tablesfile_template) + 2;
			tablesfilename = pname = सुस्मृति(nbytes, 1);
			snprintf (pname, nbytes, tablesfile_template, ctrl.prefix);
		}

		यदि ((tablesout = ख_खोलो (tablesfilename, "w")) == रिक्त)
			lerr (_("could not create %s"), tablesfilename);
		मुक्त(pname);
		tablesfilename = 0;

		yytbl_writer_init (&tableswr, tablesout);

		nbytes = म_माप (ctrl.prefix) + म_माप ("tables") + 2;
		tablesname = सुस्मृति(nbytes, 1);
		snprintf (tablesname, nbytes, "%stables", ctrl.prefix);
		yytbl_hdr_init (&hdr, flex_version, tablesname);

		यदि (yytbl_hdr_fwrite (&tableswr, &hdr) <= 0)
			flexerror (_("could not write tables header"));
	}

	यदि (env.skelname && (skelfile = ख_खोलो (env.skelname, "r")) == रिक्त)
		lerr (_("can't open skeleton file %s"), env.skelname);

	यदि (म_अक्षर(ctrl.prefix, '[') || म_अक्षर(ctrl.prefix, ']'))
		flexerror(_("Prefix cannot include '[' or ']'"));

	यदि (env.did_outfilename)
		पङ्क्ति_directive_out (मानक_निकास, रिक्त, linenum);

	/* This is where we begin writing to the file. */

	skelout(false);	/* [0.0] Make hook macros available, silently */

	comment("A lexical scanner generated by flex\n");

	/* Dump the %top code. */
	यदि( शीर्ष_buf.elts)
		outn((वर्ण*) शीर्ष_buf.elts);

	/* Place a bogus line directive, it will be fixed in the filter. */
	पङ्क्ति_directive_out(रिक्त, रिक्त, 0);

	/* User may want to set the scanner prototype */
	यदि (ctrl.yydecl != रिक्त) {
		out_str ("M4_HOOK_SET_YY_DECL(%s)\n", ctrl.yydecl);
	}

	यदि (ctrl.userinit != रिक्त) {
		out_str ("M4_HOOK_SET_USERINIT(%s)\n", ctrl.userinit);
	}
	यदि (ctrl.preaction != रिक्त) {
		out_str ("M4_HOOK_SET_PREACTION(%s)\n", ctrl.preaction);
	}
	यदि (ctrl.postaction != रिक्त) {
		out_str ("M4_HOOK_SET_POSTACTION(%s)\n", ctrl.postaction);
	}

	/* This has to be a straight textual substitution rather
	 * than a constant declaration because in C a const is
	 * not const enough to be a static array bound.
	 */
	out_dec ("m4_define([[YYLMAX]], [[%d]])\n", ctrl.yylmax);

	/* Dump the user defined preproc directives. */
	यदि (userdef_buf.elts)
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
	यदि (ctrl.posix_compat) {
		/* TODO: This is where we try to make flex behave according to
		 * POSIX, *and* check for conflicting ctrl. How far should we go
		 * with this? Should we disable all the neat-o flex features?
		 */
		/* Update: Estes says no, since other flex features don't violate posix. */
	}

	यदि (दो_पर्या ("POSIXLY_CORRECT")) {
		ctrl.posix_compat = true;
	}

	यदि (env.backing_up_report) {
		ctrl.backing_up_file = ख_खोलो (backing_name, "w");
		यदि (ctrl.backing_up_file == रिक्त)
			lerr (_
				("could not create backing-up info file %s"),
				backing_name);
	}

	अन्यथा
		ctrl.backing_up_file = रिक्त;

	यदि (ctrl.yymore_really_used == true)
		yymore_used = true;
	अन्यथा यदि (ctrl.yymore_really_used == false)
		yymore_used = false;

	यदि (ctrl.reject_really_used == true)
		reject = true;
	अन्यथा यदि (ctrl.reject_really_used == false)
		reject = false;

	यदि (env.performance_hint > 0) {
		यदि (ctrl.lex_compat) {
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("-l AT&T lex compatibility option entails a large performance penalty\n"));
			ख_लिखो (मानक_त्रुटि,
				 _
				 (" and may be the actual source of other reported performance penalties\n"));
		}

		अन्यथा यदि (ctrl.do_yylineno) {
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("%%option yylineno entails a performance penalty ONLY on rules that can match newline characters\n"));
		}

		यदि (env.performance_hint > 1) {
			यदि (ctrl.interactive == trit_true)
				ख_लिखो (मानक_त्रुटि,
					 _
					 ("-I (interactive) entails a minor performance penalty\n"));

			यदि (yymore_used)
				ख_लिखो (मानक_त्रुटि,
					 _
					 ("yymore() entails a minor performance penalty\n"));
		}

		यदि (reject)
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("REJECT entails a large performance penalty\n"));

		यदि (variable_trailing_context_rules)
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("Variable trailing context rules entail a large performance penalty\n"));
	}

	यदि (reject)
		real_reject = true;

	यदि (variable_trailing_context_rules)
		reject = true;

	यदि ((ctrl.fulltbl || ctrl.fullspd) && reject) {
		यदि (real_reject)
			flexerror (_
				   ("REJECT cannot be used with -f or -F"));
		अन्यथा यदि (ctrl.do_yylineno)
			flexerror (_
				   ("%option yylineno cannot be used with REJECT"));
		अन्यथा
			flexerror (_
				   ("variable trailing context rules cannot be used with -f or -F"));
	}

	यदि (ctrl.useecs)
		numecs = cre8ecs (nextecm, ecgroup, ctrl.csize);
	अन्यथा
		numecs = ctrl.csize;

	/* Now map the equivalence class for NUL to its expected place. */
	ecgroup[0] = ecgroup[ctrl.csize];
	NUL_ec = ABS (ecgroup[0]);

	यदि (ctrl.useecs)
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
		लागि (i = 1; i <= lastsc; i++) {
			वर्ण *str, *fmt = "M4_HOOK_CONST_DEFINE_STATE(%s, %d)";
			माप_प्रकार strsz;

			strsz = म_माप(fmt) + म_माप(scname[i]) + (माप_प्रकार)(1 + उच्चमान (log10(i))) + 2;
			str = दो_स्मृति(strsz);
			यदि (!str)
				flexfatal(_("allocation of macro definition failed"));
			snprintf(str, strsz, fmt, scname[i], i - 1);
			buf_strappend(&tmpbuf, str);
			मुक्त(str);
		}
		// FIXME: Not dumped visibly because we plan to do away with the indirection
		out_m4_define("M4_YY_SC_DEFS", tmpbuf.elts);
		buf_destroy(&tmpbuf);
	}

	यदि (ctrl.bison_bridge_lval)
		visible_define("M4_YY_BISON_LVAL");

	यदि (ctrl.bison_bridge_lloc)
		visible_define("<M4_YY_BISON_LLOC>");

	यदि (extra_type != रिक्त)
		visible_define_str ("M4_MODE_EXTRA_TYPE", extra_type);

	/* always generate the tablesverify flag. */
	visible_define_str ("M4_YY_TABLES_VERIFY", tablesverify ? "1" : "0");

	यदि (ctrl.reentrant) {
		visible_define ("M4_YY_REENTRANT");
		यदि (ctrl.yytext_is_array)
			visible_define ("M4_MODE_REENTRANT_TEXT_IS_ARRAY");
	}

	यदि (ctrl.do_main == trit_true)
		visible_define_str ( "YY_MAIN", "1");
	अन्यथा यदि (ctrl.do_main == trit_false)
		visible_define_str ( "YY_MAIN", "0");

	यदि (ctrl.do_stdinit)
		visible_define ( "M4_MODE_DO_STDINIT");
	अन्यथा
		visible_define ( "M4_MODE_NO_DO_STDINIT");

	// mode switches for YY_DO_BEFORE_ACTION code generation
	यदि (ctrl.yytext_is_array)
		visible_define ( "M4_MODE_YYTEXT_IS_ARRAY");
	अन्यथा
		visible_define ( "M4_MODE_NO_YYTEXT_IS_ARRAY");
	यदि (yymore_used)
		visible_define ( "M4_MODE_YYMORE_USED");
	अन्यथा
		visible_define ( "M4_MODE_NO_YYMORE_USED");

	यदि (ctrl.fullspd)
		visible_define ( "M4_MODE_REAL_FULLSPD");
	अन्यथा
		visible_define ( "M4_MODE_NO_REAL_FULLSPD");

	यदि (ctrl.fulltbl)
		visible_define ( "M4_MODE_REAL_FULLTBL");
	अन्यथा
		visible_define ( "M4_MODE_NO_REAL_FULLTBL");

	// niode switches for YYINPUT code generation
	यदि (ctrl.use_read)
		visible_define ( "M4_MODE_CPP_USE_READ");
	अन्यथा
		visible_define ( "M4_MODE_NO_CPP_USE_READ");

	// mode switches for next-action code
	यदि (variable_trailing_context_rules) {
		visible_define ( "M4_MODE_VARIABLE_TRAILING_CONTEXT_RULES");
	} अन्यथा {
		visible_define ( "M4_MODE_NO_VARIABLE_TRAILING_CONTEXT_RULES");
	}
	यदि (real_reject)
		visible_define ( "M4_MODE_REAL_REJECT");
	यदि (ctrl.reject_really_used)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_REALLY_USED");
	यदि (reject)
		visible_define ( "M4_MODE_USES_REJECT");
	अन्यथा
		visible_define ( "M4_MODE_NO_USES_REJECT");

	// mode switches for computing next compressed state
	यदि (ctrl.usemecs)
		visible_define ( "M4_MODE_USEMECS");

	// mode switches for find-action code
	यदि (ctrl.fullspd)
		visible_define ( "M4_MODE_FULLSPD");
	अन्यथा यदि (ctrl.fulltbl)
	    visible_define ( "M4_MODE_FIND_ACTION_FULLTBL");
	अन्यथा यदि (reject)
	    visible_define ( "M4_MODE_FIND_ACTION_REJECT");
	अन्यथा
	    visible_define ( "M4_MODE_FIND_ACTION_COMPRESSED");

	// mode switches for backup generation and gen_start_state
	यदि (!ctrl.fullspd)
		visible_define ( "M4_MODE_NO_FULLSPD");
	यदि (bol_needed)
		visible_define ( "M4_MODE_BOL_NEEDED");
	अन्यथा
		visible_define ( "M4_MODE_NO_BOL_NEEDED");

	// yylineno
	यदि (ctrl.do_yylineno)
		visible_define ( "M4_MODE_YYLINENO");

	// Equivalence classes
	यदि (ctrl.useecs)
		visible_define ( "M4_MODE_USEECS");
	अन्यथा
		visible_define ( "M4_MODE_NO_USEECS");

	// mode switches for getting next action
	यदि (gentables)
		visible_define ( "M4_MODE_GENTABLES");
	अन्यथा
		visible_define ( "M4_MODE_NO_GENTABLES");
	यदि (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");
	अन्यथा
		visible_define ( "M4_MODE_NO_INTERACTIVE");
	यदि (!(ctrl.fullspd || ctrl.fulltbl))
		visible_define ( "M4_MODE_NO_FULLSPD_OR_FULLTBL");
	यदि (reject || ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_FIND_ACTION_REJECT_OR_INTERACTIVE");

	यदि (ctrl.yyclass != रिक्त) {
		visible_define ( "M4_MODE_YYCLASS");
		out_m4_define("M4_YY_CLASS_NAME", ctrl.yyclass);
	}

	यदि (ctrl.ddebug)
		visible_define ( "M4_MODE_DEBUG");

	यदि (ctrl.lex_compat)
		visible_define ( "M4_MODE_OPTIONS.LEX_COMPAT");

	यदि (ctrl.do_yywrap)
		visible_define ( "M4_MODE_YYWRAP");
	अन्यथा
		visible_define ( "M4_MODE_NO_YYWRAP");

	यदि (ctrl.interactive == trit_true)
		visible_define ( "M4_MODE_INTERACTIVE");

	यदि (ctrl.noyyread)
		visible_define("M4_MODE_USER_YYREAD");

	यदि (is_default_backend()) {
		यदि (ctrl.C_plus_plus) {
			visible_define ( "M4_MODE_CXX_ONLY");
		} अन्यथा {
			visible_define ( "M4_MODE_C_ONLY");
		}
	}

	यदि (tablesext)
		visible_define ( "M4_MODE_TABLESEXT");
	यदि (ctrl.prefix != रिक्त)
	    visible_define_str ( "M4_MODE_PREFIX", ctrl.prefix);

	यदि (ctrl.no_yyinput)
		visible_define("M4_MODE_NO_YYINPUT");

	यदि (ctrl.bufsize != 0)
	    visible_define_int("M4_MODE_YY_BUFSIZE", ctrl.bufsize);

	यदि (ctrl.yyterminate != रिक्त)
	    visible_define_str("M4_MODE_YYTERMINATE", ctrl.yyterminate);
	
	यदि (ctrl.no_yypanic)
		visible_define("M4_YY_NO_YYPANIC");
	यदि (ctrl.no_yy_थप_state)
		visible_define("M4_YY_NO_PUSH_STATE");
	यदि (ctrl.no_yy_झिक_state)
		visible_define("M4_YY_NO_POP_STATE");
	यदि (ctrl.no_yy_शीर्ष_state)
		visible_define("M4_YY_NO_TOP_STATE");
	यदि (ctrl.no_yyunput)
		visible_define("M4_YY_NO_YYUNPUT");
	यदि (ctrl.no_yy_scan_buffer)
		visible_define("M4_YY_NO_SCAN_BUFFER");
	यदि (ctrl.no_yy_scan_bytes)
		visible_define("M4_YY_NO_SCAN_BYTES");
	यदि (ctrl.no_yy_scan_string)
		visible_define("M4_YY_NO_SCAN_STRING");
	यदि (ctrl.no_yyget_extra)
		visible_define("M4_YY_NO_GET_EXTRA");
	यदि (ctrl.no_yyset_extra)
		visible_define("M4_YY_NO_SET_EXTRA");
	यदि (ctrl.no_yyget_leng)
		visible_define("M4_YY_NO_GET_LENG");
	यदि (ctrl.no_yyget_text)
		visible_define("M4_YY_NO_GET_TEXT");
	यदि (ctrl.no_yyget_lineno)
		visible_define("M4_YY_NO_GET_LINENO");
	यदि (ctrl.no_yyset_lineno)
		visible_define("M4_YY_NO_SET_LINENO");
	यदि (ctrl.no_yyget_column)
		visible_define("M4_YY_NO_GET_COLUMN");
	यदि (ctrl.no_yyset_column)
		visible_define("M4_YY_NO_SET_COLUMN");
	यदि (ctrl.no_yyget_in)
		visible_define("M4_YY_NO_GET_IN");
	यदि (ctrl.no_yyset_in)
		visible_define("M4_YY_NO_SET_IN");
	यदि (ctrl.no_yyget_out)
		visible_define("M4_YY_NO_GET_OUT");
	यदि (ctrl.no_yyset_out)
		visible_define("M4_YY_NO_SET_OUT");
	यदि (ctrl.no_yyget_lval)
		visible_define("M4_YY_NO_GET_LVAL");
	यदि (ctrl.no_yyset_lval)
		visible_define("M4_YY_NO_SET_LVAL");
	यदि (ctrl.no_yyget_lloc)
		visible_define("M4_YY_NO_GET_LLOC");
	यदि (ctrl.no_yyset_lloc)
		visible_define("M4_YY_NO_SET_LLOC");
	यदि (ctrl.no_flex_alloc)
		visible_define("M4_YY_NO_FLEX_ALLOC");
	यदि (ctrl.no_flex_realloc)
		visible_define("M4_YY_NO_FLEX_REALLOC");
	यदि (ctrl.no_flex_free)
		visible_define("M4_YY_NO_FLEX_FREE");
	यदि (ctrl.no_get_debug)
		visible_define("M4_YY_NO_GET_DEBUG");
	यदि (ctrl.no_set_debug)
		visible_define("M4_YY_NO_SET_DEBUG");

	यदि (ctrl.no_unistd)
		visible_define("M4_YY_NO_UNISTD_H");

	यदि (ctrl.always_interactive)
		visible_define("M4_YY_ALWAYS_INTERACTIVE");
	यदि (ctrl.never_interactive)
		visible_define("M4_YY_NEVER_INTERACTIVE");
	यदि (ctrl.थाक_used)
		visible_define("M4_YY_STACK_USED");

	यदि (ctrl.rewrite)
		visible_define ( "M4_MODE_REWRITE");
	अन्यथा
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
	खाता   *f = मानक_निकास;

	यदि (!env.did_outfilename) {
		snprintf (outfile_path, परिमाण(outfile_path), outfile_template,
			  ctrl.prefix, suffix());
		env.outfilename = outfile_path;
	}

	ख_लिखो (f, _("Usage: %s [OPTIONS] [FILE]...\n"), program_name);
	ख_लिखो (f,
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
