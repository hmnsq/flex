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
#ଅନ୍ତର୍ଭାଵ "flexdef.h"
#ଅନ୍ତର୍ଭାଵ "tables.h"

/* Append "new_text" to the running buffer. */
ଶୂନ୍ୟ add_action (ଅଚଳ ଅକ୍ଷର *new_text)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     len = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) strlen (new_text);

	ଯେତେବେଳେ (len + action_index >= action_size - 10 /* slop */ ) {

		ଯଦି (action_size > INT_MAX / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		ଅନ୍ୟଥା
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	strcpy (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

ଶୂନ୍ୟ   *allocate_array (ପୂର୍ଣ୍ଣସଂଖ୍ୟା size, size_t element_size)
{
	ଫେରନ୍ତୁ reallocate_array(ଖାଲି, size, element_size);
}


/* all_lower - true if a string is all lower-case */

ପୂର୍ଣ୍ଣସଂଖ୍ୟା all_lower (ଅକ୍ଷର *str)
{
	ଯେତେବେଳେ (*str) {
		ଯଦି (!isascii ((unsigned ଅକ୍ଷର) * str) || !islower ((unsigned ଅକ୍ଷର) * str))
			ଫେରନ୍ତୁ 0;
		++str;
	}

	ଫେରନ୍ତୁ 1;
}


/* all_upper - true if a string is all upper-case */

ପୂର୍ଣ୍ଣସଂଖ୍ୟା all_upper (ଅକ୍ଷର *str)
{
	ଯେତେବେଳେ (*str) {
		ଯଦି (!isascii ((unsigned ଅକ୍ଷର) * str) || !isupper ((unsigned ଅକ୍ଷର) * str))
			ଫେରନ୍ତୁ 0;
		++str;
	}

	ଫେରନ୍ତୁ 1;
}


/* intcmp - compares two integers for use by qsort. */

ପୂର୍ଣ୍ଣସଂଖ୍ୟା intcmp (ଅଚଳ ଶୂନ୍ୟ *a, ଅଚଳ ଶୂନ୍ୟ *b)
{
  ଫେରନ୍ତୁ *(ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *) a - *(ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

ଶୂନ୍ୟ check_char (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c)
{
	ଯଦି (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	ଯଦି (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

unsigned ଅକ୍ଷର clower (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c)
{
	ଫେରନ୍ତୁ (unsigned ଅକ୍ଷର) ((isascii (c) && isupper (c)) ? tolower (c) : c);
}


ଅକ୍ଷର *xstrdup(ଅଚଳ ଅକ୍ଷର *s)
{
	ଅକ୍ଷର *s2;

	ଯଦି ((s2 = strdup(s)) == ଖାଲି)
		flexfatal (_("memory allocation failure in xstrdup()"));

	ଫେରନ୍ତୁ s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

ପୂର୍ଣ୍ଣସଂଖ୍ୟା cclcmp (ଅଚଳ ଶୂନ୍ୟ *a, ଅଚଳ ଶୂନ୍ୟ *b)
{
	ଯଦି (!*(ଅଚଳ unsigned ଅକ୍ଷର *) a)
		ଫେରନ୍ତୁ 1;
	ଅନ୍ୟଥା
		ଯଦି (!*(ଅଚଳ unsigned ଅକ୍ଷର *) b)
			ଫେରନ୍ତୁ - 1;
		ଅନ୍ୟଥା
			ଫେରନ୍ତୁ *(ଅଚଳ unsigned ଅକ୍ଷର *) a - *(ଅଚଳ unsigned ଅକ୍ଷର *) b;
}


/* dataend - finish up a block of data declarations */

ଶୂନ୍ୟ dataend (ଅଚଳ ଅକ୍ଷର *endit)
{
	/* short circuit any output */
	ଯଦି (gentables) {

		ଯଦି (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		ଯଦି (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

ଶୂନ୍ୟ dataflush (ଶୂନ୍ୟ)
{
	ପ୍ରତିଜ୍ଞା (gentables);

	ଯଦି (datapos > 0)
		outc ('\n');

	ଯଦି (++dataline >= NUMDATALINES) {
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

ଶୂନ୍ୟ flexerror (ଅଚଳ ଅକ୍ଷର *ସନ୍ଦେଶ)
{
	fprintf (stderr, "%s: %s\n", program_name, ସନ୍ଦେଶ);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

ଶୂନ୍ୟ flexfatal (ଅଚଳ ଅକ୍ଷର *ସନ୍ଦେଶ)
{
	fprintf (stderr, _("%s: fatal internal error, %s\n"),
		 program_name, ସନ୍ଦେଶ);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

ଶୂନ୍ୟ lerr (ଅଚଳ ଅକ୍ଷର *ସନ୍ଦେଶ, ...)
{
	ଅକ୍ଷର    errmsg[MAXLINE];
	va_list args;

	va_start(args, ସନ୍ଦେଶ);
	vsnprintf (errmsg, ଆକାର(errmsg), ସନ୍ଦେଶ, args);
	va_end(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

ଶୂନ୍ୟ lerr_fatal (ଅଚଳ ଅକ୍ଷର *ସନ୍ଦେଶ, ...)
{
	ଅକ୍ଷର    errmsg[MAXLINE];
	va_list args;
	va_start(args, ସନ୍ଦେଶ);

	vsnprintf (errmsg, ଆକାର(errmsg), ସନ୍ଦେଶ, args);
	va_end(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
ଶୂନ୍ୟ ଧାଡ଼ି_directive_out (FILE *output_file, ଅକ୍ଷର *path, ପୂର୍ଣ୍ଣସଂଖ୍ୟା linenum)
{
	ଅକ୍ଷର	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	ଅକ୍ଷର    directive[MAXLINE*2], filename[MAXLINE];
	ଅକ୍ଷର   *s1, *s2, *s3;

	ଯଦି (!ctrl.gen_ଧାଡ଼ି_dirs)
		ଫେରନ୍ତୁ;

	s1 = (path != ଖାଲି) ? path : "M4_YY_OUTFILE_NAME";

	ଯଦି ((path != ଖାଲି) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[ଆକାର (filename) - 2];

	ଯେତେବେଳେ (s2 < s3 && *s1) {
		ଯଦି (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	ଯଦି (path != ଖାଲି)
		snprintf (directive, ଆକାର(directive), trace_fmt, linenum, filename);
	ଅନ୍ୟଥା {
		snprintf (directive, ଆକାର(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	ଯଦି (output_file) {
		fputs (directive, output_file);
	}
	ଅନ୍ୟଥା
		add_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
ଶୂନ୍ୟ mark_defs1 (ଶୂନ୍ୟ)
{
	defs1_offset = 0;
	action_array[action_index++] = '\0';
	action_offset = prolog_offset = action_index;
	action_array[action_index] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
ଶୂନ୍ୟ mark_prolog (ଶୂନ୍ୟ)
{
	action_array[action_index++] = '\0';
	action_offset = action_index;
	action_array[action_index] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
ଶୂନ୍ୟ mk2data (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ)
{
	/* short circuit any output */
	ଯଦି (!gentables)
		ଫେରନ୍ତୁ;

	ଯଦି (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ଯଦି (datapos == 0)
		/* Indent. */
		out ("    ");

	ଅନ୍ୟଥା
	  outc (',');

	++datapos;

	out_dec ("%5d", ମୂଲ୍ୟ);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
ଶୂନ୍ୟ mkdata (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ)
{
	/* short circuit any output */
	ଯଦି (!gentables)
		ଫେରନ୍ତୁ;

	ଯଦି (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	ଯଦି (datapos == 0)
		/* Indent. */
		out ("    ");
	ଅନ୍ୟଥା
		outc (',');
	++datapos;

	out_dec ("%5d", ମୂଲ୍ୟ);
}


/* myctoi - return the integer represented by a string of digits */

ପୂର୍ଣ୍ଣସଂଖ୍ୟା myctoi (ଅଚଳ ଅକ୍ଷର *array)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     val = 0;

	(ଶୂନ୍ୟ) sscanf (array, "%d", &val);

	ଫେରନ୍ତୁ val;
}


/* myesc - return character corresponding to escape sequence */

unsigned ଅକ୍ଷର myesc (unsigned ଅକ୍ଷର array[])
{
	unsigned ଅକ୍ଷର    c, esc_char;

	ବାଛ (array[1]) {
	ସ୍ଥିତି 'b':
		ଫେରନ୍ତୁ '\b';
	ସ୍ଥିତି 'f':
		ଫେରନ୍ତୁ '\f';
	ସ୍ଥିତି 'n':
		ଫେରନ୍ତୁ '\n';
	ସ୍ଥିତି 'r':
		ଫେରନ୍ତୁ '\r';
	ସ୍ଥିତି 't':
		ଫେରନ୍ତୁ '\t';
	ସ୍ଥିତି 'a':
		ଫେରନ୍ତୁ '\a';
	ସ୍ଥିତି 'v':
		ଫେରନ୍ତୁ '\v';
	ସ୍ଥିତି '0':
	ସ୍ଥିତି '1':
	ସ୍ଥିତି '2':
	ସ୍ଥିତି '3':
	ସ୍ଥିତି '4':
	ସ୍ଥିତି '5':
	ସ୍ଥିତି '6':
	ସ୍ଥିତି '7':
		{		/* \<octal> */
			ପୂର୍ଣ୍ଣସଂଖ୍ୟା     sptr = 1;

			ଯେତେବେଳେ (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned ଅକ୍ଷର) strtoul (array + 1, ଖାଲି, 8);

			array[sptr] = c;

			ଫେରନ୍ତୁ esc_char;
		}

	ସ୍ଥିତି 'x':
		{		/* \x<hex> */
			ପୂର୍ଣ୍ଣସଂଖ୍ୟା     sptr = 2;

			ଯେତେବେଳେ (sptr <= 3 && isxdigit (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (unsigned ଅକ୍ଷର) strtoul (array + 2, ଖାଲି, 16);

			array[sptr] = c;

			ଫେରନ୍ତୁ esc_char;
		}

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
		ଫେରନ୍ତୁ array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

ଶୂନ୍ୟ out (ଅଚଳ ଅକ୍ଷର *str)
{
	fputs (str, stdout);
}

ଶୂନ୍ୟ out_dec (ଅଚଳ ଅକ୍ଷର *fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା n)
{
	fprintf (stdout, fmt, n);
}

ଶୂନ୍ୟ out_dec2 (ଅଚଳ ଅକ୍ଷର *fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା n1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା n2)
{
	fprintf (stdout, fmt, n1, n2);
}

ଶୂନ୍ୟ out_hex (ଅଚଳ ଅକ୍ଷର *fmt, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା x)
{
	fprintf (stdout, fmt, x);
}

ଶୂନ୍ୟ out_str (ଅଚଳ ଅକ୍ଷର *fmt, ଅଚଳ ଅକ୍ଷର str[])
{
	fprintf (stdout,fmt, str);
}

ଶୂନ୍ୟ out_str_dec (ଅଚଳ ଅକ୍ଷର *fmt, ଅଚଳ ଅକ୍ଷର str[], ପୂର୍ଣ୍ଣସଂଖ୍ୟା n)
{
	fprintf (stdout,fmt, str, n);
}

ଶୂନ୍ୟ outc (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c)
{
	fputc (c, stdout);
}

ଶୂନ୍ୟ outn (ଅଚଳ ଅକ୍ଷର *str)
{
	fputs (str,stdout);
    fputc('\n',stdout);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
ଶୂନ୍ୟ out_m4_define (ଅଚଳ ଅକ୍ଷର* def, ଅଚଳ ଅକ୍ଷର* val)
{
    ଅଚଳ ଅକ୍ଷର * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    fprintf(stdout, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

ଅକ୍ଷର   *readable_form (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c)
{
	ସ୍ଥିର ଅକ୍ଷର rform[20];

	ଯଦି ((c >= 0 && c < 32) || c >= 127) {
		ବାଛ (c) {
		ସ୍ଥିତି '\b':
			ଫେରନ୍ତୁ "\\b";
		ସ୍ଥିତି '\f':
			ଫେରନ୍ତୁ "\\f";
		ସ୍ଥିତି '\n':
			ଫେରନ୍ତୁ "\\n";
		ସ୍ଥିତି '\r':
			ଫେରନ୍ତୁ "\\r";
		ସ୍ଥିତି '\t':
			ଫେରନ୍ତୁ "\\t";
		ସ୍ଥିତି '\a':
			ଫେରନ୍ତୁ "\\a";
		ସ୍ଥିତି '\v':
			ଫେରନ୍ତୁ "\\v";
		ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
			ଯଦି(env.trace_hex)
				snprintf (rform, ଆକାର(rform), "\\x%.2x", (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) c);
			ଅନ୍ୟଥା
				snprintf (rform, ଆକାର(rform), "\\%.3o", (unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା) c);
			ଫେରନ୍ତୁ rform;
		}
	}

	ଅନ୍ୟଥା ଯଦି (c == ' ')
		ଫେରନ୍ତୁ "' '";

	ଅନ୍ୟଥା {
		rform[0] = (ଅକ୍ଷର) c;
		rform[1] = '\0';

		ଫେରନ୍ତୁ rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

ଶୂନ୍ୟ   *reallocate_array (ଶୂନ୍ୟ *array, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size, size_t element_size)
{
	ଶୂନ୍ୟ *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	ଯଦି (reallocarr(&new_array, (size_t) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#ଅନ୍ୟଥା
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (size_t) size, element_size);
# ଅନ୍ୟଥା
	/* Do manual overflow detection */
	size_t ଅଙ୍କ_bytes = (size_t) size * element_size;
	new_array = (size && SIZE_MAX / (size_t) size < element_size) ? ଖାଲି :
		realloc(array, ଅଙ୍କ_bytes);
# endif
	ଯଦି (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	ଫେରନ୍ତୁ new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

ଶୂନ୍ୟ transition_struct_out (ପୂର୍ଣ୍ଣସଂଖ୍ୟା element_v, ପୂର୍ଣ୍ଣସଂଖ୍ୟା element_n)
{

	/* short circuit any output */
	ଯଦି (!gentables)
		ଫେରନ୍ତୁ;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	ଯଦି (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		ଯଦି (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
ଶୂନ୍ୟ   *yy_flex_xmalloc (ପୂର୍ଣ୍ଣସଂଖ୍ୟା size)
{
	ଶୂନ୍ୟ   *result;

	result = malloc((size_t) size);
	ଯଦି (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	ଫେରନ୍ତୁ result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
ଅକ୍ଷର   *chomp (ଅକ୍ଷର *str)
{
	ଅକ୍ଷର   *p = str;

	ଯଦି (!str || !*str)	/* s is null or empty string */
		ଫେରନ୍ତୁ str;

	/* find end of string minus one */
	ଯେତେବେଳେ (*p)
		++p;
	--p;

	/* eat newlines */
	ଯେତେବେଳେ (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	ଫେରନ୍ତୁ str;
}

ଶୂନ୍ୟ comment(ଅଚଳ ଅକ୍ଷର *txt)
{
	ଅକ୍ଷର buf[MAXLINE];
	bool eol;

	strncpy(buf, txt, MAXLINE-1);
	eol = buf[strlen(buf)-1] == '\n';

	ଯଦି (eol)
		buf[strlen(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	ଯଦି (eol)
		outc ('\n');
}


