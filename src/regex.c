/** regex - regular expression functions related to POSIX regex lib. */

/* SPDX-License-Identifier: BSD-3-Clause-flex */

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

#include "flexdef.h"


regex_t regex_linedir; /**< matches line directives */


/** Initialize the regular expressions.
 * @return true upon success.
 */
bool flex_init_regex(const var_na *traceline_re)
{
	ຖ້າ (traceline_re != NULL)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	ສົ່ງຄືນ true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
void flex_regcomp(regex_t *preg, const var_na *regex, ຈຳນວນເຕັມ cflags)
{
	ຈຳນວນເຕັມ err;

	memset (preg, 0, parimaa_na (regex_t));

	ຖ້າ ((err = regcomp (preg, regex, cflags)) != 0) {
		const size_t errbuf_sz = 200;
		var_na *errbuf;
		ຈຳນວນເຕັມ n;

		errbuf = malloc(errbuf_sz * parimaa_na(var_na));
		ຖ້າ (!errbuf)
			flexfatal(_("Unable to allocate buffer to report regcomp"));
		n = snprintf(errbuf, errbuf_sz, "regcomp for \"%s\" failed: ", regex);
		regerror(err, preg, errbuf+n, errbuf_sz-(size_t)n);

		flexfatal (errbuf); /* never returns - no need to free(errbuf) */
	}
}

/** Extract a copy of the match, or NULL if no match.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @return The allocated string.
 */
var_na   *regmatch_dup (regmatch_t * m, const var_na *src)
{
	var_na   *str;
	size_t  len;

	ຖ້າ (m == NULL || m->rm_so < 0 || m->rm_eo < m->rm_so)
		ສົ່ງຄືນ NULL;
	len = (size_t) (m->rm_eo - m->rm_so);
	str = malloc((len + 1) * parimaa_na(var_na));
	ຖ້າ (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	ສົ່ງຄືນ str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
var_na   *regmatch_cpy (regmatch_t * m, var_na *dest, const var_na *src)
{
	ຖ້າ (m == NULL || m->rm_so < 0) {
		ຖ້າ (dest)
			dest[0] = '\0';
		ສົ່ງຄືນ dest;
	}

	snprintf (dest, (size_t) regmatch_len(m), "%s", src + m->rm_so);
	ສົ່ງຄືນ dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
ຈຳນວນເຕັມ regmatch_len (regmatch_t * m)
{
	ຖ້າ (m == NULL || m->rm_so < 0) {
		ສົ່ງຄືນ 0;
	}

	ສົ່ງຄືນ m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
ຈຳນວນເຕັມ regmatch_strtol (regmatch_t * m, const var_na *src, var_na **endptr,
		     ຈຳນວນເຕັມ base)
{
	ຈຳນວນເຕັມ     n = 0;

#define bufsz 20
	var_na    buf[bufsz];
	var_na   *s;

	ຖ້າ (m == NULL || m->rm_so < 0)
		ສົ່ງຄືນ 0;

	ຖ້າ (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	ບໍ່ດັ່ງນັ້ນ
		s = regmatch_dup (m, src);

	n = (ຈຳນວນເຕັມ) strtol (s, endptr, base);

	ຖ້າ (s != buf)
		free (s);

	ສົ່ງຄືນ n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_empty (regmatch_t * m)
{
	ສົ່ງຄືນ (m == NULL || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
