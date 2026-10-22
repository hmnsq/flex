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
ಬಾಹ್ಯ ವರ್ಣ *yytext;
ಬಾಹ್ಯ FILE *yyout;
bool no_section3_escape = false;
ಪೂರ್ಣಾಙ್ಕ     yylex (ಶೂನ್ಯ)
{
	ಪೂರ್ಣಾಙ್ಕ     toktype;
	ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ beglin = false;

	ಯದಿ (eofseen) {
		toktype = EOF;
        } ಅನ್ಯಥಾ {
		toktype = flexscan ();
        }
	ಯದಿ (toktype == EOF || toktype == 0) {
		eofseen = true;

		ಯದಿ (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		ಅನ್ಯಥಾ
			toktype = 0;
	}

	ಯದಿ (env.trace) {
		ಯದಿ (beglin) {
			fprintf (stderr, "%d\t", ಅಂಕೆ_rules + 1);
			beglin = 0;
		}

		ವಿಕಲ್ಪ (toktype) {
		ಪಕ್ಷ '<':
		ಪಕ್ಷ '>':
		ಪಕ್ಷ '^':
		ಪಕ್ಷ '$':
		ಪಕ್ಷ '"':
		ಪಕ್ಷ '[':
		ಪಕ್ಷ ']':
		ಪಕ್ಷ '{':
		ಪಕ್ಷ '}':
		ಪಕ್ಷ '|':
		ಪಕ್ಷ '(':
		ಪಕ್ಷ ')':
		ಪಕ್ಷ '-':
		ಪಕ್ಷ '/':
		ಪಕ್ಷ '\\':
		ಪಕ್ಷ '?':
		ಪಕ್ಷ '.':
		ಪಕ್ಷ '*':
		ಪಕ್ಷ '+':
		ಪಕ್ಷ ',':
			(ಶೂನ್ಯ) putc (toktype, stderr);
			ಭಙ್ಗ;

		ಪಕ್ಷ '\n':
			(ಶೂನ್ಯ) putc ('\n', stderr);

			ಯದಿ (sectnum == 2)
				beglin = 1;

			ಭಙ್ಗ;

		ಪಕ್ಷ SCDECL:
			fputs ("%s", stderr);
			ಭಙ್ಗ;

		ಪಕ್ಷ XSCDECL:
			fputs ("%x", stderr);
			ಭಙ್ಗ;

		ಪಕ್ಷ SECTEND:
			fputs ("%%\n", stderr);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			ಯದಿ (sectnum == 2)
				beglin = 1;

			ಭಙ್ಗ;

		ಪಕ್ಷ NAME:
			fprintf (stderr, "'%s'", nmstr);
			ಭಙ್ಗ;

		ಪಕ್ಷ CHAR:
			ವಿಕಲ್ಪ (yylval) {
			ಪಕ್ಷ '<':
			ಪಕ್ಷ '>':
			ಪಕ್ಷ '^':
			ಪಕ್ಷ '$':
			ಪಕ್ಷ '"':
			ಪಕ್ಷ '[':
			ಪಕ್ಷ ']':
			ಪಕ್ಷ '{':
			ಪಕ್ಷ '}':
			ಪಕ್ಷ '|':
			ಪಕ್ಷ '(':
			ಪಕ್ಷ ')':
			ಪಕ್ಷ '-':
			ಪಕ್ಷ '/':
			ಪಕ್ಷ '\\':
			ಪಕ್ಷ '?':
			ಪಕ್ಷ '.':
			ಪಕ್ಷ '*':
			ಪಕ್ಷ '+':
			ಪಕ್ಷ ',':
				fprintf (stderr, "\\%c", yylval);
				ಭಙ್ಗ;

			ಸ್ವಭಾವ:
				ಯದಿ (!isascii (yylval) || !isprint (yylval)) {
					ಯದಿ(env.trace_hex)
						fprintf (stderr, "\\x%02x", (unsigned ಪೂರ್ಣಾಙ್ಕ) yylval);
					ಅನ್ಯಥಾ
						fprintf (stderr, "\\%.3o", (unsigned ಪೂರ್ಣಾಙ್ಕ) yylval);
				} ಅನ್ಯಥಾ
					(ಶೂನ್ಯ) putc (yylval, stderr);
				ಭಙ್ಗ;
			}

			ಭಙ್ಗ;

		ಪಕ್ಷ ಸಂಖ್ಯೆ:
			fprintf (stderr, "%d", yylval);
			ಭಙ್ಗ;

		ಪಕ್ಷ PREVCCL:
			fprintf (stderr, "[%d]", yylval);
			ಭಙ್ಗ;

		ಪಕ್ಷ EOF_OP:
			fprintf (stderr, "<<EOF>>");
			ಭಙ್ಗ;

		ಪಕ್ಷ TOK_OPTION:
			fprintf (stderr, "%s ", yytext);
			ಭಙ್ಗ;

		ಪಕ್ಷ TOK_OUTFILE:
		ಪಕ್ಷ TOK_PREFIX:
		ಪಕ್ಷ CCE_ALNUM:
		ಪಕ್ಷ CCE_ALPHA:
		ಪಕ್ಷ CCE_BLANK:
		ಪಕ್ಷ CCE_CNTRL:
		ಪಕ್ಷ CCE_DIGIT:
		ಪಕ್ಷ CCE_GRAPH:
		ಪಕ್ಷ CCE_LOWER:
		ಪಕ್ಷ CCE_PRINT:
		ಪಕ್ಷ CCE_PUNCT:
		ಪಕ್ಷ CCE_SPACE:
		ಪಕ್ಷ CCE_UPPER:
		ಪಕ್ಷ CCE_XDIGIT:
			fprintf (stderr, "%s", yytext);
			ಭಙ್ಗ;

		ಪಕ್ಷ 0:
			fprintf (stderr, _("End Marker\n"));
			ಭಙ್ಗ;

		ಸ್ವಭಾವ:
			fprintf (stderr,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			ಭಙ್ಗ;
		}
	}

	ಪ್ರತ್ಯಾಗಮ toktype;
}
