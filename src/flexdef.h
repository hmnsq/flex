
/* flexdef - definitions file for flex */

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

#నిర్వచితం_కాకపోతే FLEXDEF_H
#నిర్వచించు FLEXDEF_H 1

#నిర్వచితం_కాకపోతే USE_CONFIG_FOR_BUILD
# ifdef HAVE_CONFIG_H
#అన్తర్భావ <config.h>
# endif
#లేకపోతే
#అన్తర్భావ <config_for_build.h>
#అయితే_ముగింపు

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <stdarg.h>
#అన్తర్భావ <setjmp.h>
#అన్తర్భావ <ctype.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <math.h>

#నిర్వచితమైతే HAVE_ASSERT_H
#అన్తర్భావ <assert.h>
#లేకపోతే
#నిర్వచించు ప్రతిజ్ఞా(Pred)
#అయితే_ముగింపు

#నిర్వచితమైతే HAVE_LIMITS_H
#అన్తర్భావ <limits.h>
#అయితే_ముగింపు
/* Required: dup() and dup2() in <unistd.h> */
#అన్తర్భావ <unistd.h>
#నిర్వచితమైతే HAVE_NETINET_లోపల_H
#అన్తర్భావ <netinet/in.h>
#అయితే_ముగింపు
#నిర్వచితమైతే HAVE_SYS_PARAMS_H
#అన్తర్భావ <sys/params.h>
#అయితే_ముగింపు
/* Required: wait() in <sys/wait.h> */
#అన్తర్భావ <sys/wait.h>
#నిర్వచితమైతే HAVE_STDBOOL_H
#అన్తర్భావ <stdbool.h>
#లేదావేళ !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# లేకపోతే
#  define bool పూర్ణాంకం
# endif
# define false 0
# define true 1
#అయితే_ముగింపు
#అన్తర్భావ <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#అన్తర్భావ <regex.h>
/* Required: strcasecmp() in <strings.h> */
#అన్తర్భావ <strings.h>
#అన్తర్భావ "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#ఒకవేళ defined(ENABLE_NLS) && ENABLE_NLS
#నిర్వచితమైతే HAVE_LOCALE_H
#అన్తర్భావ <locale.h>
#అయితే_ముగింపు /* HAVE_LOCALE_H */
#అన్తర్భావ "gettext.h"
#నిర్వచించు _(String) gettext (String)
#లేకపోతే
#నిర్వచించు _(STRING) STRING
#అయితే_ముగింపు /* ENABLE_NLS */

/* Always be prepared to generate an 8-bit scanner. */
#నిర్వచించు CSIZE 256

/* Size of input alphabet - should be size of ASCII set. */
#నిర్వచితం_కాకపోతే DEFAULT_CSIZE
#నిర్వచించు DEFAULT_CSIZE 128
#అయితే_ముగింపు

/* Maximum line length we'll have to deal with. */
#నిర్వచించు MAXLINE 2048

#నిర్వచితం_కాకపోతే MIN
#నిర్వచించు MIN(x,y) ((x) < (y) ? (x) : (y))
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే MAX
#నిర్వచించు MAX(x,y) ((x) > (y) ? (x) : (y))
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే ABS
#నిర్వచించు ABS(x) ((x) < 0 ? -(x) : (x))
#అయితే_ముగింపు

/* Whether an integer is a power of two */
#నిర్వచించు is_power_యొక్క_2(n) ((n) > 0 && ((n) & ((n) - 1)) == 0)

/* Special chk[] values marking the slots taking by end-of-buffer and action
 * numbers.
 */
#నిర్వచించు EOB_POSITION -1
#నిర్వచించు ACTION_POSITION -2

/* Number of data items per line for -f output. */
#నిర్వచించు NUMDATAITEMS 10

/* Number of lines of data in -f output before inserting a blank line for
 * readability.
 */
#నిర్వచించు NUMDATALINES 10

/* transition_struct_out() definitions. */
#నిర్వచించు TRANS_STRUCT_PRINT_నిడివి 14

/* Returns true if an nfa state has an epsilon out-transition slot
 * that can be used.  This definition is currently not used.
 */
#నిర్వచించు FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans2[state] == NO_TRANSITION && \
	 finalst[state] != state)

/* Returns true if an nfa state has an epsilon out-transition character
 * and both slots are free
 */
#నిర్వచించు SUPER_FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans1[state] == NO_TRANSITION) \

/* Maximum number of NFA states that can comprise a DFA state.  It's real
 * big because if there's a lot of rules, the initial state will have a
 * huge epsilon closure.
 */
#నిర్వచించు INITIAL_MAX_DFA_కొలత 750
#నిర్వచించు MAX_DFA_కొలత_INCREMENT 750


/* A note on the following masks.  They are used to mark accepting numbers
 * as being special.  As such, they implicitly limit the number of accepting
 * numbers (i.e., rules) because if there are too many rules the rule numbers
 * will overload the mask bits.  Fortunately, this limit is \large/ (0x2000 ==
 * 8192) so unlikely to actually cause any problems.  A check is made in
 * new_rule() to ensure that this limit is not reached.
 */

/* Mask to mark a trailing context accepting number. */
#నిర్వచించు YY_TRAILING_ముసుగు 0x2000

/* Mask to mark the accepting number of the "head" of a trailing context
 * rule.
 */
#నిర్వచించు YY_TRAILING_తల_ముసుగు 0x4000

/* Maximum number of rules, as outlined in the above note. */
#నిర్వచించు MAX_నియమం (YY_TRAILING_ముసుగు - 1)


/* NIL must be 0.  If not, its special meaning when making equivalence classes
 * (it marks the representative of a given e.c.) will be unidentifiable.
 */
#నిర్వచించు NIL 0

#నిర్వచించు JAM -1			/* to mark a missing DFA transition */
#నిర్వచించు NO_TRANSITION NIL
#నిర్వచించు UNIQUE -1		/* marks a symbol as an e.c. representative */
#నిర్వచించు INFINITE_REPEAT -1		/* for x{5,} constructions */

#నిర్వచించు INITIAL_MAX_CCLS 100	/* max number of unique character classes */
#నిర్వచించు MAX_CCLS_INCREMENT 100

/* Size of table holding members of character classes. */
#నిర్వచించు INITIAL_MAX_CCL_TBL_కొలత 500
#నిర్వచించు MAX_CCL_TBL_కొలత_INCREMENT 250

#నిర్వచించు INITIAL_MAX_నియమాలు 100	/* default maximum number of rules */
#నిర్వచించు MAX_నియమాలు_INCREMENT 100

#నిర్వచించు INITIAL_MNS 2000	/* default maximum number of nfa states */
#నిర్వచించు MNS_INCREMENT 1000	/* amount to bump above by if it's not enough */

#నిర్వచించు INITIAL_MAX_DFAS 1000	/* default maximum number of dfa states */
#నిర్వచించు MAX_DFAS_INCREMENT 1000

#నిర్వచించు JAMSTATE -32766		/* marks a reference to the state that always jams */

/* Maximum number of NFA states. */
#నిర్వచించు గరిష్ఠ_MNS 31999
#నిర్వచించు గరిష్ఠ_MNS_LONG 1999999999

/* Enough so that if it's subtracted from an NFA state number, the result
 * is guaranteed to be negative.
 */
#నిర్వచించు MARKER_DIFFERENCE (గరిష్ఠ_mns+2)

/* Maximum number of nxt/chk pairs for non-templates. */
#నిర్వచించు INITIAL_MAX_XPAIRS 2000
#నిర్వచించు MAX_XPAIRS_INCREMENT 2000

/* Maximum number of nxt/chk pairs needed for templates. */
#నిర్వచించు INITIAL_MAX_TEMPLATE_XPAIRS 2500
#నిర్వచించు MAX_TEMPLATE_XPAIRS_INCREMENT 2500

#నిర్వచించు SYM_EPSILON (CSIZE + 1)	/* to mark transitions on the symbol epsilon */

#నిర్వచించు INITIAL_MAX_SCS 40	/* maximum number of start conditions */
#నిర్వచించు MAX_SCS_INCREMENT 40	/* amount to bump by if it's not enough */

#నిర్వచించు ONE_దొంతర_కొలత 500	/* stack of states with only one out-transition */
#నిర్వచించు SAME_TRANS -1		/* transition is the same as "default" entry for state */

/* The following percentages are used to tune table compression:

 * The percentage the number of out-transitions a state must be of the
 * number of equivalence classes in order to be considered for table
 * compaction by using protos.
 */
#నిర్వచించు PROTO_కొలత_PERCENTAGE 15

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * that the state's transition table is first compared with a potential
 * template of the most common out-transition instead of with the first
 * proto in the proto queue.
 */
#నిర్వచించు CHECK_COM_PERCENTAGE 50

/* The percentage the number of differences between a state's transition
 * table and the proto it was first compared with must be of the total
 * number of out-transitions of the state in order to keep the first
 * proto as a good match and not search any further.
 */
#నిర్వచించు మొదటి_సరిపోలిక_DIFF_PERCENTAGE 10

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to use the proto as an acceptable close match.
 */
#నిర్వచించు ACCEPTABLE_DIFF_PERCENTAGE 50

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * to consider making a template from the state.
 */
#నిర్వచించు TEMPLATE_SAME_PERCENTAGE 60

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to create a new proto from the state.
 */
#నిర్వచించు NEW_PROTO_DIFF_PERCENTAGE 20

/* The percentage the total number of out-transitions of a state must be
 * of the number of equivalence classes in order to consider trying to
 * fit the transition table into "holes" inside the nxt/chk table.
 */
#నిర్వచించు INTERIOR_FIT_PERCENTAGE 15

/* Size of region set aside to cache the complete transition table of
 * protos on the proto queue to enable quick comparisons.
 */
#నిర్వచించు PROT_SAVE_కొలత 2000

#నిర్వచించు MSP 50			/* maximum number of saved protos (protos on the proto queue) */

/* Maximum number of out-transitions a state can have that we'll rummage
 * around through the interior of the internal fast table looking for a
 * spot for it.
 */
#నిర్వచించు MAX_XTIONS_నిండిన_INTERIOR_FIT 4

/* Maximum number of rules which will be reported as being associated
 * with a DFA state.
 */
#నిర్వచించు MAX_ASSOC_నియమాలు 100

/* Number that, if used to subscript an array, has a good chance of producing
 * an error; should be small enough to fit into a short.
 */
#నిర్వచించు BAD_SUBSCRIPT -32767

రకనిర్వచనం గణన trit_t {
	trit_unspecified = -1,
	trit_false = 0,
	trit_true = 1,
} trit;

/* Control variables.  These are in a struct to avoid having to replicate definitions
 * twice for each option, instead a single struct can be declared and externed.
 * If it's in this structure, it has a corresponding m4 symbol.
 */
నిర్మాణం ctrl_bundle_t {
	bool always_interactive;// always use character-by-character input
	FILE *backing_పైకి_file;	// file to summarize backing-up states to 
	bool bison_bridge_lval;	// (--bison-bridge), bison pure calling convention. 
	bool bison_bridge_lloc;	// (--bison-locations), bison yylloc.
	size_t bufsize;		// input buffer size
	bool C_plus_plus;	// (-+ flag) generate a C++ scanner class 
	పూర్ణాంకం csize;		// size of character set for the scanner 
				// 128 for 7-bit chars and 256 for 8-bit 
	bool ddebug;		// (-d) make a "debug" scanner 
	trit do_main;		// generate main part to make lexer standalone.
	bool do_stdinit;	// whether to initialize yyin/yyout to stdin/stdout
	bool do_yylineno;	// if true, generate code to maintain yylineno 
	bool do_yywrap;		// do yywrap() processing on EOF. 
				// If false, EOF treated as "no more files" 
	bool fullspd;		// (-F flag) use Jacobson method of table representation 
	bool fulltbl;		// (-Cf flag) don't compress the DFA state table 
 	bool gen_పంక్తి_dirs;	// (no -L flag) generate #line directives 
	trit interactive;	// (-I) generate an interactive scanner
	bool never_interactive;	// always use buffered input, don't check for tty.
	bool lex_compat;	// (-l), maximize compatibility with AT&T lex 
	bool long_align;	// (-Ca flag), favor long-word alignment for speed 
	bool no_yyinput;	// suppress use of yyinput()
	bool no_unistd;		// suppress inclusion of unistd.h
	bool posix_compat;	// (-X) maximize compatibility with POSIX lex 
	అక్షరం *ఉపసర్గ;		// prefix for externally visible names, default "yy" 
	trit reject_really_వాడిన;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool దొంతర_వాడిన;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	అక్షరం *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	అక్షరం *yydecl;		// user-specified prototype for yylex.
	పూర్ణాంకం yylmax;		// Maximum buffer length if %array
	trit yymore_really_వాడిన;// Force geberation of support code for yymore
	bool yytext_is_array;	// if true (i.e., %array directive), then declare
				// yytext as array instead of a character pointer.
				// Nice and inefficient.
	bool noyyread;		// User supplied a yyread function, don't generate default
	అక్షరం *userinit;		// Code fragment to be inserted before scanning
	అక్షరం *preaction;	// Code fragment to be inserted before each action
	అక్షరం *postaction;	// Code fragment to be inserted after each action
	అక్షరం *emit;		// Specify target language to emit.
	అక్షరం *yyterminate;	// Set a non-default termination hook.
	bool no_yypanic;	// if true, no not generate default yypanic function
 	// flags corresponding to the huge mass of --no-yy options
	bool no_yy_నెట్టు_state;
	bool no_yy_తీయి_state;
	bool no_yy_శిఖరం_state;
	bool no_yyunput;
	bool no_yy_పరిశీలన_బఫరు;
	bool no_yy_పరిశీలన_బైట్లు;
	bool no_yy_పరిశీలన_string;
	bool no_yyget_extra;
	bool no_yyset_extra;
	bool no_yyget_leng;
	bool no_yyget_పాఠ్యం;
	bool no_yyget_lineno;
	bool no_yyset_lineno;
	bool no_yyget_స్తంభం;
	bool no_yyset_స్తంభం;
	bool no_yyget_లోపల;
	bool no_yyset_లోపల;
	bool no_yyget_బహిర్గతం;
	bool no_yyset_బహిర్గతం;
	bool no_yyget_lval;
	bool no_yyset_lval;
	bool no_yyget_lloc;
	bool no_yyset_lloc;
	bool no_flex_alloc;
	bool no_flex_realloc;
	bool no_flex_free;
	bool no_get_debug;
	bool no_సమితి_debug;
	// Properties read from the skeleton
	స్థిరరాశి అక్షరం *backend_name;	// What the back end tells you its name is
	స్థిరరాశి అక్షరం *traceline_re;	// Regular expression for recognizing tracelines */
	స్థిరరాశి అక్షరం *traceline_template;	// templare for emitting trace lines */
	bool have_state_నమోదు_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
నిర్మాణం env_bundle_t {
	bool backing_పైకి_report;	// (-b flag), generate "lex.backup" file 
				// listing backing-up states
	bool did_outfilename;	// whether outfilename was explicitly set
	అక్షరం *headerfilename;	// name of the .h file to generate
	bool nowarn;		// (-w) do not generate warnings 
	పూర్ణాంకం performance_hint;	// if > 0 (i.e., -p flag), generate a report 
				// relating to scanner performance; 
				// if > 1 (-p -p), report 
 				// on minor performance problems, too.
	అక్షరం *outfilename;	// output file name
	bool printstats;	// (-v) dump statistics
	అక్షరం *skelname;		// name of skeleton for code generation
	FILE *skelfile;		// the skeleton file'd descriptor
	bool trace;		// (-T) env.trace processing 
	bool trace_hex; 	// use hex in trace/debug outputs not octal
	bool use_stdout;	// the -t flag
};

/* Name and byte-width information on a type for code-generation purposes. */
నిర్మాణం packtype_t {
	అక్షరం *name;
	size_t వెడల్పు;
};

బాహ్య నిర్మాణం ctrl_bundle_t ctrl;
బాహ్య నిర్మాణం env_bundle_t env;

/* Declarations for global variables. */


/* Variables for flags:
 * syntaxerror - true if a syntax error has been found
 * eofseen - true if we've seen an eof in the input file
 * yymore_used - if true, yymore() is used in input rules
 * reject - if true, generate back-up tables for REJECT macro
 * real_reject - if true, scanner really uses REJECT (as opposed to just
 *   having "reject" set for variable trailing context)
 * continued_action - true if this rule's action is to "fall through" to
 *   the next rule's action (i.e., the '|' action)
 * in_rule - true if we're inside an individual rule, false if not.
 * yymore_really_used - whether to treat yymore() as really used, regardless
 *   of what we think based on references to it in the user's actions.
 * reject_really_used - same for REJECT
  */

బాహ్య bool syntaxerror, eofseen;
బాహ్య పూర్ణాంకం yymore_వాడిన, reject, real_reject, continued_action, లోపల_నియమం;

/* Variables used in the flex input routines:
 * datapos - characters on current output line
 * dataline - number of contiguous lines of data in current data
 * 	statement.  Used to generate readable -f output
 * linenum - current input line number
 * skel_ind - index into "skel" array, if skelfile is nil
 * yyin - input file
 * infilename - name of input file
 * outfilename - name of output file
 * input_files - array holding names of input files
 * num_input_files - size of input_files array
 * program_name - name with which program was invoked
 *
 * action_array - array to hold the rule actions
 * action_size - size of action_array
 * defs1_offset - index where the user's section 1 definitions start
 *	in action_array
 * prolog_offset - index where the prolog starts in action_array
 * action_offset - index where the non-prolog starts in action_array
 * action_index - index where the next action should go, with respect
 * 	to "action_array"
 * always_interactive - if true, generate an interactive scanner
 */

బాహ్య పూర్ణాంకం datapos, dataline, linenum;
బాహ్య పూర్ణాంకం skel_ind;
బాహ్య అక్షరం *infilename;
బాహ్య అక్షరం *extra_type;
బాహ్య అక్షరం **ఆదానం_files;
బాహ్య పూర్ణాంకం అంకె_ఆదానం_files;
బాహ్య అక్షరం *కార్యక్రమం_name;

బాహ్య అక్షరం *action_array;
బాహ్య పూర్ణాంకం action_కొలత;
బాహ్య పూర్ణాంకం defs1_స్థానభ్రంశం, prolog_స్థానభ్రంశం, action_స్థానభ్రంశం, action_సూచీ;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

బాహ్య పూర్ణాంకం onestate[ONE_దొంతర_కొలత], onesym[ONE_దొంతర_కొలత];
బాహ్య పూర్ణాంకం onenext[ONE_దొంతర_కొలత], onedef[ONE_దొంతర_కొలత], onesp;


/* Variables for nfa machine data:
 * maximum_mns - maximal number of NFA states supported by tables
 * current_mns - current maximum on number of NFA states
 * num_rules - number of the last accepting state; also is number of
 * 	rules created so far
 * num_eof_rules - number of <<EOF>> rules
 * default_rule - number of the default rule
 * current_max_rules - current maximum number of rules
 * lastnfa - last nfa state number created
 * firstst - physically the first state of a fragment
 * lastst - last physical state of fragment
 * finalst - last logical state of fragment
 * transchar - transition character
 * trans1 - transition state
 * trans2 - 2nd transition state for epsilons
 * accptnum - accepting number
 * assoc_rule - rule associated with this NFA state (or 0 if none)
 * state_type - a STATE_xxx type identifying whether the state is part
 * 	of a normal rule, the leading state in a trailing context
 * 	rule (i.e., the state which marks the transition from
 * 	recognizing the text-to-be-matched to the beginning of
 * 	the trailing context), or a subsequent state in a trailing
 * 	context rule
 * rule_type - a RULE_xxx type identifying whether this a ho-hum
 * 	normal rule or one which has variable head & trailing
 * 	context
 * rule_linenum - line number associated with rule
 * rule_useful - true if we've determined that the rule can be matched
 * rule_has_nl - true if rule could possibly match a newline
 * ccl_has_nl - true if current ccl could match a newline
 * nlch - default eol char
 * footprint - total size of tables, in bytes.
 */

బాహ్య పూర్ణాంకం గరిష్ఠ_mns, current_mns, current_max_నియమాలు;
బాహ్య పూర్ణాంకం అంకె_నియమాలు, అంకె_eof_నియమాలు, default_నియమం, lastnfa;
బాహ్య పూర్ణాంకం *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
బాహ్య పూర్ణాంకం *accptnum, *assoc_నియమం, *state_type;
బాహ్య పూర్ణాంకం *నియమం_type, *నియమం_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
బాహ్య అక్షరం *నియమం_useful, *నియమం_has_nl, *ccl_has_nl;
బాహ్య పూర్ణాంకం nlch;
బాహ్య size_t footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#నిర్వచించు STATE_సాధారణ 0x1
#నిర్వచించు STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

బాహ్య పూర్ణాంకం current_state_type;

/* Different types of rules. */
#నిర్వచించు నియమం_సాధారణ 0
#నిర్వచించు నియమం_VARIABLE 1

/* True if the input rules include a rule with both variable-length head
 * and trailing context, false otherwise.
 */
బాహ్య bool variable_trailing_context_నియమాలు;


/* Variables for protos:
 * numtemps - number of templates created
 * numprots - number of protos created
 * protprev - backlink to a more-recently used proto
 * protnext - forward link to a less-recently used proto
 * prottbl - base/def table entry for proto
 * protcomst - common state of proto
 * firstprot - number of the most recently used proto
 * lastprot - number of the least recently used proto
 * protsave contains the entire state array for protos
 */

బాహ్య పూర్ణాంకం numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
బాహ్య పూర్ణాంకం protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_కొలత];


/* Variables for managing equivalence classes:
 * numecs - number of equivalence classes
 * nextecm - forward link of Equivalence Class members
 * ecgroup - class number or backward link of EC members
 * nummecs - number of meta-equivalence classes (used to compress
 *   templates)
 * tecfwd - forward link of meta-equivalence classes members
 * tecbck - backward link of MEC's
 */

/* Reserve enough room in the equivalence class arrays so that we
 * can use the CSIZE'th element to hold equivalence class information
 * for the NUL character.  Later we'll move this information into
 * the 0th element.
 */
బాహ్య పూర్ణాంకం numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs;

/* Meta-equivalence classes are indexed starting at 1, so it's possible
 * that they will require positions from 1 .. CSIZE, i.e., CSIZE + 1
 * slots total (since the arrays are 0-based).  nextecm[] and ecgroup[]
 * don't require the extra position since they're indexed from 1 .. CSIZE - 1.
 */
బాహ్య పూర్ణాంకం tecfwd[CSIZE + 1], tecbck[CSIZE + 1];


/* Variables for start conditions:
 * lastsc - last start condition created
 * current_max_scs - current limit on number of start conditions
 * scset - set of rules active in start condition
 * scbol - set of rules active only at the beginning of line in a s.c.
 * scxclu - true if start condition is exclusive
 * sceof - true if start condition has EOF rule
 * scname - start condition name
 */

బాహ్య పూర్ణాంకం lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
బాహ్య అక్షరం *scxclu, *sceof;
బాహ్య పూర్ణాంకం current_max_scs;
బాహ్య స్థిరరాశి అక్షరం **scname;


/* Variables for dfa machine data:
 * current_max_dfa_size - current maximum number of NFA states in DFA
 * current_max_xpairs - current maximum number of non-template xtion pairs
 * current_max_template_xpairs - current maximum number of template pairs
 * current_max_dfas - current maximum number DFA states
 * lastdfa - last dfa state number created
 * nxt - state to enter upon reading character
 * chk - check value to see if "nxt" applies
 * tnxt - internal nxt table for templates
 * base - offset into "nxt" for given state
 * def - where to go if "chk" disallows "nxt" entry
 * nultrans - NUL transition for each state
 * NUL_ec - equivalence class of the NUL character
 * tblend - last "nxt/chk" table entry being used
 * firstfree - first empty entry in "nxt/chk" table
 * dss - nfa state set for each dfa
 * dfasiz - size of nfa state set for each dfa
 * dfaacc - accepting set for each dfa state (if using REJECT), or accepting
 *	number, if not
 * accsiz - size of accepting set for each dfa state
 * dhash - dfa state hash value
 * numas - number of DFA accepting states created; note that this
 *	is not necessarily the same value as num_rules, which is the analogous
 *	value for the NFA
 * numsnpairs - number of state/nextstate transition pairs
 * jambase - position in base/def where the default jam table starts
 * jamstate - state number corresponding to "jam" state
 * end_of_buffer_state - end-of-buffer dfa state number
 */

బాహ్య పూర్ణాంకం current_max_dfa_కొలత, current_max_xpairs;
బాహ్య పూర్ణాంకం current_max_template_xpairs, current_max_dfas;
బాహ్య పూర్ణాంకం lastdfa, *nxt, *chk, *tnxt;
బాహ్య పూర్ణాంకం *పునాది, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
బాహ్య సంఘం dfaacc_union {
	పూర్ణాంకం    *dfaacc_సమితి;
	పూర్ణాంకం     dfaacc_state;
}      *dfaacc;
బాహ్య పూర్ణాంకం *accsiz, *dhash, numas;
బాహ్య పూర్ణాంకం numsnpairs, jambase, jamstate;
బాహ్య పూర్ణాంకం చివర_యొక్క_బఫరు_state;

/* Variables for ccl information:
 * lastccl - ccl index of the last created ccl
 * current_maxccls - current limit on the maximum number of unique ccl's
 * cclmap - maps a ccl index to its set pointer
 * ccllen - gives the length of a ccl
 * cclng - true for a given ccl if the ccl is negated
 * cclreuse - counts how many times a ccl is re-used
 * current_max_ccl_tbl_size - current limit on number of characters needed
 *	to represent the unique ccl's
 * ccltbl - holds the characters in each ccl - indexed by cclmap
 */

బాహ్య పూర్ణాంకం lastccl, *cclmap, *ccllen, *cclng, cclreuse;
బాహ్య పూర్ణాంకం current_maxccls, current_max_ccl_tbl_కొలత;
బాహ్య గుర్తులేని అక్షరం *ccltbl;


/* Variables for miscellaneous information:
 * nmstr - last NAME scanned by the scanner
 * nmval - last numeric scanned by the scanner
 * sectnum - section number currently being parsed
 * nummt - number of empty nxt/chk table entries
 * hshcol - number of hash collisions detected by snstods
 * dfaeql - number of times a newly created dfa was equal to an old one
 * numeps - number of epsilon NFA states created
 * eps2 - number of epsilon states which have 2 out-transitions
 * num_reallocs - number of times it was necessary to realloc() a group
 *	  of arrays
 * tmpuses - number of DFA states that chain to templates
 * totnst - total number of NFA states used to make DFA states
 * peakpairs - peak number of transition pairs we had to store internally
 * numuniq - number of unique transitions
 * numdup - number of duplicate transitions
 * hshsave - number of hash collisions saved by checking number of states
 * num_backing_up - number of DFA states requiring backing up
 * bol_needed - whether scanner needs beginning-of-line recognition
 */

బాహ్య అక్షరం nmstr[MAXLINE];
బాహ్య పూర్ణాంకం sectnum, nummt, hshcol, dfaeql, numeps, eps2, అంకె_reallocs, nmval;
బాహ్య పూర్ణాంకం tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
బాహ్య పూర్ణాంకం అంకె_backing_పైకి, bol_needed;

శూన్య   *allocate_array(పూర్ణాంకం, size_t);
శూన్య   *reallocate_array(శూన్య *, పూర్ణాంకం, size_t);

#నిర్వచించు allocate_integer_array(కొలత) \
	allocate_array(కొలత, పరిమాణం(పూర్ణాంకం))

#నిర్వచించు reallocate_integer_array(array,కొలత) \
	reallocate_array((శూన్య *) array, కొలత, పరిమాణం(పూర్ణాంకం))

#నిర్వచించు allocate_int_ptr_array(కొలత) \
	allocate_array(కొలత, పరిమాణం(పూర్ణాంకం *))

#నిర్వచించు allocate_char_ptr_array(కొలత) \
	allocate_array(కొలత, పరిమాణం(అక్షరం *))

#నిర్వచించు reallocate_int_ptr_array(array,కొలత) \
	reallocate_array((శూన్య *) array, కొలత, పరిమాణం(పూర్ణాంకం *))

#నిర్వచించు reallocate_char_ptr_array(array,కొలత) \
	reallocate_array((శూన్య *) array, కొలత, పరిమాణం(అక్షరం *))

#నిర్వచించు allocate_character_array(కొలత) \
	allocate_array( కొలత, పరిమాణం(అక్షరం))

#నిర్వచించు reallocate_character_array(array,కొలత) \
	reallocate_array((శూన్య *) array, కొలత, పరిమాణం(అక్షరం))

#నిర్వచించు allocate_Character_array(కొలత) \
	allocate_array(కొలత, పరిమాణం(గుర్తులేని అక్షరం))

#నిర్వచించు reallocate_Character_array(array,కొలత) \
	reallocate_array((శూన్య *) array, కొలత, పరిమాణం(గుర్తులేని అక్షరం))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

బాహ్య శూన్య ccladd(పూర్ణాంకం, పూర్ణాంకం);	/* add a single character to a ccl */
బాహ్య పూర్ణాంకం cclinit(శూన్య);	/* make an empty ccl */
బాహ్య శూన్య cclnegate(పూర్ణాంకం);	/* negate a ccl */
బాహ్య పూర్ణాంకం ccl_సమితి_diff (పూర్ణాంకం a, పూర్ణాంకం b); /* set difference of two ccls. */
బాహ్య పూర్ణాంకం ccl_సమితి_union (పూర్ణాంకం a, పూర్ణాంకం b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
బాహ్య శూన్య list_character_సమితి(FILE *, పూర్ణాంకం[]);


/* from file dfa.c */

/* Increase the maximum number of dfas. */
బాహ్య శూన్య increase_max_dfas(శూన్య);

బాహ్య size_t ntod(శూన్య);	/* convert a ndfa to a dfa */


/* from file ecs.c */

/* Convert character classes to set of equivalence classes. */
బాహ్య శూన్య ccl2ecl(శూన్య);

/* Associate equivalence class numbers with class members. */
బాహ్య పూర్ణాంకం cre8ecs(పూర్ణాంకం[], పూర్ణాంకం[], పూర్ణాంకం);

/* Update equivalence classes based on character class transitions. */
బాహ్య శూన్య mkeccl(గుర్తులేని అక్షరం[], పూర్ణాంకం, పూర్ణాంకం[], పూర్ణాంకం[], పూర్ణాంకం, పూర్ణాంకం);

/* Create equivalence class for single character. */
బాహ్య శూన్య mkechar(పూర్ణాంకం, పూర్ణాంకం[], పూర్ణాంకం[]);


/* from file gen.c */

/* Set a conditional amd make it visible in generated code */
బాహ్య శూన్య visible_define (స్థిరరాశి అక్షరం *);

/* And again, with an explicit value part. */
బాహ్య శూన్య visible_define_str (స్థిరరాశి అక్షరం *, స్థిరరాశి అక్షరం *);

/* This time the value part is an int */
బాహ్య శూన్య visible_define_int (స్థిరరాశి అక్షరం *, స్థిరరాశి పూర్ణాంకం);

/* generate transition tables */
బాహ్య శూన్య make_tables(శూన్య);

/* Select a type for optimal packing */
నిర్మాణం packtype_t *optimize_pack(size_t);

/* from file main.c */

బాహ్య శూన్య check_options(శూన్య);
బాహ్య శూన్య flexend(పూర్ణాంకం);
బాహ్య శూన్య usage(శూన్య);


/* from file misc.c */

/* Add the given text to the stored actions. */
బాహ్య శూన్య కూడు_action(స్థిరరాశి అక్షరం *new_పాఠ్యం);

/* True if a string is all lower case. */
బాహ్య పూర్ణాంకం all_క్రింది(అక్షరం *);

/* True if a string is all upper case. */
బాహ్య పూర్ణాంకం all_పై(అక్షరం *);

/* Compare two integers for use by qsort. */
బాహ్య పూర్ణాంకం intcmp(స్థిరరాశి శూన్య *, స్థిరరాశి శూన్య *);

/* Check a character to make sure it's in the expected range. */
బాహ్య శూన్య check_char(పూర్ణాంకం c);

/* Replace upper-case letter to lower-case. */
బాహ్య గుర్తులేని అక్షరం clower(పూర్ణాంకం);

/* strdup() that fails fatally on allocation failures. */
బాహ్య అక్షరం *xstrdup(స్థిరరాశి అక్షరం *);

/* Compare two characters for use by qsort with '\0' sorting last. */
బాహ్య పూర్ణాంకం cclcmp(స్థిరరాశి శూన్య *, స్థిరరాశి శూన్య *);

/* Finish up a block of data declarations. */
బాహ్య శూన్య dataend(స్థిరరాశి అక్షరం *);

/* Flush generated data statements. */
బాహ్య శూన్య dataflush(శూన్య);

/* Report an error message and terminate. */
బాహ్య శూన్య flexerror(స్థిరరాశి అక్షరం *);

/* Report a fatal error message and terminate. */
బాహ్య శూన్య flexfatal(స్థిరరాశి అక్షరం *);

/* Report a fatal error with a pinpoint, and terminate */
#నిర్వచితమైతే HAVE_DECL___FUNC__
#నిర్వచించు flex_die(సందేశం) \
    చేయి{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                కార్యక్రమం_name, __FILE__, (పూర్ణాంకం)__LINE__,\
                __func__,సందేశం);\
        FLEX_EXIT(1);\
    }అయితే(0)
#లేకపోతే /* ! HAVE_DECL___FUNC__ */
#నిర్వచించు flex_die(సందేశం) \
    చేయి{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                కార్యక్రమం_name, __FILE__, (పూర్ణాంకం)__LINE__,\
                సందేశం);\
        FLEX_EXIT(1);\
    }అయితే(0)
#అయితే_ముగింపు /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
బాహ్య శూన్య lerr(స్థిరరాశి అక్షరం *, ...)
#ఒకవేళ defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#అయితే_ముగింపు
;

/* Like lerr, but also exit after displaying message. */
బాహ్య శూన్య lerr_fatal(స్థిరరాశి అక్షరం *, ...)
#ఒకవేళ defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#అయితే_ముగింపు
;

/* Spit out a "#line" statement. */
బాహ్య శూన్య పంక్తి_directive_బహిర్గతం(FILE *, అక్షరం *, పూర్ణాంకం);

/* Mark the current position in the action array as the end of the section 1
 * user defs.
 */
బాహ్య శూన్య mark_defs1(శూన్య);

/* Mark the current position in the action array as the end of the prolog. */
బాహ్య శూన్య mark_prolog(శూన్య);

/* Generate a data statement for a two-dimensional array. */
బాహ్య శూన్య mk2data(పూర్ణాంకం);

బాహ్య శూన్య mkdata(పూర్ణాంకం);	/* generate a data statement */

/* Return the integer represented by a string of digits. */
బాహ్య పూర్ణాంకం myctoi(స్థిరరాశి అక్షరం *);

/* Return character corresponding to escape sequence. */
బాహ్య గుర్తులేని అక్షరం myesc(గుర్తులేని అక్షరం[]);

/* Output a (possibly-formatted) string to the generated scanner. */
బాహ్య శూన్య బహిర్గతం(స్థిరరాశి అక్షరం *);
బాహ్య శూన్య బహిర్గతం_dec(స్థిరరాశి అక్షరం *, పూర్ణాంకం);
బాహ్య శూన్య బహిర్గతం_dec2(స్థిరరాశి అక్షరం *, పూర్ణాంకం, పూర్ణాంకం);
బాహ్య శూన్య బహిర్గతం_hex(స్థిరరాశి అక్షరం *, గుర్తులేని పూర్ణాంకం);
బాహ్య శూన్య బహిర్గతం_str(స్థిరరాశి అక్షరం *, స్థిరరాశి అక్షరం *);
బాహ్య శూన్య బహిర్గతం_str_dec(స్థిరరాశి అక్షరం *, స్థిరరాశి అక్షరం *, పూర్ణాంకం);
బాహ్య శూన్య outc(పూర్ణాంకం);
బాహ్య శూన్య outn(స్థిరరాశి అక్షరం *);
బాహ్య శూన్య బహిర్గతం_m4_define(స్థిరరాశి అక్షరం* def, స్థిరరాశి అక్షరం* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
బాహ్య అక్షరం *readable_form(పూర్ణాంకం);

/* Output a yy_trans_info structure. */
బాహ్య శూన్య transition_struct_బహిర్గతం(పూర్ణాంకం, పూర్ణాంకం);

/* Only needed when using certain broken versions of bison to build parse.c. */
బాహ్య శూన్య *yy_flex_xmalloc(పూర్ణాంకం);


/* from file nfa.c */

/* Add an accepting state to a machine. */
బాహ్య శూన్య కూడు_accept(పూర్ణాంకం, పూర్ణాంకం);

/* Make a given number of copies of a singleton machine. */
బాహ్య పూర్ణాంకం copysingl(పూర్ణాంకం, పూర్ణాంకం);

/* Debugging routine to write out an nfa. */
బాహ్య శూన్య dumpnfa(పూర్ణాంకం);

/* Finish up the processing for a rule. */
బాహ్య శూన్య ముగింపు_నియమం(పూర్ణాంకం, bool, పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం);

/* Connect two machines together. */
బాహ్య పూర్ణాంకం link_machines(పూర్ణాంకం, పూర్ణాంకం);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
బాహ్య శూన్య mark_beginning_as_సాధారణ(పూర్ణాంకం);

/* Make a machine that branches to two machines. */
బాహ్య పూర్ణాంకం mkbranch(పూర్ణాంకం, పూర్ణాంకం);

బాహ్య పూర్ణాంకం mkclos(పూర్ణాంకం);	/* convert a machine into a closure */
బాహ్య పూర్ణాంకం mkopt(పూర్ణాంకం);	/* make a machine optional */

/* Make a machine that matches either one of two machines. */
బాహ్య పూర్ణాంకం mkor(పూర్ణాంకం, పూర్ణాంకం);

/* Convert a machine into a positive closure. */
బాహ్య పూర్ణాంకం mkposcl(పూర్ణాంకం);

బాహ్య పూర్ణాంకం mkrep(పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం);	/* make a replicated machine */

/* Create a state with a transition on a given symbol. */
బాహ్య పూర్ణాంకం mkstate(పూర్ణాంకం);

బాహ్య శూన్య new_నియమం(శూన్య);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
బాహ్య శూన్య build_eof_action(శూన్య);

/* Write out a message formatted with one string, pinpointing its location. */
బాహ్య శూన్య format_pinpoint_సందేశం(స్థిరరాశి అక్షరం *, స్థిరరాశి అక్షరం *);

/* Write out a message, pinpointing its location. */
బాహ్య శూన్య pinpoint_సందేశం(స్థిరరాశి అక్షరం *);

/* Write out a warning, pinpointing it at the given line. */
బాహ్య శూన్య పంక్తి_warning(స్థిరరాశి అక్షరం *, పూర్ణాంకం);

/* Write out a message, pinpointing it at the given line. */
బాహ్య శూన్య పంక్తి_pinpoint(స్థిరరాశి అక్షరం *, పూర్ణాంకం);

/* Report a formatted syntax error. */
బాహ్య శూన్య format_synerr(స్థిరరాశి అక్షరం *, స్థిరరాశి అక్షరం *);
బాహ్య శూన్య synerr(స్థిరరాశి అక్షరం *);	/* report a syntax error */
బాహ్య శూన్య format_warn(స్థిరరాశి అక్షరం *, స్థిరరాశి అక్షరం *);
బాహ్య శూన్య lwarn(స్థిరరాశి అక్షరం *);	/* report a warning */
బాహ్య శూన్య yyerror(స్థిరరాశి అక్షరం *);	/* report a parse error */
బాహ్య పూర్ణాంకం yyparse(శూన్య);		/* the YACC parser */

/* Ship a comment to the generated output */
బాహ్య శూన్య comment(స్థిరరాశి అక్షరం *);

/* from file scan.l */

/* The Flex-generated scanner for flex. */
బాహ్య పూర్ణాంకం flexscan(శూన్య);

/* Open the given file (if NULL, stdin) for scanning. */
బాహ్య శూన్య సమితి_ఆదానం_file(అక్షరం *);

/* from file skeletons.c */

/* return the correct file suffix for the selected back end */
స్థిరరాశి అక్షరం *suffix (శూన్య);

/* Mine a text-valued property out of the skeleton file */
బాహ్య స్థిరరాశి అక్షరం *skel_property(స్థిరరాశి అక్షరం *);

/* Is the default back end selected?*/
బాహ్య bool is_default_backend(శూన్య);

/* Select a backend by name */
బాహ్య శూన్య backend_by_name(స్థిరరాశి అక్షరం *);

/* Write out one section of the skeleton file. */
బాహ్య శూన్య skelout(bool);

/* from file sym.c */

/* Save the text of a character class. */
బాహ్య శూన్య cclinstal(అక్షరం[], పూర్ణాంకం);

/* Lookup the number associated with character class. */
బాహ్య పూర్ణాంకం ccllookup(అక్షరం[]);

బాహ్య శూన్య ndinstal(స్థిరరాశి అక్షరం *, అక్షరం[]);	/* install a name definition */
బాహ్య అక్షరం *ndlookup(స్థిరరాశి అక్షరం *);	/* lookup a name definition */

/* Increase maximum number of SC's. */
బాహ్య శూన్య scextend(శూన్య);
బాహ్య శూన్య scinstal(స్థిరరాశి అక్షరం *, bool);	/* make a start condition */

/* Lookup the number associated with a start condition. */
బాహ్య పూర్ణాంకం sclookup(స్థిరరాశి అక్షరం *);

/* Supply context argument for a function if required */
బాహ్య శూన్య context_call(అక్షరం *);

/* from file tblcmp.c */

/* Build table entries for dfa state. */
బాహ్య శూన్య bldtbl(పూర్ణాంకం[], పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం);

బాహ్య శూన్య cmptmps(శూన్య);	/* compress template table entries */
బాహ్య శూన్య expand_nxt_chk(శూన్య);	/* increase nxt/chk arrays */

/* Finds a space in the table for a state to be placed. */
బాహ్య పూర్ణాంకం కనుగొను_పట్టిక_space(పూర్ణాంకం *, పూర్ణాంకం);
బాహ్య శూన్య inittbl(శూన్య);	/* initialize transition tables */

/* Make the default, "jam" table entries. */
బాహ్య శూన్య mkdeftbl(శూన్య);

/* Create table entries for a state (or state fragment) which has
 * only one out-transition.
 */
బాహ్య శూన్య mk1tbl(పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం);

/* Place a state into full speed transition table. */
బాహ్య శూన్య ఉంచు_state(పూర్ణాంకం *, పూర్ణాంకం, పూర్ణాంకం);

/* Save states with only one out-transition to be processed later. */
బాహ్య శూన్య stack1(పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం);


/* from file yylex.c */

బాహ్య పూర్ణాంకం yylex(శూన్య);

/* A growable array. See buf.c. */
నిర్మాణం Buf {
	శూన్య   *elts;		/* elements. */
	పూర్ణాంకం     nelts;		/* number of elements. */
	size_t  elt_కొలత;	/* in bytes. */
	పూర్ణాంకం     nmax;		/* max capacity of elements. */
};

బాహ్య శూన్య buf_init(నిర్మాణం Buf * buf, size_t elem_కొలత);
బాహ్య శూన్య buf_destroy(నిర్మాణం Buf * buf);
బాహ్య నిర్మాణం Buf *buf_append(నిర్మాణం Buf * buf, స్థిరరాశి శూన్య *ptr, పూర్ణాంకం n_elem);
బాహ్య నిర్మాణం Buf *buf_strappend(నిర్మాణం Buf *, స్థిరరాశి అక్షరం *str);
బాహ్య నిర్మాణం Buf *buf_strnappend(నిర్మాణం Buf *, స్థిరరాశి అక్షరం *str, పూర్ణాంకం nchars);
బాహ్య నిర్మాణం Buf *buf_prints(నిర్మాణం Buf *buf, స్థిరరాశి అక్షరం *fmt, స్థిరరాశి అక్షరం* s);

బాహ్య నిర్మాణం Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
బాహ్య నిర్మాణం Buf శిఖరం_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#నిర్వచించు బహిర్గతం_BEGIN_సంకేతం() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#నిర్వచించు బహిర్గతం_చివర_సంకేతం()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
బాహ్య jmp_buf flex_main_jmp_buf;

#నిర్వచించు FLEX_EXIT(స్థితి_2) longjmp(flex_main_jmp_buf,(స్థితి_2)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
బాహ్య అక్షరం *chomp (అక్షరం *str);

/* ctype functions forced to return boolean */
#నిర్వచించు b_isalnum(c) (అక్షరమా_అంకెనా(c)?true:false)
#నిర్వచించు b_isalpha(c) (అక్షరమా(c)?true:false)
#నిర్వచించు b_isascii(c) (isascii(c)?true:false)
#నిర్వచించు b_isblank(c) (isblank(c)?true:false)
#నిర్వచించు b_iscntrl(c) (iscntrl(c)?true:false)
#నిర్వచించు b_isdigit(c) (అంకెనా(c)?true:false)
#నిర్వచించు b_isgraph(c) (isgraph(c)?true:false)
#నిర్వచించు b_islower(c) (islower(c)?true:false)
#నిర్వచించు b_isprint(c) (isprint(c)?true:false)
#నిర్వచించు b_ispunct(c) (ispunct(c)?true:false)
#నిర్వచించు b_isspace(c) (ఖాళీనా(c)?true:false)
#నిర్వచించు b_isupper(c) (isupper(c)?true:false)
#నిర్వచించు b_isxdigit(c) (isxdigit(c)?true:false)

/* return true if char is uppercase or lowercase. */
bool has_case(పూర్ణాంకం c);

/* Change case of character if possible. */
పూర్ణాంకం తిరగేయి_case(పూర్ణాంకం c);

/* return false if [c1-c2] is ambiguous for a caseless scanner. */
bool range_covers_case (పూర్ణాంకం c1, పూర్ణాంకం c2);

/*
 *  From "filter.c"
 */

/** A single stdio filter to execute.
 *  The filter may be external, such as "sed", or it
 *  may be internal, as a function call.
 */
నిర్మాణం filter {
    పూర్ణాంకం    (*filter_func)(నిర్మాణం filter*); /**< internal filter function */
    శూన్య * extra;         /**< extra data passed to filter_func */
	పూర్ణాంకం     argc;         /**< arg count */
	స్థిరరాశి అక్షరం ** argv;   /**< arg vector, \0-terminated */
    నిర్మాణం filter * తదుపరి; /**< next filter or NULL */
};

/* output filter chain */
బాహ్య నిర్మాణం filter * output_chain;
బాహ్య నిర్మాణం filter *filter_create_ext (నిర్మాణం filter * chain, స్థిరరాశి అక్షరం *cmd, ...);
నిర్మాణం filter *filter_create_int(నిర్మాణం filter *chain,
				  పూర్ణాంకం (*filter_func) (నిర్మాణం filter *),
                  శూన్య *extra);
బాహ్య bool filter_apply_chain(నిర్మాణం filter * chain);
బాహ్య పూర్ణాంకం filter_truncate(నిర్మాణం filter * chain, పూర్ణాంకం max_len);
బాహ్య పూర్ణాంకం filter_tee_శీర్షిక(నిర్మాణం filter *chain);
బాహ్య పూర్ణాంకం filter_fix_linedirs(నిర్మాణం filter *chain);


/*
 * From "regex.c"
 */

బాహ్య regex_t regex_linedir;
bool flex_init_regex(స్థిరరాశి అక్షరం *);
శూన్య flex_regcomp(regex_t *preg, స్థిరరాశి అక్షరం *regex, పూర్ణాంకం cflags);
అక్షరం   *regmatch_dup (regmatch_t * m, స్థిరరాశి అక్షరం *src);
అక్షరం   *regmatch_cpy (regmatch_t * m, అక్షరం *dest, స్థిరరాశి అక్షరం *src);
పూర్ణాంకం regmatch_len (regmatch_t * m);
పూర్ణాంకం regmatch_strtol (regmatch_t * m, స్థిరరాశి అక్షరం *src, అక్షరం **endptr, పూర్ణాంకం పునాది);
bool regmatch_ఖాళీలు (regmatch_t * m);

/* From "scanflags.h" */
రకనిర్వచనం గుర్తులేని పూర్ణాంకం scanflags_t;
బాహ్య scanflags_t* _sf_stk;
బాహ్య size_t sf_శిఖరం_ix, _sf_max; /**< stack of scanner flags. */
#నిర్వచించు _SF_CASE_INS   ((scanflags_t) 0x0001)
#నిర్వచించు _SF_DOT_ALL    ((scanflags_t) 0x0002)
#నిర్వచించు _SF_SKIP_WS    ((scanflags_t) 0x0004)
#నిర్వచించు sf_శిఖరం()           (_sf_stk[sf_శిఖరం_ix])
#నిర్వచించు sf_case_ins()      (sf_శిఖరం() & _SF_CASE_INS)
#నిర్వచించు sf_dot_all()       (sf_శిఖరం() & _SF_DOT_ALL)
#నిర్వచించు sf_skip_ws()       (sf_శిఖరం() & _SF_SKIP_WS)
#నిర్వచించు sf_సమితి_case_ins(X)      ((X) ? (sf_శిఖరం() |= _SF_CASE_INS) : (sf_శిఖరం() &= ~_SF_CASE_INS))
#నిర్వచించు sf_సమితి_dot_all(X)       ((X) ? (sf_శిఖరం() |= _SF_DOT_ALL)  : (sf_శిఖరం() &= ~_SF_DOT_ALL))
#నిర్వచించు sf_సమితి_skip_ws(X)       ((X) ? (sf_శిఖరం() |= _SF_SKIP_WS)  : (sf_శిఖరం() &= ~_SF_SKIP_WS))
బాహ్య శూన్య sf_init(శూన్య);
బాహ్య శూన్య sf_నెట్టు(శూన్య);
బాహ్య శూన్య sf_తీయి(శూన్య);


#అయితే_ముగింపు /* not defined FLEXDEF_H */
