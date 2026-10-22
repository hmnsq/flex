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

#અન્તર્ભાવ "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

સંરચના hash_entry {
	સંરચના hash_entry *next;
	અક્ષર   *name;
	અક્ષર   *str_val;
	પૂર્ણાંક     int_val;
};

પ્રકારવ્યાખ્યા સંરચના hash_entry **hash_table;

#define NAME_TABLE_HASH_SIZE 101
#define START_COND_HASH_SIZE 101
#define CCL_HASH_SIZE 101

સ્થિર સંરચના hash_entry *ndtbl[NAME_TABLE_HASH_SIZE] = {ખાલી};
સ્થિર સંરચના hash_entry *sctbl[START_COND_HASH_SIZE] = {ખાલી};
સ્થિર સંરચના hash_entry *ccltab[CCL_HASH_SIZE] = {ખાલી};


/* declare functions that have forward references */

સ્થિર પૂર્ણાંક addsym(અચલ અક્ષર *, અચલ અક્ષર *, પૂર્ણાંક, hash_table, size_t);
સ્થિર સંરચના hash_entry *findsym (અચલ અક્ષર *sym, hash_table table,
				   size_t table_size);
સ્થિર size_t hashfunct(અચલ અક્ષર *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

સ્થિર પૂર્ણાંક addsym (અચલ અક્ષર *sym, અચલ અક્ષર *str_def, પૂર્ણાંક int_def, hash_table table, size_t table_size)
{
	size_t hash_val = hashfunct (sym, table_size);
	સંરચના hash_entry *sym_entry = table[hash_val];
	સંરચના hash_entry *new_entry;

	જ્યારે (sym_entry) {
		જો (!strcmp (sym, sym_entry->name)) {	/* entry already exists */
			પાછા -1;
		}

		sym_entry = sym_entry->next;
	}

	/* create new entry */
	new_entry = malloc(કદ(સંરચના hash_entry));

	જો (new_entry == ખાલી)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->next = table[hash_val];
	new_entry->name = xstrdup(sym);
	જો (str_def == ખાલી) {
		new_entry->str_val = ખાલી;
	} નહીંતર {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	પાછા 0;
}


/* cclinstal - save the text of a character class */

શૂન્ય    cclinstal (અક્ષર ccltxt[], પૂર્ણાંક cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(શૂન્ય) addsym(ccltxt, ખાલી, cclnum, ccltab, CCL_HASH_SIZE);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

પૂર્ણાંક     ccllookup (અક્ષર ccltxt[])
{
	પાછા findsym (ccltxt, ccltab, CCL_HASH_SIZE)->int_val;
}


/* findsym - find symbol in symbol table */

સ્થિર સંરચના hash_entry *findsym (અચલ અક્ષર *sym, hash_table table, size_t table_size)
{
	સ્થિર સંરચના hash_entry empty_entry = {
		ખાલી, ખાલી, ખાલી, 0,
	};
	સંરચના hash_entry *sym_entry =

		table[hashfunct (sym, table_size)];

	જ્યારે (sym_entry) {
		જો (!strcmp (sym, sym_entry->name))
			પાછા sym_entry;
		sym_entry = sym_entry->next;
	}

	પાછા &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

સ્થિર size_t hashfunct (અચલ અક્ષર *str, size_t hash_size)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	જ્યારે (str[locstr] != '\0') {
		hashval = (hashval << 1) + (unsigned અક્ષર) str[locstr++];
		hashval %= hash_size;
	}

	પાછા hashval;
}


/* ndinstal - install a name definition */

શૂન્ય    ndinstal (અચલ અક્ષર *name, અક્ષર definition[])
{
	જો (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_SIZE)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

અક્ષર   *ndlookup (અચલ અક્ષર *nd)
{
	પાછા findsym (nd, ndtbl, NAME_TABLE_HASH_SIZE)->str_val;
}


/* scextend - increase the maximum number of start conditions */

શૂન્ય    scextend (શૂન્ય)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++અંક_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		કદ(અક્ષર));
	sceof = reallocate_array(sceof, current_max_scs, કદ(અક્ષર));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

શૂન્ય    scinstal (અચલ અક્ષર *str, bool sc_is_exclusive)
{

	જો (++lastsc >= current_max_scs)
		scextend ();

	જો (addsym(str, ખાલી, lastsc, sctbl, START_COND_HASH_SIZE)) {
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

પૂર્ણાંક     sclookup (અચલ અક્ષર *str)
{
	પાછા findsym (str, sctbl, START_COND_HASH_SIZE)->int_val;
}
