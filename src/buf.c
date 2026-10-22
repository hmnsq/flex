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

#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"

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
ਬਣਤਰ Buf userdef_buf;		/**< for user #definitions triggered by cmd-line. */
ਬਣਤਰ Buf ਸਿਖਰ_buf;             /**< contains %top code. String buffer. */

/* Append a "%s" formatted string to a string buffer */
ਬਣਤਰ Buf *buf_prints (ਬਣਤਰ Buf *buf, ਅਚਲ ਅੱਖਰ *fmt, ਅਚਲ ਅੱਖਰ *s)
{
	ਅੱਖਰ   *t;
	size_t tsz;

	tsz = ਲੜੀ_ਲੰਬਾਈ(fmt) + ਲੜੀ_ਲੰਬਾਈ(s) + 1;
	t = ਸਮ੍ਰਿਤੀ_ਦਿਓ(tsz);
	ਜੇ (!t)
	    flexfatal (_("Allocation of buffer to print string failed"));
	snprintf (t, tsz, fmt, s);
	buf = buf_strappend (buf, t);
	ਮੁਕਤ(t);
	ਵਾਪਸ buf;
}

/* Appends n characters in str to buf. */
ਬਣਤਰ Buf *buf_strnappend (ਬਣਤਰ Buf *buf, ਅਚਲ ਅੱਖਰ *str, ਪੂਰਨ n)
{
	buf_append (buf, str, n + 1);

	/* "undo" the '\0' character that buf_append() already copied. */
	buf->nelts--;

	ਵਾਪਸ buf;
}

/* Appends characters in str to buf. */
ਬਣਤਰ Buf *buf_strappend (ਬਣਤਰ Buf *buf, ਅਚਲ ਅੱਖਰ *str)
{
	ਵਾਪਸ buf_strnappend (buf, str, (ਪੂਰਨ) ਲੜੀ_ਲੰਬਾਈ (str));
}

/* create buf with 0 elements, each of size elem_size. */
ਖਾਲੀ buf_init (ਬਣਤਰ Buf *buf, size_t elem_ਮਾਪ)
{
	buf->elts = ਨਿਰਾ;
	buf->nelts = 0;
	buf->elt_ਮਾਪ = elem_ਮਾਪ;
	buf->nmax = 0;
}

/* frees memory */
ਖਾਲੀ buf_destroy (ਬਣਤਰ Buf *buf)
{
	ਜੇ (buf) {
		ਮੁਕਤ(buf->elts);
		buf->elts = ਨਿਰਾ;
	}
}


/* appends ptr[] to buf, grow if necessary.
 * n_elem is number of elements in ptr[], NOT bytes.
 * returns buf.
 * We grow by mod(512) boundaries.
 */

ਬਣਤਰ Buf *buf_append (ਬਣਤਰ Buf *buf, ਅਚਲ ਖਾਲੀ *ptr, ਪੂਰਨ n_elem)
{
	ਪੂਰਨ     n_alloc = 0;

	ਜੇ (!ptr || n_elem == 0)
		ਵਾਪਸ buf;

	/* May need to alloc more. */
	ਜੇ (n_elem + buf->nelts > buf->nmax) {

		/* exact count needed... */
		n_alloc = n_elem + buf->nelts;

		/* ...plus some extra */
		ਜੇ ((((size_t) n_alloc * buf->elt_ਮਾਪ) % 512) != 0
		    && buf->elt_ਮਾਪ < 512)
			n_alloc += (ਪੂਰਨ)
				((512 -
				 (((size_t) n_alloc * buf->elt_ਮਾਪ) % 512)) /
				buf->elt_ਮਾਪ);

		ਜੇ (!buf->elts)
			buf->elts =
				allocate_array ((ਪੂਰਨ) n_alloc, buf->elt_ਮਾਪ);
		ਨਹੀਂਤਾਂ
			buf->elts =
				reallocate_array (buf->elts, (ਪੂਰਨ) n_alloc,
						  buf->elt_ਮਾਪ);

		buf->nmax = n_alloc;
	}

	ਸਮ੍ਰਿਤੀ_ਨਕਲ ((ਅੱਖਰ *) buf->elts + (size_t) buf->nelts * buf->elt_ਮਾਪ, ptr,
		(size_t) n_elem * buf->elt_ਮਾਪ);
	buf->nelts += n_elem;

	ਵਾਪਸ buf;
}

/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
