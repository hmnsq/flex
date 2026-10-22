/* scan.l - scanner for flex input -*-C-*- */

%top{
/* flexdef.h includes config.h, which may contain macros that alter the API */
/* of libc functions. Must include first before any libc header. */
#अन्तर्भाव "flexdef.h"
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

#अन्तर्भाव "parse.h"
बाह्य bool tablesverify, tablesext;
बाह्य bool trlcontxt; /* Set in parse.y for each rule. */
बाह्य ध्रुव वर्ण *escaped_qstart, *escaped_qend;

#define M4QSTART "[""["
#define M4QEND "]""]"

#define ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#define ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#define ACTION_ECHO add_action( yytext )
#define ACTION_ECHO_QSTART add_action (ESCAPED_QSTART)
#define ACTION_ECHO_QEND   add_action (ESCAPED_QEND)

#define MARK_END_OF_PROLOG mark_prolog();

#define YY_DECL \
	पूर्णाङ्क flexscan(शून्य)

#define RETURNCHAR \
	yylval = (unsigned वर्ण) yytext[0]; \
	पटिनिवत्त CHAR;

#define RETURNNAME \
	सचे(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, परिमाण(nmstr) ); \
	पटिनिवत्त NAME; \
	 } \
	अञ्ञथा \
	 करोहि { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } याव (0)

#define PUT_BACK_STRING(str, start) \
	{ size_t i = strlen( str );	\
	  याव ( i > start )		\
	    unput((str)[--i]);		\
	}

#define CHECK_REJECT(str) \
	सचे ( all_upper( str ) ) \
		reject = true;

#define CHECK_YYREJECT(str) \
	सचे ( all_lower( str ) ) \
		reject = true;

#define YY_USER_INIT \
	सचे ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#define START_CODEBLOCK(x) करोहि { \
    /* Emit the needed line directive... */\
    सचे (indented_code == false) { \
        सचे (!x) linenum++; \
        पङ्क्तिः_directive_out(रिक्त, infilename, linenum);	\
    } \
    add_action(M4QSTART); \
    yy_प्रक्षिप_state(CODEBLOCK); \
    सचे ((indented_code = x)) ACTION_ECHO; \
} याव(0)

#define END_CODEBLOCK करोहि { \
    yy_निष्कासय_state();\
    add_action(M4QEND); \
    सचे (!indented_code) पङ्क्तिः_directive_out(रिक्त, रिक्त, linenum);	\
} याव (0)

%}

%option caseless nodefault noreject राशिः noyy_शिखरम्_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL अङ्कः_2 QUOTE
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
CCL_व्यञ्जकम्	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
शून्य context_call(वर्ण *);
शून्य context_member(वर्ण *, ध्रुव वर्ण *);
#undef yyreject
%}
%%
	स्थिर पूर्णाङ्क bracelevel, didadef, indented_code;
	स्थिर bool doing_rule_action = false;
	स्थिर bool option_sense;

	स्थिर bool doing_codeblock = false;
	पूर्णाङ्क brace_depth=0, brace_start_पङ्क्तिः=0;
	वर्ण nmdef[MAXLINE];


<INITIAL>{
	^{WS}		START_CODEBLOCK(true);
	^"/*"		add_action("/*[""["); yy_प्रक्षिप_state( COMMENT );
	^#{OPTWS}पङ्क्तिः{WS}	yy_प्रक्षिप_state( LINEDIR );
	^"%s"{NAME}?	पटिनिवत्त SCDECL;
	^"%x"{NAME}?	पटिनिवत्त XSCDECL;
	^"%{".*{NL}	START_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		वर्ण trampoline[512];
                brace_start_पङ्क्तिः = linenum;
                ++linenum;
		snprintf(trampoline, परिमाण(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                सचे (ctrl.gen_पङ्क्तिः_dirs)
                    buf_strappend(&शिखरम्_buf, trampoline);
                brace_depth = 1;
                yy_प्रक्षिप_state(CODEBLOCK_MATCH_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			पङ्क्तिः_directive_out(रिक्त, infilename, linenum);
			BEGIN(SECT2PROLOG);
			पटिनिवत्त SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); पटिनिवत्त TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			सचे(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, परिमाण(nmstr) );
			 }
			अञ्ञथा
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
	"*/"	    add_action("*/]""]"); yy_निष्कासय_state();
}
<CODE_COMMENT>{
        "*/"        ACTION_ECHO; yy_निष्कासय_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_निष्कासय_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_निष्कासय_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_निष्कासय_state();
	[[:digit:]]+	linenum = myctoi( yytext );

	"\""[^""\n]*"\""	{
			मुक्त(infilename);
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
			सचे ( indented_code ) END_CODEBLOCK;
			}
}

<CODEBLOCK_MATCH_BRACE>{
    "}"     {
                सचे( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_निष्कासय_state();
                }अञ्ञथा
                    buf_strnappend(&शिखरम्_buf, yytext, yyleng);
            }

    "{"     {
                brace_depth++;
                buf_strnappend(&शिखरम्_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&शिखरम्_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&शिखरम्_buf, escaped_qstart, (पूर्णाङ्क) strlen(escaped_qstart));
    {M4QEND}    buf_strnappend(&शिखरम्_buf, escaped_qend, (पूर्णाङ्क) strlen(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&शिखरम्_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_start_पङ्क्तिः;
                synerr(_("Unmatched '{'"));
                पटिनिवत्त YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        सचे(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, परिमाण(nmdef) );
 		         }
 		        अञ्ञथा
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = strlen( nmdef );
			    याव (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			सचे ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		पटिनिवत्त '=';
	[[:digit:]]+	{nmval = atoi(yytext); पटिनिवत्त TOK_NUMERIC;}

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
	bison-locations  { सचे((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|पक्ष-sensitive		sf_set_case_ins(!option_sense);
	caseless|पक्ष-insensitive	sf_set_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	स्वभाव		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	full		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	निवेशः		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	पङ्क्तिः		ctrl.gen_पङ्क्तिः_dirs = option_sense;
	main		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			सचे (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	pointer		ctrl.yytext_is_array = ! option_sense;
	पठ		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_used = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	राशिः		ctrl.राशिः_used = option_sense;
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

	yy_प्रक्षिप_state	ctrl.no_yy_प्रक्षिप_state = ! option_sense;
	yy_निष्कासय_state	ctrl.no_yy_निष्कासय_state = ! option_sense;
	yy_शिखरम्_state	ctrl.no_yy_शिखरम्_state = ! option_sense;

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

	bufsize		पटिनिवत्त TOK_BUFSIZE;
	emit		पटिनिवत्त TOK_EMIT;
	extra-type	पटिनिवत्त TOK_EXTRA_TYPE;
	outfile		पटिनिवत्त TOK_OUTFILE;
	prefix		पटिनिवत्त TOK_PREFIX;
	yyclass		पटिनिवत्त TOK_YYCLASS;
	yylmax		पटिनिवत्त TOK_YYLMAX;
	yydecl		पटिनिवत्त TOK_YYDECL;
	yyterminate	पटिनिवत्त TOK_YYTERMINATE;
	pre-action	पटिनिवत्त TOK_PREACTION;
	post-action	पटिनिवत्त TOK_POSTACTION;
	user-init	पटिनिवत्त TOK_USERINIT;
	header(-file)?      पटिनिवत्त TOK_HEADER_FILE;
	tables-file         पटिनिवत्त TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    सचे (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			सचे(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, परिमाण(nmstr) );
			 }
			अञ्ञथा
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[strlen( nmstr ) - 1] = '\0';
			पटिनिवत्त NAME;
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
		सचे ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_set_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } अञ्ञथा {
            START_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			पटिनिवत्त YY_NULL; /* to stop the parser */
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
                        सचे (!sf_skip_ws())
                            BEGIN(SC);
                        पटिनिवत्त '<';
                    }
	^{OPTWS}"^"	पटिनिवत्त '^';
	"\""		BEGIN(QUOTE); पटिनिवत्त '"';
	"{"/[[:digit:]]	{
			BEGIN(अङ्कः_2);
			सचे ( ctrl.lex_compat || ctrl.posix_compat )
				पटिनिवत्त BEGIN_REPEAT_POSIX;
			अञ्ञथा
				पटिनिवत्त BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	पटिनिवत्त '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			सचे ( in_rule )
				{
				doing_rule_action = true;
				in_rule = false;
				पटिनिवत्त '\n';
				}
			}
	{WS}"|".*{NL}	{
                        सचे (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            पूर्णाङ्क amt = (पूर्णाङ्क) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        अञ्ञथा {
                            add_action("]""]");
                            continued_action = true;
                            ++linenum;
                            पटिनिवत्त '\n';
                        }
                    }

	^{WS}"/*"	{

                सचे (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_प्रक्षिप_state(COMMENT_DISCARD);
                }
                अञ्ञथा{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            सचे (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            अञ्ञथा{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                सचे ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    पटिनिवत्त '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            सचे (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            अञ्ञथा{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                सचे ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    पटिनिवत्त '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	पटिनिवत्त EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({FIRST_CCL_CHAR}|{CCL_व्यञ्जकम्})({CCL_CHAR}|{CCL_व्यञ्जकम्})*	{
			पूर्णाङ्क cclval;

			सचे(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, परिमाण(nmstr) );
			 }
			अञ्ञथा
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			सचे (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			अञ्ञथा
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
				पटिनिवत्त '[';
				}
			}
    "{-}"       पटिनिवत्त CCL_OP_DIFF;
    "{+}"       पटिनिवत्त CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			वर्ण *nmdefptr;
            पूर्णाङ्क end_is_ws, end_ch;

            end_ch = yytext[yyleng-1];
            end_is_ws = end_ch != '}' ? 1 : 0;

 			सचे(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, परिमाण(nmstr) );
 			 }
 			अञ्ञथा
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - end_is_ws] = '\0';  /* chop trailing brace */

			सचे ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			अञ्ञथा
				{ /* push back name surrounded by ()'s */
				size_t len = strlen( nmdefptr );
                सचे (end_is_ws)
                    unput(end_ch);

				सचे ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (end_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_BACK_STRING(nmdefptr, 0);

					सचे ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				अञ्ञथा
					{
					unput(')');
					PUT_BACK_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    सचे (sf_skip_ws())
                        yy_प्रक्षिप_state(COMMENT_DISCARD);
                    अञ्ञथा{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        पटिनिवत्त '/';
                    }
                }

    "(?#"       {
                    सचे (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_प्रक्षिप(); 
                        पटिनिवत्त '(';
                    }
                    अञ्ञथा
                        yy_प्रक्षिप_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_प्रक्षिप();
                    सचे (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    अञ्ञथा
                        BEGIN(GROUP_WITH_PARAMS);
                    पटिनिवत्त '(';
                }
    "("         sf_प्रक्षिप(); पटिनिवत्त '(';
    ")"         {
                    सचे (sf_शिखरम्_ix > 0) {
                        sf_निष्कासय();
                        पटिनिवत्त ')';
                    } अञ्ञथा
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	पटिनिवत्त (unsigned वर्ण) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		पटिनिवत्त (unsigned वर्ण) yytext[0];
	">"		BEGIN(SECT2); पटिनिवत्त '>';
	">"/^		BEGIN(CARETISBOL); पटिनिवत्त '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); पटिनिवत्त '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); पटिनिवत्त '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			पटिनिवत्त '"';
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
	"^"/[^-\]\n]	BEGIN(CCL); पटिनिवत्त '^';
	"^"/("-"|"]")	पटिनिवत्त '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	पटिनिवत्त '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); पटिनिवत्त ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			पटिनिवत्त ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); पटिनिवत्त CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); पटिनिवत्त CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); पटिनिवत्त CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); पटिनिवत्त CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); पटिनिवत्त CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); पटिनिवत्त CCE_GRAPH;
	"[:lower:]"	BEGIN(CCL); पटिनिवत्त CCE_LOWER;
	"[:print:]"	BEGIN(CCL); पटिनिवत्त CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); पटिनिवत्त CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); पटिनिवत्त CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); पटिनिवत्त CCE_UPPER;
	"[:xdigit:]"	BEGIN(CCL); पटिनिवत्त CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_GRAPH;
	"[:^lower:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_LOWER;
	"[:^print:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_UPPER;
	"[:^xdigit:]"	BEGIN(CCL); पटिनिवत्त CCE_NEG_XDIGIT;
	{CCL_व्यञ्जकम्}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); पटिनिवत्त CCE_ALNUM;
			}
}

<अङ्कः_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			पटिनिवत्त सङ्ख्या;
			}

	","		पटिनिवत्त ',';
	"}"		{
			BEGIN(SECT2);
			सचे ( ctrl.lex_compat || ctrl.posix_compat )
				पटिनिवत्त END_REPEAT_POSIX;
			अञ्ञथा
				पटिनिवत्त END_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			पटिनिवत्त '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			पटिनिवत्त '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_प्रक्षिप_state( CODE_COMMENT );

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
			सचे (ctrl.rewrite)
				context_call(yytext);
			अञ्ञथा
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		सचे (bracelevel <= 0 || (doing_codeblock && indented_code)) {
            सचे ( doing_rule_action )
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
			सचे (ctrl.rewrite)
				context_call(yytext);
			अञ्ञथा
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			add_action("]""]");
			add_action(yytext);
			add_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			सचे (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			अञ्ञथा
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			सचे (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			अञ्ञथा
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
                सचे (bracelevel <= 0) {
                   सचे ( doing_rule_action )
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
	{NL}	++linenum; ACTION_ECHO; सचे (bracelevel <= 0) { BEGIN(SECT2); } अञ्ञथा { BEGIN(ACTION); }
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
			yylval = myesc( (unsigned वर्ण *) yytext );

			सचे ( YY_START == FIRSTCCL )
				BEGIN(CCL);

			पटिनिवत्त CHAR;
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


पूर्णाङ्क yywrap(शून्य)
	{
	सचे ( --num_input_files > 0 )
		{
		set_निवेशः_file( *++निवेशः_files );
		पटिनिवत्त 0;
		}

	अञ्ञथा
		पटिनिवत्त 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

शून्य set_निवेशः_file( वर्ण *file )
	{
	सचे ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		सचे ( yyin == रिक्त )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	अञ्ञथा
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

शून्य context_call(वर्ण *txt) {
	ध्रुव वर्ण *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	सचे (context_arg == रिक्त) {
		add_action(txt);
	} अञ्ञथा {
		वर्ण buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		प्रतिज्ञा(txt[strlen(txt)-1] == ')');
		strncpy(buf, txt, परिमाण(buf));
		buf[strlen(buf)-1] = '\0';	/* remove trailing ) */
		add_action(buf);
		सचे (txt[strlen(buf)-1] != '(') {
			add_action(", ");
		}
		add_action(context_arg);
		add_action(")");
	}
}

शून्य context_member(वर्ण *txt, ध्रुव वर्ण *prop) {
	ध्रुव वर्ण *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	सचे (context_format == रिक्त) {
		add_action(txt);
	} अञ्ञथा {
		वर्ण buf[128];
		snprintf(buf, परिमाण(buf), context_format, txt);
		add_action(buf);
	}
}
