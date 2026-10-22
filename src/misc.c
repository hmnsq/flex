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
#شامل "flexdef.h"
#شامل "tables.h"

/* Append "new_text" to the running buffer. */
تهی add_action (ثابت نویسه *new_text)
{
	صحیح     len = (صحیح) strlen (new_text);

	وقتی (len + action_index >= action_size - 10 /* slop */ ) {

		اگر (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		وگرنه
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

تهی   *allocate_array (صحیح size, size_t element_size)
{
	بازگشت reallocate_array(پوچ, size, element_size);
}


/* all_lower - true if a string is all lower-case */

صحیح all_lower (نویسه *str)
{
	وقتی (*str) {
		اگر (!isascii ((unsigned نویسه) * str) || !islower ((unsigned نویسه) * str))
			بازگشت 0;
		++str;
	}

	بازگشت 1;
}


/* all_upper - true if a string is all upper-case */

صحیح all_upper (نویسه *str)
{
	وقتی (*str) {
		اگر (!isascii ((unsigned نویسه) * str) || !isupper ((unsigned نویسه) * str))
			بازگشت 0;
		++str;
	}

	بازگشت 1;
}


/* intcmp - compares two integers for use by qsort. */

صحیح intcmp (ثابت تهی *a, ثابت تهی *b)
{
  بازگشت *(ثابت صحیح *) a - *(ثابت صحیح *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

تهی check_char (صحیح c)
{
	اگر (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	اگر (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned نویسه clower (صحیح c)
{
	بازگشت (unsigned نویسه) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


نویسه *xstrdup(ثابت نویسه *s)
{
	نویسه *s2;

	اگر ((s2 = strdup(s)) == پوچ)
		flexfatal (_("memory allocation failure in xstrdup()"));

	بازگشت s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

صحیح cclcmp (ثابت تهی *a, ثابت تهی *b)
{
	اگر (!*(ثابت unsigned نویسه *) a)
		بازگشت 1;
	وگرنه
		اگر (!*(ثابت unsigned نویسه *) b)
			بازگشت - 1;
		وگرنه
			بازگشت *(ثابت unsigned نویسه *) a - *(ثابت unsigned نویسه *) b;
}


/* dataend - finish up a block of data declarations */

تهی dataend (ثابت نویسه *endit)
{
	/* short circuit any output */
	اگر (gentables) {

		اگر (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		اگر (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

تهی dataflush (تهی)
{
	أكد (gentables);

	اگر (datapos > 0)
		outc ('\n');

	اگر (++dataline >= NUMDATALINES) {
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

تهی flexerror (ثابت نویسه *پیام)
{
	fprintf (stderr, "%s: %s\n", program_name, پیام);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

تهی flexfatal (ثابت نویسه *پیام)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, پیام);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

تهی lerr (ثابت نویسه *پیام, ...)
{
	نویسه    errmsg[MAXLINE];
	va_list args;

	va_start(args, پیام);
	vsnprintf (errmsg, اندازه(errmsg), پیام, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

تهی lerr_fatal (ثابت نویسه *پیام, ...)
{
	نویسه    errmsg[MAXLINE];
	va_list args;
	va_start(args, پیام);

	vsnprintf (errmsg, اندازه(errmsg), پیام, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
تهی سطر_directive_out (FILE *output_file, نویسه *path, صحیح linenum)
{
	نویسه	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	نویسه    directive[MAXLINE*2], filename[MAXLINE];
	نویسه   *s1, *s2, *s3;

	اگر (!ctrl.gen_سطر_dirs)
		بازگشت;

	s1 = (path != پوچ) ? path : "M4_YY_OUTFILE_NAME";

	اگر ((path != پوچ) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[اندازه (filename) - 2];

	وقتی (s2 < s3 && *s1) {
		اگر (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	اگر (path != پوچ)
		snprintf (directive, اندازه(directive), trace_fmt, linenum, filename);
	وگرنه {
		snprintf (directive, اندازه(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	اگر (output_file) {
		fputs (directive, output_file);
	}
	وگرنه
		add_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
تهی mark_defs1 (تهی)
{
	defs1_offset = 0;
	action_array[action_index++] = '\0';
	action_offset = prolog_offset = action_index;
	action_array[action_index] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
تهی mark_prolog (تهی)
{
	action_array[action_index++] = '\0';
	action_offset = action_index;
	action_array[action_index] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
تهی mk2data (صحیح مقدار)
{
	/* short circuit any output */
	اگر (!gentables)
		بازگشت;

	اگر (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	اگر (datapos == 0)
		/* Indent. */
		out ("    ");

	وگرنه
	  outc (',');

	++datapos;

	out_dec ("%5d", مقدار);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
تهی mkdata (صحیح مقدار)
{
	/* short circuit any output */
	اگر (!gentables)
		بازگشت;

	اگر (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	اگر (datapos == 0)
		/* Indent. */
		out ("    ");
	وگرنه
		outc (',');
	++datapos;

	out_dec ("%5d", مقدار);
}


/* myctoi - return the integer represented by a string of digits */

صحیح myctoi (ثابت نویسه *array)
{
	صحیح     val = 0;

	(تهی) sscanf (array, "%d", &val);

	بازگشت val;
}


/* myesc - return character corresponding to escape sequence */

unsigned نویسه myesc (unsigned نویسه array[])
{
	unsigned نویسه    c, esc_char;

	انتخاب (array[1]) {
	حالت 'b':
		بازگشت '\b';
	حالت 'f':
		بازگشت '\f';
	حالت 'n':
		بازگشت '\n';
	حالت 'r':
		بازگشت '\r';
	حالت 't':
		بازگشت '\t';
	حالت 'a':
		بازگشت '\a';
	حالت 'v':
		بازگشت '\v';
	حالت '0':
	حالت '1':
	حالت '2':
	حالت '3':
	حالت '4':
	حالت '5':
	حالت '6':
	حالت '7':
		{		/* \<octal> */
			صحیح     sptr = 1;

			وقتی (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned نویسه) strtoul (array + 1, پوچ, 8);

			array[sptr] = c;

			بازگشت esc_char;
		}

	حالت 'x':
		{		/* \x<hex> */
			صحیح     sptr = 2;

			وقتی (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned نویسه) strtoul (array + 2, پوچ, 16);

			array[sptr] = c;

			بازگشت esc_char;
		}

	پیشفرض:
		بازگشت array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

تهی out (ثابت نویسه *str)
{
	fputs (str, stdout);
}

تهی out_dec (ثابت نویسه *fmt, صحیح n)
{
	fprintf (stdout, fmt, n);
}

تهی out_dec2 (ثابت نویسه *fmt, صحیح n1, صحیح n2)
{
	fprintf (stdout, fmt, n1, n2);
}

تهی out_hex (ثابت نویسه *fmt, unsigned صحیح x)
{
	fprintf (stdout, fmt, x);
}

تهی out_str (ثابت نویسه *fmt, ثابت نویسه str[])
{
	fprintf (stdout,fmt, str);
}

تهی out_str_dec (ثابت نویسه *fmt, ثابت نویسه str[], صحیح n)
{
	fprintf (stdout,fmt, str, n);
}

تهی outc (صحیح c)
{
	fputc (c, stdout);
}

تهی outn (ثابت نویسه *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
تهی out_m4_define (ثابت نویسه* def, ثابت نویسه* val)
{
    ثابت نویسه * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

نویسه   *readable_form (صحیح c)
{
	ایستا نویسه rform[20];

	اگر ((c >= 0 && c < 32) || c >= 127) {
		انتخاب (c) {
		حالت '\b':
			بازگشت "\\b";
		حالت '\f':
			بازگشت "\\f";
		حالت '\n':
			بازگشت "\\n";
		حالت '\r':
			بازگشت "\\r";
		حالت '\t':
			بازگشت "\\t";
		حالت '\a':
			بازگشت "\\a";
		حالت '\v':
			بازگشت "\\v";
		پیشفرض:
			اگر(env.trace_hex)
				snprintf (rform, اندازه(rform), "\\x%.2x", (unsigned صحیح) c);
			وگرنه
				snprintf (rform, اندازه(rform), "\\%.3o", (unsigned صحیح) c);
			بازگشت rform;
		}
	}

	وگرنه اگر (c == ' ')
		بازگشت "' '";

	وگرنه {
		rform[0] = (نویسه) c;
		rform[1] = '\0';

		بازگشت rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

تهی   *reallocate_array (تهی *array, صحیح size, size_t element_size)
{
	تهی *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	اگر (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#وگرنه
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# وگرنه
	/* Do manual overflow detection */
	size_t رقم_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? پوچ :
		realloc(array, رقم_bytes);
# endif
	اگر (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	بازگشت new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

تهی transition_struct_out (صحیح element_v, صحیح element_n)
{

	/* short circuit any output */
	اگر (!gentables)
		بازگشت;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	اگر (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		اگر (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
تهی   *yy_flex_xmalloc (صحیح size)
{
	تهی   *result;

	result = malloc((size_t) size);
	اگر (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	بازگشت result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
نویسه   *chomp (نویسه *str)
{
	نویسه   *p = str;

	اگر (!str || !*str)	/* s is null or empty string */
		بازگشت str;

	/* find end of string minus one */
	وقتی (*p)
		++p;
	--p;

	/* eat newlines */
	وقتی (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	بازگشت str;
}

تهی comment(ثابت نویسه *txt)
{
	نویسه buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	اگر (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	اگر (eol)
		outc ('\n');
}


