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

#ਅਨ੍ਤਰ੍ਭਾਵ <ctype.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "parse.h"


/* yylex - scan for a regular expression token */
ਬਾਹਰੀ ਅੱਖਰ *yytext;
ਬਾਹਰੀ FILE *yyout;
bool no_section3_escape = false;
ਪੂਰਨ     yylex (ਖਾਲੀ)
{
	ਪੂਰਨ     toktype;
	ਸਥਿਰ ਪੂਰਨ beglin = false;

	ਜੇ (eofseen) {
		toktype = EOF;
        } ਨਹੀਂਤਾਂ {
		toktype = flexscan ();
        }
	ਜੇ (toktype == EOF || toktype == 0) {
		eofseen = true;

		ਜੇ (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		ਨਹੀਂਤਾਂ
			toktype = 0;
	}

	ਜੇ (env.trace) {
		ਜੇ (beglin) {
			fprintf (stderr, "%d\t", ਅੰਕ_ਨਿਯਮਾਂ + 1);
			beglin = 0;
		}

		ਚੋਣ (toktype) {
		ਹਾਲਤ '<':
		ਹਾਲਤ '>':
		ਹਾਲਤ '^':
		ਹਾਲਤ '$':
		ਹਾਲਤ '"':
		ਹਾਲਤ '[':
		ਹਾਲਤ ']':
		ਹਾਲਤ '{':
		ਹਾਲਤ '}':
		ਹਾਲਤ '|':
		ਹਾਲਤ '(':
		ਹਾਲਤ ')':
		ਹਾਲਤ '-':
		ਹਾਲਤ '/':
		ਹਾਲਤ '\\':
		ਹਾਲਤ '?':
		ਹਾਲਤ '.':
		ਹਾਲਤ '*':
		ਹਾਲਤ '+':
		ਹਾਲਤ ',':
			(ਖਾਲੀ) putc (toktype, stderr);
			ਰੋਕੋ;

		ਹਾਲਤ '\n':
			(ਖਾਲੀ) putc ('\n', stderr);

			ਜੇ (sectnum == 2)
				beglin = 1;

			ਰੋਕੋ;

		ਹਾਲਤ SCDECL:
			fputs ("%s", stderr);
			ਰੋਕੋ;

		ਹਾਲਤ XSCDECL:
			fputs ("%x", stderr);
			ਰੋਕੋ;

		ਹਾਲਤ SECTEND:
			fputs ("%%\n", stderr);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			ਜੇ (sectnum == 2)
				beglin = 1;

			ਰੋਕੋ;

		ਹਾਲਤ NAME:
			fprintf (stderr, "'%s'", nmstr);
			ਰੋਕੋ;

		ਹਾਲਤ CHAR:
			ਚੋਣ (yylval) {
			ਹਾਲਤ '<':
			ਹਾਲਤ '>':
			ਹਾਲਤ '^':
			ਹਾਲਤ '$':
			ਹਾਲਤ '"':
			ਹਾਲਤ '[':
			ਹਾਲਤ ']':
			ਹਾਲਤ '{':
			ਹਾਲਤ '}':
			ਹਾਲਤ '|':
			ਹਾਲਤ '(':
			ਹਾਲਤ ')':
			ਹਾਲਤ '-':
			ਹਾਲਤ '/':
			ਹਾਲਤ '\\':
			ਹਾਲਤ '?':
			ਹਾਲਤ '.':
			ਹਾਲਤ '*':
			ਹਾਲਤ '+':
			ਹਾਲਤ ',':
				fprintf (stderr, "\\%c", yylval);
				ਰੋਕੋ;

			ਮੂਲ:
				ਜੇ (!isascii (yylval) || !isprint (yylval)) {
					ਜੇ(env.trace_hex)
						fprintf (stderr, "\\x%02x", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) yylval);
					ਨਹੀਂਤਾਂ
						fprintf (stderr, "\\%.3o", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) yylval);
				} ਨਹੀਂਤਾਂ
					(ਖਾਲੀ) putc (yylval, stderr);
				ਰੋਕੋ;
			}

			ਰੋਕੋ;

		ਹਾਲਤ ਸੰਖਿਆ:
			fprintf (stderr, "%d", yylval);
			ਰੋਕੋ;

		ਹਾਲਤ PREVCCL:
			fprintf (stderr, "[%d]", yylval);
			ਰੋਕੋ;

		ਹਾਲਤ EOF_OP:
			fprintf (stderr, "<<EOF>>");
			ਰੋਕੋ;

		ਹਾਲਤ TOK_OPTION:
			fprintf (stderr, "%s ", yytext);
			ਰੋਕੋ;

		ਹਾਲਤ TOK_OUTFILE:
		ਹਾਲਤ TOK_ਅਗੇਤਰ:
		ਹਾਲਤ CCE_ALNUM:
		ਹਾਲਤ CCE_ALPHA:
		ਹਾਲਤ CCE_BLANK:
		ਹਾਲਤ CCE_CNTRL:
		ਹਾਲਤ CCE_DIGIT:
		ਹਾਲਤ CCE_ਗ੍ਰਾਫ:
		ਹਾਲਤ CCE_ਹੇਠਲਾ:
		ਹਾਲਤ CCE_PRINT:
		ਹਾਲਤ CCE_PUNCT:
		ਹਾਲਤ CCE_SPACE:
		ਹਾਲਤ CCE_ਉੱਤਲਾ:
		ਹਾਲਤ CCE_XDIGIT:
			fprintf (stderr, "%s", yytext);
			ਰੋਕੋ;

		ਹਾਲਤ 0:
			fprintf (stderr, _("End Marker\n"));
			ਰੋਕੋ;

		ਮੂਲ:
			fprintf (stderr,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			ਰੋਕੋ;
		}
	}

	ਵਾਪਸ toktype;
}
