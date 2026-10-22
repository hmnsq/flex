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

#ಅನ್ತರ್ಭಾವ "flexdef.h"

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
ರಚನೆ Buf userdef_buf;		/**< for user #definitions triggered by cmd-line. */
ರಚನೆ Buf ತುದಿ_buf;             /**< contains %top code. String buffer. */

/* Append a "%s" formatted string to a string buffer */
ರಚನೆ Buf *buf_prints (ರಚನೆ Buf *buf, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s)
{
	ಅಕ್ಷರ   *t;
	size_t tsz;

	tsz = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(fmt) + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(s) + 1;
	t = ಸ್ಮರಣೆ_ಕೊಡು(tsz);
	ಆದರೆ (!t)
	    flexfatal (_("Allocation of buffer to print string failed"));
	snprintf (t, tsz, fmt, s);
	buf = buf_strappend (buf, t);
	ಬಿಡುಗಡೆ(t);
	ಹಿಂತಿರುಗಿ buf;
}

/* Appends n characters in str to buf. */
ರಚನೆ Buf *buf_strnappend (ರಚನೆ Buf *buf, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಪೂರ್ಣಾಂಕ n)
{
	buf_append (buf, str, n + 1);

	/* "undo" the '\0' character that buf_append() already copied. */
	buf->nelts--;

	ಹಿಂತಿರುಗಿ buf;
}

/* Appends characters in str to buf. */
ರಚನೆ Buf *buf_strappend (ರಚನೆ Buf *buf, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
	ಹಿಂತಿರುಗಿ buf_strnappend (buf, str, (ಪೂರ್ಣಾಂಕ) ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (str));
}

/* create buf with 0 elements, each of size elem_size. */
ಶೂನ್ಯ buf_init (ರಚನೆ Buf *buf, size_t elem_ಗಾತ್ರ)
{
	buf->elts = ಖಾಲಿ;
	buf->nelts = 0;
	buf->elt_ಗಾತ್ರ = elem_ಗಾತ್ರ;
	buf->nmax = 0;
}

/* frees memory */
ಶೂನ್ಯ buf_destroy (ರಚನೆ Buf *buf)
{
	ಆದರೆ (buf) {
		ಬಿಡುಗಡೆ(buf->elts);
		buf->elts = ಖಾಲಿ;
	}
}


/* appends ptr[] to buf, grow if necessary.
 * n_elem is number of elements in ptr[], NOT bytes.
 * returns buf.
 * We grow by mod(512) boundaries.
 */

ರಚನೆ Buf *buf_append (ರಚನೆ Buf *buf, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ptr, ಪೂರ್ಣಾಂಕ n_elem)
{
	ಪೂರ್ಣಾಂಕ     n_alloc = 0;

	ಆದರೆ (!ptr || n_elem == 0)
		ಹಿಂತಿರುಗಿ buf;

	/* May need to alloc more. */
	ಆದರೆ (n_elem + buf->nelts > buf->nmax) {

		/* exact count needed... */
		n_alloc = n_elem + buf->nelts;

		/* ...plus some extra */
		ಆದರೆ ((((size_t) n_alloc * buf->elt_ಗಾತ್ರ) % 512) != 0
		    && buf->elt_ಗಾತ್ರ < 512)
			n_alloc += (ಪೂರ್ಣಾಂಕ)
				((512 -
				 (((size_t) n_alloc * buf->elt_ಗಾತ್ರ) % 512)) /
				buf->elt_ಗಾತ್ರ);

		ಆದರೆ (!buf->elts)
			buf->elts =
				allocate_array ((ಪೂರ್ಣಾಂಕ) n_alloc, buf->elt_ಗಾತ್ರ);
		ಇಲ್ಲದಿದ್ದರೆ
			buf->elts =
				reallocate_array (buf->elts, (ಪೂರ್ಣಾಂಕ) n_alloc,
						  buf->elt_ಗಾತ್ರ);

		buf->nmax = n_alloc;
	}

	ಸ್ಮರಣೆ_ನಕಲು ((ಅಕ್ಷರ *) buf->elts + (size_t) buf->nelts * buf->elt_ಗಾತ್ರ, ptr,
		(size_t) n_elem * buf->elt_ಗಾತ್ರ);
	buf->nelts += n_elem;

	ಹಿಂತಿರುಗಿ buf;
}

/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
