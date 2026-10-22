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

#அந்தர்பாவ "flexdef.h"


regex_t regex_linedir; /**< matches line directives */


/** Initialize the regular expressions.
 * @return true upon success.
 */
bool flex_init_regex(மாறிலி எழுத்து *traceline_re)
{
	எனில் (traceline_re != வெற்று)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	திரும்பு true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
வெறுமை flex_regcomp(regex_t *preg, மாறிலி எழுத்து *regex, முழு cflags)
{
	முழு err;

	memset (preg, 0, அளவு (regex_t));

	எனில் ((err = regcomp (preg, regex, cflags)) != 0) {
		மாறிலி size_t errbuf_sz = 200;
		எழுத்து *errbuf;
		முழு n;

		errbuf = malloc(errbuf_sz * அளவு(எழுத்து));
		எனில் (!errbuf)
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
எழுத்து   *regmatch_dup (regmatch_t * m, மாறிலி எழுத்து *src)
{
	எழுத்து   *str;
	size_t  len;

	எனில் (m == வெற்று || m->rm_so < 0 || m->rm_eo < m->rm_so)
		திரும்பு வெற்று;
	len = (size_t) (m->rm_eo - m->rm_so);
	str = malloc((len + 1) * அளவு(எழுத்து));
	எனில் (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	திரும்பு str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
எழுத்து   *regmatch_cpy (regmatch_t * m, எழுத்து *dest, மாறிலி எழுத்து *src)
{
	எனில் (m == வெற்று || m->rm_so < 0) {
		எனில் (dest)
			dest[0] = '\0';
		திரும்பு dest;
	}

	snprintf (dest, (size_t) regmatch_len(m), "%s", src + m->rm_so);
	திரும்பு dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
முழு regmatch_len (regmatch_t * m)
{
	எனில் (m == வெற்று || m->rm_so < 0) {
		திரும்பு 0;
	}

	திரும்பு m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
முழு regmatch_strtol (regmatch_t * m, மாறிலி எழுத்து *src, எழுத்து **endptr,
		     முழு base)
{
	முழு     n = 0;

#define bufsz 20
	எழுத்து    buf[bufsz];
	எழுத்து   *s;

	எனில் (m == வெற்று || m->rm_so < 0)
		திரும்பு 0;

	எனில் (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	இல்லையெனில்
		s = regmatch_dup (m, src);

	n = (முழு) strtol (s, endptr, base);

	எனில் (s != buf)
		விடுவி (s);

	திரும்பு n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_empty (regmatch_t * m)
{
	திரும்பு (m == வெற்று || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
