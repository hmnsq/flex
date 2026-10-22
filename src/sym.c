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

#ଅନ୍ତର୍ଭାଵ "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

ସଂରଚନା hash_entry {
	ସଂରଚନା hash_entry *next;
	ଅକ୍ଷର   *name;
	ଅକ୍ଷର   *str_val;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     int_val;
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା hash_entry **hash_table;

#define NAME_TABLE_HASH_SIZE 101
#define START_COND_HASH_SIZE 101
#define CCL_HASH_SIZE 101

ସ୍ଥିର ସଂରଚନା hash_entry *ndtbl[NAME_TABLE_HASH_SIZE] = {ଖାଲି};
ସ୍ଥିର ସଂରଚନା hash_entry *sctbl[START_COND_HASH_SIZE] = {ଖାଲି};
ସ୍ଥିର ସଂରଚନା hash_entry *ccltab[CCL_HASH_SIZE] = {ଖାଲି};


/* declare functions that have forward references */

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା addsym(ଅଚଳ ଅକ୍ଷର *, ଅଚଳ ଅକ୍ଷର *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, hash_table, size_t);
ସ୍ଥିର ସଂରଚନା hash_entry *findsym (ଅଚଳ ଅକ୍ଷର *sym, hash_table table,
				   size_t table_size);
ସ୍ଥିର size_t hashfunct(ଅଚଳ ଅକ୍ଷର *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା addsym (ଅଚଳ ଅକ୍ଷର *sym, ଅଚଳ ଅକ୍ଷର *str_def, ପୂର୍ଣ୍ଣସଂଖ୍ୟା int_def, hash_table table, size_t table_size)
{
	size_t hash_val = hashfunct (sym, table_size);
	ସଂରଚନା hash_entry *sym_entry = table[hash_val];
	ସଂରଚନା hash_entry *new_entry;

	ଯେତେବେଳେ (sym_entry) {
		ଯଦି (!strcmp (sym, sym_entry->name)) {	/* entry already exists */
			ଫେରନ୍ତୁ -1;
		}

		sym_entry = sym_entry->next;
	}

	/* create new entry */
	new_entry = malloc(ଆକାର(ସଂରଚନା hash_entry));

	ଯଦି (new_entry == ଖାଲି)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->next = table[hash_val];
	new_entry->name = xstrdup(sym);
	ଯଦି (str_def == ଖାଲି) {
		new_entry->str_val = ଖାଲି;
	} ଅନ୍ୟଥା {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	ଫେରନ୍ତୁ 0;
}


/* cclinstal - save the text of a character class */

ଶୂନ୍ୟ    cclinstal (ଅକ୍ଷର ccltxt[], ପୂର୍ଣ୍ଣସଂଖ୍ୟା cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(ଶୂନ୍ୟ) addsym(ccltxt, ଖାଲି, cclnum, ccltab, CCL_HASH_SIZE);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

ପୂର୍ଣ୍ଣସଂଖ୍ୟା     ccllookup (ଅକ୍ଷର ccltxt[])
{
	ଫେରନ୍ତୁ findsym (ccltxt, ccltab, CCL_HASH_SIZE)->int_val;
}


/* findsym - find symbol in symbol table */

ସ୍ଥିର ସଂରଚନା hash_entry *findsym (ଅଚଳ ଅକ୍ଷର *sym, hash_table table, size_t table_size)
{
	ସ୍ଥିର ସଂରଚନା hash_entry empty_entry = {
		ଖାଲି, ଖାଲି, ଖାଲି, 0,
	};
	ସଂରଚନା hash_entry *sym_entry =

		table[hashfunct (sym, table_size)];

	ଯେତେବେଳେ (sym_entry) {
		ଯଦି (!strcmp (sym, sym_entry->name))
			ଫେରନ୍ତୁ sym_entry;
		sym_entry = sym_entry->next;
	}

	ଫେରନ୍ତୁ &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

ସ୍ଥିର size_t hashfunct (ଅଚଳ ଅକ୍ଷର *str, size_t hash_size)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	ଯେତେବେଳେ (str[locstr] != '\0') {
		hashval = (hashval << 1) + (unsigned ଅକ୍ଷର) str[locstr++];
		hashval %= hash_size;
	}

	ଫେରନ୍ତୁ hashval;
}


/* ndinstal - install a name definition */

ଶୂନ୍ୟ    ndinstal (ଅଚଳ ଅକ୍ଷର *name, ଅକ୍ଷର definition[])
{
	ଯଦି (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_SIZE)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

ଅକ୍ଷର   *ndlookup (ଅଚଳ ଅକ୍ଷର *nd)
{
	ଫେରନ୍ତୁ findsym (nd, ndtbl, NAME_TABLE_HASH_SIZE)->str_val;
}


/* scextend - increase the maximum number of start conditions */

ଶୂନ୍ୟ    scextend (ଶୂନ୍ୟ)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++ଅଙ୍କ_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		ଆକାର(ଅକ୍ଷର));
	sceof = reallocate_array(sceof, current_max_scs, ଆକାର(ଅକ୍ଷର));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

ଶୂନ୍ୟ    scinstal (ଅଚଳ ଅକ୍ଷର *str, bool sc_is_exclusive)
{

	ଯଦି (++lastsc >= current_max_scs)
		scextend ();

	ଯଦି (addsym(str, ଖାଲି, lastsc, sctbl, START_COND_HASH_SIZE)) {
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

ପୂର୍ଣ୍ଣସଂଖ୍ୟା     sclookup (ଅଚଳ ଅକ୍ଷର *str)
{
	ଫେରନ୍ତୁ findsym (str, sctbl, START_COND_HASH_SIZE)->int_val;
}
