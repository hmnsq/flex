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

#అన్తర్భావ "flexdef.h"

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
నిర్మాణం Buf userdef_buf;		/**< for user #definitions triggered by cmd-line. */
నిర్మాణం Buf శిఖరం_buf;             /**< contains %top code. String buffer. */

/* Append a "%s" formatted string to a string buffer */
నిర్మాణం Buf *buf_prints (నిర్మాణం Buf *buf, స్థిరరాశి అక్షరం *fmt, స్థిరరాశి అక్షరం *s)
{
	అక్షరం   *t;
	size_t tsz;

	tsz = అక్షరశ్రేణి_పొడవు(fmt) + అక్షరశ్రేణి_పొడవు(s) + 1;
	t = జ్ఞాపకం_ఇవ్వు(tsz);
	ఒకవేళ (!t)
	    flexfatal (_("Allocation of buffer to print string failed"));
	snprintf (t, tsz, fmt, s);
	buf = buf_strappend (buf, t);
	విడుదల(t);
	తిరిగి buf;
}

/* Appends n characters in str to buf. */
నిర్మాణం Buf *buf_strnappend (నిర్మాణం Buf *buf, స్థిరరాశి అక్షరం *str, పూర్ణాంకం n)
{
	buf_append (buf, str, n + 1);

	/* "undo" the '\0' character that buf_append() already copied. */
	buf->nelts--;

	తిరిగి buf;
}

/* Appends characters in str to buf. */
నిర్మాణం Buf *buf_strappend (నిర్మాణం Buf *buf, స్థిరరాశి అక్షరం *str)
{
	తిరిగి buf_strnappend (buf, str, (పూర్ణాంకం) అక్షరశ్రేణి_పొడవు (str));
}

/* create buf with 0 elements, each of size elem_size. */
శూన్య buf_init (నిర్మాణం Buf *buf, size_t elem_కొలత)
{
	buf->elts = ఖాళీ;
	buf->nelts = 0;
	buf->elt_కొలత = elem_కొలత;
	buf->nmax = 0;
}

/* frees memory */
శూన్య buf_destroy (నిర్మాణం Buf *buf)
{
	ఒకవేళ (buf) {
		విడుదల(buf->elts);
		buf->elts = ఖాళీ;
	}
}


/* appends ptr[] to buf, grow if necessary.
 * n_elem is number of elements in ptr[], NOT bytes.
 * returns buf.
 * We grow by mod(512) boundaries.
 */

నిర్మాణం Buf *buf_append (నిర్మాణం Buf *buf, స్థిరరాశి శూన్య *ptr, పూర్ణాంకం n_elem)
{
	పూర్ణాంకం     n_alloc = 0;

	ఒకవేళ (!ptr || n_elem == 0)
		తిరిగి buf;

	/* May need to alloc more. */
	ఒకవేళ (n_elem + buf->nelts > buf->nmax) {

		/* exact count needed... */
		n_alloc = n_elem + buf->nelts;

		/* ...plus some extra */
		ఒకవేళ ((((size_t) n_alloc * buf->elt_కొలత) % 512) != 0
		    && buf->elt_కొలత < 512)
			n_alloc += (పూర్ణాంకం)
				((512 -
				 (((size_t) n_alloc * buf->elt_కొలత) % 512)) /
				buf->elt_కొలత);

		ఒకవేళ (!buf->elts)
			buf->elts =
				allocate_array ((పూర్ణాంకం) n_alloc, buf->elt_కొలత);
		లేకపోతే
			buf->elts =
				reallocate_array (buf->elts, (పూర్ణాంకం) n_alloc,
						  buf->elt_కొలత);

		buf->nmax = n_alloc;
	}

	జ్ఞాపకం_నకలు ((అక్షరం *) buf->elts + (size_t) buf->nelts * buf->elt_కొలత, ptr,
		(size_t) n_elem * buf->elt_కొలత);
	buf->nelts += n_elem;

	తిరిగి buf;
}

/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
