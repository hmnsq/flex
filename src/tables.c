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


#অন্তর্ভাব "flexdef.h"
#অন্তর্ভাব "tables.h"

/** Convert size_t to t_flag.
 *  @param n in {1,2,4}
 *  @return YYTD_DATA*. 
 */
#define BYTES2TFLAG(n)\
    (((n) == আকার(flex_int8_t))\
        ? YYTD_DATA8\
        :(((n)== আকার(flex_int16_t))\
            ? YYTD_DATA16\
            : YYTD_DATA32))

/** Clear YYTD_DATA* bit flags
 * @return the flag with the YYTD_DATA* bits cleared
 */
#define TFLAGS_CLRDATA(flg) ((flg) & ~(YYTD_DATA8 | YYTD_DATA16 | YYTD_DATA32))

পূর্ণসংখ্যা     yytbl_write32 (কাঠামো yytbl_writer *wr, flex_uint32_t v);
পূর্ণসংখ্যা     yytbl_write16 (কাঠামো yytbl_writer *wr, flex_uint16_t v);
পূর্ণসংখ্যা     yytbl_write8 (কাঠামো yytbl_writer *wr, flex_uint8_t v);
পূর্ণসংখ্যা     yytbl_writen (কাঠামো yytbl_writer *wr, শূন্য *v, পূর্ণসংখ্যা len);
স্থির flex_int32_t yytbl_তথ্য_geti (ধ্রুবক কাঠামো yytbl_তথ্য *tbl, পূর্ণসংখ্যা i);
/* XXX Not used
static flex_int32_t yytbl_data_getijk (const struct yytbl_data *tbl, int i,
				  int j, int k);
 */


/** Initialize the table writer.
 *  @param wr an uninitialized writer
 *  @param out the output file
 *  @return 0 on success
 */
পূর্ণসংখ্যা yytbl_writer_init (কাঠামো yytbl_writer *wr, FILE * out)
{
	wr->out = out;
	wr->যোগ_written = 0;
	ফেরত 0;
}

/** Initialize a table header.
 *  @param th  The uninitialized structure
 *  @param version_str the  version string
 *  @param name the name of this table set
 */
পূর্ণসংখ্যা yytbl_hdr_init (কাঠামো yytbl_hdr *th, ধ্রুবক অক্ষর *version_str,
		    ধ্রুবক অক্ষর *name)
{
	memset (th, 0, আকার (কাঠামো yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = (flex_uint32_t) (14 + strlen (version_str) + 1 + strlen (name) + 1);
	th->th_hsize += (8 - (th->th_hsize % 8)) % 8; // Pad to 64-bit boundary
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_version = xstrdup(version_str);
	th->th_name = xstrdup(name);
	ফেরত 0;
}

/** Allocate and initialize a table data structure.
 *  @param td a pointer to an uninitialized table
 *  @param id  the table identifier
 *  @return 0 on success
 */
পূর্ণসংখ্যা yytbl_তথ্য_init (কাঠামো yytbl_তথ্য *td, গণনা yytbl_id id)
{

	memset (td, 0, আকার (কাঠামো yytbl_তথ্য));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	ফেরত 0;
}

/** Clean up table and data array.
 *  @param td will be destroyed
 *  @return 0 on success
 */
পূর্ণসংখ্যা yytbl_তথ্য_destroy (কাঠামো yytbl_তথ্য *td)
{
	মুক্ত(td->td_তথ্য);
	td->td_তথ্য = 0;
	মুক্ত (td);
	ফেরত 0;
}

/** Write enough padding to bring the file pointer to a 64-bit boundary. */
স্থির পূর্ণসংখ্যা yytbl_write_pad64 (কাঠামো yytbl_writer *wr)
{
	পূর্ণসংখ্যা bwritten = 0;

	যখন (wr->যোগ_written % (8 * আকার(flex_uint8_t)) > 0) {
		যদি (yytbl_write8 (wr, 0) < 0)
			ফেরত -1;
		অন্যথা
			bwritten++;
	}
	ফেরত bwritten;
}

/** write the header.
 *  @param wr the output stream
 *  @param th table header to be written
 *  @return -1 on error, or bytes written on success.
 */
পূর্ণসংখ্যা yytbl_hdr_fwrite (কাঠামো yytbl_writer *wr, ধ্রুবক কাঠামো yytbl_hdr *th)
{
	পূর্ণসংখ্যা  sz, rv;
	পূর্ণসংখ্যা     bwritten = 0;

	যদি (yytbl_write32 (wr, th->th_magic) < 0
	    || yytbl_write32 (wr, th->th_hsize) < 0)
		flex_die (_("th_magic|th_hsize write32 failed"));
	bwritten += 8;

	যদি (fgetpos (wr->out, &(wr->th_ssize_pos)) != 0)
		flex_die (_("fgetpos failed"));

	যদি (yytbl_write32 (wr, th->th_ssize) < 0
	    || yytbl_write16 (wr, th->th_flags) < 0)
		flex_die (_("th_ssize|th_flags write failed"));
	bwritten += 6;

	sz = (পূর্ণসংখ্যা) strlen (th->th_version) + 1;
	যদি ((rv = yytbl_writen (wr, th->th_version, sz)) != sz)
		flex_die (_("th_version written failed"));
	bwritten += rv;

	sz = (পূর্ণসংখ্যা) strlen (th->th_name) + 1;
	যদি ((rv = yytbl_writen (wr, th->th_name, sz)) != sz)
		flex_die (_("th_name written failed"));
	bwritten += rv;

	/* add padding */
	যদি ((rv = yytbl_write_pad64 (wr)) < 0)
		flex_die (_("pad64 failed"));
	bwritten += rv;

	/* Sanity check */
	যদি (bwritten != (পূর্ণসংখ্যা) th->th_hsize)
		flex_die (_("pad64 failed"));

	ফেরত bwritten;
}


/** Write this table.
 *  @param wr the file writer
 *  @param td table data to be written
 *  @return -1 on error, or bytes written on success.
 */
পূর্ণসংখ্যা yytbl_তথ্য_fwrite (কাঠামো yytbl_writer *wr, কাঠামো yytbl_তথ্য *td)
{
	পূর্ণসংখ্যা  rv;
	flex_int32_t bwritten = 0;
	flex_int32_t i, যোগ_len;
	fpos_t  pos;

	যদি ((rv = yytbl_write16 (wr, td->td_id)) < 0)
		ফেরত -1;
	bwritten += rv;

	যদি ((rv = yytbl_write16 (wr, td->td_flags)) < 0)
		ফেরত -1;
	bwritten += rv;

	যদি ((rv = yytbl_write32 (wr, td->td_hilen)) < 0)
		ফেরত -1;
	bwritten += rv;

	যদি ((rv = yytbl_write32 (wr, td->td_lolen)) < 0)
		ফেরত -1;
	bwritten += rv;

	যোগ_len = yytbl_calc_যোগ_len (td);
	জন্য (i = 0; i < যোগ_len; i++) {
		নির্বাচন (YYTDFLAGS2BYTES (td->td_flags)) {
		ক্ষেত্র আকার (flex_int8_t):
			rv = yytbl_write8 (wr, (flex_uint8_t) yytbl_তথ্য_geti (td, i));
			বিরতি;
		ক্ষেত্র আকার (flex_int16_t):
			rv = yytbl_write16 (wr, (flex_uint16_t) yytbl_তথ্য_geti (td, i));
			বিরতি;
		ক্ষেত্র আকার (flex_int32_t):
			rv = yytbl_write32 (wr, (flex_uint32_t) yytbl_তথ্য_geti (td, i));
			বিরতি;
		পূর্বনির্ধারিত:
			flex_die (_("invalid td_flags detected"));
		}
		যদি (rv < 0) {
			flex_die (_("error while writing tables"));
			ফেরত -1;
		}
		bwritten += rv;
	}

	/* Sanity check */
	যদি (bwritten != (12 + যোগ_len * (পূর্ণসংখ্যা) YYTDFLAGS2BYTES (td->td_flags))) {
		flex_die (_("insanity detected"));
		ফেরত -1;
	}

	/* add padding */
	যদি ((rv = yytbl_write_pad64 (wr)) < 0) {
		flex_die (_("pad64 failed"));
		ফেরত -1;
	}
	bwritten += rv;

	/* Now go back and update the th_hsize member */
	যদি (fgetpos (wr->out, &pos) != 0
	    || fsetpos (wr->out, &(wr->th_ssize_pos)) != 0
	    || yytbl_write32 (wr, (flex_uint32_t) wr->যোগ_written) < 0
	    || fsetpos (wr->out, &pos)) {
		flex_die (_("get|set|fwrite32 failed"));
		ফেরত -1;
	}
	অন্যথা
		/* Don't count the int we just wrote. */
		wr->যোগ_written -= (পূর্ণসংখ্যা) আকার (flex_int32_t);
	ফেরত bwritten;
}

/** Write n bytes.
 *  @param  wr   the table writer
 *  @param  v    data to be written
 *  @param  len  number of bytes
 *  @return  -1 on error. number of bytes written on success.
 */
পূর্ণসংখ্যা yytbl_writen (কাঠামো yytbl_writer *wr, শূন্য *v, পূর্ণসংখ্যা len)
{
	পূর্ণসংখ্যা  rv;

	rv = (পূর্ণসংখ্যা) fwrite (v, 1, (size_t) len, wr->out);
	যদি (rv != len)
		ফেরত -1;
	wr->যোগ_written += len;
	ফেরত len;
}

/** Write four bytes in network byte order
 *  @param  wr  the table writer
 *  @param  v    a dword in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
পূর্ণসংখ্যা yytbl_write32 (কাঠামো yytbl_writer *wr, flex_uint32_t v)
{
	flex_uint32_t vnet;
	পূর্ণসংখ্যা  bytes, rv;

	vnet = htonl (v);
	bytes = (পূর্ণসংখ্যা) আকার (flex_uint32_t);
	rv = (পূর্ণসংখ্যা) fwrite (&vnet, (size_t) bytes, 1, wr->out);
	যদি (rv != 1)
		ফেরত -1;
	wr->যোগ_written += bytes;
	ফেরত bytes;
}

/** Write two bytes in network byte order.
 *  @param  wr  the table writer
 *  @param  v    a word in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
পূর্ণসংখ্যা yytbl_write16 (কাঠামো yytbl_writer *wr, flex_uint16_t v)
{
	flex_uint16_t vnet;
	পূর্ণসংখ্যা  bytes, rv;

	vnet = htons (v);
	bytes = (পূর্ণসংখ্যা) আকার (flex_uint16_t);
	rv = (পূর্ণসংখ্যা) fwrite (&vnet, (size_t) bytes, 1, wr->out);
	যদি (rv != 1)
		ফেরত -1;
	wr->যোগ_written += bytes;
	ফেরত bytes;
}

/** Write a byte.
 *  @param  wr  the table writer
 *  @param  v    the value to be written
 *  @return  -1 on error. number of bytes written on success.
 */
পূর্ণসংখ্যা yytbl_write8 (কাঠামো yytbl_writer *wr, flex_uint8_t v)
{
	পূর্ণসংখ্যা  bytes, rv;

	bytes = (পূর্ণসংখ্যা) আকার (flex_uint8_t);
	rv = (পূর্ণসংখ্যা) fwrite (&v, (size_t) bytes, 1, wr->out);
	যদি (rv != 1)
		ফেরত -1;
	wr->যোগ_written += bytes;
	ফেরত bytes;
}


/* XXX Not Used */
#যদি 0
/** Extract data element [i][j] from array data tables. 
 * @param tbl data table
 * @param i index into higher dimension array. i should be zero for one-dimensional arrays.
 * @param j index into lower dimension array.
 * @param k index into struct, must be 0 or 1. Only valid for YYTD_ID_TRANSITION table
 * @return data[i][j + k]
 */
স্থির flex_int32_t yytbl_তথ্য_getijk (ধ্রুবক কাঠামো yytbl_তথ্য *tbl, পূর্ণসংখ্যা i,
				  পূর্ণসংখ্যা j, পূর্ণসংখ্যা k)
{
	flex_int32_t lo;

	k %= 2;
	lo = tbl->td_lolen;

	নির্বাচন (YYTDFLAGS2BYTES (tbl->td_flags)) {
	ক্ষেত্র আকার (flex_int8_t):
		ফেরত ((flex_int8_t *) (tbl->td_তথ্য))[(i * lo + j) * (k + 1) +
						   k];
	ক্ষেত্র আকার (flex_int16_t):
		ফেরত ((flex_int16_t *) (tbl->td_তথ্য))[(i * lo + j) * (k +
								    1) +
						    k];
	ক্ষেত্র আকার (flex_int32_t):
		ফেরত ((flex_int32_t *) (tbl->td_তথ্য))[(i * lo + j) * (k +
								    1) +
						    k];
	পূর্বনির্ধারিত:
		flex_die (_("invalid td_flags detected"));
		বিরতি;
	}

	ফেরত 0;
}
#endif /* Not used */

/** Extract data element [i] from array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @return data[i]
 */
স্থির flex_int32_t yytbl_তথ্য_geti (ধ্রুবক কাঠামো yytbl_তথ্য *tbl, পূর্ণসংখ্যা i)
{

	নির্বাচন (YYTDFLAGS2BYTES (tbl->td_flags)) {
	ক্ষেত্র আকার (flex_int8_t):
		ফেরত ((flex_int8_t *) (tbl->td_তথ্য))[i];
	ক্ষেত্র আকার (flex_int16_t):
		ফেরত ((flex_int16_t *) (tbl->td_তথ্য))[i];
	ক্ষেত্র আকার (flex_int32_t):
		ফেরত ((flex_int32_t *) (tbl->td_তথ্য))[i];
	পূর্বনির্ধারিত:
		flex_die (_("invalid td_flags detected"));
		বিরতি;
	}
	ফেরত 0;
}

/** Set data element [i] in array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @param newval new value for data[i]
 */
স্থির শূন্য yytbl_তথ্য_seti (ধ্রুবক কাঠামো yytbl_তথ্য *tbl, পূর্ণসংখ্যা i,
			     flex_int32_t newval)
{

	নির্বাচন (YYTDFLAGS2BYTES (tbl->td_flags)) {
	ক্ষেত্র আকার (flex_int8_t):
		((flex_int8_t *) (tbl->td_তথ্য))[i] = (flex_int8_t) newval;
		বিরতি;
	ক্ষেত্র আকার (flex_int16_t):
		((flex_int16_t *) (tbl->td_তথ্য))[i] = (flex_int16_t) newval;
		বিরতি;
	ক্ষেত্র আকার (flex_int32_t):
		((flex_int32_t *) (tbl->td_তথ্য))[i] = (flex_int32_t) newval;
		বিরতি;
	পূর্বনির্ধারিত:
		flex_die (_("invalid td_flags detected"));
		বিরতি;
	}
}

/** Calculate the number of bytes  needed to hold the largest
 *  absolute value in this data array.
 *  @param tbl  the data table
 *  @return sizeof(n) where n in {flex_int8_t, flex_int16_t, flex_int32_t}
 */
স্থির size_t min_int_আকার (কাঠামো yytbl_তথ্য *tbl)
{
	flex_int32_t i, যোগ_len;
	flex_int32_t max = 0;

	যোগ_len = yytbl_calc_যোগ_len (tbl);

	জন্য (i = 0; i < যোগ_len; i++) {
		flex_int32_t n;

		n = abs (yytbl_তথ্য_geti (tbl, i));

		যদি (max < n)
			max = n;
	}

	যদি (max <= INT8_MAX)
		ফেরত আকার (flex_int8_t);
	অন্যথা যদি (max <= INT16_MAX)
		ফেরত আকার (flex_int16_t);
	অন্যথা
		ফেরত আকার (flex_int32_t);
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
শূন্য yytbl_তথ্য_compress (কাঠামো yytbl_তথ্য *tbl)
{
	flex_int32_t i, যোগ_len;
	size_t newsz;
	কাঠামো yytbl_তথ্য newtbl;

	yytbl_তথ্য_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_আকার (tbl);


	যদি (newsz == YYTDFLAGS2BYTES (tbl->td_flags))
		/* No change in this table needed. */
		ফেরত;

	যদি (newsz > YYTDFLAGS2BYTES (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		ফেরত;
	}

	যোগ_len = yytbl_calc_যোগ_len (tbl);
	newtbl.td_তথ্য = calloc ((size_t) যোগ_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	জন্য (i = 0; i < যোগ_len; i++) {
		flex_int32_t g;

		g = yytbl_তথ্য_geti (tbl, i);
		yytbl_তথ্য_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	মুক্ত (tbl->td_তথ্য);
	*tbl = newtbl;
}

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
