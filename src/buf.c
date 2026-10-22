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

#অন্তর্ভাব "flexdef.h"

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
কাঠামো Buf userdef_buf;		/**< for user #definitions triggered by cmd-line. */
কাঠামো Buf শীর্ষ_buf;             /**< contains %top code. String buffer. */

/* Append a "%s" formatted string to a string buffer */
কাঠামো Buf *buf_prints (কাঠামো Buf *buf, ধ্রুবক অক্ষর *fmt, ধ্রুবক অক্ষর *s)
{
	অক্ষর   *t;
	size_t tsz;

	tsz = strlen(fmt) + strlen(s) + 1;
	t = malloc(tsz);
	যদি (!t)
	    flexfatal (_("Allocation of buffer to print string failed"));
	snprintf (t, tsz, fmt, s);
	buf = buf_strappend (buf, t);
	মুক্ত(t);
	ফেরত buf;
}

/* Appends n characters in str to buf. */
কাঠামো Buf *buf_strnappend (কাঠামো Buf *buf, ধ্রুবক অক্ষর *str, পূর্ণসংখ্যা n)
{
	buf_append (buf, str, n + 1);

	/* "undo" the '\0' character that buf_append() already copied. */
	buf->nelts--;

	ফেরত buf;
}

/* Appends characters in str to buf. */
কাঠামো Buf *buf_strappend (কাঠামো Buf *buf, ধ্রুবক অক্ষর *str)
{
	ফেরত buf_strnappend (buf, str, (পূর্ণসংখ্যা) strlen (str));
}

/* create buf with 0 elements, each of size elem_size. */
শূন্য buf_init (কাঠামো Buf *buf, size_t elem_আকার)
{
	buf->elts = ফাঁকা;
	buf->nelts = 0;
	buf->elt_আকার = elem_আকার;
	buf->nmax = 0;
}

/* frees memory */
শূন্য buf_destroy (কাঠামো Buf *buf)
{
	যদি (buf) {
		মুক্ত(buf->elts);
		buf->elts = ফাঁকা;
	}
}


/* appends ptr[] to buf, grow if necessary.
 * n_elem is number of elements in ptr[], NOT bytes.
 * returns buf.
 * We grow by mod(512) boundaries.
 */

কাঠামো Buf *buf_append (কাঠামো Buf *buf, ধ্রুবক শূন্য *ptr, পূর্ণসংখ্যা n_elem)
{
	পূর্ণসংখ্যা     n_alloc = 0;

	যদি (!ptr || n_elem == 0)
		ফেরত buf;

	/* May need to alloc more. */
	যদি (n_elem + buf->nelts > buf->nmax) {

		/* exact count needed... */
		n_alloc = n_elem + buf->nelts;

		/* ...plus some extra */
		যদি ((((size_t) n_alloc * buf->elt_আকার) % 512) != 0
		    && buf->elt_আকার < 512)
			n_alloc += (পূর্ণসংখ্যা)
				((512 -
				 (((size_t) n_alloc * buf->elt_আকার) % 512)) /
				buf->elt_আকার);

		যদি (!buf->elts)
			buf->elts =
				allocate_array ((পূর্ণসংখ্যা) n_alloc, buf->elt_আকার);
		অন্যথা
			buf->elts =
				reallocate_array (buf->elts, (পূর্ণসংখ্যা) n_alloc,
						  buf->elt_আকার);

		buf->nmax = n_alloc;
	}

	memcpy ((অক্ষর *) buf->elts + (size_t) buf->nelts * buf->elt_আকার, ptr,
		(size_t) n_elem * buf->elt_আকার);
	buf->nelts += n_elem;

	ফেরত buf;
}

/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
