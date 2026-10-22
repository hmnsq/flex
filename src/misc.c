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
शून्य add_action (अचर वर्ण *new_text)
{
	पूर्णाङ्क     len = (पूर्णाङ्क) म_माप (new_text);

	जबसम्म (len + action_index >= action_size - 10 /* slop */ ) {

		यदि (action_size > पूर्णांक_उच्च / 2)
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

शून्य   *allocate_array (पूर्णाङ्क size, माप_प्रकार element_size)
{
	फर्काऊ reallocate_array(रिक्त, size, element_size);
}


/* all_lower - true if a string is all lower-case */

पूर्णाङ्क all_lower (वर्ण *str)
{
	जबसम्म (*str) {
		यदि (!isascii ((अचिन्हित वर्ण) * str) || !है_छोटा ((अचिन्हित वर्ण) * str))
			फर्काऊ 0;
		++str;
	}

	फर्काऊ 1;
}


/* all_upper - true if a string is all upper-case */

पूर्णाङ्क all_upper (वर्ण *str)
{
	जबसम्म (*str) {
		यदि (!isascii ((अचिन्हित वर्ण) * str) || !है_बड़ा ((अचिन्हित वर्ण) * str))
			फर्काऊ 0;
		++str;
	}

	फर्काऊ 1;
}


/* intcmp - compares two integers for use by qsort. */

पूर्णाङ्क intcmp (अचर शून्य *a, अचर शून्य *b)
{
  फर्काऊ *(अचर पूर्णाङ्क *) a - *(अचर पूर्णाङ्क *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

शून्य check_char (पूर्णाङ्क c)
{
	यदि (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	यदि (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

अचिन्हित वर्ण clower (पूर्णाङ्क c)
{
	फर्काऊ (अचिन्हित वर्ण) ((isascii (c) && है_बड़ा (c)) ? छोटे (c) : c);
}


वर्ण *xstrdup(अचर वर्ण *s)
{
	वर्ण *s2;

	यदि ((s2 = strdup(s)) == रिक्त)
		flexfatal (_("memory allocation failure in xstrdup()"));

	फर्काऊ s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

पूर्णाङ्क cclcmp (अचर शून्य *a, अचर शून्य *b)
{
	यदि (!*(अचर अचिन्हित वर्ण *) a)
		फर्काऊ 1;
	अन्यथा
		यदि (!*(अचर अचिन्हित वर्ण *) b)
			फर्काऊ - 1;
		अन्यथा
			फर्काऊ *(अचर अचिन्हित वर्ण *) a - *(अचर अचिन्हित वर्ण *) b;
}


/* dataend - finish up a block of data declarations */

शून्य dataend (अचर वर्ण *endit)
{
	/* short circuit any output */
	यदि (gentables) {

		यदि (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		यदि (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

शून्य dataflush (शून्य)
{
	प्रतिज्ञा (gentables);

	यदि (datapos > 0)
		outc ('\n');

	यदि (++dataline >= NUMDATALINES) {
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

शून्य flexerror (अचर वर्ण *सन्देश)
{
	ख_लिखो (मानक_त्रुटि, "%s: %s\n", program_name, सन्देश);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

शून्य flexfatal (अचर वर्ण *सन्देश)
{
	ख_लिखो (मानक_त्रुटि, _("%s: fatal internal error, %s\n"),
		 program_name, सन्देश);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

शून्य lerr (अचर वर्ण *सन्देश, ...)
{
	वर्ण    errmsg[MAXLINE];
	बहु_सूची args;

	बहु_शुरू(args, सन्देश);
	vsnprintf (errmsg, परिमाण(errmsg), सन्देश, args);
	बहु_पूर्ण(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

शून्य lerr_fatal (अचर वर्ण *सन्देश, ...)
{
	वर्ण    errmsg[MAXLINE];
	बहु_सूची args;
	बहु_शुरू(args, सन्देश);

	vsnprintf (errmsg, परिमाण(errmsg), सन्देश, args);
	बहु_पूर्ण(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
शून्य पङ्क्ति_directive_out (खाता *output_file, वर्ण *path, पूर्णाङ्क linenum)
{
	वर्ण	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	वर्ण    directive[MAXLINE*2], filename[MAXLINE];
	वर्ण   *s1, *s2, *s3;

	यदि (!ctrl.gen_पङ्क्ति_dirs)
		फर्काऊ;

	s1 = (path != रिक्त) ? path : "M4_YY_OUTFILE_NAME";

	यदि ((path != रिक्त) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[परिमाण (filename) - 2];

	जबसम्म (s2 < s3 && *s1) {
		यदि (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	यदि (path != रिक्त)
		snprintf (directive, परिमाण(directive), trace_fmt, linenum, filename);
	अन्यथा {
		snprintf (directive, परिमाण(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	यदि (output_file) {
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
शून्य mk2data (पूर्णाङ्क मान)
{
	/* short circuit any output */
	यदि (!gentables)
		फर्काऊ;

	यदि (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	यदि (datapos == 0)
		/* Indent. */
		out ("    ");

	अन्यथा
	  outc (',');

	++datapos;

	out_dec ("%5d", मान);
}


/* mkdata - generate a data statement
 *
 * Generates a data statement initializing the current array element to
 * "value".
 */
शून्य mkdata (पूर्णाङ्क मान)
{
	/* short circuit any output */
	यदि (!gentables)
		फर्काऊ;

	यदि (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	यदि (datapos == 0)
		/* Indent. */
		out ("    ");
	अन्यथा
		outc (',');
	++datapos;

	out_dec ("%5d", मान);
}


/* myctoi - return the integer represented by a string of digits */

पूर्णाङ्क myctoi (अचर वर्ण *array)
{
	पूर्णाङ्क     val = 0;

	(शून्य) माला_पूछो (array, "%d", &val);

	फर्काऊ val;
}


/* myesc - return character corresponding to escape sequence */

अचिन्हित वर्ण myesc (अचिन्हित वर्ण array[])
{
	अचिन्हित वर्ण    c, esc_char;

	विकल्प (array[1]) {
	पक्ष 'b':
		फर्काऊ '\b';
	पक्ष 'f':
		फर्काऊ '\f';
	पक्ष 'n':
		फर्काऊ '\n';
	पक्ष 'r':
		फर्काऊ '\r';
	पक्ष 't':
		फर्काऊ '\t';
	पक्ष 'a':
		फर्काऊ '\a';
	पक्ष 'v':
		फर्काऊ '\v';
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

			जबसम्म (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (अचिन्हित वर्ण) म_से_अदीर्घ (array + 1, रिक्त, 8);

			array[sptr] = c;

			फर्काऊ esc_char;
		}

	पक्ष 'x':
		{		/* \x<hex> */
			पूर्णाङ्क     sptr = 2;

			जबसम्म (sptr <= 3 && है_षष्ठादशक (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (अचिन्हित वर्ण) म_से_अदीर्घ (array + 2, रिक्त, 16);

			array[sptr] = c;

			फर्काऊ esc_char;
		}

	स्वभाव:
		फर्काऊ array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

शून्य out (अचर वर्ण *str)
{
	ख_माला_दो (str, मानक_निकास);
}

शून्य out_dec (अचर वर्ण *fmt, पूर्णाङ्क n)
{
	ख_लिखो (मानक_निकास, fmt, n);
}

शून्य out_dec2 (अचर वर्ण *fmt, पूर्णाङ्क n1, पूर्णाङ्क n2)
{
	ख_लिखो (मानक_निकास, fmt, n1, n2);
}

शून्य out_hex (अचर वर्ण *fmt, अचिन्हित पूर्णाङ्क x)
{
	ख_लिखो (मानक_निकास, fmt, x);
}

शून्य out_str (अचर वर्ण *fmt, अचर वर्ण str[])
{
	ख_लिखो (मानक_निकास,fmt, str);
}

शून्य out_str_dec (अचर वर्ण *fmt, अचर वर्ण str[], पूर्णाङ्क n)
{
	ख_लिखो (मानक_निकास,fmt, str, n);
}

शून्य outc (पूर्णाङ्क c)
{
	ख_अक्षर_दो (c, मानक_निकास);
}

शून्य outn (अचर वर्ण *str)
{
	ख_माला_दो (str,मानक_निकास);
    ख_अक्षर_दो('\n',मानक_निकास);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
शून्य out_m4_define (अचर वर्ण* def, अचर वर्ण* val)
{
    अचर वर्ण * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    ख_लिखो(मानक_निकास, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

वर्ण   *readable_form (पूर्णाङ्क c)
{
	स्थिर वर्ण rform[20];

	यदि ((c >= 0 && c < 32) || c >= 127) {
		विकल्प (c) {
		पक्ष '\b':
			फर्काऊ "\\b";
		पक्ष '\f':
			फर्काऊ "\\f";
		पक्ष '\n':
			फर्काऊ "\\n";
		पक्ष '\r':
			फर्काऊ "\\r";
		पक्ष '\t':
			फर्काऊ "\\t";
		पक्ष '\a':
			फर्काऊ "\\a";
		पक्ष '\v':
			फर्काऊ "\\v";
		स्वभाव:
			यदि(env.trace_hex)
				snprintf (rform, परिमाण(rform), "\\x%.2x", (अचिन्हित पूर्णाङ्क) c);
			अन्यथा
				snprintf (rform, परिमाण(rform), "\\%.3o", (अचिन्हित पूर्णाङ्क) c);
			फर्काऊ rform;
		}
	}

	अन्यथा यदि (c == ' ')
		फर्काऊ "' '";

	अन्यथा {
		rform[0] = (वर्ण) c;
		rform[1] = '\0';

		फर्काऊ rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

शून्य   *reallocate_array (शून्य *array, पूर्णाङ्क size, माप_प्रकार element_size)
{
	शून्य *new_array;
#ifdef HAVE_REALLOCARR
	new_array = array;
	यदि (reallocarr(&new_array, (माप_प्रकार) size, element_size)) {
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
	माप_प्रकार अङ्क_bytes = (माप_प्रकार) size * element_size;
	new_array = (size && SIZE_MAX / (माप_प्रकार) size < element_size) ? रिक्त :
		पुनः_स्मृति(array, अङ्क_bytes);
# endif
	यदि (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#endif
	फर्काऊ new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

शून्य transition_struct_out (पूर्णाङ्क element_v, पूर्णाङ्क element_n)
{

	/* short circuit any output */
	यदि (!gentables)
		फर्काऊ;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_LENGTH;

	यदि (datapos >= 79 - TRANS_STRUCT_PRINT_LENGTH) {
		outc ('\n');

		यदि (++dataline % 10 == 0)
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

	result = दो_स्मृति((माप_प्रकार) size);
	यदि (!result)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	फर्काऊ result;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
वर्ण   *chomp (वर्ण *str)
{
	वर्ण   *p = str;

	यदि (!str || !*str)	/* s is null or empty string */
		फर्काऊ str;

	/* find end of string minus one */
	जबसम्म (*p)
		++p;
	--p;

	/* eat newlines */
	जबसम्म (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	फर्काऊ str;
}

शून्य comment(अचर वर्ण *txt)
{
	वर्ण buf[MAXLINE];
	bool eol;

	म_नकलन(buf, txt, MAXLINE-1);
	eol = buf[म_माप(buf)-1] == '\n';

	यदि (eol)
		buf[म_माप(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	यदि (eol)
		outc ('\n');
}


