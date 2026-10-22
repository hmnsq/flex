/* yylex - scanner front-end for flex */

/* SPDX-License-Identifier: BSD-3-Clause-flex */

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

#include <ctype.h>
#include "flexdef.h"
#include "parse.h"


/* yylex - scan for a regular expression token */
extern char *yytext;
extern FILE *yyout;
bool no_section3_escape = false;
số_nguyên     yylex (void)
{
	số_nguyên     toktype;
	static số_nguyên beglin = false;

	nếu (eofseen) {
		toktype = EOF;
        } không_thì {
		toktype = flexscan ();
        }
	nếu (toktype == EOF || toktype == 0) {
		eofseen = true;

		nếu (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		không_thì
			toktype = 0;
	}

	nếu (env.trace) {
		nếu (beglin) {
			fprintf (stderr, "%d\t", num_rules + 1);
			beglin = 0;
		}

		switch (toktype) {
		case '<':
		case '>':
		case '^':
		case '$':
		case '"':
		case '[':
		case ']':
		case '{':
		case '}':
		case '|':
		case '(':
		case ')':
		case '-':
		case '/':
		case '\\':
		case '?':
		case '.':
		case '*':
		case '+':
		case ',':
			(void) putc (toktype, stderr);
			break;

		case '\n':
			(void) putc ('\n', stderr);

			nếu (sectnum == 2)
				beglin = 1;

			break;

		case SCDECL:
			fputs ("%s", stderr);
			break;

		case XSCDECL:
			fputs ("%x", stderr);
			break;

		case SECTEND:
			fputs ("%%\n", stderr);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			nếu (sectnum == 2)
				beglin = 1;

			break;

		case NAME:
			fprintf (stderr, "'%s'", nmstr);
			break;

		case CHAR:
			switch (yylval) {
			case '<':
			case '>':
			case '^':
			case '$':
			case '"':
			case '[':
			case ']':
			case '{':
			case '}':
			case '|':
			case '(':
			case ')':
			case '-':
			case '/':
			case '\\':
			case '?':
			case '.':
			case '*':
			case '+':
			case ',':
				fprintf (stderr, "\\%c", yylval);
				break;

			default:
				nếu (!isascii (yylval) || !isprint (yylval)) {
					nếu(env.trace_hex)
						fprintf (stderr, "\\x%02x", (unsigned số_nguyên) yylval);
					không_thì
						fprintf (stderr, "\\%.3o", (unsigned số_nguyên) yylval);
				} không_thì
					(void) putc (yylval, stderr);
				break;
			}

			break;

		case NUMBER:
			fprintf (stderr, "%d", yylval);
			break;

		case PREVCCL:
			fprintf (stderr, "[%d]", yylval);
			break;

		case EOF_OP:
			fprintf (stderr, "<<EOF>>");
			break;

		case TOK_OPTION:
			fprintf (stderr, "%s ", yytext);
			break;

		case TOK_OUTFILE:
		case TOK_PREFIX:
		case CCE_ALNUM:
		case CCE_ALPHA:
		case CCE_BLANK:
		case CCE_CNTRL:
		case CCE_DIGIT:
		case CCE_GRAPH:
		case CCE_LOWER:
		case CCE_PRINT:
		case CCE_PUNCT:
		case CCE_SPACE:
		case CCE_UPPER:
		case CCE_XDIGIT:
			fprintf (stderr, "%s", yytext);
			break;

		case 0:
			fprintf (stderr, _("End Marker\n"));
			break;

		default:
			fprintf (stderr,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			break;
		}
	}

	trả_về toktype;
}
