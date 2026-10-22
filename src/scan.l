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
बाह्य अचर वर्ण *escaped_qstart, *escaped_qend;

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
	yylval = (अचिन्हित वर्ण) yytext[0]; \
	फर्काऊ CHAR;

#define RETURNNAME \
	यदि(yyleng < MAXLINE) \
         { \
	म_नकलन( nmstr, yytext, परिमाण(nmstr) ); \
	फर्काऊ NAME; \
	 } \
	अन्यथा \
	 गर { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(निकास_त्रुटि);  \
	 } जबसम्म (0)

#define PUT_BACK_STRING(str, start) \
	{ माप_प्रकार i = म_माप( str );	\
	  जबसम्म ( i > start )		\
	    unput((str)[--i]);		\
	}

#define CHECK_REJECT(str) \
	यदि ( all_upper( str ) ) \
		reject = true;

#define CHECK_YYREJECT(str) \
	यदि ( all_lower( str ) ) \
		reject = true;

#define YY_USER_INIT \
	यदि ( दो_पर्या("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#define START_CODEBLOCK(x) गर { \
    /* Emit the needed line directive... */\
    यदि (indented_code == false) { \
        यदि (!x) linenum++; \
        पङ्क्ति_directive_out(रिक्त, infilename, linenum);	\
    } \
    add_action(M4QSTART); \
    yy_थप_state(CODEBLOCK); \
    यदि ((indented_code = x)) ACTION_ECHO; \
} जबसम्म(0)

#define END_CODEBLOCK गर { \
    yy_झिक_state();\
    add_action(M4QEND); \
    यदि (!indented_code) पङ्क्ति_directive_out(रिक्त, रिक्त, linenum);	\
} जबसम्म (0)

%}

%option caseless nodefault noreject थाक noyy_शीर्ष_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL अङ्क_2 QUOTE
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
CCL_अभिव्यक्ति	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
शून्य context_call(वर्ण *);
शून्य context_member(वर्ण *, अचर वर्ण *);
#undef yyreject
%}
%%
	स्थिर पूर्णाङ्क bracelevel, didadef, indented_code;
	स्थिर bool doing_rule_action = false;
	स्थिर bool option_sense;

	स्थिर bool doing_codeblock = false;
	पूर्णाङ्क brace_depth=0, brace_start_पङ्क्ति=0;
	वर्ण nmdef[MAXLINE];


<INITIAL>{
	^{WS}		START_CODEBLOCK(true);
	^"/*"		add_action("/*[""["); yy_थप_state( COMMENT );
	^#{OPTWS}पङ्क्ति{WS}	yy_थप_state( LINEDIR );
	^"%s"{NAME}?	फर्काऊ SCDECL;
	^"%x"{NAME}?	फर्काऊ XSCDECL;
	^"%{".*{NL}	START_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		वर्ण trampoline[512];
                brace_start_पङ्क्ति = linenum;
                ++linenum;
		snprintf(trampoline, परिमाण(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                यदि (ctrl.gen_पङ्क्ति_dirs)
                    buf_strappend(&शीर्ष_buf, trampoline);
                brace_depth = 1;
                yy_थप_state(CODEBLOCK_MATCH_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			पङ्क्ति_directive_out(रिक्त, infilename, linenum);
			BEGIN(SECT2PROLOG);
			फर्काऊ SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); फर्काऊ TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			यदि(yyleng < MAXLINE)
        		 {
			म_नकलन( nmstr, yytext, परिमाण(nmstr) );
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
	"*/"	    add_action("*/]""]"); yy_झिक_state();
}
<CODE_COMMENT>{
        "*/"        ACTION_ECHO; yy_झिक_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_झिक_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_झिक_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_झिक_state();
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
			यदि ( indented_code ) END_CODEBLOCK;
			}
}

<CODEBLOCK_MATCH_BRACE>{
    "}"     {
                यदि( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_झिक_state();
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

    {M4QSTART}  buf_strnappend(&शीर्ष_buf, escaped_qstart, (पूर्णाङ्क) म_माप(escaped_qstart));
    {M4QEND}    buf_strnappend(&शीर्ष_buf, escaped_qend, (पूर्णाङ्क) म_माप(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&शीर्ष_buf, yytext, yyleng);
    }

    <<खातापूर्ण>>     {
                linenum = brace_start_पङ्क्ति;
                synerr(_("Unmatched '{'"));
                फर्काऊ YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        यदि(yyleng < MAXLINE)
 		         {
			म_नकलन( nmdef, yytext, परिमाण(nmdef) );
 		         }
 		        अन्यथा
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(निकास_त्रुटि);
			 }
			/* Skip trailing whitespace. */
			{
			    माप_प्रकार i = म_माप( nmdef );
			    जबसम्म (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
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

	"="		फर्काऊ '=';
	[[:digit:]]+	{nmval = म_से_प(yytext); फर्काऊ TOK_NUMERIC;}

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
	आगत		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	पङ्क्ति		ctrl.gen_पङ्क्ति_dirs = option_sense;
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
	थाक		ctrl.थाक_used = option_sense;
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

	yy_थप_state	ctrl.no_yy_थप_state = ! option_sense;
	yy_झिक_state	ctrl.no_yy_झिक_state = ! option_sense;
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

	bufsize		फर्काऊ TOK_BUFSIZE;
	emit		फर्काऊ TOK_EMIT;
	extra-type	फर्काऊ TOK_EXTRA_TYPE;
	outfile		फर्काऊ TOK_OUTFILE;
	prefix		फर्काऊ TOK_PREFIX;
	yyclass		फर्काऊ TOK_YYCLASS;
	yylmax		फर्काऊ TOK_YYLMAX;
	yydecl		फर्काऊ TOK_YYDECL;
	yyterminate	फर्काऊ TOK_YYTERMINATE;
	pre-action	फर्काऊ TOK_PREACTION;
	post-action	फर्काऊ TOK_POSTACTION;
	user-init	फर्काऊ TOK_USERINIT;
	header(-file)?      फर्काऊ TOK_HEADER_FILE;
	tables-file         फर्काऊ TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    यदि (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			यदि(yyleng-1 < MAXLINE)
        		 {
			म_नकलन( nmstr, yytext + 1, परिमाण(nmstr) );
			 }
			अन्यथा
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(निकास_त्रुटि);
			 }
			nmstr[म_माप( nmstr ) - 1] = '\0';
			फर्काऊ NAME;
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

	<<खातापूर्ण>>		{
			mark_prolog();
			sectnum = 0;
			फर्काऊ YY_NULL; /* to stop the parser */
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
                        फर्काऊ '<';
                    }
	^{OPTWS}"^"	फर्काऊ '^';
	"\""		BEGIN(QUOTE); फर्काऊ '"';
	"{"/[[:digit:]]	{
			BEGIN(अङ्क_2);
			यदि ( ctrl.lex_compat || ctrl.posix_compat )
				फर्काऊ BEGIN_REPEAT_POSIX;
			अन्यथा
				फर्काऊ BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	फर्काऊ '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			यदि ( in_rule )
				{
				doing_rule_action = true;
				in_rule = false;
				फर्काऊ '\n';
				}
			}
	{WS}"|".*{NL}	{
                        यदि (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            पूर्णाङ्क amt = (पूर्णाङ्क) (म_अक्षर (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        अन्यथा {
                            add_action("]""]");
                            continued_action = true;
                            ++linenum;
                            फर्काऊ '\n';
                        }
                    }

	^{WS}"/*"	{

                यदि (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_थप_state(COMMENT_DISCARD);
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
                    फर्काऊ '\n';
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
                    फर्काऊ '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	फर्काऊ EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({FIRST_CCL_CHAR}|{CCL_अभिव्यक्ति})({CCL_CHAR}|{CCL_अभिव्यक्ति})*	{
			पूर्णाङ्क cclval;

			यदि(yyleng < MAXLINE)
        		 {
			म_नकलन( nmstr, yytext, परिमाण(nmstr) );
			 }
			अन्यथा
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(निकास_त्रुटि);
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
				फर्काऊ '[';
				}
			}
    "{-}"       फर्काऊ CCL_OP_DIFF;
    "{+}"       फर्काऊ CCL_OP_UNION;


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
			म_नकलन( nmstr, yytext + 1, परिमाण(nmstr) );
 			 }
 			अन्यथा
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(निकास_त्रुटि);
 			 }
nmstr[yyleng - 2 - end_is_ws] = '\0';  /* chop trailing brace */

			यदि ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			अन्यथा
				{ /* push back name surrounded by ()'s */
				माप_प्रकार len = म_माप( nmdefptr );
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
                        yy_थप_state(COMMENT_DISCARD);
                    अन्यथा{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        फर्काऊ '/';
                    }
                }

    "(?#"       {
                    यदि (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_थप(); 
                        फर्काऊ '(';
                    }
                    अन्यथा
                        yy_थप_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_थप();
                    यदि (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    अन्यथा
                        BEGIN(GROUP_WITH_PARAMS);
                    फर्काऊ '(';
                }
    "("         sf_थप(); फर्काऊ '(';
    ")"         {
                    यदि (sf_शीर्ष_ix > 0) {
                        sf_झिक();
                        फर्काऊ ')';
                    } अन्यथा
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	फर्काऊ (अचिन्हित वर्ण) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		फर्काऊ (अचिन्हित वर्ण) yytext[0];
	">"		BEGIN(SECT2); फर्काऊ '>';
	">"/^		BEGIN(CARETISBOL); फर्काऊ '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); फर्काऊ '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); फर्काऊ '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			फर्काऊ '"';
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
	"^"/[^-\]\n]	BEGIN(CCL); फर्काऊ '^';
	"^"/("-"|"]")	फर्काऊ '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	फर्काऊ '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); फर्काऊ ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			फर्काऊ ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); फर्काऊ CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); फर्काऊ CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); फर्काऊ CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); फर्काऊ CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); फर्काऊ CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); फर्काऊ CCE_GRAPH;
	"[:lower:]"	BEGIN(CCL); फर्काऊ CCE_LOWER;
	"[:print:]"	BEGIN(CCL); फर्काऊ CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); फर्काऊ CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); फर्काऊ CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); फर्काऊ CCE_UPPER;
	"[:xdigit:]"	BEGIN(CCL); फर्काऊ CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); फर्काऊ CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); फर्काऊ CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); फर्काऊ CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); फर्काऊ CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); फर्काऊ CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); फर्काऊ CCE_NEG_GRAPH;
	"[:^lower:]"	BEGIN(CCL); फर्काऊ CCE_NEG_LOWER;
	"[:^print:]"	BEGIN(CCL); फर्काऊ CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); फर्काऊ CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); फर्काऊ CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); फर्काऊ CCE_NEG_UPPER;
	"[:^xdigit:]"	BEGIN(CCL); फर्काऊ CCE_NEG_XDIGIT;
	{CCL_अभिव्यक्ति}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); फर्काऊ CCE_ALNUM;
			}
}

<अङ्क_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			फर्काऊ सङ्ख्या;
			}

	","		फर्काऊ ',';
	"}"		{
			BEGIN(SECT2);
			यदि ( ctrl.lex_compat || ctrl.posix_compat )
				फर्काऊ END_REPEAT_POSIX;
			अन्यथा
				फर्काऊ END_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			फर्काऊ '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			फर्काऊ '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_थप_state( CODE_COMMENT );

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

<COMMENT,CODE_COMMENT,COMMENT_DISCARD,ACTION,ACTION_STRING,CHARACTER_CONSTANT><<खातापूर्ण>>	{
			synerr( _( "EOF encountered inside an action" ) );
			yyterminate();
			}

<EXTENDED_COMMENT,GROUP_WITH_PARAMS,GROUP_MINUS_PARAMS><<खातापूर्ण>>	{
			synerr( _( "EOF encountered inside pattern" ) );
			yyterminate();
			}

<SECT2,QUOTE,FIRSTCCL,CCL>{ESCSEQ}	{
			yylval = myesc( (अचिन्हित वर्ण *) yytext );

			यदि ( YY_START == FIRSTCCL )
				BEGIN(CCL);

			फर्काऊ CHAR;
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


पूर्णाङ्क yywrap(शून्य)
	{
	यदि ( --num_input_files > 0 )
		{
		set_आगत_file( *++आगत_files );
		फर्काऊ 0;
		}

	अन्यथा
		फर्काऊ 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

शून्य set_आगत_file( वर्ण *file )
	{
	यदि ( file && म_भेद( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = ख_खोलो( infilename, "r" );

		यदि ( yyin == रिक्त )
			lerr( _( "can't open %s: %s" ), file, म_त्रुटि(त्रुटि_सं));
		}

	अन्यथा
		{
		yyin = मानक_निवेश;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

शून्य context_call(वर्ण *txt) {
	अचर वर्ण *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	यदि (context_arg == रिक्त) {
		add_action(txt);
	} अन्यथा {
		वर्ण buf[बफ_मान];

		/* otherwise, supply the context string as a final argument */
		प्रतिज्ञा(txt[म_माप(txt)-1] == ')');
		म_नकलन(buf, txt, परिमाण(buf));
		buf[म_माप(buf)-1] = '\0';	/* remove trailing ) */
		add_action(buf);
		यदि (txt[म_माप(buf)-1] != '(') {
			add_action(", ");
		}
		add_action(context_arg);
		add_action(")");
	}
}

शून्य context_member(वर्ण *txt, अचर वर्ण *prop) {
	अचर वर्ण *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	यदि (context_format == रिक्त) {
		add_action(txt);
	} अन्यथा {
		वर्ण buf[128];
		snprintf(buf, परिमाण(buf), context_format, txt);
		add_action(buf);
	}
}
