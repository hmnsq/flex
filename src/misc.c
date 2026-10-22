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
#ضمن "flexdef.h"
#ضمن "tables.h"

/* Append "new_text" to the running buffer. */
فراغ جوڑو_action (ثابت حرف *new_متن)
{
	صحيح     len = (صحيح) لڑی_لمبائی (new_متن);

	طالما (len + action_اشاریہ >= action_ناپ - 10 /* slop */ ) {

		إذا (action_ناپ > ودھ_توں_ودھ_عدد / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_ناپ += action_ناپ / 8;
		وإلا
			action_ناپ = action_ناپ * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_ناپ);
	}

	strcpy (&action_array[action_اشاریہ], new_متن);

	action_اشاریہ += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

فراغ   *allocate_array (صحيح ناپ, size_t element_ناپ)
{
	أرجع reallocate_array(عدم, ناپ, element_ناپ);
}


/* all_lower - true if a string is all lower-case */

صحيح all_ہیٹھلا (حرف *str)
{
	طالما (*str) {
		إذا (!isascii ((بنانشانی حرف) * str) || !islower ((بنانشانی حرف) * str))
			أرجع 0;
		++str;
	}

	أرجع 1;
}


/* all_upper - true if a string is all upper-case */

صحيح all_اتلا (حرف *str)
{
	طالما (*str) {
		إذا (!isascii ((بنانشانی حرف) * str) || !isupper ((بنانشانی حرف) * str))
			أرجع 0;
		++str;
	}

	أرجع 1;
}


/* intcmp - compares two integers for use by qsort. */

صحيح intcmp (ثابت فراغ *a, ثابت فراغ *b)
{
  أرجع *(ثابت صحيح *) a - *(ثابت صحيح *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

فراغ check_char (صحيح c)
{
	إذا (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	إذا (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

بنانشانی حرف clower (صحيح c)
{
	أرجع (بنانشانی حرف) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


حرف *xstrdup(ثابت حرف *s)
{
	حرف *s2;

	إذا ((s2 = strdup(s)) == عدم)
		flexfatal (_("memory allocation failure in xstrdup()"));

	أرجع s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

صحيح cclcmp (ثابت فراغ *a, ثابت فراغ *b)
{
	إذا (!*(ثابت بنانشانی حرف *) a)
		أرجع 1;
	وإلا
		إذا (!*(ثابت بنانشانی حرف *) b)
			أرجع - 1;
		وإلا
			أرجع *(ثابت بنانشانی حرف *) a - *(ثابت بنانشانی حرف *) b;
}


/* dataend - finish up a block of data declarations */

فراغ dataend (ثابت حرف *endit)
{
	/* short circuit any output */
	إذا (gentables) {

		إذا (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		إذا (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

فراغ dataflush (فراغ)
{
	أكد (gentables);

	إذا (datapos > 0)
		outc ('\n');

	إذا (++dataline >= NUMDATALINES) {
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

فراغ flexerror (ثابت حرف *پیغام)
{
	fprintf (stderr, "%s: %s\n", پروگرام_name, پیغام);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

فراغ flexfatal (ثابت حرف *پیغام)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 پروگرام_name, پیغام);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

فراغ lerr (ثابت حرف *پیغام, ...)
{
	حرف    errmsg[MAXLINE];
	va_list دلیلاں;

	va_شروع(دلیلاں, پیغام);
	vsnprintf (errmsg, حجم(errmsg), پیغام, دلیلاں);
	va_سرا(دلیلاں);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

فراغ lerr_fatal (ثابت حرف *پیغام, ...)
{
	حرف    errmsg[MAXLINE];
	va_list دلیلاں;
	va_شروع(دلیلاں, پیغام);

	vsnprintf (errmsg, حجم(errmsg), پیغام, دلیلاں);
	va_سرا(دلیلاں);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
فراغ سطر_directive_باہرلا (FILE *output_file, حرف *رستہ, صحيح linenum)
{
	حرف	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	حرف    directive[MAXLINE*2], filename[MAXLINE];
	حرف   *s1, *s2, *s3;

	إذا (!ctrl.gen_سطر_dirs)
		أرجع;

	s1 = (رستہ != عدم) ? رستہ : "M4_YY_OUTFILE_NAME";

	إذا ((رستہ != عدم) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[حجم (filename) - 2];

	طالما (s2 < s3 && *s1) {
		إذا (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	إذا (رستہ != عدم)
		snprintf (directive, حجم(directive), trace_fmt, linenum, filename);
	وإلا {
		snprintf (directive, حجم(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	إذا (output_file) {
		fputs (directive, output_file);
	}
	وإلا
		جوڑو_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
فراغ mark_defs1 (فراغ)
{
	defs1_وتھ = 0;
	action_array[action_اشاریہ++] = '\0';
	action_وتھ = prolog_وتھ = action_اشاریہ;
	action_array[action_اشاریہ] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
فراغ mark_prolog (فراغ)
{
	action_array[action_اشاریہ++] = '\0';
	action_وتھ = action_اشاریہ;
	action_array[action_اشاریہ] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
فراغ mk2data (صحيح قدر)
{
	/* short circuit any output */
	إذا (!gentables)
		أرجع;

	إذا (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	إذا (datapos == 0)
		/* Indent. */
		باہرلا ("    ");

	وإلا
	  outc (',');

	++datapos;

	باہرلا_dec ("%5d", قدر);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
فراغ mkdata (صحيح قدر)
{
	/* short circuit any output */
	إذا (!gentables)
		أرجع;

	إذا (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	إذا (datapos == 0)
		/* Indent. */
		باہرلا ("    ");
	وإلا
		outc (',');
	++datapos;

	باہرلا_dec ("%5d", قدر);
}


/* myctoi - return the integer represented by a string of digits */

صحيح myctoi (ثابت حرف *array)
{
	صحيح     val = 0;

	(فراغ) لڑی_توں_پڑھو (array, "%d", &val);

	أرجع val;
}


/* myesc - return character corresponding to escape sequence */

بنانشانی حرف myesc (بنانشانی حرف array[])
{
	بنانشانی حرف    c, esc_char;

	بدل (array[1]) {
	حالة 'b':
		أرجع '\b';
	حالة 'f':
		أرجع '\f';
	حالة 'n':
		أرجع '\n';
	حالة 'r':
		أرجع '\r';
	حالة 't':
		أرجع '\t';
	حالة 'a':
		أرجع '\a';
	حالة 'v':
		أرجع '\v';
	حالة '0':
	حالة '1':
	حالة '2':
	حالة '3':
	حالة '4':
	حالة '5':
	حالة '6':
	حالة '7':
		{		/* \<octal> */
			صحيح     sptr = 1;

			طالما (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (بنانشانی حرف) strtoul (array + 1, عدم, 8);

			array[sptr] = c;

			أرجع esc_char;
		}

	حالة 'x':
		{		/* \x<hex> */
			صحيح     sptr = 2;

			طالما (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (بنانشانی حرف) strtoul (array + 2, عدم, 16);

			array[sptr] = c;

			أرجع esc_char;
		}

	افتراضي:
		أرجع array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

فراغ باہرلا (ثابت حرف *str)
{
	fputs (str, stdout);
}

فراغ باہرلا_dec (ثابت حرف *fmt, صحيح n)
{
	fprintf (stdout, fmt, n);
}

فراغ باہرلا_dec2 (ثابت حرف *fmt, صحيح n1, صحيح n2)
{
	fprintf (stdout, fmt, n1, n2);
}

فراغ باہرلا_hex (ثابت حرف *fmt, بنانشانی صحيح x)
{
	fprintf (stdout, fmt, x);
}

فراغ باہرلا_str (ثابت حرف *fmt, ثابت حرف str[])
{
	fprintf (stdout,fmt, str);
}

فراغ باہرلا_str_dec (ثابت حرف *fmt, ثابت حرف str[], صحيح n)
{
	fprintf (stdout,fmt, str, n);
}

فراغ outc (صحيح c)
{
	fputc (c, stdout);
}

فراغ outn (ثابت حرف *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
فراغ باہرلا_m4_define (ثابت حرف* def, ثابت حرف* val)
{
    ثابت حرف * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

حرف   *readable_form (صحيح c)
{
	ساكن حرف rform[20];

	إذا ((c >= 0 && c < 32) || c >= 127) {
		بدل (c) {
		حالة '\b':
			أرجع "\\b";
		حالة '\f':
			أرجع "\\f";
		حالة '\n':
			أرجع "\\n";
		حالة '\r':
			أرجع "\\r";
		حالة '\t':
			أرجع "\\t";
		حالة '\a':
			أرجع "\\a";
		حالة '\v':
			أرجع "\\v";
		افتراضي:
			إذا(env.trace_hex)
				snprintf (rform, حجم(rform), "\\x%.2x", (بنانشانی صحيح) c);
			وإلا
				snprintf (rform, حجم(rform), "\\%.3o", (بنانشانی صحيح) c);
			أرجع rform;
		}
	}

	وإلا إذا (c == ' ')
		أرجع "' '";

	وإلا {
		rform[0] = (حرف) c;
		rform[1] = '\0';

		أرجع rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

فراغ   *reallocate_array (فراغ *array, صحيح ناپ, size_t element_ناپ)
{
	فراغ *new_array;
#جے_تعریف_شدہ HAVE_REALLOCARR
	new_array = array;
	إذا (reallocarr(&new_array, (size_t) ناپ, element_ناپ)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#وإلا
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) ناپ, element_ناپ);
# وإلا
	/* Do manual overflow detection */
	size_t عدد_بائٹاں = (size_t) ناپ * element_ناپ;
	new_array = (ناپ && ناپ_MAX / (size_t) ناپ < element_ناپ) ? عدم :
		realloc(array, عدد_بائٹاں);
# endif
	إذا (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#جے_انت
	أرجع new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

فراغ transition_struct_باہرلا (صحيح element_v, صحيح element_n)
{

	/* short circuit any output */
	إذا (!gentables)
		أرجع;

	باہرلا_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_لمائی;

	إذا (datapos >= 79 - TRANS_STRUCT_PRINT_لمائی) {
		outc ('\n');

		إذا (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
فراغ   *yy_flex_xmalloc (صحيح ناپ)
{
	فراغ   *نتیجہ;

	نتیجہ = حافظہ_دیو((size_t) ناپ);
	إذا (!نتیجہ)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	أرجع نتیجہ;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
حرف   *chomp (حرف *str)
{
	حرف   *p = str;

	إذا (!str || !*str)	/* s is null or empty string */
		أرجع str;

	/* find end of string minus one */
	طالما (*p)
		++p;
	--p;

	/* eat newlines */
	طالما (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	أرجع str;
}

فراغ comment(ثابت حرف *txt)
{
	حرف buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[لڑی_لمبائی(buf)-1] == '\n';

	إذا (eol)
		buf[لڑی_لمبائی(buf)-1] = '\0';
	باہرلا_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	إذا (eol)
		outc ('\n');
}


