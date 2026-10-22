/* parse.y - parser for flex input */

%token CHAR عدد SECTEND SCDECL XSCDECL NAME PREVCCL EOF_OP
%token TOK_OPTION TOK_OUTFILE TOK_اڳياڙي TOK_YYCLASS TOK_سرو_FILE TOK_EXTRA_TYPE
%token TOK_TABLES_FILE TOK_YYLMAX TOK_NUMERIC TOK_YYDECL TOK_PREACTION TOK_POSTACTION
%token TOK_USERINIT TOK_EMIT TOK_BUFSIZE TOK_YYTERMINATE

%token CCE_ALNUM CCE_ALPHA CCE_BLANK CCE_CNTRL CCE_DIGIT CCE_گراف
%token CCE_هيٺاهون CCE_PRINT CCE_PUNCT CCE_SPACE CCE_مٿانهون CCE_XDIGIT

%token CCE_NEG_ALNUM CCE_NEG_ALPHA CCE_NEG_BLANK CCE_NEG_CNTRL CCE_NEG_DIGIT CCE_NEG_گراف
%token CCE_NEG_هيٺاهون CCE_NEG_PRINT CCE_NEG_PUNCT CCE_NEG_SPACE CCE_NEG_مٿانهون CCE_NEG_XDIGIT

%کاٻي CCL_OP_DIFF CCL_OP_UNION

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

%token BEGIN_REPEAT_POSIX پڇاڙي_REPEAT_POSIX BEGIN_REPEAT_FLEX پڇاڙي_REPEAT_FLEX


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

#ضمن "flexdef.h"
#ضمن "tables.h"

صحيح pat, scnum, eps, headcnt, trailcnt, lastchar, i, rulelen;
ساكن صحيح currccl;
bool trlcontxt;
ساكن bool sc_is_exclusive, cclsorted, varlength, variable_trail_قاعدو;

صحيح *scon_stk;
صحيح scon_stk_ptr;

ساكن صحيح madeany = false;  /* whether we've made the '.' character class */
ساكن صحيح ccldot, cclany;
صحيح اڳيون_continued_action;	/* whether the previous rule's action was '|' */

#وصف_ڪريو format_warn3(fmt, a1, a2) \
	افعل{ \
        حرف fw3_نياپو[MAXLINE];\
        snprintf( fw3_نياپو, MAXLINE,(fmt), (a1), (a2) );\
        lwarn( fw3_نياپو );\
	}طالما(0)

/* Expand a POSIX character class expression. */
#وصف_ڪريو CCL_اظهار(func) \
	افعل{ \
	صحيح c; \
	لكل ( c = 0; c < ctrl.csize; ++c ) \
		إذا ( isascii(c) && func(c) ) \
			ccladd( currccl, c ); \
	}طالما(0)

/* negated class */
#وصف_ڪريو CCL_NEG_اظهار(func) \
	افعل{ \
	صحيح c; \
	لكل ( c = 0; c < ctrl.csize; ++c ) \
		إذا ( !func(c) ) \
			ccladd( currccl, c ); \
	}طالما(0)

/* While POSIX defines isblank(), it's not ANSI C. */
#وصف_ڪريو IS_BLANK(c) ((c) == ' ' || (c) == '\t')

/* On some over-ambitious machines, such as DEC Alpha's, the default
 * token type is "long" instead of "int"; this leads to problems with
 * declaring yylval in flexdef.h.  But so far, all the yacc's I've seen
 * wrap their definitions of YYSTYPE with "#ifndef YYSTYPE"'s, so the
 * following should ensure that the default token type is "int".
 */
#وصف_ڪريو YYSTYPE صحيح

%}

%%
goal		:  initlex sect1 sect1end sect2 initforrule
			{ /* add default rule */
			صحيح def_قاعدو;

			pat = cclinit();
			cclnegate( pat );

			def_قاعدو = mkstate( -pat );

			/* Remember the number of the default rule so we
			 * don't generate "can't match" warnings for it.
			 */
			default_قاعدو = انگ_قاعدا;

			پڄاڻي_قاعدو( def_قاعدو, false, 0, 0, 0);

			لكل ( i = 1; i <= lastsc; ++i )
				scset[i] = mkbranch( scset[i], def_قاعدو );

			جوڙيو_action("]]");

			إذا ( ctrl.spprdflt )
				جوڙيو_action(
				"M4_HOOK_FATAL_ERROR(\"flex scanner jammed\")");
			وإلا {
			    جوڙيو_action("M4_HOOK_ECHO");
			}

			جوڙيو_action( "\n\tM4_HOOK_STATE_CASE_BREAK\n" );
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
		|  TOK_اڳياڙي '=' NAME
			{ ctrl.اڳياڙي = xstrdup(nmstr);
                          إذا (strchr(ctrl.اڳياڙي, '[') || strchr(ctrl.اڳياڙي, ']'))
                              flexerror(_("Prefix must not contain [ or ]")); }
		|  TOK_YYCLASS '=' NAME
			{ ctrl.yyclass = xstrdup(nmstr); }
		|  TOK_سرو_FILE '=' NAME
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
			trlcontxt = variable_trail_قاعدو = varlength = false;
			trailcnt = headcnt = rulelen = 0;
			current_state_type = STATE_عام;
			اڳيون_continued_action = continued_action;
			اندريون_قاعدو = true;

			new_قاعدو();
			}
		;

flexrule	:  '^' قاعدو
			{
			pat = $2;
			پڄاڻي_قاعدو( pat, variable_trail_قاعدو,
				headcnt, trailcnt , اڳيون_continued_action);

			إذا ( scon_stk_ptr > 0 )
				{
				لكل ( i = 1; i <= scon_stk_ptr; ++i )
					scbol[scon_stk[i]] =
						mkbranch( scbol[scon_stk[i]],
								pat );
				}

			وإلا
				{
				/* Add to all non-exclusive start conditions,
				 * including the default (0) start condition.
				 */

				لكل ( i = 1; i <= lastsc; ++i )
					إذا ( ! scxclu[i] )
						scbol[i] = mkbranch( scbol[i],
									pat );
				}

			إذا ( ! bol_needed )
				{
				bol_needed = true;

				إذا ( env.performance_hint > 1 )
					pinpoint_پيغام(
			"'^' operator results in sub-optimal performance" );
				}
			}

		|  قاعدو
			{
			pat = $1;
			پڄاڻي_قاعدو( pat, variable_trail_قاعدو,
				headcnt, trailcnt , اڳيون_continued_action);

			إذا ( scon_stk_ptr > 0 )
				{
				لكل ( i = 1; i <= scon_stk_ptr; ++i )
					scset[scon_stk[i]] =
						mkbranch( scset[scon_stk[i]],
								pat );
				}

			وإلا
				{
				لكل ( i = 1; i <= lastsc; ++i )
					إذا ( ! scxclu[i] )
						scset[i] =
							mkbranch( scset[i],
								pat );
				}
			}

		|  EOF_OP
			{
			إذا ( scon_stk_ptr > 0 )
				build_eof_action();
	
			وإلا
				{
				/* This EOF applies to all start conditions
				 * which don't already have EOF actions.
				 */
				لكل ( i = 1; i <= lastsc; ++i )
					إذا ( ! sceof[i] )
						scon_stk[++scon_stk_ptr] = i;

				إذا ( scon_stk_ptr == 0 )
					lwarn(
			"all start conditions already have <<EOF>> rules" );

				وإلا
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

			لكل ( i = 1; i <= lastsc; ++i )
				{
				صحيح j;

				لكل ( j = 1; j <= scon_stk_ptr; ++j )
					إذا ( scon_stk[j] == i )
						اكسر;

				إذا ( j > scon_stk_ptr )
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
			إذا ( (scnum = sclookup( nmstr )) == 0 )
				format_pinpoint_پيغام(
					"undeclared start condition %s",
					nmstr );
			وإلا
				{
				لكل ( i = 1; i <= scon_stk_ptr; ++i )
					إذا ( scon_stk[i] == scnum )
						{
						format_warn(
							"<%s> specified twice",
							scname[scnum] );
						اكسر;
						}

				إذا ( i > scon_stk_ptr )
					scon_stk[++scon_stk_ptr] = scnum;
				}
			}
		;

قاعدو		:  re2 re
			{
			إذا ( transchar[lastst[$2]] != SYM_EPSILON )
				/* Provide final transition \now/ so it
				 * will be marked as a trailing context
				 * state.
				 */
				$2 = link_machines( $2,
						mkstate( SYM_EPSILON ) );

			mark_beginning_as_عام( $2 );
			current_state_type = STATE_عام;

			إذا ( اڳيون_continued_action )
				{
				/* We need to treat this as variable trailing
				 * context so that the backup does not happen
				 * in the action but before the action switch
				 * statement.  If the backup happens in the
				 * action, then the rules "falling into" this
				 * one's action will *also* do the backup,
				 * erroneously.
				 */
				إذا ( ! varlength || headcnt != 0 )
					lwarn(
		"trailing context made variable due to preceding '|' action" );

				/* Mark as variable. */
				varlength = true;
				headcnt = 0;

				}

			إذا ( ctrl.lex_compat || (varlength && headcnt == 0) )
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
				جوڙيو_accept( $1,
					انگ_قاعدا | YY_TRAILING_سر_نقاب );
				variable_trail_قاعدو = true;
				}
			
			وإلا
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

			إذا ( trlcontxt )
				{
				synerr( _("trailing context used twice") );
				$$ = mkstate( SYM_EPSILON );
				}

			وإلا إذا ( اڳيون_continued_action )
				{
				/* See the comment in the rule for "re2 re"
				 * above.
				 */
				lwarn(
		"trailing context made variable due to preceding '|' action" );

				varlength = true;
				}

			إذا ( ctrl.lex_compat || varlength )
				{
				/* Again, see the comment in the rule for
				 * "re2 re" above.
				 */
				جوڙيو_accept( $1,
					انگ_قاعدا | YY_TRAILING_سر_نقاب );
				variable_trail_قاعدو = true;
				}

			trlcontxt = true;

			eps = mkstate( SYM_EPSILON );
			$$ = link_machines( $1,
				link_machines( eps, mkstate( '\n' ) ) );
			}

		|  re
			{
			$$ = $1;

			إذا ( trlcontxt )
				{
				إذا ( ctrl.lex_compat || (varlength && headcnt == 0) )
					/* Both head and trail are
					 * variable-length.
					 */
					variable_trail_قاعدو = true;
				وإلا
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

			إذا ( trlcontxt )
				synerr( _("trailing context used twice") );
			وإلا
				trlcontxt = true;

			إذا ( varlength )
				/* We hope the trailing context is
				 * fixed-length.
				 */
				varlength = false;
			وإلا
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

		|  series BEGIN_REPEAT_POSIX عدد ',' عدد پڇاڙي_REPEAT_POSIX
			{
			varlength = true;

			إذا ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			وإلا
				{
				إذا ( $3 == 0 )
					{
					إذا ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					وإلا
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				وإلا
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  series BEGIN_REPEAT_POSIX عدد ',' پڇاڙي_REPEAT_POSIX
			{
			varlength = true;

			إذا ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			وإلا
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  series BEGIN_REPEAT_POSIX عدد پڇاڙي_REPEAT_POSIX
			{
			/* The series could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			إذا ( $3 <= 0 )
				{
				  synerr( _("iteration value must be positive")
					  );
				$$ = $1;
				}

			وإلا
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

		|  singleton BEGIN_REPEAT_FLEX عدد ',' عدد پڇاڙي_REPEAT_FLEX
			{
			varlength = true;

			إذا ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			وإلا
				{
				إذا ( $3 == 0 )
					{
					إذا ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					وإلا
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				وإلا
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  singleton BEGIN_REPEAT_FLEX عدد ',' پڇاڙي_REPEAT_FLEX
			{
			varlength = true;

			إذا ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			وإلا
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  singleton BEGIN_REPEAT_FLEX عدد پڇاڙي_REPEAT_FLEX
			{
			/* The singleton could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			إذا ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			وإلا
				$$ = link_machines( $1,
						copysingl( $1, $3 - 1 ) );
			}

		|  '.'
			{
			إذا ( ! madeany )
				{
				/* Create the '.' character class. */
                    ccldot = cclinit();
                    ccladd( ccldot, '\n' );
                    cclnegate( ccldot );

                    إذا ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[ccldot],
                            ccllen[ccldot], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				/* Create the (?s:'.') character class. */
                    cclany = cclinit();
                    cclnegate( cclany );

                    إذا ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[cclany],
                            ccllen[cclany], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				madeany = true;
				}

			++rulelen;

            إذا (sf_dot_all())
                $$ = mkstate( -cclany );
            وإلا
                $$ = mkstate( -ccldot );
			}

		|  fullccl
			{
				/* Sort characters for fast searching.
				 */
				qsort( ccltbl + cclmap[$1], (size_t) ccllen[$1], حجم (*ccltbl), cclcmp );

			إذا ( ctrl.useecs )
				mkeccl( ccltbl + cclmap[$1], ccllen[$1],
					nextecm, ecgroup, ctrl.csize, ctrl.csize);

			++rulelen;

			إذا (ccl_has_nl[$1])
				قاعدو_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  PREVCCL
			{
			++rulelen;

			إذا (ccl_has_nl[$1])
				قاعدو_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  '"' string '"'
			{ $$ = $2; }

		|  '(' re ')'
			{ $$ = $2; }

		|  CHAR
			{
			++rulelen;

			إذا ($1 == nlch)
				قاعدو_has_nl[num_rules] = true;

            إذا (sf_case_ins() && has_case($1))
                /* create an alternation, as in (a|A) */
                $$ = mkor (mkstate($1), mkstate(ابتو_case($1)));
            وإلا
                $$ = mkstate( $1 );
			}
		;
fullccl:
        fullccl CCL_OP_DIFF  braceccl  { $$ = ccl_سيٽ_diff  ($1, $3); }
    |   fullccl CCL_OP_UNION braceccl  { $$ = ccl_سيٽ_union ($1, $3); }
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

			إذا (sf_case_ins())
			  {

			    /* If one end of the range has case and the other
			     * does not, or the cases are different, then we're not
			     * sure what range the user is trying to express.
			     * Examples: [@-z] or [S-t]
			     */
			    إذا (has_case ($2) != has_case ($4)
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
			    وإلا إذا (!has_case ($2) && !has_case ($4) && !range_covers_case ($2, $4))
			      format_warn3 (
			      _("the character range [%c-%c] is ambiguous in a case-insensitive scanner"),
					    $2, $4);
			  }

			إذا ( $2 > $4 )
				synerr( _("negative range in character class") );

			وإلا
				{
				لكل ( i = $2; i <= $4; ++i )
					ccladd( $1, i );

				/* Keep track if this ccl is staying in
				 * alphabetical order.
				 */
				cclsorted = cclsorted && ($2 > lastchar);
				lastchar = $4;

                /* Do it again for upper/lowercase */
                إذا (sf_case_ins() && has_case($2) && has_case($4)){
                    $2 = ابتو_case ($2);
                    $4 = ابتو_case ($4);
                    
                    لكل ( i = $2; i <= $4; ++i )
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
            إذا (sf_case_ins() && has_case($2)){
                $2 = ابتو_case ($2);
                ccladd ($1, $2);

                cclsorted = cclsorted && ($2 > lastchar);
                lastchar = $2;
            }

			$$ = $1;
			}

		|  ccl ccl_اظهار
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

ccl_اظهار:	   
           CCE_ALNUM	{ CCL_اظهار(اکر_يا_انگ); }
		|  CCE_ALPHA	{ CCL_اظهار(اکر_آهي); }
		|  CCE_BLANK	{ CCL_اظهار(IS_BLANK); }
		|  CCE_CNTRL	{ CCL_اظهار(iscntrl); }
		|  CCE_DIGIT	{ CCL_اظهار(انگ_آهي); }
		|  CCE_گراف	{ CCL_اظهار(isgraph); }
		|  CCE_هيٺاهون	{ 
                          CCL_اظهار(islower);
                          إذا (sf_case_ins())
                              CCL_اظهار(isupper);
                        }
		|  CCE_PRINT	{ CCL_اظهار(isprint); }
		|  CCE_PUNCT	{ CCL_اظهار(ispunct); }
		|  CCE_SPACE	{ CCL_اظهار(خال_آهي); }
		|  CCE_XDIGIT	{ CCL_اظهار(isxdigit); }
		|  CCE_مٿانهون	{
                    CCL_اظهار(isupper);
                    إذا (sf_case_ins())
                        CCL_اظهار(islower);
				}

        |  CCE_NEG_ALNUM	{ CCL_NEG_اظهار(اکر_يا_انگ); }
		|  CCE_NEG_ALPHA	{ CCL_NEG_اظهار(اکر_آهي); }
		|  CCE_NEG_BLANK	{ CCL_NEG_اظهار(IS_BLANK); }
		|  CCE_NEG_CNTRL	{ CCL_NEG_اظهار(iscntrl); }
		|  CCE_NEG_DIGIT	{ CCL_NEG_اظهار(انگ_آهي); }
		|  CCE_NEG_گراف	{ CCL_NEG_اظهار(isgraph); }
		|  CCE_NEG_PRINT	{ CCL_NEG_اظهار(isprint); }
		|  CCE_NEG_PUNCT	{ CCL_NEG_اظهار(ispunct); }
		|  CCE_NEG_SPACE	{ CCL_NEG_اظهار(خال_آهي); }
		|  CCE_NEG_XDIGIT	{ CCL_NEG_اظهار(isxdigit); }
		|  CCE_NEG_هيٺاهون	{ 
				إذا ( sf_case_ins() )
					lwarn(_("[:^lower:] is ambiguous in case insensitive scanner"));
				وإلا
					CCL_NEG_اظهار(islower);
				}
		|  CCE_NEG_مٿانهون	{
				إذا ( sf_case_ins() )
					lwarn(_("[:^upper:] ambiguous in case insensitive scanner"));
				وإلا
					CCL_NEG_اظهار(isupper);
				}
		;
		
string		:  string CHAR
			{
			إذا ( $2 == nlch )
				قاعدو_has_nl[num_rules] = true;

			++rulelen;

            إذا (sf_case_ins() && has_case($2))
                $$ = mkor (mkstate($2), mkstate(ابتو_case($2)));
            وإلا
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

فراغ build_eof_action(فراغ)
	{
	صحيح i;
	حرف action_متن[MAXLINE];

	لكل ( i = 1; i <= scon_stk_ptr; ++i )
		{
		إذا ( sceof[scon_stk[i]] )
			format_pinpoint_پيغام(
				"multiple <<EOF>> rules for start condition %s",
				scname[scon_stk[i]] );

		وإلا
			{
			sceof[scon_stk[i]] = true;

			إذا (اڳيون_continued_action /* && previous action was regular */)
				جوڙيو_action("YY_RULE_SETUP\n");

			snprintf( action_متن, حجم(action_متن), "M4_HOOK_EOF_STATE_CASE_ARM(%s)\n",
				scname[scon_stk[i]] );
			جوڙيو_action( action_متن );
			}
		}

	سٽ_directive_ٻاهريون(عدم, infilename, linenum);
        جوڙيو_action("[[");

	/* This isn't a normal rule after all - don't count it as
	 * such, so we don't have any holes in the rule numbering
	 * (which make generating "rule can never match" warnings
	 * more difficult.
	 */
	--num_rules;
	++انگ_eof_قاعدا;
	}


/* format_synerr - write out formatted syntax error */

فراغ format_synerr( ثابت حرف *نياپو, ثابت حرف arg[] )
	{
	حرف errmsg[MAXLINE];

	(فراغ) snprintf( errmsg, حجم(errmsg), نياپو, arg );
	synerr( errmsg );
	}


/* synerr - report a syntax error */

فراغ synerr( ثابت حرف *str )
	{
	syntaxerror = true;
	pinpoint_پيغام( str );
	}


/* format_warn - write out formatted warning */

فراغ format_warn( ثابت حرف *نياپو, ثابت حرف arg[] )
	{
	حرف warn_نياپو[MAXLINE];

	snprintf( warn_نياپو, حجم(warn_نياپو), نياپو, arg );
	lwarn( warn_نياپو );
	}


/* lwarn - report a warning, unless -w was given */

فراغ lwarn( ثابت حرف *str )
	{
	سٽ_warning( str, linenum );
	}

/* format_pinpoint_message - write out a message formatted with one string,
 *			     pinpointing its location
 */

فراغ format_pinpoint_پيغام( ثابت حرف *نياپو, ثابت حرف arg[] )
	{
	حرف errmsg[MAXLINE*2];

	snprintf( errmsg, حجم(errmsg), نياپو, arg );
	pinpoint_پيغام( errmsg );
	}


/* pinpoint_message - write out a message, pinpointing its location */

فراغ pinpoint_پيغام( ثابت حرف *str )
	{
	سٽ_pinpoint( str, linenum );
	}


/* line_warning - report a warning at a given line, unless -w was given */

فراغ سٽ_warning( ثابت حرف *str, صحيح سٽ )
	{
	حرف warning[MAXLINE*2];

	إذا ( ! env.nowarn )
		{
		snprintf( warning, حجم(warning), "warning, %s", str );
		سٽ_pinpoint( warning, سٽ );
		}
	}


/* line_pinpoint - write out a message, pinpointing it at the given line */

فراغ سٽ_pinpoint( ثابت حرف *str, صحيح سٽ )
	{
	fprintf( stderr, "%s:%d: %s\n", infilename, سٽ, str );
	}


/* yyerror - eat up an error message from the parser;
 *	     currently, messages are ignore
 */

فراغ yyerror( ثابت حرف *نياپو )
	{
		(فراغ)نياپو;
	}
