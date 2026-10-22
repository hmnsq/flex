/* parse.y - parser for flex input */

%token CHAR సంఖ్య SECTEND SCDECL XSCDECL NAME PREVCCL EOF_OP
%token TOK_OPTION TOK_OUTFILE TOK_ఉపసర్గ TOK_YYCLASS TOK_శీర్షిక_FILE TOK_EXTRA_TYPE
%token TOK_TABLES_FILE TOK_YYLMAX TOK_NUMERIC TOK_YYDECL TOK_PREACTION TOK_POSTACTION
%token TOK_USERINIT TOK_EMIT TOK_BUFSIZE TOK_YYTERMINATE

%token CCE_ALNUM CCE_ALPHA CCE_BLANK CCE_CNTRL CCE_DIGIT CCE_లేఖాచిత్రం
%token CCE_క్రింది CCE_PRINT CCE_PUNCT CCE_SPACE CCE_పై CCE_XDIGIT

%token CCE_NEG_ALNUM CCE_NEG_ALPHA CCE_NEG_BLANK CCE_NEG_CNTRL CCE_NEG_DIGIT CCE_NEG_లేఖాచిత్రం
%token CCE_NEG_క్రింది CCE_NEG_PRINT CCE_NEG_PUNCT CCE_NEG_SPACE CCE_NEG_పై CCE_NEG_XDIGIT

%ఎడమ CCL_OP_DIFF CCL_OP_UNION

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

%token BEGIN_REPEAT_POSIX చివర_REPEAT_POSIX BEGIN_REPEAT_FLEX చివర_REPEAT_FLEX


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

#అన్తర్భావ "flexdef.h"
#అన్తర్భావ "tables.h"

పూర్ణాంకం pat, scnum, eps, headcnt, trailcnt, lastchar, i, rulelen;
స్థిర పూర్ణాంకం currccl;
bool trlcontxt;
స్థిర bool sc_is_exclusive, cclsorted, varlength, variable_trail_నియమం;

పూర్ణాంకం *scon_stk;
పూర్ణాంకం scon_stk_ptr;

స్థిర పూర్ణాంకం madeany = false;  /* whether we've made the '.' character class */
స్థిర పూర్ణాంకం ccldot, cclany;
పూర్ణాంకం మునుపటి_continued_action;	/* whether the previous rule's action was '|' */

#నిర్వచించు format_warn3(fmt, a1, a2) \
	చేయి{ \
        అక్షరం fw3_సందేశం[MAXLINE];\
        snprintf( fw3_సందేశం, MAXLINE,(fmt), (a1), (a2) );\
        lwarn( fw3_సందేశం );\
	}అయితే(0)

/* Expand a POSIX character class expression. */
#నిర్వచించు CCL_సమాసం(func) \
	చేయి{ \
	పూర్ణాంకం c; \
	కొరకు ( c = 0; c < ctrl.csize; ++c ) \
		ఒకవేళ ( isascii(c) && func(c) ) \
			ccladd( currccl, c ); \
	}అయితే(0)

/* negated class */
#నిర్వచించు CCL_NEG_సమాసం(func) \
	చేయి{ \
	పూర్ణాంకం c; \
	కొరకు ( c = 0; c < ctrl.csize; ++c ) \
		ఒకవేళ ( !func(c) ) \
			ccladd( currccl, c ); \
	}అయితే(0)

/* While POSIX defines isblank(), it's not ANSI C. */
#నిర్వచించు IS_BLANK(c) ((c) == ' ' || (c) == '\t')

/* On some over-ambitious machines, such as DEC Alpha's, the default
 * token type is "long" instead of "int"; this leads to problems with
 * declaring yylval in flexdef.h.  But so far, all the yacc's I've seen
 * wrap their definitions of YYSTYPE with "#ifndef YYSTYPE"'s, so the
 * following should ensure that the default token type is "int".
 */
#నిర్వచించు YYSTYPE పూర్ణాంకం

%}

%%
goal		:  initlex sect1 sect1end sect2 initforrule
			{ /* add default rule */
			పూర్ణాంకం def_నియమం;

			pat = cclinit();
			cclnegate( pat );

			def_నియమం = mkstate( -pat );

			/* Remember the number of the default rule so we
			 * don't generate "can't match" warnings for it.
			 */
			default_నియమం = అంకె_నియమాలు;

			ముగింపు_నియమం( def_నియమం, false, 0, 0, 0);

			కొరకు ( i = 1; i <= lastsc; ++i )
				scset[i] = mkbranch( scset[i], def_నియమం );

			కూడు_action("]]");

			ఒకవేళ ( ctrl.spprdflt )
				కూడు_action(
				"M4_HOOK_FATAL_ERROR(\"flex scanner jammed\")");
			లేకపోతే {
			    కూడు_action("M4_HOOK_ECHO");
			}

			కూడు_action( "\n\tM4_HOOK_STATE_CASE_BREAK\n" );
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
		|  TOK_ఉపసర్గ '=' NAME
			{ ctrl.ఉపసర్గ = xstrdup(nmstr);
                          ఒకవేళ (strchr(ctrl.ఉపసర్గ, '[') || strchr(ctrl.ఉపసర్గ, ']'))
                              flexerror(_("Prefix must not contain [ or ]")); }
		|  TOK_YYCLASS '=' NAME
			{ ctrl.yyclass = xstrdup(nmstr); }
		|  TOK_శీర్షిక_FILE '=' NAME
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
			trlcontxt = variable_trail_నియమం = varlength = false;
			trailcnt = headcnt = rulelen = 0;
			current_state_type = STATE_సాధారణ;
			మునుపటి_continued_action = continued_action;
			లోపల_నియమం = true;

			new_నియమం();
			}
		;

flexrule	:  '^' నియమం
			{
			pat = $2;
			ముగింపు_నియమం( pat, variable_trail_నియమం,
				headcnt, trailcnt , మునుపటి_continued_action);

			ఒకవేళ ( scon_stk_ptr > 0 )
				{
				కొరకు ( i = 1; i <= scon_stk_ptr; ++i )
					scbol[scon_stk[i]] =
						mkbranch( scbol[scon_stk[i]],
								pat );
				}

			లేకపోతే
				{
				/* Add to all non-exclusive start conditions,
				 * including the default (0) start condition.
				 */

				కొరకు ( i = 1; i <= lastsc; ++i )
					ఒకవేళ ( ! scxclu[i] )
						scbol[i] = mkbranch( scbol[i],
									pat );
				}

			ఒకవేళ ( ! bol_needed )
				{
				bol_needed = true;

				ఒకవేళ ( env.performance_hint > 1 )
					pinpoint_సందేశం(
			"'^' operator results in sub-optimal performance" );
				}
			}

		|  నియమం
			{
			pat = $1;
			ముగింపు_నియమం( pat, variable_trail_నియమం,
				headcnt, trailcnt , మునుపటి_continued_action);

			ఒకవేళ ( scon_stk_ptr > 0 )
				{
				కొరకు ( i = 1; i <= scon_stk_ptr; ++i )
					scset[scon_stk[i]] =
						mkbranch( scset[scon_stk[i]],
								pat );
				}

			లేకపోతే
				{
				కొరకు ( i = 1; i <= lastsc; ++i )
					ఒకవేళ ( ! scxclu[i] )
						scset[i] =
							mkbranch( scset[i],
								pat );
				}
			}

		|  EOF_OP
			{
			ఒకవేళ ( scon_stk_ptr > 0 )
				build_eof_action();
	
			లేకపోతే
				{
				/* This EOF applies to all start conditions
				 * which don't already have EOF actions.
				 */
				కొరకు ( i = 1; i <= lastsc; ++i )
					ఒకవేళ ( ! sceof[i] )
						scon_stk[++scon_stk_ptr] = i;

				ఒకవేళ ( scon_stk_ptr == 0 )
					lwarn(
			"all start conditions already have <<EOF>> rules" );

				లేకపోతే
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

			కొరకు ( i = 1; i <= lastsc; ++i )
				{
				పూర్ణాంకం j;

				కొరకు ( j = 1; j <= scon_stk_ptr; ++j )
					ఒకవేళ ( scon_stk[j] == i )
						ఆపు;

				ఒకవేళ ( j > scon_stk_ptr )
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
			ఒకవేళ ( (scnum = sclookup( nmstr )) == 0 )
				format_pinpoint_సందేశం(
					"undeclared start condition %s",
					nmstr );
			లేకపోతే
				{
				కొరకు ( i = 1; i <= scon_stk_ptr; ++i )
					ఒకవేళ ( scon_stk[i] == scnum )
						{
						format_warn(
							"<%s> specified twice",
							scname[scnum] );
						ఆపు;
						}

				ఒకవేళ ( i > scon_stk_ptr )
					scon_stk[++scon_stk_ptr] = scnum;
				}
			}
		;

నియమం		:  re2 re
			{
			ఒకవేళ ( transchar[lastst[$2]] != SYM_EPSILON )
				/* Provide final transition \now/ so it
				 * will be marked as a trailing context
				 * state.
				 */
				$2 = link_machines( $2,
						mkstate( SYM_EPSILON ) );

			mark_beginning_as_సాధారణ( $2 );
			current_state_type = STATE_సాధారణ;

			ఒకవేళ ( మునుపటి_continued_action )
				{
				/* We need to treat this as variable trailing
				 * context so that the backup does not happen
				 * in the action but before the action switch
				 * statement.  If the backup happens in the
				 * action, then the rules "falling into" this
				 * one's action will *also* do the backup,
				 * erroneously.
				 */
				ఒకవేళ ( ! varlength || headcnt != 0 )
					lwarn(
		"trailing context made variable due to preceding '|' action" );

				/* Mark as variable. */
				varlength = true;
				headcnt = 0;

				}

			ఒకవేళ ( ctrl.lex_compat || (varlength && headcnt == 0) )
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
				కూడు_accept( $1,
					అంకె_నియమాలు | YY_TRAILING_తల_ముసుగు );
				variable_trail_నియమం = true;
				}
			
			లేకపోతే
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

			ఒకవేళ ( trlcontxt )
				{
				synerr( _("trailing context used twice") );
				$$ = mkstate( SYM_EPSILON );
				}

			లేకపోతే ఒకవేళ ( మునుపటి_continued_action )
				{
				/* See the comment in the rule for "re2 re"
				 * above.
				 */
				lwarn(
		"trailing context made variable due to preceding '|' action" );

				varlength = true;
				}

			ఒకవేళ ( ctrl.lex_compat || varlength )
				{
				/* Again, see the comment in the rule for
				 * "re2 re" above.
				 */
				కూడు_accept( $1,
					అంకె_నియమాలు | YY_TRAILING_తల_ముసుగు );
				variable_trail_నియమం = true;
				}

			trlcontxt = true;

			eps = mkstate( SYM_EPSILON );
			$$ = link_machines( $1,
				link_machines( eps, mkstate( '\n' ) ) );
			}

		|  re
			{
			$$ = $1;

			ఒకవేళ ( trlcontxt )
				{
				ఒకవేళ ( ctrl.lex_compat || (varlength && headcnt == 0) )
					/* Both head and trail are
					 * variable-length.
					 */
					variable_trail_నియమం = true;
				లేకపోతే
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

			ఒకవేళ ( trlcontxt )
				synerr( _("trailing context used twice") );
			లేకపోతే
				trlcontxt = true;

			ఒకవేళ ( varlength )
				/* We hope the trailing context is
				 * fixed-length.
				 */
				varlength = false;
			లేకపోతే
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

		|  series BEGIN_REPEAT_POSIX సంఖ్య ',' సంఖ్య చివర_REPEAT_POSIX
			{
			varlength = true;

			ఒకవేళ ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			లేకపోతే
				{
				ఒకవేళ ( $3 == 0 )
					{
					ఒకవేళ ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					లేకపోతే
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				లేకపోతే
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  series BEGIN_REPEAT_POSIX సంఖ్య ',' చివర_REPEAT_POSIX
			{
			varlength = true;

			ఒకవేళ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			లేకపోతే
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  series BEGIN_REPEAT_POSIX సంఖ్య చివర_REPEAT_POSIX
			{
			/* The series could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			ఒకవేళ ( $3 <= 0 )
				{
				  synerr( _("iteration value must be positive")
					  );
				$$ = $1;
				}

			లేకపోతే
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

		|  singleton BEGIN_REPEAT_FLEX సంఖ్య ',' సంఖ్య చివర_REPEAT_FLEX
			{
			varlength = true;

			ఒకవేళ ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			లేకపోతే
				{
				ఒకవేళ ( $3 == 0 )
					{
					ఒకవేళ ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					లేకపోతే
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				లేకపోతే
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  singleton BEGIN_REPEAT_FLEX సంఖ్య ',' చివర_REPEAT_FLEX
			{
			varlength = true;

			ఒకవేళ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			లేకపోతే
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  singleton BEGIN_REPEAT_FLEX సంఖ్య చివర_REPEAT_FLEX
			{
			/* The singleton could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			ఒకవేళ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			లేకపోతే
				$$ = link_machines( $1,
						copysingl( $1, $3 - 1 ) );
			}

		|  '.'
			{
			ఒకవేళ ( ! madeany )
				{
				/* Create the '.' character class. */
                    ccldot = cclinit();
                    ccladd( ccldot, '\n' );
                    cclnegate( ccldot );

                    ఒకవేళ ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[ccldot],
                            ccllen[ccldot], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				/* Create the (?s:'.') character class. */
                    cclany = cclinit();
                    cclnegate( cclany );

                    ఒకవేళ ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[cclany],
                            ccllen[cclany], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				madeany = true;
				}

			++rulelen;

            ఒకవేళ (sf_dot_all())
                $$ = mkstate( -cclany );
            లేకపోతే
                $$ = mkstate( -ccldot );
			}

		|  fullccl
			{
				/* Sort characters for fast searching.
				 */
				qsort( ccltbl + cclmap[$1], (size_t) ccllen[$1], పరిమాణం (*ccltbl), cclcmp );

			ఒకవేళ ( ctrl.useecs )
				mkeccl( ccltbl + cclmap[$1], ccllen[$1],
					nextecm, ecgroup, ctrl.csize, ctrl.csize);

			++rulelen;

			ఒకవేళ (ccl_has_nl[$1])
				నియమం_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  PREVCCL
			{
			++rulelen;

			ఒకవేళ (ccl_has_nl[$1])
				నియమం_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  '"' string '"'
			{ $$ = $2; }

		|  '(' re ')'
			{ $$ = $2; }

		|  CHAR
			{
			++rulelen;

			ఒకవేళ ($1 == nlch)
				నియమం_has_nl[num_rules] = true;

            ఒకవేళ (sf_case_ins() && has_case($1))
                /* create an alternation, as in (a|A) */
                $$ = mkor (mkstate($1), mkstate(తిరగేయి_case($1)));
            లేకపోతే
                $$ = mkstate( $1 );
			}
		;
fullccl:
        fullccl CCL_OP_DIFF  braceccl  { $$ = ccl_సమితి_diff  ($1, $3); }
    |   fullccl CCL_OP_UNION braceccl  { $$ = ccl_సమితి_union ($1, $3); }
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

			ఒకవేళ (sf_case_ins())
			  {

			    /* If one end of the range has case and the other
			     * does not, or the cases are different, then we're not
			     * sure what range the user is trying to express.
			     * Examples: [@-z] or [S-t]
			     */
			    ఒకవేళ (has_case ($2) != has_case ($4)
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
			    లేకపోతే ఒకవేళ (!has_case ($2) && !has_case ($4) && !range_covers_case ($2, $4))
			      format_warn3 (
			      _("the character range [%c-%c] is ambiguous in a case-insensitive scanner"),
					    $2, $4);
			  }

			ఒకవేళ ( $2 > $4 )
				synerr( _("negative range in character class") );

			లేకపోతే
				{
				కొరకు ( i = $2; i <= $4; ++i )
					ccladd( $1, i );

				/* Keep track if this ccl is staying in
				 * alphabetical order.
				 */
				cclsorted = cclsorted && ($2 > lastchar);
				lastchar = $4;

                /* Do it again for upper/lowercase */
                ఒకవేళ (sf_case_ins() && has_case($2) && has_case($4)){
                    $2 = తిరగేయి_case ($2);
                    $4 = తిరగేయి_case ($4);
                    
                    కొరకు ( i = $2; i <= $4; ++i )
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
            ఒకవేళ (sf_case_ins() && has_case($2)){
                $2 = తిరగేయి_case ($2);
                ccladd ($1, $2);

                cclsorted = cclsorted && ($2 > lastchar);
                lastchar = $2;
            }

			$$ = $1;
			}

		|  ccl ccl_సమాసం
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

ccl_సమాసం:	   
           CCE_ALNUM	{ CCL_సమాసం(అక్షరమా_అంకెనా); }
		|  CCE_ALPHA	{ CCL_సమాసం(అక్షరమా); }
		|  CCE_BLANK	{ CCL_సమాసం(IS_BLANK); }
		|  CCE_CNTRL	{ CCL_సమాసం(iscntrl); }
		|  CCE_DIGIT	{ CCL_సమాసం(అంకెనా); }
		|  CCE_లేఖాచిత్రం	{ CCL_సమాసం(isgraph); }
		|  CCE_క్రింది	{ 
                          CCL_సమాసం(islower);
                          ఒకవేళ (sf_case_ins())
                              CCL_సమాసం(isupper);
                        }
		|  CCE_PRINT	{ CCL_సమాసం(isprint); }
		|  CCE_PUNCT	{ CCL_సమాసం(ispunct); }
		|  CCE_SPACE	{ CCL_సమాసం(ఖాళీనా); }
		|  CCE_XDIGIT	{ CCL_సమాసం(isxdigit); }
		|  CCE_పై	{
                    CCL_సమాసం(isupper);
                    ఒకవేళ (sf_case_ins())
                        CCL_సమాసం(islower);
				}

        |  CCE_NEG_ALNUM	{ CCL_NEG_సమాసం(అక్షరమా_అంకెనా); }
		|  CCE_NEG_ALPHA	{ CCL_NEG_సమాసం(అక్షరమా); }
		|  CCE_NEG_BLANK	{ CCL_NEG_సమాసం(IS_BLANK); }
		|  CCE_NEG_CNTRL	{ CCL_NEG_సమాసం(iscntrl); }
		|  CCE_NEG_DIGIT	{ CCL_NEG_సమాసం(అంకెనా); }
		|  CCE_NEG_లేఖాచిత్రం	{ CCL_NEG_సమాసం(isgraph); }
		|  CCE_NEG_PRINT	{ CCL_NEG_సమాసం(isprint); }
		|  CCE_NEG_PUNCT	{ CCL_NEG_సమాసం(ispunct); }
		|  CCE_NEG_SPACE	{ CCL_NEG_సమాసం(ఖాళీనా); }
		|  CCE_NEG_XDIGIT	{ CCL_NEG_సమాసం(isxdigit); }
		|  CCE_NEG_క్రింది	{ 
				ఒకవేళ ( sf_case_ins() )
					lwarn(_("[:^lower:] is ambiguous in case insensitive scanner"));
				లేకపోతే
					CCL_NEG_సమాసం(islower);
				}
		|  CCE_NEG_పై	{
				ఒకవేళ ( sf_case_ins() )
					lwarn(_("[:^upper:] ambiguous in case insensitive scanner"));
				లేకపోతే
					CCL_NEG_సమాసం(isupper);
				}
		;
		
string		:  string CHAR
			{
			ఒకవేళ ( $2 == nlch )
				నియమం_has_nl[num_rules] = true;

			++rulelen;

            ఒకవేళ (sf_case_ins() && has_case($2))
                $$ = mkor (mkstate($2), mkstate(తిరగేయి_case($2)));
            లేకపోతే
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

శూన్య build_eof_action(శూన్య)
	{
	పూర్ణాంకం i;
	అక్షరం action_పాఠ్యం[MAXLINE];

	కొరకు ( i = 1; i <= scon_stk_ptr; ++i )
		{
		ఒకవేళ ( sceof[scon_stk[i]] )
			format_pinpoint_సందేశం(
				"multiple <<EOF>> rules for start condition %s",
				scname[scon_stk[i]] );

		లేకపోతే
			{
			sceof[scon_stk[i]] = true;

			ఒకవేళ (మునుపటి_continued_action /* && previous action was regular */)
				కూడు_action("YY_RULE_SETUP\n");

			snprintf( action_పాఠ్యం, పరిమాణం(action_పాఠ్యం), "M4_HOOK_EOF_STATE_CASE_ARM(%s)\n",
				scname[scon_stk[i]] );
			కూడు_action( action_పాఠ్యం );
			}
		}

	పంక్తి_directive_బహిర్గతం(ఖాళీ, infilename, linenum);
        కూడు_action("[[");

	/* This isn't a normal rule after all - don't count it as
	 * such, so we don't have any holes in the rule numbering
	 * (which make generating "rule can never match" warnings
	 * more difficult.
	 */
	--num_rules;
	++అంకె_eof_నియమాలు;
	}


/* format_synerr - write out formatted syntax error */

శూన్య format_synerr( స్థిరరాశి అక్షరం *సందేశం, స్థిరరాశి అక్షరం arg[] )
	{
	అక్షరం errmsg[MAXLINE];

	(శూన్య) snprintf( errmsg, పరిమాణం(errmsg), సందేశం, arg );
	synerr( errmsg );
	}


/* synerr - report a syntax error */

శూన్య synerr( స్థిరరాశి అక్షరం *str )
	{
	syntaxerror = true;
	pinpoint_సందేశం( str );
	}


/* format_warn - write out formatted warning */

శూన్య format_warn( స్థిరరాశి అక్షరం *సందేశం, స్థిరరాశి అక్షరం arg[] )
	{
	అక్షరం warn_సందేశం[MAXLINE];

	snprintf( warn_సందేశం, పరిమాణం(warn_సందేశం), సందేశం, arg );
	lwarn( warn_సందేశం );
	}


/* lwarn - report a warning, unless -w was given */

శూన్య lwarn( స్థిరరాశి అక్షరం *str )
	{
	పంక్తి_warning( str, linenum );
	}

/* format_pinpoint_message - write out a message formatted with one string,
 *			     pinpointing its location
 */

శూన్య format_pinpoint_సందేశం( స్థిరరాశి అక్షరం *సందేశం, స్థిరరాశి అక్షరం arg[] )
	{
	అక్షరం errmsg[MAXLINE*2];

	snprintf( errmsg, పరిమాణం(errmsg), సందేశం, arg );
	pinpoint_సందేశం( errmsg );
	}


/* pinpoint_message - write out a message, pinpointing its location */

శూన్య pinpoint_సందేశం( స్థిరరాశి అక్షరం *str )
	{
	పంక్తి_pinpoint( str, linenum );
	}


/* line_warning - report a warning at a given line, unless -w was given */

శూన్య పంక్తి_warning( స్థిరరాశి అక్షరం *str, పూర్ణాంకం పంక్తి )
	{
	అక్షరం warning[MAXLINE*2];

	ఒకవేళ ( ! env.nowarn )
		{
		snprintf( warning, పరిమాణం(warning), "warning, %s", str );
		పంక్తి_pinpoint( warning, పంక్తి );
		}
	}


/* line_pinpoint - write out a message, pinpointing it at the given line */

శూన్య పంక్తి_pinpoint( స్థిరరాశి అక్షరం *str, పూర్ణాంకం పంక్తి )
	{
	fprintf( stderr, "%s:%d: %s\n", infilename, పంక్తి, str );
	}


/* yyerror - eat up an error message from the parser;
 *	     currently, messages are ignore
 */

శూన్య yyerror( స్థిరరాశి అక్షరం *సందేశం )
	{
		(శూన్య)సందేశం;
	}
