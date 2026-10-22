
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

#اگر_تعریف_نشده FLEXDEF_H
#تعریف_کن FLEXDEF_H 1

#اگر_تعریف_نشده USE_CONFIG_FOR_BUILD
# ifdef HAVE_CONFIG_H
#ضمن <config.h>
# endif
#وإلا
#ضمن <config_for_build.h>
#پایان_اگر

#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <stdarg.h>
#ضمن <setjmp.h>
#ضمن <ctype.h>
#ضمن <string.h>
#ضمن <math.h>

#اگر_تعریف_شده HAVE_ASSERT_H
#ضمن <assert.h>
#وإلا
#تعریف_کن أكد(Pred)
#پایان_اگر

#اگر_تعریف_شده HAVE_LIMITS_H
#ضمن <limits.h>
#پایان_اگر
/* Required: dup() and dup2() in <unistd.h> */
#ضمن <unistd.h>
#اگر_تعریف_شده HAVE_NETINET_درون_H
#ضمن <netinet/in.h>
#پایان_اگر
#اگر_تعریف_شده HAVE_SYS_PARAMS_H
#ضمن <sys/params.h>
#پایان_اگر
/* Required: wait() in <sys/wait.h> */
#ضمن <sys/wait.h>
#اگر_تعریف_شده HAVE_STDBOOL_H
#ضمن <stdbool.h>
#وإلاإذا !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# وإلا
#  define bool صحيح
# endif
# define false 0
# define true 1
#پایان_اگر
#ضمن <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#ضمن <regex.h>
/* Required: strcasecmp() in <strings.h> */
#ضمن <strings.h>
#ضمن "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#إذا defined(ENABLE_NLS) && ENABLE_NLS
#اگر_تعریف_شده HAVE_LOCALE_H
#ضمن <locale.h>
#پایان_اگر /* HAVE_LOCALE_H */
#ضمن "gettext.h"
#تعریف_کن _(String) gettext (String)
#وإلا
#تعریف_کن _(STRING) STRING
#پایان_اگر /* ENABLE_NLS */

/* Always be prepared to generate an 8-bit scanner. */
#تعریف_کن CSIZE 256

/* Size of input alphabet - should be size of ASCII set. */
#اگر_تعریف_نشده DEFAULT_CSIZE
#تعریف_کن DEFAULT_CSIZE 128
#پایان_اگر

/* Maximum line length we'll have to deal with. */
#تعریف_کن MAXLINE 2048

#اگر_تعریف_نشده MIN
#تعریف_کن MIN(x,y) ((x) < (y) ? (x) : (y))
#پایان_اگر
#اگر_تعریف_نشده MAX
#تعریف_کن MAX(x,y) ((x) > (y) ? (x) : (y))
#پایان_اگر
#اگر_تعریف_نشده ABS
#تعریف_کن ABS(x) ((x) < 0 ? -(x) : (x))
#پایان_اگر

/* Whether an integer is a power of two */
#تعریف_کن is_power_از_2(n) ((n) > 0 && ((n) & ((n) - 1)) == 0)

/* Special chk[] values marking the slots taking by end-of-buffer and action
 * numbers.
 */
#تعریف_کن EOB_POSITION -1
#تعریف_کن ACTION_POSITION -2

/* Number of data items per line for -f output. */
#تعریف_کن NUMDATAITEMS 10

/* Number of lines of data in -f output before inserting a blank line for
 * readability.
 */
#تعریف_کن NUMDATALINES 10

/* transition_struct_out() definitions. */
#تعریف_کن TRANS_STRUCT_PRINT_درازی 14

/* Returns true if an nfa state has an epsilon out-transition slot
 * that can be used.  This definition is currently not used.
 */
#تعریف_کن FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans2[state] == NO_TRANSITION && \
	 finalst[state] != state)

/* Returns true if an nfa state has an epsilon out-transition character
 * and both slots are free
 */
#تعریف_کن SUPER_FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans1[state] == NO_TRANSITION) \

/* Maximum number of NFA states that can comprise a DFA state.  It's real
 * big because if there's a lot of rules, the initial state will have a
 * huge epsilon closure.
 */
#تعریف_کن INITIAL_MAX_DFA_اندازه 750
#تعریف_کن MAX_DFA_اندازه_INCREMENT 750


/* A note on the following masks.  They are used to mark accepting numbers
 * as being special.  As such, they implicitly limit the number of accepting
 * numbers (i.e., rules) because if there are too many rules the rule numbers
 * will overload the mask bits.  Fortunately, this limit is \large/ (0x2000 ==
 * 8192) so unlikely to actually cause any problems.  A check is made in
 * new_rule() to ensure that this limit is not reached.
 */

/* Mask to mark a trailing context accepting number. */
#تعریف_کن YY_TRAILING_ماسک 0x2000

/* Mask to mark the accepting number of the "head" of a trailing context
 * rule.
 */
#تعریف_کن YY_TRAILING_سر_ماسک 0x4000

/* Maximum number of rules, as outlined in the above note. */
#تعریف_کن MAX_قاعده (YY_TRAILING_ماسک - 1)


/* NIL must be 0.  If not, its special meaning when making equivalence classes
 * (it marks the representative of a given e.c.) will be unidentifiable.
 */
#تعریف_کن NIL 0

#تعریف_کن JAM -1			/* to mark a missing DFA transition */
#تعریف_کن NO_TRANSITION NIL
#تعریف_کن UNIQUE -1		/* marks a symbol as an e.c. representative */
#تعریف_کن INFINITE_REPEAT -1		/* for x{5,} constructions */

#تعریف_کن INITIAL_MAX_CCLS 100	/* max number of unique character classes */
#تعریف_کن MAX_CCLS_INCREMENT 100

/* Size of table holding members of character classes. */
#تعریف_کن INITIAL_MAX_CCL_TBL_اندازه 500
#تعریف_کن MAX_CCL_TBL_اندازه_INCREMENT 250

#تعریف_کن INITIAL_MAX_قواعد 100	/* default maximum number of rules */
#تعریف_کن MAX_قواعد_INCREMENT 100

#تعریف_کن INITIAL_MNS 2000	/* default maximum number of nfa states */
#تعریف_کن MNS_INCREMENT 1000	/* amount to bump above by if it's not enough */

#تعریف_کن INITIAL_MAX_DFAS 1000	/* default maximum number of dfa states */
#تعریف_کن MAX_DFAS_INCREMENT 1000

#تعریف_کن JAMSTATE -32766		/* marks a reference to the state that always jams */

/* Maximum number of NFA states. */
#تعریف_کن بیشینه_MNS 31999
#تعریف_کن بیشینه_MNS_LONG 1999999999

/* Enough so that if it's subtracted from an NFA state number, the result
 * is guaranteed to be negative.
 */
#تعریف_کن MARKER_DIFFERENCE (بیشینه_mns+2)

/* Maximum number of nxt/chk pairs for non-templates. */
#تعریف_کن INITIAL_MAX_XPAIRS 2000
#تعریف_کن MAX_XPAIRS_INCREMENT 2000

/* Maximum number of nxt/chk pairs needed for templates. */
#تعریف_کن INITIAL_MAX_TEMPLATE_XPAIRS 2500
#تعریف_کن MAX_TEMPLATE_XPAIRS_INCREMENT 2500

#تعریف_کن SYM_EPSILON (CSIZE + 1)	/* to mark transitions on the symbol epsilon */

#تعریف_کن INITIAL_MAX_SCS 40	/* maximum number of start conditions */
#تعریف_کن MAX_SCS_INCREMENT 40	/* amount to bump by if it's not enough */

#تعریف_کن ONE_پشته_اندازه 500	/* stack of states with only one out-transition */
#تعریف_کن SAME_TRANS -1		/* transition is the same as "default" entry for state */

/* The following percentages are used to tune table compression:

 * The percentage the number of out-transitions a state must be of the
 * number of equivalence classes in order to be considered for table
 * compaction by using protos.
 */
#تعریف_کن PROTO_اندازه_PERCENTAGE 15

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * that the state's transition table is first compared with a potential
 * template of the most common out-transition instead of with the first
 * proto in the proto queue.
 */
#تعریف_کن CHECK_COM_PERCENTAGE 50

/* The percentage the number of differences between a state's transition
 * table and the proto it was first compared with must be of the total
 * number of out-transitions of the state in order to keep the first
 * proto as a good match and not search any further.
 */
#تعریف_کن اولی_تطابق_DIFF_PERCENTAGE 10

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to use the proto as an acceptable close match.
 */
#تعریف_کن ACCEPTABLE_DIFF_PERCENTAGE 50

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * to consider making a template from the state.
 */
#تعریف_کن TEMPLATE_SAME_PERCENTAGE 60

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to create a new proto from the state.
 */
#تعریف_کن NEW_PROTO_DIFF_PERCENTAGE 20

/* The percentage the total number of out-transitions of a state must be
 * of the number of equivalence classes in order to consider trying to
 * fit the transition table into "holes" inside the nxt/chk table.
 */
#تعریف_کن INTERIOR_FIT_PERCENTAGE 15

/* Size of region set aside to cache the complete transition table of
 * protos on the proto queue to enable quick comparisons.
 */
#تعریف_کن PROT_SAVE_اندازه 2000

#تعریف_کن MSP 50			/* maximum number of saved protos (protos on the proto queue) */

/* Maximum number of out-transitions a state can have that we'll rummage
 * around through the interior of the internal fast table looking for a
 * spot for it.
 */
#تعریف_کن MAX_XTIONS_پر_INTERIOR_FIT 4

/* Maximum number of rules which will be reported as being associated
 * with a DFA state.
 */
#تعریف_کن MAX_ASSOC_قواعد 100

/* Number that, if used to subscript an array, has a good chance of producing
 * an error; should be small enough to fit into a short.
 */
#تعریف_کن BAD_SUBSCRIPT -32767

تعريفنوع تعداد trit_t {
	trit_unspecified = -1,
	trit_false = 0,
	trit_true = 1,
} trit;

/* Control variables.  These are in a struct to avoid having to replicate definitions
 * twice for each option, instead a single struct can be declared and externed.
 * If it's in this structure, it has a corresponding m4 symbol.
 */
بنية ctrl_bundle_t {
	bool always_interactive;// always use character-by-character input
	FILE *backing_به_بالا_file;	// file to summarize backing-up states to 
	bool bison_bridge_lval;	// (--bison-bridge), bison pure calling convention. 
	bool bison_bridge_lloc;	// (--bison-locations), bison yylloc.
	size_t bufsize;		// input buffer size
	bool C_plus_plus;	// (-+ flag) generate a C++ scanner class 
	صحيح csize;		// size of character set for the scanner 
				// 128 for 7-bit chars and 256 for 8-bit 
	bool ddebug;		// (-d) make a "debug" scanner 
	trit do_main;		// generate main part to make lexer standalone.
	bool do_stdinit;	// whether to initialize yyin/yyout to stdin/stdout
	bool do_yylineno;	// if true, generate code to maintain yylineno 
	bool do_yywrap;		// do yywrap() processing on EOF. 
				// If false, EOF treated as "no more files" 
	bool fullspd;		// (-F flag) use Jacobson method of table representation 
	bool fulltbl;		// (-Cf flag) don't compress the DFA state table 
 	bool gen_سطر_dirs;	// (no -L flag) generate #line directives 
	trit interactive;	// (-I) generate an interactive scanner
	bool never_interactive;	// always use buffered input, don't check for tty.
	bool lex_compat;	// (-l), maximize compatibility with AT&T lex 
	bool long_align;	// (-Ca flag), favor long-word alignment for speed 
	bool no_yyinput;	// suppress use of yyinput()
	bool no_unistd;		// suppress inclusion of unistd.h
	bool posix_compat;	// (-X) maximize compatibility with POSIX lex 
	حرف *پیشوند;		// prefix for externally visible names, default "yy" 
	trit reject_really_استفاده_شده;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool پشته_استفاده_شده;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	حرف *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	حرف *yydecl;		// user-specified prototype for yylex.
	صحيح yylmax;		// Maximum buffer length if %array
	trit yymore_really_استفاده_شده;// Force geberation of support code for yymore
	bool yytext_is_array;	// if true (i.e., %array directive), then declare
				// yytext as array instead of a character pointer.
				// Nice and inefficient.
	bool noyyread;		// User supplied a yyread function, don't generate default
	حرف *userinit;		// Code fragment to be inserted before scanning
	حرف *preaction;	// Code fragment to be inserted before each action
	حرف *postaction;	// Code fragment to be inserted after each action
	حرف *emit;		// Specify target language to emit.
	حرف *yyterminate;	// Set a non-default termination hook.
	bool no_yypanic;	// if true, no not generate default yypanic function
 	// flags corresponding to the huge mass of --no-yy options
	bool no_yy_افزودن_state;
	bool no_yy_برداشت_state;
	bool no_yy_بالاترین_state;
	bool no_yyunput;
	bool no_yy_پیمایش_میانگیر;
	bool no_yy_پیمایش_بایتها;
	bool no_yy_پیمایش_string;
	bool no_yyget_extra;
	bool no_yyset_extra;
	bool no_yyget_leng;
	bool no_yyget_متن;
	bool no_yyget_lineno;
	bool no_yyset_lineno;
	bool no_yyget_ستونی;
	bool no_yyset_ستونی;
	bool no_yyget_درون;
	bool no_yyset_درون;
	bool no_yyget_بیرون;
	bool no_yyset_بیرون;
	bool no_yyget_lval;
	bool no_yyset_lval;
	bool no_yyget_lloc;
	bool no_yyset_lloc;
	bool no_flex_alloc;
	bool no_flex_realloc;
	bool no_flex_free;
	bool no_get_debug;
	bool no_مجموعه_debug;
	// Properties read from the skeleton
	ثابت حرف *backend_name;	// What the back end tells you its name is
	ثابت حرف *traceline_re;	// Regular expression for recognizing tracelines */
	ثابت حرف *traceline_template;	// templare for emitting trace lines */
	bool have_state_مدخل_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
بنية env_bundle_t {
	bool backing_به_بالا_report;	// (-b flag), generate "lex.backup" file 
				// listing backing-up states
	bool did_outfilename;	// whether outfilename was explicitly set
	حرف *headerfilename;	// name of the .h file to generate
	bool nowarn;		// (-w) do not generate warnings 
	صحيح performance_hint;	// if > 0 (i.e., -p flag), generate a report 
				// relating to scanner performance; 
				// if > 1 (-p -p), report 
 				// on minor performance problems, too.
	حرف *outfilename;	// output file name
	bool printstats;	// (-v) dump statistics
	حرف *skelname;		// name of skeleton for code generation
	FILE *skelfile;		// the skeleton file'd descriptor
	bool trace;		// (-T) env.trace processing 
	bool trace_hex; 	// use hex in trace/debug outputs not octal
	bool use_stdout;	// the -t flag
};

/* Name and byte-width information on a type for code-generation purposes. */
بنية packtype_t {
	حرف *name;
	size_t عرض;
};

خارجي بنية ctrl_bundle_t ctrl;
خارجي بنية env_bundle_t env;

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

خارجي bool syntaxerror, eofseen;
خارجي صحيح yymore_استفاده_شده, reject, real_reject, continued_action, درون_قاعده;

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

خارجي صحيح datapos, dataline, linenum;
خارجي صحيح skel_ind;
خارجي حرف *infilename;
خارجي حرف *extra_type;
خارجي حرف **درون_داد_files;
خارجي صحيح رقم_درون_داد_files;
خارجي حرف *برنامه_name;

خارجي حرف *action_array;
خارجي صحيح action_اندازه;
خارجي صحيح defs1_جابه_جایی, prolog_جابه_جایی, action_جابه_جایی, action_شاخص;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

خارجي صحيح onestate[ONE_پشته_اندازه], onesym[ONE_پشته_اندازه];
خارجي صحيح onenext[ONE_پشته_اندازه], onedef[ONE_پشته_اندازه], onesp;


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

خارجي صحيح بیشینه_mns, current_mns, current_max_قواعد;
خارجي صحيح رقم_قواعد, رقم_eof_قواعد, default_قاعده, lastnfa;
خارجي صحيح *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
خارجي صحيح *accptnum, *assoc_قاعده, *state_type;
خارجي صحيح *قاعده_type, *قاعده_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
خارجي حرف *قاعده_useful, *قاعده_has_nl, *ccl_has_nl;
خارجي صحيح nlch;
خارجي size_t footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#تعریف_کن STATE_نرمال 0x1
#تعریف_کن STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

خارجي صحيح current_state_type;

/* Different types of rules. */
#تعریف_کن قاعده_نرمال 0
#تعریف_کن قاعده_VARIABLE 1

/* True if the input rules include a rule with both variable-length head
 * and trailing context, false otherwise.
 */
خارجي bool variable_trailing_context_قواعد;


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

خارجي صحيح numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
خارجي صحيح protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_اندازه];


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
خارجي صحيح numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs;

/* Meta-equivalence classes are indexed starting at 1, so it's possible
 * that they will require positions from 1 .. CSIZE, i.e., CSIZE + 1
 * slots total (since the arrays are 0-based).  nextecm[] and ecgroup[]
 * don't require the extra position since they're indexed from 1 .. CSIZE - 1.
 */
خارجي صحيح tecfwd[CSIZE + 1], tecbck[CSIZE + 1];


/* Variables for start conditions:
 * lastsc - last start condition created
 * current_max_scs - current limit on number of start conditions
 * scset - set of rules active in start condition
 * scbol - set of rules active only at the beginning of line in a s.c.
 * scxclu - true if start condition is exclusive
 * sceof - true if start condition has EOF rule
 * scname - start condition name
 */

خارجي صحيح lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
خارجي حرف *scxclu, *sceof;
خارجي صحيح current_max_scs;
خارجي ثابت حرف **scname;


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

خارجي صحيح current_max_dfa_اندازه, current_max_xpairs;
خارجي صحيح current_max_template_xpairs, current_max_dfas;
خارجي صحيح lastdfa, *nxt, *chk, *tnxt;
خارجي صحيح *پایه, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
خارجي اتحاد dfaacc_union {
	صحيح    *dfaacc_مجموعه;
	صحيح     dfaacc_state;
}      *dfaacc;
خارجي صحيح *accsiz, *dhash, numas;
خارجي صحيح numsnpairs, jambase, jamstate;
خارجي صحيح انتها_از_میانگیر_state;

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

خارجي صحيح lastccl, *cclmap, *ccllen, *cclng, cclreuse;
خارجي صحيح current_maxccls, current_max_ccl_tbl_اندازه;
خارجي بیعلامت حرف *ccltbl;


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

خارجي حرف nmstr[MAXLINE];
خارجي صحيح sectnum, nummt, hshcol, dfaeql, numeps, eps2, رقم_reallocs, nmval;
خارجي صحيح tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
خارجي صحيح رقم_backing_به_بالا, bol_needed;

فراغ   *allocate_array(صحيح, size_t);
فراغ   *reallocate_array(فراغ *, صحيح, size_t);

#تعریف_کن allocate_integer_array(اندازه) \
	allocate_array(اندازه, حجم(صحيح))

#تعریف_کن reallocate_integer_array(array,اندازه) \
	reallocate_array((فراغ *) array, اندازه, حجم(صحيح))

#تعریف_کن allocate_int_ptr_array(اندازه) \
	allocate_array(اندازه, حجم(صحيح *))

#تعریف_کن allocate_char_ptr_array(اندازه) \
	allocate_array(اندازه, حجم(حرف *))

#تعریف_کن reallocate_int_ptr_array(array,اندازه) \
	reallocate_array((فراغ *) array, اندازه, حجم(صحيح *))

#تعریف_کن reallocate_char_ptr_array(array,اندازه) \
	reallocate_array((فراغ *) array, اندازه, حجم(حرف *))

#تعریف_کن allocate_character_array(اندازه) \
	allocate_array( اندازه, حجم(حرف))

#تعریف_کن reallocate_character_array(array,اندازه) \
	reallocate_array((فراغ *) array, اندازه, حجم(حرف))

#تعریف_کن allocate_Character_array(اندازه) \
	allocate_array(اندازه, حجم(بیعلامت حرف))

#تعریف_کن reallocate_Character_array(array,اندازه) \
	reallocate_array((فراغ *) array, اندازه, حجم(بیعلامت حرف))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

خارجي فراغ ccladd(صحيح, صحيح);	/* add a single character to a ccl */
خارجي صحيح cclinit(فراغ);	/* make an empty ccl */
خارجي فراغ cclnegate(صحيح);	/* negate a ccl */
خارجي صحيح ccl_مجموعه_diff (صحيح a, صحيح b); /* set difference of two ccls. */
خارجي صحيح ccl_مجموعه_union (صحيح a, صحيح b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
خارجي فراغ list_character_مجموعه(FILE *, صحيح[]);


/* from file dfa.c */

/* Increase the maximum number of dfas. */
خارجي فراغ increase_max_dfas(فراغ);

خارجي size_t ntod(فراغ);	/* convert a ndfa to a dfa */


/* from file ecs.c */

/* Convert character classes to set of equivalence classes. */
خارجي فراغ ccl2ecl(فراغ);

/* Associate equivalence class numbers with class members. */
خارجي صحيح cre8ecs(صحيح[], صحيح[], صحيح);

/* Update equivalence classes based on character class transitions. */
خارجي فراغ mkeccl(بیعلامت حرف[], صحيح, صحيح[], صحيح[], صحيح, صحيح);

/* Create equivalence class for single character. */
خارجي فراغ mkechar(صحيح, صحيح[], صحيح[]);


/* from file gen.c */

/* Set a conditional amd make it visible in generated code */
خارجي فراغ visible_define (ثابت حرف *);

/* And again, with an explicit value part. */
خارجي فراغ visible_define_str (ثابت حرف *, ثابت حرف *);

/* This time the value part is an int */
خارجي فراغ visible_define_int (ثابت حرف *, ثابت صحيح);

/* generate transition tables */
خارجي فراغ make_tables(فراغ);

/* Select a type for optimal packing */
بنية packtype_t *optimize_pack(size_t);

/* from file main.c */

خارجي فراغ check_options(فراغ);
خارجي فراغ flexend(صحيح);
خارجي فراغ usage(فراغ);


/* from file misc.c */

/* Add the given text to the stored actions. */
خارجي فراغ جمع_کن_action(ثابت حرف *new_متن);

/* True if a string is all lower case. */
خارجي صحيح all_پایینی(حرف *);

/* True if a string is all upper case. */
خارجي صحيح all_فوقانی(حرف *);

/* Compare two integers for use by qsort. */
خارجي صحيح intcmp(ثابت فراغ *, ثابت فراغ *);

/* Check a character to make sure it's in the expected range. */
خارجي فراغ check_char(صحيح c);

/* Replace upper-case letter to lower-case. */
خارجي بیعلامت حرف clower(صحيح);

/* strdup() that fails fatally on allocation failures. */
خارجي حرف *xstrdup(ثابت حرف *);

/* Compare two characters for use by qsort with '\0' sorting last. */
خارجي صحيح cclcmp(ثابت فراغ *, ثابت فراغ *);

/* Finish up a block of data declarations. */
خارجي فراغ dataend(ثابت حرف *);

/* Flush generated data statements. */
خارجي فراغ dataflush(فراغ);

/* Report an error message and terminate. */
خارجي فراغ flexerror(ثابت حرف *);

/* Report a fatal error message and terminate. */
خارجي فراغ flexfatal(ثابت حرف *);

/* Report a fatal error with a pinpoint, and terminate */
#اگر_تعریف_شده HAVE_DECL___FUNC__
#تعریف_کن flex_die(پیام) \
    افعل{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                برنامه_name, __FILE__, (صحيح)__LINE__,\
                __func__,پیام);\
        FLEX_EXIT(1);\
    }طالما(0)
#وإلا /* ! HAVE_DECL___FUNC__ */
#تعریف_کن flex_die(پیام) \
    افعل{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                برنامه_name, __FILE__, (صحيح)__LINE__,\
                پیام);\
        FLEX_EXIT(1);\
    }طالما(0)
#پایان_اگر /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
خارجي فراغ lerr(ثابت حرف *, ...)
#إذا defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#پایان_اگر
;

/* Like lerr, but also exit after displaying message. */
خارجي فراغ lerr_fatal(ثابت حرف *, ...)
#إذا defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#پایان_اگر
;

/* Spit out a "#line" statement. */
خارجي فراغ سطر_directive_بیرون(FILE *, حرف *, صحيح);

/* Mark the current position in the action array as the end of the section 1
 * user defs.
 */
خارجي فراغ mark_defs1(فراغ);

/* Mark the current position in the action array as the end of the prolog. */
خارجي فراغ mark_prolog(فراغ);

/* Generate a data statement for a two-dimensional array. */
خارجي فراغ mk2data(صحيح);

خارجي فراغ mkdata(صحيح);	/* generate a data statement */

/* Return the integer represented by a string of digits. */
خارجي صحيح myctoi(ثابت حرف *);

/* Return character corresponding to escape sequence. */
خارجي بیعلامت حرف myesc(بیعلامت حرف[]);

/* Output a (possibly-formatted) string to the generated scanner. */
خارجي فراغ بیرون(ثابت حرف *);
خارجي فراغ بیرون_dec(ثابت حرف *, صحيح);
خارجي فراغ بیرون_dec2(ثابت حرف *, صحيح, صحيح);
خارجي فراغ بیرون_hex(ثابت حرف *, بیعلامت صحيح);
خارجي فراغ بیرون_str(ثابت حرف *, ثابت حرف *);
خارجي فراغ بیرون_str_dec(ثابت حرف *, ثابت حرف *, صحيح);
خارجي فراغ outc(صحيح);
خارجي فراغ outn(ثابت حرف *);
خارجي فراغ بیرون_m4_define(ثابت حرف* def, ثابت حرف* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
خارجي حرف *readable_form(صحيح);

/* Output a yy_trans_info structure. */
خارجي فراغ transition_struct_بیرون(صحيح, صحيح);

/* Only needed when using certain broken versions of bison to build parse.c. */
خارجي فراغ *yy_flex_xmalloc(صحيح);


/* from file nfa.c */

/* Add an accepting state to a machine. */
خارجي فراغ جمع_کن_accept(صحيح, صحيح);

/* Make a given number of copies of a singleton machine. */
خارجي صحيح copysingl(صحيح, صحيح);

/* Debugging routine to write out an nfa. */
خارجي فراغ dumpnfa(صحيح);

/* Finish up the processing for a rule. */
خارجي فراغ پایان_قاعده(صحيح, bool, صحيح, صحيح, صحيح);

/* Connect two machines together. */
خارجي صحيح link_machines(صحيح, صحيح);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
خارجي فراغ mark_beginning_as_نرمال(صحيح);

/* Make a machine that branches to two machines. */
خارجي صحيح mkbranch(صحيح, صحيح);

خارجي صحيح mkclos(صحيح);	/* convert a machine into a closure */
خارجي صحيح mkopt(صحيح);	/* make a machine optional */

/* Make a machine that matches either one of two machines. */
خارجي صحيح mkor(صحيح, صحيح);

/* Convert a machine into a positive closure. */
خارجي صحيح mkposcl(صحيح);

خارجي صحيح mkrep(صحيح, صحيح, صحيح);	/* make a replicated machine */

/* Create a state with a transition on a given symbol. */
خارجي صحيح mkstate(صحيح);

خارجي فراغ new_قاعده(فراغ);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
خارجي فراغ build_eof_action(فراغ);

/* Write out a message formatted with one string, pinpointing its location. */
خارجي فراغ format_pinpoint_پیام(ثابت حرف *, ثابت حرف *);

/* Write out a message, pinpointing its location. */
خارجي فراغ pinpoint_پیام(ثابت حرف *);

/* Write out a warning, pinpointing it at the given line. */
خارجي فراغ سطر_warning(ثابت حرف *, صحيح);

/* Write out a message, pinpointing it at the given line. */
خارجي فراغ سطر_pinpoint(ثابت حرف *, صحيح);

/* Report a formatted syntax error. */
خارجي فراغ format_synerr(ثابت حرف *, ثابت حرف *);
خارجي فراغ synerr(ثابت حرف *);	/* report a syntax error */
خارجي فراغ format_warn(ثابت حرف *, ثابت حرف *);
خارجي فراغ lwarn(ثابت حرف *);	/* report a warning */
خارجي فراغ yyerror(ثابت حرف *);	/* report a parse error */
خارجي صحيح yyparse(فراغ);		/* the YACC parser */

/* Ship a comment to the generated output */
خارجي فراغ comment(ثابت حرف *);

/* from file scan.l */

/* The Flex-generated scanner for flex. */
خارجي صحيح flexscan(فراغ);

/* Open the given file (if NULL, stdin) for scanning. */
خارجي فراغ مجموعه_درون_داد_file(حرف *);

/* from file skeletons.c */

/* return the correct file suffix for the selected back end */
ثابت حرف *suffix (فراغ);

/* Mine a text-valued property out of the skeleton file */
خارجي ثابت حرف *skel_property(ثابت حرف *);

/* Is the default back end selected?*/
خارجي bool is_default_backend(فراغ);

/* Select a backend by name */
خارجي فراغ backend_by_name(ثابت حرف *);

/* Write out one section of the skeleton file. */
خارجي فراغ skelout(bool);

/* from file sym.c */

/* Save the text of a character class. */
خارجي فراغ cclinstal(حرف[], صحيح);

/* Lookup the number associated with character class. */
خارجي صحيح ccllookup(حرف[]);

خارجي فراغ ndinstal(ثابت حرف *, حرف[]);	/* install a name definition */
خارجي حرف *ndlookup(ثابت حرف *);	/* lookup a name definition */

/* Increase maximum number of SC's. */
خارجي فراغ scextend(فراغ);
خارجي فراغ scinstal(ثابت حرف *, bool);	/* make a start condition */

/* Lookup the number associated with a start condition. */
خارجي صحيح sclookup(ثابت حرف *);

/* Supply context argument for a function if required */
خارجي فراغ context_call(حرف *);

/* from file tblcmp.c */

/* Build table entries for dfa state. */
خارجي فراغ bldtbl(صحيح[], صحيح, صحيح, صحيح, صحيح);

خارجي فراغ cmptmps(فراغ);	/* compress template table entries */
خارجي فراغ expand_nxt_chk(فراغ);	/* increase nxt/chk arrays */

/* Finds a space in the table for a state to be placed. */
خارجي صحيح پیدا_کن_جدول_space(صحيح *, صحيح);
خارجي فراغ inittbl(فراغ);	/* initialize transition tables */

/* Make the default, "jam" table entries. */
خارجي فراغ mkdeftbl(فراغ);

/* Create table entries for a state (or state fragment) which has
 * only one out-transition.
 */
خارجي فراغ mk1tbl(صحيح, صحيح, صحيح, صحيح);

/* Place a state into full speed transition table. */
خارجي فراغ قراربده_state(صحيح *, صحيح, صحيح);

/* Save states with only one out-transition to be processed later. */
خارجي فراغ stack1(صحيح, صحيح, صحيح, صحيح);


/* from file yylex.c */

خارجي صحيح yylex(فراغ);

/* A growable array. See buf.c. */
بنية Buf {
	فراغ   *elts;		/* elements. */
	صحيح     nelts;		/* number of elements. */
	size_t  elt_اندازه;	/* in bytes. */
	صحيح     nmax;		/* max capacity of elements. */
};

خارجي فراغ buf_init(بنية Buf * buf, size_t elem_اندازه);
خارجي فراغ buf_destroy(بنية Buf * buf);
خارجي بنية Buf *buf_append(بنية Buf * buf, ثابت فراغ *ptr, صحيح n_elem);
خارجي بنية Buf *buf_strappend(بنية Buf *, ثابت حرف *str);
خارجي بنية Buf *buf_strnappend(بنية Buf *, ثابت حرف *str, صحيح nchars);
خارجي بنية Buf *buf_prints(بنية Buf *buf, ثابت حرف *fmt, ثابت حرف* s);

خارجي بنية Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
خارجي بنية Buf بالاترین_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#تعریف_کن بیرون_BEGIN_کد() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#تعریف_کن بیرون_انتها_کد()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
خارجي jmp_buf flex_main_jmp_buf;

#تعریف_کن FLEX_EXIT(وضعیت) longjmp(flex_main_jmp_buf,(وضعیت)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
خارجي حرف *chomp (حرف *str);

/* ctype functions forced to return boolean */
#تعریف_کن b_isalnum(c) (آیا_حرف_یا_رقم(c)?true:false)
#تعریف_کن b_isalpha(c) (آیا_حرف(c)?true:false)
#تعریف_کن b_isascii(c) (isascii(c)?true:false)
#تعریف_کن b_isblank(c) (isblank(c)?true:false)
#تعریف_کن b_iscntrl(c) (iscntrl(c)?true:false)
#تعریف_کن b_isdigit(c) (آیا_رقم(c)?true:false)
#تعریف_کن b_isgraph(c) (isgraph(c)?true:false)
#تعریف_کن b_islower(c) (islower(c)?true:false)
#تعریف_کن b_isprint(c) (isprint(c)?true:false)
#تعریف_کن b_ispunct(c) (ispunct(c)?true:false)
#تعریف_کن b_isspace(c) (آیا_فاصله(c)?true:false)
#تعریف_کن b_isupper(c) (isupper(c)?true:false)
#تعریف_کن b_isxdigit(c) (isxdigit(c)?true:false)

/* return true if char is uppercase or lowercase. */
bool has_case(صحيح c);

/* Change case of character if possible. */
صحيح معکوس_case(صحيح c);

/* return false if [c1-c2] is ambiguous for a caseless scanner. */
bool range_covers_case (صحيح c1, صحيح c2);

/*
 *  From "filter.c"
 */

/** A single stdio filter to execute.
 *  The filter may be external, such as "sed", or it
 *  may be internal, as a function call.
 */
بنية filter {
    صحيح    (*filter_func)(بنية filter*); /**< internal filter function */
    فراغ * extra;         /**< extra data passed to filter_func */
	صحيح     argc;         /**< arg count */
	ثابت حرف ** argv;   /**< arg vector, \0-terminated */
    بنية filter * بعدی; /**< next filter or NULL */
};

/* output filter chain */
خارجي بنية filter * output_chain;
خارجي بنية filter *filter_create_ext (بنية filter * chain, ثابت حرف *cmd, ...);
بنية filter *filter_create_int(بنية filter *chain,
				  صحيح (*filter_func) (بنية filter *),
                  فراغ *extra);
خارجي bool filter_apply_chain(بنية filter * chain);
خارجي صحيح filter_truncate(بنية filter * chain, صحيح max_len);
خارجي صحيح filter_tee_سرآیند(بنية filter *chain);
خارجي صحيح filter_fix_linedirs(بنية filter *chain);


/*
 * From "regex.c"
 */

خارجي regex_t regex_linedir;
bool flex_init_regex(ثابت حرف *);
فراغ flex_regcomp(regex_t *preg, ثابت حرف *regex, صحيح cflags);
حرف   *regmatch_dup (regmatch_t * m, ثابت حرف *src);
حرف   *regmatch_cpy (regmatch_t * m, حرف *dest, ثابت حرف *src);
صحيح regmatch_len (regmatch_t * m);
صحيح regmatch_strtol (regmatch_t * m, ثابت حرف *src, حرف **endptr, صحيح پایه);
bool regmatch_خالی (regmatch_t * m);

/* From "scanflags.h" */
تعريفنوع بیعلامت صحيح scanflags_t;
خارجي scanflags_t* _sf_stk;
خارجي size_t sf_بالاترین_ix, _sf_max; /**< stack of scanner flags. */
#تعریف_کن _SF_CASE_INS   ((scanflags_t) 0x0001)
#تعریف_کن _SF_DOT_ALL    ((scanflags_t) 0x0002)
#تعریف_کن _SF_SKIP_WS    ((scanflags_t) 0x0004)
#تعریف_کن sf_بالاترین()           (_sf_stk[sf_بالاترین_ix])
#تعریف_کن sf_case_ins()      (sf_بالاترین() & _SF_CASE_INS)
#تعریف_کن sf_dot_all()       (sf_بالاترین() & _SF_DOT_ALL)
#تعریف_کن sf_skip_ws()       (sf_بالاترین() & _SF_SKIP_WS)
#تعریف_کن sf_مجموعه_case_ins(X)      ((X) ? (sf_بالاترین() |= _SF_CASE_INS) : (sf_بالاترین() &= ~_SF_CASE_INS))
#تعریف_کن sf_مجموعه_dot_all(X)       ((X) ? (sf_بالاترین() |= _SF_DOT_ALL)  : (sf_بالاترین() &= ~_SF_DOT_ALL))
#تعریف_کن sf_مجموعه_skip_ws(X)       ((X) ? (sf_بالاترین() |= _SF_SKIP_WS)  : (sf_بالاترین() &= ~_SF_SKIP_WS))
خارجي فراغ sf_init(فراغ);
خارجي فراغ sf_افزودن(فراغ);
خارجي فراغ sf_برداشت(فراغ);


#پایان_اگر /* not defined FLEXDEF_H */
