/* parse.y - parser for flex input */

%token CHAR सङ्ख्या SECTEND SCDECL XSCDECL NAME PREVCCL EOF_OP
%token TOK_OPTION TOK_OUTFILE TOK_PREFIX TOK_YYCLASS TOK_HEADER_FILE TOK_EXTRA_TYPE
%token TOK_TABLES_FILE TOK_YYLMAX TOK_NUMERIC TOK_YYDECL TOK_PREACTION TOK_POSTACTION
%token TOK_USERINIT TOK_EMIT TOK_BUFSIZE TOK_YYTERMINATE

%token CCE_ALNUM CCE_ALPHA CCE_BLANK CCE_CNTRL CCE_DIGIT CCE_GRAPH
%token CCE_LOWER CCE_PRINT CCE_PUNCT CCE_SPACE CCE_UPPER CCE_XDIGIT

%token CCE_NEG_ALNUM CCE_NEG_ALPHA CCE_NEG_BLANK CCE_NEG_CNTRL CCE_NEG_DIGIT CCE_NEG_GRAPH
%token CCE_NEG_LOWER CCE_NEG_PRINT CCE_NEG_PUNCT CCE_NEG_SPACE CCE_NEG_UPPER CCE_NEG_XDIGIT

%left CCL_OP_DIFF CCL_OP_UNION

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

%token BEGIN_REPEAT_POSIX END_REPEAT_POSIX BEGIN_REPEAT_FLEX END_REPEAT_FLEX


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

#अन्तर्भाव "flexdef.h"
#अन्तर्भाव "tables.h"

पूर्णाङ्क pat, scnum, eps, headcnt, trailcnt, lastchar, i, rulelen;
स्थिर पूर्णाङ्क currccl;
bool trlcontxt;
स्थिर bool sc_is_exclusive, cclsorted, varlength, variable_trail_rule;

पूर्णाङ्क *scon_stk;
पूर्णाङ्क scon_stk_ptr;

स्थिर पूर्णाङ्क madeany = false;  /* whether we've made the '.' character class */
स्थिर पूर्णाङ्क ccldot, cclany;
पूर्णाङ्क previous_continued_action;	/* whether the previous rule's action was '|' */

#define format_warn3(fmt, a1, a2) \
	करेहि{ \
        वर्ण fw3_सन्देशः[MAXLINE];\
        snprintf( fw3_सन्देशः, MAXLINE,(fmt), (a1), (a2) );\
        lwarn( fw3_सन्देशः );\
	}जाव(0)

/* Expand a POSIX character class expression. */
#define CCL_व्यञ्जकम्(func) \
	करेहि{ \
	पूर्णाङ्क c; \
	प्रति ( c = 0; c < ctrl.csize; ++c ) \
		जइ ( isascii(c) && func(c) ) \
			ccladd( currccl, c ); \
	}जाव(0)

/* negated class */
#define CCL_NEG_व्यञ्जकम्(func) \
	करेहि{ \
	पूर्णाङ्क c; \
	प्रति ( c = 0; c < ctrl.csize; ++c ) \
		जइ ( !func(c) ) \
			ccladd( currccl, c ); \
	}जाव(0)

/* While POSIX defines isblank(), it's not ANSI C. */
#define IS_BLANK(c) ((c) == ' ' || (c) == '\t')

/* On some over-ambitious machines, such as DEC Alpha's, the default
 * token type is "long" instead of "int"; this leads to problems with
 * declaring yylval in flexdef.h.  But so far, all the yacc's I've seen
 * wrap their definitions of YYSTYPE with "#ifndef YYSTYPE"'s, so the
 * following should ensure that the default token type is "int".
 */
#define YYSTYPE पूर्णाङ्क

%}

%%
goal		:  initlex sect1 sect1end sect2 initforrule
			{ /* add default rule */
			पूर्णाङ्क def_rule;

			pat = cclinit();
			cclnegate( pat );

			def_rule = mkstate( -pat );

			/* Remember the number of the default rule so we
			 * don't generate "can't match" warnings for it.
			 */
			default_rule = अङ्कः_rules;

			finish_rule( def_rule, false, 0, 0, 0);

			प्रति ( i = 1; i <= lastsc; ++i )
				scset[i] = mkbranch( scset[i], def_rule );

			add_action("]]");

			जइ ( ctrl.spprdflt )
				add_action(
				"M4_HOOK_FATAL_ERROR(\"flex scanner jammed\")");
			अण्णहा {
			    add_action("M4_HOOK_ECHO");
			}

			add_action( "\n\tM4_HOOK_STATE_CASE_BREAK\n" );
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
		|  TOK_PREFIX '=' NAME
			{ ctrl.prefix = xstrdup(nmstr);
                          जइ (strchr(ctrl.prefix, '[') || strchr(ctrl.prefix, ']'))
                              flexerror(_("Prefix must not contain [ or ]")); }
		|  TOK_YYCLASS '=' NAME
			{ ctrl.yyclass = xstrdup(nmstr); }
		|  TOK_HEADER_FILE '=' NAME
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
			trlcontxt = variable_trail_rule = varlength = false;
			trailcnt = headcnt = rulelen = 0;
			current_state_type = STATE_NORMAL;
			previous_continued_action = continued_action;
			in_rule = true;

			new_rule();
			}
		;

flexrule	:  '^' rule
			{
			pat = $2;
			finish_rule( pat, variable_trail_rule,
				headcnt, trailcnt , previous_continued_action);

			जइ ( scon_stk_ptr > 0 )
				{
				प्रति ( i = 1; i <= scon_stk_ptr; ++i )
					scbol[scon_stk[i]] =
						mkbranch( scbol[scon_stk[i]],
								pat );
				}

			अण्णहा
				{
				/* Add to all non-exclusive start conditions,
				 * including the default (0) start condition.
				 */

				प्रति ( i = 1; i <= lastsc; ++i )
					जइ ( ! scxclu[i] )
						scbol[i] = mkbranch( scbol[i],
									pat );
				}

			जइ ( ! bol_needed )
				{
				bol_needed = true;

				जइ ( env.performance_hint > 1 )
					pinpoint_message(
			"'^' operator results in sub-optimal performance" );
				}
			}

		|  rule
			{
			pat = $1;
			finish_rule( pat, variable_trail_rule,
				headcnt, trailcnt , previous_continued_action);

			जइ ( scon_stk_ptr > 0 )
				{
				प्रति ( i = 1; i <= scon_stk_ptr; ++i )
					scset[scon_stk[i]] =
						mkbranch( scset[scon_stk[i]],
								pat );
				}

			अण्णहा
				{
				प्रति ( i = 1; i <= lastsc; ++i )
					जइ ( ! scxclu[i] )
						scset[i] =
							mkbranch( scset[i],
								pat );
				}
			}

		|  EOF_OP
			{
			जइ ( scon_stk_ptr > 0 )
				build_eof_action();
	
			अण्णहा
				{
				/* This EOF applies to all start conditions
				 * which don't already have EOF actions.
				 */
				प्रति ( i = 1; i <= lastsc; ++i )
					जइ ( ! sceof[i] )
						scon_stk[++scon_stk_ptr] = i;

				जइ ( scon_stk_ptr == 0 )
					lwarn(
			"all start conditions already have <<EOF>> rules" );

				अण्णहा
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

			प्रति ( i = 1; i <= lastsc; ++i )
				{
				पूर्णाङ्क j;

				प्रति ( j = 1; j <= scon_stk_ptr; ++j )
					जइ ( scon_stk[j] == i )
						भङ्ग;

				जइ ( j > scon_stk_ptr )
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
			जइ ( (scnum = sclookup( nmstr )) == 0 )
				format_pinpoint_message(
					"undeclared start condition %s",
					nmstr );
			अण्णहा
				{
				प्रति ( i = 1; i <= scon_stk_ptr; ++i )
					जइ ( scon_stk[i] == scnum )
						{
						format_warn(
							"<%s> specified twice",
							scname[scnum] );
						भङ्ग;
						}

				जइ ( i > scon_stk_ptr )
					scon_stk[++scon_stk_ptr] = scnum;
				}
			}
		;

rule		:  re2 re
			{
			जइ ( transchar[lastst[$2]] != SYM_EPSILON )
				/* Provide final transition \now/ so it
				 * will be marked as a trailing context
				 * state.
				 */
				$2 = link_machines( $2,
						mkstate( SYM_EPSILON ) );

			mark_beginning_as_normal( $2 );
			current_state_type = STATE_NORMAL;

			जइ ( previous_continued_action )
				{
				/* We need to treat this as variable trailing
				 * context so that the backup does not happen
				 * in the action but before the action switch
				 * statement.  If the backup happens in the
				 * action, then the rules "falling into" this
				 * one's action will *also* do the backup,
				 * erroneously.
				 */
				जइ ( ! varlength || headcnt != 0 )
					lwarn(
		"trailing context made variable due to preceding '|' action" );

				/* Mark as variable. */
				varlength = true;
				headcnt = 0;

				}

			जइ ( ctrl.lex_compat || (varlength && headcnt == 0) )
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
				add_accept( $1,
					अङ्कः_rules | YY_TRAILING_HEAD_MASK );
				variable_trail_rule = true;
				}
			
			अण्णहा
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

			जइ ( trlcontxt )
				{
				synerr( _("trailing context used twice") );
				$$ = mkstate( SYM_EPSILON );
				}

			अण्णहा जइ ( previous_continued_action )
				{
				/* See the comment in the rule for "re2 re"
				 * above.
				 */
				lwarn(
		"trailing context made variable due to preceding '|' action" );

				varlength = true;
				}

			जइ ( ctrl.lex_compat || varlength )
				{
				/* Again, see the comment in the rule for
				 * "re2 re" above.
				 */
				add_accept( $1,
					अङ्कः_rules | YY_TRAILING_HEAD_MASK );
				variable_trail_rule = true;
				}

			trlcontxt = true;

			eps = mkstate( SYM_EPSILON );
			$$ = link_machines( $1,
				link_machines( eps, mkstate( '\n' ) ) );
			}

		|  re
			{
			$$ = $1;

			जइ ( trlcontxt )
				{
				जइ ( ctrl.lex_compat || (varlength && headcnt == 0) )
					/* Both head and trail are
					 * variable-length.
					 */
					variable_trail_rule = true;
				अण्णहा
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

			जइ ( trlcontxt )
				synerr( _("trailing context used twice") );
			अण्णहा
				trlcontxt = true;

			जइ ( varlength )
				/* We hope the trailing context is
				 * fixed-length.
				 */
				varlength = false;
			अण्णहा
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

		|  series BEGIN_REPEAT_POSIX सङ्ख्या ',' सङ्ख्या END_REPEAT_POSIX
			{
			varlength = true;

			जइ ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			अण्णहा
				{
				जइ ( $3 == 0 )
					{
					जइ ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					अण्णहा
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				अण्णहा
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  series BEGIN_REPEAT_POSIX सङ्ख्या ',' END_REPEAT_POSIX
			{
			varlength = true;

			जइ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			अण्णहा
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  series BEGIN_REPEAT_POSIX सङ्ख्या END_REPEAT_POSIX
			{
			/* The series could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			जइ ( $3 <= 0 )
				{
				  synerr( _("iteration value must be positive")
					  );
				$$ = $1;
				}

			अण्णहा
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

		|  singleton BEGIN_REPEAT_FLEX सङ्ख्या ',' सङ्ख्या END_REPEAT_FLEX
			{
			varlength = true;

			जइ ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			अण्णहा
				{
				जइ ( $3 == 0 )
					{
					जइ ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					अण्णहा
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				अण्णहा
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  singleton BEGIN_REPEAT_FLEX सङ्ख्या ',' END_REPEAT_FLEX
			{
			varlength = true;

			जइ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			अण्णहा
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  singleton BEGIN_REPEAT_FLEX सङ्ख्या END_REPEAT_FLEX
			{
			/* The singleton could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			जइ ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			अण्णहा
				$$ = link_machines( $1,
						copysingl( $1, $3 - 1 ) );
			}

		|  '.'
			{
			जइ ( ! madeany )
				{
				/* Create the '.' character class. */
                    ccldot = cclinit();
                    ccladd( ccldot, '\n' );
                    cclnegate( ccldot );

                    जइ ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[ccldot],
                            ccllen[ccldot], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				/* Create the (?s:'.') character class. */
                    cclany = cclinit();
                    cclnegate( cclany );

                    जइ ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[cclany],
                            ccllen[cclany], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				madeany = true;
				}

			++rulelen;

            जइ (sf_dot_all())
                $$ = mkstate( -cclany );
            अण्णहा
                $$ = mkstate( -ccldot );
			}

		|  fullccl
			{
				/* Sort characters for fast searching.
				 */
				qsort( ccltbl + cclmap[$1], (size_t) ccllen[$1], परिमाण (*ccltbl), cclcmp );

			जइ ( ctrl.useecs )
				mkeccl( ccltbl + cclmap[$1], ccllen[$1],
					nextecm, ecgroup, ctrl.csize, ctrl.csize);

			++rulelen;

			जइ (ccl_has_nl[$1])
				rule_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  PREVCCL
			{
			++rulelen;

			जइ (ccl_has_nl[$1])
				rule_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  '"' string '"'
			{ $$ = $2; }

		|  '(' re ')'
			{ $$ = $2; }

		|  CHAR
			{
			++rulelen;

			जइ ($1 == nlch)
				rule_has_nl[num_rules] = true;

            जइ (sf_case_ins() && has_case($1))
                /* create an alternation, as in (a|A) */
                $$ = mkor (mkstate($1), mkstate(reverse_case($1)));
            अण्णहा
                $$ = mkstate( $1 );
			}
		;
fullccl:
        fullccl CCL_OP_DIFF  braceccl  { $$ = ccl_set_diff  ($1, $3); }
    |   fullccl CCL_OP_UNION braceccl  { $$ = ccl_set_union ($1, $3); }
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

			जइ (sf_case_ins())
			  {

			    /* If one end of the range has case and the other
			     * does not, or the cases are different, then we're not
			     * sure what range the user is trying to express.
			     * Examples: [@-z] or [S-t]
			     */
			    जइ (has_case ($2) != has_case ($4)
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
			    अण्णहा जइ (!has_case ($2) && !has_case ($4) && !range_covers_case ($2, $4))
			      format_warn3 (
			      _("the character range [%c-%c] is ambiguous in a case-insensitive scanner"),
					    $2, $4);
			  }

			जइ ( $2 > $4 )
				synerr( _("negative range in character class") );

			अण्णहा
				{
				प्रति ( i = $2; i <= $4; ++i )
					ccladd( $1, i );

				/* Keep track if this ccl is staying in
				 * alphabetical order.
				 */
				cclsorted = cclsorted && ($2 > lastchar);
				lastchar = $4;

                /* Do it again for upper/lowercase */
                जइ (sf_case_ins() && has_case($2) && has_case($4)){
                    $2 = reverse_case ($2);
                    $4 = reverse_case ($4);
                    
                    प्रति ( i = $2; i <= $4; ++i )
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
            जइ (sf_case_ins() && has_case($2)){
                $2 = reverse_case ($2);
                ccladd ($1, $2);

                cclsorted = cclsorted && ($2 > lastchar);
                lastchar = $2;
            }

			$$ = $1;
			}

		|  ccl ccl_व्यञ्जकम्
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

ccl_व्यञ्जकम्:	   
           CCE_ALNUM	{ CCL_व्यञ्जकम्(isalnum); }
		|  CCE_ALPHA	{ CCL_व्यञ्जकम्(isalpha); }
		|  CCE_BLANK	{ CCL_व्यञ्जकम्(IS_BLANK); }
		|  CCE_CNTRL	{ CCL_व्यञ्जकम्(iscntrl); }
		|  CCE_DIGIT	{ CCL_व्यञ्जकम्(isdigit); }
		|  CCE_GRAPH	{ CCL_व्यञ्जकम्(isgraph); }
		|  CCE_LOWER	{ 
                          CCL_व्यञ्जकम्(islower);
                          जइ (sf_case_ins())
                              CCL_व्यञ्जकम्(isupper);
                        }
		|  CCE_PRINT	{ CCL_व्यञ्जकम्(isprint); }
		|  CCE_PUNCT	{ CCL_व्यञ्जकम्(ispunct); }
		|  CCE_SPACE	{ CCL_व्यञ्जकम्(isspace); }
		|  CCE_XDIGIT	{ CCL_व्यञ्जकम्(isxdigit); }
		|  CCE_UPPER	{
                    CCL_व्यञ्जकम्(isupper);
                    जइ (sf_case_ins())
                        CCL_व्यञ्जकम्(islower);
				}

        |  CCE_NEG_ALNUM	{ CCL_NEG_व्यञ्जकम्(isalnum); }
		|  CCE_NEG_ALPHA	{ CCL_NEG_व्यञ्जकम्(isalpha); }
		|  CCE_NEG_BLANK	{ CCL_NEG_व्यञ्जकम्(IS_BLANK); }
		|  CCE_NEG_CNTRL	{ CCL_NEG_व्यञ्जकम्(iscntrl); }
		|  CCE_NEG_DIGIT	{ CCL_NEG_व्यञ्जकम्(isdigit); }
		|  CCE_NEG_GRAPH	{ CCL_NEG_व्यञ्जकम्(isgraph); }
		|  CCE_NEG_PRINT	{ CCL_NEG_व्यञ्जकम्(isprint); }
		|  CCE_NEG_PUNCT	{ CCL_NEG_व्यञ्जकम्(ispunct); }
		|  CCE_NEG_SPACE	{ CCL_NEG_व्यञ्जकम्(isspace); }
		|  CCE_NEG_XDIGIT	{ CCL_NEG_व्यञ्जकम्(isxdigit); }
		|  CCE_NEG_LOWER	{ 
				जइ ( sf_case_ins() )
					lwarn(_("[:^lower:] is ambiguous in case insensitive scanner"));
				अण्णहा
					CCL_NEG_व्यञ्जकम्(islower);
				}
		|  CCE_NEG_UPPER	{
				जइ ( sf_case_ins() )
					lwarn(_("[:^upper:] ambiguous in case insensitive scanner"));
				अण्णहा
					CCL_NEG_व्यञ्जकम्(isupper);
				}
		;
		
string		:  string CHAR
			{
			जइ ( $2 == nlch )
				rule_has_nl[num_rules] = true;

			++rulelen;

            जइ (sf_case_ins() && has_case($2))
                $$ = mkor (mkstate($2), mkstate(reverse_case($2)));
            अण्णहा
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

शून्य build_eof_action(शून्य)
	{
	पूर्णाङ्क i;
	वर्ण action_text[MAXLINE];

	प्रति ( i = 1; i <= scon_stk_ptr; ++i )
		{
		जइ ( sceof[scon_stk[i]] )
			format_pinpoint_message(
				"multiple <<EOF>> rules for start condition %s",
				scname[scon_stk[i]] );

		अण्णहा
			{
			sceof[scon_stk[i]] = true;

			जइ (previous_continued_action /* && previous action was regular */)
				add_action("YY_RULE_SETUP\n");

			snprintf( action_text, परिमाण(action_text), "M4_HOOK_EOF_STATE_CASE_ARM(%s)\n",
				scname[scon_stk[i]] );
			add_action( action_text );
			}
		}

	पङ्क्तिः_directive_out(रिक्त, infilename, linenum);
        add_action("[[");

	/* This isn't a normal rule after all - don't count it as
	 * such, so we don't have any holes in the rule numbering
	 * (which make generating "rule can never match" warnings
	 * more difficult.
	 */
	--num_rules;
	++अङ्कः_eof_rules;
	}


/* format_synerr - write out formatted syntax error */

शून्य format_synerr( ध्रुव वर्ण *सन्देशः, ध्रुव वर्ण arg[] )
	{
	वर्ण errmsg[MAXLINE];

	(शून्य) snprintf( errmsg, परिमाण(errmsg), सन्देशः, arg );
	synerr( errmsg );
	}


/* synerr - report a syntax error */

शून्य synerr( ध्रुव वर्ण *str )
	{
	syntaxerror = true;
	pinpoint_message( str );
	}


/* format_warn - write out formatted warning */

शून्य format_warn( ध्रुव वर्ण *सन्देशः, ध्रुव वर्ण arg[] )
	{
	वर्ण warn_सन्देशः[MAXLINE];

	snprintf( warn_सन्देशः, परिमाण(warn_सन्देशः), सन्देशः, arg );
	lwarn( warn_सन्देशः );
	}


/* lwarn - report a warning, unless -w was given */

शून्य lwarn( ध्रुव वर्ण *str )
	{
	पङ्क्तिः_warning( str, linenum );
	}

/* format_pinpoint_message - write out a message formatted with one string,
 *			     pinpointing its location
 */

शून्य format_pinpoint_message( ध्रुव वर्ण *सन्देशः, ध्रुव वर्ण arg[] )
	{
	वर्ण errmsg[MAXLINE*2];

	snprintf( errmsg, परिमाण(errmsg), सन्देशः, arg );
	pinpoint_message( errmsg );
	}


/* pinpoint_message - write out a message, pinpointing its location */

शून्य pinpoint_message( ध्रुव वर्ण *str )
	{
	पङ्क्तिः_pinpoint( str, linenum );
	}


/* line_warning - report a warning at a given line, unless -w was given */

शून्य पङ्क्तिः_warning( ध्रुव वर्ण *str, पूर्णाङ्क पङ्क्तिः )
	{
	वर्ण warning[MAXLINE*2];

	जइ ( ! env.nowarn )
		{
		snprintf( warning, परिमाण(warning), "warning, %s", str );
		पङ्क्तिः_pinpoint( warning, पङ्क्तिः );
		}
	}


/* line_pinpoint - write out a message, pinpointing it at the given line */

शून्य पङ्क्तिः_pinpoint( ध्रुव वर्ण *str, पूर्णाङ्क पङ्क्तिः )
	{
	fprintf( stderr, "%s:%d: %s\n", infilename, पङ्क्तिः, str );
	}


/* yyerror - eat up an error message from the parser;
 *	     currently, messages are ignore
 */

शून्य yyerror( ध्रुव वर्ण *सन्देशः )
	{
		(शून्य)सन्देशः;
	}
