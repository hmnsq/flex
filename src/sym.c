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

#అన్తర్భావ "flexdef.h"

/* Variables for symbol tables:
 * sctbl - start-condition symbol table
 * ndtbl - name-definition symbol table
 * ccltab - character class text symbol table
 */

నిర్మాణం hash_నమోదు {
	నిర్మాణం hash_నమోదు *తదుపరి;
	అక్షరం   *name;
	అక్షరం   *str_val;
	పూర్ణాంకం     int_val;
};

రకనిర్వచనం నిర్మాణం hash_నమోదు **hash_పట్టిక;

#నిర్వచించు NAME_పట్టిక_HASH_కొలత 101
#నిర్వచించు ప్రారంభం_COND_HASH_కొలత 101
#నిర్వచించు CCL_HASH_కొలత 101

స్థిర నిర్మాణం hash_నమోదు *ndtbl[NAME_పట్టిక_HASH_కొలత] = {ఖాళీ};
స్థిర నిర్మాణం hash_నమోదు *sctbl[ప్రారంభం_COND_HASH_కొలత] = {ఖాళీ};
స్థిర నిర్మాణం hash_నమోదు *ccltab[CCL_HASH_కొలత] = {ఖాళీ};


/* declare functions that have forward references */

స్థిర పూర్ణాంకం addsym(స్థిరరాశి అక్షరం *, స్థిరరాశి అక్షరం *, పూర్ణాంకం, hash_పట్టిక, size_t);
స్థిర నిర్మాణం hash_నమోదు *findsym (స్థిరరాశి అక్షరం *sym, hash_పట్టిక పట్టిక,
				   size_t పట్టిక_కొలత);
స్థిర size_t hashfunct(స్థిరరాశి అక్షరం *, size_t);


/* addsym - add symbol and definitions to symbol table
 *
 * -1 is returned if the symbol already exists, and the change not made.
 */

స్థిర పూర్ణాంకం addsym (స్థిరరాశి అక్షరం *sym, స్థిరరాశి అక్షరం *str_def, పూర్ణాంకం int_def, hash_పట్టిక పట్టిక, size_t పట్టిక_కొలత)
{
	size_t hash_val = hashfunct (sym, పట్టిక_కొలత);
	నిర్మాణం hash_నమోదు *sym_నమోదు = పట్టిక[hash_val];
	నిర్మాణం hash_నమోదు *new_నమోదు;

	అయితే (sym_నమోదు) {
		ఒకవేళ (!strcmp (sym, sym_నమోదు->name)) {	/* entry already exists */
			తిరిగి -1;
		}

		sym_నమోదు = sym_నమోదు->తదుపరి;
	}

	/* create new entry */
	new_నమోదు = జ్ఞాపకం_ఇవ్వు(పరిమాణం(నిర్మాణం hash_నమోదు));

	ఒకవేళ (new_నమోదు == ఖాళీ)
		flexfatal (_("symbol table memory allocation failed"));

	new_నమోదు->తదుపరి = పట్టిక[hash_val];
	new_నమోదు->name = xstrdup(sym);
	ఒకవేళ (str_def == ఖాళీ) {
		new_నమోదు->str_val = ఖాళీ;
	} లేకపోతే {
		new_నమోదు->str_val = xstrdup(str_def);
	}
	new_నమోదు->int_val = int_def;

	పట్టిక[hash_val] = new_నమోదు;

	తిరిగి 0;
}


/* cclinstal - save the text of a character class */

శూన్య    cclinstal (అక్షరం ccltxt[], పూర్ణాంకం cclnum)
{
	/* We don't bother checking the return status because we are not
	 * called unless the symbol is new.
	 */

	(శూన్య) addsym(ccltxt, ఖాళీ, cclnum, ccltab, CCL_HASH_కొలత);
}


/* ccllookup - lookup the number associated with character class text
 *
 * Returns 0 if there's no CCL associated with the text.
 */

పూర్ణాంకం     ccllookup (అక్షరం ccltxt[])
{
	తిరిగి findsym (ccltxt, ccltab, CCL_HASH_కొలత)->int_val;
}


/* findsym - find symbol in symbol table */

స్థిర నిర్మాణం hash_నమోదు *findsym (స్థిరరాశి అక్షరం *sym, hash_పట్టిక పట్టిక, size_t పట్టిక_కొలత)
{
	స్థిర నిర్మాణం hash_నమోదు ఖాళీలు_నమోదు = {
		ఖాళీ, ఖాళీ, ఖాళీ, 0,
	};
	నిర్మాణం hash_నమోదు *sym_నమోదు =

		పట్టిక[hashfunct (sym, పట్టిక_కొలత)];

	అయితే (sym_నమోదు) {
		ఒకవేళ (!strcmp (sym, sym_నమోదు->name))
			తిరిగి sym_నమోదు;
		sym_నమోదు = sym_నమోదు->తదుపరి;
	}

	తిరిగి &ఖాళీలు_నమోదు;
}

/* hashfunct - compute the hash value for "str" and hash size "hash_size" */

స్థిర size_t hashfunct (స్థిరరాశి అక్షరం *str, size_t hash_కొలత)
{
	size_t hashval;
	size_t locstr;

	hashval = 0;
	locstr = 0;

	అయితే (str[locstr] != '\0') {
		hashval = (hashval << 1) + (గుర్తులేని అక్షరం) str[locstr++];
		hashval %= hash_కొలత;
	}

	తిరిగి hashval;
}


/* ndinstal - install a name definition */

శూన్య    ndinstal (స్థిరరాశి అక్షరం *name, అక్షరం definition[])
{
	ఒకవేళ (addsym(name, definition, 0, ndtbl, NAME_పట్టిక_HASH_కొలత)) {
		synerr (_("name defined twice"));
	}
}


/* ndlookup - lookup a name definition
 *
 * Returns a nil pointer if the name definition does not exist.
 */

అక్షరం   *ndlookup (స్థిరరాశి అక్షరం *nd)
{
	తిరిగి findsym (nd, ndtbl, NAME_పట్టిక_HASH_కొలత)->str_val;
}


/* scextend - increase the maximum number of start conditions */

శూన్య    scextend (శూన్య)
{
	current_max_scs += MAX_SCS_INCREMENT;

	++అంకె_reallocs;

	scset = reallocate_integer_array (scset, current_max_scs);
	scbol = reallocate_integer_array (scbol, current_max_scs);
	scxclu = reallocate_array(scxclu, current_max_scs,
		పరిమాణం(అక్షరం));
	sceof = reallocate_array(sceof, current_max_scs, పరిమాణం(అక్షరం));
	scname = reallocate_char_ptr_array (scname, current_max_scs);
}


/* scinstal - make a start condition */

శూన్య    scinstal (స్థిరరాశి అక్షరం *str, bool sc_is_exclusive)
{

	ఒకవేళ (++lastsc >= current_max_scs)
		scextend ();

	ఒకవేళ (addsym(str, ఖాళీ, lastsc, sctbl, ప్రారంభం_COND_HASH_కొలత)) {
		format_pinpoint_సందేశం (
			_("start condition %s declared twice"), str);
	}
	scname[lastsc] = sctbl[hashfunct(str, ప్రారంభం_COND_HASH_కొలత)]->name;

	scset[lastsc] = mkstate (SYM_EPSILON);
	scbol[lastsc] = mkstate (SYM_EPSILON);
	scxclu[lastsc] = sc_is_exclusive ? 1 : 0;
	sceof[lastsc] = false;
}


/* sclookup - lookup the number associated with a start condition
 *
 * Returns 0 if no such start condition.
 */

పూర్ణాంకం     sclookup (స్థిరరాశి అక్షరం *str)
{
	తిరిగి findsym (str, sctbl, ప్రారంభం_COND_HASH_కొలత)->int_val;
}
