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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ TABLES_H
#ವ್ಯಾಖ್ಯಾನಿಸು TABLES_H

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
/* *INDENT-OFF* */
ಬಾಹ್ಯ  "C" {
/* *INDENT-ON* */
#ಆದರೆ_ಅಂತ್ಯ

/* Tables serialization API declarations. */
#ಅನ್ತರ್ಭಾವ "tables_shared.h"
ರಚನೆ yytbl_writer {
	FILE   *ಹೊರಹೋಗು;
	ಪೂರ್ಣಾಂಕ ಒಟ್ಟು_written;
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
ಬಾಹ್ಯ bool tablesext, tablesverify,gentables;
ಬಾಹ್ಯ ಅಕ್ಷರ *tablesfilename, *tablesname;
ಬಾಹ್ಯ ರಚನೆ yytbl_writer tableswr;

ಪೂರ್ಣಾಂಕ     yytbl_writer_init (ರಚನೆ yytbl_writer *, FILE *);
ಪೂರ್ಣಾಂಕ     yytbl_hdr_init (ರಚನೆ yytbl_hdr *th, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಆವೃತ್ತಿ_str,
			ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name);
ಪೂರ್ಣಾಂಕ     yytbl_ದತ್ತಾಂಶ_init (ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl, ಎಣಿಕೆ yytbl_id id);
ಪೂರ್ಣಾಂಕ     yytbl_ದತ್ತಾಂಶ_destroy (ರಚನೆ yytbl_ದತ್ತಾಂಶ *td);
ಪೂರ್ಣಾಂಕ     yytbl_hdr_fwrite (ರಚನೆ yytbl_writer *wr,
			  ಸ್ಥಿರಾಂಕ ರಚನೆ yytbl_hdr *th);
ಪೂರ್ಣಾಂಕ     yytbl_ದತ್ತಾಂಶ_fwrite (ರಚನೆ yytbl_writer *wr, ರಚನೆ yytbl_ದತ್ತಾಂಶ *td);
ಶೂನ್ಯ    yytbl_ದತ್ತಾಂಶ_compress (ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl);


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
