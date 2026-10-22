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

#ضمن <ctype.h>
#ضمن "flexdef.h"
#ضمن "parse.h"


/* yylex - scan for a regular expression token */
خارجي حرف *yytext;
خارجي FILE *yyout;
bool no_section3_escape = false;
صحيح     yylex (فراغ)
{
	صحيح     toktype;
	ساكن صحيح beglin = false;

	إذا (eofseen) {
		toktype = EOF;
        } وإلا {
		toktype = flexscan ();
        }
	إذا (toktype == EOF || toktype == 0) {
		eofseen = true;

		إذا (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		وإلا
			toktype = 0;
	}

	إذا (env.trace) {
		إذا (beglin) {
			fprintf (stderr, "%d\t", عدد_rules + 1);
			beglin = 0;
		}

		بدل (toktype) {
		حالة '<':
		حالة '>':
		حالة '^':
		حالة '$':
		حالة '"':
		حالة '[':
		حالة ']':
		حالة '{':
		حالة '}':
		حالة '|':
		حالة '(':
		حالة ')':
		حالة '-':
		حالة '/':
		حالة '\\':
		حالة '?':
		حالة '.':
		حالة '*':
		حالة '+':
		حالة ',':
			(فراغ) putc (toktype, stderr);
			اكسر;

		حالة '\n':
			(فراغ) putc ('\n', stderr);

			إذا (sectnum == 2)
				beglin = 1;

			اكسر;

		حالة SCDECL:
			fputs ("%s", stderr);
			اكسر;

		حالة XSCDECL:
			fputs ("%x", stderr);
			اكسر;

		حالة SECTEND:
			fputs ("%%\n", stderr);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			إذا (sectnum == 2)
				beglin = 1;

			اكسر;

		حالة NAME:
			fprintf (stderr, "'%s'", nmstr);
			اكسر;

		حالة CHAR:
			بدل (yylval) {
			حالة '<':
			حالة '>':
			حالة '^':
			حالة '$':
			حالة '"':
			حالة '[':
			حالة ']':
			حالة '{':
			حالة '}':
			حالة '|':
			حالة '(':
			حالة ')':
			حالة '-':
			حالة '/':
			حالة '\\':
			حالة '?':
			حالة '.':
			حالة '*':
			حالة '+':
			حالة ',':
				fprintf (stderr, "\\%c", yylval);
				اكسر;

			افتراضي:
				إذا (!isascii (yylval) || !isprint (yylval)) {
					إذا(env.trace_hex)
						fprintf (stderr, "\\x%02x", (unsigned صحيح) yylval);
					وإلا
						fprintf (stderr, "\\%.3o", (unsigned صحيح) yylval);
				} وإلا
					(فراغ) putc (yylval, stderr);
				اكسر;
			}

			اكسر;

		حالة نمبر:
			fprintf (stderr, "%d", yylval);
			اكسر;

		حالة PREVCCL:
			fprintf (stderr, "[%d]", yylval);
			اكسر;

		حالة EOF_OP:
			fprintf (stderr, "<<EOF>>");
			اكسر;

		حالة TOK_OPTION:
			fprintf (stderr, "%s ", yytext);
			اكسر;

		حالة TOK_OUTFILE:
		حالة TOK_PREFIX:
		حالة CCE_ALNUM:
		حالة CCE_ALPHA:
		حالة CCE_BLANK:
		حالة CCE_CNTRL:
		حالة CCE_DIGIT:
		حالة CCE_GRAPH:
		حالة CCE_LOWER:
		حالة CCE_PRINT:
		حالة CCE_PUNCT:
		حالة CCE_SPACE:
		حالة CCE_UPPER:
		حالة CCE_XDIGIT:
			fprintf (stderr, "%s", yytext);
			اكسر;

		حالة 0:
			fprintf (stderr, _("End Marker\n"));
			اكسر;

		افتراضي:
			fprintf (stderr,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			اكسر;
		}
	}

	أرجع toktype;
}
