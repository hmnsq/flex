
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

#اگر_غیر_تعریف_شدہ FLEXDEF_H
#تعریف_کرو FLEXDEF_H 1

#اگر_غیر_تعریف_شدہ USE_CONFIG_FOR_BUILD
# ifdef HAVE_CONFIG_H
#شامل <config.h>
# endif
#ورنہ
#شامل <config_for_build.h>
#اگر_ختم

#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <stdarg.h>
#شامل <setjmp.h>
#شامل <ctype.h>
#شامل <string.h>
#شامل <math.h>

#اگر_تعریف_شدہ HAVE_ASSERT_H
#شامل <assert.h>
#ورنہ
#تعریف_کرو أكد(Pred)
#اگر_ختم

#اگر_تعریف_شدہ HAVE_LIMITS_H
#شامل <limits.h>
#اگر_ختم
/* Required: dup() and dup2() in <unistd.h> */
#شامل <unistd.h>
#اگر_تعریف_شدہ HAVE_NETINET_اندر_H
#شامل <netinet/in.h>
#اگر_ختم
#اگر_تعریف_شدہ HAVE_SYS_PARAMS_H
#شامل <sys/params.h>
#اگر_ختم
/* Required: wait() in <sys/wait.h> */
#شامل <sys/wait.h>
#اگر_تعریف_شدہ HAVE_STDBOOL_H
#شامل <stdbool.h>
#وگرنہ_اگر !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# ورنہ
#  define bool صحیح
# endif
# define false 0
# define true 1
#اگر_ختم
#شامل <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#شامل <regex.h>
/* Required: strcasecmp() in <strings.h> */
#شامل <strings.h>
#شامل "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#اگر defined(ENABLE_NLS) && ENABLE_NLS
#اگر_تعریف_شدہ HAVE_LOCALE_H
#شامل <locale.h>
#اگر_ختم /* HAVE_LOCALE_H */
#شامل "gettext.h"
#تعریف_کرو _(String) gettext (String)
#ورنہ
#تعریف_کرو _(STRING) STRING
#اگر_ختم /* ENABLE_NLS */

/* Always be prepared to generate an 8-bit scanner. */
#تعریف_کرو CSIZE 256

/* Size of input alphabet - should be size of ASCII set. */
#اگر_غیر_تعریف_شدہ DEFAULT_CSIZE
#تعریف_کرو DEFAULT_CSIZE 128
#اگر_ختم

/* Maximum line length we'll have to deal with. */
#تعریف_کرو MAXLINE 2048

#اگر_غیر_تعریف_شدہ MIN
#تعریف_کرو MIN(x,y) ((x) < (y) ? (x) : (y))
#اگر_ختم
#اگر_غیر_تعریف_شدہ MAX
#تعریف_کرو MAX(x,y) ((x) > (y) ? (x) : (y))
#اگر_ختم
#اگر_غیر_تعریف_شدہ ABS
#تعریف_کرو ABS(x) ((x) < 0 ? -(x) : (x))
#اگر_ختم

/* Whether an integer is a power of two */
#تعریف_کرو is_power_کا_2(n) ((n) > 0 && ((n) & ((n) - 1)) == 0)

/* Special chk[] values marking the slots taking by end-of-buffer and action
 * numbers.
 */
#تعریف_کرو EOB_POSITION -1
#تعریف_کرو ACTION_POSITION -2

/* Number of data items per line for -f output. */
#تعریف_کرو NUMDATAITEMS 10

/* Number of lines of data in -f output before inserting a blank line for
 * readability.
 */
#تعریف_کرو NUMDATALINES 10

/* transition_struct_out() definitions. */
#تعریف_کرو TRANS_STRUCT_PRINT_لمبائی 14

/* Returns true if an nfa state has an epsilon out-transition slot
 * that can be used.  This definition is currently not used.
 */
#تعریف_کرو FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans2[state] == NO_TRANSITION && \
	 finalst[state] != state)

/* Returns true if an nfa state has an epsilon out-transition character
 * and both slots are free
 */
#تعریف_کرو SUPER_FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans1[state] == NO_TRANSITION) \

/* Maximum number of NFA states that can comprise a DFA state.  It's real
 * big because if there's a lot of rules, the initial state will have a
 * huge epsilon closure.
 */
#تعریف_کرو INITIAL_MAX_DFA_سائز 750
#تعریف_کرو MAX_DFA_سائز_INCREMENT 750


/* A note on the following masks.  They are used to mark accepting numbers
 * as being special.  As such, they implicitly limit the number of accepting
 * numbers (i.e., rules) because if there are too many rules the rule numbers
 * will overload the mask bits.  Fortunately, this limit is \large/ (0x2000 ==
 * 8192) so unlikely to actually cause any problems.  A check is made in
 * new_rule() to ensure that this limit is not reached.
 */

/* Mask to mark a trailing context accepting number. */
#تعریف_کرو YY_TRAILING_نقاب 0x2000

/* Mask to mark the accepting number of the "head" of a trailing context
 * rule.
 */
#تعریف_کرو YY_TRAILING_سر_نقاب 0x4000

/* Maximum number of rules, as outlined in the above note. */
#تعریف_کرو MAX_قاعدہ (YY_TRAILING_نقاب - 1)


/* NIL must be 0.  If not, its special meaning when making equivalence classes
 * (it marks the representative of a given e.c.) will be unidentifiable.
 */
#تعریف_کرو NIL 0

#تعریف_کرو JAM -1			/* to mark a missing DFA transition */
#تعریف_کرو NO_TRANSITION NIL
#تعریف_کرو UNIQUE -1		/* marks a symbol as an e.c. representative */
#تعریف_کرو INFINITE_REPEAT -1		/* for x{5,} constructions */

#تعریف_کرو INITIAL_MAX_CCLS 100	/* max number of unique character classes */
#تعریف_کرو MAX_CCLS_INCREMENT 100

/* Size of table holding members of character classes. */
#تعریف_کرو INITIAL_MAX_CCL_TBL_سائز 500
#تعریف_کرو MAX_CCL_TBL_سائز_INCREMENT 250

#تعریف_کرو INITIAL_MAX_قواعد 100	/* default maximum number of rules */
#تعریف_کرو MAX_قواعد_INCREMENT 100

#تعریف_کرو INITIAL_MNS 2000	/* default maximum number of nfa states */
#تعریف_کرو MNS_INCREMENT 1000	/* amount to bump above by if it's not enough */

#تعریف_کرو INITIAL_MAX_DFAS 1000	/* default maximum number of dfa states */
#تعریف_کرو MAX_DFAS_INCREMENT 1000

#تعریف_کرو JAMSTATE -32766		/* marks a reference to the state that always jams */

/* Maximum number of NFA states. */
#تعریف_کرو زیادہ_سے_زیادہ_MNS 31999
#تعریف_کرو زیادہ_سے_زیادہ_MNS_LONG 1999999999

/* Enough so that if it's subtracted from an NFA state number, the result
 * is guaranteed to be negative.
 */
#تعریف_کرو MARKER_DIFFERENCE (زیادہ_سے_زیادہ_mns+2)

/* Maximum number of nxt/chk pairs for non-templates. */
#تعریف_کرو INITIAL_MAX_XPAIRS 2000
#تعریف_کرو MAX_XPAIRS_INCREMENT 2000

/* Maximum number of nxt/chk pairs needed for templates. */
#تعریف_کرو INITIAL_MAX_TEMPLATE_XPAIRS 2500
#تعریف_کرو MAX_TEMPLATE_XPAIRS_INCREMENT 2500

#تعریف_کرو SYM_EPSILON (CSIZE + 1)	/* to mark transitions on the symbol epsilon */

#تعریف_کرو INITIAL_MAX_SCS 40	/* maximum number of start conditions */
#تعریف_کرو MAX_SCS_INCREMENT 40	/* amount to bump by if it's not enough */

#تعریف_کرو ONE_ڈھیر_سائز 500	/* stack of states with only one out-transition */
#تعریف_کرو SAME_TRANS -1		/* transition is the same as "default" entry for state */

/* The following percentages are used to tune table compression:

 * The percentage the number of out-transitions a state must be of the
 * number of equivalence classes in order to be considered for table
 * compaction by using protos.
 */
#تعریف_کرو PROTO_سائز_PERCENTAGE 15

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * that the state's transition table is first compared with a potential
 * template of the most common out-transition instead of with the first
 * proto in the proto queue.
 */
#تعریف_کرو CHECK_COM_PERCENTAGE 50

/* The percentage the number of differences between a state's transition
 * table and the proto it was first compared with must be of the total
 * number of out-transitions of the state in order to keep the first
 * proto as a good match and not search any further.
 */
#تعریف_کرو پہلا_مطابقت_DIFF_PERCENTAGE 10

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to use the proto as an acceptable close match.
 */
#تعریف_کرو ACCEPTABLE_DIFF_PERCENTAGE 50

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * to consider making a template from the state.
 */
#تعریف_کرو TEMPLATE_SAME_PERCENTAGE 60

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to create a new proto from the state.
 */
#تعریف_کرو NEW_PROTO_DIFF_PERCENTAGE 20

/* The percentage the total number of out-transitions of a state must be
 * of the number of equivalence classes in order to consider trying to
 * fit the transition table into "holes" inside the nxt/chk table.
 */
#تعریف_کرو INTERIOR_FIT_PERCENTAGE 15

/* Size of region set aside to cache the complete transition table of
 * protos on the proto queue to enable quick comparisons.
 */
#تعریف_کرو PROT_SAVE_سائز 2000

#تعریف_کرو MSP 50			/* maximum number of saved protos (protos on the proto queue) */

/* Maximum number of out-transitions a state can have that we'll rummage
 * around through the interior of the internal fast table looking for a
 * spot for it.
 */
#تعریف_کرو MAX_XTIONS_بھرا_INTERIOR_FIT 4

/* Maximum number of rules which will be reported as being associated
 * with a DFA state.
 */
#تعریف_کرو MAX_ASSOC_قواعد 100

/* Number that, if used to subscript an array, has a good chance of producing
 * an error; should be small enough to fit into a short.
 */
#تعریف_کرو BAD_SUBSCRIPT -32767

قسمتعریف شمار trit_t {
	trit_unspecified = -1,
	trit_false = 0,
	trit_true = 1,
} trit;

/* Control variables.  These are in a struct to avoid having to replicate definitions
 * twice for each option, instead a single struct can be declared and externed.
 * If it's in this structure, it has a corresponding m4 symbol.
 */
ساخت ctrl_bundle_t {
	bool always_interactive;// always use character-by-character input
	FILE *backing_اوپر_file;	// file to summarize backing-up states to 
	bool bison_bridge_lval;	// (--bison-bridge), bison pure calling convention. 
	bool bison_bridge_lloc;	// (--bison-locations), bison yylloc.
	size_t bufsize;		// input buffer size
	bool C_plus_plus;	// (-+ flag) generate a C++ scanner class 
	صحیح csize;		// size of character set for the scanner 
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
	حرف *سابقہ;		// prefix for externally visible names, default "yy" 
	trit reject_really_مستعمل;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool ڈھیر_مستعمل;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	حرف *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	حرف *yydecl;		// user-specified prototype for yylex.
	صحیح yylmax;		// Maximum buffer length if %array
	trit yymore_really_مستعمل;// Force geberation of support code for yymore
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
	bool no_yy_ڈالو_state;
	bool no_yy_نکالو_state;
	bool no_yy_چوٹی_state;
	bool no_yyunput;
	bool no_yy_جائزہ_بفر;
	bool no_yy_جائزہ_بائٹیں;
	bool no_yy_جائزہ_string;
	bool no_yyget_extra;
	bool no_yyset_extra;
	bool no_yyget_leng;
	bool no_yyget_متن;
	bool no_yyget_lineno;
	bool no_yyset_lineno;
	bool no_yyget_عمود;
	bool no_yyset_عمود;
	bool no_yyget_اندر;
	bool no_yyset_اندر;
	bool no_yyget_برآمد;
	bool no_yyset_برآمد;
	bool no_yyget_lval;
	bool no_yyset_lval;
	bool no_yyget_lloc;
	bool no_yyset_lloc;
	bool no_flex_alloc;
	bool no_flex_realloc;
	bool no_flex_free;
	bool no_get_debug;
	bool no_سیٹ_debug;
	// Properties read from the skeleton
	ثابت حرف *backend_name;	// What the back end tells you its name is
	ثابت حرف *traceline_re;	// Regular expression for recognizing tracelines */
	ثابت حرف *traceline_template;	// templare for emitting trace lines */
	bool have_state_اندراج_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
ساخت env_bundle_t {
	bool backing_اوپر_report;	// (-b flag), generate "lex.backup" file 
				// listing backing-up states
	bool did_outfilename;	// whether outfilename was explicitly set
	حرف *headerfilename;	// name of the .h file to generate
	bool nowarn;		// (-w) do not generate warnings 
	صحیح performance_hint;	// if > 0 (i.e., -p flag), generate a report 
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
ساخت packtype_t {
	حرف *name;
	size_t چوڑائی;
};

خارجی ساخت ctrl_bundle_t ctrl;
خارجی ساخت env_bundle_t env;

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

خارجی bool syntaxerror, eofseen;
خارجی صحیح yymore_مستعمل, reject, real_reject, continued_action, اندر_قاعدہ;

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

خارجی صحیح datapos, dataline, linenum;
خارجی صحیح skel_ind;
خارجی حرف *infilename;
خارجی حرف *extra_type;
خارجی حرف **داخلہ_files;
خارجی صحیح عدد_داخلہ_files;
خارجی حرف *پروگرام_name;

خارجی حرف *action_array;
خارجی صحیح action_سائز;
خارجی صحیح defs1_انحراف, prolog_انحراف, action_انحراف, action_اشاریہ;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

خارجی صحیح onestate[ONE_ڈھیر_سائز], onesym[ONE_ڈھیر_سائز];
خارجی صحیح onenext[ONE_ڈھیر_سائز], onedef[ONE_ڈھیر_سائز], onesp;


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

خارجی صحیح زیادہ_سے_زیادہ_mns, current_mns, current_max_قواعد;
خارجی صحیح عدد_قواعد, عدد_eof_قواعد, default_قاعدہ, lastnfa;
خارجی صحیح *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
خارجی صحیح *accptnum, *assoc_قاعدہ, *state_type;
خارجی صحیح *قاعدہ_type, *قاعدہ_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
خارجی حرف *قاعدہ_useful, *قاعدہ_has_nl, *ccl_has_nl;
خارجی صحیح nlch;
خارجی size_t footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#تعریف_کرو STATE_معمول 0x1
#تعریف_کرو STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

خارجی صحیح current_state_type;

/* Different types of rules. */
#تعریف_کرو قاعدہ_معمول 0
#تعریف_کرو قاعدہ_VARIABLE 1

/* True if the input rules include a rule with both variable-length head
 * and trailing context, false otherwise.
 */
خارجی bool variable_trailing_context_قواعد;


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

خارجی صحیح numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
خارجی صحیح protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_سائز];


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
خارجی صحیح numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs;

/* Meta-equivalence classes are indexed starting at 1, so it's possible
 * that they will require positions from 1 .. CSIZE, i.e., CSIZE + 1
 * slots total (since the arrays are 0-based).  nextecm[] and ecgroup[]
 * don't require the extra position since they're indexed from 1 .. CSIZE - 1.
 */
خارجی صحیح tecfwd[CSIZE + 1], tecbck[CSIZE + 1];


/* Variables for start conditions:
 * lastsc - last start condition created
 * current_max_scs - current limit on number of start conditions
 * scset - set of rules active in start condition
 * scbol - set of rules active only at the beginning of line in a s.c.
 * scxclu - true if start condition is exclusive
 * sceof - true if start condition has EOF rule
 * scname - start condition name
 */

خارجی صحیح lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
خارجی حرف *scxclu, *sceof;
خارجی صحیح current_max_scs;
خارجی ثابت حرف **scname;


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

خارجی صحیح current_max_dfa_سائز, current_max_xpairs;
خارجی صحیح current_max_template_xpairs, current_max_dfas;
خارجی صحیح lastdfa, *nxt, *chk, *tnxt;
خارجی صحیح *بنیاد, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
خارجی اتحاد dfaacc_union {
	صحیح    *dfaacc_سیٹ;
	صحیح     dfaacc_state;
}      *dfaacc;
خارجی صحیح *accsiz, *dhash, numas;
خارجی صحیح numsnpairs, jambase, jamstate;
خارجی صحیح انتہا_کا_بفر_state;

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

خارجی صحیح lastccl, *cclmap, *ccllen, *cclng, cclreuse;
خارجی صحیح current_maxccls, current_max_ccl_tbl_سائز;
خارجی غیرعلامتی حرف *ccltbl;


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

خارجی حرف nmstr[MAXLINE];
خارجی صحیح sectnum, nummt, hshcol, dfaeql, numeps, eps2, عدد_reallocs, nmval;
خارجی صحیح tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
خارجی صحیح عدد_backing_اوپر, bol_needed;

خالی   *allocate_array(صحیح, size_t);
خالی   *reallocate_array(خالی *, صحیح, size_t);

#تعریف_کرو allocate_integer_array(سائز) \
	allocate_array(سائز, حجم(صحیح))

#تعریف_کرو reallocate_integer_array(array,سائز) \
	reallocate_array((خالی *) array, سائز, حجم(صحیح))

#تعریف_کرو allocate_int_ptr_array(سائز) \
	allocate_array(سائز, حجم(صحیح *))

#تعریف_کرو allocate_char_ptr_array(سائز) \
	allocate_array(سائز, حجم(حرف *))

#تعریف_کرو reallocate_int_ptr_array(array,سائز) \
	reallocate_array((خالی *) array, سائز, حجم(صحیح *))

#تعریف_کرو reallocate_char_ptr_array(array,سائز) \
	reallocate_array((خالی *) array, سائز, حجم(حرف *))

#تعریف_کرو allocate_character_array(سائز) \
	allocate_array( سائز, حجم(حرف))

#تعریف_کرو reallocate_character_array(array,سائز) \
	reallocate_array((خالی *) array, سائز, حجم(حرف))

#تعریف_کرو allocate_Character_array(سائز) \
	allocate_array(سائز, حجم(غیرعلامتی حرف))

#تعریف_کرو reallocate_Character_array(array,سائز) \
	reallocate_array((خالی *) array, سائز, حجم(غیرعلامتی حرف))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

خارجی خالی ccladd(صحیح, صحیح);	/* add a single character to a ccl */
خارجی صحیح cclinit(خالی);	/* make an empty ccl */
خارجی خالی cclnegate(صحیح);	/* negate a ccl */
خارجی صحیح ccl_سیٹ_diff (صحیح a, صحیح b); /* set difference of two ccls. */
خارجی صحیح ccl_سیٹ_union (صحیح a, صحیح b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
خارجی خالی list_character_سیٹ(FILE *, صحیح[]);


/* from file dfa.c */

/* Increase the maximum number of dfas. */
خارجی خالی increase_max_dfas(خالی);

خارجی size_t ntod(خالی);	/* convert a ndfa to a dfa */


/* from file ecs.c */

/* Convert character classes to set of equivalence classes. */
خارجی خالی ccl2ecl(خالی);

/* Associate equivalence class numbers with class members. */
خارجی صحیح cre8ecs(صحیح[], صحیح[], صحیح);

/* Update equivalence classes based on character class transitions. */
خارجی خالی mkeccl(غیرعلامتی حرف[], صحیح, صحیح[], صحیح[], صحیح, صحیح);

/* Create equivalence class for single character. */
خارجی خالی mkechar(صحیح, صحیح[], صحیح[]);


/* from file gen.c */

/* Set a conditional amd make it visible in generated code */
خارجی خالی visible_define (ثابت حرف *);

/* And again, with an explicit value part. */
خارجی خالی visible_define_str (ثابت حرف *, ثابت حرف *);

/* This time the value part is an int */
خارجی خالی visible_define_int (ثابت حرف *, ثابت صحیح);

/* generate transition tables */
خارجی خالی make_tables(خالی);

/* Select a type for optimal packing */
ساخت packtype_t *optimize_pack(size_t);

/* from file main.c */

خارجی خالی check_options(خالی);
خارجی خالی flexend(صحیح);
خارجی خالی usage(خالی);


/* from file misc.c */

/* Add the given text to the stored actions. */
خارجی خالی جوڑو_action(ثابت حرف *new_متن);

/* True if a string is all lower case. */
خارجی صحیح all_زیریں(حرف *);

/* True if a string is all upper case. */
خارجی صحیح all_بالائی(حرف *);

/* Compare two integers for use by qsort. */
خارجی صحیح intcmp(ثابت خالی *, ثابت خالی *);

/* Check a character to make sure it's in the expected range. */
خارجی خالی check_char(صحیح c);

/* Replace upper-case letter to lower-case. */
خارجی غیرعلامتی حرف clower(صحیح);

/* strdup() that fails fatally on allocation failures. */
خارجی حرف *xstrdup(ثابت حرف *);

/* Compare two characters for use by qsort with '\0' sorting last. */
خارجی صحیح cclcmp(ثابت خالی *, ثابت خالی *);

/* Finish up a block of data declarations. */
خارجی خالی dataend(ثابت حرف *);

/* Flush generated data statements. */
خارجی خالی dataflush(خالی);

/* Report an error message and terminate. */
خارجی خالی flexerror(ثابت حرف *);

/* Report a fatal error message and terminate. */
خارجی خالی flexfatal(ثابت حرف *);

/* Report a fatal error with a pinpoint, and terminate */
#اگر_تعریف_شدہ HAVE_DECL___FUNC__
#تعریف_کرو flex_die(پیغام) \
    کرو{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                پروگرام_name, __FILE__, (صحیح)__LINE__,\
                __func__,پیغام);\
        FLEX_EXIT(1);\
    }جب(0)
#ورنہ /* ! HAVE_DECL___FUNC__ */
#تعریف_کرو flex_die(پیغام) \
    کرو{ \
        fprintf (stderr,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                پروگرام_name, __FILE__, (صحیح)__LINE__,\
                پیغام);\
        FLEX_EXIT(1);\
    }جب(0)
#اگر_ختم /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
خارجی خالی lerr(ثابت حرف *, ...)
#اگر defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#اگر_ختم
;

/* Like lerr, but also exit after displaying message. */
خارجی خالی lerr_fatal(ثابت حرف *, ...)
#اگر defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#اگر_ختم
;

/* Spit out a "#line" statement. */
خارجی خالی سطر_directive_برآمد(FILE *, حرف *, صحیح);

/* Mark the current position in the action array as the end of the section 1
 * user defs.
 */
خارجی خالی mark_defs1(خالی);

/* Mark the current position in the action array as the end of the prolog. */
خارجی خالی mark_prolog(خالی);

/* Generate a data statement for a two-dimensional array. */
خارجی خالی mk2data(صحیح);

خارجی خالی mkdata(صحیح);	/* generate a data statement */

/* Return the integer represented by a string of digits. */
خارجی صحیح myctoi(ثابت حرف *);

/* Return character corresponding to escape sequence. */
خارجی غیرعلامتی حرف myesc(غیرعلامتی حرف[]);

/* Output a (possibly-formatted) string to the generated scanner. */
خارجی خالی برآمد(ثابت حرف *);
خارجی خالی برآمد_dec(ثابت حرف *, صحیح);
خارجی خالی برآمد_dec2(ثابت حرف *, صحیح, صحیح);
خارجی خالی برآمد_hex(ثابت حرف *, غیرعلامتی صحیح);
خارجی خالی برآمد_str(ثابت حرف *, ثابت حرف *);
خارجی خالی برآمد_str_dec(ثابت حرف *, ثابت حرف *, صحیح);
خارجی خالی outc(صحیح);
خارجی خالی outn(ثابت حرف *);
خارجی خالی برآمد_m4_define(ثابت حرف* def, ثابت حرف* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
خارجی حرف *readable_form(صحیح);

/* Output a yy_trans_info structure. */
خارجی خالی transition_struct_برآمد(صحیح, صحیح);

/* Only needed when using certain broken versions of bison to build parse.c. */
خارجی خالی *yy_flex_xmalloc(صحیح);


/* from file nfa.c */

/* Add an accepting state to a machine. */
خارجی خالی جوڑو_accept(صحیح, صحیح);

/* Make a given number of copies of a singleton machine. */
خارجی صحیح copysingl(صحیح, صحیح);

/* Debugging routine to write out an nfa. */
خارجی خالی dumpnfa(صحیح);

/* Finish up the processing for a rule. */
خارجی خالی اختتام_قاعدہ(صحیح, bool, صحیح, صحیح, صحیح);

/* Connect two machines together. */
خارجی صحیح link_machines(صحیح, صحیح);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
خارجی خالی mark_beginning_as_معمول(صحیح);

/* Make a machine that branches to two machines. */
خارجی صحیح mkbranch(صحیح, صحیح);

خارجی صحیح mkclos(صحیح);	/* convert a machine into a closure */
خارجی صحیح mkopt(صحیح);	/* make a machine optional */

/* Make a machine that matches either one of two machines. */
خارجی صحیح mkor(صحیح, صحیح);

/* Convert a machine into a positive closure. */
خارجی صحیح mkposcl(صحیح);

خارجی صحیح mkrep(صحیح, صحیح, صحیح);	/* make a replicated machine */

/* Create a state with a transition on a given symbol. */
خارجی صحیح mkstate(صحیح);

خارجی خالی new_قاعدہ(خالی);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
خارجی خالی build_eof_action(خالی);

/* Write out a message formatted with one string, pinpointing its location. */
خارجی خالی format_pinpoint_پیغام(ثابت حرف *, ثابت حرف *);

/* Write out a message, pinpointing its location. */
خارجی خالی pinpoint_پیغام(ثابت حرف *);

/* Write out a warning, pinpointing it at the given line. */
خارجی خالی سطر_warning(ثابت حرف *, صحیح);

/* Write out a message, pinpointing it at the given line. */
خارجی خالی سطر_pinpoint(ثابت حرف *, صحیح);

/* Report a formatted syntax error. */
خارجی خالی format_synerr(ثابت حرف *, ثابت حرف *);
خارجی خالی synerr(ثابت حرف *);	/* report a syntax error */
خارجی خالی format_warn(ثابت حرف *, ثابت حرف *);
خارجی خالی lwarn(ثابت حرف *);	/* report a warning */
خارجی خالی yyerror(ثابت حرف *);	/* report a parse error */
خارجی صحیح yyparse(خالی);		/* the YACC parser */

/* Ship a comment to the generated output */
خارجی خالی comment(ثابت حرف *);

/* from file scan.l */

/* The Flex-generated scanner for flex. */
خارجی صحیح flexscan(خالی);

/* Open the given file (if NULL, stdin) for scanning. */
خارجی خالی سیٹ_داخلہ_file(حرف *);

/* from file skeletons.c */

/* return the correct file suffix for the selected back end */
ثابت حرف *suffix (خالی);

/* Mine a text-valued property out of the skeleton file */
خارجی ثابت حرف *skel_property(ثابت حرف *);

/* Is the default back end selected?*/
خارجی bool is_default_backend(خالی);

/* Select a backend by name */
خارجی خالی backend_by_name(ثابت حرف *);

/* Write out one section of the skeleton file. */
خارجی خالی skelout(bool);

/* from file sym.c */

/* Save the text of a character class. */
خارجی خالی cclinstal(حرف[], صحیح);

/* Lookup the number associated with character class. */
خارجی صحیح ccllookup(حرف[]);

خارجی خالی ndinstal(ثابت حرف *, حرف[]);	/* install a name definition */
خارجی حرف *ndlookup(ثابت حرف *);	/* lookup a name definition */

/* Increase maximum number of SC's. */
خارجی خالی scextend(خالی);
خارجی خالی scinstal(ثابت حرف *, bool);	/* make a start condition */

/* Lookup the number associated with a start condition. */
خارجی صحیح sclookup(ثابت حرف *);

/* Supply context argument for a function if required */
خارجی خالی context_call(حرف *);

/* from file tblcmp.c */

/* Build table entries for dfa state. */
خارجی خالی bldtbl(صحیح[], صحیح, صحیح, صحیح, صحیح);

خارجی خالی cmptmps(خالی);	/* compress template table entries */
خارجی خالی expand_nxt_chk(خالی);	/* increase nxt/chk arrays */

/* Finds a space in the table for a state to be placed. */
خارجی صحیح ڈھونڈو_جدول_space(صحیح *, صحیح);
خارجی خالی inittbl(خالی);	/* initialize transition tables */

/* Make the default, "jam" table entries. */
خارجی خالی mkdeftbl(خالی);

/* Create table entries for a state (or state fragment) which has
 * only one out-transition.
 */
خارجی خالی mk1tbl(صحیح, صحیح, صحیح, صحیح);

/* Place a state into full speed transition table. */
خارجی خالی رکھو_state(صحیح *, صحیح, صحیح);

/* Save states with only one out-transition to be processed later. */
خارجی خالی stack1(صحیح, صحیح, صحیح, صحیح);


/* from file yylex.c */

خارجی صحیح yylex(خالی);

/* A growable array. See buf.c. */
ساخت Buf {
	خالی   *elts;		/* elements. */
	صحیح     nelts;		/* number of elements. */
	size_t  elt_سائز;	/* in bytes. */
	صحیح     nmax;		/* max capacity of elements. */
};

خارجی خالی buf_init(ساخت Buf * buf, size_t elem_سائز);
خارجی خالی buf_destroy(ساخت Buf * buf);
خارجی ساخت Buf *buf_append(ساخت Buf * buf, ثابت خالی *ptr, صحیح n_elem);
خارجی ساخت Buf *buf_strappend(ساخت Buf *, ثابت حرف *str);
خارجی ساخت Buf *buf_strnappend(ساخت Buf *, ثابت حرف *str, صحیح nchars);
خارجی ساخت Buf *buf_prints(ساخت Buf *buf, ثابت حرف *fmt, ثابت حرف* s);

خارجی ساخت Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
خارجی ساخت Buf چوٹی_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#تعریف_کرو برآمد_BEGIN_رمز() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#تعریف_کرو برآمد_انتہا_رمز()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
خارجی jmp_buf flex_main_jmp_buf;

#تعریف_کرو FLEX_EXIT(حالت_2) longjmp(flex_main_jmp_buf,(حالت_2)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
خارجی حرف *chomp (حرف *str);

/* ctype functions forced to return boolean */
#تعریف_کرو b_isalnum(c) (حرف_یا_ہندسہ(c)?true:false)
#تعریف_کرو b_isalpha(c) (حرف_ہے(c)?true:false)
#تعریف_کرو b_isascii(c) (isascii(c)?true:false)
#تعریف_کرو b_isblank(c) (isblank(c)?true:false)
#تعریف_کرو b_iscntrl(c) (iscntrl(c)?true:false)
#تعریف_کرو b_isdigit(c) (ہندسہ_ہے(c)?true:false)
#تعریف_کرو b_isgraph(c) (isgraph(c)?true:false)
#تعریف_کرو b_islower(c) (islower(c)?true:false)
#تعریف_کرو b_isprint(c) (isprint(c)?true:false)
#تعریف_کرو b_ispunct(c) (ispunct(c)?true:false)
#تعریف_کرو b_isspace(c) (خلا_ہے(c)?true:false)
#تعریف_کرو b_isupper(c) (isupper(c)?true:false)
#تعریف_کرو b_isxdigit(c) (isxdigit(c)?true:false)

/* return true if char is uppercase or lowercase. */
bool has_case(صحیح c);

/* Change case of character if possible. */
صحیح الٹ_case(صحیح c);

/* return false if [c1-c2] is ambiguous for a caseless scanner. */
bool range_covers_case (صحیح c1, صحیح c2);

/*
 *  From "filter.c"
 */

/** A single stdio filter to execute.
 *  The filter may be external, such as "sed", or it
 *  may be internal, as a function call.
 */
ساخت filter {
    صحیح    (*filter_func)(ساخت filter*); /**< internal filter function */
    خالی * extra;         /**< extra data passed to filter_func */
	صحیح     argc;         /**< arg count */
	ثابت حرف ** argv;   /**< arg vector, \0-terminated */
    ساخت filter * اگلا; /**< next filter or NULL */
};

/* output filter chain */
خارجی ساخت filter * output_chain;
خارجی ساخت filter *filter_create_ext (ساخت filter * chain, ثابت حرف *cmd, ...);
ساخت filter *filter_create_int(ساخت filter *chain,
				  صحیح (*filter_func) (ساخت filter *),
                  خالی *extra);
خارجی bool filter_apply_chain(ساخت filter * chain);
خارجی صحیح filter_truncate(ساخت filter * chain, صحیح max_len);
خارجی صحیح filter_tee_سرخی(ساخت filter *chain);
خارجی صحیح filter_fix_linedirs(ساخت filter *chain);


/*
 * From "regex.c"
 */

خارجی regex_t regex_linedir;
bool flex_init_regex(ثابت حرف *);
خالی flex_regcomp(regex_t *preg, ثابت حرف *regex, صحیح cflags);
حرف   *regmatch_dup (regmatch_t * m, ثابت حرف *src);
حرف   *regmatch_cpy (regmatch_t * m, حرف *dest, ثابت حرف *src);
صحیح regmatch_len (regmatch_t * m);
صحیح regmatch_strtol (regmatch_t * m, ثابت حرف *src, حرف **endptr, صحیح بنیاد);
bool regmatch_خالی_خانے (regmatch_t * m);

/* From "scanflags.h" */
قسمتعریف غیرعلامتی صحیح scanflags_t;
خارجی scanflags_t* _sf_stk;
خارجی size_t sf_چوٹی_ix, _sf_max; /**< stack of scanner flags. */
#تعریف_کرو _SF_CASE_INS   ((scanflags_t) 0x0001)
#تعریف_کرو _SF_DOT_ALL    ((scanflags_t) 0x0002)
#تعریف_کرو _SF_SKIP_WS    ((scanflags_t) 0x0004)
#تعریف_کرو sf_چوٹی()           (_sf_stk[sf_چوٹی_ix])
#تعریف_کرو sf_case_ins()      (sf_چوٹی() & _SF_CASE_INS)
#تعریف_کرو sf_dot_all()       (sf_چوٹی() & _SF_DOT_ALL)
#تعریف_کرو sf_skip_ws()       (sf_چوٹی() & _SF_SKIP_WS)
#تعریف_کرو sf_سیٹ_case_ins(X)      ((X) ? (sf_چوٹی() |= _SF_CASE_INS) : (sf_چوٹی() &= ~_SF_CASE_INS))
#تعریف_کرو sf_سیٹ_dot_all(X)       ((X) ? (sf_چوٹی() |= _SF_DOT_ALL)  : (sf_چوٹی() &= ~_SF_DOT_ALL))
#تعریف_کرو sf_سیٹ_skip_ws(X)       ((X) ? (sf_چوٹی() |= _SF_SKIP_WS)  : (sf_چوٹی() &= ~_SF_SKIP_WS))
خارجی خالی sf_init(خالی);
خارجی خالی sf_ڈالو(خالی);
خارجی خالی sf_نکالو(خالی);


#اگر_ختم /* not defined FLEXDEF_H */
