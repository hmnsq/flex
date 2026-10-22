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
#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tables.h"

/* Append "new_text" to the running buffer. */
ਖਾਲੀ ਜੋੜੋ_action (ਅਚਲ ਅੱਖਰ *new_ਪਾਠ)
{
	ਪੂਰਨ     len = (ਪੂਰਨ) ਲੜੀ_ਲੰਬਾਈ (new_ਪਾਠ);

	ਜਦੋਂ (len + action_ਸੂਚਕਾਂਕ >= action_ਮਾਪ - 10 /* slop */ ) {

		ਜੇ (action_ਮਾਪ > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_ਮਾਪ += action_ਮਾਪ / 8;
		ਨਹੀਂਤਾਂ
			action_ਮਾਪ = action_ਮਾਪ * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_ਮਾਪ);
	}

	strcpy (&action_array[action_ਸੂਚਕਾਂਕ], new_ਪਾਠ);

	action_ਸੂਚਕਾਂਕ += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

ਖਾਲੀ   *allocate_array (ਪੂਰਨ ਮਾਪ, size_t element_ਮਾਪ)
{
	ਵਾਪਸ reallocate_array(ਨਿਰਾ, ਮਾਪ, element_ਮਾਪ);
}


/* all_lower - true if a string is all lower-case */

ਪੂਰਨ all_ਹੇਠਲਾ (ਅੱਖਰ *str)
{
	ਜਦੋਂ (*str) {
		ਜੇ (!isascii ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) * str) || !islower ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) * str))
			ਵਾਪਸ 0;
		++str;
	}

	ਵਾਪਸ 1;
}


/* all_upper - true if a string is all upper-case */

ਪੂਰਨ all_ਉੱਤਲਾ (ਅੱਖਰ *str)
{
	ਜਦੋਂ (*str) {
		ਜੇ (!isascii ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) * str) || !isupper ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) * str))
			ਵਾਪਸ 0;
		++str;
	}

	ਵਾਪਸ 1;
}


/* intcmp - compares two integers for use by qsort. */

ਪੂਰਨ intcmp (ਅਚਲ ਖਾਲੀ *a, ਅਚਲ ਖਾਲੀ *b)
{
  ਵਾਪਸ *(ਅਚਲ ਪੂਰਨ *) a - *(ਅਚਲ ਪੂਰਨ *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

ਖਾਲੀ check_char (ਪੂਰਨ c)
{
	ਜੇ (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	ਜੇ (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ clower (ਪੂਰਨ c)
{
	ਵਾਪਸ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


ਅੱਖਰ *xstrdup(ਅਚਲ ਅੱਖਰ *s)
{
	ਅੱਖਰ *s2;

	ਜੇ ((s2 = strdup(s)) == ਨਿਰਾ)
		flexfatal (_("memory allocation failure in xstrdup()"));

	ਵਾਪਸ s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

ਪੂਰਨ cclcmp (ਅਚਲ ਖਾਲੀ *a, ਅਚਲ ਖਾਲੀ *b)
{
	ਜੇ (!*(ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) a)
		ਵਾਪਸ 1;
	ਨਹੀਂਤਾਂ
		ਜੇ (!*(ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) b)
			ਵਾਪਸ - 1;
		ਨਹੀਂਤਾਂ
			ਵਾਪਸ *(ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) a - *(ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) b;
}


/* dataend - finish up a block of data declarations */

ਖਾਲੀ dataend (ਅਚਲ ਅੱਖਰ *endit)
{
	/* short circuit any output */
	ਜੇ (gentables) {

		ਜੇ (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		ਜੇ (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

ਖਾਲੀ dataflush (ਖਾਲੀ)
{
	ਪ੍ਰਤਿਜ੍ਞਾ (gentables);

	ਜੇ (datapos > 0)
		outc ('\n');

	ਜੇ (++dataline >= NUMDATALINES) {
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

ਖਾਲੀ flexerror (ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ)
{
	fprintf (stderr, "%s: %s\n", ਪ੍ਰੋਗਰਾਮ_name, ਸੁਨੇਹਾ);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

ਖਾਲੀ flexfatal (ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 ਪ੍ਰੋਗਰਾਮ_name, ਸੁਨੇਹਾ);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

ਖਾਲੀ lerr (ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ...)
{
	ਅੱਖਰ    errmsg[MAXLINE];
	va_list ਦਲੀਲਾਂ;

	va_ਸ਼ੁਰੂ(ਦਲੀਲਾਂ, ਸੁਨੇਹਾ);
	vsnprintf (errmsg, ਆਕਾਰ(errmsg), ਸੁਨੇਹਾ, ਦਲੀਲਾਂ);
	va_ਸਿਰਾ(ਦਲੀਲਾਂ);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

ਖਾਲੀ lerr_fatal (ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ, ...)
{
	ਅੱਖਰ    errmsg[MAXLINE];
	va_list ਦਲੀਲਾਂ;
	va_ਸ਼ੁਰੂ(ਦਲੀਲਾਂ, ਸੁਨੇਹਾ);

	vsnprintf (errmsg, ਆਕਾਰ(errmsg), ਸੁਨੇਹਾ, ਦਲੀਲਾਂ);
	va_ਸਿਰਾ(ਦਲੀਲਾਂ);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
ਖਾਲੀ ਸਤਰ_directive_ਬਾਹਰਲਾ (FILE *output_file, ਅੱਖਰ *ਰਸਤਾ, ਪੂਰਨ linenum)
{
	ਅੱਖਰ	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	ਅੱਖਰ    directive[MAXLINE*2], filename[MAXLINE];
	ਅੱਖਰ   *s1, *s2, *s3;

	ਜੇ (!ctrl.gen_ਸਤਰ_dirs)
		ਵਾਪਸ;

	s1 = (ਰਸਤਾ != ਨਿਰਾ) ? ਰਸਤਾ : "M4_YY_OUTFILE_NAME";

	ਜੇ ((ਰਸਤਾ != ਨਿਰਾ) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[ਆਕਾਰ (filename) - 2];

	ਜਦੋਂ (s2 < s3 && *s1) {
		ਜੇ (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	ਜੇ (ਰਸਤਾ != ਨਿਰਾ)
		snprintf (directive, ਆਕਾਰ(directive), trace_fmt, linenum, filename);
	ਨਹੀਂਤਾਂ {
		snprintf (directive, ਆਕਾਰ(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	ਜੇ (output_file) {
		fputs (directive, output_file);
	}
	ਨਹੀਂਤਾਂ
		ਜੋੜੋ_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
ਖਾਲੀ mark_defs1 (ਖਾਲੀ)
{
	defs1_ਵਿੱਥ = 0;
	action_array[action_ਸੂਚਕਾਂਕ++] = '\0';
	action_ਵਿੱਥ = prolog_ਵਿੱਥ = action_ਸੂਚਕਾਂਕ;
	action_array[action_ਸੂਚਕਾਂਕ] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
ਖਾਲੀ mark_prolog (ਖਾਲੀ)
{
	action_array[action_ਸੂਚਕਾਂਕ++] = '\0';
	action_ਵਿੱਥ = action_ਸੂਚਕਾਂਕ;
	action_array[action_ਸੂਚਕਾਂਕ] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
ਖਾਲੀ mk2data (ਪੂਰਨ ਮੁੱਲ)
{
	/* short circuit any output */
	ਜੇ (!gentables)
		ਵਾਪਸ;

	ਜੇ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ਜੇ (datapos == 0)
		/* Indent. */
		ਬਾਹਰਲਾ ("    ");

	ਨਹੀਂਤਾਂ
	  outc (',');

	++datapos;

	ਬਾਹਰਲਾ_dec ("%5d", ਮੁੱਲ);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
ਖਾਲੀ mkdata (ਪੂਰਨ ਮੁੱਲ)
{
	/* short circuit any output */
	ਜੇ (!gentables)
		ਵਾਪਸ;

	ਜੇ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ਜੇ (datapos == 0)
		/* Indent. */
		ਬਾਹਰਲਾ ("    ");
	ਨਹੀਂਤਾਂ
		outc (',');
	++datapos;

	ਬਾਹਰਲਾ_dec ("%5d", ਮੁੱਲ);
}


/* myctoi - return the integer represented by a string of digits */

ਪੂਰਨ myctoi (ਅਚਲ ਅੱਖਰ *array)
{
	ਪੂਰਨ     val = 0;

	(ਖਾਲੀ) ਲੜੀ_ਤੋਂ_ਪੜ੍ਹੋ (array, "%d", &val);

	ਵਾਪਸ val;
}


/* myesc - return character corresponding to escape sequence */

ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ myesc (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ array[])
{
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ    c, esc_char;

	ਚੋਣ (array[1]) {
	ਹਾਲਤ 'b':
		ਵਾਪਸ '\b';
	ਹਾਲਤ 'f':
		ਵਾਪਸ '\f';
	ਹਾਲਤ 'n':
		ਵਾਪਸ '\n';
	ਹਾਲਤ 'r':
		ਵਾਪਸ '\r';
	ਹਾਲਤ 't':
		ਵਾਪਸ '\t';
	ਹਾਲਤ 'a':
		ਵਾਪਸ '\a';
	ਹਾਲਤ 'v':
		ਵਾਪਸ '\v';
	ਹਾਲਤ '0':
	ਹਾਲਤ '1':
	ਹਾਲਤ '2':
	ਹਾਲਤ '3':
	ਹਾਲਤ '4':
	ਹਾਲਤ '5':
	ਹਾਲਤ '6':
	ਹਾਲਤ '7':
		{		/* \<octal> */
			ਪੂਰਨ     sptr = 1;

			ਜਦੋਂ (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) strtoul (array + 1, ਨਿਰਾ, 8);

			array[sptr] = c;

			ਵਾਪਸ esc_char;
		}

	ਹਾਲਤ 'x':
		{		/* \x<hex> */
			ਪੂਰਨ     sptr = 2;

			ਜਦੋਂ (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) strtoul (array + 2, ਨਿਰਾ, 16);

			array[sptr] = c;

			ਵਾਪਸ esc_char;
		}

	ਮੂਲ:
		ਵਾਪਸ array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

ਖਾਲੀ ਬਾਹਰਲਾ (ਅਚਲ ਅੱਖਰ *str)
{
	fputs (str, stdout);
}

ਖਾਲੀ ਬਾਹਰਲਾ_dec (ਅਚਲ ਅੱਖਰ *fmt, ਪੂਰਨ n)
{
	fprintf (stdout, fmt, n);
}

ਖਾਲੀ ਬਾਹਰਲਾ_dec2 (ਅਚਲ ਅੱਖਰ *fmt, ਪੂਰਨ n1, ਪੂਰਨ n2)
{
	fprintf (stdout, fmt, n1, n2);
}

ਖਾਲੀ ਬਾਹਰਲਾ_hex (ਅਚਲ ਅੱਖਰ *fmt, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ x)
{
	fprintf (stdout, fmt, x);
}

ਖਾਲੀ ਬਾਹਰਲਾ_str (ਅਚਲ ਅੱਖਰ *fmt, ਅਚਲ ਅੱਖਰ str[])
{
	fprintf (stdout,fmt, str);
}

ਖਾਲੀ ਬਾਹਰਲਾ_str_dec (ਅਚਲ ਅੱਖਰ *fmt, ਅਚਲ ਅੱਖਰ str[], ਪੂਰਨ n)
{
	fprintf (stdout,fmt, str, n);
}

ਖਾਲੀ outc (ਪੂਰਨ c)
{
	fputc (c, stdout);
}

ਖਾਲੀ outn (ਅਚਲ ਅੱਖਰ *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
ਖਾਲੀ ਬਾਹਰਲਾ_m4_define (ਅਚਲ ਅੱਖਰ* def, ਅਚਲ ਅੱਖਰ* val)
{
    ਅਚਲ ਅੱਖਰ * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

ਅੱਖਰ   *readable_form (ਪੂਰਨ c)
{
	ਸਥਿਰ ਅੱਖਰ rform[20];

	ਜੇ ((c >= 0 && c < 32) || c >= 127) {
		ਚੋਣ (c) {
		ਹਾਲਤ '\b':
			ਵਾਪਸ "\\b";
		ਹਾਲਤ '\f':
			ਵਾਪਸ "\\f";
		ਹਾਲਤ '\n':
			ਵਾਪਸ "\\n";
		ਹਾਲਤ '\r':
			ਵਾਪਸ "\\r";
		ਹਾਲਤ '\t':
			ਵਾਪਸ "\\t";
		ਹਾਲਤ '\a':
			ਵਾਪਸ "\\a";
		ਹਾਲਤ '\v':
			ਵਾਪਸ "\\v";
		ਮੂਲ:
			ਜੇ(env.trace_hex)
				snprintf (rform, ਆਕਾਰ(rform), "\\x%.2x", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) c);
			ਨਹੀਂਤਾਂ
				snprintf (rform, ਆਕਾਰ(rform), "\\%.3o", (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ) c);
			ਵਾਪਸ rform;
		}
	}

	ਨਹੀਂਤਾਂ ਜੇ (c == ' ')
		ਵਾਪਸ "' '";

	ਨਹੀਂਤਾਂ {
		rform[0] = (ਅੱਖਰ) c;
		rform[1] = '\0';

		ਵਾਪਸ rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

ਖਾਲੀ   *reallocate_array (ਖਾਲੀ *array, ਪੂਰਨ ਮਾਪ, size_t element_ਮਾਪ)
{
	ਖਾਲੀ *new_array;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_REALLOCARR
	new_array = array;
	ਜੇ (reallocarr(&new_array, (size_t) ਮਾਪ, element_ਮਾਪ)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#ਨਹੀਂਤਾਂ
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) ਮਾਪ, element_ਮਾਪ);
# ਨਹੀਂਤਾਂ
	/* Do manual overflow detection */
	size_t ਅੰਕ_ਬਾਈਟਾਂ = (size_t) ਮਾਪ * element_ਮਾਪ;
	new_array = (ਮਾਪ && ਮਾਪ_MAX / (size_t) ਮਾਪ < element_ਮਾਪ) ? ਨਿਰਾ :
		realloc(array, ਅੰਕ_ਬਾਈਟਾਂ);
# endif
	ਜੇ (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#ਜੇ_ਅੰਤ
	ਵਾਪਸ new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

ਖਾਲੀ transition_struct_ਬਾਹਰਲਾ (ਪੂਰਨ element_v, ਪੂਰਨ element_n)
{

	/* short circuit any output */
	ਜੇ (!gentables)
		ਵਾਪਸ;

	ਬਾਹਰਲਾ_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_ਲੰਮਾਈ;

	ਜੇ (datapos >= 79 - TRANS_STRUCT_PRINT_ਲੰਮਾਈ) {
		outc ('\n');

		ਜੇ (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
ਖਾਲੀ   *yy_flex_xmalloc (ਪੂਰਨ ਮਾਪ)
{
	ਖਾਲੀ   *ਨਤੀਜਾ;

	ਨਤੀਜਾ = ਸਮ੍ਰਿਤੀ_ਦਿਓ((size_t) ਮਾਪ);
	ਜੇ (!ਨਤੀਜਾ)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	ਵਾਪਸ ਨਤੀਜਾ;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
ਅੱਖਰ   *chomp (ਅੱਖਰ *str)
{
	ਅੱਖਰ   *p = str;

	ਜੇ (!str || !*str)	/* s is null or empty string */
		ਵਾਪਸ str;

	/* find end of string minus one */
	ਜਦੋਂ (*p)
		++p;
	--p;

	/* eat newlines */
	ਜਦੋਂ (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	ਵਾਪਸ str;
}

ਖਾਲੀ comment(ਅਚਲ ਅੱਖਰ *txt)
{
	ਅੱਖਰ buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[ਲੜੀ_ਲੰਬਾਈ(buf)-1] == '\n';

	ਜੇ (eol)
		buf[ਲੜੀ_ਲੰਬਾਈ(buf)-1] = '\0';
	ਬਾਹਰਲਾ_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	ਜੇ (eol)
		outc ('\n');
}


