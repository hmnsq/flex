
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ FLEXDEF_H
#ವ್ಯಾಖ್ಯಾನಿಸು FLEXDEF_H 1

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ USE_CONFIG_FOR_BUILD
# ifdef HAVE_CONFIG_H
#ಅನ್ತರ್ಭಾವ <config.h>
# endif
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ <config_for_build.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <setjmp.h>
#ಅನ್ತರ್ಭಾವ <ctype.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <math.h>

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_ASSERT_H
#ಅನ್ತರ್ಭಾವ <assert.h>
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು ಪ್ರತಿಜ್ಞಾ(Pred)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LIMITS_H
#ಅನ್ತರ್ಭಾವ <limits.h>
#ಆದರೆ_ಅಂತ್ಯ
/* Required: dup() and dup2() in <unistd.h> */
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_NETINET_ಒಳ_H
#ಅನ್ತರ್ಭಾವ <netinet/in.h>
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_SYS_PARAMS_H
#ಅನ್ತರ್ಭಾವ <sys/params.h>
#ಆದರೆ_ಅಂತ್ಯ
/* Required: wait() in <sys/wait.h> */
#ಅನ್ತರ್ಭಾವ <sys/wait.h>
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_STDBOOL_H
#ಅನ್ತರ್ಭಾವ <stdbool.h>
#ಅಥವಾಆದರೆ !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# ಇಲ್ಲದಿದ್ದರೆ
#  define bool ಪೂರ್ಣಾಂಕ
# endif
# define false 0
# define true 1
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#ಅನ್ತರ್ಭಾವ <regex.h>
/* Required: strcasecmp() in <strings.h> */
#ಅನ್ತರ್ಭಾವ <strings.h>
#ಅನ್ತರ್ಭಾವ "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#ಆದರೆ defined(ENABLE_NLS) && ENABLE_NLS
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_LOCALE_H
#ಅನ್ತರ್ಭಾವ <locale.h>
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_LOCALE_H */
#ಅನ್ತರ್ಭಾವ "gettext.h"
#ವ್ಯಾಖ್ಯಾನಿಸು _(String) gettext (String)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು _(STRING) STRING
#ಆದರೆ_ಅಂತ್ಯ /* ENABLE_NLS */

/* Always be prepared to generate an 8-bit scanner. */
#ವ್ಯಾಖ್ಯಾನಿಸು CSIZE 256

/* Size of input alphabet - should be size of ASCII set. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ DEFAULT_CSIZE
#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_CSIZE 128
#ಆದರೆ_ಅಂತ್ಯ

/* Maximum line length we'll have to deal with. */
#ವ್ಯಾಖ್ಯಾನಿಸು MAXLINE 2048

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MIN
#ವ್ಯಾಖ್ಯಾನಿಸು MIN(x,y) ((x) < (y) ? (x) : (y))
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MAX
#ವ್ಯಾಖ್ಯಾನಿಸು MAX(x,y) ((x) > (y) ? (x) : (y))
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ABS
#ವ್ಯಾಖ್ಯಾನಿಸು ABS(x) ((x) < 0 ? -(x) : (x))
#ಆದರೆ_ಅಂತ್ಯ

/* Whether an integer is a power of two */
#ವ್ಯಾಖ್ಯಾನಿಸು is_power_ದ_2(n) ((n) > 0 && ((n) & ((n) - 1)) == 0)

/* Special chk[] values marking the slots taking by end-of-buffer and action
 * numbers.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು EOB_POSITION -1
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_POSITION -2

/* Number of data items per line for -f output. */
#ವ್ಯಾಖ್ಯಾನಿಸು NUMDATAITEMS 10

/* Number of lines of data in -f output before inserting a blank line for
 * readability.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು NUMDATALINES 10

/* transition_struct_out() definitions. */
#ವ್ಯಾಖ್ಯಾನಿಸು TRANS_STRUCT_PRINT_ಉದ್ದಳತೆ 14

/* Returns true if an nfa state has an epsilon out-transition slot
 * that can be used.  This definition is currently not used.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans2[state] == NO_TRANSITION && \
	 finalst[state] != state)

/* Returns true if an nfa state has an epsilon out-transition character
 * and both slots are free
 */
#ವ್ಯಾಖ್ಯಾನಿಸು SUPER_FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans1[state] == NO_TRANSITION) \

/* Maximum number of NFA states that can comprise a DFA state.  It's real
 * big because if there's a lot of rules, the initial state will have a
 * huge epsilon closure.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು INITIAL_MAX_DFA_ಗಾತ್ರ 750
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_DFA_ಗಾತ್ರ_INCREMENT 750


/* A note on the following masks.  They are used to mark accepting numbers
 * as being special.  As such, they implicitly limit the number of accepting
 * numbers (i.e., rules) because if there are too many rules the rule numbers
 * will overload the mask bits.  Fortunately, this limit is \large/ (0x2000 ==
 * 8192) so unlikely to actually cause any problems.  A check is made in
 * new_rule() to ensure that this limit is not reached.
 */

/* Mask to mark a trailing context accepting number. */
#ವ್ಯಾಖ್ಯಾನಿಸು YY_TRAILING_ಮುಖವಾಡ 0x2000

/* Mask to mark the accepting number of the "head" of a trailing context
 * rule.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು YY_TRAILING_ತಲೆ_ಮುಖವಾಡ 0x4000

/* Maximum number of rules, as outlined in the above note. */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_ನಿಯಮ (YY_TRAILING_ಮುಖವಾಡ - 1)


/* NIL must be 0.  If not, its special meaning when making equivalence classes
 * (it marks the representative of a given e.c.) will be unidentifiable.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು NIL 0

#ವ್ಯಾಖ್ಯಾನಿಸು JAM -1			/* to mark a missing DFA transition */
#ವ್ಯಾಖ್ಯಾನಿಸು NO_TRANSITION NIL
#ವ್ಯಾಖ್ಯಾನಿಸು UNIQUE -1		/* marks a symbol as an e.c. representative */
#ವ್ಯಾಖ್ಯಾನಿಸು INFINITE_REPEAT -1		/* for x{5,} constructions */

#ವ್ಯಾಖ್ಯಾನಿಸು INITIAL_MAX_CCLS 100	/* max number of unique character classes */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_CCLS_INCREMENT 100

/* Size of table holding members of character classes. */
#ವ್ಯಾಖ್ಯಾನಿಸು INITIAL_MAX_CCL_TBL_ಗಾತ್ರ 500
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_CCL_TBL_ಗಾತ್ರ_INCREMENT 250

#ವ್ಯಾಖ್ಯಾನಿಸು INITIAL_MAX_ನಿಯಮಗಳು 100	/* default maximum number of rules */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_ನಿಯಮಗಳು_INCREMENT 100

#ವ್ಯಾಖ್ಯಾನಿಸು INITIAL_MNS 2000	/* default maximum number of nfa states */
#ವ್ಯಾಖ್ಯಾನಿಸು MNS_INCREMENT 1000	/* amount to bump above by if it's not enough */

#ವ್ಯಾಖ್ಯಾನಿಸು INITIAL_MAX_DFAS 1000	/* default maximum number of dfa states */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_DFAS_INCREMENT 1000

#ವ್ಯಾಖ್ಯಾನಿಸು JAMSTATE -32766		/* marks a reference to the state that always jams */

/* Maximum number of NFA states. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಗರಿಷ್ಠ_MNS 31999
#ವ್ಯಾಖ್ಯಾನಿಸು ಗರಿಷ್ಠ_MNS_LONG 1999999999

/* Enough so that if it's subtracted from an NFA state number, the result
 * is guaranteed to be negative.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು MARKER_DIFFERENCE (ಗರಿಷ್ಠ_mns+2)

/* Maximum number of nxt/chk pairs for non-templates. */
#ವ್ಯಾಖ್ಯಾನಿಸು INITIAL_MAX_XPAIRS 2000
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_XPAIRS_INCREMENT 2000

/* Maximum number of nxt/chk pairs needed for templates. */
#ವ್ಯಾಖ್ಯಾನಿಸು INITIAL_MAX_TEMPLATE_XPAIRS 2500
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_TEMPLATE_XPAIRS_INCREMENT 2500

#ವ್ಯಾಖ್ಯಾನಿಸು SYM_EPSILON (CSIZE + 1)	/* to mark transitions on the symbol epsilon */

#ವ್ಯಾಖ್ಯಾನಿಸು INITIAL_MAX_SCS 40	/* maximum number of start conditions */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_SCS_INCREMENT 40	/* amount to bump by if it's not enough */

#ವ್ಯಾಖ್ಯಾನಿಸು ONE_ರಾಶಿ_ಗಾತ್ರ 500	/* stack of states with only one out-transition */
#ವ್ಯಾಖ್ಯಾನಿಸು SAME_TRANS -1		/* transition is the same as "default" entry for state */

/* The following percentages are used to tune table compression:

 * The percentage the number of out-transitions a state must be of the
 * number of equivalence classes in order to be considered for table
 * compaction by using protos.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು PROTO_ಗಾತ್ರ_PERCENTAGE 15

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * that the state's transition table is first compared with a potential
 * template of the most common out-transition instead of with the first
 * proto in the proto queue.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_COM_PERCENTAGE 50

/* The percentage the number of differences between a state's transition
 * table and the proto it was first compared with must be of the total
 * number of out-transitions of the state in order to keep the first
 * proto as a good match and not search any further.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಮೊದಲ_ಹೊಂದಿಕೆ_DIFF_PERCENTAGE 10

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to use the proto as an acceptable close match.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ACCEPTABLE_DIFF_PERCENTAGE 50

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * to consider making a template from the state.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು TEMPLATE_SAME_PERCENTAGE 60

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to create a new proto from the state.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು NEW_PROTO_DIFF_PERCENTAGE 20

/* The percentage the total number of out-transitions of a state must be
 * of the number of equivalence classes in order to consider trying to
 * fit the transition table into "holes" inside the nxt/chk table.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು INTERIOR_FIT_PERCENTAGE 15

/* Size of region set aside to cache the complete transition table of
 * protos on the proto queue to enable quick comparisons.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು PROT_SAVE_ಗಾತ್ರ 2000

#ವ್ಯಾಖ್ಯಾನಿಸು MSP 50			/* maximum number of saved protos (protos on the proto queue) */

/* Maximum number of out-transitions a state can have that we'll rummage
 * around through the interior of the internal fast table looking for a
 * spot for it.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_XTIONS_ತುಂಬಿದ_INTERIOR_FIT 4

/* Maximum number of rules which will be reported as being associated
 * with a DFA state.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_ASSOC_ನಿಯಮಗಳು 100

/* Number that, if used to subscript an array, has a good chance of producing
 * an error; should be small enough to fit into a short.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು BAD_SUBSCRIPT -32767

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ trit_t {
	trit_unspecified = -1,
	trit_false = 0,
	trit_true = 1,
} trit;

/* Control variables.  These are in a struct to avoid having to replicate definitions
 * twice for each option, instead a single struct can be declared and externed.
 * If it's in this structure, it has a corresponding m4 symbol.
 */
ರಚನೆ ctrl_bundle_t {
	bool always_interactive;// always use character-by-character input
	FILE *backing_ಮೇಲೆ_file;	// file to summarize backing-up states to 
	bool bison_bridge_lval;	// (--bison-bridge), bison pure calling convention. 
	bool bison_bridge_lloc;	// (--bison-locations), bison yylloc.
	size_t bufsize;		// input buffer size
	bool C_plus_plus;	// (-+ flag) generate a C++ scanner class 
	ಪೂರ್ಣಾಂಕ csize;		// size of character set for the scanner 
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
	ಅಕ್ಷರ *ಪೂರ್ವಪ್ರತ್ಯಯ;		// prefix for externally visible names, default "yy" 
	trit reject_really_ಬಳಸಿದ;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool ರಾಶಿ_ಬಳಸಿದ;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	ಅಕ್ಷರ *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	ಅಕ್ಷರ *yydecl;		// user-specified prototype for yylex.
	ಪೂರ್ಣಾಂಕ yylmax;		// Maximum buffer length if %array
	trit yymore_really_ಬಳಸಿದ;// Force geberation of support code for yymore
	bool yytext_is_array;	// if true (i.e., %array directive), then declare
				// yytext as array instead of a character pointer.
				// Nice and inefficient.
	bool noyyread;		// User supplied a yyread function, don't generate default
	ಅಕ್ಷರ *userinit;		// Code fragment to be inserted before scanning
	ಅಕ್ಷರ *preaction;	// Code fragment to be inserted before each action
	ಅಕ್ಷರ *postaction;	// Code fragment to be inserted after each action
	ಅಕ್ಷರ *emit;		// Specify target language to emit.
	ಅಕ್ಷರ *yyterminate;	// Set a non-default termination hook.
	bool no_yypanic;	// if true, no not generate default yypanic function
 	// flags corresponding to the huge mass of --no-yy options
	bool no_yy_ತಳ್ಳು_state;
	bool no_yy_ತೆಗೆ_state;
	bool no_yy_ತುದಿ_state;
	bool no_yyunput;
	bool no_yy_ಪರಿಶೀಲನೆ_ಬಫರ್;
	bool no_yy_ಪರಿಶೀಲನೆ_ಬೈಟುಗಳು;
	bool no_yy_ಪರಿಶೀಲನೆ_string;
	bool no_yyget_extra;
	bool no_yyset_extra;
	bool no_yyget_leng;
	bool no_yyget_ಪಠ್ಯ;
	bool no_yyget_lineno;
	bool no_yyset_lineno;
	bool no_yyget_ಸ್ತಂಭ;
	bool no_yyset_ಸ್ತಂಭ;
	bool no_yyget_ಒಳ;
	bool no_yyset_ಒಳ;
	bool no_yyget_ಹೊರಹೋಗು;
	bool no_yyset_ಹೊರಹೋಗು;
	bool no_yyget_lval;
	bool no_yyset_lval;
	bool no_yyget_lloc;
	bool no_yyset_lloc;
	bool no_flex_alloc;
	bool no_flex_realloc;
	bool no_flex_free;
	bool no_get_debug;
	bool no_ಗಣ_debug;
	// Properties read from the skeleton
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *backend_name;	// What the back end tells you its name is
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *traceline_re;	// Regular expression for recognizing tracelines */
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *traceline_template;	// templare for emitting trace lines */
	bool have_state_ನಮೂದು_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
ರಚನೆ env_bundle_t {
	bool backing_ಮೇಲೆ_report;	// (-b flag), generate "lex.backup" file 
				// listing backing-up states
	bool did_outfilename;	// whether outfilename was explicitly set
	ಅಕ್ಷರ *headerfilename;	// name of the .h file to generate
	bool nowarn;		// (-w) do not generate warnings 
	ಪೂರ್ಣಾಂಕ performance_hint;	// if > 0 (i.e., -p flag), generate a report 
				// relating to scanner performance; 
				// if > 1 (-p -p), report 
 				// on minor performance problems, too.
	ಅಕ್ಷರ *outfilename;	// output file name
	bool printstats;	// (-v) dump statistics
	ಅಕ್ಷರ *skelname;		// name of skeleton for code generation
	FILE *skelfile;		// the skeleton file'd descriptor
	bool trace;		// (-T) env.trace processing 
	bool trace_hex; 	// use hex in trace/debug outputs not octal
	bool use_stdout;	// the -t flag
};

/* Name and byte-width information on a type for code-generation purposes. */
ರಚನೆ packtype_t {
	ಅಕ್ಷರ *name;
	size_t ಅಗಲ;
};

ಬಾಹ್ಯ ರಚನೆ ctrl_bundle_t ctrl;
ಬಾಹ್ಯ ರಚನೆ env_bundle_t env;

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
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ yymore_ಬಳಸಿದ, reject, real_reject, continued_action, ಒಳ_ನಿಯಮ;

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

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ datapos, dataline, linenum;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ skel_ind;
ಬಾಹ್ಯ ಅಕ್ಷರ *infilename;
ಬಾಹ್ಯ ಅಕ್ಷರ *extra_type;
ಬಾಹ್ಯ ಅಕ್ಷರ **ಒಳಹರಿವು_files;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ಒಳಹರಿವು_files;
ಬಾಹ್ಯ ಅಕ್ಷರ *ಕಾರ್ಯಕ್ರಮ_name;

ಬಾಹ್ಯ ಅಕ್ಷರ *action_array;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ action_ಗಾತ್ರ;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ defs1_ಸ್ಥಾನಾಂತರ, prolog_ಸ್ಥಾನಾಂತರ, action_ಸ್ಥಾನಾಂತರ, action_ಸೂಚ್ಯಂಕ;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ onestate[ONE_ರಾಶಿ_ಗಾತ್ರ], onesym[ONE_ರಾಶಿ_ಗಾತ್ರ];
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ onenext[ONE_ರಾಶಿ_ಗಾತ್ರ], onedef[ONE_ರಾಶಿ_ಗಾತ್ರ], onesp;


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

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಗರಿಷ್ಠ_mns, current_mns, current_max_ನಿಯಮಗಳು;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ನಿಯಮಗಳು, ಅಂಕೆ_eof_ನಿಯಮಗಳು, default_ನಿಯಮ, lastnfa;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ *accptnum, *assoc_ನಿಯಮ, *state_type;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ *ನಿಯಮ_type, *ನಿಯಮ_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
ಬಾಹ್ಯ ಅಕ್ಷರ *ನಿಯಮ_useful, *ನಿಯಮ_has_nl, *ccl_has_nl;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ nlch;
ಬಾಹ್ಯ size_t footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#ವ್ಯಾಖ್ಯಾನಿಸು STATE_ಸಾಮಾನ್ಯ 0x1
#ವ್ಯಾಖ್ಯಾನಿಸು STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ current_state_type;

/* Different types of rules. */
#ವ್ಯಾಖ್ಯಾನಿಸು ನಿಯಮ_ಸಾಮಾನ್ಯ 0
#ವ್ಯಾಖ್ಯಾನಿಸು ನಿಯಮ_VARIABLE 1

/* True if the input rules include a rule with both variable-length head
 * and trailing context, false otherwise.
 */
ಬಾಹ್ಯ bool variable_trailing_context_ನಿಯಮಗಳು;


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

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_ಗಾತ್ರ];


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
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs;

/* Meta-equivalence classes are indexed starting at 1, so it's possible
 * that they will require positions from 1 .. CSIZE, i.e., CSIZE + 1
 * slots total (since the arrays are 0-based).  nextecm[] and ecgroup[]
 * don't require the extra position since they're indexed from 1 .. CSIZE - 1.
 */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ tecfwd[CSIZE + 1], tecbck[CSIZE + 1];


/* Variables for start conditions:
 * lastsc - last start condition created
 * current_max_scs - current limit on number of start conditions
 * scset - set of rules active in start condition
 * scbol - set of rules active only at the beginning of line in a s.c.
 * scxclu - true if start condition is exclusive
 * sceof - true if start condition has EOF rule
 * scname - start condition name
 */

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
ಬಾಹ್ಯ ಅಕ್ಷರ *scxclu, *sceof;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ current_max_scs;
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **scname;


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

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ current_max_dfa_ಗಾತ್ರ, current_max_xpairs;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ current_max_template_xpairs, current_max_dfas;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ lastdfa, *nxt, *chk, *tnxt;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ *ತಳ, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
ಬಾಹ್ಯ ಒಕ್ಕೂಟ dfaacc_union {
	ಪೂರ್ಣಾಂಕ    *dfaacc_ಗಣ;
	ಪೂರ್ಣಾಂಕ     dfaacc_state;
}      *dfaacc;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ *accsiz, *dhash, numas;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ numsnpairs, jambase, jamstate;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಕೊನೆ_ದ_ಬಫರ್_state;

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

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ lastccl, *cclmap, *ccllen, *cclng, cclreuse;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ current_maxccls, current_max_ccl_tbl_ಗಾತ್ರ;
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ccltbl;


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

ಬಾಹ್ಯ ಅಕ್ಷರ nmstr[MAXLINE];
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ sectnum, nummt, hshcol, dfaeql, numeps, eps2, ಅಂಕೆ_reallocs, nmval;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಅಂಕೆ_backing_ಮೇಲೆ, bol_needed;

ಶೂನ್ಯ   *allocate_array(ಪೂರ್ಣಾಂಕ, size_t);
ಶೂನ್ಯ   *reallocate_array(ಶೂನ್ಯ *, ಪೂರ್ಣಾಂಕ, size_t);

#ವ್ಯಾಖ್ಯಾನಿಸು allocate_integer_array(ಗಾತ್ರ_2) \
	allocate_array(ಗಾತ್ರ_2, ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ))

#ವ್ಯಾಖ್ಯಾನಿಸು reallocate_integer_array(array,ಗಾತ್ರ_2) \
	reallocate_array((ಶೂನ್ಯ *) array, ಗಾತ್ರ_2, ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ))

#ವ್ಯಾಖ್ಯಾನಿಸು allocate_int_ptr_array(ಗಾತ್ರ_2) \
	allocate_array(ಗಾತ್ರ_2, ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ *))

#ವ್ಯಾಖ್ಯಾನಿಸು allocate_char_ptr_array(ಗಾತ್ರ_2) \
	allocate_array(ಗಾತ್ರ_2, ಗಾತ್ರ(ಅಕ್ಷರ *))

#ವ್ಯಾಖ್ಯಾನಿಸು reallocate_int_ptr_array(array,ಗಾತ್ರ_2) \
	reallocate_array((ಶೂನ್ಯ *) array, ಗಾತ್ರ_2, ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ *))

#ವ್ಯಾಖ್ಯಾನಿಸು reallocate_char_ptr_array(array,ಗಾತ್ರ_2) \
	reallocate_array((ಶೂನ್ಯ *) array, ಗಾತ್ರ_2, ಗಾತ್ರ(ಅಕ್ಷರ *))

#ವ್ಯಾಖ್ಯಾನಿಸು allocate_character_array(ಗಾತ್ರ_2) \
	allocate_array( ಗಾತ್ರ_2, ಗಾತ್ರ(ಅಕ್ಷರ))

#ವ್ಯಾಖ್ಯಾನಿಸು reallocate_character_array(array,ಗಾತ್ರ_2) \
	reallocate_array((ಶೂನ್ಯ *) array, ಗಾತ್ರ_2, ಗಾತ್ರ(ಅಕ್ಷರ))

#ವ್ಯಾಖ್ಯಾನಿಸು allocate_Character_array(ಗಾತ್ರ_2) \
	allocate_array(ಗಾತ್ರ_2, ಗಾತ್ರ(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ))

#ವ್ಯಾಖ್ಯಾನಿಸು reallocate_Character_array(array,ಗಾತ್ರ_2) \
	reallocate_array((ಶೂನ್ಯ *) array, ಗಾತ್ರ_2, ಗಾತ್ರ(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

ಬಾಹ್ಯ ಶೂನ್ಯ ccladd(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);	/* add a single character to a ccl */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ cclinit(ಶೂನ್ಯ);	/* make an empty ccl */
ಬಾಹ್ಯ ಶೂನ್ಯ cclnegate(ಪೂರ್ಣಾಂಕ);	/* negate a ccl */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ccl_ಗಣ_diff (ಪೂರ್ಣಾಂಕ a, ಪೂರ್ಣಾಂಕ b); /* set difference of two ccls. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ccl_ಗಣ_union (ಪೂರ್ಣಾಂಕ a, ಪೂರ್ಣಾಂಕ b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
ಬಾಹ್ಯ ಶೂನ್ಯ list_character_ಗಣ(FILE *, ಪೂರ್ಣಾಂಕ[]);


/* from file dfa.c */

/* Increase the maximum number of dfas. */
ಬಾಹ್ಯ ಶೂನ್ಯ increase_max_dfas(ಶೂನ್ಯ);

ಬಾಹ್ಯ size_t ntod(ಶೂನ್ಯ);	/* convert a ndfa to a dfa */


/* from file ecs.c */

/* Convert character classes to set of equivalence classes. */
ಬಾಹ್ಯ ಶೂನ್ಯ ccl2ecl(ಶೂನ್ಯ);

/* Associate equivalence class numbers with class members. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ cre8ecs(ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ);

/* Update equivalence classes based on character class transitions. */
ಬಾಹ್ಯ ಶೂನ್ಯ mkeccl(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ[], ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

/* Create equivalence class for single character. */
ಬಾಹ್ಯ ಶೂನ್ಯ mkechar(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ[]);


/* from file gen.c */

/* Set a conditional amd make it visible in generated code */
ಬಾಹ್ಯ ಶೂನ್ಯ visible_define (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* And again, with an explicit value part. */
ಬಾಹ್ಯ ಶೂನ್ಯ visible_define_str (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* This time the value part is an int */
ಬಾಹ್ಯ ಶೂನ್ಯ visible_define_int (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ);

/* generate transition tables */
ಬಾಹ್ಯ ಶೂನ್ಯ make_tables(ಶೂನ್ಯ);

/* Select a type for optimal packing */
ರಚನೆ packtype_t *optimize_pack(size_t);

/* from file main.c */

ಬಾಹ್ಯ ಶೂನ್ಯ check_options(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ flexend(ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ usage(ಶೂನ್ಯ);


/* from file misc.c */

/* Add the given text to the stored actions. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಕೂಡಿಸು_action(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಪಠ್ಯ);

/* True if a string is all lower case. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ all_ಅಧೋ(ಅಕ್ಷರ *);

/* True if a string is all upper case. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ all_ಊರ್ಧ್ವ(ಅಕ್ಷರ *);

/* Compare two integers for use by qsort. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ intcmp(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *);

/* Check a character to make sure it's in the expected range. */
ಬಾಹ್ಯ ಶೂನ್ಯ check_char(ಪೂರ್ಣಾಂಕ c);

/* Replace upper-case letter to lower-case. */
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ clower(ಪೂರ್ಣಾಂಕ);

/* strdup() that fails fatally on allocation failures. */
ಬಾಹ್ಯ ಅಕ್ಷರ *xstrdup(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* Compare two characters for use by qsort with '\0' sorting last. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ cclcmp(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *);

/* Finish up a block of data declarations. */
ಬಾಹ್ಯ ಶೂನ್ಯ dataend(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* Flush generated data statements. */
ಬಾಹ್ಯ ಶೂನ್ಯ dataflush(ಶೂನ್ಯ);

/* Report an error message and terminate. */
ಬಾಹ್ಯ ಶೂನ್ಯ flexerror(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* Report a fatal error message and terminate. */
ಬಾಹ್ಯ ಶೂನ್ಯ flexfatal(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* Report a fatal error with a pinpoint, and terminate */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_DECL___FUNC__
#ವ್ಯಾಖ್ಯಾನಿಸು flex_die(ಸಂದೇಶ) \
    ಮಾಡು{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                ಕಾರ್ಯಕ್ರಮ_name, __FILE__, (ಪೂರ್ಣಾಂಕ)__LINE__,\
                __func__,ಸಂದೇಶ);\
        FLEX_EXIT(1);\
    }ಆಗ(0)
#ಇಲ್ಲದಿದ್ದರೆ /* ! HAVE_DECL___FUNC__ */
#ವ್ಯಾಖ್ಯಾನಿಸು flex_die(ಸಂದೇಶ) \
    ಮಾಡು{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                ಕಾರ್ಯಕ್ರಮ_name, __FILE__, (ಪೂರ್ಣಾಂಕ)__LINE__,\
                ಸಂದೇಶ);\
        FLEX_EXIT(1);\
    }ಆಗ(0)
#ಆದರೆ_ಅಂತ್ಯ /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
ಬಾಹ್ಯ ಶೂನ್ಯ lerr(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ...)
#ಆದರೆ defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#ಆದರೆ_ಅಂತ್ಯ
;

/* Like lerr, but also exit after displaying message. */
ಬಾಹ್ಯ ಶೂನ್ಯ lerr_fatal(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ...)
#ಆದರೆ defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#ಆದರೆ_ಅಂತ್ಯ
;

/* Spit out a "#line" statement. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಸಾಲು_directive_ಹೊರಹೋಗು(FILE *, ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ);

/* Mark the current position in the action array as the end of the section 1
 * user defs.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ mark_defs1(ಶೂನ್ಯ);

/* Mark the current position in the action array as the end of the prolog. */
ಬಾಹ್ಯ ಶೂನ್ಯ mark_prolog(ಶೂನ್ಯ);

/* Generate a data statement for a two-dimensional array. */
ಬಾಹ್ಯ ಶೂನ್ಯ mk2data(ಪೂರ್ಣಾಂಕ);

ಬಾಹ್ಯ ಶೂನ್ಯ mkdata(ಪೂರ್ಣಾಂಕ);	/* generate a data statement */

/* Return the integer represented by a string of digits. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ myctoi(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* Return character corresponding to escape sequence. */
ಬಾಹ್ಯ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ myesc(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ[]);

/* Output a (possibly-formatted) string to the generated scanner. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಹೊರಹೋಗು(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
ಬಾಹ್ಯ ಶೂನ್ಯ ಹೊರಹೋಗು_dec(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ ಹೊರಹೋಗು_dec2(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ ಹೊರಹೋಗು_hex(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ ಹೊರಹೋಗು_str(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
ಬಾಹ್ಯ ಶೂನ್ಯ ಹೊರಹೋಗು_str_dec(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ outc(ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ outn(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
ಬಾಹ್ಯ ಶೂನ್ಯ ಹೊರಹೋಗು_m4_define(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* def, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
ಬಾಹ್ಯ ಅಕ್ಷರ *readable_form(ಪೂರ್ಣಾಂಕ);

/* Output a yy_trans_info structure. */
ಬಾಹ್ಯ ಶೂನ್ಯ transition_struct_ಹೊರಹೋಗು(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

/* Only needed when using certain broken versions of bison to build parse.c. */
ಬಾಹ್ಯ ಶೂನ್ಯ *yy_flex_xmalloc(ಪೂರ್ಣಾಂಕ);


/* from file nfa.c */

/* Add an accepting state to a machine. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಕೂಡಿಸು_accept(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

/* Make a given number of copies of a singleton machine. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ copysingl(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

/* Debugging routine to write out an nfa. */
ಬಾಹ್ಯ ಶೂನ್ಯ dumpnfa(ಪೂರ್ಣಾಂಕ);

/* Finish up the processing for a rule. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಮುಕ್ತಾಯ_ನಿಯಮ(ಪೂರ್ಣಾಂಕ, bool, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

/* Connect two machines together. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ link_machines(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ mark_beginning_as_ಸಾಮಾನ್ಯ(ಪೂರ್ಣಾಂಕ);

/* Make a machine that branches to two machines. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ mkbranch(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ mkclos(ಪೂರ್ಣಾಂಕ);	/* convert a machine into a closure */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ mkopt(ಪೂರ್ಣಾಂಕ);	/* make a machine optional */

/* Make a machine that matches either one of two machines. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ mkor(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

/* Convert a machine into a positive closure. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ mkposcl(ಪೂರ್ಣಾಂಕ);

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ mkrep(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);	/* make a replicated machine */

/* Create a state with a transition on a given symbol. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ mkstate(ಪೂರ್ಣಾಂಕ);

ಬಾಹ್ಯ ಶೂನ್ಯ new_ನಿಯಮ(ಶೂನ್ಯ);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
ಬಾಹ್ಯ ಶೂನ್ಯ build_eof_action(ಶೂನ್ಯ);

/* Write out a message formatted with one string, pinpointing its location. */
ಬಾಹ್ಯ ಶೂನ್ಯ format_pinpoint_ಸಂದೇಶ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* Write out a message, pinpointing its location. */
ಬಾಹ್ಯ ಶೂನ್ಯ pinpoint_ಸಂದೇಶ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* Write out a warning, pinpointing it at the given line. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಸಾಲು_warning(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ);

/* Write out a message, pinpointing it at the given line. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಸಾಲು_pinpoint(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ);

/* Report a formatted syntax error. */
ಬಾಹ್ಯ ಶೂನ್ಯ format_synerr(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
ಬಾಹ್ಯ ಶೂನ್ಯ synerr(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);	/* report a syntax error */
ಬಾಹ್ಯ ಶೂನ್ಯ format_warn(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
ಬಾಹ್ಯ ಶೂನ್ಯ lwarn(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);	/* report a warning */
ಬಾಹ್ಯ ಶೂನ್ಯ yyerror(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);	/* report a parse error */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ yyparse(ಶೂನ್ಯ);		/* the YACC parser */

/* Ship a comment to the generated output */
ಬಾಹ್ಯ ಶೂನ್ಯ comment(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* from file scan.l */

/* The Flex-generated scanner for flex. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ flexscan(ಶೂನ್ಯ);

/* Open the given file (if NULL, stdin) for scanning. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಗಣ_ಒಳಹರಿವು_file(ಅಕ್ಷರ *);

/* from file skeletons.c */

/* return the correct file suffix for the selected back end */
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *suffix (ಶೂನ್ಯ);

/* Mine a text-valued property out of the skeleton file */
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *skel_property(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* Is the default back end selected?*/
ಬಾಹ್ಯ bool is_default_backend(ಶೂನ್ಯ);

/* Select a backend by name */
ಬಾಹ್ಯ ಶೂನ್ಯ backend_by_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* Write out one section of the skeleton file. */
ಬಾಹ್ಯ ಶೂನ್ಯ skelout(bool);

/* from file sym.c */

/* Save the text of a character class. */
ಬಾಹ್ಯ ಶೂನ್ಯ cclinstal(ಅಕ್ಷರ[], ಪೂರ್ಣಾಂಕ);

/* Lookup the number associated with character class. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ccllookup(ಅಕ್ಷರ[]);

ಬಾಹ್ಯ ಶೂನ್ಯ ndinstal(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಅಕ್ಷರ[]);	/* install a name definition */
ಬಾಹ್ಯ ಅಕ್ಷರ *ndlookup(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);	/* lookup a name definition */

/* Increase maximum number of SC's. */
ಬಾಹ್ಯ ಶೂನ್ಯ scextend(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ scinstal(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, bool);	/* make a start condition */

/* Lookup the number associated with a start condition. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ sclookup(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);

/* Supply context argument for a function if required */
ಬಾಹ್ಯ ಶೂನ್ಯ context_call(ಅಕ್ಷರ *);

/* from file tblcmp.c */

/* Build table entries for dfa state. */
ಬಾಹ್ಯ ಶೂನ್ಯ bldtbl(ಪೂರ್ಣಾಂಕ[], ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

ಬಾಹ್ಯ ಶೂನ್ಯ cmptmps(ಶೂನ್ಯ);	/* compress template table entries */
ಬಾಹ್ಯ ಶೂನ್ಯ expand_nxt_chk(ಶೂನ್ಯ);	/* increase nxt/chk arrays */

/* Finds a space in the table for a state to be placed. */
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ಕಂಡುಹಿಡಿ_ಕೋಷ್ಟಕ_space(ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ);
ಬಾಹ್ಯ ಶೂನ್ಯ inittbl(ಶೂನ್ಯ);	/* initialize transition tables */

/* Make the default, "jam" table entries. */
ಬಾಹ್ಯ ಶೂನ್ಯ mkdeftbl(ಶೂನ್ಯ);

/* Create table entries for a state (or state fragment) which has
 * only one out-transition.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ mk1tbl(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

/* Place a state into full speed transition table. */
ಬಾಹ್ಯ ಶೂನ್ಯ ಇರಿಸು_state(ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);

/* Save states with only one out-transition to be processed later. */
ಬಾಹ್ಯ ಶೂನ್ಯ stack1(ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);


/* from file yylex.c */

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ yylex(ಶೂನ್ಯ);

/* A growable array. See buf.c. */
ರಚನೆ Buf {
	ಶೂನ್ಯ   *elts;		/* elements. */
	ಪೂರ್ಣಾಂಕ     nelts;		/* number of elements. */
	size_t  elt_ಗಾತ್ರ;	/* in bytes. */
	ಪೂರ್ಣಾಂಕ     nmax;		/* max capacity of elements. */
};

ಬಾಹ್ಯ ಶೂನ್ಯ buf_init(ರಚನೆ Buf * buf, size_t elem_ಗಾತ್ರ);
ಬಾಹ್ಯ ಶೂನ್ಯ buf_destroy(ರಚನೆ Buf * buf);
ಬಾಹ್ಯ ರಚನೆ Buf *buf_append(ರಚನೆ Buf * buf, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ptr, ಪೂರ್ಣಾಂಕ n_elem);
ಬಾಹ್ಯ ರಚನೆ Buf *buf_strappend(ರಚನೆ Buf *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str);
ಬಾಹ್ಯ ರಚನೆ Buf *buf_strnappend(ರಚನೆ Buf *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ nchars);
ಬಾಹ್ಯ ರಚನೆ Buf *buf_prints(ರಚನೆ Buf *buf, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* s);

ಬಾಹ್ಯ ರಚನೆ Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
ಬಾಹ್ಯ ರಚನೆ Buf ತುದಿ_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಹೊರಹೋಗು_BEGIN_ಸಂಕೇತ() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#ವ್ಯಾಖ್ಯಾನಿಸು ಹೊರಹೋಗು_ಕೊನೆ_ಸಂಕೇತ()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
ಬಾಹ್ಯ jmp_buf flex_main_jmp_buf;

#ವ್ಯಾಖ್ಯಾನಿಸು FLEX_EXIT(ಸ್ಥಿತಿ_2) longjmp(flex_main_jmp_buf,(ಸ್ಥಿತಿ_2)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
ಬಾಹ್ಯ ಅಕ್ಷರ *chomp (ಅಕ್ಷರ *str);

/* ctype functions forced to return boolean */
#ವ್ಯಾಖ್ಯಾನಿಸು b_isalnum(c) (ಅಕ್ಷರವೇ_ಅಂಕಿಯೇ(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_isalpha(c) (ಅಕ್ಷರವೇ(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_isascii(c) (isascii(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_isblank(c) (isblank(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_iscntrl(c) (iscntrl(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_isdigit(c) (ಅಂಕಿಯೇ(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_isgraph(c) (isgraph(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_islower(c) (islower(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_isprint(c) (isprint(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_ispunct(c) (ispunct(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_isspace(c) (ಖಾಲಿಯೇ(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_isupper(c) (isupper(c)?true:false)
#ವ್ಯಾಖ್ಯಾನಿಸು b_isxdigit(c) (isxdigit(c)?true:false)

/* return true if char is uppercase or lowercase. */
bool has_case(ಪೂರ್ಣಾಂಕ c);

/* Change case of character if possible. */
ಪೂರ್ಣಾಂಕ ಹಿಮ್ಮುಖ_case(ಪೂರ್ಣಾಂಕ c);

/* return false if [c1-c2] is ambiguous for a caseless scanner. */
bool range_covers_case (ಪೂರ್ಣಾಂಕ c1, ಪೂರ್ಣಾಂಕ c2);

/*
 *  From "filter.c"
 */

/** A single stdio filter to execute.
 *  The filter may be external, such as "sed", or it
 *  may be internal, as a function call.
 */
ರಚನೆ filter {
    ಪೂರ್ಣಾಂಕ    (*filter_func)(ರಚನೆ filter*); /**< internal filter function */
    ಶೂನ್ಯ * extra;         /**< extra data passed to filter_func */
	ಪೂರ್ಣಾಂಕ     argc;         /**< arg count */
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ** argv;   /**< arg vector, \0-terminated */
    ರಚನೆ filter * ಮುಂದಿನ; /**< next filter or NULL */
};

/* output filter chain */
ಬಾಹ್ಯ ರಚನೆ filter * output_chain;
ಬಾಹ್ಯ ರಚನೆ filter *filter_create_ext (ರಚನೆ filter * chain, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cmd, ...);
ರಚನೆ filter *filter_create_int(ರಚನೆ filter *chain,
				  ಪೂರ್ಣಾಂಕ (*filter_func) (ರಚನೆ filter *),
                  ಶೂನ್ಯ *extra);
ಬಾಹ್ಯ bool filter_apply_chain(ರಚನೆ filter * chain);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ filter_truncate(ರಚನೆ filter * chain, ಪೂರ್ಣಾಂಕ max_len);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ filter_tee_ಶೀರ್ಷಿಕೆ(ರಚನೆ filter *chain);
ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ filter_fix_linedirs(ರಚನೆ filter *chain);


/*
 * From "regex.c"
 */

ಬಾಹ್ಯ regex_t regex_linedir;
bool flex_init_regex(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
ಶೂನ್ಯ flex_regcomp(regex_t *preg, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *regex, ಪೂರ್ಣಾಂಕ cflags);
ಅಕ್ಷರ   *regmatch_dup (regmatch_t * m, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src);
ಅಕ್ಷರ   *regmatch_cpy (regmatch_t * m, ಅಕ್ಷರ *dest, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src);
ಪೂರ್ಣಾಂಕ regmatch_len (regmatch_t * m);
ಪೂರ್ಣಾಂಕ regmatch_strtol (regmatch_t * m, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src, ಅಕ್ಷರ **endptr, ಪೂರ್ಣಾಂಕ ತಳ);
bool regmatch_ಖಾಲಿಗಳು (regmatch_t * m);

/* From "scanflags.h" */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ scanflags_t;
ಬಾಹ್ಯ scanflags_t* _sf_stk;
ಬಾಹ್ಯ size_t sf_ತುದಿ_ix, _sf_max; /**< stack of scanner flags. */
#ವ್ಯಾಖ್ಯಾನಿಸು _SF_CASE_INS   ((scanflags_t) 0x0001)
#ವ್ಯಾಖ್ಯಾನಿಸು _SF_DOT_ALL    ((scanflags_t) 0x0002)
#ವ್ಯಾಖ್ಯಾನಿಸು _SF_SKIP_WS    ((scanflags_t) 0x0004)
#ವ್ಯಾಖ್ಯಾನಿಸು sf_ತುದಿ()           (_sf_stk[sf_ತುದಿ_ix])
#ವ್ಯಾಖ್ಯಾನಿಸು sf_case_ins()      (sf_ತುದಿ() & _SF_CASE_INS)
#ವ್ಯಾಖ್ಯಾನಿಸು sf_dot_all()       (sf_ತುದಿ() & _SF_DOT_ALL)
#ವ್ಯಾಖ್ಯಾನಿಸು sf_skip_ws()       (sf_ತುದಿ() & _SF_SKIP_WS)
#ವ್ಯಾಖ್ಯಾನಿಸು sf_ಗಣ_case_ins(X)      ((X) ? (sf_ತುದಿ() |= _SF_CASE_INS) : (sf_ತುದಿ() &= ~_SF_CASE_INS))
#ವ್ಯಾಖ್ಯಾನಿಸು sf_ಗಣ_dot_all(X)       ((X) ? (sf_ತುದಿ() |= _SF_DOT_ALL)  : (sf_ತುದಿ() &= ~_SF_DOT_ALL))
#ವ್ಯಾಖ್ಯಾನಿಸು sf_ಗಣ_skip_ws(X)       ((X) ? (sf_ತುದಿ() |= _SF_SKIP_WS)  : (sf_ತುದಿ() &= ~_SF_SKIP_WS))
ಬಾಹ್ಯ ಶೂನ್ಯ sf_init(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ sf_ತಳ್ಳು(ಶೂನ್ಯ);
ಬಾಹ್ಯ ಶೂನ್ಯ sf_ತೆಗೆ(ಶೂನ್ಯ);


#ಆದರೆ_ಅಂತ್ಯ /* not defined FLEXDEF_H */
