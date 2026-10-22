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
#अन्तर्भाव "flexdef.h"
#अन्तर्भाव "tables.h"

/* Append "new_text" to the running buffer. */
शून्य add_action (ध्रुव वर्ण *new_text)
{
	पूर्णाङ्क     len = (पूर्णाङ्क) strlen (new_text);

	जाव (len + action_index >= action_size - 10 /* slop */ ) {

		जइ (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		अण्णहा
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

शून्य   *allocate_array (पूर्णाङ्क size, size_t element_size)
{
	प्रत्यागम reallocate_array(रिक्त, size, element_size);
}


/* all_lower - true if a string is all lower-case */

पूर्णाङ्क all_lower (वर्ण *str)
{
	जाव (*str) {
		जइ (!isascii ((unsigned वर्ण) * str) || !islower ((unsigned वर्ण) * str))
			प्रत्यागम 0;
		++str;
	}

	प्रत्यागम 1;
}


/* all_upper - true if a string is all upper-case */

पूर्णाङ्क all_upper (वर्ण *str)
{
	जाव (*str) {
		जइ (!isascii ((unsigned वर्ण) * str) || !isupper ((unsigned वर्ण) * str))
			प्रत्यागम 0;
		++str;
	}

	प्रत्यागम 1;
}


/* intcmp - compares two integers for use by qsort. */

पूर्णाङ्क intcmp (ध्रुव शून्य *a, ध्रुव शून्य *b)
{
  प्रत्यागम *(ध्रुव पूर्णाङ्क *) a - *(ध्रुव पूर्णाङ्क *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

शून्य check_char (पूर्णाङ्क c)
{
	जइ (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	जइ (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned वर्ण clower (पूर्णाङ्क c)
{
	प्रत्यागम (unsigned वर्ण) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


वर्ण *xstrdup(ध्रुव वर्ण *s)
{
	वर्ण *s2;

	जइ ((s2 = strdup(s)) == रिक्त)
		flexfatal (_("memory allocation failure in xstrdup()"));

	प्रत्यागम s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

पूर्णाङ्क cclcmp (ध्रुव शून्य *a, ध्रुव शून्य *b)
{
	जइ (!*(ध्रुव unsigned वर्ण *) a)
		प्रत्यागम 1;
	अण्णहा
		जइ (!*(ध्रुव unsigned वर्ण *) b)
			प्रत्यागम - 1;
		अण्णहा
			प्रत्यागम *(ध्रुव unsigned वर्ण *) a - *(ध्रुव unsigned वर्ण *) b;
}


/* dataend - finish up a block of data declarations */

शून्य dataend (ध्रुव वर्ण *endit)
{
	/* short circuit any output */
	जइ (gentables) {

		जइ (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		जइ (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

शून्य dataflush (शून्य)
{
	प्रतिज्ञा (gentables);

	जइ (datapos > 0)
		outc ('\n');

	जइ (++dataline >= NUMDATALINES) {
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

शून्य flexerror (ध्रुव वर्ण *सन्देशः)
{
	fprintf (stderr, "%s: %s\n", program_name, सन्देशः);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

शून्य flexfatal (ध्रुव वर्ण *सन्देशः)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, सन्देशः);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

शून्य lerr (ध्रुव वर्ण *सन्देशः, ...)
{
	वर्ण    errmsg[MAXLINE];
	va_list args;

	va_start(args, सन्देशः);
	vsnprintf (errmsg, परिमाण(errmsg), सन्देशः, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

शून्य lerr_fatal (ध्रुव वर्ण *सन्देशः, ...)
{
	वर्ण    errmsg[MAXLINE];
	va_list args;
	va_start(args, सन्देशः);

	vsnprintf (errmsg, परिमाण(errmsg), सन्देशः, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
शून्य पङ्क्तिः_directive_out (FILE *output_file, वर्ण *path, पूर्णाङ्क linenum)
{
	वर्ण	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	वर्ण    directive[MAXLINE*2], filename[MAXLINE];
	वर्ण   *s1, *s2, *s3;

	जइ (!ctrl.gen_पङ्क्तिः_dirs)
		प्रत्यागम;

	s1 = (path != रिक्त) ? path : "M4_YY_OUTFILE_NAME";

	जइ ((path != रिक्त) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[परिमाण (filename) - 2];

	जाव (s2 < s3 && *s1) {
		जइ (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	जइ (path != रिक्त)
		snprintf (directive, परिमाण(directive), trace_fmt, linenum, filename);
	अण्णहा {
		snprintf (directive, परिमाण(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	जइ (output_file) {
		fputs (directive, output_file);
	}
	अण्णहा
		add_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
शून्य mark_defs1 (शून्य)
{
	defs1_offset = 0;
	action_array[action_index++] = '\0';
	action_offset = prolog_offset = action_index;
	action_array[action_index] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
शून्य mark_prolog (शून्य)
{
	action_array[action_index++] = '\0';
	action_offset = action_index;
	action_array[action_index] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
शून्य mk2data (पूर्णाङ्क मानम्)
{
	/* short circuit any output */
	जइ (!gentables)
		प्रत्यागम;

	जइ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	जइ (datapos == 0)
		/* Indent. */
		out ("    ");

	अण्णहा
	  outc (',');

	++datapos;

	out_dec ("%5d", मानम्);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
शून्य mkdata (पूर्णाङ्क मानम्)
{
	/* short circuit any output */
	जइ (!gentables)
		प्रत्यागम;

	जइ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	जइ (datapos == 0)
		/* Indent. */
		out ("    ");
	अण्णहा
		outc (',');
	++datapos;

	out_dec ("%5d", मानम्);
}


/* myctoi - return the integer represented by a string of digits */

पूर्णाङ्क myctoi (ध्रुव वर्ण *array)
{
	पूर्णाङ्क     val = 0;

	(शून्य) sscanf (array, "%d", &val);

	प्रत्यागम val;
}


/* myesc - return character corresponding to escape sequence */

unsigned वर्ण myesc (unsigned वर्ण array[])
{
	unsigned वर्ण    c, esc_char;

	विकल्प (array[1]) {
	पक्ष 'b':
		प्रत्यागम '\b';
	पक्ष 'f':
		प्रत्यागम '\f';
	पक्ष 'n':
		प्रत्यागम '\n';
	पक्ष 'r':
		प्रत्यागम '\r';
	पक्ष 't':
		प्रत्यागम '\t';
	पक्ष 'a':
		प्रत्यागम '\a';
	पक्ष 'v':
		प्रत्यागम '\v';
	पक्ष '0':
	पक्ष '1':
	पक्ष '2':
	पक्ष '3':
	पक्ष '4':
	पक्ष '5':
	पक्ष '6':
	पक्ष '7':
		{		/* \<octal> */
			पूर्णाङ्क     sptr = 1;

			जाव (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned वर्ण) strtoul (array + 1, रिक्त, 8);

			array[sptr] = c;

			प्रत्यागम esc_char;
		}

	पक्ष 'x':
		{		/* \x<hex> */
			पूर्णाङ्क     sptr = 2;

			जाव (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned वर्ण) strtoul (array + 2, रिक्त, 16);

			array[sptr] = c;

			प्रत्यागम esc_char;
		}

	स्वभाव:
		प्रत्यागम array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

शून्य out (ध्रुव वर्ण *str)
{
	fputs (str, stdout);
}

शून्य out_dec (ध्रुव वर्ण *fmt, पूर्णाङ्क n)
{
	fprintf (stdout, fmt, n);
}

शून्य out_dec2 (ध्रुव वर्ण *fmt, पूर्णाङ्क n1, पूर्णाङ्क n2)
{
	fprintf (stdout, fmt, n1, n2);
}

शून्य out_hex (ध्रुव वर्ण *fmt, unsigned पूर्णाङ्क x)
{
	fprintf (stdout, fmt, x);
}

शून्य out_str (ध्रुव वर्ण *fmt, ध्रुव वर्ण str[])
{
	fprintf (stdout,fmt, str);
}

शून्य out_str_dec (ध्रुव वर्ण *fmt, ध्रुव वर्ण str[], पूर्णाङ्क n)
{
	fprintf (stdout,fmt, str, n);
}

शून्य outc (पूर्णाङ्क c)
{
	fputc (c, stdout);
}

शून्य outn (ध्रुव वर्ण *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
शून्य out_m4_define (ध्रुव वर्ण* def, ध्रुव वर्ण* val)
{
    ध्रुव वर्ण * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

वर्ण   *readable_form (पूर्णाङ्क c)
{
	स्थिर वर्ण rform[20];

	जइ ((c >= 0 && c < 32) || c >= 127) {
		विकल्प (c) {
		पक्ष '\b':
			प्रत्यागम "\\b";
		पक्ष '\f':
			प्रत्यागम "\\f";
		पक्ष '\n':
			प्रत्यागम "\\n";
		पक्ष '\r':
			प्रत्यागम "\\r";
		पक्ष '\t':
			प्रत्यागम "\\t";
		पक्ष '\a':
			प्रत्यागम "\\a";
		पक्ष '\v':
			प्रत्यागम "\\v";
		स्वभाव:
			जइ(env.trace_hex)
				snprintf (rform, परिमाण(rform), "\\x%.2x", (unsigned पूर्णाङ्क) c);
			अण्णहा
				snprintf (rform, परिमाण(rform), "\\%.3o", (unsigned पूर्णाङ्क) c);
			प्रत्यागम rform;
		}
	}

	अण्णहा जइ (c == ' ')
		प्रत्यागम "' '";

	अण्णहा {
		rform[0] = (वर्ण) c;
		rform[1] = '\0';

		प्रत्यागम rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

शून्य   *reallocate_array (शून्य *array, पूर्णाङ्क size, size_t element_size)
{
	शून्य *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	जइ (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#अण्णहा
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# अण्णहा
	/* Do manual overflow detection */
	size_t अङ्कः_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? रिक्त :
		realloc(array, अङ्कः_bytes);
# endif
	जइ (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	प्रत्यागम new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

शून्य transition_struct_out (पूर्णाङ्क element_v, पूर्णाङ्क element_n)
{

	/* short circuit any output */
	जइ (!gentables)
		प्रत्यागम;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	जइ (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		जइ (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
शून्य   *yy_flex_xmalloc (पूर्णाङ्क size)
{
	शून्य   *result;

	result = malloc((size_t) size);
	जइ (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	प्रत्यागम result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
वर्ण   *chomp (वर्ण *str)
{
	वर्ण   *p = str;

	जइ (!str || !*str)	/* s is null or empty string */
		प्रत्यागम str;

	/* find end of string minus one */
	जाव (*p)
		++p;
	--p;

	/* eat newlines */
	जाव (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	प्रत्यागम str;
}

शून्य comment(ध्रुव वर्ण *txt)
{
	वर्ण buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	जइ (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	जइ (eol)
		outc ('\n');
}


