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

#شامل "flexdef.h"

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
ساخت Buf userdef_buf;		/**< for user #definitions triggered by cmd-line. */
ساخت Buf چوٹی_buf;             /**< contains %top code. String buffer. */

/* Append a "%s" formatted string to a string buffer */
ساخت Buf *buf_prints (ساخت Buf *buf, ثابت حرف *fmt, ثابت حرف *s)
{
	حرف   *t;
	size_t tsz;

	tsz = لڑی_لمبائی(fmt) + لڑی_لمبائی(s) + 1;
	t = حافظہ_دو(tsz);
	اگر (!t)
	    flexfatal (_("Allocation of buffer to print string failed"));
	snprintf (t, tsz, fmt, s);
	buf = buf_strappend (buf, t);
	آزاد(t);
	واپس buf;
}

/* Appends n characters in str to buf. */
ساخت Buf *buf_strnappend (ساخت Buf *buf, ثابت حرف *str, صحیح n)
{
	buf_append (buf, str, n + 1);

	/* "undo" the '\0' character that buf_append() already copied. */
	buf->nelts--;

	واپس buf;
}

/* Appends characters in str to buf. */
ساخت Buf *buf_strappend (ساخت Buf *buf, ثابت حرف *str)
{
	واپس buf_strnappend (buf, str, (صحیح) لڑی_لمبائی (str));
}

/* create buf with 0 elements, each of size elem_size. */
خالی buf_init (ساخت Buf *buf, size_t elem_سائز)
{
	buf->elts = تہی;
	buf->nelts = 0;
	buf->elt_سائز = elem_سائز;
	buf->nmax = 0;
}

/* frees memory */
خالی buf_destroy (ساخت Buf *buf)
{
	اگر (buf) {
		آزاد(buf->elts);
		buf->elts = تہی;
	}
}


/* appends ptr[] to buf, grow if necessary.
 * n_elem is number of elements in ptr[], NOT bytes.
 * returns buf.
 * We grow by mod(512) boundaries.
 */

ساخت Buf *buf_append (ساخت Buf *buf, ثابت خالی *ptr, صحیح n_elem)
{
	صحیح     n_alloc = 0;

	اگر (!ptr || n_elem == 0)
		واپس buf;

	/* May need to alloc more. */
	اگر (n_elem + buf->nelts > buf->nmax) {

		/* exact count needed... */
		n_alloc = n_elem + buf->nelts;

		/* ...plus some extra */
		اگر ((((size_t) n_alloc * buf->elt_سائز) % 512) != 0
		    && buf->elt_سائز < 512)
			n_alloc += (صحیح)
				((512 -
				 (((size_t) n_alloc * buf->elt_سائز) % 512)) /
				buf->elt_سائز);

		اگر (!buf->elts)
			buf->elts =
				allocate_array ((صحیح) n_alloc, buf->elt_سائز);
		ورنہ
			buf->elts =
				reallocate_array (buf->elts, (صحیح) n_alloc,
						  buf->elt_سائز);

		buf->nmax = n_alloc;
	}

	حافظہ_نقل ((حرف *) buf->elts + (size_t) buf->nelts * buf->elt_سائز, ptr,
		(size_t) n_elem * buf->elt_سائز);
	buf->nelts += n_elem;

	واپس buf;
}

/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
