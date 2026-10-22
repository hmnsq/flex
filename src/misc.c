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
خالی جوڑو_action (ثابت حرف *new_متن)
{
	صحیح     len = (صحیح) لڑی_لمبائی (new_متن);

	جب (len + action_اشاریہ >= action_سائز - 10 /* slop */ ) {

		اگر (action_سائز > زیادہ_سے_زیادہ_عدد / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_سائز += action_سائز / 8;
		ورنہ
			action_سائز = action_سائز * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_سائز);
	}

	strcpy (&action_array[action_اشاریہ], new_متن);

	action_اشاریہ += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

خالی   *allocate_array (صحیح سائز, size_t element_سائز)
{
	واپس reallocate_array(تہی, سائز, element_سائز);
}


/* all_lower - true if a string is all lower-case */

صحیح all_زیریں (حرف *str)
{
	جب (*str) {
		اگر (!isascii ((غیرعلامتی حرف) * str) || !islower ((غیرعلامتی حرف) * str))
			واپس 0;
		++str;
	}

	واپس 1;
}


/* all_upper - true if a string is all upper-case */

صحیح all_بالائی (حرف *str)
{
	جب (*str) {
		اگر (!isascii ((غیرعلامتی حرف) * str) || !isupper ((غیرعلامتی حرف) * str))
			واپس 0;
		++str;
	}

	واپس 1;
}


/* intcmp - compares two integers for use by qsort. */

صحیح intcmp (ثابت خالی *a, ثابت خالی *b)
{
  واپس *(ثابت صحیح *) a - *(ثابت صحیح *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

خالی check_char (صحیح c)
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

غیرعلامتی حرف clower (صحیح c)
{
	واپس (غیرعلامتی حرف) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


حرف *xstrdup(ثابت حرف *s)
{
	حرف *s2;

	اگر ((s2 = strdup(s)) == تہی)
		flexfatal (_("memory allocation failure in xstrdup()"));

	واپس s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

صحیح cclcmp (ثابت خالی *a, ثابت خالی *b)
{
	اگر (!*(ثابت غیرعلامتی حرف *) a)
		واپس 1;
	ورنہ
		اگر (!*(ثابت غیرعلامتی حرف *) b)
			واپس - 1;
		ورنہ
			واپس *(ثابت غیرعلامتی حرف *) a - *(ثابت غیرعلامتی حرف *) b;
}


/* dataend - finish up a block of data declarations */

خالی dataend (ثابت حرف *endit)
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

خالی dataflush (خالی)
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

خالی flexerror (ثابت حرف *پیغام)
{
	fprintf (stderr, "%s: %s\n", پروگرام_name, پیغام);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

خالی flexfatal (ثابت حرف *پیغام)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 پروگرام_name, پیغام);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

خالی lerr (ثابت حرف *پیغام, ...)
{
	حرف    errmsg[MAXLINE];
	va_list دلائل;

	va_آغاز(دلائل, پیغام);
	vsnprintf (errmsg, حجم(errmsg), پیغام, دلائل);
	va_انتہا(دلائل);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

خالی lerr_fatal (ثابت حرف *پیغام, ...)
{
	حرف    errmsg[MAXLINE];
	va_list دلائل;
	va_آغاز(دلائل, پیغام);

	vsnprintf (errmsg, حجم(errmsg), پیغام, دلائل);
	va_انتہا(دلائل);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
خالی سطر_directive_برآمد (FILE *output_file, حرف *راستہ, صحیح linenum)
{
	حرف	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	حرف    directive[MAXLINE*2], filename[MAXLINE];
	حرف   *s1, *s2, *s3;

	اگر (!ctrl.gen_سطر_dirs)
		واپس;

	s1 = (راستہ != تہی) ? راستہ : "M4_YY_OUTFILE_NAME";

	اگر ((راستہ != تہی) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[حجم (filename) - 2];

	جب (s2 < s3 && *s1) {
		اگر (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	اگر (راستہ != تہی)
		snprintf (directive, حجم(directive), trace_fmt, linenum, filename);
	ورنہ {
		snprintf (directive, حجم(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	اگر (output_file) {
		fputs (directive, output_file);
	}
	ورنہ
		جوڑو_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
خالی mark_defs1 (خالی)
{
	defs1_انحراف = 0;
	action_array[action_اشاریہ++] = '\0';
	action_انحراف = prolog_انحراف = action_اشاریہ;
	action_array[action_اشاریہ] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
خالی mark_prolog (خالی)
{
	action_array[action_اشاریہ++] = '\0';
	action_انحراف = action_اشاریہ;
	action_array[action_اشاریہ] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
خالی mk2data (صحیح قدر)
{
	/* short circuit any output */
	اگر (!gentables)
		واپس;

	اگر (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	اگر (datapos == 0)
		/* Indent. */
		برآمد ("    ");

	ورنہ
	  outc (',');

	++datapos;

	برآمد_dec ("%5d", قدر);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
خالی mkdata (صحیح قدر)
{
	/* short circuit any output */
	اگر (!gentables)
		واپس;

	اگر (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	اگر (datapos == 0)
		/* Indent. */
		برآمد ("    ");
	ورنہ
		outc (',');
	++datapos;

	برآمد_dec ("%5d", قدر);
}


/* myctoi - return the integer represented by a string of digits */

صحیح myctoi (ثابت حرف *array)
{
	صحیح     val = 0;

	(خالی) لڑی_سے_پڑھو (array, "%d", &val);

	واپس val;
}


/* myesc - return character corresponding to escape sequence */

غیرعلامتی حرف myesc (غیرعلامتی حرف array[])
{
	غیرعلامتی حرف    c, esc_char;

	انتخاب (array[1]) {
	حالت 'b':
		واپس '\b';
	حالت 'f':
		واپس '\f';
	حالت 'n':
		واپس '\n';
	حالت 'r':
		واپس '\r';
	حالت 't':
		واپس '\t';
	حالت 'a':
		واپس '\a';
	حالت 'v':
		واپس '\v';
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

			جب (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (غیرعلامتی حرف) strtoul (array + 1, تہی, 8);

			array[sptr] = c;

			واپس esc_char;
		}

	حالت 'x':
		{		/* \x<hex> */
			صحیح     sptr = 2;

			جب (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (غیرعلامتی حرف) strtoul (array + 2, تہی, 16);

			array[sptr] = c;

			واپس esc_char;
		}

	طےشدہ:
		واپس array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

خالی برآمد (ثابت حرف *str)
{
	fputs (str, stdout);
}

خالی برآمد_dec (ثابت حرف *fmt, صحیح n)
{
	fprintf (stdout, fmt, n);
}

خالی برآمد_dec2 (ثابت حرف *fmt, صحیح n1, صحیح n2)
{
	fprintf (stdout, fmt, n1, n2);
}

خالی برآمد_hex (ثابت حرف *fmt, غیرعلامتی صحیح x)
{
	fprintf (stdout, fmt, x);
}

خالی برآمد_str (ثابت حرف *fmt, ثابت حرف str[])
{
	fprintf (stdout,fmt, str);
}

خالی برآمد_str_dec (ثابت حرف *fmt, ثابت حرف str[], صحیح n)
{
	fprintf (stdout,fmt, str, n);
}

خالی outc (صحیح c)
{
	fputc (c, stdout);
}

خالی outn (ثابت حرف *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
خالی برآمد_m4_define (ثابت حرف* def, ثابت حرف* val)
{
    ثابت حرف * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

حرف   *readable_form (صحیح c)
{
	ساکن حرف rform[20];

	اگر ((c >= 0 && c < 32) || c >= 127) {
		انتخاب (c) {
		حالت '\b':
			واپس "\\b";
		حالت '\f':
			واپس "\\f";
		حالت '\n':
			واپس "\\n";
		حالت '\r':
			واپس "\\r";
		حالت '\t':
			واپس "\\t";
		حالت '\a':
			واپس "\\a";
		حالت '\v':
			واپس "\\v";
		طےشدہ:
			اگر(env.trace_hex)
				snprintf (rform, حجم(rform), "\\x%.2x", (غیرعلامتی صحیح) c);
			ورنہ
				snprintf (rform, حجم(rform), "\\%.3o", (غیرعلامتی صحیح) c);
			واپس rform;
		}
	}

	ورنہ اگر (c == ' ')
		واپس "' '";

	ورنہ {
		rform[0] = (حرف) c;
		rform[1] = '\0';

		واپس rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

خالی   *reallocate_array (خالی *array, صحیح سائز, size_t element_سائز)
{
	خالی *new_array;
#اگر_تعریف_شدہ HAVE_REALLOCARR
	new_array = array;
	اگر (reallocarr(&new_array, (size_t) سائز, element_سائز)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#ورنہ
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) سائز, element_سائز);
# ورنہ
	/* Do manual overflow detection */
	size_t عدد_بائٹیں = (size_t) سائز * element_سائز;
	new_array = (سائز && سائز_MAX / (size_t) سائز < element_سائز) ? تہی :
		realloc(array, عدد_بائٹیں);
# endif
	اگر (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#اگر_ختم
	واپس new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

خالی transition_struct_برآمد (صحیح element_v, صحیح element_n)
{

	/* short circuit any output */
	اگر (!gentables)
		واپس;

	برآمد_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_لمبائی;

	اگر (datapos >= 79 - TRANS_STRUCT_PRINT_لمبائی) {
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
خالی   *yy_flex_xmalloc (صحیح سائز)
{
	خالی   *نتیجہ;

	نتیجہ = حافظہ_دو((size_t) سائز);
	اگر (!نتیجہ)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	واپس نتیجہ;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
حرف   *chomp (حرف *str)
{
	حرف   *p = str;

	اگر (!str || !*str)	/* s is null or empty string */
		واپس str;

	/* find end of string minus one */
	جب (*p)
		++p;
	--p;

	/* eat newlines */
	جب (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	واپس str;
}

خالی comment(ثابت حرف *txt)
{
	حرف buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[لڑی_لمبائی(buf)-1] == '\n';

	اگر (eol)
		buf[لڑی_لمبائی(buf)-1] = '\0';
	برآمد_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	اگر (eol)
		outc ('\n');
}


