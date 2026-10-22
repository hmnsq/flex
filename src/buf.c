/* flex - tool to generate fast lexical analyzers */

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

/* Take note: The buffer object is sometimes used as a String buffer (one
 * continuous string), and sometimes used as a list of strings, usually line by
 * line.
 * 
 * The type is specified in buf_init by the elt_size. If the elt_size is
 * sizeof(char), then the buffer should be treated as string buffer. If the
 * elt_size is sizeof(char*), then the buffer should be treated as a list of
 * strings.
 *
 * Certain functions are only appropriate for one type or the other. 
 */

/* global buffers. */
संरचना Buf userdef_buf;		/**< for user #definitions triggered by cmd-line. */
संरचना Buf शीर्ष_buf;             /**< contains %top code. String buffer. */

/* Append a "%s" formatted string to a string buffer */
संरचना Buf *buf_prints (संरचना Buf *buf, स्थिरांक अक्षर *fmt, स्थिरांक अक्षर *s)
{
	अक्षर   *t;
	माप_प्रकार tsz;

	tsz = म_माप(fmt) + म_माप(s) + 1;
	t = दो_स्मृति(tsz);
	जर (!t)
	    flexfatal (_("Allocation of buffer to print string failed"));
	snprintf (t, tsz, fmt, s);
	buf = buf_strappend (buf, t);
	मुक्त(t);
	परत buf;
}

/* Appends n characters in str to buf. */
संरचना Buf *buf_strnappend (संरचना Buf *buf, स्थिरांक अक्षर *str, पूर्णांक n)
{
	buf_append (buf, str, n + 1);

	/* "undo" the '\0' character that buf_append() already copied. */
	buf->nelts--;

	परत buf;
}

/* Appends characters in str to buf. */
संरचना Buf *buf_strappend (संरचना Buf *buf, स्थिरांक अक्षर *str)
{
	परत buf_strnappend (buf, str, (पूर्णांक) म_माप (str));
}

/* create buf with 0 elements, each of size elem_size. */
शून्य buf_init (संरचना Buf *buf, माप_प्रकार elem_size)
{
	buf->elts = रिक्त;
	buf->nelts = 0;
	buf->elt_size = elem_size;
	buf->nmax = 0;
}

/* frees memory */
शून्य buf_destroy (संरचना Buf *buf)
{
	जर (buf) {
		मुक्त(buf->elts);
		buf->elts = रिक्त;
	}
}


/* appends ptr[] to buf, grow if necessary.
 * n_elem is number of elements in ptr[], NOT bytes.
 * returns buf.
 * We grow by mod(512) boundaries.
 */

संरचना Buf *buf_append (संरचना Buf *buf, स्थिरांक शून्य *ptr, पूर्णांक n_elem)
{
	पूर्णांक     n_alloc = 0;

	जर (!ptr || n_elem == 0)
		परत buf;

	/* May need to alloc more. */
	जर (n_elem + buf->nelts > buf->nmax) {

		/* exact count needed... */
		n_alloc = n_elem + buf->nelts;

		/* ...plus some extra */
		जर ((((माप_प्रकार) n_alloc * buf->elt_size) % 512) != 0
		    && buf->elt_size < 512)
			n_alloc += (पूर्णांक)
				((512 -
				 (((माप_प्रकार) n_alloc * buf->elt_size) % 512)) /
				buf->elt_size);

		जर (!buf->elts)
			buf->elts =
				allocate_array ((पूर्णांक) n_alloc, buf->elt_size);
		अन्यथा
			buf->elts =
				reallocate_array (buf->elts, (पूर्णांक) n_alloc,
						  buf->elt_size);

		buf->nmax = n_alloc;
	}

	स_नकल ((अक्षर *) buf->elts + (माप_प्रकार) buf->nelts * buf->elt_size, ptr,
		(माप_प्रकार) n_elem * buf->elt_size);
	buf->nelts += n_elem;

	परत buf;
}

/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
