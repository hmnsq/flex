/* parse.y - parser for flex input */

%token CHAR ಸಂಖ್ಯೆ SECTEND SCDECL XSCDECL NAME PREVCCL EOF_OP
%token TOK_OPTION TOK_OUTFILE TOK_ಪೂರ್ವಪ್ರತ್ಯಯ TOK_YYCLASS TOK_ಶೀರ್ಷಿಕೆ_FILE TOK_EXTRA_TYPE
%token TOK_TABLES_FILE TOK_YYLMAX TOK_NUMERIC TOK_YYDECL TOK_PREACTION TOK_POSTACTION
%token TOK_USERINIT TOK_EMIT TOK_BUFSIZE TOK_YYTERMINATE

%token CCE_ALNUM CCE_ALPHA CCE_BLANK CCE_CNTRL CCE_DIGIT CCE_ನಕ್ಷೆ
%token CCE_ಅಧೋ CCE_PRINT CCE_PUNCT CCE_SPACE CCE_ಊರ್ಧ್ವ CCE_XDIGIT

%token CCE_NEG_ALNUM CCE_NEG_ALPHA CCE_NEG_BLANK CCE_NEG_CNTRL CCE_NEG_DIGIT CCE_NEG_ನಕ್ಷೆ
%token CCE_NEG_ಅಧೋ CCE_NEG_PRINT CCE_NEG_PUNCT CCE_NEG_SPACE CCE_NEG_ಊರ್ಧ್ವ CCE_NEG_XDIGIT

%ಎಡ CCL_OP_DIFF CCL_OP_UNION

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

%token BEGIN_REPEAT_POSIX ಕೊನೆ_REPEAT_POSIX BEGIN_REPEAT_FLEX ಕೊನೆ_REPEAT_FLEX


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

#ಅನ್ತರ್ಭಾವ "flexdef.h"
#ಅನ್ತರ್ಭಾವ "tables.h"

ಪೂರ್ಣಾಂಕ pat, scnum, eps, headcnt, trailcnt, lastchar, i, rulelen;
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ currccl;
bool trlcontxt;
ಸ್ಥಿರ bool sc_is_exclusive, cclsorted, varlength, variable_trail_ನಿಯಮ;

ಪೂರ್ಣಾಂಕ *scon_stk;
ಪೂರ್ಣಾಂಕ scon_stk_ptr;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ madeany = false;  /* whether we've made the '.' character class */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ccldot, cclany;
ಪೂರ್ಣಾಂಕ ಹಿಂದಿನ_continued_action;	/* whether the previous rule's action was '|' */

#ವ್ಯಾಖ್ಯಾನಿಸು format_warn3(fmt, a1, a2) \
	ಮಾಡು{ \
        ಅಕ್ಷರ fw3_ಸಂದೇಶ[MAXLINE];\
        snprintf( fw3_ಸಂದೇಶ, MAXLINE,(fmt), (a1), (a2) );\
        lwarn( fw3_ಸಂದೇಶ );\
	}ಆಗ(0)

/* Expand a POSIX character class expression. */
#ವ್ಯಾಖ್ಯಾನಿಸು CCL_ಅಭಿವ್ಯಕ್ತಿ(func) \
	ಮಾಡು{ \
	ಪೂರ್ಣಾಂಕ c; \
	ಗಾಗಿ ( c = 0; c < ctrl.csize; ++c ) \
		ಆದರೆ ( isascii(c) && func(c) ) \
			ccladd( currccl, c ); \
	}ಆಗ(0)

/* negated class */
#ವ್ಯಾಖ್ಯಾನಿಸು CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(func) \
	ಮಾಡು{ \
	ಪೂರ್ಣಾಂಕ c; \
	ಗಾಗಿ ( c = 0; c < ctrl.csize; ++c ) \
		ಆದರೆ ( !func(c) ) \
			ccladd( currccl, c ); \
	}ಆಗ(0)

/* While POSIX defines isblank(), it's not ANSI C. */
#ವ್ಯಾಖ್ಯಾನಿಸು IS_BLANK(c) ((c) == ' ' || (c) == '\t')

/* On some over-ambitious machines, such as DEC Alpha's, the default
 * token type is "long" instead of "int"; this leads to problems with
 * declaring yylval in flexdef.h.  But so far, all the yacc's I've seen
 * wrap their definitions of YYSTYPE with "#ifndef YYSTYPE"'s, so the
 * following should ensure that the default token type is "int".
 */
#ವ್ಯಾಖ್ಯಾನಿಸು YYSTYPE ಪೂರ್ಣಾಂಕ

%}

%%
goal		:  initlex sect1 sect1end sect2 initforrule
			{ /* add default rule */
			ಪೂರ್ಣಾಂಕ def_ನಿಯಮ;

			pat = cclinit();
			cclnegate( pat );

			def_ನಿಯಮ = mkstate( -pat );

			/* Remember the number of the default rule so we
			 * don't generate "can't match" warnings for it.
			 */
			default_ನಿಯಮ = ಅಂಕೆ_ನಿಯಮಗಳು;

			ಮುಕ್ತಾಯ_ನಿಯಮ( def_ನಿಯಮ, false, 0, 0, 0);

			ಗಾಗಿ ( i = 1; i <= lastsc; ++i )
				scset[i] = mkbranch( scset[i], def_ನಿಯಮ );

			ಕೂಡಿಸು_action("]]");

			ಆದರೆ ( ctrl.spprdflt )
				ಕೂಡಿಸು_action(
				"M4_HOOK_FATAL_ERROR(\"flex scanner jammed\")");
			ಇಲ್ಲದಿದ್ದರೆ {
			    ಕೂಡಿಸು_action("M4_HOOK_ECHO");
			}

			ಕೂಡಿಸು_action( "\n\tM4_HOOK_STATE_CASE_BREAK\n" );
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
		|  TOK_ಪೂರ್ವಪ್ರತ್ಯಯ '=' NAME
			{ ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ = xstrdup(nmstr);
                          ಆದರೆ (strchr(ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ, '[') || strchr(ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ, ']'))
                              flexerror(_("Prefix must not contain [ or ]")); }
		|  TOK_YYCLASS '=' NAME
			{ ctrl.yyclass = xstrdup(nmstr); }
		|  TOK_ಶೀರ್ಷಿಕೆ_FILE '=' NAME
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
			trlcontxt = variable_trail_ನಿಯಮ = varlength = false;
			trailcnt = headcnt = rulelen = 0;
			current_state_type = STATE_ಸಾಮಾನ್ಯ;
			ಹಿಂದಿನ_continued_action = continued_action;
			ಒಳ_ನಿಯಮ = true;

			new_ನಿಯಮ();
			}
		;

flexrule	:  '^' ನಿಯಮ
			{
			pat = $2;
			ಮುಕ್ತಾಯ_ನಿಯಮ( pat, variable_trail_ನಿಯಮ,
				headcnt, trailcnt , ಹಿಂದಿನ_continued_action);

			ಆದರೆ ( scon_stk_ptr > 0 )
				{
				ಗಾಗಿ ( i = 1; i <= scon_stk_ptr; ++i )
					scbol[scon_stk[i]] =
						mkbranch( scbol[scon_stk[i]],
								pat );
				}

			ಇಲ್ಲದಿದ್ದರೆ
				{
				/* Add to all non-exclusive start conditions,
				 * including the default (0) start condition.
				 */

				ಗಾಗಿ ( i = 1; i <= lastsc; ++i )
					ಆದರೆ ( ! scxclu[i] )
						scbol[i] = mkbranch( scbol[i],
									pat );
				}

			ಆದರೆ ( ! bol_needed )
				{
				bol_needed = true;

				ಆದರೆ ( env.performance_hint > 1 )
					pinpoint_ಸಂದೇಶ(
			"'^' operator results in sub-optimal performance" );
				}
			}

		|  ನಿಯಮ
			{
			pat = $1;
			ಮುಕ್ತಾಯ_ನಿಯಮ( pat, variable_trail_ನಿಯಮ,
				headcnt, trailcnt , ಹಿಂದಿನ_continued_action);

			ಆದರೆ ( scon_stk_ptr > 0 )
				{
				ಗಾಗಿ ( i = 1; i <= scon_stk_ptr; ++i )
					scset[scon_stk[i]] =
						mkbranch( scset[scon_stk[i]],
								pat );
				}

			ಇಲ್ಲದಿದ್ದರೆ
				{
				ಗಾಗಿ ( i = 1; i <= lastsc; ++i )
					ಆದರೆ ( ! scxclu[i] )
						scset[i] =
							mkbranch( scset[i],
								pat );
				}
			}

		|  EOF_OP
			{
			ಆದರೆ ( scon_stk_ptr > 0 )
				build_eof_action();
	
			ಇಲ್ಲದಿದ್ದರೆ
				{
				/* This EOF applies to all start conditions
				 * which don't already have EOF actions.
				 */
				ಗಾಗಿ ( i = 1; i <= lastsc; ++i )
					ಆದರೆ ( ! sceof[i] )
						scon_stk[++scon_stk_ptr] = i;

				ಆದರೆ ( scon_stk_ptr == 0 )
					lwarn(
			"all start conditions already have <<EOF>> rules" );

				ಇಲ್ಲದಿದ್ದರೆ
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

			ಗಾಗಿ ( i = 1; i <= lastsc; ++i )
				{
				ಪೂರ್ಣಾಂಕ j;

				ಗಾಗಿ ( j = 1; j <= scon_stk_ptr; ++j )
					ಆದರೆ ( scon_stk[j] == i )
						ನಿಲ್ಲಿಸು;

				ಆದರೆ ( j > scon_stk_ptr )
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
			ಆದರೆ ( (scnum = sclookup( nmstr )) == 0 )
				format_pinpoint_ಸಂದೇಶ(
					"undeclared start condition %s",
					nmstr );
			ಇಲ್ಲದಿದ್ದರೆ
				{
				ಗಾಗಿ ( i = 1; i <= scon_stk_ptr; ++i )
					ಆದರೆ ( scon_stk[i] == scnum )
						{
						format_warn(
							"<%s> specified twice",
							scname[scnum] );
						ನಿಲ್ಲಿಸು;
						}

				ಆದರೆ ( i > scon_stk_ptr )
					scon_stk[++scon_stk_ptr] = scnum;
				}
			}
		;

ನಿಯಮ		:  re2 re
			{
			ಆದರೆ ( transchar[lastst[$2]] != SYM_EPSILON )
				/* Provide final transition \now/ so it
				 * will be marked as a trailing context
				 * state.
				 */
				$2 = link_machines( $2,
						mkstate( SYM_EPSILON ) );

			mark_beginning_as_ಸಾಮಾನ್ಯ( $2 );
			current_state_type = STATE_ಸಾಮಾನ್ಯ;

			ಆದರೆ ( ಹಿಂದಿನ_continued_action )
				{
				/* We need to treat this as variable trailing
				 * context so that the backup does not happen
				 * in the action but before the action switch
				 * statement.  If the backup happens in the
				 * action, then the rules "falling into" this
				 * one's action will *also* do the backup,
				 * erroneously.
				 */
				ಆದರೆ ( ! varlength || headcnt != 0 )
					lwarn(
		"trailing context made variable due to preceding '|' action" );

				/* Mark as variable. */
				varlength = true;
				headcnt = 0;

				}

			ಆದರೆ ( ctrl.lex_compat || (varlength && headcnt == 0) )
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
				ಕೂಡಿಸು_accept( $1,
					ಅಂಕೆ_ನಿಯಮಗಳು | YY_TRAILING_ತಲೆ_ಮುಖವಾಡ );
				variable_trail_ನಿಯಮ = true;
				}
			
			ಇಲ್ಲದಿದ್ದರೆ
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

			ಆದರೆ ( trlcontxt )
				{
				synerr( _("trailing context used twice") );
				$$ = mkstate( SYM_EPSILON );
				}

			ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ( ಹಿಂದಿನ_continued_action )
				{
				/* See the comment in the rule for "re2 re"
				 * above.
				 */
				lwarn(
		"trailing context made variable due to preceding '|' action" );

				varlength = true;
				}

			ಆದರೆ ( ctrl.lex_compat || varlength )
				{
				/* Again, see the comment in the rule for
				 * "re2 re" above.
				 */
				ಕೂಡಿಸು_accept( $1,
					ಅಂಕೆ_ನಿಯಮಗಳು | YY_TRAILING_ತಲೆ_ಮುಖವಾಡ );
				variable_trail_ನಿಯಮ = true;
				}

			trlcontxt = true;

			eps = mkstate( SYM_EPSILON );
			$$ = link_machines( $1,
				link_machines( eps, mkstate( '\n' ) ) );
			}

		|  re
			{
			$$ = $1;

			ಆದರೆ ( trlcontxt )
				{
				ಆದರೆ ( ctrl.lex_compat || (varlength && headcnt == 0) )
					/* Both head and trail are
					 * variable-length.
					 */
					variable_trail_ನಿಯಮ = true;
				ಇಲ್ಲದಿದ್ದರೆ
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

			ಆದರೆ ( trlcontxt )
				synerr( _("trailing context used twice") );
			ಇಲ್ಲದಿದ್ದರೆ
				trlcontxt = true;

			ಆದರೆ ( varlength )
				/* We hope the trailing context is
				 * fixed-length.
				 */
				varlength = false;
			ಇಲ್ಲದಿದ್ದರೆ
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

		|  series BEGIN_REPEAT_POSIX ಸಂಖ್ಯೆ ',' ಸಂಖ್ಯೆ ಕೊನೆ_REPEAT_POSIX
			{
			varlength = true;

			ಆದರೆ ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			ಇಲ್ಲದಿದ್ದರೆ
				{
				ಆದರೆ ( $3 == 0 )
					{
					ಆದರೆ ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					ಇಲ್ಲದಿದ್ದರೆ
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				ಇಲ್ಲದಿದ್ದರೆ
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  series BEGIN_REPEAT_POSIX ಸಂಖ್ಯೆ ',' ಕೊನೆ_REPEAT_POSIX
			{
			varlength = true;

			ಆದರೆ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			ಇಲ್ಲದಿದ್ದರೆ
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  series BEGIN_REPEAT_POSIX ಸಂಖ್ಯೆ ಕೊನೆ_REPEAT_POSIX
			{
			/* The series could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			ಆದರೆ ( $3 <= 0 )
				{
				  synerr( _("iteration value must be positive")
					  );
				$$ = $1;
				}

			ಇಲ್ಲದಿದ್ದರೆ
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

		|  singleton BEGIN_REPEAT_FLEX ಸಂಖ್ಯೆ ',' ಸಂಖ್ಯೆ ಕೊನೆ_REPEAT_FLEX
			{
			varlength = true;

			ಆದರೆ ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			ಇಲ್ಲದಿದ್ದರೆ
				{
				ಆದರೆ ( $3 == 0 )
					{
					ಆದರೆ ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					ಇಲ್ಲದಿದ್ದರೆ
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				ಇಲ್ಲದಿದ್ದರೆ
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  singleton BEGIN_REPEAT_FLEX ಸಂಖ್ಯೆ ',' ಕೊನೆ_REPEAT_FLEX
			{
			varlength = true;

			ಆದರೆ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			ಇಲ್ಲದಿದ್ದರೆ
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  singleton BEGIN_REPEAT_FLEX ಸಂಖ್ಯೆ ಕೊನೆ_REPEAT_FLEX
			{
			/* The singleton could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			ಆದರೆ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			ಇಲ್ಲದಿದ್ದರೆ
				$$ = link_machines( $1,
						copysingl( $1, $3 - 1 ) );
			}

		|  '.'
			{
			ಆದರೆ ( ! madeany )
				{
				/* Create the '.' character class. */
                    ccldot = cclinit();
                    ccladd( ccldot, '\n' );
                    cclnegate( ccldot );

                    ಆದರೆ ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[ccldot],
                            ccllen[ccldot], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				/* Create the (?s:'.') character class. */
                    cclany = cclinit();
                    cclnegate( cclany );

                    ಆದರೆ ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[cclany],
                            ccllen[cclany], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				madeany = true;
				}

			++rulelen;

            ಆದರೆ (sf_dot_all())
                $$ = mkstate( -cclany );
            ಇಲ್ಲದಿದ್ದರೆ
                $$ = mkstate( -ccldot );
			}

		|  fullccl
			{
				/* Sort characters for fast searching.
				 */
				qsort( ccltbl + cclmap[$1], (size_t) ccllen[$1], ಗಾತ್ರ (*ccltbl), cclcmp );

			ಆದರೆ ( ctrl.useecs )
				mkeccl( ccltbl + cclmap[$1], ccllen[$1],
					nextecm, ecgroup, ctrl.csize, ctrl.csize);

			++rulelen;

			ಆದರೆ (ccl_has_nl[$1])
				ನಿಯಮ_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  PREVCCL
			{
			++rulelen;

			ಆದರೆ (ccl_has_nl[$1])
				ನಿಯಮ_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  '"' string '"'
			{ $$ = $2; }

		|  '(' re ')'
			{ $$ = $2; }

		|  CHAR
			{
			++rulelen;

			ಆದರೆ ($1 == nlch)
				ನಿಯಮ_has_nl[num_rules] = true;

            ಆದರೆ (sf_case_ins() && has_case($1))
                /* create an alternation, as in (a|A) */
                $$ = mkor (mkstate($1), mkstate(ಹಿಮ್ಮುಖ_case($1)));
            ಇಲ್ಲದಿದ್ದರೆ
                $$ = mkstate( $1 );
			}
		;
fullccl:
        fullccl CCL_OP_DIFF  braceccl  { $$ = ccl_ಗಣ_diff  ($1, $3); }
    |   fullccl CCL_OP_UNION braceccl  { $$ = ccl_ಗಣ_union ($1, $3); }
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

			ಆದರೆ (sf_case_ins())
			  {

			    /* If one end of the range has case and the other
			     * does not, or the cases are different, then we're not
			     * sure what range the user is trying to express.
			     * Examples: [@-z] or [S-t]
			     */
			    ಆದರೆ (has_case ($2) != has_case ($4)
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
			    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!has_case ($2) && !has_case ($4) && !range_covers_case ($2, $4))
			      format_warn3 (
			      _("the character range [%c-%c] is ambiguous in a case-insensitive scanner"),
					    $2, $4);
			  }

			ಆದರೆ ( $2 > $4 )
				synerr( _("negative range in character class") );

			ಇಲ್ಲದಿದ್ದರೆ
				{
				ಗಾಗಿ ( i = $2; i <= $4; ++i )
					ccladd( $1, i );

				/* Keep track if this ccl is staying in
				 * alphabetical order.
				 */
				cclsorted = cclsorted && ($2 > lastchar);
				lastchar = $4;

                /* Do it again for upper/lowercase */
                ಆದರೆ (sf_case_ins() && has_case($2) && has_case($4)){
                    $2 = ಹಿಮ್ಮುಖ_case ($2);
                    $4 = ಹಿಮ್ಮುಖ_case ($4);
                    
                    ಗಾಗಿ ( i = $2; i <= $4; ++i )
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
            ಆದರೆ (sf_case_ins() && has_case($2)){
                $2 = ಹಿಮ್ಮುಖ_case ($2);
                ccladd ($1, $2);

                cclsorted = cclsorted && ($2 > lastchar);
                lastchar = $2;
            }

			$$ = $1;
			}

		|  ccl ccl_ಅಭಿವ್ಯಕ್ತಿ
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

ccl_ಅಭಿವ್ಯಕ್ತಿ:	   
           CCE_ALNUM	{ CCL_ಅಭಿವ್ಯಕ್ತಿ(ಅಕ್ಷರವೇ_ಅಂಕಿಯೇ); }
		|  CCE_ALPHA	{ CCL_ಅಭಿವ್ಯಕ್ತಿ(ಅಕ್ಷರವೇ); }
		|  CCE_BLANK	{ CCL_ಅಭಿವ್ಯಕ್ತಿ(IS_BLANK); }
		|  CCE_CNTRL	{ CCL_ಅಭಿವ್ಯಕ್ತಿ(iscntrl); }
		|  CCE_DIGIT	{ CCL_ಅಭಿವ್ಯಕ್ತಿ(ಅಂಕಿಯೇ); }
		|  CCE_ನಕ್ಷೆ	{ CCL_ಅಭಿವ್ಯಕ್ತಿ(isgraph); }
		|  CCE_ಅಧೋ	{ 
                          CCL_ಅಭಿವ್ಯಕ್ತಿ(islower);
                          ಆದರೆ (sf_case_ins())
                              CCL_ಅಭಿವ್ಯಕ್ತಿ(isupper);
                        }
		|  CCE_PRINT	{ CCL_ಅಭಿವ್ಯಕ್ತಿ(isprint); }
		|  CCE_PUNCT	{ CCL_ಅಭಿವ್ಯಕ್ತಿ(ispunct); }
		|  CCE_SPACE	{ CCL_ಅಭಿವ್ಯಕ್ತಿ(ಖಾಲಿಯೇ); }
		|  CCE_XDIGIT	{ CCL_ಅಭಿವ್ಯಕ್ತಿ(isxdigit); }
		|  CCE_ಊರ್ಧ್ವ	{
                    CCL_ಅಭಿವ್ಯಕ್ತಿ(isupper);
                    ಆದರೆ (sf_case_ins())
                        CCL_ಅಭಿವ್ಯಕ್ತಿ(islower);
				}

        |  CCE_NEG_ALNUM	{ CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(ಅಕ್ಷರವೇ_ಅಂಕಿಯೇ); }
		|  CCE_NEG_ALPHA	{ CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(ಅಕ್ಷರವೇ); }
		|  CCE_NEG_BLANK	{ CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(IS_BLANK); }
		|  CCE_NEG_CNTRL	{ CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(iscntrl); }
		|  CCE_NEG_DIGIT	{ CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(ಅಂಕಿಯೇ); }
		|  CCE_NEG_ನಕ್ಷೆ	{ CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(isgraph); }
		|  CCE_NEG_PRINT	{ CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(isprint); }
		|  CCE_NEG_PUNCT	{ CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(ispunct); }
		|  CCE_NEG_SPACE	{ CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(ಖಾಲಿಯೇ); }
		|  CCE_NEG_XDIGIT	{ CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(isxdigit); }
		|  CCE_NEG_ಅಧೋ	{ 
				ಆದರೆ ( sf_case_ins() )
					lwarn(_("[:^lower:] is ambiguous in case insensitive scanner"));
				ಇಲ್ಲದಿದ್ದರೆ
					CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(islower);
				}
		|  CCE_NEG_ಊರ್ಧ್ವ	{
				ಆದರೆ ( sf_case_ins() )
					lwarn(_("[:^upper:] ambiguous in case insensitive scanner"));
				ಇಲ್ಲದಿದ್ದರೆ
					CCL_NEG_ಅಭಿವ್ಯಕ್ತಿ(isupper);
				}
		;
		
string		:  string CHAR
			{
			ಆದರೆ ( $2 == nlch )
				ನಿಯಮ_has_nl[num_rules] = true;

			++rulelen;

            ಆದರೆ (sf_case_ins() && has_case($2))
                $$ = mkor (mkstate($2), mkstate(ಹಿಮ್ಮುಖ_case($2)));
            ಇಲ್ಲದಿದ್ದರೆ
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

ಶೂನ್ಯ build_eof_action(ಶೂನ್ಯ)
	{
	ಪೂರ್ಣಾಂಕ i;
	ಅಕ್ಷರ action_ಪಠ್ಯ[MAXLINE];

	ಗಾಗಿ ( i = 1; i <= scon_stk_ptr; ++i )
		{
		ಆದರೆ ( sceof[scon_stk[i]] )
			format_pinpoint_ಸಂದೇಶ(
				"multiple <<EOF>> rules for start condition %s",
				scname[scon_stk[i]] );

		ಇಲ್ಲದಿದ್ದರೆ
			{
			sceof[scon_stk[i]] = true;

			ಆದರೆ (ಹಿಂದಿನ_continued_action /* && previous action was regular */)
				ಕೂಡಿಸು_action("YY_RULE_SETUP\n");

			snprintf( action_ಪಠ್ಯ, ಗಾತ್ರ(action_ಪಠ್ಯ), "M4_HOOK_EOF_STATE_CASE_ARM(%s)\n",
				scname[scon_stk[i]] );
			ಕೂಡಿಸು_action( action_ಪಠ್ಯ );
			}
		}

	ಸಾಲು_directive_ಹೊರಹೋಗು(ಖಾಲಿ, infilename, linenum);
        ಕೂಡಿಸು_action("[[");

	/* This isn't a normal rule after all - don't count it as
	 * such, so we don't have any holes in the rule numbering
	 * (which make generating "rule can never match" warnings
	 * more difficult.
	 */
	--num_rules;
	++ಅಂಕೆ_eof_ನಿಯಮಗಳು;
	}


/* format_synerr - write out formatted syntax error */

ಶೂನ್ಯ format_synerr( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ arg[] )
	{
	ಅಕ್ಷರ errmsg[MAXLINE];

	(ಶೂನ್ಯ) snprintf( errmsg, ಗಾತ್ರ(errmsg), ಸಂದೇಶ, arg );
	synerr( errmsg );
	}


/* synerr - report a syntax error */

ಶೂನ್ಯ synerr( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str )
	{
	syntaxerror = true;
	pinpoint_ಸಂದೇಶ( str );
	}


/* format_warn - write out formatted warning */

ಶೂನ್ಯ format_warn( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ arg[] )
	{
	ಅಕ್ಷರ warn_ಸಂದೇಶ[MAXLINE];

	snprintf( warn_ಸಂದೇಶ, ಗಾತ್ರ(warn_ಸಂದೇಶ), ಸಂದೇಶ, arg );
	lwarn( warn_ಸಂದೇಶ );
	}


/* lwarn - report a warning, unless -w was given */

ಶೂನ್ಯ lwarn( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str )
	{
	ಸಾಲು_warning( str, linenum );
	}

/* format_pinpoint_message - write out a message formatted with one string,
 *			     pinpointing its location
 */

ಶೂನ್ಯ format_pinpoint_ಸಂದೇಶ( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ arg[] )
	{
	ಅಕ್ಷರ errmsg[MAXLINE*2];

	snprintf( errmsg, ಗಾತ್ರ(errmsg), ಸಂದೇಶ, arg );
	pinpoint_ಸಂದೇಶ( errmsg );
	}


/* pinpoint_message - write out a message, pinpointing its location */

ಶೂನ್ಯ pinpoint_ಸಂದೇಶ( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str )
	{
	ಸಾಲು_pinpoint( str, linenum );
	}


/* line_warning - report a warning at a given line, unless -w was given */

ಶೂನ್ಯ ಸಾಲು_warning( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ ಸಾಲು )
	{
	ಅಕ್ಷರ warning[MAXLINE*2];

	ಆದರೆ ( ! env.nowarn )
		{
		snprintf( warning, ಗಾತ್ರ(warning), "warning, %s", str );
		ಸಾಲು_pinpoint( warning, ಸಾಲು );
		}
	}


/* line_pinpoint - write out a message, pinpointing it at the given line */

ಶೂನ್ಯ ಸಾಲು_pinpoint( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ ಸಾಲು )
	{
	fprintf( stderr, "%s:%d: %s\n", infilename, ಸಾಲು, str );
	}


/* yyerror - eat up an error message from the parser;
 *	     currently, messages are ignore
 */

ಶೂನ್ಯ yyerror( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ )
	{
		(ಶೂನ್ಯ)ಸಂದೇಶ;
	}
