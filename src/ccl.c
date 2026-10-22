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

#include "flexdef.h"

/* return true if the chr is in the ccl. Takes negation into account. */
static bool
ccl_contains (const puur_naa_nka cclp, const puur_naa_nka ch)
{
	puur_naa_nka     ind, len, i;

	len = ccllen[cclp];
	ind = cclmap[cclp];

	ꦏꦁꦒꦺꦴ (i = 0; i < len; ++i)
		ꦪꦼꦤ꧀ (ccltbl[ind + i] == ch)
			ꦮꦭꦶ !cclng[cclp];

    ꦮꦭꦶ cclng[cclp];
}


/* ccladd - add a single character to a ccl */

void ccladd (puur_naa_nka cclp, puur_naa_nka ch)
{
	puur_naa_nka     ind, len, newpos, i;

	check_char (ch);

	len = ccllen[cclp];
	ind = cclmap[cclp];

	/* check to see if the character is already in the ccl */

	ꦏꦁꦒꦺꦴ (i = 0; i < len; ++i)
		ꦪꦼꦤ꧀ (ccltbl[ind + i] == ch)
			ꦮꦭꦶ;

	/* mark newlines */
	ꦪꦼꦤ꧀ (ch == nlch)
		ccl_has_nl[cclp] = true;

	newpos = ind + len;

	/* For a non-last cclp, expanding the set will overflow and overwrite a
	 * char in the next cclp.
	 * FIXME: Need another allocation scheme for ccl's. */
	ꦪꦼꦤ꧀ (cclp != lastccl) {
		flexfatal(_("internal error: trying to add a char to a non-last ccl.\n"));
	}

	ꦪꦼꦤ꧀ (newpos >= current_max_ccl_tbl_size) {
		current_max_ccl_tbl_size += MAX_CCL_TBL_SIZE_INCREMENT;

		++num_reallocs;

		ccltbl = reallocate_Character_array (ccltbl,
						     current_max_ccl_tbl_size);
	}

	ccllen[cclp] = len + 1;
	ccltbl[newpos] = (unsigned var_na) ch;
}

/* dump_cclp - same thing as list_character_set, but for cclps.  */

static void    dump_cclp (FILE* file, puur_naa_nka cclp)
{
	puur_naa_nka i;

	putc ('[', file);

	ꦏꦁꦒꦺꦴ (i = 0; i < ctrl.csize; ++i) {
		ꦪꦼꦤ꧀ (ccl_contains(cclp, i)){
			puur_naa_nka start_char = i;

			putc (' ', file);

			fputs (readable_form (i), file);

			ꦱꦼꦢꦼꦭ (++i < ctrl.csize && ccl_contains(cclp,i)) ;

			ꦪꦼꦤ꧀ (i - 1 > start_char)
				/* this was a run */
				fprintf (file, "-%s",
					 readable_form (i - 1));

			putc (' ', file);
		}
	}

	putc (']', file);
}



/* ccl_set_diff - create a new ccl as the set difference of the two given ccls. */
puur_naa_nka
ccl_set_diff (puur_naa_nka a, puur_naa_nka b)
{
    puur_naa_nka  d, ch;

    /* create new class  */
    d = cclinit();

    /* In order to handle negation, we spin through all possible chars,
     * adding each char in a that is not in b.
     * (This could be O(n^2), but n is small and bounded.)
     */
	ꦏꦁꦒꦺꦴ ( ch = 0; ch < ctrl.csize; ++ch )
        ꦪꦼꦤ꧀ (ccl_contains (a, ch) && !ccl_contains(b, ch))
            ccladd (d, ch);

    /* debug */
    ꦪꦼꦤ꧀ (0){
        fprintf(stderr, "ccl_set_diff (");
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, a);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, b);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, d);
        fprintf(stderr, "\n)\n");
    }
    ꦮꦭꦶ d;
}

/* ccl_set_union - create a new ccl as the set union of the two given ccls. */
puur_naa_nka
ccl_set_union (puur_naa_nka a, puur_naa_nka b)
{
    puur_naa_nka  d, i;

    /* create new class  */
    d = cclinit();

    /* Add all of a */
    ꦏꦁꦒꦺꦴ (i = 0; i < ccllen[a]; ++i)
		ccladd (d, ccltbl[cclmap[a] + i]);

    /* Add all of b */
    ꦏꦁꦒꦺꦴ (i = 0; i < ccllen[b]; ++i)
		ccladd (d, ccltbl[cclmap[b] + i]);

    /* debug */
    ꦪꦼꦤ꧀ (0){
        fprintf(stderr, "ccl_set_union (%d + %d = %d", a, b, d);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, a);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, b);
            fprintf(stderr, "\n    ");
            dump_cclp (stderr, d);
        fprintf(stderr, "\n)\n");
    }
    ꦮꦭꦶ d;
}


/* cclinit - return an empty ccl */

puur_naa_nka     cclinit (void)
{
	ꦪꦼꦤ꧀ (++lastccl >= current_maxccls) {
		current_maxccls += MAX_CCLS_INCREMENT;

		++num_reallocs;

		cclmap =
			reallocate_integer_array (cclmap, current_maxccls);
		ccllen =
			reallocate_integer_array (ccllen, current_maxccls);
		cclng = reallocate_integer_array (cclng, current_maxccls);
		ccl_has_nl = reallocate_array(ccl_has_nl, current_maxccls, parimaa_na(var_na));
	}

	ꦪꦼꦤ꧀ (lastccl == 1)
		/* we're making the first ccl */
		cclmap[lastccl] = 0;

	ꦭꦶꦪ
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

	ꦮꦭꦶ lastccl;
}


/* cclnegate - negate the given ccl */

void    cclnegate (puur_naa_nka cclp)
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

void    list_character_set (FILE *file, puur_naa_nka cset[])
{
	puur_naa_nka i;

	putc ('[', file);

	ꦏꦁꦒꦺꦴ (i = 0; i < ctrl.csize; ++i) {
		ꦪꦼꦤ꧀ (cset[i]) {
			puur_naa_nka start_char = i;

			putc (' ', file);

			fputs (readable_form (i), file);

			ꦱꦼꦢꦼꦭ (++i < ctrl.csize && cset[i]) ;

			ꦪꦼꦤ꧀ (i - 1 > start_char)
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
bool range_covers_case (puur_naa_nka c1, puur_naa_nka c2)
{
	puur_naa_nka     i, o;

	ꦏꦁꦒꦺꦴ (i = c1; i <= c2; i++) {
		ꦪꦼꦤ꧀ (has_case (i)) {
			o = reverse_case (i);
			ꦪꦼꦤ꧀ (o < c1 || c2 < o)
				ꦮꦭꦶ false;
		}
	}
	ꦮꦭꦶ true;
}

/** Reverse the case of a character, if possible.
 * @return c if case-reversal does not apply.
 */
puur_naa_nka reverse_case (puur_naa_nka c)
{
	ꦮꦭꦶ isupper (c) ? tolower (c) : (islower (c) ? toupper (c) : c);
}

/** Return true if c is uppercase or lowercase. */
bool has_case (puur_naa_nka c)
{
	ꦮꦭꦶ (isupper (c) || islower (c)) ? true : false;
}
