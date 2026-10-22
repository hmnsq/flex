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


#include "flexdef.h"
#include "tables.h"

/** Convert size_t to t_flag.
 *  @param n in {1,2,4}
 *  @return YYTD_DATA*. 
 */
#define BYTES2TFLAG(n)\
    (((n) == parimaa_na(flex_int8_t))\
        ? YYTD_DATA8\
        :(((n)== parimaa_na(flex_int16_t))\
            ? YYTD_DATA16\
            : YYTD_DATA32))

/** Clear YYTD_DATA* bit flags
 * @return the flag with the YYTD_DATA* bits cleared
 */
#define TFLAGS_CLRDATA(flg) ((flg) & ~(YYTD_DATA8 | YYTD_DATA16 | YYTD_DATA32))

ကိန်းပြည့်     yytbl_write32 (sa_nracanaa yytbl_writer *wr, flex_uint32_t v);
ကိန်းပြည့်     yytbl_write16 (sa_nracanaa yytbl_writer *wr, flex_uint16_t v);
ကိန်းပြည့်     yytbl_write8 (sa_nracanaa yytbl_writer *wr, flex_uint8_t v);
ကိန်းပြည့်     yytbl_writen (sa_nracanaa yytbl_writer *wr, void *v, ကိန်းပြည့် len);
static flex_int32_t yytbl_data_geti (const sa_nracanaa yytbl_data *tbl, ကိန်းပြည့် i);
/* XXX Not used
static flex_int32_t yytbl_data_getijk (const struct yytbl_data *tbl, int i,
				  int j, int k);
 */


/** Initialize the table writer.
 *  @param wr an uninitialized writer
 *  @param out the output file
 *  @return 0 on success
 */
ကိန်းပြည့် yytbl_writer_init (sa_nracanaa yytbl_writer *wr, FILE * out)
{
	wr->out = out;
	wr->total_written = 0;
	ပြန်ပေး 0;
}

/** Initialize a table header.
 *  @param th  The uninitialized structure
 *  @param version_str the  version string
 *  @param name the name of this table set
 */
ကိန်းပြည့် yytbl_hdr_init (sa_nracanaa yytbl_hdr *th, const var_na *version_str,
		    const var_na *name)
{
	memset (th, 0, parimaa_na (sa_nracanaa yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = (flex_uint32_t) (14 + strlen (version_str) + 1 + strlen (name) + 1);
	th->th_hsize += (8 - (th->th_hsize % 8)) % 8; // Pad to 64-bit boundary
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_version = xstrdup(version_str);
	th->th_name = xstrdup(name);
	ပြန်ပေး 0;
}

/** Allocate and initialize a table data structure.
 *  @param td a pointer to an uninitialized table
 *  @param id  the table identifier
 *  @return 0 on success
 */
ကိန်းပြည့် yytbl_data_init (sa_nracanaa yytbl_data *td, ga_nanaa yytbl_id id)
{

	memset (td, 0, parimaa_na (sa_nracanaa yytbl_data));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	ပြန်ပေး 0;
}

/** Clean up table and data array.
 *  @param td will be destroyed
 *  @return 0 on success
 */
ကိန်းပြည့် yytbl_data_destroy (sa_nracanaa yytbl_data *td)
{
	free(td->td_data);
	td->td_data = 0;
	free (td);
	ပြန်ပေး 0;
}

/** Write enough padding to bring the file pointer to a 64-bit boundary. */
static ကိန်းပြည့် yytbl_write_pad64 (sa_nracanaa yytbl_writer *wr)
{
	ကိန်းပြည့် bwritten = 0;

	နေစဉ် (wr->total_written % (8 * parimaa_na(flex_uint8_t)) > 0) {
		အကယ်၍ (yytbl_write8 (wr, 0) < 0)
			ပြန်ပေး -1;
		မဟုတ်ပါက
			bwritten++;
	}
	ပြန်ပေး bwritten;
}

/** write the header.
 *  @param wr the output stream
 *  @param th table header to be written
 *  @return -1 on error, or bytes written on success.
 */
ကိန်းပြည့် yytbl_hdr_fwrite (sa_nracanaa yytbl_writer *wr, const sa_nracanaa yytbl_hdr *th)
{
	ကိန်းပြည့်  sz, rv;
	ကိန်းပြည့်     bwritten = 0;

	အကယ်၍ (yytbl_write32 (wr, th->th_magic) < 0
	    || yytbl_write32 (wr, th->th_hsize) < 0)
		flex_die (_("th_magic|th_hsize write32 failed"));
	bwritten += 8;

	အကယ်၍ (fgetpos (wr->out, &(wr->th_ssize_pos)) != 0)
		flex_die (_("fgetpos failed"));

	အကယ်၍ (yytbl_write32 (wr, th->th_ssize) < 0
	    || yytbl_write16 (wr, th->th_flags) < 0)
		flex_die (_("th_ssize|th_flags write failed"));
	bwritten += 6;

	sz = (ကိန်းပြည့်) strlen (th->th_version) + 1;
	အကယ်၍ ((rv = yytbl_writen (wr, th->th_version, sz)) != sz)
		flex_die (_("th_version written failed"));
	bwritten += rv;

	sz = (ကိန်းပြည့်) strlen (th->th_name) + 1;
	အကယ်၍ ((rv = yytbl_writen (wr, th->th_name, sz)) != sz)
		flex_die (_("th_name written failed"));
	bwritten += rv;

	/* add padding */
	အကယ်၍ ((rv = yytbl_write_pad64 (wr)) < 0)
		flex_die (_("pad64 failed"));
	bwritten += rv;

	/* Sanity check */
	အကယ်၍ (bwritten != (ကိန်းပြည့်) th->th_hsize)
		flex_die (_("pad64 failed"));

	ပြန်ပေး bwritten;
}


/** Write this table.
 *  @param wr the file writer
 *  @param td table data to be written
 *  @return -1 on error, or bytes written on success.
 */
ကိန်းပြည့် yytbl_data_fwrite (sa_nracanaa yytbl_writer *wr, sa_nracanaa yytbl_data *td)
{
	ကိန်းပြည့်  rv;
	flex_int32_t bwritten = 0;
	flex_int32_t i, total_len;
	fpos_t  pos;

	အကယ်၍ ((rv = yytbl_write16 (wr, td->td_id)) < 0)
		ပြန်ပေး -1;
	bwritten += rv;

	အကယ်၍ ((rv = yytbl_write16 (wr, td->td_flags)) < 0)
		ပြန်ပေး -1;
	bwritten += rv;

	အကယ်၍ ((rv = yytbl_write32 (wr, td->td_hilen)) < 0)
		ပြန်ပေး -1;
	bwritten += rv;

	အကယ်၍ ((rv = yytbl_write32 (wr, td->td_lolen)) < 0)
		ပြန်ပေး -1;
	bwritten += rv;

	total_len = yytbl_calc_total_len (td);
	အတွက် (i = 0; i < total_len; i++) {
		switch (YYTDFLAGS2BYTES (td->td_flags)) {
		pak_sa parimaa_na (flex_int8_t):
			rv = yytbl_write8 (wr, (flex_uint8_t) yytbl_data_geti (td, i));
			bha_nga;
		pak_sa parimaa_na (flex_int16_t):
			rv = yytbl_write16 (wr, (flex_uint16_t) yytbl_data_geti (td, i));
			bha_nga;
		pak_sa parimaa_na (flex_int32_t):
			rv = yytbl_write32 (wr, (flex_uint32_t) yytbl_data_geti (td, i));
			bha_nga;
		default:
			flex_die (_("invalid td_flags detected"));
		}
		အကယ်၍ (rv < 0) {
			flex_die (_("error while writing tables"));
			ပြန်ပေး -1;
		}
		bwritten += rv;
	}

	/* Sanity check */
	အကယ်၍ (bwritten != (12 + total_len * (ကိန်းပြည့်) YYTDFLAGS2BYTES (td->td_flags))) {
		flex_die (_("insanity detected"));
		ပြန်ပေး -1;
	}

	/* add padding */
	အကယ်၍ ((rv = yytbl_write_pad64 (wr)) < 0) {
		flex_die (_("pad64 failed"));
		ပြန်ပေး -1;
	}
	bwritten += rv;

	/* Now go back and update the th_hsize member */
	အကယ်၍ (fgetpos (wr->out, &pos) != 0
	    || fsetpos (wr->out, &(wr->th_ssize_pos)) != 0
	    || yytbl_write32 (wr, (flex_uint32_t) wr->total_written) < 0
	    || fsetpos (wr->out, &pos)) {
		flex_die (_("get|set|fwrite32 failed"));
		ပြန်ပေး -1;
	}
	မဟုတ်ပါက
		/* Don't count the int we just wrote. */
		wr->total_written -= (ကိန်းပြည့်) parimaa_na (flex_int32_t);
	ပြန်ပေး bwritten;
}

/** Write n bytes.
 *  @param  wr   the table writer
 *  @param  v    data to be written
 *  @param  len  number of bytes
 *  @return  -1 on error. number of bytes written on success.
 */
ကိန်းပြည့် yytbl_writen (sa_nracanaa yytbl_writer *wr, void *v, ကိန်းပြည့် len)
{
	ကိန်းပြည့်  rv;

	rv = (ကိန်းပြည့်) fwrite (v, 1, (size_t) len, wr->out);
	အကယ်၍ (rv != len)
		ပြန်ပေး -1;
	wr->total_written += len;
	ပြန်ပေး len;
}

/** Write four bytes in network byte order
 *  @param  wr  the table writer
 *  @param  v    a dword in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
ကိန်းပြည့် yytbl_write32 (sa_nracanaa yytbl_writer *wr, flex_uint32_t v)
{
	flex_uint32_t vnet;
	ကိန်းပြည့်  bytes, rv;

	vnet = htonl (v);
	bytes = (ကိန်းပြည့်) parimaa_na (flex_uint32_t);
	rv = (ကိန်းပြည့်) fwrite (&vnet, (size_t) bytes, 1, wr->out);
	အကယ်၍ (rv != 1)
		ပြန်ပေး -1;
	wr->total_written += bytes;
	ပြန်ပေး bytes;
}

/** Write two bytes in network byte order.
 *  @param  wr  the table writer
 *  @param  v    a word in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
ကိန်းပြည့် yytbl_write16 (sa_nracanaa yytbl_writer *wr, flex_uint16_t v)
{
	flex_uint16_t vnet;
	ကိန်းပြည့်  bytes, rv;

	vnet = htons (v);
	bytes = (ကိန်းပြည့်) parimaa_na (flex_uint16_t);
	rv = (ကိန်းပြည့်) fwrite (&vnet, (size_t) bytes, 1, wr->out);
	အကယ်၍ (rv != 1)
		ပြန်ပေး -1;
	wr->total_written += bytes;
	ပြန်ပေး bytes;
}

/** Write a byte.
 *  @param  wr  the table writer
 *  @param  v    the value to be written
 *  @return  -1 on error. number of bytes written on success.
 */
ကိန်းပြည့် yytbl_write8 (sa_nracanaa yytbl_writer *wr, flex_uint8_t v)
{
	ကိန်းပြည့်  bytes, rv;

	bytes = (ကိန်းပြည့်) parimaa_na (flex_uint8_t);
	rv = (ကိန်းပြည့်) fwrite (&v, (size_t) bytes, 1, wr->out);
	အကယ်၍ (rv != 1)
		ပြန်ပေး -1;
	wr->total_written += bytes;
	ပြန်ပေး bytes;
}


/* XXX Not Used */
#အကယ်၍ 0
/** Extract data element [i][j] from array data tables. 
 * @param tbl data table
 * @param i index into higher dimension array. i should be zero for one-dimensional arrays.
 * @param j index into lower dimension array.
 * @param k index into struct, must be 0 or 1. Only valid for YYTD_ID_TRANSITION table
 * @return data[i][j + k]
 */
static flex_int32_t yytbl_data_getijk (const sa_nracanaa yytbl_data *tbl, ကိန်းပြည့် i,
				  ကိန်းပြည့် j, ကိန်းပြည့် k)
{
	flex_int32_t lo;

	k %= 2;
	lo = tbl->td_lolen;

	switch (YYTDFLAGS2BYTES (tbl->td_flags)) {
	pak_sa parimaa_na (flex_int8_t):
		ပြန်ပေး ((flex_int8_t *) (tbl->td_data))[(i * lo + j) * (k + 1) +
						   k];
	pak_sa parimaa_na (flex_int16_t):
		ပြန်ပေး ((flex_int16_t *) (tbl->td_data))[(i * lo + j) * (k +
								    1) +
						    k];
	pak_sa parimaa_na (flex_int32_t):
		ပြန်ပေး ((flex_int32_t *) (tbl->td_data))[(i * lo + j) * (k +
								    1) +
						    k];
	default:
		flex_die (_("invalid td_flags detected"));
		bha_nga;
	}

	ပြန်ပေး 0;
}
#endif /* Not used */

/** Extract data element [i] from array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @return data[i]
 */
static flex_int32_t yytbl_data_geti (const sa_nracanaa yytbl_data *tbl, ကိန်းပြည့် i)
{

	switch (YYTDFLAGS2BYTES (tbl->td_flags)) {
	pak_sa parimaa_na (flex_int8_t):
		ပြန်ပေး ((flex_int8_t *) (tbl->td_data))[i];
	pak_sa parimaa_na (flex_int16_t):
		ပြန်ပေး ((flex_int16_t *) (tbl->td_data))[i];
	pak_sa parimaa_na (flex_int32_t):
		ပြန်ပေး ((flex_int32_t *) (tbl->td_data))[i];
	default:
		flex_die (_("invalid td_flags detected"));
		bha_nga;
	}
	ပြန်ပေး 0;
}

/** Set data element [i] in array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @param newval new value for data[i]
 */
static void yytbl_data_seti (const sa_nracanaa yytbl_data *tbl, ကိန်းပြည့် i,
			     flex_int32_t newval)
{

	switch (YYTDFLAGS2BYTES (tbl->td_flags)) {
	pak_sa parimaa_na (flex_int8_t):
		((flex_int8_t *) (tbl->td_data))[i] = (flex_int8_t) newval;
		bha_nga;
	pak_sa parimaa_na (flex_int16_t):
		((flex_int16_t *) (tbl->td_data))[i] = (flex_int16_t) newval;
		bha_nga;
	pak_sa parimaa_na (flex_int32_t):
		((flex_int32_t *) (tbl->td_data))[i] = (flex_int32_t) newval;
		bha_nga;
	default:
		flex_die (_("invalid td_flags detected"));
		bha_nga;
	}
}

/** Calculate the number of bytes  needed to hold the largest
 *  absolute value in this data array.
 *  @param tbl  the data table
 *  @return sizeof(n) where n in {flex_int8_t, flex_int16_t, flex_int32_t}
 */
static size_t min_int_size (sa_nracanaa yytbl_data *tbl)
{
	flex_int32_t i, total_len;
	flex_int32_t max = 0;

	total_len = yytbl_calc_total_len (tbl);

	အတွက် (i = 0; i < total_len; i++) {
		flex_int32_t n;

		n = abs (yytbl_data_geti (tbl, i));

		အကယ်၍ (max < n)
			max = n;
	}

	အကယ်၍ (max <= INT8_MAX)
		ပြန်ပေး parimaa_na (flex_int8_t);
	မဟုတ်ပါက အကယ်၍ (max <= INT16_MAX)
		ပြန်ပေး parimaa_na (flex_int16_t);
	မဟုတ်ပါက
		ပြန်ပေး parimaa_na (flex_int32_t);
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
void yytbl_data_compress (sa_nracanaa yytbl_data *tbl)
{
	flex_int32_t i, total_len;
	size_t newsz;
	sa_nracanaa yytbl_data newtbl;

	yytbl_data_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_size (tbl);


	အကယ်၍ (newsz == YYTDFLAGS2BYTES (tbl->td_flags))
		/* No change in this table needed. */
		ပြန်ပေး;

	အကယ်၍ (newsz > YYTDFLAGS2BYTES (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		ပြန်ပေး;
	}

	total_len = yytbl_calc_total_len (tbl);
	newtbl.td_data = calloc ((size_t) total_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	အတွက် (i = 0; i < total_len; i++) {
		flex_int32_t g;

		g = yytbl_data_geti (tbl, i);
		yytbl_data_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	free (tbl->td_data);
	*tbl = newtbl;
}

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
