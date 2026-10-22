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
#समावेश "flexdef.h"
#समावेश "tables.h"

/* Append "new_text" to the running buffer. */
व्योम add_action (स्थिर अक्षर *new_text)
{
	पूर्णांक     len = (पूर्णांक) म_माप (new_text);

	जबतक (len + action_सूचकांक >= action_आकार - 10 /* slop */ ) {

		अगर (action_आकार > पूर्णांक_उच्च / 2)
			/* Increase just a little, to try to avoid overflow
			 * on 16-bit machines.
			 */
			action_आकार += action_आकार / 8;
		अन्यथा
			action_आकार = action_आकार * 2;

		action_array =
			reallocate_character_array (action_array,
						    action_आकार);
	}

	म_नकल (&action_array[action_सूचकांक], new_text);

	action_सूचकांक += len;
}


/* allocate_array - allocate memory for an integer array of the given size */

व्योम   *allocate_array (पूर्णांक आकार, माप_प्रकार element_आकार)
{
	वापस reallocate_array(शून्य, आकार, element_आकार);
}


/* all_lower - true if a string is all lower-case */

पूर्णांक all_lower (अक्षर *str)
{
	जबतक (*str) {
		अगर (!isascii ((अचिन्हित अक्षर) * str) || !है_छोटा ((अचिन्हित अक्षर) * str))
			वापस 0;
		++str;
	}

	वापस 1;
}


/* all_upper - true if a string is all upper-case */

पूर्णांक all_upper (अक्षर *str)
{
	जबतक (*str) {
		अगर (!isascii ((अचिन्हित अक्षर) * str) || !है_बड़ा ((अचिन्हित अक्षर) * str))
			वापस 0;
		++str;
	}

	वापस 1;
}


/* intcmp - compares two integers for use by qsort. */

पूर्णांक intcmp (स्थिर व्योम *a, स्थिर व्योम *b)
{
  वापस *(स्थिर पूर्णांक *) a - *(स्थिर पूर्णांक *) b;
}


/* check_char - checks a character to make sure it's within the range
 *		we're expecting.  If not, generates fatal error message
 *		and exits.
 */

व्योम check_char (पूर्णांक c)
{
	अगर (c >= CSIZE)
		lerr (_("bad character '%s' detected in check_char()"),
			readable_form (c));

	अगर (c >= ctrl.csize)
		lerr (_
			("scanner requires -8 flag to use the character %s"),
			readable_form (c));
}



/* clower - replace upper-case letter to lower-case */

अचिन्हित अक्षर clower (पूर्णांक c)
{
	वापस (अचिन्हित अक्षर) ((isascii (c) && है_बड़ा (c)) ? छोटे (c) : c);
}


अक्षर *xstrdup(स्थिर अक्षर *s)
{
	अक्षर *s2;

	अगर ((s2 = strdup(s)) == शून्य)
		flexfatal (_("memory allocation failure in xstrdup()"));

	वापस s2;
}


/* cclcmp - compares two characters for use by qsort with '\0' sorting last. */

पूर्णांक cclcmp (स्थिर व्योम *a, स्थिर व्योम *b)
{
	अगर (!*(स्थिर अचिन्हित अक्षर *) a)
		वापस 1;
	अन्यथा
		अगर (!*(स्थिर अचिन्हित अक्षर *) b)
			वापस - 1;
		अन्यथा
			वापस *(स्थिर अचिन्हित अक्षर *) a - *(स्थिर अचिन्हित अक्षर *) b;
}


/* dataend - finish up a block of data declarations */

व्योम dataend (स्थिर अक्षर *endit)
{
	/* short circuit any output */
	अगर (gentables) {

		अगर (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		अगर (endit)
			outn (endit);
	}
	dataline = 0;
	datapos = 0;
}


/* dataflush - flush generated data statements */

व्योम dataflush (व्योम)
{
	निश्चित (gentables);

	अगर (datapos > 0)
		outc ('\n');

	अगर (++dataline >= NUMDATALINES) {
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

व्योम flexerror (स्थिर अक्षर *संदेश)
{
	ख_लिखो (मानक_त्रुटि, "%s: %s\n", program_name, संदेश);
	flexend (1);
}


/* flexfatal - report a fatal error message and terminate */

व्योम flexfatal (स्थिर अक्षर *संदेश)
{
	ख_लिखो (मानक_त्रुटि, _("%s: fatal internal error, %s\n"),
		 program_name, संदेश);
	FLEX_EXIT (1);
}


/* lerr - report an error message */

व्योम lerr (स्थिर अक्षर *संदेश, ...)
{
	अक्षर    errmsg[MAXLINE];
	बहु_सूची args;

	बहु_शुरू(args, संदेश);
	vsnprintf (errmsg, माप(errmsg), संदेश, args);
	बहु_पूर्ण(args);
	flexerror (errmsg);
}


/* lerr_fatal - as lerr, but call flexfatal */

व्योम lerr_fatal (स्थिर अक्षर *संदेश, ...)
{
	अक्षर    errmsg[MAXLINE];
	बहु_सूची args;
	बहु_शुरू(args, संदेश);

	vsnprintf (errmsg, माप(errmsg), संदेश, args);
	बहु_पूर्ण(args);
	flexfatal (errmsg);
}


/* line_directive_out - spit out a "#line" statement or equivalent */
व्योम पंक्ति_directive_out (खाता *output_file, अक्षर *path, पूर्णांक linenum)
{
	अक्षर	*trace_fmt = "m4_ifdef([[M4_HOOK_TRACE_LINE_FORMAT]], [[M4_HOOK_TRACE_LINE_FORMAT([[%d]], [[%s]])]])";
	अक्षर    directive[MAXLINE*2], filename[MAXLINE];
	अक्षर   *s1, *s2, *s3;

	अगर (!ctrl.gen_पंक्ति_dirs)
		वापस;

	s1 = (path != शून्य) ? path : "M4_YY_OUTFILE_NAME";

	अगर ((path != शून्य) && !s1)
		s1 = "<stdin>";
    
	s2 = filename;
	s3 = &filename[माप (filename) - 2];

	जबतक (s2 < s3 && *s1) {
		अगर (*s1 == '\\' || *s1 == '"')
			/* Escape the '\' or '"' */
			*s2++ = '\\';

		*s2++ = *s1++;
	}

	*s2 = '\0';

	अगर (path != शून्य)
		snprintf (directive, माप(directive), trace_fmt, linenum, filename);
	अन्यथा {
		snprintf (directive, माप(directive), trace_fmt, 0, filename);
	}

	/* If output_file is nil then we should put the directive in
	 * the accumulated actions.
	 */
	अगर (output_file) {
		ख_माला_दो (directive, output_file);
	}
	अन्यथा
		add_action (directive);
}


/* mark_defs1 - mark the current position in the action array as
 *               representing where the user's section 1 definitions end
 *		 and the prolog begins
 */
व्योम mark_defs1 (व्योम)
{
	defs1_offset = 0;
	action_array[action_सूचकांक++] = '\0';
	action_offset = prolog_offset = action_सूचकांक;
	action_array[action_सूचकांक] = '\0';
}


/* mark_prolog - mark the current position in the action array as
 *               representing the end of the action prolog
 */
व्योम mark_prolog (व्योम)
{
	action_array[action_सूचकांक++] = '\0';
	action_offset = action_सूचकांक;
	action_array[action_सूचकांक] = '\0';
}


/* mk2data - generate a data statement for a two-dimensional array
 *
 * Generates a data statement initializing the current 2-D array to "value".
 */
व्योम mk2data (पूर्णांक मूल्य)
{
	/* short circuit any output */
	अगर (!gentables)
		वापस;

	अगर (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	अगर (datapos == 0)
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
व्योम mkdata (पूर्णांक मूल्य)
{
	/* short circuit any output */
	अगर (!gentables)
		वापस;

	अगर (datapos >= NUMDATAITEMS) {
		outc (',');
		dataflush ();
	}

	अगर (datapos == 0)
		/* Indent. */
		out ("    ");
	अन्यथा
		outc (',');
	++datapos;

	out_dec ("%5d", मूल्य);
}


/* myctoi - return the integer represented by a string of digits */

पूर्णांक myctoi (स्थिर अक्षर *array)
{
	पूर्णांक     val = 0;

	(व्योम) माला_पूछो (array, "%d", &val);

	वापस val;
}


/* myesc - return character corresponding to escape sequence */

अचिन्हित अक्षर myesc (अचिन्हित अक्षर array[])
{
	अचिन्हित अक्षर    c, esc_char;

	चयन (array[1]) {
	हाल 'b':
		वापस '\b';
	हाल 'f':
		वापस '\f';
	हाल 'n':
		वापस '\n';
	हाल 'r':
		वापस '\r';
	हाल 't':
		वापस '\t';
	हाल 'a':
		वापस '\a';
	हाल 'v':
		वापस '\v';
	हाल '0':
	हाल '1':
	हाल '2':
	हाल '3':
	हाल '4':
	हाल '5':
	हाल '6':
	हाल '7':
		{		/* \<octal> */
			पूर्णांक     sptr = 1;

			जबतक (sptr <= 3 &&
                               array[sptr] >= '0' && array[sptr] <= '7') {
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (अचिन्हित अक्षर) म_से_अदीर्घ (array + 1, शून्य, 8);

			array[sptr] = c;

			वापस esc_char;
		}

	हाल 'x':
		{		/* \x<hex> */
			पूर्णांक     sptr = 2;

			जबतक (sptr <= 3 && है_षष्ठादशक (array[sptr])) {
				/* Don't increment inside loop control
				 * because if isxdigit() is a macro it might
				 * expand into multiple increments ...
				 */
				++sptr;
			}

			c = array[sptr];
			array[sptr] = '\0';

			esc_char = (अचिन्हित अक्षर) म_से_अदीर्घ (array + 2, शून्य, 16);

			array[sptr] = c;

			वापस esc_char;
		}

	शेष:
		वापस array[1];
	}
}


/* out - various flavors of outputting a (possibly formatted) string for the
 *	 generated scanner, keeping track of the line count.
 */

व्योम out (स्थिर अक्षर *str)
{
	ख_माला_दो (str, मानक_निकास);
}

व्योम out_dec (स्थिर अक्षर *fmt, पूर्णांक n)
{
	ख_लिखो (मानक_निकास, fmt, n);
}

व्योम out_dec2 (स्थिर अक्षर *fmt, पूर्णांक n1, पूर्णांक n2)
{
	ख_लिखो (मानक_निकास, fmt, n1, n2);
}

व्योम out_hex (स्थिर अक्षर *fmt, अचिन्हित पूर्णांक x)
{
	ख_लिखो (मानक_निकास, fmt, x);
}

व्योम out_str (स्थिर अक्षर *fmt, स्थिर अक्षर str[])
{
	ख_लिखो (मानक_निकास,fmt, str);
}

व्योम out_str_dec (स्थिर अक्षर *fmt, स्थिर अक्षर str[], पूर्णांक n)
{
	ख_लिखो (मानक_निकास,fmt, str, n);
}

व्योम outc (पूर्णांक c)
{
	ख_अक्षर_दो (c, मानक_निकास);
}

व्योम outn (स्थिर अक्षर *str)
{
	ख_माला_दो (str,मानक_निकास);
    ख_अक्षर_दो('\n',मानक_निकास);
}

/** Print "m4_define( [[def]], [[val]])m4_dnl\n".
 * @param def The m4 symbol to define.
 * @param val The definition; may be NULL.
 */
व्योम out_m4_define (स्थिर अक्षर* def, स्थिर अक्षर* val)
{
    स्थिर अक्षर * fmt = "m4_define( [[%s]], [[%s]])m4_dnl\n";
    ख_लिखो(मानक_निकास, fmt, def, val?val:"");
}


/* readable_form - return the the human-readable form of a character
 *
 * The returned string is in static storage.
 */

अक्षर   *readable_form (पूर्णांक c)
{
	अटल अक्षर rform[20];

	अगर ((c >= 0 && c < 32) || c >= 127) {
		चयन (c) {
		हाल '\b':
			वापस "\\b";
		हाल '\f':
			वापस "\\f";
		हाल '\n':
			वापस "\\n";
		हाल '\r':
			वापस "\\r";
		हाल '\t':
			वापस "\\t";
		हाल '\a':
			वापस "\\a";
		हाल '\v':
			वापस "\\v";
		शेष:
			अगर(env.trace_hex)
				snprintf (rform, माप(rform), "\\x%.2x", (अचिन्हित पूर्णांक) c);
			अन्यथा
				snprintf (rform, माप(rform), "\\%.3o", (अचिन्हित पूर्णांक) c);
			वापस rform;
		}
	}

	अन्यथा अगर (c == ' ')
		वापस "' '";

	अन्यथा {
		rform[0] = (अक्षर) c;
		rform[1] = '\0';

		वापस rform;
	}
}


/* reallocate_array - increase the size of a dynamic array */

व्योम   *reallocate_array (व्योम *array, पूर्णांक आकार, माप_प्रकार element_आकार)
{
	व्योम *new_array;
#अगर_घोषित HAVE_REALLOCARR
	new_array = array;
	अगर (reallocarr(&new_array, (माप_प्रकार) आकार, element_आकार)) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#अन्यथा
# ifdef HAVE_REALLOCARRAY
	new_array = reallocarray(array, (माप_प्रकार) आकार, element_आकार);
# अन्यथा
	/* Do manual overflow detection */
	माप_प्रकार अंक_bytes = (माप_प्रकार) आकार * element_आकार;
	new_array = (आकार && आकार_MAX / (माप_प्रकार) आकार < element_आकार) ? शून्य :
		पुनः_स्मृति(array, अंक_bytes);
# endif
	अगर (!new_array) {
		flexfatal ((array) ?
			_("attempt to increase array size failed") :
			/* Function name is allocate_array() because of
			 * compatibility (for translations): */
			_("memory allocation failed in allocate_array()"));
	}
#पूर्ण_अगर
	वापस new_array;
}


/* transition_struct_out - output a yy_trans_info structure
 *
 * outputs the yy_trans_info structure with the two elements, element_v and
 * element_n.  Formats the output with spaces and carriage returns.
 */

व्योम transition_struct_out (पूर्णांक element_v, पूर्णांक element_n)
{

	/* short circuit any output */
	अगर (!gentables)
		वापस;

	out_dec2 ("M4_HOOK_TABLE_OPENER[[%4d]],[[%4d]]M4_HOOK_TABLE_CONTINUE", element_v, element_n);
	outc ('\n');

	datapos += TRANS_STRUCT_PRINT_लंबाई;

	अगर (datapos >= 79 - TRANS_STRUCT_PRINT_लंबाई) {
		outc ('\n');

		अगर (++dataline % 10 == 0)
			outc ('\n');

		datapos = 0;
	}
}


/* The following is only needed when building flex's parser using certain
 * broken versions of bison.
 *
 * XXX: this is should go soon
 */
व्योम   *yy_flex_xmalloc (पूर्णांक आकार)
{
	व्योम   *परिणाम;

	परिणाम = दो_स्मृति((माप_प्रकार) आकार);
	अगर (!परिणाम)
		flexfatal (_
			   ("memory allocation failed in yy_flex_xmalloc()"));

	वापस परिणाम;
}


/* Remove all '\n' and '\r' characters, if any, from the end of str.
 * str can be any null-terminated string, or NULL.
 * returns str. */
अक्षर   *chomp (अक्षर *str)
{
	अक्षर   *p = str;

	अगर (!str || !*str)	/* s is null or empty string */
		वापस str;

	/* find end of string minus one */
	जबतक (*p)
		++p;
	--p;

	/* eat newlines */
	जबतक (p >= str && (*p == '\r' || *p == '\n'))
		*p-- = 0;
	वापस str;
}

व्योम comment(स्थिर अक्षर *txt)
{
	अक्षर buf[MAXLINE];
	bool eol;

	म_नकलन(buf, txt, MAXLINE-1);
	eol = buf[म_माप(buf)-1] == '\n';

	अगर (eol)
		buf[म_माप(buf)-1] = '\0';
	out_str("M4_HOOK_COMMENT_OPEN [[%s]] M4_HOOK_COMMENT_CLOSE", buf);
	अगर (eol)
		outc ('\n');
}


