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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ TABLES_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TABLES_H

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
/* *INDENT-OFF* */
ਬਾਹਰੀ  "C" {
/* *INDENT-ON* */
#ਜੇ_ਅੰਤ

/* Tables serialization API declarations. */
#ਅਨ੍ਤਰ੍ਭਾਵ "tables_shared.h"
ਬਣਤਰ yytbl_writer {
	FILE   *ਬਾਹਰਲਾ;
	ਪੂਰਨ ਕੁੱਲ_written;
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
ਬਾਹਰੀ bool tablesext, tablesverify,gentables;
ਬਾਹਰੀ ਅੱਖਰ *tablesfilename, *tablesname;
ਬਾਹਰੀ ਬਣਤਰ yytbl_writer tableswr;

ਪੂਰਨ     yytbl_writer_init (ਬਣਤਰ yytbl_writer *, FILE *);
ਪੂਰਨ     yytbl_hdr_init (ਬਣਤਰ yytbl_hdr *th, ਅਚਲ ਅੱਖਰ *ਸੰਸਕਰਣ_str,
			ਅਚਲ ਅੱਖਰ *name);
ਪੂਰਨ     yytbl_ਅੰਕੜੇ_init (ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl, ਗਿਣਤੀ yytbl_id id);
ਪੂਰਨ     yytbl_ਅੰਕੜੇ_destroy (ਬਣਤਰ yytbl_ਅੰਕੜੇ *td);
ਪੂਰਨ     yytbl_hdr_fwrite (ਬਣਤਰ yytbl_writer *wr,
			  ਅਚਲ ਬਣਤਰ yytbl_hdr *th);
ਪੂਰਨ     yytbl_ਅੰਕੜੇ_fwrite (ਬਣਤਰ yytbl_writer *wr, ਬਣਤਰ yytbl_ਅੰਕੜੇ *td);
ਖਾਲੀ    yytbl_ਅੰਕੜੇ_compress (ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl);


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
