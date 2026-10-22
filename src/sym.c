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

#অন্তর্ভাব "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

কাঠামো hash_entry {
	কাঠামো hash_entry *পরবর্তী;
	অক্ষর   *name;
	অক্ষর   *str_val;
	পূর্ণসংখ্যা     int_val;
};

প্রকারলেখ কাঠামো hash_entry **hash_table;

#define NAME_TABLE_HASH_আকার 101
#define START_COND_HASH_আকার 101
#define CCL_HASH_আকার 101

স্থির কাঠামো hash_entry *ndtbl[NAME_TABLE_HASH_আকার] = {ফাঁকা};
স্থির কাঠামো hash_entry *sctbl[START_COND_HASH_আকার] = {ফাঁকা};
স্থির কাঠামো hash_entry *ccltab[CCL_HASH_আকার] = {ফাঁকা};


/* declare functions that have forward references */

স্থির পূর্ণসংখ্যা addsym(ধ্রুবক অক্ষর *, ধ্রুবক অক্ষর *, পূর্ণসংখ্যা, hash_table, size_t);
স্থির কাঠামো hash_entry *findsym (ধ্রুবক অক্ষর *sym, hash_table table,
				   size_t table_আকার);
স্থির size_t hashfunct(ধ্রুবক অক্ষর *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

স্থির পূর্ণসংখ্যা addsym (ধ্রুবক অক্ষর *sym, ধ্রুবক অক্ষর *str_def, পূর্ণসংখ্যা int_def, hash_table table, size_t table_আকার)
{
	size_t hash_val = hashfunct (sym, table_আকার);
	কাঠামো hash_entry *sym_entry = table[hash_val];
	কাঠামো hash_entry *new_entry;

	যখন (sym_entry) {
		যদি (!strcmp (sym, sym_entry->name)) {	/* entry already exists */
			ফেরত -1;
		}

		sym_entry = sym_entry->পরবর্তী;
	}

	/* create new entry */
	new_entry = malloc(আকার(কাঠামো hash_entry));

	যদি (new_entry == ফাঁকা)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->পরবর্তী = table[hash_val];
	new_entry->name = xstrdup(sym);
	যদি (str_def == ফাঁকা) {
		new_entry->str_val = ফাঁকা;
	} অন্যথা {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	ফেরত 0;
}


/* cclinstal - save the text of a character class */

শূন্য    cclinstal (অক্ষর ccltxt[], পূর্ণসংখ্যা cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(শূন্য) addsym(ccltxt, ফাঁকা, cclnum, ccltab, CCL_HASH_আকার);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

পূর্ণসংখ্যা     ccllookup (অক্ষর ccltxt[])
{
	ফেরত findsym (ccltxt, ccltab, CCL_HASH_আকার)->int_val;
}


/* findsym - find symbol in symbol table */

স্থির কাঠামো hash_entry *findsym (ধ্রুবক অক্ষর *sym, hash_table table, size_t table_আকার)
{
	স্থির কাঠামো hash_entry empty_entry = {
		ফাঁকা, ফাঁকা, ফাঁকা, 0,
	};
	কাঠামো hash_entry *sym_entry =

		table[hashfunct (sym, table_আকার)];

	যখন (sym_entry) {
		যদি (!strcmp (sym, sym_entry->name))
			ফেরত sym_entry;
		sym_entry = sym_entry->পরবর্তী;
	}

	ফেরত &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

স্থির size_t hashfunct (ধ্রুবক অক্ষর *str, size_t hash_আকার)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	যখন (str[locstr] != '\0') {
		hashval = (hashval << 1) + (unsigned অক্ষর) str[locstr++];
		hashval %= hash_আকার;
	}

	ফেরত hashval;
}


/* ndinstal - install a name definition */

শূন্য    ndinstal (ধ্রুবক অক্ষর *name, অক্ষর definition[])
{
	যদি (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_আকার)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

অক্ষর   *ndlookup (ধ্রুবক অক্ষর *nd)
{
	ফেরত findsym (nd, ndtbl, NAME_TABLE_HASH_আকার)->str_val;
}


/* scextend - increase the maximum number of start conditions */

শূন্য    scextend (শূন্য)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++অঙ্ক_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		আকার(অক্ষর));
	sceof = reallocate_array(sceof, current_max_scs, আকার(অক্ষর));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

শূন্য    scinstal (ধ্রুবক অক্ষর *str, bool sc_is_exclusive)
{

	যদি (++lastsc >= current_max_scs)
		scextend ();

	যদি (addsym(str, ফাঁকা, lastsc, sctbl, START_COND_HASH_আকার)) {
		format_pinpoint_message (
			_("start condition %s declared twice"), str);
	}
	scname[lastsc] = sctbl[hashfunct(str, START_COND_HASH_আকার)]->name;

	scset[lastsc] = mkstate (SYM_EPSILON);
	scbol[lastsc] = mkstate (SYM_EPSILON);
	scxclu[lastsc] = sc_is_exclusive ? 1 : 0;
	sceof[lastsc] = false;
}


/* sclookup - lookup the number associated with a start condition
 *
 * Returns 0 if no such start condition.
 */

পূর্ণসংখ্যা     sclookup (ধ্রুবক অক্ষর *str)
{
	ফেরত findsym (str, sctbl, START_COND_HASH_আকার)->int_val;
}
