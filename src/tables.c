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


#ಅನ್ತರ್ಭಾವ "flexdef.h"
#ಅನ್ತರ್ಭಾವ "tables.h"

/** Convert size_t to t_flag.
 *  @param n in {1,2,4}
 *  @return YYTD_DATA*. 
 */
#define BYTES2TFLAG(n)\
    (((n) == ಪರಿಮಾಣ(flex_int8_t))\
        ? YYTD_DATA8\
        :(((n)== ಪರಿಮಾಣ(flex_int16_t))\
            ? YYTD_DATA16\
            : YYTD_DATA32))

/** Clear YYTD_DATA* bit flags
 * @return the flag with the YYTD_DATA* bits cleared
 */
#define TFLAGS_CLRDATA(flg) ((flg) & ~(YYTD_DATA8 | YYTD_DATA16 | YYTD_DATA32))

ಪೂರ್ಣಾಙ್ಕ     yytbl_write32 (ಸಂರಚನಾ yytbl_writer *wr, flex_uint32_t v);
ಪೂರ್ಣಾಙ್ಕ     yytbl_write16 (ಸಂರಚನಾ yytbl_writer *wr, flex_uint16_t v);
ಪೂರ್ಣಾಙ್ಕ     yytbl_write8 (ಸಂರಚನಾ yytbl_writer *wr, flex_uint8_t v);
ಪೂರ್ಣಾಙ್ಕ     yytbl_writen (ಸಂರಚನಾ yytbl_writer *wr, ಶೂನ್ಯ *v, ಪೂರ್ಣಾಙ್ಕ len);
ಸ್ಥಿರ flex_int32_t yytbl_data_geti (ಧ್ರುವ ಸಂರಚನಾ yytbl_data *tbl, ಪೂರ್ಣಾಙ್ಕ i);
/* XXX Not used
static flex_int32_t yytbl_data_getijk (const struct yytbl_data *tbl, int i,
				  int j, int k);
 */


/** Initialize the table writer.
 *  @param wr an uninitialized writer
 *  @param out the output file
 *  @return 0 on success
 */
ಪೂರ್ಣಾಙ್ಕ yytbl_writer_init (ಸಂರಚನಾ yytbl_writer *wr, FILE * out)
{
	wr->out = out;
	wr->total_written = 0;
	ಪ್ರತ್ಯಾಗಮ 0;
}

/** Initialize a table header.
 *  @param th  The uninitialized structure
 *  @param version_str the  version string
 *  @param name the name of this table set
 */
ಪೂರ್ಣಾಙ್ಕ yytbl_hdr_init (ಸಂರಚನಾ yytbl_hdr *th, ಧ್ರುವ ವರ್ಣ *version_str,
		    ಧ್ರುವ ವರ್ಣ *name)
{
	memset (th, 0, ಪರಿಮಾಣ (ಸಂರಚನಾ yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = (flex_uint32_t) (14 + strlen (version_str) + 1 + strlen (name) + 1);
	th->th_hsize += (8 - (th->th_hsize % 8)) % 8; // Pad to 64-bit boundary
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_version = xstrdup(version_str);
	th->th_name = xstrdup(name);
	ಪ್ರತ್ಯಾಗಮ 0;
}

/** Allocate and initialize a table data structure.
 *  @param td a pointer to an uninitialized table
 *  @param id  the table identifier
 *  @return 0 on success
 */
ಪೂರ್ಣಾಙ್ಕ yytbl_data_init (ಸಂರಚನಾ yytbl_data *td, ಗಣನಾ yytbl_id id)
{

	memset (td, 0, ಪರಿಮಾಣ (ಸಂರಚನಾ yytbl_data));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	ಪ್ರತ್ಯಾಗಮ 0;
}

/** Clean up table and data array.
 *  @param td will be destroyed
 *  @return 0 on success
 */
ಪೂರ್ಣಾಙ್ಕ yytbl_data_destroy (ಸಂರಚನಾ yytbl_data *td)
{
	ಮುಕ್ತ(td->td_data);
	td->td_data = 0;
	ಮುಕ್ತ (td);
	ಪ್ರತ್ಯಾಗಮ 0;
}

/** Write enough padding to bring the file pointer to a 64-bit boundary. */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ yytbl_write_pad64 (ಸಂರಚನಾ yytbl_writer *wr)
{
	ಪೂರ್ಣಾಙ್ಕ bwritten = 0;

	ಯಾವತ್ (wr->total_written % (8 * ಪರಿಮಾಣ(flex_uint8_t)) > 0) {
		ಯದಿ (yytbl_write8 (wr, 0) < 0)
			ಪ್ರತ್ಯಾಗಮ -1;
		ಅನ್ಯಥಾ
			bwritten++;
	}
	ಪ್ರತ್ಯಾಗಮ bwritten;
}

/** write the header.
 *  @param wr the output stream
 *  @param th table header to be written
 *  @return -1 on error, or bytes written on success.
 */
ಪೂರ್ಣಾಙ್ಕ yytbl_hdr_fwrite (ಸಂರಚನಾ yytbl_writer *wr, ಧ್ರುವ ಸಂರಚನಾ yytbl_hdr *th)
{
	ಪೂರ್ಣಾಙ್ಕ  sz, rv;
	ಪೂರ್ಣಾಙ್ಕ     bwritten = 0;

	ಯದಿ (yytbl_write32 (wr, th->th_magic) < 0
	    || yytbl_write32 (wr, th->th_hsize) < 0)
		flex_die (_("th_magic|th_hsize write32 failed"));
	bwritten += 8;

	ಯದಿ (fgetpos (wr->out, &(wr->th_ssize_pos)) != 0)
		flex_die (_("fgetpos failed"));

	ಯದಿ (yytbl_write32 (wr, th->th_ssize) < 0
	    || yytbl_write16 (wr, th->th_flags) < 0)
		flex_die (_("th_ssize|th_flags write failed"));
	bwritten += 6;

	sz = (ಪೂರ್ಣಾಙ್ಕ) strlen (th->th_version) + 1;
	ಯದಿ ((rv = yytbl_writen (wr, th->th_version, sz)) != sz)
		flex_die (_("th_version written failed"));
	bwritten += rv;

	sz = (ಪೂರ್ಣಾಙ್ಕ) strlen (th->th_name) + 1;
	ಯದಿ ((rv = yytbl_writen (wr, th->th_name, sz)) != sz)
		flex_die (_("th_name written failed"));
	bwritten += rv;

	/* add padding */
	ಯದಿ ((rv = yytbl_write_pad64 (wr)) < 0)
		flex_die (_("pad64 failed"));
	bwritten += rv;

	/* Sanity check */
	ಯದಿ (bwritten != (ಪೂರ್ಣಾಙ್ಕ) th->th_hsize)
		flex_die (_("pad64 failed"));

	ಪ್ರತ್ಯಾಗಮ bwritten;
}


/** Write this table.
 *  @param wr the file writer
 *  @param td table data to be written
 *  @return -1 on error, or bytes written on success.
 */
ಪೂರ್ಣಾಙ್ಕ yytbl_data_fwrite (ಸಂರಚನಾ yytbl_writer *wr, ಸಂರಚನಾ yytbl_data *td)
{
	ಪೂರ್ಣಾಙ್ಕ  rv;
	flex_int32_t bwritten = 0;
	flex_int32_t i, total_len;
	fpos_t  pos;

	ಯದಿ ((rv = yytbl_write16 (wr, td->td_id)) < 0)
		ಪ್ರತ್ಯಾಗಮ -1;
	bwritten += rv;

	ಯದಿ ((rv = yytbl_write16 (wr, td->td_flags)) < 0)
		ಪ್ರತ್ಯಾಗಮ -1;
	bwritten += rv;

	ಯದಿ ((rv = yytbl_write32 (wr, td->td_hilen)) < 0)
		ಪ್ರತ್ಯಾಗಮ -1;
	bwritten += rv;

	ಯದಿ ((rv = yytbl_write32 (wr, td->td_lolen)) < 0)
		ಪ್ರತ್ಯಾಗಮ -1;
	bwritten += rv;

	total_len = yytbl_calc_total_len (td);
	ಪ್ರತಿ (i = 0; i < total_len; i++) {
		ವಿಕಲ್ಪ (YYTDFLAGS2BYTES (td->td_flags)) {
		ಪಕ್ಷ ಪರಿಮಾಣ (flex_int8_t):
			rv = yytbl_write8 (wr, (flex_uint8_t) yytbl_data_geti (td, i));
			ಭಙ್ಗ;
		ಪಕ್ಷ ಪರಿಮಾಣ (flex_int16_t):
			rv = yytbl_write16 (wr, (flex_uint16_t) yytbl_data_geti (td, i));
			ಭಙ್ಗ;
		ಪಕ್ಷ ಪರಿಮಾಣ (flex_int32_t):
			rv = yytbl_write32 (wr, (flex_uint32_t) yytbl_data_geti (td, i));
			ಭಙ್ಗ;
		ಸ್ವಭಾವ:
			flex_die (_("invalid td_flags detected"));
		}
		ಯದಿ (rv < 0) {
			flex_die (_("error while writing tables"));
			ಪ್ರತ್ಯಾಗಮ -1;
		}
		bwritten += rv;
	}

	/* Sanity check */
	ಯದಿ (bwritten != (12 + total_len * (ಪೂರ್ಣಾಙ್ಕ) YYTDFLAGS2BYTES (td->td_flags))) {
		flex_die (_("insanity detected"));
		ಪ್ರತ್ಯಾಗಮ -1;
	}

	/* add padding */
	ಯದಿ ((rv = yytbl_write_pad64 (wr)) < 0) {
		flex_die (_("pad64 failed"));
		ಪ್ರತ್ಯಾಗಮ -1;
	}
	bwritten += rv;

	/* Now go back and update the th_hsize member */
	ಯದಿ (fgetpos (wr->out, &pos) != 0
	    || fsetpos (wr->out, &(wr->th_ssize_pos)) != 0
	    || yytbl_write32 (wr, (flex_uint32_t) wr->total_written) < 0
	    || fsetpos (wr->out, &pos)) {
		flex_die (_("get|set|fwrite32 failed"));
		ಪ್ರತ್ಯಾಗಮ -1;
	}
	ಅನ್ಯಥಾ
		/* Don't count the int we just wrote. */
		wr->total_written -= (ಪೂರ್ಣಾಙ್ಕ) ಪರಿಮಾಣ (flex_int32_t);
	ಪ್ರತ್ಯಾಗಮ bwritten;
}

/** Write n bytes.
 *  @param  wr   the table writer
 *  @param  v    data to be written
 *  @param  len  number of bytes
 *  @return  -1 on error. number of bytes written on success.
 */
ಪೂರ್ಣಾಙ್ಕ yytbl_writen (ಸಂರಚನಾ yytbl_writer *wr, ಶೂನ್ಯ *v, ಪೂರ್ಣಾಙ್ಕ len)
{
	ಪೂರ್ಣಾಙ್ಕ  rv;

	rv = (ಪೂರ್ಣಾಙ್ಕ) fwrite (v, 1, (size_t) len, wr->out);
	ಯದಿ (rv != len)
		ಪ್ರತ್ಯಾಗಮ -1;
	wr->total_written += len;
	ಪ್ರತ್ಯಾಗಮ len;
}

/** Write four bytes in network byte order
 *  @param  wr  the table writer
 *  @param  v    a dword in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
ಪೂರ್ಣಾಙ್ಕ yytbl_write32 (ಸಂರಚನಾ yytbl_writer *wr, flex_uint32_t v)
{
	flex_uint32_t vnet;
	ಪೂರ್ಣಾಙ್ಕ  bytes, rv;

	vnet = htonl (v);
	bytes = (ಪೂರ್ಣಾಙ್ಕ) ಪರಿಮಾಣ (flex_uint32_t);
	rv = (ಪೂರ್ಣಾಙ್ಕ) fwrite (&vnet, (size_t) bytes, 1, wr->out);
	ಯದಿ (rv != 1)
		ಪ್ರತ್ಯಾಗಮ -1;
	wr->total_written += bytes;
	ಪ್ರತ್ಯಾಗಮ bytes;
}

/** Write two bytes in network byte order.
 *  @param  wr  the table writer
 *  @param  v    a word in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
ಪೂರ್ಣಾಙ್ಕ yytbl_write16 (ಸಂರಚನಾ yytbl_writer *wr, flex_uint16_t v)
{
	flex_uint16_t vnet;
	ಪೂರ್ಣಾಙ್ಕ  bytes, rv;

	vnet = htons (v);
	bytes = (ಪೂರ್ಣಾಙ್ಕ) ಪರಿಮಾಣ (flex_uint16_t);
	rv = (ಪೂರ್ಣಾಙ್ಕ) fwrite (&vnet, (size_t) bytes, 1, wr->out);
	ಯದಿ (rv != 1)
		ಪ್ರತ್ಯಾಗಮ -1;
	wr->total_written += bytes;
	ಪ್ರತ್ಯಾಗಮ bytes;
}

/** Write a byte.
 *  @param  wr  the table writer
 *  @param  v    the value to be written
 *  @return  -1 on error. number of bytes written on success.
 */
ಪೂರ್ಣಾಙ್ಕ yytbl_write8 (ಸಂರಚನಾ yytbl_writer *wr, flex_uint8_t v)
{
	ಪೂರ್ಣಾಙ್ಕ  bytes, rv;

	bytes = (ಪೂರ್ಣಾಙ್ಕ) ಪರಿಮಾಣ (flex_uint8_t);
	rv = (ಪೂರ್ಣಾಙ್ಕ) fwrite (&v, (size_t) bytes, 1, wr->out);
	ಯದಿ (rv != 1)
		ಪ್ರತ್ಯಾಗಮ -1;
	wr->total_written += bytes;
	ಪ್ರತ್ಯಾಗಮ bytes;
}


/* XXX Not Used */
#ಯದಿ 0
/** Extract data element [i][j] from array data tables. 
 * @param tbl data table
 * @param i index into higher dimension array. i should be zero for one-dimensional arrays.
 * @param j index into lower dimension array.
 * @param k index into struct, must be 0 or 1. Only valid for YYTD_ID_TRANSITION table
 * @return data[i][j + k]
 */
ಸ್ಥಿರ flex_int32_t yytbl_data_getijk (ಧ್ರುವ ಸಂರಚನಾ yytbl_data *tbl, ಪೂರ್ಣಾಙ್ಕ i,
				  ಪೂರ್ಣಾಙ್ಕ j, ಪೂರ್ಣಾಙ್ಕ k)
{
	flex_int32_t lo;

	k %= 2;
	lo = tbl->td_lolen;

	ವಿಕಲ್ಪ (YYTDFLAGS2BYTES (tbl->td_flags)) {
	ಪಕ್ಷ ಪರಿಮಾಣ (flex_int8_t):
		ಪ್ರತ್ಯಾಗಮ ((flex_int8_t *) (tbl->td_data))[(i * lo + j) * (k + 1) +
						   k];
	ಪಕ್ಷ ಪರಿಮಾಣ (flex_int16_t):
		ಪ್ರತ್ಯಾಗಮ ((flex_int16_t *) (tbl->td_data))[(i * lo + j) * (k +
								    1) +
						    k];
	ಪಕ್ಷ ಪರಿಮಾಣ (flex_int32_t):
		ಪ್ರತ್ಯಾಗಮ ((flex_int32_t *) (tbl->td_data))[(i * lo + j) * (k +
								    1) +
						    k];
	ಸ್ವಭಾವ:
		flex_die (_("invalid td_flags detected"));
		ಭಙ್ಗ;
	}

	ಪ್ರತ್ಯಾಗಮ 0;
}
#endif /* Not used */

/** Extract data element [i] from array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @return data[i]
 */
ಸ್ಥಿರ flex_int32_t yytbl_data_geti (ಧ್ರುವ ಸಂರಚನಾ yytbl_data *tbl, ಪೂರ್ಣಾಙ್ಕ i)
{

	ವಿಕಲ್ಪ (YYTDFLAGS2BYTES (tbl->td_flags)) {
	ಪಕ್ಷ ಪರಿಮಾಣ (flex_int8_t):
		ಪ್ರತ್ಯಾಗಮ ((flex_int8_t *) (tbl->td_data))[i];
	ಪಕ್ಷ ಪರಿಮಾಣ (flex_int16_t):
		ಪ್ರತ್ಯಾಗಮ ((flex_int16_t *) (tbl->td_data))[i];
	ಪಕ್ಷ ಪರಿಮಾಣ (flex_int32_t):
		ಪ್ರತ್ಯಾಗಮ ((flex_int32_t *) (tbl->td_data))[i];
	ಸ್ವಭಾವ:
		flex_die (_("invalid td_flags detected"));
		ಭಙ್ಗ;
	}
	ಪ್ರತ್ಯಾಗಮ 0;
}

/** Set data element [i] in array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @param newval new value for data[i]
 */
ಸ್ಥಿರ ಶೂನ್ಯ yytbl_data_seti (ಧ್ರುವ ಸಂರಚನಾ yytbl_data *tbl, ಪೂರ್ಣಾಙ್ಕ i,
			     flex_int32_t newval)
{

	ವಿಕಲ್ಪ (YYTDFLAGS2BYTES (tbl->td_flags)) {
	ಪಕ್ಷ ಪರಿಮಾಣ (flex_int8_t):
		((flex_int8_t *) (tbl->td_data))[i] = (flex_int8_t) newval;
		ಭಙ್ಗ;
	ಪಕ್ಷ ಪರಿಮಾಣ (flex_int16_t):
		((flex_int16_t *) (tbl->td_data))[i] = (flex_int16_t) newval;
		ಭಙ್ಗ;
	ಪಕ್ಷ ಪರಿಮಾಣ (flex_int32_t):
		((flex_int32_t *) (tbl->td_data))[i] = (flex_int32_t) newval;
		ಭಙ್ಗ;
	ಸ್ವಭಾವ:
		flex_die (_("invalid td_flags detected"));
		ಭಙ್ಗ;
	}
}

/** Calculate the number of bytes  needed to hold the largest
 *  absolute value in this data array.
 *  @param tbl  the data table
 *  @return sizeof(n) where n in {flex_int8_t, flex_int16_t, flex_int32_t}
 */
ಸ್ಥಿರ size_t min_int_size (ಸಂರಚನಾ yytbl_data *tbl)
{
	flex_int32_t i, total_len;
	flex_int32_t max = 0;

	total_len = yytbl_calc_total_len (tbl);

	ಪ್ರತಿ (i = 0; i < total_len; i++) {
		flex_int32_t n;

		n = abs (yytbl_data_geti (tbl, i));

		ಯದಿ (max < n)
			max = n;
	}

	ಯದಿ (max <= INT8_MAX)
		ಪ್ರತ್ಯಾಗಮ ಪರಿಮಾಣ (flex_int8_t);
	ಅನ್ಯಥಾ ಯದಿ (max <= INT16_MAX)
		ಪ್ರತ್ಯಾಗಮ ಪರಿಮಾಣ (flex_int16_t);
	ಅನ್ಯಥಾ
		ಪ್ರತ್ಯಾಗಮ ಪರಿಮಾಣ (flex_int32_t);
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
ಶೂನ್ಯ yytbl_data_compress (ಸಂರಚನಾ yytbl_data *tbl)
{
	flex_int32_t i, total_len;
	size_t newsz;
	ಸಂರಚನಾ yytbl_data newtbl;

	yytbl_data_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_size (tbl);


	ಯದಿ (newsz == YYTDFLAGS2BYTES (tbl->td_flags))
		/* No change in this table needed. */
		ಪ್ರತ್ಯಾಗಮ;

	ಯದಿ (newsz > YYTDFLAGS2BYTES (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		ಪ್ರತ್ಯಾಗಮ;
	}

	total_len = yytbl_calc_total_len (tbl);
	newtbl.td_data = calloc ((size_t) total_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	ಪ್ರತಿ (i = 0; i < total_len; i++) {
		flex_int32_t g;

		g = yytbl_data_geti (tbl, i);
		yytbl_data_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	ಮುಕ್ತ (tbl->td_data);
	*tbl = newtbl;
}

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
