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

#અન્તર્ભાવ <ctype.h>
#અન્તર્ભાવ "flexdef.h"
#અન્તર્ભાવ "parse.h"


/* yylex - scan for a regular expression token */
બાહ્ય અક્ષર *yytext;
બાહ્ય FILE *yyout;
bool no_section3_escape = false;
પૂર્ણાંક     yylex (શૂન્ય)
{
	પૂર્ણાંક     toktype;
	સ્થિર પૂર્ણાંક beglin = false;

	જો (eofseen) {
		toktype = EOF;
        } નહીંતર {
		toktype = flexscan ();
        }
	જો (toktype == EOF || toktype == 0) {
		eofseen = true;

		જો (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		નહીંતર
			toktype = 0;
	}

	જો (env.trace) {
		જો (beglin) {
			fprintf (stderr, "%d\t", અંક_rules + 1);
			beglin = 0;
		}

		પસંદગી (toktype) {
		સ્થિતિ '<':
		સ્થિતિ '>':
		સ્થિતિ '^':
		સ્થિતિ '$':
		સ્થિતિ '"':
		સ્થિતિ '[':
		સ્થિતિ ']':
		સ્થિતિ '{':
		સ્થિતિ '}':
		સ્થિતિ '|':
		સ્થિતિ '(':
		સ્થિતિ ')':
		સ્થિતિ '-':
		સ્થિતિ '/':
		સ્થિતિ '\\':
		સ્થિતિ '?':
		સ્થિતિ '.':
		સ્થિતિ '*':
		સ્થિતિ '+':
		સ્થિતિ ',':
			(શૂન્ય) putc (toktype, stderr);
			તોડો;

		સ્થિતિ '\n':
			(શૂન્ય) putc ('\n', stderr);

			જો (sectnum == 2)
				beglin = 1;

			તોડો;

		સ્થિતિ SCDECL:
			fputs ("%s", stderr);
			તોડો;

		સ્થિતિ XSCDECL:
			fputs ("%x", stderr);
			તોડો;

		સ્થિતિ SECTEND:
			fputs ("%%\n", stderr);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			જો (sectnum == 2)
				beglin = 1;

			તોડો;

		સ્થિતિ NAME:
			fprintf (stderr, "'%s'", nmstr);
			તોડો;

		સ્થિતિ CHAR:
			પસંદગી (yylval) {
			સ્થિતિ '<':
			સ્થિતિ '>':
			સ્થિતિ '^':
			સ્થિતિ '$':
			સ્થિતિ '"':
			સ્થિતિ '[':
			સ્થિતિ ']':
			સ્થિતિ '{':
			સ્થિતિ '}':
			સ્થિતિ '|':
			સ્થિતિ '(':
			સ્થિતિ ')':
			સ્થિતિ '-':
			સ્થિતિ '/':
			સ્થિતિ '\\':
			સ્થિતિ '?':
			સ્થિતિ '.':
			સ્થિતિ '*':
			સ્થિતિ '+':
			સ્થિતિ ',':
				fprintf (stderr, "\\%c", yylval);
				તોડો;

			મૂળભૂત:
				જો (!isascii (yylval) || !isprint (yylval)) {
					જો(env.trace_hex)
						fprintf (stderr, "\\x%02x", (unsigned પૂર્ણાંક) yylval);
					નહીંતર
						fprintf (stderr, "\\%.3o", (unsigned પૂર્ણાંક) yylval);
				} નહીંતર
					(શૂન્ય) putc (yylval, stderr);
				તોડો;
			}

			તોડો;

		સ્થિતિ સંખ્યા:
			fprintf (stderr, "%d", yylval);
			તોડો;

		સ્થિતિ PREVCCL:
			fprintf (stderr, "[%d]", yylval);
			તોડો;

		સ્થિતિ EOF_OP:
			fprintf (stderr, "<<EOF>>");
			તોડો;

		સ્થિતિ TOK_OPTION:
			fprintf (stderr, "%s ", yytext);
			તોડો;

		સ્થિતિ TOK_OUTFILE:
		સ્થિતિ TOK_PREFIX:
		સ્થિતિ CCE_ALNUM:
		સ્થિતિ CCE_ALPHA:
		સ્થિતિ CCE_BLANK:
		સ્થિતિ CCE_CNTRL:
		સ્થિતિ CCE_DIGIT:
		સ્થિતિ CCE_GRAPH:
		સ્થિતિ CCE_LOWER:
		સ્થિતિ CCE_PRINT:
		સ્થિતિ CCE_PUNCT:
		સ્થિતિ CCE_SPACE:
		સ્થિતિ CCE_UPPER:
		સ્થિતિ CCE_XDIGIT:
			fprintf (stderr, "%s", yytext);
			તોડો;

		સ્થિતિ 0:
			fprintf (stderr, _("End Marker\n"));
			તોડો;

		મૂળભૂત:
			fprintf (stderr,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			તોડો;
		}
	}

	પાછા toktype;
}
