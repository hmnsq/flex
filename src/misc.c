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
शून्य add_action (स्थिरांक अक्षर *new_text)
{
	पूर्णांक     len = (पूर्णांक) म_माप (new_text);

	पर्यंत (len + action_index >= action_size - 10 /* slop */ ) {

		जर (action_size > पूर्णांक_उच्च / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_size += action_size / 8;
		अन्यथा
			action_size = action_size * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_size);
	}

	म_नकल (&action_array[action_index], new_text);

	action_index += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

शून्य   *allocate_array (पूर्णांक size, माप_प्रकार element_size)
{
	परत reallocate_array(रिक्त, size, element_size);
}


/* all_lower - true if a string is all lower-case */

पूर्णांक all_lower (अक्षर *str)
{
	पर्यंत (*str) {
		जर (!isascii ((अचिन्हित अक्षर) * str) || !है_छोटा ((अचिन्हित अक्षर) * str))
			परत 0;
		++str;
	}

	परत 1;
}


/* all_upper - true if a string is all upper-case */

पूर्णांक all_upper (अक्षर *str)
{
	पर्यंत (*str) {
		जर (!isascii ((अचिन्हित अक्षर) * str) || !है_बड़ा ((अचिन्हित अक्षर) * str))
			परत 0;
		++str;
	}

	परत 1;
}


/* intcmp - compares two integers for use by qsort. */

पूर्णांक intcmp (स्थिरांक शून्य *a, स्थिरांक शून्य *b)
{
  परत *(स्थिरांक पूर्णांक *) a - *(स्थिरांक पूर्णांक *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

शून्य check_char (पूर्णांक c)
{
	जर (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	जर (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

अचिन्हित अक्षर clower (पूर्णांक c)
{
	परत (अचिन्हित अक्षर) ((isascii (c) && है_बड़ा (c)) ? छोटे (c) : c);
}


अक्षर *xstrdup(स्थिरांक अक्षर *s)
{
	अक्षर *s2;

	जर ((s2 = strdup(s)) == रिक्त)
		flexfatal (_("memory allocation failure in xstrdup()"));

	परत s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

पूर्णांक cclcmp (स्थिरांक शून्य *a, स्थिरांक शून्य *b)
{
	जर (!*(स्थिरांक अचिन्हित अक्षर *) a)
		परत 1;
	अन्यथा
		जर (!*(स्थिरांक अचिन्हित अक्षर *) b)
			परत - 1;
		अन्यथा
			परत *(स्थिरांक अचिन्हित अक्षर *) a - *(स्थिरांक अचिन्हित अक्षर *) b;
}


/* dataend - finish up a block of data declarations */

शून्य dataend (स्थिरांक अक्षर *endit)
{
	/* short circuit any output */
	जर (gentables) {

		जर (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		जर (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

शून्य dataflush (शून्य)
{
	प्रतिज्ञा (gentables);

	जर (datapos > 0)
		outc ('\n');

	जर (++dataline >= NUMDATALINES) {
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

शून्य flexerror (स्थिरांक अक्षर *संदेश)
{
	ख_लिखो (मानक_त्रुटि, "%s: %s\n", program_name, संदेश);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

शून्य flexfatal (स्थिरांक अक्षर *संदेश)
{
	ख_लिखो (मानक_त्रुटि, _("%s: fatal internal error, %s\n"),
		 program_name, संदेश);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

शून्य lerr (स्थिरांक अक्षर *संदेश, ...)
{
	अक्षर    errmsg[MAXLINE];
	बहु_सूची args;

	बहु_शुरू(args, संदेश);
	vsnprintf (errmsg, आकार(errmsg), संदेश, args);
	बहु_पूर्ण(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

शून्य lerr_fatal (स्थिरांक अक्षर *संदेश, ...)
{
	अक्षर    errmsg[MAXLINE];
	बहु_सूची args;
	बहु_शुरू(args, संदेश);

	vsnprintf (errmsg, आकार(errmsg), संदेश, args);
	बहु_पूर्ण(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
शून्य ओळ_directive_out (खाता *output_file, अक्षर *path, पूर्णांक linenum)
{
	अक्षर	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	अक्षर    directive[MAXLINE*2], filename[MAXLINE];
	अक्षर   *s1, *s2, *s3;

	जर (!ctrl.gen_ओळ_dirs)
		परत;

	s1 = (path != रिक्त) ? path : "M4_YY_OUTFILE_NAME";

	जर ((path != रिक्त) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[आकार (filename) - 2];

	पर्यंत (s2 < s3 && *s1) {
		जर (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	जर (path != रिक्त)
		snprintf (directive, आकार(directive), trace_fmt, linenum, filename);
	अन्यथा {
		snprintf (directive, आकार(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	जर (output_file) {
		ख_माला_दो (directive, output_file);
	}
	अन्यथा
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
शून्य mk2data (पूर्णांक मूल्य)
{
	/* short circuit any output */
	जर (!gentables)
		परत;

	जर (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	जर (datapos == 0)
		/* Indent. */
		out ("    ");

	अन्यथा
	  outc (',');

	++datapos;

	out_dec ("%5d", मूल्य);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
शून्य mkdata (पूर्णांक मूल्य)
{
	/* short circuit any output */
	जर (!gentables)
		परत;

	जर (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	जर (datapos == 0)
		/* Indent. */
		out ("    ");
	अन्यथा
		outc (',');
	++datapos;

	out_dec ("%5d", मूल्य);
}


/* myctoi - return the integer represented by a string of digits */

पूर्णांक myctoi (स्थिरांक अक्षर *array)
{
	पूर्णांक     val = 0;

	(शून्य) माला_पूछो (array, "%d", &val);

	परत val;
}


/* myesc - return character corresponding to escape sequence */

अचिन्हित अक्षर myesc (अचिन्हित अक्षर array[])
{
	अचिन्हित अक्षर    c, esc_char;

	निवड (array[1]) {
	स्थिती 'b':
		परत '\b';
	स्थिती 'f':
		परत '\f';
	स्थिती 'n':
		परत '\n';
	स्थिती 'r':
		परत '\r';
	स्थिती 't':
		परत '\t';
	स्थिती 'a':
		परत '\a';
	स्थिती 'v':
		परत '\v';
	स्थिती '0':
	स्थिती '1':
	स्थिती '2':
	स्थिती '3':
	स्थिती '4':
	स्थिती '5':
	स्थिती '6':
	स्थिती '7':
		{		/* \<octal> */
			पूर्णांक     sptr = 1;

			पर्यंत (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (अचिन्हित अक्षर) म_से_अदीर्घ (array + 1, रिक्त, 8);

			array[sptr] = c;

			परत esc_char;
		}

	स्थिती 'x':
		{		/* \x<hex> */
			पूर्णांक     sptr = 2;

			पर्यंत (sptr <= 3 && है_षष्ठादशक (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (अचिन्हित अक्षर) म_से_अदीर्घ (array + 2, रिक्त, 16);

			array[sptr] = c;

			परत esc_char;
		}

	पूर्वनिर्धारित:
		परत array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

शून्य out (स्थिरांक अक्षर *str)
{
	ख_माला_दो (str, मानक_निकास);
}

शून्य out_dec (स्थिरांक अक्षर *fmt, पूर्णांक n)
{
	ख_लिखो (मानक_निकास, fmt, n);
}

शून्य out_dec2 (स्थिरांक अक्षर *fmt, पूर्णांक n1, पूर्णांक n2)
{
	ख_लिखो (मानक_निकास, fmt, n1, n2);
}

शून्य out_hex (स्थिरांक अक्षर *fmt, अचिन्हित पूर्णांक x)
{
	ख_लिखो (मानक_निकास, fmt, x);
}

शून्य out_str (स्थिरांक अक्षर *fmt, स्थिरांक अक्षर str[])
{
	ख_लिखो (मानक_निकास,fmt, str);
}

शून्य out_str_dec (स्थिरांक अक्षर *fmt, स्थिरांक अक्षर str[], पूर्णांक n)
{
	ख_लिखो (मानक_निकास,fmt, str, n);
}

शून्य outc (पूर्णांक c)
{
	ख_अक्षर_दो (c, मानक_निकास);
}

शून्य outn (स्थिरांक अक्षर *str)
{
	ख_माला_दो (str,मानक_निकास);
    ख_अक्षर_दो('\n',मानक_निकास);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
शून्य out_m4_define (स्थिरांक अक्षर* def, स्थिरांक अक्षर* val)
{
    स्थिरांक अक्षर * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    ख_लिखो(मानक_निकास, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

अक्षर   *readable_form (पूर्णांक c)
{
	स्थिर अक्षर rform[20];

	जर ((c >= 0 && c < 32) || c >= 127) {
		निवड (c) {
		स्थिती '\b':
			परत "\\b";
		स्थिती '\f':
			परत "\\f";
		स्थिती '\n':
			परत "\\n";
		स्थिती '\r':
			परत "\\r";
		स्थिती '\t':
			परत "\\t";
		स्थिती '\a':
			परत "\\a";
		स्थिती '\v':
			परत "\\v";
		पूर्वनिर्धारित:
			जर(env.trace_hex)
				snprintf (rform, आकार(rform), "\\x%.2x", (अचिन्हित पूर्णांक) c);
			अन्यथा
				snprintf (rform, आकार(rform), "\\%.3o", (अचिन्हित पूर्णांक) c);
			परत rform;
		}
	}

	अन्यथा जर (c == ' ')
		परत "' '";

	अन्यथा {
		rform[0] = (अक्षर) c;
		rform[1] = '\0';

		परत rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

शून्य   *reallocate_array (शून्य *array, पूर्णांक size, माप_प्रकार element_size)
{
	शून्य *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	जर (reallocarr(&new_array, (माप_प्रकार) size, element_size)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#अन्यथा
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (माप_प्रकार) size, element_size);
# अन्यथा
	/* Do manual overflow detection */
	माप_प्रकार अंक_bytes = (माप_प्रकार) size * element_size;
	new_array = (size && SIZE_MAX / (माप_प्रकार) size < element_size) ? रिक्त :
		पुनः_स्मृति(array, अंक_bytes);
# endif
	जर (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	परत new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

शून्य transition_struct_out (पूर्णांक element_v, पूर्णांक element_n)
{

	/* short circuit any output */
	जर (!gentables)
		परत;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	जर (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		जर (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
शून्य   *yy_flex_xmalloc (पूर्णांक size)
{
	शून्य   *result;

	result = दो_स्मृति((माप_प्रकार) size);
	जर (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	परत result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
अक्षर   *chomp (अक्षर *str)
{
	अक्षर   *p = str;

	जर (!str || !*str)	/* s is null or empty string */
		परत str;

	/* find end of string minus one */
	पर्यंत (*p)
		++p;
	--p;

	/* eat newlines */
	पर्यंत (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	परत str;
}

शून्य comment(स्थिरांक अक्षर *txt)
{
	अक्षर buf[MAXLINE];
	bool eol;

	म_नकलन(buf, txt, MAXLINE-1);
	eol = buf[म_माप(buf)-1] == '\n';

	जर (eol)
		buf[म_माप(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	जर (eol)
		outc ('\n');
}


