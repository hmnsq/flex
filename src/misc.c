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
#અન્તર્ભાવ "flexdef.h"
#અન્તર્ભાવ "tables.h"

/* Append "new_text" to the running buffer. */
શૂન્ય add_action (અચલ અક્ષર *new_text)
{
	પૂર્ણાંક     len = (પૂર્ણાંક) strlen (new_text);

	જ્યારે (len + action_index >= action_size - 10 /* slop */ ) {

		જો (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		નહીંતર
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

શૂન્ય   *allocate_array (પૂર્ણાંક size, size_t element_size)
{
	પાછા reallocate_array(ખાલી, size, element_size);
}


/* all_lower - true if a string is all lower-case */

પૂર્ણાંક all_lower (અક્ષર *str)
{
	જ્યારે (*str) {
		જો (!isascii ((unsigned અક્ષર) * str) || !islower ((unsigned અક્ષર) * str))
			પાછા 0;
		++str;
	}

	પાછા 1;
}


/* all_upper - true if a string is all upper-case */

પૂર્ણાંક all_upper (અક્ષર *str)
{
	જ્યારે (*str) {
		જો (!isascii ((unsigned અક્ષર) * str) || !isupper ((unsigned અક્ષર) * str))
			પાછા 0;
		++str;
	}

	પાછા 1;
}


/* intcmp - compares two integers for use by qsort. */

પૂર્ણાંક intcmp (અચલ શૂન્ય *a, અચલ શૂન્ય *b)
{
  પાછા *(અચલ પૂર્ણાંક *) a - *(અચલ પૂર્ણાંક *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

શૂન્ય check_char (પૂર્ણાંક c)
{
	જો (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	જો (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned અક્ષર clower (પૂર્ણાંક c)
{
	પાછા (unsigned અક્ષર) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


અક્ષર *xstrdup(અચલ અક્ષર *s)
{
	અક્ષર *s2;

	જો ((s2 = strdup(s)) == ખાલી)
		flexfatal (_("memory allocation failure in xstrdup()"));

	પાછા s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

પૂર્ણાંક cclcmp (અચલ શૂન્ય *a, અચલ શૂન્ય *b)
{
	જો (!*(અચલ unsigned અક્ષર *) a)
		પાછા 1;
	નહીંતર
		જો (!*(અચલ unsigned અક્ષર *) b)
			પાછા - 1;
		નહીંતર
			પાછા *(અચલ unsigned અક્ષર *) a - *(અચલ unsigned અક્ષર *) b;
}


/* dataend - finish up a block of data declarations */

શૂન્ય dataend (અચલ અક્ષર *endit)
{
	/* short circuit any output */
	જો (gentables) {

		જો (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		જો (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

શૂન્ય dataflush (શૂન્ય)
{
	પ્રતિજ્ઞા (gentables);

	જો (datapos > 0)
		outc ('\n');

	જો (++dataline >= NUMDATALINES) {
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

શૂન્ય flexerror (અચલ અક્ષર *સંદેશ)
{
	fprintf (stderr, "%s: %s\n", program_name, સંદેશ);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

શૂન્ય flexfatal (અચલ અક્ષર *સંદેશ)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, સંદેશ);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

શૂન્ય lerr (અચલ અક્ષર *સંદેશ, ...)
{
	અક્ષર    errmsg[MAXLINE];
	va_list args;

	va_start(args, સંદેશ);
	vsnprintf (errmsg, કદ(errmsg), સંદેશ, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

શૂન્ય lerr_fatal (અચલ અક્ષર *સંદેશ, ...)
{
	અક્ષર    errmsg[MAXLINE];
	va_list args;
	va_start(args, સંદેશ);

	vsnprintf (errmsg, કદ(errmsg), સંદેશ, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
શૂન્ય લીટી_directive_out (FILE *output_file, અક્ષર *path, પૂર્ણાંક linenum)
{
	અક્ષર	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	અક્ષર    directive[MAXLINE*2], filename[MAXLINE];
	અક્ષર   *s1, *s2, *s3;

	જો (!ctrl.gen_લીટી_dirs)
		પાછા;

	s1 = (path != ખાલી) ? path : "M4_YY_OUTFILE_NAME";

	જો ((path != ખાલી) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[કદ (filename) - 2];

	જ્યારે (s2 < s3 && *s1) {
		જો (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	જો (path != ખાલી)
		snprintf (directive, કદ(directive), trace_fmt, linenum, filename);
	નહીંતર {
		snprintf (directive, કદ(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	જો (output_file) {
		fputs (directive, output_file);
	}
	નહીંતર
		add_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
શૂન્ય mark_defs1 (શૂન્ય)
{
	defs1_offset = 0;
	action_array[action_index++] = '\0';
	action_offset = prolog_offset = action_index;
	action_array[action_index] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
શૂન્ય mark_prolog (શૂન્ય)
{
	action_array[action_index++] = '\0';
	action_offset = action_index;
	action_array[action_index] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
શૂન્ય mk2data (પૂર્ણાંક કિંમત)
{
	/* short circuit any output */
	જો (!gentables)
		પાછા;

	જો (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	જો (datapos == 0)
		/* Indent. */
		out ("    ");

	નહીંતર
	  outc (',');

	++datapos;

	out_dec ("%5d", કિંમત);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
શૂન્ય mkdata (પૂર્ણાંક કિંમત)
{
	/* short circuit any output */
	જો (!gentables)
		પાછા;

	જો (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	જો (datapos == 0)
		/* Indent. */
		out ("    ");
	નહીંતર
		outc (',');
	++datapos;

	out_dec ("%5d", કિંમત);
}


/* myctoi - return the integer represented by a string of digits */

પૂર્ણાંક myctoi (અચલ અક્ષર *array)
{
	પૂર્ણાંક     val = 0;

	(શૂન્ય) sscanf (array, "%d", &val);

	પાછા val;
}


/* myesc - return character corresponding to escape sequence */

unsigned અક્ષર myesc (unsigned અક્ષર array[])
{
	unsigned અક્ષર    c, esc_char;

	પસંદગી (array[1]) {
	સ્થિતિ 'b':
		પાછા '\b';
	સ્થિતિ 'f':
		પાછા '\f';
	સ્થિતિ 'n':
		પાછા '\n';
	સ્થિતિ 'r':
		પાછા '\r';
	સ્થિતિ 't':
		પાછા '\t';
	સ્થિતિ 'a':
		પાછા '\a';
	સ્થિતિ 'v':
		પાછા '\v';
	સ્થિતિ '0':
	સ્થિતિ '1':
	સ્થિતિ '2':
	સ્થિતિ '3':
	સ્થિતિ '4':
	સ્થિતિ '5':
	સ્થિતિ '6':
	સ્થિતિ '7':
		{		/* \<octal> */
			પૂર્ણાંક     sptr = 1;

			જ્યારે (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned અક્ષર) strtoul (array + 1, ખાલી, 8);

			array[sptr] = c;

			પાછા esc_char;
		}

	સ્થિતિ 'x':
		{		/* \x<hex> */
			પૂર્ણાંક     sptr = 2;

			જ્યારે (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned અક્ષર) strtoul (array + 2, ખાલી, 16);

			array[sptr] = c;

			પાછા esc_char;
		}

	મૂળભૂત:
		પાછા array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

શૂન્ય out (અચલ અક્ષર *str)
{
	fputs (str, stdout);
}

શૂન્ય out_dec (અચલ અક્ષર *fmt, પૂર્ણાંક n)
{
	fprintf (stdout, fmt, n);
}

શૂન્ય out_dec2 (અચલ અક્ષર *fmt, પૂર્ણાંક n1, પૂર્ણાંક n2)
{
	fprintf (stdout, fmt, n1, n2);
}

શૂન્ય out_hex (અચલ અક્ષર *fmt, unsigned પૂર્ણાંક x)
{
	fprintf (stdout, fmt, x);
}

શૂન્ય out_str (અચલ અક્ષર *fmt, અચલ અક્ષર str[])
{
	fprintf (stdout,fmt, str);
}

શૂન્ય out_str_dec (અચલ અક્ષર *fmt, અચલ અક્ષર str[], પૂર્ણાંક n)
{
	fprintf (stdout,fmt, str, n);
}

શૂન્ય outc (પૂર્ણાંક c)
{
	fputc (c, stdout);
}

શૂન્ય outn (અચલ અક્ષર *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
શૂન્ય out_m4_define (અચલ અક્ષર* def, અચલ અક્ષર* val)
{
    અચલ અક્ષર * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

અક્ષર   *readable_form (પૂર્ણાંક c)
{
	સ્થિર અક્ષર rform[20];

	જો ((c >= 0 && c < 32) || c >= 127) {
		પસંદગી (c) {
		સ્થિતિ '\b':
			પાછા "\\b";
		સ્થિતિ '\f':
			પાછા "\\f";
		સ્થિતિ '\n':
			પાછા "\\n";
		સ્થિતિ '\r':
			પાછા "\\r";
		સ્થિતિ '\t':
			પાછા "\\t";
		સ્થિતિ '\a':
			પાછા "\\a";
		સ્થિતિ '\v':
			પાછા "\\v";
		મૂળભૂત:
			જો(env.trace_hex)
				snprintf (rform, કદ(rform), "\\x%.2x", (unsigned પૂર્ણાંક) c);
			નહીંતર
				snprintf (rform, કદ(rform), "\\%.3o", (unsigned પૂર્ણાંક) c);
			પાછા rform;
		}
	}

	નહીંતર જો (c == ' ')
		પાછા "' '";

	નહીંતર {
		rform[0] = (અક્ષર) c;
		rform[1] = '\0';

		પાછા rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

શૂન્ય   *reallocate_array (શૂન્ય *array, પૂર્ણાંક size, size_t element_size)
{
	શૂન્ય *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	જો (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#નહીંતર
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# નહીંતર
	/* Do manual overflow detection */
	size_t અંક_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? ખાલી :
		realloc(array, અંક_bytes);
# endif
	જો (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	પાછા new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

શૂન્ય transition_struct_out (પૂર્ણાંક element_v, પૂર્ણાંક element_n)
{

	/* short circuit any output */
	જો (!gentables)
		પાછા;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	જો (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		જો (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
શૂન્ય   *yy_flex_xmalloc (પૂર્ણાંક size)
{
	શૂન્ય   *result;

	result = malloc((size_t) size);
	જો (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	પાછા result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
અક્ષર   *chomp (અક્ષર *str)
{
	અક્ષર   *p = str;

	જો (!str || !*str)	/* s is null or empty string */
		પાછા str;

	/* find end of string minus one */
	જ્યારે (*p)
		++p;
	--p;

	/* eat newlines */
	જ્યારે (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	પાછા str;
}

શૂન્ય comment(અચલ અક્ષર *txt)
{
	અક્ષર buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	જો (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	જો (eol)
		outc ('\n');
}


