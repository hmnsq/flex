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

#समावेश "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

काष्ठा hash_entry {
	काष्ठा hash_entry *अग्र;
	अक्षर   *name;
	अक्षर   *str_val;
	पूर्णांक     int_val;
};

प्रकार काष्ठा hash_entry **hash_table;

#घोषणा NAME_TABLE_HASH_आकार 101
#घोषणा START_COND_HASH_आकार 101
#घोषणा CCL_HASH_आकार 101

अटल काष्ठा hash_entry *ndtbl[NAME_TABLE_HASH_आकार] = {शून्य};
अटल काष्ठा hash_entry *sctbl[START_COND_HASH_आकार] = {शून्य};
अटल काष्ठा hash_entry *ccltab[CCL_HASH_आकार] = {शून्य};


/* declare functions that have forward references */

अटल पूर्णांक addsym(स्थिर अक्षर *, स्थिर अक्षर *, पूर्णांक, hash_table, माप_प्रकार);
अटल काष्ठा hash_entry *findsym (स्थिर अक्षर *sym, hash_table table,
				   माप_प्रकार table_आकार);
अटल माप_प्रकार hashfunct(स्थिर अक्षर *, माप_प्रकार);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

अटल पूर्णांक addsym (स्थिर अक्षर *sym, स्थिर अक्षर *str_def, पूर्णांक int_def, hash_table table, माप_प्रकार table_आकार)
{
	माप_प्रकार hash_val = hashfunct (sym, table_आकार);
	काष्ठा hash_entry *sym_entry = table[hash_val];
	काष्ठा hash_entry *new_entry;

	जबतक (sym_entry) {
		अगर (!म_भेद (sym, sym_entry->name)) {	/* entry already exists */
			वापस -1;
		}

		sym_entry = sym_entry->अग्र;
	}

	/* create new entry */
	new_entry = दो_स्मृति(माप(काष्ठा hash_entry));

	अगर (new_entry == शून्य)
		flexfatal (_("symbol table memory allocation failed"));

	new_entry->अग्र = table[hash_val];
	new_entry->name = xstrdup(sym);
	अगर (str_def == शून्य) {
		new_entry->str_val = शून्य;
	} अन्यथा {
		new_entry->str_val = xstrdup(str_def);
	}
	new_entry->int_val = int_def;

	table[hash_val] = new_entry;

	वापस 0;
}


/* cclinstal - save the text of a character class */

व्योम    cclinstal (अक्षर ccltxt[], पूर्णांक cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(व्योम) addsym(ccltxt, शून्य, cclnum, ccltab, CCL_HASH_आकार);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

पूर्णांक     ccllookup (अक्षर ccltxt[])
{
	वापस findsym (ccltxt, ccltab, CCL_HASH_आकार)->int_val;
}


/* findsym - find symbol in symbol table */

अटल काष्ठा hash_entry *findsym (स्थिर अक्षर *sym, hash_table table, माप_प्रकार table_आकार)
{
	अटल काष्ठा hash_entry empty_entry = {
		शून्य, शून्य, शून्य, 0,
	};
	काष्ठा hash_entry *sym_entry =

		table[hashfunct (sym, table_आकार)];

	जबतक (sym_entry) {
		अगर (!म_भेद (sym, sym_entry->name))
			वापस sym_entry;
		sym_entry = sym_entry->अग्र;
	}

	वापस &empty_entry;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

अटल माप_प्रकार hashfunct (स्थिर अक्षर *str, माप_प्रकार hash_आकार)
{
	माप_प्रकार hashval;
	माप_प्रकार locstr;

	hashval = 0;
	locstr = 0;

	जबतक (str[locstr] != '\0') {
		hashval = (hashval << 1) + (अचिन्हित अक्षर) str[locstr++];
		hashval %= hash_आकार;
	}

	वापस hashval;
}


/* ndinstal - install a name definition */

व्योम    ndinstal (स्थिर अक्षर *name, अक्षर definition[])
{
	अगर (addsym(name, definition, 0, ndtbl, NAME_TABLE_HASH_आकार)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

अक्षर   *ndlookup (स्थिर अक्षर *nd)
{
	वापस findsym (nd, ndtbl, NAME_TABLE_HASH_आकार)->str_val;
}


/* scextend - increase the maximum number of start conditions */

व्योम    scextend (व्योम)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++अंक_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		माप(अक्षर));
	sceof = reallocate_array(sceof, current_max_scs, माप(अक्षर));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

व्योम    scinstal (स्थिर अक्षर *str, bool sc_is_exclusive)
{

	अगर (++lastsc >= current_max_scs)
		scextend ();

	अगर (addsym(str, शून्य, lastsc, sctbl, START_COND_HASH_आकार)) {
		format_pinpoint_message (
			_("start condition %s declared twice"), str);
	}
	scname[lastsc] = sctbl[hashfunct(str, START_COND_HASH_आकार)]->name;

	scset[lastsc] = mkstate (SYM_EPSILON);
	scbol[lastsc] = mkstate (SYM_EPSILON);
	scxclu[lastsc] = sc_is_exclusive ? 1 : 0;
	sceof[lastsc] = false;
}


/* sclookup - lookup the number associated with a start condition
 *
 * Returns 0 if no such start condition.
 */

पूर्णांक     sclookup (स्थिर अक्षर *str)
{
	वापस findsym (str, sctbl, START_COND_HASH_आकार)->int_val;
}
