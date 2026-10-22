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
ಬಾಹ್ಯ ಧ್ರುವ ವರ್ಣ *escaped_qstart, *escaped_qend;

#define M4QSTART "[""["
#define M4QEND "]""]"

#define ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#define ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#define ACTION_ECHO add_action( yytext )
#define ACTION_ECHO_QSTART add_action (ESCAPED_QSTART)
#define ACTION_ECHO_QEND   add_action (ESCAPED_QEND)

#define MARK_END_OF_PROLOG mark_prolog();

#define YY_DECL \
	ಪೂರ್ಣಾಙ್ಕ flexscan(ಶೂನ್ಯ)

#define RETURNCHAR \
	yylval = (unsigned ವರ್ಣ) yytext[0]; \
	ಪ್ರತ್ಯಾಗಮ CHAR;

#define RETURNNAME \
	ಯದಿ(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, ಪರಿಮಾಣ(nmstr) ); \
	ಪ್ರತ್ಯಾಗಮ NAME; \
	 } \
	ಅನ್ಯಥಾ \
	 ಕುರು { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } ಯಾವತ್ (0)

#define PUT_BACK_STRING(str, start) \
	{ size_t i = strlen( str );	\
	  ಯಾವತ್ ( i > start )		\
	    unput((str)[--i]);		\
	}

#define CHECK_REJECT(str) \
	ಯದಿ ( all_upper( str ) ) \
		reject = true;

#define CHECK_YYREJECT(str) \
	ಯದಿ ( all_lower( str ) ) \
		reject = true;

#define YY_USER_INIT \
	ಯದಿ ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#define START_CODEBLOCK(x) ಕುರು { \
    /* Emit the needed line directive... */\
    ಯದಿ (indented_code == false) { \
        ಯದಿ (!x) linenum++; \
        ಸಾಲು_directive_out(ರಿಕ್ತ, infilename, linenum);	\
    } \
    add_action(M4QSTART); \
    yy_ತಳ್ಳು_state(CODEBLOCK); \
    ಯದಿ ((indented_code = x)) ACTION_ECHO; \
} ಯಾವತ್(0)

#define END_CODEBLOCK ಕುರು { \
    yy_ತೆಗೆ_state();\
    add_action(M4QEND); \
    ಯದಿ (!indented_code) ಸಾಲು_directive_out(ರಿಕ್ತ, ರಿಕ್ತ, linenum);	\
} ಯಾವತ್ (0)

%}

%option caseless nodefault noreject ರಾಶಿ noyy_ತುದಿ_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL ಅಂಕೆ_2 QUOTE
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
CCL_ಅಭಿವ್ಯಕ್ತಿ	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
ಶೂನ್ಯ context_call(ವರ್ಣ *);
ಶೂನ್ಯ context_member(ವರ್ಣ *, ಧ್ರುವ ವರ್ಣ *);
#undef yyreject
%}
%%
	ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ bracelevel, didadef, indented_code;
	ಸ್ಥಿರ bool doing_rule_action = false;
	ಸ್ಥಿರ bool option_sense;

	ಸ್ಥಿರ bool doing_codeblock = false;
	ಪೂರ್ಣಾಙ್ಕ brace_depth=0, brace_start_ಸಾಲು=0;
	ವರ್ಣ nmdef[MAXLINE];


<INITIAL>{
	^{WS}		START_CODEBLOCK(true);
	^"/*"		add_action("/*[""["); yy_ತಳ್ಳು_state( COMMENT );
	^#{OPTWS}ಸಾಲು{WS}	yy_ತಳ್ಳು_state( LINEDIR );
	^"%s"{NAME}?	ಪ್ರತ್ಯಾಗಮ SCDECL;
	^"%x"{NAME}?	ಪ್ರತ್ಯಾಗಮ XSCDECL;
	^"%{".*{NL}	START_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		ವರ್ಣ trampoline[512];
                brace_start_ಸಾಲು = linenum;
                ++linenum;
		snprintf(trampoline, ಪರಿಮಾಣ(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                ಯದಿ (ctrl.gen_ಸಾಲು_dirs)
                    buf_strappend(&ತುದಿ_buf, trampoline);
                brace_depth = 1;
                yy_ತಳ್ಳು_state(CODEBLOCK_MATCH_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			ಸಾಲು_directive_out(ರಿಕ್ತ, infilename, linenum);
			BEGIN(SECT2PROLOG);
			ಪ್ರತ್ಯಾಗಮ SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); ಪ್ರತ್ಯಾಗಮ TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			ಯದಿ(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, ಪರಿಮಾಣ(nmstr) );
			 }
			ಅನ್ಯಥಾ
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
	"*/"	    add_action("*/]""]"); yy_ತೆಗೆ_state();
}
<CODE_COMMENT>{
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
			ಮುಕ್ತ(infilename);
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
			ಯದಿ ( indented_code ) END_CODEBLOCK;
			}
}

<CODEBLOCK_MATCH_BRACE>{
    "}"     {
                ಯದಿ( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_ತೆಗೆ_state();
                }ಅನ್ಯಥಾ
                    buf_strnappend(&ತುದಿ_buf, yytext, yyleng);
            }

    "{"     {
                brace_depth++;
                buf_strnappend(&ತುದಿ_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&ತುದಿ_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&ತುದಿ_buf, escaped_qstart, (ಪೂರ್ಣಾಙ್ಕ) strlen(escaped_qstart));
    {M4QEND}    buf_strnappend(&ತುದಿ_buf, escaped_qend, (ಪೂರ್ಣಾಙ್ಕ) strlen(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&ತುದಿ_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_start_ಸಾಲು;
                synerr(_("Unmatched '{'"));
                ಪ್ರತ್ಯಾಗಮ YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        ಯದಿ(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, ಪರಿಮಾಣ(nmdef) );
 		         }
 		        ಅನ್ಯಥಾ
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = strlen( nmdef );
			    ಯಾವತ್ (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			ಯದಿ ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		ಪ್ರತ್ಯಾಗಮ '=';
	[[:digit:]]+	{nmval = atoi(yytext); ಪ್ರತ್ಯಾಗಮ TOK_NUMERIC;}

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
	bison-locations  { ಯದಿ((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|ಪಕ್ಷ-sensitive		sf_set_case_ins(!option_sense);
	caseless|ಪಕ್ಷ-insensitive	sf_set_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	ಸ್ವಭಾವ		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	full		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	ಒಳಹರಿವು		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	ಸಾಲು		ctrl.gen_ಸಾಲು_dirs = option_sense;
	main		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			ಯದಿ (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	pointer		ctrl.yytext_is_array = ! option_sense;
	ಪಠ		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_used = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	ರಾಶಿ		ctrl.ರಾಶಿ_used = option_sense;
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

	yy_ತಳ್ಳು_state	ctrl.no_yy_ತಳ್ಳು_state = ! option_sense;
	yy_ತೆಗೆ_state	ctrl.no_yy_ತೆಗೆ_state = ! option_sense;
	yy_ತುದಿ_state	ctrl.no_yy_ತುದಿ_state = ! option_sense;

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

	bufsize		ಪ್ರತ್ಯಾಗಮ TOK_BUFSIZE;
	emit		ಪ್ರತ್ಯಾಗಮ TOK_EMIT;
	extra-type	ಪ್ರತ್ಯಾಗಮ TOK_EXTRA_TYPE;
	outfile		ಪ್ರತ್ಯಾಗಮ TOK_OUTFILE;
	prefix		ಪ್ರತ್ಯಾಗಮ TOK_PREFIX;
	yyclass		ಪ್ರತ್ಯಾಗಮ TOK_YYCLASS;
	yylmax		ಪ್ರತ್ಯಾಗಮ TOK_YYLMAX;
	yydecl		ಪ್ರತ್ಯಾಗಮ TOK_YYDECL;
	yyterminate	ಪ್ರತ್ಯಾಗಮ TOK_YYTERMINATE;
	pre-action	ಪ್ರತ್ಯಾಗಮ TOK_PREACTION;
	post-action	ಪ್ರತ್ಯಾಗಮ TOK_POSTACTION;
	user-init	ಪ್ರತ್ಯಾಗಮ TOK_USERINIT;
	header(-file)?      ಪ್ರತ್ಯಾಗಮ TOK_HEADER_FILE;
	tables-file         ಪ್ರತ್ಯಾಗಮ TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    ಯದಿ (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			ಯದಿ(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, ಪರಿಮಾಣ(nmstr) );
			 }
			ಅನ್ಯಥಾ
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[strlen( nmstr ) - 1] = '\0';
			ಪ್ರತ್ಯಾಗಮ NAME;
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
		ಯದಿ ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_set_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } ಅನ್ಯಥಾ {
            START_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			ಪ್ರತ್ಯಾಗಮ YY_NULL; /* to stop the parser */
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
                        ಯದಿ (!sf_skip_ws())
                            BEGIN(SC);
                        ಪ್ರತ್ಯಾಗಮ '<';
                    }
	^{OPTWS}"^"	ಪ್ರತ್ಯಾಗಮ '^';
	"\""		BEGIN(QUOTE); ಪ್ರತ್ಯಾಗಮ '"';
	"{"/[[:digit:]]	{
			BEGIN(ಅಂಕೆ_2);
			ಯದಿ ( ctrl.lex_compat || ctrl.posix_compat )
				ಪ್ರತ್ಯಾಗಮ BEGIN_REPEAT_POSIX;
			ಅನ್ಯಥಾ
				ಪ್ರತ್ಯಾಗಮ BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	ಪ್ರತ್ಯಾಗಮ '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			ಯದಿ ( in_rule )
				{
				doing_rule_action = true;
				in_rule = false;
				ಪ್ರತ್ಯಾಗಮ '\n';
				}
			}
	{WS}"|".*{NL}	{
                        ಯದಿ (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            ಪೂರ್ಣಾಙ್ಕ amt = (ಪೂರ್ಣಾಙ್ಕ) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        ಅನ್ಯಥಾ {
                            add_action("]""]");
                            continued_action = true;
                            ++linenum;
                            ಪ್ರತ್ಯಾಗಮ '\n';
                        }
                    }

	^{WS}"/*"	{

                ಯದಿ (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_ತಳ್ಳು_state(COMMENT_DISCARD);
                }
                ಅನ್ಯಥಾ{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            ಯದಿ (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            ಅನ್ಯಥಾ{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                ಯದಿ ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    ಪ್ರತ್ಯಾಗಮ '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            ಯದಿ (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            ಅನ್ಯಥಾ{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                ಯದಿ ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    ಪ್ರತ್ಯಾಗಮ '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	ಪ್ರತ್ಯಾಗಮ EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({FIRST_CCL_CHAR}|{CCL_ಅಭಿವ್ಯಕ್ತಿ})({CCL_CHAR}|{CCL_ಅಭಿವ್ಯಕ್ತಿ})*	{
			ಪೂರ್ಣಾಙ್ಕ cclval;

			ಯದಿ(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, ಪರಿಮಾಣ(nmstr) );
			 }
			ಅನ್ಯಥಾ
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			ಯದಿ (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			ಅನ್ಯಥಾ
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
				ಪ್ರತ್ಯಾಗಮ '[';
				}
			}
    "{-}"       ಪ್ರತ್ಯಾಗಮ CCL_OP_DIFF;
    "{+}"       ಪ್ರತ್ಯಾಗಮ CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			ವರ್ಣ *nmdefptr;
            ಪೂರ್ಣಾಙ್ಕ end_is_ws, end_ch;

            end_ch = yytext[yyleng-1];
            end_is_ws = end_ch != '}' ? 1 : 0;

 			ಯದಿ(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, ಪರಿಮಾಣ(nmstr) );
 			 }
 			ಅನ್ಯಥಾ
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - end_is_ws] = '\0';  /* chop trailing brace */

			ಯದಿ ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			ಅನ್ಯಥಾ
				{ /* push back name surrounded by ()'s */
				size_t len = strlen( nmdefptr );
                ಯದಿ (end_is_ws)
                    unput(end_ch);

				ಯದಿ ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (end_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_BACK_STRING(nmdefptr, 0);

					ಯದಿ ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				ಅನ್ಯಥಾ
					{
					unput(')');
					PUT_BACK_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    ಯದಿ (sf_skip_ws())
                        yy_ತಳ್ಳು_state(COMMENT_DISCARD);
                    ಅನ್ಯಥಾ{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        ಪ್ರತ್ಯಾಗಮ '/';
                    }
                }

    "(?#"       {
                    ಯದಿ (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_ತಳ್ಳು(); 
                        ಪ್ರತ್ಯಾಗಮ '(';
                    }
                    ಅನ್ಯಥಾ
                        yy_ತಳ್ಳು_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_ತಳ್ಳು();
                    ಯದಿ (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    ಅನ್ಯಥಾ
                        BEGIN(GROUP_WITH_PARAMS);
                    ಪ್ರತ್ಯಾಗಮ '(';
                }
    "("         sf_ತಳ್ಳು(); ಪ್ರತ್ಯಾಗಮ '(';
    ")"         {
                    ಯದಿ (sf_ತುದಿ_ix > 0) {
                        sf_ತೆಗೆ();
                        ಪ್ರತ್ಯಾಗಮ ')';
                    } ಅನ್ಯಥಾ
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	ಪ್ರತ್ಯಾಗಮ (unsigned ವರ್ಣ) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		ಪ್ರತ್ಯಾಗಮ (unsigned ವರ್ಣ) yytext[0];
	">"		BEGIN(SECT2); ಪ್ರತ್ಯಾಗಮ '>';
	">"/^		BEGIN(CARETISBOL); ಪ್ರತ್ಯಾಗಮ '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); ಪ್ರತ್ಯಾಗಮ '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); ಪ್ರತ್ಯಾಗಮ '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			ಪ್ರತ್ಯಾಗಮ '"';
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
	"^"/[^-\]\n]	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ '^';
	"^"/("-"|"]")	ಪ್ರತ್ಯಾಗಮ '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	ಪ್ರತ್ಯಾಗಮ '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); ಪ್ರತ್ಯಾಗಮ ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			ಪ್ರತ್ಯಾಗಮ ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_GRAPH;
	"[:lower:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_LOWER;
	"[:print:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_UPPER;
	"[:xdigit:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_GRAPH;
	"[:^lower:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_LOWER;
	"[:^print:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_UPPER;
	"[:^xdigit:]"	BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_NEG_XDIGIT;
	{CCL_ಅಭಿವ್ಯಕ್ತಿ}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); ಪ್ರತ್ಯಾಗಮ CCE_ALNUM;
			}
}

<ಅಂಕೆ_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			ಪ್ರತ್ಯಾಗಮ ಸಂಖ್ಯೆ;
			}

	","		ಪ್ರತ್ಯಾಗಮ ',';
	"}"		{
			BEGIN(SECT2);
			ಯದಿ ( ctrl.lex_compat || ctrl.posix_compat )
				ಪ್ರತ್ಯಾಗಮ END_REPEAT_POSIX;
			ಅನ್ಯಥಾ
				ಪ್ರತ್ಯಾಗಮ END_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			ಪ್ರತ್ಯಾಗಮ '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			ಪ್ರತ್ಯಾಗಮ '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_ತಳ್ಳು_state( CODE_COMMENT );

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
			ಯದಿ (ctrl.rewrite)
				context_call(yytext);
			ಅನ್ಯಥಾ
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		ಯದಿ (bracelevel <= 0 || (doing_codeblock && indented_code)) {
            ಯದಿ ( doing_rule_action )
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
			ಯದಿ (ctrl.rewrite)
				context_call(yytext);
			ಅನ್ಯಥಾ
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			add_action("]""]");
			add_action(yytext);
			add_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			ಯದಿ (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			ಅನ್ಯಥಾ
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			ಯದಿ (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			ಅನ್ಯಥಾ
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
                ಯದಿ (bracelevel <= 0) {
                   ಯದಿ ( doing_rule_action )
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
	{NL}	++linenum; ACTION_ECHO; ಯದಿ (bracelevel <= 0) { BEGIN(SECT2); } ಅನ್ಯಥಾ { BEGIN(ACTION); }
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
			yylval = myesc( (unsigned ವರ್ಣ *) yytext );

			ಯದಿ ( YY_START == FIRSTCCL )
				BEGIN(CCL);

			ಪ್ರತ್ಯಾಗಮ CHAR;
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


ಪೂರ್ಣಾಙ್ಕ yywrap(ಶೂನ್ಯ)
	{
	ಯದಿ ( --num_input_files > 0 )
		{
		set_ಒಳಹರಿವು_file( *++ಒಳಹರಿವು_files );
		ಪ್ರತ್ಯಾಗಮ 0;
		}

	ಅನ್ಯಥಾ
		ಪ್ರತ್ಯಾಗಮ 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

ಶೂನ್ಯ set_ಒಳಹರಿವು_file( ವರ್ಣ *file )
	{
	ಯದಿ ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		ಯದಿ ( yyin == ರಿಕ್ತ )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	ಅನ್ಯಥಾ
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

ಶೂನ್ಯ context_call(ವರ್ಣ *txt) {
	ಧ್ರುವ ವರ್ಣ *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	ಯದಿ (context_arg == ರಿಕ್ತ) {
		add_action(txt);
	} ಅನ್ಯಥಾ {
		ವರ್ಣ buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		ಪ್ರತಿಜ್ಞಾ(txt[strlen(txt)-1] == ')');
		strncpy(buf, txt, ಪರಿಮಾಣ(buf));
		buf[strlen(buf)-1] = '\0';	/* remove trailing ) */
		add_action(buf);
		ಯದಿ (txt[strlen(buf)-1] != '(') {
			add_action(", ");
		}
		add_action(context_arg);
		add_action(")");
	}
}

ಶೂನ್ಯ context_member(ವರ್ಣ *txt, ಧ್ರುವ ವರ್ಣ *prop) {
	ಧ್ರುವ ವರ್ಣ *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	ಯದಿ (context_format == ರಿಕ್ತ) {
		add_action(txt);
	} ಅನ್ಯಥಾ {
		ವರ್ಣ buf[128];
		snprintf(buf, ಪರಿಮಾಣ(buf), context_format, txt);
		add_action(buf);
	}
}
