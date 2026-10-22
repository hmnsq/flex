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
ccl_contains (स्थिरांक पूर्णांक cclp, स्थिरांक पूर्णांक ch)
{
	पूर्णांक     ind, len, i;

	len = ccllen[cclp];
	ind = cclmap[cclp];

	साठी (i = 0; i < len; ++i)
		जर (ccltbl[ind + i] == ch)
			परत !cclng[cclp];

    परत cclng[cclp];
}


/* ccladd - add a single character to a ccl */

शून्य ccladd (पूर्णांक cclp, पूर्णांक ch)
{
	पूर्णांक     ind, len, newpos, i;

	check_char (ch);

	len = ccllen[cclp];
	ind = cclmap[cclp];

	/* check to see if the character is already in the ccl */

	साठी (i = 0; i < len; ++i)
		जर (ccltbl[ind + i] == ch)
			परत;

	/* mark newlines */
	जर (ch == nlch)
		ccl_has_nl[cclp] = true;

	newpos = ind + len;

	/* For a non-last cclp, expanding the set will overflow and overwrite a
	 * char in the next cclp.
	 * FIXME: Need another allocation scheme for ccl's. */
	जर (cclp != lastccl) {
		flexfatal(_("internal error: trying to add a char to a non-last ccl.\n"));
	}

	जर (newpos >= current_max_ccl_tbl_size) {
		current_max_ccl_tbl_size += MAX_CCL_TBL_SIZE_INCREMENT;

		++अंक_reallocs;

		ccltbl = reallocate_Character_array (ccltbl,
						     current_max_ccl_tbl_size);
	}

	ccllen[cclp] = len + 1;
	ccltbl[newpos] = (अचिन्हित अक्षर) ch;
}

/* dump_cclp - same thing as list_character_set, but for cclps.  */

स्थिर शून्य    dump_cclp (खाता* file, पूर्णांक cclp)
{
	पूर्णांक i;

	अ_दो ('[', file);

	साठी (i = 0; i < ctrl.csize; ++i) {
		जर (ccl_contains(cclp, i)){
			पूर्णांक start_char = i;

			अ_दो (' ', file);

			ख_माला_दो (readable_form (i), file);

			पर्यंत (++i < ctrl.csize && ccl_contains(cclp,i)) ;

			जर (i - 1 > start_char)
				/* this was a run */
				ख_लिखो (file, "-%s",
					 readable_form (i - 1));

			अ_दो (' ', file);
		}
	}

	अ_दो (']', file);
}



/* ccl_set_diff - create a new ccl as the set difference of the two given ccls. */
पूर्णांक
ccl_set_diff (पूर्णांक a, पूर्णांक b)
{
    पूर्णांक  d, ch;

    /* create new class  */
    d = cclinit();

    /* In order to handle negation, we spin through all possible chars,
     * adding each char in a that is not in b.
     * (This could be O(n^2), but n is small and bounded.)
     */
	साठी ( ch = 0; ch < ctrl.csize; ++ch )
        जर (ccl_contains (a, ch) && !ccl_contains(b, ch))
            ccladd (d, ch);

    /* debug */
    जर (0){
        ख_लिखो(मानक_त्रुटि, "ccl_set_diff (");
            ख_लिखो(मानक_त्रुटि, "\n    ");
            dump_cclp (मानक_त्रुटि, a);
            ख_लिखो(मानक_त्रुटि, "\n    ");
            dump_cclp (मानक_त्रुटि, b);
            ख_लिखो(मानक_त्रुटि, "\n    ");
            dump_cclp (मानक_त्रुटि, d);
        ख_लिखो(मानक_त्रुटि, "\n)\n");
    }
    परत d;
}

/* ccl_set_union - create a new ccl as the set union of the two given ccls. */
पूर्णांक
ccl_set_union (पूर्णांक a, पूर्णांक b)
{
    पूर्णांक  d, i;

    /* create new class  */
    d = cclinit();

    /* Add all of a */
    साठी (i = 0; i < ccllen[a]; ++i)
		ccladd (d, ccltbl[cclmap[a] + i]);

    /* Add all of b */
    साठी (i = 0; i < ccllen[b]; ++i)
		ccladd (d, ccltbl[cclmap[b] + i]);

    /* debug */
    जर (0){
        ख_लिखो(मानक_त्रुटि, "ccl_set_union (%d + %d = %d", a, b, d);
            ख_लिखो(मानक_त्रुटि, "\n    ");
            dump_cclp (मानक_त्रुटि, a);
            ख_लिखो(मानक_त्रुटि, "\n    ");
            dump_cclp (मानक_त्रुटि, b);
            ख_लिखो(मानक_त्रुटि, "\n    ");
            dump_cclp (मानक_त्रुटि, d);
        ख_लिखो(मानक_त्रुटि, "\n)\n");
    }
    परत d;
}


/* cclinit - return an empty ccl */

पूर्णांक     cclinit (शून्य)
{
	जर (++lastccl >= current_maxccls) {
		current_maxccls += MAX_CCLS_INCREMENT;

		++अंक_reallocs;

		cclmap =
			reallocate_integer_array (cclmap, current_maxccls);
		ccllen =
			reallocate_integer_array (ccllen, current_maxccls);
		cclng = reallocate_integer_array (cclng, current_maxccls);
		ccl_has_nl = reallocate_array(ccl_has_nl, current_maxccls, आकार(अक्षर));
	}

	जर (lastccl == 1)
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

	परत lastccl;
}


/* cclnegate - negate the given ccl */

शून्य    cclnegate (पूर्णांक cclp)
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

शून्य    list_character_set (खाता *file, पूर्णांक cset[])
{
	पूर्णांक i;

	अ_दो ('[', file);

	साठी (i = 0; i < ctrl.csize; ++i) {
		जर (cset[i]) {
			पूर्णांक start_char = i;

			अ_दो (' ', file);

			ख_माला_दो (readable_form (i), file);

			पर्यंत (++i < ctrl.csize && cset[i]) ;

			जर (i - 1 > start_char)
				/* this was a run */
				ख_लिखो (file, "-%s",
					 readable_form (i - 1));

			अ_दो (' ', file);
		}
	}

	अ_दो (']', file);
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
bool range_covers_case (पूर्णांक c1, पूर्णांक c2)
{
	पूर्णांक     i, o;

	साठी (i = c1; i <= c2; i++) {
		जर (has_case (i)) {
			o = reverse_case (i);
			जर (o < c1 || c2 < o)
				परत false;
		}
	}
	परत true;
}

/** Reverse the case of a character, if possible.
 * @return c if case-reversal does not apply.
 */
पूर्णांक reverse_case (पूर्णांक c)
{
	परत है_बड़ा (c) ? छोटे (c) : (है_छोटा (c) ? बड़े (c) : c);
}

/** Return true if c is uppercase or lowercase. */
bool has_case (पूर्णांक c)
{
	परत (है_बड़ा (c) || है_छोटा (c)) ? true : false;
}
