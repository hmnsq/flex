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

#অন্তর্ভাৱ "flexdef.h"

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
সংরচনা Buf userdef_buf;		/**< for user #definitions triggered by cmd-line. */
সংরচনা Buf শীৰ্ষ_buf;             /**< contains %top code. String buffer. */

/* Append a "%s" formatted string to a string buffer */
সংরচনা Buf *buf_prints (সংরচনা Buf *buf, ধ্রুৱ ৱর্ণ *fmt, ধ্রুৱ ৱর্ণ *s)
{
	ৱর্ণ   *t;
	size_t tsz;

	tsz = strlen(fmt) + strlen(s) + 1;
	t = malloc(tsz);
	যদি (!t)
	    flexfatal (_("Allocation of buffer to print string failed"));
	snprintf (t, tsz, fmt, s);
	buf = buf_strappend (buf, t);
	মুক্ত(t);
	ঘূৰাই buf;
}

/* Appends n characters in str to buf. */
সংরচনা Buf *buf_strnappend (সংরচনা Buf *buf, ধ্রুৱ ৱর্ণ *str, পূর্ণাঙ্ক n)
{
	buf_append (buf, str, n + 1);

	/* "undo" the '\0' character that buf_append() already copied. */
	buf->nelts--;

	ঘূৰাই buf;
}

/* Appends characters in str to buf. */
সংরচনা Buf *buf_strappend (সংরচনা Buf *buf, ধ্রুৱ ৱর্ণ *str)
{
	ঘূৰাই buf_strnappend (buf, str, (পূর্ণাঙ্ক) strlen (str));
}

/* create buf with 0 elements, each of size elem_size. */
শূন্য buf_init (সংরচনা Buf *buf, size_t elem_size)
{
	buf->elts = রিক্ত;
	buf->nelts = 0;
	buf->elt_size = elem_size;
	buf->nmax = 0;
}

/* frees memory */
শূন্য buf_destroy (সংরচনা Buf *buf)
{
	যদি (buf) {
		মুক্ত(buf->elts);
		buf->elts = রিক্ত;
	}
}


/* appends ptr[] to buf, grow if necessary.
 * n_elem is number of elements in ptr[], NOT bytes.
 * returns buf.
 * We grow by mod(512) boundaries.
 */

সংরচনা Buf *buf_append (সংরচনা Buf *buf, ধ্রুৱ শূন্য *ptr, পূর্ণাঙ্ক n_elem)
{
	পূর্ণাঙ্ক     n_alloc = 0;

	যদি (!ptr || n_elem == 0)
		ঘূৰাই buf;

	/* May need to alloc more. */
	যদি (n_elem + buf->nelts > buf->nmax) {

		/* exact count needed... */
		n_alloc = n_elem + buf->nelts;

		/* ...plus some extra */
		যদি ((((size_t) n_alloc * buf->elt_size) % 512) != 0
		    && buf->elt_size < 512)
			n_alloc += (পূর্ণাঙ্ক)
				((512 -
				 (((size_t) n_alloc * buf->elt_size) % 512)) /
				buf->elt_size);

		যদি (!buf->elts)
			buf->elts =
				allocate_array ((পূর্ণাঙ্ক) n_alloc, buf->elt_size);
		অন্যথা
			buf->elts =
				reallocate_array (buf->elts, (পূর্ণাঙ্ক) n_alloc,
						  buf->elt_size);

		buf->nmax = n_alloc;
	}

	memcpy ((ৱর্ণ *) buf->elts + (size_t) buf->nelts * buf->elt_size, ptr,
		(size_t) n_elem * buf->elt_size);
	buf->nelts += n_elem;

	ঘূৰাই buf;
}

/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
