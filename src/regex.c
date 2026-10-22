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

#అన్తర్భావ "flexdef.h"


regex_t regex_linedir; /**< matches line directives */


/** Initialize the regular expressions.
 * @return true upon success.
 */
bool flex_init_regex(స్థిరరాశి అక్షరం *traceline_re)
{
	ఒకవేళ (traceline_re != ఖాళీ)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	తిరిగి true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
శూన్య flex_regcomp(regex_t *preg, స్థిరరాశి అక్షరం *regex, పూర్ణాంకం cflags)
{
	పూర్ణాంకం err;

	memset (preg, 0, పరిమాణం (regex_t));

	ఒకవేళ ((err = regcomp (preg, regex, cflags)) != 0) {
		స్థిరరాశి size_t errbuf_sz = 200;
		అక్షరం *errbuf;
		పూర్ణాంకం n;

		errbuf = జ్ఞాపకం_ఇవ్వు(errbuf_sz * పరిమాణం(అక్షరం));
		ఒకవేళ (!errbuf)
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
అక్షరం   *regmatch_dup (regmatch_t * m, స్థిరరాశి అక్షరం *src)
{
	అక్షరం   *str;
	size_t  len;

	ఒకవేళ (m == ఖాళీ || m->rm_so < 0 || m->rm_eo < m->rm_so)
		తిరిగి ఖాళీ;
	len = (size_t) (m->rm_eo - m->rm_so);
	str = జ్ఞాపకం_ఇవ్వు((len + 1) * పరిమాణం(అక్షరం));
	ఒకవేళ (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	తిరిగి str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
అక్షరం   *regmatch_cpy (regmatch_t * m, అక్షరం *dest, స్థిరరాశి అక్షరం *src)
{
	ఒకవేళ (m == ఖాళీ || m->rm_so < 0) {
		ఒకవేళ (dest)
			dest[0] = '\0';
		తిరిగి dest;
	}

	snprintf (dest, (size_t) regmatch_len(m), "%s", src + m->rm_so);
	తిరిగి dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
పూర్ణాంకం regmatch_len (regmatch_t * m)
{
	ఒకవేళ (m == ఖాళీ || m->rm_so < 0) {
		తిరిగి 0;
	}

	తిరిగి m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
పూర్ణాంకం regmatch_strtol (regmatch_t * m, స్థిరరాశి అక్షరం *src, అక్షరం **endptr,
		     పూర్ణాంకం పునాది)
{
	పూర్ణాంకం     n = 0;

#నిర్వచించు bufsz 20
	అక్షరం    buf[bufsz];
	అక్షరం   *s;

	ఒకవేళ (m == ఖాళీ || m->rm_so < 0)
		తిరిగి 0;

	ఒకవేళ (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	లేకపోతే
		s = regmatch_dup (m, src);

	n = (పూర్ణాంకం) strtol (s, endptr, పునాది);

	ఒకవేళ (s != buf)
		విడుదల (s);

	తిరిగి n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_ఖాళీలు (regmatch_t * m)
{
	తిరిగి (m == ఖాళీ || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
