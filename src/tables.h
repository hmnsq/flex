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

#अगर_अघोषित TABLES_H
#घोषणा TABLES_H

#अगर_घोषित __cplusplus
/* *INDENT-OFF* */
बाह्य  "C" {
/* *INDENT-ON* */
#पूर्ण_अगर

/* Tables serialization API declarations. */
#समावेश "tables_shared.h"
काष्ठा yytbl_writer {
	खाता   *out;
	पूर्णांक योग_written;
			    /**< bytes written so far */
	ख_स्थान_प्रकार  th_ssize_pos;
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
बाह्य bool tablesext, tablesverify,gentables;
बाह्य अक्षर *tablesfilename, *tablesname;
बाह्य काष्ठा yytbl_writer tableswr;

पूर्णांक     yytbl_writer_init (काष्ठा yytbl_writer *, खाता *);
पूर्णांक     yytbl_hdr_init (काष्ठा yytbl_hdr *th, स्थिर अक्षर *version_str,
			स्थिर अक्षर *name);
पूर्णांक     yytbl_तथ्य_init (काष्ठा yytbl_तथ्य *tbl, क्रमागत yytbl_id id);
पूर्णांक     yytbl_तथ्य_destroy (काष्ठा yytbl_तथ्य *td);
पूर्णांक     yytbl_hdr_fwrite (काष्ठा yytbl_writer *wr,
			  स्थिर काष्ठा yytbl_hdr *th);
पूर्णांक     yytbl_तथ्य_fwrite (काष्ठा yytbl_writer *wr, काष्ठा yytbl_तथ्य *td);
व्योम    yytbl_तथ्य_compress (काष्ठा yytbl_तथ्य *tbl);


#अगर_घोषित __cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#पूर्ण_अगर
#पूर्ण_अगर

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
