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

#include "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

sa_nracanaa hash_entry {
	sa_nracanaa hash_entry *next;
	var_na   *name;
	var_na   *str_val;
	puur_naa_nka     int_val;
};

typedef sa_nracanaa hash_entry **hash_table;

#define NAME_TABLE_HASH_SIZE 101
#define START_COND_HASH_SIZE 101
#define CCL_HASH_SIZE 101

static sa_nracanaa hash_entry *ndtbl[NAME_TABLE_HASH_SIZE] = {NULL};
static sa_nracanaa hash_entry *sctbl[START_COND_HASH_SIZE] = {NULL};
static sa_nracanaa hash_entry *ccltab[CCL_HASH_SIZE] = {NULL};


/* declare functions that have forward references */

static puur_naa_nka addsym(const var_na *, const var_na *, puur_naa_nka, hash_table, size_t);
static sa_nracanaa hash_entry *findsym (const var_na *sym, hash_table table,
				   size_t table_size);
static size_t hashfunct(const var_na *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

static puur_naa_nka addsym (const var_na *sym, const var_na *str_def, puur_naa_nka int_def, hash_table table, size_t table_size)
{
	size_t hash_val = hashfunct (sym, table_size);
	sa_nracanaa hash_entry *sym_entry = table[hash_val];
	sa_nracanaa hash_entry *new_entry;

	ᨀᨛ (sym_entry) {
		ᨀᨘ (!strcmp (sym, sym_entry->name)) {	/* entry already exists */
			ᨀᨘᨒ -1;
		}

		sym_entry = sym_entry->next;
	}

	/* create new entry */
	new_entry = malloc(parimaa_na(sa_nracanaa hash_entry));

	ᨀᨘ (new_entry == NULL)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->next = table[hash_val];
	new_entry->name = xstrdup(sym);
	ᨀᨘ (str_def == NULL) {
		new_entry->str_val = NULL;
	} ᨀᨘᨁ {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	ᨀᨘᨒ 0;
}


/* cclinstal - save the text of a character class */

void    cclinstal (var_na ccltxt[], puur_naa_nka cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(void) addsym(ccltxt, NULL, cclnum, ccltab, CCL_HASH_SIZE);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

puur_naa_nka     ccllookup (var_na ccltxt[])
{
	ᨀᨘᨒ findsym (ccltxt, ccltab, CCL_HASH_SIZE)->int_val;
}


/* findsym - find symbol in symbol table */

static sa_nracanaa hash_entry *findsym (const var_na *sym, hash_table table, size_t table_size)
{
	static sa_nracanaa hash_entry empty_entry = {
		NULL, NULL, NULL, 0,
	};
	sa_nracanaa hash_entry *sym_entry =

		table[hashfunct (sym, table_size)];

	ᨀᨛ (sym_entry) {
		ᨀᨘ (!strcmp (sym, sym_entry->name))
			ᨀᨘᨒ sym_entry;
		sym_entry = sym_entry->next;
	}

	ᨀᨘᨒ &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

static size_t hashfunct (const var_na *str, size_t hash_size)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	ᨀᨛ (str[locstr] != '\0') {
		hashval = (hashval << 1) + (unsigned var_na) str[locstr++];
		hashval %= hash_size;
	}

	ᨀᨘᨒ hashval;
}


/* ndinstal - install a name definition */

void    ndinstal (const var_na *name, var_na definition[])
{
	ᨀᨘ (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_SIZE)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

var_na   *ndlookup (const var_na *nd)
{
	ᨀᨘᨒ findsym (nd, ndtbl, NAME_TABLE_HASH_SIZE)->str_val;
}


/* scextend - increase the maximum number of start conditions */

void    scextend (void)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++num_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		parimaa_na(var_na));
	sceof = reallocate_array(sceof, current_max_scs, parimaa_na(var_na));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

void    scinstal (const var_na *str, bool sc_is_exclusive)
{

	ᨀᨘ (++lastsc >= current_max_scs)
		scextend ();

	ᨀᨘ (addsym(str, NULL, lastsc, sctbl, START_COND_HASH_SIZE)) {
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

puur_naa_nka     sclookup (const var_na *str)
{
	ᨀᨘᨒ findsym (str, sctbl, START_COND_HASH_SIZE)->int_val;
}
