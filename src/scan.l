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
	प्रत्यागम CHAR;

#define RETURNNAME \
	यदि(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, परिमाण(nmstr) ); \
	प्रत्यागम NAME; \
	 } \
	अन्यथा \
	 कुरु { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } यावत् (0)

#define PUT_BACK_STRING(str, start) \
	{ size_t i = strlen( str );	\
	  यावत् ( i > start )		\
	    unput((str)[--i]);		\
	}

#define CHECK_REJECT(str) \
	यदि ( all_upper( str ) ) \
		reject = true;

#define CHECK_YYREJECT(str) \
	यदि ( all_lower( str ) ) \
		reject = true;

#define YY_USER_INIT \
	यदि ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#define START_CODEBLOCK(x) कुरु { \
    /* Emit the needed line directive... */\
    यदि (indented_code == false) { \
        यदि (!x) linenum++; \
        पंक्ति_directive_out(रिक्त, infilename, linenum);	\
    } \
    add_action(M4QSTART); \
    yy_धकेलो_state(CODEBLOCK); \
    यदि ((indented_code = x)) ACTION_ECHO; \
} यावत्(0)

#define END_CODEBLOCK कुरु { \
    yy_निकालो_state();\
    add_action(M4QEND); \
    यदि (!indented_code) पंक्ति_directive_out(रिक्त, रिक्त, linenum);	\
} यावत् (0)

%}

%option caseless nodefault noreject ढेर noyy_शीर्ष_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL अंक_2 QUOTE
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
CCL_व्यंजक	("[:"^?[[:alpha:]]+":]")

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
	पूर्णाङ्क brace_depth=0, brace_start_पंक्ति=0;
	वर्ण nmdef[MAXLINE];


<INITIAL>{
	^{WS}		START_CODEBLOCK(true);
	^"/*"		add_action("/*[""["); yy_धकेलो_state( COMMENT );
	^#{OPTWS}पंक्ति{WS}	yy_धकेलो_state( LINEDIR );
	^"%s"{NAME}?	प्रत्यागम SCDECL;
	^"%x"{NAME}?	प्रत्यागम XSCDECL;
	^"%{".*{NL}	START_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		वर्ण trampoline[512];
                brace_start_पंक्ति = linenum;
                ++linenum;
		snprintf(trampoline, परिमाण(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                यदि (ctrl.gen_पंक्ति_dirs)
                    buf_strappend(&शीर्ष_buf, trampoline);
                brace_depth = 1;
                yy_धकेलो_state(CODEBLOCK_MATCH_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			पंक्ति_directive_out(रिक्त, infilename, linenum);
			BEGIN(SECT2PROLOG);
			प्रत्यागम SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); प्रत्यागम TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			यदि(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, परिमाण(nmstr) );
			 }
			अन्यथा
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
	"*/"	    add_action("*/]""]"); yy_निकालो_state();
}
<CODE_COMMENT>{
        "*/"        ACTION_ECHO; yy_निकालो_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_निकालो_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_निकालो_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_निकालो_state();
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
			यदि ( indented_code ) END_CODEBLOCK;
			}
}

<CODEBLOCK_MATCH_BRACE>{
    "}"     {
                यदि( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_निकालो_state();
                }अन्यथा
                    buf_strnappend(&शीर्ष_buf, yytext, yyleng);
            }

    "{"     {
                brace_depth++;
                buf_strnappend(&शीर्ष_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&शीर्ष_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&शीर्ष_buf, escaped_qstart, (पूर्णाङ्क) strlen(escaped_qstart));
    {M4QEND}    buf_strnappend(&शीर्ष_buf, escaped_qend, (पूर्णाङ्क) strlen(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&शीर्ष_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_start_पंक्ति;
                synerr(_("Unmatched '{'"));
                प्रत्यागम YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        यदि(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, परिमाण(nmdef) );
 		         }
 		        अन्यथा
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = strlen( nmdef );
			    यावत् (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			यदि ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		प्रत्यागम '=';
	[[:digit:]]+	{nmval = atoi(yytext); प्रत्यागम TOK_NUMERIC;}

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
	bison-locations  { यदि((ctrl.bison_bridge_lloc = option_sense))
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
	निवेश		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	पंक्ति		ctrl.gen_पंक्ति_dirs = option_sense;
	main		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			यदि (option_sense)
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
	ढेर		ctrl.ढेर_used = option_sense;
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

	yy_धकेलो_state	ctrl.no_yy_धकेलो_state = ! option_sense;
	yy_निकालो_state	ctrl.no_yy_निकालो_state = ! option_sense;
	yy_शीर्ष_state	ctrl.no_yy_शीर्ष_state = ! option_sense;

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

	bufsize		प्रत्यागम TOK_BUFSIZE;
	emit		प्रत्यागम TOK_EMIT;
	extra-type	प्रत्यागम TOK_EXTRA_TYPE;
	outfile		प्रत्यागम TOK_OUTFILE;
	prefix		प्रत्यागम TOK_PREFIX;
	yyclass		प्रत्यागम TOK_YYCLASS;
	yylmax		प्रत्यागम TOK_YYLMAX;
	yydecl		प्रत्यागम TOK_YYDECL;
	yyterminate	प्रत्यागम TOK_YYTERMINATE;
	pre-action	प्रत्यागम TOK_PREACTION;
	post-action	प्रत्यागम TOK_POSTACTION;
	user-init	प्रत्यागम TOK_USERINIT;
	header(-file)?      प्रत्यागम TOK_HEADER_FILE;
	tables-file         प्रत्यागम TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    यदि (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			यदि(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, परिमाण(nmstr) );
			 }
			अन्यथा
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[strlen( nmstr ) - 1] = '\0';
			प्रत्यागम NAME;
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
		यदि ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_set_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } अन्यथा {
            START_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			प्रत्यागम YY_NULL; /* to stop the parser */
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
                        यदि (!sf_skip_ws())
                            BEGIN(SC);
                        प्रत्यागम '<';
                    }
	^{OPTWS}"^"	प्रत्यागम '^';
	"\""		BEGIN(QUOTE); प्रत्यागम '"';
	"{"/[[:digit:]]	{
			BEGIN(अंक_2);
			यदि ( ctrl.lex_compat || ctrl.posix_compat )
				प्रत्यागम BEGIN_REPEAT_POSIX;
			अन्यथा
				प्रत्यागम BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	प्रत्यागम '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			यदि ( in_rule )
				{
				doing_rule_action = true;
				in_rule = false;
				प्रत्यागम '\n';
				}
			}
	{WS}"|".*{NL}	{
                        यदि (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            पूर्णाङ्क amt = (पूर्णाङ्क) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        अन्यथा {
                            add_action("]""]");
                            continued_action = true;
                            ++linenum;
                            प्रत्यागम '\n';
                        }
                    }

	^{WS}"/*"	{

                यदि (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_धकेलो_state(COMMENT_DISCARD);
                }
                अन्यथा{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            यदि (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            अन्यथा{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                यदि ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    प्रत्यागम '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            यदि (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            अन्यथा{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                यदि ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    प्रत्यागम '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	प्रत्यागम EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({FIRST_CCL_CHAR}|{CCL_व्यंजक})({CCL_CHAR}|{CCL_व्यंजक})*	{
			पूर्णाङ्क cclval;

			यदि(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, परिमाण(nmstr) );
			 }
			अन्यथा
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			यदि (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			अन्यथा
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
				प्रत्यागम '[';
				}
			}
    "{-}"       प्रत्यागम CCL_OP_DIFF;
    "{+}"       प्रत्यागम CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			वर्ण *nmdefptr;
            पूर्णाङ्क end_is_ws, end_ch;

            end_ch = yytext[yyleng-1];
            end_is_ws = end_ch != '}' ? 1 : 0;

 			यदि(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, परिमाण(nmstr) );
 			 }
 			अन्यथा
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - end_is_ws] = '\0';  /* chop trailing brace */

			यदि ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			अन्यथा
				{ /* push back name surrounded by ()'s */
				size_t len = strlen( nmdefptr );
                यदि (end_is_ws)
                    unput(end_ch);

				यदि ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (end_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_BACK_STRING(nmdefptr, 0);

					यदि ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				अन्यथा
					{
					unput(')');
					PUT_BACK_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    यदि (sf_skip_ws())
                        yy_धकेलो_state(COMMENT_DISCARD);
                    अन्यथा{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        प्रत्यागम '/';
                    }
                }

    "(?#"       {
                    यदि (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_धकेलो(); 
                        प्रत्यागम '(';
                    }
                    अन्यथा
                        yy_धकेलो_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_धकेलो();
                    यदि (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    अन्यथा
                        BEGIN(GROUP_WITH_PARAMS);
                    प्रत्यागम '(';
                }
    "("         sf_धकेलो(); प्रत्यागम '(';
    ")"         {
                    यदि (sf_शीर्ष_ix > 0) {
                        sf_निकालो();
                        प्रत्यागम ')';
                    } अन्यथा
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	प्रत्यागम (unsigned वर्ण) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		प्रत्यागम (unsigned वर्ण) yytext[0];
	">"		BEGIN(SECT2); प्रत्यागम '>';
	">"/^		BEGIN(CARETISBOL); प्रत्यागम '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); प्रत्यागम '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); प्रत्यागम '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			प्रत्यागम '"';
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
	"^"/[^-\]\n]	BEGIN(CCL); प्रत्यागम '^';
	"^"/("-"|"]")	प्रत्यागम '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	प्रत्यागम '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); प्रत्यागम ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			प्रत्यागम ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); प्रत्यागम CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); प्रत्यागम CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); प्रत्यागम CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); प्रत्यागम CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); प्रत्यागम CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); प्रत्यागम CCE_GRAPH;
	"[:lower:]"	BEGIN(CCL); प्रत्यागम CCE_LOWER;
	"[:print:]"	BEGIN(CCL); प्रत्यागम CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); प्रत्यागम CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); प्रत्यागम CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); प्रत्यागम CCE_UPPER;
	"[:xdigit:]"	BEGIN(CCL); प्रत्यागम CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_GRAPH;
	"[:^lower:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_LOWER;
	"[:^print:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_UPPER;
	"[:^xdigit:]"	BEGIN(CCL); प्रत्यागम CCE_NEG_XDIGIT;
	{CCL_व्यंजक}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); प्रत्यागम CCE_ALNUM;
			}
}

<अंक_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			प्रत्यागम संख्या;
			}

	","		प्रत्यागम ',';
	"}"		{
			BEGIN(SECT2);
			यदि ( ctrl.lex_compat || ctrl.posix_compat )
				प्रत्यागम END_REPEAT_POSIX;
			अन्यथा
				प्रत्यागम END_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			प्रत्यागम '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			प्रत्यागम '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_धकेलो_state( CODE_COMMENT );

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
			यदि (ctrl.rewrite)
				context_call(yytext);
			अन्यथा
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		यदि (bracelevel <= 0 || (doing_codeblock && indented_code)) {
            यदि ( doing_rule_action )
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
			यदि (ctrl.rewrite)
				context_call(yytext);
			अन्यथा
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			add_action("]""]");
			add_action(yytext);
			add_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			यदि (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			अन्यथा
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			यदि (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			अन्यथा
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
                यदि (bracelevel <= 0) {
                   यदि ( doing_rule_action )
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
	{NL}	++linenum; ACTION_ECHO; यदि (bracelevel <= 0) { BEGIN(SECT2); } अन्यथा { BEGIN(ACTION); }
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

			यदि ( YY_START == FIRSTCCL )
				BEGIN(CCL);

			प्रत्यागम CHAR;
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
	यदि ( --num_input_files > 0 )
		{
		set_निवेश_file( *++निवेश_files );
		प्रत्यागम 0;
		}

	अन्यथा
		प्रत्यागम 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

शून्य set_निवेश_file( वर्ण *file )
	{
	यदि ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		यदि ( yyin == रिक्त )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	अन्यथा
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

शून्य context_call(वर्ण *txt) {
	ध्रुव वर्ण *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	यदि (context_arg == रिक्त) {
		add_action(txt);
	} अन्यथा {
		वर्ण buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		प्रतिज्ञा(txt[strlen(txt)-1] == ')');
		strncpy(buf, txt, परिमाण(buf));
		buf[strlen(buf)-1] = '\0';	/* remove trailing ) */
		add_action(buf);
		यदि (txt[strlen(buf)-1] != '(') {
			add_action(", ");
		}
		add_action(context_arg);
		add_action(")");
	}
}

शून्य context_member(वर्ण *txt, ध्रुव वर्ण *prop) {
	ध्रुव वर्ण *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	यदि (context_format == रिक्त) {
		add_action(txt);
	} अन्यथा {
		वर्ण buf[128];
		snprintf(buf, परिमाण(buf), context_format, txt);
		add_action(buf);
	}
}
