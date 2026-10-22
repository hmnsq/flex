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
#অন্তর্ভাব "flexdef.h"
#অন্তর্ভাব "tables.h"

/* Append "new_text" to the running buffer. */
শূন্য add_action (ধ্রুব বর্ণ *new_text)
{
	পূর্ণাঙ্ক     len = (পূর্ণাঙ্ক) strlen (new_text);

	যাবত্ (len + action_index >= action_size - 10 /* slop */ ) {

		যদি (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		অন্যথা
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

শূন্য   *allocate_array (পূর্ণাঙ্ক size, size_t element_size)
{
	প্রত্যাগম reallocate_array(রিক্ত, size, element_size);
}


/* all_lower - true if a string is all lower-case */

পূর্ণাঙ্ক all_lower (বর্ণ *str)
{
	যাবত্ (*str) {
		যদি (!isascii ((unsigned বর্ণ) * str) || !islower ((unsigned বর্ণ) * str))
			প্রত্যাগম 0;
		++str;
	}

	প্রত্যাগম 1;
}


/* all_upper - true if a string is all upper-case */

পূর্ণাঙ্ক all_upper (বর্ণ *str)
{
	যাবত্ (*str) {
		যদি (!isascii ((unsigned বর্ণ) * str) || !isupper ((unsigned বর্ণ) * str))
			প্রত্যাগম 0;
		++str;
	}

	প্রত্যাগম 1;
}


/* intcmp - compares two integers for use by qsort. */

পূর্ণাঙ্ক intcmp (ধ্রুব শূন্য *a, ধ্রুব শূন্য *b)
{
  প্রত্যাগম *(ধ্রুব পূর্ণাঙ্ক *) a - *(ধ্রুব পূর্ণাঙ্ক *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

শূন্য check_char (পূর্ণাঙ্ক c)
{
	যদি (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	যদি (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned বর্ণ clower (পূর্ণাঙ্ক c)
{
	প্রত্যাগম (unsigned বর্ণ) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


বর্ণ *xstrdup(ধ্রুব বর্ণ *s)
{
	বর্ণ *s2;

	যদি ((s2 = strdup(s)) == রিক্ত)
		flexfatal (_("memory allocation failure in xstrdup()"));

	প্রত্যাগম s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

পূর্ণাঙ্ক cclcmp (ধ্রুব শূন্য *a, ধ্রুব শূন্য *b)
{
	যদি (!*(ধ্রুব unsigned বর্ণ *) a)
		প্রত্যাগম 1;
	অন্যথা
		যদি (!*(ধ্রুব unsigned বর্ণ *) b)
			প্রত্যাগম - 1;
		অন্যথা
			প্রত্যাগম *(ধ্রুব unsigned বর্ণ *) a - *(ধ্রুব unsigned বর্ণ *) b;
}


/* dataend - finish up a block of data declarations */

শূন্য dataend (ধ্রুব বর্ণ *endit)
{
	/* short circuit any output */
	যদি (gentables) {

		যদি (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		যদি (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

শূন্য dataflush (শূন্য)
{
	প্রতিজ্ঞা (gentables);

	যদি (datapos > 0)
		outc ('\n');

	যদি (++dataline >= NUMDATALINES) {
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

শূন্য flexerror (ধ্রুব বর্ণ *বার্তা)
{
	fprintf (stderr, "%s: %s\n", program_name, বার্তা);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

শূন্য flexfatal (ধ্রুব বর্ণ *বার্তা)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, বার্তা);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

শূন্য lerr (ধ্রুব বর্ণ *বার্তা, ...)
{
	বর্ণ    errmsg[MAXLINE];
	va_list args;

	va_start(args, বার্তা);
	vsnprintf (errmsg, পরিমাণ(errmsg), বার্তা, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

শূন্য lerr_fatal (ধ্রুব বর্ণ *বার্তা, ...)
{
	বর্ণ    errmsg[MAXLINE];
	va_list args;
	va_start(args, বার্তা);

	vsnprintf (errmsg, পরিমাণ(errmsg), বার্তা, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
শূন্য সারি_directive_out (FILE *output_file, বর্ণ *path, পূর্ণাঙ্ক linenum)
{
	বর্ণ	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	বর্ণ    directive[MAXLINE*2], filename[MAXLINE];
	বর্ণ   *s1, *s2, *s3;

	যদি (!ctrl.gen_সারি_dirs)
		প্রত্যাগম;

	s1 = (path != রিক্ত) ? path : "M4_YY_OUTFILE_NAME";

	যদি ((path != রিক্ত) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[পরিমাণ (filename) - 2];

	যাবত্ (s2 < s3 && *s1) {
		যদি (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	যদি (path != রিক্ত)
		snprintf (directive, পরিমাণ(directive), trace_fmt, linenum, filename);
	অন্যথা {
		snprintf (directive, পরিমাণ(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	যদি (output_file) {
		fputs (directive, output_file);
	}
	অন্যথা
		add_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
শূন্য mark_defs1 (শূন্য)
{
	defs1_offset = 0;
	action_array[action_index++] = '\0';
	action_offset = prolog_offset = action_index;
	action_array[action_index] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
শূন্য mark_prolog (শূন্য)
{
	action_array[action_index++] = '\0';
	action_offset = action_index;
	action_array[action_index] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
শূন্য mk2data (পূর্ণাঙ্ক মান)
{
	/* short circuit any output */
	যদি (!gentables)
		প্রত্যাগম;

	যদি (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	যদি (datapos == 0)
		/* Indent. */
		out ("    ");

	অন্যথা
	  outc (',');

	++datapos;

	out_dec ("%5d", মান);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
শূন্য mkdata (পূর্ণাঙ্ক মান)
{
	/* short circuit any output */
	যদি (!gentables)
		প্রত্যাগম;

	যদি (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	যদি (datapos == 0)
		/* Indent. */
		out ("    ");
	অন্যথা
		outc (',');
	++datapos;

	out_dec ("%5d", মান);
}


/* myctoi - return the integer represented by a string of digits */

পূর্ণাঙ্ক myctoi (ধ্রুব বর্ণ *array)
{
	পূর্ণাঙ্ক     val = 0;

	(শূন্য) sscanf (array, "%d", &val);

	প্রত্যাগম val;
}


/* myesc - return character corresponding to escape sequence */

unsigned বর্ণ myesc (unsigned বর্ণ array[])
{
	unsigned বর্ণ    c, esc_char;

	বিকল্প (array[1]) {
	পক্ষ 'b':
		প্রত্যাগম '\b';
	পক্ষ 'f':
		প্রত্যাগম '\f';
	পক্ষ 'n':
		প্রত্যাগম '\n';
	পক্ষ 'r':
		প্রত্যাগম '\r';
	পক্ষ 't':
		প্রত্যাগম '\t';
	পক্ষ 'a':
		প্রত্যাগম '\a';
	পক্ষ 'v':
		প্রত্যাগম '\v';
	পক্ষ '0':
	পক্ষ '1':
	পক্ষ '2':
	পক্ষ '3':
	পক্ষ '4':
	পক্ষ '5':
	পক্ষ '6':
	পক্ষ '7':
		{		/* \<octal> */
			পূর্ণাঙ্ক     sptr = 1;

			যাবত্ (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned বর্ণ) strtoul (array + 1, রিক্ত, 8);

			array[sptr] = c;

			প্রত্যাগম esc_char;
		}

	পক্ষ 'x':
		{		/* \x<hex> */
			পূর্ণাঙ্ক     sptr = 2;

			যাবত্ (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned বর্ণ) strtoul (array + 2, রিক্ত, 16);

			array[sptr] = c;

			প্রত্যাগম esc_char;
		}

	স্বভাব:
		প্রত্যাগম array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

শূন্য out (ধ্রুব বর্ণ *str)
{
	fputs (str, stdout);
}

শূন্য out_dec (ধ্রুব বর্ণ *fmt, পূর্ণাঙ্ক n)
{
	fprintf (stdout, fmt, n);
}

শূন্য out_dec2 (ধ্রুব বর্ণ *fmt, পূর্ণাঙ্ক n1, পূর্ণাঙ্ক n2)
{
	fprintf (stdout, fmt, n1, n2);
}

শূন্য out_hex (ধ্রুব বর্ণ *fmt, unsigned পূর্ণাঙ্ক x)
{
	fprintf (stdout, fmt, x);
}

শূন্য out_str (ধ্রুব বর্ণ *fmt, ধ্রুব বর্ণ str[])
{
	fprintf (stdout,fmt, str);
}

শূন্য out_str_dec (ধ্রুব বর্ণ *fmt, ধ্রুব বর্ণ str[], পূর্ণাঙ্ক n)
{
	fprintf (stdout,fmt, str, n);
}

শূন্য outc (পূর্ণাঙ্ক c)
{
	fputc (c, stdout);
}

শূন্য outn (ধ্রুব বর্ণ *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
শূন্য out_m4_define (ধ্রুব বর্ণ* def, ধ্রুব বর্ণ* val)
{
    ধ্রুব বর্ণ * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

বর্ণ   *readable_form (পূর্ণাঙ্ক c)
{
	স্থির বর্ণ rform[20];

	যদি ((c >= 0 && c < 32) || c >= 127) {
		বিকল্প (c) {
		পক্ষ '\b':
			প্রত্যাগম "\\b";
		পক্ষ '\f':
			প্রত্যাগম "\\f";
		পক্ষ '\n':
			প্রত্যাগম "\\n";
		পক্ষ '\r':
			প্রত্যাগম "\\r";
		পক্ষ '\t':
			প্রত্যাগম "\\t";
		পক্ষ '\a':
			প্রত্যাগম "\\a";
		পক্ষ '\v':
			প্রত্যাগম "\\v";
		স্বভাব:
			যদি(env.trace_hex)
				snprintf (rform, পরিমাণ(rform), "\\x%.2x", (unsigned পূর্ণাঙ্ক) c);
			অন্যথা
				snprintf (rform, পরিমাণ(rform), "\\%.3o", (unsigned পূর্ণাঙ্ক) c);
			প্রত্যাগম rform;
		}
	}

	অন্যথা যদি (c == ' ')
		প্রত্যাগম "' '";

	অন্যথা {
		rform[0] = (বর্ণ) c;
		rform[1] = '\0';

		প্রত্যাগম rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

শূন্য   *reallocate_array (শূন্য *array, পূর্ণাঙ্ক size, size_t element_size)
{
	শূন্য *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	যদি (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#অন্যথা
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# অন্যথা
	/* Do manual overflow detection */
	size_t অঙ্ক_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? রিক্ত :
		realloc(array, অঙ্ক_bytes);
# endif
	যদি (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	প্রত্যাগম new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

শূন্য transition_struct_out (পূর্ণাঙ্ক element_v, পূর্ণাঙ্ক element_n)
{

	/* short circuit any output */
	যদি (!gentables)
		প্রত্যাগম;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	যদি (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		যদি (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
শূন্য   *yy_flex_xmalloc (পূর্ণাঙ্ক size)
{
	শূন্য   *result;

	result = malloc((size_t) size);
	যদি (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	প্রত্যাগম result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
বর্ণ   *chomp (বর্ণ *str)
{
	বর্ণ   *p = str;

	যদি (!str || !*str)	/* s is null or empty string */
		প্রত্যাগম str;

	/* find end of string minus one */
	যাবত্ (*p)
		++p;
	--p;

	/* eat newlines */
	যাবত্ (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	প্রত্যাগম str;
}

শূন্য comment(ধ্রুব বর্ণ *txt)
{
	বর্ণ buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	যদি (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	যদি (eol)
		outc ('\n');
}


