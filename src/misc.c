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
#అన్తర్భావ "flexdef.h"
#అన్తర్భావ "tables.h"

/* Append "new_text" to the running buffer. */
శూన్య కూడు_action (స్థిరరాశి అక్షరం *new_పాఠ్యం)
{
	పూర్ణాంకం     len = (పూర్ణాంకం) అక్షరశ్రేణి_పొడవు (new_పాఠ్యం);

	అయితే (len + action_సూచీ >= action_కొలత - 10 /* slop */ ) {

		ఒకవేళ (action_కొలత > గరిష్ఠ_పూర్ణాంకం / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_కొలత += action_కొలత / 8;
		లేకపోతే
			action_కొలత = action_కొలత * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_కొలత);
	}

	strcpy (&action_array[action_సూచీ], new_పాఠ్యం);

	action_సూచీ += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

శూన్య   *allocate_array (పూర్ణాంకం కొలత, size_t element_కొలత)
{
	తిరిగి reallocate_array(ఖాళీ, కొలత, element_కొలత);
}


/* all_lower - true if a string is all lower-case */

పూర్ణాంకం all_క్రింది (అక్షరం *str)
{
	అయితే (*str) {
		ఒకవేళ (!isascii ((గుర్తులేని అక్షరం) * str) || !islower ((గుర్తులేని అక్షరం) * str))
			తిరిగి 0;
		++str;
	}

	తిరిగి 1;
}


/* all_upper - true if a string is all upper-case */

పూర్ణాంకం all_పై (అక్షరం *str)
{
	అయితే (*str) {
		ఒకవేళ (!isascii ((గుర్తులేని అక్షరం) * str) || !isupper ((గుర్తులేని అక్షరం) * str))
			తిరిగి 0;
		++str;
	}

	తిరిగి 1;
}


/* intcmp - compares two integers for use by qsort. */

పూర్ణాంకం intcmp (స్థిరరాశి శూన్య *a, స్థిరరాశి శూన్య *b)
{
  తిరిగి *(స్థిరరాశి పూర్ణాంకం *) a - *(స్థిరరాశి పూర్ణాంకం *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

శూన్య check_char (పూర్ణాంకం c)
{
	ఒకవేళ (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	ఒకవేళ (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

గుర్తులేని అక్షరం clower (పూర్ణాంకం c)
{
	తిరిగి (గుర్తులేని అక్షరం) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


అక్షరం *xstrdup(స్థిరరాశి అక్షరం *s)
{
	అక్షరం *s2;

	ఒకవేళ ((s2 = strdup(s)) == ఖాళీ)
		flexfatal (_("memory allocation failure in xstrdup()"));

	తిరిగి s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

పూర్ణాంకం cclcmp (స్థిరరాశి శూన్య *a, స్థిరరాశి శూన్య *b)
{
	ఒకవేళ (!*(స్థిరరాశి గుర్తులేని అక్షరం *) a)
		తిరిగి 1;
	లేకపోతే
		ఒకవేళ (!*(స్థిరరాశి గుర్తులేని అక్షరం *) b)
			తిరిగి - 1;
		లేకపోతే
			తిరిగి *(స్థిరరాశి గుర్తులేని అక్షరం *) a - *(స్థిరరాశి గుర్తులేని అక్షరం *) b;
}


/* dataend - finish up a block of data declarations */

శూన్య dataend (స్థిరరాశి అక్షరం *endit)
{
	/* short circuit any output */
	ఒకవేళ (gentables) {

		ఒకవేళ (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		ఒకవేళ (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

శూన్య dataflush (శూన్య)
{
	ప్రతిజ్ఞా (gentables);

	ఒకవేళ (datapos > 0)
		outc ('\n');

	ఒకవేళ (++dataline >= NUMDATALINES) {
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

శూన్య flexerror (స్థిరరాశి అక్షరం *సందేశం)
{
	fprintf (stderr, "%s: %s\n", కార్యక్రమం_name, సందేశం);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

శూన్య flexfatal (స్థిరరాశి అక్షరం *సందేశం)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 కార్యక్రమం_name, సందేశం);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

శూన్య lerr (స్థిరరాశి అక్షరం *సందేశం, ...)
{
	అక్షరం    errmsg[MAXLINE];
	va_list వాదనలు;

	va_ప్రారంభం(వాదనలు, సందేశం);
	vsnprintf (errmsg, పరిమాణం(errmsg), సందేశం, వాదనలు);
	va_చివర(వాదనలు);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

శూన్య lerr_fatal (స్థిరరాశి అక్షరం *సందేశం, ...)
{
	అక్షరం    errmsg[MAXLINE];
	va_list వాదనలు;
	va_ప్రారంభం(వాదనలు, సందేశం);

	vsnprintf (errmsg, పరిమాణం(errmsg), సందేశం, వాదనలు);
	va_చివర(వాదనలు);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
శూన్య పంక్తి_directive_బహిర్గతం (FILE *output_file, అక్షరం *మార్గం, పూర్ణాంకం linenum)
{
	అక్షరం	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	అక్షరం    directive[MAXLINE*2], filename[MAXLINE];
	అక్షరం   *s1, *s2, *s3;

	ఒకవేళ (!ctrl.gen_పంక్తి_dirs)
		తిరిగి;

	s1 = (మార్గం != ఖాళీ) ? మార్గం : "M4_YY_OUTFILE_NAME";

	ఒకవేళ ((మార్గం != ఖాళీ) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[పరిమాణం (filename) - 2];

	అయితే (s2 < s3 && *s1) {
		ఒకవేళ (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	ఒకవేళ (మార్గం != ఖాళీ)
		snprintf (directive, పరిమాణం(directive), trace_fmt, linenum, filename);
	లేకపోతే {
		snprintf (directive, పరిమాణం(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	ఒకవేళ (output_file) {
		fputs (directive, output_file);
	}
	లేకపోతే
		కూడు_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
శూన్య mark_defs1 (శూన్య)
{
	defs1_స్థానభ్రంశం = 0;
	action_array[action_సూచీ++] = '\0';
	action_స్థానభ్రంశం = prolog_స్థానభ్రంశం = action_సూచీ;
	action_array[action_సూచీ] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
శూన్య mark_prolog (శూన్య)
{
	action_array[action_సూచీ++] = '\0';
	action_స్థానభ్రంశం = action_సూచీ;
	action_array[action_సూచీ] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
శూన్య mk2data (పూర్ణాంకం విలువ)
{
	/* short circuit any output */
	ఒకవేళ (!gentables)
		తిరిగి;

	ఒకవేళ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ఒకవేళ (datapos == 0)
		/* Indent. */
		బహిర్గతం ("    ");

	లేకపోతే
	  outc (',');

	++datapos;

	బహిర్గతం_dec ("%5d", విలువ);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
శూన్య mkdata (పూర్ణాంకం విలువ)
{
	/* short circuit any output */
	ఒకవేళ (!gentables)
		తిరిగి;

	ఒకవేళ (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ఒకవేళ (datapos == 0)
		/* Indent. */
		బహిర్గతం ("    ");
	లేకపోతే
		outc (',');
	++datapos;

	బహిర్గతం_dec ("%5d", విలువ);
}


/* myctoi - return the integer represented by a string of digits */

పూర్ణాంకం myctoi (స్థిరరాశి అక్షరం *array)
{
	పూర్ణాంకం     val = 0;

	(శూన్య) అక్షరశ్రేణి_చదువు (array, "%d", &val);

	తిరిగి val;
}


/* myesc - return character corresponding to escape sequence */

గుర్తులేని అక్షరం myesc (గుర్తులేని అక్షరం array[])
{
	గుర్తులేని అక్షరం    c, esc_char;

	ఎంపిక (array[1]) {
	స్థితి 'b':
		తిరిగి '\b';
	స్థితి 'f':
		తిరిగి '\f';
	స్థితి 'n':
		తిరిగి '\n';
	స్థితి 'r':
		తిరిగి '\r';
	స్థితి 't':
		తిరిగి '\t';
	స్థితి 'a':
		తిరిగి '\a';
	స్థితి 'v':
		తిరిగి '\v';
	స్థితి '0':
	స్థితి '1':
	స్థితి '2':
	స్థితి '3':
	స్థితి '4':
	స్థితి '5':
	స్థితి '6':
	స్థితి '7':
		{		/* \<octal> */
			పూర్ణాంకం     sptr = 1;

			అయితే (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (గుర్తులేని అక్షరం) strtoul (array + 1, ఖాళీ, 8);

			array[sptr] = c;

			తిరిగి esc_char;
		}

	స్థితి 'x':
		{		/* \x<hex> */
			పూర్ణాంకం     sptr = 2;

			అయితే (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (గుర్తులేని అక్షరం) strtoul (array + 2, ఖాళీ, 16);

			array[sptr] = c;

			తిరిగి esc_char;
		}

	అప్రమేయ:
		తిరిగి array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

శూన్య బహిర్గతం (స్థిరరాశి అక్షరం *str)
{
	fputs (str, stdout);
}

శూన్య బహిర్గతం_dec (స్థిరరాశి అక్షరం *fmt, పూర్ణాంకం n)
{
	fprintf (stdout, fmt, n);
}

శూన్య బహిర్గతం_dec2 (స్థిరరాశి అక్షరం *fmt, పూర్ణాంకం n1, పూర్ణాంకం n2)
{
	fprintf (stdout, fmt, n1, n2);
}

శూన్య బహిర్గతం_hex (స్థిరరాశి అక్షరం *fmt, గుర్తులేని పూర్ణాంకం x)
{
	fprintf (stdout, fmt, x);
}

శూన్య బహిర్గతం_str (స్థిరరాశి అక్షరం *fmt, స్థిరరాశి అక్షరం str[])
{
	fprintf (stdout,fmt, str);
}

శూన్య బహిర్గతం_str_dec (స్థిరరాశి అక్షరం *fmt, స్థిరరాశి అక్షరం str[], పూర్ణాంకం n)
{
	fprintf (stdout,fmt, str, n);
}

శూన్య outc (పూర్ణాంకం c)
{
	fputc (c, stdout);
}

శూన్య outn (స్థిరరాశి అక్షరం *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
శూన్య బహిర్గతం_m4_define (స్థిరరాశి అక్షరం* def, స్థిరరాశి అక్షరం* val)
{
    స్థిరరాశి అక్షరం * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

అక్షరం   *readable_form (పూర్ణాంకం c)
{
	స్థిర అక్షరం rform[20];

	ఒకవేళ ((c >= 0 && c < 32) || c >= 127) {
		ఎంపిక (c) {
		స్థితి '\b':
			తిరిగి "\\b";
		స్థితి '\f':
			తిరిగి "\\f";
		స్థితి '\n':
			తిరిగి "\\n";
		స్థితి '\r':
			తిరిగి "\\r";
		స్థితి '\t':
			తిరిగి "\\t";
		స్థితి '\a':
			తిరిగి "\\a";
		స్థితి '\v':
			తిరిగి "\\v";
		అప్రమేయ:
			ఒకవేళ(env.trace_hex)
				snprintf (rform, పరిమాణం(rform), "\\x%.2x", (గుర్తులేని పూర్ణాంకం) c);
			లేకపోతే
				snprintf (rform, పరిమాణం(rform), "\\%.3o", (గుర్తులేని పూర్ణాంకం) c);
			తిరిగి rform;
		}
	}

	లేకపోతే ఒకవేళ (c == ' ')
		తిరిగి "' '";

	లేకపోతే {
		rform[0] = (అక్షరం) c;
		rform[1] = '\0';

		తిరిగి rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

శూన్య   *reallocate_array (శూన్య *array, పూర్ణాంకం కొలత, size_t element_కొలత)
{
	శూన్య *new_array;
#నిర్వచితమైతే HAVE_REALLOCARR
	new_array = array;
	ఒకవేళ (reallocarr(&new_array, (size_t) కొలత, element_కొలత)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#లేకపోతే
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) కొలత, element_కొలత);
# లేకపోతే
	/* Do manual overflow detection */
	size_t అంకె_బైట్లు = (size_t) కొలత * element_కొలత;
	new_array = (కొలత && కొలత_MAX / (size_t) కొలత < element_కొలత) ? ఖాళీ :
		realloc(array, అంకె_బైట్లు);
# endif
	ఒకవేళ (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#అయితే_ముగింపు
	తిరిగి new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

శూన్య transition_struct_బహిర్గతం (పూర్ణాంకం element_v, పూర్ణాంకం element_n)
{

	/* short circuit any output */
	ఒకవేళ (!gentables)
		తిరిగి;

	బహిర్గతం_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_నిడివి;

	ఒకవేళ (datapos >= 79 - TRANS_STRUCT_PRINT_నిడివి) {
		outc ('\n');

		ఒకవేళ (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
శూన్య   *yy_flex_xmalloc (పూర్ణాంకం కొలత)
{
	శూన్య   *ఫలితం;

	ఫలితం = జ్ఞాపకం_ఇవ్వు((size_t) కొలత);
	ఒకవేళ (!ఫలితం)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	తిరిగి ఫలితం;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
అక్షరం   *chomp (అక్షరం *str)
{
	అక్షరం   *p = str;

	ఒకవేళ (!str || !*str)	/* s is null or empty string */
		తిరిగి str;

	/* find end of string minus one */
	అయితే (*p)
		++p;
	--p;

	/* eat newlines */
	అయితే (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	తిరిగి str;
}

శూన్య comment(స్థిరరాశి అక్షరం *txt)
{
	అక్షరం buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[అక్షరశ్రేణి_పొడవు(buf)-1] == '\n';

	ఒకవేళ (eol)
		buf[అక్షరశ్రేణి_పొడవు(buf)-1] = '\0';
	బహిర్గతం_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	ఒకవేళ (eol)
		outc ('\n');
}


