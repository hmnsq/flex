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
bool flex_init_regex(const char *traceline_re)
{
	nếu (traceline_re != NULL)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	trả_về true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
void flex_regcomp(regex_t *preg, const char *regex, số_nguyên cflags)
{
	số_nguyên err;

	memset (preg, 0, sizeof (regex_t));

	nếu ((err = regcomp (preg, regex, cflags)) != 0) {
		const size_t errbuf_sz = 200;
		char *errbuf;
		số_nguyên n;

		errbuf = malloc(errbuf_sz * sizeof(char));
		nếu (!errbuf)
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
char   *regmatch_dup (regmatch_t * m, const char *src)
{
	char   *str;
	size_t  len;

	nếu (m == NULL || m->rm_so < 0 || m->rm_eo < m->rm_so)
		trả_về NULL;
	len = (size_t) (m->rm_eo - m->rm_so);
	str = malloc((len + 1) * sizeof(char));
	nếu (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	trả_về str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
char   *regmatch_cpy (regmatch_t * m, char *dest, const char *src)
{
	nếu (m == NULL || m->rm_so < 0) {
		nếu (dest)
			dest[0] = '\0';
		trả_về dest;
	}

	snprintf (dest, (size_t) regmatch_len(m), "%s", src + m->rm_so);
	trả_về dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
số_nguyên regmatch_len (regmatch_t * m)
{
	nếu (m == NULL || m->rm_so < 0) {
		trả_về 0;
	}

	trả_về m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
số_nguyên regmatch_strtol (regmatch_t * m, const char *src, char **endptr,
		     số_nguyên base)
{
	số_nguyên     n = 0;

#define bufsz 20
	char    buf[bufsz];
	char   *s;

	nếu (m == NULL || m->rm_so < 0)
		trả_về 0;

	nếu (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	không_thì
		s = regmatch_dup (m, src);

	n = (số_nguyên) strtol (s, endptr, base);

	nếu (s != buf)
		free (s);

	trả_về n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_empty (regmatch_t * m)
{
	trả_về (m == NULL || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
