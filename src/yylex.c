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

#അന്തര്ഭാവ <ctype.h>
#അന്തര്ഭാവ "flexdef.h"
#അന്തര്ഭാവ "parse.h"


/* yylex - scan for a regular expression token */
ബാഹ്യ അക്ഷരം *yytext;
ബാഹ്യ FILE *yyout;
bool no_section3_escape = false;
പൂർണ്ണസംഖ്യ     yylex (ശൂന്യം)
{
	പൂർണ്ണസംഖ്യ     toktype;
	സ്ഥിതം പൂർണ്ണസംഖ്യ beglin = false;

	എങ്കിൽ (eofseen) {
		toktype = EOF;
        } അല്ലെങ്കിൽ {
		toktype = flexscan ();
        }
	എങ്കിൽ (toktype == EOF || toktype == 0) {
		eofseen = true;

		എങ്കിൽ (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		അല്ലെങ്കിൽ
			toktype = 0;
	}

	എങ്കിൽ (env.trace) {
		എങ്കിൽ (beglin) {
			fprintf (stderr, "%d\t", അക്കം_rules + 1);
			beglin = 0;
		}

		തിരഞ്ഞെടുപ്പ് (toktype) {
		അവസ്ഥ '<':
		അവസ്ഥ '>':
		അവസ്ഥ '^':
		അവസ്ഥ '$':
		അവസ്ഥ '"':
		അവസ്ഥ '[':
		അവസ്ഥ ']':
		അവസ്ഥ '{':
		അവസ്ഥ '}':
		അവസ്ഥ '|':
		അവസ്ഥ '(':
		അവസ്ഥ ')':
		അവസ്ഥ '-':
		അവസ്ഥ '/':
		അവസ്ഥ '\\':
		അവസ്ഥ '?':
		അവസ്ഥ '.':
		അവസ്ഥ '*':
		അവസ്ഥ '+':
		അവസ്ഥ ',':
			(ശൂന്യം) putc (toktype, stderr);
			നിർത്തുക;

		അവസ്ഥ '\n':
			(ശൂന്യം) putc ('\n', stderr);

			എങ്കിൽ (sectnum == 2)
				beglin = 1;

			നിർത്തുക;

		അവസ്ഥ SCDECL:
			fputs ("%s", stderr);
			നിർത്തുക;

		അവസ്ഥ XSCDECL:
			fputs ("%x", stderr);
			നിർത്തുക;

		അവസ്ഥ SECTEND:
			fputs ("%%\n", stderr);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			എങ്കിൽ (sectnum == 2)
				beglin = 1;

			നിർത്തുക;

		അവസ്ഥ NAME:
			fprintf (stderr, "'%s'", nmstr);
			നിർത്തുക;

		അവസ്ഥ CHAR:
			തിരഞ്ഞെടുപ്പ് (yylval) {
			അവസ്ഥ '<':
			അവസ്ഥ '>':
			അവസ്ഥ '^':
			അവസ്ഥ '$':
			അവസ്ഥ '"':
			അവസ്ഥ '[':
			അവസ്ഥ ']':
			അവസ്ഥ '{':
			അവസ്ഥ '}':
			അവസ്ഥ '|':
			അവസ്ഥ '(':
			അവസ്ഥ ')':
			അവസ്ഥ '-':
			അവസ്ഥ '/':
			അവസ്ഥ '\\':
			അവസ്ഥ '?':
			അവസ്ഥ '.':
			അവസ്ഥ '*':
			അവസ്ഥ '+':
			അവസ്ഥ ',':
				fprintf (stderr, "\\%c", yylval);
				നിർത്തുക;

			സ്ഥിരസ്ഥിതി:
				എങ്കിൽ (!isascii (yylval) || !isprint (yylval)) {
					എങ്കിൽ(env.trace_hex)
						fprintf (stderr, "\\x%02x", (unsigned പൂർണ്ണസംഖ്യ) yylval);
					അല്ലെങ്കിൽ
						fprintf (stderr, "\\%.3o", (unsigned പൂർണ്ണസംഖ്യ) yylval);
				} അല്ലെങ്കിൽ
					(ശൂന്യം) putc (yylval, stderr);
				നിർത്തുക;
			}

			നിർത്തുക;

		അവസ്ഥ സംഖ്യ:
			fprintf (stderr, "%d", yylval);
			നിർത്തുക;

		അവസ്ഥ PREVCCL:
			fprintf (stderr, "[%d]", yylval);
			നിർത്തുക;

		അവസ്ഥ EOF_OP:
			fprintf (stderr, "<<EOF>>");
			നിർത്തുക;

		അവസ്ഥ TOK_OPTION:
			fprintf (stderr, "%s ", yytext);
			നിർത്തുക;

		അവസ്ഥ TOK_OUTFILE:
		അവസ്ഥ TOK_PREFIX:
		അവസ്ഥ CCE_ALNUM:
		അവസ്ഥ CCE_ALPHA:
		അവസ്ഥ CCE_BLANK:
		അവസ്ഥ CCE_CNTRL:
		അവസ്ഥ CCE_DIGIT:
		അവസ്ഥ CCE_GRAPH:
		അവസ്ഥ CCE_LOWER:
		അവസ്ഥ CCE_PRINT:
		അവസ്ഥ CCE_PUNCT:
		അവസ്ഥ CCE_SPACE:
		അവസ്ഥ CCE_UPPER:
		അവസ്ഥ CCE_XDIGIT:
			fprintf (stderr, "%s", yytext);
			നിർത്തുക;

		അവസ്ഥ 0:
			fprintf (stderr, _("End Marker\n"));
			നിർത്തുക;

		സ്ഥിരസ്ഥിതി:
			fprintf (stderr,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			നിർത്തുക;
		}
	}

	തിരികെ toktype;
}
