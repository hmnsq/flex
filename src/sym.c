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
	अक्षर   *name;
	अक्षर   *str_val;
	पूर्णांक     int_val;
};

प्रकारव्याख्या संरचना hash_entry **hash_table;

#define NAME_TABLE_HASH_SIZE 101
#define START_COND_HASH_SIZE 101
#define CCL_HASH_SIZE 101

स्थिर संरचना hash_entry *ndtbl[NAME_TABLE_HASH_SIZE] = {रिक्त};
स्थिर संरचना hash_entry *sctbl[START_COND_HASH_SIZE] = {रिक्त};
स्थिर संरचना hash_entry *ccltab[CCL_HASH_SIZE] = {रिक्त};


/* declare functions that have forward references */

स्थिर पूर्णांक addsym(स्थिरांक अक्षर *, स्थिरांक अक्षर *, पूर्णांक, hash_table, माप_प्रकार);
स्थिर संरचना hash_entry *findsym (स्थिरांक अक्षर *sym, hash_table table,
				   माप_प्रकार table_size);
स्थिर माप_प्रकार hashfunct(स्थिरांक अक्षर *, माप_प्रकार);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

स्थिर पूर्णांक addsym (स्थिरांक अक्षर *sym, स्थिरांक अक्षर *str_def, पूर्णांक int_def, hash_table table, माप_प्रकार table_size)
{
	माप_प्रकार hash_val = hashfunct (sym, table_size);
	संरचना hash_entry *sym_entry = table[hash_val];
	संरचना hash_entry *new_entry;

	पर्यंत (sym_entry) {
		जर (!म_भेद (sym, sym_entry->name)) {	/* entry already exists */
			परत -1;
		}

		sym_entry = sym_entry->next;
	}

	/* create new entry */
	new_entry = दो_स्मृति(आकार(संरचना hash_entry));

	जर (new_entry == रिक्त)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->next = table[hash_val];
	new_entry->name = xstrdup(sym);
	जर (str_def == रिक्त) {
		new_entry->str_val = रिक्त;
	} अन्यथा {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	परत 0;
}


/* cclinstal - save the text of a character class */

शून्य    cclinstal (अक्षर ccltxt[], पूर्णांक cclnum)
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

पूर्णांक     ccllookup (अक्षर ccltxt[])
{
	परत findsym (ccltxt, ccltab, CCL_HASH_SIZE)->int_val;
}


/* findsym - find symbol in symbol table */

स्थिर संरचना hash_entry *findsym (स्थिरांक अक्षर *sym, hash_table table, माप_प्रकार table_size)
{
	स्थिर संरचना hash_entry empty_entry = {
		रिक्त, रिक्त, रिक्त, 0,
	};
	संरचना hash_entry *sym_entry =

		table[hashfunct (sym, table_size)];

	पर्यंत (sym_entry) {
		जर (!म_भेद (sym, sym_entry->name))
			परत sym_entry;
		sym_entry = sym_entry->next;
	}

	परत &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

स्थिर माप_प्रकार hashfunct (स्थिरांक अक्षर *str, माप_प्रकार hash_size)
{
	माप_प्रकार hashval;
	माप_प्रकार locstr;

	hashval = 0;
	locstr = 0;

	पर्यंत (str[locstr] != '\0') {
		hashval = (hashval << 1) + (अचिन्हित अक्षर) str[locstr++];
		hashval %= hash_size;
	}

	परत hashval;
}


/* ndinstal - install a name definition */

शून्य    ndinstal (स्थिरांक अक्षर *name, अक्षर definition[])
{
	जर (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_SIZE)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

अक्षर   *ndlookup (स्थिरांक अक्षर *nd)
{
	परत findsym (nd, ndtbl, NAME_TABLE_HASH_SIZE)->str_val;
}


/* scextend - increase the maximum number of start conditions */

शून्य    scextend (शून्य)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++अंक_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		आकार(अक्षर));
	sceof = reallocate_array(sceof, current_max_scs, आकार(अक्षर));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

शून्य    scinstal (स्थिरांक अक्षर *str, bool sc_is_exclusive)
{

	जर (++lastsc >= current_max_scs)
		scextend ();

	जर (addsym(str, रिक्त, lastsc, sctbl, START_COND_HASH_SIZE)) {
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

पूर्णांक     sclookup (स्थिरांक अक्षर *str)
{
	परत findsym (str, sctbl, START_COND_HASH_SIZE)->int_val;
}
