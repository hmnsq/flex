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

#ಅನ್ತರ್ಭಾವ <ctype.h>
#ಅನ್ತರ್ಭಾವ "flexdef.h"
#ಅನ್ತರ್ಭಾವ "parse.h"


/* yylex - scan for a regular expression token */
ಬಾಹ್ಯ ಅಕ್ಷರ *yytext;
ಬಾಹ್ಯ FILE *yyout;
bool no_section3_escape = false;
ಪೂರ್ಣಾಂಕ     yylex (ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಂಕ     toktype;
	ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ beglin = false;

	ಆದರೆ (eofseen) {
		toktype = EOF;
        } ಇಲ್ಲದಿದ್ದರೆ {
		toktype = flexscan ();
        }
	ಆದರೆ (toktype == EOF || toktype == 0) {
		eofseen = true;

		ಆದರೆ (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		ಇಲ್ಲದಿದ್ದರೆ
			toktype = 0;
	}

	ಆದರೆ (env.trace) {
		ಆದರೆ (beglin) {
			fprintf (stderr, "%d\t", ಅಂಕೆ_ನಿಯಮಗಳು + 1);
			beglin = 0;
		}

		ಆಯ್ಕೆ (toktype) {
		ಸ್ಥಿತಿ '<':
		ಸ್ಥಿತಿ '>':
		ಸ್ಥಿತಿ '^':
		ಸ್ಥಿತಿ '$':
		ಸ್ಥಿತಿ '"':
		ಸ್ಥಿತಿ '[':
		ಸ್ಥಿತಿ ']':
		ಸ್ಥಿತಿ '{':
		ಸ್ಥಿತಿ '}':
		ಸ್ಥಿತಿ '|':
		ಸ್ಥಿತಿ '(':
		ಸ್ಥಿತಿ ')':
		ಸ್ಥಿತಿ '-':
		ಸ್ಥಿತಿ '/':
		ಸ್ಥಿತಿ '\\':
		ಸ್ಥಿತಿ '?':
		ಸ್ಥಿತಿ '.':
		ಸ್ಥಿತಿ '*':
		ಸ್ಥಿತಿ '+':
		ಸ್ಥಿತಿ ',':
			(ಶೂನ್ಯ) putc (toktype, stderr);
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ '\n':
			(ಶೂನ್ಯ) putc ('\n', stderr);

			ಆದರೆ (sectnum == 2)
				beglin = 1;

			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ SCDECL:
			fputs ("%s", stderr);
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ XSCDECL:
			fputs ("%x", stderr);
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ SECTEND:
			fputs ("%%\n", stderr);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			ಆದರೆ (sectnum == 2)
				beglin = 1;

			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ NAME:
			fprintf (stderr, "'%s'", nmstr);
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ CHAR:
			ಆಯ್ಕೆ (yylval) {
			ಸ್ಥಿತಿ '<':
			ಸ್ಥಿತಿ '>':
			ಸ್ಥಿತಿ '^':
			ಸ್ಥಿತಿ '$':
			ಸ್ಥಿತಿ '"':
			ಸ್ಥಿತಿ '[':
			ಸ್ಥಿತಿ ']':
			ಸ್ಥಿತಿ '{':
			ಸ್ಥಿತಿ '}':
			ಸ್ಥಿತಿ '|':
			ಸ್ಥಿತಿ '(':
			ಸ್ಥಿತಿ ')':
			ಸ್ಥಿತಿ '-':
			ಸ್ಥಿತಿ '/':
			ಸ್ಥಿತಿ '\\':
			ಸ್ಥಿತಿ '?':
			ಸ್ಥಿತಿ '.':
			ಸ್ಥಿತಿ '*':
			ಸ್ಥಿತಿ '+':
			ಸ್ಥಿತಿ ',':
				fprintf (stderr, "\\%c", yylval);
				ನಿಲ್ಲಿಸು;

			ಪೂರ್ವನಿಯೋಜಿತ:
				ಆದರೆ (!isascii (yylval) || !isprint (yylval)) {
					ಆದರೆ(env.trace_hex)
						fprintf (stderr, "\\x%02x", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) yylval);
					ಇಲ್ಲದಿದ್ದರೆ
						fprintf (stderr, "\\%.3o", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) yylval);
				} ಇಲ್ಲದಿದ್ದರೆ
					(ಶೂನ್ಯ) putc (yylval, stderr);
				ನಿಲ್ಲಿಸು;
			}

			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ ಸಂಖ್ಯೆ:
			fprintf (stderr, "%d", yylval);
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ PREVCCL:
			fprintf (stderr, "[%d]", yylval);
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ EOF_OP:
			fprintf (stderr, "<<EOF>>");
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ TOK_OPTION:
			fprintf (stderr, "%s ", yytext);
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ TOK_OUTFILE:
		ಸ್ಥಿತಿ TOK_ಪೂರ್ವಪ್ರತ್ಯಯ:
		ಸ್ಥಿತಿ CCE_ALNUM:
		ಸ್ಥಿತಿ CCE_ALPHA:
		ಸ್ಥಿತಿ CCE_BLANK:
		ಸ್ಥಿತಿ CCE_CNTRL:
		ಸ್ಥಿತಿ CCE_DIGIT:
		ಸ್ಥಿತಿ CCE_ನಕ್ಷೆ:
		ಸ್ಥಿತಿ CCE_ಅಧೋ:
		ಸ್ಥಿತಿ CCE_PRINT:
		ಸ್ಥಿತಿ CCE_PUNCT:
		ಸ್ಥಿತಿ CCE_SPACE:
		ಸ್ಥಿತಿ CCE_ಊರ್ಧ್ವ:
		ಸ್ಥಿತಿ CCE_XDIGIT:
			fprintf (stderr, "%s", yytext);
			ನಿಲ್ಲಿಸು;

		ಸ್ಥಿತಿ 0:
			fprintf (stderr, _("End Marker\n"));
			ನಿಲ್ಲಿಸು;

		ಪೂರ್ವನಿಯೋಜಿತ:
			fprintf (stderr,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			ನಿಲ್ಲಿಸು;
		}
	}

	ಹಿಂತಿರುಗಿ toktype;
}
