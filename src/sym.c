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

ساخت hash_اندراج {
	ساخت hash_اندراج *اگلا;
	حرف   *name;
	حرف   *str_val;
	صحیح     int_val;
};

قسمتعریف ساخت hash_اندراج **hash_جدول;

#تعریف_کرو NAME_جدول_HASH_سائز 101
#تعریف_کرو آغاز_COND_HASH_سائز 101
#تعریف_کرو CCL_HASH_سائز 101

ساکن ساخت hash_اندراج *ndtbl[NAME_جدول_HASH_سائز] = {تہی};
ساکن ساخت hash_اندراج *sctbl[آغاز_COND_HASH_سائز] = {تہی};
ساکن ساخت hash_اندراج *ccltab[CCL_HASH_سائز] = {تہی};


/* declare functions that have forward references */

ساکن صحیح addsym(ثابت حرف *, ثابت حرف *, صحیح, hash_جدول, size_t);
ساکن ساخت hash_اندراج *findsym (ثابت حرف *sym, hash_جدول جدول,
				   size_t جدول_سائز);
ساکن size_t hashfunct(ثابت حرف *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

ساکن صحیح addsym (ثابت حرف *sym, ثابت حرف *str_def, صحیح int_def, hash_جدول جدول, size_t جدول_سائز)
{
	size_t hash_val = hashfunct (sym, جدول_سائز);
	ساخت hash_اندراج *sym_اندراج = جدول[hash_val];
	ساخت hash_اندراج *new_اندراج;

	جب (sym_اندراج) {
		اگر (!strcmp (sym, sym_اندراج->name)) {	/* entry already exists */
			واپس -1;
		}

		sym_اندراج = sym_اندراج->اگلا;
	}

	/* create new entry */
	new_اندراج = حافظہ_دو(حجم(ساخت hash_اندراج));

	اگر (new_اندراج == تہی)
		flexfatal (_("symbol table memory allocation failed"));

	new_اندراج->اگلا = جدول[hash_val];
	new_اندراج->name = xstrdup(sym);
	اگر (str_def == تہی) {
		new_اندراج->str_val = تہی;
	} ورنہ {
		new_اندراج->str_val = xstrdup(str_def);
	}
	new_اندراج->int_val = int_def;

	جدول[hash_val] = new_اندراج;

	واپس 0;
}


/* cclinstal - save the text of a character class */

خالی    cclinstal (حرف ccltxt[], صحیح cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(خالی) addsym(ccltxt, تہی, cclnum, ccltab, CCL_HASH_سائز);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

صحیح     ccllookup (حرف ccltxt[])
{
	واپس findsym (ccltxt, ccltab, CCL_HASH_سائز)->int_val;
}


/* findsym - find symbol in symbol table */

ساکن ساخت hash_اندراج *findsym (ثابت حرف *sym, hash_جدول جدول, size_t جدول_سائز)
{
	ساکن ساخت hash_اندراج خالی_خانے_اندراج = {
		تہی, تہی, تہی, 0,
	};
	ساخت hash_اندراج *sym_اندراج =

		جدول[hashfunct (sym, جدول_سائز)];

	جب (sym_اندراج) {
		اگر (!strcmp (sym, sym_اندراج->name))
			واپس sym_اندراج;
		sym_اندراج = sym_اندراج->اگلا;
	}

	واپس &خالی_خانے_اندراج;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

ساکن size_t hashfunct (ثابت حرف *str, size_t hash_سائز)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	جب (str[locstr] != '\0') {
		hashval = (hashval << 1) + (غیرعلامتی حرف) str[locstr++];
		hashval %= hash_سائز;
	}

	واپس hashval;
}


/* ndinstal - install a name definition */

خالی    ndinstal (ثابت حرف *name, حرف definition[])
{
	اگر (addsym(name, definition, 0, ndtbl, NAME_جدول_HASH_سائز)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

حرف   *ndlookup (ثابت حرف *nd)
{
	واپس findsym (nd, ndtbl, NAME_جدول_HASH_سائز)->str_val;
}


/* scextend - increase the maximum number of start conditions */

خالی    scextend (خالی)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++عدد_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		حجم(حرف));
	sceof = reallocate_array(sceof, current_max_scs, حجم(حرف));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

خالی    scinstal (ثابت حرف *str, bool sc_is_exclusive)
{

	اگر (++lastsc >= current_max_scs)
		scextend ();

	اگر (addsym(str, تہی, lastsc, sctbl, آغاز_COND_HASH_سائز)) {
		format_pinpoint_پیغام (
			_("start condition %s declared twice"), str);
	}
	scname[lastsc] = sctbl[hashfunct(str, آغاز_COND_HASH_سائز)]->name;

	scset[lastsc] = mkstate (SYM_EPSILON);
	scbol[lastsc] = mkstate (SYM_EPSILON);
	scxclu[lastsc] = sc_is_exclusive ? 1 : 0;
	sceof[lastsc] = false;
}


/* sclookup - lookup the number associated with a start condition
 *
 * Returns 0 if no such start condition.
 */

صحیح     sclookup (ثابت حرف *str)
{
	واپس findsym (str, sctbl, آغاز_COND_HASH_سائز)->int_val;
}
