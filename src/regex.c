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

#شامل "flexdef.h"


regex_t regex_linedir; /**< matches line directives */


/** Initialize the regular expressions.
 * @return true upon success.
 */
bool flex_init_regex(ثابت حرف *traceline_re)
{
	اگر (traceline_re != تہی)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	واپس true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
خالی flex_regcomp(regex_t *preg, ثابت حرف *regex, صحیح cflags)
{
	صحیح err;

	memset (preg, 0, حجم (regex_t));

	اگر ((err = regcomp (preg, regex, cflags)) != 0) {
		ثابت size_t errbuf_sz = 200;
		حرف *errbuf;
		صحیح n;

		errbuf = حافظہ_دو(errbuf_sz * حجم(حرف));
		اگر (!errbuf)
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
حرف   *regmatch_dup (regmatch_t * m, ثابت حرف *src)
{
	حرف   *str;
	size_t  len;

	اگر (m == تہی || m->rm_so < 0 || m->rm_eo < m->rm_so)
		واپس تہی;
	len = (size_t) (m->rm_eo - m->rm_so);
	str = حافظہ_دو((len + 1) * حجم(حرف));
	اگر (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	واپس str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
حرف   *regmatch_cpy (regmatch_t * m, حرف *dest, ثابت حرف *src)
{
	اگر (m == تہی || m->rm_so < 0) {
		اگر (dest)
			dest[0] = '\0';
		واپس dest;
	}

	snprintf (dest, (size_t) regmatch_len(m), "%s", src + m->rm_so);
	واپس dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
صحیح regmatch_len (regmatch_t * m)
{
	اگر (m == تہی || m->rm_so < 0) {
		واپس 0;
	}

	واپس m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
صحیح regmatch_strtol (regmatch_t * m, ثابت حرف *src, حرف **endptr,
		     صحیح بنیاد)
{
	صحیح     n = 0;

#تعریف_کرو bufsz 20
	حرف    buf[bufsz];
	حرف   *s;

	اگر (m == تہی || m->rm_so < 0)
		واپس 0;

	اگر (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	ورنہ
		s = regmatch_dup (m, src);

	n = (صحیح) strtol (s, endptr, بنیاد);

	اگر (s != buf)
		آزاد (s);

	واپس n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_خالی_خانے (regmatch_t * m)
{
	واپس (m == تہی || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
