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
#அந்தர்பாவ "flexdef.h"
#அந்தர்பாவ "tables.h"

/* Append "new_text" to the running buffer. */
வெறுமை add_action (மாறிலி எழுத்து *new_text)
{
	முழு     len = (முழு) strlen (new_text);

	போது (len + action_index >= action_size - 10 /* slop */ ) {

		எனில் (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		இல்லையெனில்
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

வெறுமை   *allocate_array (முழு size, size_t element_size)
{
	திரும்பு reallocate_array(வெற்று, size, element_size);
}


/* all_lower - true if a string is all lower-case */

முழு all_lower (எழுத்து *str)
{
	போது (*str) {
		எனில் (!isascii ((unsigned எழுத்து) * str) || !islower ((unsigned எழுத்து) * str))
			திரும்பு 0;
		++str;
	}

	திரும்பு 1;
}


/* all_upper - true if a string is all upper-case */

முழு all_upper (எழுத்து *str)
{
	போது (*str) {
		எனில் (!isascii ((unsigned எழுத்து) * str) || !isupper ((unsigned எழுத்து) * str))
			திரும்பு 0;
		++str;
	}

	திரும்பு 1;
}


/* intcmp - compares two integers for use by qsort. */

முழு intcmp (மாறிலி வெறுமை *a, மாறிலி வெறுமை *b)
{
  திரும்பு *(மாறிலி முழு *) a - *(மாறிலி முழு *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

வெறுமை check_char (முழு c)
{
	எனில் (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	எனில் (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned எழுத்து clower (முழு c)
{
	திரும்பு (unsigned எழுத்து) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


எழுத்து *xstrdup(மாறிலி எழுத்து *s)
{
	எழுத்து *s2;

	எனில் ((s2 = strdup(s)) == வெற்று)
		flexfatal (_("memory allocation failure in xstrdup()"));

	திரும்பு s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

முழு cclcmp (மாறிலி வெறுமை *a, மாறிலி வெறுமை *b)
{
	எனில் (!*(மாறிலி unsigned எழுத்து *) a)
		திரும்பு 1;
	இல்லையெனில்
		எனில் (!*(மாறிலி unsigned எழுத்து *) b)
			திரும்பு - 1;
		இல்லையெனில்
			திரும்பு *(மாறிலி unsigned எழுத்து *) a - *(மாறிலி unsigned எழுத்து *) b;
}


/* dataend - finish up a block of data declarations */

வெறுமை dataend (மாறிலி எழுத்து *endit)
{
	/* short circuit any output */
	எனில் (gentables) {

		எனில் (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		எனில் (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

வெறுமை dataflush (வெறுமை)
{
	ப்ரதிஜ்ஞா (gentables);

	எனில் (datapos > 0)
		outc ('\n');

	எனில் (++dataline >= NUMDATALINES) {
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

வெறுமை flexerror (மாறிலி எழுத்து *செய்தி)
{
	fprintf (stderr, "%s: %s\n", program_name, செய்தி);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

வெறுமை flexfatal (மாறிலி எழுத்து *செய்தி)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, செய்தி);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

வெறுமை lerr (மாறிலி எழுத்து *செய்தி, ...)
{
	எழுத்து    errmsg[MAXLINE];
	va_list args;

	va_start(args, செய்தி);
	vsnprintf (errmsg, அளவு(errmsg), செய்தி, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

வெறுமை lerr_fatal (மாறிலி எழுத்து *செய்தி, ...)
{
	எழுத்து    errmsg[MAXLINE];
	va_list args;
	va_start(args, செய்தி);

	vsnprintf (errmsg, அளவு(errmsg), செய்தி, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
வெறுமை வரி_directive_out (FILE *output_file, எழுத்து *path, முழு linenum)
{
	எழுத்து	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	எழுத்து    directive[MAXLINE*2], filename[MAXLINE];
	எழுத்து   *s1, *s2, *s3;

	எனில் (!ctrl.gen_வரி_dirs)
		திரும்பு;

	s1 = (path != வெற்று) ? path : "M4_YY_OUTFILE_NAME";

	எனில் ((path != வெற்று) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[அளவு (filename) - 2];

	போது (s2 < s3 && *s1) {
		எனில் (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	எனில் (path != வெற்று)
		snprintf (directive, அளவு(directive), trace_fmt, linenum, filename);
	இல்லையெனில் {
		snprintf (directive, அளவு(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	எனில் (output_file) {
		fputs (directive, output_file);
	}
	இல்லையெனில்
		add_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
வெறுமை mark_defs1 (வெறுமை)
{
	defs1_offset = 0;
	action_array[action_index++] = '\0';
	action_offset = prolog_offset = action_index;
	action_array[action_index] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
வெறுமை mark_prolog (வெறுமை)
{
	action_array[action_index++] = '\0';
	action_offset = action_index;
	action_array[action_index] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
வெறுமை mk2data (முழு மதிப்பு)
{
	/* short circuit any output */
	எனில் (!gentables)
		திரும்பு;

	எனில் (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	எனில் (datapos == 0)
		/* Indent. */
		out ("    ");

	இல்லையெனில்
	  outc (',');

	++datapos;

	out_dec ("%5d", மதிப்பு);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
வெறுமை mkdata (முழு மதிப்பு)
{
	/* short circuit any output */
	எனில் (!gentables)
		திரும்பு;

	எனில் (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	எனில் (datapos == 0)
		/* Indent. */
		out ("    ");
	இல்லையெனில்
		outc (',');
	++datapos;

	out_dec ("%5d", மதிப்பு);
}


/* myctoi - return the integer represented by a string of digits */

முழு myctoi (மாறிலி எழுத்து *array)
{
	முழு     val = 0;

	(வெறுமை) sscanf (array, "%d", &val);

	திரும்பு val;
}


/* myesc - return character corresponding to escape sequence */

unsigned எழுத்து myesc (unsigned எழுத்து array[])
{
	unsigned எழுத்து    c, esc_char;

	தேர்வு (array[1]) {
	நிலை 'b':
		திரும்பு '\b';
	நிலை 'f':
		திரும்பு '\f';
	நிலை 'n':
		திரும்பு '\n';
	நிலை 'r':
		திரும்பு '\r';
	நிலை 't':
		திரும்பு '\t';
	நிலை 'a':
		திரும்பு '\a';
	நிலை 'v':
		திரும்பு '\v';
	நிலை '0':
	நிலை '1':
	நிலை '2':
	நிலை '3':
	நிலை '4':
	நிலை '5':
	நிலை '6':
	நிலை '7':
		{		/* \<octal> */
			முழு     sptr = 1;

			போது (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned எழுத்து) strtoul (array + 1, வெற்று, 8);

			array[sptr] = c;

			திரும்பு esc_char;
		}

	நிலை 'x':
		{		/* \x<hex> */
			முழு     sptr = 2;

			போது (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned எழுத்து) strtoul (array + 2, வெற்று, 16);

			array[sptr] = c;

			திரும்பு esc_char;
		}

	இயல்பு:
		திரும்பு array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

வெறுமை out (மாறிலி எழுத்து *str)
{
	fputs (str, stdout);
}

வெறுமை out_dec (மாறிலி எழுத்து *fmt, முழு n)
{
	fprintf (stdout, fmt, n);
}

வெறுமை out_dec2 (மாறிலி எழுத்து *fmt, முழு n1, முழு n2)
{
	fprintf (stdout, fmt, n1, n2);
}

வெறுமை out_hex (மாறிலி எழுத்து *fmt, unsigned முழு x)
{
	fprintf (stdout, fmt, x);
}

வெறுமை out_str (மாறிலி எழுத்து *fmt, மாறிலி எழுத்து str[])
{
	fprintf (stdout,fmt, str);
}

வெறுமை out_str_dec (மாறிலி எழுத்து *fmt, மாறிலி எழுத்து str[], முழு n)
{
	fprintf (stdout,fmt, str, n);
}

வெறுமை outc (முழு c)
{
	fputc (c, stdout);
}

வெறுமை outn (மாறிலி எழுத்து *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
வெறுமை out_m4_define (மாறிலி எழுத்து* def, மாறிலி எழுத்து* val)
{
    மாறிலி எழுத்து * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

எழுத்து   *readable_form (முழு c)
{
	நிலையான எழுத்து rform[20];

	எனில் ((c >= 0 && c < 32) || c >= 127) {
		தேர்வு (c) {
		நிலை '\b':
			திரும்பு "\\b";
		நிலை '\f':
			திரும்பு "\\f";
		நிலை '\n':
			திரும்பு "\\n";
		நிலை '\r':
			திரும்பு "\\r";
		நிலை '\t':
			திரும்பு "\\t";
		நிலை '\a':
			திரும்பு "\\a";
		நிலை '\v':
			திரும்பு "\\v";
		இயல்பு:
			எனில்(env.trace_hex)
				snprintf (rform, அளவு(rform), "\\x%.2x", (unsigned முழு) c);
			இல்லையெனில்
				snprintf (rform, அளவு(rform), "\\%.3o", (unsigned முழு) c);
			திரும்பு rform;
		}
	}

	இல்லையெனில் எனில் (c == ' ')
		திரும்பு "' '";

	இல்லையெனில் {
		rform[0] = (எழுத்து) c;
		rform[1] = '\0';

		திரும்பு rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

வெறுமை   *reallocate_array (வெறுமை *array, முழு size, size_t element_size)
{
	வெறுமை *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	எனில் (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#இல்லையெனில்
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# இல்லையெனில்
	/* Do manual overflow detection */
	size_t இலக்கம்_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? வெற்று :
		realloc(array, இலக்கம்_bytes);
# endif
	எனில் (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	திரும்பு new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

வெறுமை transition_struct_out (முழு element_v, முழு element_n)
{

	/* short circuit any output */
	எனில் (!gentables)
		திரும்பு;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	எனில் (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		எனில் (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
வெறுமை   *yy_flex_xmalloc (முழு size)
{
	வெறுமை   *result;

	result = malloc((size_t) size);
	எனில் (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	திரும்பு result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
எழுத்து   *chomp (எழுத்து *str)
{
	எழுத்து   *p = str;

	எனில் (!str || !*str)	/* s is null or empty string */
		திரும்பு str;

	/* find end of string minus one */
	போது (*p)
		++p;
	--p;

	/* eat newlines */
	போது (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	திரும்பு str;
}

வெறுமை comment(மாறிலி எழுத்து *txt)
{
	எழுத்து buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	எனில் (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	எனில் (eol)
		outc ('\n');
}


