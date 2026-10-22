
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

#ifndef FLEXDEF_H
#define FLEXDEF_H 1

#ifndef USE_CONFIG_FOR_BUILD
# ifdef HAVE_CONFIG_H
#ಅನ್ತರ್ಭಾವ <config.h>
# endif
#ಅನ್ಯಥಾ
#ಅನ್ತರ್ಭಾವ <config_for_build.h>
#endif

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <setjmp.h>
#ಅನ್ತರ್ಭಾವ <ctype.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <math.h>

#ifdef HAVE_ASSERT_H
#ಅನ್ತರ್ಭಾವ <assert.h>
#ಅನ್ಯಥಾ
#define ಪ್ರತಿಜ್ಞಾ(Pred)
#endif

#ifdef HAVE_LIMITS_H
#ಅನ್ತರ್ಭಾವ <limits.h>
#endif
/* Required: dup() and dup2() in <unistd.h> */
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ifdef HAVE_NETINET_IN_H
#ಅನ್ತರ್ಭಾವ <netinet/in.h>
#endif
#ifdef HAVE_SYS_PARAMS_H
#ಅನ್ತರ್ಭಾವ <sys/params.h>
#endif
/* Required: wait() in <sys/wait.h> */
#ಅನ್ತರ್ಭಾವ <sys/wait.h>
#ifdef HAVE_STDBOOL_H
#ಅನ್ತರ್ಭಾವ <stdbool.h>
#ನೋಚೇದ್ಯದಿ !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# ಅನ್ಯಥಾ
#  define bool ಪೂರ್ಣಾಙ್ಕ
# endif
# define false 0
# define true 1
#endif
#ಅನ್ತರ್ಭಾವ <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#ಅನ್ತರ್ಭಾವ <regex.h>
/* Required: strcasecmp() in <strings.h> */
#ಅನ್ತರ್ಭಾವ <strings.h>
#ಅನ್ತರ್ಭಾವ "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#ಯದಿ defined(ENABLE_NLS) && ENABLE_NLS
#ifdef HAVE_LOCALE_H
#ಅನ್ತರ್ಭಾವ <locale.h>
#endif /* HAVE_LOCALE_H */
#ಅನ್ತರ್ಭಾವ "gettext.h"
#define _(String) gettext (String)
#ಅನ್ಯಥಾ
#define _(STRING) STRING
#endif /* ENABLE_NLS */

/* Always be prepared to generate an 8-bit scanner. */
#define CSIZE 256

/* Size of input alphabet - should be size of ASCII set. */
#ifndef DEFAULT_CSIZE
#define DEFAULT_CSIZE 128
#endif

/* Maximum line length we'll have to deal with. */
#define MAXLINE 2048

#ifndef MIN
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#endif
#ifndef ABS
#define ABS(x) ((x) < 0 ? -(x) : (x))
#endif

/* Whether an integer is a power of two */
#define is_power_of_2(n) ((n) > 0 && ((n) & ((n) - 1)) == 0)

/* Special chk[] values marking the slots taking by end-of-buffer and action
 * numbers.
 */
#define EOB_POSITION -1
#define ACTION_POSITION -2

/* Number of data items per line for -f output. */
#define NUMDATAITEMS 10

/* Number of lines of data in -f output before inserting a blank line for
 * readability.
 */
#define NUMDATALINES 10

/* transition_struct_out() definitions. */
#define TRANS_STRUCT_PRINT_LENGTH 14

/* Returns true if an nfa state has an epsilon out-transition slot
 * that can be used.  This definition is currently not used.
 */
#define FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans2[state] == NO_TRANSITION && \
	 finalst[state] != state)

/* Returns true if an nfa state has an epsilon out-transition character
 * and both slots are free
 */
#define SUPER_FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans1[state] == NO_TRANSITION) \

/* Maximum number of NFA states that can comprise a DFA state.  It's real
 * big because if there's a lot of rules, the initial state will have a
 * huge epsilon closure.
 */
#define INITIAL_MAX_DFA_SIZE 750
#define MAX_DFA_SIZE_INCREMENT 750


/* A note on the following masks.  They are used to mark accepting numbers
 * as being special.  As such, they implicitly limit the number of accepting
 * numbers (i.e., rules) because if there are too many rules the rule numbers
 * will overload the mask bits.  Fortunately, this limit is \large/ (0x2000 ==
 * 8192) so unlikely to actually cause any problems.  A check is made in
 * new_rule() to ensure that this limit is not reached.
 */

/* Mask to mark a trailing context accepting number. */
#define YY_TRAILING_MASK 0x2000

/* Mask to mark the accepting number of the "head" of a trailing context
 * rule.
 */
#define YY_TRAILING_HEAD_MASK 0x4000

/* Maximum number of rules, as outlined in the above note. */
#define MAX_RULE (YY_TRAILING_MASK - 1)


/* NIL must be 0.  If not, its special meaning when making equivalence classes
 * (it marks the representative of a given e.c.) will be unidentifiable.
 */
#define NIL 0

#define JAM -1			/* to mark a missing DFA transition */
#define NO_TRANSITION NIL
#define UNIQUE -1		/* marks a symbol as an e.c. representative */
#define INFINITE_REPEAT -1		/* for x{5,} constructions */

#define INITIAL_MAX_CCLS 100	/* max number of unique character classes */
#define MAX_CCLS_INCREMENT 100

/* Size of table holding members of character classes. */
#define INITIAL_MAX_CCL_TBL_SIZE 500
#define MAX_CCL_TBL_SIZE_INCREMENT 250

#define INITIAL_MAX_RULES 100	/* default maximum number of rules */
#define MAX_RULES_INCREMENT 100

#define INITIAL_MNS 2000	/* default maximum number of nfa states */
#define MNS_INCREMENT 1000	/* amount to bump above by if it's not enough */

#define INITIAL_MAX_DFAS 1000	/* default maximum number of dfa states */
#define MAX_DFAS_INCREMENT 1000

#define JAMSTATE -32766		/* marks a reference to the state that always jams */

/* Maximum number of NFA states. */
#define MAXIMUM_MNS 31999
#define MAXIMUM_MNS_LONG 1999999999

/* Enough so that if it's subtracted from an NFA state number, the result
 * is guaranteed to be negative.
 */
#define MARKER_DIFFERENCE (maximum_mns+2)

/* Maximum number of nxt/chk pairs for non-templates. */
#define INITIAL_MAX_XPAIRS 2000
#define MAX_XPAIRS_INCREMENT 2000

/* Maximum number of nxt/chk pairs needed for templates. */
#define INITIAL_MAX_TEMPLATE_XPAIRS 2500
#define MAX_TEMPLATE_XPAIRS_INCREMENT 2500

#define SYM_EPSILON (CSIZE + 1)	/* to mark transitions on the symbol epsilon */

#define INITIAL_MAX_SCS 40	/* maximum number of start conditions */
#define MAX_SCS_INCREMENT 40	/* amount to bump by if it's not enough */

#define ONE_ರಾಶಿ_SIZE 500	/* stack of states with only one out-transition */
#define SAME_TRANS -1		/* transition is the same as "default" entry for state */

/* The following percentages are used to tune table compression:

 * The percentage the number of out-transitions a state must be of the
 * number of equivalence classes in order to be considered for table
 * compaction by using protos.
 */
#define PROTO_SIZE_PERCENTAGE 15

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * that the state's transition table is first compared with a potential
 * template of the most common out-transition instead of with the first
 * proto in the proto queue.
 */
#define CHECK_COM_PERCENTAGE 50

/* The percentage the number of differences between a state's transition
 * table and the proto it was first compared with must be of the total
 * number of out-transitions of the state in order to keep the first
 * proto as a good match and not search any further.
 */
#define FIRST_MATCH_DIFF_PERCENTAGE 10

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to use the proto as an acceptable close match.
 */
#define ACCEPTABLE_DIFF_PERCENTAGE 50

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * to consider making a template from the state.
 */
#define TEMPLATE_SAME_PERCENTAGE 60

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to create a new proto from the state.
 */
#define NEW_PROTO_DIFF_PERCENTAGE 20

/* The percentage the total number of out-transitions of a state must be
 * of the number of equivalence classes in order to consider trying to
 * fit the transition table into "holes" inside the nxt/chk table.
 */
#define INTERIOR_FIT_PERCENTAGE 15

/* Size of region set aside to cache the complete transition table of
 * protos on the proto queue to enable quick comparisons.
 */
#define PROT_SAVE_SIZE 2000

#define MSP 50			/* maximum number of saved protos (protos on the proto queue) */

/* Maximum number of out-transitions a state can have that we'll rummage
 * around through the interior of the internal fast table looking for a
 * spot for it.
 */
#define MAX_XTIONS_FULL_INTERIOR_FIT 4

/* Maximum number of rules which will be reported as being associated
 * with a DFA state.
 */
#define MAX_ASSOC_RULES 100

/* Number that, if used to subscript an array, has a good chance of producing
 * an error; should be small enough to fit into a short.
 */
#define BAD_SUBSCRIPT -32767

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ trit_t {
	trit_unspecified = -1,
	trit_false = 0,
	trit_true = 1,
} trit;

/* Control variables.  These are in a struct to avoid having to replicate definitions
 * twice for each option, instead a single struct can be declared and externed.
 * If it's in this structure, it has a corresponding m4 symbol.
 */
ಸಂರಚನಾ ctrl_bundle_t {
	bool always_interactive;// always use character-by-character input
	FILE *backing_up_file;	// file to summarize backing-up states to 
	bool bison_bridge_lval;	// (--bison-bridge), bison pure calling convention. 
	bool bison_bridge_lloc;	// (--bison-locations), bison yylloc.
	size_t bufsize;		// input buffer size
	bool C_plus_plus;	// (-+ flag) generate a C++ scanner class 
	ಪೂರ್ಣಾಙ್ಕ csize;		// size of character set for the scanner 
				// 128 for 7-bit chars and 256 for 8-bit 
	bool ddebug;		// (-d) make a "debug" scanner 
	trit do_main;		// generate main part to make lexer standalone.
	bool do_stdinit;	// whether to initialize yyin/yyout to stdin/stdout
	bool do_yylineno;	// if true, generate code to maintain yylineno 
	bool do_yywrap;		// do yywrap() processing on EOF. 
				// If false, EOF treated as "no more files" 
	bool fullspd;		// (-F flag) use Jacobson method of table representation 
	bool fulltbl;		// (-Cf flag) don't compress the DFA state table 
 	bool gen_ಸಾಲು_dirs;	// (no -L flag) generate #line directives 
	trit interactive;	// (-I) generate an interactive scanner
	bool never_interactive;	// always use buffered input, don't check for tty.
	bool lex_compat;	// (-l), maximize compatibility with AT&T lex 
	bool long_align;	// (-Ca flag), favor long-word alignment for speed 
	bool no_yyinput;	// suppress use of yyinput()
	bool no_unistd;		// suppress inclusion of unistd.h
	bool posix_compat;	// (-X) maximize compatibility with POSIX lex 
	ವರ್ಣ *prefix;		// prefix for externally visible names, default "yy" 
	trit reject_really_used;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool ರಾಶಿ_used;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	ವರ್ಣ *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	ವರ್ಣ *yydecl;		// user-specified prototype for yylex.
	ಪೂರ್ಣಾಙ್ಕ yylmax;		// Maximum buffer length if %array
	trit yymore_really_used;// Force geberation of support code for yymore
	bool yytext_is_array;	// if true (i.e., %array directive), then declare
				// yytext as array instead of a character pointer.
				// Nice and inefficient.
	bool noyyread;		// User supplied a yyread function, don't generate default
	ವರ್ಣ *userinit;		// Code fragment to be inserted before scanning
	ವರ್ಣ *preaction;	// Code fragment to be inserted before each action
	ವರ್ಣ *postaction;	// Code fragment to be inserted after each action
	ವರ್ಣ *emit;		// Specify target language to emit.
	ವರ್ಣ *yyterminate;	// Set a non-default termination hook.
	bool no_yypanic;	// if true, no not generate default yypanic function
 	// flags corresponding to the huge mass of --no-yy options
	bool no_yy_ತಳ್ಳು_state;
	bool no_yy_ತೆಗೆ_state;
	bool no_yy_ತುದಿ_state;
	bool no_yyunput;
	bool no_yy_scan_buffer;
	bool no_yy_scan_bytes;
	bool no_yy_scan_string;
	bool no_yyget_extra;
	bool no_yyset_extra;
	bool no_yyget_leng;
	bool no_yyget_text;
	bool no_yyget_lineno;
	bool no_yyset_lineno;
	bool no_yyget_column;
	bool no_yyset_column;
	bool no_yyget_in;
	bool no_yyset_in;
	bool no_yyget_out;
	bool no_yyset_out;
	bool no_yyget_lval;
	bool no_yyset_lval;
	bool no_yyget_lloc;
	bool no_yyset_lloc;
	bool no_flex_alloc;
	bool no_flex_realloc;
	bool no_flex_free;
	bool no_get_debug;
	bool no_set_debug;
	// Properties read from the skeleton
	ಧ್ರುವ ವರ್ಣ *backend_name;	// What the back end tells you its name is
	ಧ್ರುವ ವರ್ಣ *traceline_re;	// Regular expression for recognizing tracelines */
	ಧ್ರುವ ವರ್ಣ *traceline_template;	// templare for emitting trace lines */
	bool have_state_entry_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
ಸಂರಚನಾ env_bundle_t {
	bool backing_up_report;	// (-b flag), generate "lex.backup" file 
				// listing backing-up states
	bool did_outfilename;	// whether outfilename was explicitly set
	ವರ್ಣ *headerfilename;	// name of the .h file to generate
	bool nowarn;		// (-w) do not generate warnings 
	ಪೂರ್ಣಾಙ್ಕ performance_hint;	// if > 0 (i.e., -p flag), generate a report 
				// relating to scanner performance; 
				// if > 1 (-p -p), report 
 				// on minor performance problems, too.
	ವರ್ಣ *outfilename;	// output file name
	bool printstats;	// (-v) dump statistics
	ವರ್ಣ *skelname;		// name of skeleton for code generation
	FILE *skelfile;		// the skeleton file'd descriptor
	bool trace;		// (-T) env.trace processing 
	bool trace_hex; 	// use hex in trace/debug outputs not octal
	bool use_stdout;	// the -t flag
};

/* Name and byte-width information on a type for code-generation purposes. */
ಸಂರಚನಾ packtype_t {
	ವರ್ಣ *name;
	size_t width;
};

ಬಾಹ್ಯ ಸಂರಚನಾ ctrl_bundle_t ctrl;
ಬಾಹ್ಯ ಸಂರಚನಾ env_bundle_t env;

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

ಬಾಹ್ಯ bool syntaxerror, eofseen;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ yymore_used, reject, real_reject, continued_action, in_rule;

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

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ datapos, dataline, linenum;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ skel_ind;
ಬಾಹ್ಯ ವರ್ಣ *infilename;
ಬಾಹ್ಯ ವರ್ಣ *extra_type;
ಬಾಹ್ಯ ವರ್ಣ **ಒಳಹರಿವು_files;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_ಒಳಹರಿವು_files;
ಬಾಹ್ಯ ವರ್ಣ *program_name;

ಬಾಹ್ಯ ವರ್ಣ *action_array;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ action_size;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ defs1_offset, prolog_offset, action_offset, action_index;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ onestate[ONE_ರಾಶಿ_SIZE], onesym[ONE_ರಾಶಿ_SIZE];
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ onenext[ONE_ರಾಶಿ_SIZE], onedef[ONE_ರಾಶಿ_SIZE], onesp;


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

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ maximum_mns, current_mns, current_max_rules;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_rules, ಅಂಕೆ_eof_rules, default_rule, lastnfa;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ *accptnum, *assoc_rule, *state_type;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ *rule_type, *rule_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
ಬಾಹ್ಯ ವರ್ಣ *rule_useful, *rule_has_nl, *ccl_has_nl;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ nlch;
ಬಾಹ್ಯ size_t footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#define STATE_NORMAL 0x1
#define STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ current_state_type;

/* Different types of rules. */
#define RULE_NORMAL 0
#define RULE_VARIABLE 1

/* True if the input rules include a rule with both variable-length head
 * and trailing context, false otherwise.
 */
ಬಾಹ್ಯ bool variable_trailing_context_rules;


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

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];


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
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs;

/* Meta-equivalence classes are indexed starting at 1, so it's possible
 * that they will require positions from 1 .. CSIZE, i.e., CSIZE + 1
 * slots total (since the arrays are 0-based).  nextecm[] and ecgroup[]
 * don't require the extra position since they're indexed from 1 .. CSIZE - 1.
 */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ tecfwd[CSIZE + 1], tecbck[CSIZE + 1];


/* Variables for start conditions:
 * lastsc - last start condition created
 * current_max_scs - current limit on number of start conditions
 * scset - set of rules active in start condition
 * scbol - set of rules active only at the beginning of line in a s.c.
 * scxclu - true if start condition is exclusive
 * sceof - true if start condition has EOF rule
 * scname - start condition name
 */

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
ಬಾಹ್ಯ ವರ್ಣ *scxclu, *sceof;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ current_max_scs;
ಬಾಹ್ಯ ಧ್ರುವ ವರ್ಣ **scname;


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

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ current_max_dfa_size, current_max_xpairs;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ current_max_template_xpairs, current_max_dfas;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ lastdfa, *nxt, *chk, *tnxt;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
ಬಾಹ್ಯ ಸಙ್ಘ dfaacc_union {
	ಪೂರ್ಣಾಙ್ಕ    *dfaacc_set;
	ಪೂರ್ಣಾಙ್ಕ     dfaacc_state;
}      *dfaacc;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ *accsiz, *dhash, numas;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ numsnpairs, jambase, jamstate;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ end_of_buffer_state;

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

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ lastccl, *cclmap, *ccllen, *cclng, cclreuse;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ current_maxccls, current_max_ccl_tbl_size;
ಬಾಹ್ಯ unsigned ವರ್ಣ *ccltbl;


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

ಬಾಹ್ಯ ವರ್ಣ nmstr[MAXLINE];
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ sectnum, nummt, hshcol, dfaeql, numeps, eps2, ಅಂಕೆ_reallocs, nmval;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_backing_up, bol_needed;

ಶೂನ್ಯ   *allocate_array(ಪೂರ್ಣಾಙ್ಕ, size_t);
ಶೂನ್ಯ   *reallocate_array(ಶೂನ್ಯ *, ಪೂರ್ಣಾಙ್ಕ, size_t);

#define allocate_integer_array(size) \
	allocate_array(size, ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ))

#define reallocate_integer_array(array,size) \
	reallocate_array((ಶೂನ್ಯ *) array, size, ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ))

#define allocate_int_ptr_array(size) \
	allocate_array(size, ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ *))

#define allocate_char_ptr_array(size) \
	allocate_array(size, ಪರಿಮಾಣ(ವರ್ಣ *))

#define reallocate_int_ptr_array(array,size) \
	reallocate_array((ಶೂನ್ಯ *) array, size, ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ *))

#define reallocate_char_ptr_array(array,size) \
	reallocate_array((ಶೂನ್ಯ *) array, size, ಪರಿಮಾಣ(ವರ್ಣ *))

#define allocate_character_array(size) \
	allocate_array( size, ಪರಿಮಾಣ(ವರ್ಣ))

#define reallocate_character_array(array,size) \
	reallocate_array((ಶೂನ್ಯ *) array, size, ಪರಿಮಾಣ(ವರ್ಣ))

#define allocate_Character_array(size) \
	allocate_array(size, ಪರಿಮಾಣ(unsigned ವರ್ಣ))

#define reallocate_Character_array(array,size) \
	reallocate_array((ಶೂನ್ಯ *) array, size, ಪರಿಮಾಣ(unsigned ವರ್ಣ))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

ಬಾಹ್ಯ ಶೂನ್ಯ ccladd(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);	/* add a single character to a ccl */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ cclinit(ಶೂನ್ಯ);	/* make an empty ccl */
ಬಾಹ್ಯ ಶೂನ್ಯ cclnegate(ಪೂರ್ಣಾಙ್ಕ);	/* negate a ccl */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ccl_set_diff (ಪೂರ್ಣಾಙ್ಕ a, ಪೂರ್ಣಾಙ್ಕ b); /* set difference of two ccls. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ccl_set_union (ಪೂರ್ಣಾಙ್ಕ a, ಪೂರ್ಣಾಙ್ಕ b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
ಬಾಹ್ಯ ಶೂನ್ಯ list_character_set(FILE *, ಪೂರ್ಣಾಙ್ಕ[]);


/* from file dfa.c */

/* Increase the maximum number of dfas. */
ಬಾಹ್ಯ ಶೂನ್ಯ increase_max_dfas(ಶೂನ್ಯ);

ಬಾಹ್ಯ size_t ntod(ಶೂನ್ಯ);	/* convert a ndfa to a dfa */


/* from file ecs.c */

/* Convert character classes to set of equivalence classes. */
ಬಾಹ್ಯ ಶೂನ್ಯ ccl2ecl(ಶೂನ್ಯ);

/* Associate equivalence class numbers with class members. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ cre8ecs(ಪೂರ್ಣಾಙ್ಕ[], ಪೂರ್ಣಾಙ್ಕ[], ಪೂರ್ಣಾಙ್ಕ);

/* Update equivalence classes based on character class transitions. */
ಬಾಹ್ಯ ಶೂನ್ಯ mkeccl(unsigned ವರ್ಣ[], ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ[], ಪೂರ್ಣಾಙ್ಕ[], ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

/* Create equivalence class for single character. */
ಬಾಹ್ಯ ಶೂನ್ಯ mkechar(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ[], ಪೂರ್ಣಾಙ್ಕ[]);


/* from file gen.c */

/* Set a conditional amd make it visible in generated code */
ಬಾಹ್ಯ ಶೂನ್ಯ visible_define (ಧ್ರುವ ವರ್ಣ *);

/* And again, with an explicit value part. */
ಬಾಹ್ಯ ಶೂನ್ಯ visible_define_str (ಧ್ರುವ ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *);

/* This time the value part is an int */
ಬಾಹ್ಯ ಶೂನ್ಯ visible_define_int (ಧ್ರುವ ವರ್ಣ *, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ);

/* generate transition tables */
ಬಾಹ್ಯ ಶೂನ್ಯ make_tables(ಶೂನ್ಯ);

/* Select a type for optimal packing */
ಸಂರಚನಾ packtype_t *optimize_pack(size_t);

/* from file main.c */

ಬಾಹ್ಯ ಶೂನ್ಯ check_options(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ flexend(ಪೂರ್ಣಾಙ್ಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ usage(ಶೂನ್ಯ);


/* from file misc.c */

/* Add the given text to the stored actions. */
ಬಾಹ್ಯ ಶೂನ್ಯ add_action(ಧ್ರುವ ವರ್ಣ *new_text);

/* True if a string is all lower case. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ all_lower(ವರ್ಣ *);

/* True if a string is all upper case. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ all_upper(ವರ್ಣ *);

/* Compare two integers for use by qsort. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ intcmp(ಧ್ರುವ ಶೂನ್ಯ *, ಧ್ರುವ ಶೂನ್ಯ *);

/* Check a character to make sure it's in the expected range. */
ಬಾಹ್ಯ ಶೂನ್ಯ check_char(ಪೂರ್ಣಾಙ್ಕ c);

/* Replace upper-case letter to lower-case. */
ಬಾಹ್ಯ unsigned ವರ್ಣ clower(ಪೂರ್ಣಾಙ್ಕ);

/* strdup() that fails fatally on allocation failures. */
ಬಾಹ್ಯ ವರ್ಣ *xstrdup(ಧ್ರುವ ವರ್ಣ *);

/* Compare two characters for use by qsort with '\0' sorting last. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ cclcmp(ಧ್ರುವ ಶೂನ್ಯ *, ಧ್ರುವ ಶೂನ್ಯ *);

/* Finish up a block of data declarations. */
ಬಾಹ್ಯ ಶೂನ್ಯ dataend(ಧ್ರುವ ವರ್ಣ *);

/* Flush generated data statements. */
ಬಾಹ್ಯ ಶೂನ್ಯ dataflush(ಶೂನ್ಯ);

/* Report an error message and terminate. */
ಬಾಹ್ಯ ಶೂನ್ಯ flexerror(ಧ್ರುವ ವರ್ಣ *);

/* Report a fatal error message and terminate. */
ಬಾಹ್ಯ ಶೂನ್ಯ flexfatal(ಧ್ರುವ ವರ್ಣ *);

/* Report a fatal error with a pinpoint, and terminate */
#ifdef HAVE_DECL___FUNC__
#define flex_die(ಸಂದೇಶ) \
    ಕುರು{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                program_name, __FILE__, (ಪೂರ್ಣಾಙ್ಕ)__LINE__,\
                __func__,ಸಂದೇಶ);\
        FLEX_EXIT(1);\
    }ಯಾವತ್(0)
#ಅನ್ಯಥಾ /* ! HAVE_DECL___FUNC__ */
#define flex_die(ಸಂದೇಶ) \
    ಕುರು{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                program_name, __FILE__, (ಪೂರ್ಣಾಙ್ಕ)__LINE__,\
                ಸಂದೇಶ);\
        FLEX_EXIT(1);\
    }ಯಾವತ್(0)
#endif /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
ಬಾಹ್ಯ ಶೂನ್ಯ lerr(ಧ್ರುವ ವರ್ಣ *, ...)
#ಯದಿ defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#endif
;

/* Like lerr, but also exit after displaying message. */
ಬಾಹ್ಯ ಶೂನ್ಯ lerr_fatal(ಧ್ರುವ ವರ್ಣ *, ...)
#ಯದಿ defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#endif
;

/* Spit out a "#line" statement. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಸಾಲು_directive_out(FILE *, ವರ್ಣ *, ಪೂರ್ಣಾಙ್ಕ);

/* Mark the current position in the action array as the end of the section 1
 * user defs.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ mark_defs1(ಶೂನ್ಯ);

/* Mark the current position in the action array as the end of the prolog. */
ಬಾಹ್ಯ ಶೂನ್ಯ mark_prolog(ಶೂನ್ಯ);

/* Generate a data statement for a two-dimensional array. */
ಬಾಹ್ಯ ಶೂನ್ಯ mk2data(ಪೂರ್ಣಾಙ್ಕ);

ಬಾಹ್ಯ ಶೂನ್ಯ mkdata(ಪೂರ್ಣಾಙ್ಕ);	/* generate a data statement */

/* Return the integer represented by a string of digits. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ myctoi(ಧ್ರುವ ವರ್ಣ *);

/* Return character corresponding to escape sequence. */
ಬಾಹ್ಯ unsigned ವರ್ಣ myesc(unsigned ವರ್ಣ[]);

/* Output a (possibly-formatted) string to the generated scanner. */
ಬಾಹ್ಯ ಶೂನ್ಯ out(ಧ್ರುವ ವರ್ಣ *);
ಬಾಹ್ಯ ಶೂನ್ಯ out_dec(ಧ್ರುವ ವರ್ಣ *, ಪೂರ್ಣಾಙ್ಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ out_dec2(ಧ್ರುವ ವರ್ಣ *, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ out_hex(ಧ್ರುವ ವರ್ಣ *, unsigned ಪೂರ್ಣಾಙ್ಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ out_str(ಧ್ರುವ ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *);
ಬಾಹ್ಯ ಶೂನ್ಯ out_str_dec(ಧ್ರುವ ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *, ಪೂರ್ಣಾಙ್ಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ outc(ಪೂರ್ಣಾಙ್ಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ outn(ಧ್ರುವ ವರ್ಣ *);
ಬಾಹ್ಯ ಶೂನ್ಯ out_m4_define(ಧ್ರುವ ವರ್ಣ* def, ಧ್ರುವ ವರ್ಣ* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
ಬಾಹ್ಯ ವರ್ಣ *readable_form(ಪೂರ್ಣಾಙ್ಕ);

/* Output a yy_trans_info structure. */
ಬಾಹ್ಯ ಶೂನ್ಯ transition_struct_out(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

/* Only needed when using certain broken versions of bison to build parse.c. */
ಬಾಹ್ಯ ಶೂನ್ಯ *yy_flex_xmalloc(ಪೂರ್ಣಾಙ್ಕ);


/* from file nfa.c */

/* Add an accepting state to a machine. */
ಬಾಹ್ಯ ಶೂನ್ಯ add_accept(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

/* Make a given number of copies of a singleton machine. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ copysingl(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

/* Debugging routine to write out an nfa. */
ಬಾಹ್ಯ ಶೂನ್ಯ dumpnfa(ಪೂರ್ಣಾಙ್ಕ);

/* Finish up the processing for a rule. */
ಬಾಹ್ಯ ಶೂನ್ಯ finish_rule(ಪೂರ್ಣಾಙ್ಕ, bool, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

/* Connect two machines together. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ link_machines(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ mark_beginning_as_normal(ಪೂರ್ಣಾಙ್ಕ);

/* Make a machine that branches to two machines. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ mkbranch(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ mkclos(ಪೂರ್ಣಾಙ್ಕ);	/* convert a machine into a closure */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ mkopt(ಪೂರ್ಣಾಙ್ಕ);	/* make a machine optional */

/* Make a machine that matches either one of two machines. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ mkor(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

/* Convert a machine into a positive closure. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ mkposcl(ಪೂರ್ಣಾಙ್ಕ);

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ mkrep(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);	/* make a replicated machine */

/* Create a state with a transition on a given symbol. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ mkstate(ಪೂರ್ಣಾಙ್ಕ);

ಬಾಹ್ಯ ಶೂನ್ಯ new_rule(ಶೂನ್ಯ);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
ಬಾಹ್ಯ ಶೂನ್ಯ build_eof_action(ಶೂನ್ಯ);

/* Write out a message formatted with one string, pinpointing its location. */
ಬಾಹ್ಯ ಶೂನ್ಯ format_pinpoint_message(ಧ್ರುವ ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *);

/* Write out a message, pinpointing its location. */
ಬಾಹ್ಯ ಶೂನ್ಯ pinpoint_message(ಧ್ರುವ ವರ್ಣ *);

/* Write out a warning, pinpointing it at the given line. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಸಾಲು_warning(ಧ್ರುವ ವರ್ಣ *, ಪೂರ್ಣಾಙ್ಕ);

/* Write out a message, pinpointing it at the given line. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಸಾಲು_pinpoint(ಧ್ರುವ ವರ್ಣ *, ಪೂರ್ಣಾಙ್ಕ);

/* Report a formatted syntax error. */
ಬಾಹ್ಯ ಶೂನ್ಯ format_synerr(ಧ್ರುವ ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *);
ಬಾಹ್ಯ ಶೂನ್ಯ synerr(ಧ್ರುವ ವರ್ಣ *);	/* report a syntax error */
ಬಾಹ್ಯ ಶೂನ್ಯ format_warn(ಧ್ರುವ ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *);
ಬಾಹ್ಯ ಶೂನ್ಯ lwarn(ಧ್ರುವ ವರ್ಣ *);	/* report a warning */
ಬಾಹ್ಯ ಶೂನ್ಯ yyerror(ಧ್ರುವ ವರ್ಣ *);	/* report a parse error */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ yyparse(ಶೂನ್ಯ);		/* the YACC parser */

/* Ship a comment to the generated output */
ಬಾಹ್ಯ ಶೂನ್ಯ comment(ಧ್ರುವ ವರ್ಣ *);

/* from file scan.l */

/* The Flex-generated scanner for flex. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ flexscan(ಶೂನ್ಯ);

/* Open the given file (if NULL, stdin) for scanning. */
ಬಾಹ್ಯ ಶೂನ್ಯ set_ಒಳಹರಿವು_file(ವರ್ಣ *);

/* from file skeletons.c */

/* return the correct file suffix for the selected back end */
ಧ್ರುವ ವರ್ಣ *suffix (ಶೂನ್ಯ);

/* Mine a text-valued property out of the skeleton file */
ಬಾಹ್ಯ ಧ್ರುವ ವರ್ಣ *skel_property(ಧ್ರುವ ವರ್ಣ *);

/* Is the default back end selected?*/
ಬಾಹ್ಯ bool is_default_backend(ಶೂನ್ಯ);

/* Select a backend by name */
ಬಾಹ್ಯ ಶೂನ್ಯ backend_by_name(ಧ್ರುವ ವರ್ಣ *);

/* Write out one section of the skeleton file. */
ಬಾಹ್ಯ ಶೂನ್ಯ skelout(bool);

/* from file sym.c */

/* Save the text of a character class. */
ಬಾಹ್ಯ ಶೂನ್ಯ cclinstal(ವರ್ಣ[], ಪೂರ್ಣಾಙ್ಕ);

/* Lookup the number associated with character class. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ccllookup(ವರ್ಣ[]);

ಬಾಹ್ಯ ಶೂನ್ಯ ndinstal(ಧ್ರುವ ವರ್ಣ *, ವರ್ಣ[]);	/* install a name definition */
ಬಾಹ್ಯ ವರ್ಣ *ndlookup(ಧ್ರುವ ವರ್ಣ *);	/* lookup a name definition */

/* Increase maximum number of SC's. */
ಬಾಹ್ಯ ಶೂನ್ಯ scextend(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ scinstal(ಧ್ರುವ ವರ್ಣ *, bool);	/* make a start condition */

/* Lookup the number associated with a start condition. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ sclookup(ಧ್ರುವ ವರ್ಣ *);

/* Supply context argument for a function if required */
ಬಾಹ್ಯ ಶೂನ್ಯ context_call(ವರ್ಣ *);

/* from file tblcmp.c */

/* Build table entries for dfa state. */
ಬಾಹ್ಯ ಶೂನ್ಯ bldtbl(ಪೂರ್ಣಾಙ್ಕ[], ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

ಬಾಹ್ಯ ಶೂನ್ಯ cmptmps(ಶೂನ್ಯ);	/* compress template table entries */
ಬಾಹ್ಯ ಶೂನ್ಯ expand_nxt_chk(ಶೂನ್ಯ);	/* increase nxt/chk arrays */

/* Finds a space in the table for a state to be placed. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ find_table_space(ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ inittbl(ಶೂನ್ಯ);	/* initialize transition tables */

/* Make the default, "jam" table entries. */
ಬಾಹ್ಯ ಶೂನ್ಯ mkdeftbl(ಶೂನ್ಯ);

/* Create table entries for a state (or state fragment) which has
 * only one out-transition.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ mk1tbl(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

/* Place a state into full speed transition table. */
ಬಾಹ್ಯ ಶೂನ್ಯ place_state(ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);

/* Save states with only one out-transition to be processed later. */
ಬಾಹ್ಯ ಶೂನ್ಯ stack1(ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);


/* from file yylex.c */

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ yylex(ಶೂನ್ಯ);

/* A growable array. See buf.c. */
ಸಂರಚನಾ Buf {
	ಶೂನ್ಯ   *elts;		/* elements. */
	ಪೂರ್ಣಾಙ್ಕ     nelts;		/* number of elements. */
	size_t  elt_size;	/* in bytes. */
	ಪೂರ್ಣಾಙ್ಕ     nmax;		/* max capacity of elements. */
};

ಬಾಹ್ಯ ಶೂನ್ಯ buf_init(ಸಂರಚನಾ Buf * buf, size_t elem_size);
ಬಾಹ್ಯ ಶೂನ್ಯ buf_destroy(ಸಂರಚನಾ Buf * buf);
ಬಾಹ್ಯ ಸಂರಚನಾ Buf *buf_append(ಸಂರಚನಾ Buf * buf, ಧ್ರುವ ಶೂನ್ಯ *ptr, ಪೂರ್ಣಾಙ್ಕ n_elem);
ಬಾಹ್ಯ ಸಂರಚನಾ Buf *buf_strappend(ಸಂರಚನಾ Buf *, ಧ್ರುವ ವರ್ಣ *str);
ಬಾಹ್ಯ ಸಂರಚನಾ Buf *buf_strnappend(ಸಂರಚನಾ Buf *, ಧ್ರುವ ವರ್ಣ *str, ಪೂರ್ಣಾಙ್ಕ nchars);
ಬಾಹ್ಯ ಸಂರಚನಾ Buf *buf_prints(ಸಂರಚನಾ Buf *buf, ಧ್ರುವ ವರ್ಣ *fmt, ಧ್ರುವ ವರ್ಣ* s);

ಬಾಹ್ಯ ಸಂರಚನಾ Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
ಬಾಹ್ಯ ಸಂರಚನಾ Buf ತುದಿ_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#define OUT_BEGIN_CODE() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#define OUT_END_CODE()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
ಬಾಹ್ಯ jmp_buf flex_main_jmp_buf;

#define FLEX_EXIT(status) longjmp(flex_main_jmp_buf,(status)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
ಬಾಹ್ಯ ವರ್ಣ *chomp (ವರ್ಣ *str);

/* ctype functions forced to return boolean */
#define b_isalnum(c) (isalnum(c)?true:false)
#define b_isalpha(c) (isalpha(c)?true:false)
#define b_isascii(c) (isascii(c)?true:false)
#define b_isblank(c) (isblank(c)?true:false)
#define b_iscntrl(c) (iscntrl(c)?true:false)
#define b_isdigit(c) (isdigit(c)?true:false)
#define b_isgraph(c) (isgraph(c)?true:false)
#define b_islower(c) (islower(c)?true:false)
#define b_isprint(c) (isprint(c)?true:false)
#define b_ispunct(c) (ispunct(c)?true:false)
#define b_isspace(c) (isspace(c)?true:false)
#define b_isupper(c) (isupper(c)?true:false)
#define b_isxdigit(c) (isxdigit(c)?true:false)

/* return true if char is uppercase or lowercase. */
bool has_case(ಪೂರ್ಣಾಙ್ಕ c);

/* Change case of character if possible. */
ಪೂರ್ಣಾಙ್ಕ reverse_case(ಪೂರ್ಣಾಙ್ಕ c);

/* return false if [c1-c2] is ambiguous for a caseless scanner. */
bool range_covers_case (ಪೂರ್ಣಾಙ್ಕ c1, ಪೂರ್ಣಾಙ್ಕ c2);

/*
 *  From "filter.c"
 */

/** A single stdio filter to execute.
 *  The filter may be external, such as "sed", or it
 *  may be internal, as a function call.
 */
ಸಂರಚನಾ filter {
    ಪೂರ್ಣಾಙ್ಕ    (*filter_func)(ಸಂರಚನಾ filter*); /**< internal filter function */
    ಶೂನ್ಯ * extra;         /**< extra data passed to filter_func */
	ಪೂರ್ಣಾಙ್ಕ     argc;         /**< arg count */
	ಧ್ರುವ ವರ್ಣ ** argv;   /**< arg vector, \0-terminated */
    ಸಂರಚನಾ filter * next; /**< next filter or NULL */
};

/* output filter chain */
ಬಾಹ್ಯ ಸಂರಚನಾ filter * output_chain;
ಬಾಹ್ಯ ಸಂರಚನಾ filter *filter_create_ext (ಸಂರಚನಾ filter * chain, ಧ್ರುವ ವರ್ಣ *cmd, ...);
ಸಂರಚನಾ filter *filter_create_int(ಸಂರಚನಾ filter *chain,
				  ಪೂರ್ಣಾಙ್ಕ (*filter_func) (ಸಂರಚನಾ filter *),
                  ಶೂನ್ಯ *extra);
ಬಾಹ್ಯ bool filter_apply_chain(ಸಂರಚನಾ filter * chain);
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ filter_truncate(ಸಂರಚನಾ filter * chain, ಪೂರ್ಣಾಙ್ಕ max_len);
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ filter_tee_header(ಸಂರಚನಾ filter *chain);
ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ filter_fix_linedirs(ಸಂರಚನಾ filter *chain);


/*
 * From "regex.c"
 */

ಬಾಹ್ಯ regex_t regex_linedir;
bool flex_init_regex(ಧ್ರುವ ವರ್ಣ *);
ಶೂನ್ಯ flex_regcomp(regex_t *preg, ಧ್ರುವ ವರ್ಣ *regex, ಪೂರ್ಣಾಙ್ಕ cflags);
ವರ್ಣ   *regmatch_dup (regmatch_t * m, ಧ್ರುವ ವರ್ಣ *src);
ವರ್ಣ   *regmatch_cpy (regmatch_t * m, ವರ್ಣ *dest, ಧ್ರುವ ವರ್ಣ *src);
ಪೂರ್ಣಾಙ್ಕ regmatch_len (regmatch_t * m);
ಪೂರ್ಣಾಙ್ಕ regmatch_strtol (regmatch_t * m, ಧ್ರುವ ವರ್ಣ *src, ವರ್ಣ **endptr, ಪೂರ್ಣಾಙ್ಕ base);
bool regmatch_empty (regmatch_t * m);

/* From "scanflags.h" */
ಪ್ರಕಾರನಿರ್ದೇಶ unsigned ಪೂರ್ಣಾಙ್ಕ scanflags_t;
ಬಾಹ್ಯ scanflags_t* _sf_stk;
ಬಾಹ್ಯ size_t sf_ತುದಿ_ix, _sf_max; /**< stack of scanner flags. */
#define _SF_CASE_INS   ((scanflags_t) 0x0001)
#define _SF_DOT_ALL    ((scanflags_t) 0x0002)
#define _SF_SKIP_WS    ((scanflags_t) 0x0004)
#define sf_ತುದಿ()           (_sf_stk[sf_ತುದಿ_ix])
#define sf_case_ins()      (sf_ತುದಿ() & _SF_CASE_INS)
#define sf_dot_all()       (sf_ತುದಿ() & _SF_DOT_ALL)
#define sf_skip_ws()       (sf_ತುದಿ() & _SF_SKIP_WS)
#define sf_set_case_ins(X)      ((X) ? (sf_ತುದಿ() |= _SF_CASE_INS) : (sf_ತುದಿ() &= ~_SF_CASE_INS))
#define sf_set_dot_all(X)       ((X) ? (sf_ತುದಿ() |= _SF_DOT_ALL)  : (sf_ತುದಿ() &= ~_SF_DOT_ALL))
#define sf_set_skip_ws(X)       ((X) ? (sf_ತುದಿ() |= _SF_SKIP_WS)  : (sf_ತುದಿ() &= ~_SF_SKIP_WS))
ಬಾಹ್ಯ ಶೂನ್ಯ sf_init(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ sf_ತಳ್ಳು(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ sf_ತೆಗೆ(ಶೂನ್ಯ);


#endif /* not defined FLEXDEF_H */
