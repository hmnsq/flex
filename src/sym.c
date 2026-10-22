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

#شامل "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

ساختار hash_entry {
	ساختار hash_entry *next;
	نویسه   *name;
	نویسه   *str_val;
	صحیح     int_val;
};

تعریفنوع ساختار hash_entry **hash_table;

#define NAME_TABLE_HASH_SIZE 101
#define START_COND_HASH_SIZE 101
#define CCL_HASH_SIZE 101

ایستا ساختار hash_entry *ndtbl[NAME_TABLE_HASH_SIZE] = {پوچ};
ایستا ساختار hash_entry *sctbl[START_COND_HASH_SIZE] = {پوچ};
ایستا ساختار hash_entry *ccltab[CCL_HASH_SIZE] = {پوچ};


/* declare functions that have forward references */

ایستا صحیح addsym(ثابت نویسه *, ثابت نویسه *, صحیح, hash_table, size_t);
ایستا ساختار hash_entry *findsym (ثابت نویسه *sym, hash_table table,
				   size_t table_size);
ایستا size_t hashfunct(ثابت نویسه *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

ایستا صحیح addsym (ثابت نویسه *sym, ثابت نویسه *str_def, صحیح int_def, hash_table table, size_t table_size)
{
	size_t hash_val = hashfunct (sym, table_size);
	ساختار hash_entry *sym_entry = table[hash_val];
	ساختار hash_entry *new_entry;

	وقتی (sym_entry) {
		اگر (!strcmp (sym, sym_entry->name)) {	/* entry already exists */
			بازگشت -1;
		}

		sym_entry = sym_entry->next;
	}

	/* create new entry */
	new_entry = malloc(اندازه(ساختار hash_entry));

	اگر (new_entry == پوچ)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->next = table[hash_val];
	new_entry->name = xstrdup(sym);
	اگر (str_def == پوچ) {
		new_entry->str_val = پوچ;
	} وگرنه {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	بازگشت 0;
}


/* cclinstal - save the text of a character class */

تهی    cclinstal (نویسه ccltxt[], صحیح cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(تهی) addsym(ccltxt, پوچ, cclnum, ccltab, CCL_HASH_SIZE);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

صحیح     ccllookup (نویسه ccltxt[])
{
	بازگشت findsym (ccltxt, ccltab, CCL_HASH_SIZE)->int_val;
}


/* findsym - find symbol in symbol table */

ایستا ساختار hash_entry *findsym (ثابت نویسه *sym, hash_table table, size_t table_size)
{
	ایستا ساختار hash_entry empty_entry = {
		پوچ, پوچ, پوچ, 0,
	};
	ساختار hash_entry *sym_entry =

		table[hashfunct (sym, table_size)];

	وقتی (sym_entry) {
		اگر (!strcmp (sym, sym_entry->name))
			بازگشت sym_entry;
		sym_entry = sym_entry->next;
	}

	بازگشت &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

ایستا size_t hashfunct (ثابت نویسه *str, size_t hash_size)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	وقتی (str[locstr] != '\0') {
		hashval = (hashval << 1) + (unsigned نویسه) str[locstr++];
		hashval %= hash_size;
	}

	بازگشت hashval;
}


/* ndinstal - install a name definition */

تهی    ndinstal (ثابت نویسه *name, نویسه definition[])
{
	اگر (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_SIZE)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

نویسه   *ndlookup (ثابت نویسه *nd)
{
	بازگشت findsym (nd, ndtbl, NAME_TABLE_HASH_SIZE)->str_val;
}


/* scextend - increase the maximum number of start conditions */

تهی    scextend (تهی)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++رقم_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		اندازه(نویسه));
	sceof = reallocate_array(sceof, current_max_scs, اندازه(نویسه));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

تهی    scinstal (ثابت نویسه *str, bool sc_is_exclusive)
{

	اگر (++lastsc >= current_max_scs)
		scextend ();

	اگر (addsym(str, پوچ, lastsc, sctbl, START_COND_HASH_SIZE)) {
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

صحیح     sclookup (ثابت نویسه *str)
{
	بازگشت findsym (str, sctbl, START_COND_HASH_SIZE)->int_val;
}
