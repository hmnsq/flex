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


#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tables.h"

/** Convert size_t to t_flag.
 *  @param n in {1,2,4}
 *  @return YYTD_DATA*. 
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BYTES2TFLAG(n)\
    (((n) == ਆਕਾਰ(flex_int8_t))\
        ? YYTD_DATA8\
        :(((n)== ਆਕਾਰ(flex_int16_t))\
            ? YYTD_DATA16\
            : YYTD_DATA32))

/** Clear YYTD_DATA* bit flags
 * @return the flag with the YYTD_DATA* bits cleared
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TFLAGS_CLRDATA(flg) ((flg) & ~(YYTD_DATA8 | YYTD_DATA16 | YYTD_DATA32))

ਪੂਰਨ     yytbl_write32 (ਬਣਤਰ yytbl_writer *wr, flex_uint32_t v);
ਪੂਰਨ     yytbl_write16 (ਬਣਤਰ yytbl_writer *wr, flex_uint16_t v);
ਪੂਰਨ     yytbl_write8 (ਬਣਤਰ yytbl_writer *wr, flex_uint8_t v);
ਪੂਰਨ     yytbl_writen (ਬਣਤਰ yytbl_writer *wr, ਖਾਲੀ *v, ਪੂਰਨ len);
ਸਥਿਰ flex_int32_t yytbl_ਅੰਕੜੇ_geti (ਅਚਲ ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl, ਪੂਰਨ i);
/* XXX Not used
static flex_int32_t yytbl_data_getijk (const struct yytbl_data *tbl, int i,
				  int j, int k);
 */


/** Initialize the table writer.
 *  @param wr an uninitialized writer
 *  @param out the output file
 *  @return 0 on success
 */
ਪੂਰਨ yytbl_writer_init (ਬਣਤਰ yytbl_writer *wr, FILE * ਬਾਹਰਲਾ)
{
	wr->ਬਾਹਰਲਾ = ਬਾਹਰਲਾ;
	wr->ਕੁੱਲ_written = 0;
	ਵਾਪਸ 0;
}

/** Initialize a table header.
 *  @param th  The uninitialized structure
 *  @param version_str the  version string
 *  @param name the name of this table set
 */
ਪੂਰਨ yytbl_hdr_init (ਬਣਤਰ yytbl_hdr *th, ਅਚਲ ਅੱਖਰ *ਸੰਸਕਰਣ_str,
		    ਅਚਲ ਅੱਖਰ *name)
{
	memset (th, 0, ਆਕਾਰ (ਬਣਤਰ yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = (flex_uint32_t) (14 + ਲੜੀ_ਲੰਬਾਈ (ਸੰਸਕਰਣ_str) + 1 + ਲੜੀ_ਲੰਬਾਈ (name) + 1);
	th->th_hsize += (8 - (th->th_hsize % 8)) % 8; // Pad to 64-bit boundary
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_ਸੰਸਕਰਣ = xstrdup(ਸੰਸਕਰਣ_str);
	th->th_name = xstrdup(name);
	ਵਾਪਸ 0;
}

/** Allocate and initialize a table data structure.
 *  @param td a pointer to an uninitialized table
 *  @param id  the table identifier
 *  @return 0 on success
 */
ਪੂਰਨ yytbl_ਅੰਕੜੇ_init (ਬਣਤਰ yytbl_ਅੰਕੜੇ *td, ਗਿਣਤੀ yytbl_id id)
{

	memset (td, 0, ਆਕਾਰ (ਬਣਤਰ yytbl_ਅੰਕੜੇ));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	ਵਾਪਸ 0;
}

/** Clean up table and data array.
 *  @param td will be destroyed
 *  @return 0 on success
 */
ਪੂਰਨ yytbl_ਅੰਕੜੇ_destroy (ਬਣਤਰ yytbl_ਅੰਕੜੇ *td)
{
	ਮੁਕਤ(td->td_ਅੰਕੜੇ);
	td->td_ਅੰਕੜੇ = 0;
	ਮੁਕਤ (td);
	ਵਾਪਸ 0;
}

/** Write enough padding to bring the file pointer to a 64-bit boundary. */
ਸਥਿਰ ਪੂਰਨ yytbl_write_pad64 (ਬਣਤਰ yytbl_writer *wr)
{
	ਪੂਰਨ bwritten = 0;

	ਜਦੋਂ (wr->ਕੁੱਲ_written % (8 * ਆਕਾਰ(flex_uint8_t)) > 0) {
		ਜੇ (yytbl_write8 (wr, 0) < 0)
			ਵਾਪਸ -1;
		ਨਹੀਂਤਾਂ
			bwritten++;
	}
	ਵਾਪਸ bwritten;
}

/** write the header.
 *  @param wr the output stream
 *  @param th table header to be written
 *  @return -1 on error, or bytes written on success.
 */
ਪੂਰਨ yytbl_hdr_fwrite (ਬਣਤਰ yytbl_writer *wr, ਅਚਲ ਬਣਤਰ yytbl_hdr *th)
{
	ਪੂਰਨ  sz, rv;
	ਪੂਰਨ     bwritten = 0;

	ਜੇ (yytbl_write32 (wr, th->th_magic) < 0
	    || yytbl_write32 (wr, th->th_hsize) < 0)
		flex_die (_("th_magic|th_hsize write32 failed"));
	bwritten += 8;

	ਜੇ (fgetpos (wr->ਬਾਹਰਲਾ, &(wr->th_ssize_pos)) != 0)
		flex_die (_("fgetpos failed"));

	ਜੇ (yytbl_write32 (wr, th->th_ssize) < 0
	    || yytbl_write16 (wr, th->th_flags) < 0)
		flex_die (_("th_ssize|th_flags write failed"));
	bwritten += 6;

	sz = (ਪੂਰਨ) ਲੜੀ_ਲੰਬਾਈ (th->th_ਸੰਸਕਰਣ) + 1;
	ਜੇ ((rv = yytbl_writen (wr, th->th_ਸੰਸਕਰਣ, sz)) != sz)
		flex_die (_("th_version written failed"));
	bwritten += rv;

	sz = (ਪੂਰਨ) ਲੜੀ_ਲੰਬਾਈ (th->th_name) + 1;
	ਜੇ ((rv = yytbl_writen (wr, th->th_name, sz)) != sz)
		flex_die (_("th_name written failed"));
	bwritten += rv;

	/* add padding */
	ਜੇ ((rv = yytbl_write_pad64 (wr)) < 0)
		flex_die (_("pad64 failed"));
	bwritten += rv;

	/* Sanity check */
	ਜੇ (bwritten != (ਪੂਰਨ) th->th_hsize)
		flex_die (_("pad64 failed"));

	ਵਾਪਸ bwritten;
}


/** Write this table.
 *  @param wr the file writer
 *  @param td table data to be written
 *  @return -1 on error, or bytes written on success.
 */
ਪੂਰਨ yytbl_ਅੰਕੜੇ_fwrite (ਬਣਤਰ yytbl_writer *wr, ਬਣਤਰ yytbl_ਅੰਕੜੇ *td)
{
	ਪੂਰਨ  rv;
	flex_int32_t bwritten = 0;
	flex_int32_t i, ਕੁੱਲ_len;
	fpos_t  pos;

	ਜੇ ((rv = yytbl_write16 (wr, td->td_id)) < 0)
		ਵਾਪਸ -1;
	bwritten += rv;

	ਜੇ ((rv = yytbl_write16 (wr, td->td_flags)) < 0)
		ਵਾਪਸ -1;
	bwritten += rv;

	ਜੇ ((rv = yytbl_write32 (wr, td->td_hilen)) < 0)
		ਵਾਪਸ -1;
	bwritten += rv;

	ਜੇ ((rv = yytbl_write32 (wr, td->td_lolen)) < 0)
		ਵਾਪਸ -1;
	bwritten += rv;

	ਕੁੱਲ_len = yytbl_calc_ਕੁੱਲ_len (td);
	ਲਈ (i = 0; i < ਕੁੱਲ_len; i++) {
		ਚੋਣ (YYTDFLAGS2_ਬਾਈਟਾਂ (td->td_flags)) {
		ਹਾਲਤ ਆਕਾਰ (flex_int8_t):
			rv = yytbl_write8 (wr, (flex_uint8_t) yytbl_ਅੰਕੜੇ_geti (td, i));
			ਰੋਕੋ;
		ਹਾਲਤ ਆਕਾਰ (flex_int16_t):
			rv = yytbl_write16 (wr, (flex_uint16_t) yytbl_ਅੰਕੜੇ_geti (td, i));
			ਰੋਕੋ;
		ਹਾਲਤ ਆਕਾਰ (flex_int32_t):
			rv = yytbl_write32 (wr, (flex_uint32_t) yytbl_ਅੰਕੜੇ_geti (td, i));
			ਰੋਕੋ;
		ਮੂਲ:
			flex_die (_("invalid td_flags detected"));
		}
		ਜੇ (rv < 0) {
			flex_die (_("error while writing tables"));
			ਵਾਪਸ -1;
		}
		bwritten += rv;
	}

	/* Sanity check */
	ਜੇ (bwritten != (12 + ਕੁੱਲ_len * (ਪੂਰਨ) YYTDFLAGS2_ਬਾਈਟਾਂ (td->td_flags))) {
		flex_die (_("insanity detected"));
		ਵਾਪਸ -1;
	}

	/* add padding */
	ਜੇ ((rv = yytbl_write_pad64 (wr)) < 0) {
		flex_die (_("pad64 failed"));
		ਵਾਪਸ -1;
	}
	bwritten += rv;

	/* Now go back and update the th_hsize member */
	ਜੇ (fgetpos (wr->ਬਾਹਰਲਾ, &pos) != 0
	    || fsetpos (wr->ਬਾਹਰਲਾ, &(wr->th_ssize_pos)) != 0
	    || yytbl_write32 (wr, (flex_uint32_t) wr->ਕੁੱਲ_written) < 0
	    || fsetpos (wr->ਬਾਹਰਲਾ, &pos)) {
		flex_die (_("get|set|fwrite32 failed"));
		ਵਾਪਸ -1;
	}
	ਨਹੀਂਤਾਂ
		/* Don't count the int we just wrote. */
		wr->ਕੁੱਲ_written -= (ਪੂਰਨ) ਆਕਾਰ (flex_int32_t);
	ਵਾਪਸ bwritten;
}

/** Write n bytes.
 *  @param  wr   the table writer
 *  @param  v    data to be written
 *  @param  len  number of bytes
 *  @return  -1 on error. number of bytes written on success.
 */
ਪੂਰਨ yytbl_writen (ਬਣਤਰ yytbl_writer *wr, ਖਾਲੀ *v, ਪੂਰਨ len)
{
	ਪੂਰਨ  rv;

	rv = (ਪੂਰਨ) fwrite (v, 1, (size_t) len, wr->ਬਾਹਰਲਾ);
	ਜੇ (rv != len)
		ਵਾਪਸ -1;
	wr->ਕੁੱਲ_written += len;
	ਵਾਪਸ len;
}

/** Write four bytes in network byte order
 *  @param  wr  the table writer
 *  @param  v    a dword in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
ਪੂਰਨ yytbl_write32 (ਬਣਤਰ yytbl_writer *wr, flex_uint32_t v)
{
	flex_uint32_t vnet;
	ਪੂਰਨ  ਬਾਈਟਾਂ, rv;

	vnet = htonl (v);
	ਬਾਈਟਾਂ = (ਪੂਰਨ) ਆਕਾਰ (flex_uint32_t);
	rv = (ਪੂਰਨ) fwrite (&vnet, (size_t) ਬਾਈਟਾਂ, 1, wr->ਬਾਹਰਲਾ);
	ਜੇ (rv != 1)
		ਵਾਪਸ -1;
	wr->ਕੁੱਲ_written += ਬਾਈਟਾਂ;
	ਵਾਪਸ ਬਾਈਟਾਂ;
}

/** Write two bytes in network byte order.
 *  @param  wr  the table writer
 *  @param  v    a word in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
ਪੂਰਨ yytbl_write16 (ਬਣਤਰ yytbl_writer *wr, flex_uint16_t v)
{
	flex_uint16_t vnet;
	ਪੂਰਨ  ਬਾਈਟਾਂ, rv;

	vnet = htons (v);
	ਬਾਈਟਾਂ = (ਪੂਰਨ) ਆਕਾਰ (flex_uint16_t);
	rv = (ਪੂਰਨ) fwrite (&vnet, (size_t) ਬਾਈਟਾਂ, 1, wr->ਬਾਹਰਲਾ);
	ਜੇ (rv != 1)
		ਵਾਪਸ -1;
	wr->ਕੁੱਲ_written += ਬਾਈਟਾਂ;
	ਵਾਪਸ ਬਾਈਟਾਂ;
}

/** Write a byte.
 *  @param  wr  the table writer
 *  @param  v    the value to be written
 *  @return  -1 on error. number of bytes written on success.
 */
ਪੂਰਨ yytbl_write8 (ਬਣਤਰ yytbl_writer *wr, flex_uint8_t v)
{
	ਪੂਰਨ  ਬਾਈਟਾਂ, rv;

	ਬਾਈਟਾਂ = (ਪੂਰਨ) ਆਕਾਰ (flex_uint8_t);
	rv = (ਪੂਰਨ) fwrite (&v, (size_t) ਬਾਈਟਾਂ, 1, wr->ਬਾਹਰਲਾ);
	ਜੇ (rv != 1)
		ਵਾਪਸ -1;
	wr->ਕੁੱਲ_written += ਬਾਈਟਾਂ;
	ਵਾਪਸ ਬਾਈਟਾਂ;
}


/* XXX Not Used */
#ਜੇ 0
/** Extract data element [i][j] from array data tables. 
 * @param tbl data table
 * @param i index into higher dimension array. i should be zero for one-dimensional arrays.
 * @param j index into lower dimension array.
 * @param k index into struct, must be 0 or 1. Only valid for YYTD_ID_TRANSITION table
 * @return data[i][j + k]
 */
ਸਥਿਰ flex_int32_t yytbl_ਅੰਕੜੇ_getijk (ਅਚਲ ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl, ਪੂਰਨ i,
				  ਪੂਰਨ j, ਪੂਰਨ k)
{
	flex_int32_t lo;

	k %= 2;
	lo = tbl->td_lolen;

	ਚੋਣ (YYTDFLAGS2_ਬਾਈਟਾਂ (tbl->td_flags)) {
	ਹਾਲਤ ਆਕਾਰ (flex_int8_t):
		ਵਾਪਸ ((flex_int8_t *) (tbl->td_ਅੰਕੜੇ))[(i * lo + j) * (k + 1) +
						   k];
	ਹਾਲਤ ਆਕਾਰ (flex_int16_t):
		ਵਾਪਸ ((flex_int16_t *) (tbl->td_ਅੰਕੜੇ))[(i * lo + j) * (k +
								    1) +
						    k];
	ਹਾਲਤ ਆਕਾਰ (flex_int32_t):
		ਵਾਪਸ ((flex_int32_t *) (tbl->td_ਅੰਕੜੇ))[(i * lo + j) * (k +
								    1) +
						    k];
	ਮੂਲ:
		flex_die (_("invalid td_flags detected"));
		ਰੋਕੋ;
	}

	ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ /* Not used */

/** Extract data element [i] from array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @return data[i]
 */
ਸਥਿਰ flex_int32_t yytbl_ਅੰਕੜੇ_geti (ਅਚਲ ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl, ਪੂਰਨ i)
{

	ਚੋਣ (YYTDFLAGS2_ਬਾਈਟਾਂ (tbl->td_flags)) {
	ਹਾਲਤ ਆਕਾਰ (flex_int8_t):
		ਵਾਪਸ ((flex_int8_t *) (tbl->td_ਅੰਕੜੇ))[i];
	ਹਾਲਤ ਆਕਾਰ (flex_int16_t):
		ਵਾਪਸ ((flex_int16_t *) (tbl->td_ਅੰਕੜੇ))[i];
	ਹਾਲਤ ਆਕਾਰ (flex_int32_t):
		ਵਾਪਸ ((flex_int32_t *) (tbl->td_ਅੰਕੜੇ))[i];
	ਮੂਲ:
		flex_die (_("invalid td_flags detected"));
		ਰੋਕੋ;
	}
	ਵਾਪਸ 0;
}

/** Set data element [i] in array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @param newval new value for data[i]
 */
ਸਥਿਰ ਖਾਲੀ yytbl_ਅੰਕੜੇ_seti (ਅਚਲ ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl, ਪੂਰਨ i,
			     flex_int32_t newval)
{

	ਚੋਣ (YYTDFLAGS2_ਬਾਈਟਾਂ (tbl->td_flags)) {
	ਹਾਲਤ ਆਕਾਰ (flex_int8_t):
		((flex_int8_t *) (tbl->td_ਅੰਕੜੇ))[i] = (flex_int8_t) newval;
		ਰੋਕੋ;
	ਹਾਲਤ ਆਕਾਰ (flex_int16_t):
		((flex_int16_t *) (tbl->td_ਅੰਕੜੇ))[i] = (flex_int16_t) newval;
		ਰੋਕੋ;
	ਹਾਲਤ ਆਕਾਰ (flex_int32_t):
		((flex_int32_t *) (tbl->td_ਅੰਕੜੇ))[i] = (flex_int32_t) newval;
		ਰੋਕੋ;
	ਮੂਲ:
		flex_die (_("invalid td_flags detected"));
		ਰੋਕੋ;
	}
}

/** Calculate the number of bytes  needed to hold the largest
 *  absolute value in this data array.
 *  @param tbl  the data table
 *  @return sizeof(n) where n in {flex_int8_t, flex_int16_t, flex_int32_t}
 */
ਸਥਿਰ size_t min_int_ਮਾਪ (ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl)
{
	flex_int32_t i, ਕੁੱਲ_len;
	flex_int32_t max = 0;

	ਕੁੱਲ_len = yytbl_calc_ਕੁੱਲ_len (tbl);

	ਲਈ (i = 0; i < ਕੁੱਲ_len; i++) {
		flex_int32_t n;

		n = ਨਿਰਪੇਖ (yytbl_ਅੰਕੜੇ_geti (tbl, i));

		ਜੇ (max < n)
			max = n;
	}

	ਜੇ (max <= INT8_MAX)
		ਵਾਪਸ ਆਕਾਰ (flex_int8_t);
	ਨਹੀਂਤਾਂ ਜੇ (max <= INT16_MAX)
		ਵਾਪਸ ਆਕਾਰ (flex_int16_t);
	ਨਹੀਂਤਾਂ
		ਵਾਪਸ ਆਕਾਰ (flex_int32_t);
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
ਖਾਲੀ yytbl_ਅੰਕੜੇ_compress (ਬਣਤਰ yytbl_ਅੰਕੜੇ *tbl)
{
	flex_int32_t i, ਕੁੱਲ_len;
	size_t newsz;
	ਬਣਤਰ yytbl_ਅੰਕੜੇ newtbl;

	yytbl_ਅੰਕੜੇ_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_ਮਾਪ (tbl);


	ਜੇ (newsz == YYTDFLAGS2_ਬਾਈਟਾਂ (tbl->td_flags))
		/* No change in this table needed. */
		ਵਾਪਸ;

	ਜੇ (newsz > YYTDFLAGS2_ਬਾਈਟਾਂ (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		ਵਾਪਸ;
	}

	ਕੁੱਲ_len = yytbl_calc_ਕੁੱਲ_len (tbl);
	newtbl.td_ਅੰਕੜੇ = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ ((size_t) ਕੁੱਲ_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	ਲਈ (i = 0; i < ਕੁੱਲ_len; i++) {
		flex_int32_t g;

		g = yytbl_ਅੰਕੜੇ_geti (tbl, i);
		yytbl_ਅੰਕੜੇ_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	ਮੁਕਤ (tbl->td_ਅੰਕੜੇ);
	*tbl = newtbl;
}

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
