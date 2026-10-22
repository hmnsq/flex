/* parse.y - parser for flex input */

%token CHAR ਸੰਖਿਆ SECTEND SCDECL XSCDECL NAME PREVCCL EOF_OP
%token TOK_OPTION TOK_OUTFILE TOK_ਅਗੇਤਰ TOK_YYCLASS TOK_ਸਿਰਲੇਖ_FILE TOK_EXTRA_TYPE
%token TOK_TABLES_FILE TOK_YYLMAX TOK_NUMERIC TOK_YYDECL TOK_PREACTION TOK_POSTACTION
%token TOK_USERINIT TOK_EMIT TOK_BUFSIZE TOK_YYTERMINATE

%token CCE_ALNUM CCE_ALPHA CCE_BLANK CCE_CNTRL CCE_DIGIT CCE_ਗ੍ਰਾਫ
%token CCE_ਹੇਠਲਾ CCE_PRINT CCE_PUNCT CCE_SPACE CCE_ਉੱਤਲਾ CCE_XDIGIT

%token CCE_NEG_ALNUM CCE_NEG_ALPHA CCE_NEG_BLANK CCE_NEG_CNTRL CCE_NEG_DIGIT CCE_NEG_ਗ੍ਰਾਫ
%token CCE_NEG_ਹੇਠਲਾ CCE_NEG_PRINT CCE_NEG_PUNCT CCE_NEG_SPACE CCE_NEG_ਉੱਤਲਾ CCE_NEG_XDIGIT

%ਖੱਬੇ CCL_OP_DIFF CCL_OP_UNION

/*
 *POSIX and AT&T lex place the
 * precedence of the repeat operator, {}, below that of concatenation.
 * Thus, ab{3} is ababab.  Most other POSIX utilities use an Extended
 * Regular Expression (ERE) precedence that has the repeat operator
 * higher than concatenation.  This causes ab{3} to yield abbb.
 *
 * In order to support the POSIX and AT&T precedence and the flex
 * precedence we define two token sets for the begin and end tokens of
 * the repeat operator, '{' and '}'.  The lexical scanner chooses
 * which tokens to return based on whether posix_compat or lex_compat
 * are specified. Specifying either posix_compat or lex_compat will
 * cause flex to parse scanner files as per the AT&T and
 * POSIX-mandated behavior.
 */

%token BEGIN_REPEAT_POSIX ਸਿਰਾ_REPEAT_POSIX BEGIN_REPEAT_FLEX ਸਿਰਾ_REPEAT_FLEX


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

#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tables.h"

ਪੂਰਨ pat, scnum, eps, headcnt, trailcnt, lastchar, i, rulelen;
ਸਥਿਰ ਪੂਰਨ currccl;
bool trlcontxt;
ਸਥਿਰ bool sc_is_exclusive, cclsorted, varlength, variable_trail_ਨਿਯਮ;

ਪੂਰਨ *scon_stk;
ਪੂਰਨ scon_stk_ptr;

ਸਥਿਰ ਪੂਰਨ madeany = false;  /* whether we've made the '.' character class */
ਸਥਿਰ ਪੂਰਨ ccldot, cclany;
ਪੂਰਨ ਪਿਛਲਾ_continued_action;	/* whether the previous rule's action was '|' */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ format_warn3(fmt, a1, a2) \
	ਕਰੋ{ \
        ਅੱਖਰ fw3_ਸੁਨੇਹਾ[MAXLINE];\
        snprintf( fw3_ਸੁਨੇਹਾ, MAXLINE,(fmt), (a1), (a2) );\
        lwarn( fw3_ਸੁਨੇਹਾ );\
	}ਜਦੋਂ(0)

/* Expand a POSIX character class expression. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCL_ਵਿਅੰਜਕ(func) \
	ਕਰੋ{ \
	ਪੂਰਨ c; \
	ਲਈ ( c = 0; c < ctrl.csize; ++c ) \
		ਜੇ ( isascii(c) && func(c) ) \
			ccladd( currccl, c ); \
	}ਜਦੋਂ(0)

/* negated class */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCL_NEG_ਵਿਅੰਜਕ(func) \
	ਕਰੋ{ \
	ਪੂਰਨ c; \
	ਲਈ ( c = 0; c < ctrl.csize; ++c ) \
		ਜੇ ( !func(c) ) \
			ccladd( currccl, c ); \
	}ਜਦੋਂ(0)

/* While POSIX defines isblank(), it's not ANSI C. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_BLANK(c) ((c) == ' ' || (c) == '\t')

/* On some over-ambitious machines, such as DEC Alpha's, the default
 * token type is "long" instead of "int"; this leads to problems with
 * declaring yylval in flexdef.h.  But so far, all the yacc's I've seen
 * wrap their definitions of YYSTYPE with "#ifndef YYSTYPE"'s, so the
 * following should ensure that the default token type is "int".
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ YYSTYPE ਪੂਰਨ

%}

%%
goal		:  initlex sect1 sect1end sect2 initforrule
			{ /* add default rule */
			ਪੂਰਨ def_ਨਿਯਮ;

			pat = cclinit();
			cclnegate( pat );

			def_ਨਿਯਮ = mkstate( -pat );

			/* Remember the number of the default rule so we
			 * don't generate "can't match" warnings for it.
			 */
			default_ਨਿਯਮ = ਅੰਕ_ਨਿਯਮਾਂ;

			ਅੰਤ_ਨਿਯਮ( def_ਨਿਯਮ, false, 0, 0, 0);

			ਲਈ ( i = 1; i <= lastsc; ++i )
				scset[i] = mkbranch( scset[i], def_ਨਿਯਮ );

			ਜੋੜੋ_action("]]");

			ਜੇ ( ctrl.spprdflt )
				ਜੋੜੋ_action(
				"M4_HOOK_FATAL_ERROR(\"flex scanner jammed\")");
			ਨਹੀਂਤਾਂ {
			    ਜੋੜੋ_action("M4_HOOK_ECHO");
			}

			ਜੋੜੋ_action( "\n\tM4_HOOK_STATE_CASE_BREAK\n" );
			}
		;

initlex		:
			{ /* initialize for processing rules */

			/* Create default DFA start condition. */
			scinstal( "INITIAL", false );
			}
		;

sect1		:  sect1 startconddecl namelist1
		|  sect1 options
		|
		|  error
			{ synerr( _("unknown error processing section 1") ); }
		;

sect1end	:  SECTEND
			{
			check_options();
			scon_stk = allocate_integer_array( lastsc + 1 );
			scon_stk_ptr = 0;
			}
		;

startconddecl	:  SCDECL
			{ sc_is_exclusive = false; }

		|  XSCDECL
			{ sc_is_exclusive = true; }
		;

namelist1	:  namelist1 NAME
			{ scinstal( nmstr, sc_is_exclusive ); }

		|  NAME
			{ scinstal( nmstr, sc_is_exclusive ); }

		|  error
			{ synerr( _("bad start condition list") ); }
		;

options		:  TOK_OPTION optionlist
		;

optionlist	:  optionlist option
		|
		;

option		:  TOK_OUTFILE '=' NAME
			{
			env.outfilename = xstrdup(nmstr);
			env.did_outfilename = 1;
			}
		|  TOK_EXTRA_TYPE '=' NAME
			{ extra_type = xstrdup(nmstr); }
		|  TOK_ਅਗੇਤਰ '=' NAME
			{ ctrl.ਅਗੇਤਰ = xstrdup(nmstr);
                          ਜੇ (strchr(ctrl.ਅਗੇਤਰ, '[') || strchr(ctrl.ਅਗੇਤਰ, ']'))
                              flexerror(_("Prefix must not contain [ or ]")); }
		|  TOK_YYCLASS '=' NAME
			{ ctrl.yyclass = xstrdup(nmstr); }
		|  TOK_ਸਿਰਲੇਖ_FILE '=' NAME
			{ env.headerfilename = xstrdup(nmstr); }
		|  TOK_YYLMAX '=' TOK_NUMERIC
			{ ctrl.yylmax = nmval; }
		|  TOK_YYDECL '=' NAME
			{ ctrl.yydecl = xstrdup(nmstr); }
		|  TOK_PREACTION '=' NAME
			{ ctrl.preaction = xstrdup(nmstr); }
		|  TOK_POSTACTION '=' NAME
			{ ctrl.postaction = xstrdup(nmstr); }
		|  TOK_BUFSIZE '=' TOK_NUMERIC
			{ ctrl.bufsize = nmval; }
		|  TOK_EMIT '=' NAME
			{ ctrl.emit = xstrdup(nmstr); backend_by_name(ctrl.emit); }
		|  TOK_USERINIT '=' NAME
			{ ctrl.userinit = xstrdup(nmstr); }
		|  TOK_YYTERMINATE '=' NAME
			{ ctrl.yyterminate = xstrdup(nmstr); }
		|  TOK_TABLES_FILE '=' NAME
        		{ tablesext = true; tablesfilename = xstrdup(nmstr); }
		;

sect2		:  sect2 scon initforrule flexrule '\n'
			{ scon_stk_ptr = $2; }
		|  sect2 scon '{' sect2 '}'
			{ scon_stk_ptr = $2; }
		|
		;

initforrule	:
			{
			/* Initialize for a parse of one rule. */
			trlcontxt = variable_trail_ਨਿਯਮ = varlength = false;
			trailcnt = headcnt = rulelen = 0;
			current_state_type = STATE_ਸਾਧਾਰਨ;
			ਪਿਛਲਾ_continued_action = continued_action;
			ਵਿੱਚ_ਨਿਯਮ = true;

			new_ਨਿਯਮ();
			}
		;

flexrule	:  '^' ਨਿਯਮ
			{
			pat = $2;
			ਅੰਤ_ਨਿਯਮ( pat, variable_trail_ਨਿਯਮ,
				headcnt, trailcnt , ਪਿਛਲਾ_continued_action);

			ਜੇ ( scon_stk_ptr > 0 )
				{
				ਲਈ ( i = 1; i <= scon_stk_ptr; ++i )
					scbol[scon_stk[i]] =
						mkbranch( scbol[scon_stk[i]],
								pat );
				}

			ਨਹੀਂਤਾਂ
				{
				/* Add to all non-exclusive start conditions,
				 * including the default (0) start condition.
				 */

				ਲਈ ( i = 1; i <= lastsc; ++i )
					ਜੇ ( ! scxclu[i] )
						scbol[i] = mkbranch( scbol[i],
									pat );
				}

			ਜੇ ( ! bol_needed )
				{
				bol_needed = true;

				ਜੇ ( env.performance_hint > 1 )
					pinpoint_ਸੁਨੇਹਾ(
			"'^' operator results in sub-optimal performance" );
				}
			}

		|  ਨਿਯਮ
			{
			pat = $1;
			ਅੰਤ_ਨਿਯਮ( pat, variable_trail_ਨਿਯਮ,
				headcnt, trailcnt , ਪਿਛਲਾ_continued_action);

			ਜੇ ( scon_stk_ptr > 0 )
				{
				ਲਈ ( i = 1; i <= scon_stk_ptr; ++i )
					scset[scon_stk[i]] =
						mkbranch( scset[scon_stk[i]],
								pat );
				}

			ਨਹੀਂਤਾਂ
				{
				ਲਈ ( i = 1; i <= lastsc; ++i )
					ਜੇ ( ! scxclu[i] )
						scset[i] =
							mkbranch( scset[i],
								pat );
				}
			}

		|  EOF_OP
			{
			ਜੇ ( scon_stk_ptr > 0 )
				build_eof_action();
	
			ਨਹੀਂਤਾਂ
				{
				/* This EOF applies to all start conditions
				 * which don't already have EOF actions.
				 */
				ਲਈ ( i = 1; i <= lastsc; ++i )
					ਜੇ ( ! sceof[i] )
						scon_stk[++scon_stk_ptr] = i;

				ਜੇ ( scon_stk_ptr == 0 )
					lwarn(
			"all start conditions already have <<EOF>> rules" );

				ਨਹੀਂਤਾਂ
					build_eof_action();
				}
			}

		|  error
			{ synerr( _("unrecognized rule") ); }
		;

scon_stk_ptr	:
			{ $$ = scon_stk_ptr; }
		;

scon		:  '<' scon_stk_ptr namelist2 '>'
			{ $$ = $2; }

		|  '<' '*' '>'
			{
			$$ = scon_stk_ptr;

			ਲਈ ( i = 1; i <= lastsc; ++i )
				{
				ਪੂਰਨ j;

				ਲਈ ( j = 1; j <= scon_stk_ptr; ++j )
					ਜੇ ( scon_stk[j] == i )
						ਰੋਕੋ;

				ਜੇ ( j > scon_stk_ptr )
					scon_stk[++scon_stk_ptr] = i;
				}
			}

		|
			{ $$ = scon_stk_ptr; }
		;

namelist2	:  namelist2 ',' sconname

		|  sconname

		|  error
			{ synerr( _("bad start condition list") ); }
		;

sconname	:  NAME
			{
			ਜੇ ( (scnum = sclookup( nmstr )) == 0 )
				format_pinpoint_ਸੁਨੇਹਾ(
					"undeclared start condition %s",
					nmstr );
			ਨਹੀਂਤਾਂ
				{
				ਲਈ ( i = 1; i <= scon_stk_ptr; ++i )
					ਜੇ ( scon_stk[i] == scnum )
						{
						format_warn(
							"<%s> specified twice",
							scname[scnum] );
						ਰੋਕੋ;
						}

				ਜੇ ( i > scon_stk_ptr )
					scon_stk[++scon_stk_ptr] = scnum;
				}
			}
		;

ਨਿਯਮ		:  re2 re
			{
			ਜੇ ( transchar[lastst[$2]] != SYM_EPSILON )
				/* Provide final transition \now/ so it
				 * will be marked as a trailing context
				 * state.
				 */
				$2 = link_machines( $2,
						mkstate( SYM_EPSILON ) );

			mark_beginning_as_ਸਾਧਾਰਨ( $2 );
			current_state_type = STATE_ਸਾਧਾਰਨ;

			ਜੇ ( ਪਿਛਲਾ_continued_action )
				{
				/* We need to treat this as variable trailing
				 * context so that the backup does not happen
				 * in the action but before the action switch
				 * statement.  If the backup happens in the
				 * action, then the rules "falling into" this
				 * one's action will *also* do the backup,
				 * erroneously.
				 */
				ਜੇ ( ! varlength || headcnt != 0 )
					lwarn(
		"trailing context made variable due to preceding '|' action" );

				/* Mark as variable. */
				varlength = true;
				headcnt = 0;

				}

			ਜੇ ( ctrl.lex_compat || (varlength && headcnt == 0) )
				{ /* variable trailing context rule */
				/* Mark the first part of the rule as the
				 * accepting "head" part of a trailing
				 * context rule.
				 *
				 * By the way, we didn't do this at the
				 * beginning of this production because back
				 * then current_state_type was set up for a
				 * trail rule, and add_accept() can create
				 * a new state ...
				 */
				ਜੋੜੋ_accept( $1,
					ਅੰਕ_ਨਿਯਮਾਂ | YY_TRAILING_ਸਿਰ_ਨਕਾਬ );
				variable_trail_ਨਿਯਮ = true;
				}
			
			ਨਹੀਂਤਾਂ
				trailcnt = rulelen;

			$$ = link_machines( $1, $2 );
			}

		|  re2 re '$'
			{ synerr( _("trailing context used twice") ); }

		|  re '$'
			{
			headcnt = 0;
			trailcnt = 1;
			rulelen = 1;
			varlength = false;

			current_state_type = STATE_TRAILING_CONTEXT;

			ਜੇ ( trlcontxt )
				{
				synerr( _("trailing context used twice") );
				$$ = mkstate( SYM_EPSILON );
				}

			ਨਹੀਂਤਾਂ ਜੇ ( ਪਿਛਲਾ_continued_action )
				{
				/* See the comment in the rule for "re2 re"
				 * above.
				 */
				lwarn(
		"trailing context made variable due to preceding '|' action" );

				varlength = true;
				}

			ਜੇ ( ctrl.lex_compat || varlength )
				{
				/* Again, see the comment in the rule for
				 * "re2 re" above.
				 */
				ਜੋੜੋ_accept( $1,
					ਅੰਕ_ਨਿਯਮਾਂ | YY_TRAILING_ਸਿਰ_ਨਕਾਬ );
				variable_trail_ਨਿਯਮ = true;
				}

			trlcontxt = true;

			eps = mkstate( SYM_EPSILON );
			$$ = link_machines( $1,
				link_machines( eps, mkstate( '\n' ) ) );
			}

		|  re
			{
			$$ = $1;

			ਜੇ ( trlcontxt )
				{
				ਜੇ ( ctrl.lex_compat || (varlength && headcnt == 0) )
					/* Both head and trail are
					 * variable-length.
					 */
					variable_trail_ਨਿਯਮ = true;
				ਨਹੀਂਤਾਂ
					trailcnt = rulelen;
				}
			}
		;


re		:  re '|' series
			{
			varlength = true;
			$$ = mkor( $1, $3 );
			}

		|  series
			{ $$ = $1; }
		;


re2		:  re '/'
			{
			/* This rule is written separately so the
			 * reduction will occur before the trailing
			 * series is parsed.
			 */

			ਜੇ ( trlcontxt )
				synerr( _("trailing context used twice") );
			ਨਹੀਂਤਾਂ
				trlcontxt = true;

			ਜੇ ( varlength )
				/* We hope the trailing context is
				 * fixed-length.
				 */
				varlength = false;
			ਨਹੀਂਤਾਂ
				headcnt = rulelen;

			rulelen = 0;

			current_state_type = STATE_TRAILING_CONTEXT;
			$$ = $1;
			}
		;

series		:  series singleton
			{
			/* This is where concatenation of adjacent patterns
			 * gets done.
			 */
			$$ = link_machines( $1, $2 );
			}

		|  singleton
			{ $$ = $1; }

		|  series BEGIN_REPEAT_POSIX ਸੰਖਿਆ ',' ਸੰਖਿਆ ਸਿਰਾ_REPEAT_POSIX
			{
			varlength = true;

			ਜੇ ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			ਨਹੀਂਤਾਂ
				{
				ਜੇ ( $3 == 0 )
					{
					ਜੇ ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					ਨਹੀਂਤਾਂ
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				ਨਹੀਂਤਾਂ
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  series BEGIN_REPEAT_POSIX ਸੰਖਿਆ ',' ਸਿਰਾ_REPEAT_POSIX
			{
			varlength = true;

			ਜੇ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			ਨਹੀਂਤਾਂ
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  series BEGIN_REPEAT_POSIX ਸੰਖਿਆ ਸਿਰਾ_REPEAT_POSIX
			{
			/* The series could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			ਜੇ ( $3 <= 0 )
				{
				  synerr( _("iteration value must be positive")
					  );
				$$ = $1;
				}

			ਨਹੀਂਤਾਂ
				$$ = link_machines( $1,
						copysingl( $1, $3 - 1 ) );
			}

		;

singleton	:  singleton '*'
			{
			varlength = true;

			$$ = mkclos( $1 );
			}

		|  singleton '+'
			{
			varlength = true;
			$$ = mkposcl( $1 );
			}

		|  singleton '?'
			{
			varlength = true;
			$$ = mkopt( $1 );
			}

		|  singleton BEGIN_REPEAT_FLEX ਸੰਖਿਆ ',' ਸੰਖਿਆ ਸਿਰਾ_REPEAT_FLEX
			{
			varlength = true;

			ਜੇ ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			ਨਹੀਂਤਾਂ
				{
				ਜੇ ( $3 == 0 )
					{
					ਜੇ ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					ਨਹੀਂਤਾਂ
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				ਨਹੀਂਤਾਂ
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  singleton BEGIN_REPEAT_FLEX ਸੰਖਿਆ ',' ਸਿਰਾ_REPEAT_FLEX
			{
			varlength = true;

			ਜੇ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			ਨਹੀਂਤਾਂ
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  singleton BEGIN_REPEAT_FLEX ਸੰਖਿਆ ਸਿਰਾ_REPEAT_FLEX
			{
			/* The singleton could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			ਜੇ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			ਨਹੀਂਤਾਂ
				$$ = link_machines( $1,
						copysingl( $1, $3 - 1 ) );
			}

		|  '.'
			{
			ਜੇ ( ! madeany )
				{
				/* Create the '.' character class. */
                    ccldot = cclinit();
                    ccladd( ccldot, '\n' );
                    cclnegate( ccldot );

                    ਜੇ ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[ccldot],
                            ccllen[ccldot], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				/* Create the (?s:'.') character class. */
                    cclany = cclinit();
                    cclnegate( cclany );

                    ਜੇ ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[cclany],
                            ccllen[cclany], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				madeany = true;
				}

			++rulelen;

            ਜੇ (sf_dot_all())
                $$ = mkstate( -cclany );
            ਨਹੀਂਤਾਂ
                $$ = mkstate( -ccldot );
			}

		|  fullccl
			{
				/* Sort characters for fast searching.
				 */
				qsort( ccltbl + cclmap[$1], (size_t) ccllen[$1], ਆਕਾਰ (*ccltbl), cclcmp );

			ਜੇ ( ctrl.useecs )
				mkeccl( ccltbl + cclmap[$1], ccllen[$1],
					nextecm, ecgroup, ctrl.csize, ctrl.csize);

			++rulelen;

			ਜੇ (ccl_has_nl[$1])
				ਨਿਯਮ_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  PREVCCL
			{
			++rulelen;

			ਜੇ (ccl_has_nl[$1])
				ਨਿਯਮ_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  '"' string '"'
			{ $$ = $2; }

		|  '(' re ')'
			{ $$ = $2; }

		|  CHAR
			{
			++rulelen;

			ਜੇ ($1 == nlch)
				ਨਿਯਮ_has_nl[num_rules] = true;

            ਜੇ (sf_case_ins() && has_case($1))
                /* create an alternation, as in (a|A) */
                $$ = mkor (mkstate($1), mkstate(ਉਲਟ_case($1)));
            ਨਹੀਂਤਾਂ
                $$ = mkstate( $1 );
			}
		;
fullccl:
        fullccl CCL_OP_DIFF  braceccl  { $$ = ccl_ਸੈੱਟ_diff  ($1, $3); }
    |   fullccl CCL_OP_UNION braceccl  { $$ = ccl_ਸੈੱਟ_union ($1, $3); }
    |   braceccl
    ;

braceccl: 

            '[' ccl ']' { $$ = $2; }

		|  '[' '^' ccl ']'
			{
			cclnegate( $3 );
			$$ = $3;
			}
		;

ccl		:  ccl CHAR '-' CHAR
			{

			ਜੇ (sf_case_ins())
			  {

			    /* If one end of the range has case and the other
			     * does not, or the cases are different, then we're not
			     * sure what range the user is trying to express.
			     * Examples: [@-z] or [S-t]
			     */
			    ਜੇ (has_case ($2) != has_case ($4)
				     || (has_case ($2) && (b_islower ($2) != b_islower ($4)))
				     || (has_case ($2) && (b_isupper ($2) != b_isupper ($4))))
			      format_warn3 (
			      _("the character range [%c-%c] is ambiguous in a case-insensitive scanner"),
					    $2, $4);

			    /* If the range spans uppercase characters but not
			     * lowercase (or vice-versa), then should we automatically
			     * include lowercase characters in the range?
			     * Example: [@-_] spans [a-z] but not [A-Z]
			     */
			    ਨਹੀਂਤਾਂ ਜੇ (!has_case ($2) && !has_case ($4) && !range_covers_case ($2, $4))
			      format_warn3 (
			      _("the character range [%c-%c] is ambiguous in a case-insensitive scanner"),
					    $2, $4);
			  }

			ਜੇ ( $2 > $4 )
				synerr( _("negative range in character class") );

			ਨਹੀਂਤਾਂ
				{
				ਲਈ ( i = $2; i <= $4; ++i )
					ccladd( $1, i );

				/* Keep track if this ccl is staying in
				 * alphabetical order.
				 */
				cclsorted = cclsorted && ($2 > lastchar);
				lastchar = $4;

                /* Do it again for upper/lowercase */
                ਜੇ (sf_case_ins() && has_case($2) && has_case($4)){
                    $2 = ਉਲਟ_case ($2);
                    $4 = ਉਲਟ_case ($4);
                    
                    ਲਈ ( i = $2; i <= $4; ++i )
                        ccladd( $1, i );

                    cclsorted = cclsorted && ($2 > lastchar);
                    lastchar = $4;
                }

				}

			$$ = $1;
			}

		|  ccl CHAR
			{
			ccladd( $1, $2 );
			cclsorted = cclsorted && ($2 > lastchar);
			lastchar = $2;

            /* Do it again for upper/lowercase */
            ਜੇ (sf_case_ins() && has_case($2)){
                $2 = ਉਲਟ_case ($2);
                ccladd ($1, $2);

                cclsorted = cclsorted && ($2 > lastchar);
                lastchar = $2;
            }

			$$ = $1;
			}

		|  ccl ccl_ਵਿਅੰਜਕ
			{
			/* Too hard to properly maintain cclsorted. */
			cclsorted = false;
			$$ = $1;
			}

		|
			{
			cclsorted = true;
			lastchar = 0;
			currccl = $$ = cclinit();
			}
		;

ccl_ਵਿਅੰਜਕ:	   
           CCE_ALNUM	{ CCL_ਵਿਅੰਜਕ(ਅੱਖਰ_ਜਾਂ_ਅੰਕ); }
		|  CCE_ALPHA	{ CCL_ਵਿਅੰਜਕ(ਅੱਖਰ_ਹੈ); }
		|  CCE_BLANK	{ CCL_ਵਿਅੰਜਕ(IS_BLANK); }
		|  CCE_CNTRL	{ CCL_ਵਿਅੰਜਕ(iscntrl); }
		|  CCE_DIGIT	{ CCL_ਵਿਅੰਜਕ(ਅੰਕ_ਹੈ); }
		|  CCE_ਗ੍ਰਾਫ	{ CCL_ਵਿਅੰਜਕ(isgraph); }
		|  CCE_ਹੇਠਲਾ	{ 
                          CCL_ਵਿਅੰਜਕ(islower);
                          ਜੇ (sf_case_ins())
                              CCL_ਵਿਅੰਜਕ(isupper);
                        }
		|  CCE_PRINT	{ CCL_ਵਿਅੰਜਕ(isprint); }
		|  CCE_PUNCT	{ CCL_ਵਿਅੰਜਕ(ispunct); }
		|  CCE_SPACE	{ CCL_ਵਿਅੰਜਕ(ਖਾਲੀ_ਥਾਂ_ਹੈ); }
		|  CCE_XDIGIT	{ CCL_ਵਿਅੰਜਕ(isxdigit); }
		|  CCE_ਉੱਤਲਾ	{
                    CCL_ਵਿਅੰਜਕ(isupper);
                    ਜੇ (sf_case_ins())
                        CCL_ਵਿਅੰਜਕ(islower);
				}

        |  CCE_NEG_ALNUM	{ CCL_NEG_ਵਿਅੰਜਕ(ਅੱਖਰ_ਜਾਂ_ਅੰਕ); }
		|  CCE_NEG_ALPHA	{ CCL_NEG_ਵਿਅੰਜਕ(ਅੱਖਰ_ਹੈ); }
		|  CCE_NEG_BLANK	{ CCL_NEG_ਵਿਅੰਜਕ(IS_BLANK); }
		|  CCE_NEG_CNTRL	{ CCL_NEG_ਵਿਅੰਜਕ(iscntrl); }
		|  CCE_NEG_DIGIT	{ CCL_NEG_ਵਿਅੰਜਕ(ਅੰਕ_ਹੈ); }
		|  CCE_NEG_ਗ੍ਰਾਫ	{ CCL_NEG_ਵਿਅੰਜਕ(isgraph); }
		|  CCE_NEG_PRINT	{ CCL_NEG_ਵਿਅੰਜਕ(isprint); }
		|  CCE_NEG_PUNCT	{ CCL_NEG_ਵਿਅੰਜਕ(ispunct); }
		|  CCE_NEG_SPACE	{ CCL_NEG_ਵਿਅੰਜਕ(ਖਾਲੀ_ਥਾਂ_ਹੈ); }
		|  CCE_NEG_XDIGIT	{ CCL_NEG_ਵਿਅੰਜਕ(isxdigit); }
		|  CCE_NEG_ਹੇਠਲਾ	{ 
				ਜੇ ( sf_case_ins() )
					lwarn(_("[:^lower:] is ambiguous in case insensitive scanner"));
				ਨਹੀਂਤਾਂ
					CCL_NEG_ਵਿਅੰਜਕ(islower);
				}
		|  CCE_NEG_ਉੱਤਲਾ	{
				ਜੇ ( sf_case_ins() )
					lwarn(_("[:^upper:] ambiguous in case insensitive scanner"));
				ਨਹੀਂਤਾਂ
					CCL_NEG_ਵਿਅੰਜਕ(isupper);
				}
		;
		
string		:  string CHAR
			{
			ਜੇ ( $2 == nlch )
				ਨਿਯਮ_has_nl[num_rules] = true;

			++rulelen;

            ਜੇ (sf_case_ins() && has_case($2))
                $$ = mkor (mkstate($2), mkstate(ਉਲਟ_case($2)));
            ਨਹੀਂਤਾਂ
                $$ = mkstate ($2);

			$$ = link_machines( $1, $$);
			}

		|
			{ $$ = mkstate( SYM_EPSILON ); }
		;

%%


/* build_eof_action - build the "<<EOF>>" action for the active start
 *                    conditions
 */

ਖਾਲੀ build_eof_action(ਖਾਲੀ)
	{
	ਪੂਰਨ i;
	ਅੱਖਰ action_ਪਾਠ[MAXLINE];

	ਲਈ ( i = 1; i <= scon_stk_ptr; ++i )
		{
		ਜੇ ( sceof[scon_stk[i]] )
			format_pinpoint_ਸੁਨੇਹਾ(
				"multiple <<EOF>> rules for start condition %s",
				scname[scon_stk[i]] );

		ਨਹੀਂਤਾਂ
			{
			sceof[scon_stk[i]] = true;

			ਜੇ (ਪਿਛਲਾ_continued_action /* && previous action was regular */)
				ਜੋੜੋ_action("YY_RULE_SETUP\n");

			snprintf( action_ਪਾਠ, ਆਕਾਰ(action_ਪਾਠ), "M4_HOOK_EOF_STATE_CASE_ARM(%s)\n",
				scname[scon_stk[i]] );
			ਜੋੜੋ_action( action_ਪਾਠ );
			}
		}

	ਸਤਰ_directive_ਬਾਹਰਲਾ(ਨਿਰਾ, infilename, linenum);
        ਜੋੜੋ_action("[[");

	/* This isn't a normal rule after all - don't count it as
	 * such, so we don't have any holes in the rule numbering
	 * (which make generating "rule can never match" warnings
	 * more difficult.
	 */
	--num_rules;
	++ਅੰਕ_eof_ਨਿਯਮਾਂ;
	}


/* format_synerr - write out formatted syntax error */

ਖਾਲੀ format_synerr( ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ਅਚਲ ਅੱਖਰ arg[] )
	{
	ਅੱਖਰ errmsg[MAXLINE];

	(ਖਾਲੀ) snprintf( errmsg, ਆਕਾਰ(errmsg), ਸੁਨੇਹਾ, arg );
	synerr( errmsg );
	}


/* synerr - report a syntax error */

ਖਾਲੀ synerr( ਅਚਲ ਅੱਖਰ *str )
	{
	syntaxerror = true;
	pinpoint_ਸੁਨੇਹਾ( str );
	}


/* format_warn - write out formatted warning */

ਖਾਲੀ format_warn( ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ਅਚਲ ਅੱਖਰ arg[] )
	{
	ਅੱਖਰ warn_ਸੁਨੇਹਾ[MAXLINE];

	snprintf( warn_ਸੁਨੇਹਾ, ਆਕਾਰ(warn_ਸੁਨੇਹਾ), ਸੁਨੇਹਾ, arg );
	lwarn( warn_ਸੁਨੇਹਾ );
	}


/* lwarn - report a warning, unless -w was given */

ਖਾਲੀ lwarn( ਅਚਲ ਅੱਖਰ *str )
	{
	ਸਤਰ_warning( str, linenum );
	}

/* format_pinpoint_message - write out a message formatted with one string,
 *			     pinpointing its location
 */

ਖਾਲੀ format_pinpoint_ਸੁਨੇਹਾ( ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ਅਚਲ ਅੱਖਰ arg[] )
	{
	ਅੱਖਰ errmsg[MAXLINE*2];

	snprintf( errmsg, ਆਕਾਰ(errmsg), ਸੁਨੇਹਾ, arg );
	pinpoint_ਸੁਨੇਹਾ( errmsg );
	}


/* pinpoint_message - write out a message, pinpointing its location */

ਖਾਲੀ pinpoint_ਸੁਨੇਹਾ( ਅਚਲ ਅੱਖਰ *str )
	{
	ਸਤਰ_pinpoint( str, linenum );
	}


/* line_warning - report a warning at a given line, unless -w was given */

ਖਾਲੀ ਸਤਰ_warning( ਅਚਲ ਅੱਖਰ *str, ਪੂਰਨ ਸਤਰ )
	{
	ਅੱਖਰ warning[MAXLINE*2];

	ਜੇ ( ! env.nowarn )
		{
		snprintf( warning, ਆਕਾਰ(warning), "warning, %s", str );
		ਸਤਰ_pinpoint( warning, ਸਤਰ );
		}
	}


/* line_pinpoint - write out a message, pinpointing it at the given line */

ਖਾਲੀ ਸਤਰ_pinpoint( ਅਚਲ ਅੱਖਰ *str, ਪੂਰਨ ਸਤਰ )
	{
	fprintf( stderr, "%s:%d: %s\n", infilename, ਸਤਰ, str );
	}


/* yyerror - eat up an error message from the parser;
 *	     currently, messages are ignore
 */

ਖਾਲੀ yyerror( ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ )
	{
		(ਖਾਲੀ)ਸੁਨੇਹਾ;
	}
