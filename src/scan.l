/* scan.l - scanner for flex input -*-C-*- */

%top{
/* flexdef.h includes config.h, which may contain macros that alter the API */
/* of libc functions. Must include first before any libc header. */
#অন্তর্ভাব "flexdef.h"
}

%{
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

#অন্তর্ভাব "parse.h"
বাহ্য bool tablesverify, tablesext;
বাহ্য bool trlcontxt; /* Set in parse.y for each rule. */
বাহ্য ধ্রুব বর্ণ *escaped_qstart, *escaped_qend;

#define M4QSTART "[""["
#define M4QEND "]""]"

#define ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#define ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#define ACTION_ECHO add_action( yytext )
#define ACTION_ECHO_QSTART add_action (ESCAPED_QSTART)
#define ACTION_ECHO_QEND   add_action (ESCAPED_QEND)

#define MARK_END_OF_PROLOG mark_prolog();

#define YY_DECL \
	পূর্ণাঙ্ক flexscan(শূন্য)

#define RETURNCHAR \
	yylval = (unsigned বর্ণ) yytext[0]; \
	প্রত্যাগম CHAR;

#define RETURNNAME \
	যদি(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, পরিমাণ(nmstr) ); \
	প্রত্যাগম NAME; \
	 } \
	অন্যথা \
	 কুরু { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } যাবত্ (0)

#define PUT_BACK_STRING(str, start) \
	{ size_t i = strlen( str );	\
	  যাবত্ ( i > start )		\
	    unput((str)[--i]);		\
	}

#define CHECK_REJECT(str) \
	যদি ( all_upper( str ) ) \
		reject = true;

#define CHECK_YYREJECT(str) \
	যদি ( all_lower( str ) ) \
		reject = true;

#define YY_USER_INIT \
	যদি ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#define START_CODEBLOCK(x) কুরু { \
    /* Emit the needed line directive... */\
    যদি (indented_code == false) { \
        যদি (!x) linenum++; \
        সারি_directive_out(রিক্ত, infilename, linenum);	\
    } \
    add_action(M4QSTART); \
    yy_ঠেলো_state(CODEBLOCK); \
    যদি ((indented_code = x)) ACTION_ECHO; \
} যাবত্(0)

#define END_CODEBLOCK কুরু { \
    yy_বের_করো_state();\
    add_action(M4QEND); \
    যদি (!indented_code) সারি_directive_out(রিক্ত, রিক্ত, linenum);	\
} যাবত্ (0)

%}

%option caseless nodefault noreject স্তূপ noyy_শীর্ষ_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL অঙ্ক_2 QUOTE
%x FIRSTCCL CCL ACTION RECOVER COMMENT ACTION_STRING PERCENT_BRACE_ACTION
%x OPTION LINEDIR CODEBLOCK_MATCH_BRACE
%x GROUP_WITH_PARAMS
%x GROUP_MINUS_PARAMS
%x EXTENDED_COMMENT
%x COMMENT_DISCARD CODE_COMMENT
%x SECT3_NOESCAPE
%x CHARACTER_CONSTANT

WS		[[:blank:]]+
OPTWS		[[:blank:]]*
NOT_WS		[^[:blank:]\r\n]

NL		\r?\n

NAME		([[:alpha:]_][[:alnum:]_-]*)
NOT_NAME	[^[:alpha:]_*\n]+

SCNAME		{NAME}

ESCSEQ		(\\([^\n]|[0-7]{1,3}|x[[:xdigit:]]{1,2}))

FIRST_CCL_CHAR	([^\\\n]|{ESCSEQ})
CCL_CHAR	([^\\\n\]]|{ESCSEQ})
CCL_রাশিমালা	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
শূন্য context_call(বর্ণ *);
শূন্য context_member(বর্ণ *, ধ্রুব বর্ণ *);
#undef yyreject
%}
%%
	স্থির পূর্ণাঙ্ক bracelevel, didadef, indented_code;
	স্থির bool doing_rule_action = false;
	স্থির bool option_sense;

	স্থির bool doing_codeblock = false;
	পূর্ণাঙ্ক brace_depth=0, brace_start_সারি=0;
	বর্ণ nmdef[MAXLINE];


<INITIAL>{
	^{WS}		START_CODEBLOCK(true);
	^"/*"		add_action("/*[""["); yy_ঠেলো_state( COMMENT );
	^#{OPTWS}সারি{WS}	yy_ঠেলো_state( LINEDIR );
	^"%s"{NAME}?	প্রত্যাগম SCDECL;
	^"%x"{NAME}?	প্রত্যাগম XSCDECL;
	^"%{".*{NL}	START_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		বর্ণ trampoline[512];
                brace_start_সারি = linenum;
                ++linenum;
		snprintf(trampoline, পরিমাণ(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                যদি (ctrl.gen_সারি_dirs)
                    buf_strappend(&শীর্ষ_buf, trampoline);
                brace_depth = 1;
                yy_ঠেলো_state(CODEBLOCK_MATCH_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			সারি_directive_out(রিক্ত, infilename, linenum);
			BEGIN(SECT2PROLOG);
			প্রত্যাগম SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); প্রত্যাগম TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			যদি(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, পরিমাণ(nmstr) );
			 }
			অন্যথা
			 {
			   synerr( _("Definition name too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			didadef = false;
			BEGIN(PICKUPDEF);
			}

	{SCNAME}	RETURNNAME;
	^{OPTWS}{NL}	++linenum; /* allows blank lines in section 1 */
	{OPTWS}{NL}	ACTION_ECHO; ++linenum; /* maybe end of comment line */
}


<COMMENT,CODE_COMMENT>{ /* */
        [^\[\]\*\n]*  ACTION_ECHO;
        .           ACTION_ECHO;

	{NL}	    ++linenum; ACTION_ECHO;
}
<COMMENT>{
	"*/"	    add_action("*/]""]"); yy_বের_করো_state();
}
<CODE_COMMENT>{
        "*/"        ACTION_ECHO; yy_বের_করো_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_বের_করো_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_বের_করো_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_বের_করো_state();
	[[:digit:]]+	linenum = myctoi( yytext );

	"\""[^""\n]*"\""	{
			মুক্ত(infilename);
			infilename = xstrdup(yytext + 1);
			infilename[strlen( infilename ) - 1] = '\0';
			}
	.		/* ignore spurious characters */
}
<ACTION,CODEBLOCK,ACTION_STRING,PERCENT_BRACE_ACTION,CHARACTER_CONSTANT,COMMENT,CODE_COMMENT>{
   {M4QSTART}   ACTION_ECHO_QSTART;
   {M4QEND}     ACTION_ECHO_QEND;
}

<CODEBLOCK>{
	^"%}".*{NL}	++linenum; END_CODEBLOCK;
	[^\n%\[\]]*         ACTION_ECHO;
        .		ACTION_ECHO;
	{NL}		{
			++linenum;
			ACTION_ECHO;
			যদি ( indented_code ) END_CODEBLOCK;
			}
}

<CODEBLOCK_MATCH_BRACE>{
    "}"     {
                যদি( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_বের_করো_state();
                }অন্যথা
                    buf_strnappend(&শীর্ষ_buf, yytext, yyleng);
            }

    "{"     {
                brace_depth++;
                buf_strnappend(&শীর্ষ_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&শীর্ষ_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&শীর্ষ_buf, escaped_qstart, (পূর্ণাঙ্ক) strlen(escaped_qstart));
    {M4QEND}    buf_strnappend(&শীর্ষ_buf, escaped_qend, (পূর্ণাঙ্ক) strlen(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&শীর্ষ_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_start_সারি;
                synerr(_("Unmatched '{'"));
                প্রত্যাগম YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        যদি(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, পরিমাণ(nmdef) );
 		         }
 		        অন্যথা
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = strlen( nmdef );
			    যাবত্ (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			যদি ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		প্রত্যাগম '=';
	[[:digit:]]+	{nmval = atoi(yytext); প্রত্যাগম TOK_NUMERIC;}

	no		option_sense = ! option_sense;

	7bit		ctrl.csize = option_sense ? 128 : 256;
	8bit		ctrl.csize = option_sense ? 256 : 128;

	align		ctrl.long_align = option_sense;
	always-interactive	{
			ctrl.always_interactive = option_sense;
			ctrl.interactive = (trit)option_sense;
			}
	array		ctrl.yytext_is_array = option_sense;
	backup		env.backing_up_report = option_sense;
	batch		ctrl.interactive = (trit)!option_sense;
	bison-bridge     ctrl.bison_bridge_lval = option_sense;
	bison-locations  { যদি((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|পক্ষ-sensitive		sf_set_case_ins(!option_sense);
	caseless|পক্ষ-insensitive	sf_set_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	স্বভাব		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	full		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	প্রবেশ		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	সারি		ctrl.gen_সারি_dirs = option_sense;
	main		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			যদি (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	pointer		ctrl.yytext_is_array = ! option_sense;
	পঠ		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_used = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	স্তূপ		ctrl.স্তূপ_used = option_sense;
	stdinit		ctrl.do_stdinit = option_sense;
	stdout		env.use_stdout = option_sense;
	unistd		ctrl.no_unistd = ! option_sense;
	unput		ctrl.no_yyunput = ! option_sense;
	yyunput		ctrl.no_yyunput = ! option_sense;
	verbose		env.printstats = option_sense;
	warn		env.nowarn = ! option_sense;
	yylineno	ctrl.do_yylineno = option_sense;
	yymore		ctrl.yymore_really_used = option_sense;
	yywrap		ctrl.do_yywrap = option_sense;
	yyread		ctrl.noyyread = !option_sense;

	yypanic		ctrl.no_yypanic = !option_sense;

	yy_ঠেলো_state	ctrl.no_yy_ঠেলো_state = ! option_sense;
	yy_বের_করো_state	ctrl.no_yy_বের_করো_state = ! option_sense;
	yy_শীর্ষ_state	ctrl.no_yy_শীর্ষ_state = ! option_sense;

	yy_scan_buffer	ctrl.no_yy_scan_buffer = ! option_sense;
	yy_scan_bytes	ctrl.no_yy_scan_bytes = ! option_sense;
	yy_scan_string	ctrl.no_yy_scan_string = ! option_sense;

	yyalloc         ctrl.no_flex_alloc = ! option_sense;
	yyrealloc       ctrl.no_flex_realloc = ! option_sense;
	yyfree          ctrl.no_flex_free = ! option_sense;

	yyget_debug     ctrl.no_get_debug = ! option_sense;
	yyset_debug     ctrl.no_set_debug = ! option_sense;
	yyget_extra     ctrl.no_yyget_extra = ! option_sense;
	yyset_extra     ctrl.no_yyset_extra = ! option_sense;
	yyget_leng      ctrl.no_yyget_leng = ! option_sense;
	yyget_text      ctrl.no_yyget_text = ! option_sense;
	yyget_column    ctrl.no_yyget_column = ! option_sense;
	yyset_column    ctrl.no_yyset_column = ! option_sense;
	yyget_lineno    ctrl.no_yyget_lineno = ! option_sense;
	yyset_lineno    ctrl.no_yyset_lineno = ! option_sense;
	yyget_in        ctrl.no_yyget_in = ! option_sense;
	yyset_in        ctrl.no_yyset_in = ! option_sense;
	yyget_out       ctrl.no_yyget_out = ! option_sense;
	yyset_out       ctrl.no_yyset_out = ! option_sense;
	yyget_lval      ctrl.no_yyget_lval = ! option_sense;
	yyset_lval      ctrl.no_yyset_lval = ! option_sense;
	yyget_lloc      ctrl.no_yyget_lloc = ! option_sense;
	yyset_lloc      ctrl.no_yyset_lloc = ! option_sense;

	bufsize		প্রত্যাগম TOK_BUFSIZE;
	emit		প্রত্যাগম TOK_EMIT;
	extra-type	প্রত্যাগম TOK_EXTRA_TYPE;
	outfile		প্রত্যাগম TOK_OUTFILE;
	prefix		প্রত্যাগম TOK_PREFIX;
	yyclass		প্রত্যাগম TOK_YYCLASS;
	yylmax		প্রত্যাগম TOK_YYLMAX;
	yydecl		প্রত্যাগম TOK_YYDECL;
	yyterminate	প্রত্যাগম TOK_YYTERMINATE;
	pre-action	প্রত্যাগম TOK_PREACTION;
	post-action	প্রত্যাগম TOK_POSTACTION;
	user-init	প্রত্যাগম TOK_USERINIT;
	header(-file)?      প্রত্যাগম TOK_HEADER_FILE;
	tables-file         প্রত্যাগম TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    যদি (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			যদি(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, পরিমাণ(nmstr) );
			 }
			অন্যথা
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[strlen( nmstr ) - 1] = '\0';
			প্রত্যাগম NAME;
			}

	(([a-mo-z]|n[a-np-z])[[:alpha:]\-+]*)|.	{
			format_synerr( _( "unrecognized %%option: %s" ),
				yytext );
			BEGIN(RECOVER);
			}
}

<RECOVER>.*{NL}		++linenum; BEGIN(INITIAL);


<SECT2PROLOG>{
	^"%{".*	++bracelevel; yyless( 2 );	/* eat only %{ */
	^"%}".*	--bracelevel; yyless( 2 );	/* eat only %} */

	^{WS} START_CODEBLOCK(true); /* indented code in prolog */

	^{NOT_WS}.*	{
        /* non-indented code */
		যদি ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_set_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } অন্যথা {
            START_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			প্রত্যাগম YY_NULL; /* to stop the parser */
			}
}

<SECT2>{
	^{OPTWS}{NL}	++linenum; /* allow blank lines in section 2 */

	^{OPTWS}"%{"	{
			indented_code = false;
			doing_codeblock = true;
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);
			}

	^{OPTWS}"<"	    {
                        /* Allow "<" to appear in (?x) patterns. */
                        যদি (!sf_skip_ws())
                            BEGIN(SC);
                        প্রত্যাগম '<';
                    }
	^{OPTWS}"^"	প্রত্যাগম '^';
	"\""		BEGIN(QUOTE); প্রত্যাগম '"';
	"{"/[[:digit:]]	{
			BEGIN(অঙ্ক_2);
			যদি ( ctrl.lex_compat || ctrl.posix_compat )
				প্রত্যাগম BEGIN_REPEAT_POSIX;
			অন্যথা
				প্রত্যাগম BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	প্রত্যাগম '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			যদি ( in_rule )
				{
				doing_rule_action = true;
				in_rule = false;
				প্রত্যাগম '\n';
				}
			}
	{WS}"|".*{NL}	{
                        যদি (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            পূর্ণাঙ্ক amt = (পূর্ণাঙ্ক) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        অন্যথা {
                            add_action("]""]");
                            continued_action = true;
                            ++linenum;
                            প্রত্যাগম '\n';
                        }
                    }

	^{WS}"/*"	{

                যদি (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_ঠেলো_state(COMMENT_DISCARD);
                }
                অন্যথা{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            যদি (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            অন্যথা{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                যদি ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    প্রত্যাগম '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            যদি (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            অন্যথা{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                যদি ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    প্রত্যাগম '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	প্রত্যাগম EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({FIRST_CCL_CHAR}|{CCL_রাশিমালা})({CCL_CHAR}|{CCL_রাশিমালা})*	{
			পূর্ণাঙ্ক cclval;

			যদি(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, পরিমাণ(nmstr) );
			 }
			অন্যথা
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			যদি (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			অন্যথা
				{
				/* We fudge a bit.  We know that this ccl will
				 * soon be numbered as lastccl + 1 by cclinit.
				 */
				cclinstal( nmstr, lastccl + 1 );

				/* Push back everything but the leading bracket
				 * so the ccl can be rescanned.
				 */
				yyless( 1 );

				BEGIN(FIRSTCCL);
				প্রত্যাগম '[';
				}
			}
    "{-}"       প্রত্যাগম CCL_OP_DIFF;
    "{+}"       প্রত্যাগম CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			বর্ণ *nmdefptr;
            পূর্ণাঙ্ক end_is_ws, end_ch;

            end_ch = yytext[yyleng-1];
            end_is_ws = end_ch != '}' ? 1 : 0;

 			যদি(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, পরিমাণ(nmstr) );
 			 }
 			অন্যথা
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - end_is_ws] = '\0';  /* chop trailing brace */

			যদি ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			অন্যথা
				{ /* push back name surrounded by ()'s */
				size_t len = strlen( nmdefptr );
                যদি (end_is_ws)
                    unput(end_ch);

				যদি ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (end_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_BACK_STRING(nmdefptr, 0);

					যদি ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				অন্যথা
					{
					unput(')');
					PUT_BACK_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    যদি (sf_skip_ws())
                        yy_ঠেলো_state(COMMENT_DISCARD);
                    অন্যথা{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        প্রত্যাগম '/';
                    }
                }

    "(?#"       {
                    যদি (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_ঠেলো(); 
                        প্রত্যাগম '(';
                    }
                    অন্যথা
                        yy_ঠেলো_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_ঠেলো();
                    যদি (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    অন্যথা
                        BEGIN(GROUP_WITH_PARAMS);
                    প্রত্যাগম '(';
                }
    "("         sf_ঠেলো(); প্রত্যাগম '(';
    ")"         {
                    যদি (sf_শীর্ষ_ix > 0) {
                        sf_বের_করো();
                        প্রত্যাগম ')';
                    } অন্যথা
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	প্রত্যাগম (unsigned বর্ণ) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		প্রত্যাগম (unsigned বর্ণ) yytext[0];
	">"		BEGIN(SECT2); প্রত্যাগম '>';
	">"/^		BEGIN(CARETISBOL); প্রত্যাগম '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); প্রত্যাগম '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); প্রত্যাগম '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			প্রত্যাগম '"';
			}
}

<GROUP_WITH_PARAMS>{
    ":"     BEGIN(SECT2);
    "-"     BEGIN(GROUP_MINUS_PARAMS);
    i       sf_set_case_ins(1);
    s       sf_set_dot_all(1);
    x       sf_set_skip_ws(1);
}
<GROUP_MINUS_PARAMS>{
    ":"     BEGIN(SECT2);
    i       sf_set_case_ins(0);
    s       sf_set_dot_all(0);
    x       sf_set_skip_ws(0);
}

<FIRSTCCL>{
	"^"/[^-\]\n]	BEGIN(CCL); প্রত্যাগম '^';
	"^"/("-"|"]")	প্রত্যাগম '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	প্রত্যাগম '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); প্রত্যাগম ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			প্রত্যাগম ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); প্রত্যাগম CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); প্রত্যাগম CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); প্রত্যাগম CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); প্রত্যাগম CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); প্রত্যাগম CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); প্রত্যাগম CCE_GRAPH;
	"[:lower:]"	BEGIN(CCL); প্রত্যাগম CCE_LOWER;
	"[:print:]"	BEGIN(CCL); প্রত্যাগম CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); প্রত্যাগম CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); প্রত্যাগম CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); প্রত্যাগম CCE_UPPER;
	"[:xdigit:]"	BEGIN(CCL); প্রত্যাগম CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_GRAPH;
	"[:^lower:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_LOWER;
	"[:^print:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_UPPER;
	"[:^xdigit:]"	BEGIN(CCL); প্রত্যাগম CCE_NEG_XDIGIT;
	{CCL_রাশিমালা}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); প্রত্যাগম CCE_ALNUM;
			}
}

<অঙ্ক_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			প্রত্যাগম সংখ্যা;
			}

	","		প্রত্যাগম ',';
	"}"		{
			BEGIN(SECT2);
			যদি ( ctrl.lex_compat || ctrl.posix_compat )
				প্রত্যাগম END_REPEAT_POSIX;
			অন্যথা
				প্রত্যাগম END_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			প্রত্যাগম '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			প্রত্যাগম '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_ঠেলো_state( CODE_COMMENT );

	<CODEBLOCK,ACTION>{
		"reject" {
			ACTION_ECHO;
			CHECK_REJECT(yytext);
        }
		"yyreject"{OPTWS}"("{OPTWS}")" {
			add_action("]""]M4_HOOK_REJECT[""[");
			CHECK_YYREJECT(yytext);
        }
		"yymore"{OPTWS}"("{OPTWS}")" {
			yymore_used = true;
			যদি (ctrl.rewrite)
				context_call(yytext);
			অন্যথা
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		যদি (bracelevel <= 0 || (doing_codeblock && indented_code)) {
            যদি ( doing_rule_action )
                add_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

            doing_rule_action = doing_codeblock = false;
            BEGIN(SECT2);
        }
    }
}


	/* yyreject and yymore() are checked for above, in PERCENT_BRACE_ACTION */
<ACTION>{
	"{"		ACTION_ECHO; ++bracelevel;
	"}"		ACTION_ECHO; --bracelevel;
	yyecho\(\)|yyinput\(\)|yystart\({FUNARGS}\)|yybegin\({FUNARGS}\)|yyunput\({FUNARGS}\)|yypanic\({FUNARGS}\)|yyatbol\(\)|yysetbol\({FUNARGS}\) {
			যদি (ctrl.rewrite)
				context_call(yytext);
			অন্যথা
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			add_action("]""]");
			add_action(yytext);
			add_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			যদি (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			অন্যথা
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			যদি (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			অন্যথা
				ACTION_ECHO;
	}
	[^[:Alpha:]_{}""''/\n\[\]]+	ACTION_ECHO;
        {NAME}		ACTION_ECHO;
        "'"([^''\\\n]|\\.)"'" ACTION_ECHO; /* character constant */
        "'"             ACTION_ECHO; BEGIN(CHARACTER_CONSTANT);
	"\""		ACTION_ECHO; BEGIN(ACTION_STRING);
	{NL} {
                ++linenum;
                ACTION_ECHO;
                যদি (bracelevel <= 0) {
                   যদি ( doing_rule_action )
                      add_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

                   doing_rule_action = false;
                   BEGIN(SECT2);
                }
             }
        .      ACTION_ECHO;
}

<ACTION_STRING>{
	[^\[\]""\\\n]+	ACTION_ECHO;
	"\""		ACTION_ECHO; BEGIN(ACTION);
}
<CHARACTER_CONSTANT>{
	[^\[\]''\\\n]+  ACTION_ECHO;
        "'"             ACTION_ECHO; BEGIN(ACTION);
}
<ACTION_STRING,CHARACTER_CONSTANT>{
        (\\\n)*         ACTION_ECHO;
	\\(\\\n)*.	ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO; যদি (bracelevel <= 0) { BEGIN(SECT2); } অন্যথা { BEGIN(ACTION); }
        .	ACTION_ECHO;
}

<COMMENT,CODE_COMMENT,COMMENT_DISCARD,ACTION,ACTION_STRING,CHARACTER_CONSTANT><<EOF>>	{
			synerr( _( "EOF encountered inside an action" ) );
			yyterminate();
			}

<EXTENDED_COMMENT,GROUP_WITH_PARAMS,GROUP_MINUS_PARAMS><<EOF>>	{
			synerr( _( "EOF encountered inside pattern" ) );
			yyterminate();
			}

<SECT2,QUOTE,FIRSTCCL,CCL>{ESCSEQ}	{
			yylval = myesc( (unsigned বর্ণ *) yytext );

			যদি ( YY_START == FIRSTCCL )
				BEGIN(CCL);

			প্রত্যাগম CHAR;
			}

<SECT3>{
    {M4QSTART}   fputs(escaped_qstart, yyout);
    {M4QEND}     fputs(escaped_qend, yyout);
    [^\[\]]*     ECHO;
    [][]         ECHO;
    <<EOF>>      {
        sectnum = 0;
        yyterminate();
    }
}
<SECT3_NOESCAPE>{
    {M4QSTART}  fprintf(yyout, "[""[%s]""]", escaped_qstart);
    {M4QEND}    fprintf(yyout, "[""[%s]""]", escaped_qend);
    [^][]*      ECHO;
    [][]        ECHO;
    <<EOF>>		{
       sectnum = 0;
       yyterminate();
    }
}
<*>.|\n			format_synerr( _( "bad character: %s" ), yytext );

%%


পূর্ণাঙ্ক yywrap(শূন্য)
	{
	যদি ( --num_input_files > 0 )
		{
		set_প্রবেশ_file( *++প্রবেশ_files );
		প্রত্যাগম 0;
		}

	অন্যথা
		প্রত্যাগম 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

শূন্য set_প্রবেশ_file( বর্ণ *file )
	{
	যদি ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		যদি ( yyin == রিক্ত )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	অন্যথা
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

শূন্য context_call(বর্ণ *txt) {
	ধ্রুব বর্ণ *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	যদি (context_arg == রিক্ত) {
		add_action(txt);
	} অন্যথা {
		বর্ণ buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		প্রতিজ্ঞা(txt[strlen(txt)-1] == ')');
		strncpy(buf, txt, পরিমাণ(buf));
		buf[strlen(buf)-1] = '\0';	/* remove trailing ) */
		add_action(buf);
		যদি (txt[strlen(buf)-1] != '(') {
			add_action(", ");
		}
		add_action(context_arg);
		add_action(")");
	}
}

শূন্য context_member(বর্ণ *txt, ধ্রুব বর্ণ *prop) {
	ধ্রুব বর্ণ *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	যদি (context_format == রিক্ত) {
		add_action(txt);
	} অন্যথা {
		বর্ণ buf[128];
		snprintf(buf, পরিমাণ(buf), context_format, txt);
		add_action(buf);
	}
}
