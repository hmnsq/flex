/* scan.l - scanner for flex input -*-C-*- */

%top{
/* flexdef.h includes config.h, which may contain macros that alter the API */
/* of libc functions. Must include first before any libc header. */
#ଅନ୍ତର୍ଭାଵ "flexdef.h"
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

#ଅନ୍ତର୍ଭାଵ "parse.h"
ବାହ୍ୟ bool tablesverify, tablesext;
ବାହ୍ୟ bool trlcontxt; /* Set in parse.y for each rule. */
ବାହ୍ୟ ଅଚଳ ଅକ୍ଷର *escaped_qstart, *escaped_qend;

#define M4QSTART "[""["
#define M4QEND "]""]"

#define ESCAPED_QSTART "[" M4QEND M4QSTART "[" M4QEND M4QSTART
#define ESCAPED_QEND M4QEND "]" M4QSTART M4QEND "]" M4QSTART

#define ACTION_ECHO add_action( yytext )
#define ACTION_ECHO_QSTART add_action (ESCAPED_QSTART)
#define ACTION_ECHO_QEND   add_action (ESCAPED_QEND)

#define MARK_END_OF_PROLOG mark_prolog();

#define YY_DECL \
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା flexscan(ଶୂନ୍ୟ)

#define RETURNCHAR \
	yylval = (unsigned ଅକ୍ଷର) yytext[0]; \
	ଫେରନ୍ତୁ CHAR;

#define RETURNNAME \
	ଯଦି(yyleng < MAXLINE) \
         { \
	strncpy( nmstr, yytext, ଆକାର(nmstr) ); \
	ଫେରନ୍ତୁ NAME; \
	 } \
	ଅନ୍ୟଥା \
	 କର { \
	   synerr(_("Input line too long\n")); \
	   FLEX_EXIT(EXIT_FAILURE);  \
	 } ଯେତେବେଳେ (0)

#define PUT_BACK_STRING(str, start) \
	{ size_t i = strlen( str );	\
	  ଯେତେବେଳେ ( i > start )		\
	    unput((str)[--i]);		\
	}

#define CHECK_REJECT(str) \
	ଯଦି ( all_upper( str ) ) \
		reject = true;

#define CHECK_YYREJECT(str) \
	ଯଦି ( all_lower( str ) ) \
		reject = true;

#define YY_USER_INIT \
	ଯଦି ( getenv("POSIXLY_CORRECT") ) \
		ctrl.posix_compat = true;

#define START_CODEBLOCK(x) କର { \
    /* Emit the needed line directive... */\
    ଯଦି (indented_code == false) { \
        ଯଦି (!x) linenum++; \
        ଧାଡ଼ି_directive_out(ଖାଲି, infilename, linenum);	\
    } \
    add_action(M4QSTART); \
    yy_ଠେଲ_state(CODEBLOCK); \
    ଯଦି ((indented_code = x)) ACTION_ECHO; \
} ଯେତେବେଳେ(0)

#define END_CODEBLOCK କର { \
    yy_କାଢ଼_state();\
    add_action(M4QEND); \
    ଯଦି (!indented_code) ଧାଡ଼ି_directive_out(ଖାଲି, ଖାଲି, linenum);	\
} ଯେତେବେଳେ (0)

%}

%option caseless nodefault noreject ଗଦା noyy_ଶୀର୍ଷ_state
%option nostdinit

%x SECT2 SECT2PROLOG SECT3 CODEBLOCK PICKUPDEF SC CARETISBOL ଅଙ୍କ_2 QUOTE
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
CCL_ପଦସମଷ୍ଟି	("[:"^?[[:alpha:]]+":]")

LEXOPT		[aceknopr]

M4QSTART    "[""["
M4QEND      "]""]"

FUNARGS     [^)]*

%{
ଶୂନ୍ୟ context_call(ଅକ୍ଷର *);
ଶୂନ୍ୟ context_member(ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *);
#undef yyreject
%}
%%
	ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା bracelevel, didadef, indented_code;
	ସ୍ଥିର bool doing_rule_action = false;
	ସ୍ଥିର bool option_sense;

	ସ୍ଥିର bool doing_codeblock = false;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା brace_depth=0, brace_start_ଧାଡ଼ି=0;
	ଅକ୍ଷର nmdef[MAXLINE];


<INITIAL>{
	^{WS}		START_CODEBLOCK(true);
	^"/*"		add_action("/*[""["); yy_ଠେଲ_state( COMMENT );
	^#{OPTWS}ଧାଡ଼ି{WS}	yy_ଠେଲ_state( LINEDIR );
	^"%s"{NAME}?	ଫେରନ୍ତୁ SCDECL;
	^"%x"{NAME}?	ଫେରନ୍ତୁ XSCDECL;
	^"%{".*{NL}	START_CODEBLOCK(false);
    ^"%top"[[:blank:]]*"{"[[:blank:]]*{NL}    {
		ଅକ୍ଷର trampoline[512];
                brace_start_ଧାଡ଼ି = linenum;
                ++linenum;
		snprintf(trampoline, ଆକାର(trampoline),
			 "M4_HOOK_TRACE_LINE_FORMAT(%d, [[%s]])",
			 linenum, infilename?infilename:"<stdin>");
                ଯଦି (ctrl.gen_ଧାଡ଼ି_dirs)
                    buf_strappend(&ଶୀର୍ଷ_buf, trampoline);
                brace_depth = 1;
                yy_ଠେଲ_state(CODEBLOCK_MATCH_BRACE);
            }

    ^"%top".*   synerr( _("malformed '%top' directive") );

	{WS}		/* discard */

	^"%%".*		{
			sectnum = 2;
			bracelevel = 0;
			mark_defs1();
			ଧାଡ଼ି_directive_out(ଖାଲି, infilename, linenum);
			BEGIN(SECT2PROLOG);
			ଫେରନ୍ତୁ SECTEND;
			}

	^"%pointer".*{NL}	ctrl.yytext_is_array = false; ++linenum;
	^"%array".*{NL}		ctrl.yytext_is_array = true; ++linenum;

	^"%option"	BEGIN(OPTION); ଫେରନ୍ତୁ TOK_OPTION;

	^"%"{LEXOPT}{OPTWS}[[:digit:]]*{OPTWS}{NL}	++linenum; /* ignore */
	^"%"{LEXOPT}{WS}.*{NL}	++linenum;	/* ignore */

	/* xgettext: no-c-format */
	^"%"[^sxaceknopr{}].*	synerr( _( "unrecognized '%' directive" ) );

	^{NAME}		{
			ଯଦି(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, ଆକାର(nmstr) );
			 }
			ଅନ୍ୟଥା
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
	"*/"	    add_action("*/]""]"); yy_କାଢ଼_state();
}
<CODE_COMMENT>{
        "*/"        ACTION_ECHO; yy_କାଢ଼_state();
}

<COMMENT_DISCARD>{
        /* This is the same as COMMENT, but is discarded rather than output. */
	"*/"		yy_କାଢ଼_state();
    "*"         ;
	[^*\n]      ;
	{NL}	    ++linenum;
}

<EXTENDED_COMMENT>{
    ")"         yy_କାଢ଼_state();
    [^\n\)]+      ;
    {NL}        ++linenum;
}

<LINEDIR>{
	\n		yy_କାଢ଼_state();
	[[:digit:]]+	linenum = myctoi( yytext );

	"\""[^""\n]*"\""	{
			ମୁକ୍ତ(infilename);
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
			ଯଦି ( indented_code ) END_CODEBLOCK;
			}
}

<CODEBLOCK_MATCH_BRACE>{
    "}"     {
                ଯଦି( --brace_depth == 0){
                    /* TODO: Matched. */
                    yy_କାଢ଼_state();
                }ଅନ୍ୟଥା
                    buf_strnappend(&ଶୀର୍ଷ_buf, yytext, yyleng);
            }

    "{"     {
                brace_depth++;
                buf_strnappend(&ଶୀର୍ଷ_buf, yytext, yyleng);
            }

    {NL}    {
                ++linenum;
                buf_strnappend(&ଶୀର୍ଷ_buf, yytext, yyleng);
            }

    {M4QSTART}  buf_strnappend(&ଶୀର୍ଷ_buf, escaped_qstart, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) strlen(escaped_qstart));
    {M4QEND}    buf_strnappend(&ଶୀର୍ଷ_buf, escaped_qend, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) strlen(escaped_qend));
    ([^{}\r\n\[\]]+)|[^{}\r\n]  {
       buf_strnappend(&ଶୀର୍ଷ_buf, yytext, yyleng);
    }

    <<EOF>>     {
                linenum = brace_start_ଧାଡ଼ି;
                synerr(_("Unmatched '{'"));
                ଫେରନ୍ତୁ YY_NULL;
                }
}


<PICKUPDEF>{
	{WS}		/* separates name and definition */

	{NOT_WS}[^\r\n]*	{
 		        ଯଦି(yyleng < MAXLINE)
 		         {
			strncpy( nmdef, yytext, ଆକାର(nmdef) );
 		         }
 		        ଅନ୍ୟଥା
 		         {
 		           format_synerr( _("Definition value for {%s} too long\n"), nmstr);
 		           FLEX_EXIT(EXIT_FAILURE);
			 }
			/* Skip trailing whitespace. */
			{
			    size_t i = strlen( nmdef );
			    ଯେତେବେଳେ (i > 0 && (nmdef[i-1] == ' ' || nmdef[i-1] == '\t'))
			       --i;
			    nmdef[i] = '\0';
			}

			ndinstal( nmstr, nmdef );
			didadef = true;
			}

	{NL}		{
			ଯଦି ( ! didadef )
				synerr( _( "incomplete name definition" ) );
			BEGIN(INITIAL);
			++linenum;
			}
}


<OPTION>{
	{NL}		++linenum; BEGIN(INITIAL);
	{WS}		option_sense = true;

	"="		ଫେରନ୍ତୁ '=';
	[[:digit:]]+	{nmval = atoi(yytext); ଫେରନ୍ତୁ TOK_NUMERIC;}

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
	bison-locations  { ଯଦି((ctrl.bison_bridge_lloc = option_sense))
                            ctrl.bison_bridge_lval = true;
			}
	"c++"		ctrl.C_plus_plus = option_sense;
	caseful|ସ୍ଥିତି-sensitive		sf_set_case_ins(!option_sense);
	caseless|ସ୍ଥିତି-insensitive	sf_set_case_ins(option_sense);
	debug		ctrl.ddebug = option_sense;
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ		ctrl.spprdflt = ! option_sense;
	ecs		ctrl.useecs = option_sense;
	fast		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fullspd = true;
			}
	full		{
			ctrl.useecs = ctrl.usemecs = false;
			ctrl.use_read = ctrl.fulltbl = true;
			}
	ନିବେଶ		ctrl.no_yyinput = ! option_sense;
	yyinput		ctrl.no_yyinput = ! option_sense;
	interactive	ctrl.interactive = (trit)option_sense;
	lex-compat	ctrl.lex_compat = option_sense;
	posix-compat	ctrl.posix_compat = option_sense;
	ଧାଡ଼ି		ctrl.gen_ଧାଡ଼ି_dirs = option_sense;
	ମୁଖ୍ୟ		{
			ctrl.do_main = option_sense;
			/* Override yywrap */
			ଯଦି (option_sense)
                		ctrl.do_yywrap = false;
			}
	meta-ecs	ctrl.usemecs = option_sense;
	never-interactive	{
			ctrl.never_interactive = option_sense;
            		ctrl.interactive = (trit)!option_sense;
			}
	perf-report	env.performance_hint += option_sense ? 1 : -1;
	pointer		ctrl.yytext_is_array = ! option_sense;
	ପଠ		ctrl.use_read = option_sense;
	reentrant	ctrl.reentrant = option_sense;
	reject		ctrl.reject_really_used = option_sense;
	rewrite		ctrl.rewrite = option_sense;
	ଗଦା		ctrl.ଗଦା_used = option_sense;
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

	yy_ଠେଲ_state	ctrl.no_yy_ଠେଲ_state = ! option_sense;
	yy_କାଢ଼_state	ctrl.no_yy_କାଢ଼_state = ! option_sense;
	yy_ଶୀର୍ଷ_state	ctrl.no_yy_ଶୀର୍ଷ_state = ! option_sense;

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

	bufsize		ଫେରନ୍ତୁ TOK_BUFSIZE;
	emit		ଫେରନ୍ତୁ TOK_EMIT;
	extra-type	ଫେରନ୍ତୁ TOK_EXTRA_TYPE;
	outfile		ଫେରନ୍ତୁ TOK_OUTFILE;
	prefix		ଫେରନ୍ତୁ TOK_PREFIX;
	yyclass		ଫେରନ୍ତୁ TOK_YYCLASS;
	yylmax		ଫେରନ୍ତୁ TOK_YYLMAX;
	yydecl		ଫେରନ୍ତୁ TOK_YYDECL;
	yyterminate	ଫେରନ୍ତୁ TOK_YYTERMINATE;
	pre-action	ଫେରନ୍ତୁ TOK_PREACTION;
	post-action	ଫେରନ୍ତୁ TOK_POSTACTION;
	user-init	ଫେରନ୍ତୁ TOK_USERINIT;
	header(-file)?      ଫେରନ୍ତୁ TOK_HEADER_FILE;
	tables-file         ଫେରନ୍ତୁ TOK_TABLES_FILE;
	tables-verify   {
                    tablesverify = option_sense;
                    ଯଦି (!tablesext && option_sense)
                        tablesext = true;
                    }


	"\""[^""\n]*"\""	{
			ଯଦି(yyleng-1 < MAXLINE)
        		 {
			strncpy( nmstr, yytext + 1, ଆକାର(nmstr) );
			 }
			ଅନ୍ୟଥା
			 {
			   synerr( _("Option line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }
			nmstr[strlen( nmstr ) - 1] = '\0';
			ଫେରନ୍ତୁ NAME;
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
		ଯଦି ( bracelevel <= 0 ) {
            /* not in %{ ... %} */
            yyless( 0 );	/* put it all back */
            yy_set_bol( 1 );
            mark_prolog();
            BEGIN(SECT2);
        } ଅନ୍ୟଥା {
            START_CODEBLOCK(true);
        }
    }

	.		ACTION_ECHO;
	{NL}	++linenum; ACTION_ECHO;

	<<EOF>>		{
			mark_prolog();
			sectnum = 0;
			ଫେରନ୍ତୁ YY_NULL; /* to stop the parser */
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
                        ଯଦି (!sf_skip_ws())
                            BEGIN(SC);
                        ଫେରନ୍ତୁ '<';
                    }
	^{OPTWS}"^"	ଫେରନ୍ତୁ '^';
	"\""		BEGIN(QUOTE); ଫେରନ୍ତୁ '"';
	"{"/[[:digit:]]	{
			BEGIN(ଅଙ୍କ_2);
			ଯଦି ( ctrl.lex_compat || ctrl.posix_compat )
				ଫେରନ୍ତୁ BEGIN_REPEAT_POSIX;
			ଅନ୍ୟଥା
				ଫେରନ୍ତୁ BEGIN_REPEAT_FLEX;
			}
	"$"/([[:blank:]]|{NL})	ଫେରନ୍ତୁ '$';

	{WS}"%{"		{
			bracelevel = 1;
			BEGIN(PERCENT_BRACE_ACTION);

			ଯଦି ( in_rule )
				{
				doing_rule_action = true;
				in_rule = false;
				ଫେରନ୍ତୁ '\n';
				}
			}
	{WS}"|".*{NL}	{
                        ଯଦି (sf_skip_ws()){
                            /* We're in the middle of a (?x: ) pattern. */
                            /* Push back everything starting at the "|" */
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା amt = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) (strchr (yytext, '|') - yytext);
                            yyless(amt);
                        }
                        ଅନ୍ୟଥା {
                            add_action("]""]");
                            continued_action = true;
                            ++linenum;
                            ଫେରନ୍ତୁ '\n';
                        }
                    }

	^{WS}"/*"	{

                ଯଦି (sf_skip_ws()){
                    /* We're in the middle of a (?x: ) pattern. */
                    yy_ଠେଲ_state(COMMENT_DISCARD);
                }
                ଅନ୍ୟଥା{
                    yyless( yyleng - 2 );	/* put back '/', '*' */
                    bracelevel = 0;
                    continued_action = false;
                    BEGIN(ACTION);
                }
			}

	^{WS}		/* allow indented rules */ ;

	{WS}		{
            ଯଦି (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
            }
            ଅନ୍ୟଥା{
                /* This rule is separate from the one below because
                 * otherwise we get variable trailing context, so
                 * we can't build the scanner using -{f,F}.
                 */
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);

                ଯଦି ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    ଫେରନ୍ତୁ '\n';
                    }
            }
			}

	{OPTWS}{NL}	{
            ଯଦି (sf_skip_ws()){
                /* We're in the middle of a (?x: ) pattern. */
                ++linenum;
            }
            ଅନ୍ୟଥା{
                bracelevel = 0;
                continued_action = false;
                BEGIN(ACTION);
                unput( '\n' );	/* so <ACTION> sees it */

                ଯଦି ( in_rule )
                    {
                    doing_rule_action = true;
                    in_rule = false;
                    ଫେରନ୍ତୁ '\n';
                    }
            }
			}

	^{OPTWS}"<<EOF>>"	|
	"<<EOF>>"	ଫେରନ୍ତୁ EOF_OP;

	^"%%".*		{
			sectnum = 3;
			BEGIN(ctrl.no_section3_escape ? SECT3_NOESCAPE : SECT3);
			yyterminate(); /* to stop the parser */

			}

	"["({FIRST_CCL_CHAR}|{CCL_ପଦସମଷ୍ଟି})({CCL_CHAR}|{CCL_ପଦସମଷ୍ଟି})*	{
			ପୂର୍ଣ୍ଣସଂଖ୍ୟା cclval;

			ଯଦି(yyleng < MAXLINE)
        		 {
			strncpy( nmstr, yytext, ଆକାର(nmstr) );
			 }
			ଅନ୍ୟଥା
			 {
			   synerr( _("Input line too long\n"));
			   FLEX_EXIT(EXIT_FAILURE);
			 }

			/* Check to see if we've already encountered this
			 * ccl.
			 */
			ଯଦି (0 /* <--- This "0" effectively disables the reuse of a
                   * character class (purely based on its source text).
                   * The reason it was disabled is so yacc/bison can parse
                   * ccl operations, such as ccl difference and union.
                   */
                &&  (cclval = ccllookup( nmstr )) != 0 )
				{
     				 /* Dead code removed */
				}
			ଅନ୍ୟଥା
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
				ଫେରନ୍ତୁ '[';
				}
			}
    "{-}"       ଫେରନ୍ତୁ CCL_OP_DIFF;
    "{+}"       ଫେରନ୍ତୁ CCL_OP_UNION;


    /* Check for :space: at the end of the rule so we don't
     * wrap the expanded regex in '(' ')' -- breaking trailing
     * context.
     */
	"{"{NAME}"}"[[:space:]]?	 {
			ଅକ୍ଷର *nmdefptr;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା end_is_ws, end_ch;

            end_ch = yytext[yyleng-1];
            end_is_ws = end_ch != '}' ? 1 : 0;

 			ଯଦି(yyleng-1 < MAXLINE)
         		 {
			strncpy( nmstr, yytext + 1, ଆକାର(nmstr) );
 			 }
 			ଅନ୍ୟଥା
 			 {
 			   synerr( _("Input line too long\n"));
 			   FLEX_EXIT(EXIT_FAILURE);
 			 }
nmstr[yyleng - 2 - end_is_ws] = '\0';  /* chop trailing brace */

			ଯଦି ( (nmdefptr = ndlookup( nmstr )) == 0 )
				format_synerr(
					_( "undefined definition {%s}" ),
						nmstr );

			ଅନ୍ୟଥା
				{ /* push back name surrounded by ()'s */
				size_t len = strlen( nmdefptr );
                ଯଦି (end_is_ws)
                    unput(end_ch);

				ଯଦି ( ctrl.lex_compat || nmdefptr[0] == '^' ||
				     (len > 0 && nmdefptr[len - 1] == '$')
                     || (end_is_ws && trlcontxt && !sf_skip_ws()))
					{ /* don't use ()'s after all */
					PUT_BACK_STRING(nmdefptr, 0);

					ଯଦି ( nmdefptr[0] == '^' )
						BEGIN(CARETISBOL);
					}

				ଅନ୍ୟଥା
					{
					unput(')');
					PUT_BACK_STRING(nmdefptr, 0);
					unput('(');
					}
				}
			}

    "/*"        {
                    ଯଦି (sf_skip_ws())
                        yy_ଠେଲ_state(COMMENT_DISCARD);
                    ଅନ୍ୟଥା{
                        /* Push back the "*" and return "/" as usual. */
                        yyless(1);
                        ଫେରନ୍ତୁ '/';
                    }
                }

    "(?#"       {
                    ଯଦି (ctrl.lex_compat || ctrl.posix_compat){
                        /* Push back the "?#" and treat it like a normal parens. */
                        yyless(1);
                        sf_ଠେଲ(); 
                        ଫେରନ୍ତୁ '(';
                    }
                    ଅନ୍ୟଥା
                        yy_ଠେଲ_state(EXTENDED_COMMENT);
                }
    "(?"        {
                    sf_ଠେଲ();
                    ଯଦି (ctrl.lex_compat || ctrl.posix_compat)
                        /* Push back the "?" and treat it like a normal parens. */
                        yyless(1);
                    ଅନ୍ୟଥା
                        BEGIN(GROUP_WITH_PARAMS);
                    ଫେରନ୍ତୁ '(';
                }
    "("         sf_ଠେଲ(); ଫେରନ୍ତୁ '(';
    ")"         {
                    ଯଦି (sf_ଶୀର୍ଷ_ix > 0) {
                        sf_କାଢ଼();
                        ଫେରନ୍ତୁ ')';
                    } ଅନ୍ୟଥା
                        synerr(_("unbalanced parenthesis"));
                }

	[/|*+?.(){}]	ଫେରନ୍ତୁ (unsigned ଅକ୍ଷର) yytext[0];
	.		RETURNCHAR;
}


<SC>{
	{OPTWS}{NL}{OPTWS}	++linenum;	/* Allow blank lines & continuations */
	[,*]		ଫେରନ୍ତୁ (unsigned ଅକ୍ଷର) yytext[0];
	">"		BEGIN(SECT2); ଫେରନ୍ତୁ '>';
	">"/^		BEGIN(CARETISBOL); ଫେରନ୍ତୁ '>';
	{SCNAME}	RETURNNAME;
	.		{
			format_synerr( _( "bad <start condition>: %s" ),
				yytext );
			}
}

<CARETISBOL>"^"		BEGIN(SECT2); ଫେରନ୍ତୁ '^';


<QUOTE>{
	[^""\n]		RETURNCHAR;
	"\""		BEGIN(SECT2); ଫେରନ୍ତୁ '"';

	{NL}		{
			synerr( _( "missing quote" ) );
			BEGIN(SECT2);
			++linenum;
			ଫେରନ୍ତୁ '"';
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
	"^"/[^-\]\n]	BEGIN(CCL); ଫେରନ୍ତୁ '^';
	"^"/("-"|"]")	ଫେରନ୍ତୁ '^';
	.		BEGIN(CCL); RETURNCHAR;
}

<CCL>{
	-/[^\]\n]	ଫେରନ୍ତୁ '-';
	[^\]\n]		RETURNCHAR;
	"]"		BEGIN(SECT2); ଫେରନ୍ତୁ ']';
	.|{NL}		{
			synerr( _( "bad character class" ) );
			BEGIN(SECT2);
			ଫେରନ୍ତୁ ']';
			}
}

<FIRSTCCL,CCL>{
	"[:alnum:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_ALNUM;
	"[:alpha:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_ALPHA;
	"[:blank:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_BLANK;
	"[:cntrl:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_CNTRL;
	"[:digit:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_DIGIT;
	"[:graph:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_GRAPH;
	"[:lower:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_LOWER;
	"[:print:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_PRINT;
	"[:punct:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_PUNCT;
	"[:space:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_SPACE;
	"[:upper:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_UPPER;
	"[:xdigit:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_XDIGIT;

	"[:^alnum:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_ALNUM;
	"[:^alpha:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_ALPHA;
	"[:^blank:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_BLANK;
	"[:^cntrl:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_CNTRL;
	"[:^digit:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_DIGIT;
	"[:^graph:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_GRAPH;
	"[:^lower:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_LOWER;
	"[:^print:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_PRINT;
	"[:^punct:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_PUNCT;
	"[:^space:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_SPACE;
	"[:^upper:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_UPPER;
	"[:^xdigit:]"	BEGIN(CCL); ଫେରନ୍ତୁ CCE_NEG_XDIGIT;
	{CCL_ପଦସମଷ୍ଟି}	{
			format_synerr(
				_( "bad character class expression: %s" ),
					yytext );
			BEGIN(CCL); ଫେରନ୍ତୁ CCE_ALNUM;
			}
}

<ଅଙ୍କ_2>{
	[[:digit:]]+	{
			yylval = myctoi( yytext );
			ଫେରନ୍ତୁ ସଂଖ୍ୟା;
			}

	","		ଫେରନ୍ତୁ ',';
	"}"		{
			BEGIN(SECT2);
			ଯଦି ( ctrl.lex_compat || ctrl.posix_compat )
				ଫେରନ୍ତୁ END_REPEAT_POSIX;
			ଅନ୍ୟଥା
				ଫେରନ୍ତୁ END_REPEAT_FLEX;
			}

	.		{
			synerr( _( "bad character inside {}'s" ) );
			BEGIN(SECT2);
			ଫେରନ୍ତୁ '}';
			}

	{NL}		{
			synerr( _( "missing }" ) );
			BEGIN(SECT2);
			++linenum;
			ଫେରନ୍ତୁ '}';
			}
}


<PERCENT_BRACE_ACTION>{
	{OPTWS}"%}".*		bracelevel = 0;

	<ACTION>"/*"		ACTION_ECHO; yy_ଠେଲ_state( CODE_COMMENT );

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
			ଯଦି (ctrl.rewrite)
				context_call(yytext);
			ଅନ୍ୟଥା
				ACTION_ECHO;
        }
	}

    .       ACTION_ECHO;
	{NL}	{
		++linenum;
		ACTION_ECHO;
		ଯଦି (bracelevel <= 0 || (doing_codeblock && indented_code)) {
            ଯଦି ( doing_rule_action )
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
			ଯଦି (ctrl.rewrite)
				context_call(yytext);
			ଅନ୍ୟଥା
				ACTION_ECHO;
	}
	yyterminate\(\)|yyless\({FUNARGS}\) {
			add_action("]""]");
			add_action(yytext);
			add_action("[""[");
	}
	(yyin|yyout|yyextra|yyleng|yytext|yyflexdebug)/[^[:alnum:]_] {
			ଯଦି (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_CONTEXT_FORMAT");
			ଅନ୍ୟଥା
				ACTION_ECHO;
	}
	(yylineno|yycolumn)/[^[:alnum:]_] {
			ଯଦି (ctrl.rewrite)
				context_member(yytext, "M4_PROPERTY_BUFFERSTACK_CONTEXT_FORMAT");
			ଅନ୍ୟଥା
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
                ଯଦି (bracelevel <= 0) {
                   ଯଦି ( doing_rule_action )
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
	{NL}	++linenum; ACTION_ECHO; ଯଦି (bracelevel <= 0) { BEGIN(SECT2); } ଅନ୍ୟଥା { BEGIN(ACTION); }
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
			yylval = myesc( (unsigned ଅକ୍ଷର *) yytext );

			ଯଦି ( YY_START == FIRSTCCL )
				BEGIN(CCL);

			ଫେରନ୍ତୁ CHAR;
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


ପୂର୍ଣ୍ଣସଂଖ୍ୟା yywrap(ଶୂନ୍ୟ)
	{
	ଯଦି ( --num_input_files > 0 )
		{
		set_ନିବେଶ_file( *++ନିବେଶ_files );
		ଫେରନ୍ତୁ 0;
		}

	ଅନ୍ୟଥା
		ଫେରନ୍ତୁ 1;
	}


/* set_input_file - open the given file (if NULL, stdin) for scanning */

ଶୂନ୍ୟ set_ନିବେଶ_file( ଅକ୍ଷର *file )
	{
	ଯଦି ( file && strcmp( file, "-" ) )
		{
		infilename = xstrdup(file);
		yyin = fopen( infilename, "r" );

		ଯଦି ( yyin == ଖାଲି )
			lerr( _( "can't open %s: %s" ), file, strerror(errno));
		}

	ଅନ୍ୟଥା
		{
		yyin = stdin;
		infilename = xstrdup("<stdin>");
		}

	linenum = 1;
	}

ଶୂନ୍ୟ context_call(ଅକ୍ଷର *txt) {
	ଅଚଳ ଅକ୍ଷର *context_arg = skel_property("M4_PROPERTY_CONTEXT_ARG");

	/* if there's no such property, simply pass through */
	ଯଦି (context_arg == ଖାଲି) {
		add_action(txt);
	} ଅନ୍ୟଥା {
		ଅକ୍ଷର buf[BUFSIZ];

		/* otherwise, supply the context string as a final argument */
		ପ୍ରତିଜ୍ଞା(txt[strlen(txt)-1] == ')');
		strncpy(buf, txt, ଆକାର(buf));
		buf[strlen(buf)-1] = '\0';	/* remove trailing ) */
		add_action(buf);
		ଯଦି (txt[strlen(buf)-1] != '(') {
			add_action(", ");
		}
		add_action(context_arg);
		add_action(")");
	}
}

ଶୂନ୍ୟ context_member(ଅକ୍ଷର *txt, ଅଚଳ ଅକ୍ଷର *prop) {
	ଅଚଳ ଅକ୍ଷର *context_format = skel_property(prop);

	/* if there's no such property, simply pass through */
	ଯଦି (context_format == ଖାଲି) {
		add_action(txt);
	} ଅନ୍ୟଥା {
		ଅକ୍ଷର buf[128];
		snprintf(buf, ଆକାର(buf), context_format, txt);
		add_action(buf);
	}
}
