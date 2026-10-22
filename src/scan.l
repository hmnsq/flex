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
बाह्य स्थिरांक अक्षर *escaped_qstart, *escaped_qend;

#define M4QSTART "[""["
#define M4QEND "]""]"

#define ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#define ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#define ACTION_ECHO add_action( yytext )
#define ACTION_ECHO_QSTART add_action (ESCAPED_QSTART)
#define ACTION_ECHO_QEND   add_action (ESCAPED_QEND)

#define MARK_END_OF_PROLOG mark_prolog();

#define YY_DECL \
	पूर्णांक flexscan(शून्य)

#define RETURNCHAR \
	yylval = (अचिन्हित अक्षर) yytext[0]; \
	परत CHAR;

#define RETURNNAME \
	जर(yyleng < MAXLINE) \
         { \
	म_नकलन( nmstr, yytext, आकार(nmstr) ); \
	परत NAME; \
	 } \
	अन्यथा \
	 करा { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(निकास_त्रुटि);  \
	 } पर्यंत (0)

#define PUT_BACK_STRING(str, start) \
	{ माप_प्रकार i = म_माप( str );	\
	  पर्यंत ( i > start )		\
	    unput((str)[--i]);		\
	}

#define CHECK_REJECT(str) \
	जर ( all_upper( str ) ) \
		reject = true;

#define CHECK_YYREJECT(str) \
	जर ( all_lower( str ) ) \
		reject = true;

#define YY_USER_INIT \
	जर ( दो_पर्या("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#define START_CODEBLOCK(x) करा { \
    /* Emit the needed line directive... */\
    जर (indented_code == false) { \
        जर (!x) linenum++; \
        ओळ_directive_out(रिक्त, infilename, linenum);	\
    } \
    add_action(M4QSTART); \
    yy_ढकला_state(CODEBLOCK); \
    जर ((indented_code = x)) ACTION_ECHO; \
} पर्यंत(0)

#define END_CODEBLOCK करा { \
    yy_काढा_state();\
    add_action(M4QEND); \
    जर (!indented_code) ओळ_directive_out(रिक्त, रिक्त, linenum);	\
} पर्यंत (0)

%}

%option caseless nodefault noreject चळत noyy_शीर्ष_state
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
CCL_अभिव्यक्ती	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
शून्य context_call(अक्षर *);
शून्य context_member(अक्षर *, स्थिरांक अक्षर *);
#undef yyreject
%}
%%
	स्थिर पूर्णांक bracelevel, didadef, indented_code;
	स्थिर bool doing_rule_action = false;
	स्थिर bool option_sense;

	स्थिर bool doing_codeblock = false;
	पूर्णांक brace_depth=0, brace_start_ओळ=0;
	अक्षर nmdef[MAXLINE];


<INITIAL>{
	^{WS}		START_CODEBLOCK(true);
	^"/*"		add_action("/*[""["); yy_ढकला_state( COMMENT );
	^#{OPTWS}ओळ{WS}	yy_ढकला_state( LINEDIR );
	^"%s"{NAME}?	परत SCDECL;
	^"%x"{NAME}?	परत XSCDECL;
	^"%{".*{NL}	START_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		अक्षर trampoline[512];
                brace_start_ओळ = linenum;
                ++linenum;
		snprintf(trampoline, आकार(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                जर (ctrl.gen_ओळ_dirs)
                    buf_strappend(&शीर्ष_buf, trampoline);
                brace_depth = 1;
                yy_ढकला_state(CODEBLOCK_MATCH_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			ओळ_directive_out(रिक्त, infilename, linenum);
			BEGIN(SECT2PROLOG);
			परत SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); परत TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			जर(yyleng < MAXLINE)
        		 {
			म_नकलन( nmstr, yytext, आकार(nmstr) );
			 }
			अन्यथा
			 {
			   synerr( _("Definition name too long\n"));
			   FLEX_EXIT(निकास_त्रुटि);
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
	"*/"	    add_action("*/]""]"); yy_काढा_state();
}
<CODE_COMMENT>{
        "*/"        ACTION_ECHO; yy_काढा_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_काढा_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_काढा_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_काढा_state();
	[[:digit:]]+	linenum = myctoi( yytext );

	"\""[^""\n]*"\""	{
			मुक्त(infilename);
			infilename = xstrdup(yytext + 1);
			infilename[म_माप( infilename ) - 1] = '\0';
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
			जर ( indented_code ) END_CODEBLOCK;
			}
}

<CODEBLOCK_MATCH_BRACE>{
    "}"     {
                जर( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_काढा_state();
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

    {M4QSTART}  buf_strnappend(&शीर्ष_buf, escaped_qstart, (पूर्णांक) म_माप(escaped_qstart));
    {M4QEND}    buf_strnappend(&शीर्ष_buf, escaped_qend, (पूर्णांक) म_माप(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&शीर्ष_buf, yytext, yyleng);
    }

    <<खातापूर्ण>>     {
                linenum = brace_start_ओळ;
                synerr(_("Unmatched '{'"));
                परत YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        जर(yyleng < MAXLINE)
 		         {
			म_नकलन( nmdef, yytext, आकार(nmdef) );
 		         }
 		        अन्यथा
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(निकास_त्रुटि);
			 }
			/* Skip trailing whitespace. */
			{
			    माप_प्रकार i = म_माप( nmdef );
			    पर्यंत (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			जर ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		परत '=';
	[[:digit:]]+	{nmval = म_से_प(yytext); परत TOK_NUMERIC;}

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
	bison-locations  { जर((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|स्थिती-sensitive		sf_set_case_ins(!option_sense);
	caseless|स्थिती-insensitive	sf_set_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	पूर्वनिर्धारित		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	full		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	आदान		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	ओळ		ctrl.gen_ओळ_dirs = option_sense;
	main		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			जर (option_sense)
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
	चळत		ctrl.चळत_used = option_sense;
	stdinit		ctrl.do_stdinit = option_sense;
	मानक_निकास		env.use_stdout = option_sense;
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

	yy_ढकला_state	ctrl.no_yy_ढकला_state = ! option_sense;
	yy_काढा_state	ctrl.no_yy_काढा_state = ! option_sense;
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

	bufsize		परत TOK_BUFSIZE;
	emit		परत TOK_EMIT;
	extra-type	परत TOK_EXTRA_TYPE;
	outfile		परत TOK_OUTFILE;
	prefix		परत TOK_PREFIX;
	yyclass		परत TOK_YYCLASS;
	yylmax		परत TOK_YYLMAX;
	yydecl		परत TOK_YYDECL;
	yyterminate	परत TOK_YYTERMINATE;
	pre-action	परत TOK_PREACTION;
	post-action	परत TOK_POSTACTION;
	user-init	परत TOK_USERINIT;
	header(-file)?      परत TOK_HEADER_FILE;
	tables-file         परत TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    जर (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			जर(yyleng-1 < MAXLINE)
        		 {
			म_नकलन( nmstr, yytext + 1, आकार(nmstr) );
			 }
			अन्यथा
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(निकास_त्रुटि);
			 }
			nmstr[म_माप( nmstr ) - 1] = '\0';
			परत NAME;
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
		जर ( bracelevel <= 0 ) {
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

	<<खातापूर्ण>>		{
			mark_prolog();
			sectnum = 0;
			परत YY_NULL; /* to stop the parser */
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
                        जर (!sf_skip_ws())
                            BEGIN(SC);
                        परत '<';
                    }
	^{OPTWS}"^"	परत '^';
	"\""		BEGIN(QUOTE); परत '"';
	"{"/[[:digit:]]	{
			BEGIN(अंक_2);
			जर ( ctrl.lex_compat || ctrl.posix_compat )
				परत BEGIN_REPEAT_POSIX;
			अन्यथा
				परत BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	परत '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			जर ( in_rule )
				{
				doing_rule_action = true;
				in_rule = false;
				परत '\n';
				}
			}
	{WS}"|".*{NL}	{
                        जर (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            पूर्णांक amt = (पूर्णांक) (म_अक्षर (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        अन्यथा {
                            add_action("]""]");
                            continued_action = true;
                            ++linenum;
                            परत '\n';
                        }
                    }

	^{WS}"/*"	{

                जर (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_ढकला_state(COMMENT_DISCARD);
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
            जर (sf_skip_ws()){
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

                जर ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    परत '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            जर (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            अन्यथा{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                जर ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    परत '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	परत EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({FIRST_CCL_CHAR}|{CCL_अभिव्यक्ती})({CCL_CHAR}|{CCL_अभिव्यक्ती})*	{
			पूर्णांक cclval;

			जर(yyleng < MAXLINE)
        		 {
			म_नकलन( nmstr, yytext, आकार(nmstr) );
			 }
			अन्यथा
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(निकास_त्रुटि);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			जर (0 /* <--- This "0" effectively disables the reuse of a
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
				परत '[';
				}
			}
    "{-}"       परत CCL_OP_DIFF;
    "{+}"       परत CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			अक्षर *nmdefptr;
            पूर्णांक end_is_ws, end_ch;

            end_ch = yytext[yyleng-1];
            end_is_ws = end_ch != '}' ? 1 : 0;

 			जर(yyleng-1 < MAXLINE)
         		 {
			म_नकलन( nmstr, yytext + 1, आकार(nmstr) );
 			 }
 			अन्यथा
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(निकास_त्रुटि);
 			 }
nmstr[yyleng - 2 - end_is_ws] = '\0';  /* chop trailing brace */

			जर ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			अन्यथा
				{ /* push back name surrounded by ()'s */
				माप_प्रकार len = म_माप( nmdefptr );
                जर (end_is_ws)
                    unput(end_ch);

				जर ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (end_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_BACK_STRING(nmdefptr, 0);

					जर ( nmdefptr[0] == '^' )
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
                    जर (sf_skip_ws())
                        yy_ढकला_state(COMMENT_DISCARD);
                    अन्यथा{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        परत '/';
                    }
                }

    "(?#"       {
                    जर (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_ढकला(); 
                        परत '(';
                    }
                    अन्यथा
                        yy_ढकला_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_ढकला();
                    जर (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    अन्यथा
                        BEGIN(GROUP_WITH_PARAMS);
                    परत '(';
                }
    "("         sf_ढकला(); परत '(';
    ")"         {
                    जर (sf_शीर्ष_ix > 0) {
                        sf_काढा();
                        परत ')';
                    } अन्यथा
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	परत (अचिन्हित अक्षर) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		परत (अचिन्हित अक्षर) yytext[0];
	">"		BEGIN(SECT2); परत '>';
	">"/^		BEGIN(CARETISBOL); परत '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); परत '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); परत '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			परत '"';
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
	"^"/[^-\]\n]	BEGIN(CCL); परत '^';
	"^"/("-"|"]")	परत '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	परत '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); परत ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			परत ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); परत CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); परत CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); परत CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); परत CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); परत CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); परत CCE_GRAPH;
	"[:lower:]"	BEGIN(CCL); परत CCE_LOWER;
	"[:print:]"	BEGIN(CCL); परत CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); परत CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); परत CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); परत CCE_UPPER;
	"[:xdigit:]"	BEGIN(CCL); परत CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); परत CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); परत CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); परत CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); परत CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); परत CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); परत CCE_NEG_GRAPH;
	"[:^lower:]"	BEGIN(CCL); परत CCE_NEG_LOWER;
	"[:^print:]"	BEGIN(CCL); परत CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); परत CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); परत CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); परत CCE_NEG_UPPER;
	"[:^xdigit:]"	BEGIN(CCL); परत CCE_NEG_XDIGIT;
	{CCL_अभिव्यक्ती}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); परत CCE_ALNUM;
			}
}

<अंक_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			परत संख्या;
			}

	","		परत ',';
	"}"		{
			BEGIN(SECT2);
			जर ( ctrl.lex_compat || ctrl.posix_compat )
				परत END_REPEAT_POSIX;
			अन्यथा
				परत END_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			परत '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			परत '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_ढकला_state( CODE_COMMENT );

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
			जर (ctrl.rewrite)
				context_call(yytext);
			अन्यथा
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		जर (bracelevel <= 0 || (doing_codeblock && indented_code)) {
            जर ( doing_rule_action )
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
			जर (ctrl.rewrite)
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
			जर (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			अन्यथा
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			जर (ctrl.rewrite)
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
                जर (bracelevel <= 0) {
                   जर ( doing_rule_action )
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
	{NL}	++linenum; ACTION_ECHO; जर (bracelevel <= 0) { BEGIN(SECT2); } अन्यथा { BEGIN(ACTION); }
        .	ACTION_ECHO;
}

<COMMENT,CODE_COMMENT,COMMENT_DISCARD,ACTION,ACTION_STRING,CHARACTER_CONSTANT><<खातापूर्ण>>	{
			synerr( _( "EOF encountered inside an action" ) );
			yyterminate();
			}

<EXTENDED_COMMENT,GROUP_WITH_PARAMS,GROUP_MINUS_PARAMS><<खातापूर्ण>>	{
			synerr( _( "EOF encountered inside pattern" ) );
			yyterminate();
			}

<SECT2,QUOTE,FIRSTCCL,CCL>{ESCSEQ}	{
			yylval = myesc( (अचिन्हित अक्षर *) yytext );

			जर ( YY_START == FIRSTCCL )
				BEGIN(CCL);

			परत CHAR;
			}

<SECT3>{
    {M4QSTART}   ख_माला_दो(escaped_qstart, yyout);
    {M4QEND}     ख_माला_दो(escaped_qend, yyout);
    [^\[\]]*     ECHO;
    [][]         ECHO;
    <<खातापूर्ण>>      {
        sectnum = 0;
        yyterminate();
    }
}
<SECT3_NOESCAPE>{
    {M4QSTART}  ख_लिखो(yyout, "[""[%s]""]", escaped_qstart);
    {M4QEND}    ख_लिखो(yyout, "[""[%s]""]", escaped_qend);
    [^][]*      ECHO;
    [][]        ECHO;
    <<खातापूर्ण>>		{
       sectnum = 0;
       yyterminate();
    }
}
<*>.|\n			format_synerr( _( "bad character: %s" ), yytext );

%%


पूर्णांक yywrap(शून्य)
	{
	जर ( --num_input_files > 0 )
		{
		set_आदान_file( *++आदान_files );
		परत 0;
		}

	अन्यथा
		परत 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

शून्य set_आदान_file( अक्षर *file )
	{
	जर ( file && म_भेद( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = ख_खोलो( infilename, "r" );

		जर ( yyin == रिक्त )
			lerr( _( "can't open %s: %s" ), file, म_त्रुटि(त्रुटि_सं));
		}

	अन्यथा
		{
		yyin = मानक_निवेश;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

शून्य context_call(अक्षर *txt) {
	स्थिरांक अक्षर *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	जर (context_arg == रिक्त) {
		add_action(txt);
	} अन्यथा {
		अक्षर buf[बफ_मान];

		/* otherwise, supply the context string as a final argument */
		प्रतिज्ञा(txt[म_माप(txt)-1] == ')');
		म_नकलन(buf, txt, आकार(buf));
		buf[म_माप(buf)-1] = '\0';	/* remove trailing ) */
		add_action(buf);
		जर (txt[म_माप(buf)-1] != '(') {
			add_action(", ");
		}
		add_action(context_arg);
		add_action(")");
	}
}

शून्य context_member(अक्षर *txt, स्थिरांक अक्षर *prop) {
	स्थिरांक अक्षर *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	जर (context_format == रिक्त) {
		add_action(txt);
	} अन्यथा {
		अक्षर buf[128];
		snprintf(buf, आकार(buf), context_format, txt);
		add_action(buf);
	}
}
