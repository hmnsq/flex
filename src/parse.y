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
	गर{ \
        वर्ण fw3_सन्देश[MAXLINE];\
        snprintf( fw3_सन्देश, MAXLINE,(fmt), (a1), (a2) );\
        lwarn( fw3_सन्देश );\
	}जबसम्म(0)

/* Expand a POSIX character class expression. */
#define CCL_अभिव्यक्ति(func) \
	गर{ \
	पूर्णाङ्क c; \
	लागि ( c = 0; c < ctrl.csize; ++c ) \
		यदि ( isascii(c) && func(c) ) \
			ccladd( currccl, c ); \
	}जबसम्म(0)

/* negated class */
#define CCL_NEG_अभिव्यक्ति(func) \
	गर{ \
	पूर्णाङ्क c; \
	लागि ( c = 0; c < ctrl.csize; ++c ) \
		यदि ( !func(c) ) \
			ccladd( currccl, c ); \
	}जबसम्म(0)

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
			default_rule = अङ्क_rules;

			finish_rule( def_rule, false, 0, 0, 0);

			लागि ( i = 1; i <= lastsc; ++i )
				scset[i] = mkbranch( scset[i], def_rule );

			add_action("]]");

			यदि ( ctrl.spprdflt )
				add_action(
				"M4_HOOK_FATAL_ERROR(\"flex scanner jammed\")");
			अन्यथा {
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
                          यदि (म_अक्षर(ctrl.prefix, '[') || म_अक्षर(ctrl.prefix, ']'))
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

			यदि ( scon_stk_ptr > 0 )
				{
				लागि ( i = 1; i <= scon_stk_ptr; ++i )
					scbol[scon_stk[i]] =
						mkbranch( scbol[scon_stk[i]],
								pat );
				}

			अन्यथा
				{
				/* Add to all non-exclusive start conditions,
				 * including the default (0) start condition.
				 */

				लागि ( i = 1; i <= lastsc; ++i )
					यदि ( ! scxclu[i] )
						scbol[i] = mkbranch( scbol[i],
									pat );
				}

			यदि ( ! bol_needed )
				{
				bol_needed = true;

				यदि ( env.performance_hint > 1 )
					pinpoint_message(
			"'^' operator results in sub-optimal performance" );
				}
			}

		|  rule
			{
			pat = $1;
			finish_rule( pat, variable_trail_rule,
				headcnt, trailcnt , previous_continued_action);

			यदि ( scon_stk_ptr > 0 )
				{
				लागि ( i = 1; i <= scon_stk_ptr; ++i )
					scset[scon_stk[i]] =
						mkbranch( scset[scon_stk[i]],
								pat );
				}

			अन्यथा
				{
				लागि ( i = 1; i <= lastsc; ++i )
					यदि ( ! scxclu[i] )
						scset[i] =
							mkbranch( scset[i],
								pat );
				}
			}

		|  EOF_OP
			{
			यदि ( scon_stk_ptr > 0 )
				build_eof_action();
	
			अन्यथा
				{
				/* This EOF applies to all start conditions
				 * which don't already have EOF actions.
				 */
				लागि ( i = 1; i <= lastsc; ++i )
					यदि ( ! sceof[i] )
						scon_stk[++scon_stk_ptr] = i;

				यदि ( scon_stk_ptr == 0 )
					lwarn(
			"all start conditions already have <<EOF>> rules" );

				अन्यथा
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

			लागि ( i = 1; i <= lastsc; ++i )
				{
				पूर्णाङ्क j;

				लागि ( j = 1; j <= scon_stk_ptr; ++j )
					यदि ( scon_stk[j] == i )
						रोक;

				यदि ( j > scon_stk_ptr )
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
			यदि ( (scnum = sclookup( nmstr )) == 0 )
				format_pinpoint_message(
					"undeclared start condition %s",
					nmstr );
			अन्यथा
				{
				लागि ( i = 1; i <= scon_stk_ptr; ++i )
					यदि ( scon_stk[i] == scnum )
						{
						format_warn(
							"<%s> specified twice",
							scname[scnum] );
						रोक;
						}

				यदि ( i > scon_stk_ptr )
					scon_stk[++scon_stk_ptr] = scnum;
				}
			}
		;

rule		:  re2 re
			{
			यदि ( transchar[lastst[$2]] != SYM_EPSILON )
				/* Provide final transition \now/ so it
				 * will be marked as a trailing context
				 * state.
				 */
				$2 = link_machines( $2,
						mkstate( SYM_EPSILON ) );

			mark_beginning_as_normal( $2 );
			current_state_type = STATE_NORMAL;

			यदि ( previous_continued_action )
				{
				/* We need to treat this as variable trailing
				 * context so that the backup does not happen
				 * in the action but before the action switch
				 * statement.  If the backup happens in the
				 * action, then the rules "falling into" this
				 * one's action will *also* do the backup,
				 * erroneously.
				 */
				यदि ( ! varlength || headcnt != 0 )
					lwarn(
		"trailing context made variable due to preceding '|' action" );

				/* Mark as variable. */
				varlength = true;
				headcnt = 0;

				}

			यदि ( ctrl.lex_compat || (varlength && headcnt == 0) )
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
					अङ्क_rules | YY_TRAILING_HEAD_MASK );
				variable_trail_rule = true;
				}
			
			अन्यथा
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

			यदि ( trlcontxt )
				{
				synerr( _("trailing context used twice") );
				$$ = mkstate( SYM_EPSILON );
				}

			अन्यथा यदि ( previous_continued_action )
				{
				/* See the comment in the rule for "re2 re"
				 * above.
				 */
				lwarn(
		"trailing context made variable due to preceding '|' action" );

				varlength = true;
				}

			यदि ( ctrl.lex_compat || varlength )
				{
				/* Again, see the comment in the rule for
				 * "re2 re" above.
				 */
				add_accept( $1,
					अङ्क_rules | YY_TRAILING_HEAD_MASK );
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

			यदि ( trlcontxt )
				{
				यदि ( ctrl.lex_compat || (varlength && headcnt == 0) )
					/* Both head and trail are
					 * variable-length.
					 */
					variable_trail_rule = true;
				अन्यथा
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

			यदि ( trlcontxt )
				synerr( _("trailing context used twice") );
			अन्यथा
				trlcontxt = true;

			यदि ( varlength )
				/* We hope the trailing context is
				 * fixed-length.
				 */
				varlength = false;
			अन्यथा
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

			यदि ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			अन्यथा
				{
				यदि ( $3 == 0 )
					{
					यदि ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					अन्यथा
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				अन्यथा
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  series BEGIN_REPEAT_POSIX सङ्ख्या ',' END_REPEAT_POSIX
			{
			varlength = true;

			यदि ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			अन्यथा
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  series BEGIN_REPEAT_POSIX सङ्ख्या END_REPEAT_POSIX
			{
			/* The series could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			यदि ( $3 <= 0 )
				{
				  synerr( _("iteration value must be positive")
					  );
				$$ = $1;
				}

			अन्यथा
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

			यदि ( $3 > $5 || $3 < 0 )
				{
				synerr( _("bad iteration values") );
				$$ = $1;
				}
			अन्यथा
				{
				यदि ( $3 == 0 )
					{
					यदि ( $5 <= 0 )
						{
						synerr(
						_("bad iteration values") );
						$$ = $1;
						}
					अन्यथा
						$$ = mkopt(
							mkrep( $1, 1, $5 ) );
					}
				अन्यथा
					$$ = mkrep( $1, $3, $5 );
				}
			}

		|  singleton BEGIN_REPEAT_FLEX सङ्ख्या ',' END_REPEAT_FLEX
			{
			varlength = true;

			यदि ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			अन्यथा
				$$ = mkrep( $1, $3, INFINITE_REPEAT );
			}

		|  singleton BEGIN_REPEAT_FLEX सङ्ख्या END_REPEAT_FLEX
			{
			/* The singleton could be something like "(foo)",
			 * in which case we have no idea what its length
			 * is, so we punt here.
			 */
			varlength = true;

			यदि ( $3 <= 0 )
				{
				synerr( _("iteration value must be positive") );
				$$ = $1;
				}

			अन्यथा
				$$ = link_machines( $1,
						copysingl( $1, $3 - 1 ) );
			}

		|  '.'
			{
			यदि ( ! madeany )
				{
				/* Create the '.' character class. */
                    ccldot = cclinit();
                    ccladd( ccldot, '\n' );
                    cclnegate( ccldot );

                    यदि ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[ccldot],
                            ccllen[ccldot], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				/* Create the (?s:'.') character class. */
                    cclany = cclinit();
                    cclnegate( cclany );

                    यदि ( ctrl.useecs )
                        mkeccl( ccltbl + cclmap[cclany],
                            ccllen[cclany], nextecm,
                            ecgroup, ctrl.csize, ctrl.csize );

				madeany = true;
				}

			++rulelen;

            यदि (sf_dot_all())
                $$ = mkstate( -cclany );
            अन्यथा
                $$ = mkstate( -ccldot );
			}

		|  fullccl
			{
				/* Sort characters for fast searching.
				 */
				क्विक( ccltbl + cclmap[$1], (माप_प्रकार) ccllen[$1], परिमाण (*ccltbl), cclcmp );

			यदि ( ctrl.useecs )
				mkeccl( ccltbl + cclmap[$1], ccllen[$1],
					nextecm, ecgroup, ctrl.csize, ctrl.csize);

			++rulelen;

			यदि (ccl_has_nl[$1])
				rule_has_nl[num_rules] = true;

			$$ = mkstate( -$1 );
			}

		|  PREVCCL
			{
			++rulelen;

			यदि (ccl_has_nl[$1])
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

			यदि ($1 == nlch)
				rule_has_nl[num_rules] = true;

            यदि (sf_case_ins() && has_case($1))
                /* create an alternation, as in (a|A) */
                $$ = mkor (mkstate($1), mkstate(reverse_case($1)));
            अन्यथा
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

			यदि (sf_case_ins())
			  {

			    /* If one end of the range has case and the other
			     * does not, or the cases are different, then we're not
			     * sure what range the user is trying to express.
			     * Examples: [@-z] or [S-t]
			     */
			    यदि (has_case ($2) != has_case ($4)
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
			    अन्यथा यदि (!has_case ($2) && !has_case ($4) && !range_covers_case ($2, $4))
			      format_warn3 (
			      _("the character range [%c-%c] is ambiguous in a case-insensitive scanner"),
					    $2, $4);
			  }

			यदि ( $2 > $4 )
				synerr( _("negative range in character class") );

			अन्यथा
				{
				लागि ( i = $2; i <= $4; ++i )
					ccladd( $1, i );

				/* Keep track if this ccl is staying in
				 * alphabetical order.
				 */
				cclsorted = cclsorted && ($2 > lastchar);
				lastchar = $4;

                /* Do it again for upper/lowercase */
                यदि (sf_case_ins() && has_case($2) && has_case($4)){
                    $2 = reverse_case ($2);
                    $4 = reverse_case ($4);
                    
                    लागि ( i = $2; i <= $4; ++i )
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
            यदि (sf_case_ins() && has_case($2)){
                $2 = reverse_case ($2);
                ccladd ($1, $2);

                cclsorted = cclsorted && ($2 > lastchar);
                lastchar = $2;
            }

			$$ = $1;
			}

		|  ccl ccl_अभिव्यक्ति
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

ccl_अभिव्यक्ति:	   
           CCE_ALNUM	{ CCL_अभिव्यक्ति(है_अक्षर_अंक); }
		|  CCE_ALPHA	{ CCL_अभिव्यक्ति(है_अक्षर); }
		|  CCE_BLANK	{ CCL_अभिव्यक्ति(IS_BLANK); }
		|  CCE_CNTRL	{ CCL_अभिव्यक्ति(है_नियंत्रण); }
		|  CCE_DIGIT	{ CCL_अभिव्यक्ति(है_अंक); }
		|  CCE_GRAPH	{ CCL_अभिव्यक्ति(है_चित्र); }
		|  CCE_LOWER	{ 
                          CCL_अभिव्यक्ति(है_छोटा);
                          यदि (sf_case_ins())
                              CCL_अभिव्यक्ति(है_बड़ा);
                        }
		|  CCE_PRINT	{ CCL_अभिव्यक्ति(है_छाप); }
		|  CCE_PUNCT	{ CCL_अभिव्यक्ति(है_विराम); }
		|  CCE_SPACE	{ CCL_अभिव्यक्ति(है_खाली); }
		|  CCE_XDIGIT	{ CCL_अभिव्यक्ति(है_षष्ठादशक); }
		|  CCE_UPPER	{
                    CCL_अभिव्यक्ति(है_बड़ा);
                    यदि (sf_case_ins())
                        CCL_अभिव्यक्ति(है_छोटा);
				}

        |  CCE_NEG_ALNUM	{ CCL_NEG_अभिव्यक्ति(है_अक्षर_अंक); }
		|  CCE_NEG_ALPHA	{ CCL_NEG_अभिव्यक्ति(है_अक्षर); }
		|  CCE_NEG_BLANK	{ CCL_NEG_अभिव्यक्ति(IS_BLANK); }
		|  CCE_NEG_CNTRL	{ CCL_NEG_अभिव्यक्ति(है_नियंत्रण); }
		|  CCE_NEG_DIGIT	{ CCL_NEG_अभिव्यक्ति(है_अंक); }
		|  CCE_NEG_GRAPH	{ CCL_NEG_अभिव्यक्ति(है_चित्र); }
		|  CCE_NEG_PRINT	{ CCL_NEG_अभिव्यक्ति(है_छाप); }
		|  CCE_NEG_PUNCT	{ CCL_NEG_अभिव्यक्ति(है_विराम); }
		|  CCE_NEG_SPACE	{ CCL_NEG_अभिव्यक्ति(है_खाली); }
		|  CCE_NEG_XDIGIT	{ CCL_NEG_अभिव्यक्ति(है_षष्ठादशक); }
		|  CCE_NEG_LOWER	{ 
				यदि ( sf_case_ins() )
					lwarn(_("[:^lower:] is ambiguous in case insensitive scanner"));
				अन्यथा
					CCL_NEG_अभिव्यक्ति(है_छोटा);
				}
		|  CCE_NEG_UPPER	{
				यदि ( sf_case_ins() )
					lwarn(_("[:^upper:] ambiguous in case insensitive scanner"));
				अन्यथा
					CCL_NEG_अभिव्यक्ति(है_बड़ा);
				}
		;
		
string		:  string CHAR
			{
			यदि ( $2 == nlch )
				rule_has_nl[num_rules] = true;

			++rulelen;

            यदि (sf_case_ins() && has_case($2))
                $$ = mkor (mkstate($2), mkstate(reverse_case($2)));
            अन्यथा
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

	लागि ( i = 1; i <= scon_stk_ptr; ++i )
		{
		यदि ( sceof[scon_stk[i]] )
			format_pinpoint_message(
				"multiple <<EOF>> rules for start condition %s",
				scname[scon_stk[i]] );

		अन्यथा
			{
			sceof[scon_stk[i]] = true;

			यदि (previous_continued_action /* && previous action was regular */)
				add_action("YY_RULE_SETUP\n");

			snprintf( action_text, परिमाण(action_text), "M4_HOOK_EOF_STATE_CASE_ARM(%s)\n",
				scname[scon_stk[i]] );
			add_action( action_text );
			}
		}

	पङ्क्ति_directive_out(रिक्त, infilename, linenum);
        add_action("[[");

	/* This isn't a normal rule after all - don't count it as
	 * such, so we don't have any holes in the rule numbering
	 * (which make generating "rule can never match" warnings
	 * more difficult.
	 */
	--num_rules;
	++अङ्क_eof_rules;
	}


/* format_synerr - write out formatted syntax error */

शून्य format_synerr( अचर वर्ण *सन्देश, अचर वर्ण arg[] )
	{
	वर्ण errmsg[MAXLINE];

	(शून्य) snprintf( errmsg, परिमाण(errmsg), सन्देश, arg );
	synerr( errmsg );
	}


/* synerr - report a syntax error */

शून्य synerr( अचर वर्ण *str )
	{
	syntaxerror = true;
	pinpoint_message( str );
	}


/* format_warn - write out formatted warning */

शून्य format_warn( अचर वर्ण *सन्देश, अचर वर्ण arg[] )
	{
	वर्ण warn_सन्देश[MAXLINE];

	snprintf( warn_सन्देश, परिमाण(warn_सन्देश), सन्देश, arg );
	lwarn( warn_सन्देश );
	}


/* lwarn - report a warning, unless -w was given */

शून्य lwarn( अचर वर्ण *str )
	{
	पङ्क्ति_warning( str, linenum );
	}

/* format_pinpoint_message - write out a message formatted with one string,
 *			     pinpointing its location
 */

शून्य format_pinpoint_message( अचर वर्ण *सन्देश, अचर वर्ण arg[] )
	{
	वर्ण errmsg[MAXLINE*2];

	snprintf( errmsg, परिमाण(errmsg), सन्देश, arg );
	pinpoint_message( errmsg );
	}


/* pinpoint_message - write out a message, pinpointing its location */

शून्य pinpoint_message( अचर वर्ण *str )
	{
	पङ्क्ति_pinpoint( str, linenum );
	}


/* line_warning - report a warning at a given line, unless -w was given */

शून्य पङ्क्ति_warning( अचर वर्ण *str, पूर्णाङ्क पङ्क्ति )
	{
	वर्ण warning[MAXLINE*2];

	यदि ( ! env.nowarn )
		{
		snprintf( warning, परिमाण(warning), "warning, %s", str );
		पङ्क्ति_pinpoint( warning, पङ्क्ति );
		}
	}


/* line_pinpoint - write out a message, pinpointing it at the given line */

शून्य पङ्क्ति_pinpoint( अचर वर्ण *str, पूर्णाङ्क पङ्क्ति )
	{
	ख_लिखो( मानक_त्रुटि, "%s:%d: %s\n", infilename, पङ्क्ति, str );
	}


/* yyerror - eat up an error message from the parser;
 *	     currently, messages are ignore
 */

शून्य yyerror( अचर वर्ण *सन्देश )
	{
		(शून्य)सन्देश;
	}
