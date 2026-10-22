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

#अन्तर्भाव <ctype.h>
#अन्तर्भाव "flexdef.h"
#अन्तर्भाव "parse.h"


/* yylex - scan for a regular expression token */
बाह्य अक्षर *yytext;
बाह्य खाता *yyout;
bool no_section3_escape = false;
पूर्णांक     yylex (शून्य)
{
	पूर्णांक     toktype;
	स्थिर पूर्णांक beglin = false;

	जर (eofseen) {
		toktype = खातापूर्ण;
        } अन्यथा {
		toktype = flexscan ();
        }
	जर (toktype == खातापूर्ण || toktype == 0) {
		eofseen = true;

		जर (sectnum == 1) {
			synerr (_("premature EOF"));
			sectnum = 2;
			toktype = SECTEND;
		}

		अन्यथा
			toktype = 0;
	}

	जर (env.trace) {
		जर (beglin) {
			ख_लिखो (मानक_त्रुटि, "%d\t", अंक_rules + 1);
			beglin = 0;
		}

		निवड (toktype) {
		स्थिती '<':
		स्थिती '>':
		स्थिती '^':
		स्थिती '$':
		स्थिती '"':
		स्थिती '[':
		स्थिती ']':
		स्थिती '{':
		स्थिती '}':
		स्थिती '|':
		स्थिती '(':
		स्थिती ')':
		स्थिती '-':
		स्थिती '/':
		स्थिती '\\':
		स्थिती '?':
		स्थिती '.':
		स्थिती '*':
		स्थिती '+':
		स्थिती ',':
			(शून्य) अ_दो (toktype, मानक_त्रुटि);
			थांबा;

		स्थिती '\n':
			(शून्य) अ_दो ('\n', मानक_त्रुटि);

			जर (sectnum == 2)
				beglin = 1;

			थांबा;

		स्थिती SCDECL:
			ख_माला_दो ("%s", मानक_त्रुटि);
			थांबा;

		स्थिती XSCDECL:
			ख_माला_दो ("%x", मानक_त्रुटि);
			थांबा;

		स्थिती SECTEND:
			ख_माला_दो ("%%\n", मानक_त्रुटि);

			/* We set beglin to be true so we'll start
			 * writing out numbers as we echo rules.
			 * flexscan() has already assigned sectnum.
			 */
			जर (sectnum == 2)
				beglin = 1;

			थांबा;

		स्थिती NAME:
			ख_लिखो (मानक_त्रुटि, "'%s'", nmstr);
			थांबा;

		स्थिती CHAR:
			निवड (yylval) {
			स्थिती '<':
			स्थिती '>':
			स्थिती '^':
			स्थिती '$':
			स्थिती '"':
			स्थिती '[':
			स्थिती ']':
			स्थिती '{':
			स्थिती '}':
			स्थिती '|':
			स्थिती '(':
			स्थिती ')':
			स्थिती '-':
			स्थिती '/':
			स्थिती '\\':
			स्थिती '?':
			स्थिती '.':
			स्थिती '*':
			स्थिती '+':
			स्थिती ',':
				ख_लिखो (मानक_त्रुटि, "\\%c", yylval);
				थांबा;

			पूर्वनिर्धारित:
				जर (!isascii (yylval) || !है_छाप (yylval)) {
					जर(env.trace_hex)
						ख_लिखो (मानक_त्रुटि, "\\x%02x", (अचिन्हित पूर्णांक) yylval);
					अन्यथा
						ख_लिखो (मानक_त्रुटि, "\\%.3o", (अचिन्हित पूर्णांक) yylval);
				} अन्यथा
					(शून्य) अ_दो (yylval, मानक_त्रुटि);
				थांबा;
			}

			थांबा;

		स्थिती संख्या:
			ख_लिखो (मानक_त्रुटि, "%d", yylval);
			थांबा;

		स्थिती PREVCCL:
			ख_लिखो (मानक_त्रुटि, "[%d]", yylval);
			थांबा;

		स्थिती EOF_OP:
			ख_लिखो (मानक_त्रुटि, "<<EOF>>");
			थांबा;

		स्थिती TOK_OPTION:
			ख_लिखो (मानक_त्रुटि, "%s ", yytext);
			थांबा;

		स्थिती TOK_OUTFILE:
		स्थिती TOK_PREFIX:
		स्थिती CCE_ALNUM:
		स्थिती CCE_ALPHA:
		स्थिती CCE_BLANK:
		स्थिती CCE_CNTRL:
		स्थिती CCE_DIGIT:
		स्थिती CCE_GRAPH:
		स्थिती CCE_LOWER:
		स्थिती CCE_PRINT:
		स्थिती CCE_PUNCT:
		स्थिती CCE_SPACE:
		स्थिती CCE_UPPER:
		स्थिती CCE_XDIGIT:
			ख_लिखो (मानक_त्रुटि, "%s", yytext);
			थांबा;

		स्थिती 0:
			ख_लिखो (मानक_त्रुटि, _("End Marker\n"));
			थांबा;

		पूर्वनिर्धारित:
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("*Something Weird* - tok: %d val: %d\n"),
				 toktype, yylval);
			थांबा;
		}
	}

	परत toktype;
}
