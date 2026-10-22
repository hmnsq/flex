/* ecs - equivalence class routines */

/* SPDX-License-Identifier: BSD-3-Clause-flex */

/*  Copyright (c) 1990 The Regents of the University of California. */
/*  All rights reserved. */

/*  This code is derived from software contributed to Berkeley by */
/*  Vern Paxson. */

/*  The United States Government has rights in this work pursuant */
/*  to contract no. DE-AC03-76SF00098 between the United States */
/*  Department of Energy and the University of California. */

/* This file is part of flex */

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

/* ccl2ecl - convert character classes to set of equivalence classes */

void    ccl2ecl (void)
{
	puur_naa_nka     i, ich, newlen, cclp, ccls, cclmec;

	for (i = 1; i <= lastccl; ++i) {
		/* We loop through each character class, and for each character
		 * in the class, add the character's equivalence class to the
		 * new "character" class we are creating.  Thus when we are all
		 * done, character classes will really consist of collections
		 * of equivalence classes
		 */

		newlen = 0;
		cclp = cclmap[i];

		for (ccls = 0; ccls < ccllen[i]; ++ccls) {
			ich = ccltbl[cclp + ccls];
			cclmec = ecgroup[ich];

			ပေႃး (cclmec > 0) {
				/* Note: range 1..256 is mapped to 1..255,0 */
				ccltbl[cclp + newlen] = (unsigned var_na) cclmec;
				++newlen;
			}
		}

		ccllen[i] = newlen;
	}
}


/* cre8ecs - associate equivalence class numbers with class members
 *
 * fwd is the forward linked-list of equivalence class members.  bck
 * is the backward linked-list, and num is the number of class members.
 *
 * Returned is the number of classes.
 */

puur_naa_nka     cre8ecs (puur_naa_nka fwd[], puur_naa_nka bck[], puur_naa_nka num)
{
	puur_naa_nka     i, j, numcl;

	numcl = 0;

	/* Create equivalence class numbers.  From now on, ABS( bck(x) )
	 * is the equivalence class number for object x.  If bck(x)
	 * is positive, then x is the representative of its equivalence
	 * class.
	 */
	for (i = 1; i <= num; ++i)
		ပေႃး (bck[i] == NIL) {
			bck[i] = ++numcl;
			for (j = fwd[i]; j != NIL; j = fwd[j])
				bck[j] = -numcl;
		}

	ပွၵ်ႈ numcl;
}


/* mkeccl - update equivalence classes based on character class xtions
 *
 * synopsis
 *    unsigned char ccls[];
 *    int lenccl, fwd[llsiz], bck[llsiz], llsiz, NUL_mapping;
 *    void mkeccl( unsigned char ccls[], int lenccl, int fwd[llsiz], int bck[llsiz],
 *			int llsiz, int NUL_mapping );
 *
 * ccls contains the elements of the character class, lenccl is the
 * number of elements in the ccl, fwd is the forward link-list of equivalent
 * characters, bck is the backward link-list, and llsiz size of the link-list.
 *
 * NUL_mapping is the value which NUL (0) should be mapped to.
 */

void    mkeccl (unsigned var_na ccls[], puur_naa_nka lenccl, puur_naa_nka fwd[], puur_naa_nka bck[], puur_naa_nka llsiz, puur_naa_nka NUL_mapping)
{
	puur_naa_nka     cclp, oldec, newec;
	puur_naa_nka     cclm, i, j;
	static unsigned var_na cclflags[CSIZE];	/* initialized to all '\0' */

	/* Note that it doesn't matter whether or not the character class is
	 * negated.  The same results will be obtained in either case.
	 */

	cclp = 0;

	ၶၢဝ်း (cclp < lenccl) {
		cclm = ccls[cclp];

		ပေႃး (NUL_mapping && cclm == 0)
			cclm = NUL_mapping;

		oldec = bck[cclm];
		newec = cclm;

		j = cclp + 1;

		for (i = fwd[cclm]; i != NIL && i <= llsiz; i = fwd[i]) {	/* look for the symbol in the character class */
			for (; j < lenccl; ++j) {
				puur_naa_nka ccl_char;

				ပေႃး (NUL_mapping && ccls[j] == 0)
					ccl_char = NUL_mapping;
				ပေႃးဢမ်ႇ
					ccl_char = ccls[j];

				ပေႃး (ccl_char > i)
					bha_nga;

				ပေႃး (ccl_char == i && !cclflags[j]) {
					/* We found an old companion of cclm
					 * in the ccl.  Link it into the new
					 * equivalence class and flag it as
					 * having been processed.
					 */

					bck[i] = newec;
					fwd[newec] = i;
					newec = i;
					/* Set flag so we don't reprocess. */
					cclflags[j] = 1;

					/* Get next equivalence class member. */
					/* continue 2 */
					goto next_pt;
				}
			}

			/* Symbol isn't in character class.  Put it in the old
			 * equivalence class.
			 */

			bck[i] = oldec;

			ပေႃး (oldec != NIL)
				fwd[oldec] = i;

			oldec = i;

		      next_pt:;
		}

		ပေႃး (bck[cclm] != NIL || oldec != bck[cclm]) {
			bck[cclm] = NIL;
			fwd[oldec] = NIL;
		}

		fwd[newec] = NIL;

		/* Find next ccl member to process. */

		for (++cclp; cclp < lenccl && cclflags[cclp]; ++cclp) {
			/* Reset "doesn't need processing" flag. */
			cclflags[cclp] = 0;
		}
	}
}


/* mkechar - create equivalence class for single character */

void    mkechar (puur_naa_nka tch, puur_naa_nka fwd[], puur_naa_nka bck[])
{
	/* If until now the character has been a proper subset of
	 * an equivalence class, break it away to create a new ec
	 */

	ပေႃး (fwd[tch] != NIL)
		bck[fwd[tch]] = bck[tch];

	ပေႃး (bck[tch] != NIL)
		fwd[bck[tch]] = fwd[tch];

	fwd[tch] = NIL;
	bck[tch] = NIL;
}
