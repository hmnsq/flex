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

#അന്തര്ഭാവ "flexdef.h"


regex_t regex_linedir; /**< matches line directives */


/** Initialize the regular expressions.
 * @return true upon success.
 */
bool flex_init_regex(സ്ഥിരം അക്ഷരം *traceline_re)
{
	എങ്കിൽ (traceline_re != ശൂന്യ)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	തിരികെ true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
ശൂന്യം flex_regcomp(regex_t *preg, സ്ഥിരം അക്ഷരം *regex, പൂർണ്ണസംഖ്യ cflags)
{
	പൂർണ്ണസംഖ്യ err;

	memset (preg, 0, വലുപ്പം (regex_t));

	എങ്കിൽ ((err = regcomp (preg, regex, cflags)) != 0) {
		സ്ഥിരം size_t errbuf_sz = 200;
		അക്ഷരം *errbuf;
		പൂർണ്ണസംഖ്യ n;

		errbuf = malloc(errbuf_sz * വലുപ്പം(അക്ഷരം));
		എങ്കിൽ (!errbuf)
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
അക്ഷരം   *regmatch_dup (regmatch_t * m, സ്ഥിരം അക്ഷരം *src)
{
	അക്ഷരം   *str;
	size_t  len;

	എങ്കിൽ (m == ശൂന്യ || m->rm_so < 0 || m->rm_eo < m->rm_so)
		തിരികെ ശൂന്യ;
	len = (size_t) (m->rm_eo - m->rm_so);
	str = malloc((len + 1) * വലുപ്പം(അക്ഷരം));
	എങ്കിൽ (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	തിരികെ str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
അക്ഷരം   *regmatch_cpy (regmatch_t * m, അക്ഷരം *dest, സ്ഥിരം അക്ഷരം *src)
{
	എങ്കിൽ (m == ശൂന്യ || m->rm_so < 0) {
		എങ്കിൽ (dest)
			dest[0] = '\0';
		തിരികെ dest;
	}

	snprintf (dest, (size_t) regmatch_len(m), "%s", src + m->rm_so);
	തിരികെ dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
പൂർണ്ണസംഖ്യ regmatch_len (regmatch_t * m)
{
	എങ്കിൽ (m == ശൂന്യ || m->rm_so < 0) {
		തിരികെ 0;
	}

	തിരികെ m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
പൂർണ്ണസംഖ്യ regmatch_strtol (regmatch_t * m, സ്ഥിരം അക്ഷരം *src, അക്ഷരം **endptr,
		     പൂർണ്ണസംഖ്യ base)
{
	പൂർണ്ണസംഖ്യ     n = 0;

#define bufsz 20
	അക്ഷരം    buf[bufsz];
	അക്ഷരം   *s;

	എങ്കിൽ (m == ശൂന്യ || m->rm_so < 0)
		തിരികെ 0;

	എങ്കിൽ (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	അല്ലെങ്കിൽ
		s = regmatch_dup (m, src);

	n = (പൂർണ്ണസംഖ്യ) strtol (s, endptr, base);

	എങ്കിൽ (s != buf)
		സ്വതന്ത്രം (s);

	തിരികെ n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_empty (regmatch_t * m)
{
	തിരികെ (m == ശൂന്യ || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
