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

#அந்தர்பாவ "flexdef.h"

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
கட்டமைப்பு Buf userdef_buf;		/**< for user #definitions triggered by cmd-line. */
கட்டமைப்பு Buf உச்சி_buf;             /**< contains %top code. String buffer. */

/* Append a "%s" formatted string to a string buffer */
கட்டமைப்பு Buf *buf_prints (கட்டமைப்பு Buf *buf, மாறிலி எழுத்து *fmt, மாறிலி எழுத்து *s)
{
	எழுத்து   *t;
	size_t tsz;

	tsz = strlen(fmt) + strlen(s) + 1;
	t = malloc(tsz);
	எனில் (!t)
	    flexfatal (_("Allocation of buffer to print string failed"));
	snprintf (t, tsz, fmt, s);
	buf = buf_strappend (buf, t);
	விடுவி(t);
	திரும்பு buf;
}

/* Appends n characters in str to buf. */
கட்டமைப்பு Buf *buf_strnappend (கட்டமைப்பு Buf *buf, மாறிலி எழுத்து *str, முழு n)
{
	buf_append (buf, str, n + 1);

	/* "undo" the '\0' character that buf_append() already copied. */
	buf->nelts--;

	திரும்பு buf;
}

/* Appends characters in str to buf. */
கட்டமைப்பு Buf *buf_strappend (கட்டமைப்பு Buf *buf, மாறிலி எழுத்து *str)
{
	திரும்பு buf_strnappend (buf, str, (முழு) strlen (str));
}

/* create buf with 0 elements, each of size elem_size. */
வெறுமை buf_init (கட்டமைப்பு Buf *buf, size_t elem_size)
{
	buf->elts = வெற்று;
	buf->nelts = 0;
	buf->elt_size = elem_size;
	buf->nmax = 0;
}

/* frees memory */
வெறுமை buf_destroy (கட்டமைப்பு Buf *buf)
{
	எனில் (buf) {
		விடுவி(buf->elts);
		buf->elts = வெற்று;
	}
}


/* appends ptr[] to buf, grow if necessary.
 * n_elem is number of elements in ptr[], NOT bytes.
 * returns buf.
 * We grow by mod(512) boundaries.
 */

கட்டமைப்பு Buf *buf_append (கட்டமைப்பு Buf *buf, மாறிலி வெறுமை *ptr, முழு n_elem)
{
	முழு     n_alloc = 0;

	எனில் (!ptr || n_elem == 0)
		திரும்பு buf;

	/* May need to alloc more. */
	எனில் (n_elem + buf->nelts > buf->nmax) {

		/* exact count needed... */
		n_alloc = n_elem + buf->nelts;

		/* ...plus some extra */
		எனில் ((((size_t) n_alloc * buf->elt_size) % 512) != 0
		    && buf->elt_size < 512)
			n_alloc += (முழு)
				((512 -
				 (((size_t) n_alloc * buf->elt_size) % 512)) /
				buf->elt_size);

		எனில் (!buf->elts)
			buf->elts =
				allocate_array ((முழு) n_alloc, buf->elt_size);
		இல்லையெனில்
			buf->elts =
				reallocate_array (buf->elts, (முழு) n_alloc,
						  buf->elt_size);

		buf->nmax = n_alloc;
	}

	memcpy ((எழுத்து *) buf->elts + (size_t) buf->nelts * buf->elt_size, ptr,
		(size_t) n_elem * buf->elt_size);
	buf->nelts += n_elem;

	திரும்பு buf;
}

/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
