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


#अन्तर्भाव "flexdef.h"
#अन्तर्भाव "tables.h"

/** Convert size_t to t_flag.
 *  @param n in {1,2,4}
 *  @return YYTD_DATA*. 
 */
#define BYTES2TFLAG(n)\
    (((n) == परिमाण(flex_int8_t))\
        ? YYTD_DATA8\
        :(((n)== परिमाण(flex_int16_t))\
            ? YYTD_DATA16\
            : YYTD_DATA32))

/** Clear YYTD_DATA* bit flags
 * @return the flag with the YYTD_DATA* bits cleared
 */
#define TFLAGS_CLRDATA(flg) ((flg) & ~(YYTD_DATA8 | YYTD_DATA16 | YYTD_DATA32))

पूर्णाङ्क     yytbl_write32 (संरचना yytbl_writer *wr, flex_uint32_t v);
पूर्णाङ्क     yytbl_write16 (संरचना yytbl_writer *wr, flex_uint16_t v);
पूर्णाङ्क     yytbl_write8 (संरचना yytbl_writer *wr, flex_uint8_t v);
पूर्णाङ्क     yytbl_writen (संरचना yytbl_writer *wr, शून्य *v, पूर्णाङ्क len);
स्थिर flex_int32_t yytbl_data_geti (ध्रुव संरचना yytbl_data *tbl, पूर्णाङ्क i);
/* XXX Not used
static flex_int32_t yytbl_data_getijk (const struct yytbl_data *tbl, int i,
				  int j, int k);
 */


/** Initialize the table writer.
 *  @param wr an uninitialized writer
 *  @param out the output file
 *  @return 0 on success
 */
पूर्णाङ्क yytbl_writer_init (संरचना yytbl_writer *wr, FILE * out)
{
	wr->out = out;
	wr->total_written = 0;
	प्रत्यागम 0;
}

/** Initialize a table header.
 *  @param th  The uninitialized structure
 *  @param version_str the  version string
 *  @param name the name of this table set
 */
पूर्णाङ्क yytbl_hdr_init (संरचना yytbl_hdr *th, ध्रुव वर्ण *version_str,
		    ध्रुव वर्ण *name)
{
	memset (th, 0, परिमाण (संरचना yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = (flex_uint32_t) (14 + strlen (version_str) + 1 + strlen (name) + 1);
	th->th_hsize += (8 - (th->th_hsize % 8)) % 8; // Pad to 64-bit boundary
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_version = xstrdup(version_str);
	th->th_name = xstrdup(name);
	प्रत्यागम 0;
}

/** Allocate and initialize a table data structure.
 *  @param td a pointer to an uninitialized table
 *  @param id  the table identifier
 *  @return 0 on success
 */
पूर्णाङ्क yytbl_data_init (संरचना yytbl_data *td, गणना yytbl_id id)
{

	memset (td, 0, परिमाण (संरचना yytbl_data));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	प्रत्यागम 0;
}

/** Clean up table and data array.
 *  @param td will be destroyed
 *  @return 0 on success
 */
पूर्णाङ्क yytbl_data_destroy (संरचना yytbl_data *td)
{
	मुक्त(td->td_data);
	td->td_data = 0;
	मुक्त (td);
	प्रत्यागम 0;
}

/** Write enough padding to bring the file pointer to a 64-bit boundary. */
स्थिर पूर्णाङ्क yytbl_write_pad64 (संरचना yytbl_writer *wr)
{
	पूर्णाङ्क bwritten = 0;

	यावत् (wr->total_written % (8 * परिमाण(flex_uint8_t)) > 0) {
		यदि (yytbl_write8 (wr, 0) < 0)
			प्रत्यागम -1;
		अन्यथा
			bwritten++;
	}
	प्रत्यागम bwritten;
}

/** write the header.
 *  @param wr the output stream
 *  @param th table header to be written
 *  @return -1 on error, or bytes written on success.
 */
पूर्णाङ्क yytbl_hdr_fwrite (संरचना yytbl_writer *wr, ध्रुव संरचना yytbl_hdr *th)
{
	पूर्णाङ्क  sz, rv;
	पूर्णाङ्क     bwritten = 0;

	यदि (yytbl_write32 (wr, th->th_magic) < 0
	    || yytbl_write32 (wr, th->th_hsize) < 0)
		flex_die (_("th_magic|th_hsize write32 failed"));
	bwritten += 8;

	यदि (fgetpos (wr->out, &(wr->th_ssize_pos)) != 0)
		flex_die (_("fgetpos failed"));

	यदि (yytbl_write32 (wr, th->th_ssize) < 0
	    || yytbl_write16 (wr, th->th_flags) < 0)
		flex_die (_("th_ssize|th_flags write failed"));
	bwritten += 6;

	sz = (पूर्णाङ्क) strlen (th->th_version) + 1;
	यदि ((rv = yytbl_writen (wr, th->th_version, sz)) != sz)
		flex_die (_("th_version written failed"));
	bwritten += rv;

	sz = (पूर्णाङ्क) strlen (th->th_name) + 1;
	यदि ((rv = yytbl_writen (wr, th->th_name, sz)) != sz)
		flex_die (_("th_name written failed"));
	bwritten += rv;

	/* add padding */
	यदि ((rv = yytbl_write_pad64 (wr)) < 0)
		flex_die (_("pad64 failed"));
	bwritten += rv;

	/* Sanity check */
	यदि (bwritten != (पूर्णाङ्क) th->th_hsize)
		flex_die (_("pad64 failed"));

	प्रत्यागम bwritten;
}


/** Write this table.
 *  @param wr the file writer
 *  @param td table data to be written
 *  @return -1 on error, or bytes written on success.
 */
पूर्णाङ्क yytbl_data_fwrite (संरचना yytbl_writer *wr, संरचना yytbl_data *td)
{
	पूर्णाङ्क  rv;
	flex_int32_t bwritten = 0;
	flex_int32_t i, total_len;
	fpos_t  pos;

	यदि ((rv = yytbl_write16 (wr, td->td_id)) < 0)
		प्रत्यागम -1;
	bwritten += rv;

	यदि ((rv = yytbl_write16 (wr, td->td_flags)) < 0)
		प्रत्यागम -1;
	bwritten += rv;

	यदि ((rv = yytbl_write32 (wr, td->td_hilen)) < 0)
		प्रत्यागम -1;
	bwritten += rv;

	यदि ((rv = yytbl_write32 (wr, td->td_lolen)) < 0)
		प्रत्यागम -1;
	bwritten += rv;

	total_len = yytbl_calc_total_len (td);
	प्रति (i = 0; i < total_len; i++) {
		विकल्प (YYTDFLAGS2BYTES (td->td_flags)) {
		पक्ष परिमाण (flex_int8_t):
			rv = yytbl_write8 (wr, (flex_uint8_t) yytbl_data_geti (td, i));
			भङ्ग;
		पक्ष परिमाण (flex_int16_t):
			rv = yytbl_write16 (wr, (flex_uint16_t) yytbl_data_geti (td, i));
			भङ्ग;
		पक्ष परिमाण (flex_int32_t):
			rv = yytbl_write32 (wr, (flex_uint32_t) yytbl_data_geti (td, i));
			भङ्ग;
		स्वभाव:
			flex_die (_("invalid td_flags detected"));
		}
		यदि (rv < 0) {
			flex_die (_("error while writing tables"));
			प्रत्यागम -1;
		}
		bwritten += rv;
	}

	/* Sanity check */
	यदि (bwritten != (12 + total_len * (पूर्णाङ्क) YYTDFLAGS2BYTES (td->td_flags))) {
		flex_die (_("insanity detected"));
		प्रत्यागम -1;
	}

	/* add padding */
	यदि ((rv = yytbl_write_pad64 (wr)) < 0) {
		flex_die (_("pad64 failed"));
		प्रत्यागम -1;
	}
	bwritten += rv;

	/* Now go back and update the th_hsize member */
	यदि (fgetpos (wr->out, &pos) != 0
	    || fsetpos (wr->out, &(wr->th_ssize_pos)) != 0
	    || yytbl_write32 (wr, (flex_uint32_t) wr->total_written) < 0
	    || fsetpos (wr->out, &pos)) {
		flex_die (_("get|set|fwrite32 failed"));
		प्रत्यागम -1;
	}
	अन्यथा
		/* Don't count the int we just wrote. */
		wr->total_written -= (पूर्णाङ्क) परिमाण (flex_int32_t);
	प्रत्यागम bwritten;
}

/** Write n bytes.
 *  @param  wr   the table writer
 *  @param  v    data to be written
 *  @param  len  number of bytes
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णाङ्क yytbl_writen (संरचना yytbl_writer *wr, शून्य *v, पूर्णाङ्क len)
{
	पूर्णाङ्क  rv;

	rv = (पूर्णाङ्क) fwrite (v, 1, (size_t) len, wr->out);
	यदि (rv != len)
		प्रत्यागम -1;
	wr->total_written += len;
	प्रत्यागम len;
}

/** Write four bytes in network byte order
 *  @param  wr  the table writer
 *  @param  v    a dword in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णाङ्क yytbl_write32 (संरचना yytbl_writer *wr, flex_uint32_t v)
{
	flex_uint32_t vnet;
	पूर्णाङ्क  bytes, rv;

	vnet = htonl (v);
	bytes = (पूर्णाङ्क) परिमाण (flex_uint32_t);
	rv = (पूर्णाङ्क) fwrite (&vnet, (size_t) bytes, 1, wr->out);
	यदि (rv != 1)
		प्रत्यागम -1;
	wr->total_written += bytes;
	प्रत्यागम bytes;
}

/** Write two bytes in network byte order.
 *  @param  wr  the table writer
 *  @param  v    a word in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णाङ्क yytbl_write16 (संरचना yytbl_writer *wr, flex_uint16_t v)
{
	flex_uint16_t vnet;
	पूर्णाङ्क  bytes, rv;

	vnet = htons (v);
	bytes = (पूर्णाङ्क) परिमाण (flex_uint16_t);
	rv = (पूर्णाङ्क) fwrite (&vnet, (size_t) bytes, 1, wr->out);
	यदि (rv != 1)
		प्रत्यागम -1;
	wr->total_written += bytes;
	प्रत्यागम bytes;
}

/** Write a byte.
 *  @param  wr  the table writer
 *  @param  v    the value to be written
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णाङ्क yytbl_write8 (संरचना yytbl_writer *wr, flex_uint8_t v)
{
	पूर्णाङ्क  bytes, rv;

	bytes = (पूर्णाङ्क) परिमाण (flex_uint8_t);
	rv = (पूर्णाङ्क) fwrite (&v, (size_t) bytes, 1, wr->out);
	यदि (rv != 1)
		प्रत्यागम -1;
	wr->total_written += bytes;
	प्रत्यागम bytes;
}


/* XXX Not Used */
#यदि 0
/** Extract data element [i][j] from array data tables. 
 * @param tbl data table
 * @param i index into higher dimension array. i should be zero for one-dimensional arrays.
 * @param j index into lower dimension array.
 * @param k index into struct, must be 0 or 1. Only valid for YYTD_ID_TRANSITION table
 * @return data[i][j + k]
 */
स्थिर flex_int32_t yytbl_data_getijk (ध्रुव संरचना yytbl_data *tbl, पूर्णाङ्क i,
				  पूर्णाङ्क j, पूर्णाङ्क k)
{
	flex_int32_t lo;

	k %= 2;
	lo = tbl->td_lolen;

	विकल्प (YYTDFLAGS2BYTES (tbl->td_flags)) {
	पक्ष परिमाण (flex_int8_t):
		प्रत्यागम ((flex_int8_t *) (tbl->td_data))[(i * lo + j) * (k + 1) +
						   k];
	पक्ष परिमाण (flex_int16_t):
		प्रत्यागम ((flex_int16_t *) (tbl->td_data))[(i * lo + j) * (k +
								    1) +
						    k];
	पक्ष परिमाण (flex_int32_t):
		प्रत्यागम ((flex_int32_t *) (tbl->td_data))[(i * lo + j) * (k +
								    1) +
						    k];
	स्वभाव:
		flex_die (_("invalid td_flags detected"));
		भङ्ग;
	}

	प्रत्यागम 0;
}
#endif /* Not used */

/** Extract data element [i] from array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @return data[i]
 */
स्थिर flex_int32_t yytbl_data_geti (ध्रुव संरचना yytbl_data *tbl, पूर्णाङ्क i)
{

	विकल्प (YYTDFLAGS2BYTES (tbl->td_flags)) {
	पक्ष परिमाण (flex_int8_t):
		प्रत्यागम ((flex_int8_t *) (tbl->td_data))[i];
	पक्ष परिमाण (flex_int16_t):
		प्रत्यागम ((flex_int16_t *) (tbl->td_data))[i];
	पक्ष परिमाण (flex_int32_t):
		प्रत्यागम ((flex_int32_t *) (tbl->td_data))[i];
	स्वभाव:
		flex_die (_("invalid td_flags detected"));
		भङ्ग;
	}
	प्रत्यागम 0;
}

/** Set data element [i] in array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @param newval new value for data[i]
 */
स्थिर शून्य yytbl_data_seti (ध्रुव संरचना yytbl_data *tbl, पूर्णाङ्क i,
			     flex_int32_t newval)
{

	विकल्प (YYTDFLAGS2BYTES (tbl->td_flags)) {
	पक्ष परिमाण (flex_int8_t):
		((flex_int8_t *) (tbl->td_data))[i] = (flex_int8_t) newval;
		भङ्ग;
	पक्ष परिमाण (flex_int16_t):
		((flex_int16_t *) (tbl->td_data))[i] = (flex_int16_t) newval;
		भङ्ग;
	पक्ष परिमाण (flex_int32_t):
		((flex_int32_t *) (tbl->td_data))[i] = (flex_int32_t) newval;
		भङ्ग;
	स्वभाव:
		flex_die (_("invalid td_flags detected"));
		भङ्ग;
	}
}

/** Calculate the number of bytes  needed to hold the largest
 *  absolute value in this data array.
 *  @param tbl  the data table
 *  @return sizeof(n) where n in {flex_int8_t, flex_int16_t, flex_int32_t}
 */
स्थिर size_t min_int_size (संरचना yytbl_data *tbl)
{
	flex_int32_t i, total_len;
	flex_int32_t max = 0;

	total_len = yytbl_calc_total_len (tbl);

	प्रति (i = 0; i < total_len; i++) {
		flex_int32_t n;

		n = abs (yytbl_data_geti (tbl, i));

		यदि (max < n)
			max = n;
	}

	यदि (max <= INT8_MAX)
		प्रत्यागम परिमाण (flex_int8_t);
	अन्यथा यदि (max <= INT16_MAX)
		प्रत्यागम परिमाण (flex_int16_t);
	अन्यथा
		प्रत्यागम परिमाण (flex_int32_t);
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
शून्य yytbl_data_compress (संरचना yytbl_data *tbl)
{
	flex_int32_t i, total_len;
	size_t newsz;
	संरचना yytbl_data newtbl;

	yytbl_data_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_size (tbl);


	यदि (newsz == YYTDFLAGS2BYTES (tbl->td_flags))
		/* No change in this table needed. */
		प्रत्यागम;

	यदि (newsz > YYTDFLAGS2BYTES (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		प्रत्यागम;
	}

	total_len = yytbl_calc_total_len (tbl);
	newtbl.td_data = calloc ((size_t) total_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	प्रति (i = 0; i < total_len; i++) {
		flex_int32_t g;

		g = yytbl_data_geti (tbl, i);
		yytbl_data_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	मुक्त (tbl->td_data);
	*tbl = newtbl;
}

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
