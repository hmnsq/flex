/* ccl - routines for character classes */

/* SPDX-License-Identifier: BSD-3-Clause-flex */

/*  Copyright (c) 1990 The Regents of the University of California. */
/*  All rights reserved. */

/*  This code is derived from software contributed to Berkeley by */
/*  Vern Paxson. */

/*  The United States Government has rights in this work pursuant */
/*  to contract no. DE-AC03-76SF00098 between the United States */
 /*  Department of Energy and the University of California. */

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

/* return true if the chr is in the ccl. Takes negation into account. */
स्थिर bool
ccl_अन्तर्भवति (ध्रुव पूर्णाङ्क cclp, ध्रुव पूर्णाङ्क ch)
{
	पूर्णाङ्क     ind, len, i;

	len = ccllen[cclp];
	ind = cclmap[cclp];

	प्रति (i = 0; i < len; ++i)
		यदि (ccltbl[ind + i] == ch)
			प्रत्यागम !cclng[cclp];

    प्रत्यागम cclng[cclp];
}


/* ccladd - add a single character to a ccl */

शून्य ccladd (पूर्णाङ्क cclp, पूर्णाङ्क ch)
{
	पूर्णाङ्क     ind, len, newpos, i;

	check_char (ch);

	len = ccllen[cclp];
	ind = cclmap[cclp];

	/* check to see if the character is already in the ccl */

	प्रति (i = 0; i < len; ++i)
		यदि (ccltbl[ind + i] == ch)
			प्रत्यागम;

	/* mark newlines */
	यदि (ch == nlch)
		ccl_has_nl[cclp] = true;

	newpos = ind + len;

	/* For a non-last cclp, expanding the set will overflow and overwrite a
	 * char in the next cclp.
	 * FIXME: Need another allocation scheme for ccl's. */
	यदि (cclp != lastccl) {
		flexfatal(_("internal error: trying to add a char to a non-last ccl.\n"));
	}

	यदि (newpos >= current_max_ccl_tbl_आकार) {
		current_max_ccl_tbl_आकार += MAX_CCL_TBL_आकार_INCREMENT;

		++अङ्कः_reallocs;

		ccltbl = reallocate_Character_array (ccltbl,
						     current_max_ccl_tbl_आकार);
	}

	ccllen[cclp] = len + 1;
	ccltbl[newpos] = (अचिह्नित वर्ण) ch;
}

/* dump_cclp - same thing as list_character_set, but for cclps.  */

स्थिर शून्य    dump_cclp (FILE* file, पूर्णाङ्क cclp)
{
	पूर्णाङ्क i;

	putc ('[', file);

	प्रति (i = 0; i < ctrl.csize; ++i) {
		यदि (ccl_अन्तर्भवति(cclp, i)){
			पूर्णाङ्क start_char = i;

			putc (' ', file);

			fputs (readable_form (i), file);

			यावत् (++i < ctrl.csize && ccl_अन्तर्भवति(cclp,i)) ;

			यदि (i - 1 > start_char)
				/* this was a run */
				fprintf (file, "-%s",
					 readable_form (i - 1));

			putc (' ', file);
		}
	}

	putc (']', file);
}



/* ccl_set_diff - create a new ccl as the set difference of the two given ccls. */
पूर्णाङ्क
ccl_समुच्चयः_diff (पूर्णाङ्क a, पूर्णाङ्क b)
{
    पूर्णाङ्क  d, ch;

    /* create new class  */
    d = cclinit();

    /* In order to handle negation, we spin through all possible chars,
     * adding each char in a that is not in b.
     * (This could be O(n^2), but n is small and bounded.)
     */
	प्रति ( ch = 0; ch < ctrl.csize; ++ch )
        यदि (ccl_अन्तर्भवति (a, ch) && !ccl_अन्तर्भवति(b, ch))
            ccladd (d, ch);

    /* debug */
    यदि (0){
        fprintf(stderr, "ccl_set_diff (");
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, a);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, b);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, d);
        fprintf(stderr, "\n)\n");
    }
    प्रत्यागम d;
}

/* ccl_set_union - create a new ccl as the set union of the two given ccls. */
पूर्णाङ्क
ccl_समुच्चयः_union (पूर्णाङ्क a, पूर्णाङ्क b)
{
    पूर्णाङ्क  d, i;

    /* create new class  */
    d = cclinit();

    /* Add all of a */
    प्रति (i = 0; i < ccllen[a]; ++i)
		ccladd (d, ccltbl[cclmap[a] + i]);

    /* Add all of b */
    प्रति (i = 0; i < ccllen[b]; ++i)
		ccladd (d, ccltbl[cclmap[b] + i]);

    /* debug */
    यदि (0){
        fprintf(stderr, "ccl_set_union (%d + %d = %d", a, b, d);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, a);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, b);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, d);
        fprintf(stderr, "\n)\n");
    }
    प्रत्यागम d;
}


/* cclinit - return an empty ccl */

पूर्णाङ्क     cclinit (शून्य)
{
	यदि (++lastccl >= current_maxccls) {
		current_maxccls += MAX_CCLS_INCREMENT;

		++अङ्कः_reallocs;

		cclmap =
			reallocate_integer_array (cclmap, current_maxccls);
		ccllen =
			reallocate_integer_array (ccllen, current_maxccls);
		cclng = reallocate_integer_array (cclng, current_maxccls);
		ccl_has_nl = reallocate_array(ccl_has_nl, current_maxccls, परिमाण(वर्ण));
	}

	यदि (lastccl == 1)
		/* we're making the first ccl */
		cclmap[lastccl] = 0;

	अन्यथा
		/* The new pointer is just past the end of the last ccl.
		 * Since the cclmap points to the \first/ character of a
		 * ccl, adding the length of the ccl to the cclmap pointer
		 * will produce a cursor to the first free space.
		 */
		cclmap[lastccl] =
			cclmap[lastccl - 1] + ccllen[lastccl - 1];

	ccllen[lastccl] = 0;
	cclng[lastccl] = 0;	/* ccl's start out life un-negated */
	ccl_has_nl[lastccl] = false;

	प्रत्यागम lastccl;
}


/* cclnegate - negate the given ccl */

शून्य    cclnegate (पूर्णाङ्क cclp)
{
	cclng[cclp] = 1;
	ccl_has_nl[cclp] = !ccl_has_nl[cclp];
}


/* list_character_set - list the members of a set of characters in CCL form
 *
 * Writes to the given file a character-class representation of those
 * characters present in the given CCL.  A character is present if it
 * has a non-zero value in the cset array.
 */

शून्य    list_character_समुच्चयः (FILE *file, पूर्णाङ्क cset[])
{
	पूर्णाङ्क i;

	putc ('[', file);

	प्रति (i = 0; i < ctrl.csize; ++i) {
		यदि (cset[i]) {
			पूर्णाङ्क start_char = i;

			putc (' ', file);

			fputs (readable_form (i), file);

			यावत् (++i < ctrl.csize && cset[i]) ;

			यदि (i - 1 > start_char)
				/* this was a run */
				fprintf (file, "-%s",
					 readable_form (i - 1));

			putc (' ', file);
		}
	}

	putc (']', file);
}

/** Determines if the range [c1-c2] is unambiguous in a case-insensitive
 * scanner.  Specifically, if a lowercase or uppercase character, x, is in the
 * range [c1-c2], then we require that UPPERCASE(x) and LOWERCASE(x) must also
 * be in the range. If not, then this range is ambiguous, and the function
 * returns false.  For example, [@-_] spans [a-z] but not [A-Z].  Beware that
 * [a-z] will be labeled ambiguous because it does not include [A-Z].
 *
 * @param c1 the lower end of the range
 * @param c2 the upper end of the range
 * @return true if [c1-c2] is not ambiguous for a caseless scanner.
 */
bool range_covers_case (पूर्णाङ्क c1, पूर्णाङ्क c2)
{
	पूर्णाङ्क     i, o;

	प्रति (i = c1; i <= c2; i++) {
		यदि (has_case (i)) {
			o = reverse_case (i);
			यदि (o < c1 || c2 < o)
				प्रत्यागम false;
		}
	}
	प्रत्यागम true;
}

/** Reverse the case of a character, if possible.
 * @return c if case-reversal does not apply.
 */
पूर्णाङ्क reverse_case (पूर्णाङ्क c)
{
	प्रत्यागम isupper (c) ? tolower (c) : (islower (c) ? महाक्षरम् (c) : c);
}

/** Return true if c is uppercase or lowercase. */
bool has_case (पूर्णाङ्क c)
{
	प्रत्यागम (isupper (c) || islower (c)) ? true : false;
}
