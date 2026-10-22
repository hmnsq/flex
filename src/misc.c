/* misc - miscellaneous flex routines */

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
#ಅನ್ತರ್ಭಾವ "flexdef.h"
#ಅನ್ತರ್ಭಾವ "tables.h"

/* Append "new_text" to the running buffer. */
ಶೂನ್ಯ ಕೂಡಿಸು_action (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *new_ಪಠ್ಯ)
{
	ಪೂರ್ಣಾಂಕ     len = (ಪೂರ್ಣಾಂಕ) ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (new_ಪಠ್ಯ);

	ಆಗ (len + action_ಸೂಚ್ಯಂಕ >= action_ಗಾತ್ರ - 10 /* slop */ ) {

		ಆದರೆ (action_ಗಾತ್ರ > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_ಗಾತ್ರ += action_ಗಾತ್ರ / 8;
		ಇಲ್ಲದಿದ್ದರೆ
			action_ಗಾತ್ರ = action_ಗಾತ್ರ * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_ಗಾತ್ರ);
	}

	strcpy (&action_array[action_ಸೂಚ್ಯಂಕ], new_ಪಠ್ಯ);

	action_ಸೂಚ್ಯಂಕ += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

ಶೂನ್ಯ   *allocate_array (ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2, size_t element_ಗಾತ್ರ)
{
	ಹಿಂತಿರುಗಿ reallocate_array(ಖಾಲಿ, ಗಾತ್ರ_2, element_ಗಾತ್ರ);
}


/* all_lower - true if a string is all lower-case */

ಪೂರ್ಣಾಂಕ all_ಅಧೋ (ಅಕ್ಷರ *str)
{
	ಆಗ (*str) {
		ಆದರೆ (!isascii ((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) * str) || !islower ((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) * str))
			ಹಿಂತಿರುಗಿ 0;
		++str;
	}

	ಹಿಂತಿರುಗಿ 1;
}


/* all_upper - true if a string is all upper-case */

ಪೂರ್ಣಾಂಕ all_ಊರ್ಧ್ವ (ಅಕ್ಷರ *str)
{
	ಆಗ (*str) {
		ಆದರೆ (!isascii ((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) * str) || !isupper ((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) * str))
			ಹಿಂತಿರುಗಿ 0;
		++str;
	}

	ಹಿಂತಿರುಗಿ 1;
}


/* intcmp - compares two integers for use by qsort. */

ಪೂರ್ಣಾಂಕ intcmp (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *a, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *b)
{
  ಹಿಂತಿರುಗಿ *(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *) a - *(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

ಶೂನ್ಯ check_char (ಪೂರ್ಣಾಂಕ c)
{
	ಆದರೆ (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	ಆದರೆ (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ clower (ಪೂರ್ಣಾಂಕ c)
{
	ಹಿಂತಿರುಗಿ (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


ಅಕ್ಷರ *xstrdup(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s)
{
	ಅಕ್ಷರ *s2;

	ಆದರೆ ((s2 = strdup(s)) == ಖಾಲಿ)
		flexfatal (_("memory allocation failure in xstrdup()"));

	ಹಿಂತಿರುಗಿ s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

ಪೂರ್ಣಾಂಕ cclcmp (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *a, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *b)
{
	ಆದರೆ (!*(ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) a)
		ಹಿಂತಿರುಗಿ 1;
	ಇಲ್ಲದಿದ್ದರೆ
		ಆದರೆ (!*(ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) b)
			ಹಿಂತಿರುಗಿ - 1;
		ಇಲ್ಲದಿದ್ದರೆ
			ಹಿಂತಿರುಗಿ *(ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) a - *(ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *) b;
}


/* dataend - finish up a block of data declarations */

ಶೂನ್ಯ dataend (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *endit)
{
	/* short circuit any output */
	ಆದರೆ (gentables) {

		ಆದರೆ (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		ಆದರೆ (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

ಶೂನ್ಯ dataflush (ಶೂನ್ಯ)
{
	ಪ್ರತಿಜ್ಞಾ (gentables);

	ಆದರೆ (datapos > 0)
		outc ('\n');

	ಆದರೆ (++dataline >= NUMDATALINES) {
		/* Put out a blank line so that the table is grouped into
		 * large blocks that enable the user to find elements easily.
		 */
		outc ('\n');
		dataline = 0;
	}

	/* Reset the number of characters written on the current line. */
	datapos = 0;
}


/* flexerror - report an error message and terminate */

ಶೂನ್ಯ flexerror (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ)
{
	fprintf (stderr, "%s: %s\n", ಕಾರ್ಯಕ್ರಮ_name, ಸಂದೇಶ);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

ಶೂನ್ಯ flexfatal (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 ಕಾರ್ಯಕ್ರಮ_name, ಸಂದೇಶ);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

ಶೂನ್ಯ lerr (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ...)
{
	ಅಕ್ಷರ    errmsg[MAXLINE];
	va_list ವಾದಗಳು;

	va_ಆರಂಭ(ವಾದಗಳು, ಸಂದೇಶ);
	vsnprintf (errmsg, ಗಾತ್ರ(errmsg), ಸಂದೇಶ, ವಾದಗಳು);
	va_ಕೊನೆ(ವಾದಗಳು);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

ಶೂನ್ಯ lerr_fatal (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಂದೇಶ, ...)
{
	ಅಕ್ಷರ    errmsg[MAXLINE];
	va_list ವಾದಗಳು;
	va_ಆರಂಭ(ವಾದಗಳು, ಸಂದೇಶ);

	vsnprintf (errmsg, ಗಾತ್ರ(errmsg), ಸಂದೇಶ, ವಾದಗಳು);
	va_ಕೊನೆ(ವಾದಗಳು);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
ಶೂನ್ಯ ಸಾಲು_directive_ಹೊರಹೋಗು (FILE *output_file, ಅಕ್ಷರ *ಮಾರ್ಗ, ಪೂರ್ಣಾಂಕ linenum)
{
	ಅಕ್ಷರ	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	ಅಕ್ಷರ    directive[MAXLINE*2], filename[MAXLINE];
	ಅಕ್ಷರ   *s1, *s2, *s3;

	ಆದರೆ (!ctrl.gen_ಸಾಲು_dirs)
		ಹಿಂತಿರುಗಿ;

	s1 = (ಮಾರ್ಗ != ಖಾಲಿ) ? ಮಾರ್ಗ : "M4_YY_OUTFILE_NAME";

	ಆದರೆ ((ಮಾರ್ಗ != ಖಾಲಿ) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[ಗಾತ್ರ (filename) - 2];

	ಆಗ (s2 < s3 && *s1) {
		ಆದರೆ (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	ಆದರೆ (ಮಾರ್ಗ != ಖಾಲಿ)
		snprintf (directive, ಗಾತ್ರ(directive), trace_fmt, linenum, filename);
	ಇಲ್ಲದಿದ್ದರೆ {
		snprintf (directive, ಗಾತ್ರ(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	ಆದರೆ (output_file) {
		fputs (directive, output_file);
	}
	ಇಲ್ಲದಿದ್ದರೆ
		ಕೂಡಿಸು_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
ಶೂನ್ಯ mark_defs1 (ಶೂನ್ಯ)
{
	defs1_ಸ್ಥಾನಾಂತರ = 0;
	action_array[action_ಸೂಚ್ಯಂಕ++] = '\0';
	action_ಸ್ಥಾನಾಂತರ = prolog_ಸ್ಥಾನಾಂತರ = action_ಸೂಚ್ಯಂಕ;
	action_array[action_ಸೂಚ್ಯಂಕ] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
ಶೂನ್ಯ mark_prolog (ಶೂನ್ಯ)
{
	action_array[action_ಸೂಚ್ಯಂಕ++] = '\0';
	action_ಸ್ಥಾನಾಂತರ = action_ಸೂಚ್ಯಂಕ;
	action_array[action_ಸೂಚ್ಯಂಕ] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
ಶೂನ್ಯ mk2data (ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ)
{
	/* short circuit any output */
	ಆದರೆ (!gentables)
		ಹಿಂತಿರುಗಿ;

	ಆದರೆ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ಆದರೆ (datapos == 0)
		/* Indent. */
		ಹೊರಹೋಗು ("    ");

	ಇಲ್ಲದಿದ್ದರೆ
	  outc (',');

	++datapos;

	ಹೊರಹೋಗು_dec ("%5d", ಮೌಲ್ಯ);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
ಶೂನ್ಯ mkdata (ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ)
{
	/* short circuit any output */
	ಆದರೆ (!gentables)
		ಹಿಂತಿರುಗಿ;

	ಆದರೆ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ಆದರೆ (datapos == 0)
		/* Indent. */
		ಹೊರಹೋಗು ("    ");
	ಇಲ್ಲದಿದ್ದರೆ
		outc (',');
	++datapos;

	ಹೊರಹೋಗು_dec ("%5d", ಮೌಲ್ಯ);
}


/* myctoi - return the integer represented by a string of digits */

ಪೂರ್ಣಾಂಕ myctoi (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *array)
{
	ಪೂರ್ಣಾಂಕ     val = 0;

	(ಶೂನ್ಯ) ಅಕ್ಷರಸರಣಿ_ಓದು (array, "%d", &val);

	ಹಿಂತಿರುಗಿ val;
}


/* myesc - return character corresponding to escape sequence */

ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ myesc (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ array[])
{
	ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ    c, esc_char;

	ಆಯ್ಕೆ (array[1]) {
	ಸ್ಥಿತಿ 'b':
		ಹಿಂತಿರುಗಿ '\b';
	ಸ್ಥಿತಿ 'f':
		ಹಿಂತಿರುಗಿ '\f';
	ಸ್ಥಿತಿ 'n':
		ಹಿಂತಿರುಗಿ '\n';
	ಸ್ಥಿತಿ 'r':
		ಹಿಂತಿರುಗಿ '\r';
	ಸ್ಥಿತಿ 't':
		ಹಿಂತಿರುಗಿ '\t';
	ಸ್ಥಿತಿ 'a':
		ಹಿಂತಿರುಗಿ '\a';
	ಸ್ಥಿತಿ 'v':
		ಹಿಂತಿರುಗಿ '\v';
	ಸ್ಥಿತಿ '0':
	ಸ್ಥಿತಿ '1':
	ಸ್ಥಿತಿ '2':
	ಸ್ಥಿತಿ '3':
	ಸ್ಥಿತಿ '4':
	ಸ್ಥಿತಿ '5':
	ಸ್ಥಿತಿ '6':
	ಸ್ಥಿತಿ '7':
		{		/* \<octal> */
			ಪೂರ್ಣಾಂಕ     sptr = 1;

			ಆಗ (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) strtoul (array + 1, ಖಾಲಿ, 8);

			array[sptr] = c;

			ಹಿಂತಿರುಗಿ esc_char;
		}

	ಸ್ಥಿತಿ 'x':
		{		/* \x<hex> */
			ಪೂರ್ಣಾಂಕ     sptr = 2;

			ಆಗ (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) strtoul (array + 2, ಖಾಲಿ, 16);

			array[sptr] = c;

			ಹಿಂತಿರುಗಿ esc_char;
		}

	ಪೂರ್ವನಿಯೋಜಿತ:
		ಹಿಂತಿರುಗಿ array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

ಶೂನ್ಯ ಹೊರಹೋಗು (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
	fputs (str, stdout);
}

ಶೂನ್ಯ ಹೊರಹೋಗು_dec (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ಪೂರ್ಣಾಂಕ n)
{
	fprintf (stdout, fmt, n);
}

ಶೂನ್ಯ ಹೊರಹೋಗು_dec2 (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ಪೂರ್ಣಾಂಕ n1, ಪೂರ್ಣಾಂಕ n2)
{
	fprintf (stdout, fmt, n1, n2);
}

ಶೂನ್ಯ ಹೊರಹೋಗು_hex (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ x)
{
	fprintf (stdout, fmt, x);
}

ಶೂನ್ಯ ಹೊರಹೋಗು_str (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ str[])
{
	fprintf (stdout,fmt, str);
}

ಶೂನ್ಯ ಹೊರಹೋಗು_str_dec (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ str[], ಪೂರ್ಣಾಂಕ n)
{
	fprintf (stdout,fmt, str, n);
}

ಶೂನ್ಯ outc (ಪೂರ್ಣಾಂಕ c)
{
	fputc (c, stdout);
}

ಶೂನ್ಯ outn (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
ಶೂನ್ಯ ಹೊರಹೋಗು_m4_define (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* def, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* val)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

ಅಕ್ಷರ   *readable_form (ಪೂರ್ಣಾಂಕ c)
{
	ಸ್ಥಿರ ಅಕ್ಷರ rform[20];

	ಆದರೆ ((c >= 0 && c < 32) || c >= 127) {
		ಆಯ್ಕೆ (c) {
		ಸ್ಥಿತಿ '\b':
			ಹಿಂತಿರುಗಿ "\\b";
		ಸ್ಥಿತಿ '\f':
			ಹಿಂತಿರುಗಿ "\\f";
		ಸ್ಥಿತಿ '\n':
			ಹಿಂತಿರುಗಿ "\\n";
		ಸ್ಥಿತಿ '\r':
			ಹಿಂತಿರುಗಿ "\\r";
		ಸ್ಥಿತಿ '\t':
			ಹಿಂತಿರುಗಿ "\\t";
		ಸ್ಥಿತಿ '\a':
			ಹಿಂತಿರುಗಿ "\\a";
		ಸ್ಥಿತಿ '\v':
			ಹಿಂತಿರುಗಿ "\\v";
		ಪೂರ್ವನಿಯೋಜಿತ:
			ಆದರೆ(env.trace_hex)
				snprintf (rform, ಗಾತ್ರ(rform), "\\x%.2x", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) c);
			ಇಲ್ಲದಿದ್ದರೆ
				snprintf (rform, ಗಾತ್ರ(rform), "\\%.3o", (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) c);
			ಹಿಂತಿರುಗಿ rform;
		}
	}

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c == ' ')
		ಹಿಂತಿರುಗಿ "' '";

	ಇಲ್ಲದಿದ್ದರೆ {
		rform[0] = (ಅಕ್ಷರ) c;
		rform[1] = '\0';

		ಹಿಂತಿರುಗಿ rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

ಶೂನ್ಯ   *reallocate_array (ಶೂನ್ಯ *array, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2, size_t element_ಗಾತ್ರ)
{
	ಶೂನ್ಯ *new_array;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_REALLOCARR
	new_array = array;
	ಆದರೆ (reallocarr(&new_array, (size_t) ಗಾತ್ರ_2, element_ಗಾತ್ರ)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#ಇಲ್ಲದಿದ್ದರೆ
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) ಗಾತ್ರ_2, element_ಗಾತ್ರ);
# ಇಲ್ಲದಿದ್ದರೆ
	/* Do manual overflow detection */
	size_t ಅಂಕೆ_ಬೈಟುಗಳು = (size_t) ಗಾತ್ರ_2 * element_ಗಾತ್ರ;
	new_array = (ಗಾತ್ರ_2 && ಗಾತ್ರ_MAX / (size_t) ಗಾತ್ರ_2 < element_ಗಾತ್ರ) ? ಖಾಲಿ :
		realloc(array, ಅಂಕೆ_ಬೈಟುಗಳು);
# endif
	ಆದರೆ (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#ಆದರೆ_ಅಂತ್ಯ
	ಹಿಂತಿರುಗಿ new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

ಶೂನ್ಯ transition_struct_ಹೊರಹೋಗು (ಪೂರ್ಣಾಂಕ element_v, ಪೂರ್ಣಾಂಕ element_n)
{

	/* short circuit any output */
	ಆದರೆ (!gentables)
		ಹಿಂತಿರುಗಿ;

	ಹೊರಹೋಗು_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_ಉದ್ದಳತೆ;

	ಆದರೆ (datapos >= 79 - TRANS_STRUCT_PRINT_ಉದ್ದಳತೆ) {
		outc ('\n');

		ಆದರೆ (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
ಶೂನ್ಯ   *yy_flex_xmalloc (ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2)
{
	ಶೂನ್ಯ   *ಫಲಿತಾಂಶ;

	ಫಲಿತಾಂಶ = ಸ್ಮರಣೆ_ಕೊಡು((size_t) ಗಾತ್ರ_2);
	ಆದರೆ (!ಫಲಿತಾಂಶ)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
ಅಕ್ಷರ   *chomp (ಅಕ್ಷರ *str)
{
	ಅಕ್ಷರ   *p = str;

	ಆದರೆ (!str || !*str)	/* s is null or empty string */
		ಹಿಂತಿರುಗಿ str;

	/* find end of string minus one */
	ಆಗ (*p)
		++p;
	--p;

	/* eat newlines */
	ಆಗ (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	ಹಿಂತಿರುಗಿ str;
}

ಶೂನ್ಯ comment(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *txt)
{
	ಅಕ್ಷರ buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(buf)-1] == '\n';

	ಆದರೆ (eol)
		buf[ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(buf)-1] = '\0';
	ಹೊರಹೋಗು_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	ಆದರೆ (eol)
		outc ('\n');
}


