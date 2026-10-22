/* scan.l - scanner for flex input -*-C-*- */

%top{
/* flexdef.h includes config.h, which may contain macros that alter the API */
/* of libc functions. Must include first before any libc header. */
#అన్తర్భావ "flexdef.h"
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

#అన్తర్భావ "parse.h"
బాహ్య bool tablesverify, tablesext;
బాహ్య bool trlcontxt; /* Set in parse.y for each rule. */
బాహ్య స్థిరరాశి అక్షరం *escaped_qstart, *escaped_qend;

#నిర్వచించు M4QSTART "[""["
#నిర్వచించు M4QEND "]""]"

#నిర్వచించు ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#నిర్వచించు ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#నిర్వచించు ACTION_ECHO కూడు_action( yytext )
#నిర్వచించు ACTION_ECHO_QSTART కూడు_action (ESCAPED_QSTART)
#నిర్వచించు ACTION_ECHO_QEND   కూడు_action (ESCAPED_QEND)

#నిర్వచించు MARK_చివర_యొక్క_PROLOG mark_prolog();

#నిర్వచించు YY_DECL \
	పూర్ణాంకం flexscan(శూన్య)

#నిర్వచించు RETURNCHAR \
	yylval = (గుర్తులేని అక్షరం) yytext[0]; \
	తిరిగి CHAR;

#నిర్వచించు RETURNNAME \
	ఒకవేళ(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, పరిమాణం(nmstr) ); \
	తిరిగి NAME; \
	 } \
	లేకపోతే \
	 చేయి { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } అయితే (0)

#నిర్వచించు PUT_వెనుక_STRING(str, ప్రారంభం) \
	{ size_t i = అక్షరశ్రేణి_పొడవు( str );	\
	  అయితే ( i > ప్రారంభం )		\
	    unput((str)[--i]);		\
	}

#నిర్వచించు CHECK_REJECT(str) \
	ఒకవేళ ( all_పై( str ) ) \
		reject = true;

#నిర్వచించు CHECK_YYREJECT(str) \
	ఒకవేళ ( all_క్రింది( str ) ) \
		reject = true;

#నిర్వచించు YY_USER_INIT \
	ఒకవేళ ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#నిర్వచించు ప్రారంభం_CODEBLOCK(x) చేయి { \
    /* Emit the needed line directive... */\
    ఒకవేళ (indented_సంకేతం == false) { \
        ఒకవేళ (!x) linenum++; \
        పంక్తి_directive_బహిర్గతం(ఖాళీ, infilename, linenum);	\
    } \
    కూడు_action(M4QSTART); \
    yy_నెట్టు_state(CODEBLOCK); \
    ఒకవేళ ((indented_సంకేతం = x)) ACTION_ECHO; \
} అయితే(0)

#నిర్వచించు చివర_CODEBLOCK చేయి { \
    yy_తీయి_state();\
    కూడు_action(M4QEND); \
    ఒకవేళ (!indented_సంకేతం) పంక్తి_directive_బహిర్గతం(ఖాళీ, ఖాళీ, linenum);	\
} అయితే (0)

%}

%option caseless nodefault noreject దొంతర noyy_శిఖరం_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL అంకె_2 QUOTE
%x FIRSTCCL CCL ACTION RECOVER COMMENT ACTION_STRING PERCENT_BRACE_ACTION
%x OPTION LINEDIR CODEBLOCK_సరిపోలిక_BRACE
%x సమూహం_WITH_PARAMS
%x సమూహం_MINUS_PARAMS
%x EXTENDED_COMMENT
%x COMMENT_DISCARD సంకేతం_COMMENT
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

మొదటి_CCL_CHAR	([^\\\n]|{ESCSEQ})
CCL_CHAR	([^\\\n\]]|{ESCSEQ})
CCL_సమాసం	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
శూన్య context_call(అక్షరం *);
శూన్య context_member(అక్షరం *, స్థిరరాశి అక్షరం *);
#నిర్వచనం_రద్దు yyreject
%}
%%
	స్థిర పూర్ణాంకం bracelevel, didadef, indented_సంకేతం;
	స్థిర bool doing_నియమం_action = false;
	స్థిర bool option_sense;

	స్థిర bool doing_codeblock = false;
	పూర్ణాంకం brace_లోతు=0, brace_ప్రారంభం_పంక్తి=0;
	అక్షరం nmdef[MAXLINE];


<INITIAL>{
	^{WS}		ప్రారంభం_CODEBLOCK(true);
	^"/*"		కూడు_action("/*[""["); yy_నెట్టు_state( COMMENT );
	^#{OPTWS}పంక్తి{WS}	yy_నెట్టు_state( LINEDIR );
	^"%s"{NAME}?	తిరిగి SCDECL;
	^"%x"{NAME}?	తిరిగి XSCDECL;
	^"%{".*{NL}	ప్రారంభం_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		అక్షరం trampoline[512];
                brace_ప్రారంభం_పంక్తి = linenum;
                ++linenum;
		snprintf(trampoline, పరిమాణం(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                ఒకవేళ (ctrl.gen_పంక్తి_dirs)
                    buf_strappend(&శిఖరం_buf, trampoline);
                brace_లోతు = 1;
                yy_నెట్టు_state(CODEBLOCK_సరిపోలిక_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			పంక్తి_directive_బహిర్గతం(ఖాళీ, infilename, linenum);
			BEGIN(SECT2PROLOG);
			తిరిగి SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); తిరిగి TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			ఒకవేళ(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, పరిమాణం(nmstr) );
			 }
			లేకపోతే
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


<COMMENT,సంకేతం_COMMENT>{ /* */
        [^\[\]\*\n]*  ACTION_ECHO;
        .           ACTION_ECHO;

	{NL}	    ++linenum; ACTION_ECHO;
}
<COMMENT>{
	"*/"	    కూడు_action("*/]""]"); yy_తీయి_state();
}
<సంకేతం_COMMENT>{
        "*/"        ACTION_ECHO; yy_తీయి_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_తీయి_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_తీయి_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_తీయి_state();
	[[:digit:]]+	linenum = myctoi( yytext );

	"\""[^""\n]*"\""	{
			విడుదల(infilename);
			infilename = xstrdup(yytext + 1);
			infilename[అక్షరశ్రేణి_పొడవు( infilename ) - 1] = '\0';
			}
	.		/* ignore spurious characters */
}
<ACTION,CODEBLOCK,ACTION_STRING,PERCENT_BRACE_ACTION,CHARACTER_CONSTANT,COMMENT,సంకేతం_COMMENT>{
   {M4QSTART}   ACTION_ECHO_QSTART;
   {M4QEND}     ACTION_ECHO_QEND;
}

<CODEBLOCK>{
	^"%}".*{NL}	++linenum; చివర_CODEBLOCK;
	[^\n%\[\]]*         ACTION_ECHO;
        .		ACTION_ECHO;
	{NL}		{
			++linenum;
			ACTION_ECHO;
			ఒకవేళ ( indented_సంకేతం ) చివర_CODEBLOCK;
			}
}

<CODEBLOCK_సరిపోలిక_BRACE>{
    "}"     {
                ఒకవేళ( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_తీయి_state();
                }లేకపోతే
                    buf_strnappend(&శిఖరం_buf, yytext, yyleng);
            }

    "{"     {
                brace_లోతు++;
                buf_strnappend(&శిఖరం_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&శిఖరం_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&శిఖరం_buf, escaped_qstart, (పూర్ణాంకం) అక్షరశ్రేణి_పొడవు(escaped_qstart));
    {M4QEND}    buf_strnappend(&శిఖరం_buf, escaped_qend, (పూర్ణాంకం) అక్షరశ్రేణి_పొడవు(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&శిఖరం_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_ప్రారంభం_పంక్తి;
                synerr(_("Unmatched '{'"));
                తిరిగి YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        ఒకవేళ(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, పరిమాణం(nmdef) );
 		         }
 		        లేకపోతే
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = అక్షరశ్రేణి_పొడవు( nmdef );
			    అయితే (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			ఒకవేళ ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		తిరిగి '=';
	[[:digit:]]+	{nmval = atoi(yytext); తిరిగి TOK_NUMERIC;}

	no		option_sense = ! option_sense;

	7బిట్టు		ctrl.csize = option_sense ? 128 : 256;
	8బిట్టు		ctrl.csize = option_sense ? 256 : 128;

	align		ctrl.long_align = option_sense;
	always-interactive	{
			ctrl.always_interactive = option_sense;
			ctrl.interactive = (trit)option_sense;
			}
	array		ctrl.yytext_is_array = option_sense;
	backup		env.backing_పైకి_report = option_sense;
	batch		ctrl.interactive = (trit)!option_sense;
	bison-bridge     ctrl.bison_bridge_lval = option_sense;
	bison-locations  { ఒకవేళ((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|స్థితి-sensitive		sf_సమితి_case_ins(!option_sense);
	caseless|స్థితి-insensitive	sf_సమితి_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	అప్రమేయ		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	నిండిన		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	ఆదానం		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	పంక్తి		ctrl.gen_పంక్తి_dirs = option_sense;
	ప్రధాన		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			ఒకవేళ (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	సూచిక		ctrl.yytext_is_array = ! option_sense;
	పఠ		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_వాడిన = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	దొంతర		ctrl.దొంతర_వాడిన = option_sense;
	stdinit		ctrl.do_stdinit = option_sense;
	stdout		env.use_stdout = option_sense;
	unistd		ctrl.no_unistd = ! option_sense;
	unput		ctrl.no_yyunput = ! option_sense;
	yyunput		ctrl.no_yyunput = ! option_sense;
	verbose		env.printstats = option_sense;
	warn		env.nowarn = ! option_sense;
	yylineno	ctrl.do_yylineno = option_sense;
	yymore		ctrl.yymore_really_వాడిన = option_sense;
	yywrap		ctrl.do_yywrap = option_sense;
	yyread		ctrl.noyyread = !option_sense;

	yypanic		ctrl.no_yypanic = !option_sense;

	yy_నెట్టు_state	ctrl.no_yy_నెట్టు_state = ! option_sense;
	yy_తీయి_state	ctrl.no_yy_తీయి_state = ! option_sense;
	yy_శిఖరం_state	ctrl.no_yy_శిఖరం_state = ! option_sense;

	yy_పరిశీలన_బఫరు	ctrl.no_yy_పరిశీలన_బఫరు = ! option_sense;
	yy_పరిశీలన_బైట్లు	ctrl.no_yy_పరిశీలన_బైట్లు = ! option_sense;
	yy_పరిశీలన_string	ctrl.no_yy_పరిశీలన_string = ! option_sense;

	yyalloc         ctrl.no_flex_alloc = ! option_sense;
	yyrealloc       ctrl.no_flex_realloc = ! option_sense;
	yyfree          ctrl.no_flex_free = ! option_sense;

	yyget_debug     ctrl.no_get_debug = ! option_sense;
	yyset_debug     ctrl.no_సమితి_debug = ! option_sense;
	yyget_extra     ctrl.no_yyget_extra = ! option_sense;
	yyset_extra     ctrl.no_yyset_extra = ! option_sense;
	yyget_leng      ctrl.no_yyget_leng = ! option_sense;
	yyget_పాఠ్యం      ctrl.no_yyget_పాఠ్యం = ! option_sense;
	yyget_స్తంభం    ctrl.no_yyget_స్తంభం = ! option_sense;
	yyset_స్తంభం    ctrl.no_yyset_స్తంభం = ! option_sense;
	yyget_lineno    ctrl.no_yyget_lineno = ! option_sense;
	yyset_lineno    ctrl.no_yyset_lineno = ! option_sense;
	yyget_లోపల        ctrl.no_yyget_లోపల = ! option_sense;
	yyset_లోపల        ctrl.no_yyset_లోపల = ! option_sense;
	yyget_బహిర్గతం       ctrl.no_yyget_బహిర్గతం = ! option_sense;
	yyset_బహిర్గతం       ctrl.no_yyset_బహిర్గతం = ! option_sense;
	yyget_lval      ctrl.no_yyget_lval = ! option_sense;
	yyset_lval      ctrl.no_yyset_lval = ! option_sense;
	yyget_lloc      ctrl.no_yyget_lloc = ! option_sense;
	yyset_lloc      ctrl.no_yyset_lloc = ! option_sense;

	bufsize		తిరిగి TOK_BUFSIZE;
	emit		తిరిగి TOK_EMIT;
	extra-type	తిరిగి TOK_EXTRA_TYPE;
	outfile		తిరిగి TOK_OUTFILE;
	ఉపసర్గ		తిరిగి TOK_ఉపసర్గ;
	yyclass		తిరిగి TOK_YYCLASS;
	yylmax		తిరిగి TOK_YYLMAX;
	yydecl		తిరిగి TOK_YYDECL;
	yyterminate	తిరిగి TOK_YYTERMINATE;
	pre-action	తిరిగి TOK_PREACTION;
	post-action	తిరిగి TOK_POSTACTION;
	user-init	తిరిగి TOK_USERINIT;
	శీర్షిక(-file)?      తిరిగి TOK_శీర్షిక_FILE;
	tables-file         తిరిగి TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    ఒకవేళ (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			ఒకవేళ(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, పరిమాణం(nmstr) );
			 }
			లేకపోతే
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[అక్షరశ్రేణి_పొడవు( nmstr ) - 1] = '\0';
			తిరిగి NAME;
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

	^{WS} ప్రారంభం_CODEBLOCK(true); /* indented code in prolog */

	^{NOT_WS}.*	{
        /* non-indented code */
		ఒకవేళ ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_సమితి_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } లేకపోతే {
            ప్రారంభం_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			తిరిగి YY_NULL; /* to stop the parser */
			}
}

<SECT2>{
	^{OPTWS}{NL}	++linenum; /* allow blank lines in section 2 */

	^{OPTWS}"%{"	{
			indented_సంకేతం = false;
			doing_codeblock = true;
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);
			}

	^{OPTWS}"<"	    {
                        /* Allow "<" to appear in (?x) patterns. */
                        ఒకవేళ (!sf_skip_ws())
                            BEGIN(SC);
                        తిరిగి '<';
                    }
	^{OPTWS}"^"	తిరిగి '^';
	"\""		BEGIN(QUOTE); తిరిగి '"';
	"{"/[[:digit:]]	{
			BEGIN(అంకె_2);
			ఒకవేళ ( ctrl.lex_compat || ctrl.posix_compat )
				తిరిగి BEGIN_REPEAT_POSIX;
			లేకపోతే
				తిరిగి BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	తిరిగి '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			ఒకవేళ ( లోపల_నియమం )
				{
				doing_నియమం_action = true;
				లోపల_నియమం = false;
				తిరిగి '\n';
				}
			}
	{WS}"|".*{NL}	{
                        ఒకవేళ (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            పూర్ణాంకం amt = (పూర్ణాంకం) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        లేకపోతే {
                            కూడు_action("]""]");
                            continued_action = true;
                            ++linenum;
                            తిరిగి '\n';
                        }
                    }

	^{WS}"/*"	{

                ఒకవేళ (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_నెట్టు_state(COMMENT_DISCARD);
                }
                లేకపోతే{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            ఒకవేళ (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            లేకపోతే{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                ఒకవేళ ( లోపల_నియమం )
                    {
                    doing_నియమం_action = true;
                    లోపల_నియమం = false;
                    తిరిగి '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            ఒకవేళ (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            లేకపోతే{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                ఒకవేళ ( లోపల_నియమం )
                    {
                    doing_నియమం_action = true;
                    లోపల_నియమం = false;
                    తిరిగి '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	తిరిగి EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({మొదటి_CCL_CHAR}|{CCL_సమాసం})({CCL_CHAR}|{CCL_సమాసం})*	{
			పూర్ణాంకం cclval;

			ఒకవేళ(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, పరిమాణం(nmstr) );
			 }
			లేకపోతే
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			ఒకవేళ (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			లేకపోతే
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
				తిరిగి '[';
				}
			}
    "{-}"       తిరిగి CCL_OP_DIFF;
    "{+}"       తిరిగి CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			అక్షరం *nmdefptr;
            పూర్ణాంకం చివర_is_ws, చివర_ch;

            చివర_ch = yytext[yyleng-1];
            చివర_is_ws = చివర_ch != '}' ? 1 : 0;

 			ఒకవేళ(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, పరిమాణం(nmstr) );
 			 }
 			లేకపోతే
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - చివర_is_ws] = '\0';  /* chop trailing brace */

			ఒకవేళ ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			లేకపోతే
				{ /* push back name surrounded by ()'s */
				size_t len = అక్షరశ్రేణి_పొడవు( nmdefptr );
                ఒకవేళ (చివర_is_ws)
                    unput(చివర_ch);

				ఒకవేళ ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (చివర_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_వెనుక_STRING(nmdefptr, 0);

					ఒకవేళ ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				లేకపోతే
					{
					unput(')');
					PUT_వెనుక_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    ఒకవేళ (sf_skip_ws())
                        yy_నెట్టు_state(COMMENT_DISCARD);
                    లేకపోతే{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        తిరిగి '/';
                    }
                }

    "(?#"       {
                    ఒకవేళ (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_నెట్టు(); 
                        తిరిగి '(';
                    }
                    లేకపోతే
                        yy_నెట్టు_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_నెట్టు();
                    ఒకవేళ (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    లేకపోతే
                        BEGIN(సమూహం_WITH_PARAMS);
                    తిరిగి '(';
                }
    "("         sf_నెట్టు(); తిరిగి '(';
    ")"         {
                    ఒకవేళ (sf_శిఖరం_ix > 0) {
                        sf_తీయి();
                        తిరిగి ')';
                    } లేకపోతే
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	తిరిగి (గుర్తులేని అక్షరం) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		తిరిగి (గుర్తులేని అక్షరం) yytext[0];
	">"		BEGIN(SECT2); తిరిగి '>';
	">"/^		BEGIN(CARETISBOL); తిరిగి '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); తిరిగి '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); తిరిగి '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			తిరిగి '"';
			}
}

<సమూహం_WITH_PARAMS>{
    ":"     BEGIN(SECT2);
    "-"     BEGIN(సమూహం_MINUS_PARAMS);
    i       sf_సమితి_case_ins(1);
    s       sf_సమితి_dot_all(1);
    x       sf_సమితి_skip_ws(1);
}
<సమూహం_MINUS_PARAMS>{
    ":"     BEGIN(SECT2);
    i       sf_సమితి_case_ins(0);
    s       sf_సమితి_dot_all(0);
    x       sf_సమితి_skip_ws(0);
}

<FIRSTCCL>{
	"^"/[^-\]\n]	BEGIN(CCL); తిరిగి '^';
	"^"/("-"|"]")	తిరిగి '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	తిరిగి '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); తిరిగి ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			తిరిగి ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); తిరిగి CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); తిరిగి CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); తిరిగి CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); తిరిగి CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); తిరిగి CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); తిరిగి CCE_లేఖాచిత్రం;
	"[:lower:]"	BEGIN(CCL); తిరిగి CCE_క్రింది;
	"[:print:]"	BEGIN(CCL); తిరిగి CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); తిరిగి CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); తిరిగి CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); తిరిగి CCE_పై;
	"[:xdigit:]"	BEGIN(CCL); తిరిగి CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); తిరిగి CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); తిరిగి CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); తిరిగి CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); తిరిగి CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); తిరిగి CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); తిరిగి CCE_NEG_లేఖాచిత్రం;
	"[:^lower:]"	BEGIN(CCL); తిరిగి CCE_NEG_క్రింది;
	"[:^print:]"	BEGIN(CCL); తిరిగి CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); తిరిగి CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); తిరిగి CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); తిరిగి CCE_NEG_పై;
	"[:^xdigit:]"	BEGIN(CCL); తిరిగి CCE_NEG_XDIGIT;
	{CCL_సమాసం}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); తిరిగి CCE_ALNUM;
			}
}

<అంకె_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			తిరిగి సంఖ్య;
			}

	","		తిరిగి ',';
	"}"		{
			BEGIN(SECT2);
			ఒకవేళ ( ctrl.lex_compat || ctrl.posix_compat )
				తిరిగి చివర_REPEAT_POSIX;
			లేకపోతే
				తిరిగి చివర_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			తిరిగి '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			తిరిగి '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_నెట్టు_state( సంకేతం_COMMENT );

	<CODEBLOCK,ACTION>{
		"reject" {
			ACTION_ECHO;
			CHECK_REJECT(yytext);
        }
		"yyreject"{OPTWS}"("{OPTWS}")" {
			కూడు_action("]""]M4_HOOK_REJECT[""[");
			CHECK_YYREJECT(yytext);
        }
		"yymore"{OPTWS}"("{OPTWS}")" {
			yymore_వాడిన = true;
			ఒకవేళ (ctrl.rewrite)
				context_call(yytext);
			లేకపోతే
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		ఒకవేళ (bracelevel <= 0 || (doing_codeblock && indented_సంకేతం)) {
            ఒకవేళ ( doing_నియమం_action )
                కూడు_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

            doing_నియమం_action = doing_codeblock = false;
            BEGIN(SECT2);
        }
    }
}


	/* yyreject and yymore() are checked for above, in PERCENT_BRACE_ACTION */
<ACTION>{
	"{"		ACTION_ECHO; ++bracelevel;
	"}"		ACTION_ECHO; --bracelevel;
	yyecho\(\)|yyinput\(\)|yystart\({FUNARGS}\)|yybegin\({FUNARGS}\)|yyunput\({FUNARGS}\)|yypanic\({FUNARGS}\)|yyatbol\(\)|yysetbol\({FUNARGS}\) {
			ఒకవేళ (ctrl.rewrite)
				context_call(yytext);
			లేకపోతే
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			కూడు_action("]""]");
			కూడు_action(yytext);
			కూడు_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			ఒకవేళ (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			లేకపోతే
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			ఒకవేళ (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			లేకపోతే
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
                ఒకవేళ (bracelevel <= 0) {
                   ఒకవేళ ( doing_నియమం_action )
                      కూడు_action( "\t]""]M4_HOOK_STATE_CASE_BREAK\n" );

                   doing_నియమం_action = false;
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
	{NL}	++linenum; ACTION_ECHO; ఒకవేళ (bracelevel <= 0) { BEGIN(SECT2); } లేకపోతే { BEGIN(ACTION); }
        .	ACTION_ECHO;
}

<COMMENT,సంకేతం_COMMENT,COMMENT_DISCARD,ACTION,ACTION_STRING,CHARACTER_CONSTANT><<EOF>>	{
			synerr( _( "EOF encountered inside an action" ) );
			yyterminate();
			}

<EXTENDED_COMMENT,సమూహం_WITH_PARAMS,సమూహం_MINUS_PARAMS><<EOF>>	{
			synerr( _( "EOF encountered inside pattern" ) );
			yyterminate();
			}

<SECT2,QUOTE,FIRSTCCL,CCL>{ESCSEQ}	{
			yylval = myesc( (గుర్తులేని అక్షరం *) yytext );

			ఒకవేళ ( YY_ప్రారంభం == FIRSTCCL )
				BEGIN(CCL);

			తిరిగి CHAR;
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


పూర్ణాంకం yywrap(శూన్య)
	{
	ఒకవేళ ( --num_input_files > 0 )
		{
		సమితి_ఆదానం_file( *++ఆదానం_files );
		తిరిగి 0;
		}

	లేకపోతే
		తిరిగి 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

శూన్య సమితి_ఆదానం_file( అక్షరం *file )
	{
	ఒకవేళ ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		ఒకవేళ ( yyin == ఖాళీ )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	లేకపోతే
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

శూన్య context_call(అక్షరం *txt) {
	స్థిరరాశి అక్షరం *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	ఒకవేళ (context_arg == ఖాళీ) {
		కూడు_action(txt);
	} లేకపోతే {
		అక్షరం buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		ప్రతిజ్ఞా(txt[అక్షరశ్రేణి_పొడవు(txt)-1] == ')');
		strncpy(buf, txt, పరిమాణం(buf));
		buf[అక్షరశ్రేణి_పొడవు(buf)-1] = '\0';	/* remove trailing ) */
		కూడు_action(buf);
		ఒకవేళ (txt[అక్షరశ్రేణి_పొడవు(buf)-1] != '(') {
			కూడు_action(", ");
		}
		కూడు_action(context_arg);
		కూడు_action(")");
	}
}

శూన్య context_member(అక్షరం *txt, స్థిరరాశి అక్షరం *prop) {
	స్థిరరాశి అక్షరం *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	ఒకవేళ (context_format == ఖాళీ) {
		కూడు_action(txt);
	} లేకపోతే {
		అక్షరం buf[128];
		snprintf(buf, పరిమాణం(buf), context_format, txt);
		కూడు_action(buf);
	}
}
