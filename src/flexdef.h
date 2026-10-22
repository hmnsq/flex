
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ FLEXDEF_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FLEXDEF_H 1

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ USE_CONFIG_FOR_BUILD
# ifdef HAVE_CONFIG_H
#ਅਨ੍ਤਰ੍ਭਾਵ <config.h>
# endif
#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ <config_for_build.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <setjmp.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <ctype.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_ASSERT_H
#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪ੍ਰਤਿਜ੍ਞਾ(Pred)
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LIMITS_H
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਜੇ_ਅੰਤ
/* Required: dup() and dup2() in <unistd.h> */
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_NETINET_ਵਿੱਚ_H
#ਅਨ੍ਤਰ੍ਭਾਵ <netinet/in.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_SYS_PARAMS_H
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/params.h>
#ਜੇ_ਅੰਤ
/* Required: wait() in <sys/wait.h> */
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/wait.h>
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_STDBOOL_H
#ਅਨ੍ਤਰ੍ਭਾਵ <stdbool.h>
#ਜਾਂਜੇ !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# ਨਹੀਂਤਾਂ
#  define bool ਪੂਰਨ
# endif
# define false 0
# define true 1
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#ਅਨ੍ਤਰ੍ਭਾਵ <regex.h>
/* Required: strcasecmp() in <strings.h> */
#ਅਨ੍ਤਰ੍ਭਾਵ <strings.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#ਜੇ defined(ENABLE_NLS) && ENABLE_NLS
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_LOCALE_H
#ਅਨ੍ਤਰ੍ਭਾਵ <locale.h>
#ਜੇ_ਅੰਤ /* HAVE_LOCALE_H */
#ਅਨ੍ਤਰ੍ਭਾਵ "gettext.h"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _(String) gettext (String)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _(STRING) STRING
#ਜੇ_ਅੰਤ /* ENABLE_NLS */

/* Always be prepared to generate an 8-bit scanner. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CSIZE 256

/* Size of input alphabet - should be size of ASCII set. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ DEFAULT_CSIZE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_CSIZE 128
#ਜੇ_ਅੰਤ

/* Maximum line length we'll have to deal with. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAXLINE 2048

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MIN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN(x,y) ((x) < (y) ? (x) : (y))
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MAX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX(x,y) ((x) > (y) ? (x) : (y))
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ABS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ABS(x) ((x) < 0 ? -(x) : (x))
#ਜੇ_ਅੰਤ

/* Whether an integer is a power of two */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ is_power_ਦਾ_2(n) ((n) > 0 && ((n) & ((n) - 1)) == 0)

/* Special chk[] values marking the slots taking by end-of-buffer and action
 * numbers.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EOB_POSITION -1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_POSITION -2

/* Number of data items per line for -f output. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NUMDATAITEMS 10

/* Number of lines of data in -f output before inserting a blank line for
 * readability.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NUMDATALINES 10

/* transition_struct_out() definitions. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANS_STRUCT_PRINT_ਲੰਮਾਈ 14

/* Returns true if an nfa state has an epsilon out-transition slot
 * that can be used.  This definition is currently not used.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans2[state] == NO_TRANSITION && \
	 finalst[state] != state)

/* Returns true if an nfa state has an epsilon out-transition character
 * and both slots are free
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUPER_FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans1[state] == NO_TRANSITION) \

/* Maximum number of NFA states that can comprise a DFA state.  It's real
 * big because if there's a lot of rules, the initial state will have a
 * huge epsilon closure.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INITIAL_MAX_DFA_ਮਾਪ 750
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_DFA_ਮਾਪ_INCREMENT 750


/* A note on the following masks.  They are used to mark accepting numbers
 * as being special.  As such, they implicitly limit the number of accepting
 * numbers (i.e., rules) because if there are too many rules the rule numbers
 * will overload the mask bits.  Fortunately, this limit is \large/ (0x2000 ==
 * 8192) so unlikely to actually cause any problems.  A check is made in
 * new_rule() to ensure that this limit is not reached.
 */

/* Mask to mark a trailing context accepting number. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YY_TRAILING_ਨਕਾਬ 0x2000

/* Mask to mark the accepting number of the "head" of a trailing context
 * rule.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YY_TRAILING_ਸਿਰ_ਨਕਾਬ 0x4000

/* Maximum number of rules, as outlined in the above note. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ਨਿਯਮ (YY_TRAILING_ਨਕਾਬ - 1)


/* NIL must be 0.  If not, its special meaning when making equivalence classes
 * (it marks the representative of a given e.c.) will be unidentifiable.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NIL 0

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ JAM -1			/* to mark a missing DFA transition */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NO_TRANSITION NIL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UNIQUE -1		/* marks a symbol as an e.c. representative */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INFINITE_REPEAT -1		/* for x{5,} constructions */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INITIAL_MAX_CCLS 100	/* max number of unique character classes */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CCLS_INCREMENT 100

/* Size of table holding members of character classes. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INITIAL_MAX_CCL_TBL_ਮਾਪ 500
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CCL_TBL_ਮਾਪ_INCREMENT 250

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INITIAL_MAX_ਨਿਯਮਾਂ 100	/* default maximum number of rules */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ਨਿਯਮਾਂ_INCREMENT 100

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INITIAL_MNS 2000	/* default maximum number of nfa states */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MNS_INCREMENT 1000	/* amount to bump above by if it's not enough */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INITIAL_MAX_DFAS 1000	/* default maximum number of dfa states */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_DFAS_INCREMENT 1000

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ JAMSTATE -32766		/* marks a reference to the state that always jams */

/* Maximum number of NFA states. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵੱਧ_ਤੋਂ_ਵੱਧ_MNS 31999
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵੱਧ_ਤੋਂ_ਵੱਧ_MNS_LONG 1999999999

/* Enough so that if it's subtracted from an NFA state number, the result
 * is guaranteed to be negative.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MARKER_DIFFERENCE (ਵੱਧ_ਤੋਂ_ਵੱਧ_mns+2)

/* Maximum number of nxt/chk pairs for non-templates. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INITIAL_MAX_XPAIRS 2000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_XPAIRS_INCREMENT 2000

/* Maximum number of nxt/chk pairs needed for templates. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INITIAL_MAX_TEMPLATE_XPAIRS 2500
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_TEMPLATE_XPAIRS_INCREMENT 2500

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SYM_EPSILON (CSIZE + 1)	/* to mark transitions on the symbol epsilon */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INITIAL_MAX_SCS 40	/* maximum number of start conditions */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_SCS_INCREMENT 40	/* amount to bump by if it's not enough */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ONE_ਢੇਰ_ਮਾਪ 500	/* stack of states with only one out-transition */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAME_TRANS -1		/* transition is the same as "default" entry for state */

/* The following percentages are used to tune table compression:

 * The percentage the number of out-transitions a state must be of the
 * number of equivalence classes in order to be considered for table
 * compaction by using protos.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PROTO_ਮਾਪ_PERCENTAGE 15

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * that the state's transition table is first compared with a potential
 * template of the most common out-transition instead of with the first
 * proto in the proto queue.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_COM_PERCENTAGE 50

/* The percentage the number of differences between a state's transition
 * table and the proto it was first compared with must be of the total
 * number of out-transitions of the state in order to keep the first
 * proto as a good match and not search any further.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਹਿਲਾ_ਮੇਲ_DIFF_PERCENTAGE 10

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to use the proto as an acceptable close match.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACCEPTABLE_DIFF_PERCENTAGE 50

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * to consider making a template from the state.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEMPLATE_SAME_PERCENTAGE 60

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to create a new proto from the state.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NEW_PROTO_DIFF_PERCENTAGE 20

/* The percentage the total number of out-transitions of a state must be
 * of the number of equivalence classes in order to consider trying to
 * fit the transition table into "holes" inside the nxt/chk table.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INTERIOR_FIT_PERCENTAGE 15

/* Size of region set aside to cache the complete transition table of
 * protos on the proto queue to enable quick comparisons.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PROT_SAVE_ਮਾਪ 2000

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MSP 50			/* maximum number of saved protos (protos on the proto queue) */

/* Maximum number of out-transitions a state can have that we'll rummage
 * around through the interior of the internal fast table looking for a
 * spot for it.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_XTIONS_ਭਰਿਆ_INTERIOR_FIT 4

/* Maximum number of rules which will be reported as being associated
 * with a DFA state.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ASSOC_ਨਿਯਮਾਂ 100

/* Number that, if used to subscript an array, has a good chance of producing
 * an error; should be small enough to fit into a short.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BAD_SUBSCRIPT -32767

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ trit_t {
	trit_unspecified = -1,
	trit_false = 0,
	trit_true = 1,
} trit;

/* Control variables.  These are in a struct to avoid having to replicate definitions
 * twice for each option, instead a single struct can be declared and externed.
 * If it's in this structure, it has a corresponding m4 symbol.
 */
ਬਣਤਰ ctrl_bundle_t {
	bool always_interactive;// always use character-by-character input
	FILE *backing_ਉੱਪਰ_file;	// file to summarize backing-up states to 
	bool bison_bridge_lval;	// (--bison-bridge), bison pure calling convention. 
	bool bison_bridge_lloc;	// (--bison-locations), bison yylloc.
	size_t bufsize;		// input buffer size
	bool C_plus_plus;	// (-+ flag) generate a C++ scanner class 
	ਪੂਰਨ csize;		// size of character set for the scanner 
				// 128 for 7-bit chars and 256 for 8-bit 
	bool ddebug;		// (-d) make a "debug" scanner 
	trit do_main;		// generate main part to make lexer standalone.
	bool do_stdinit;	// whether to initialize yyin/yyout to stdin/stdout
	bool do_yylineno;	// if true, generate code to maintain yylineno 
	bool do_yywrap;		// do yywrap() processing on EOF. 
				// If false, EOF treated as "no more files" 
	bool fullspd;		// (-F flag) use Jacobson method of table representation 
	bool fulltbl;		// (-Cf flag) don't compress the DFA state table 
 	bool gen_ਸਤਰ_dirs;	// (no -L flag) generate #line directives 
	trit interactive;	// (-I) generate an interactive scanner
	bool never_interactive;	// always use buffered input, don't check for tty.
	bool lex_compat;	// (-l), maximize compatibility with AT&T lex 
	bool long_align;	// (-Ca flag), favor long-word alignment for speed 
	bool no_yyinput;	// suppress use of yyinput()
	bool no_unistd;		// suppress inclusion of unistd.h
	bool posix_compat;	// (-X) maximize compatibility with POSIX lex 
	ਅੱਖਰ *ਅਗੇਤਰ;		// prefix for externally visible names, default "yy" 
	trit reject_really_ਵਰਤਿਆ;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool ਢੇਰ_ਵਰਤਿਆ;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	ਅੱਖਰ *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	ਅੱਖਰ *yydecl;		// user-specified prototype for yylex.
	ਪੂਰਨ yylmax;		// Maximum buffer length if %array
	trit yymore_really_ਵਰਤਿਆ;// Force geberation of support code for yymore
	bool yytext_is_array;	// if true (i.e., %array directive), then declare
				// yytext as array instead of a character pointer.
				// Nice and inefficient.
	bool noyyread;		// User supplied a yyread function, don't generate default
	ਅੱਖਰ *userinit;		// Code fragment to be inserted before scanning
	ਅੱਖਰ *preaction;	// Code fragment to be inserted before each action
	ਅੱਖਰ *postaction;	// Code fragment to be inserted after each action
	ਅੱਖਰ *emit;		// Specify target language to emit.
	ਅੱਖਰ *yyterminate;	// Set a non-default termination hook.
	bool no_yypanic;	// if true, no not generate default yypanic function
 	// flags corresponding to the huge mass of --no-yy options
	bool no_yy_ਧੱਕੋ_state;
	bool no_yy_ਕੱਢੋ_state;
	bool no_yy_ਸਿਖਰ_state;
	bool no_yyunput;
	bool no_yy_ਜਾਂਚ_ਬਫਰ;
	bool no_yy_ਜਾਂਚ_ਬਾਈਟਾਂ;
	bool no_yy_ਜਾਂਚ_string;
	bool no_yyget_extra;
	bool no_yyset_extra;
	bool no_yyget_leng;
	bool no_yyget_ਪਾਠ;
	bool no_yyget_lineno;
	bool no_yyset_lineno;
	bool no_yyget_ਕਾਲਮ;
	bool no_yyset_ਕਾਲਮ;
	bool no_yyget_ਵਿੱਚ;
	bool no_yyset_ਵਿੱਚ;
	bool no_yyget_ਬਾਹਰਲਾ;
	bool no_yyset_ਬਾਹਰਲਾ;
	bool no_yyget_lval;
	bool no_yyset_lval;
	bool no_yyget_lloc;
	bool no_yyset_lloc;
	bool no_flex_alloc;
	bool no_flex_realloc;
	bool no_flex_free;
	bool no_get_debug;
	bool no_ਸੈੱਟ_debug;
	// Properties read from the skeleton
	ਅਚਲ ਅੱਖਰ *backend_name;	// What the back end tells you its name is
	ਅਚਲ ਅੱਖਰ *traceline_re;	// Regular expression for recognizing tracelines */
	ਅਚਲ ਅੱਖਰ *traceline_template;	// templare for emitting trace lines */
	bool have_state_ਇੰਦਰਾਜ_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
ਬਣਤਰ env_bundle_t {
	bool backing_ਉੱਪਰ_report;	// (-b flag), generate "lex.backup" file 
				// listing backing-up states
	bool did_outfilename;	// whether outfilename was explicitly set
	ਅੱਖਰ *headerfilename;	// name of the .h file to generate
	bool nowarn;		// (-w) do not generate warnings 
	ਪੂਰਨ performance_hint;	// if > 0 (i.e., -p flag), generate a report 
				// relating to scanner performance; 
				// if > 1 (-p -p), report 
 				// on minor performance problems, too.
	ਅੱਖਰ *outfilename;	// output file name
	bool printstats;	// (-v) dump statistics
	ਅੱਖਰ *skelname;		// name of skeleton for code generation
	FILE *skelfile;		// the skeleton file'd descriptor
	bool trace;		// (-T) env.trace processing 
	bool trace_hex; 	// use hex in trace/debug outputs not octal
	bool use_stdout;	// the -t flag
};

/* Name and byte-width information on a type for code-generation purposes. */
ਬਣਤਰ packtype_t {
	ਅੱਖਰ *name;
	size_t ਚੌੜਾਈ;
};

ਬਾਹਰੀ ਬਣਤਰ ctrl_bundle_t ctrl;
ਬਾਹਰੀ ਬਣਤਰ env_bundle_t env;

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

ਬਾਹਰੀ bool syntaxerror, eofseen;
ਬਾਹਰੀ ਪੂਰਨ yymore_ਵਰਤਿਆ, reject, real_reject, continued_action, ਵਿੱਚ_ਨਿਯਮ;

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

ਬਾਹਰੀ ਪੂਰਨ datapos, dataline, linenum;
ਬਾਹਰੀ ਪੂਰਨ skel_ind;
ਬਾਹਰੀ ਅੱਖਰ *infilename;
ਬਾਹਰੀ ਅੱਖਰ *extra_type;
ਬਾਹਰੀ ਅੱਖਰ **ਨਿਵੇਸ਼_files;
ਬਾਹਰੀ ਪੂਰਨ ਅੰਕ_ਨਿਵੇਸ਼_files;
ਬਾਹਰੀ ਅੱਖਰ *ਪ੍ਰੋਗਰਾਮ_name;

ਬਾਹਰੀ ਅੱਖਰ *action_array;
ਬਾਹਰੀ ਪੂਰਨ action_ਮਾਪ;
ਬਾਹਰੀ ਪੂਰਨ defs1_ਵਿੱਥ, prolog_ਵਿੱਥ, action_ਵਿੱਥ, action_ਸੂਚਕਾਂਕ;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

ਬਾਹਰੀ ਪੂਰਨ onestate[ONE_ਢੇਰ_ਮਾਪ], onesym[ONE_ਢੇਰ_ਮਾਪ];
ਬਾਹਰੀ ਪੂਰਨ onenext[ONE_ਢੇਰ_ਮਾਪ], onedef[ONE_ਢੇਰ_ਮਾਪ], onesp;


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

ਬਾਹਰੀ ਪੂਰਨ ਵੱਧ_ਤੋਂ_ਵੱਧ_mns, current_mns, current_max_ਨਿਯਮਾਂ;
ਬਾਹਰੀ ਪੂਰਨ ਅੰਕ_ਨਿਯਮਾਂ, ਅੰਕ_eof_ਨਿਯਮਾਂ, default_ਨਿਯਮ, lastnfa;
ਬਾਹਰੀ ਪੂਰਨ *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
ਬਾਹਰੀ ਪੂਰਨ *accptnum, *assoc_ਨਿਯਮ, *state_type;
ਬਾਹਰੀ ਪੂਰਨ *ਨਿਯਮ_type, *ਨਿਯਮ_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
ਬਾਹਰੀ ਅੱਖਰ *ਨਿਯਮ_useful, *ਨਿਯਮ_has_nl, *ccl_has_nl;
ਬਾਹਰੀ ਪੂਰਨ nlch;
ਬਾਹਰੀ size_t footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STATE_ਸਾਧਾਰਨ 0x1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

ਬਾਹਰੀ ਪੂਰਨ current_state_type;

/* Different types of rules. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨਿਯਮ_ਸਾਧਾਰਨ 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਨਿਯਮ_VARIABLE 1

/* True if the input rules include a rule with both variable-length head
 * and trailing context, false otherwise.
 */
ਬਾਹਰੀ bool variable_trailing_context_ਨਿਯਮਾਂ;


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

ਬਾਹਰੀ ਪੂਰਨ numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
ਬਾਹਰੀ ਪੂਰਨ protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_ਮਾਪ];


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
ਬਾਹਰੀ ਪੂਰਨ numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs;

/* Meta-equivalence classes are indexed starting at 1, so it's possible
 * that they will require positions from 1 .. CSIZE, i.e., CSIZE + 1
 * slots total (since the arrays are 0-based).  nextecm[] and ecgroup[]
 * don't require the extra position since they're indexed from 1 .. CSIZE - 1.
 */
ਬਾਹਰੀ ਪੂਰਨ tecfwd[CSIZE + 1], tecbck[CSIZE + 1];


/* Variables for start conditions:
 * lastsc - last start condition created
 * current_max_scs - current limit on number of start conditions
 * scset - set of rules active in start condition
 * scbol - set of rules active only at the beginning of line in a s.c.
 * scxclu - true if start condition is exclusive
 * sceof - true if start condition has EOF rule
 * scname - start condition name
 */

ਬਾਹਰੀ ਪੂਰਨ lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
ਬਾਹਰੀ ਅੱਖਰ *scxclu, *sceof;
ਬਾਹਰੀ ਪੂਰਨ current_max_scs;
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ **scname;


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

ਬਾਹਰੀ ਪੂਰਨ current_max_dfa_ਮਾਪ, current_max_xpairs;
ਬਾਹਰੀ ਪੂਰਨ current_max_template_xpairs, current_max_dfas;
ਬਾਹਰੀ ਪੂਰਨ lastdfa, *nxt, *chk, *tnxt;
ਬਾਹਰੀ ਪੂਰਨ *ਅਧਾਰ, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
ਬਾਹਰੀ ਸੰਘ dfaacc_union {
	ਪੂਰਨ    *dfaacc_ਸੈੱਟ;
	ਪੂਰਨ     dfaacc_state;
}      *dfaacc;
ਬਾਹਰੀ ਪੂਰਨ *accsiz, *dhash, numas;
ਬਾਹਰੀ ਪੂਰਨ numsnpairs, jambase, jamstate;
ਬਾਹਰੀ ਪੂਰਨ ਸਿਰਾ_ਦਾ_ਬਫਰ_state;

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

ਬਾਹਰੀ ਪੂਰਨ lastccl, *cclmap, *ccllen, *cclng, cclreuse;
ਬਾਹਰੀ ਪੂਰਨ current_maxccls, current_max_ccl_tbl_ਮਾਪ;
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ccltbl;


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

ਬਾਹਰੀ ਅੱਖਰ nmstr[MAXLINE];
ਬਾਹਰੀ ਪੂਰਨ sectnum, nummt, hshcol, dfaeql, numeps, eps2, ਅੰਕ_reallocs, nmval;
ਬਾਹਰੀ ਪੂਰਨ tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
ਬਾਹਰੀ ਪੂਰਨ ਅੰਕ_backing_ਉੱਪਰ, bol_needed;

ਖਾਲੀ   *allocate_array(ਪੂਰਨ, size_t);
ਖਾਲੀ   *reallocate_array(ਖਾਲੀ *, ਪੂਰਨ, size_t);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ allocate_integer_array(ਮਾਪ) \
	allocate_array(ਮਾਪ, ਆਕਾਰ(ਪੂਰਨ))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ reallocate_integer_array(array,ਮਾਪ) \
	reallocate_array((ਖਾਲੀ *) array, ਮਾਪ, ਆਕਾਰ(ਪੂਰਨ))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ allocate_int_ptr_array(ਮਾਪ) \
	allocate_array(ਮਾਪ, ਆਕਾਰ(ਪੂਰਨ *))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ allocate_char_ptr_array(ਮਾਪ) \
	allocate_array(ਮਾਪ, ਆਕਾਰ(ਅੱਖਰ *))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ reallocate_int_ptr_array(array,ਮਾਪ) \
	reallocate_array((ਖਾਲੀ *) array, ਮਾਪ, ਆਕਾਰ(ਪੂਰਨ *))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ reallocate_char_ptr_array(array,ਮਾਪ) \
	reallocate_array((ਖਾਲੀ *) array, ਮਾਪ, ਆਕਾਰ(ਅੱਖਰ *))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ allocate_character_array(ਮਾਪ) \
	allocate_array( ਮਾਪ, ਆਕਾਰ(ਅੱਖਰ))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ reallocate_character_array(array,ਮਾਪ) \
	reallocate_array((ਖਾਲੀ *) array, ਮਾਪ, ਆਕਾਰ(ਅੱਖਰ))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ allocate_Character_array(ਮਾਪ) \
	allocate_array(ਮਾਪ, ਆਕਾਰ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ reallocate_Character_array(array,ਮਾਪ) \
	reallocate_array((ਖਾਲੀ *) array, ਮਾਪ, ਆਕਾਰ(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

ਬਾਹਰੀ ਖਾਲੀ ccladd(ਪੂਰਨ, ਪੂਰਨ);	/* add a single character to a ccl */
ਬਾਹਰੀ ਪੂਰਨ cclinit(ਖਾਲੀ);	/* make an empty ccl */
ਬਾਹਰੀ ਖਾਲੀ cclnegate(ਪੂਰਨ);	/* negate a ccl */
ਬਾਹਰੀ ਪੂਰਨ ccl_ਸੈੱਟ_diff (ਪੂਰਨ a, ਪੂਰਨ b); /* set difference of two ccls. */
ਬਾਹਰੀ ਪੂਰਨ ccl_ਸੈੱਟ_union (ਪੂਰਨ a, ਪੂਰਨ b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
ਬਾਹਰੀ ਖਾਲੀ list_character_ਸੈੱਟ(FILE *, ਪੂਰਨ[]);


/* from file dfa.c */

/* Increase the maximum number of dfas. */
ਬਾਹਰੀ ਖਾਲੀ increase_max_dfas(ਖਾਲੀ);

ਬਾਹਰੀ size_t ntod(ਖਾਲੀ);	/* convert a ndfa to a dfa */


/* from file ecs.c */

/* Convert character classes to set of equivalence classes. */
ਬਾਹਰੀ ਖਾਲੀ ccl2ecl(ਖਾਲੀ);

/* Associate equivalence class numbers with class members. */
ਬਾਹਰੀ ਪੂਰਨ cre8ecs(ਪੂਰਨ[], ਪੂਰਨ[], ਪੂਰਨ);

/* Update equivalence classes based on character class transitions. */
ਬਾਹਰੀ ਖਾਲੀ mkeccl(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ[], ਪੂਰਨ, ਪੂਰਨ[], ਪੂਰਨ[], ਪੂਰਨ, ਪੂਰਨ);

/* Create equivalence class for single character. */
ਬਾਹਰੀ ਖਾਲੀ mkechar(ਪੂਰਨ, ਪੂਰਨ[], ਪੂਰਨ[]);


/* from file gen.c */

/* Set a conditional amd make it visible in generated code */
ਬਾਹਰੀ ਖਾਲੀ visible_define (ਅਚਲ ਅੱਖਰ *);

/* And again, with an explicit value part. */
ਬਾਹਰੀ ਖਾਲੀ visible_define_str (ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *);

/* This time the value part is an int */
ਬਾਹਰੀ ਖਾਲੀ visible_define_int (ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਪੂਰਨ);

/* generate transition tables */
ਬਾਹਰੀ ਖਾਲੀ make_tables(ਖਾਲੀ);

/* Select a type for optimal packing */
ਬਣਤਰ packtype_t *optimize_pack(size_t);

/* from file main.c */

ਬਾਹਰੀ ਖਾਲੀ check_options(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ flexend(ਪੂਰਨ);
ਬਾਹਰੀ ਖਾਲੀ usage(ਖਾਲੀ);


/* from file misc.c */

/* Add the given text to the stored actions. */
ਬਾਹਰੀ ਖਾਲੀ ਜੋੜੋ_action(ਅਚਲ ਅੱਖਰ *new_ਪਾਠ);

/* True if a string is all lower case. */
ਬਾਹਰੀ ਪੂਰਨ all_ਹੇਠਲਾ(ਅੱਖਰ *);

/* True if a string is all upper case. */
ਬਾਹਰੀ ਪੂਰਨ all_ਉੱਤਲਾ(ਅੱਖਰ *);

/* Compare two integers for use by qsort. */
ਬਾਹਰੀ ਪੂਰਨ intcmp(ਅਚਲ ਖਾਲੀ *, ਅਚਲ ਖਾਲੀ *);

/* Check a character to make sure it's in the expected range. */
ਬਾਹਰੀ ਖਾਲੀ check_char(ਪੂਰਨ c);

/* Replace upper-case letter to lower-case. */
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ clower(ਪੂਰਨ);

/* strdup() that fails fatally on allocation failures. */
ਬਾਹਰੀ ਅੱਖਰ *xstrdup(ਅਚਲ ਅੱਖਰ *);

/* Compare two characters for use by qsort with '\0' sorting last. */
ਬਾਹਰੀ ਪੂਰਨ cclcmp(ਅਚਲ ਖਾਲੀ *, ਅਚਲ ਖਾਲੀ *);

/* Finish up a block of data declarations. */
ਬਾਹਰੀ ਖਾਲੀ dataend(ਅਚਲ ਅੱਖਰ *);

/* Flush generated data statements. */
ਬਾਹਰੀ ਖਾਲੀ dataflush(ਖਾਲੀ);

/* Report an error message and terminate. */
ਬਾਹਰੀ ਖਾਲੀ flexerror(ਅਚਲ ਅੱਖਰ *);

/* Report a fatal error message and terminate. */
ਬਾਹਰੀ ਖਾਲੀ flexfatal(ਅਚਲ ਅੱਖਰ *);

/* Report a fatal error with a pinpoint, and terminate */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_DECL___FUNC__
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ flex_die(ਸੁਨੇਹਾ) \
    ਕਰੋ{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                ਪ੍ਰੋਗਰਾਮ_name, __FILE__, (ਪੂਰਨ)__LINE__,\
                __func__,ਸੁਨੇਹਾ);\
        FLEX_EXIT(1);\
    }ਜਦੋਂ(0)
#ਨਹੀਂਤਾਂ /* ! HAVE_DECL___FUNC__ */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ flex_die(ਸੁਨੇਹਾ) \
    ਕਰੋ{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                ਪ੍ਰੋਗਰਾਮ_name, __FILE__, (ਪੂਰਨ)__LINE__,\
                ਸੁਨੇਹਾ);\
        FLEX_EXIT(1);\
    }ਜਦੋਂ(0)
#ਜੇ_ਅੰਤ /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
ਬਾਹਰੀ ਖਾਲੀ lerr(ਅਚਲ ਅੱਖਰ *, ...)
#ਜੇ defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#ਜੇ_ਅੰਤ
;

/* Like lerr, but also exit after displaying message. */
ਬਾਹਰੀ ਖਾਲੀ lerr_fatal(ਅਚਲ ਅੱਖਰ *, ...)
#ਜੇ defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#ਜੇ_ਅੰਤ
;

/* Spit out a "#line" statement. */
ਬਾਹਰੀ ਖਾਲੀ ਸਤਰ_directive_ਬਾਹਰਲਾ(FILE *, ਅੱਖਰ *, ਪੂਰਨ);

/* Mark the current position in the action array as the end of the section 1
 * user defs.
 */
ਬਾਹਰੀ ਖਾਲੀ mark_defs1(ਖਾਲੀ);

/* Mark the current position in the action array as the end of the prolog. */
ਬਾਹਰੀ ਖਾਲੀ mark_prolog(ਖਾਲੀ);

/* Generate a data statement for a two-dimensional array. */
ਬਾਹਰੀ ਖਾਲੀ mk2data(ਪੂਰਨ);

ਬਾਹਰੀ ਖਾਲੀ mkdata(ਪੂਰਨ);	/* generate a data statement */

/* Return the integer represented by a string of digits. */
ਬਾਹਰੀ ਪੂਰਨ myctoi(ਅਚਲ ਅੱਖਰ *);

/* Return character corresponding to escape sequence. */
ਬਾਹਰੀ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ myesc(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ[]);

/* Output a (possibly-formatted) string to the generated scanner. */
ਬਾਹਰੀ ਖਾਲੀ ਬਾਹਰਲਾ(ਅਚਲ ਅੱਖਰ *);
ਬਾਹਰੀ ਖਾਲੀ ਬਾਹਰਲਾ_dec(ਅਚਲ ਅੱਖਰ *, ਪੂਰਨ);
ਬਾਹਰੀ ਖਾਲੀ ਬਾਹਰਲਾ_dec2(ਅਚਲ ਅੱਖਰ *, ਪੂਰਨ, ਪੂਰਨ);
ਬਾਹਰੀ ਖਾਲੀ ਬਾਹਰਲਾ_hex(ਅਚਲ ਅੱਖਰ *, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ);
ਬਾਹਰੀ ਖਾਲੀ ਬਾਹਰਲਾ_str(ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *);
ਬਾਹਰੀ ਖਾਲੀ ਬਾਹਰਲਾ_str_dec(ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *, ਪੂਰਨ);
ਬਾਹਰੀ ਖਾਲੀ outc(ਪੂਰਨ);
ਬਾਹਰੀ ਖਾਲੀ outn(ਅਚਲ ਅੱਖਰ *);
ਬਾਹਰੀ ਖਾਲੀ ਬਾਹਰਲਾ_m4_define(ਅਚਲ ਅੱਖਰ* def, ਅਚਲ ਅੱਖਰ* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
ਬਾਹਰੀ ਅੱਖਰ *readable_form(ਪੂਰਨ);

/* Output a yy_trans_info structure. */
ਬਾਹਰੀ ਖਾਲੀ transition_struct_ਬਾਹਰਲਾ(ਪੂਰਨ, ਪੂਰਨ);

/* Only needed when using certain broken versions of bison to build parse.c. */
ਬਾਹਰੀ ਖਾਲੀ *yy_flex_xmalloc(ਪੂਰਨ);


/* from file nfa.c */

/* Add an accepting state to a machine. */
ਬਾਹਰੀ ਖਾਲੀ ਜੋੜੋ_accept(ਪੂਰਨ, ਪੂਰਨ);

/* Make a given number of copies of a singleton machine. */
ਬਾਹਰੀ ਪੂਰਨ copysingl(ਪੂਰਨ, ਪੂਰਨ);

/* Debugging routine to write out an nfa. */
ਬਾਹਰੀ ਖਾਲੀ dumpnfa(ਪੂਰਨ);

/* Finish up the processing for a rule. */
ਬਾਹਰੀ ਖਾਲੀ ਅੰਤ_ਨਿਯਮ(ਪੂਰਨ, bool, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ);

/* Connect two machines together. */
ਬਾਹਰੀ ਪੂਰਨ link_machines(ਪੂਰਨ, ਪੂਰਨ);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
ਬਾਹਰੀ ਖਾਲੀ mark_beginning_as_ਸਾਧਾਰਨ(ਪੂਰਨ);

/* Make a machine that branches to two machines. */
ਬਾਹਰੀ ਪੂਰਨ mkbranch(ਪੂਰਨ, ਪੂਰਨ);

ਬਾਹਰੀ ਪੂਰਨ mkclos(ਪੂਰਨ);	/* convert a machine into a closure */
ਬਾਹਰੀ ਪੂਰਨ mkopt(ਪੂਰਨ);	/* make a machine optional */

/* Make a machine that matches either one of two machines. */
ਬਾਹਰੀ ਪੂਰਨ mkor(ਪੂਰਨ, ਪੂਰਨ);

/* Convert a machine into a positive closure. */
ਬਾਹਰੀ ਪੂਰਨ mkposcl(ਪੂਰਨ);

ਬਾਹਰੀ ਪੂਰਨ mkrep(ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ);	/* make a replicated machine */

/* Create a state with a transition on a given symbol. */
ਬਾਹਰੀ ਪੂਰਨ mkstate(ਪੂਰਨ);

ਬਾਹਰੀ ਖਾਲੀ new_ਨਿਯਮ(ਖਾਲੀ);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
ਬਾਹਰੀ ਖਾਲੀ build_eof_action(ਖਾਲੀ);

/* Write out a message formatted with one string, pinpointing its location. */
ਬਾਹਰੀ ਖਾਲੀ format_pinpoint_ਸੁਨੇਹਾ(ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *);

/* Write out a message, pinpointing its location. */
ਬਾਹਰੀ ਖਾਲੀ pinpoint_ਸੁਨੇਹਾ(ਅਚਲ ਅੱਖਰ *);

/* Write out a warning, pinpointing it at the given line. */
ਬਾਹਰੀ ਖਾਲੀ ਸਤਰ_warning(ਅਚਲ ਅੱਖਰ *, ਪੂਰਨ);

/* Write out a message, pinpointing it at the given line. */
ਬਾਹਰੀ ਖਾਲੀ ਸਤਰ_pinpoint(ਅਚਲ ਅੱਖਰ *, ਪੂਰਨ);

/* Report a formatted syntax error. */
ਬਾਹਰੀ ਖਾਲੀ format_synerr(ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *);
ਬਾਹਰੀ ਖਾਲੀ synerr(ਅਚਲ ਅੱਖਰ *);	/* report a syntax error */
ਬਾਹਰੀ ਖਾਲੀ format_warn(ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *);
ਬਾਹਰੀ ਖਾਲੀ lwarn(ਅਚਲ ਅੱਖਰ *);	/* report a warning */
ਬਾਹਰੀ ਖਾਲੀ yyerror(ਅਚਲ ਅੱਖਰ *);	/* report a parse error */
ਬਾਹਰੀ ਪੂਰਨ yyparse(ਖਾਲੀ);		/* the YACC parser */

/* Ship a comment to the generated output */
ਬਾਹਰੀ ਖਾਲੀ comment(ਅਚਲ ਅੱਖਰ *);

/* from file scan.l */

/* The Flex-generated scanner for flex. */
ਬਾਹਰੀ ਪੂਰਨ flexscan(ਖਾਲੀ);

/* Open the given file (if NULL, stdin) for scanning. */
ਬਾਹਰੀ ਖਾਲੀ ਸੈੱਟ_ਨਿਵੇਸ਼_file(ਅੱਖਰ *);

/* from file skeletons.c */

/* return the correct file suffix for the selected back end */
ਅਚਲ ਅੱਖਰ *suffix (ਖਾਲੀ);

/* Mine a text-valued property out of the skeleton file */
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *skel_property(ਅਚਲ ਅੱਖਰ *);

/* Is the default back end selected?*/
ਬਾਹਰੀ bool is_default_backend(ਖਾਲੀ);

/* Select a backend by name */
ਬਾਹਰੀ ਖਾਲੀ backend_by_name(ਅਚਲ ਅੱਖਰ *);

/* Write out one section of the skeleton file. */
ਬਾਹਰੀ ਖਾਲੀ skelout(bool);

/* from file sym.c */

/* Save the text of a character class. */
ਬਾਹਰੀ ਖਾਲੀ cclinstal(ਅੱਖਰ[], ਪੂਰਨ);

/* Lookup the number associated with character class. */
ਬਾਹਰੀ ਪੂਰਨ ccllookup(ਅੱਖਰ[]);

ਬਾਹਰੀ ਖਾਲੀ ndinstal(ਅਚਲ ਅੱਖਰ *, ਅੱਖਰ[]);	/* install a name definition */
ਬਾਹਰੀ ਅੱਖਰ *ndlookup(ਅਚਲ ਅੱਖਰ *);	/* lookup a name definition */

/* Increase maximum number of SC's. */
ਬਾਹਰੀ ਖਾਲੀ scextend(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ scinstal(ਅਚਲ ਅੱਖਰ *, bool);	/* make a start condition */

/* Lookup the number associated with a start condition. */
ਬਾਹਰੀ ਪੂਰਨ sclookup(ਅਚਲ ਅੱਖਰ *);

/* Supply context argument for a function if required */
ਬਾਹਰੀ ਖਾਲੀ context_call(ਅੱਖਰ *);

/* from file tblcmp.c */

/* Build table entries for dfa state. */
ਬਾਹਰੀ ਖਾਲੀ bldtbl(ਪੂਰਨ[], ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ);

ਬਾਹਰੀ ਖਾਲੀ cmptmps(ਖਾਲੀ);	/* compress template table entries */
ਬਾਹਰੀ ਖਾਲੀ expand_nxt_chk(ਖਾਲੀ);	/* increase nxt/chk arrays */

/* Finds a space in the table for a state to be placed. */
ਬਾਹਰੀ ਪੂਰਨ ਲੱਭੋ_ਸਾਰਣੀ_space(ਪੂਰਨ *, ਪੂਰਨ);
ਬਾਹਰੀ ਖਾਲੀ inittbl(ਖਾਲੀ);	/* initialize transition tables */

/* Make the default, "jam" table entries. */
ਬਾਹਰੀ ਖਾਲੀ mkdeftbl(ਖਾਲੀ);

/* Create table entries for a state (or state fragment) which has
 * only one out-transition.
 */
ਬਾਹਰੀ ਖਾਲੀ mk1tbl(ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ);

/* Place a state into full speed transition table. */
ਬਾਹਰੀ ਖਾਲੀ ਰੱਖੋ_state(ਪੂਰਨ *, ਪੂਰਨ, ਪੂਰਨ);

/* Save states with only one out-transition to be processed later. */
ਬਾਹਰੀ ਖਾਲੀ stack1(ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ);


/* from file yylex.c */

ਬਾਹਰੀ ਪੂਰਨ yylex(ਖਾਲੀ);

/* A growable array. See buf.c. */
ਬਣਤਰ Buf {
	ਖਾਲੀ   *elts;		/* elements. */
	ਪੂਰਨ     nelts;		/* number of elements. */
	size_t  elt_ਮਾਪ;	/* in bytes. */
	ਪੂਰਨ     nmax;		/* max capacity of elements. */
};

ਬਾਹਰੀ ਖਾਲੀ buf_init(ਬਣਤਰ Buf * buf, size_t elem_ਮਾਪ);
ਬਾਹਰੀ ਖਾਲੀ buf_destroy(ਬਣਤਰ Buf * buf);
ਬਾਹਰੀ ਬਣਤਰ Buf *buf_append(ਬਣਤਰ Buf * buf, ਅਚਲ ਖਾਲੀ *ptr, ਪੂਰਨ n_elem);
ਬਾਹਰੀ ਬਣਤਰ Buf *buf_strappend(ਬਣਤਰ Buf *, ਅਚਲ ਅੱਖਰ *str);
ਬਾਹਰੀ ਬਣਤਰ Buf *buf_strnappend(ਬਣਤਰ Buf *, ਅਚਲ ਅੱਖਰ *str, ਪੂਰਨ nchars);
ਬਾਹਰੀ ਬਣਤਰ Buf *buf_prints(ਬਣਤਰ Buf *buf, ਅਚਲ ਅੱਖਰ *fmt, ਅਚਲ ਅੱਖਰ* s);

ਬਾਹਰੀ ਬਣਤਰ Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
ਬਾਹਰੀ ਬਣਤਰ Buf ਸਿਖਰ_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਬਾਹਰਲਾ_BEGIN_ਕੋਡ() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਬਾਹਰਲਾ_ਸਿਰਾ_ਕੋਡ()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
ਬਾਹਰੀ jmp_buf flex_main_jmp_buf;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FLEX_EXIT(ਸਥਿਤੀ) longjmp(flex_main_jmp_buf,(ਸਥਿਤੀ)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
ਬਾਹਰੀ ਅੱਖਰ *chomp (ਅੱਖਰ *str);

/* ctype functions forced to return boolean */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_isalnum(c) (ਅੱਖਰ_ਜਾਂ_ਅੰਕ(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_isalpha(c) (ਅੱਖਰ_ਹੈ(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_isascii(c) (isascii(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_isblank(c) (isblank(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_iscntrl(c) (iscntrl(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_isdigit(c) (ਅੰਕ_ਹੈ(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_isgraph(c) (isgraph(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_islower(c) (islower(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_isprint(c) (isprint(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_ispunct(c) (ispunct(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_isspace(c) (ਖਾਲੀ_ਥਾਂ_ਹੈ(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_isupper(c) (isupper(c)?true:false)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ b_isxdigit(c) (isxdigit(c)?true:false)

/* return true if char is uppercase or lowercase. */
bool has_case(ਪੂਰਨ c);

/* Change case of character if possible. */
ਪੂਰਨ ਉਲਟ_case(ਪੂਰਨ c);

/* return false if [c1-c2] is ambiguous for a caseless scanner. */
bool range_covers_case (ਪੂਰਨ c1, ਪੂਰਨ c2);

/*
 *  From "filter.c"
 */

/** A single stdio filter to execute.
 *  The filter may be external, such as "sed", or it
 *  may be internal, as a function call.
 */
ਬਣਤਰ filter {
    ਪੂਰਨ    (*filter_func)(ਬਣਤਰ filter*); /**< internal filter function */
    ਖਾਲੀ * extra;         /**< extra data passed to filter_func */
	ਪੂਰਨ     argc;         /**< arg count */
	ਅਚਲ ਅੱਖਰ ** argv;   /**< arg vector, \0-terminated */
    ਬਣਤਰ filter * ਅਗਲਾ; /**< next filter or NULL */
};

/* output filter chain */
ਬਾਹਰੀ ਬਣਤਰ filter * output_chain;
ਬਾਹਰੀ ਬਣਤਰ filter *filter_create_ext (ਬਣਤਰ filter * chain, ਅਚਲ ਅੱਖਰ *cmd, ...);
ਬਣਤਰ filter *filter_create_int(ਬਣਤਰ filter *chain,
				  ਪੂਰਨ (*filter_func) (ਬਣਤਰ filter *),
                  ਖਾਲੀ *extra);
ਬਾਹਰੀ bool filter_apply_chain(ਬਣਤਰ filter * chain);
ਬਾਹਰੀ ਪੂਰਨ filter_truncate(ਬਣਤਰ filter * chain, ਪੂਰਨ max_len);
ਬਾਹਰੀ ਪੂਰਨ filter_tee_ਸਿਰਲੇਖ(ਬਣਤਰ filter *chain);
ਬਾਹਰੀ ਪੂਰਨ filter_fix_linedirs(ਬਣਤਰ filter *chain);


/*
 * From "regex.c"
 */

ਬਾਹਰੀ regex_t regex_linedir;
bool flex_init_regex(ਅਚਲ ਅੱਖਰ *);
ਖਾਲੀ flex_regcomp(regex_t *preg, ਅਚਲ ਅੱਖਰ *regex, ਪੂਰਨ cflags);
ਅੱਖਰ   *regmatch_dup (regmatch_t * m, ਅਚਲ ਅੱਖਰ *src);
ਅੱਖਰ   *regmatch_cpy (regmatch_t * m, ਅੱਖਰ *dest, ਅਚਲ ਅੱਖਰ *src);
ਪੂਰਨ regmatch_len (regmatch_t * m);
ਪੂਰਨ regmatch_strtol (regmatch_t * m, ਅਚਲ ਅੱਖਰ *src, ਅੱਖਰ **endptr, ਪੂਰਨ ਅਧਾਰ);
bool regmatch_ਖਾਲੀ_ਥਾਵਾਂ (regmatch_t * m);

/* From "scanflags.h" */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ scanflags_t;
ਬਾਹਰੀ scanflags_t* _sf_stk;
ਬਾਹਰੀ size_t sf_ਸਿਖਰ_ix, _sf_max; /**< stack of scanner flags. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _SF_CASE_INS   ((scanflags_t) 0x0001)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _SF_DOT_ALL    ((scanflags_t) 0x0002)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ _SF_SKIP_WS    ((scanflags_t) 0x0004)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sf_ਸਿਖਰ()           (_sf_stk[sf_ਸਿਖਰ_ix])
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sf_case_ins()      (sf_ਸਿਖਰ() & _SF_CASE_INS)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sf_dot_all()       (sf_ਸਿਖਰ() & _SF_DOT_ALL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sf_skip_ws()       (sf_ਸਿਖਰ() & _SF_SKIP_WS)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sf_ਸੈੱਟ_case_ins(X)      ((X) ? (sf_ਸਿਖਰ() |= _SF_CASE_INS) : (sf_ਸਿਖਰ() &= ~_SF_CASE_INS))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sf_ਸੈੱਟ_dot_all(X)       ((X) ? (sf_ਸਿਖਰ() |= _SF_DOT_ALL)  : (sf_ਸਿਖਰ() &= ~_SF_DOT_ALL))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ sf_ਸੈੱਟ_skip_ws(X)       ((X) ? (sf_ਸਿਖਰ() |= _SF_SKIP_WS)  : (sf_ਸਿਖਰ() &= ~_SF_SKIP_WS))
ਬਾਹਰੀ ਖਾਲੀ sf_init(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ sf_ਧੱਕੋ(ਖਾਲੀ);
ਬਾਹਰੀ ਖਾਲੀ sf_ਕੱਢੋ(ਖਾਲੀ);


#ਜੇ_ਅੰਤ /* not defined FLEXDEF_H */
