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

#अन्तर्भाव "flexdef.h"


regex_t regex_linedir; /**< matches line directives */


/** Initialize the regular expressions.
 * @return true upon success.
 */
bool flex_init_regex(अचर वर्ण *traceline_re)
{
	यदि (traceline_re != रिक्त)
		flex_regcomp(&regex_linedir, traceline_re, REG_EXTENDED);
	फर्काऊ true;
}

/** Compiles a regular expression or dies trying.
 * @param preg  Same as for regcomp().
 * @param regex Same as for regcomp().
 * @param cflags Same as for regcomp().
 */
शून्य flex_regcomp(regex_t *preg, अचर वर्ण *regex, पूर्णाङ्क cflags)
{
	पूर्णाङ्क err;

	स_रखो (preg, 0, परिमाण (regex_t));

	यदि ((err = regcomp (preg, regex, cflags)) != 0) {
		अचर माप_प्रकार errbuf_sz = 200;
		वर्ण *errbuf;
		पूर्णाङ्क n;

		errbuf = दो_स्मृति(errbuf_sz * परिमाण(वर्ण));
		यदि (!errbuf)
			flexfatal(_("Unable to allocate buffer to report regcomp"));
		n = snprintf(errbuf, errbuf_sz, "regcomp for \"%s\" failed: ", regex);
		regerror(err, preg, errbuf+n, errbuf_sz-(माप_प्रकार)n);

		flexfatal (errbuf); /* never returns - no need to free(errbuf) */
	}
}

/** Extract a copy of the match, or NULL if no match.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @return The allocated string.
 */
वर्ण   *regmatch_dup (regmatch_t * m, अचर वर्ण *src)
{
	वर्ण   *str;
	माप_प्रकार  len;

	यदि (m == रिक्त || m->rm_so < 0 || m->rm_eo < m->rm_so)
		फर्काऊ रिक्त;
	len = (माप_प्रकार) (m->rm_eo - m->rm_so);
	str = दो_स्मृति((len + 1) * परिमाण(वर्ण));
	यदि (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	म_नकलन (str, src + m->rm_so, len);
	str[len] = 0;
	फर्काऊ str;
}

/** Copy the match.
 * @param m A match as returned by regexec().
 * @param dest The destination buffer.
 * @param src The source string that was passed to regexec().
 * @return dest
 */
वर्ण   *regmatch_cpy (regmatch_t * m, वर्ण *dest, अचर वर्ण *src)
{
	यदि (m == रिक्त || m->rm_so < 0) {
		यदि (dest)
			dest[0] = '\0';
		फर्काऊ dest;
	}

	snprintf (dest, (माप_प्रकार) regmatch_len(m), "%s", src + m->rm_so);
	फर्काऊ dest;
}

/** Get the length in characters of the match.
 * @param m A match as returned by regexec().
 * @return The length of the match.
 */
पूर्णाङ्क regmatch_len (regmatch_t * m)
{
	यदि (m == रिक्त || m->rm_so < 0) {
		फर्काऊ 0;
	}

	फर्काऊ m->rm_eo - m->rm_so;
}



/** Convert a regmatch_t object to an integer using the strtol() function.
 * @param m A match as returned by regexec().
 * @param src The source string that was passed to regexec().
 * @param endptr Same as the second argument to strtol().
 * @param base   Same as the third argument to strtol().
 * @return The converted integer or error (Return value is the same as for strtol()).
 */
पूर्णाङ्क regmatch_strtol (regmatch_t * m, अचर वर्ण *src, वर्ण **endptr,
		     पूर्णाङ्क base)
{
	पूर्णाङ्क     n = 0;

#define bufsz 20
	वर्ण    buf[bufsz];
	वर्ण   *s;

	यदि (m == रिक्त || m->rm_so < 0)
		फर्काऊ 0;

	यदि (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	अन्यथा
		s = regmatch_dup (m, src);

	n = (पूर्णाङ्क) म_से_दीर्घ (s, endptr, base);

	यदि (s != buf)
		मुक्त (s);

	फर्काऊ n;
}

/** Check for empty or non-existent match.
 * @param m A match as returned by regexec().
 * @return false if match length is non-zero.
 * Note that reg_empty returns true even if match did not occur at all.
 */
bool regmatch_empty (regmatch_t * m)
{
	फर्काऊ (m == रिक्त || m->rm_so < 0 || m->rm_so == m->rm_eo);
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
