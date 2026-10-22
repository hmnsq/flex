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

#شامل <ctype.h>
#شامل "flexdef.h"
#شامل "parse.h"


/* yylex - scan for a regular expression token */
بیرونی نویسه *yytext;
بیرونی FILE *yyout;
bool no_section3_escape = false;
صحیح     yylex (تهی)
{
	صحیح     toktype;
	ایستا صحیح beglin = false;

	اگر (eofseen) {
		toktype = EOF;
        } وگرنه {
		toktype = flexscan ();
        }
	اگر (toktype == EOF || toktype == 0) {
		eofseen = true;

		اگر (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		وگرنه
			toktype = 0;
	}

	اگر (env.trace) {
		اگر (beglin) {
			fprintf (stderr, "%d\t", رقم_rules + 1);
			beglin = 0;
		}

		انتخاب (toktype) {
		حالت '<':
		حالت '>':
		حالت '^':
		حالت '$':
		حالت '"':
		حالت '[':
		حالت ']':
		حالت '{':
		حالت '}':
		حالت '|':
		حالت '(':
		حالت ')':
		حالت '-':
		حالت '/':
		حالت '\\':
		حالت '?':
		حالت '.':
		حالت '*':
		حالت '+':
		حالت ',':
			(تهی) putc (toktype, stderr);
			بشکن;

		حالت '\n':
			(تهی) putc ('\n', stderr);

			اگر (sectnum == 2)
				beglin = 1;

			بشکن;

		حالت SCDECL:
			fputs ("%s", stderr);
			بشکن;

		حالت XSCDECL:
			fputs ("%x", stderr);
			بشکن;

		حالت SECTEND:
			fputs ("%%\n", stderr);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			اگر (sectnum == 2)
				beglin = 1;

			بشکن;

		حالت NAME:
			fprintf (stderr, "'%s'", nmstr);
			بشکن;

		حالت CHAR:
			انتخاب (yylval) {
			حالت '<':
			حالت '>':
			حالت '^':
			حالت '$':
			حالت '"':
			حالت '[':
			حالت ']':
			حالت '{':
			حالت '}':
			حالت '|':
			حالت '(':
			حالت ')':
			حالت '-':
			حالت '/':
			حالت '\\':
			حالت '?':
			حالت '.':
			حالت '*':
			حالت '+':
			حالت ',':
				fprintf (stderr, "\\%c", yylval);
				بشکن;

			پیشفرض:
				اگر (!isascii (yylval) || !isprint (yylval)) {
					اگر(env.trace_hex)
						fprintf (stderr, "\\x%02x", (unsigned صحیح) yylval);
					وگرنه
						fprintf (stderr, "\\%.3o", (unsigned صحیح) yylval);
				} وگرنه
					(تهی) putc (yylval, stderr);
				بشکن;
			}

			بشکن;

		حالت عدد:
			fprintf (stderr, "%d", yylval);
			بشکن;

		حالت PREVCCL:
			fprintf (stderr, "[%d]", yylval);
			بشکن;

		حالت EOF_OP:
			fprintf (stderr, "<<EOF>>");
			بشکن;

		حالت TOK_OPTION:
			fprintf (stderr, "%s ", yytext);
			بشکن;

		حالت TOK_OUTFILE:
		حالت TOK_PREFIX:
		حالت CCE_ALNUM:
		حالت CCE_ALPHA:
		حالت CCE_BLANK:
		حالت CCE_CNTRL:
		حالت CCE_DIGIT:
		حالت CCE_GRAPH:
		حالت CCE_LOWER:
		حالت CCE_PRINT:
		حالت CCE_PUNCT:
		حالت CCE_SPACE:
		حالت CCE_UPPER:
		حالت CCE_XDIGIT:
			fprintf (stderr, "%s", yytext);
			بشکن;

		حالت 0:
			fprintf (stderr, _("End Marker\n"));
			بشکن;

		پیشفرض:
			fprintf (stderr,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			بشکن;
		}
	}

	بازگشت toktype;
}
