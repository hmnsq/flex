/* scan.l - scanner for flex input -*-C-*- */

%top{
/* flexdef.h includes config.h, which may contain macros that alter the API */
/* of libc functions. Must include first before any libc header. */
#समावेश "flexdef.h"
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

#समावेश "parse.h"
बाह्य bool tablesverify, tablesext;
बाह्य bool trlcontxt; /* Set in parse.y for each rule. */
बाह्य स्थिर अक्षर *escaped_qstart, *escaped_qend;

#घोषणा M4QSTART "[""["
#घोषणा M4QEND "]""]"

#घोषणा ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#घोषणा ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#घोषणा ACTION_ECHO add_action( श_माला )
#घोषणा ACTION_ECHO_QSTART add_action (ESCAPED_QSTART)
#घोषणा ACTION_ECHO_QEND   add_action (ESCAPED_QEND)

#घोषणा MARK_END_OF_PROLOG mark_prolog();

#घोषणा YY_DECL \
	पूर्णांक flexscan(व्योम)

#घोषणा RETURNCHAR \
	yylval = (अचिन्हित अक्षर) श_माला[0]; \
	वापस CHAR;

#घोषणा RETURNNAME \
	अगर(yyleng < MAXLINE) \
         { \
	म_नकलन( nmstr, श_माला, माप(nmstr) ); \
	वापस NAME; \
	 } \
	अन्यथा \
	 करो { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(निकास_त्रुटि);  \
	 } जबतक (0)

#घोषणा PUT_BACK_STRING(str, start) \
	{ माप_प्रकार i = म_माप( str );	\
	  जबतक ( i > start )		\
	    unput((str)[--i]);		\
	}

#घोषणा CHECK_REJECT(str) \
	अगर ( all_upper( str ) ) \
		reject = true;

#घोषणा CHECK_YYREJECT(str) \
	अगर ( all_lower( str ) ) \
		reject = true;

#घोषणा YY_USER_INIT \
	अगर ( दो_पर्या("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#घोषणा START_CODEBLOCK(x) करो { \
    /* Emit the needed line directive... */\
    अगर (indented_code == false) { \
        अगर (!x) linenum++; \
        पंक्ति_directive_out(शून्य, infilename, linenum);	\
    } \
    add_action(M4QSTART); \
    yy_धकेलो_state(CODEBLOCK); \
    अगर ((indented_code = x)) ACTION_ECHO; \
} जबतक(0)

#घोषणा END_CODEBLOCK करो { \
    yy_निकालो_state();\
    add_action(M4QEND); \
    अगर (!indented_code) पंक्ति_directive_out(शून्य, शून्य, linenum);	\
} जबतक (0)

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
व्योम context_call(अक्षर *);
व्योम context_member(अक्षर *, स्थिर अक्षर *);
#अघोषित yyreject
%}
%%
	अटल पूर्णांक bracelevel, didadef, indented_code;
	अटल bool doing_rule_action = false;
	अटल bool option_sense;

	अटल bool doing_codeblock = false;
	पूर्णांक brace_depth=0, brace_start_पंक्ति=0;
	अक्षर nmdef[MAXLINE];


<INITIAL>{
	^{WS}		START_CODEBLOCK(true);
	^"/*"		add_action("/*[""["); yy_धकेलो_state( COMMENT );
	^#{OPTWS}पंक्ति{WS}	yy_धकेलो_state( LINEDIR );
	^"%s"{NAME}?	वापस SCDECL;
	^"%x"{NAME}?	वापस XSCDECL;
	^"%{".*{NL}	START_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		अक्षर trampoline[512];
                brace_start_पंक्ति = linenum;
                ++linenum;
		snprintf(trampoline, माप(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                अगर (ctrl.gen_पंक्ति_dirs)
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
			पंक्ति_directive_out(शून्य, infilename, linenum);
			BEGIN(SECT2PROLOG);
			वापस SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); वापस TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			अगर(yyleng < MAXLINE)
        		 {
			म_नकलन( nmstr, श_माला, माप(nmstr) );
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
	[[:digit:]]+	linenum = myctoi( श_माला );

	"\""[^""\n]*"\""	{
			मुक्त(infilename);
			infilename = xstrdup(श_माला + 1);
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
			अगर ( indented_code ) END_CODEBLOCK;
			}
}

<CODEBLOCK_MATCH_BRACE>{
    "}"     {
                अगर( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_निकालो_state();
                }अन्यथा
                    buf_strnappend(&शीर्ष_buf, श_माला, yyleng);
            }

    "{"     {
                brace_depth++;
                buf_strnappend(&शीर्ष_buf, श_माला, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&शीर्ष_buf, श_माला, yyleng);
            }

    {M4QSTART}  buf_strnappend(&शीर्ष_buf, escaped_qstart, (पूर्णांक) म_माप(escaped_qstart));
    {M4QEND}    buf_strnappend(&शीर्ष_buf, escaped_qend, (पूर्णांक) म_माप(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&शीर्ष_buf, श_माला, yyleng);
    }

    <<खातापूर्ण>>     {
                linenum = brace_start_पंक्ति;
                synerr(_("Unmatched '{'"));
                वापस YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        अगर(yyleng < MAXLINE)
 		         {
			म_नकलन( nmdef, श_माला, माप(nmdef) );
 		         }
 		        अन्यथा
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(निकास_त्रुटि);
			 }
			/* Skip trailing whitespace. */
			{
			    माप_प्रकार i = म_माप( nmdef );
			    जबतक (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			अगर ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		वापस '=';
	[[:digit:]]+	{nmval = म_से_प(श_माला); वापस TOK_NUMERIC;}

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
	bison-locations  { अगर((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|हाल-sensitive		sf_set_case_ins(!option_sense);
	caseless|हाल-insensitive	sf_set_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	शेष		ctrl.spprdflt = ! option_sense;
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
	मुख्य		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			अगर (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	pointer		ctrl.yytext_is_array = ! option_sense;
	पढ़ो		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_used = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	ढेर		ctrl.ढेर_used = option_sense;
	stdinit		ctrl.do_stdinit = option_sense;
	मानक_निकास		env.use_stdout = option_sense;
	unistd		ctrl.no_unistd = ! option_sense;
	unput		ctrl.no_yyunput = ! option_sense;
	yyunput		ctrl.no_yyunput = ! option_sense;
	verbose		env.printstats = option_sense;
	warn		env.nowarn = ! option_sense;
	श_पंक्ति	ctrl.do_yylineno = option_sense;
	yymore		ctrl.yymore_really_used = option_sense;
	yywrap		ctrl.do_yywrap = option_sense;
	yyread		ctrl.noyyread = !option_sense;

	yypanic		ctrl.no_yypanic = !option_sense;

	yy_धकेलो_state	ctrl.no_yy_धकेलो_state = ! option_sense;
	yy_निकालो_state	ctrl.no_yy_निकालो_state = ! option_sense;
	yy_शीर्ष_state	ctrl.no_yy_शीर्ष_state = ! option_sense;

	yy_scan_बफर	ctrl.no_yy_scan_बफर = ! option_sense;
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

	bufsize		वापस TOK_BUFSIZE;
	emit		वापस TOK_EMIT;
	extra-type	वापस TOK_EXTRA_TYPE;
	outfile		वापस TOK_OUTFILE;
	prefix		वापस TOK_PREFIX;
	yyclass		वापस TOK_YYCLASS;
	yylmax		वापस TOK_YYLMAX;
	yydecl		वापस TOK_YYDECL;
	yyterminate	वापस TOK_YYTERMINATE;
	pre-action	वापस TOK_PREACTION;
	post-action	वापस TOK_POSTACTION;
	user-init	वापस TOK_USERINIT;
	header(-file)?      वापस TOK_HEADER_FILE;
	tables-file         वापस TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    अगर (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			अगर(yyleng-1 < MAXLINE)
        		 {
			म_नकलन( nmstr, श_माला + 1, माप(nmstr) );
			 }
			अन्यथा
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(निकास_त्रुटि);
			 }
			nmstr[म_माप( nmstr ) - 1] = '\0';
			वापस NAME;
			}

	(([a-mo-z]|n[a-np-z])[[:alpha:]\-+]*)|.	{
			format_synerr( _( "unrecognized %%option: %s" ),
				श_माला );
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
		अगर ( bracelevel <= 0 ) {
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
			वापस YY_NULL; /* to stop the parser */
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
                        अगर (!sf_skip_ws())
                            BEGIN(SC);
                        वापस '<';
                    }
	^{OPTWS}"^"	वापस '^';
	"\""		BEGIN(QUOTE); वापस '"';
	"{"/[[:digit:]]	{
			BEGIN(अंक_2);
			अगर ( ctrl.lex_compat || ctrl.posix_compat )
				वापस BEGIN_REPEAT_POSIX;
			अन्यथा
				वापस BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	वापस '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			अगर ( in_rule )
				{
				doing_rule_action = true;
				in_rule = false;
				वापस '\n';
				}
			}
	{WS}"|".*{NL}	{
                        अगर (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            पूर्णांक amt = (पूर्णांक) (म_अक्षर (श_माला, '|') - श_माला);
                            yyless(amt);
                        }
                        अन्यथा {
                            add_action("]""]");
                            continued_action = true;
                            ++linenum;
                            वापस '\n';
                        }
                    }

	^{WS}"/*"	{

                अगर (sf_skip_ws()){
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
            अगर (sf_skip_ws()){
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

                अगर ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    वापस '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            अगर (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            अन्यथा{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                अगर ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    वापस '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	वापस EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({FIRST_CCL_CHAR}|{CCL_व्यंजक})({CCL_CHAR}|{CCL_व्यंजक})*	{
			पूर्णांक cclval;

			अगर(yyleng < MAXLINE)
        		 {
			म_नकलन( nmstr, श_माला, माप(nmstr) );
			 }
			अन्यथा
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(निकास_त्रुटि);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			अगर (0 /* <--- This "0" effectively disables the reuse of a
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
				वापस '[';
				}
			}
    "{-}"       वापस CCL_OP_DIFF;
    "{+}"       वापस CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			अक्षर *nmdefptr;
            पूर्णांक end_is_ws, end_ch;

            end_ch = श_माला[yyleng-1];
            end_is_ws = end_ch != '}' ? 1 : 0;

 			अगर(yyleng-1 < MAXLINE)
         		 {
			म_नकलन( nmstr, श_माला + 1, माप(nmstr) );
 			 }
 			अन्यथा
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(निकास_त्रुटि);
 			 }
nmstr[yyleng - 2 - end_is_ws] = '\0';  /* chop trailing brace */

			अगर ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			अन्यथा
				{ /* push back name surrounded by ()'s */
				माप_प्रकार len = म_माप( nmdefptr );
                अगर (end_is_ws)
                    unput(end_ch);

				अगर ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (end_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_BACK_STRING(nmdefptr, 0);

					अगर ( nmdefptr[0] == '^' )
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
                    अगर (sf_skip_ws())
                        yy_धकेलो_state(COMMENT_DISCARD);
                    अन्यथा{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        वापस '/';
                    }
                }

    "(?#"       {
                    अगर (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_धकेलो(); 
                        वापस '(';
                    }
                    अन्यथा
                        yy_धकेलो_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_धकेलो();
                    अगर (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    अन्यथा
                        BEGIN(GROUP_WITH_PARAMS);
                    वापस '(';
                }
    "("         sf_धकेलो(); वापस '(';
    ")"         {
                    अगर (sf_शीर्ष_ix > 0) {
                        sf_निकालो();
                        वापस ')';
                    } अन्यथा
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	वापस (अचिन्हित अक्षर) श_माला[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		वापस (अचिन्हित अक्षर) श_माला[0];
	">"		BEGIN(SECT2); वापस '>';
	">"/^		BEGIN(CARETISBOL); वापस '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				श_माला );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); वापस '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); वापस '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			वापस '"';
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
	"^"/[^-\]\n]	BEGIN(CCL); वापस '^';
	"^"/("-"|"]")	वापस '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	वापस '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); वापस ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			वापस ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); वापस CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); वापस CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); वापस CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); वापस CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); वापस CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); वापस CCE_GRAPH;
	"[:lower:]"	BEGIN(CCL); वापस CCE_LOWER;
	"[:print:]"	BEGIN(CCL); वापस CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); वापस CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); वापस CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); वापस CCE_UPPER;
	"[:xdigit:]"	BEGIN(CCL); वापस CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); वापस CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); वापस CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); वापस CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); वापस CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); वापस CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); वापस CCE_NEG_GRAPH;
	"[:^lower:]"	BEGIN(CCL); वापस CCE_NEG_LOWER;
	"[:^print:]"	BEGIN(CCL); वापस CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); वापस CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); वापस CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); वापस CCE_NEG_UPPER;
	"[:^xdigit:]"	BEGIN(CCL); वापस CCE_NEG_XDIGIT;
	{CCL_व्यंजक}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					श_माला );
			BEGIN(CCL); वापस CCE_ALNUM;
			}
}

<अंक_2>{
	[[:digit:]]+	{
			yylval = myctoi( श_माला );
			वापस संख्या;
			}

	","		वापस ',';
	"}"		{
			BEGIN(SECT2);
			अगर ( ctrl.lex_compat || ctrl.posix_compat )
				वापस END_REPEAT_POSIX;
			अन्यथा
				वापस END_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			वापस '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			वापस '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_धकेलो_state( CODE_COMMENT );

	<CODEBLOCK,ACTION>{
		"reject" {
			ACTION_ECHO;
			CHECK_REJECT(श_माला);
        }
		"yyreject"{OPTWS}"("{OPTWS}")" {
			add_action("]""]M4_HOOK_REJECT[""[");
			CHECK_YYREJECT(श_माला);
        }
		"yymore"{OPTWS}"("{OPTWS}")" {
			yymore_used = true;
			अगर (ctrl.rewrite)
				context_call(श_माला);
			अन्यथा
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		अगर (bracelevel <= 0 || (doing_codeblock && indented_code)) {
            अगर ( doing_rule_action )
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
			अगर (ctrl.rewrite)
				context_call(श_माला);
			अन्यथा
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			add_action("]""]");
			add_action(श_माला);
			add_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|श_माला|yyflexdebug)/[^[:alnum:]_] {
			अगर (ctrl.rewrite)
				context_member(श_माला, "M4_PROPERTY_CONTEXT_FORMAT");
			अन्यथा
				ACTION_ECHO;
	}
	(श_पंक्ति|yycolumn)/[^[:alnum:]_] {
			अगर (ctrl.rewrite)
				context_member(श_माला, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
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
                अगर (bracelevel <= 0) {
                   अगर ( doing_rule_action )
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
	{NL}	++linenum; ACTION_ECHO; अगर (bracelevel <= 0) { BEGIN(SECT2); } अन्यथा { BEGIN(ACTION); }
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
			yylval = myesc( (अचिन्हित अक्षर *) श_माला );

			अगर ( YY_START == FIRSTCCL )
				BEGIN(CCL);

			वापस CHAR;
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
<*>.|\n			format_synerr( _( "bad character: %s" ), श_माला );

%%


पूर्णांक yywrap(व्योम)
	{
	अगर ( --num_input_files > 0 )
		{
		set_निवेश_file( *++निवेश_files );
		वापस 0;
		}

	अन्यथा
		वापस 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

व्योम set_निवेश_file( अक्षर *file )
	{
	अगर ( file && म_भेद( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = ख_खोलो( infilename, "r" );

		अगर ( yyin == शून्य )
			lerr( _( "can't open %s: %s" ), file, म_त्रुटि(त्रुटि_सं));
		}

	अन्यथा
		{
		yyin = मानक_निवेश;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

व्योम context_call(अक्षर *txt) {
	स्थिर अक्षर *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	अगर (context_arg == शून्य) {
		add_action(txt);
	} अन्यथा {
		अक्षर buf[बफ_मान];

		/* otherwise, supply the context string as a final argument */
		निश्चित(txt[म_माप(txt)-1] == ')');
		म_नकलन(buf, txt, माप(buf));
		buf[म_माप(buf)-1] = '\0';	/* remove trailing ) */
		add_action(buf);
		अगर (txt[म_माप(buf)-1] != '(') {
			add_action(", ");
		}
		add_action(context_arg);
		add_action(")");
	}
}

व्योम context_member(अक्षर *txt, स्थिर अक्षर *prop) {
	स्थिर अक्षर *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	अगर (context_format == शून्य) {
		add_action(txt);
	} अन्यथा {
		अक्षर buf[128];
		snprintf(buf, माप(buf), context_format, txt);
		add_action(buf);
	}
}
