/* scan.l - scanner for flex input -*-C-*- */

%top{
/* flexdef.h includes config.h, which may contain macros that alter the API */
/* of libc functions. Must include first before any libc header. */
#شامل "flexdef.h"
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

#شامل "parse.h"
خارجی bool tablesverify, tablesext;
خارجی bool trlcontxt; /* Set in parse.y for each rule. */
خارجی ثابت حرف *escaped_qstart, *escaped_qend;

#تعریف_کرو M4QSTART "[""["
#تعریف_کرو M4QEND "]""]"

#تعریف_کرو ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#تعریف_کرو ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#تعریف_کرو ACTION_ECHO جوڑو_action( yytext )
#تعریف_کرو ACTION_ECHO_QSTART جوڑو_action (ESCAPED_QSTART)
#تعریف_کرو ACTION_ECHO_QEND   جوڑو_action (ESCAPED_QEND)

#تعریف_کرو MARK_انتہا_کا_PROLOG mark_prolog();

#تعریف_کرو YY_DECL \
	صحیح flexscan(خالی)

#تعریف_کرو RETURNCHAR \
	yylval = (غیرعلامتی حرف) yytext[0]; \
	واپس CHAR;

#تعریف_کرو RETURNNAME \
	اگر(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, حجم(nmstr) ); \
	واپس NAME; \
	 } \
	ورنہ \
	 کرو { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } جب (0)

#تعریف_کرو PUT_عقب_STRING(str, آغاز) \
	{ size_t i = لڑی_لمبائی( str );	\
	  جب ( i > آغاز )		\
	    unput((str)[--i]);		\
	}

#تعریف_کرو CHECK_REJECT(str) \
	اگر ( all_بالائی( str ) ) \
		reject = true;

#تعریف_کرو CHECK_YYREJECT(str) \
	اگر ( all_زیریں( str ) ) \
		reject = true;

#تعریف_کرو YY_USER_INIT \
	اگر ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#تعریف_کرو آغاز_CODEBLOCK(x) کرو { \
    /* Emit the needed line directive... */\
    اگر (indented_رمز == false) { \
        اگر (!x) linenum++; \
        سطر_directive_برآمد(تہی, infilename, linenum);	\
    } \
    جوڑو_action(M4QSTART); \
    yy_ڈالو_state(CODEBLOCK); \
    اگر ((indented_رمز = x)) ACTION_ECHO; \
} جب(0)

#تعریف_کرو انتہا_CODEBLOCK کرو { \
    yy_نکالو_state();\
    جوڑو_action(M4QEND); \
    اگر (!indented_رمز) سطر_directive_برآمد(تہی, تہی, linenum);	\
} جب (0)

%}

%option caseless nodefault noreject ڈھیر noyy_چوٹی_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL عدد_2 QUOTE
%x FIRSTCCL CCL ACTION RECOVER COMMENT ACTION_STRING PERCENT_BRACE_ACTION
%x OPTION LINEDIR CODEBLOCK_مطابقت_BRACE
%x گروہ_WITH_PARAMS
%x گروہ_MINUS_PARAMS
%x EXTENDED_COMMENT
%x COMMENT_DISCARD رمز_COMMENT
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

پہلا_CCL_CHAR	([^\\\n]|{ESCSEQ})
CCL_CHAR	([^\\\n\]]|{ESCSEQ})
CCL_اظہاریہ	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
خالی context_call(حرف *);
خالی context_member(حرف *, ثابت حرف *);
#تعریف_منسوخ yyreject
%}
%%
	ساکن صحیح bracelevel, didadef, indented_رمز;
	ساکن bool doing_قاعدہ_action = false;
	ساکن bool option_sense;

	ساکن bool doing_codeblock = false;
	صحیح brace_گہرائی=0, brace_آغاز_سطر=0;
	حرف nmdef[MAXLINE];


<INITIAL>{
	^{WS}		آغاز_CODEBLOCK(true);
	^"/*"		جوڑو_action("/*[""["); yy_ڈالو_state( COMMENT );
	^#{OPTWS}سطر{WS}	yy_ڈالو_state( LINEDIR );
	^"%s"{NAME}?	واپس SCDECL;
	^"%x"{NAME}?	واپس XSCDECL;
	^"%{".*{NL}	آغاز_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		حرف trampoline[512];
                brace_آغاز_سطر = linenum;
                ++linenum;
		snprintf(trampoline, حجم(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                اگر (ctrl.gen_سطر_dirs)
                    buf_strappend(&چوٹی_buf, trampoline);
                brace_گہرائی = 1;
                yy_ڈالو_state(CODEBLOCK_مطابقت_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			سطر_directive_برآمد(تہی, infilename, linenum);
			BEGIN(SECT2PROLOG);
			واپس SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); واپس TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			اگر(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, حجم(nmstr) );
			 }
			ورنہ
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


<COMMENT,رمز_COMMENT>{ /* */
        [^\[\]\*\n]*  ACTION_ECHO;
        .           ACTION_ECHO;

	{NL}	    ++linenum; ACTION_ECHO;
}
<COMMENT>{
	"*/"	    جوڑو_action("*/]""]"); yy_نکالو_state();
}
<رمز_COMMENT>{
        "*/"        ACTION_ECHO; yy_نکالو_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_نکالو_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_نکالو_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_نکالو_state();
	[[:digit:]]+	linenum = myctoi( yytext );

	"\""[^""\n]*"\""	{
			آزاد(infilename);
			infilename = xstrdup(yytext + 1);
			infilename[لڑی_لمبائی( infilename ) - 1] = '\0';
			}
	.		/* ignore spurious characters */
}
<ACTION,CODEBLOCK,ACTION_STRING,PERCENT_BRACE_ACTION,CHARACTER_CONSTANT,COMMENT,رمز_COMMENT>{
   {M4QSTART}   ACTION_ECHO_QSTART;
   {M4QEND}     ACTION_ECHO_QEND;
}

<CODEBLOCK>{
	^"%}".*{NL}	++linenum; انتہا_CODEBLOCK;
	[^\n%\[\]]*         ACTION_ECHO;
        .		ACTION_ECHO;
	{NL}		{
			++linenum;
			ACTION_ECHO;
			اگر ( indented_رمز ) انتہا_CODEBLOCK;
			}
}

<CODEBLOCK_مطابقت_BRACE>{
    "}"     {
                اگر( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_نکالو_state();
                }ورنہ
                    buf_strnappend(&چوٹی_buf, yytext, yyleng);
            }

    "{"     {
                brace_گہرائی++;
                buf_strnappend(&چوٹی_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&چوٹی_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&چوٹی_buf, escaped_qstart, (صحیح) لڑی_لمبائی(escaped_qstart));
    {M4QEND}    buf_strnappend(&چوٹی_buf, escaped_qend, (صحیح) لڑی_لمبائی(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&چوٹی_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_آغاز_سطر;
                synerr(_("Unmatched '{'"));
                واپس YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        اگر(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, حجم(nmdef) );
 		         }
 		        ورنہ
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = لڑی_لمبائی( nmdef );
			    جب (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			اگر ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		واپس '=';
	[[:digit:]]+	{nmval = atoi(yytext); واپس TOK_NUMERIC;}

	no		option_sense = ! option_sense;

	7ثنائی_ہندسہ		ctrl.csize = option_sense ? 128 : 256;
	8ثنائی_ہندسہ		ctrl.csize = option_sense ? 256 : 128;

	align		ctrl.long_align = option_sense;
	always-interactive	{
			ctrl.always_interactive = option_sense;
			ctrl.interactive = (trit)option_sense;
			}
	array		ctrl.yytext_is_array = option_sense;
	backup		env.backing_اوپر_report = option_sense;
	batch		ctrl.interactive = (trit)!option_sense;
	bison-bridge     ctrl.bison_bridge_lval = option_sense;
	bison-locations  { اگر((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|حالت-sensitive		sf_سیٹ_case_ins(!option_sense);
	caseless|حالت-insensitive	sf_سیٹ_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	طےشدہ		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	بھرا		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	داخلہ		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	سطر		ctrl.gen_سطر_dirs = option_sense;
	مین		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			اگر (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	اشارہ_گر		ctrl.yytext_is_array = ! option_sense;
	اقرأ		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_مستعمل = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	ڈھیر		ctrl.ڈھیر_مستعمل = option_sense;
	stdinit		ctrl.do_stdinit = option_sense;
	stdout		env.use_stdout = option_sense;
	unistd		ctrl.no_unistd = ! option_sense;
	unput		ctrl.no_yyunput = ! option_sense;
	yyunput		ctrl.no_yyunput = ! option_sense;
	verbose		env.printstats = option_sense;
	warn		env.nowarn = ! option_sense;
	yylineno	ctrl.do_yylineno = option_sense;
	yymore		ctrl.yymore_really_مستعمل = option_sense;
	yywrap		ctrl.do_yywrap = option_sense;
	yyread		ctrl.noyyread = !option_sense;

	yypanic		ctrl.no_yypanic = !option_sense;

	yy_ڈالو_state	ctrl.no_yy_ڈالو_state = ! option_sense;
	yy_نکالو_state	ctrl.no_yy_نکالو_state = ! option_sense;
	yy_چوٹی_state	ctrl.no_yy_چوٹی_state = ! option_sense;

	yy_جائزہ_بفر	ctrl.no_yy_جائزہ_بفر = ! option_sense;
	yy_جائزہ_بائٹیں	ctrl.no_yy_جائزہ_بائٹیں = ! option_sense;
	yy_جائزہ_string	ctrl.no_yy_جائزہ_string = ! option_sense;

	yyalloc         ctrl.no_flex_alloc = ! option_sense;
	yyrealloc       ctrl.no_flex_realloc = ! option_sense;
	yyfree          ctrl.no_flex_free = ! option_sense;

	yyget_debug     ctrl.no_get_debug = ! option_sense;
	yyset_debug     ctrl.no_سیٹ_debug = ! option_sense;
	yyget_extra     ctrl.no_yyget_extra = ! option_sense;
	yyset_extra     ctrl.no_yyset_extra = ! option_sense;
	yyget_leng      ctrl.no_yyget_leng = ! option_sense;
	yyget_متن      ctrl.no_yyget_متن = ! option_sense;
	yyget_عمود    ctrl.no_yyget_عمود = ! option_sense;
	yyset_عمود    ctrl.no_yyset_عمود = ! option_sense;
	yyget_lineno    ctrl.no_yyget_lineno = ! option_sense;
	yyset_lineno    ctrl.no_yyset_lineno = ! option_sense;
	yyget_اندر        ctrl.no_yyget_اندر = ! option_sense;
	yyset_اندر        ctrl.no_yyset_اندر = ! option_sense;
	yyget_برآمد       ctrl.no_yyget_برآمد = ! option_sense;
	yyset_برآمد       ctrl.no_yyset_برآمد = ! option_sense;
	yyget_lval      ctrl.no_yyget_lval = ! option_sense;
	yyset_lval      ctrl.no_yyset_lval = ! option_sense;
	yyget_lloc      ctrl.no_yyget_lloc = ! option_sense;
	yyset_lloc      ctrl.no_yyset_lloc = ! option_sense;

	bufsize		واپس TOK_BUFSIZE;
	emit		واپس TOK_EMIT;
	extra-type	واپس TOK_EXTRA_TYPE;
	outfile		واپس TOK_OUTFILE;
	سابقہ		واپس TOK_سابقہ;
	yyclass		واپس TOK_YYCLASS;
	yylmax		واپس TOK_YYLMAX;
	yydecl		واپس TOK_YYDECL;
	yyterminate	واپس TOK_YYTERMINATE;
	pre-action	واپس TOK_PREACTION;
	post-action	واپس TOK_POSTACTION;
	user-init	واپس TOK_USERINIT;
	سرخی(-file)?      واپس TOK_سرخی_FILE;
	tables-file         واپس TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    اگر (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			اگر(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, حجم(nmstr) );
			 }
			ورنہ
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[لڑی_لمبائی( nmstr ) - 1] = '\0';
			واپس NAME;
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

	^{WS} آغاز_CODEBLOCK(true); /* indented code in prolog */

	^{NOT_WS}.*	{
        /* non-indented code */
		اگر ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_سیٹ_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } ورنہ {
            آغاز_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			واپس YY_NULL; /* to stop the parser */
			}
}

<SECT2>{
	^{OPTWS}{NL}	++linenum; /* allow blank lines in section 2 */

	^{OPTWS}"%{"	{
			indented_رمز = false;
			doing_codeblock = true;
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);
			}

	^{OPTWS}"<"	    {
                        /* Allow "<" to appear in (?x) patterns. */
                        اگر (!sf_skip_ws())
                            BEGIN(SC);
                        واپس '<';
                    }
	^{OPTWS}"^"	واپس '^';
	"\""		BEGIN(QUOTE); واپس '"';
	"{"/[[:digit:]]	{
			BEGIN(عدد_2);
			اگر ( ctrl.lex_compat || ctrl.posix_compat )
				واپس BEGIN_REPEAT_POSIX;
			ورنہ
				واپس BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	واپس '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			اگر ( اندر_قاعدہ )
				{
				doing_قاعدہ_action = true;
				اندر_قاعدہ = false;
				واپس '\n';
				}
			}
	{WS}"|".*{NL}	{
                        اگر (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            صحیح amt = (صحیح) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        ورنہ {
                            جوڑو_action("]""]");
                            continued_action = true;
                            ++linenum;
                            واپس '\n';
                        }
                    }

	^{WS}"/*"	{

                اگر (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_ڈالو_state(COMMENT_DISCARD);
                }
                ورنہ{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            اگر (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            ورنہ{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                اگر ( اندر_قاعدہ )
                    {
                    doing_قاعدہ_action = true;
                    اندر_قاعدہ = false;
                    واپس '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            اگر (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            ورنہ{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                اگر ( اندر_قاعدہ )
                    {
                    doing_قاعدہ_action = true;
                    اندر_قاعدہ = false;
                    واپس '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	واپس EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({پہلا_CCL_CHAR}|{CCL_اظہاریہ})({CCL_CHAR}|{CCL_اظہاریہ})*	{
			صحیح cclval;

			اگر(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, حجم(nmstr) );
			 }
			ورنہ
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			اگر (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			ورنہ
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
				واپس '[';
				}
			}
    "{-}"       واپس CCL_OP_DIFF;
    "{+}"       واپس CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			حرف *nmdefptr;
            صحیح انتہا_is_ws, انتہا_ch;

            انتہا_ch = yytext[yyleng-1];
            انتہا_is_ws = انتہا_ch != '}' ? 1 : 0;

 			اگر(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, حجم(nmstr) );
 			 }
 			ورنہ
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - انتہا_is_ws] = '\0';  /* chop trailing brace */

			اگر ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			ورنہ
				{ /* push back name surrounded by ()'s */
				size_t len = لڑی_لمبائی( nmdefptr );
                اگر (انتہا_is_ws)
                    unput(انتہا_ch);

				اگر ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (انتہا_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_عقب_STRING(nmdefptr, 0);

					اگر ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				ورنہ
					{
					unput(')');
					PUT_عقب_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    اگر (sf_skip_ws())
                        yy_ڈالو_state(COMMENT_DISCARD);
                    ورنہ{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        واپس '/';
                    }
                }

    "(?#"       {
                    اگر (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_ڈالو(); 
                        واپس '(';
                    }
                    ورنہ
                        yy_ڈالو_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_ڈالو();
                    اگر (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    ورنہ
                        BEGIN(گروہ_WITH_PARAMS);
                    واپس '(';
                }
    "("         sf_ڈالو(); واپس '(';
    ")"         {
                    اگر (sf_چوٹی_ix > 0) {
                        sf_نکالو();
                        واپس ')';
                    } ورنہ
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	واپس (غیرعلامتی حرف) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		واپس (غیرعلامتی حرف) yytext[0];
	">"		BEGIN(SECT2); واپس '>';
	">"/^		BEGIN(CARETISBOL); واپس '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); واپس '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); واپس '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			واپس '"';
			}
}

<گروہ_WITH_PARAMS>{
    ":"     BEGIN(SECT2);
    "-"     BEGIN(گروہ_MINUS_PARAMS);
    i       sf_سیٹ_case_ins(1);
    s       sf_سیٹ_dot_all(1);
    x       sf_سیٹ_skip_ws(1);
}
<گروہ_MINUS_PARAMS>{
    ":"     BEGIN(SECT2);
    i       sf_سیٹ_case_ins(0);
    s       sf_سیٹ_dot_all(0);
    x       sf_سیٹ_skip_ws(0);
}

<FIRSTCCL>{
	"^"/[^-\]\n]	BEGIN(CCL); واپس '^';
	"^"/("-"|"]")	واپس '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	واپس '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); واپس ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			واپس ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); واپس CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); واپس CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); واپس CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); واپس CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); واپس CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); واپس CCE_گراف;
	"[:lower:]"	BEGIN(CCL); واپس CCE_زیریں;
	"[:print:]"	BEGIN(CCL); واپس CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); واپس CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); واپس CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); واپس CCE_بالائی;
	"[:xdigit:]"	BEGIN(CCL); واپس CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); واپس CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); واپس CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); واپس CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); واپس CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); واپس CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); واپس CCE_NEG_گراف;
	"[:^lower:]"	BEGIN(CCL); واپس CCE_NEG_زیریں;
	"[:^print:]"	BEGIN(CCL); واپس CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); واپس CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); واپس CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); واپس CCE_NEG_بالائی;
	"[:^xdigit:]"	BEGIN(CCL); واپس CCE_NEG_XDIGIT;
	{CCL_اظہاریہ}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); واپس CCE_ALNUM;
			}
}

<عدد_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			واپس نمبر;
			}

	","		واپس ',';
	"}"		{
			BEGIN(SECT2);
			اگر ( ctrl.lex_compat || ctrl.posix_compat )
				واپس انتہا_REPEAT_POSIX;
			ورنہ
				واپس انتہا_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			واپس '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			واپس '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_ڈالو_state( رمز_COMMENT );

	<CODEBLOCK,ACTION>{
		"reject" {
			ACTION_ECHO;
			CHECK_REJECT(yytext);
        }
		"yyreject"{OPTWS}"("{OPTWS}")" {
			جوڑو_action("]""]M4_HOOK_REJECT[""[");
			CHECK_YYREJECT(yytext);
        }
		"yymore"{OPTWS}"("{OPTWS}")" {
			yymore_مستعمل = true;
			اگر (ctrl.rewrite)
				context_call(yytext);
			ورنہ
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		اگر (bracelevel <= 0 || (doing_codeblock && indented_رمز)) {
            اگر ( doing_قاعدہ_action )
                جوڑو_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

            doing_قاعدہ_action = doing_codeblock = false;
            BEGIN(SECT2);
        }
    }
}


	/* yyreject and yymore() are checked for above, in PERCENT_BRACE_ACTION */
<ACTION>{
	"{"		ACTION_ECHO; ++bracelevel;
	"}"		ACTION_ECHO; --bracelevel;
	yyecho\(\)|yyinput\(\)|yystart\({FUNARGS}\)|yybegin\({FUNARGS}\)|yyunput\({FUNARGS}\)|yypanic\({FUNARGS}\)|yyatbol\(\)|yysetbol\({FUNARGS}\) {
			اگر (ctrl.rewrite)
				context_call(yytext);
			ورنہ
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			جوڑو_action("]""]");
			جوڑو_action(yytext);
			جوڑو_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			اگر (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			ورنہ
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			اگر (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			ورنہ
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
                اگر (bracelevel <= 0) {
                   اگر ( doing_قاعدہ_action )
                      جوڑو_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

                   doing_قاعدہ_action = false;
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
	{NL}	++linenum; ACTION_ECHO; اگر (bracelevel <= 0) { BEGIN(SECT2); } ورنہ { BEGIN(ACTION); }
        .	ACTION_ECHO;
}

<COMMENT,رمز_COMMENT,COMMENT_DISCARD,ACTION,ACTION_STRING,CHARACTER_CONSTANT><<EOF>>	{
			synerr( _( "EOF encountered inside an action" ) );
			yyterminate();
			}

<EXTENDED_COMMENT,گروہ_WITH_PARAMS,گروہ_MINUS_PARAMS><<EOF>>	{
			synerr( _( "EOF encountered inside pattern" ) );
			yyterminate();
			}

<SECT2,QUOTE,FIRSTCCL,CCL>{ESCSEQ}	{
			yylval = myesc( (غیرعلامتی حرف *) yytext );

			اگر ( YY_آغاز == FIRSTCCL )
				BEGIN(CCL);

			واپس CHAR;
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


صحیح yywrap(خالی)
	{
	اگر ( --num_input_files > 0 )
		{
		سیٹ_داخلہ_file( *++داخلہ_files );
		واپس 0;
		}

	ورنہ
		واپس 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

خالی سیٹ_داخلہ_file( حرف *file )
	{
	اگر ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		اگر ( yyin == تہی )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	ورنہ
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

خالی context_call(حرف *txt) {
	ثابت حرف *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	اگر (context_arg == تہی) {
		جوڑو_action(txt);
	} ورنہ {
		حرف buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		أكد(txt[لڑی_لمبائی(txt)-1] == ')');
		strncpy(buf, txt, حجم(buf));
		buf[لڑی_لمبائی(buf)-1] = '\0';	/* remove trailing ) */
		جوڑو_action(buf);
		اگر (txt[لڑی_لمبائی(buf)-1] != '(') {
			جوڑو_action(", ");
		}
		جوڑو_action(context_arg);
		جوڑو_action(")");
	}
}

خالی context_member(حرف *txt, ثابت حرف *prop) {
	ثابت حرف *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	اگر (context_format == تہی) {
		جوڑو_action(txt);
	} ورنہ {
		حرف buf[128];
		snprintf(buf, حجم(buf), context_format, txt);
		جوڑو_action(buf);
	}
}
