/*  tables.h - tables serialization code
 *
 *  Copyright (c) 1990 The Regents of the University of California.
 *  All rights reserved.
 *
 *  This code is derived from software contributed to Berkeley by
 *  Vern Paxson.
 *
 *  The United States Government has rights in this work pursuant
 *  to contract no. DE-AC03-76SF00098 between the United States
 *  Department of Energy and the University of California.
 *
 *  This file is part of flex.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  Neither the name of the University nor the names of its contributors
 *  may be used to endorse or promote products derived from this software
 *  without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE.
 */

#ifndef TABLES_H
#define TABLES_H

#ifdef __cplusplus
/* *INDENT-OFF* */
বাহ্য  "C" {
/* *INDENT-ON* */
#endif

/* Tables serialization API declarations. */
#অন্তর্ভাৱ "tables_shared.h"
সংরচনা yytbl_writer {
	FILE   *out;
	পূর্ণাঙ্ক total_written;
			    /**< bytes written so far */
	fpos_t  th_ssize_pos;
			    /**< position of th_ssize */
};

/* These are used by main.c, gen.c, etc.
 * tablesext - if true, create external tables
 * tablesfilename - filename for external tables
 * tablesname - name that goes in serialized data, e.g., "yytables"
 * tableswr -  writer for external tables
 * tablesverify - true if tables-verify option specified
 * gentables - true if we should spit out the normal C tables
 */
বাহ্য bool tablesext, tablesverify,gentables;
বাহ্য ৱর্ণ *tablesfilename, *tablesname;
বাহ্য সংরচনা yytbl_writer tableswr;

পূর্ণাঙ্ক     yytbl_writer_init (সংরচনা yytbl_writer *, FILE *);
পূর্ণাঙ্ক     yytbl_hdr_init (সংরচনা yytbl_hdr *th, ধ্রুৱ ৱর্ণ *version_str,
			ধ্রুৱ ৱর্ণ *name);
পূর্ণাঙ্ক     yytbl_data_init (সংরচনা yytbl_data *tbl, গণনা yytbl_id id);
পূর্ণাঙ্ক     yytbl_data_destroy (সংরচনা yytbl_data *td);
পূর্ণাঙ্ক     yytbl_hdr_fwrite (সংরচনা yytbl_writer *wr,
			  ধ্রুৱ সংরচনা yytbl_hdr *th);
পূর্ণাঙ্ক     yytbl_data_fwrite (সংরচনা yytbl_writer *wr, সংরচনা yytbl_data *td);
শূন্য    yytbl_data_compress (সংরচনা yytbl_data *tbl);


#ifdef __cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#endif
#endif

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
