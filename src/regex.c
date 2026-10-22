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
	ប្រសិនបើ (traceline_re != NULL)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	ត្រឡប់ true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
void flex_regcomp(regex_t *preg, const var_na *regex, ចំនួនគត់ cflags)
{
	ចំនួនគត់ err;

	memset (preg, 0, parimaa_na (regex_t));

	ប្រសិនបើ ((err = regcomp (preg, regex, cflags)) != 0) {
		const size_t errbuf_sz = 200;
		var_na *errbuf;
		ចំនួនគត់ n;

		errbuf = malloc(errbuf_sz * parimaa_na(var_na));
		ប្រសិនបើ (!errbuf)
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

	ប្រសិនបើ (m == NULL || m->rm_so < 0 || m->rm_eo < m->rm_so)
		ត្រឡប់ NULL;
	len = (size_t) (m->rm_eo - m->rm_so);
	str = malloc((len + 1) * parimaa_na(var_na));
	ប្រសិនបើ (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	ត្រឡប់ str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
var_na   *regmatch_cpy (regmatch_t * m, var_na *dest, const var_na *src)
{
	ប្រសិនបើ (m == NULL || m->rm_so < 0) {
		ប្រសិនបើ (dest)
			dest[0] = '\0';
		ត្រឡប់ dest;
	}

	snprintf (dest, (size_t) regmatch_len(m), "%s", src + m->rm_so);
	ត្រឡប់ dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
ចំនួនគត់ regmatch_len (regmatch_t * m)
{
	ប្រសិនបើ (m == NULL || m->rm_so < 0) {
		ត្រឡប់ 0;
	}

	ត្រឡប់ m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
ចំនួនគត់ regmatch_strtol (regmatch_t * m, const var_na *src, var_na **endptr,
		     ចំនួនគត់ base)
{
	ចំនួនគត់     n = 0;

#define bufsz 20
	var_na    buf[bufsz];
	var_na   *s;

	ប្រសិនបើ (m == NULL || m->rm_so < 0)
		ត្រឡប់ 0;

	ប្រសិនបើ (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	បើមិនដូច្នេះ
		s = regmatch_dup (m, src);

	n = (ចំនួនគត់) strtol (s, endptr, base);

	ប្រសិនបើ (s != buf)
		free (s);

	ត្រឡប់ n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_empty (regmatch_t * m)
{
	ត្រឡប់ (m == NULL || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
