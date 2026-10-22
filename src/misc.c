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
void add_action (const char *new_text)
{
	ціле     len = (ціле) strlen (new_text);

	поки (len + action_index >= action_size - 10 /* slop */ ) {

		якщо (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		інакше
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

void   *allocate_array (ціле size, size_t element_size)
{
	повернути reallocate_array(NULL, size, element_size);
}


/* all_lower - true if a string is all lower-case */

ціле all_lower (char *str)
{
	поки (*str) {
		якщо (!isascii ((unsigned char) * str) || !islower ((unsigned char) * str))
			повернути 0;
		++str;
	}

	повернути 1;
}


/* all_upper - true if a string is all upper-case */

ціле all_upper (char *str)
{
	поки (*str) {
		якщо (!isascii ((unsigned char) * str) || !isupper ((unsigned char) * str))
			повернути 0;
		++str;
	}

	повернути 1;
}


/* intcmp - compares two integers for use by qsort. */

ціле intcmp (const void *a, const void *b)
{
  повернути *(const ціле *) a - *(const ціле *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

void check_char (ціле c)
{
	якщо (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	якщо (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned char clower (ціле c)
{
	повернути (unsigned char) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


char *xstrdup(const char *s)
{
	char *s2;

	якщо ((s2 = strdup(s)) == NULL)
		flexfatal (_("memory allocation failure in xstrdup()"));

	повернути s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

ціле cclcmp (const void *a, const void *b)
{
	якщо (!*(const unsigned char *) a)
		повернути 1;
	інакше
		якщо (!*(const unsigned char *) b)
			повернути - 1;
		інакше
			повернути *(const unsigned char *) a - *(const unsigned char *) b;
}


/* dataend - finish up a block of data declarations */

void dataend (const char *endit)
{
	/* short circuit any output */
	якщо (gentables) {

		якщо (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		якщо (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

void dataflush (void)
{
	assert (gentables);

	якщо (datapos > 0)
		outc ('\n');

	якщо (++dataline >= NUMDATALINES) {
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

void flexerror (const char *msg)
{
	fprintf (stderr, "%s: %s\n", program_name, msg);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

void flexfatal (const char *msg)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, msg);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

void lerr (const char *msg, ...)
{
	char    errmsg[MAXLINE];
	va_list args;

	va_start(args, msg);
	vsnprintf (errmsg, sizeof(errmsg), msg, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

void lerr_fatal (const char *msg, ...)
{
	char    errmsg[MAXLINE];
	va_list args;
	va_start(args, msg);

	vsnprintf (errmsg, sizeof(errmsg), msg, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
void line_directive_out (FILE *output_file, char *path, ціле linenum)
{
	char	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	char    directive[MAXLINE*2], filename[MAXLINE];
	char   *s1, *s2, *s3;

	якщо (!ctrl.gen_line_dirs)
		повернути;

	s1 = (path != NULL) ? path : "M4_YY_OUTFILE_NAME";

	якщо ((path != NULL) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[sizeof (filename) - 2];

	поки (s2 < s3 && *s1) {
		якщо (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	якщо (path != NULL)
		snprintf (directive, sizeof(directive), trace_fmt, linenum, filename);
	інакше {
		snprintf (directive, sizeof(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	якщо (output_file) {
		fputs (directive, output_file);
	}
	інакше
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
void mk2data (ціле value)
{
	/* short circuit any output */
	якщо (!gentables)
		повернути;

	якщо (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	якщо (datapos == 0)
		/* Indent. */
		out ("    ");

	інакше
	  outc (',');

	++datapos;

	out_dec ("%5d", value);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
void mkdata (ціле value)
{
	/* short circuit any output */
	якщо (!gentables)
		повернути;

	якщо (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	якщо (datapos == 0)
		/* Indent. */
		out ("    ");
	інакше
		outc (',');
	++datapos;

	out_dec ("%5d", value);
}


/* myctoi - return the integer represented by a string of digits */

ціле myctoi (const char *array)
{
	ціле     val = 0;

	(void) sscanf (array, "%d", &val);

	повернути val;
}


/* myesc - return character corresponding to escape sequence */

unsigned char myesc (unsigned char array[])
{
	unsigned char    c, esc_char;

	switch (array[1]) {
	case 'b':
		повернути '\b';
	case 'f':
		повернути '\f';
	case 'n':
		повернути '\n';
	case 'r':
		повернути '\r';
	case 't':
		повернути '\t';
	case 'a':
		повернути '\a';
	case 'v':
		повернути '\v';
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		{		/* \<octal> */
			ціле     sptr = 1;

			поки (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned char) strtoul (array + 1, NULL, 8);

			array[sptr] = c;

			повернути esc_char;
		}

	case 'x':
		{		/* \x<hex> */
			ціле     sptr = 2;

			поки (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned char) strtoul (array + 2, NULL, 16);

			array[sptr] = c;

			повернути esc_char;
		}

	default:
		повернути array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

void out (const char *str)
{
	fputs (str, stdout);
}

void out_dec (const char *fmt, ціле n)
{
	fprintf (stdout, fmt, n);
}

void out_dec2 (const char *fmt, ціле n1, ціле n2)
{
	fprintf (stdout, fmt, n1, n2);
}

void out_hex (const char *fmt, unsigned ціле x)
{
	fprintf (stdout, fmt, x);
}

void out_str (const char *fmt, const char str[])
{
	fprintf (stdout,fmt, str);
}

void out_str_dec (const char *fmt, const char str[], ціле n)
{
	fprintf (stdout,fmt, str, n);
}

void outc (ціле c)
{
	fputc (c, stdout);
}

void outn (const char *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
void out_m4_define (const char* def, const char* val)
{
    const char * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

char   *readable_form (ціле c)
{
	static char rform[20];

	якщо ((c >= 0 && c < 32) || c >= 127) {
		switch (c) {
		case '\b':
			повернути "\\b";
		case '\f':
			повернути "\\f";
		case '\n':
			повернути "\\n";
		case '\r':
			повернути "\\r";
		case '\t':
			повернути "\\t";
		case '\a':
			повернути "\\a";
		case '\v':
			повернути "\\v";
		default:
			якщо(env.trace_hex)
				snprintf (rform, sizeof(rform), "\\x%.2x", (unsigned ціле) c);
			інакше
				snprintf (rform, sizeof(rform), "\\%.3o", (unsigned ціле) c);
			повернути rform;
		}
	}

	інакше якщо (c == ' ')
		повернути "' '";

	інакше {
		rform[0] = (char) c;
		rform[1] = '\0';

		повернути rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

void   *reallocate_array (void *array, ціле size, size_t element_size)
{
	void *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	якщо (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#інакше
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# інакше
	/* Do manual overflow detection */
	size_t num_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? NULL :
		realloc(array, num_bytes);
# endif
	якщо (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	повернути new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

void transition_struct_out (ціле element_v, ціле element_n)
{

	/* short circuit any output */
	якщо (!gentables)
		повернути;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	якщо (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		якщо (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
void   *yy_flex_xmalloc (ціле size)
{
	void   *result;

	result = malloc((size_t) size);
	якщо (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	повернути result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
char   *chomp (char *str)
{
	char   *p = str;

	якщо (!str || !*str)	/* s is null or empty string */
		повернути str;

	/* find end of string minus one */
	поки (*p)
		++p;
	--p;

	/* eat newlines */
	поки (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	повернути str;
}

void comment(const char *txt)
{
	char buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	якщо (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	якщо (eol)
		outc ('\n');
}


