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
ಶೂನ್ಯ add_action (ಧ್ರುವ ವರ್ಣ *new_text)
{
	ಪೂರ್ಣಾಙ್ಕ     len = (ಪೂರ್ಣಾಙ್ಕ) strlen (new_text);

	ಯಾವತ್ (len + action_index >= action_size - 10 /* slop */ ) {

		ಯದಿ (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		ಅನ್ಯಥಾ
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

ಶೂನ್ಯ   *allocate_array (ಪೂರ್ಣಾಙ್ಕ size, size_t element_size)
{
	ಪ್ರತ್ಯಾಗಮ reallocate_array(ರಿಕ್ತ, size, element_size);
}


/* all_lower - true if a string is all lower-case */

ಪೂರ್ಣಾಙ್ಕ all_lower (ವರ್ಣ *str)
{
	ಯಾವತ್ (*str) {
		ಯದಿ (!isascii ((unsigned ವರ್ಣ) * str) || !islower ((unsigned ವರ್ಣ) * str))
			ಪ್ರತ್ಯಾಗಮ 0;
		++str;
	}

	ಪ್ರತ್ಯಾಗಮ 1;
}


/* all_upper - true if a string is all upper-case */

ಪೂರ್ಣಾಙ್ಕ all_upper (ವರ್ಣ *str)
{
	ಯಾವತ್ (*str) {
		ಯದಿ (!isascii ((unsigned ವರ್ಣ) * str) || !isupper ((unsigned ವರ್ಣ) * str))
			ಪ್ರತ್ಯಾಗಮ 0;
		++str;
	}

	ಪ್ರತ್ಯಾಗಮ 1;
}


/* intcmp - compares two integers for use by qsort. */

ಪೂರ್ಣಾಙ್ಕ intcmp (ಧ್ರುವ ಶೂನ್ಯ *a, ಧ್ರುವ ಶೂನ್ಯ *b)
{
  ಪ್ರತ್ಯಾಗಮ *(ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *) a - *(ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

ಶೂನ್ಯ check_char (ಪೂರ್ಣಾಙ್ಕ c)
{
	ಯದಿ (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	ಯದಿ (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned ವರ್ಣ clower (ಪೂರ್ಣಾಙ್ಕ c)
{
	ಪ್ರತ್ಯಾಗಮ (unsigned ವರ್ಣ) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


ವರ್ಣ *xstrdup(ಧ್ರುವ ವರ್ಣ *s)
{
	ವರ್ಣ *s2;

	ಯದಿ ((s2 = strdup(s)) == ರಿಕ್ತ)
		flexfatal (_("memory allocation failure in xstrdup()"));

	ಪ್ರತ್ಯಾಗಮ s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

ಪೂರ್ಣಾಙ್ಕ cclcmp (ಧ್ರುವ ಶೂನ್ಯ *a, ಧ್ರುವ ಶೂನ್ಯ *b)
{
	ಯದಿ (!*(ಧ್ರುವ unsigned ವರ್ಣ *) a)
		ಪ್ರತ್ಯಾಗಮ 1;
	ಅನ್ಯಥಾ
		ಯದಿ (!*(ಧ್ರುವ unsigned ವರ್ಣ *) b)
			ಪ್ರತ್ಯಾಗಮ - 1;
		ಅನ್ಯಥಾ
			ಪ್ರತ್ಯಾಗಮ *(ಧ್ರುವ unsigned ವರ್ಣ *) a - *(ಧ್ರುವ unsigned ವರ್ಣ *) b;
}


/* dataend - finish up a block of data declarations */

ಶೂನ್ಯ dataend (ಧ್ರುವ ವರ್ಣ *endit)
{
	/* short circuit any output */
	ಯದಿ (gentables) {

		ಯದಿ (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		ಯದಿ (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

ಶೂನ್ಯ dataflush (ಶೂನ್ಯ)
{
	ಪ್ರತಿಜ್ಞಾ (gentables);

	ಯದಿ (datapos > 0)
		outc ('\n');

	ಯದಿ (++dataline >= NUMDATALINES) {
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

ಶೂನ್ಯ flexerror (ಧ್ರುವ ವರ್ಣ *ಸಂದೇಶ)
{
	fprintf (stderr, "%s: %s\n", program_name, ಸಂದೇಶ);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

ಶೂನ್ಯ flexfatal (ಧ್ರುವ ವರ್ಣ *ಸಂದೇಶ)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, ಸಂದೇಶ);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

ಶೂನ್ಯ lerr (ಧ್ರುವ ವರ್ಣ *ಸಂದೇಶ, ...)
{
	ವರ್ಣ    errmsg[MAXLINE];
	va_list args;

	va_start(args, ಸಂದೇಶ);
	vsnprintf (errmsg, ಪರಿಮಾಣ(errmsg), ಸಂದೇಶ, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

ಶೂನ್ಯ lerr_fatal (ಧ್ರುವ ವರ್ಣ *ಸಂದೇಶ, ...)
{
	ವರ್ಣ    errmsg[MAXLINE];
	va_list args;
	va_start(args, ಸಂದೇಶ);

	vsnprintf (errmsg, ಪರಿಮಾಣ(errmsg), ಸಂದೇಶ, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
ಶೂನ್ಯ ಸಾಲು_directive_out (FILE *output_file, ವರ್ಣ *path, ಪೂರ್ಣಾಙ್ಕ linenum)
{
	ವರ್ಣ	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	ವರ್ಣ    directive[MAXLINE*2], filename[MAXLINE];
	ವರ್ಣ   *s1, *s2, *s3;

	ಯದಿ (!ctrl.gen_ಸಾಲು_dirs)
		ಪ್ರತ್ಯಾಗಮ;

	s1 = (path != ರಿಕ್ತ) ? path : "M4_YY_OUTFILE_NAME";

	ಯದಿ ((path != ರಿಕ್ತ) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[ಪರಿಮಾಣ (filename) - 2];

	ಯಾವತ್ (s2 < s3 && *s1) {
		ಯದಿ (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	ಯದಿ (path != ರಿಕ್ತ)
		snprintf (directive, ಪರಿಮಾಣ(directive), trace_fmt, linenum, filename);
	ಅನ್ಯಥಾ {
		snprintf (directive, ಪರಿಮಾಣ(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	ಯದಿ (output_file) {
		fputs (directive, output_file);
	}
	ಅನ್ಯಥಾ
		add_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
ಶೂನ್ಯ mark_defs1 (ಶೂನ್ಯ)
{
	defs1_offset = 0;
	action_array[action_index++] = '\0';
	action_offset = prolog_offset = action_index;
	action_array[action_index] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
ಶೂನ್ಯ mark_prolog (ಶೂನ್ಯ)
{
	action_array[action_index++] = '\0';
	action_offset = action_index;
	action_array[action_index] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
ಶೂನ್ಯ mk2data (ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯ)
{
	/* short circuit any output */
	ಯದಿ (!gentables)
		ಪ್ರತ್ಯಾಗಮ;

	ಯದಿ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ಯದಿ (datapos == 0)
		/* Indent. */
		out ("    ");

	ಅನ್ಯಥಾ
	  outc (',');

	++datapos;

	out_dec ("%5d", ಮೌಲ್ಯ);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
ಶೂನ್ಯ mkdata (ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯ)
{
	/* short circuit any output */
	ಯದಿ (!gentables)
		ಪ್ರತ್ಯಾಗಮ;

	ಯದಿ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ಯದಿ (datapos == 0)
		/* Indent. */
		out ("    ");
	ಅನ್ಯಥಾ
		outc (',');
	++datapos;

	out_dec ("%5d", ಮೌಲ್ಯ);
}


/* myctoi - return the integer represented by a string of digits */

ಪೂರ್ಣಾಙ್ಕ myctoi (ಧ್ರುವ ವರ್ಣ *array)
{
	ಪೂರ್ಣಾಙ್ಕ     val = 0;

	(ಶೂನ್ಯ) sscanf (array, "%d", &val);

	ಪ್ರತ್ಯಾಗಮ val;
}


/* myesc - return character corresponding to escape sequence */

unsigned ವರ್ಣ myesc (unsigned ವರ್ಣ array[])
{
	unsigned ವರ್ಣ    c, esc_char;

	ವಿಕಲ್ಪ (array[1]) {
	ಪಕ್ಷ 'b':
		ಪ್ರತ್ಯಾಗಮ '\b';
	ಪಕ್ಷ 'f':
		ಪ್ರತ್ಯಾಗಮ '\f';
	ಪಕ್ಷ 'n':
		ಪ್ರತ್ಯಾಗಮ '\n';
	ಪಕ್ಷ 'r':
		ಪ್ರತ್ಯಾಗಮ '\r';
	ಪಕ್ಷ 't':
		ಪ್ರತ್ಯಾಗಮ '\t';
	ಪಕ್ಷ 'a':
		ಪ್ರತ್ಯಾಗಮ '\a';
	ಪಕ್ಷ 'v':
		ಪ್ರತ್ಯಾಗಮ '\v';
	ಪಕ್ಷ '0':
	ಪಕ್ಷ '1':
	ಪಕ್ಷ '2':
	ಪಕ್ಷ '3':
	ಪಕ್ಷ '4':
	ಪಕ್ಷ '5':
	ಪಕ್ಷ '6':
	ಪಕ್ಷ '7':
		{		/* \<octal> */
			ಪೂರ್ಣಾಙ್ಕ     sptr = 1;

			ಯಾವತ್ (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned ವರ್ಣ) strtoul (array + 1, ರಿಕ್ತ, 8);

			array[sptr] = c;

			ಪ್ರತ್ಯಾಗಮ esc_char;
		}

	ಪಕ್ಷ 'x':
		{		/* \x<hex> */
			ಪೂರ್ಣಾಙ್ಕ     sptr = 2;

			ಯಾವತ್ (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned ವರ್ಣ) strtoul (array + 2, ರಿಕ್ತ, 16);

			array[sptr] = c;

			ಪ್ರತ್ಯಾಗಮ esc_char;
		}

	ಸ್ವಭಾವ:
		ಪ್ರತ್ಯಾಗಮ array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

ಶೂನ್ಯ out (ಧ್ರುವ ವರ್ಣ *str)
{
	fputs (str, stdout);
}

ಶೂನ್ಯ out_dec (ಧ್ರುವ ವರ್ಣ *fmt, ಪೂರ್ಣಾಙ್ಕ n)
{
	fprintf (stdout, fmt, n);
}

ಶೂನ್ಯ out_dec2 (ಧ್ರುವ ವರ್ಣ *fmt, ಪೂರ್ಣಾಙ್ಕ n1, ಪೂರ್ಣಾಙ್ಕ n2)
{
	fprintf (stdout, fmt, n1, n2);
}

ಶೂನ್ಯ out_hex (ಧ್ರುವ ವರ್ಣ *fmt, unsigned ಪೂರ್ಣಾಙ್ಕ x)
{
	fprintf (stdout, fmt, x);
}

ಶೂನ್ಯ out_str (ಧ್ರುವ ವರ್ಣ *fmt, ಧ್ರುವ ವರ್ಣ str[])
{
	fprintf (stdout,fmt, str);
}

ಶೂನ್ಯ out_str_dec (ಧ್ರುವ ವರ್ಣ *fmt, ಧ್ರುವ ವರ್ಣ str[], ಪೂರ್ಣಾಙ್ಕ n)
{
	fprintf (stdout,fmt, str, n);
}

ಶೂನ್ಯ outc (ಪೂರ್ಣಾಙ್ಕ c)
{
	fputc (c, stdout);
}

ಶೂನ್ಯ outn (ಧ್ರುವ ವರ್ಣ *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
ಶೂನ್ಯ out_m4_define (ಧ್ರುವ ವರ್ಣ* def, ಧ್ರುವ ವರ್ಣ* val)
{
    ಧ್ರುವ ವರ್ಣ * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

ವರ್ಣ   *readable_form (ಪೂರ್ಣಾಙ್ಕ c)
{
	ಸ್ಥಿರ ವರ್ಣ rform[20];

	ಯದಿ ((c >= 0 && c < 32) || c >= 127) {
		ವಿಕಲ್ಪ (c) {
		ಪಕ್ಷ '\b':
			ಪ್ರತ್ಯಾಗಮ "\\b";
		ಪಕ್ಷ '\f':
			ಪ್ರತ್ಯಾಗಮ "\\f";
		ಪಕ್ಷ '\n':
			ಪ್ರತ್ಯಾಗಮ "\\n";
		ಪಕ್ಷ '\r':
			ಪ್ರತ್ಯಾಗಮ "\\r";
		ಪಕ್ಷ '\t':
			ಪ್ರತ್ಯಾಗಮ "\\t";
		ಪಕ್ಷ '\a':
			ಪ್ರತ್ಯಾಗಮ "\\a";
		ಪಕ್ಷ '\v':
			ಪ್ರತ್ಯಾಗಮ "\\v";
		ಸ್ವಭಾವ:
			ಯದಿ(env.trace_hex)
				snprintf (rform, ಪರಿಮಾಣ(rform), "\\x%.2x", (unsigned ಪೂರ್ಣಾಙ್ಕ) c);
			ಅನ್ಯಥಾ
				snprintf (rform, ಪರಿಮಾಣ(rform), "\\%.3o", (unsigned ಪೂರ್ಣಾಙ್ಕ) c);
			ಪ್ರತ್ಯಾಗಮ rform;
		}
	}

	ಅನ್ಯಥಾ ಯದಿ (c == ' ')
		ಪ್ರತ್ಯಾಗಮ "' '";

	ಅನ್ಯಥಾ {
		rform[0] = (ವರ್ಣ) c;
		rform[1] = '\0';

		ಪ್ರತ್ಯಾಗಮ rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

ಶೂನ್ಯ   *reallocate_array (ಶೂನ್ಯ *array, ಪೂರ್ಣಾಙ್ಕ size, size_t element_size)
{
	ಶೂನ್ಯ *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	ಯದಿ (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#ಅನ್ಯಥಾ
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# ಅನ್ಯಥಾ
	/* Do manual overflow detection */
	size_t ಅಂಕೆ_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? ರಿಕ್ತ :
		realloc(array, ಅಂಕೆ_bytes);
# endif
	ಯದಿ (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	ಪ್ರತ್ಯಾಗಮ new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

ಶೂನ್ಯ transition_struct_out (ಪೂರ್ಣಾಙ್ಕ element_v, ಪೂರ್ಣಾಙ್ಕ element_n)
{

	/* short circuit any output */
	ಯದಿ (!gentables)
		ಪ್ರತ್ಯಾಗಮ;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	ಯದಿ (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		ಯದಿ (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
ಶೂನ್ಯ   *yy_flex_xmalloc (ಪೂರ್ಣಾಙ್ಕ size)
{
	ಶೂನ್ಯ   *result;

	result = malloc((size_t) size);
	ಯದಿ (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	ಪ್ರತ್ಯಾಗಮ result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
ವರ್ಣ   *chomp (ವರ್ಣ *str)
{
	ವರ್ಣ   *p = str;

	ಯದಿ (!str || !*str)	/* s is null or empty string */
		ಪ್ರತ್ಯಾಗಮ str;

	/* find end of string minus one */
	ಯಾವತ್ (*p)
		++p;
	--p;

	/* eat newlines */
	ಯಾವತ್ (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	ಪ್ರತ್ಯಾಗಮ str;
}

ಶೂನ್ಯ comment(ಧ್ರುವ ವರ್ಣ *txt)
{
	ವರ್ಣ buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	ಯದಿ (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	ಯದಿ (eol)
		outc ('\n');
}


