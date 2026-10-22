
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
#अन्तर्भाव <config.h>
# endif
#अञ्ञथा
#अन्तर्भाव <config_for_build.h>
#endif

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdarg.h>
#अन्तर्भाव <setjmp.h>
#अन्तर्भाव <ctype.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <math.h>

#ifdef HAVE_ASSERT_H
#अन्तर्भाव <assert.h>
#अञ्ञथा
#define प्रतिज्ञा(Pred)
#endif

#ifdef HAVE_LIMITS_H
#अन्तर्भाव <limits.h>
#endif
/* Required: dup() and dup2() in <unistd.h> */
#अन्तर्भाव <unistd.h>
#ifdef HAVE_NETINET_IN_H
#अन्तर्भाव <netinet/in.h>
#endif
#ifdef HAVE_SYS_PARAMS_H
#अन्तर्भाव <sys/params.h>
#endif
/* Required: wait() in <sys/wait.h> */
#अन्तर्भाव <sys/wait.h>
#ifdef HAVE_STDBOOL_H
#अन्तर्भाव <stdbool.h>
#नोचेद्यदि !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# अञ्ञथा
#  define bool पूर्णाङ्क
# endif
# define false 0
# define true 1
#endif
#अन्तर्भाव <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#अन्तर्भाव <regex.h>
/* Required: strcasecmp() in <strings.h> */
#अन्तर्भाव <strings.h>
#अन्तर्भाव "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#सचे defined(ENABLE_NLS) && ENABLE_NLS
#ifdef HAVE_LOCALE_H
#अन्तर्भाव <locale.h>
#endif /* HAVE_LOCALE_H */
#अन्तर्भाव "gettext.h"
#define _(String) gettext (String)
#अञ्ञथा
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

#define ONE_राशिः_SIZE 500	/* stack of states with only one out-transition */
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
	FILE *backing_up_file;	// file to summarize backing-up states to 
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
	वर्ण *prefix;		// prefix for externally visible names, default "yy" 
	trit reject_really_used;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool राशिः_used;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	वर्ण *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	वर्ण *yydecl;		// user-specified prototype for yylex.
	पूर्णाङ्क yylmax;		// Maximum buffer length if %array
	trit yymore_really_used;// Force geberation of support code for yymore
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
	ध्रुव वर्ण *backend_name;	// What the back end tells you its name is
	ध्रुव वर्ण *traceline_re;	// Regular expression for recognizing tracelines */
	ध्रुव वर्ण *traceline_template;	// templare for emitting trace lines */
	bool have_state_entry_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
संरचना env_bundle_t {
	bool backing_up_report;	// (-b flag), generate "lex.backup" file 
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
	size_t width;
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
बाह्य पूर्णाङ्क yymore_used, reject, real_reject, continued_action, in_rule;

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
बाह्य वर्ण *program_name;

बाह्य वर्ण *action_array;
बाह्य पूर्णाङ्क action_size;
बाह्य पूर्णाङ्क defs1_offset, prolog_offset, action_offset, action_index;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

बाह्य पूर्णाङ्क onestate[ONE_राशिः_SIZE], onesym[ONE_राशिः_SIZE];
बाह्य पूर्णाङ्क onenext[ONE_राशिः_SIZE], onedef[ONE_राशिः_SIZE], onesp;


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

बाह्य पूर्णाङ्क maximum_mns, current_mns, current_max_rules;
बाह्य पूर्णाङ्क अङ्कः_rules, अङ्कः_eof_rules, default_rule, lastnfa;
बाह्य पूर्णाङ्क *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
बाह्य पूर्णाङ्क *accptnum, *assoc_rule, *state_type;
बाह्य पूर्णाङ्क *rule_type, *rule_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
बाह्य वर्ण *rule_useful, *rule_has_nl, *ccl_has_nl;
बाह्य पूर्णाङ्क nlch;
बाह्य size_t footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#define STATE_NORMAL 0x1
#define STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

बाह्य पूर्णाङ्क current_state_type;

/* Different types of rules. */
#define RULE_NORMAL 0
#define RULE_VARIABLE 1

/* True if the input rules include a rule with both variable-length head
 * and trailing context, false otherwise.
 */
बाह्य bool variable_trailing_context_rules;


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
बाह्य पूर्णाङ्क protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_SIZE];


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

बाह्य पूर्णाङ्क current_max_dfa_size, current_max_xpairs;
बाह्य पूर्णाङ्क current_max_template_xpairs, current_max_dfas;
बाह्य पूर्णाङ्क lastdfa, *nxt, *chk, *tnxt;
बाह्य पूर्णाङ्क *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
बाह्य सङ्घ dfaacc_union {
	पूर्णाङ्क    *dfaacc_set;
	पूर्णाङ्क     dfaacc_state;
}      *dfaacc;
बाह्य पूर्णाङ्क *accsiz, *dhash, numas;
बाह्य पूर्णाङ्क numsnpairs, jambase, jamstate;
बाह्य पूर्णाङ्क end_of_buffer_state;

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
बाह्य पूर्णाङ्क current_maxccls, current_max_ccl_tbl_size;
बाह्य unsigned वर्ण *ccltbl;


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
बाह्य पूर्णाङ्क अङ्कः_backing_up, bol_needed;

शून्य   *allocate_array(पूर्णाङ्क, size_t);
शून्य   *reallocate_array(शून्य *, पूर्णाङ्क, size_t);

#define allocate_integer_array(size) \
	allocate_array(size, परिमाण(पूर्णाङ्क))

#define reallocate_integer_array(array,size) \
	reallocate_array((शून्य *) array, size, परिमाण(पूर्णाङ्क))

#define allocate_int_ptr_array(size) \
	allocate_array(size, परिमाण(पूर्णाङ्क *))

#define allocate_char_ptr_array(size) \
	allocate_array(size, परिमाण(वर्ण *))

#define reallocate_int_ptr_array(array,size) \
	reallocate_array((शून्य *) array, size, परिमाण(पूर्णाङ्क *))

#define reallocate_char_ptr_array(array,size) \
	reallocate_array((शून्य *) array, size, परिमाण(वर्ण *))

#define allocate_character_array(size) \
	allocate_array( size, परिमाण(वर्ण))

#define reallocate_character_array(array,size) \
	reallocate_array((शून्य *) array, size, परिमाण(वर्ण))

#define allocate_Character_array(size) \
	allocate_array(size, परिमाण(unsigned वर्ण))

#define reallocate_Character_array(array,size) \
	reallocate_array((शून्य *) array, size, परिमाण(unsigned वर्ण))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

बाह्य शून्य ccladd(पूर्णाङ्क, पूर्णाङ्क);	/* add a single character to a ccl */
बाह्य पूर्णाङ्क cclinit(शून्य);	/* make an empty ccl */
बाह्य शून्य cclnegate(पूर्णाङ्क);	/* negate a ccl */
बाह्य पूर्णाङ्क ccl_set_diff (पूर्णाङ्क a, पूर्णाङ्क b); /* set difference of two ccls. */
बाह्य पूर्णाङ्क ccl_set_union (पूर्णाङ्क a, पूर्णाङ्क b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
बाह्य शून्य list_character_set(FILE *, पूर्णाङ्क[]);


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
बाह्य शून्य mkeccl(unsigned वर्ण[], पूर्णाङ्क, पूर्णाङ्क[], पूर्णाङ्क[], पूर्णाङ्क, पूर्णाङ्क);

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
बाह्य शून्य add_action(ध्रुव वर्ण *new_text);

/* True if a string is all lower case. */
बाह्य पूर्णाङ्क all_lower(वर्ण *);

/* True if a string is all upper case. */
बाह्य पूर्णाङ्क all_upper(वर्ण *);

/* Compare two integers for use by qsort. */
बाह्य पूर्णाङ्क intcmp(ध्रुव शून्य *, ध्रुव शून्य *);

/* Check a character to make sure it's in the expected range. */
बाह्य शून्य check_char(पूर्णाङ्क c);

/* Replace upper-case letter to lower-case. */
बाह्य unsigned वर्ण clower(पूर्णाङ्क);

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
#ifdef HAVE_DECL___FUNC__
#define flex_die(सन्देशः) \
    करोहि{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                program_name, __FILE__, (पूर्णाङ्क)__LINE__,\
                __func__,सन्देशः);\
        FLEX_EXIT(1);\
    }याव(0)
#अञ्ञथा /* ! HAVE_DECL___FUNC__ */
#define flex_die(सन्देशः) \
    करोहि{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                program_name, __FILE__, (पूर्णाङ्क)__LINE__,\
                सन्देशः);\
        FLEX_EXIT(1);\
    }याव(0)
#endif /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
बाह्य शून्य lerr(ध्रुव वर्ण *, ...)
#सचे defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#endif
;

/* Like lerr, but also exit after displaying message. */
बाह्य शून्य lerr_fatal(ध्रुव वर्ण *, ...)
#सचे defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#endif
;

/* Spit out a "#line" statement. */
बाह्य शून्य पङ्क्तिः_directive_out(FILE *, वर्ण *, पूर्णाङ्क);

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
बाह्य unsigned वर्ण myesc(unsigned वर्ण[]);

/* Output a (possibly-formatted) string to the generated scanner. */
बाह्य शून्य out(ध्रुव वर्ण *);
बाह्य शून्य out_dec(ध्रुव वर्ण *, पूर्णाङ्क);
बाह्य शून्य out_dec2(ध्रुव वर्ण *, पूर्णाङ्क, पूर्णाङ्क);
बाह्य शून्य out_hex(ध्रुव वर्ण *, unsigned पूर्णाङ्क);
बाह्य शून्य out_str(ध्रुव वर्ण *, ध्रुव वर्ण *);
बाह्य शून्य out_str_dec(ध्रुव वर्ण *, ध्रुव वर्ण *, पूर्णाङ्क);
बाह्य शून्य outc(पूर्णाङ्क);
बाह्य शून्य outn(ध्रुव वर्ण *);
बाह्य शून्य out_m4_define(ध्रुव वर्ण* def, ध्रुव वर्ण* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
बाह्य वर्ण *readable_form(पूर्णाङ्क);

/* Output a yy_trans_info structure. */
बाह्य शून्य transition_struct_out(पूर्णाङ्क, पूर्णाङ्क);

/* Only needed when using certain broken versions of bison to build parse.c. */
बाह्य शून्य *yy_flex_xmalloc(पूर्णाङ्क);


/* from file nfa.c */

/* Add an accepting state to a machine. */
बाह्य शून्य add_accept(पूर्णाङ्क, पूर्णाङ्क);

/* Make a given number of copies of a singleton machine. */
बाह्य पूर्णाङ्क copysingl(पूर्णाङ्क, पूर्णाङ्क);

/* Debugging routine to write out an nfa. */
बाह्य शून्य dumpnfa(पूर्णाङ्क);

/* Finish up the processing for a rule. */
बाह्य शून्य finish_rule(पूर्णाङ्क, bool, पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क);

/* Connect two machines together. */
बाह्य पूर्णाङ्क link_machines(पूर्णाङ्क, पूर्णाङ्क);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
बाह्य शून्य mark_beginning_as_normal(पूर्णाङ्क);

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

बाह्य शून्य new_rule(शून्य);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
बाह्य शून्य build_eof_action(शून्य);

/* Write out a message formatted with one string, pinpointing its location. */
बाह्य शून्य format_pinpoint_message(ध्रुव वर्ण *, ध्रुव वर्ण *);

/* Write out a message, pinpointing its location. */
बाह्य शून्य pinpoint_message(ध्रुव वर्ण *);

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
बाह्य शून्य set_निवेशः_file(वर्ण *);

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
बाह्य पूर्णाङ्क find_table_space(पूर्णाङ्क *, पूर्णाङ्क);
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
	size_t  elt_size;	/* in bytes. */
	पूर्णाङ्क     nmax;		/* max capacity of elements. */
};

बाह्य शून्य buf_init(संरचना Buf * buf, size_t elem_size);
बाह्य शून्य buf_destroy(संरचना Buf * buf);
बाह्य संरचना Buf *buf_append(संरचना Buf * buf, ध्रुव शून्य *ptr, पूर्णाङ्क n_elem);
बाह्य संरचना Buf *buf_strappend(संरचना Buf *, ध्रुव वर्ण *str);
बाह्य संरचना Buf *buf_strnappend(संरचना Buf *, ध्रुव वर्ण *str, पूर्णाङ्क nchars);
बाह्य संरचना Buf *buf_prints(संरचना Buf *buf, ध्रुव वर्ण *fmt, ध्रुव वर्ण* s);

बाह्य संरचना Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
बाह्य संरचना Buf शिखरम्_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#define OUT_BEGIN_CODE() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#define OUT_END_CODE()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
बाह्य jmp_buf flex_main_jmp_buf;

#define FLEX_EXIT(status) longjmp(flex_main_jmp_buf,(status)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
बाह्य वर्ण *chomp (वर्ण *str);

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
    संरचना filter * next; /**< next filter or NULL */
};

/* output filter chain */
बाह्य संरचना filter * output_chain;
बाह्य संरचना filter *filter_create_ext (संरचना filter * chain, ध्रुव वर्ण *cmd, ...);
संरचना filter *filter_create_int(संरचना filter *chain,
				  पूर्णाङ्क (*filter_func) (संरचना filter *),
                  शून्य *extra);
बाह्य bool filter_apply_chain(संरचना filter * chain);
बाह्य पूर्णाङ्क filter_truncate(संरचना filter * chain, पूर्णाङ्क max_len);
बाह्य पूर्णाङ्क filter_tee_header(संरचना filter *chain);
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
पूर्णाङ्क regmatch_strtol (regmatch_t * m, ध्रुव वर्ण *src, वर्ण **endptr, पूर्णाङ्क base);
bool regmatch_empty (regmatch_t * m);

/* From "scanflags.h" */
प्रकारनिर्देश unsigned पूर्णाङ्क scanflags_t;
बाह्य scanflags_t* _sf_stk;
बाह्य size_t sf_शिखरम्_ix, _sf_max; /**< stack of scanner flags. */
#define _SF_CASE_INS   ((scanflags_t) 0x0001)
#define _SF_DOT_ALL    ((scanflags_t) 0x0002)
#define _SF_SKIP_WS    ((scanflags_t) 0x0004)
#define sf_शिखरम्()           (_sf_stk[sf_शिखरम्_ix])
#define sf_case_ins()      (sf_शिखरम्() & _SF_CASE_INS)
#define sf_dot_all()       (sf_शिखरम्() & _SF_DOT_ALL)
#define sf_skip_ws()       (sf_शिखरम्() & _SF_SKIP_WS)
#define sf_set_case_ins(X)      ((X) ? (sf_शिखरम्() |= _SF_CASE_INS) : (sf_शिखरम्() &= ~_SF_CASE_INS))
#define sf_set_dot_all(X)       ((X) ? (sf_शिखरम्() |= _SF_DOT_ALL)  : (sf_शिखरम्() &= ~_SF_DOT_ALL))
#define sf_set_skip_ws(X)       ((X) ? (sf_शिखरम्() |= _SF_SKIP_WS)  : (sf_शिखरम्() &= ~_SF_SKIP_WS))
बाह्य शून्य sf_init(शून्य);
बाह्य शून्य sf_प्रक्षिप(शून्य);
बाह्य शून्य sf_निष्कासय(शून्य);


#endif /* not defined FLEXDEF_H */
