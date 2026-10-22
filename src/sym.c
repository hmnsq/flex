/* sym - symbol table routines */

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

#ಅನ್ತರ್ಭಾವ "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

ರಚನೆ hash_ನಮೂದು {
	ರಚನೆ hash_ನಮೂದು *ಮುಂದಿನ;
	ಅಕ್ಷರ   *name;
	ಅಕ್ಷರ   *str_val;
	ಪೂರ್ಣಾಂಕ     int_val;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ hash_ನಮೂದು **hash_ಕೋಷ್ಟಕ;

#ವ್ಯಾಖ್ಯಾನಿಸು NAME_ಕೋಷ್ಟಕ_HASH_ಗಾತ್ರ 101
#ವ್ಯಾಖ್ಯಾನಿಸು ಆರಂಭ_COND_HASH_ಗಾತ್ರ 101
#ವ್ಯಾಖ್ಯಾನಿಸು CCL_HASH_ಗಾತ್ರ 101

ಸ್ಥಿರ ರಚನೆ hash_ನಮೂದು *ndtbl[NAME_ಕೋಷ್ಟಕ_HASH_ಗಾತ್ರ] = {ಖಾಲಿ};
ಸ್ಥಿರ ರಚನೆ hash_ನಮೂದು *sctbl[ಆರಂಭ_COND_HASH_ಗಾತ್ರ] = {ಖಾಲಿ};
ಸ್ಥಿರ ರಚನೆ hash_ನಮೂದು *ccltab[CCL_HASH_ಗಾತ್ರ] = {ಖಾಲಿ};


/* declare functions that have forward references */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ addsym(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ, hash_ಕೋಷ್ಟಕ, size_t);
ಸ್ಥಿರ ರಚನೆ hash_ನಮೂದು *findsym (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *sym, hash_ಕೋಷ್ಟಕ ಕೋಷ್ಟಕ,
				   size_t ಕೋಷ್ಟಕ_ಗಾತ್ರ);
ಸ್ಥಿರ size_t hashfunct(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ addsym (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *sym, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str_def, ಪೂರ್ಣಾಂಕ int_def, hash_ಕೋಷ್ಟಕ ಕೋಷ್ಟಕ, size_t ಕೋಷ್ಟಕ_ಗಾತ್ರ)
{
	size_t hash_val = hashfunct (sym, ಕೋಷ್ಟಕ_ಗಾತ್ರ);
	ರಚನೆ hash_ನಮೂದು *sym_ನಮೂದು = ಕೋಷ್ಟಕ[hash_val];
	ರಚನೆ hash_ನಮೂದು *new_ನಮೂದು;

	ಆಗ (sym_ನಮೂದು) {
		ಆದರೆ (!strcmp (sym, sym_ನಮೂದು->name)) {	/* entry already exists */
			ಹಿಂತಿರುಗಿ -1;
		}

		sym_ನಮೂದು = sym_ನಮೂದು->ಮುಂದಿನ;
	}

	/* create new entry */
	new_ನಮೂದು = ಸ್ಮರಣೆ_ಕೊಡು(ಗಾತ್ರ(ರಚನೆ hash_ನಮೂದು));

	ಆದರೆ (new_ನಮೂದು == ಖಾಲಿ)
		flexfatal (_("symbol table memory allocation failed"));

	new_ನಮೂದು->ಮುಂದಿನ = ಕೋಷ್ಟಕ[hash_val];
	new_ನಮೂದು->name = xstrdup(sym);
	ಆದರೆ (str_def == ಖಾಲಿ) {
		new_ನಮೂದು->str_val = ಖಾಲಿ;
	} ಇಲ್ಲದಿದ್ದರೆ {
		new_ನಮೂದು->str_val = xstrdup(str_def);
	}
	new_ನಮೂದು->int_val = int_def;

	ಕೋಷ್ಟಕ[hash_val] = new_ನಮೂದು;

	ಹಿಂತಿರುಗಿ 0;
}


/* cclinstal - save the text of a character class */

ಶೂನ್ಯ    cclinstal (ಅಕ್ಷರ ccltxt[], ಪೂರ್ಣಾಂಕ cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(ಶೂನ್ಯ) addsym(ccltxt, ಖಾಲಿ, cclnum, ccltab, CCL_HASH_ಗಾತ್ರ);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

ಪೂರ್ಣಾಂಕ     ccllookup (ಅಕ್ಷರ ccltxt[])
{
	ಹಿಂತಿರುಗಿ findsym (ccltxt, ccltab, CCL_HASH_ಗಾತ್ರ)->int_val;
}


/* findsym - find symbol in symbol table */

ಸ್ಥಿರ ರಚನೆ hash_ನಮೂದು *findsym (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *sym, hash_ಕೋಷ್ಟಕ ಕೋಷ್ಟಕ, size_t ಕೋಷ್ಟಕ_ಗಾತ್ರ)
{
	ಸ್ಥಿರ ರಚನೆ hash_ನಮೂದು ಖಾಲಿಗಳು_ನಮೂದು = {
		ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, 0,
	};
	ರಚನೆ hash_ನಮೂದು *sym_ನಮೂದು =

		ಕೋಷ್ಟಕ[hashfunct (sym, ಕೋಷ್ಟಕ_ಗಾತ್ರ)];

	ಆಗ (sym_ನಮೂದು) {
		ಆದರೆ (!strcmp (sym, sym_ನಮೂದು->name))
			ಹಿಂತಿರುಗಿ sym_ನಮೂದು;
		sym_ನಮೂದು = sym_ನಮೂದು->ಮುಂದಿನ;
	}

	ಹಿಂತಿರುಗಿ &ಖಾಲಿಗಳು_ನಮೂದು;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

ಸ್ಥಿರ size_t hashfunct (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, size_t hash_ಗಾತ್ರ)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	ಆಗ (str[locstr] != '\0') {
		hashval = (hashval << 1) + (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ) str[locstr++];
		hashval %= hash_ಗಾತ್ರ;
	}

	ಹಿಂತಿರುಗಿ hashval;
}


/* ndinstal - install a name definition */

ಶೂನ್ಯ    ndinstal (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಅಕ್ಷರ definition[])
{
	ಆದರೆ (addsym(name, definition, 0, ndtbl, NAME_ಕೋಷ್ಟಕ_HASH_ಗಾತ್ರ)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

ಅಕ್ಷರ   *ndlookup (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *nd)
{
	ಹಿಂತಿರುಗಿ findsym (nd, ndtbl, NAME_ಕೋಷ್ಟಕ_HASH_ಗಾತ್ರ)->str_val;
}


/* scextend - increase the maximum number of start conditions */

ಶೂನ್ಯ    scextend (ಶೂನ್ಯ)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++ಅಂಕೆ_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		ಗಾತ್ರ(ಅಕ್ಷರ));
	sceof = reallocate_array(sceof, current_max_scs, ಗಾತ್ರ(ಅಕ್ಷರ));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

ಶೂನ್ಯ    scinstal (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, bool sc_is_exclusive)
{

	ಆದರೆ (++lastsc >= current_max_scs)
		scextend ();

	ಆದರೆ (addsym(str, ಖಾಲಿ, lastsc, sctbl, ಆರಂಭ_COND_HASH_ಗಾತ್ರ)) {
		format_pinpoint_ಸಂದೇಶ (
			_("start condition %s declared twice"), str);
	}
	scname[lastsc] = sctbl[hashfunct(str, ಆರಂಭ_COND_HASH_ಗಾತ್ರ)]->name;

	scset[lastsc] = mkstate (SYM_EPSILON);
	scbol[lastsc] = mkstate (SYM_EPSILON);
	scxclu[lastsc] = sc_is_exclusive ? 1 : 0;
	sceof[lastsc] = false;
}


/* sclookup - lookup the number associated with a start condition
 *
 * Returns 0 if no such start condition.
 */

ಪೂರ್ಣಾಂಕ     sclookup (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
	ಹಿಂತಿರುಗಿ findsym (str, sctbl, ಆರಂಭ_COND_HASH_ಗಾತ್ರ)->int_val;
}
