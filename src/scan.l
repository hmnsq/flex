/* scan.l - scanner for flex input -*-C-*- */

%top{
/* flexdef.h includes config.h, which may contain macros that alter the API */
/* of libc functions. Must include first before any libc header. */
#ಅನ್ತರ್ಭಾವ "flexdef.h"
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

#ಅನ್ತರ್ಭಾವ "parse.h"
ಬಾಹ್ಯ bool tablesverify, tablesext;
ಬಾಹ್ಯ bool trlcontxt; /* Set in parse.y for each rule. */
ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *escaped_qstart, *escaped_qend;

#ವ್ಯಾಖ್ಯಾನಿಸು M4QSTART "[""["
#ವ್ಯಾಖ್ಯಾನಿಸು M4QEND "]""]"

#ವ್ಯಾಖ್ಯಾನಿಸು ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#ವ್ಯಾಖ್ಯಾನಿಸು ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ECHO ಕೂಡಿಸು_action( yytext )
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ECHO_QSTART ಕೂಡಿಸು_action (ESCAPED_QSTART)
#ವ್ಯಾಖ್ಯಾನಿಸು ACTION_ECHO_QEND   ಕೂಡಿಸು_action (ESCAPED_QEND)

#ವ್ಯಾಖ್ಯಾನಿಸು MARK_ಕೊನೆ_ದ_PROLOG mark_prolog();

#ವ್ಯಾಖ್ಯಾನಿಸು YY_DECL \
	ಪೂರ್ಣಾಂಕ flexscan(ಶೂನ್ಯ)

#ವ್ಯಾಖ್ಯಾನಿಸು RETURNCHAR \
	yylval = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) yytext[0]; \
	ಹಿಂತಿರುಗಿ CHAR;

#ವ್ಯಾಖ್ಯಾನಿಸು RETURNNAME \
	ಆದರೆ(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, ಗಾತ್ರ(nmstr) ); \
	ಹಿಂತಿರುಗಿ NAME; \
	 } \
	ಇಲ್ಲದಿದ್ದರೆ \
	 ಮಾಡು { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } ಆಗ (0)

#ವ್ಯಾಖ್ಯಾನಿಸು PUT_ಹಿಂಭಾಗ_STRING(str, ಆರಂಭ) \
	{ size_t i = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ( str );	\
	  ಆಗ ( i > ಆರಂಭ )		\
	    unput((str)[--i]);		\
	}

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_REJECT(str) \
	ಆದರೆ ( all_ಊರ್ಧ್ವ( str ) ) \
		reject = true;

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_YYREJECT(str) \
	ಆದರೆ ( all_ಅಧೋ( str ) ) \
		reject = true;

#ವ್ಯಾಖ್ಯಾನಿಸು YY_USER_INIT \
	ಆದರೆ ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#ವ್ಯಾಖ್ಯಾನಿಸು ಆರಂಭ_CODEBLOCK(x) ಮಾಡು { \
    /* Emit the needed line directive... */\
    ಆದರೆ (indented_ಸಂಕೇತ == false) { \
        ಆದರೆ (!x) linenum++; \
        ಸಾಲು_directive_ಹೊರಹೋಗು(ಖಾಲಿ, infilename, linenum);	\
    } \
    ಕೂಡಿಸು_action(M4QSTART); \
    yy_ತಳ್ಳು_state(CODEBLOCK); \
    ಆದರೆ ((indented_ಸಂಕೇತ = x)) ACTION_ECHO; \
} ಆಗ(0)

#ವ್ಯಾಖ್ಯಾನಿಸು ಕೊನೆ_CODEBLOCK ಮಾಡು { \
    yy_ತೆಗೆ_state();\
    ಕೂಡಿಸು_action(M4QEND); \
    ಆದರೆ (!indented_ಸಂಕೇತ) ಸಾಲು_directive_ಹೊರಹೋಗು(ಖಾಲಿ, ಖಾಲಿ, linenum);	\
} ಆಗ (0)

%}

%option caseless nodefault noreject ರಾಶಿ noyy_ತುದಿ_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL ಅಂಕೆ_2 QUOTE
%x FIRSTCCL CCL ACTION RECOVER COMMENT ACTION_STRING PERCENT_BRACE_ACTION
%x OPTION LINEDIR CODEBLOCK_ಹೊಂದಿಕೆ_BRACE
%x ಗುಂಪು_WITH_PARAMS
%x ಗುಂಪು_MINUS_PARAMS
%x EXTENDED_COMMENT
%x COMMENT_DISCARD ಸಂಕೇತ_COMMENT
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

ಮೊದಲ_CCL_CHAR	([^\\\n]|{ESCSEQ})
CCL_CHAR	([^\\\n\]]|{ESCSEQ})
CCL_ಅಭಿವ್ಯಕ್ತಿ	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
ಶೂನ್ಯ context_call(ಅಕ್ಷರ *);
ಶೂನ್ಯ context_member(ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *);
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು yyreject
%}
%%
	ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ bracelevel, didadef, indented_ಸಂಕೇತ;
	ಸ್ಥಿರ bool doing_ನಿಯಮ_action = false;
	ಸ್ಥಿರ bool option_sense;

	ಸ್ಥಿರ bool doing_codeblock = false;
	ಪೂರ್ಣಾಂಕ brace_ಆಳ=0, brace_ಆರಂಭ_ಸಾಲು=0;
	ಅಕ್ಷರ nmdef[MAXLINE];


<INITIAL>{
	^{WS}		ಆರಂಭ_CODEBLOCK(true);
	^"/*"		ಕೂಡಿಸು_action("/*[""["); yy_ತಳ್ಳು_state( COMMENT );
	^#{OPTWS}ಸಾಲು{WS}	yy_ತಳ್ಳು_state( LINEDIR );
	^"%s"{NAME}?	ಹಿಂತಿರುಗಿ SCDECL;
	^"%x"{NAME}?	ಹಿಂತಿರುಗಿ XSCDECL;
	^"%{".*{NL}	ಆರಂಭ_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		ಅಕ್ಷರ trampoline[512];
                brace_ಆರಂಭ_ಸಾಲು = linenum;
                ++linenum;
		snprintf(trampoline, ಗಾತ್ರ(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                ಆದರೆ (ctrl.gen_ಸಾಲು_dirs)
                    buf_strappend(&ತುದಿ_buf, trampoline);
                brace_ಆಳ = 1;
                yy_ತಳ್ಳು_state(CODEBLOCK_ಹೊಂದಿಕೆ_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			ಸಾಲು_directive_ಹೊರಹೋಗು(ಖಾಲಿ, infilename, linenum);
			BEGIN(SECT2PROLOG);
			ಹಿಂತಿರುಗಿ SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); ಹಿಂತಿರುಗಿ TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			ಆದರೆ(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, ಗಾತ್ರ(nmstr) );
			 }
			ಇಲ್ಲದಿದ್ದರೆ
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


<COMMENT,ಸಂಕೇತ_COMMENT>{ /* */
        [^\[\]\*\n]*  ACTION_ECHO;
        .           ACTION_ECHO;

	{NL}	    ++linenum; ACTION_ECHO;
}
<COMMENT>{
	"*/"	    ಕೂಡಿಸು_action("*/]""]"); yy_ತೆಗೆ_state();
}
<ಸಂಕೇತ_COMMENT>{
        "*/"        ACTION_ECHO; yy_ತೆಗೆ_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_ತೆಗೆ_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_ತೆಗೆ_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_ತೆಗೆ_state();
	[[:digit:]]+	linenum = myctoi( yytext );

	"\""[^""\n]*"\""	{
			ಬಿಡುಗಡೆ(infilename);
			infilename = xstrdup(yytext + 1);
			infilename[ಅಕ್ಷರಸರಣಿ_ಉದ್ದ( infilename ) - 1] = '\0';
			}
	.		/* ignore spurious characters */
}
<ACTION,CODEBLOCK,ACTION_STRING,PERCENT_BRACE_ACTION,CHARACTER_CONSTANT,COMMENT,ಸಂಕೇತ_COMMENT>{
   {M4QSTART}   ACTION_ECHO_QSTART;
   {M4QEND}     ACTION_ECHO_QEND;
}

<CODEBLOCK>{
	^"%}".*{NL}	++linenum; ಕೊನೆ_CODEBLOCK;
	[^\n%\[\]]*         ACTION_ECHO;
        .		ACTION_ECHO;
	{NL}		{
			++linenum;
			ACTION_ECHO;
			ಆದರೆ ( indented_ಸಂಕೇತ ) ಕೊನೆ_CODEBLOCK;
			}
}

<CODEBLOCK_ಹೊಂದಿಕೆ_BRACE>{
    "}"     {
                ಆದರೆ( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_ತೆಗೆ_state();
                }ಇಲ್ಲದಿದ್ದರೆ
                    buf_strnappend(&ತುದಿ_buf, yytext, yyleng);
            }

    "{"     {
                brace_ಆಳ++;
                buf_strnappend(&ತುದಿ_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&ತುದಿ_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&ತುದಿ_buf, escaped_qstart, (ಪೂರ್ಣಾಂಕ) ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(escaped_qstart));
    {M4QEND}    buf_strnappend(&ತುದಿ_buf, escaped_qend, (ಪೂರ್ಣಾಂಕ) ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&ತುದಿ_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_ಆರಂಭ_ಸಾಲು;
                synerr(_("Unmatched '{'"));
                ಹಿಂತಿರುಗಿ YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        ಆದರೆ(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, ಗಾತ್ರ(nmdef) );
 		         }
 		        ಇಲ್ಲದಿದ್ದರೆ
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ( nmdef );
			    ಆಗ (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			ಆದರೆ ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		ಹಿಂತಿರುಗಿ '=';
	[[:digit:]]+	{nmval = atoi(yytext); ಹಿಂತಿರುಗಿ TOK_NUMERIC;}

	no		option_sense = ! option_sense;

	7ಬಿಟ್		ctrl.csize = option_sense ? 128 : 256;
	8ಬಿಟ್		ctrl.csize = option_sense ? 256 : 128;

	align		ctrl.long_align = option_sense;
	always-interactive	{
			ctrl.always_interactive = option_sense;
			ctrl.interactive = (trit)option_sense;
			}
	array		ctrl.yytext_is_array = option_sense;
	backup		env.backing_ಮೇಲೆ_report = option_sense;
	batch		ctrl.interactive = (trit)!option_sense;
	bison-bridge     ctrl.bison_bridge_lval = option_sense;
	bison-locations  { ಆದರೆ((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|ಸ್ಥಿತಿ-sensitive		sf_ಗಣ_case_ins(!option_sense);
	caseless|ಸ್ಥಿತಿ-insensitive	sf_ಗಣ_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	ಪೂರ್ವನಿಯೋಜಿತ		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	ತುಂಬಿದ		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	ಒಳಹರಿವು		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	ಸಾಲು		ctrl.gen_ಸಾಲು_dirs = option_sense;
	ಮುಖ್ಯ		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			ಆದರೆ (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	ಸೂಚಕ		ctrl.yytext_is_array = ! option_sense;
	ಪಠ		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_ಬಳಸಿದ = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	ರಾಶಿ		ctrl.ರಾಶಿ_ಬಳಸಿದ = option_sense;
	stdinit		ctrl.do_stdinit = option_sense;
	stdout		env.use_stdout = option_sense;
	unistd		ctrl.no_unistd = ! option_sense;
	unput		ctrl.no_yyunput = ! option_sense;
	yyunput		ctrl.no_yyunput = ! option_sense;
	verbose		env.printstats = option_sense;
	warn		env.nowarn = ! option_sense;
	yylineno	ctrl.do_yylineno = option_sense;
	yymore		ctrl.yymore_really_ಬಳಸಿದ = option_sense;
	yywrap		ctrl.do_yywrap = option_sense;
	yyread		ctrl.noyyread = !option_sense;

	yypanic		ctrl.no_yypanic = !option_sense;

	yy_ತಳ್ಳು_state	ctrl.no_yy_ತಳ್ಳು_state = ! option_sense;
	yy_ತೆಗೆ_state	ctrl.no_yy_ತೆಗೆ_state = ! option_sense;
	yy_ತುದಿ_state	ctrl.no_yy_ತುದಿ_state = ! option_sense;

	yy_ಪರಿಶೀಲನೆ_ಬಫರ್	ctrl.no_yy_ಪರಿಶೀಲನೆ_ಬಫರ್ = ! option_sense;
	yy_ಪರಿಶೀಲನೆ_ಬೈಟುಗಳು	ctrl.no_yy_ಪರಿಶೀಲನೆ_ಬೈಟುಗಳು = ! option_sense;
	yy_ಪರಿಶೀಲನೆ_string	ctrl.no_yy_ಪರಿಶೀಲನೆ_string = ! option_sense;

	yyalloc         ctrl.no_flex_alloc = ! option_sense;
	yyrealloc       ctrl.no_flex_realloc = ! option_sense;
	yyfree          ctrl.no_flex_free = ! option_sense;

	yyget_debug     ctrl.no_get_debug = ! option_sense;
	yyset_debug     ctrl.no_ಗಣ_debug = ! option_sense;
	yyget_extra     ctrl.no_yyget_extra = ! option_sense;
	yyset_extra     ctrl.no_yyset_extra = ! option_sense;
	yyget_leng      ctrl.no_yyget_leng = ! option_sense;
	yyget_ಪಠ್ಯ      ctrl.no_yyget_ಪಠ್ಯ = ! option_sense;
	yyget_ಸ್ತಂಭ    ctrl.no_yyget_ಸ್ತಂಭ = ! option_sense;
	yyset_ಸ್ತಂಭ    ctrl.no_yyset_ಸ್ತಂಭ = ! option_sense;
	yyget_lineno    ctrl.no_yyget_lineno = ! option_sense;
	yyset_lineno    ctrl.no_yyset_lineno = ! option_sense;
	yyget_ಒಳ        ctrl.no_yyget_ಒಳ = ! option_sense;
	yyset_ಒಳ        ctrl.no_yyset_ಒಳ = ! option_sense;
	yyget_ಹೊರಹೋಗು       ctrl.no_yyget_ಹೊರಹೋಗು = ! option_sense;
	yyset_ಹೊರಹೋಗು       ctrl.no_yyset_ಹೊರಹೋಗು = ! option_sense;
	yyget_lval      ctrl.no_yyget_lval = ! option_sense;
	yyset_lval      ctrl.no_yyset_lval = ! option_sense;
	yyget_lloc      ctrl.no_yyget_lloc = ! option_sense;
	yyset_lloc      ctrl.no_yyset_lloc = ! option_sense;

	bufsize		ಹಿಂತಿರುಗಿ TOK_BUFSIZE;
	emit		ಹಿಂತಿರುಗಿ TOK_EMIT;
	extra-type	ಹಿಂತಿರುಗಿ TOK_EXTRA_TYPE;
	outfile		ಹಿಂತಿರುಗಿ TOK_OUTFILE;
	ಪೂರ್ವಪ್ರತ್ಯಯ		ಹಿಂತಿರುಗಿ TOK_ಪೂರ್ವಪ್ರತ್ಯಯ;
	yyclass		ಹಿಂತಿರುಗಿ TOK_YYCLASS;
	yylmax		ಹಿಂತಿರುಗಿ TOK_YYLMAX;
	yydecl		ಹಿಂತಿರುಗಿ TOK_YYDECL;
	yyterminate	ಹಿಂತಿರುಗಿ TOK_YYTERMINATE;
	pre-action	ಹಿಂತಿರುಗಿ TOK_PREACTION;
	post-action	ಹಿಂತಿರುಗಿ TOK_POSTACTION;
	user-init	ಹಿಂತಿರುಗಿ TOK_USERINIT;
	ಶೀರ್ಷಿಕೆ(-file)?      ಹಿಂತಿರುಗಿ TOK_ಶೀರ್ಷಿಕೆ_FILE;
	tables-file         ಹಿಂತಿರುಗಿ TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    ಆದರೆ (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			ಆದರೆ(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, ಗಾತ್ರ(nmstr) );
			 }
			ಇಲ್ಲದಿದ್ದರೆ
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[ಅಕ್ಷರಸರಣಿ_ಉದ್ದ( nmstr ) - 1] = '\0';
			ಹಿಂತಿರುಗಿ NAME;
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

	^{WS} ಆರಂಭ_CODEBLOCK(true); /* indented code in prolog */

	^{NOT_WS}.*	{
        /* non-indented code */
		ಆದರೆ ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_ಗಣ_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆರಂಭ_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			ಹಿಂತಿರುಗಿ YY_NULL; /* to stop the parser */
			}
}

<SECT2>{
	^{OPTWS}{NL}	++linenum; /* allow blank lines in section 2 */

	^{OPTWS}"%{"	{
			indented_ಸಂಕೇತ = false;
			doing_codeblock = true;
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);
			}

	^{OPTWS}"<"	    {
                        /* Allow "<" to appear in (?x) patterns. */
                        ಆದರೆ (!sf_skip_ws())
                            BEGIN(SC);
                        ಹಿಂತಿರುಗಿ '<';
                    }
	^{OPTWS}"^"	ಹಿಂತಿರುಗಿ '^';
	"\""		BEGIN(QUOTE); ಹಿಂತಿರುಗಿ '"';
	"{"/[[:digit:]]	{
			BEGIN(ಅಂಕೆ_2);
			ಆದರೆ ( ctrl.lex_compat || ctrl.posix_compat )
				ಹಿಂತಿರುಗಿ BEGIN_REPEAT_POSIX;
			ಇಲ್ಲದಿದ್ದರೆ
				ಹಿಂತಿರುಗಿ BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	ಹಿಂತಿರುಗಿ '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			ಆದರೆ ( ಒಳ_ನಿಯಮ )
				{
				doing_ನಿಯಮ_action = true;
				ಒಳ_ನಿಯಮ = false;
				ಹಿಂತಿರುಗಿ '\n';
				}
			}
	{WS}"|".*{NL}	{
                        ಆದರೆ (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            ಪೂರ್ಣಾಂಕ amt = (ಪೂರ್ಣಾಂಕ) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        ಇಲ್ಲದಿದ್ದರೆ {
                            ಕೂಡಿಸು_action("]""]");
                            continued_action = true;
                            ++linenum;
                            ಹಿಂತಿರುಗಿ '\n';
                        }
                    }

	^{WS}"/*"	{

                ಆದರೆ (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_ತಳ್ಳು_state(COMMENT_DISCARD);
                }
                ಇಲ್ಲದಿದ್ದರೆ{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            ಆದರೆ (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            ಇಲ್ಲದಿದ್ದರೆ{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                ಆದರೆ ( ಒಳ_ನಿಯಮ )
                    {
                    doing_ನಿಯಮ_action = true;
                    ಒಳ_ನಿಯಮ = false;
                    ಹಿಂತಿರುಗಿ '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            ಆದರೆ (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            ಇಲ್ಲದಿದ್ದರೆ{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                ಆದರೆ ( ಒಳ_ನಿಯಮ )
                    {
                    doing_ನಿಯಮ_action = true;
                    ಒಳ_ನಿಯಮ = false;
                    ಹಿಂತಿರುಗಿ '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	ಹಿಂತಿರುಗಿ EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({ಮೊದಲ_CCL_CHAR}|{CCL_ಅಭಿವ್ಯಕ್ತಿ})({CCL_CHAR}|{CCL_ಅಭಿವ್ಯಕ್ತಿ})*	{
			ಪೂರ್ಣಾಂಕ cclval;

			ಆದರೆ(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, ಗಾತ್ರ(nmstr) );
			 }
			ಇಲ್ಲದಿದ್ದರೆ
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			ಆದರೆ (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			ಇಲ್ಲದಿದ್ದರೆ
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
				ಹಿಂತಿರುಗಿ '[';
				}
			}
    "{-}"       ಹಿಂತಿರುಗಿ CCL_OP_DIFF;
    "{+}"       ಹಿಂತಿರುಗಿ CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			ಅಕ್ಷರ *nmdefptr;
            ಪೂರ್ಣಾಂಕ ಕೊನೆ_is_ws, ಕೊನೆ_ch;

            ಕೊನೆ_ch = yytext[yyleng-1];
            ಕೊನೆ_is_ws = ಕೊನೆ_ch != '}' ? 1 : 0;

 			ಆದರೆ(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, ಗಾತ್ರ(nmstr) );
 			 }
 			ಇಲ್ಲದಿದ್ದರೆ
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - ಕೊನೆ_is_ws] = '\0';  /* chop trailing brace */

			ಆದರೆ ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			ಇಲ್ಲದಿದ್ದರೆ
				{ /* push back name surrounded by ()'s */
				size_t len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ( nmdefptr );
                ಆದರೆ (ಕೊನೆ_is_ws)
                    unput(ಕೊನೆ_ch);

				ಆದರೆ ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (ಕೊನೆ_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_ಹಿಂಭಾಗ_STRING(nmdefptr, 0);

					ಆದರೆ ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				ಇಲ್ಲದಿದ್ದರೆ
					{
					unput(')');
					PUT_ಹಿಂಭಾಗ_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    ಆದರೆ (sf_skip_ws())
                        yy_ತಳ್ಳು_state(COMMENT_DISCARD);
                    ಇಲ್ಲದಿದ್ದರೆ{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        ಹಿಂತಿರುಗಿ '/';
                    }
                }

    "(?#"       {
                    ಆದರೆ (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_ತಳ್ಳು(); 
                        ಹಿಂತಿರುಗಿ '(';
                    }
                    ಇಲ್ಲದಿದ್ದರೆ
                        yy_ತಳ್ಳು_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_ತಳ್ಳು();
                    ಆದರೆ (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    ಇಲ್ಲದಿದ್ದರೆ
                        BEGIN(ಗುಂಪು_WITH_PARAMS);
                    ಹಿಂತಿರುಗಿ '(';
                }
    "("         sf_ತಳ್ಳು(); ಹಿಂತಿರುಗಿ '(';
    ")"         {
                    ಆದರೆ (sf_ತುದಿ_ix > 0) {
                        sf_ತೆಗೆ();
                        ಹಿಂತಿರುಗಿ ')';
                    } ಇಲ್ಲದಿದ್ದರೆ
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	ಹಿಂತಿರುಗಿ (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		ಹಿಂತಿರುಗಿ (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) yytext[0];
	">"		BEGIN(SECT2); ಹಿಂತಿರುಗಿ '>';
	">"/^		BEGIN(CARETISBOL); ಹಿಂತಿರುಗಿ '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); ಹಿಂತಿರುಗಿ '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); ಹಿಂತಿರುಗಿ '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			ಹಿಂತಿರುಗಿ '"';
			}
}

<ಗುಂಪು_WITH_PARAMS>{
    ":"     BEGIN(SECT2);
    "-"     BEGIN(ಗುಂಪು_MINUS_PARAMS);
    i       sf_ಗಣ_case_ins(1);
    s       sf_ಗಣ_dot_all(1);
    x       sf_ಗಣ_skip_ws(1);
}
<ಗುಂಪು_MINUS_PARAMS>{
    ":"     BEGIN(SECT2);
    i       sf_ಗಣ_case_ins(0);
    s       sf_ಗಣ_dot_all(0);
    x       sf_ಗಣ_skip_ws(0);
}

<FIRSTCCL>{
	"^"/[^-\]\n]	BEGIN(CCL); ಹಿಂತಿರುಗಿ '^';
	"^"/("-"|"]")	ಹಿಂತಿರುಗಿ '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	ಹಿಂತಿರುಗಿ '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); ಹಿಂತಿರುಗಿ ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			ಹಿಂತಿರುಗಿ ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_ನಕ್ಷೆ;
	"[:lower:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_ಅಧೋ;
	"[:print:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_ಊರ್ಧ್ವ;
	"[:xdigit:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_ನಕ್ಷೆ;
	"[:^lower:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_ಅಧೋ;
	"[:^print:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_ಊರ್ಧ್ವ;
	"[:^xdigit:]"	BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_NEG_XDIGIT;
	{CCL_ಅಭಿವ್ಯಕ್ತಿ}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); ಹಿಂತಿರುಗಿ CCE_ALNUM;
			}
}

<ಅಂಕೆ_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			ಹಿಂತಿರುಗಿ ಸಂಖ್ಯೆ;
			}

	","		ಹಿಂತಿರುಗಿ ',';
	"}"		{
			BEGIN(SECT2);
			ಆದರೆ ( ctrl.lex_compat || ctrl.posix_compat )
				ಹಿಂತಿರುಗಿ ಕೊನೆ_REPEAT_POSIX;
			ಇಲ್ಲದಿದ್ದರೆ
				ಹಿಂತಿರುಗಿ ಕೊನೆ_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			ಹಿಂತಿರುಗಿ '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			ಹಿಂತಿರುಗಿ '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_ತಳ್ಳು_state( ಸಂಕೇತ_COMMENT );

	<CODEBLOCK,ACTION>{
		"reject" {
			ACTION_ECHO;
			CHECK_REJECT(yytext);
        }
		"yyreject"{OPTWS}"("{OPTWS}")" {
			ಕೂಡಿಸು_action("]""]M4_HOOK_REJECT[""[");
			CHECK_YYREJECT(yytext);
        }
		"yymore"{OPTWS}"("{OPTWS}")" {
			yymore_ಬಳಸಿದ = true;
			ಆದರೆ (ctrl.rewrite)
				context_call(yytext);
			ಇಲ್ಲದಿದ್ದರೆ
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		ಆದರೆ (bracelevel <= 0 || (doing_codeblock && indented_ಸಂಕೇತ)) {
            ಆದರೆ ( doing_ನಿಯಮ_action )
                ಕೂಡಿಸು_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

            doing_ನಿಯಮ_action = doing_codeblock = false;
            BEGIN(SECT2);
        }
    }
}


	/* yyreject and yymore() are checked for above, in PERCENT_BRACE_ACTION */
<ACTION>{
	"{"		ACTION_ECHO; ++bracelevel;
	"}"		ACTION_ECHO; --bracelevel;
	yyecho\(\)|yyinput\(\)|yystart\({FUNARGS}\)|yybegin\({FUNARGS}\)|yyunput\({FUNARGS}\)|yypanic\({FUNARGS}\)|yyatbol\(\)|yysetbol\({FUNARGS}\) {
			ಆದರೆ (ctrl.rewrite)
				context_call(yytext);
			ಇಲ್ಲದಿದ್ದರೆ
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			ಕೂಡಿಸು_action("]""]");
			ಕೂಡಿಸು_action(yytext);
			ಕೂಡಿಸು_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			ಆದರೆ (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			ಇಲ್ಲದಿದ್ದರೆ
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			ಆದರೆ (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			ಇಲ್ಲದಿದ್ದರೆ
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
                ಆದರೆ (bracelevel <= 0) {
                   ಆದರೆ ( doing_ನಿಯಮ_action )
                      ಕೂಡಿಸು_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

                   doing_ನಿಯಮ_action = false;
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
	{NL}	++linenum; ACTION_ECHO; ಆದರೆ (bracelevel <= 0) { BEGIN(SECT2); } ಇಲ್ಲದಿದ್ದರೆ { BEGIN(ACTION); }
        .	ACTION_ECHO;
}

<COMMENT,ಸಂಕೇತ_COMMENT,COMMENT_DISCARD,ACTION,ACTION_STRING,CHARACTER_CONSTANT><<EOF>>	{
			synerr( _( "EOF encountered inside an action" ) );
			yyterminate();
			}

<EXTENDED_COMMENT,ಗುಂಪು_WITH_PARAMS,ಗುಂಪು_MINUS_PARAMS><<EOF>>	{
			synerr( _( "EOF encountered inside pattern" ) );
			yyterminate();
			}

<SECT2,QUOTE,FIRSTCCL,CCL>{ESCSEQ}	{
			yylval = myesc( (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) yytext );

			ಆದರೆ ( YY_ಆರಂಭ == FIRSTCCL )
				BEGIN(CCL);

			ಹಿಂತಿರುಗಿ CHAR;
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


ಪೂರ್ಣಾಂಕ yywrap(ಶೂನ್ಯ)
	{
	ಆದರೆ ( --num_input_files > 0 )
		{
		ಗಣ_ಒಳಹರಿವು_file( *++ಒಳಹರಿವು_files );
		ಹಿಂತಿರುಗಿ 0;
		}

	ಇಲ್ಲದಿದ್ದರೆ
		ಹಿಂತಿರುಗಿ 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

ಶೂನ್ಯ ಗಣ_ಒಳಹರಿವು_file( ಅಕ್ಷರ *file )
	{
	ಆದರೆ ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		ಆದರೆ ( yyin == ಖಾಲಿ )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	ಇಲ್ಲದಿದ್ದರೆ
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

ಶೂನ್ಯ context_call(ಅಕ್ಷರ *txt) {
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	ಆದರೆ (context_arg == ಖಾಲಿ) {
		ಕೂಡಿಸು_action(txt);
	} ಇಲ್ಲದಿದ್ದರೆ {
		ಅಕ್ಷರ buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		ಪ್ರತಿಜ್ಞಾ(txt[ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(txt)-1] == ')');
		strncpy(buf, txt, ಗಾತ್ರ(buf));
		buf[ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(buf)-1] = '\0';	/* remove trailing ) */
		ಕೂಡಿಸು_action(buf);
		ಆದರೆ (txt[ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(buf)-1] != '(') {
			ಕೂಡಿಸು_action(", ");
		}
		ಕೂಡಿಸು_action(context_arg);
		ಕೂಡಿಸು_action(")");
	}
}

ಶೂನ್ಯ context_member(ಅಕ್ಷರ *txt, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *prop) {
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	ಆದರೆ (context_format == ಖಾಲಿ) {
		ಕೂಡಿಸು_action(txt);
	} ಇಲ್ಲದಿದ್ದರೆ {
		ಅಕ್ಷರ buf[128];
		snprintf(buf, ಗಾತ್ರ(buf), context_format, txt);
		ಕೂಡಿಸು_action(buf);
	}
}
