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

#অন্তর্ভাৱ "flexdef.h"


regex_t regex_linedir; /**< matches line directives */


/** Initialize the regular expressions.
 * @return true upon success.
 */
bool flex_init_regex(ধ্রুৱ ৱর্ণ *traceline_re)
{
	যদি (traceline_re != রিক্ত)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	ঘূৰাই true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
শূন্য flex_regcomp(regex_t *preg, ধ্রুৱ ৱর্ণ *regex, পূর্ণাঙ্ক cflags)
{
	পূর্ণাঙ্ক err;

	memset (preg, 0, পরিমাণ (regex_t));

	যদি ((err = regcomp (preg, regex, cflags)) != 0) {
		ধ্রুৱ size_t errbuf_sz = 200;
		ৱর্ণ *errbuf;
		পূর্ণাঙ্ক n;

		errbuf = malloc(errbuf_sz * পরিমাণ(ৱর্ণ));
		যদি (!errbuf)
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
ৱর্ণ   *regmatch_dup (regmatch_t * m, ধ্রুৱ ৱর্ণ *src)
{
	ৱর্ণ   *str;
	size_t  len;

	যদি (m == রিক্ত || m->rm_so < 0 || m->rm_eo < m->rm_so)
		ঘূৰাই রিক্ত;
	len = (size_t) (m->rm_eo - m->rm_so);
	str = malloc((len + 1) * পরিমাণ(ৱর্ণ));
	যদি (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	ঘূৰাই str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
ৱর্ণ   *regmatch_cpy (regmatch_t * m, ৱর্ণ *dest, ধ্রুৱ ৱর্ণ *src)
{
	যদি (m == রিক্ত || m->rm_so < 0) {
		যদি (dest)
			dest[0] = '\0';
		ঘূৰাই dest;
	}

	snprintf (dest, (size_t) regmatch_len(m), "%s", src + m->rm_so);
	ঘূৰাই dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
পূর্ণাঙ্ক regmatch_len (regmatch_t * m)
{
	যদি (m == রিক্ত || m->rm_so < 0) {
		ঘূৰাই 0;
	}

	ঘূৰাই m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
পূর্ণাঙ্ক regmatch_strtol (regmatch_t * m, ধ্রুৱ ৱর্ণ *src, ৱর্ণ **endptr,
		     পূর্ণাঙ্ক base)
{
	পূর্ণাঙ্ক     n = 0;

#define bufsz 20
	ৱর্ণ    buf[bufsz];
	ৱর্ণ   *s;

	যদি (m == রিক্ত || m->rm_so < 0)
		ঘূৰাই 0;

	যদি (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	অন্যথা
		s = regmatch_dup (m, src);

	n = (পূর্ণাঙ্ক) strtol (s, endptr, base);

	যদি (s != buf)
		মুক্ত (s);

	ঘূৰাই n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_empty (regmatch_t * m)
{
	ঘূৰাই (m == রিক্ত || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
