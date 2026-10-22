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
শূন্য add_action (ধ্রুবক অক্ষর *new_text)
{
	পূর্ণসংখ্যা     len = (পূর্ণসংখ্যা) strlen (new_text);

	যখন (len + action_সূচক >= action_আকার - 10 /* slop */ ) {

		যদি (action_আকার > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_আকার += action_আকার / 8;
		অন্যথা
			action_আকার = action_আকার * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_আকার);
	}

	strcpy (&action_array[action_সূচক], new_text);

	action_সূচক += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

শূন্য   *allocate_array (পূর্ণসংখ্যা আকার_2, size_t element_আকার)
{
	ফেরত reallocate_array(ফাঁকা, আকার_2, element_আকার);
}


/* all_lower - true if a string is all lower-case */

পূর্ণসংখ্যা all_lower (অক্ষর *str)
{
	যখন (*str) {
		যদি (!isascii ((unsigned অক্ষর) * str) || !islower ((unsigned অক্ষর) * str))
			ফেরত 0;
		++str;
	}

	ফেরত 1;
}


/* all_upper - true if a string is all upper-case */

পূর্ণসংখ্যা all_upper (অক্ষর *str)
{
	যখন (*str) {
		যদি (!isascii ((unsigned অক্ষর) * str) || !isupper ((unsigned অক্ষর) * str))
			ফেরত 0;
		++str;
	}

	ফেরত 1;
}


/* intcmp - compares two integers for use by qsort. */

পূর্ণসংখ্যা intcmp (ধ্রুবক শূন্য *a, ধ্রুবক শূন্য *b)
{
  ফেরত *(ধ্রুবক পূর্ণসংখ্যা *) a - *(ধ্রুবক পূর্ণসংখ্যা *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

শূন্য check_char (পূর্ণসংখ্যা c)
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

unsigned অক্ষর clower (পূর্ণসংখ্যা c)
{
	ফেরত (unsigned অক্ষর) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


অক্ষর *xstrdup(ধ্রুবক অক্ষর *s)
{
	অক্ষর *s2;

	যদি ((s2 = strdup(s)) == ফাঁকা)
		flexfatal (_("memory allocation failure in xstrdup()"));

	ফেরত s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

পূর্ণসংখ্যা cclcmp (ধ্রুবক শূন্য *a, ধ্রুবক শূন্য *b)
{
	যদি (!*(ধ্রুবক unsigned অক্ষর *) a)
		ফেরত 1;
	অন্যথা
		যদি (!*(ধ্রুবক unsigned অক্ষর *) b)
			ফেরত - 1;
		অন্যথা
			ফেরত *(ধ্রুবক unsigned অক্ষর *) a - *(ধ্রুবক unsigned অক্ষর *) b;
}


/* dataend - finish up a block of data declarations */

শূন্য dataend (ধ্রুবক অক্ষর *endit)
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

শূন্য flexerror (ধ্রুবক অক্ষর *বার্তা)
{
	fprintf (stderr, "%s: %s\n", program_name, বার্তা);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

শূন্য flexfatal (ধ্রুবক অক্ষর *বার্তা)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, বার্তা);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

শূন্য lerr (ধ্রুবক অক্ষর *বার্তা, ...)
{
	অক্ষর    errmsg[MAXLINE];
	va_list args;

	va_start(args, বার্তা);
	vsnprintf (errmsg, আকার(errmsg), বার্তা, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

শূন্য lerr_fatal (ধ্রুবক অক্ষর *বার্তা, ...)
{
	অক্ষর    errmsg[MAXLINE];
	va_list args;
	va_start(args, বার্তা);

	vsnprintf (errmsg, আকার(errmsg), বার্তা, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
শূন্য সারি_directive_out (FILE *output_file, অক্ষর *path, পূর্ণসংখ্যা linenum)
{
	অক্ষর	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	অক্ষর    directive[MAXLINE*2], filename[MAXLINE];
	অক্ষর   *s1, *s2, *s3;

	যদি (!ctrl.gen_সারি_dirs)
		ফেরত;

	s1 = (path != ফাঁকা) ? path : "M4_YY_OUTFILE_NAME";

	যদি ((path != ফাঁকা) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[আকার (filename) - 2];

	যখন (s2 < s3 && *s1) {
		যদি (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	যদি (path != ফাঁকা)
		snprintf (directive, আকার(directive), trace_fmt, linenum, filename);
	অন্যথা {
		snprintf (directive, আকার(directive), trace_fmt, 0, filename);
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
	action_array[action_সূচক++] = '\0';
	action_offset = prolog_offset = action_সূচক;
	action_array[action_সূচক] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
শূন্য mark_prolog (শূন্য)
{
	action_array[action_সূচক++] = '\0';
	action_offset = action_সূচক;
	action_array[action_সূচক] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
শূন্য mk2data (পূর্ণসংখ্যা মান)
{
	/* short circuit any output */
	যদি (!gentables)
		ফেরত;

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
শূন্য mkdata (পূর্ণসংখ্যা মান)
{
	/* short circuit any output */
	যদি (!gentables)
		ফেরত;

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

পূর্ণসংখ্যা myctoi (ধ্রুবক অক্ষর *array)
{
	পূর্ণসংখ্যা     val = 0;

	(শূন্য) sscanf (array, "%d", &val);

	ফেরত val;
}


/* myesc - return character corresponding to escape sequence */

unsigned অক্ষর myesc (unsigned অক্ষর array[])
{
	unsigned অক্ষর    c, esc_char;

	নির্বাচন (array[1]) {
	ক্ষেত্র 'b':
		ফেরত '\b';
	ক্ষেত্র 'f':
		ফেরত '\f';
	ক্ষেত্র 'n':
		ফেরত '\n';
	ক্ষেত্র 'r':
		ফেরত '\r';
	ক্ষেত্র 't':
		ফেরত '\t';
	ক্ষেত্র 'a':
		ফেরত '\a';
	ক্ষেত্র 'v':
		ফেরত '\v';
	ক্ষেত্র '0':
	ক্ষেত্র '1':
	ক্ষেত্র '2':
	ক্ষেত্র '3':
	ক্ষেত্র '4':
	ক্ষেত্র '5':
	ক্ষেত্র '6':
	ক্ষেত্র '7':
		{		/* \<octal> */
			পূর্ণসংখ্যা     sptr = 1;

			যখন (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned অক্ষর) strtoul (array + 1, ফাঁকা, 8);

			array[sptr] = c;

			ফেরত esc_char;
		}

	ক্ষেত্র 'x':
		{		/* \x<hex> */
			পূর্ণসংখ্যা     sptr = 2;

			যখন (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned অক্ষর) strtoul (array + 2, ফাঁকা, 16);

			array[sptr] = c;

			ফেরত esc_char;
		}

	পূর্বনির্ধারিত:
		ফেরত array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

শূন্য out (ধ্রুবক অক্ষর *str)
{
	fputs (str, stdout);
}

শূন্য out_dec (ধ্রুবক অক্ষর *fmt, পূর্ণসংখ্যা n)
{
	fprintf (stdout, fmt, n);
}

শূন্য out_dec2 (ধ্রুবক অক্ষর *fmt, পূর্ণসংখ্যা n1, পূর্ণসংখ্যা n2)
{
	fprintf (stdout, fmt, n1, n2);
}

শূন্য out_hex (ধ্রুবক অক্ষর *fmt, unsigned পূর্ণসংখ্যা x)
{
	fprintf (stdout, fmt, x);
}

শূন্য out_str (ধ্রুবক অক্ষর *fmt, ধ্রুবক অক্ষর str[])
{
	fprintf (stdout,fmt, str);
}

শূন্য out_str_dec (ধ্রুবক অক্ষর *fmt, ধ্রুবক অক্ষর str[], পূর্ণসংখ্যা n)
{
	fprintf (stdout,fmt, str, n);
}

শূন্য outc (পূর্ণসংখ্যা c)
{
	fputc (c, stdout);
}

শূন্য outn (ধ্রুবক অক্ষর *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
শূন্য out_m4_define (ধ্রুবক অক্ষর* def, ধ্রুবক অক্ষর* val)
{
    ধ্রুবক অক্ষর * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

অক্ষর   *readable_form (পূর্ণসংখ্যা c)
{
	স্থির অক্ষর rform[20];

	যদি ((c >= 0 && c < 32) || c >= 127) {
		নির্বাচন (c) {
		ক্ষেত্র '\b':
			ফেরত "\\b";
		ক্ষেত্র '\f':
			ফেরত "\\f";
		ক্ষেত্র '\n':
			ফেরত "\\n";
		ক্ষেত্র '\r':
			ফেরত "\\r";
		ক্ষেত্র '\t':
			ফেরত "\\t";
		ক্ষেত্র '\a':
			ফেরত "\\a";
		ক্ষেত্র '\v':
			ফেরত "\\v";
		পূর্বনির্ধারিত:
			যদি(env.trace_hex)
				snprintf (rform, আকার(rform), "\\x%.2x", (unsigned পূর্ণসংখ্যা) c);
			অন্যথা
				snprintf (rform, আকার(rform), "\\%.3o", (unsigned পূর্ণসংখ্যা) c);
			ফেরত rform;
		}
	}

	অন্যথা যদি (c == ' ')
		ফেরত "' '";

	অন্যথা {
		rform[0] = (অক্ষর) c;
		rform[1] = '\0';

		ফেরত rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

শূন্য   *reallocate_array (শূন্য *array, পূর্ণসংখ্যা আকার_2, size_t element_আকার)
{
	শূন্য *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	যদি (reallocarr(&new_array, (size_t) আকার_2, element_আকার)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#অন্যথা
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) আকার_2, element_আকার);
# অন্যথা
	/* Do manual overflow detection */
	size_t অঙ্ক_bytes = (size_t) আকার_2 * element_আকার;
	new_array = (আকার_2 && আকার_MAX / (size_t) আকার_2 < element_আকার) ? ফাঁকা :
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
	ফেরত new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

শূন্য transition_struct_out (পূর্ণসংখ্যা element_v, পূর্ণসংখ্যা element_n)
{

	/* short circuit any output */
	যদি (!gentables)
		ফেরত;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_দৈর্ঘ্য;

	যদি (datapos >= 79 - TRANS_STRUCT_PRINT_দৈর্ঘ্য) {
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
শূন্য   *yy_flex_xmalloc (পূর্ণসংখ্যা আকার_2)
{
	শূন্য   *ফলাফল;

	ফলাফল = malloc((size_t) আকার_2);
	যদি (!ফলাফল)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	ফেরত ফলাফল;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
অক্ষর   *chomp (অক্ষর *str)
{
	অক্ষর   *p = str;

	যদি (!str || !*str)	/* s is null or empty string */
		ফেরত str;

	/* find end of string minus one */
	যখন (*p)
		++p;
	--p;

	/* eat newlines */
	যখন (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	ফেরত str;
}

শূন্য comment(ধ্রুবক অক্ষর *txt)
{
	অক্ষর buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	যদি (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	যদি (eol)
		outc ('\n');
}


