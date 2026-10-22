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

#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

ਬਣਤਰ hash_ਇੰਦਰਾਜ {
	ਬਣਤਰ hash_ਇੰਦਰਾਜ *ਅਗਲਾ;
	ਅੱਖਰ   *name;
	ਅੱਖਰ   *str_val;
	ਪੂਰਨ     int_val;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ hash_ਇੰਦਰਾਜ **hash_ਸਾਰਣੀ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NAME_ਸਾਰਣੀ_HASH_ਮਾਪ 101
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸ਼ੁਰੂ_COND_HASH_ਮਾਪ 101
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CCL_HASH_ਮਾਪ 101

ਸਥਿਰ ਬਣਤਰ hash_ਇੰਦਰਾਜ *ndtbl[NAME_ਸਾਰਣੀ_HASH_ਮਾਪ] = {ਨਿਰਾ};
ਸਥਿਰ ਬਣਤਰ hash_ਇੰਦਰਾਜ *sctbl[ਸ਼ੁਰੂ_COND_HASH_ਮਾਪ] = {ਨਿਰਾ};
ਸਥਿਰ ਬਣਤਰ hash_ਇੰਦਰਾਜ *ccltab[CCL_HASH_ਮਾਪ] = {ਨਿਰਾ};


/* declare functions that have forward references */

ਸਥਿਰ ਪੂਰਨ addsym(ਅਚਲ ਅੱਖਰ *, ਅਚਲ ਅੱਖਰ *, ਪੂਰਨ, hash_ਸਾਰਣੀ, size_t);
ਸਥਿਰ ਬਣਤਰ hash_ਇੰਦਰਾਜ *findsym (ਅਚਲ ਅੱਖਰ *sym, hash_ਸਾਰਣੀ ਸਾਰਣੀ,
				   size_t ਸਾਰਣੀ_ਮਾਪ);
ਸਥਿਰ size_t hashfunct(ਅਚਲ ਅੱਖਰ *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

ਸਥਿਰ ਪੂਰਨ addsym (ਅਚਲ ਅੱਖਰ *sym, ਅਚਲ ਅੱਖਰ *str_def, ਪੂਰਨ int_def, hash_ਸਾਰਣੀ ਸਾਰਣੀ, size_t ਸਾਰਣੀ_ਮਾਪ)
{
	size_t hash_val = hashfunct (sym, ਸਾਰਣੀ_ਮਾਪ);
	ਬਣਤਰ hash_ਇੰਦਰਾਜ *sym_ਇੰਦਰਾਜ = ਸਾਰਣੀ[hash_val];
	ਬਣਤਰ hash_ਇੰਦਰਾਜ *new_ਇੰਦਰਾਜ;

	ਜਦੋਂ (sym_ਇੰਦਰਾਜ) {
		ਜੇ (!strcmp (sym, sym_ਇੰਦਰਾਜ->name)) {	/* entry already exists */
			ਵਾਪਸ -1;
		}

		sym_ਇੰਦਰਾਜ = sym_ਇੰਦਰਾਜ->ਅਗਲਾ;
	}

	/* create new entry */
	new_ਇੰਦਰਾਜ = ਸਮ੍ਰਿਤੀ_ਦਿਓ(ਆਕਾਰ(ਬਣਤਰ hash_ਇੰਦਰਾਜ));

	ਜੇ (new_ਇੰਦਰਾਜ == ਨਿਰਾ)
		flexfatal (_("symbol table memory allocation failed"));

	new_ਇੰਦਰਾਜ->ਅਗਲਾ = ਸਾਰਣੀ[hash_val];
	new_ਇੰਦਰਾਜ->name = xstrdup(sym);
	ਜੇ (str_def == ਨਿਰਾ) {
		new_ਇੰਦਰਾਜ->str_val = ਨਿਰਾ;
	} ਨਹੀਂਤਾਂ {
		new_ਇੰਦਰਾਜ->str_val = xstrdup(str_def);
	}
	new_ਇੰਦਰਾਜ->int_val = int_def;

	ਸਾਰਣੀ[hash_val] = new_ਇੰਦਰਾਜ;

	ਵਾਪਸ 0;
}


/* cclinstal - save the text of a character class */

ਖਾਲੀ    cclinstal (ਅੱਖਰ ccltxt[], ਪੂਰਨ cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(ਖਾਲੀ) addsym(ccltxt, ਨਿਰਾ, cclnum, ccltab, CCL_HASH_ਮਾਪ);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

ਪੂਰਨ     ccllookup (ਅੱਖਰ ccltxt[])
{
	ਵਾਪਸ findsym (ccltxt, ccltab, CCL_HASH_ਮਾਪ)->int_val;
}


/* findsym - find symbol in symbol table */

ਸਥਿਰ ਬਣਤਰ hash_ਇੰਦਰਾਜ *findsym (ਅਚਲ ਅੱਖਰ *sym, hash_ਸਾਰਣੀ ਸਾਰਣੀ, size_t ਸਾਰਣੀ_ਮਾਪ)
{
	ਸਥਿਰ ਬਣਤਰ hash_ਇੰਦਰਾਜ ਖਾਲੀ_ਥਾਵਾਂ_ਇੰਦਰਾਜ = {
		ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, 0,
	};
	ਬਣਤਰ hash_ਇੰਦਰਾਜ *sym_ਇੰਦਰਾਜ =

		ਸਾਰਣੀ[hashfunct (sym, ਸਾਰਣੀ_ਮਾਪ)];

	ਜਦੋਂ (sym_ਇੰਦਰਾਜ) {
		ਜੇ (!strcmp (sym, sym_ਇੰਦਰਾਜ->name))
			ਵਾਪਸ sym_ਇੰਦਰਾਜ;
		sym_ਇੰਦਰਾਜ = sym_ਇੰਦਰਾਜ->ਅਗਲਾ;
	}

	ਵਾਪਸ &ਖਾਲੀ_ਥਾਵਾਂ_ਇੰਦਰਾਜ;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

ਸਥਿਰ size_t hashfunct (ਅਚਲ ਅੱਖਰ *str, size_t hash_ਮਾਪ)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	ਜਦੋਂ (str[locstr] != '\0') {
		hashval = (hashval << 1) + (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ) str[locstr++];
		hashval %= hash_ਮਾਪ;
	}

	ਵਾਪਸ hashval;
}


/* ndinstal - install a name definition */

ਖਾਲੀ    ndinstal (ਅਚਲ ਅੱਖਰ *name, ਅੱਖਰ definition[])
{
	ਜੇ (addsym(name, definition, 0, ndtbl, NAME_ਸਾਰਣੀ_HASH_ਮਾਪ)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

ਅੱਖਰ   *ndlookup (ਅਚਲ ਅੱਖਰ *nd)
{
	ਵਾਪਸ findsym (nd, ndtbl, NAME_ਸਾਰਣੀ_HASH_ਮਾਪ)->str_val;
}


/* scextend - increase the maximum number of start conditions */

ਖਾਲੀ    scextend (ਖਾਲੀ)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++ਅੰਕ_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		ਆਕਾਰ(ਅੱਖਰ));
	sceof = reallocate_array(sceof, current_max_scs, ਆਕਾਰ(ਅੱਖਰ));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

ਖਾਲੀ    scinstal (ਅਚਲ ਅੱਖਰ *str, bool sc_is_exclusive)
{

	ਜੇ (++lastsc >= current_max_scs)
		scextend ();

	ਜੇ (addsym(str, ਨਿਰਾ, lastsc, sctbl, ਸ਼ੁਰੂ_COND_HASH_ਮਾਪ)) {
		format_pinpoint_ਸੁਨੇਹਾ (
			_("start condition %s declared twice"), str);
	}
	scname[lastsc] = sctbl[hashfunct(str, ਸ਼ੁਰੂ_COND_HASH_ਮਾਪ)]->name;

	scset[lastsc] = mkstate (SYM_EPSILON);
	scbol[lastsc] = mkstate (SYM_EPSILON);
	scxclu[lastsc] = sc_is_exclusive ? 1 : 0;
	sceof[lastsc] = false;
}


/* sclookup - lookup the number associated with a start condition
 *
 * Returns 0 if no such start condition.
 */

ਪੂਰਨ     sclookup (ਅਚਲ ਅੱਖਰ *str)
{
	ਵਾਪਸ findsym (str, sctbl, ਸ਼ੁਰੂ_COND_HASH_ਮਾਪ)->int_val;
}
