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
#അന്തര്ഭാവ "flexdef.h"
#അന്തര്ഭാവ "tables.h"

/* Append "new_text" to the running buffer. */
ശൂന്യം add_action (സ്ഥിരം അക്ഷരം *new_text)
{
	പൂർണ്ണസംഖ്യ     len = (പൂർണ്ണസംഖ്യ) strlen (new_text);

	ആകുമ്പോൾ (len + action_index >= action_size - 10 /* slop */ ) {

		എങ്കിൽ (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		അല്ലെങ്കിൽ
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

ശൂന്യം   *allocate_array (പൂർണ്ണസംഖ്യ size, size_t element_size)
{
	തിരികെ reallocate_array(ശൂന്യ, size, element_size);
}


/* all_lower - true if a string is all lower-case */

പൂർണ്ണസംഖ്യ all_lower (അക്ഷരം *str)
{
	ആകുമ്പോൾ (*str) {
		എങ്കിൽ (!isascii ((unsigned അക്ഷരം) * str) || !islower ((unsigned അക്ഷരം) * str))
			തിരികെ 0;
		++str;
	}

	തിരികെ 1;
}


/* all_upper - true if a string is all upper-case */

പൂർണ്ണസംഖ്യ all_upper (അക്ഷരം *str)
{
	ആകുമ്പോൾ (*str) {
		എങ്കിൽ (!isascii ((unsigned അക്ഷരം) * str) || !isupper ((unsigned അക്ഷരം) * str))
			തിരികെ 0;
		++str;
	}

	തിരികെ 1;
}


/* intcmp - compares two integers for use by qsort. */

പൂർണ്ണസംഖ്യ intcmp (സ്ഥിരം ശൂന്യം *a, സ്ഥിരം ശൂന്യം *b)
{
  തിരികെ *(സ്ഥിരം പൂർണ്ണസംഖ്യ *) a - *(സ്ഥിരം പൂർണ്ണസംഖ്യ *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

ശൂന്യം check_char (പൂർണ്ണസംഖ്യ c)
{
	എങ്കിൽ (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	എങ്കിൽ (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned അക്ഷരം clower (പൂർണ്ണസംഖ്യ c)
{
	തിരികെ (unsigned അക്ഷരം) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


അക്ഷരം *xstrdup(സ്ഥിരം അക്ഷരം *s)
{
	അക്ഷരം *s2;

	എങ്കിൽ ((s2 = strdup(s)) == ശൂന്യ)
		flexfatal (_("memory allocation failure in xstrdup()"));

	തിരികെ s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

പൂർണ്ണസംഖ്യ cclcmp (സ്ഥിരം ശൂന്യം *a, സ്ഥിരം ശൂന്യം *b)
{
	എങ്കിൽ (!*(സ്ഥിരം unsigned അക്ഷരം *) a)
		തിരികെ 1;
	അല്ലെങ്കിൽ
		എങ്കിൽ (!*(സ്ഥിരം unsigned അക്ഷരം *) b)
			തിരികെ - 1;
		അല്ലെങ്കിൽ
			തിരികെ *(സ്ഥിരം unsigned അക്ഷരം *) a - *(സ്ഥിരം unsigned അക്ഷരം *) b;
}


/* dataend - finish up a block of data declarations */

ശൂന്യം dataend (സ്ഥിരം അക്ഷരം *endit)
{
	/* short circuit any output */
	എങ്കിൽ (gentables) {

		എങ്കിൽ (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		എങ്കിൽ (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

ശൂന്യം dataflush (ശൂന്യം)
{
	പ്രതിജ്ഞാ (gentables);

	എങ്കിൽ (datapos > 0)
		outc ('\n');

	എങ്കിൽ (++dataline >= NUMDATALINES) {
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

ശൂന്യം flexerror (സ്ഥിരം അക്ഷരം *സന്ദേശം)
{
	fprintf (stderr, "%s: %s\n", program_name, സന്ദേശം);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

ശൂന്യം flexfatal (സ്ഥിരം അക്ഷരം *സന്ദേശം)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, സന്ദേശം);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

ശൂന്യം lerr (സ്ഥിരം അക്ഷരം *സന്ദേശം, ...)
{
	അക്ഷരം    errmsg[MAXLINE];
	va_list args;

	va_start(args, സന്ദേശം);
	vsnprintf (errmsg, വലുപ്പം(errmsg), സന്ദേശം, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

ശൂന്യം lerr_fatal (സ്ഥിരം അക്ഷരം *സന്ദേശം, ...)
{
	അക്ഷരം    errmsg[MAXLINE];
	va_list args;
	va_start(args, സന്ദേശം);

	vsnprintf (errmsg, വലുപ്പം(errmsg), സന്ദേശം, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
ശൂന്യം വരി_directive_out (FILE *output_file, അക്ഷരം *path, പൂർണ്ണസംഖ്യ linenum)
{
	അക്ഷരം	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	അക്ഷരം    directive[MAXLINE*2], filename[MAXLINE];
	അക്ഷരം   *s1, *s2, *s3;

	എങ്കിൽ (!ctrl.gen_വരി_dirs)
		തിരികെ;

	s1 = (path != ശൂന്യ) ? path : "M4_YY_OUTFILE_NAME";

	എങ്കിൽ ((path != ശൂന്യ) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[വലുപ്പം (filename) - 2];

	ആകുമ്പോൾ (s2 < s3 && *s1) {
		എങ്കിൽ (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	എങ്കിൽ (path != ശൂന്യ)
		snprintf (directive, വലുപ്പം(directive), trace_fmt, linenum, filename);
	അല്ലെങ്കിൽ {
		snprintf (directive, വലുപ്പം(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	എങ്കിൽ (output_file) {
		fputs (directive, output_file);
	}
	അല്ലെങ്കിൽ
		add_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
ശൂന്യം mark_defs1 (ശൂന്യം)
{
	defs1_offset = 0;
	action_array[action_index++] = '\0';
	action_offset = prolog_offset = action_index;
	action_array[action_index] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
ശൂന്യം mark_prolog (ശൂന്യം)
{
	action_array[action_index++] = '\0';
	action_offset = action_index;
	action_array[action_index] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
ശൂന്യം mk2data (പൂർണ്ണസംഖ്യ മൂല്യം)
{
	/* short circuit any output */
	എങ്കിൽ (!gentables)
		തിരികെ;

	എങ്കിൽ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	എങ്കിൽ (datapos == 0)
		/* Indent. */
		out ("    ");

	അല്ലെങ്കിൽ
	  outc (',');

	++datapos;

	out_dec ("%5d", മൂല്യം);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
ശൂന്യം mkdata (പൂർണ്ണസംഖ്യ മൂല്യം)
{
	/* short circuit any output */
	എങ്കിൽ (!gentables)
		തിരികെ;

	എങ്കിൽ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	എങ്കിൽ (datapos == 0)
		/* Indent. */
		out ("    ");
	അല്ലെങ്കിൽ
		outc (',');
	++datapos;

	out_dec ("%5d", മൂല്യം);
}


/* myctoi - return the integer represented by a string of digits */

പൂർണ്ണസംഖ്യ myctoi (സ്ഥിരം അക്ഷരം *array)
{
	പൂർണ്ണസംഖ്യ     val = 0;

	(ശൂന്യം) sscanf (array, "%d", &val);

	തിരികെ val;
}


/* myesc - return character corresponding to escape sequence */

unsigned അക്ഷരം myesc (unsigned അക്ഷരം array[])
{
	unsigned അക്ഷരം    c, esc_char;

	തിരഞ്ഞെടുപ്പ് (array[1]) {
	അവസ്ഥ 'b':
		തിരികെ '\b';
	അവസ്ഥ 'f':
		തിരികെ '\f';
	അവസ്ഥ 'n':
		തിരികെ '\n';
	അവസ്ഥ 'r':
		തിരികെ '\r';
	അവസ്ഥ 't':
		തിരികെ '\t';
	അവസ്ഥ 'a':
		തിരികെ '\a';
	അവസ്ഥ 'v':
		തിരികെ '\v';
	അവസ്ഥ '0':
	അവസ്ഥ '1':
	അവസ്ഥ '2':
	അവസ്ഥ '3':
	അവസ്ഥ '4':
	അവസ്ഥ '5':
	അവസ്ഥ '6':
	അവസ്ഥ '7':
		{		/* \<octal> */
			പൂർണ്ണസംഖ്യ     sptr = 1;

			ആകുമ്പോൾ (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned അക്ഷരം) strtoul (array + 1, ശൂന്യ, 8);

			array[sptr] = c;

			തിരികെ esc_char;
		}

	അവസ്ഥ 'x':
		{		/* \x<hex> */
			പൂർണ്ണസംഖ്യ     sptr = 2;

			ആകുമ്പോൾ (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned അക്ഷരം) strtoul (array + 2, ശൂന്യ, 16);

			array[sptr] = c;

			തിരികെ esc_char;
		}

	സ്ഥിരസ്ഥിതി:
		തിരികെ array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

ശൂന്യം out (സ്ഥിരം അക്ഷരം *str)
{
	fputs (str, stdout);
}

ശൂന്യം out_dec (സ്ഥിരം അക്ഷരം *fmt, പൂർണ്ണസംഖ്യ n)
{
	fprintf (stdout, fmt, n);
}

ശൂന്യം out_dec2 (സ്ഥിരം അക്ഷരം *fmt, പൂർണ്ണസംഖ്യ n1, പൂർണ്ണസംഖ്യ n2)
{
	fprintf (stdout, fmt, n1, n2);
}

ശൂന്യം out_hex (സ്ഥിരം അക്ഷരം *fmt, unsigned പൂർണ്ണസംഖ്യ x)
{
	fprintf (stdout, fmt, x);
}

ശൂന്യം out_str (സ്ഥിരം അക്ഷരം *fmt, സ്ഥിരം അക്ഷരം str[])
{
	fprintf (stdout,fmt, str);
}

ശൂന്യം out_str_dec (സ്ഥിരം അക്ഷരം *fmt, സ്ഥിരം അക്ഷരം str[], പൂർണ്ണസംഖ്യ n)
{
	fprintf (stdout,fmt, str, n);
}

ശൂന്യം outc (പൂർണ്ണസംഖ്യ c)
{
	fputc (c, stdout);
}

ശൂന്യം outn (സ്ഥിരം അക്ഷരം *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
ശൂന്യം out_m4_define (സ്ഥിരം അക്ഷരം* def, സ്ഥിരം അക്ഷരം* val)
{
    സ്ഥിരം അക്ഷരം * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

അക്ഷരം   *readable_form (പൂർണ്ണസംഖ്യ c)
{
	സ്ഥിതം അക്ഷരം rform[20];

	എങ്കിൽ ((c >= 0 && c < 32) || c >= 127) {
		തിരഞ്ഞെടുപ്പ് (c) {
		അവസ്ഥ '\b':
			തിരികെ "\\b";
		അവസ്ഥ '\f':
			തിരികെ "\\f";
		അവസ്ഥ '\n':
			തിരികെ "\\n";
		അവസ്ഥ '\r':
			തിരികെ "\\r";
		അവസ്ഥ '\t':
			തിരികെ "\\t";
		അവസ്ഥ '\a':
			തിരികെ "\\a";
		അവസ്ഥ '\v':
			തിരികെ "\\v";
		സ്ഥിരസ്ഥിതി:
			എങ്കിൽ(env.trace_hex)
				snprintf (rform, വലുപ്പം(rform), "\\x%.2x", (unsigned പൂർണ്ണസംഖ്യ) c);
			അല്ലെങ്കിൽ
				snprintf (rform, വലുപ്പം(rform), "\\%.3o", (unsigned പൂർണ്ണസംഖ്യ) c);
			തിരികെ rform;
		}
	}

	അല്ലെങ്കിൽ എങ്കിൽ (c == ' ')
		തിരികെ "' '";

	അല്ലെങ്കിൽ {
		rform[0] = (അക്ഷരം) c;
		rform[1] = '\0';

		തിരികെ rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

ശൂന്യം   *reallocate_array (ശൂന്യം *array, പൂർണ്ണസംഖ്യ size, size_t element_size)
{
	ശൂന്യം *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	എങ്കിൽ (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#അല്ലെങ്കിൽ
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# അല്ലെങ്കിൽ
	/* Do manual overflow detection */
	size_t അക്കം_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? ശൂന്യ :
		realloc(array, അക്കം_bytes);
# endif
	എങ്കിൽ (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	തിരികെ new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

ശൂന്യം transition_struct_out (പൂർണ്ണസംഖ്യ element_v, പൂർണ്ണസംഖ്യ element_n)
{

	/* short circuit any output */
	എങ്കിൽ (!gentables)
		തിരികെ;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	എങ്കിൽ (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		എങ്കിൽ (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
ശൂന്യം   *yy_flex_xmalloc (പൂർണ്ണസംഖ്യ size)
{
	ശൂന്യം   *result;

	result = malloc((size_t) size);
	എങ്കിൽ (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	തിരികെ result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
അക്ഷരം   *chomp (അക്ഷരം *str)
{
	അക്ഷരം   *p = str;

	എങ്കിൽ (!str || !*str)	/* s is null or empty string */
		തിരികെ str;

	/* find end of string minus one */
	ആകുമ്പോൾ (*p)
		++p;
	--p;

	/* eat newlines */
	ആകുമ്പോൾ (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	തിരികെ str;
}

ശൂന്യം comment(സ്ഥിരം അക്ഷരം *txt)
{
	അക്ഷരം buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	എങ്കിൽ (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	എങ്കിൽ (eol)
		outc ('\n');
}


