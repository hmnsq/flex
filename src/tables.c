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


#شامل "flexdef.h"
#شامل "tables.h"

/** Convert size_t to t_flag.
 *  @param n in {1,2,4}
 *  @return YYTD_DATA*. 
 */
#تعریف_کرو BYTES2TFLAG(n)\
    (((n) == حجم(flex_int8_t))\
        ? YYTD_DATA8\
        :(((n)== حجم(flex_int16_t))\
            ? YYTD_DATA16\
            : YYTD_DATA32))

/** Clear YYTD_DATA* bit flags
 * @return the flag with the YYTD_DATA* bits cleared
 */
#تعریف_کرو TFLAGS_CLRDATA(flg) ((flg) & ~(YYTD_DATA8 | YYTD_DATA16 | YYTD_DATA32))

صحیح     yytbl_write32 (ساخت yytbl_writer *wr, flex_uint32_t v);
صحیح     yytbl_write16 (ساخت yytbl_writer *wr, flex_uint16_t v);
صحیح     yytbl_write8 (ساخت yytbl_writer *wr, flex_uint8_t v);
صحیح     yytbl_writen (ساخت yytbl_writer *wr, خالی *v, صحیح len);
ساکن flex_int32_t yytbl_ڈیٹا_geti (ثابت ساخت yytbl_ڈیٹا *tbl, صحیح i);
/* XXX Not used
static flex_int32_t yytbl_data_getijk (const struct yytbl_data *tbl, int i,
				  int j, int k);
 */


/** Initialize the table writer.
 *  @param wr an uninitialized writer
 *  @param out the output file
 *  @return 0 on success
 */
صحیح yytbl_writer_init (ساخت yytbl_writer *wr, FILE * برآمد)
{
	wr->برآمد = برآمد;
	wr->کل_written = 0;
	واپس 0;
}

/** Initialize a table header.
 *  @param th  The uninitialized structure
 *  @param version_str the  version string
 *  @param name the name of this table set
 */
صحیح yytbl_hdr_init (ساخت yytbl_hdr *th, ثابت حرف *نسخہ_str,
		    ثابت حرف *name)
{
	memset (th, 0, حجم (ساخت yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = (flex_uint32_t) (14 + لڑی_لمبائی (نسخہ_str) + 1 + لڑی_لمبائی (name) + 1);
	th->th_hsize += (8 - (th->th_hsize % 8)) % 8; // Pad to 64-bit boundary
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_نسخہ = xstrdup(نسخہ_str);
	th->th_name = xstrdup(name);
	واپس 0;
}

/** Allocate and initialize a table data structure.
 *  @param td a pointer to an uninitialized table
 *  @param id  the table identifier
 *  @return 0 on success
 */
صحیح yytbl_ڈیٹا_init (ساخت yytbl_ڈیٹا *td, شمار yytbl_id id)
{

	memset (td, 0, حجم (ساخت yytbl_ڈیٹا));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	واپس 0;
}

/** Clean up table and data array.
 *  @param td will be destroyed
 *  @return 0 on success
 */
صحیح yytbl_ڈیٹا_destroy (ساخت yytbl_ڈیٹا *td)
{
	آزاد(td->td_ڈیٹا);
	td->td_ڈیٹا = 0;
	آزاد (td);
	واپس 0;
}

/** Write enough padding to bring the file pointer to a 64-bit boundary. */
ساکن صحیح yytbl_write_pad64 (ساخت yytbl_writer *wr)
{
	صحیح bwritten = 0;

	جب (wr->کل_written % (8 * حجم(flex_uint8_t)) > 0) {
		اگر (yytbl_write8 (wr, 0) < 0)
			واپس -1;
		ورنہ
			bwritten++;
	}
	واپس bwritten;
}

/** write the header.
 *  @param wr the output stream
 *  @param th table header to be written
 *  @return -1 on error, or bytes written on success.
 */
صحیح yytbl_hdr_fwrite (ساخت yytbl_writer *wr, ثابت ساخت yytbl_hdr *th)
{
	صحیح  sz, rv;
	صحیح     bwritten = 0;

	اگر (yytbl_write32 (wr, th->th_magic) < 0
	    || yytbl_write32 (wr, th->th_hsize) < 0)
		flex_die (_("th_magic|th_hsize write32 failed"));
	bwritten += 8;

	اگر (fgetpos (wr->برآمد, &(wr->th_ssize_pos)) != 0)
		flex_die (_("fgetpos failed"));

	اگر (yytbl_write32 (wr, th->th_ssize) < 0
	    || yytbl_write16 (wr, th->th_flags) < 0)
		flex_die (_("th_ssize|th_flags write failed"));
	bwritten += 6;

	sz = (صحیح) لڑی_لمبائی (th->th_نسخہ) + 1;
	اگر ((rv = yytbl_writen (wr, th->th_نسخہ, sz)) != sz)
		flex_die (_("th_version written failed"));
	bwritten += rv;

	sz = (صحیح) لڑی_لمبائی (th->th_name) + 1;
	اگر ((rv = yytbl_writen (wr, th->th_name, sz)) != sz)
		flex_die (_("th_name written failed"));
	bwritten += rv;

	/* add padding */
	اگر ((rv = yytbl_write_pad64 (wr)) < 0)
		flex_die (_("pad64 failed"));
	bwritten += rv;

	/* Sanity check */
	اگر (bwritten != (صحیح) th->th_hsize)
		flex_die (_("pad64 failed"));

	واپس bwritten;
}


/** Write this table.
 *  @param wr the file writer
 *  @param td table data to be written
 *  @return -1 on error, or bytes written on success.
 */
صحیح yytbl_ڈیٹا_fwrite (ساخت yytbl_writer *wr, ساخت yytbl_ڈیٹا *td)
{
	صحیح  rv;
	flex_int32_t bwritten = 0;
	flex_int32_t i, کل_len;
	fpos_t  pos;

	اگر ((rv = yytbl_write16 (wr, td->td_id)) < 0)
		واپس -1;
	bwritten += rv;

	اگر ((rv = yytbl_write16 (wr, td->td_flags)) < 0)
		واپس -1;
	bwritten += rv;

	اگر ((rv = yytbl_write32 (wr, td->td_hilen)) < 0)
		واپس -1;
	bwritten += rv;

	اگر ((rv = yytbl_write32 (wr, td->td_lolen)) < 0)
		واپس -1;
	bwritten += rv;

	کل_len = yytbl_calc_کل_len (td);
	برائے (i = 0; i < کل_len; i++) {
		انتخاب (YYTDFLAGS2_بائٹیں (td->td_flags)) {
		حالت حجم (flex_int8_t):
			rv = yytbl_write8 (wr, (flex_uint8_t) yytbl_ڈیٹا_geti (td, i));
			توڑو;
		حالت حجم (flex_int16_t):
			rv = yytbl_write16 (wr, (flex_uint16_t) yytbl_ڈیٹا_geti (td, i));
			توڑو;
		حالت حجم (flex_int32_t):
			rv = yytbl_write32 (wr, (flex_uint32_t) yytbl_ڈیٹا_geti (td, i));
			توڑو;
		طےشدہ:
			flex_die (_("invalid td_flags detected"));
		}
		اگر (rv < 0) {
			flex_die (_("error while writing tables"));
			واپس -1;
		}
		bwritten += rv;
	}

	/* Sanity check */
	اگر (bwritten != (12 + کل_len * (صحیح) YYTDFLAGS2_بائٹیں (td->td_flags))) {
		flex_die (_("insanity detected"));
		واپس -1;
	}

	/* add padding */
	اگر ((rv = yytbl_write_pad64 (wr)) < 0) {
		flex_die (_("pad64 failed"));
		واپس -1;
	}
	bwritten += rv;

	/* Now go back and update the th_hsize member */
	اگر (fgetpos (wr->برآمد, &pos) != 0
	    || fsetpos (wr->برآمد, &(wr->th_ssize_pos)) != 0
	    || yytbl_write32 (wr, (flex_uint32_t) wr->کل_written) < 0
	    || fsetpos (wr->برآمد, &pos)) {
		flex_die (_("get|set|fwrite32 failed"));
		واپس -1;
	}
	ورنہ
		/* Don't count the int we just wrote. */
		wr->کل_written -= (صحیح) حجم (flex_int32_t);
	واپس bwritten;
}

/** Write n bytes.
 *  @param  wr   the table writer
 *  @param  v    data to be written
 *  @param  len  number of bytes
 *  @return  -1 on error. number of bytes written on success.
 */
صحیح yytbl_writen (ساخت yytbl_writer *wr, خالی *v, صحیح len)
{
	صحیح  rv;

	rv = (صحیح) fwrite (v, 1, (size_t) len, wr->برآمد);
	اگر (rv != len)
		واپس -1;
	wr->کل_written += len;
	واپس len;
}

/** Write four bytes in network byte order
 *  @param  wr  the table writer
 *  @param  v    a dword in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
صحیح yytbl_write32 (ساخت yytbl_writer *wr, flex_uint32_t v)
{
	flex_uint32_t vnet;
	صحیح  بائٹیں, rv;

	vnet = htonl (v);
	بائٹیں = (صحیح) حجم (flex_uint32_t);
	rv = (صحیح) fwrite (&vnet, (size_t) بائٹیں, 1, wr->برآمد);
	اگر (rv != 1)
		واپس -1;
	wr->کل_written += بائٹیں;
	واپس بائٹیں;
}

/** Write two bytes in network byte order.
 *  @param  wr  the table writer
 *  @param  v    a word in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
صحیح yytbl_write16 (ساخت yytbl_writer *wr, flex_uint16_t v)
{
	flex_uint16_t vnet;
	صحیح  بائٹیں, rv;

	vnet = htons (v);
	بائٹیں = (صحیح) حجم (flex_uint16_t);
	rv = (صحیح) fwrite (&vnet, (size_t) بائٹیں, 1, wr->برآمد);
	اگر (rv != 1)
		واپس -1;
	wr->کل_written += بائٹیں;
	واپس بائٹیں;
}

/** Write a byte.
 *  @param  wr  the table writer
 *  @param  v    the value to be written
 *  @return  -1 on error. number of bytes written on success.
 */
صحیح yytbl_write8 (ساخت yytbl_writer *wr, flex_uint8_t v)
{
	صحیح  بائٹیں, rv;

	بائٹیں = (صحیح) حجم (flex_uint8_t);
	rv = (صحیح) fwrite (&v, (size_t) بائٹیں, 1, wr->برآمد);
	اگر (rv != 1)
		واپس -1;
	wr->کل_written += بائٹیں;
	واپس بائٹیں;
}


/* XXX Not Used */
#اگر 0
/** Extract data element [i][j] from array data tables. 
 * @param tbl data table
 * @param i index into higher dimension array. i should be zero for one-dimensional arrays.
 * @param j index into lower dimension array.
 * @param k index into struct, must be 0 or 1. Only valid for YYTD_ID_TRANSITION table
 * @return data[i][j + k]
 */
ساکن flex_int32_t yytbl_ڈیٹا_getijk (ثابت ساخت yytbl_ڈیٹا *tbl, صحیح i,
				  صحیح j, صحیح k)
{
	flex_int32_t lo;

	k %= 2;
	lo = tbl->td_lolen;

	انتخاب (YYTDFLAGS2_بائٹیں (tbl->td_flags)) {
	حالت حجم (flex_int8_t):
		واپس ((flex_int8_t *) (tbl->td_ڈیٹا))[(i * lo + j) * (k + 1) +
						   k];
	حالت حجم (flex_int16_t):
		واپس ((flex_int16_t *) (tbl->td_ڈیٹا))[(i * lo + j) * (k +
								    1) +
						    k];
	حالت حجم (flex_int32_t):
		واپس ((flex_int32_t *) (tbl->td_ڈیٹا))[(i * lo + j) * (k +
								    1) +
						    k];
	طےشدہ:
		flex_die (_("invalid td_flags detected"));
		توڑو;
	}

	واپس 0;
}
#اگر_ختم /* Not used */

/** Extract data element [i] from array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @return data[i]
 */
ساکن flex_int32_t yytbl_ڈیٹا_geti (ثابت ساخت yytbl_ڈیٹا *tbl, صحیح i)
{

	انتخاب (YYTDFLAGS2_بائٹیں (tbl->td_flags)) {
	حالت حجم (flex_int8_t):
		واپس ((flex_int8_t *) (tbl->td_ڈیٹا))[i];
	حالت حجم (flex_int16_t):
		واپس ((flex_int16_t *) (tbl->td_ڈیٹا))[i];
	حالت حجم (flex_int32_t):
		واپس ((flex_int32_t *) (tbl->td_ڈیٹا))[i];
	طےشدہ:
		flex_die (_("invalid td_flags detected"));
		توڑو;
	}
	واپس 0;
}

/** Set data element [i] in array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @param newval new value for data[i]
 */
ساکن خالی yytbl_ڈیٹا_seti (ثابت ساخت yytbl_ڈیٹا *tbl, صحیح i,
			     flex_int32_t newval)
{

	انتخاب (YYTDFLAGS2_بائٹیں (tbl->td_flags)) {
	حالت حجم (flex_int8_t):
		((flex_int8_t *) (tbl->td_ڈیٹا))[i] = (flex_int8_t) newval;
		توڑو;
	حالت حجم (flex_int16_t):
		((flex_int16_t *) (tbl->td_ڈیٹا))[i] = (flex_int16_t) newval;
		توڑو;
	حالت حجم (flex_int32_t):
		((flex_int32_t *) (tbl->td_ڈیٹا))[i] = (flex_int32_t) newval;
		توڑو;
	طےشدہ:
		flex_die (_("invalid td_flags detected"));
		توڑو;
	}
}

/** Calculate the number of bytes  needed to hold the largest
 *  absolute value in this data array.
 *  @param tbl  the data table
 *  @return sizeof(n) where n in {flex_int8_t, flex_int16_t, flex_int32_t}
 */
ساکن size_t min_int_سائز (ساخت yytbl_ڈیٹا *tbl)
{
	flex_int32_t i, کل_len;
	flex_int32_t max = 0;

	کل_len = yytbl_calc_کل_len (tbl);

	برائے (i = 0; i < کل_len; i++) {
		flex_int32_t n;

		n = مطلق_قدر (yytbl_ڈیٹا_geti (tbl, i));

		اگر (max < n)
			max = n;
	}

	اگر (max <= INT8_MAX)
		واپس حجم (flex_int8_t);
	ورنہ اگر (max <= INT16_MAX)
		واپس حجم (flex_int16_t);
	ورنہ
		واپس حجم (flex_int32_t);
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
خالی yytbl_ڈیٹا_compress (ساخت yytbl_ڈیٹا *tbl)
{
	flex_int32_t i, کل_len;
	size_t newsz;
	ساخت yytbl_ڈیٹا newtbl;

	yytbl_ڈیٹا_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_سائز (tbl);


	اگر (newsz == YYTDFLAGS2_بائٹیں (tbl->td_flags))
		/* No change in this table needed. */
		واپس;

	اگر (newsz > YYTDFLAGS2_بائٹیں (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		واپس;
	}

	کل_len = yytbl_calc_کل_len (tbl);
	newtbl.td_ڈیٹا = صفر_حافظہ_دو ((size_t) کل_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	برائے (i = 0; i < کل_len; i++) {
		flex_int32_t g;

		g = yytbl_ڈیٹا_geti (tbl, i);
		yytbl_ڈیٹا_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	آزاد (tbl->td_ڈیٹا);
	*tbl = newtbl;
}

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
