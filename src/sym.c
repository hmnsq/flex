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

#অন্তর্ভাৱ "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

সংরচনা hash_entry {
	সংরচনা hash_entry *next;
	ৱর্ণ   *name;
	ৱর্ণ   *str_val;
	পূর্ণাঙ্ক     int_val;
};

প্রকারনির্দেশ সংরচনা hash_entry **hash_table;

#define NAME_TABLE_HASH_SIZE 101
#define START_COND_HASH_SIZE 101
#define CCL_HASH_SIZE 101

স্থির সংরচনা hash_entry *ndtbl[NAME_TABLE_HASH_SIZE] = {রিক্ত};
স্থির সংরচনা hash_entry *sctbl[START_COND_HASH_SIZE] = {রিক্ত};
স্থির সংরচনা hash_entry *ccltab[CCL_HASH_SIZE] = {রিক্ত};


/* declare functions that have forward references */

স্থির পূর্ণাঙ্ক addsym(ধ্রুৱ ৱর্ণ *, ধ্রুৱ ৱর্ণ *, পূর্ণাঙ্ক, hash_table, size_t);
স্থির সংরচনা hash_entry *findsym (ধ্রুৱ ৱর্ণ *sym, hash_table table,
				   size_t table_size);
স্থির size_t hashfunct(ধ্রুৱ ৱর্ণ *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

স্থির পূর্ণাঙ্ক addsym (ধ্রুৱ ৱর্ণ *sym, ধ্রুৱ ৱর্ণ *str_def, পূর্ণাঙ্ক int_def, hash_table table, size_t table_size)
{
	size_t hash_val = hashfunct (sym, table_size);
	সংরচনা hash_entry *sym_entry = table[hash_val];
	সংরচনা hash_entry *new_entry;

	যেতিয়ালৈ (sym_entry) {
		যদি (!strcmp (sym, sym_entry->name)) {	/* entry already exists */
			ঘূৰাই -1;
		}

		sym_entry = sym_entry->next;
	}

	/* create new entry */
	new_entry = malloc(পরিমাণ(সংরচনা hash_entry));

	যদি (new_entry == রিক্ত)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->next = table[hash_val];
	new_entry->name = xstrdup(sym);
	যদি (str_def == রিক্ত) {
		new_entry->str_val = রিক্ত;
	} অন্যথা {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	ঘূৰাই 0;
}


/* cclinstal - save the text of a character class */

শূন্য    cclinstal (ৱর্ণ ccltxt[], পূর্ণাঙ্ক cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(শূন্য) addsym(ccltxt, রিক্ত, cclnum, ccltab, CCL_HASH_SIZE);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

পূর্ণাঙ্ক     ccllookup (ৱর্ণ ccltxt[])
{
	ঘূৰাই findsym (ccltxt, ccltab, CCL_HASH_SIZE)->int_val;
}


/* findsym - find symbol in symbol table */

স্থির সংরচনা hash_entry *findsym (ধ্রুৱ ৱর্ণ *sym, hash_table table, size_t table_size)
{
	স্থির সংরচনা hash_entry empty_entry = {
		রিক্ত, রিক্ত, রিক্ত, 0,
	};
	সংরচনা hash_entry *sym_entry =

		table[hashfunct (sym, table_size)];

	যেতিয়ালৈ (sym_entry) {
		যদি (!strcmp (sym, sym_entry->name))
			ঘূৰাই sym_entry;
		sym_entry = sym_entry->next;
	}

	ঘূৰাই &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

স্থির size_t hashfunct (ধ্রুৱ ৱর্ণ *str, size_t hash_size)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	যেতিয়ালৈ (str[locstr] != '\0') {
		hashval = (hashval << 1) + (unsigned ৱর্ণ) str[locstr++];
		hashval %= hash_size;
	}

	ঘূৰাই hashval;
}


/* ndinstal - install a name definition */

শূন্য    ndinstal (ধ্রুৱ ৱর্ণ *name, ৱর্ণ definition[])
{
	যদি (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_SIZE)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

ৱর্ণ   *ndlookup (ধ্রুৱ ৱর্ণ *nd)
{
	ঘূৰাই findsym (nd, ndtbl, NAME_TABLE_HASH_SIZE)->str_val;
}


/* scextend - increase the maximum number of start conditions */

শূন্য    scextend (শূন্য)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++অঙ্ক_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		পরিমাণ(ৱর্ণ));
	sceof = reallocate_array(sceof, current_max_scs, পরিমাণ(ৱর্ণ));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

শূন্য    scinstal (ধ্রুৱ ৱর্ণ *str, bool sc_is_exclusive)
{

	যদি (++lastsc >= current_max_scs)
		scextend ();

	যদি (addsym(str, রিক্ত, lastsc, sctbl, START_COND_HASH_SIZE)) {
		format_pinpoint_message (
			_("start condition %s declared twice"), str);
	}
	scname[lastsc] = sctbl[hashfunct(str, START_COND_HASH_SIZE)]->name;

	scset[lastsc] = mkstate (SYM_EPSILON);
	scbol[lastsc] = mkstate (SYM_EPSILON);
	scxclu[lastsc] = sc_is_exclusive ? 1 : 0;
	sceof[lastsc] = false;
}


/* sclookup - lookup the number associated with a start condition
 *
 * Returns 0 if no such start condition.
 */

পূর্ণাঙ্ক     sclookup (ধ্রুৱ ৱর্ণ *str)
{
	ঘূৰাই findsym (str, sctbl, START_COND_HASH_SIZE)->int_val;
}
