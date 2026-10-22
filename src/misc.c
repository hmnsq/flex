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
#include "flexdef.h"
#include "tables.h"

/* Append "new_text" to the running buffer. */
void add_action (const var_na *new_text)
{
	ចំនួនគត់     len = (ចំនួនគត់) strlen (new_text);

	ខណៈពេល (len + action_index >= action_size - 10 /* slop */ ) {

		ប្រសិនបើ (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		បើមិនដូច្នេះ
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

void   *allocate_array (ចំនួនគត់ size, size_t element_size)
{
	ត្រឡប់ reallocate_array(NULL, size, element_size);
}


/* all_lower - true if a string is all lower-case */

ចំនួនគត់ all_lower (var_na *str)
{
	ខណៈពេល (*str) {
		ប្រសិនបើ (!isascii ((unsigned var_na) * str) || !islower ((unsigned var_na) * str))
			ត្រឡប់ 0;
		++str;
	}

	ត្រឡប់ 1;
}


/* all_upper - true if a string is all upper-case */

ចំនួនគត់ all_upper (var_na *str)
{
	ខណៈពេល (*str) {
		ប្រសិនបើ (!isascii ((unsigned var_na) * str) || !isupper ((unsigned var_na) * str))
			ត្រឡប់ 0;
		++str;
	}

	ត្រឡប់ 1;
}


/* intcmp - compares two integers for use by qsort. */

ចំនួនគត់ intcmp (const void *a, const void *b)
{
  ត្រឡប់ *(const ចំនួនគត់ *) a - *(const ចំនួនគត់ *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

void check_char (ចំនួនគត់ c)
{
	ប្រសិនបើ (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	ប្រសិនបើ (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned var_na clower (ចំនួនគត់ c)
{
	ត្រឡប់ (unsigned var_na) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


var_na *xstrdup(const var_na *s)
{
	var_na *s2;

	ប្រសិនបើ ((s2 = strdup(s)) == NULL)
		flexfatal (_("memory allocation failure in xstrdup()"));

	ត្រឡប់ s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

ចំនួនគត់ cclcmp (const void *a, const void *b)
{
	ប្រសិនបើ (!*(const unsigned var_na *) a)
		ត្រឡប់ 1;
	បើមិនដូច្នេះ
		ប្រសិនបើ (!*(const unsigned var_na *) b)
			ត្រឡប់ - 1;
		បើមិនដូច្នេះ
			ត្រឡប់ *(const unsigned var_na *) a - *(const unsigned var_na *) b;
}


/* dataend - finish up a block of data declarations */

void dataend (const var_na *endit)
{
	/* short circuit any output */
	ប្រសិនបើ (gentables) {

		ប្រសិនបើ (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		ប្រសិនបើ (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

void dataflush (void)
{
	assert (gentables);

	ប្រសិនបើ (datapos > 0)
		outc ('\n');

	ប្រសិនបើ (++dataline >= NUMDATALINES) {
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

void flexerror (const var_na *msg)
{
	fprintf (stderr, "%s: %s\n", program_name, msg);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

void flexfatal (const var_na *msg)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, msg);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

void lerr (const var_na *msg, ...)
{
	var_na    errmsg[MAXLINE];
	va_list args;

	va_start(args, msg);
	vsnprintf (errmsg, parimaa_na(errmsg), msg, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

void lerr_fatal (const var_na *msg, ...)
{
	var_na    errmsg[MAXLINE];
	va_list args;
	va_start(args, msg);

	vsnprintf (errmsg, parimaa_na(errmsg), msg, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
void line_directive_out (FILE *output_file, var_na *path, ចំនួនគត់ linenum)
{
	var_na	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	var_na    directive[MAXLINE*2], filename[MAXLINE];
	var_na   *s1, *s2, *s3;

	ប្រសិនបើ (!ctrl.gen_line_dirs)
		ត្រឡប់;

	s1 = (path != NULL) ? path : "M4_YY_OUTFILE_NAME";

	ប្រសិនបើ ((path != NULL) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[parimaa_na (filename) - 2];

	ខណៈពេល (s2 < s3 && *s1) {
		ប្រសិនបើ (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	ប្រសិនបើ (path != NULL)
		snprintf (directive, parimaa_na(directive), trace_fmt, linenum, filename);
	បើមិនដូច្នេះ {
		snprintf (directive, parimaa_na(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	ប្រសិនបើ (output_file) {
		fputs (directive, output_file);
	}
	បើមិនដូច្នេះ
		add_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
void mark_defs1 (void)
{
	defs1_offset = 0;
	action_array[action_index++] = '\0';
	action_offset = prolog_offset = action_index;
	action_array[action_index] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
void mark_prolog (void)
{
	action_array[action_index++] = '\0';
	action_offset = action_index;
	action_array[action_index] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
void mk2data (ចំនួនគត់ value)
{
	/* short circuit any output */
	ប្រសិនបើ (!gentables)
		ត្រឡប់;

	ប្រសិនបើ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ប្រសិនបើ (datapos == 0)
		/* Indent. */
		out ("    ");

	បើមិនដូច្នេះ
	  outc (',');

	++datapos;

	out_dec ("%5d", value);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
void mkdata (ចំនួនគត់ value)
{
	/* short circuit any output */
	ប្រសិនបើ (!gentables)
		ត្រឡប់;

	ប្រសិនបើ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ប្រសិនបើ (datapos == 0)
		/* Indent. */
		out ("    ");
	បើមិនដូច្នេះ
		outc (',');
	++datapos;

	out_dec ("%5d", value);
}


/* myctoi - return the integer represented by a string of digits */

ចំនួនគត់ myctoi (const var_na *array)
{
	ចំនួនគត់     val = 0;

	(void) sscanf (array, "%d", &val);

	ត្រឡប់ val;
}


/* myesc - return character corresponding to escape sequence */

unsigned var_na myesc (unsigned var_na array[])
{
	unsigned var_na    c, esc_char;

	switch (array[1]) {
	pak_sa 'b':
		ត្រឡប់ '\b';
	pak_sa 'f':
		ត្រឡប់ '\f';
	pak_sa 'n':
		ត្រឡប់ '\n';
	pak_sa 'r':
		ត្រឡប់ '\r';
	pak_sa 't':
		ត្រឡប់ '\t';
	pak_sa 'a':
		ត្រឡប់ '\a';
	pak_sa 'v':
		ត្រឡប់ '\v';
	pak_sa '0':
	pak_sa '1':
	pak_sa '2':
	pak_sa '3':
	pak_sa '4':
	pak_sa '5':
	pak_sa '6':
	pak_sa '7':
		{		/* \<octal> */
			ចំនួនគត់     sptr = 1;

			ខណៈពេល (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned var_na) strtoul (array + 1, NULL, 8);

			array[sptr] = c;

			ត្រឡប់ esc_char;
		}

	pak_sa 'x':
		{		/* \x<hex> */
			ចំនួនគត់     sptr = 2;

			ខណៈពេល (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned var_na) strtoul (array + 2, NULL, 16);

			array[sptr] = c;

			ត្រឡប់ esc_char;
		}

	default:
		ត្រឡប់ array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

void out (const var_na *str)
{
	fputs (str, stdout);
}

void out_dec (const var_na *fmt, ចំនួនគត់ n)
{
	fprintf (stdout, fmt, n);
}

void out_dec2 (const var_na *fmt, ចំនួនគត់ n1, ចំនួនគត់ n2)
{
	fprintf (stdout, fmt, n1, n2);
}

void out_hex (const var_na *fmt, unsigned ចំនួនគត់ x)
{
	fprintf (stdout, fmt, x);
}

void out_str (const var_na *fmt, const var_na str[])
{
	fprintf (stdout,fmt, str);
}

void out_str_dec (const var_na *fmt, const var_na str[], ចំនួនគត់ n)
{
	fprintf (stdout,fmt, str, n);
}

void outc (ចំនួនគត់ c)
{
	fputc (c, stdout);
}

void outn (const var_na *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
void out_m4_define (const var_na* def, const var_na* val)
{
    const var_na * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

var_na   *readable_form (ចំនួនគត់ c)
{
	static var_na rform[20];

	ប្រសិនបើ ((c >= 0 && c < 32) || c >= 127) {
		switch (c) {
		pak_sa '\b':
			ត្រឡប់ "\\b";
		pak_sa '\f':
			ត្រឡប់ "\\f";
		pak_sa '\n':
			ត្រឡប់ "\\n";
		pak_sa '\r':
			ត្រឡប់ "\\r";
		pak_sa '\t':
			ត្រឡប់ "\\t";
		pak_sa '\a':
			ត្រឡប់ "\\a";
		pak_sa '\v':
			ត្រឡប់ "\\v";
		default:
			ប្រសិនបើ(env.trace_hex)
				snprintf (rform, parimaa_na(rform), "\\x%.2x", (unsigned ចំនួនគត់) c);
			បើមិនដូច្នេះ
				snprintf (rform, parimaa_na(rform), "\\%.3o", (unsigned ចំនួនគត់) c);
			ត្រឡប់ rform;
		}
	}

	បើមិនដូច្នេះ ប្រសិនបើ (c == ' ')
		ត្រឡប់ "' '";

	បើមិនដូច្នេះ {
		rform[0] = (var_na) c;
		rform[1] = '\0';

		ត្រឡប់ rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

void   *reallocate_array (void *array, ចំនួនគត់ size, size_t element_size)
{
	void *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	ប្រសិនបើ (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#បើមិនដូច្នេះ
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# បើមិនដូច្នេះ
	/* Do manual overflow detection */
	size_t num_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? NULL :
		realloc(array, num_bytes);
# endif
	ប្រសិនបើ (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	ត្រឡប់ new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

void transition_struct_out (ចំនួនគត់ element_v, ចំនួនគត់ element_n)
{

	/* short circuit any output */
	ប្រសិនបើ (!gentables)
		ត្រឡប់;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	ប្រសិនបើ (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		ប្រសិនបើ (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
void   *yy_flex_xmalloc (ចំនួនគត់ size)
{
	void   *result;

	result = malloc((size_t) size);
	ប្រសិនបើ (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	ត្រឡប់ result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
var_na   *chomp (var_na *str)
{
	var_na   *p = str;

	ប្រសិនបើ (!str || !*str)	/* s is null or empty string */
		ត្រឡប់ str;

	/* find end of string minus one */
	ខណៈពេល (*p)
		++p;
	--p;

	/* eat newlines */
	ខណៈពេល (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	ត្រឡប់ str;
}

void comment(const var_na *txt)
{
	var_na buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	ប្រសិនបើ (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	ប្រសិនបើ (eol)
		outc ('\n');
}


