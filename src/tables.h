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

#నిర్వచితం_కాకపోతే TABLES_H
#నిర్వచించు TABLES_H

#నిర్వచితమైతే __cplusplus
/* *INDENT-OFF* */
బాహ్య  "C" {
/* *INDENT-ON* */
#అయితే_ముగింపు

/* Tables serialization API declarations. */
#అన్తర్భావ "tables_shared.h"
నిర్మాణం yytbl_writer {
	FILE   *బహిర్గతం;
	పూర్ణాంకం మొత్తం_written;
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
బాహ్య bool tablesext, tablesverify,gentables;
బాహ్య అక్షరం *tablesfilename, *tablesname;
బాహ్య నిర్మాణం yytbl_writer tableswr;

పూర్ణాంకం     yytbl_writer_init (నిర్మాణం yytbl_writer *, FILE *);
పూర్ణాంకం     yytbl_hdr_init (నిర్మాణం yytbl_hdr *th, స్థిరరాశి అక్షరం *సంస్కరణ_str,
			స్థిరరాశి అక్షరం *name);
పూర్ణాంకం     yytbl_దత్తాంశం_init (నిర్మాణం yytbl_దత్తాంశం *tbl, గణన yytbl_id id);
పూర్ణాంకం     yytbl_దత్తాంశం_destroy (నిర్మాణం yytbl_దత్తాంశం *td);
పూర్ణాంకం     yytbl_hdr_fwrite (నిర్మాణం yytbl_writer *wr,
			  స్థిరరాశి నిర్మాణం yytbl_hdr *th);
పూర్ణాంకం     yytbl_దత్తాంశం_fwrite (నిర్మాణం yytbl_writer *wr, నిర్మాణం yytbl_దత్తాంశం *td);
శూన్య    yytbl_దత్తాంశం_compress (నిర్మాణం yytbl_దత్తాంశం *tbl);


#నిర్వచితమైతే __cplusplus
/* *INDENT-OFF* */
}
/* *INDENT-ON* */
#అయితే_ముగింపు
#అయితే_ముగింపు

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
