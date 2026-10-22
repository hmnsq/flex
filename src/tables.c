/*  tables.c - tables serialization code
 *
 * SPDX-License-Identifier: BSD-3-Clause-flex
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


#అన్తర్భావ "flexdef.h"
#అన్తర్భావ "tables.h"

/** Convert size_t to t_flag.
 *  @param n in {1,2,4}
 *  @return YYTD_DATA*. 
 */
#నిర్వచించు BYTES2TFLAG(n)\
    (((n) == పరిమాణం(flex_int8_t))\
        ? YYTD_DATA8\
        :(((n)== పరిమాణం(flex_int16_t))\
            ? YYTD_DATA16\
            : YYTD_DATA32))

/** Clear YYTD_DATA* bit flags
 * @return the flag with the YYTD_DATA* bits cleared
 */
#నిర్వచించు TFLAGS_CLRDATA(flg) ((flg) & ~(YYTD_DATA8 | YYTD_DATA16 | YYTD_DATA32))

పూర్ణాంకం     yytbl_write32 (నిర్మాణం yytbl_writer *wr, flex_uint32_t v);
పూర్ణాంకం     yytbl_write16 (నిర్మాణం yytbl_writer *wr, flex_uint16_t v);
పూర్ణాంకం     yytbl_write8 (నిర్మాణం yytbl_writer *wr, flex_uint8_t v);
పూర్ణాంకం     yytbl_writen (నిర్మాణం yytbl_writer *wr, శూన్య *v, పూర్ణాంకం len);
స్థిర flex_int32_t yytbl_దత్తాంశం_geti (స్థిరరాశి నిర్మాణం yytbl_దత్తాంశం *tbl, పూర్ణాంకం i);
/* XXX Not used
static flex_int32_t yytbl_data_getijk (const struct yytbl_data *tbl, int i,
				  int j, int k);
 */


/** Initialize the table writer.
 *  @param wr an uninitialized writer
 *  @param out the output file
 *  @return 0 on success
 */
పూర్ణాంకం yytbl_writer_init (నిర్మాణం yytbl_writer *wr, FILE * బహిర్గతం)
{
	wr->బహిర్గతం = బహిర్గతం;
	wr->మొత్తం_written = 0;
	తిరిగి 0;
}

/** Initialize a table header.
 *  @param th  The uninitialized structure
 *  @param version_str the  version string
 *  @param name the name of this table set
 */
పూర్ణాంకం yytbl_hdr_init (నిర్మాణం yytbl_hdr *th, స్థిరరాశి అక్షరం *సంస్కరణ_str,
		    స్థిరరాశి అక్షరం *name)
{
	memset (th, 0, పరిమాణం (నిర్మాణం yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = (flex_uint32_t) (14 + అక్షరశ్రేణి_పొడవు (సంస్కరణ_str) + 1 + అక్షరశ్రేణి_పొడవు (name) + 1);
	th->th_hsize += (8 - (th->th_hsize % 8)) % 8; // Pad to 64-bit boundary
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_సంస్కరణ = xstrdup(సంస్కరణ_str);
	th->th_name = xstrdup(name);
	తిరిగి 0;
}

/** Allocate and initialize a table data structure.
 *  @param td a pointer to an uninitialized table
 *  @param id  the table identifier
 *  @return 0 on success
 */
పూర్ణాంకం yytbl_దత్తాంశం_init (నిర్మాణం yytbl_దత్తాంశం *td, గణన yytbl_id id)
{

	memset (td, 0, పరిమాణం (నిర్మాణం yytbl_దత్తాంశం));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	తిరిగి 0;
}

/** Clean up table and data array.
 *  @param td will be destroyed
 *  @return 0 on success
 */
పూర్ణాంకం yytbl_దత్తాంశం_destroy (నిర్మాణం yytbl_దత్తాంశం *td)
{
	విడుదల(td->td_దత్తాంశం);
	td->td_దత్తాంశం = 0;
	విడుదల (td);
	తిరిగి 0;
}

/** Write enough padding to bring the file pointer to a 64-bit boundary. */
స్థిర పూర్ణాంకం yytbl_write_pad64 (నిర్మాణం yytbl_writer *wr)
{
	పూర్ణాంకం bwritten = 0;

	అయితే (wr->మొత్తం_written % (8 * పరిమాణం(flex_uint8_t)) > 0) {
		ఒకవేళ (yytbl_write8 (wr, 0) < 0)
			తిరిగి -1;
		లేకపోతే
			bwritten++;
	}
	తిరిగి bwritten;
}

/** write the header.
 *  @param wr the output stream
 *  @param th table header to be written
 *  @return -1 on error, or bytes written on success.
 */
పూర్ణాంకం yytbl_hdr_fwrite (నిర్మాణం yytbl_writer *wr, స్థిరరాశి నిర్మాణం yytbl_hdr *th)
{
	పూర్ణాంకం  sz, rv;
	పూర్ణాంకం     bwritten = 0;

	ఒకవేళ (yytbl_write32 (wr, th->th_magic) < 0
	    || yytbl_write32 (wr, th->th_hsize) < 0)
		flex_die (_("th_magic|th_hsize write32 failed"));
	bwritten += 8;

	ఒకవేళ (fgetpos (wr->బహిర్గతం, &(wr->th_ssize_pos)) != 0)
		flex_die (_("fgetpos failed"));

	ఒకవేళ (yytbl_write32 (wr, th->th_ssize) < 0
	    || yytbl_write16 (wr, th->th_flags) < 0)
		flex_die (_("th_ssize|th_flags write failed"));
	bwritten += 6;

	sz = (పూర్ణాంకం) అక్షరశ్రేణి_పొడవు (th->th_సంస్కరణ) + 1;
	ఒకవేళ ((rv = yytbl_writen (wr, th->th_సంస్కరణ, sz)) != sz)
		flex_die (_("th_version written failed"));
	bwritten += rv;

	sz = (పూర్ణాంకం) అక్షరశ్రేణి_పొడవు (th->th_name) + 1;
	ఒకవేళ ((rv = yytbl_writen (wr, th->th_name, sz)) != sz)
		flex_die (_("th_name written failed"));
	bwritten += rv;

	/* add padding */
	ఒకవేళ ((rv = yytbl_write_pad64 (wr)) < 0)
		flex_die (_("pad64 failed"));
	bwritten += rv;

	/* Sanity check */
	ఒకవేళ (bwritten != (పూర్ణాంకం) th->th_hsize)
		flex_die (_("pad64 failed"));

	తిరిగి bwritten;
}


/** Write this table.
 *  @param wr the file writer
 *  @param td table data to be written
 *  @return -1 on error, or bytes written on success.
 */
పూర్ణాంకం yytbl_దత్తాంశం_fwrite (నిర్మాణం yytbl_writer *wr, నిర్మాణం yytbl_దత్తాంశం *td)
{
	పూర్ణాంకం  rv;
	flex_int32_t bwritten = 0;
	flex_int32_t i, మొత్తం_len;
	fpos_t  pos;

	ఒకవేళ ((rv = yytbl_write16 (wr, td->td_id)) < 0)
		తిరిగి -1;
	bwritten += rv;

	ఒకవేళ ((rv = yytbl_write16 (wr, td->td_flags)) < 0)
		తిరిగి -1;
	bwritten += rv;

	ఒకవేళ ((rv = yytbl_write32 (wr, td->td_hilen)) < 0)
		తిరిగి -1;
	bwritten += rv;

	ఒకవేళ ((rv = yytbl_write32 (wr, td->td_lolen)) < 0)
		తిరిగి -1;
	bwritten += rv;

	మొత్తం_len = yytbl_calc_మొత్తం_len (td);
	కొరకు (i = 0; i < మొత్తం_len; i++) {
		ఎంపిక (YYTDFLAGS2_బైట్లు (td->td_flags)) {
		స్థితి పరిమాణం (flex_int8_t):
			rv = yytbl_write8 (wr, (flex_uint8_t) yytbl_దత్తాంశం_geti (td, i));
			ఆపు;
		స్థితి పరిమాణం (flex_int16_t):
			rv = yytbl_write16 (wr, (flex_uint16_t) yytbl_దత్తాంశం_geti (td, i));
			ఆపు;
		స్థితి పరిమాణం (flex_int32_t):
			rv = yytbl_write32 (wr, (flex_uint32_t) yytbl_దత్తాంశం_geti (td, i));
			ఆపు;
		అప్రమేయ:
			flex_die (_("invalid td_flags detected"));
		}
		ఒకవేళ (rv < 0) {
			flex_die (_("error while writing tables"));
			తిరిగి -1;
		}
		bwritten += rv;
	}

	/* Sanity check */
	ఒకవేళ (bwritten != (12 + మొత్తం_len * (పూర్ణాంకం) YYTDFLAGS2_బైట్లు (td->td_flags))) {
		flex_die (_("insanity detected"));
		తిరిగి -1;
	}

	/* add padding */
	ఒకవేళ ((rv = yytbl_write_pad64 (wr)) < 0) {
		flex_die (_("pad64 failed"));
		తిరిగి -1;
	}
	bwritten += rv;

	/* Now go back and update the th_hsize member */
	ఒకవేళ (fgetpos (wr->బహిర్గతం, &pos) != 0
	    || fsetpos (wr->బహిర్గతం, &(wr->th_ssize_pos)) != 0
	    || yytbl_write32 (wr, (flex_uint32_t) wr->మొత్తం_written) < 0
	    || fsetpos (wr->బహిర్గతం, &pos)) {
		flex_die (_("get|set|fwrite32 failed"));
		తిరిగి -1;
	}
	లేకపోతే
		/* Don't count the int we just wrote. */
		wr->మొత్తం_written -= (పూర్ణాంకం) పరిమాణం (flex_int32_t);
	తిరిగి bwritten;
}

/** Write n bytes.
 *  @param  wr   the table writer
 *  @param  v    data to be written
 *  @param  len  number of bytes
 *  @return  -1 on error. number of bytes written on success.
 */
పూర్ణాంకం yytbl_writen (నిర్మాణం yytbl_writer *wr, శూన్య *v, పూర్ణాంకం len)
{
	పూర్ణాంకం  rv;

	rv = (పూర్ణాంకం) fwrite (v, 1, (size_t) len, wr->బహిర్గతం);
	ఒకవేళ (rv != len)
		తిరిగి -1;
	wr->మొత్తం_written += len;
	తిరిగి len;
}

/** Write four bytes in network byte order
 *  @param  wr  the table writer
 *  @param  v    a dword in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
పూర్ణాంకం yytbl_write32 (నిర్మాణం yytbl_writer *wr, flex_uint32_t v)
{
	flex_uint32_t vnet;
	పూర్ణాంకం  బైట్లు, rv;

	vnet = htonl (v);
	బైట్లు = (పూర్ణాంకం) పరిమాణం (flex_uint32_t);
	rv = (పూర్ణాంకం) fwrite (&vnet, (size_t) బైట్లు, 1, wr->బహిర్గతం);
	ఒకవేళ (rv != 1)
		తిరిగి -1;
	wr->మొత్తం_written += బైట్లు;
	తిరిగి బైట్లు;
}

/** Write two bytes in network byte order.
 *  @param  wr  the table writer
 *  @param  v    a word in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
పూర్ణాంకం yytbl_write16 (నిర్మాణం yytbl_writer *wr, flex_uint16_t v)
{
	flex_uint16_t vnet;
	పూర్ణాంకం  బైట్లు, rv;

	vnet = htons (v);
	బైట్లు = (పూర్ణాంకం) పరిమాణం (flex_uint16_t);
	rv = (పూర్ణాంకం) fwrite (&vnet, (size_t) బైట్లు, 1, wr->బహిర్గతం);
	ఒకవేళ (rv != 1)
		తిరిగి -1;
	wr->మొత్తం_written += బైట్లు;
	తిరిగి బైట్లు;
}

/** Write a byte.
 *  @param  wr  the table writer
 *  @param  v    the value to be written
 *  @return  -1 on error. number of bytes written on success.
 */
పూర్ణాంకం yytbl_write8 (నిర్మాణం yytbl_writer *wr, flex_uint8_t v)
{
	పూర్ణాంకం  బైట్లు, rv;

	బైట్లు = (పూర్ణాంకం) పరిమాణం (flex_uint8_t);
	rv = (పూర్ణాంకం) fwrite (&v, (size_t) బైట్లు, 1, wr->బహిర్గతం);
	ఒకవేళ (rv != 1)
		తిరిగి -1;
	wr->మొత్తం_written += బైట్లు;
	తిరిగి బైట్లు;
}


/* XXX Not Used */
#ఒకవేళ 0
/** Extract data element [i][j] from array data tables. 
 * @param tbl data table
 * @param i index into higher dimension array. i should be zero for one-dimensional arrays.
 * @param j index into lower dimension array.
 * @param k index into struct, must be 0 or 1. Only valid for YYTD_ID_TRANSITION table
 * @return data[i][j + k]
 */
స్థిర flex_int32_t yytbl_దత్తాంశం_getijk (స్థిరరాశి నిర్మాణం yytbl_దత్తాంశం *tbl, పూర్ణాంకం i,
				  పూర్ణాంకం j, పూర్ణాంకం k)
{
	flex_int32_t lo;

	k %= 2;
	lo = tbl->td_lolen;

	ఎంపిక (YYTDFLAGS2_బైట్లు (tbl->td_flags)) {
	స్థితి పరిమాణం (flex_int8_t):
		తిరిగి ((flex_int8_t *) (tbl->td_దత్తాంశం))[(i * lo + j) * (k + 1) +
						   k];
	స్థితి పరిమాణం (flex_int16_t):
		తిరిగి ((flex_int16_t *) (tbl->td_దత్తాంశం))[(i * lo + j) * (k +
								    1) +
						    k];
	స్థితి పరిమాణం (flex_int32_t):
		తిరిగి ((flex_int32_t *) (tbl->td_దత్తాంశం))[(i * lo + j) * (k +
								    1) +
						    k];
	అప్రమేయ:
		flex_die (_("invalid td_flags detected"));
		ఆపు;
	}

	తిరిగి 0;
}
#అయితే_ముగింపు /* Not used */

/** Extract data element [i] from array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @return data[i]
 */
స్థిర flex_int32_t yytbl_దత్తాంశం_geti (స్థిరరాశి నిర్మాణం yytbl_దత్తాంశం *tbl, పూర్ణాంకం i)
{

	ఎంపిక (YYTDFLAGS2_బైట్లు (tbl->td_flags)) {
	స్థితి పరిమాణం (flex_int8_t):
		తిరిగి ((flex_int8_t *) (tbl->td_దత్తాంశం))[i];
	స్థితి పరిమాణం (flex_int16_t):
		తిరిగి ((flex_int16_t *) (tbl->td_దత్తాంశం))[i];
	స్థితి పరిమాణం (flex_int32_t):
		తిరిగి ((flex_int32_t *) (tbl->td_దత్తాంశం))[i];
	అప్రమేయ:
		flex_die (_("invalid td_flags detected"));
		ఆపు;
	}
	తిరిగి 0;
}

/** Set data element [i] in array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @param newval new value for data[i]
 */
స్థిర శూన్య yytbl_దత్తాంశం_seti (స్థిరరాశి నిర్మాణం yytbl_దత్తాంశం *tbl, పూర్ణాంకం i,
			     flex_int32_t newval)
{

	ఎంపిక (YYTDFLAGS2_బైట్లు (tbl->td_flags)) {
	స్థితి పరిమాణం (flex_int8_t):
		((flex_int8_t *) (tbl->td_దత్తాంశం))[i] = (flex_int8_t) newval;
		ఆపు;
	స్థితి పరిమాణం (flex_int16_t):
		((flex_int16_t *) (tbl->td_దత్తాంశం))[i] = (flex_int16_t) newval;
		ఆపు;
	స్థితి పరిమాణం (flex_int32_t):
		((flex_int32_t *) (tbl->td_దత్తాంశం))[i] = (flex_int32_t) newval;
		ఆపు;
	అప్రమేయ:
		flex_die (_("invalid td_flags detected"));
		ఆపు;
	}
}

/** Calculate the number of bytes  needed to hold the largest
 *  absolute value in this data array.
 *  @param tbl  the data table
 *  @return sizeof(n) where n in {flex_int8_t, flex_int16_t, flex_int32_t}
 */
స్థిర size_t min_int_కొలత (నిర్మాణం yytbl_దత్తాంశం *tbl)
{
	flex_int32_t i, మొత్తం_len;
	flex_int32_t max = 0;

	మొత్తం_len = yytbl_calc_మొత్తం_len (tbl);

	కొరకు (i = 0; i < మొత్తం_len; i++) {
		flex_int32_t n;

		n = నిరపేక్ష (yytbl_దత్తాంశం_geti (tbl, i));

		ఒకవేళ (max < n)
			max = n;
	}

	ఒకవేళ (max <= INT8_MAX)
		తిరిగి పరిమాణం (flex_int8_t);
	లేకపోతే ఒకవేళ (max <= INT16_MAX)
		తిరిగి పరిమాణం (flex_int16_t);
	లేకపోతే
		తిరిగి పరిమాణం (flex_int32_t);
}

/** Transform data to smallest possible of (int32, int16, int8).
 * For example, we may have generated an int32 array due to user options
 * (e.g., %option align), but if the maximum value in that array
 * is 80 (for example), then we can serialize it with only 1 byte per int.
 * This is NOT the same as compressed DFA tables. We're just trying
 * to save storage space here.
 *
 * @param tbl the table to be compressed
 */
శూన్య yytbl_దత్తాంశం_compress (నిర్మాణం yytbl_దత్తాంశం *tbl)
{
	flex_int32_t i, మొత్తం_len;
	size_t newsz;
	నిర్మాణం yytbl_దత్తాంశం newtbl;

	yytbl_దత్తాంశం_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_కొలత (tbl);


	ఒకవేళ (newsz == YYTDFLAGS2_బైట్లు (tbl->td_flags))
		/* No change in this table needed. */
		తిరిగి;

	ఒకవేళ (newsz > YYTDFLAGS2_బైట్లు (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		తిరిగి;
	}

	మొత్తం_len = yytbl_calc_మొత్తం_len (tbl);
	newtbl.td_దత్తాంశం = సున్నా_జ్ఞాపకం_ఇవ్వు ((size_t) మొత్తం_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	కొరకు (i = 0; i < మొత్తం_len; i++) {
		flex_int32_t g;

		g = yytbl_దత్తాంశం_geti (tbl, i);
		yytbl_దత్తాంశం_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	విడుదల (tbl->td_దత్తాంశం);
	*tbl = newtbl;
}

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
