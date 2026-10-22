
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

#यदि_अपरिभाषितम् FLEXDEF_H
#परिभाषय FLEXDEF_H 1

#यदि_अपरिभाषितम् USE_CONFIG_FOR_BUILD
# ifdef HAVE_CONFIG_H
#अन्तर्भाव <config.h>
# endif
#अन्यथा
#अन्तर्भाव <config_for_build.h>
#यदि_अन्तः

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdarg.h>
#अन्तर्भाव <setjmp.h>
#अन्तर्भाव <ctype.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <math.h>

#यदि_परिभाषितम् HAVE_ASSERT_H
#अन्तर्भाव <assert.h>
#अन्यथा
#परिभाषय प्रतिज्ञा(Pred)
#यदि_अन्तः

#यदि_परिभाषितम् HAVE_LIMITS_H
#अन्तर्भाव <limits.h>
#यदि_अन्तः
/* Required: dup() and dup2() in <unistd.h> */
#अन्तर्भाव <unistd.h>
#यदि_परिभाषितम् HAVE_NETINET_अन्तर्_H
#अन्तर्भाव <netinet/in.h>
#यदि_अन्तः
#यदि_परिभाषितम् HAVE_SYS_PARAMS_H
#अन्तर्भाव <sys/params.h>
#यदि_अन्तः
/* Required: wait() in <sys/wait.h> */
#अन्तर्भाव <sys/wait.h>
#यदि_परिभाषितम् HAVE_STDBOOL_H
#अन्तर्भाव <stdbool.h>
#नोचेद्यदि !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# अन्यथा
#  define bool पूर्णाङ्क
# endif
# define false 0
# define true 1
#यदि_अन्तः
#अन्तर्भाव <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#अन्तर्भाव <regex.h>
/* Required: strcasecmp() in <strings.h> */
#अन्तर्भाव <strings.h>
#अन्तर्भाव "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#यदि defined(ENABLE_NLS) && ENABLE_NLS
#यदि_परिभाषितम् HAVE_LOCALE_H
#अन्तर्भाव <locale.h>
#यदि_अन्तः /* HAVE_LOCALE_H */
#अन्तर्भाव "gettext.h"
#परिभाषय _(String) gettext (String)
#अन्यथा
#परिभाषय _(STRING) STRING
#यदि_अन्तः /* ENABLE_NLS */

/* Always be prepared to generate an 8-bit scanner. */
#परिभाषय CSIZE 256

/* Size of input alphabet - should be size of ASCII set. */
#यदि_अपरिभाषितम् DEFAULT_CSIZE
#परिभाषय DEFAULT_CSIZE 128
#यदि_अन्तः

/* Maximum line length we'll have to deal with. */
#परिभाषय MAXLINE 2048

#यदि_अपरिभाषितम् MIN
#परिभाषय MIN(x,y) ((x) < (y) ? (x) : (y))
#यदि_अन्तः
#यदि_अपरिभाषितम् MAX
#परिभाषय MAX(x,y) ((x) > (y) ? (x) : (y))
#यदि_अन्तः
#यदि_अपरिभाषितम् ABS
#परिभाषय ABS(x) ((x) < 0 ? -(x) : (x))
#यदि_अन्तः

/* Whether an integer is a power of two */
#परिभाषय is_power_सम्बन्धि_2(n) ((n) > 0 && ((n) & ((n) - 1)) == 0)

/* Special chk[] values marking the slots taking by end-of-buffer and action
 * numbers.
 */
#परिभाषय EOB_POSITION -1
#परिभाषय ACTION_POSITION -2

/* Number of data items per line for -f output. */
#परिभाषय NUMDATAITEMS 10

/* Number of lines of data in -f output before inserting a blank line for
 * readability.
 */
#परिभाषय NUMDATALINES 10

/* transition_struct_out() definitions. */
#परिभाषय TRANS_STRUCT_PRINT_दीर्घता 14

/* Returns true if an nfa state has an epsilon out-transition slot
 * that can be used.  This definition is currently not used.
 */
#परिभाषय FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans2[state] == NO_TRANSITION && \
	 finalst[state] != state)

/* Returns true if an nfa state has an epsilon out-transition character
 * and both slots are free
 */
#परिभाषय SUPER_FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans1[state] == NO_TRANSITION) \

/* Maximum number of NFA states that can comprise a DFA state.  It's real
 * big because if there's a lot of rules, the initial state will have a
 * huge epsilon closure.
 */
#परिभाषय INITIAL_MAX_DFA_आकार 750
#परिभाषय MAX_DFA_आकार_INCREMENT 750


/* A note on the following masks.  They are used to mark accepting numbers
 * as being special.  As such, they implicitly limit the number of accepting
 * numbers (i.e., rules) because if there are too many rules the rule numbers
 * will overload the mask bits.  Fortunately, this limit is \large/ (0x2000 ==
 * 8192) so unlikely to actually cause any problems.  A check is made in
 * new_rule() to ensure that this limit is not reached.
 */

/* Mask to mark a trailing context accepting number. */
#परिभाषय YY_TRAILING_आवरणम् 0x2000

/* Mask to mark the accepting number of the "head" of a trailing context
 * rule.
 */
#परिभाषय YY_TRAILING_शीर्ष_आवरणम् 0x4000

/* Maximum number of rules, as outlined in the above note. */
#परिभाषय MAX_नियमः (YY_TRAILING_आवरणम् - 1)


/* NIL must be 0.  If not, its special meaning when making equivalence classes
 * (it marks the representative of a given e.c.) will be unidentifiable.
 */
#परिभाषय NIL 0

#परिभाषय JAM -1			/* to mark a missing DFA transition */
#परिभाषय NO_TRANSITION NIL
#परिभाषय UNIQUE -1		/* marks a symbol as an e.c. representative */
#परिभाषय INFINITE_REPEAT -1		/* for x{5,} constructions */

#परिभाषय INITIAL_MAX_CCLS 100	/* max number of unique character classes */
#परिभाषय MAX_CCLS_INCREMENT 100

/* Size of table holding members of character classes. */
#परिभाषय INITIAL_MAX_CCL_TBL_आकार 500
#परिभाषय MAX_CCL_TBL_आकार_INCREMENT 250

#परिभाषय INITIAL_MAX_नियमाः 100	/* default maximum number of rules */
#परिभाषय MAX_नियमाः_INCREMENT 100

#परिभाषय INITIAL_MNS 2000	/* default maximum number of nfa states */
#परिभाषय MNS_INCREMENT 1000	/* amount to bump above by if it's not enough */

#परिभाषय INITIAL_MAX_DFAS 1000	/* default maximum number of dfa states */
#परिभाषय MAX_DFAS_INCREMENT 1000

#परिभाषय JAMSTATE -32766		/* marks a reference to the state that always jams */

/* Maximum number of NFA states. */
#परिभाषय अधिकतमम्_MNS 31999
#परिभाषय अधिकतमम्_MNS_LONG 1999999999

/* Enough so that if it's subtracted from an NFA state number, the result
 * is guaranteed to be negative.
 */
#परिभाषय MARKER_DIFFERENCE (अधिकतमम्_mns+2)

/* Maximum number of nxt/chk pairs for non-templates. */
#परिभाषय INITIAL_MAX_XPAIRS 2000
#परिभाषय MAX_XPAIRS_INCREMENT 2000

/* Maximum number of nxt/chk pairs needed for templates. */
#परिभाषय INITIAL_MAX_TEMPLATE_XPAIRS 2500
#परिभाषय MAX_TEMPLATE_XPAIRS_INCREMENT 2500

#परिभाषय SYM_EPSILON (CSIZE + 1)	/* to mark transitions on the symbol epsilon */

#परिभाषय INITIAL_MAX_SCS 40	/* maximum number of start conditions */
#परिभाषय MAX_SCS_INCREMENT 40	/* amount to bump by if it's not enough */

#परिभाषय ONE_राशिः_आकार 500	/* stack of states with only one out-transition */
#परिभाषय SAME_TRANS -1		/* transition is the same as "default" entry for state */

/* The following percentages are used to tune table compression:

 * The percentage the number of out-transitions a state must be of the
 * number of equivalence classes in order to be considered for table
 * compaction by using protos.
 */
#परिभाषय PROTO_आकार_PERCENTAGE 15

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * that the state's transition table is first compared with a potential
 * template of the most common out-transition instead of with the first
 * proto in the proto queue.
 */
#परिभाषय CHECK_COM_PERCENTAGE 50

/* The percentage the number of differences between a state's transition
 * table and the proto it was first compared with must be of the total
 * number of out-transitions of the state in order to keep the first
 * proto as a good match and not search any further.
 */
#परिभाषय FIRST_मेलनम्_DIFF_PERCENTAGE 10

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to use the proto as an acceptable close match.
 */
#परिभाषय ACCEPTABLE_DIFF_PERCENTAGE 50

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * to consider making a template from the state.
 */
#परिभाषय TEMPLATE_SAME_PERCENTAGE 60

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to create a new proto from the state.
 */
#परिभाषय NEW_PROTO_DIFF_PERCENTAGE 20

/* The percentage the total number of out-transitions of a state must be
 * of the number of equivalence classes in order to consider trying to
 * fit the transition table into "holes" inside the nxt/chk table.
 */
#परिभाषय INTERIOR_FIT_PERCENTAGE 15

/* Size of region set aside to cache the complete transition table of
 * protos on the proto queue to enable quick comparisons.
 */
#परिभाषय PROT_SAVE_आकार 2000

#परिभाषय MSP 50			/* maximum number of saved protos (protos on the proto queue) */

/* Maximum number of out-transitions a state can have that we'll rummage
 * around through the interior of the internal fast table looking for a
 * spot for it.
 */
#परिभाषय MAX_XTIONS_पूर्णम्_INTERIOR_FIT 4

/* Maximum number of rules which will be reported as being associated
 * with a DFA state.
 */
#परिभाषय MAX_ASSOC_नियमाः 100

/* Number that, if used to subscript an array, has a good chance of producing
 * an error; should be small enough to fit into a short.
 */
#परिभाषय BAD_SUBSCRIPT -32767

प्रकारनिर्देश गणना trit_t {
	trit_unspecified = -1,
	trit_false = 0,
	trit_true = 1,
} trit;

/* Control variables.  These are in a struct to avoid having to replicate definitions
 * twice for each option, instead a single struct can be declared and externed.
 * If it's in this structure, it has a corresponding m4 symbol.
 */
संरचना ctrl_bundle_t {
	bool always_interactive;// always use character-by-character input
	FILE *backing_ऊर्ध्वम्_file;	// file to summarize backing-up states to 
	bool bison_bridge_lval;	// (--bison-bridge), bison pure calling convention. 
	bool bison_bridge_lloc;	// (--bison-locations), bison yylloc.
	size_t bufsize;		// input buffer size
	bool C_plus_plus;	// (-+ flag) generate a C++ scanner class 
	पूर्णाङ्क csize;		// size of character set for the scanner 
				// 128 for 7-bit chars and 256 for 8-bit 
	bool ddebug;		// (-d) make a "debug" scanner 
	trit do_main;		// generate main part to make lexer standalone.
	bool do_stdinit;	// whether to initialize yyin/yyout to stdin/stdout
	bool do_yylineno;	// if true, generate code to maintain yylineno 
	bool do_yywrap;		// do yywrap() processing on EOF. 
				// If false, EOF treated as "no more files" 
	bool fullspd;		// (-F flag) use Jacobson method of table representation 
	bool fulltbl;		// (-Cf flag) don't compress the DFA state table 
 	bool gen_पङ्क्तिः_dirs;	// (no -L flag) generate #line directives 
	trit interactive;	// (-I) generate an interactive scanner
	bool never_interactive;	// always use buffered input, don't check for tty.
	bool lex_compat;	// (-l), maximize compatibility with AT&T lex 
	bool long_align;	// (-Ca flag), favor long-word alignment for speed 
	bool no_yyinput;	// suppress use of yyinput()
	bool no_unistd;		// suppress inclusion of unistd.h
	bool posix_compat;	// (-X) maximize compatibility with POSIX lex 
	वर्ण *उपसर्गः;		// prefix for externally visible names, default "yy" 
	trit reject_really_प्रयुक्तम्;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool राशिः_प्रयुक्तम्;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	वर्ण *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	वर्ण *yydecl;		// user-specified prototype for yylex.
	पूर्णाङ्क yylmax;		// Maximum buffer length if %array
	trit yymore_really_प्रयुक्तम्;// Force geberation of support code for yymore
	bool yytext_is_array;	// if true (i.e., %array directive), then declare
				// yytext as array instead of a character pointer.
				// Nice and inefficient.
	bool noyyread;		// User supplied a yyread function, don't generate default
	वर्ण *userinit;		// Code fragment to be inserted before scanning
	वर्ण *preaction;	// Code fragment to be inserted before each action
	वर्ण *postaction;	// Code fragment to be inserted after each action
	वर्ण *emit;		// Specify target language to emit.
	वर्ण *yyterminate;	// Set a non-default termination hook.
	bool no_yypanic;	// if true, no not generate default yypanic function
 	// flags corresponding to the huge mass of --no-yy options
	bool no_yy_प्रक्षिप_state;
	bool no_yy_निष्कासय_state;
	bool no_yy_शिखरम्_state;
	bool no_yyunput;
	bool no_yy_अवलोकनम्_बफर;
	bool no_yy_अवलोकनम्_अष्टकानि;
	bool no_yy_अवलोकनम्_string;
	bool no_yyget_extra;
	bool no_yyset_extra;
	bool no_yyget_leng;
	bool no_yyget_text;
	bool no_yyget_lineno;
	bool no_yyset_lineno;
	bool no_yyget_column;
	bool no_yyset_column;
	bool no_yyget_अन्तर्;
	bool no_yyset_अन्तर्;
	bool no_yyget_बहिर्गमनम्;
	bool no_yyset_बहिर्गमनम्;
	bool no_yyget_lval;
	bool no_yyset_lval;
	bool no_yyget_lloc;
	bool no_yyset_lloc;
	bool no_flex_alloc;
	bool no_flex_realloc;
	bool no_flex_free;
	bool no_get_debug;
	bool no_समुच्चयः_debug;
	// Properties read from the skeleton
	ध्रुव वर्ण *backend_name;	// What the back end tells you its name is
	ध्रुव वर्ण *traceline_re;	// Regular expression for recognizing tracelines */
	ध्रुव वर्ण *traceline_template;	// templare for emitting trace lines */
	bool have_state_प्रविष्टिः_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
संरचना env_bundle_t {
	bool backing_ऊर्ध्वम्_report;	// (-b flag), generate "lex.backup" file 
				// listing backing-up states
	bool did_outfilename;	// whether outfilename was explicitly set
	वर्ण *headerfilename;	// name of the .h file to generate
	bool nowarn;		// (-w) do not generate warnings 
	पूर्णाङ्क performance_hint;	// if > 0 (i.e., -p flag), generate a report 
				// relating to scanner performance; 
				// if > 1 (-p -p), report 
 				// on minor performance problems, too.
	वर्ण *outfilename;	// output file name
	bool printstats;	// (-v) dump statistics
	वर्ण *skelname;		// name of skeleton for code generation
	FILE *skelfile;		// the skeleton file'd descriptor
	bool trace;		// (-T) env.trace processing 
	bool trace_hex; 	// use hex in trace/debug outputs not octal
	bool use_stdout;	// the -t flag
};

/* Name and byte-width information on a type for code-generation purposes. */
संरचना packtype_t {
	वर्ण *name;
	size_t विस्तारः;
};

बाह्य संरचना ctrl_bundle_t ctrl;
बाह्य संरचना env_bundle_t env;

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

बाह्य bool syntaxerror, eofseen;
बाह्य पूर्णाङ्क yymore_प्रयुक्तम्, reject, real_reject, continued_action, अन्तर्_नियमः;

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

बाह्य पूर्णाङ्क datapos, dataline, linenum;
बाह्य पूर्णाङ्क skel_ind;
बाह्य वर्ण *infilename;
बाह्य वर्ण *extra_type;
बाह्य वर्ण **निवेशः_files;
बाह्य पूर्णाङ्क अङ्कः_निवेशः_files;
बाह्य वर्ण *क्रमादेशः_name;

बाह्य वर्ण *action_array;
बाह्य पूर्णाङ्क action_आकार;
बाह्य पूर्णाङ्क defs1_विस्थापनम्, prolog_विस्थापनम्, action_विस्थापनम्, action_सूचकांक;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

बाह्य पूर्णाङ्क onestate[ONE_राशिः_आकार], onesym[ONE_राशिः_आकार];
बाह्य पूर्णाङ्क onenext[ONE_राशिः_आकार], onedef[ONE_राशिः_आकार], onesp;


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

बाह्य पूर्णाङ्क अधिकतमम्_mns, current_mns, current_max_नियमाः;
बाह्य पूर्णाङ्क अङ्कः_नियमाः, अङ्कः_eof_नियमाः, default_नियमः, lastnfa;
बाह्य पूर्णाङ्क *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
बाह्य पूर्णाङ्क *accptnum, *assoc_नियमः, *state_type;
बाह्य पूर्णाङ्क *नियमः_type, *नियमः_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
बाह्य वर्ण *नियमः_useful, *नियमः_has_nl, *ccl_has_nl;
बाह्य पूर्णाङ्क nlch;
बाह्य size_t footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#परिभाषय STATE_प्रसामान्यम् 0x1
#परिभाषय STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

बाह्य पूर्णाङ्क current_state_type;

/* Different types of rules. */
#परिभाषय नियमः_प्रसामान्यम् 0
#परिभाषय नियमः_VARIABLE 1

/* True if the input rules include a rule with both variable-length head
 * and trailing context, false otherwise.
 */
बाह्य bool variable_trailing_context_नियमाः;


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

बाह्य पूर्णाङ्क numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
बाह्य पूर्णाङ्क protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_आकार];


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
बाह्य पूर्णाङ्क numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs;

/* Meta-equivalence classes are indexed starting at 1, so it's possible
 * that they will require positions from 1 .. CSIZE, i.e., CSIZE + 1
 * slots total (since the arrays are 0-based).  nextecm[] and ecgroup[]
 * don't require the extra position since they're indexed from 1 .. CSIZE - 1.
 */
बाह्य पूर्णाङ्क tecfwd[CSIZE + 1], tecbck[CSIZE + 1];


/* Variables for start conditions:
 * lastsc - last start condition created
 * current_max_scs - current limit on number of start conditions
 * scset - set of rules active in start condition
 * scbol - set of rules active only at the beginning of line in a s.c.
 * scxclu - true if start condition is exclusive
 * sceof - true if start condition has EOF rule
 * scname - start condition name
 */

बाह्य पूर्णाङ्क lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
बाह्य वर्ण *scxclu, *sceof;
बाह्य पूर्णाङ्क current_max_scs;
बाह्य ध्रुव वर्ण **scname;


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

बाह्य पूर्णाङ्क current_max_dfa_आकार, current_max_xpairs;
बाह्य पूर्णाङ्क current_max_template_xpairs, current_max_dfas;
बाह्य पूर्णाङ्क lastdfa, *nxt, *chk, *tnxt;
बाह्य पूर्णाङ्क *आधारः, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
बाह्य सङ्घ dfaacc_union {
	पूर्णाङ्क    *dfaacc_समुच्चयः;
	पूर्णाङ्क     dfaacc_state;
}      *dfaacc;
बाह्य पूर्णाङ्क *accsiz, *dhash, numas;
बाह्य पूर्णाङ्क numsnpairs, jambase, jamstate;
बाह्य पूर्णाङ्क अन्तः_सम्बन्धि_बफर_state;

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

बाह्य पूर्णाङ्क lastccl, *cclmap, *ccllen, *cclng, cclreuse;
बाह्य पूर्णाङ्क current_maxccls, current_max_ccl_tbl_आकार;
बाह्य अचिह्नित वर्ण *ccltbl;


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

बाह्य वर्ण nmstr[MAXLINE];
बाह्य पूर्णाङ्क sectnum, nummt, hshcol, dfaeql, numeps, eps2, अङ्कः_reallocs, nmval;
बाह्य पूर्णाङ्क tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
बाह्य पूर्णाङ्क अङ्कः_backing_ऊर्ध्वम्, bol_needed;

शून्य   *allocate_array(पूर्णाङ्क, size_t);
शून्य   *reallocate_array(शून्य *, पूर्णाङ्क, size_t);

#परिभाषय allocate_integer_array(आकार) \
	allocate_array(आकार, परिमाण(पूर्णाङ्क))

#परिभाषय reallocate_integer_array(array,आकार) \
	reallocate_array((शून्य *) array, आकार, परिमाण(पूर्णाङ्क))

#परिभाषय allocate_int_ptr_array(आकार) \
	allocate_array(आकार, परिमाण(पूर्णाङ्क *))

#परिभाषय allocate_char_ptr_array(आकार) \
	allocate_array(आकार, परिमाण(वर्ण *))

#परिभाषय reallocate_int_ptr_array(array,आकार) \
	reallocate_array((शून्य *) array, आकार, परिमाण(पूर्णाङ्क *))

#परिभाषय reallocate_char_ptr_array(array,आकार) \
	reallocate_array((शून्य *) array, आकार, परिमाण(वर्ण *))

#परिभाषय allocate_character_array(आकार) \
	allocate_array( आकार, परिमाण(वर्ण))

#परिभाषय reallocate_character_array(array,आकार) \
	reallocate_array((शून्य *) array, आकार, परिमाण(वर्ण))

#परिभाषय allocate_Character_array(आकार) \
	allocate_array(आकार, परिमाण(अचिह्नित वर्ण))

#परिभाषय reallocate_Character_array(array,आकार) \
	reallocate_array((शून्य *) array, आकार, परिमाण(अचिह्नित वर्ण))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

बाह्य शून्य ccladd(पूर्णाङ्क, पूर्णाङ्क);	/* add a single character to a ccl */
बाह्य पूर्णाङ्क cclinit(शून्य);	/* make an empty ccl */
बाह्य शून्य cclnegate(पूर्णाङ्क);	/* negate a ccl */
बाह्य पूर्णाङ्क ccl_समुच्चयः_diff (पूर्णाङ्क a, पूर्णाङ्क b); /* set difference of two ccls. */
बाह्य पूर्णाङ्क ccl_समुच्चयः_union (पूर्णाङ्क a, पूर्णाङ्क b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
बाह्य शून्य list_character_समुच्चयः(FILE *, पूर्णाङ्क[]);


/* from file dfa.c */

/* Increase the maximum number of dfas. */
बाह्य शून्य increase_max_dfas(शून्य);

बाह्य size_t ntod(शून्य);	/* convert a ndfa to a dfa */


/* from file ecs.c */

/* Convert character classes to set of equivalence classes. */
बाह्य शून्य ccl2ecl(शून्य);

/* Associate equivalence class numbers with class members. */
बाह्य पूर्णाङ्क cre8ecs(पूर्णाङ्क[], पूर्णाङ्क[], पूर्णाङ्क);

/* Update equivalence classes based on character class transitions. */
बाह्य शून्य mkeccl(अचिह्नित वर्ण[], पूर्णाङ्क, पूर्णाङ्क[], पूर्णाङ्क[], पूर्णाङ्क, पूर्णाङ्क);

/* Create equivalence class for single character. */
बाह्य शून्य mkechar(पूर्णाङ्क, पूर्णाङ्क[], पूर्णाङ्क[]);


/* from file gen.c */

/* Set a conditional amd make it visible in generated code */
बाह्य शून्य visible_define (ध्रुव वर्ण *);

/* And again, with an explicit value part. */
बाह्य शून्य visible_define_str (ध्रुव वर्ण *, ध्रुव वर्ण *);

/* This time the value part is an int */
बाह्य शून्य visible_define_int (ध्रुव वर्ण *, ध्रुव पूर्णाङ्क);

/* generate transition tables */
बाह्य शून्य make_tables(शून्य);

/* Select a type for optimal packing */
संरचना packtype_t *optimize_pack(size_t);

/* from file main.c */

बाह्य शून्य check_options(शून्य);
बाह्य शून्य flexend(पूर्णाङ्क);
बाह्य शून्य usage(शून्य);


/* from file misc.c */

/* Add the given text to the stored actions. */
बाह्य शून्य सङ्कलय_action(ध्रुव वर्ण *new_text);

/* True if a string is all lower case. */
बाह्य पूर्णाङ्क all_अधस्तनम्(वर्ण *);

/* True if a string is all upper case. */
बाह्य पूर्णाङ्क all_ऊर्ध्वस्थम्(वर्ण *);

/* Compare two integers for use by qsort. */
बाह्य पूर्णाङ्क intcmp(ध्रुव शून्य *, ध्रुव शून्य *);

/* Check a character to make sure it's in the expected range. */
बाह्य शून्य check_char(पूर्णाङ्क c);

/* Replace upper-case letter to lower-case. */
बाह्य अचिह्नित वर्ण clower(पूर्णाङ्क);

/* strdup() that fails fatally on allocation failures. */
बाह्य वर्ण *xstrdup(ध्रुव वर्ण *);

/* Compare two characters for use by qsort with '\0' sorting last. */
बाह्य पूर्णाङ्क cclcmp(ध्रुव शून्य *, ध्रुव शून्य *);

/* Finish up a block of data declarations. */
बाह्य शून्य dataend(ध्रुव वर्ण *);

/* Flush generated data statements. */
बाह्य शून्य dataflush(शून्य);

/* Report an error message and terminate. */
बाह्य शून्य flexerror(ध्रुव वर्ण *);

/* Report a fatal error message and terminate. */
बाह्य शून्य flexfatal(ध्रुव वर्ण *);

/* Report a fatal error with a pinpoint, and terminate */
#यदि_परिभाषितम् HAVE_DECL___FUNC__
#परिभाषय flex_die(सन्देशः) \
    कुरु{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                क्रमादेशः_name, __FILE__, (पूर्णाङ्क)__LINE__,\
                __func__,सन्देशः);\
        FLEX_EXIT(1);\
    }यावत्(0)
#अन्यथा /* ! HAVE_DECL___FUNC__ */
#परिभाषय flex_die(सन्देशः) \
    कुरु{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                क्रमादेशः_name, __FILE__, (पूर्णाङ्क)__LINE__,\
                सन्देशः);\
        FLEX_EXIT(1);\
    }यावत्(0)
#यदि_अन्तः /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
बाह्य शून्य lerr(ध्रुव वर्ण *, ...)
#यदि defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#यदि_अन्तः
;

/* Like lerr, but also exit after displaying message. */
बाह्य शून्य lerr_fatal(ध्रुव वर्ण *, ...)
#यदि defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#यदि_अन्तः
;

/* Spit out a "#line" statement. */
बाह्य शून्य पङ्क्तिः_directive_बहिर्गमनम्(FILE *, वर्ण *, पूर्णाङ्क);

/* Mark the current position in the action array as the end of the section 1
 * user defs.
 */
बाह्य शून्य mark_defs1(शून्य);

/* Mark the current position in the action array as the end of the prolog. */
बाह्य शून्य mark_prolog(शून्य);

/* Generate a data statement for a two-dimensional array. */
बाह्य शून्य mk2data(पूर्णाङ्क);

बाह्य शून्य mkdata(पूर्णाङ्क);	/* generate a data statement */

/* Return the integer represented by a string of digits. */
बाह्य पूर्णाङ्क myctoi(ध्रुव वर्ण *);

/* Return character corresponding to escape sequence. */
बाह्य अचिह्नित वर्ण myesc(अचिह्नित वर्ण[]);

/* Output a (possibly-formatted) string to the generated scanner. */
बाह्य शून्य बहिर्गमनम्(ध्रुव वर्ण *);
बाह्य शून्य बहिर्गमनम्_dec(ध्रुव वर्ण *, पूर्णाङ्क);
बाह्य शून्य बहिर्गमनम्_dec2(ध्रुव वर्ण *, पूर्णाङ्क, पूर्णाङ्क);
बाह्य शून्य बहिर्गमनम्_hex(ध्रुव वर्ण *, अचिह्नित पूर्णाङ्क);
बाह्य शून्य बहिर्गमनम्_str(ध्रुव वर्ण *, ध्रुव वर्ण *);
बाह्य शून्य बहिर्गमनम्_str_dec(ध्रुव वर्ण *, ध्रुव वर्ण *, पूर्णाङ्क);
बाह्य शून्य outc(पूर्णाङ्क);
बाह्य शून्य outn(ध्रुव वर्ण *);
बाह्य शून्य बहिर्गमनम्_m4_define(ध्रुव वर्ण* def, ध्रुव वर्ण* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
बाह्य वर्ण *readable_form(पूर्णाङ्क);

/* Output a yy_trans_info structure. */
बाह्य शून्य transition_struct_बहिर्गमनम्(पूर्णाङ्क, पूर्णाङ्क);

/* Only needed when using certain broken versions of bison to build parse.c. */
बाह्य शून्य *yy_flex_xmalloc(पूर्णाङ्क);


/* from file nfa.c */

/* Add an accepting state to a machine. */
बाह्य शून्य सङ्कलय_accept(पूर्णाङ्क, पूर्णाङ्क);

/* Make a given number of copies of a singleton machine. */
बाह्य पूर्णाङ्क copysingl(पूर्णाङ्क, पूर्णाङ्क);

/* Debugging routine to write out an nfa. */
बाह्य शून्य dumpnfa(पूर्णाङ्क);

/* Finish up the processing for a rule. */
बाह्य शून्य finish_नियमः(पूर्णाङ्क, bool, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क);

/* Connect two machines together. */
बाह्य पूर्णाङ्क link_machines(पूर्णाङ्क, पूर्णाङ्क);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
बाह्य शून्य mark_beginning_as_प्रसामान्यम्(पूर्णाङ्क);

/* Make a machine that branches to two machines. */
बाह्य पूर्णाङ्क mkbranch(पूर्णाङ्क, पूर्णाङ्क);

बाह्य पूर्णाङ्क mkclos(पूर्णाङ्क);	/* convert a machine into a closure */
बाह्य पूर्णाङ्क mkopt(पूर्णाङ्क);	/* make a machine optional */

/* Make a machine that matches either one of two machines. */
बाह्य पूर्णाङ्क mkor(पूर्णाङ्क, पूर्णाङ्क);

/* Convert a machine into a positive closure. */
बाह्य पूर्णाङ्क mkposcl(पूर्णाङ्क);

बाह्य पूर्णाङ्क mkrep(पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क);	/* make a replicated machine */

/* Create a state with a transition on a given symbol. */
बाह्य पूर्णाङ्क mkstate(पूर्णाङ्क);

बाह्य शून्य new_नियमः(शून्य);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
बाह्य शून्य build_eof_action(शून्य);

/* Write out a message formatted with one string, pinpointing its location. */
बाह्य शून्य format_pinpoint_सन्देशः(ध्रुव वर्ण *, ध्रुव वर्ण *);

/* Write out a message, pinpointing its location. */
बाह्य शून्य pinpoint_सन्देशः(ध्रुव वर्ण *);

/* Write out a warning, pinpointing it at the given line. */
बाह्य शून्य पङ्क्तिः_warning(ध्रुव वर्ण *, पूर्णाङ्क);

/* Write out a message, pinpointing it at the given line. */
बाह्य शून्य पङ्क्तिः_pinpoint(ध्रुव वर्ण *, पूर्णाङ्क);

/* Report a formatted syntax error. */
बाह्य शून्य format_synerr(ध्रुव वर्ण *, ध्रुव वर्ण *);
बाह्य शून्य synerr(ध्रुव वर्ण *);	/* report a syntax error */
बाह्य शून्य format_warn(ध्रुव वर्ण *, ध्रुव वर्ण *);
बाह्य शून्य lwarn(ध्रुव वर्ण *);	/* report a warning */
बाह्य शून्य yyerror(ध्रुव वर्ण *);	/* report a parse error */
बाह्य पूर्णाङ्क yyparse(शून्य);		/* the YACC parser */

/* Ship a comment to the generated output */
बाह्य शून्य comment(ध्रुव वर्ण *);

/* from file scan.l */

/* The Flex-generated scanner for flex. */
बाह्य पूर्णाङ्क flexscan(शून्य);

/* Open the given file (if NULL, stdin) for scanning. */
बाह्य शून्य समुच्चयः_निवेशः_file(वर्ण *);

/* from file skeletons.c */

/* return the correct file suffix for the selected back end */
ध्रुव वर्ण *suffix (शून्य);

/* Mine a text-valued property out of the skeleton file */
बाह्य ध्रुव वर्ण *skel_property(ध्रुव वर्ण *);

/* Is the default back end selected?*/
बाह्य bool is_default_backend(शून्य);

/* Select a backend by name */
बाह्य शून्य backend_by_name(ध्रुव वर्ण *);

/* Write out one section of the skeleton file. */
बाह्य शून्य skelout(bool);

/* from file sym.c */

/* Save the text of a character class. */
बाह्य शून्य cclinstal(वर्ण[], पूर्णाङ्क);

/* Lookup the number associated with character class. */
बाह्य पूर्णाङ्क ccllookup(वर्ण[]);

बाह्य शून्य ndinstal(ध्रुव वर्ण *, वर्ण[]);	/* install a name definition */
बाह्य वर्ण *ndlookup(ध्रुव वर्ण *);	/* lookup a name definition */

/* Increase maximum number of SC's. */
बाह्य शून्य scextend(शून्य);
बाह्य शून्य scinstal(ध्रुव वर्ण *, bool);	/* make a start condition */

/* Lookup the number associated with a start condition. */
बाह्य पूर्णाङ्क sclookup(ध्रुव वर्ण *);

/* Supply context argument for a function if required */
बाह्य शून्य context_call(वर्ण *);

/* from file tblcmp.c */

/* Build table entries for dfa state. */
बाह्य शून्य bldtbl(पूर्णाङ्क[], पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क);

बाह्य शून्य cmptmps(शून्य);	/* compress template table entries */
बाह्य शून्य expand_nxt_chk(शून्य);	/* increase nxt/chk arrays */

/* Finds a space in the table for a state to be placed. */
बाह्य पूर्णाङ्क find_सारणी_space(पूर्णाङ्क *, पूर्णाङ्क);
बाह्य शून्य inittbl(शून्य);	/* initialize transition tables */

/* Make the default, "jam" table entries. */
बाह्य शून्य mkdeftbl(शून्य);

/* Create table entries for a state (or state fragment) which has
 * only one out-transition.
 */
बाह्य शून्य mk1tbl(पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क);

/* Place a state into full speed transition table. */
बाह्य शून्य place_state(पूर्णाङ्क *, पूर्णाङ्क, पूर्णाङ्क);

/* Save states with only one out-transition to be processed later. */
बाह्य शून्य stack1(पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क);


/* from file yylex.c */

बाह्य पूर्णाङ्क yylex(शून्य);

/* A growable array. See buf.c. */
संरचना Buf {
	शून्य   *elts;		/* elements. */
	पूर्णाङ्क     nelts;		/* number of elements. */
	size_t  elt_आकार;	/* in bytes. */
	पूर्णाङ्क     nmax;		/* max capacity of elements. */
};

बाह्य शून्य buf_init(संरचना Buf * buf, size_t elem_आकार);
बाह्य शून्य buf_destroy(संरचना Buf * buf);
बाह्य संरचना Buf *buf_append(संरचना Buf * buf, ध्रुव शून्य *ptr, पूर्णाङ्क n_elem);
बाह्य संरचना Buf *buf_strappend(संरचना Buf *, ध्रुव वर्ण *str);
बाह्य संरचना Buf *buf_strnappend(संरचना Buf *, ध्रुव वर्ण *str, पूर्णाङ्क nchars);
बाह्य संरचना Buf *buf_prints(संरचना Buf *buf, ध्रुव वर्ण *fmt, ध्रुव वर्ण* s);

बाह्य संरचना Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
बाह्य संरचना Buf शिखरम्_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#परिभाषय बहिर्गमनम्_BEGIN_संहिता() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#परिभाषय बहिर्गमनम्_अन्तः_संहिता()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
बाह्य jmp_buf flex_main_jmp_buf;

#परिभाषय FLEX_EXIT(स्थितिः) longjmp(flex_main_jmp_buf,(स्थितिः)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
बाह्य वर्ण *chomp (वर्ण *str);

/* ctype functions forced to return boolean */
#परिभाषय b_isalnum(c) (अक्षरम्_अङ्कः_वा(c)?true:false)
#परिभाषय b_isalpha(c) (अक्षरम्_वा(c)?true:false)
#परिभाषय b_isascii(c) (isascii(c)?true:false)
#परिभाषय b_isblank(c) (isblank(c)?true:false)
#परिभाषय b_iscntrl(c) (iscntrl(c)?true:false)
#परिभाषय b_isdigit(c) (अङ्कः_वा(c)?true:false)
#परिभाषय b_isgraph(c) (isgraph(c)?true:false)
#परिभाषय b_islower(c) (islower(c)?true:false)
#परिभाषय b_isprint(c) (isprint(c)?true:false)
#परिभाषय b_ispunct(c) (ispunct(c)?true:false)
#परिभाषय b_isspace(c) (रिक्तम्_वा(c)?true:false)
#परिभाषय b_isupper(c) (isupper(c)?true:false)
#परिभाषय b_isxdigit(c) (isxdigit(c)?true:false)

/* return true if char is uppercase or lowercase. */
bool has_case(पूर्णाङ्क c);

/* Change case of character if possible. */
पूर्णाङ्क reverse_case(पूर्णाङ्क c);

/* return false if [c1-c2] is ambiguous for a caseless scanner. */
bool range_covers_case (पूर्णाङ्क c1, पूर्णाङ्क c2);

/*
 *  From "filter.c"
 */

/** A single stdio filter to execute.
 *  The filter may be external, such as "sed", or it
 *  may be internal, as a function call.
 */
संरचना filter {
    पूर्णाङ्क    (*filter_func)(संरचना filter*); /**< internal filter function */
    शून्य * extra;         /**< extra data passed to filter_func */
	पूर्णाङ्क     argc;         /**< arg count */
	ध्रुव वर्ण ** argv;   /**< arg vector, \0-terminated */
    संरचना filter * अग्र; /**< next filter or NULL */
};

/* output filter chain */
बाह्य संरचना filter * output_chain;
बाह्य संरचना filter *filter_create_ext (संरचना filter * chain, ध्रुव वर्ण *cmd, ...);
संरचना filter *filter_create_int(संरचना filter *chain,
				  पूर्णाङ्क (*filter_func) (संरचना filter *),
                  शून्य *extra);
बाह्य bool filter_apply_chain(संरचना filter * chain);
बाह्य पूर्णाङ्क filter_truncate(संरचना filter * chain, पूर्णाङ्क max_len);
बाह्य पूर्णाङ्क filter_tee_शीर्षकम्(संरचना filter *chain);
बाह्य पूर्णाङ्क filter_fix_linedirs(संरचना filter *chain);


/*
 * From "regex.c"
 */

बाह्य regex_t regex_linedir;
bool flex_init_regex(ध्रुव वर्ण *);
शून्य flex_regcomp(regex_t *preg, ध्रुव वर्ण *regex, पूर्णाङ्क cflags);
वर्ण   *regmatch_dup (regmatch_t * m, ध्रुव वर्ण *src);
वर्ण   *regmatch_cpy (regmatch_t * m, वर्ण *dest, ध्रुव वर्ण *src);
पूर्णाङ्क regmatch_len (regmatch_t * m);
पूर्णाङ्क regmatch_strtol (regmatch_t * m, ध्रुव वर्ण *src, वर्ण **endptr, पूर्णाङ्क आधारः);
bool regmatch_रिक्तानि (regmatch_t * m);

/* From "scanflags.h" */
प्रकारनिर्देश अचिह्नित पूर्णाङ्क scanflags_t;
बाह्य scanflags_t* _sf_stk;
बाह्य size_t sf_शिखरम्_ix, _sf_max; /**< stack of scanner flags. */
#परिभाषय _SF_CASE_INS   ((scanflags_t) 0x0001)
#परिभाषय _SF_DOT_ALL    ((scanflags_t) 0x0002)
#परिभाषय _SF_SKIP_WS    ((scanflags_t) 0x0004)
#परिभाषय sf_शिखरम्()           (_sf_stk[sf_शिखरम्_ix])
#परिभाषय sf_case_ins()      (sf_शिखरम्() & _SF_CASE_INS)
#परिभाषय sf_dot_all()       (sf_शिखरम्() & _SF_DOT_ALL)
#परिभाषय sf_skip_ws()       (sf_शिखरम्() & _SF_SKIP_WS)
#परिभाषय sf_समुच्चयः_case_ins(X)      ((X) ? (sf_शिखरम्() |= _SF_CASE_INS) : (sf_शिखरम्() &= ~_SF_CASE_INS))
#परिभाषय sf_समुच्चयः_dot_all(X)       ((X) ? (sf_शिखरम्() |= _SF_DOT_ALL)  : (sf_शिखरम्() &= ~_SF_DOT_ALL))
#परिभाषय sf_समुच्चयः_skip_ws(X)       ((X) ? (sf_शिखरम्() |= _SF_SKIP_WS)  : (sf_शिखरम्() &= ~_SF_SKIP_WS))
बाह्य शून्य sf_init(शून्य);
बाह्य शून्य sf_प्रक्षिप(शून्य);
बाह्य शून्य sf_निष्कासय(शून्य);


#यदि_अन्तः /* not defined FLEXDEF_H */
