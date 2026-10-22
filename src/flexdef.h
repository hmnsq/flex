
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
#অন্তর্ভাব <config.h>
# endif
#অন্যথা
#অন্তর্ভাব <config_for_build.h>
#endif

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <stdarg.h>
#অন্তর্ভাব <setjmp.h>
#অন্তর্ভাব <ctype.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <math.h>

#ifdef HAVE_ASSERT_H
#অন্তর্ভাব <assert.h>
#অন্যথা
#define প্রতিজ্ঞা(Pred)
#endif

#ifdef HAVE_LIMITS_H
#অন্তর্ভাব <limits.h>
#endif
/* Required: dup() and dup2() in <unistd.h> */
#অন্তর্ভাব <unistd.h>
#ifdef HAVE_NETINET_IN_H
#অন্তর্ভাব <netinet/in.h>
#endif
#ifdef HAVE_SYS_PARAMS_H
#অন্তর্ভাব <sys/params.h>
#endif
/* Required: wait() in <sys/wait.h> */
#অন্তর্ভাব <sys/wait.h>
#ifdef HAVE_STDBOOL_H
#অন্তর্ভাব <stdbool.h>
#নতুবা_যদি !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# অন্যথা
#  define bool পূর্ণসংখ্যা
# endif
# define false 0
# define true 1
#endif
#অন্তর্ভাব <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#অন্তর্ভাব <regex.h>
/* Required: strcasecmp() in <strings.h> */
#অন্তর্ভাব <strings.h>
#অন্তর্ভাব "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#যদি defined(ENABLE_NLS) && ENABLE_NLS
#ifdef HAVE_LOCALE_H
#অন্তর্ভাব <locale.h>
#endif /* HAVE_LOCALE_H */
#অন্তর্ভাব "gettext.h"
#define _(String) gettext (String)
#অন্যথা
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
#define TRANS_STRUCT_PRINT_দৈর্ঘ্য 14

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
#define INITIAL_MAX_DFA_আকার 750
#define MAX_DFA_আকার_INCREMENT 750


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
#define YY_TRAILING_শীর্ষ_MASK 0x4000

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
#define INITIAL_MAX_CCL_TBL_আকার 500
#define MAX_CCL_TBL_আকার_INCREMENT 250

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

#define ONE_স্তূপ_আকার 500	/* stack of states with only one out-transition */
#define SAME_TRANS -1		/* transition is the same as "default" entry for state */

/* The following percentages are used to tune table compression:

 * The percentage the number of out-transitions a state must be of the
 * number of equivalence classes in order to be considered for table
 * compaction by using protos.
 */
#define PROTO_আকার_PERCENTAGE 15

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
#define PROT_SAVE_আকার 2000

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

প্রকারলেখ গণনা trit_t {
	trit_unspecified = -1,
	trit_false = 0,
	trit_true = 1,
} trit;

/* Control variables.  These are in a struct to avoid having to replicate definitions
 * twice for each option, instead a single struct can be declared and externed.
 * If it's in this structure, it has a corresponding m4 symbol.
 */
কাঠামো ctrl_bundle_t {
	bool always_interactive;// always use character-by-character input
	FILE *backing_up_file;	// file to summarize backing-up states to 
	bool bison_bridge_lval;	// (--bison-bridge), bison pure calling convention. 
	bool bison_bridge_lloc;	// (--bison-locations), bison yylloc.
	size_t bufsize;		// input buffer size
	bool C_plus_plus;	// (-+ flag) generate a C++ scanner class 
	পূর্ণসংখ্যা csize;		// size of character set for the scanner 
				// 128 for 7-bit chars and 256 for 8-bit 
	bool ddebug;		// (-d) make a "debug" scanner 
	trit do_main;		// generate main part to make lexer standalone.
	bool do_stdinit;	// whether to initialize yyin/yyout to stdin/stdout
	bool do_yylineno;	// if true, generate code to maintain yylineno 
	bool do_yywrap;		// do yywrap() processing on EOF. 
				// If false, EOF treated as "no more files" 
	bool fullspd;		// (-F flag) use Jacobson method of table representation 
	bool fulltbl;		// (-Cf flag) don't compress the DFA state table 
 	bool gen_সারি_dirs;	// (no -L flag) generate #line directives 
	trit interactive;	// (-I) generate an interactive scanner
	bool never_interactive;	// always use buffered input, don't check for tty.
	bool lex_compat;	// (-l), maximize compatibility with AT&T lex 
	bool long_align;	// (-Ca flag), favor long-word alignment for speed 
	bool no_yyinput;	// suppress use of yyinput()
	bool no_unistd;		// suppress inclusion of unistd.h
	bool posix_compat;	// (-X) maximize compatibility with POSIX lex 
	অক্ষর *prefix;		// prefix for externally visible names, default "yy" 
	trit reject_really_used;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool স্তূপ_used;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	অক্ষর *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	অক্ষর *yydecl;		// user-specified prototype for yylex.
	পূর্ণসংখ্যা yylmax;		// Maximum buffer length if %array
	trit yymore_really_used;// Force geberation of support code for yymore
	bool yytext_is_array;	// if true (i.e., %array directive), then declare
				// yytext as array instead of a character pointer.
				// Nice and inefficient.
	bool noyyread;		// User supplied a yyread function, don't generate default
	অক্ষর *userinit;		// Code fragment to be inserted before scanning
	অক্ষর *preaction;	// Code fragment to be inserted before each action
	অক্ষর *postaction;	// Code fragment to be inserted after each action
	অক্ষর *emit;		// Specify target language to emit.
	অক্ষর *yyterminate;	// Set a non-default termination hook.
	bool no_yypanic;	// if true, no not generate default yypanic function
 	// flags corresponding to the huge mass of --no-yy options
	bool no_yy_ঠেলো_state;
	bool no_yy_বের_করো_state;
	bool no_yy_শীর্ষ_state;
	bool no_yyunput;
	bool no_yy_scan_বাফার;
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
	ধ্রুবক অক্ষর *backend_name;	// What the back end tells you its name is
	ধ্রুবক অক্ষর *traceline_re;	// Regular expression for recognizing tracelines */
	ধ্রুবক অক্ষর *traceline_template;	// templare for emitting trace lines */
	bool have_state_entry_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
কাঠামো env_bundle_t {
	bool backing_up_report;	// (-b flag), generate "lex.backup" file 
				// listing backing-up states
	bool did_outfilename;	// whether outfilename was explicitly set
	অক্ষর *headerfilename;	// name of the .h file to generate
	bool nowarn;		// (-w) do not generate warnings 
	পূর্ণসংখ্যা performance_hint;	// if > 0 (i.e., -p flag), generate a report 
				// relating to scanner performance; 
				// if > 1 (-p -p), report 
 				// on minor performance problems, too.
	অক্ষর *outfilename;	// output file name
	bool printstats;	// (-v) dump statistics
	অক্ষর *skelname;		// name of skeleton for code generation
	FILE *skelfile;		// the skeleton file'd descriptor
	bool trace;		// (-T) env.trace processing 
	bool trace_hex; 	// use hex in trace/debug outputs not octal
	bool use_stdout;	// the -t flag
};

/* Name and byte-width information on a type for code-generation purposes. */
কাঠামো packtype_t {
	অক্ষর *name;
	size_t width;
};

বাহ্যিক কাঠামো ctrl_bundle_t ctrl;
বাহ্যিক কাঠামো env_bundle_t env;

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

বাহ্যিক bool syntaxerror, eofseen;
বাহ্যিক পূর্ণসংখ্যা yymore_used, reject, real_reject, continued_action, in_rule;

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

বাহ্যিক পূর্ণসংখ্যা datapos, dataline, linenum;
বাহ্যিক পূর্ণসংখ্যা skel_ind;
বাহ্যিক অক্ষর *infilename;
বাহ্যিক অক্ষর *extra_type;
বাহ্যিক অক্ষর **প্রবেশ_files;
বাহ্যিক পূর্ণসংখ্যা অঙ্ক_প্রবেশ_files;
বাহ্যিক অক্ষর *program_name;

বাহ্যিক অক্ষর *action_array;
বাহ্যিক পূর্ণসংখ্যা action_আকার;
বাহ্যিক পূর্ণসংখ্যা defs1_offset, prolog_offset, action_offset, action_সূচক;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

বাহ্যিক পূর্ণসংখ্যা onestate[ONE_স্তূপ_আকার], onesym[ONE_স্তূপ_আকার];
বাহ্যিক পূর্ণসংখ্যা onenext[ONE_স্তূপ_আকার], onedef[ONE_স্তূপ_আকার], onesp;


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

বাহ্যিক পূর্ণসংখ্যা maximum_mns, current_mns, current_max_rules;
বাহ্যিক পূর্ণসংখ্যা অঙ্ক_rules, অঙ্ক_eof_rules, default_rule, lastnfa;
বাহ্যিক পূর্ণসংখ্যা *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
বাহ্যিক পূর্ণসংখ্যা *accptnum, *assoc_rule, *state_type;
বাহ্যিক পূর্ণসংখ্যা *rule_type, *rule_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
বাহ্যিক অক্ষর *rule_useful, *rule_has_nl, *ccl_has_nl;
বাহ্যিক পূর্ণসংখ্যা nlch;
বাহ্যিক size_t footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#define STATE_NORMAL 0x1
#define STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

বাহ্যিক পূর্ণসংখ্যা current_state_type;

/* Different types of rules. */
#define RULE_NORMAL 0
#define RULE_VARIABLE 1

/* True if the input rules include a rule with both variable-length head
 * and trailing context, false otherwise.
 */
বাহ্যিক bool variable_trailing_context_rules;


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

বাহ্যিক পূর্ণসংখ্যা numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
বাহ্যিক পূর্ণসংখ্যা protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_আকার];


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
বাহ্যিক পূর্ণসংখ্যা numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs;

/* Meta-equivalence classes are indexed starting at 1, so it's possible
 * that they will require positions from 1 .. CSIZE, i.e., CSIZE + 1
 * slots total (since the arrays are 0-based).  nextecm[] and ecgroup[]
 * don't require the extra position since they're indexed from 1 .. CSIZE - 1.
 */
বাহ্যিক পূর্ণসংখ্যা tecfwd[CSIZE + 1], tecbck[CSIZE + 1];


/* Variables for start conditions:
 * lastsc - last start condition created
 * current_max_scs - current limit on number of start conditions
 * scset - set of rules active in start condition
 * scbol - set of rules active only at the beginning of line in a s.c.
 * scxclu - true if start condition is exclusive
 * sceof - true if start condition has EOF rule
 * scname - start condition name
 */

বাহ্যিক পূর্ণসংখ্যা lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
বাহ্যিক অক্ষর *scxclu, *sceof;
বাহ্যিক পূর্ণসংখ্যা current_max_scs;
বাহ্যিক ধ্রুবক অক্ষর **scname;


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

বাহ্যিক পূর্ণসংখ্যা current_max_dfa_আকার, current_max_xpairs;
বাহ্যিক পূর্ণসংখ্যা current_max_template_xpairs, current_max_dfas;
বাহ্যিক পূর্ণসংখ্যা lastdfa, *nxt, *chk, *tnxt;
বাহ্যিক পূর্ণসংখ্যা *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
বাহ্যিক সংঘ dfaacc_union {
	পূর্ণসংখ্যা    *dfaacc_set;
	পূর্ণসংখ্যা     dfaacc_state;
}      *dfaacc;
বাহ্যিক পূর্ণসংখ্যা *accsiz, *dhash, numas;
বাহ্যিক পূর্ণসংখ্যা numsnpairs, jambase, jamstate;
বাহ্যিক পূর্ণসংখ্যা end_of_বাফার_state;

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

বাহ্যিক পূর্ণসংখ্যা lastccl, *cclmap, *ccllen, *cclng, cclreuse;
বাহ্যিক পূর্ণসংখ্যা current_maxccls, current_max_ccl_tbl_আকার;
বাহ্যিক unsigned অক্ষর *ccltbl;


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

বাহ্যিক অক্ষর nmstr[MAXLINE];
বাহ্যিক পূর্ণসংখ্যা sectnum, nummt, hshcol, dfaeql, numeps, eps2, অঙ্ক_reallocs, nmval;
বাহ্যিক পূর্ণসংখ্যা tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
বাহ্যিক পূর্ণসংখ্যা অঙ্ক_backing_up, bol_needed;

শূন্য   *allocate_array(পূর্ণসংখ্যা, size_t);
শূন্য   *reallocate_array(শূন্য *, পূর্ণসংখ্যা, size_t);

#define allocate_integer_array(আকার_2) \
	allocate_array(আকার_2, আকার(পূর্ণসংখ্যা))

#define reallocate_integer_array(array,আকার_2) \
	reallocate_array((শূন্য *) array, আকার_2, আকার(পূর্ণসংখ্যা))

#define allocate_int_ptr_array(আকার_2) \
	allocate_array(আকার_2, আকার(পূর্ণসংখ্যা *))

#define allocate_char_ptr_array(আকার_2) \
	allocate_array(আকার_2, আকার(অক্ষর *))

#define reallocate_int_ptr_array(array,আকার_2) \
	reallocate_array((শূন্য *) array, আকার_2, আকার(পূর্ণসংখ্যা *))

#define reallocate_char_ptr_array(array,আকার_2) \
	reallocate_array((শূন্য *) array, আকার_2, আকার(অক্ষর *))

#define allocate_character_array(আকার_2) \
	allocate_array( আকার_2, আকার(অক্ষর))

#define reallocate_character_array(array,আকার_2) \
	reallocate_array((শূন্য *) array, আকার_2, আকার(অক্ষর))

#define allocate_Character_array(আকার_2) \
	allocate_array(আকার_2, আকার(unsigned অক্ষর))

#define reallocate_Character_array(array,আকার_2) \
	reallocate_array((শূন্য *) array, আকার_2, আকার(unsigned অক্ষর))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

বাহ্যিক শূন্য ccladd(পূর্ণসংখ্যা, পূর্ণসংখ্যা);	/* add a single character to a ccl */
বাহ্যিক পূর্ণসংখ্যা cclinit(শূন্য);	/* make an empty ccl */
বাহ্যিক শূন্য cclnegate(পূর্ণসংখ্যা);	/* negate a ccl */
বাহ্যিক পূর্ণসংখ্যা ccl_set_diff (পূর্ণসংখ্যা a, পূর্ণসংখ্যা b); /* set difference of two ccls. */
বাহ্যিক পূর্ণসংখ্যা ccl_set_union (পূর্ণসংখ্যা a, পূর্ণসংখ্যা b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
বাহ্যিক শূন্য list_character_set(FILE *, পূর্ণসংখ্যা[]);


/* from file dfa.c */

/* Increase the maximum number of dfas. */
বাহ্যিক শূন্য increase_max_dfas(শূন্য);

বাহ্যিক size_t ntod(শূন্য);	/* convert a ndfa to a dfa */


/* from file ecs.c */

/* Convert character classes to set of equivalence classes. */
বাহ্যিক শূন্য ccl2ecl(শূন্য);

/* Associate equivalence class numbers with class members. */
বাহ্যিক পূর্ণসংখ্যা cre8ecs(পূর্ণসংখ্যা[], পূর্ণসংখ্যা[], পূর্ণসংখ্যা);

/* Update equivalence classes based on character class transitions. */
বাহ্যিক শূন্য mkeccl(unsigned অক্ষর[], পূর্ণসংখ্যা, পূর্ণসংখ্যা[], পূর্ণসংখ্যা[], পূর্ণসংখ্যা, পূর্ণসংখ্যা);

/* Create equivalence class for single character. */
বাহ্যিক শূন্য mkechar(পূর্ণসংখ্যা, পূর্ণসংখ্যা[], পূর্ণসংখ্যা[]);


/* from file gen.c */

/* Set a conditional amd make it visible in generated code */
বাহ্যিক শূন্য visible_define (ধ্রুবক অক্ষর *);

/* And again, with an explicit value part. */
বাহ্যিক শূন্য visible_define_str (ধ্রুবক অক্ষর *, ধ্রুবক অক্ষর *);

/* This time the value part is an int */
বাহ্যিক শূন্য visible_define_int (ধ্রুবক অক্ষর *, ধ্রুবক পূর্ণসংখ্যা);

/* generate transition tables */
বাহ্যিক শূন্য make_tables(শূন্য);

/* Select a type for optimal packing */
কাঠামো packtype_t *optimize_pack(size_t);

/* from file main.c */

বাহ্যিক শূন্য check_options(শূন্য);
বাহ্যিক শূন্য flexend(পূর্ণসংখ্যা);
বাহ্যিক শূন্য usage(শূন্য);


/* from file misc.c */

/* Add the given text to the stored actions. */
বাহ্যিক শূন্য add_action(ধ্রুবক অক্ষর *new_text);

/* True if a string is all lower case. */
বাহ্যিক পূর্ণসংখ্যা all_lower(অক্ষর *);

/* True if a string is all upper case. */
বাহ্যিক পূর্ণসংখ্যা all_upper(অক্ষর *);

/* Compare two integers for use by qsort. */
বাহ্যিক পূর্ণসংখ্যা intcmp(ধ্রুবক শূন্য *, ধ্রুবক শূন্য *);

/* Check a character to make sure it's in the expected range. */
বাহ্যিক শূন্য check_char(পূর্ণসংখ্যা c);

/* Replace upper-case letter to lower-case. */
বাহ্যিক unsigned অক্ষর clower(পূর্ণসংখ্যা);

/* strdup() that fails fatally on allocation failures. */
বাহ্যিক অক্ষর *xstrdup(ধ্রুবক অক্ষর *);

/* Compare two characters for use by qsort with '\0' sorting last. */
বাহ্যিক পূর্ণসংখ্যা cclcmp(ধ্রুবক শূন্য *, ধ্রুবক শূন্য *);

/* Finish up a block of data declarations. */
বাহ্যিক শূন্য dataend(ধ্রুবক অক্ষর *);

/* Flush generated data statements. */
বাহ্যিক শূন্য dataflush(শূন্য);

/* Report an error message and terminate. */
বাহ্যিক শূন্য flexerror(ধ্রুবক অক্ষর *);

/* Report a fatal error message and terminate. */
বাহ্যিক শূন্য flexfatal(ধ্রুবক অক্ষর *);

/* Report a fatal error with a pinpoint, and terminate */
#ifdef HAVE_DECL___FUNC__
#define flex_die(বার্তা) \
    করো{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                program_name, __FILE__, (পূর্ণসংখ্যা)__LINE__,\
                __func__,বার্তা);\
        FLEX_EXIT(1);\
    }যখন(0)
#অন্যথা /* ! HAVE_DECL___FUNC__ */
#define flex_die(বার্তা) \
    করো{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                program_name, __FILE__, (পূর্ণসংখ্যা)__LINE__,\
                বার্তা);\
        FLEX_EXIT(1);\
    }যখন(0)
#endif /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
বাহ্যিক শূন্য lerr(ধ্রুবক অক্ষর *, ...)
#যদি defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#endif
;

/* Like lerr, but also exit after displaying message. */
বাহ্যিক শূন্য lerr_fatal(ধ্রুবক অক্ষর *, ...)
#যদি defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#endif
;

/* Spit out a "#line" statement. */
বাহ্যিক শূন্য সারি_directive_out(FILE *, অক্ষর *, পূর্ণসংখ্যা);

/* Mark the current position in the action array as the end of the section 1
 * user defs.
 */
বাহ্যিক শূন্য mark_defs1(শূন্য);

/* Mark the current position in the action array as the end of the prolog. */
বাহ্যিক শূন্য mark_prolog(শূন্য);

/* Generate a data statement for a two-dimensional array. */
বাহ্যিক শূন্য mk2data(পূর্ণসংখ্যা);

বাহ্যিক শূন্য mkdata(পূর্ণসংখ্যা);	/* generate a data statement */

/* Return the integer represented by a string of digits. */
বাহ্যিক পূর্ণসংখ্যা myctoi(ধ্রুবক অক্ষর *);

/* Return character corresponding to escape sequence. */
বাহ্যিক unsigned অক্ষর myesc(unsigned অক্ষর[]);

/* Output a (possibly-formatted) string to the generated scanner. */
বাহ্যিক শূন্য out(ধ্রুবক অক্ষর *);
বাহ্যিক শূন্য out_dec(ধ্রুবক অক্ষর *, পূর্ণসংখ্যা);
বাহ্যিক শূন্য out_dec2(ধ্রুবক অক্ষর *, পূর্ণসংখ্যা, পূর্ণসংখ্যা);
বাহ্যিক শূন্য out_hex(ধ্রুবক অক্ষর *, unsigned পূর্ণসংখ্যা);
বাহ্যিক শূন্য out_str(ধ্রুবক অক্ষর *, ধ্রুবক অক্ষর *);
বাহ্যিক শূন্য out_str_dec(ধ্রুবক অক্ষর *, ধ্রুবক অক্ষর *, পূর্ণসংখ্যা);
বাহ্যিক শূন্য outc(পূর্ণসংখ্যা);
বাহ্যিক শূন্য outn(ধ্রুবক অক্ষর *);
বাহ্যিক শূন্য out_m4_define(ধ্রুবক অক্ষর* def, ধ্রুবক অক্ষর* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
বাহ্যিক অক্ষর *readable_form(পূর্ণসংখ্যা);

/* Output a yy_trans_info structure. */
বাহ্যিক শূন্য transition_struct_out(পূর্ণসংখ্যা, পূর্ণসংখ্যা);

/* Only needed when using certain broken versions of bison to build parse.c. */
বাহ্যিক শূন্য *yy_flex_xmalloc(পূর্ণসংখ্যা);


/* from file nfa.c */

/* Add an accepting state to a machine. */
বাহ্যিক শূন্য add_accept(পূর্ণসংখ্যা, পূর্ণসংখ্যা);

/* Make a given number of copies of a singleton machine. */
বাহ্যিক পূর্ণসংখ্যা copysingl(পূর্ণসংখ্যা, পূর্ণসংখ্যা);

/* Debugging routine to write out an nfa. */
বাহ্যিক শূন্য dumpnfa(পূর্ণসংখ্যা);

/* Finish up the processing for a rule. */
বাহ্যিক শূন্য finish_rule(পূর্ণসংখ্যা, bool, পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা);

/* Connect two machines together. */
বাহ্যিক পূর্ণসংখ্যা link_machines(পূর্ণসংখ্যা, পূর্ণসংখ্যা);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
বাহ্যিক শূন্য mark_beginning_as_normal(পূর্ণসংখ্যা);

/* Make a machine that branches to two machines. */
বাহ্যিক পূর্ণসংখ্যা mkbranch(পূর্ণসংখ্যা, পূর্ণসংখ্যা);

বাহ্যিক পূর্ণসংখ্যা mkclos(পূর্ণসংখ্যা);	/* convert a machine into a closure */
বাহ্যিক পূর্ণসংখ্যা mkopt(পূর্ণসংখ্যা);	/* make a machine optional */

/* Make a machine that matches either one of two machines. */
বাহ্যিক পূর্ণসংখ্যা mkor(পূর্ণসংখ্যা, পূর্ণসংখ্যা);

/* Convert a machine into a positive closure. */
বাহ্যিক পূর্ণসংখ্যা mkposcl(পূর্ণসংখ্যা);

বাহ্যিক পূর্ণসংখ্যা mkrep(পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা);	/* make a replicated machine */

/* Create a state with a transition on a given symbol. */
বাহ্যিক পূর্ণসংখ্যা mkstate(পূর্ণসংখ্যা);

বাহ্যিক শূন্য new_rule(শূন্য);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
বাহ্যিক শূন্য build_eof_action(শূন্য);

/* Write out a message formatted with one string, pinpointing its location. */
বাহ্যিক শূন্য format_pinpoint_message(ধ্রুবক অক্ষর *, ধ্রুবক অক্ষর *);

/* Write out a message, pinpointing its location. */
বাহ্যিক শূন্য pinpoint_message(ধ্রুবক অক্ষর *);

/* Write out a warning, pinpointing it at the given line. */
বাহ্যিক শূন্য সারি_warning(ধ্রুবক অক্ষর *, পূর্ণসংখ্যা);

/* Write out a message, pinpointing it at the given line. */
বাহ্যিক শূন্য সারি_pinpoint(ধ্রুবক অক্ষর *, পূর্ণসংখ্যা);

/* Report a formatted syntax error. */
বাহ্যিক শূন্য format_synerr(ধ্রুবক অক্ষর *, ধ্রুবক অক্ষর *);
বাহ্যিক শূন্য synerr(ধ্রুবক অক্ষর *);	/* report a syntax error */
বাহ্যিক শূন্য format_warn(ধ্রুবক অক্ষর *, ধ্রুবক অক্ষর *);
বাহ্যিক শূন্য lwarn(ধ্রুবক অক্ষর *);	/* report a warning */
বাহ্যিক শূন্য yyerror(ধ্রুবক অক্ষর *);	/* report a parse error */
বাহ্যিক পূর্ণসংখ্যা yyparse(শূন্য);		/* the YACC parser */

/* Ship a comment to the generated output */
বাহ্যিক শূন্য comment(ধ্রুবক অক্ষর *);

/* from file scan.l */

/* The Flex-generated scanner for flex. */
বাহ্যিক পূর্ণসংখ্যা flexscan(শূন্য);

/* Open the given file (if NULL, stdin) for scanning. */
বাহ্যিক শূন্য set_প্রবেশ_file(অক্ষর *);

/* from file skeletons.c */

/* return the correct file suffix for the selected back end */
ধ্রুবক অক্ষর *suffix (শূন্য);

/* Mine a text-valued property out of the skeleton file */
বাহ্যিক ধ্রুবক অক্ষর *skel_property(ধ্রুবক অক্ষর *);

/* Is the default back end selected?*/
বাহ্যিক bool is_default_backend(শূন্য);

/* Select a backend by name */
বাহ্যিক শূন্য backend_by_name(ধ্রুবক অক্ষর *);

/* Write out one section of the skeleton file. */
বাহ্যিক শূন্য skelout(bool);

/* from file sym.c */

/* Save the text of a character class. */
বাহ্যিক শূন্য cclinstal(অক্ষর[], পূর্ণসংখ্যা);

/* Lookup the number associated with character class. */
বাহ্যিক পূর্ণসংখ্যা ccllookup(অক্ষর[]);

বাহ্যিক শূন্য ndinstal(ধ্রুবক অক্ষর *, অক্ষর[]);	/* install a name definition */
বাহ্যিক অক্ষর *ndlookup(ধ্রুবক অক্ষর *);	/* lookup a name definition */

/* Increase maximum number of SC's. */
বাহ্যিক শূন্য scextend(শূন্য);
বাহ্যিক শূন্য scinstal(ধ্রুবক অক্ষর *, bool);	/* make a start condition */

/* Lookup the number associated with a start condition. */
বাহ্যিক পূর্ণসংখ্যা sclookup(ধ্রুবক অক্ষর *);

/* Supply context argument for a function if required */
বাহ্যিক শূন্য context_call(অক্ষর *);

/* from file tblcmp.c */

/* Build table entries for dfa state. */
বাহ্যিক শূন্য bldtbl(পূর্ণসংখ্যা[], পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা);

বাহ্যিক শূন্য cmptmps(শূন্য);	/* compress template table entries */
বাহ্যিক শূন্য expand_nxt_chk(শূন্য);	/* increase nxt/chk arrays */

/* Finds a space in the table for a state to be placed. */
বাহ্যিক পূর্ণসংখ্যা find_table_space(পূর্ণসংখ্যা *, পূর্ণসংখ্যা);
বাহ্যিক শূন্য inittbl(শূন্য);	/* initialize transition tables */

/* Make the default, "jam" table entries. */
বাহ্যিক শূন্য mkdeftbl(শূন্য);

/* Create table entries for a state (or state fragment) which has
 * only one out-transition.
 */
বাহ্যিক শূন্য mk1tbl(পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা);

/* Place a state into full speed transition table. */
বাহ্যিক শূন্য place_state(পূর্ণসংখ্যা *, পূর্ণসংখ্যা, পূর্ণসংখ্যা);

/* Save states with only one out-transition to be processed later. */
বাহ্যিক শূন্য stack1(পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা);


/* from file yylex.c */

বাহ্যিক পূর্ণসংখ্যা yylex(শূন্য);

/* A growable array. See buf.c. */
কাঠামো Buf {
	শূন্য   *elts;		/* elements. */
	পূর্ণসংখ্যা     nelts;		/* number of elements. */
	size_t  elt_আকার;	/* in bytes. */
	পূর্ণসংখ্যা     nmax;		/* max capacity of elements. */
};

বাহ্যিক শূন্য buf_init(কাঠামো Buf * buf, size_t elem_আকার);
বাহ্যিক শূন্য buf_destroy(কাঠামো Buf * buf);
বাহ্যিক কাঠামো Buf *buf_append(কাঠামো Buf * buf, ধ্রুবক শূন্য *ptr, পূর্ণসংখ্যা n_elem);
বাহ্যিক কাঠামো Buf *buf_strappend(কাঠামো Buf *, ধ্রুবক অক্ষর *str);
বাহ্যিক কাঠামো Buf *buf_strnappend(কাঠামো Buf *, ধ্রুবক অক্ষর *str, পূর্ণসংখ্যা nchars);
বাহ্যিক কাঠামো Buf *buf_prints(কাঠামো Buf *buf, ধ্রুবক অক্ষর *fmt, ধ্রুবক অক্ষর* s);

বাহ্যিক কাঠামো Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
বাহ্যিক কাঠামো Buf শীর্ষ_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#define OUT_BEGIN_CODE() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#define OUT_END_CODE()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
বাহ্যিক jmp_buf flex_main_jmp_buf;

#define FLEX_EXIT(status) longjmp(flex_main_jmp_buf,(status)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
বাহ্যিক অক্ষর *chomp (অক্ষর *str);

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
bool has_case(পূর্ণসংখ্যা c);

/* Change case of character if possible. */
পূর্ণসংখ্যা reverse_case(পূর্ণসংখ্যা c);

/* return false if [c1-c2] is ambiguous for a caseless scanner. */
bool range_covers_case (পূর্ণসংখ্যা c1, পূর্ণসংখ্যা c2);

/*
 *  From "filter.c"
 */

/** A single stdio filter to execute.
 *  The filter may be external, such as "sed", or it
 *  may be internal, as a function call.
 */
কাঠামো filter {
    পূর্ণসংখ্যা    (*filter_func)(কাঠামো filter*); /**< internal filter function */
    শূন্য * extra;         /**< extra data passed to filter_func */
	পূর্ণসংখ্যা     argc;         /**< arg count */
	ধ্রুবক অক্ষর ** argv;   /**< arg vector, \0-terminated */
    কাঠামো filter * পরবর্তী; /**< next filter or NULL */
};

/* output filter chain */
বাহ্যিক কাঠামো filter * output_chain;
বাহ্যিক কাঠামো filter *filter_create_ext (কাঠামো filter * chain, ধ্রুবক অক্ষর *cmd, ...);
কাঠামো filter *filter_create_int(কাঠামো filter *chain,
				  পূর্ণসংখ্যা (*filter_func) (কাঠামো filter *),
                  শূন্য *extra);
বাহ্যিক bool filter_apply_chain(কাঠামো filter * chain);
বাহ্যিক পূর্ণসংখ্যা filter_truncate(কাঠামো filter * chain, পূর্ণসংখ্যা max_len);
বাহ্যিক পূর্ণসংখ্যা filter_tee_header(কাঠামো filter *chain);
বাহ্যিক পূর্ণসংখ্যা filter_fix_linedirs(কাঠামো filter *chain);


/*
 * From "regex.c"
 */

বাহ্যিক regex_t regex_linedir;
bool flex_init_regex(ধ্রুবক অক্ষর *);
শূন্য flex_regcomp(regex_t *preg, ধ্রুবক অক্ষর *regex, পূর্ণসংখ্যা cflags);
অক্ষর   *regmatch_dup (regmatch_t * m, ধ্রুবক অক্ষর *src);
অক্ষর   *regmatch_cpy (regmatch_t * m, অক্ষর *dest, ধ্রুবক অক্ষর *src);
পূর্ণসংখ্যা regmatch_len (regmatch_t * m);
পূর্ণসংখ্যা regmatch_strtol (regmatch_t * m, ধ্রুবক অক্ষর *src, অক্ষর **endptr, পূর্ণসংখ্যা base);
bool regmatch_empty (regmatch_t * m);

/* From "scanflags.h" */
প্রকারলেখ unsigned পূর্ণসংখ্যা scanflags_t;
বাহ্যিক scanflags_t* _sf_stk;
বাহ্যিক size_t sf_শীর্ষ_ix, _sf_max; /**< stack of scanner flags. */
#define _SF_CASE_INS   ((scanflags_t) 0x0001)
#define _SF_DOT_ALL    ((scanflags_t) 0x0002)
#define _SF_SKIP_WS    ((scanflags_t) 0x0004)
#define sf_শীর্ষ()           (_sf_stk[sf_শীর্ষ_ix])
#define sf_case_ins()      (sf_শীর্ষ() & _SF_CASE_INS)
#define sf_dot_all()       (sf_শীর্ষ() & _SF_DOT_ALL)
#define sf_skip_ws()       (sf_শীর্ষ() & _SF_SKIP_WS)
#define sf_set_case_ins(X)      ((X) ? (sf_শীর্ষ() |= _SF_CASE_INS) : (sf_শীর্ষ() &= ~_SF_CASE_INS))
#define sf_set_dot_all(X)       ((X) ? (sf_শীর্ষ() |= _SF_DOT_ALL)  : (sf_শীর্ষ() &= ~_SF_DOT_ALL))
#define sf_set_skip_ws(X)       ((X) ? (sf_শীর্ষ() |= _SF_SKIP_WS)  : (sf_শীর্ষ() &= ~_SF_SKIP_WS))
বাহ্যিক শূন্য sf_init(শূন্য);
বাহ্যিক শূন্য sf_ঠেলো(শূন্য);
বাহ্যিক শূন্য sf_বের_করো(শূন্য);


#endif /* not defined FLEXDEF_H */
