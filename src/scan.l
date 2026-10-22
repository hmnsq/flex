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

#تعریف_کن M4QSTART "[""["
#تعریف_کن M4QEND "]""]"

#تعریف_کن ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#تعریف_کن ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#تعریف_کن ACTION_ECHO جمع_کن_action( yytext )
#تعریف_کن ACTION_ECHO_QSTART جمع_کن_action (ESCAPED_QSTART)
#تعریف_کن ACTION_ECHO_QEND   جمع_کن_action (ESCAPED_QEND)

#تعریف_کن MARK_انتها_از_PROLOG mark_prolog();

#تعریف_کن YY_DECL \
	صحيح flexscan(فراغ)

#تعریف_کن RETURNCHAR \
	yylval = (بیعلامت حرف) yytext[0]; \
	أرجع CHAR;

#تعریف_کن RETURNNAME \
	إذا(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, حجم(nmstr) ); \
	أرجع NAME; \
	 } \
	وإلا \
	 افعل { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } طالما (0)

#تعریف_کن PUT_پشت_STRING(str, شروع) \
	{ size_t i = طول_رشته( str );	\
	  طالما ( i > شروع )		\
	    unput((str)[--i]);		\
	}

#تعریف_کن CHECK_REJECT(str) \
	إذا ( all_فوقانی( str ) ) \
		reject = true;

#تعریف_کن CHECK_YYREJECT(str) \
	إذا ( all_پایینی( str ) ) \
		reject = true;

#تعریف_کن YY_USER_INIT \
	إذا ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#تعریف_کن شروع_CODEBLOCK(x) افعل { \
    /* Emit the needed line directive... */\
    إذا (indented_کد == false) { \
        إذا (!x) linenum++; \
        سطر_directive_بیرون(عدم, infilename, linenum);	\
    } \
    جمع_کن_action(M4QSTART); \
    yy_افزودن_state(CODEBLOCK); \
    إذا ((indented_کد = x)) ACTION_ECHO; \
} طالما(0)

#تعریف_کن انتها_CODEBLOCK افعل { \
    yy_برداشت_state();\
    جمع_کن_action(M4QEND); \
    إذا (!indented_کد) سطر_directive_بیرون(عدم, عدم, linenum);	\
} طالما (0)

%}

%option caseless nodefault noreject پشته noyy_بالاترین_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL رقم_2 QUOTE
%x FIRSTCCL CCL ACTION RECOVER COMMENT ACTION_STRING PERCENT_BRACE_ACTION
%x OPTION LINEDIR CODEBLOCK_تطابق_BRACE
%x گروه_WITH_PARAMS
%x گروه_MINUS_PARAMS
%x EXTENDED_COMMENT
%x COMMENT_DISCARD کد_COMMENT
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

اولی_CCL_CHAR	([^\\\n]|{ESCSEQ})
CCL_CHAR	([^\\\n\]]|{ESCSEQ})
CCL_عبارت	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
فراغ context_call(حرف *);
فراغ context_member(حرف *, ثابت حرف *);
#لغو_تعریف yyreject
%}
%%
	ساكن صحيح bracelevel, didadef, indented_کد;
	ساكن bool doing_قاعده_action = false;
	ساكن bool option_sense;

	ساكن bool doing_codeblock = false;
	صحيح brace_عمق=0, brace_شروع_سطر=0;
	حرف nmdef[MAXLINE];


<INITIAL>{
	^{WS}		شروع_CODEBLOCK(true);
	^"/*"		جمع_کن_action("/*[""["); yy_افزودن_state( COMMENT );
	^#{OPTWS}سطر{WS}	yy_افزودن_state( LINEDIR );
	^"%s"{NAME}?	أرجع SCDECL;
	^"%x"{NAME}?	أرجع XSCDECL;
	^"%{".*{NL}	شروع_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		حرف trampoline[512];
                brace_شروع_سطر = linenum;
                ++linenum;
		snprintf(trampoline, حجم(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                إذا (ctrl.gen_سطر_dirs)
                    buf_strappend(&بالاترین_buf, trampoline);
                brace_عمق = 1;
                yy_افزودن_state(CODEBLOCK_تطابق_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			سطر_directive_بیرون(عدم, infilename, linenum);
			BEGIN(SECT2PROLOG);
			أرجع SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); أرجع TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			إذا(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, حجم(nmstr) );
			 }
			وإلا
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


<COMMENT,کد_COMMENT>{ /* */
        [^\[\]\*\n]*  ACTION_ECHO;
        .           ACTION_ECHO;

	{NL}	    ++linenum; ACTION_ECHO;
}
<COMMENT>{
	"*/"	    جمع_کن_action("*/]""]"); yy_برداشت_state();
}
<کد_COMMENT>{
        "*/"        ACTION_ECHO; yy_برداشت_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_برداشت_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_برداشت_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_برداشت_state();
	[[:digit:]]+	linenum = myctoi( yytext );

	"\""[^""\n]*"\""	{
			حرر(infilename);
			infilename = xstrdup(yytext + 1);
			infilename[طول_رشته( infilename ) - 1] = '\0';
			}
	.		/* ignore spurious characters */
}
<ACTION,CODEBLOCK,ACTION_STRING,PERCENT_BRACE_ACTION,CHARACTER_CONSTANT,COMMENT,کد_COMMENT>{
   {M4QSTART}   ACTION_ECHO_QSTART;
   {M4QEND}     ACTION_ECHO_QEND;
}

<CODEBLOCK>{
	^"%}".*{NL}	++linenum; انتها_CODEBLOCK;
	[^\n%\[\]]*         ACTION_ECHO;
        .		ACTION_ECHO;
	{NL}		{
			++linenum;
			ACTION_ECHO;
			إذا ( indented_کد ) انتها_CODEBLOCK;
			}
}

<CODEBLOCK_تطابق_BRACE>{
    "}"     {
                إذا( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_برداشت_state();
                }وإلا
                    buf_strnappend(&بالاترین_buf, yytext, yyleng);
            }

    "{"     {
                brace_عمق++;
                buf_strnappend(&بالاترین_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&بالاترین_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&بالاترین_buf, escaped_qstart, (صحيح) طول_رشته(escaped_qstart));
    {M4QEND}    buf_strnappend(&بالاترین_buf, escaped_qend, (صحيح) طول_رشته(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&بالاترین_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_شروع_سطر;
                synerr(_("Unmatched '{'"));
                أرجع YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        إذا(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, حجم(nmdef) );
 		         }
 		        وإلا
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = طول_رشته( nmdef );
			    طالما (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			إذا ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		أرجع '=';
	[[:digit:]]+	{nmval = atoi(yytext); أرجع TOK_NUMERIC;}

	no		option_sense = ! option_sense;

	7بیت		ctrl.csize = option_sense ? 128 : 256;
	8بیت		ctrl.csize = option_sense ? 256 : 128;

	align		ctrl.long_align = option_sense;
	always-interactive	{
			ctrl.always_interactive = option_sense;
			ctrl.interactive = (trit)option_sense;
			}
	array		ctrl.yytext_is_array = option_sense;
	backup		env.backing_به_بالا_report = option_sense;
	batch		ctrl.interactive = (trit)!option_sense;
	bison-bridge     ctrl.bison_bridge_lval = option_sense;
	bison-locations  { إذا((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|حالة-sensitive		sf_مجموعه_case_ins(!option_sense);
	caseless|حالة-insensitive	sf_مجموعه_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	افتراضي		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	پر		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	درون_داد		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	سطر		ctrl.gen_سطر_dirs = option_sense;
	اصلی		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			إذا (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	اشاره_گر		ctrl.yytext_is_array = ! option_sense;
	اقرأ		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_استفاده_شده = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	پشته		ctrl.پشته_استفاده_شده = option_sense;
	stdinit		ctrl.do_stdinit = option_sense;
	stdout		env.use_stdout = option_sense;
	unistd		ctrl.no_unistd = ! option_sense;
	unput		ctrl.no_yyunput = ! option_sense;
	yyunput		ctrl.no_yyunput = ! option_sense;
	verbose		env.printstats = option_sense;
	warn		env.nowarn = ! option_sense;
	yylineno	ctrl.do_yylineno = option_sense;
	yymore		ctrl.yymore_really_استفاده_شده = option_sense;
	yywrap		ctrl.do_yywrap = option_sense;
	yyread		ctrl.noyyread = !option_sense;

	yypanic		ctrl.no_yypanic = !option_sense;

	yy_افزودن_state	ctrl.no_yy_افزودن_state = ! option_sense;
	yy_برداشت_state	ctrl.no_yy_برداشت_state = ! option_sense;
	yy_بالاترین_state	ctrl.no_yy_بالاترین_state = ! option_sense;

	yy_پیمایش_میانگیر	ctrl.no_yy_پیمایش_میانگیر = ! option_sense;
	yy_پیمایش_بایتها	ctrl.no_yy_پیمایش_بایتها = ! option_sense;
	yy_پیمایش_string	ctrl.no_yy_پیمایش_string = ! option_sense;

	yyalloc         ctrl.no_flex_alloc = ! option_sense;
	yyrealloc       ctrl.no_flex_realloc = ! option_sense;
	yyfree          ctrl.no_flex_free = ! option_sense;

	yyget_debug     ctrl.no_get_debug = ! option_sense;
	yyset_debug     ctrl.no_مجموعه_debug = ! option_sense;
	yyget_extra     ctrl.no_yyget_extra = ! option_sense;
	yyset_extra     ctrl.no_yyset_extra = ! option_sense;
	yyget_leng      ctrl.no_yyget_leng = ! option_sense;
	yyget_متن      ctrl.no_yyget_متن = ! option_sense;
	yyget_ستونی    ctrl.no_yyget_ستونی = ! option_sense;
	yyset_ستونی    ctrl.no_yyset_ستونی = ! option_sense;
	yyget_lineno    ctrl.no_yyget_lineno = ! option_sense;
	yyset_lineno    ctrl.no_yyset_lineno = ! option_sense;
	yyget_درون        ctrl.no_yyget_درون = ! option_sense;
	yyset_درون        ctrl.no_yyset_درون = ! option_sense;
	yyget_بیرون       ctrl.no_yyget_بیرون = ! option_sense;
	yyset_بیرون       ctrl.no_yyset_بیرون = ! option_sense;
	yyget_lval      ctrl.no_yyget_lval = ! option_sense;
	yyset_lval      ctrl.no_yyset_lval = ! option_sense;
	yyget_lloc      ctrl.no_yyget_lloc = ! option_sense;
	yyset_lloc      ctrl.no_yyset_lloc = ! option_sense;

	bufsize		أرجع TOK_BUFSIZE;
	emit		أرجع TOK_EMIT;
	extra-type	أرجع TOK_EXTRA_TYPE;
	outfile		أرجع TOK_OUTFILE;
	پیشوند		أرجع TOK_پیشوند;
	yyclass		أرجع TOK_YYCLASS;
	yylmax		أرجع TOK_YYLMAX;
	yydecl		أرجع TOK_YYDECL;
	yyterminate	أرجع TOK_YYTERMINATE;
	pre-action	أرجع TOK_PREACTION;
	post-action	أرجع TOK_POSTACTION;
	user-init	أرجع TOK_USERINIT;
	سرآیند(-file)?      أرجع TOK_سرآیند_FILE;
	tables-file         أرجع TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    إذا (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			إذا(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, حجم(nmstr) );
			 }
			وإلا
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[طول_رشته( nmstr ) - 1] = '\0';
			أرجع NAME;
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

	^{WS} شروع_CODEBLOCK(true); /* indented code in prolog */

	^{NOT_WS}.*	{
        /* non-indented code */
		إذا ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_مجموعه_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } وإلا {
            شروع_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			أرجع YY_NULL; /* to stop the parser */
			}
}

<SECT2>{
	^{OPTWS}{NL}	++linenum; /* allow blank lines in section 2 */

	^{OPTWS}"%{"	{
			indented_کد = false;
			doing_codeblock = true;
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);
			}

	^{OPTWS}"<"	    {
                        /* Allow "<" to appear in (?x) patterns. */
                        إذا (!sf_skip_ws())
                            BEGIN(SC);
                        أرجع '<';
                    }
	^{OPTWS}"^"	أرجع '^';
	"\""		BEGIN(QUOTE); أرجع '"';
	"{"/[[:digit:]]	{
			BEGIN(رقم_2);
			إذا ( ctrl.lex_compat || ctrl.posix_compat )
				أرجع BEGIN_REPEAT_POSIX;
			وإلا
				أرجع BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	أرجع '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			إذا ( درون_قاعده )
				{
				doing_قاعده_action = true;
				درون_قاعده = false;
				أرجع '\n';
				}
			}
	{WS}"|".*{NL}	{
                        إذا (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            صحيح amt = (صحيح) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        وإلا {
                            جمع_کن_action("]""]");
                            continued_action = true;
                            ++linenum;
                            أرجع '\n';
                        }
                    }

	^{WS}"/*"	{

                إذا (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_افزودن_state(COMMENT_DISCARD);
                }
                وإلا{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            إذا (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            وإلا{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                إذا ( درون_قاعده )
                    {
                    doing_قاعده_action = true;
                    درون_قاعده = false;
                    أرجع '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            إذا (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            وإلا{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                إذا ( درون_قاعده )
                    {
                    doing_قاعده_action = true;
                    درون_قاعده = false;
                    أرجع '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	أرجع EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({اولی_CCL_CHAR}|{CCL_عبارت})({CCL_CHAR}|{CCL_عبارت})*	{
			صحيح cclval;

			إذا(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, حجم(nmstr) );
			 }
			وإلا
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			إذا (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			وإلا
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
				أرجع '[';
				}
			}
    "{-}"       أرجع CCL_OP_DIFF;
    "{+}"       أرجع CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			حرف *nmdefptr;
            صحيح انتها_is_ws, انتها_ch;

            انتها_ch = yytext[yyleng-1];
            انتها_is_ws = انتها_ch != '}' ? 1 : 0;

 			إذا(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, حجم(nmstr) );
 			 }
 			وإلا
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - انتها_is_ws] = '\0';  /* chop trailing brace */

			إذا ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			وإلا
				{ /* push back name surrounded by ()'s */
				size_t len = طول_رشته( nmdefptr );
                إذا (انتها_is_ws)
                    unput(انتها_ch);

				إذا ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (انتها_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_پشت_STRING(nmdefptr, 0);

					إذا ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				وإلا
					{
					unput(')');
					PUT_پشت_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    إذا (sf_skip_ws())
                        yy_افزودن_state(COMMENT_DISCARD);
                    وإلا{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        أرجع '/';
                    }
                }

    "(?#"       {
                    إذا (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_افزودن(); 
                        أرجع '(';
                    }
                    وإلا
                        yy_افزودن_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_افزودن();
                    إذا (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    وإلا
                        BEGIN(گروه_WITH_PARAMS);
                    أرجع '(';
                }
    "("         sf_افزودن(); أرجع '(';
    ")"         {
                    إذا (sf_بالاترین_ix > 0) {
                        sf_برداشت();
                        أرجع ')';
                    } وإلا
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	أرجع (بیعلامت حرف) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		أرجع (بیعلامت حرف) yytext[0];
	">"		BEGIN(SECT2); أرجع '>';
	">"/^		BEGIN(CARETISBOL); أرجع '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); أرجع '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); أرجع '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			أرجع '"';
			}
}

<گروه_WITH_PARAMS>{
    ":"     BEGIN(SECT2);
    "-"     BEGIN(گروه_MINUS_PARAMS);
    i       sf_مجموعه_case_ins(1);
    s       sf_مجموعه_dot_all(1);
    x       sf_مجموعه_skip_ws(1);
}
<گروه_MINUS_PARAMS>{
    ":"     BEGIN(SECT2);
    i       sf_مجموعه_case_ins(0);
    s       sf_مجموعه_dot_all(0);
    x       sf_مجموعه_skip_ws(0);
}

<FIRSTCCL>{
	"^"/[^-\]\n]	BEGIN(CCL); أرجع '^';
	"^"/("-"|"]")	أرجع '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	أرجع '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); أرجع ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			أرجع ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); أرجع CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); أرجع CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); أرجع CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); أرجع CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); أرجع CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); أرجع CCE_گراف;
	"[:lower:]"	BEGIN(CCL); أرجع CCE_پایینی;
	"[:print:]"	BEGIN(CCL); أرجع CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); أرجع CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); أرجع CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); أرجع CCE_فوقانی;
	"[:xdigit:]"	BEGIN(CCL); أرجع CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); أرجع CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); أرجع CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); أرجع CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); أرجع CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); أرجع CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); أرجع CCE_NEG_گراف;
	"[:^lower:]"	BEGIN(CCL); أرجع CCE_NEG_پایینی;
	"[:^print:]"	BEGIN(CCL); أرجع CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); أرجع CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); أرجع CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); أرجع CCE_NEG_فوقانی;
	"[:^xdigit:]"	BEGIN(CCL); أرجع CCE_NEG_XDIGIT;
	{CCL_عبارت}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); أرجع CCE_ALNUM;
			}
}

<رقم_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			أرجع عدد;
			}

	","		أرجع ',';
	"}"		{
			BEGIN(SECT2);
			إذا ( ctrl.lex_compat || ctrl.posix_compat )
				أرجع انتها_REPEAT_POSIX;
			وإلا
				أرجع انتها_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			أرجع '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			أرجع '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_افزودن_state( کد_COMMENT );

	<CODEBLOCK,ACTION>{
		"reject" {
			ACTION_ECHO;
			CHECK_REJECT(yytext);
        }
		"yyreject"{OPTWS}"("{OPTWS}")" {
			جمع_کن_action("]""]M4_HOOK_REJECT[""[");
			CHECK_YYREJECT(yytext);
        }
		"yymore"{OPTWS}"("{OPTWS}")" {
			yymore_استفاده_شده = true;
			إذا (ctrl.rewrite)
				context_call(yytext);
			وإلا
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		إذا (bracelevel <= 0 || (doing_codeblock && indented_کد)) {
            إذا ( doing_قاعده_action )
                جمع_کن_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

            doing_قاعده_action = doing_codeblock = false;
            BEGIN(SECT2);
        }
    }
}


	/* yyreject and yymore() are checked for above, in PERCENT_BRACE_ACTION */
<ACTION>{
	"{"		ACTION_ECHO; ++bracelevel;
	"}"		ACTION_ECHO; --bracelevel;
	yyecho\(\)|yyinput\(\)|yystart\({FUNARGS}\)|yybegin\({FUNARGS}\)|yyunput\({FUNARGS}\)|yypanic\({FUNARGS}\)|yyatbol\(\)|yysetbol\({FUNARGS}\) {
			إذا (ctrl.rewrite)
				context_call(yytext);
			وإلا
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			جمع_کن_action("]""]");
			جمع_کن_action(yytext);
			جمع_کن_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			إذا (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			وإلا
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			إذا (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			وإلا
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
                إذا (bracelevel <= 0) {
                   إذا ( doing_قاعده_action )
                      جمع_کن_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

                   doing_قاعده_action = false;
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
	{NL}	++linenum; ACTION_ECHO; إذا (bracelevel <= 0) { BEGIN(SECT2); } وإلا { BEGIN(ACTION); }
        .	ACTION_ECHO;
}

<COMMENT,کد_COMMENT,COMMENT_DISCARD,ACTION,ACTION_STRING,CHARACTER_CONSTANT><<EOF>>	{
			synerr( _( "EOF encountered inside an action" ) );
			yyterminate();
			}

<EXTENDED_COMMENT,گروه_WITH_PARAMS,گروه_MINUS_PARAMS><<EOF>>	{
			synerr( _( "EOF encountered inside pattern" ) );
			yyterminate();
			}

<SECT2,QUOTE,FIRSTCCL,CCL>{ESCSEQ}	{
			yylval = myesc( (بیعلامت حرف *) yytext );

			إذا ( YY_شروع == FIRSTCCL )
				BEGIN(CCL);

			أرجع CHAR;
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
	إذا ( --num_input_files > 0 )
		{
		مجموعه_درون_داد_file( *++درون_داد_files );
		أرجع 0;
		}

	وإلا
		أرجع 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

فراغ مجموعه_درون_داد_file( حرف *file )
	{
	إذا ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		إذا ( yyin == عدم )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	وإلا
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

فراغ context_call(حرف *txt) {
	ثابت حرف *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	إذا (context_arg == عدم) {
		جمع_کن_action(txt);
	} وإلا {
		حرف buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		أكد(txt[طول_رشته(txt)-1] == ')');
		strncpy(buf, txt, حجم(buf));
		buf[طول_رشته(buf)-1] = '\0';	/* remove trailing ) */
		جمع_کن_action(buf);
		إذا (txt[طول_رشته(buf)-1] != '(') {
			جمع_کن_action(", ");
		}
		جمع_کن_action(context_arg);
		جمع_کن_action(")");
	}
}

فراغ context_member(حرف *txt, ثابت حرف *prop) {
	ثابت حرف *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	إذا (context_format == عدم) {
		جمع_کن_action(txt);
	} وإلا {
		حرف buf[128];
		snprintf(buf, حجم(buf), context_format, txt);
		جمع_کن_action(buf);
	}
}
