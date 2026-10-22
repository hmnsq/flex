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

#ಅನ್ತರ್ಭಾವ "flexdef.h"


regex_t regex_linedir; /**< matches line directives */


/** Initialize the regular expressions.
 * @return true upon success.
 */
bool flex_init_regex(ಧ್ರುವ ವರ್ಣ *traceline_re)
{
	ಯದಿ (traceline_re != ರಿಕ್ತ)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	ಪ್ರತ್ಯಾಗಮ true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
ಶೂನ್ಯ flex_regcomp(regex_t *preg, ಧ್ರುವ ವರ್ಣ *regex, ಪೂರ್ಣಾಙ್ಕ cflags)
{
	ಪೂರ್ಣಾಙ್ಕ err;

	memset (preg, 0, ಪರಿಮಾಣ (regex_t));

	ಯದಿ ((err = regcomp (preg, regex, cflags)) != 0) {
		ಧ್ರುವ size_t errbuf_sz = 200;
		ವರ್ಣ *errbuf;
		ಪೂರ್ಣಾಙ್ಕ n;

		errbuf = malloc(errbuf_sz * ಪರಿಮಾಣ(ವರ್ಣ));
		ಯದಿ (!errbuf)
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
ವರ್ಣ   *regmatch_dup (regmatch_t * m, ಧ್ರುವ ವರ್ಣ *src)
{
	ವರ್ಣ   *str;
	size_t  len;

	ಯದಿ (m == ರಿಕ್ತ || m->rm_so < 0 || m->rm_eo < m->rm_so)
		ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
	len = (size_t) (m->rm_eo - m->rm_so);
	str = malloc((len + 1) * ಪರಿಮಾಣ(ವರ್ಣ));
	ಯದಿ (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	ಪ್ರತ್ಯಾಗಮ str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
ವರ್ಣ   *regmatch_cpy (regmatch_t * m, ವರ್ಣ *dest, ಧ್ರುವ ವರ್ಣ *src)
{
	ಯದಿ (m == ರಿಕ್ತ || m->rm_so < 0) {
		ಯದಿ (dest)
			dest[0] = '\0';
		ಪ್ರತ್ಯಾಗಮ dest;
	}

	snprintf (dest, (size_t) regmatch_len(m), "%s", src + m->rm_so);
	ಪ್ರತ್ಯಾಗಮ dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
ಪೂರ್ಣಾಙ್ಕ regmatch_len (regmatch_t * m)
{
	ಯದಿ (m == ರಿಕ್ತ || m->rm_so < 0) {
		ಪ್ರತ್ಯಾಗಮ 0;
	}

	ಪ್ರತ್ಯಾಗಮ m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
ಪೂರ್ಣಾಙ್ಕ regmatch_strtol (regmatch_t * m, ಧ್ರುವ ವರ್ಣ *src, ವರ್ಣ **endptr,
		     ಪೂರ್ಣಾಙ್ಕ base)
{
	ಪೂರ್ಣಾಙ್ಕ     n = 0;

#define bufsz 20
	ವರ್ಣ    buf[bufsz];
	ವರ್ಣ   *s;

	ಯದಿ (m == ರಿಕ್ತ || m->rm_so < 0)
		ಪ್ರತ್ಯಾಗಮ 0;

	ಯದಿ (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	ಅನ್ಯಥಾ
		s = regmatch_dup (m, src);

	n = (ಪೂರ್ಣಾಙ್ಕ) strtol (s, endptr, base);

	ಯದಿ (s != buf)
		ಮುಕ್ತ (s);

	ಪ್ರತ್ಯಾಗಮ n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_empty (regmatch_t * m)
{
	ಪ್ರತ್ಯಾಗಮ (m == ರಿಕ್ತ || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
