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
	số_nguyên     len = (số_nguyên) strlen (new_text);

	trong_khi (len + action_index >= action_size - 10 /* slop */ ) {

		nếu (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		không_thì
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

void   *allocate_array (số_nguyên size, size_t element_size)
{
	trả_về reallocate_array(NULL, size, element_size);
}


/* all_lower - true if a string is all lower-case */

số_nguyên all_lower (char *str)
{
	trong_khi (*str) {
		nếu (!isascii ((unsigned char) * str) || !islower ((unsigned char) * str))
			trả_về 0;
		++str;
	}

	trả_về 1;
}


/* all_upper - true if a string is all upper-case */

số_nguyên all_upper (char *str)
{
	trong_khi (*str) {
		nếu (!isascii ((unsigned char) * str) || !isupper ((unsigned char) * str))
			trả_về 0;
		++str;
	}

	trả_về 1;
}


/* intcmp - compares two integers for use by qsort. */

số_nguyên intcmp (const void *a, const void *b)
{
  trả_về *(const số_nguyên *) a - *(const số_nguyên *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

void check_char (số_nguyên c)
{
	nếu (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	nếu (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned char clower (số_nguyên c)
{
	trả_về (unsigned char) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


char *xstrdup(const char *s)
{
	char *s2;

	nếu ((s2 = strdup(s)) == NULL)
		flexfatal (_("memory allocation failure in xstrdup()"));

	trả_về s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

số_nguyên cclcmp (const void *a, const void *b)
{
	nếu (!*(const unsigned char *) a)
		trả_về 1;
	không_thì
		nếu (!*(const unsigned char *) b)
			trả_về - 1;
		không_thì
			trả_về *(const unsigned char *) a - *(const unsigned char *) b;
}


/* dataend - finish up a block of data declarations */

void dataend (const char *endit)
{
	/* short circuit any output */
	nếu (gentables) {

		nếu (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		nếu (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

void dataflush (void)
{
	assert (gentables);

	nếu (datapos > 0)
		outc ('\n');

	nếu (++dataline >= NUMDATALINES) {
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
void line_directive_out (FILE *output_file, char *path, số_nguyên linenum)
{
	char	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	char    directive[MAXLINE*2], filename[MAXLINE];
	char   *s1, *s2, *s3;

	nếu (!ctrl.gen_line_dirs)
		trả_về;

	s1 = (path != NULL) ? path : "M4_YY_OUTFILE_NAME";

	nếu ((path != NULL) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[sizeof (filename) - 2];

	trong_khi (s2 < s3 && *s1) {
		nếu (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	nếu (path != NULL)
		snprintf (directive, sizeof(directive), trace_fmt, linenum, filename);
	không_thì {
		snprintf (directive, sizeof(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	nếu (output_file) {
		fputs (directive, output_file);
	}
	không_thì
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
void mk2data (số_nguyên value)
{
	/* short circuit any output */
	nếu (!gentables)
		trả_về;

	nếu (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	nếu (datapos == 0)
		/* Indent. */
		out ("    ");

	không_thì
	  outc (',');

	++datapos;

	out_dec ("%5d", value);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
void mkdata (số_nguyên value)
{
	/* short circuit any output */
	nếu (!gentables)
		trả_về;

	nếu (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	nếu (datapos == 0)
		/* Indent. */
		out ("    ");
	không_thì
		outc (',');
	++datapos;

	out_dec ("%5d", value);
}


/* myctoi - return the integer represented by a string of digits */

số_nguyên myctoi (const char *array)
{
	số_nguyên     val = 0;

	(void) sscanf (array, "%d", &val);

	trả_về val;
}


/* myesc - return character corresponding to escape sequence */

unsigned char myesc (unsigned char array[])
{
	unsigned char    c, esc_char;

	switch (array[1]) {
	case 'b':
		trả_về '\b';
	case 'f':
		trả_về '\f';
	case 'n':
		trả_về '\n';
	case 'r':
		trả_về '\r';
	case 't':
		trả_về '\t';
	case 'a':
		trả_về '\a';
	case 'v':
		trả_về '\v';
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
		{		/* \<octal> */
			số_nguyên     sptr = 1;

			trong_khi (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned char) strtoul (array + 1, NULL, 8);

			array[sptr] = c;

			trả_về esc_char;
		}

	case 'x':
		{		/* \x<hex> */
			số_nguyên     sptr = 2;

			trong_khi (sptr <= 3 && isxdigit (array[sptr])) {
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

			trả_về esc_char;
		}

	default:
		trả_về array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

void out (const char *str)
{
	fputs (str, stdout);
}

void out_dec (const char *fmt, số_nguyên n)
{
	fprintf (stdout, fmt, n);
}

void out_dec2 (const char *fmt, số_nguyên n1, số_nguyên n2)
{
	fprintf (stdout, fmt, n1, n2);
}

void out_hex (const char *fmt, unsigned số_nguyên x)
{
	fprintf (stdout, fmt, x);
}

void out_str (const char *fmt, const char str[])
{
	fprintf (stdout,fmt, str);
}

void out_str_dec (const char *fmt, const char str[], số_nguyên n)
{
	fprintf (stdout,fmt, str, n);
}

void outc (số_nguyên c)
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

char   *readable_form (số_nguyên c)
{
	static char rform[20];

	nếu ((c >= 0 && c < 32) || c >= 127) {
		switch (c) {
		case '\b':
			trả_về "\\b";
		case '\f':
			trả_về "\\f";
		case '\n':
			trả_về "\\n";
		case '\r':
			trả_về "\\r";
		case '\t':
			trả_về "\\t";
		case '\a':
			trả_về "\\a";
		case '\v':
			trả_về "\\v";
		default:
			nếu(env.trace_hex)
				snprintf (rform, sizeof(rform), "\\x%.2x", (unsigned số_nguyên) c);
			không_thì
				snprintf (rform, sizeof(rform), "\\%.3o", (unsigned số_nguyên) c);
			trả_về rform;
		}
	}

	không_thì nếu (c == ' ')
		trả_về "' '";

	không_thì {
		rform[0] = (char) c;
		rform[1] = '\0';

		trả_về rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

void   *reallocate_array (void *array, số_nguyên size, size_t element_size)
{
	void *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	nếu (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#không_thì
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# không_thì
	/* Do manual overflow detection */
	size_t num_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? NULL :
		realloc(array, num_bytes);
# endif
	nếu (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	trả_về new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

void transition_struct_out (số_nguyên element_v, số_nguyên element_n)
{

	/* short circuit any output */
	nếu (!gentables)
		trả_về;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	nếu (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		nếu (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
void   *yy_flex_xmalloc (số_nguyên size)
{
	void   *result;

	result = malloc((size_t) size);
	nếu (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	trả_về result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
char   *chomp (char *str)
{
	char   *p = str;

	nếu (!str || !*str)	/* s is null or empty string */
		trả_về str;

	/* find end of string minus one */
	trong_khi (*p)
		++p;
	--p;

	/* eat newlines */
	trong_khi (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	trả_về str;
}

void comment(const char *txt)
{
	char buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	nếu (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	nếu (eol)
		outc ('\n');
}


