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

#ضمن "flexdef.h"

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
بنية Buf userdef_buf;		/**< for user #definitions triggered by cmd-line. */
بنية Buf top_buf;             /**< contains %top code. String buffer. */

/* Append a "%s" formatted string to a string buffer */
بنية Buf *buf_prints (بنية Buf *buf, ثابت حرف *fmt, ثابت حرف *s)
{
	حرف   *t;
	size_t tsz;

	tsz = strlen(fmt) + strlen(s) + 1;
	t = malloc(tsz);
	אם (!t)
	    flexfatal (_("Allocation of buffer to print string failed"));
	snprintf (t, tsz, fmt, s);
	buf = buf_strappend (buf, t);
	حرر(t);
	החזר buf;
}

/* Appends n characters in str to buf. */
بنية Buf *buf_strnappend (بنية Buf *buf, ثابت حرف *str, صحيح n)
{
	buf_append (buf, str, n + 1);

	/* "undo" the '\0' character that buf_append() already copied. */
	buf->nelts--;

	החזר buf;
}

/* Appends characters in str to buf. */
بنية Buf *buf_strappend (بنية Buf *buf, ثابت حرف *str)
{
	החזר buf_strnappend (buf, str, (صحيح) strlen (str));
}

/* create buf with 0 elements, each of size elem_size. */
فراغ buf_init (بنية Buf *buf, size_t elem_size)
{
	buf->elts = عدم;
	buf->nelts = 0;
	buf->elt_size = elem_size;
	buf->nmax = 0;
}

/* frees memory */
فراغ buf_destroy (بنية Buf *buf)
{
	אם (buf) {
		حرر(buf->elts);
		buf->elts = عدم;
	}
}


/* appends ptr[] to buf, grow if necessary.
 * n_elem is number of elements in ptr[], NOT bytes.
 * returns buf.
 * We grow by mod(512) boundaries.
 */

بنية Buf *buf_append (بنية Buf *buf, ثابت فراغ *ptr, صحيح n_elem)
{
	صحيح     n_alloc = 0;

	אם (!ptr || n_elem == 0)
		החזר buf;

	/* May need to alloc more. */
	אם (n_elem + buf->nelts > buf->nmax) {

		/* exact count needed... */
		n_alloc = n_elem + buf->nelts;

		/* ...plus some extra */
		אם ((((size_t) n_alloc * buf->elt_size) % 512) != 0
		    && buf->elt_size < 512)
			n_alloc += (صحيح)
				((512 -
				 (((size_t) n_alloc * buf->elt_size) % 512)) /
				buf->elt_size);

		אם (!buf->elts)
			buf->elts =
				allocate_array ((صحيح) n_alloc, buf->elt_size);
		אחרת
			buf->elts =
				reallocate_array (buf->elts, (صحيح) n_alloc,
						  buf->elt_size);

		buf->nmax = n_alloc;
	}

	memcpy ((حرف *) buf->elts + (size_t) buf->nelts * buf->elt_size, ptr,
		(size_t) n_elem * buf->elt_size);
	buf->nelts += n_elem;

	החזר buf;
}

/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
