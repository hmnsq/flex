/* scan.l - scanner for flex input -*-C-*- */

%top{
/* flexdef.h includes config.h, which may contain macros that alter the API */
/* of libc functions. Must include first before any libc header. */
#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
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

#ਅਨ੍ਤਰ੍ਭਾਵ "parse.h"
ਬਾਹਰੀ bool tablesverify, tablesext;
ਬਾਹਰੀ bool trlcontxt; /* Set in parse.y for each rule. */
ਬਾਹਰੀ ਅਚਲ ਅੱਖਰ *escaped_qstart, *escaped_qend;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ M4QSTART "[""["
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ M4QEND "]""]"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ECHO ਜੋੜੋ_action( yytext )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ECHO_QSTART ਜੋੜੋ_action (ESCAPED_QSTART)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ECHO_QEND   ਜੋੜੋ_action (ESCAPED_QEND)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MARK_ਸਿਰਾ_ਦਾ_PROLOG mark_prolog();

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YY_DECL \
	ਪੂਰਨ flexscan(ਖਾਲੀ)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RETURNCHAR \
	yylval = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) yytext[0]; \
	ਵਾਪਸ CHAR;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RETURNNAME \
	ਜੇ(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, ਆਕਾਰ(nmstr) ); \
	ਵਾਪਸ NAME; \
	 } \
	ਨਹੀਂਤਾਂ \
	 ਕਰੋ { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } ਜਦੋਂ (0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PUT_ਪਿੱਠ_STRING(str, ਸ਼ੁਰੂ) \
	{ size_t i = ਲੜੀ_ਲੰਬਾਈ( str );	\
	  ਜਦੋਂ ( i > ਸ਼ੁਰੂ )		\
	    unput((str)[--i]);		\
	}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_REJECT(str) \
	ਜੇ ( all_ਉੱਤਲਾ( str ) ) \
		reject = true;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_YYREJECT(str) \
	ਜੇ ( all_ਹੇਠਲਾ( str ) ) \
		reject = true;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YY_USER_INIT \
	ਜੇ ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸ਼ੁਰੂ_CODEBLOCK(x) ਕਰੋ { \
    /* Emit the needed line directive... */\
    ਜੇ (indented_ਕੋਡ == false) { \
        ਜੇ (!x) linenum++; \
        ਸਤਰ_directive_ਬਾਹਰਲਾ(ਨਿਰਾ, infilename, linenum);	\
    } \
    ਜੋੜੋ_action(M4QSTART); \
    yy_ਧੱਕੋ_state(CODEBLOCK); \
    ਜੇ ((indented_ਕੋਡ = x)) ACTION_ECHO; \
} ਜਦੋਂ(0)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸਿਰਾ_CODEBLOCK ਕਰੋ { \
    yy_ਕੱਢੋ_state();\
    ਜੋੜੋ_action(M4QEND); \
    ਜੇ (!indented_ਕੋਡ) ਸਤਰ_directive_ਬਾਹਰਲਾ(ਨਿਰਾ, ਨਿਰਾ, linenum);	\
} ਜਦੋਂ (0)

%}

%option caseless nodefault noreject ਢੇਰ noyy_ਸਿਖਰ_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL ਅੰਕ_2 QUOTE
%x FIRSTCCL CCL ACTION RECOVER COMMENT ACTION_STRING PERCENT_BRACE_ACTION
%x OPTION LINEDIR CODEBLOCK_ਮੇਲ_BRACE
%x ਸਮੂਹ_WITH_PARAMS
%x ਸਮੂਹ_MINUS_PARAMS
%x EXTENDED_COMMENT
%x COMMENT_DISCARD ਕੋਡ_COMMENT
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

ਪਹਿਲਾ_CCL_CHAR	([^\\\n]|{ESCSEQ})
CCL_CHAR	([^\\\n\]]|{ESCSEQ})
CCL_ਵਿਅੰਜਕ	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
ਖਾਲੀ context_call(ਅੱਖਰ *);
ਖਾਲੀ context_member(ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *);
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ yyreject
%}
%%
	ਸਥਿਰ ਪੂਰਨ bracelevel, didadef, indented_ਕੋਡ;
	ਸਥਿਰ bool doing_ਨਿਯਮ_action = false;
	ਸਥਿਰ bool option_sense;

	ਸਥਿਰ bool doing_codeblock = false;
	ਪੂਰਨ brace_ਡੂੰਘਾਈ=0, brace_ਸ਼ੁਰੂ_ਸਤਰ=0;
	ਅੱਖਰ nmdef[MAXLINE];


<INITIAL>{
	^{WS}		ਸ਼ੁਰੂ_CODEBLOCK(true);
	^"/*"		ਜੋੜੋ_action("/*[""["); yy_ਧੱਕੋ_state( COMMENT );
	^#{OPTWS}ਸਤਰ{WS}	yy_ਧੱਕੋ_state( LINEDIR );
	^"%s"{NAME}?	ਵਾਪਸ SCDECL;
	^"%x"{NAME}?	ਵਾਪਸ XSCDECL;
	^"%{".*{NL}	ਸ਼ੁਰੂ_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		ਅੱਖਰ trampoline[512];
                brace_ਸ਼ੁਰੂ_ਸਤਰ = linenum;
                ++linenum;
		snprintf(trampoline, ਆਕਾਰ(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                ਜੇ (ctrl.gen_ਸਤਰ_dirs)
                    buf_strappend(&ਸਿਖਰ_buf, trampoline);
                brace_ਡੂੰਘਾਈ = 1;
                yy_ਧੱਕੋ_state(CODEBLOCK_ਮੇਲ_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			ਸਤਰ_directive_ਬਾਹਰਲਾ(ਨਿਰਾ, infilename, linenum);
			BEGIN(SECT2PROLOG);
			ਵਾਪਸ SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); ਵਾਪਸ TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			ਜੇ(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, ਆਕਾਰ(nmstr) );
			 }
			ਨਹੀਂਤਾਂ
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


<COMMENT,ਕੋਡ_COMMENT>{ /* */
        [^\[\]\*\n]*  ACTION_ECHO;
        .           ACTION_ECHO;

	{NL}	    ++linenum; ACTION_ECHO;
}
<COMMENT>{
	"*/"	    ਜੋੜੋ_action("*/]""]"); yy_ਕੱਢੋ_state();
}
<ਕੋਡ_COMMENT>{
        "*/"        ACTION_ECHO; yy_ਕੱਢੋ_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_ਕੱਢੋ_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_ਕੱਢੋ_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_ਕੱਢੋ_state();
	[[:digit:]]+	linenum = myctoi( yytext );

	"\""[^""\n]*"\""	{
			ਮੁਕਤ(infilename);
			infilename = xstrdup(yytext + 1);
			infilename[ਲੜੀ_ਲੰਬਾਈ( infilename ) - 1] = '\0';
			}
	.		/* ignore spurious characters */
}
<ACTION,CODEBLOCK,ACTION_STRING,PERCENT_BRACE_ACTION,CHARACTER_CONSTANT,COMMENT,ਕੋਡ_COMMENT>{
   {M4QSTART}   ACTION_ECHO_QSTART;
   {M4QEND}     ACTION_ECHO_QEND;
}

<CODEBLOCK>{
	^"%}".*{NL}	++linenum; ਸਿਰਾ_CODEBLOCK;
	[^\n%\[\]]*         ACTION_ECHO;
        .		ACTION_ECHO;
	{NL}		{
			++linenum;
			ACTION_ECHO;
			ਜੇ ( indented_ਕੋਡ ) ਸਿਰਾ_CODEBLOCK;
			}
}

<CODEBLOCK_ਮੇਲ_BRACE>{
    "}"     {
                ਜੇ( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_ਕੱਢੋ_state();
                }ਨਹੀਂਤਾਂ
                    buf_strnappend(&ਸਿਖਰ_buf, yytext, yyleng);
            }

    "{"     {
                brace_ਡੂੰਘਾਈ++;
                buf_strnappend(&ਸਿਖਰ_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&ਸਿਖਰ_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&ਸਿਖਰ_buf, escaped_qstart, (ਪੂਰਨ) ਲੜੀ_ਲੰਬਾਈ(escaped_qstart));
    {M4QEND}    buf_strnappend(&ਸਿਖਰ_buf, escaped_qend, (ਪੂਰਨ) ਲੜੀ_ਲੰਬਾਈ(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&ਸਿਖਰ_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_ਸ਼ੁਰੂ_ਸਤਰ;
                synerr(_("Unmatched '{'"));
                ਵਾਪਸ YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        ਜੇ(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, ਆਕਾਰ(nmdef) );
 		         }
 		        ਨਹੀਂਤਾਂ
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = ਲੜੀ_ਲੰਬਾਈ( nmdef );
			    ਜਦੋਂ (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			ਜੇ ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		ਵਾਪਸ '=';
	[[:digit:]]+	{nmval = atoi(yytext); ਵਾਪਸ TOK_NUMERIC;}

	no		option_sense = ! option_sense;

	7ਦੋਆਧਾਰੀ_ਅੰਕ		ctrl.csize = option_sense ? 128 : 256;
	8ਦੋਆਧਾਰੀ_ਅੰਕ		ctrl.csize = option_sense ? 256 : 128;

	align		ctrl.long_align = option_sense;
	always-interactive	{
			ctrl.always_interactive = option_sense;
			ctrl.interactive = (trit)option_sense;
			}
	array		ctrl.yytext_is_array = option_sense;
	backup		env.backing_ਉੱਪਰ_report = option_sense;
	batch		ctrl.interactive = (trit)!option_sense;
	bison-bridge     ctrl.bison_bridge_lval = option_sense;
	bison-locations  { ਜੇ((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|ਹਾਲਤ-sensitive		sf_ਸੈੱਟ_case_ins(!option_sense);
	caseless|ਹਾਲਤ-insensitive	sf_ਸੈੱਟ_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	ਮੂਲ		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	ਭਰਿਆ		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	ਨਿਵੇਸ਼		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	ਸਤਰ		ctrl.gen_ਸਤਰ_dirs = option_sense;
	ਮੁੱਖ		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			ਜੇ (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	ਸੂਚਕ		ctrl.yytext_is_array = ! option_sense;
	ਪਠ		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_ਵਰਤਿਆ = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	ਢੇਰ		ctrl.ਢੇਰ_ਵਰਤਿਆ = option_sense;
	stdinit		ctrl.do_stdinit = option_sense;
	stdout		env.use_stdout = option_sense;
	unistd		ctrl.no_unistd = ! option_sense;
	unput		ctrl.no_yyunput = ! option_sense;
	yyunput		ctrl.no_yyunput = ! option_sense;
	verbose		env.printstats = option_sense;
	warn		env.nowarn = ! option_sense;
	yylineno	ctrl.do_yylineno = option_sense;
	yymore		ctrl.yymore_really_ਵਰਤਿਆ = option_sense;
	yywrap		ctrl.do_yywrap = option_sense;
	yyread		ctrl.noyyread = !option_sense;

	yypanic		ctrl.no_yypanic = !option_sense;

	yy_ਧੱਕੋ_state	ctrl.no_yy_ਧੱਕੋ_state = ! option_sense;
	yy_ਕੱਢੋ_state	ctrl.no_yy_ਕੱਢੋ_state = ! option_sense;
	yy_ਸਿਖਰ_state	ctrl.no_yy_ਸਿਖਰ_state = ! option_sense;

	yy_ਜਾਂਚ_ਬਫਰ	ctrl.no_yy_ਜਾਂਚ_ਬਫਰ = ! option_sense;
	yy_ਜਾਂਚ_ਬਾਈਟਾਂ	ctrl.no_yy_ਜਾਂਚ_ਬਾਈਟਾਂ = ! option_sense;
	yy_ਜਾਂਚ_string	ctrl.no_yy_ਜਾਂਚ_string = ! option_sense;

	yyalloc         ctrl.no_flex_alloc = ! option_sense;
	yyrealloc       ctrl.no_flex_realloc = ! option_sense;
	yyfree          ctrl.no_flex_free = ! option_sense;

	yyget_debug     ctrl.no_get_debug = ! option_sense;
	yyset_debug     ctrl.no_ਸੈੱਟ_debug = ! option_sense;
	yyget_extra     ctrl.no_yyget_extra = ! option_sense;
	yyset_extra     ctrl.no_yyset_extra = ! option_sense;
	yyget_leng      ctrl.no_yyget_leng = ! option_sense;
	yyget_ਪਾਠ      ctrl.no_yyget_ਪਾਠ = ! option_sense;
	yyget_ਕਾਲਮ    ctrl.no_yyget_ਕਾਲਮ = ! option_sense;
	yyset_ਕਾਲਮ    ctrl.no_yyset_ਕਾਲਮ = ! option_sense;
	yyget_lineno    ctrl.no_yyget_lineno = ! option_sense;
	yyset_lineno    ctrl.no_yyset_lineno = ! option_sense;
	yyget_ਵਿੱਚ        ctrl.no_yyget_ਵਿੱਚ = ! option_sense;
	yyset_ਵਿੱਚ        ctrl.no_yyset_ਵਿੱਚ = ! option_sense;
	yyget_ਬਾਹਰਲਾ       ctrl.no_yyget_ਬਾਹਰਲਾ = ! option_sense;
	yyset_ਬਾਹਰਲਾ       ctrl.no_yyset_ਬਾਹਰਲਾ = ! option_sense;
	yyget_lval      ctrl.no_yyget_lval = ! option_sense;
	yyset_lval      ctrl.no_yyset_lval = ! option_sense;
	yyget_lloc      ctrl.no_yyget_lloc = ! option_sense;
	yyset_lloc      ctrl.no_yyset_lloc = ! option_sense;

	bufsize		ਵਾਪਸ TOK_BUFSIZE;
	emit		ਵਾਪਸ TOK_EMIT;
	extra-type	ਵਾਪਸ TOK_EXTRA_TYPE;
	outfile		ਵਾਪਸ TOK_OUTFILE;
	ਅਗੇਤਰ		ਵਾਪਸ TOK_ਅਗੇਤਰ;
	yyclass		ਵਾਪਸ TOK_YYCLASS;
	yylmax		ਵਾਪਸ TOK_YYLMAX;
	yydecl		ਵਾਪਸ TOK_YYDECL;
	yyterminate	ਵਾਪਸ TOK_YYTERMINATE;
	pre-action	ਵਾਪਸ TOK_PREACTION;
	post-action	ਵਾਪਸ TOK_POSTACTION;
	user-init	ਵਾਪਸ TOK_USERINIT;
	ਸਿਰਲੇਖ(-file)?      ਵਾਪਸ TOK_ਸਿਰਲੇਖ_FILE;
	tables-file         ਵਾਪਸ TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    ਜੇ (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			ਜੇ(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, ਆਕਾਰ(nmstr) );
			 }
			ਨਹੀਂਤਾਂ
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[ਲੜੀ_ਲੰਬਾਈ( nmstr ) - 1] = '\0';
			ਵਾਪਸ NAME;
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

	^{WS} ਸ਼ੁਰੂ_CODEBLOCK(true); /* indented code in prolog */

	^{NOT_WS}.*	{
        /* non-indented code */
		ਜੇ ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_ਸੈੱਟ_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } ਨਹੀਂਤਾਂ {
            ਸ਼ੁਰੂ_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			ਵਾਪਸ YY_NULL; /* to stop the parser */
			}
}

<SECT2>{
	^{OPTWS}{NL}	++linenum; /* allow blank lines in section 2 */

	^{OPTWS}"%{"	{
			indented_ਕੋਡ = false;
			doing_codeblock = true;
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);
			}

	^{OPTWS}"<"	    {
                        /* Allow "<" to appear in (?x) patterns. */
                        ਜੇ (!sf_skip_ws())
                            BEGIN(SC);
                        ਵਾਪਸ '<';
                    }
	^{OPTWS}"^"	ਵਾਪਸ '^';
	"\""		BEGIN(QUOTE); ਵਾਪਸ '"';
	"{"/[[:digit:]]	{
			BEGIN(ਅੰਕ_2);
			ਜੇ ( ctrl.lex_compat || ctrl.posix_compat )
				ਵਾਪਸ BEGIN_REPEAT_POSIX;
			ਨਹੀਂਤਾਂ
				ਵਾਪਸ BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	ਵਾਪਸ '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			ਜੇ ( ਵਿੱਚ_ਨਿਯਮ )
				{
				doing_ਨਿਯਮ_action = true;
				ਵਿੱਚ_ਨਿਯਮ = false;
				ਵਾਪਸ '\n';
				}
			}
	{WS}"|".*{NL}	{
                        ਜੇ (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            ਪੂਰਨ amt = (ਪੂਰਨ) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        ਨਹੀਂਤਾਂ {
                            ਜੋੜੋ_action("]""]");
                            continued_action = true;
                            ++linenum;
                            ਵਾਪਸ '\n';
                        }
                    }

	^{WS}"/*"	{

                ਜੇ (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_ਧੱਕੋ_state(COMMENT_DISCARD);
                }
                ਨਹੀਂਤਾਂ{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            ਜੇ (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            ਨਹੀਂਤਾਂ{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                ਜੇ ( ਵਿੱਚ_ਨਿਯਮ )
                    {
                    doing_ਨਿਯਮ_action = true;
                    ਵਿੱਚ_ਨਿਯਮ = false;
                    ਵਾਪਸ '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            ਜੇ (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            ਨਹੀਂਤਾਂ{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                ਜੇ ( ਵਿੱਚ_ਨਿਯਮ )
                    {
                    doing_ਨਿਯਮ_action = true;
                    ਵਿੱਚ_ਨਿਯਮ = false;
                    ਵਾਪਸ '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	ਵਾਪਸ EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({ਪਹਿਲਾ_CCL_CHAR}|{CCL_ਵਿਅੰਜਕ})({CCL_CHAR}|{CCL_ਵਿਅੰਜਕ})*	{
			ਪੂਰਨ cclval;

			ਜੇ(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, ਆਕਾਰ(nmstr) );
			 }
			ਨਹੀਂਤਾਂ
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			ਜੇ (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			ਨਹੀਂਤਾਂ
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
				ਵਾਪਸ '[';
				}
			}
    "{-}"       ਵਾਪਸ CCL_OP_DIFF;
    "{+}"       ਵਾਪਸ CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			ਅੱਖਰ *nmdefptr;
            ਪੂਰਨ ਸਿਰਾ_is_ws, ਸਿਰਾ_ch;

            ਸਿਰਾ_ch = yytext[yyleng-1];
            ਸਿਰਾ_is_ws = ਸਿਰਾ_ch != '}' ? 1 : 0;

 			ਜੇ(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, ਆਕਾਰ(nmstr) );
 			 }
 			ਨਹੀਂਤਾਂ
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - ਸਿਰਾ_is_ws] = '\0';  /* chop trailing brace */

			ਜੇ ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			ਨਹੀਂਤਾਂ
				{ /* push back name surrounded by ()'s */
				size_t len = ਲੜੀ_ਲੰਬਾਈ( nmdefptr );
                ਜੇ (ਸਿਰਾ_is_ws)
                    unput(ਸਿਰਾ_ch);

				ਜੇ ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (ਸਿਰਾ_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_ਪਿੱਠ_STRING(nmdefptr, 0);

					ਜੇ ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				ਨਹੀਂਤਾਂ
					{
					unput(')');
					PUT_ਪਿੱਠ_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    ਜੇ (sf_skip_ws())
                        yy_ਧੱਕੋ_state(COMMENT_DISCARD);
                    ਨਹੀਂਤਾਂ{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        ਵਾਪਸ '/';
                    }
                }

    "(?#"       {
                    ਜੇ (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_ਧੱਕੋ(); 
                        ਵਾਪਸ '(';
                    }
                    ਨਹੀਂਤਾਂ
                        yy_ਧੱਕੋ_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_ਧੱਕੋ();
                    ਜੇ (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    ਨਹੀਂਤਾਂ
                        BEGIN(ਸਮੂਹ_WITH_PARAMS);
                    ਵਾਪਸ '(';
                }
    "("         sf_ਧੱਕੋ(); ਵਾਪਸ '(';
    ")"         {
                    ਜੇ (sf_ਸਿਖਰ_ix > 0) {
                        sf_ਕੱਢੋ();
                        ਵਾਪਸ ')';
                    } ਨਹੀਂਤਾਂ
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	ਵਾਪਸ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		ਵਾਪਸ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) yytext[0];
	">"		BEGIN(SECT2); ਵਾਪਸ '>';
	">"/^		BEGIN(CARETISBOL); ਵਾਪਸ '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); ਵਾਪਸ '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); ਵਾਪਸ '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			ਵਾਪਸ '"';
			}
}

<ਸਮੂਹ_WITH_PARAMS>{
    ":"     BEGIN(SECT2);
    "-"     BEGIN(ਸਮੂਹ_MINUS_PARAMS);
    i       sf_ਸੈੱਟ_case_ins(1);
    s       sf_ਸੈੱਟ_dot_all(1);
    x       sf_ਸੈੱਟ_skip_ws(1);
}
<ਸਮੂਹ_MINUS_PARAMS>{
    ":"     BEGIN(SECT2);
    i       sf_ਸੈੱਟ_case_ins(0);
    s       sf_ਸੈੱਟ_dot_all(0);
    x       sf_ਸੈੱਟ_skip_ws(0);
}

<FIRSTCCL>{
	"^"/[^-\]\n]	BEGIN(CCL); ਵਾਪਸ '^';
	"^"/("-"|"]")	ਵਾਪਸ '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	ਵਾਪਸ '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); ਵਾਪਸ ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			ਵਾਪਸ ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); ਵਾਪਸ CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); ਵਾਪਸ CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); ਵਾਪਸ CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); ਵਾਪਸ CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); ਵਾਪਸ CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); ਵਾਪਸ CCE_ਗ੍ਰਾਫ;
	"[:lower:]"	BEGIN(CCL); ਵਾਪਸ CCE_ਹੇਠਲਾ;
	"[:print:]"	BEGIN(CCL); ਵਾਪਸ CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); ਵਾਪਸ CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); ਵਾਪਸ CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); ਵਾਪਸ CCE_ਉੱਤਲਾ;
	"[:xdigit:]"	BEGIN(CCL); ਵਾਪਸ CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_ਗ੍ਰਾਫ;
	"[:^lower:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_ਹੇਠਲਾ;
	"[:^print:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_ਉੱਤਲਾ;
	"[:^xdigit:]"	BEGIN(CCL); ਵਾਪਸ CCE_NEG_XDIGIT;
	{CCL_ਵਿਅੰਜਕ}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); ਵਾਪਸ CCE_ALNUM;
			}
}

<ਅੰਕ_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			ਵਾਪਸ ਸੰਖਿਆ;
			}

	","		ਵਾਪਸ ',';
	"}"		{
			BEGIN(SECT2);
			ਜੇ ( ctrl.lex_compat || ctrl.posix_compat )
				ਵਾਪਸ ਸਿਰਾ_REPEAT_POSIX;
			ਨਹੀਂਤਾਂ
				ਵਾਪਸ ਸਿਰਾ_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			ਵਾਪਸ '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			ਵਾਪਸ '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_ਧੱਕੋ_state( ਕੋਡ_COMMENT );

	<CODEBLOCK,ACTION>{
		"reject" {
			ACTION_ECHO;
			CHECK_REJECT(yytext);
        }
		"yyreject"{OPTWS}"("{OPTWS}")" {
			ਜੋੜੋ_action("]""]M4_HOOK_REJECT[""[");
			CHECK_YYREJECT(yytext);
        }
		"yymore"{OPTWS}"("{OPTWS}")" {
			yymore_ਵਰਤਿਆ = true;
			ਜੇ (ctrl.rewrite)
				context_call(yytext);
			ਨਹੀਂਤਾਂ
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		ਜੇ (bracelevel <= 0 || (doing_codeblock && indented_ਕੋਡ)) {
            ਜੇ ( doing_ਨਿਯਮ_action )
                ਜੋੜੋ_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

            doing_ਨਿਯਮ_action = doing_codeblock = false;
            BEGIN(SECT2);
        }
    }
}


	/* yyreject and yymore() are checked for above, in PERCENT_BRACE_ACTION */
<ACTION>{
	"{"		ACTION_ECHO; ++bracelevel;
	"}"		ACTION_ECHO; --bracelevel;
	yyecho\(\)|yyinput\(\)|yystart\({FUNARGS}\)|yybegin\({FUNARGS}\)|yyunput\({FUNARGS}\)|yypanic\({FUNARGS}\)|yyatbol\(\)|yysetbol\({FUNARGS}\) {
			ਜੇ (ctrl.rewrite)
				context_call(yytext);
			ਨਹੀਂਤਾਂ
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			ਜੋੜੋ_action("]""]");
			ਜੋੜੋ_action(yytext);
			ਜੋੜੋ_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			ਜੇ (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			ਨਹੀਂਤਾਂ
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			ਜੇ (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			ਨਹੀਂਤਾਂ
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
                ਜੇ (bracelevel <= 0) {
                   ਜੇ ( doing_ਨਿਯਮ_action )
                      ਜੋੜੋ_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

                   doing_ਨਿਯਮ_action = false;
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
	{NL}	++linenum; ACTION_ECHO; ਜੇ (bracelevel <= 0) { BEGIN(SECT2); } ਨਹੀਂਤਾਂ { BEGIN(ACTION); }
        .	ACTION_ECHO;
}

<COMMENT,ਕੋਡ_COMMENT,COMMENT_DISCARD,ACTION,ACTION_STRING,CHARACTER_CONSTANT><<EOF>>	{
			synerr( _( "EOF encountered inside an action" ) );
			yyterminate();
			}

<EXTENDED_COMMENT,ਸਮੂਹ_WITH_PARAMS,ਸਮੂਹ_MINUS_PARAMS><<EOF>>	{
			synerr( _( "EOF encountered inside pattern" ) );
			yyterminate();
			}

<SECT2,QUOTE,FIRSTCCL,CCL>{ESCSEQ}	{
			yylval = myesc( (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) yytext );

			ਜੇ ( YY_ਸ਼ੁਰੂ == FIRSTCCL )
				BEGIN(CCL);

			ਵਾਪਸ CHAR;
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


ਪੂਰਨ yywrap(ਖਾਲੀ)
	{
	ਜੇ ( --num_input_files > 0 )
		{
		ਸੈੱਟ_ਨਿਵੇਸ਼_file( *++ਨਿਵੇਸ਼_files );
		ਵਾਪਸ 0;
		}

	ਨਹੀਂਤਾਂ
		ਵਾਪਸ 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

ਖਾਲੀ ਸੈੱਟ_ਨਿਵੇਸ਼_file( ਅੱਖਰ *file )
	{
	ਜੇ ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		ਜੇ ( yyin == ਨਿਰਾ )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	ਨਹੀਂਤਾਂ
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

ਖਾਲੀ context_call(ਅੱਖਰ *txt) {
	ਅਚਲ ਅੱਖਰ *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	ਜੇ (context_arg == ਨਿਰਾ) {
		ਜੋੜੋ_action(txt);
	} ਨਹੀਂਤਾਂ {
		ਅੱਖਰ buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		ਪ੍ਰਤਿਜ੍ਞਾ(txt[ਲੜੀ_ਲੰਬਾਈ(txt)-1] == ')');
		strncpy(buf, txt, ਆਕਾਰ(buf));
		buf[ਲੜੀ_ਲੰਬਾਈ(buf)-1] = '\0';	/* remove trailing ) */
		ਜੋੜੋ_action(buf);
		ਜੇ (txt[ਲੜੀ_ਲੰਬਾਈ(buf)-1] != '(') {
			ਜੋੜੋ_action(", ");
		}
		ਜੋੜੋ_action(context_arg);
		ਜੋੜੋ_action(")");
	}
}

ਖਾਲੀ context_member(ਅੱਖਰ *txt, ਅਚਲ ਅੱਖਰ *prop) {
	ਅਚਲ ਅੱਖਰ *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	ਜੇ (context_format == ਨਿਰਾ) {
		ਜੋੜੋ_action(txt);
	} ਨਹੀਂਤਾਂ {
		ਅੱਖਰ buf[128];
		snprintf(buf, ਆਕਾਰ(buf), context_format, txt);
		ਜੋੜੋ_action(buf);
	}
}
