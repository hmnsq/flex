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

#अन्तर्भाव "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

संरचना hash_entry {
	संरचना hash_entry *next;
	वर्ण   *name;
	वर्ण   *str_val;
	पूर्णाङ्क     int_val;
};

प्रकारनिर्देश संरचना hash_entry **hash_table;

#define NAME_TABLE_HASH_SIZE 101
#define START_COND_HASH_SIZE 101
#define CCL_HASH_SIZE 101

स्थिर संरचना hash_entry *ndtbl[NAME_TABLE_HASH_SIZE] = {रिक्त};
स्थिर संरचना hash_entry *sctbl[START_COND_HASH_SIZE] = {रिक्त};
स्थिर संरचना hash_entry *ccltab[CCL_HASH_SIZE] = {रिक्त};


/* declare functions that have forward references */

स्थिर पूर्णाङ्क addsym(ध्रुव वर्ण *, ध्रुव वर्ण *, पूर्णाङ्क, hash_table, size_t);
स्थिर संरचना hash_entry *findsym (ध्रुव वर्ण *sym, hash_table table,
				   size_t table_size);
स्थिर size_t hashfunct(ध्रुव वर्ण *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

स्थिर पूर्णाङ्क addsym (ध्रुव वर्ण *sym, ध्रुव वर्ण *str_def, पूर्णाङ्क int_def, hash_table table, size_t table_size)
{
	size_t hash_val = hashfunct (sym, table_size);
	संरचना hash_entry *sym_entry = table[hash_val];
	संरचना hash_entry *new_entry;

	जाव (sym_entry) {
		जइ (!strcmp (sym, sym_entry->name)) {	/* entry already exists */
			प्रत्यागम -1;
		}

		sym_entry = sym_entry->next;
	}

	/* create new entry */
	new_entry = malloc(परिमाण(संरचना hash_entry));

	जइ (new_entry == रिक्त)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->next = table[hash_val];
	new_entry->name = xstrdup(sym);
	जइ (str_def == रिक्त) {
		new_entry->str_val = रिक्त;
	} अण्णहा {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	प्रत्यागम 0;
}


/* cclinstal - save the text of a character class */

शून्य    cclinstal (वर्ण ccltxt[], पूर्णाङ्क cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(शून्य) addsym(ccltxt, रिक्त, cclnum, ccltab, CCL_HASH_SIZE);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

पूर्णाङ्क     ccllookup (वर्ण ccltxt[])
{
	प्रत्यागम findsym (ccltxt, ccltab, CCL_HASH_SIZE)->int_val;
}


/* findsym - find symbol in symbol table */

स्थिर संरचना hash_entry *findsym (ध्रुव वर्ण *sym, hash_table table, size_t table_size)
{
	स्थिर संरचना hash_entry empty_entry = {
		रिक्त, रिक्त, रिक्त, 0,
	};
	संरचना hash_entry *sym_entry =

		table[hashfunct (sym, table_size)];

	जाव (sym_entry) {
		जइ (!strcmp (sym, sym_entry->name))
			प्रत्यागम sym_entry;
		sym_entry = sym_entry->next;
	}

	प्रत्यागम &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

स्थिर size_t hashfunct (ध्रुव वर्ण *str, size_t hash_size)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	जाव (str[locstr] != '\0') {
		hashval = (hashval << 1) + (unsigned वर्ण) str[locstr++];
		hashval %= hash_size;
	}

	प्रत्यागम hashval;
}


/* ndinstal - install a name definition */

शून्य    ndinstal (ध्रुव वर्ण *name, वर्ण definition[])
{
	जइ (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_SIZE)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

वर्ण   *ndlookup (ध्रुव वर्ण *nd)
{
	प्रत्यागम findsym (nd, ndtbl, NAME_TABLE_HASH_SIZE)->str_val;
}


/* scextend - increase the maximum number of start conditions */

शून्य    scextend (शून्य)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++अङ्कः_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		परिमाण(वर्ण));
	sceof = reallocate_array(sceof, current_max_scs, परिमाण(वर्ण));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

शून्य    scinstal (ध्रुव वर्ण *str, bool sc_is_exclusive)
{

	जइ (++lastsc >= current_max_scs)
		scextend ();

	जइ (addsym(str, रिक्त, lastsc, sctbl, START_COND_HASH_SIZE)) {
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

पूर्णाङ्क     sclookup (ध्रुव वर्ण *str)
{
	प्रत्यागम findsym (str, sctbl, START_COND_HASH_SIZE)->int_val;
}
