
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
#ଅନ୍ତର୍ଭାଵ <config.h>
# endif
#ଅନ୍ୟଥା
#ଅନ୍ତର୍ଭାଵ <config_for_build.h>
#endif

#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <stdarg.h>
#ଅନ୍ତର୍ଭାଵ <setjmp.h>
#ଅନ୍ତର୍ଭାଵ <ctype.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <math.h>

#ifdef HAVE_ASSERT_H
#ଅନ୍ତର୍ଭାଵ <assert.h>
#ଅନ୍ୟଥା
#define ପ୍ରତିଜ୍ଞା(Pred)
#endif

#ifdef HAVE_LIMITS_H
#ଅନ୍ତର୍ଭାଵ <limits.h>
#endif
/* Required: dup() and dup2() in <unistd.h> */
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#ifdef HAVE_NETINET_IN_H
#ଅନ୍ତର୍ଭାଵ <netinet/in.h>
#endif
#ifdef HAVE_SYS_PARAMS_H
#ଅନ୍ତର୍ଭାଵ <sys/params.h>
#endif
/* Required: wait() in <sys/wait.h> */
#ଅନ୍ତର୍ଭାଵ <sys/wait.h>
#ifdef HAVE_STDBOOL_H
#ଅନ୍ତର୍ଭାଵ <stdbool.h>
#ନଚେତଯଦି !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# ଅନ୍ୟଥା
#  define bool ପୂର୍ଣ୍ଣସଂଖ୍ୟା
# endif
# define false 0
# define true 1
#endif
#ଅନ୍ତର୍ଭାଵ <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#ଅନ୍ତର୍ଭାଵ <regex.h>
/* Required: strcasecmp() in <strings.h> */
#ଅନ୍ତର୍ଭାଵ <strings.h>
#ଅନ୍ତର୍ଭାଵ "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#ଯଦି defined(ENABLE_NLS) && ENABLE_NLS
#ifdef HAVE_LOCALE_H
#ଅନ୍ତର୍ଭାଵ <locale.h>
#endif /* HAVE_LOCALE_H */
#ଅନ୍ତର୍ଭାଵ "gettext.h"
#define _(String) gettext (String)
#ଅନ୍ୟଥା
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

#define ONE_ଗଦା_SIZE 500	/* stack of states with only one out-transition */
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା trit_t {
	trit_unspecified = -1,
	trit_false = 0,
	trit_true = 1,
} trit;

/* Control variables.  These are in a struct to avoid having to replicate definitions
 * twice for each option, instead a single struct can be declared and externed.
 * If it's in this structure, it has a corresponding m4 symbol.
 */
ସଂରଚନା ctrl_bundle_t {
	bool always_interactive;// always use character-by-character input
	FILE *backing_up_file;	// file to summarize backing-up states to 
	bool bison_bridge_lval;	// (--bison-bridge), bison pure calling convention. 
	bool bison_bridge_lloc;	// (--bison-locations), bison yylloc.
	size_t bufsize;		// input buffer size
	bool C_plus_plus;	// (-+ flag) generate a C++ scanner class 
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା csize;		// size of character set for the scanner 
				// 128 for 7-bit chars and 256 for 8-bit 
	bool ddebug;		// (-d) make a "debug" scanner 
	trit do_main;		// generate main part to make lexer standalone.
	bool do_stdinit;	// whether to initialize yyin/yyout to stdin/stdout
	bool do_yylineno;	// if true, generate code to maintain yylineno 
	bool do_yywrap;		// do yywrap() processing on EOF. 
				// If false, EOF treated as "no more files" 
	bool fullspd;		// (-F flag) use Jacobson method of table representation 
	bool fulltbl;		// (-Cf flag) don't compress the DFA state table 
 	bool gen_ଧାଡ଼ି_dirs;	// (no -L flag) generate #line directives 
	trit interactive;	// (-I) generate an interactive scanner
	bool never_interactive;	// always use buffered input, don't check for tty.
	bool lex_compat;	// (-l), maximize compatibility with AT&T lex 
	bool long_align;	// (-Ca flag), favor long-word alignment for speed 
	bool no_yyinput;	// suppress use of yyinput()
	bool no_unistd;		// suppress inclusion of unistd.h
	bool posix_compat;	// (-X) maximize compatibility with POSIX lex 
	ଅକ୍ଷର *prefix;		// prefix for externally visible names, default "yy" 
	trit reject_really_used;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool ଗଦା_used;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	ଅକ୍ଷର *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	ଅକ୍ଷର *yydecl;		// user-specified prototype for yylex.
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା yylmax;		// Maximum buffer length if %array
	trit yymore_really_used;// Force geberation of support code for yymore
	bool yytext_is_array;	// if true (i.e., %array directive), then declare
				// yytext as array instead of a character pointer.
				// Nice and inefficient.
	bool noyyread;		// User supplied a yyread function, don't generate default
	ଅକ୍ଷର *userinit;		// Code fragment to be inserted before scanning
	ଅକ୍ଷର *preaction;	// Code fragment to be inserted before each action
	ଅକ୍ଷର *postaction;	// Code fragment to be inserted after each action
	ଅକ୍ଷର *emit;		// Specify target language to emit.
	ଅକ୍ଷର *yyterminate;	// Set a non-default termination hook.
	bool no_yypanic;	// if true, no not generate default yypanic function
 	// flags corresponding to the huge mass of --no-yy options
	bool no_yy_ଠେଲ_state;
	bool no_yy_କାଢ଼_state;
	bool no_yy_ଶୀର୍ଷ_state;
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
	ଅଚଳ ଅକ୍ଷର *backend_name;	// What the back end tells you its name is
	ଅଚଳ ଅକ୍ଷର *traceline_re;	// Regular expression for recognizing tracelines */
	ଅଚଳ ଅକ୍ଷର *traceline_template;	// templare for emitting trace lines */
	bool have_state_entry_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
ସଂରଚନା env_bundle_t {
	bool backing_up_report;	// (-b flag), generate "lex.backup" file 
				// listing backing-up states
	bool did_outfilename;	// whether outfilename was explicitly set
	ଅକ୍ଷର *headerfilename;	// name of the .h file to generate
	bool nowarn;		// (-w) do not generate warnings 
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା performance_hint;	// if > 0 (i.e., -p flag), generate a report 
				// relating to scanner performance; 
				// if > 1 (-p -p), report 
 				// on minor performance problems, too.
	ଅକ୍ଷର *outfilename;	// output file name
	bool printstats;	// (-v) dump statistics
	ଅକ୍ଷର *skelname;		// name of skeleton for code generation
	FILE *skelfile;		// the skeleton file'd descriptor
	bool trace;		// (-T) env.trace processing 
	bool trace_hex; 	// use hex in trace/debug outputs not octal
	bool use_stdout;	// the -t flag
};

/* Name and byte-width information on a type for code-generation purposes. */
ସଂରଚନା packtype_t {
	ଅକ୍ଷର *name;
	size_t width;
};

ବାହ୍ୟ ସଂରଚନା ctrl_bundle_t ctrl;
ବାହ୍ୟ ସଂରଚନା env_bundle_t env;

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

ବାହ୍ୟ bool syntaxerror, eofseen;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା yymore_used, reject, real_reject, continued_action, in_rule;

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

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା datapos, dataline, linenum;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା skel_ind;
ବାହ୍ୟ ଅକ୍ଷର *infilename;
ବାହ୍ୟ ଅକ୍ଷର *extra_type;
ବାହ୍ୟ ଅକ୍ଷର **ନିବେଶ_files;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_ନିବେଶ_files;
ବାହ୍ୟ ଅକ୍ଷର *program_name;

ବାହ୍ୟ ଅକ୍ଷର *action_array;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା action_size;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା defs1_offset, prolog_offset, action_offset, action_index;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା onestate[ONE_ଗଦା_SIZE], onesym[ONE_ଗଦା_SIZE];
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା onenext[ONE_ଗଦା_SIZE], onedef[ONE_ଗଦା_SIZE], onesp;


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

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା maximum_mns, current_mns, current_max_rules;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_rules, ଅଙ୍କ_eof_rules, default_rule, lastnfa;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *accptnum, *assoc_rule, *state_type;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *rule_type, *rule_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
ବାହ୍ୟ ଅକ୍ଷର *rule_useful, *rule_has_nl, *ccl_has_nl;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nlch;
ବାହ୍ୟ size_t footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#define STATE_NORMAL 0x1
#define STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା current_state_type;

/* Different types of rules. */
#define RULE_NORMAL 0
#define RULE_VARIABLE 1

/* True if the input rules include a rule with both variable-length head
 * and trailing context, false otherwise.
 */
ବାହ୍ୟ bool variable_trailing_context_rules;


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

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];


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
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs;

/* Meta-equivalence classes are indexed starting at 1, so it's possible
 * that they will require positions from 1 .. CSIZE, i.e., CSIZE + 1
 * slots total (since the arrays are 0-based).  nextecm[] and ecgroup[]
 * don't require the extra position since they're indexed from 1 .. CSIZE - 1.
 */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା tecfwd[CSIZE + 1], tecbck[CSIZE + 1];


/* Variables for start conditions:
 * lastsc - last start condition created
 * current_max_scs - current limit on number of start conditions
 * scset - set of rules active in start condition
 * scbol - set of rules active only at the beginning of line in a s.c.
 * scxclu - true if start condition is exclusive
 * sceof - true if start condition has EOF rule
 * scname - start condition name
 */

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
ବାହ୍ୟ ଅକ୍ଷର *scxclu, *sceof;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା current_max_scs;
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର **scname;


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

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା current_max_dfa_size, current_max_xpairs;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା current_max_template_xpairs, current_max_dfas;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା lastdfa, *nxt, *chk, *tnxt;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
ବାହ୍ୟ ସଂଘ dfaacc_union {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା    *dfaacc_set;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     dfaacc_state;
}      *dfaacc;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *accsiz, *dhash, numas;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା numsnpairs, jambase, jamstate;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା end_of_buffer_state;

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

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା lastccl, *cclmap, *ccllen, *cclng, cclreuse;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା current_maxccls, current_max_ccl_tbl_size;
ବାହ୍ୟ unsigned ଅକ୍ଷର *ccltbl;


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

ବାହ୍ୟ ଅକ୍ଷର nmstr[MAXLINE];
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା sectnum, nummt, hshcol, dfaeql, numeps, eps2, ଅଙ୍କ_reallocs, nmval;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_backing_up, bol_needed;

ଶୂନ୍ୟ   *allocate_array(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, size_t);
ଶୂନ୍ୟ   *reallocate_array(ଶୂନ୍ୟ *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, size_t);

#define allocate_integer_array(size) \
	allocate_array(size, ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା))

#define reallocate_integer_array(array,size) \
	reallocate_array((ଶୂନ୍ୟ *) array, size, ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା))

#define allocate_int_ptr_array(size) \
	allocate_array(size, ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *))

#define allocate_char_ptr_array(size) \
	allocate_array(size, ଆକାର(ଅକ୍ଷର *))

#define reallocate_int_ptr_array(array,size) \
	reallocate_array((ଶୂନ୍ୟ *) array, size, ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *))

#define reallocate_char_ptr_array(array,size) \
	reallocate_array((ଶୂନ୍ୟ *) array, size, ଆକାର(ଅକ୍ଷର *))

#define allocate_character_array(size) \
	allocate_array( size, ଆକାର(ଅକ୍ଷର))

#define reallocate_character_array(array,size) \
	reallocate_array((ଶୂନ୍ୟ *) array, size, ଆକାର(ଅକ୍ଷର))

#define allocate_Character_array(size) \
	allocate_array(size, ଆକାର(unsigned ଅକ୍ଷର))

#define reallocate_Character_array(array,size) \
	reallocate_array((ଶୂନ୍ୟ *) array, size, ଆକାର(unsigned ଅକ୍ଷର))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

ବାହ୍ୟ ଶୂନ୍ୟ ccladd(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);	/* add a single character to a ccl */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା cclinit(ଶୂନ୍ୟ);	/* make an empty ccl */
ବାହ୍ୟ ଶୂନ୍ୟ cclnegate(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);	/* negate a ccl */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ccl_set_diff (ପୂର୍ଣ୍ଣସଂଖ୍ୟା a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା b); /* set difference of two ccls. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ccl_set_union (ପୂର୍ଣ୍ଣସଂଖ୍ୟା a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
ବାହ୍ୟ ଶୂନ୍ୟ list_character_set(FILE *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା[]);


/* from file dfa.c */

/* Increase the maximum number of dfas. */
ବାହ୍ୟ ଶୂନ୍ୟ increase_max_dfas(ଶୂନ୍ୟ);

ବାହ୍ୟ size_t ntod(ଶୂନ୍ୟ);	/* convert a ndfa to a dfa */


/* from file ecs.c */

/* Convert character classes to set of equivalence classes. */
ବାହ୍ୟ ଶୂନ୍ୟ ccl2ecl(ଶୂନ୍ୟ);

/* Associate equivalence class numbers with class members. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା cre8ecs(ପୂର୍ଣ୍ଣସଂଖ୍ୟା[], ପୂର୍ଣ୍ଣସଂଖ୍ୟା[], ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Update equivalence classes based on character class transitions. */
ବାହ୍ୟ ଶୂନ୍ୟ mkeccl(unsigned ଅକ୍ଷର[], ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା[], ପୂର୍ଣ୍ଣସଂଖ୍ୟା[], ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Create equivalence class for single character. */
ବାହ୍ୟ ଶୂନ୍ୟ mkechar(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା[], ପୂର୍ଣ୍ଣସଂଖ୍ୟା[]);


/* from file gen.c */

/* Set a conditional amd make it visible in generated code */
ବାହ୍ୟ ଶୂନ୍ୟ visible_define (ଅଚଳ ଅକ୍ଷର *);

/* And again, with an explicit value part. */
ବାହ୍ୟ ଶୂନ୍ୟ visible_define_str (ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *);

/* This time the value part is an int */
ବାହ୍ୟ ଶୂନ୍ୟ visible_define_int (ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* generate transition tables */
ବାହ୍ୟ ଶୂନ୍ୟ make_tables(ଶୂନ୍ୟ);

/* Select a type for optimal packing */
ସଂରଚନା packtype_t *optimize_pack(size_t);

/* from file main.c */

ବାହ୍ୟ ଶୂନ୍ୟ check_options(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ flexend(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ଶୂନ୍ୟ usage(ଶୂନ୍ୟ);


/* from file misc.c */

/* Add the given text to the stored actions. */
ବାହ୍ୟ ଶୂନ୍ୟ add_action(ଅଚଳ ଅକ୍ଷର *new_text);

/* True if a string is all lower case. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା all_lower(ଅକ୍ଷର *);

/* True if a string is all upper case. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା all_upper(ଅକ୍ଷର *);

/* Compare two integers for use by qsort. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା intcmp(ଅଚଳ ଶୂନ୍ୟ *, ଅଚଳ ଶୂନ୍ୟ *);

/* Check a character to make sure it's in the expected range. */
ବାହ୍ୟ ଶୂନ୍ୟ check_char(ପୂର୍ଣ୍ଣସଂଖ୍ୟା c);

/* Replace upper-case letter to lower-case. */
ବାହ୍ୟ unsigned ଅକ୍ଷର clower(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* strdup() that fails fatally on allocation failures. */
ବାହ୍ୟ ଅକ୍ଷର *xstrdup(ଅଚଳ ଅକ୍ଷର *);

/* Compare two characters for use by qsort with '\0' sorting last. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା cclcmp(ଅଚଳ ଶୂନ୍ୟ *, ଅଚଳ ଶୂନ୍ୟ *);

/* Finish up a block of data declarations. */
ବାହ୍ୟ ଶୂନ୍ୟ dataend(ଅଚଳ ଅକ୍ଷର *);

/* Flush generated data statements. */
ବାହ୍ୟ ଶୂନ୍ୟ dataflush(ଶୂନ୍ୟ);

/* Report an error message and terminate. */
ବାହ୍ୟ ଶୂନ୍ୟ flexerror(ଅଚଳ ଅକ୍ଷର *);

/* Report a fatal error message and terminate. */
ବାହ୍ୟ ଶୂନ୍ୟ flexfatal(ଅଚଳ ଅକ୍ଷର *);

/* Report a fatal error with a pinpoint, and terminate */
#ifdef HAVE_DECL___FUNC__
#define flex_die(ସନ୍ଦେଶ) \
    କର{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                program_name, __FILE__, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)__LINE__,\
                __func__,ସନ୍ଦେଶ);\
        FLEX_EXIT(1);\
    }ଯେତେବେଳେ(0)
#ଅନ୍ୟଥା /* ! HAVE_DECL___FUNC__ */
#define flex_die(ସନ୍ଦେଶ) \
    କର{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                program_name, __FILE__, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)__LINE__,\
                ସନ୍ଦେଶ);\
        FLEX_EXIT(1);\
    }ଯେତେବେଳେ(0)
#endif /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
ବାହ୍ୟ ଶୂନ୍ୟ lerr(ଅଚଳ ଅକ୍ଷର *, ...)
#ଯଦି defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#endif
;

/* Like lerr, but also exit after displaying message. */
ବାହ୍ୟ ଶୂନ୍ୟ lerr_fatal(ଅଚଳ ଅକ୍ଷର *, ...)
#ଯଦି defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#endif
;

/* Spit out a "#line" statement. */
ବାହ୍ୟ ଶୂନ୍ୟ ଧାଡ଼ି_directive_out(FILE *, ଅକ୍ଷର *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Mark the current position in the action array as the end of the section 1
 * user defs.
 */
ବାହ୍ୟ ଶୂନ୍ୟ mark_defs1(ଶୂନ୍ୟ);

/* Mark the current position in the action array as the end of the prolog. */
ବାହ୍ୟ ଶୂନ୍ୟ mark_prolog(ଶୂନ୍ୟ);

/* Generate a data statement for a two-dimensional array. */
ବାହ୍ୟ ଶୂନ୍ୟ mk2data(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

ବାହ୍ୟ ଶୂନ୍ୟ mkdata(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);	/* generate a data statement */

/* Return the integer represented by a string of digits. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା myctoi(ଅଚଳ ଅକ୍ଷର *);

/* Return character corresponding to escape sequence. */
ବାହ୍ୟ unsigned ଅକ୍ଷର myesc(unsigned ଅକ୍ଷର[]);

/* Output a (possibly-formatted) string to the generated scanner. */
ବାହ୍ୟ ଶୂନ୍ୟ out(ଅଚଳ ଅକ୍ଷର *);
ବାହ୍ୟ ଶୂନ୍ୟ out_dec(ଅଚଳ ଅକ୍ଷର *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ଶୂନ୍ୟ out_dec2(ଅଚଳ ଅକ୍ଷର *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ଶୂନ୍ୟ out_hex(ଅଚଳ ଅକ୍ଷର *, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ଶୂନ୍ୟ out_str(ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *);
ବାହ୍ୟ ଶୂନ୍ୟ out_str_dec(ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ଶୂନ୍ୟ outc(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ଶୂନ୍ୟ outn(ଅଚଳ ଅକ୍ଷର *);
ବାହ୍ୟ ଶୂନ୍ୟ out_m4_define(ଅଚଳ ଅକ୍ଷର* def, ଅଚଳ ଅକ୍ଷର* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
ବାହ୍ୟ ଅକ୍ଷର *readable_form(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Output a yy_trans_info structure. */
ବାହ୍ୟ ଶୂନ୍ୟ transition_struct_out(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Only needed when using certain broken versions of bison to build parse.c. */
ବାହ୍ୟ ଶୂନ୍ୟ *yy_flex_xmalloc(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);


/* from file nfa.c */

/* Add an accepting state to a machine. */
ବାହ୍ୟ ଶୂନ୍ୟ add_accept(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Make a given number of copies of a singleton machine. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା copysingl(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Debugging routine to write out an nfa. */
ବାହ୍ୟ ଶୂନ୍ୟ dumpnfa(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Finish up the processing for a rule. */
ବାହ୍ୟ ଶୂନ୍ୟ finish_rule(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, bool, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Connect two machines together. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା link_machines(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
ବାହ୍ୟ ଶୂନ୍ୟ mark_beginning_as_normal(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Make a machine that branches to two machines. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା mkbranch(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା mkclos(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);	/* convert a machine into a closure */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା mkopt(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);	/* make a machine optional */

/* Make a machine that matches either one of two machines. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା mkor(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Convert a machine into a positive closure. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା mkposcl(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା mkrep(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);	/* make a replicated machine */

/* Create a state with a transition on a given symbol. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା mkstate(ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

ବାହ୍ୟ ଶୂନ୍ୟ new_rule(ଶୂନ୍ୟ);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
ବାହ୍ୟ ଶୂନ୍ୟ build_eof_action(ଶୂନ୍ୟ);

/* Write out a message formatted with one string, pinpointing its location. */
ବାହ୍ୟ ଶୂନ୍ୟ format_pinpoint_message(ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *);

/* Write out a message, pinpointing its location. */
ବାହ୍ୟ ଶୂନ୍ୟ pinpoint_message(ଅଚଳ ଅକ୍ଷର *);

/* Write out a warning, pinpointing it at the given line. */
ବାହ୍ୟ ଶୂନ୍ୟ ଧାଡ଼ି_warning(ଅଚଳ ଅକ୍ଷର *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Write out a message, pinpointing it at the given line. */
ବାହ୍ୟ ଶୂନ୍ୟ ଧାଡ଼ି_pinpoint(ଅଚଳ ଅକ୍ଷର *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Report a formatted syntax error. */
ବାହ୍ୟ ଶୂନ୍ୟ format_synerr(ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *);
ବାହ୍ୟ ଶୂନ୍ୟ synerr(ଅଚଳ ଅକ୍ଷର *);	/* report a syntax error */
ବାହ୍ୟ ଶୂନ୍ୟ format_warn(ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *);
ବାହ୍ୟ ଶୂନ୍ୟ lwarn(ଅଚଳ ଅକ୍ଷର *);	/* report a warning */
ବାହ୍ୟ ଶୂନ୍ୟ yyerror(ଅଚଳ ଅକ୍ଷର *);	/* report a parse error */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା yyparse(ଶୂନ୍ୟ);		/* the YACC parser */

/* Ship a comment to the generated output */
ବାହ୍ୟ ଶୂନ୍ୟ comment(ଅଚଳ ଅକ୍ଷର *);

/* from file scan.l */

/* The Flex-generated scanner for flex. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା flexscan(ଶୂନ୍ୟ);

/* Open the given file (if NULL, stdin) for scanning. */
ବାହ୍ୟ ଶୂନ୍ୟ set_ନିବେଶ_file(ଅକ୍ଷର *);

/* from file skeletons.c */

/* return the correct file suffix for the selected back end */
ଅଚଳ ଅକ୍ଷର *suffix (ଶୂନ୍ୟ);

/* Mine a text-valued property out of the skeleton file */
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *skel_property(ଅଚଳ ଅକ୍ଷର *);

/* Is the default back end selected?*/
ବାହ୍ୟ bool is_default_backend(ଶୂନ୍ୟ);

/* Select a backend by name */
ବାହ୍ୟ ଶୂନ୍ୟ backend_by_name(ଅଚଳ ଅକ୍ଷର *);

/* Write out one section of the skeleton file. */
ବାହ୍ୟ ଶୂନ୍ୟ skelout(bool);

/* from file sym.c */

/* Save the text of a character class. */
ବାହ୍ୟ ଶୂନ୍ୟ cclinstal(ଅକ୍ଷର[], ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Lookup the number associated with character class. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ccllookup(ଅକ୍ଷର[]);

ବାହ୍ୟ ଶୂନ୍ୟ ndinstal(ଅଚଳ ଅକ୍ଷର *, ଅକ୍ଷର[]);	/* install a name definition */
ବାହ୍ୟ ଅକ୍ଷର *ndlookup(ଅଚଳ ଅକ୍ଷର *);	/* lookup a name definition */

/* Increase maximum number of SC's. */
ବାହ୍ୟ ଶୂନ୍ୟ scextend(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ scinstal(ଅଚଳ ଅକ୍ଷର *, bool);	/* make a start condition */

/* Lookup the number associated with a start condition. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା sclookup(ଅଚଳ ଅକ୍ଷର *);

/* Supply context argument for a function if required */
ବାହ୍ୟ ଶୂନ୍ୟ context_call(ଅକ୍ଷର *);

/* from file tblcmp.c */

/* Build table entries for dfa state. */
ବାହ୍ୟ ଶୂନ୍ୟ bldtbl(ପୂର୍ଣ୍ଣସଂଖ୍ୟା[], ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

ବାହ୍ୟ ଶୂନ୍ୟ cmptmps(ଶୂନ୍ୟ);	/* compress template table entries */
ବାହ୍ୟ ଶୂନ୍ୟ expand_nxt_chk(ଶୂନ୍ୟ);	/* increase nxt/chk arrays */

/* Finds a space in the table for a state to be placed. */
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା find_table_space(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ବାହ୍ୟ ଶୂନ୍ୟ inittbl(ଶୂନ୍ୟ);	/* initialize transition tables */

/* Make the default, "jam" table entries. */
ବାହ୍ୟ ଶୂନ୍ୟ mkdeftbl(ଶୂନ୍ୟ);

/* Create table entries for a state (or state fragment) which has
 * only one out-transition.
 */
ବାହ୍ୟ ଶୂନ୍ୟ mk1tbl(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Place a state into full speed transition table. */
ବାହ୍ୟ ଶୂନ୍ୟ place_state(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);

/* Save states with only one out-transition to be processed later. */
ବାହ୍ୟ ଶୂନ୍ୟ stack1(ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);


/* from file yylex.c */

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା yylex(ଶୂନ୍ୟ);

/* A growable array. See buf.c. */
ସଂରଚନା Buf {
	ଶୂନ୍ୟ   *elts;		/* elements. */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     nelts;		/* number of elements. */
	size_t  elt_size;	/* in bytes. */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     nmax;		/* max capacity of elements. */
};

ବାହ୍ୟ ଶୂନ୍ୟ buf_init(ସଂରଚନା Buf * buf, size_t elem_size);
ବାହ୍ୟ ଶୂନ୍ୟ buf_destroy(ସଂରଚନା Buf * buf);
ବାହ୍ୟ ସଂରଚନା Buf *buf_append(ସଂରଚନା Buf * buf, ଅଚଳ ଶୂନ୍ୟ *ptr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା n_elem);
ବାହ୍ୟ ସଂରଚନା Buf *buf_strappend(ସଂରଚନା Buf *, ଅଚଳ ଅକ୍ଷର *str);
ବାହ୍ୟ ସଂରଚନା Buf *buf_strnappend(ସଂରଚନା Buf *, ଅଚଳ ଅକ୍ଷର *str, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nchars);
ବାହ୍ୟ ସଂରଚନା Buf *buf_prints(ସଂରଚନା Buf *buf, ଅଚଳ ଅକ୍ଷର *fmt, ଅଚଳ ଅକ୍ଷର* s);

ବାହ୍ୟ ସଂରଚନା Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
ବାହ୍ୟ ସଂରଚନା Buf ଶୀର୍ଷ_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#define OUT_BEGIN_CODE() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#define OUT_END_CODE()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
ବାହ୍ୟ jmp_buf flex_main_jmp_buf;

#define FLEX_EXIT(status) longjmp(flex_main_jmp_buf,(status)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
ବାହ୍ୟ ଅକ୍ଷର *chomp (ଅକ୍ଷର *str);

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
bool has_case(ପୂର୍ଣ୍ଣସଂଖ୍ୟା c);

/* Change case of character if possible. */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା reverse_case(ପୂର୍ଣ୍ଣସଂଖ୍ୟା c);

/* return false if [c1-c2] is ambiguous for a caseless scanner. */
bool range_covers_case (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c2);

/*
 *  From "filter.c"
 */

/** A single stdio filter to execute.
 *  The filter may be external, such as "sed", or it
 *  may be internal, as a function call.
 */
ସଂରଚନା filter {
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା    (*filter_func)(ସଂରଚନା filter*); /**< internal filter function */
    ଶୂନ୍ୟ * extra;         /**< extra data passed to filter_func */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     argc;         /**< arg count */
	ଅଚଳ ଅକ୍ଷର ** argv;   /**< arg vector, \0-terminated */
    ସଂରଚନା filter * next; /**< next filter or NULL */
};

/* output filter chain */
ବାହ୍ୟ ସଂରଚନା filter * output_chain;
ବାହ୍ୟ ସଂରଚନା filter *filter_create_ext (ସଂରଚନା filter * chain, ଅଚଳ ଅକ୍ଷର *cmd, ...);
ସଂରଚନା filter *filter_create_int(ସଂରଚନା filter *chain,
				  ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*filter_func) (ସଂରଚନା filter *),
                  ଶୂନ୍ୟ *extra);
ବାହ୍ୟ bool filter_apply_chain(ସଂରଚନା filter * chain);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା filter_truncate(ସଂରଚନା filter * chain, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_len);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା filter_tee_header(ସଂରଚନା filter *chain);
ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା filter_fix_linedirs(ସଂରଚନା filter *chain);


/*
 * From "regex.c"
 */

ବାହ୍ୟ regex_t regex_linedir;
bool flex_init_regex(ଅଚଳ ଅକ୍ଷର *);
ଶୂନ୍ୟ flex_regcomp(regex_t *preg, ଅଚଳ ଅକ୍ଷର *regex, ପୂର୍ଣ୍ଣସଂଖ୍ୟା cflags);
ଅକ୍ଷର   *regmatch_dup (regmatch_t * m, ଅଚଳ ଅକ୍ଷର *src);
ଅକ୍ଷର   *regmatch_cpy (regmatch_t * m, ଅକ୍ଷର *dest, ଅଚଳ ଅକ୍ଷର *src);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା regmatch_len (regmatch_t * m);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା regmatch_strtol (regmatch_t * m, ଅଚଳ ଅକ୍ଷର *src, ଅକ୍ଷର **endptr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା base);
bool regmatch_empty (regmatch_t * m);

/* From "scanflags.h" */
ପ୍ରକାରବ୍ୟାଖ୍ୟା unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା scanflags_t;
ବାହ୍ୟ scanflags_t* _sf_stk;
ବାହ୍ୟ size_t sf_ଶୀର୍ଷ_ix, _sf_max; /**< stack of scanner flags. */
#define _SF_CASE_INS   ((scanflags_t) 0x0001)
#define _SF_DOT_ALL    ((scanflags_t) 0x0002)
#define _SF_SKIP_WS    ((scanflags_t) 0x0004)
#define sf_ଶୀର୍ଷ()           (_sf_stk[sf_ଶୀର୍ଷ_ix])
#define sf_case_ins()      (sf_ଶୀର୍ଷ() & _SF_CASE_INS)
#define sf_dot_all()       (sf_ଶୀର୍ଷ() & _SF_DOT_ALL)
#define sf_skip_ws()       (sf_ଶୀର୍ଷ() & _SF_SKIP_WS)
#define sf_set_case_ins(X)      ((X) ? (sf_ଶୀର୍ଷ() |= _SF_CASE_INS) : (sf_ଶୀର୍ଷ() &= ~_SF_CASE_INS))
#define sf_set_dot_all(X)       ((X) ? (sf_ଶୀର୍ଷ() |= _SF_DOT_ALL)  : (sf_ଶୀର୍ଷ() &= ~_SF_DOT_ALL))
#define sf_set_skip_ws(X)       ((X) ? (sf_ଶୀର୍ଷ() |= _SF_SKIP_WS)  : (sf_ଶୀର୍ଷ() &= ~_SF_SKIP_WS))
ବାହ୍ୟ ଶୂନ୍ୟ sf_init(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ sf_ଠେଲ(ଶୂନ୍ୟ);
ବାହ୍ୟ ଶୂନ୍ୟ sf_କାଢ଼(ଶୂନ୍ୟ);


#endif /* not defined FLEXDEF_H */
