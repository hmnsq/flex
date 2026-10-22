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

#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"


regex_t regex_linedir; /**< matches line directives */


/** Initialize the regular expressions.
 * @return true upon success.
 */
bool flex_init_regex(ਅਚਲ ਅੱਖਰ *traceline_re)
{
	ਜੇ (traceline_re != ਨਿਰਾ)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	ਵਾਪਸ true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
ਖਾਲੀ flex_regcomp(regex_t *preg, ਅਚਲ ਅੱਖਰ *regex, ਪੂਰਨ cflags)
{
	ਪੂਰਨ err;

	memset (preg, 0, ਆਕਾਰ (regex_t));

	ਜੇ ((err = regcomp (preg, regex, cflags)) != 0) {
		ਅਚਲ size_t errbuf_sz = 200;
		ਅੱਖਰ *errbuf;
		ਪੂਰਨ n;

		errbuf = ਸਮ੍ਰਿਤੀ_ਦਿਓ(errbuf_sz * ਆਕਾਰ(ਅੱਖਰ));
		ਜੇ (!errbuf)
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
ਅੱਖਰ   *regmatch_dup (regmatch_t * m, ਅਚਲ ਅੱਖਰ *src)
{
	ਅੱਖਰ   *str;
	size_t  len;

	ਜੇ (m == ਨਿਰਾ || m->rm_so < 0 || m->rm_eo < m->rm_so)
		ਵਾਪਸ ਨਿਰਾ;
	len = (size_t) (m->rm_eo - m->rm_so);
	str = ਸਮ੍ਰਿਤੀ_ਦਿਓ((len + 1) * ਆਕਾਰ(ਅੱਖਰ));
	ਜੇ (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	ਵਾਪਸ str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
ਅੱਖਰ   *regmatch_cpy (regmatch_t * m, ਅੱਖਰ *dest, ਅਚਲ ਅੱਖਰ *src)
{
	ਜੇ (m == ਨਿਰਾ || m->rm_so < 0) {
		ਜੇ (dest)
			dest[0] = '\0';
		ਵਾਪਸ dest;
	}

	snprintf (dest, (size_t) regmatch_len(m), "%s", src + m->rm_so);
	ਵਾਪਸ dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
ਪੂਰਨ regmatch_len (regmatch_t * m)
{
	ਜੇ (m == ਨਿਰਾ || m->rm_so < 0) {
		ਵਾਪਸ 0;
	}

	ਵਾਪਸ m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
ਪੂਰਨ regmatch_strtol (regmatch_t * m, ਅਚਲ ਅੱਖਰ *src, ਅੱਖਰ **endptr,
		     ਪੂਰਨ ਅਧਾਰ)
{
	ਪੂਰਨ     n = 0;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ bufsz 20
	ਅੱਖਰ    buf[bufsz];
	ਅੱਖਰ   *s;

	ਜੇ (m == ਨਿਰਾ || m->rm_so < 0)
		ਵਾਪਸ 0;

	ਜੇ (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	ਨਹੀਂਤਾਂ
		s = regmatch_dup (m, src);

	n = (ਪੂਰਨ) strtol (s, endptr, ਅਧਾਰ);

	ਜੇ (s != buf)
		ਮੁਕਤ (s);

	ਵਾਪਸ n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_ਖਾਲੀ_ਥਾਵਾਂ (regmatch_t * m)
{
	ਵਾਪਸ (m == ਨਿਰਾ || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
