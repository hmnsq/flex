/* scan.l - scanner for flex input -*-C-*- */

%top{
/* flexdef.h includes config.h, which may contain macros that alter the API */
/* of libc functions. Must include first before any libc header. */
#ضمن "flexdef.h"
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

#ضمن "parse.h"
خارجي bool tablesverify, tablesext;
خارجي bool trlcontxt; /* Set in parse.y for each rule. */
خارجي ثابت حرف *escaped_qstart, *escaped_qend;

#define M4QSTART "[""["
#define M4QEND "]""]"

#define ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#define ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#define ACTION_ECHO add_action( yytext )
#define ACTION_ECHO_QSTART add_action (ESCAPED_QSTART)
#define ACTION_ECHO_QEND   add_action (ESCAPED_QEND)

#define MARK_END_OF_PROLOG mark_prolog();

#define YY_DECL \
	صحيح flexscan(فراغ)

#define RETURNCHAR \
	yylval = (unsigned حرف) yytext[0]; \
	ܦܢܐ CHAR;

#define RETURNNAME \
	ܐܢ(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, حجم(nmstr) ); \
	ܦܢܐ NAME; \
	 } \
	ܐܚܪܢܐ \
	 ܥܒܕ { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } ܟܡܐ (0)

#define PUT_BACK_STRING(str, start) \
	{ size_t i = strlen( str );	\
	  ܟܡܐ ( i > start )		\
	    unput((str)[--i]);		\
	}

#define CHECK_REJECT(str) \
	ܐܢ ( all_upper( str ) ) \
		reject = true;

#define CHECK_YYREJECT(str) \
	ܐܢ ( all_lower( str ) ) \
		reject = true;

#define YY_USER_INIT \
	ܐܢ ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#define START_CODEBLOCK(x) ܥܒܕ { \
    /* Emit the needed line directive... */\
    ܐܢ (indented_code == false) { \
        ܐܢ (!x) linenum++; \
        line_directive_out(عدم, infilename, linenum);	\
    } \
    add_action(M4QSTART); \
    yy_push_state(CODEBLOCK); \
    ܐܢ ((indented_code = x)) ACTION_ECHO; \
} ܟܡܐ(0)

#define END_CODEBLOCK ܥܒܕ { \
    yy_pop_state();\
    add_action(M4QEND); \
    ܐܢ (!indented_code) line_directive_out(عدم, عدم, linenum);	\
} ܟܡܐ (0)

%}

%option caseless nodefault noreject stack noyy_top_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL NUM QUOTE
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
CCL_EXPR	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
فراغ context_call(حرف *);
فراغ context_member(حرف *, ثابت حرف *);
#undef yyreject
%}
%%
	ساكن صحيح bracelevel, didadef, indented_code;
	ساكن bool doing_rule_action = false;
	ساكن bool option_sense;

	ساكن bool doing_codeblock = false;
	صحيح brace_depth=0, brace_start_line=0;
	حرف nmdef[MAXLINE];


<INITIAL>{
	^{WS}		START_CODEBLOCK(true);
	^"/*"		add_action("/*[""["); yy_push_state( COMMENT );
	^#{OPTWS}line{WS}	yy_push_state( LINEDIR );
	^"%s"{NAME}?	ܦܢܐ SCDECL;
	^"%x"{NAME}?	ܦܢܐ XSCDECL;
	^"%{".*{NL}	START_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		حرف trampoline[512];
                brace_start_line = linenum;
                ++linenum;
		snprintf(trampoline, حجم(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                ܐܢ (ctrl.gen_line_dirs)
                    buf_strappend(&top_buf, trampoline);
                brace_depth = 1;
                yy_push_state(CODEBLOCK_MATCH_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			line_directive_out(عدم, infilename, linenum);
			BEGIN(SECT2PROLOG);
			ܦܢܐ SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); ܦܢܐ TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			ܐܢ(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, حجم(nmstr) );
			 }
			ܐܚܪܢܐ
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
	"*/"	    add_action("*/]""]"); yy_pop_state();
}
<CODE_COMMENT>{
        "*/"        ACTION_ECHO; yy_pop_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_pop_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_pop_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_pop_state();
	[[:digit:]]+	linenum = myctoi( yytext );

	"\""[^""\n]*"\""	{
			حرر(infilename);
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
			ܐܢ ( indented_code ) END_CODEBLOCK;
			}
}

<CODEBLOCK_MATCH_BRACE>{
    "}"     {
                ܐܢ( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_pop_state();
                }ܐܚܪܢܐ
                    buf_strnappend(&top_buf, yytext, yyleng);
            }

    "{"     {
                brace_depth++;
                buf_strnappend(&top_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&top_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&top_buf, escaped_qstart, (صحيح) strlen(escaped_qstart));
    {M4QEND}    buf_strnappend(&top_buf, escaped_qend, (صحيح) strlen(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&top_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_start_line;
                synerr(_("Unmatched '{'"));
                ܦܢܐ YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        ܐܢ(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, حجم(nmdef) );
 		         }
 		        ܐܚܪܢܐ
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = strlen( nmdef );
			    ܟܡܐ (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			ܐܢ ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		ܦܢܐ '=';
	[[:digit:]]+	{nmval = atoi(yytext); ܦܢܐ TOK_NUMERIC;}

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
	bison-locations  { ܐܢ((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|حالة-sensitive		sf_set_case_ins(!option_sense);
	caseless|حالة-insensitive	sf_set_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	افتراضي		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	full		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	input		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	line		ctrl.gen_line_dirs = option_sense;
	main		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			ܐܢ (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	pointer		ctrl.yytext_is_array = ! option_sense;
	اقرأ		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_used = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	stack		ctrl.stack_used = option_sense;
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

	yy_push_state	ctrl.no_yy_push_state = ! option_sense;
	yy_pop_state	ctrl.no_yy_pop_state = ! option_sense;
	yy_top_state	ctrl.no_yy_top_state = ! option_sense;

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

	bufsize		ܦܢܐ TOK_BUFSIZE;
	emit		ܦܢܐ TOK_EMIT;
	extra-type	ܦܢܐ TOK_EXTRA_TYPE;
	outfile		ܦܢܐ TOK_OUTFILE;
	prefix		ܦܢܐ TOK_PREFIX;
	yyclass		ܦܢܐ TOK_YYCLASS;
	yylmax		ܦܢܐ TOK_YYLMAX;
	yydecl		ܦܢܐ TOK_YYDECL;
	yyterminate	ܦܢܐ TOK_YYTERMINATE;
	pre-action	ܦܢܐ TOK_PREACTION;
	post-action	ܦܢܐ TOK_POSTACTION;
	user-init	ܦܢܐ TOK_USERINIT;
	header(-file)?      ܦܢܐ TOK_HEADER_FILE;
	tables-file         ܦܢܐ TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    ܐܢ (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			ܐܢ(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, حجم(nmstr) );
			 }
			ܐܚܪܢܐ
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[strlen( nmstr ) - 1] = '\0';
			ܦܢܐ NAME;
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
		ܐܢ ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_set_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } ܐܚܪܢܐ {
            START_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			ܦܢܐ YY_NULL; /* to stop the parser */
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
                        ܐܢ (!sf_skip_ws())
                            BEGIN(SC);
                        ܦܢܐ '<';
                    }
	^{OPTWS}"^"	ܦܢܐ '^';
	"\""		BEGIN(QUOTE); ܦܢܐ '"';
	"{"/[[:digit:]]	{
			BEGIN(NUM);
			ܐܢ ( ctrl.lex_compat || ctrl.posix_compat )
				ܦܢܐ BEGIN_REPEAT_POSIX;
			ܐܚܪܢܐ
				ܦܢܐ BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	ܦܢܐ '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			ܐܢ ( in_rule )
				{
				doing_rule_action = true;
				in_rule = false;
				ܦܢܐ '\n';
				}
			}
	{WS}"|".*{NL}	{
                        ܐܢ (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            صحيح amt = (صحيح) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        ܐܚܪܢܐ {
                            add_action("]""]");
                            continued_action = true;
                            ++linenum;
                            ܦܢܐ '\n';
                        }
                    }

	^{WS}"/*"	{

                ܐܢ (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_push_state(COMMENT_DISCARD);
                }
                ܐܚܪܢܐ{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            ܐܢ (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            ܐܚܪܢܐ{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                ܐܢ ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    ܦܢܐ '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            ܐܢ (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            ܐܚܪܢܐ{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                ܐܢ ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    ܦܢܐ '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	ܦܢܐ EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({FIRST_CCL_CHAR}|{CCL_EXPR})({CCL_CHAR}|{CCL_EXPR})*	{
			صحيح cclval;

			ܐܢ(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, حجم(nmstr) );
			 }
			ܐܚܪܢܐ
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			ܐܢ (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			ܐܚܪܢܐ
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
				ܦܢܐ '[';
				}
			}
    "{-}"       ܦܢܐ CCL_OP_DIFF;
    "{+}"       ܦܢܐ CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			حرف *nmdefptr;
            صحيح end_is_ws, end_ch;

            end_ch = yytext[yyleng-1];
            end_is_ws = end_ch != '}' ? 1 : 0;

 			ܐܢ(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, حجم(nmstr) );
 			 }
 			ܐܚܪܢܐ
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - end_is_ws] = '\0';  /* chop trailing brace */

			ܐܢ ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			ܐܚܪܢܐ
				{ /* push back name surrounded by ()'s */
				size_t len = strlen( nmdefptr );
                ܐܢ (end_is_ws)
                    unput(end_ch);

				ܐܢ ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (end_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_BACK_STRING(nmdefptr, 0);

					ܐܢ ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				ܐܚܪܢܐ
					{
					unput(')');
					PUT_BACK_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    ܐܢ (sf_skip_ws())
                        yy_push_state(COMMENT_DISCARD);
                    ܐܚܪܢܐ{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        ܦܢܐ '/';
                    }
                }

    "(?#"       {
                    ܐܢ (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_push(); 
                        ܦܢܐ '(';
                    }
                    ܐܚܪܢܐ
                        yy_push_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_push();
                    ܐܢ (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    ܐܚܪܢܐ
                        BEGIN(GROUP_WITH_PARAMS);
                    ܦܢܐ '(';
                }
    "("         sf_push(); ܦܢܐ '(';
    ")"         {
                    ܐܢ (_sf_top_ix > 0) {
                        sf_pop();
                        ܦܢܐ ')';
                    } ܐܚܪܢܐ
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	ܦܢܐ (unsigned حرف) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		ܦܢܐ (unsigned حرف) yytext[0];
	">"		BEGIN(SECT2); ܦܢܐ '>';
	">"/^		BEGIN(CARETISBOL); ܦܢܐ '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); ܦܢܐ '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); ܦܢܐ '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			ܦܢܐ '"';
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
	"^"/[^-\]\n]	BEGIN(CCL); ܦܢܐ '^';
	"^"/("-"|"]")	ܦܢܐ '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	ܦܢܐ '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); ܦܢܐ ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			ܦܢܐ ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); ܦܢܐ CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); ܦܢܐ CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); ܦܢܐ CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); ܦܢܐ CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); ܦܢܐ CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); ܦܢܐ CCE_GRAPH;
	"[:lower:]"	BEGIN(CCL); ܦܢܐ CCE_LOWER;
	"[:print:]"	BEGIN(CCL); ܦܢܐ CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); ܦܢܐ CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); ܦܢܐ CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); ܦܢܐ CCE_UPPER;
	"[:xdigit:]"	BEGIN(CCL); ܦܢܐ CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_GRAPH;
	"[:^lower:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_LOWER;
	"[:^print:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_UPPER;
	"[:^xdigit:]"	BEGIN(CCL); ܦܢܐ CCE_NEG_XDIGIT;
	{CCL_EXPR}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); ܦܢܐ CCE_ALNUM;
			}
}

<NUM>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			ܦܢܐ NUMBER;
			}

	","		ܦܢܐ ',';
	"}"		{
			BEGIN(SECT2);
			ܐܢ ( ctrl.lex_compat || ctrl.posix_compat )
				ܦܢܐ END_REPEAT_POSIX;
			ܐܚܪܢܐ
				ܦܢܐ END_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			ܦܢܐ '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			ܦܢܐ '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_push_state( CODE_COMMENT );

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
			ܐܢ (ctrl.rewrite)
				context_call(yytext);
			ܐܚܪܢܐ
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		ܐܢ (bracelevel <= 0 || (doing_codeblock && indented_code)) {
            ܐܢ ( doing_rule_action )
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
			ܐܢ (ctrl.rewrite)
				context_call(yytext);
			ܐܚܪܢܐ
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			add_action("]""]");
			add_action(yytext);
			add_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			ܐܢ (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			ܐܚܪܢܐ
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			ܐܢ (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			ܐܚܪܢܐ
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
                ܐܢ (bracelevel <= 0) {
                   ܐܢ ( doing_rule_action )
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
	{NL}	++linenum; ACTION_ECHO; ܐܢ (bracelevel <= 0) { BEGIN(SECT2); } ܐܚܪܢܐ { BEGIN(ACTION); }
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
			yylval = myesc( (unsigned حرف *) yytext );

			ܐܢ ( YY_START == FIRSTCCL )
				BEGIN(CCL);

			ܦܢܐ CHAR;
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


صحيح yywrap(فراغ)
	{
	ܐܢ ( --num_input_files > 0 )
		{
		set_input_file( *++input_files );
		ܦܢܐ 0;
		}

	ܐܚܪܢܐ
		ܦܢܐ 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

فراغ set_input_file( حرف *file )
	{
	ܐܢ ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		ܐܢ ( yyin == عدم )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	ܐܚܪܢܐ
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

فراغ context_call(حرف *txt) {
	ثابت حرف *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	ܐܢ (context_arg == عدم) {
		add_action(txt);
	} ܐܚܪܢܐ {
		حرف buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		أكد(txt[strlen(txt)-1] == ')');
		strncpy(buf, txt, حجم(buf));
		buf[strlen(buf)-1] = '\0';	/* remove trailing ) */
		add_action(buf);
		ܐܢ (txt[strlen(buf)-1] != '(') {
			add_action(", ");
		}
		add_action(context_arg);
		add_action(")");
	}
}

فراغ context_member(حرف *txt, ثابت حرف *prop) {
	ثابت حرف *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	ܐܢ (context_format == عدم) {
		add_action(txt);
	} ܐܚܪܢܐ {
		حرف buf[128];
		snprintf(buf, حجم(buf), context_format, txt);
		add_action(buf);
	}
}
