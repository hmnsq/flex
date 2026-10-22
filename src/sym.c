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

#ضمن "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

بنية hash_مدخل {
	بنية hash_مدخل *بعدی;
	حرف   *name;
	حرف   *str_val;
	صحيح     int_val;
};

تعريفنوع بنية hash_مدخل **hash_جدول;

#تعریف_کن NAME_جدول_HASH_اندازه 101
#تعریف_کن شروع_COND_HASH_اندازه 101
#تعریف_کن CCL_HASH_اندازه 101

ساكن بنية hash_مدخل *ndtbl[NAME_جدول_HASH_اندازه] = {عدم};
ساكن بنية hash_مدخل *sctbl[شروع_COND_HASH_اندازه] = {عدم};
ساكن بنية hash_مدخل *ccltab[CCL_HASH_اندازه] = {عدم};


/* declare functions that have forward references */

ساكن صحيح addsym(ثابت حرف *, ثابت حرف *, صحيح, hash_جدول, size_t);
ساكن بنية hash_مدخل *findsym (ثابت حرف *sym, hash_جدول جدول,
				   size_t جدول_اندازه);
ساكن size_t hashfunct(ثابت حرف *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

ساكن صحيح addsym (ثابت حرف *sym, ثابت حرف *str_def, صحيح int_def, hash_جدول جدول, size_t جدول_اندازه)
{
	size_t hash_val = hashfunct (sym, جدول_اندازه);
	بنية hash_مدخل *sym_مدخل = جدول[hash_val];
	بنية hash_مدخل *new_مدخل;

	طالما (sym_مدخل) {
		إذا (!strcmp (sym, sym_مدخل->name)) {	/* entry already exists */
			أرجع -1;
		}

		sym_مدخل = sym_مدخل->بعدی;
	}

	/* create new entry */
	new_مدخل = حافظه_بده(حجم(بنية hash_مدخل));

	إذا (new_مدخل == عدم)
		flexfatal (_("symbol table memory allocation failed"));

	new_مدخل->بعدی = جدول[hash_val];
	new_مدخل->name = xstrdup(sym);
	إذا (str_def == عدم) {
		new_مدخل->str_val = عدم;
	} وإلا {
		new_مدخل->str_val = xstrdup(str_def);
	}
	new_مدخل->int_val = int_def;

	جدول[hash_val] = new_مدخل;

	أرجع 0;
}


/* cclinstal - save the text of a character class */

فراغ    cclinstal (حرف ccltxt[], صحيح cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(فراغ) addsym(ccltxt, عدم, cclnum, ccltab, CCL_HASH_اندازه);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

صحيح     ccllookup (حرف ccltxt[])
{
	أرجع findsym (ccltxt, ccltab, CCL_HASH_اندازه)->int_val;
}


/* findsym - find symbol in symbol table */

ساكن بنية hash_مدخل *findsym (ثابت حرف *sym, hash_جدول جدول, size_t جدول_اندازه)
{
	ساكن بنية hash_مدخل خالی_مدخل = {
		عدم, عدم, عدم, 0,
	};
	بنية hash_مدخل *sym_مدخل =

		جدول[hashfunct (sym, جدول_اندازه)];

	طالما (sym_مدخل) {
		إذا (!strcmp (sym, sym_مدخل->name))
			أرجع sym_مدخل;
		sym_مدخل = sym_مدخل->بعدی;
	}

	أرجع &خالی_مدخل;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

ساكن size_t hashfunct (ثابت حرف *str, size_t hash_اندازه)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	طالما (str[locstr] != '\0') {
		hashval = (hashval << 1) + (بیعلامت حرف) str[locstr++];
		hashval %= hash_اندازه;
	}

	أرجع hashval;
}


/* ndinstal - install a name definition */

فراغ    ndinstal (ثابت حرف *name, حرف definition[])
{
	إذا (addsym(name, definition, 0, ndtbl, NAME_جدول_HASH_اندازه)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

حرف   *ndlookup (ثابت حرف *nd)
{
	أرجع findsym (nd, ndtbl, NAME_جدول_HASH_اندازه)->str_val;
}


/* scextend - increase the maximum number of start conditions */

فراغ    scextend (فراغ)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++رقم_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		حجم(حرف));
	sceof = reallocate_array(sceof, current_max_scs, حجم(حرف));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

فراغ    scinstal (ثابت حرف *str, bool sc_is_exclusive)
{

	إذا (++lastsc >= current_max_scs)
		scextend ();

	إذا (addsym(str, عدم, lastsc, sctbl, شروع_COND_HASH_اندازه)) {
		format_pinpoint_پیام (
			_("start condition %s declared twice"), str);
	}
	scname[lastsc] = sctbl[hashfunct(str, شروع_COND_HASH_اندازه)]->name;

	scset[lastsc] = mkstate (SYM_EPSILON);
	scbol[lastsc] = mkstate (SYM_EPSILON);
	scxclu[lastsc] = sc_is_exclusive ? 1 : 0;
	sceof[lastsc] = false;
}


/* sclookup - lookup the number associated with a start condition
 *
 * Returns 0 if no such start condition.
 */

صحيح     sclookup (ثابت حرف *str)
{
	أرجع findsym (str, sctbl, شروع_COND_HASH_اندازه)->int_val;
}
