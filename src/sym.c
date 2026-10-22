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

#அந்தர்பாவ "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

கட்டமைப்பு hash_entry {
	கட்டமைப்பு hash_entry *next;
	எழுத்து   *name;
	எழுத்து   *str_val;
	முழு     int_val;
};

வகைவரை கட்டமைப்பு hash_entry **hash_table;

#define NAME_TABLE_HASH_SIZE 101
#define START_COND_HASH_SIZE 101
#define CCL_HASH_SIZE 101

நிலையான கட்டமைப்பு hash_entry *ndtbl[NAME_TABLE_HASH_SIZE] = {வெற்று};
நிலையான கட்டமைப்பு hash_entry *sctbl[START_COND_HASH_SIZE] = {வெற்று};
நிலையான கட்டமைப்பு hash_entry *ccltab[CCL_HASH_SIZE] = {வெற்று};


/* declare functions that have forward references */

நிலையான முழு addsym(மாறிலி எழுத்து *, மாறிலி எழுத்து *, முழு, hash_table, size_t);
நிலையான கட்டமைப்பு hash_entry *findsym (மாறிலி எழுத்து *sym, hash_table table,
				   size_t table_size);
நிலையான size_t hashfunct(மாறிலி எழுத்து *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

நிலையான முழு addsym (மாறிலி எழுத்து *sym, மாறிலி எழுத்து *str_def, முழு int_def, hash_table table, size_t table_size)
{
	size_t hash_val = hashfunct (sym, table_size);
	கட்டமைப்பு hash_entry *sym_entry = table[hash_val];
	கட்டமைப்பு hash_entry *new_entry;

	போது (sym_entry) {
		எனில் (!strcmp (sym, sym_entry->name)) {	/* entry already exists */
			திரும்பு -1;
		}

		sym_entry = sym_entry->next;
	}

	/* create new entry */
	new_entry = malloc(அளவு(கட்டமைப்பு hash_entry));

	எனில் (new_entry == வெற்று)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->next = table[hash_val];
	new_entry->name = xstrdup(sym);
	எனில் (str_def == வெற்று) {
		new_entry->str_val = வெற்று;
	} இல்லையெனில் {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	திரும்பு 0;
}


/* cclinstal - save the text of a character class */

வெறுமை    cclinstal (எழுத்து ccltxt[], முழு cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(வெறுமை) addsym(ccltxt, வெற்று, cclnum, ccltab, CCL_HASH_SIZE);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

முழு     ccllookup (எழுத்து ccltxt[])
{
	திரும்பு findsym (ccltxt, ccltab, CCL_HASH_SIZE)->int_val;
}


/* findsym - find symbol in symbol table */

நிலையான கட்டமைப்பு hash_entry *findsym (மாறிலி எழுத்து *sym, hash_table table, size_t table_size)
{
	நிலையான கட்டமைப்பு hash_entry empty_entry = {
		வெற்று, வெற்று, வெற்று, 0,
	};
	கட்டமைப்பு hash_entry *sym_entry =

		table[hashfunct (sym, table_size)];

	போது (sym_entry) {
		எனில் (!strcmp (sym, sym_entry->name))
			திரும்பு sym_entry;
		sym_entry = sym_entry->next;
	}

	திரும்பு &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

நிலையான size_t hashfunct (மாறிலி எழுத்து *str, size_t hash_size)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	போது (str[locstr] != '\0') {
		hashval = (hashval << 1) + (unsigned எழுத்து) str[locstr++];
		hashval %= hash_size;
	}

	திரும்பு hashval;
}


/* ndinstal - install a name definition */

வெறுமை    ndinstal (மாறிலி எழுத்து *name, எழுத்து definition[])
{
	எனில் (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_SIZE)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

எழுத்து   *ndlookup (மாறிலி எழுத்து *nd)
{
	திரும்பு findsym (nd, ndtbl, NAME_TABLE_HASH_SIZE)->str_val;
}


/* scextend - increase the maximum number of start conditions */

வெறுமை    scextend (வெறுமை)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++இலக்கம்_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		அளவு(எழுத்து));
	sceof = reallocate_array(sceof, current_max_scs, அளவு(எழுத்து));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

வெறுமை    scinstal (மாறிலி எழுத்து *str, bool sc_is_exclusive)
{

	எனில் (++lastsc >= current_max_scs)
		scextend ();

	எனில் (addsym(str, வெற்று, lastsc, sctbl, START_COND_HASH_SIZE)) {
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

முழு     sclookup (மாறிலி எழுத்து *str)
{
	திரும்பு findsym (str, sctbl, START_COND_HASH_SIZE)->int_val;
}
