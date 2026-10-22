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

#அந்தர்பாவ <ctype.h>
#அந்தர்பாவ "flexdef.h"
#அந்தர்பாவ "parse.h"


/* yylex - scan for a regular expression token */
வெளி எழுத்து *yytext;
வெளி FILE *yyout;
bool no_section3_escape = false;
முழு     yylex (வெறுமை)
{
	முழு     toktype;
	நிலையான முழு beglin = false;

	எனில் (eofseen) {
		toktype = EOF;
        } இல்லையெனில் {
		toktype = flexscan ();
        }
	எனில் (toktype == EOF || toktype == 0) {
		eofseen = true;

		எனில் (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		இல்லையெனில்
			toktype = 0;
	}

	எனில் (env.trace) {
		எனில் (beglin) {
			fprintf (stderr, "%d\t", இலக்கம்_rules + 1);
			beglin = 0;
		}

		தேர்வு (toktype) {
		நிலை '<':
		நிலை '>':
		நிலை '^':
		நிலை '$':
		நிலை '"':
		நிலை '[':
		நிலை ']':
		நிலை '{':
		நிலை '}':
		நிலை '|':
		நிலை '(':
		நிலை ')':
		நிலை '-':
		நிலை '/':
		நிலை '\\':
		நிலை '?':
		நிலை '.':
		நிலை '*':
		நிலை '+':
		நிலை ',':
			(வெறுமை) putc (toktype, stderr);
			நிறுத்து;

		நிலை '\n':
			(வெறுமை) putc ('\n', stderr);

			எனில் (sectnum == 2)
				beglin = 1;

			நிறுத்து;

		நிலை SCDECL:
			fputs ("%s", stderr);
			நிறுத்து;

		நிலை XSCDECL:
			fputs ("%x", stderr);
			நிறுத்து;

		நிலை SECTEND:
			fputs ("%%\n", stderr);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			எனில் (sectnum == 2)
				beglin = 1;

			நிறுத்து;

		நிலை NAME:
			fprintf (stderr, "'%s'", nmstr);
			நிறுத்து;

		நிலை CHAR:
			தேர்வு (yylval) {
			நிலை '<':
			நிலை '>':
			நிலை '^':
			நிலை '$':
			நிலை '"':
			நிலை '[':
			நிலை ']':
			நிலை '{':
			நிலை '}':
			நிலை '|':
			நிலை '(':
			நிலை ')':
			நிலை '-':
			நிலை '/':
			நிலை '\\':
			நிலை '?':
			நிலை '.':
			நிலை '*':
			நிலை '+':
			நிலை ',':
				fprintf (stderr, "\\%c", yylval);
				நிறுத்து;

			இயல்பு:
				எனில் (!isascii (yylval) || !isprint (yylval)) {
					எனில்(env.trace_hex)
						fprintf (stderr, "\\x%02x", (unsigned முழு) yylval);
					இல்லையெனில்
						fprintf (stderr, "\\%.3o", (unsigned முழு) yylval);
				} இல்லையெனில்
					(வெறுமை) putc (yylval, stderr);
				நிறுத்து;
			}

			நிறுத்து;

		நிலை எண்:
			fprintf (stderr, "%d", yylval);
			நிறுத்து;

		நிலை PREVCCL:
			fprintf (stderr, "[%d]", yylval);
			நிறுத்து;

		நிலை EOF_OP:
			fprintf (stderr, "<<EOF>>");
			நிறுத்து;

		நிலை TOK_OPTION:
			fprintf (stderr, "%s ", yytext);
			நிறுத்து;

		நிலை TOK_OUTFILE:
		நிலை TOK_PREFIX:
		நிலை CCE_ALNUM:
		நிலை CCE_ALPHA:
		நிலை CCE_BLANK:
		நிலை CCE_CNTRL:
		நிலை CCE_DIGIT:
		நிலை CCE_GRAPH:
		நிலை CCE_LOWER:
		நிலை CCE_PRINT:
		நிலை CCE_PUNCT:
		நிலை CCE_SPACE:
		நிலை CCE_UPPER:
		நிலை CCE_XDIGIT:
			fprintf (stderr, "%s", yytext);
			நிறுத்து;

		நிலை 0:
			fprintf (stderr, _("End Marker\n"));
			நிறுத்து;

		இயல்பு:
			fprintf (stderr,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			நிறுத்து;
		}
	}

	திரும்பு toktype;
}
