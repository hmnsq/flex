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

#അന്തര്ഭാവ "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

ഘടന hash_entry {
	ഘടന hash_entry *next;
	അക്ഷരം   *name;
	അക്ഷരം   *str_val;
	പൂർണ്ണസംഖ്യ     int_val;
};

തരനിർവചനം ഘടന hash_entry **hash_table;

#define NAME_TABLE_HASH_SIZE 101
#define START_COND_HASH_SIZE 101
#define CCL_HASH_SIZE 101

സ്ഥിതം ഘടന hash_entry *ndtbl[NAME_TABLE_HASH_SIZE] = {ശൂന്യ};
സ്ഥിതം ഘടന hash_entry *sctbl[START_COND_HASH_SIZE] = {ശൂന്യ};
സ്ഥിതം ഘടന hash_entry *ccltab[CCL_HASH_SIZE] = {ശൂന്യ};


/* declare functions that have forward references */

സ്ഥിതം പൂർണ്ണസംഖ്യ addsym(സ്ഥിരം അക്ഷരം *, സ്ഥിരം അക്ഷരം *, പൂർണ്ണസംഖ്യ, hash_table, size_t);
സ്ഥിതം ഘടന hash_entry *findsym (സ്ഥിരം അക്ഷരം *sym, hash_table table,
				   size_t table_size);
സ്ഥിതം size_t hashfunct(സ്ഥിരം അക്ഷരം *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

സ്ഥിതം പൂർണ്ണസംഖ്യ addsym (സ്ഥിരം അക്ഷരം *sym, സ്ഥിരം അക്ഷരം *str_def, പൂർണ്ണസംഖ്യ int_def, hash_table table, size_t table_size)
{
	size_t hash_val = hashfunct (sym, table_size);
	ഘടന hash_entry *sym_entry = table[hash_val];
	ഘടന hash_entry *new_entry;

	ആകുമ്പോൾ (sym_entry) {
		എങ്കിൽ (!strcmp (sym, sym_entry->name)) {	/* entry already exists */
			തിരികെ -1;
		}

		sym_entry = sym_entry->next;
	}

	/* create new entry */
	new_entry = malloc(വലുപ്പം(ഘടന hash_entry));

	എങ്കിൽ (new_entry == ശൂന്യ)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->next = table[hash_val];
	new_entry->name = xstrdup(sym);
	എങ്കിൽ (str_def == ശൂന്യ) {
		new_entry->str_val = ശൂന്യ;
	} അല്ലെങ്കിൽ {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	തിരികെ 0;
}


/* cclinstal - save the text of a character class */

ശൂന്യം    cclinstal (അക്ഷരം ccltxt[], പൂർണ്ണസംഖ്യ cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(ശൂന്യം) addsym(ccltxt, ശൂന്യ, cclnum, ccltab, CCL_HASH_SIZE);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

പൂർണ്ണസംഖ്യ     ccllookup (അക്ഷരം ccltxt[])
{
	തിരികെ findsym (ccltxt, ccltab, CCL_HASH_SIZE)->int_val;
}


/* findsym - find symbol in symbol table */

സ്ഥിതം ഘടന hash_entry *findsym (സ്ഥിരം അക്ഷരം *sym, hash_table table, size_t table_size)
{
	സ്ഥിതം ഘടന hash_entry empty_entry = {
		ശൂന്യ, ശൂന്യ, ശൂന്യ, 0,
	};
	ഘടന hash_entry *sym_entry =

		table[hashfunct (sym, table_size)];

	ആകുമ്പോൾ (sym_entry) {
		എങ്കിൽ (!strcmp (sym, sym_entry->name))
			തിരികെ sym_entry;
		sym_entry = sym_entry->next;
	}

	തിരികെ &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

സ്ഥിതം size_t hashfunct (സ്ഥിരം അക്ഷരം *str, size_t hash_size)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	ആകുമ്പോൾ (str[locstr] != '\0') {
		hashval = (hashval << 1) + (unsigned അക്ഷരം) str[locstr++];
		hashval %= hash_size;
	}

	തിരികെ hashval;
}


/* ndinstal - install a name definition */

ശൂന്യം    ndinstal (സ്ഥിരം അക്ഷരം *name, അക്ഷരം definition[])
{
	എങ്കിൽ (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_SIZE)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

അക്ഷരം   *ndlookup (സ്ഥിരം അക്ഷരം *nd)
{
	തിരികെ findsym (nd, ndtbl, NAME_TABLE_HASH_SIZE)->str_val;
}


/* scextend - increase the maximum number of start conditions */

ശൂന്യം    scextend (ശൂന്യം)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++അക്കം_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		വലുപ്പം(അക്ഷരം));
	sceof = reallocate_array(sceof, current_max_scs, വലുപ്പം(അക്ഷരം));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

ശൂന്യം    scinstal (സ്ഥിരം അക്ഷരം *str, bool sc_is_exclusive)
{

	എങ്കിൽ (++lastsc >= current_max_scs)
		scextend ();

	എങ്കിൽ (addsym(str, ശൂന്യ, lastsc, sctbl, START_COND_HASH_SIZE)) {
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

പൂർണ്ണസംഖ്യ     sclookup (സ്ഥിരം അക്ഷരം *str)
{
	തിരികെ findsym (str, sctbl, START_COND_HASH_SIZE)->int_val;
}
