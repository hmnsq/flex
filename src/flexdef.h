
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

#अगर_अघोषित FLEXDEF_H
#घोषणा FLEXDEF_H 1

#अगर_अघोषित USE_CONFIG_FOR_BUILD
# ifdef HAVE_CONFIG_H
#समावेश <config.h>
# endif
#अन्यथा
#समावेश <config_for_build.h>
#पूर्ण_अगर

#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <stdarg.h>
#समावेश <setjmp.h>
#समावेश <ctype.h>
#समावेश <string.h>
#समावेश <math.h>

#अगर_घोषित HAVE_ASSERT_H
#समावेश <assert.h>
#अन्यथा
#घोषणा निश्चित(Pred)
#पूर्ण_अगर

#अगर_घोषित HAVE_LIMITS_H
#समावेश <limits.h>
#पूर्ण_अगर
/* Required: dup() and dup2() in <unistd.h> */
#समावेश <unistd.h>
#अगर_घोषित HAVE_NETINET_IN_H
#समावेश <netinet/in.h>
#पूर्ण_अगर
#अगर_घोषित HAVE_SYS_PARAMS_H
#समावेश <sys/params.h>
#पूर्ण_अगर
/* Required: wait() in <sys/wait.h> */
#समावेश <sys/wait.h>
#अगर_घोषित HAVE_STDBOOL_H
#समावेश <stdbool.h>
#या_अगर !defined(__cplusplus) && (!defined(__STDC_VERSION__) || \
      __STDC_VERSION__ < 202311L)
# ifdef HAVE__BOOL
#  define bool _Bool
# अन्यथा
#  define bool पूर्णांक
# endif
# define false 0
# define true 1
#पूर्ण_अगर
#समावेश <stdarg.h>
/* Required: regcomp(), regexec() and regerror() in <regex.h> */
#समावेश <regex.h>
/* Required: strcasecmp() in <strings.h> */
#समावेश <strings.h>
#समावेश "flexint.h"

/* We use gettext. So, when we write strings which should be translated, we
 * mark them with _()
 */
#अगर defined(ENABLE_NLS) && ENABLE_NLS
#अगर_घोषित HAVE_LOCALE_H
#समावेश <locale.h>
#पूर्ण_अगर /* HAVE_LOCALE_H */
#समावेश "gettext.h"
#घोषणा _(String) gettext (String)
#अन्यथा
#घोषणा _(STRING) STRING
#पूर्ण_अगर /* ENABLE_NLS */

/* Always be prepared to generate an 8-bit scanner. */
#घोषणा CSIZE 256

/* Size of input alphabet - should be size of ASCII set. */
#अगर_अघोषित DEFAULT_CSIZE
#घोषणा DEFAULT_CSIZE 128
#पूर्ण_अगर

/* Maximum line length we'll have to deal with. */
#घोषणा MAXLINE 2048

#अगर_अघोषित MIN
#घोषणा MIN(x,y) ((x) < (y) ? (x) : (y))
#पूर्ण_अगर
#अगर_अघोषित MAX
#घोषणा MAX(x,y) ((x) > (y) ? (x) : (y))
#पूर्ण_अगर
#अगर_अघोषित ABS
#घोषणा ABS(x) ((x) < 0 ? -(x) : (x))
#पूर्ण_अगर

/* Whether an integer is a power of two */
#घोषणा is_power_of_2(n) ((n) > 0 && ((n) & ((n) - 1)) == 0)

/* Special chk[] values marking the slots taking by end-of-buffer and action
 * numbers.
 */
#घोषणा EOB_POSITION -1
#घोषणा ACTION_POSITION -2

/* Number of data items per line for -f output. */
#घोषणा NUMDATAITEMS 10

/* Number of lines of data in -f output before inserting a blank line for
 * readability.
 */
#घोषणा NUMDATALINES 10

/* transition_struct_out() definitions. */
#घोषणा TRANS_STRUCT_PRINT_लंबाई 14

/* Returns true if an nfa state has an epsilon out-transition slot
 * that can be used.  This definition is currently not used.
 */
#घोषणा FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans2[state] == NO_TRANSITION && \
	 finalst[state] != state)

/* Returns true if an nfa state has an epsilon out-transition character
 * and both slots are free
 */
#घोषणा SUPER_FREE_EPSILON(state) \
	(transchar[state] == SYM_EPSILON && \
	 trans1[state] == NO_TRANSITION) \

/* Maximum number of NFA states that can comprise a DFA state.  It's real
 * big because if there's a lot of rules, the initial state will have a
 * huge epsilon closure.
 */
#घोषणा INITIAL_MAX_DFA_आकार 750
#घोषणा MAX_DFA_आकार_INCREMENT 750


/* A note on the following masks.  They are used to mark accepting numbers
 * as being special.  As such, they implicitly limit the number of accepting
 * numbers (i.e., rules) because if there are too many rules the rule numbers
 * will overload the mask bits.  Fortunately, this limit is \large/ (0x2000 ==
 * 8192) so unlikely to actually cause any problems.  A check is made in
 * new_rule() to ensure that this limit is not reached.
 */

/* Mask to mark a trailing context accepting number. */
#घोषणा YY_TRAILING_MASK 0x2000

/* Mask to mark the accepting number of the "head" of a trailing context
 * rule.
 */
#घोषणा YY_TRAILING_शीर्ष_MASK 0x4000

/* Maximum number of rules, as outlined in the above note. */
#घोषणा MAX_RULE (YY_TRAILING_MASK - 1)


/* NIL must be 0.  If not, its special meaning when making equivalence classes
 * (it marks the representative of a given e.c.) will be unidentifiable.
 */
#घोषणा NIL 0

#घोषणा JAM -1			/* to mark a missing DFA transition */
#घोषणा NO_TRANSITION NIL
#घोषणा UNIQUE -1		/* marks a symbol as an e.c. representative */
#घोषणा INFINITE_REPEAT -1		/* for x{5,} constructions */

#घोषणा INITIAL_MAX_CCLS 100	/* max number of unique character classes */
#घोषणा MAX_CCLS_INCREMENT 100

/* Size of table holding members of character classes. */
#घोषणा INITIAL_MAX_CCL_TBL_आकार 500
#घोषणा MAX_CCL_TBL_आकार_INCREMENT 250

#घोषणा INITIAL_MAX_RULES 100	/* default maximum number of rules */
#घोषणा MAX_RULES_INCREMENT 100

#घोषणा INITIAL_MNS 2000	/* default maximum number of nfa states */
#घोषणा MNS_INCREMENT 1000	/* amount to bump above by if it's not enough */

#घोषणा INITIAL_MAX_DFAS 1000	/* default maximum number of dfa states */
#घोषणा MAX_DFAS_INCREMENT 1000

#घोषणा JAMSTATE -32766		/* marks a reference to the state that always jams */

/* Maximum number of NFA states. */
#घोषणा MAXIMUM_MNS 31999
#घोषणा MAXIMUM_MNS_LONG 1999999999

/* Enough so that if it's subtracted from an NFA state number, the result
 * is guaranteed to be negative.
 */
#घोषणा MARKER_DIFFERENCE (maximum_mns+2)

/* Maximum number of nxt/chk pairs for non-templates. */
#घोषणा INITIAL_MAX_XPAIRS 2000
#घोषणा MAX_XPAIRS_INCREMENT 2000

/* Maximum number of nxt/chk pairs needed for templates. */
#घोषणा INITIAL_MAX_TEMPLATE_XPAIRS 2500
#घोषणा MAX_TEMPLATE_XPAIRS_INCREMENT 2500

#घोषणा SYM_EPSILON (CSIZE + 1)	/* to mark transitions on the symbol epsilon */

#घोषणा INITIAL_MAX_SCS 40	/* maximum number of start conditions */
#घोषणा MAX_SCS_INCREMENT 40	/* amount to bump by if it's not enough */

#घोषणा ONE_ढेर_आकार 500	/* stack of states with only one out-transition */
#घोषणा SAME_TRANS -1		/* transition is the same as "default" entry for state */

/* The following percentages are used to tune table compression:

 * The percentage the number of out-transitions a state must be of the
 * number of equivalence classes in order to be considered for table
 * compaction by using protos.
 */
#घोषणा PROTO_आकार_PERCENTAGE 15

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * that the state's transition table is first compared with a potential
 * template of the most common out-transition instead of with the first
 * proto in the proto queue.
 */
#घोषणा CHECK_COM_PERCENTAGE 50

/* The percentage the number of differences between a state's transition
 * table and the proto it was first compared with must be of the total
 * number of out-transitions of the state in order to keep the first
 * proto as a good match and not search any further.
 */
#घोषणा FIRST_MATCH_DIFF_PERCENTAGE 10

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to use the proto as an acceptable close match.
 */
#घोषणा ACCEPTABLE_DIFF_PERCENTAGE 50

/* The percentage the number of homogeneous out-transitions of a state
 * must be of the number of total out-transitions of the state in order
 * to consider making a template from the state.
 */
#घोषणा TEMPLATE_SAME_PERCENTAGE 60

/* The percentage the number of differences between a state's transition
 * table and the most similar proto must be of the state's total number
 * of out-transitions to create a new proto from the state.
 */
#घोषणा NEW_PROTO_DIFF_PERCENTAGE 20

/* The percentage the total number of out-transitions of a state must be
 * of the number of equivalence classes in order to consider trying to
 * fit the transition table into "holes" inside the nxt/chk table.
 */
#घोषणा INTERIOR_FIT_PERCENTAGE 15

/* Size of region set aside to cache the complete transition table of
 * protos on the proto queue to enable quick comparisons.
 */
#घोषणा PROT_SAVE_आकार 2000

#घोषणा MSP 50			/* maximum number of saved protos (protos on the proto queue) */

/* Maximum number of out-transitions a state can have that we'll rummage
 * around through the interior of the internal fast table looking for a
 * spot for it.
 */
#घोषणा MAX_XTIONS_FULL_INTERIOR_FIT 4

/* Maximum number of rules which will be reported as being associated
 * with a DFA state.
 */
#घोषणा MAX_ASSOC_RULES 100

/* Number that, if used to subscript an array, has a good chance of producing
 * an error; should be small enough to fit into a short.
 */
#घोषणा BAD_SUBSCRIPT -32767

प्रकार क्रमागत trit_t {
	trit_unspecified = -1,
	trit_false = 0,
	trit_true = 1,
} trit;

/* Control variables.  These are in a struct to avoid having to replicate definitions
 * twice for each option, instead a single struct can be declared and externed.
 * If it's in this structure, it has a corresponding m4 symbol.
 */
काष्ठा ctrl_bundle_t {
	bool always_interactive;// always use character-by-character input
	खाता *backing_up_file;	// file to summarize backing-up states to 
	bool bison_bridge_lval;	// (--bison-bridge), bison pure calling convention. 
	bool bison_bridge_lloc;	// (--bison-locations), bison yylloc.
	माप_प्रकार bufsize;		// input buffer size
	bool C_plus_plus;	// (-+ flag) generate a C++ scanner class 
	पूर्णांक csize;		// size of character set for the scanner 
				// 128 for 7-bit chars and 256 for 8-bit 
	bool ddebug;		// (-d) make a "debug" scanner 
	trit do_main;		// generate main part to make lexer standalone.
	bool do_stdinit;	// whether to initialize yyin/yyout to stdin/stdout
	bool do_yylineno;	// if true, generate code to maintain yylineno 
	bool do_yywrap;		// do yywrap() processing on EOF. 
				// If false, EOF treated as "no more files" 
	bool fullspd;		// (-F flag) use Jacobson method of table representation 
	bool fulltbl;		// (-Cf flag) don't compress the DFA state table 
 	bool gen_पंक्ति_dirs;	// (no -L flag) generate #line directives 
	trit interactive;	// (-I) generate an interactive scanner
	bool never_interactive;	// always use buffered input, don't check for tty.
	bool lex_compat;	// (-l), maximize compatibility with AT&T lex 
	bool long_align;	// (-Ca flag), favor long-word alignment for speed 
	bool no_yyinput;	// suppress use of yyinput()
	bool no_unistd;		// suppress inclusion of unistd.h
	bool posix_compat;	// (-X) maximize compatibility with POSIX lex 
	अक्षर *prefix;		// prefix for externally visible names, default "yy" 
	trit reject_really_used;// Force generation of support code for reject operation
	bool reentrant;		// if true (-R), generate a reentrant C scanner
	bool rewrite;		// Appl;y magic rewre rles to special fumctions 
	bool ढेर_used;	// Enable use of start-condition stacks
	bool no_section3_escape;// True if the undocumented option --unsafe-no-m4-sect3-escape was passed
	bool spprdflt;		// (-s) suppress the default rule
	bool useecs;		// (-Ce flag) use equivalence classes 
	bool usemecs;		// (-Cm flag), use meta-equivalence classes 
	bool use_read;		// (-f, -F, or -Cr) use read() for scanner input 
       				// otherwise, use fread(). 
	अक्षर *yyclass;		// yyFlexLexer subclass to use for YY_DECL
	अक्षर *yydecl;		// user-specified prototype for yylex.
	पूर्णांक yylmax;		// Maximum buffer length if %array
	trit yymore_really_used;// Force geberation of support code for yymore
	bool yytext_is_array;	// if true (i.e., %array directive), then declare
				// yytext as array instead of a character pointer.
				// Nice and inefficient.
	bool noyyread;		// User supplied a yyread function, don't generate default
	अक्षर *userinit;		// Code fragment to be inserted before scanning
	अक्षर *preaction;	// Code fragment to be inserted before each action
	अक्षर *postaction;	// Code fragment to be inserted after each action
	अक्षर *emit;		// Specify target language to emit.
	अक्षर *yyterminate;	// Set a non-default termination hook.
	bool no_yypanic;	// if true, no not generate default yypanic function
 	// flags corresponding to the huge mass of --no-yy options
	bool no_yy_धकेलो_state;
	bool no_yy_निकालो_state;
	bool no_yy_शीर्ष_state;
	bool no_yyunput;
	bool no_yy_scan_बफर;
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
	स्थिर अक्षर *backend_name;	// What the back end tells you its name is
	स्थिर अक्षर *traceline_re;	// Regular expression for recognizing tracelines */
	स्थिर अक्षर *traceline_template;	// templare for emitting trace lines */
	bool have_state_entry_format;	// Do we know how to make a state entry address?
};

/* Environment variables.  These control the lexer operation, but do
 * not have corresponding m4 symbols and do not affect the behavior of
 * the generated parser.
 */
काष्ठा env_bundle_t {
	bool backing_up_report;	// (-b flag), generate "lex.backup" file 
				// listing backing-up states
	bool did_outfilename;	// whether outfilename was explicitly set
	अक्षर *headerfilename;	// name of the .h file to generate
	bool nowarn;		// (-w) do not generate warnings 
	पूर्णांक performance_hint;	// if > 0 (i.e., -p flag), generate a report 
				// relating to scanner performance; 
				// if > 1 (-p -p), report 
 				// on minor performance problems, too.
	अक्षर *outfilename;	// output file name
	bool printstats;	// (-v) dump statistics
	अक्षर *skelname;		// name of skeleton for code generation
	खाता *skelfile;		// the skeleton file'd descriptor
	bool trace;		// (-T) env.trace processing 
	bool trace_hex; 	// use hex in trace/debug outputs not octal
	bool use_stdout;	// the -t flag
};

/* Name and byte-width information on a type for code-generation purposes. */
काष्ठा packtype_t {
	अक्षर *name;
	माप_प्रकार width;
};

बाह्य काष्ठा ctrl_bundle_t ctrl;
बाह्य काष्ठा env_bundle_t env;

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
बाह्य पूर्णांक yymore_used, reject, real_reject, continued_action, in_rule;

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

बाह्य पूर्णांक datapos, dataline, linenum;
बाह्य पूर्णांक skel_ind;
बाह्य अक्षर *infilename;
बाह्य अक्षर *extra_type;
बाह्य अक्षर **निवेश_files;
बाह्य पूर्णांक अंक_निवेश_files;
बाह्य अक्षर *program_name;

बाह्य अक्षर *action_array;
बाह्य पूर्णांक action_आकार;
बाह्य पूर्णांक defs1_offset, prolog_offset, action_offset, action_सूचकांक;


/* Variables for stack of states having only one out-transition:
 * onestate - state number
 * onesym - transition symbol
 * onenext - target state
 * onedef - default base entry
 * onesp - stack pointer
 */

बाह्य पूर्णांक onestate[ONE_ढेर_आकार], onesym[ONE_ढेर_आकार];
बाह्य पूर्णांक onenext[ONE_ढेर_आकार], onedef[ONE_ढेर_आकार], onesp;


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

बाह्य पूर्णांक maximum_mns, current_mns, current_max_rules;
बाह्य पूर्णांक अंक_rules, अंक_eof_rules, default_rule, lastnfa;
बाह्य पूर्णांक *firstst, *lastst, *finalst, *transchar, *trans1, *trans2;
बाह्य पूर्णांक *accptnum, *assoc_rule, *state_type;
बाह्य पूर्णांक *rule_type, *rule_linenum;
/* rule_useful[], rule_has_nl[] and ccl_has_nl[] are boolean arrays,
 * but allocated as char arrays for size. */
बाह्य अक्षर *rule_useful, *rule_has_nl, *ccl_has_nl;
बाह्य पूर्णांक nlch;
बाह्य माप_प्रकार footprint;


/* Different types of states; values are useful as masks, as well, for
 * routines like check_trailing_context().
 */
#घोषणा STATE_NORMAL 0x1
#घोषणा STATE_TRAILING_CONTEXT 0x2

/* Global holding current type of state we're making. */

बाह्य पूर्णांक current_state_type;

/* Different types of rules. */
#घोषणा RULE_NORMAL 0
#घोषणा RULE_VARIABLE 1

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

बाह्य पूर्णांक numtemps, numprots, protprev[MSP], protnext[MSP], prottbl[MSP];
बाह्य पूर्णांक protcomst[MSP], firstprot, lastprot, protsave[PROT_SAVE_आकार];


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
बाह्य पूर्णांक numecs, nextecm[CSIZE + 1], ecgroup[CSIZE + 1], nummecs;

/* Meta-equivalence classes are indexed starting at 1, so it's possible
 * that they will require positions from 1 .. CSIZE, i.e., CSIZE + 1
 * slots total (since the arrays are 0-based).  nextecm[] and ecgroup[]
 * don't require the extra position since they're indexed from 1 .. CSIZE - 1.
 */
बाह्य पूर्णांक tecfwd[CSIZE + 1], tecbck[CSIZE + 1];


/* Variables for start conditions:
 * lastsc - last start condition created
 * current_max_scs - current limit on number of start conditions
 * scset - set of rules active in start condition
 * scbol - set of rules active only at the beginning of line in a s.c.
 * scxclu - true if start condition is exclusive
 * sceof - true if start condition has EOF rule
 * scname - start condition name
 */

बाह्य पूर्णांक lastsc, *scset, *scbol;
/* scxclu[] and sceof[] are boolean arrays, but allocated as char
 * arrays for size. */
बाह्य अक्षर *scxclu, *sceof;
बाह्य पूर्णांक current_max_scs;
बाह्य स्थिर अक्षर **scname;


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

बाह्य पूर्णांक current_max_dfa_आकार, current_max_xpairs;
बाह्य पूर्णांक current_max_template_xpairs, current_max_dfas;
बाह्य पूर्णांक lastdfa, *nxt, *chk, *tnxt;
बाह्य पूर्णांक *base, *def, *nultrans, NUL_ec, tblend, firstfree, **dss,
	*dfasiz;
बाह्य जोड़ dfaacc_union {
	पूर्णांक    *dfaacc_set;
	पूर्णांक     dfaacc_state;
}      *dfaacc;
बाह्य पूर्णांक *accsiz, *dhash, numas;
बाह्य पूर्णांक numsnpairs, jambase, jamstate;
बाह्य पूर्णांक end_of_बफर_state;

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

बाह्य पूर्णांक lastccl, *cclmap, *ccllen, *cclng, cclreuse;
बाह्य पूर्णांक current_maxccls, current_max_ccl_tbl_आकार;
बाह्य अचिन्हित अक्षर *ccltbl;


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

बाह्य अक्षर nmstr[MAXLINE];
बाह्य पूर्णांक sectnum, nummt, hshcol, dfaeql, numeps, eps2, अंक_reallocs, nmval;
बाह्य पूर्णांक tmpuses, totnst, peakpairs, numuniq, numdup, hshsave;
बाह्य पूर्णांक अंक_backing_up, bol_needed;

व्योम   *allocate_array(पूर्णांक, माप_प्रकार);
व्योम   *reallocate_array(व्योम *, पूर्णांक, माप_प्रकार);

#घोषणा allocate_integer_array(आकार) \
	allocate_array(आकार, माप(पूर्णांक))

#घोषणा reallocate_integer_array(array,आकार) \
	reallocate_array((व्योम *) array, आकार, माप(पूर्णांक))

#घोषणा allocate_int_ptr_array(आकार) \
	allocate_array(आकार, माप(पूर्णांक *))

#घोषणा allocate_char_ptr_array(आकार) \
	allocate_array(आकार, माप(अक्षर *))

#घोषणा reallocate_int_ptr_array(array,आकार) \
	reallocate_array((व्योम *) array, आकार, माप(पूर्णांक *))

#घोषणा reallocate_char_ptr_array(array,आकार) \
	reallocate_array((व्योम *) array, आकार, माप(अक्षर *))

#घोषणा allocate_character_array(आकार) \
	allocate_array( आकार, माप(अक्षर))

#घोषणा reallocate_character_array(array,आकार) \
	reallocate_array((व्योम *) array, आकार, माप(अक्षर))

#घोषणा allocate_Character_array(आकार) \
	allocate_array(आकार, माप(अचिन्हित अक्षर))

#घोषणा reallocate_Character_array(array,आकार) \
	reallocate_array((व्योम *) array, आकार, माप(अचिन्हित अक्षर))


/* External functions that are cross-referenced among the flex source files. */


/* from file ccl.c */

बाह्य व्योम ccladd(पूर्णांक, पूर्णांक);	/* add a single character to a ccl */
बाह्य पूर्णांक cclinit(व्योम);	/* make an empty ccl */
बाह्य व्योम cclnegate(पूर्णांक);	/* negate a ccl */
बाह्य पूर्णांक ccl_set_diff (पूर्णांक a, पूर्णांक b); /* set difference of two ccls. */
बाह्य पूर्णांक ccl_set_union (पूर्णांक a, पूर्णांक b); /* set union of two ccls. */

/* List the members of a set of characters in CCL form. */
बाह्य व्योम list_character_set(खाता *, पूर्णांक[]);


/* from file dfa.c */

/* Increase the maximum number of dfas. */
बाह्य व्योम increase_max_dfas(व्योम);

बाह्य माप_प्रकार ntod(व्योम);	/* convert a ndfa to a dfa */


/* from file ecs.c */

/* Convert character classes to set of equivalence classes. */
बाह्य व्योम ccl2ecl(व्योम);

/* Associate equivalence class numbers with class members. */
बाह्य पूर्णांक cre8ecs(पूर्णांक[], पूर्णांक[], पूर्णांक);

/* Update equivalence classes based on character class transitions. */
बाह्य व्योम mkeccl(अचिन्हित अक्षर[], पूर्णांक, पूर्णांक[], पूर्णांक[], पूर्णांक, पूर्णांक);

/* Create equivalence class for single character. */
बाह्य व्योम mkechar(पूर्णांक, पूर्णांक[], पूर्णांक[]);


/* from file gen.c */

/* Set a conditional amd make it visible in generated code */
बाह्य व्योम visible_define (स्थिर अक्षर *);

/* And again, with an explicit value part. */
बाह्य व्योम visible_define_str (स्थिर अक्षर *, स्थिर अक्षर *);

/* This time the value part is an int */
बाह्य व्योम visible_define_int (स्थिर अक्षर *, स्थिर पूर्णांक);

/* generate transition tables */
बाह्य व्योम make_tables(व्योम);

/* Select a type for optimal packing */
काष्ठा packtype_t *optimize_pack(माप_प्रकार);

/* from file main.c */

बाह्य व्योम check_options(व्योम);
बाह्य व्योम flexend(पूर्णांक);
बाह्य व्योम usage(व्योम);


/* from file misc.c */

/* Add the given text to the stored actions. */
बाह्य व्योम add_action(स्थिर अक्षर *new_text);

/* True if a string is all lower case. */
बाह्य पूर्णांक all_lower(अक्षर *);

/* True if a string is all upper case. */
बाह्य पूर्णांक all_upper(अक्षर *);

/* Compare two integers for use by qsort. */
बाह्य पूर्णांक intcmp(स्थिर व्योम *, स्थिर व्योम *);

/* Check a character to make sure it's in the expected range. */
बाह्य व्योम check_char(पूर्णांक c);

/* Replace upper-case letter to lower-case. */
बाह्य अचिन्हित अक्षर clower(पूर्णांक);

/* strdup() that fails fatally on allocation failures. */
बाह्य अक्षर *xstrdup(स्थिर अक्षर *);

/* Compare two characters for use by qsort with '\0' sorting last. */
बाह्य पूर्णांक cclcmp(स्थिर व्योम *, स्थिर व्योम *);

/* Finish up a block of data declarations. */
बाह्य व्योम dataend(स्थिर अक्षर *);

/* Flush generated data statements. */
बाह्य व्योम dataflush(व्योम);

/* Report an error message and terminate. */
बाह्य व्योम flexerror(स्थिर अक्षर *);

/* Report a fatal error message and terminate. */
बाह्य व्योम flexfatal(स्थिर अक्षर *);

/* Report a fatal error with a pinpoint, and terminate */
#अगर_घोषित HAVE_DECL___FUNC__
#घोषणा flex_die(संदेश) \
    करो{ \
        ख_लिखो (मानक_त्रुटि,\
                _("%s: fatal internal error at %s:%d (%s): %s\n"),\
                program_name, __खाता__, (पूर्णांक)__LINE__,\
                __func__,संदेश);\
        FLEX_EXIT(1);\
    }जबतक(0)
#अन्यथा /* ! HAVE_DECL___FUNC__ */
#घोषणा flex_die(संदेश) \
    करो{ \
        ख_लिखो (मानक_त्रुटि,\
                _("%s: fatal internal error at %s:%d %s\n"),\
                program_name, __खाता__, (पूर्णांक)__LINE__,\
                संदेश);\
        FLEX_EXIT(1);\
    }जबतक(0)
#पूर्ण_अगर /* ! HAVE_DECL___func__ */

/* Report an error message formatted  */
बाह्य व्योम lerr(स्थिर अक्षर *, ...)
#अगर defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#पूर्ण_अगर
;

/* Like lerr, but also exit after displaying message. */
बाह्य व्योम lerr_fatal(स्थिर अक्षर *, ...)
#अगर defined(__GNUC__) && __GNUC__ >= 3
    __attribute__((__format__(__printf__, 1, 2)))
#पूर्ण_अगर
;

/* Spit out a "#line" statement. */
बाह्य व्योम पंक्ति_directive_out(खाता *, अक्षर *, पूर्णांक);

/* Mark the current position in the action array as the end of the section 1
 * user defs.
 */
बाह्य व्योम mark_defs1(व्योम);

/* Mark the current position in the action array as the end of the prolog. */
बाह्य व्योम mark_prolog(व्योम);

/* Generate a data statement for a two-dimensional array. */
बाह्य व्योम mk2data(पूर्णांक);

बाह्य व्योम mkdata(पूर्णांक);	/* generate a data statement */

/* Return the integer represented by a string of digits. */
बाह्य पूर्णांक myctoi(स्थिर अक्षर *);

/* Return character corresponding to escape sequence. */
बाह्य अचिन्हित अक्षर myesc(अचिन्हित अक्षर[]);

/* Output a (possibly-formatted) string to the generated scanner. */
बाह्य व्योम out(स्थिर अक्षर *);
बाह्य व्योम out_dec(स्थिर अक्षर *, पूर्णांक);
बाह्य व्योम out_dec2(स्थिर अक्षर *, पूर्णांक, पूर्णांक);
बाह्य व्योम out_hex(स्थिर अक्षर *, अचिन्हित पूर्णांक);
बाह्य व्योम out_str(स्थिर अक्षर *, स्थिर अक्षर *);
बाह्य व्योम out_str_dec(स्थिर अक्षर *, स्थिर अक्षर *, पूर्णांक);
बाह्य व्योम outc(पूर्णांक);
बाह्य व्योम outn(स्थिर अक्षर *);
बाह्य व्योम out_m4_define(स्थिर अक्षर* def, स्थिर अक्षर* val);

/* Return a printable version of the given character, which might be
 * 8-bit.
 */
बाह्य अक्षर *readable_form(पूर्णांक);

/* Output a yy_trans_info structure. */
बाह्य व्योम transition_struct_out(पूर्णांक, पूर्णांक);

/* Only needed when using certain broken versions of bison to build parse.c. */
बाह्य व्योम *yy_flex_xmalloc(पूर्णांक);


/* from file nfa.c */

/* Add an accepting state to a machine. */
बाह्य व्योम add_accept(पूर्णांक, पूर्णांक);

/* Make a given number of copies of a singleton machine. */
बाह्य पूर्णांक copysingl(पूर्णांक, पूर्णांक);

/* Debugging routine to write out an nfa. */
बाह्य व्योम dumpnfa(पूर्णांक);

/* Finish up the processing for a rule. */
बाह्य व्योम finish_rule(पूर्णांक, bool, पूर्णांक, पूर्णांक, पूर्णांक);

/* Connect two machines together. */
बाह्य पूर्णांक link_machines(पूर्णांक, पूर्णांक);

/* Mark each "beginning" state in a machine as being a "normal" (i.e.,
 * not trailing context associated) state.
 */
बाह्य व्योम mark_beginning_as_normal(पूर्णांक);

/* Make a machine that branches to two machines. */
बाह्य पूर्णांक mkbranch(पूर्णांक, पूर्णांक);

बाह्य पूर्णांक mkclos(पूर्णांक);	/* convert a machine into a closure */
बाह्य पूर्णांक mkopt(पूर्णांक);	/* make a machine optional */

/* Make a machine that matches either one of two machines. */
बाह्य पूर्णांक mkor(पूर्णांक, पूर्णांक);

/* Convert a machine into a positive closure. */
बाह्य पूर्णांक mkposcl(पूर्णांक);

बाह्य पूर्णांक mkrep(पूर्णांक, पूर्णांक, पूर्णांक);	/* make a replicated machine */

/* Create a state with a transition on a given symbol. */
बाह्य पूर्णांक mkstate(पूर्णांक);

बाह्य व्योम new_rule(व्योम);	/* initialize for a new rule */


/* from file parse.y */

/* Build the "<<EOF>>" action for the active start conditions. */
बाह्य व्योम build_eof_action(व्योम);

/* Write out a message formatted with one string, pinpointing its location. */
बाह्य व्योम format_pinpoint_message(स्थिर अक्षर *, स्थिर अक्षर *);

/* Write out a message, pinpointing its location. */
बाह्य व्योम pinpoint_message(स्थिर अक्षर *);

/* Write out a warning, pinpointing it at the given line. */
बाह्य व्योम पंक्ति_warning(स्थिर अक्षर *, पूर्णांक);

/* Write out a message, pinpointing it at the given line. */
बाह्य व्योम पंक्ति_pinpoint(स्थिर अक्षर *, पूर्णांक);

/* Report a formatted syntax error. */
बाह्य व्योम format_synerr(स्थिर अक्षर *, स्थिर अक्षर *);
बाह्य व्योम synerr(स्थिर अक्षर *);	/* report a syntax error */
बाह्य व्योम format_warn(स्थिर अक्षर *, स्थिर अक्षर *);
बाह्य व्योम lwarn(स्थिर अक्षर *);	/* report a warning */
बाह्य व्योम yyerror(स्थिर अक्षर *);	/* report a parse error */
बाह्य पूर्णांक yyparse(व्योम);		/* the YACC parser */

/* Ship a comment to the generated output */
बाह्य व्योम comment(स्थिर अक्षर *);

/* from file scan.l */

/* The Flex-generated scanner for flex. */
बाह्य पूर्णांक flexscan(व्योम);

/* Open the given file (if NULL, stdin) for scanning. */
बाह्य व्योम set_निवेश_file(अक्षर *);

/* from file skeletons.c */

/* return the correct file suffix for the selected back end */
स्थिर अक्षर *suffix (व्योम);

/* Mine a text-valued property out of the skeleton file */
बाह्य स्थिर अक्षर *skel_property(स्थिर अक्षर *);

/* Is the default back end selected?*/
बाह्य bool is_default_backend(व्योम);

/* Select a backend by name */
बाह्य व्योम backend_by_name(स्थिर अक्षर *);

/* Write out one section of the skeleton file. */
बाह्य व्योम skelout(bool);

/* from file sym.c */

/* Save the text of a character class. */
बाह्य व्योम cclinstal(अक्षर[], पूर्णांक);

/* Lookup the number associated with character class. */
बाह्य पूर्णांक ccllookup(अक्षर[]);

बाह्य व्योम ndinstal(स्थिर अक्षर *, अक्षर[]);	/* install a name definition */
बाह्य अक्षर *ndlookup(स्थिर अक्षर *);	/* lookup a name definition */

/* Increase maximum number of SC's. */
बाह्य व्योम scextend(व्योम);
बाह्य व्योम scinstal(स्थिर अक्षर *, bool);	/* make a start condition */

/* Lookup the number associated with a start condition. */
बाह्य पूर्णांक sclookup(स्थिर अक्षर *);

/* Supply context argument for a function if required */
बाह्य व्योम context_call(अक्षर *);

/* from file tblcmp.c */

/* Build table entries for dfa state. */
बाह्य व्योम bldtbl(पूर्णांक[], पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);

बाह्य व्योम cmptmps(व्योम);	/* compress template table entries */
बाह्य व्योम expand_nxt_chk(व्योम);	/* increase nxt/chk arrays */

/* Finds a space in the table for a state to be placed. */
बाह्य पूर्णांक find_table_space(पूर्णांक *, पूर्णांक);
बाह्य व्योम inittbl(व्योम);	/* initialize transition tables */

/* Make the default, "jam" table entries. */
बाह्य व्योम mkdeftbl(व्योम);

/* Create table entries for a state (or state fragment) which has
 * only one out-transition.
 */
बाह्य व्योम mk1tbl(पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);

/* Place a state into full speed transition table. */
बाह्य व्योम place_state(पूर्णांक *, पूर्णांक, पूर्णांक);

/* Save states with only one out-transition to be processed later. */
बाह्य व्योम stack1(पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);


/* from file yylex.c */

बाह्य पूर्णांक yylex(व्योम);

/* A growable array. See buf.c. */
काष्ठा Buf {
	व्योम   *elts;		/* elements. */
	पूर्णांक     nelts;		/* number of elements. */
	माप_प्रकार  elt_आकार;	/* in bytes. */
	पूर्णांक     nmax;		/* max capacity of elements. */
};

बाह्य व्योम buf_init(काष्ठा Buf * buf, माप_प्रकार elem_आकार);
बाह्य व्योम buf_destroy(काष्ठा Buf * buf);
बाह्य काष्ठा Buf *buf_append(काष्ठा Buf * buf, स्थिर व्योम *ptr, पूर्णांक n_elem);
बाह्य काष्ठा Buf *buf_strappend(काष्ठा Buf *, स्थिर अक्षर *str);
बाह्य काष्ठा Buf *buf_strnappend(काष्ठा Buf *, स्थिर अक्षर *str, पूर्णांक nchars);
बाह्य काष्ठा Buf *buf_prints(काष्ठा Buf *buf, स्थिर अक्षर *fmt, स्थिर अक्षर* s);

बाह्य काष्ठा Buf userdef_buf; /* a string buffer for #define's generated by user-options on cmd line. */
बाह्य काष्ठा Buf शीर्ष_buf;     /* contains %top code. String buffer. */

/* For blocking out code from the header file. */
#घोषणा OUT_BEGIN_CODE() outn("m4_ifdef( [[M4_YY_IN_HEADER]],,[[m4_dnl")
#घोषणा OUT_END_CODE()   outn("]])")

/* For setjmp/longjmp (instead of calling exit(2)). Linkage in main.c */
बाह्य लाँघ_बफ flex_main_jmp_buf;

#घोषणा FLEX_EXIT(status) दीर्घ_लाँघ(flex_main_jmp_buf,(status)+1)

/* Removes all \n and \r chars from tail of str. returns str. */
बाह्य अक्षर *chomp (अक्षर *str);

/* ctype functions forced to return boolean */
#घोषणा b_isalnum(c) (है_अक्षर_अंक(c)?true:false)
#घोषणा b_isalpha(c) (है_अक्षर(c)?true:false)
#घोषणा b_isascii(c) (isascii(c)?true:false)
#घोषणा b_isblank(c) (isblank(c)?true:false)
#घोषणा b_iscntrl(c) (है_नियंत्रण(c)?true:false)
#घोषणा b_isdigit(c) (है_अंक(c)?true:false)
#घोषणा b_isgraph(c) (है_चित्र(c)?true:false)
#घोषणा b_islower(c) (है_छोटा(c)?true:false)
#घोषणा b_isprint(c) (है_छाप(c)?true:false)
#घोषणा b_ispunct(c) (है_विराम(c)?true:false)
#घोषणा b_isspace(c) (है_खाली(c)?true:false)
#घोषणा b_isupper(c) (है_बड़ा(c)?true:false)
#घोषणा b_isxdigit(c) (है_षष्ठादशक(c)?true:false)

/* return true if char is uppercase or lowercase. */
bool has_case(पूर्णांक c);

/* Change case of character if possible. */
पूर्णांक reverse_case(पूर्णांक c);

/* return false if [c1-c2] is ambiguous for a caseless scanner. */
bool range_covers_case (पूर्णांक c1, पूर्णांक c2);

/*
 *  From "filter.c"
 */

/** A single stdio filter to execute.
 *  The filter may be external, such as "sed", or it
 *  may be internal, as a function call.
 */
काष्ठा filter {
    पूर्णांक    (*filter_func)(काष्ठा filter*); /**< internal filter function */
    व्योम * extra;         /**< extra data passed to filter_func */
	पूर्णांक     argc;         /**< arg count */
	स्थिर अक्षर ** argv;   /**< arg vector, \0-terminated */
    काष्ठा filter * अग्र; /**< next filter or NULL */
};

/* output filter chain */
बाह्य काष्ठा filter * output_chain;
बाह्य काष्ठा filter *filter_create_ext (काष्ठा filter * chain, स्थिर अक्षर *cmd, ...);
काष्ठा filter *filter_create_int(काष्ठा filter *chain,
				  पूर्णांक (*filter_func) (काष्ठा filter *),
                  व्योम *extra);
बाह्य bool filter_apply_chain(काष्ठा filter * chain);
बाह्य पूर्णांक filter_truncate(काष्ठा filter * chain, पूर्णांक max_len);
बाह्य पूर्णांक filter_tee_header(काष्ठा filter *chain);
बाह्य पूर्णांक filter_fix_linedirs(काष्ठा filter *chain);


/*
 * From "regex.c"
 */

बाह्य regex_t regex_linedir;
bool flex_init_regex(स्थिर अक्षर *);
व्योम flex_regcomp(regex_t *preg, स्थिर अक्षर *regex, पूर्णांक cflags);
अक्षर   *regmatch_dup (regmatch_t * m, स्थिर अक्षर *src);
अक्षर   *regmatch_cpy (regmatch_t * m, अक्षर *dest, स्थिर अक्षर *src);
पूर्णांक regmatch_len (regmatch_t * m);
पूर्णांक regmatch_strtol (regmatch_t * m, स्थिर अक्षर *src, अक्षर **endptr, पूर्णांक base);
bool regmatch_empty (regmatch_t * m);

/* From "scanflags.h" */
प्रकार अचिन्हित पूर्णांक scanflags_t;
बाह्य scanflags_t* _sf_stk;
बाह्य माप_प्रकार sf_शीर्ष_ix, _sf_max; /**< stack of scanner flags. */
#घोषणा _SF_CASE_INS   ((scanflags_t) 0x0001)
#घोषणा _SF_DOT_ALL    ((scanflags_t) 0x0002)
#घोषणा _SF_SKIP_WS    ((scanflags_t) 0x0004)
#घोषणा sf_शीर्ष()           (_sf_stk[sf_शीर्ष_ix])
#घोषणा sf_case_ins()      (sf_शीर्ष() & _SF_CASE_INS)
#घोषणा sf_dot_all()       (sf_शीर्ष() & _SF_DOT_ALL)
#घोषणा sf_skip_ws()       (sf_शीर्ष() & _SF_SKIP_WS)
#घोषणा sf_set_case_ins(X)      ((X) ? (sf_शीर्ष() |= _SF_CASE_INS) : (sf_शीर्ष() &= ~_SF_CASE_INS))
#घोषणा sf_set_dot_all(X)       ((X) ? (sf_शीर्ष() |= _SF_DOT_ALL)  : (sf_शीर्ष() &= ~_SF_DOT_ALL))
#घोषणा sf_set_skip_ws(X)       ((X) ? (sf_शीर्ष() |= _SF_SKIP_WS)  : (sf_शीर्ष() &= ~_SF_SKIP_WS))
बाह्य व्योम sf_init(व्योम);
बाह्य व्योम sf_धकेलो(व्योम);
बाह्य व्योम sf_निकालो(व्योम);


#पूर्ण_अगर /* not defined FLEXDEF_H */
