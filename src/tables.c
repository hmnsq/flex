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
    (((n) == आकार(flex_int8_t))\
        ? YYTD_DATA8\
        :(((n)== आकार(flex_int16_t))\
            ? YYTD_DATA16\
            : YYTD_DATA32))

/** Clear YYTD_DATA* bit flags
 * @return the flag with the YYTD_DATA* bits cleared
 */
#define TFLAGS_CLRDATA(flg) ((flg) & ~(YYTD_DATA8 | YYTD_DATA16 | YYTD_DATA32))

पूर्णांक     yytbl_write32 (संरचना yytbl_writer *wr, flex_uint32_t v);
पूर्णांक     yytbl_write16 (संरचना yytbl_writer *wr, flex_uint16_t v);
पूर्णांक     yytbl_write8 (संरचना yytbl_writer *wr, flex_uint8_t v);
पूर्णांक     yytbl_writen (संरचना yytbl_writer *wr, शून्य *v, पूर्णांक len);
स्थिर flex_int32_t yytbl_data_geti (स्थिरांक संरचना yytbl_data *tbl, पूर्णांक i);
/* XXX Not used
static flex_int32_t yytbl_data_getijk (const struct yytbl_data *tbl, int i,
				  int j, int k);
 */


/** Initialize the table writer.
 *  @param wr an uninitialized writer
 *  @param out the output file
 *  @return 0 on success
 */
पूर्णांक yytbl_writer_init (संरचना yytbl_writer *wr, खाता * out)
{
	wr->out = out;
	wr->total_written = 0;
	परत 0;
}

/** Initialize a table header.
 *  @param th  The uninitialized structure
 *  @param version_str the  version string
 *  @param name the name of this table set
 */
पूर्णांक yytbl_hdr_init (संरचना yytbl_hdr *th, स्थिरांक अक्षर *version_str,
		    स्थिरांक अक्षर *name)
{
	स_रखो (th, 0, आकार (संरचना yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = (flex_uint32_t) (14 + म_माप (version_str) + 1 + म_माप (name) + 1);
	th->th_hsize += (8 - (th->th_hsize % 8)) % 8; // Pad to 64-bit boundary
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_version = xstrdup(version_str);
	th->th_name = xstrdup(name);
	परत 0;
}

/** Allocate and initialize a table data structure.
 *  @param td a pointer to an uninitialized table
 *  @param id  the table identifier
 *  @return 0 on success
 */
पूर्णांक yytbl_data_init (संरचना yytbl_data *td, गणना yytbl_id id)
{

	स_रखो (td, 0, आकार (संरचना yytbl_data));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	परत 0;
}

/** Clean up table and data array.
 *  @param td will be destroyed
 *  @return 0 on success
 */
पूर्णांक yytbl_data_destroy (संरचना yytbl_data *td)
{
	मुक्त(td->td_data);
	td->td_data = 0;
	मुक्त (td);
	परत 0;
}

/** Write enough padding to bring the file pointer to a 64-bit boundary. */
स्थिर पूर्णांक yytbl_write_pad64 (संरचना yytbl_writer *wr)
{
	पूर्णांक bwritten = 0;

	पर्यंत (wr->total_written % (8 * आकार(flex_uint8_t)) > 0) {
		जर (yytbl_write8 (wr, 0) < 0)
			परत -1;
		अन्यथा
			bwritten++;
	}
	परत bwritten;
}

/** write the header.
 *  @param wr the output stream
 *  @param th table header to be written
 *  @return -1 on error, or bytes written on success.
 */
पूर्णांक yytbl_hdr_fwrite (संरचना yytbl_writer *wr, स्थिरांक संरचना yytbl_hdr *th)
{
	पूर्णांक  sz, rv;
	पूर्णांक     bwritten = 0;

	जर (yytbl_write32 (wr, th->th_magic) < 0
	    || yytbl_write32 (wr, th->th_hsize) < 0)
		flex_die (_("th_magic|th_hsize write32 failed"));
	bwritten += 8;

	जर (ख_स्थान_लो (wr->out, &(wr->th_ssize_pos)) != 0)
		flex_die (_("fgetpos failed"));

	जर (yytbl_write32 (wr, th->th_ssize) < 0
	    || yytbl_write16 (wr, th->th_flags) < 0)
		flex_die (_("th_ssize|th_flags write failed"));
	bwritten += 6;

	sz = (पूर्णांक) म_माप (th->th_version) + 1;
	जर ((rv = yytbl_writen (wr, th->th_version, sz)) != sz)
		flex_die (_("th_version written failed"));
	bwritten += rv;

	sz = (पूर्णांक) म_माप (th->th_name) + 1;
	जर ((rv = yytbl_writen (wr, th->th_name, sz)) != sz)
		flex_die (_("th_name written failed"));
	bwritten += rv;

	/* add padding */
	जर ((rv = yytbl_write_pad64 (wr)) < 0)
		flex_die (_("pad64 failed"));
	bwritten += rv;

	/* Sanity check */
	जर (bwritten != (पूर्णांक) th->th_hsize)
		flex_die (_("pad64 failed"));

	परत bwritten;
}


/** Write this table.
 *  @param wr the file writer
 *  @param td table data to be written
 *  @return -1 on error, or bytes written on success.
 */
पूर्णांक yytbl_data_fwrite (संरचना yytbl_writer *wr, संरचना yytbl_data *td)
{
	पूर्णांक  rv;
	flex_int32_t bwritten = 0;
	flex_int32_t i, total_len;
	ख_स्थान_प्रकार  pos;

	जर ((rv = yytbl_write16 (wr, td->td_id)) < 0)
		परत -1;
	bwritten += rv;

	जर ((rv = yytbl_write16 (wr, td->td_flags)) < 0)
		परत -1;
	bwritten += rv;

	जर ((rv = yytbl_write32 (wr, td->td_hilen)) < 0)
		परत -1;
	bwritten += rv;

	जर ((rv = yytbl_write32 (wr, td->td_lolen)) < 0)
		परत -1;
	bwritten += rv;

	total_len = yytbl_calc_total_len (td);
	साठी (i = 0; i < total_len; i++) {
		निवड (YYTDFLAGS2BYTES (td->td_flags)) {
		स्थिती आकार (flex_int8_t):
			rv = yytbl_write8 (wr, (flex_uint8_t) yytbl_data_geti (td, i));
			थांबा;
		स्थिती आकार (flex_int16_t):
			rv = yytbl_write16 (wr, (flex_uint16_t) yytbl_data_geti (td, i));
			थांबा;
		स्थिती आकार (flex_int32_t):
			rv = yytbl_write32 (wr, (flex_uint32_t) yytbl_data_geti (td, i));
			थांबा;
		पूर्वनिर्धारित:
			flex_die (_("invalid td_flags detected"));
		}
		जर (rv < 0) {
			flex_die (_("error while writing tables"));
			परत -1;
		}
		bwritten += rv;
	}

	/* Sanity check */
	जर (bwritten != (12 + total_len * (पूर्णांक) YYTDFLAGS2BYTES (td->td_flags))) {
		flex_die (_("insanity detected"));
		परत -1;
	}

	/* add padding */
	जर ((rv = yytbl_write_pad64 (wr)) < 0) {
		flex_die (_("pad64 failed"));
		परत -1;
	}
	bwritten += rv;

	/* Now go back and update the th_hsize member */
	जर (ख_स्थान_लो (wr->out, &pos) != 0
	    || ख_स्थान_दो (wr->out, &(wr->th_ssize_pos)) != 0
	    || yytbl_write32 (wr, (flex_uint32_t) wr->total_written) < 0
	    || ख_स्थान_दो (wr->out, &pos)) {
		flex_die (_("get|set|fwrite32 failed"));
		परत -1;
	}
	अन्यथा
		/* Don't count the int we just wrote. */
		wr->total_written -= (पूर्णांक) आकार (flex_int32_t);
	परत bwritten;
}

/** Write n bytes.
 *  @param  wr   the table writer
 *  @param  v    data to be written
 *  @param  len  number of bytes
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णांक yytbl_writen (संरचना yytbl_writer *wr, शून्य *v, पूर्णांक len)
{
	पूर्णांक  rv;

	rv = (पूर्णांक) ख_डालो (v, 1, (माप_प्रकार) len, wr->out);
	जर (rv != len)
		परत -1;
	wr->total_written += len;
	परत len;
}

/** Write four bytes in network byte order
 *  @param  wr  the table writer
 *  @param  v    a dword in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णांक yytbl_write32 (संरचना yytbl_writer *wr, flex_uint32_t v)
{
	flex_uint32_t vnet;
	पूर्णांक  bytes, rv;

	vnet = htonl (v);
	bytes = (पूर्णांक) आकार (flex_uint32_t);
	rv = (पूर्णांक) ख_डालो (&vnet, (माप_प्रकार) bytes, 1, wr->out);
	जर (rv != 1)
		परत -1;
	wr->total_written += bytes;
	परत bytes;
}

/** Write two bytes in network byte order.
 *  @param  wr  the table writer
 *  @param  v    a word in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णांक yytbl_write16 (संरचना yytbl_writer *wr, flex_uint16_t v)
{
	flex_uint16_t vnet;
	पूर्णांक  bytes, rv;

	vnet = htons (v);
	bytes = (पूर्णांक) आकार (flex_uint16_t);
	rv = (पूर्णांक) ख_डालो (&vnet, (माप_प्रकार) bytes, 1, wr->out);
	जर (rv != 1)
		परत -1;
	wr->total_written += bytes;
	परत bytes;
}

/** Write a byte.
 *  @param  wr  the table writer
 *  @param  v    the value to be written
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णांक yytbl_write8 (संरचना yytbl_writer *wr, flex_uint8_t v)
{
	पूर्णांक  bytes, rv;

	bytes = (पूर्णांक) आकार (flex_uint8_t);
	rv = (पूर्णांक) ख_डालो (&v, (माप_प्रकार) bytes, 1, wr->out);
	जर (rv != 1)
		परत -1;
	wr->total_written += bytes;
	परत bytes;
}


/* XXX Not Used */
#जर 0
/** Extract data element [i][j] from array data tables. 
 * @param tbl data table
 * @param i index into higher dimension array. i should be zero for one-dimensional arrays.
 * @param j index into lower dimension array.
 * @param k index into struct, must be 0 or 1. Only valid for YYTD_ID_TRANSITION table
 * @return data[i][j + k]
 */
स्थिर flex_int32_t yytbl_data_getijk (स्थिरांक संरचना yytbl_data *tbl, पूर्णांक i,
				  पूर्णांक j, पूर्णांक k)
{
	flex_int32_t lo;

	k %= 2;
	lo = tbl->td_lolen;

	निवड (YYTDFLAGS2BYTES (tbl->td_flags)) {
	स्थिती आकार (flex_int8_t):
		परत ((flex_int8_t *) (tbl->td_data))[(i * lo + j) * (k + 1) +
						   k];
	स्थिती आकार (flex_int16_t):
		परत ((flex_int16_t *) (tbl->td_data))[(i * lo + j) * (k +
								    1) +
						    k];
	स्थिती आकार (flex_int32_t):
		परत ((flex_int32_t *) (tbl->td_data))[(i * lo + j) * (k +
								    1) +
						    k];
	पूर्वनिर्धारित:
		flex_die (_("invalid td_flags detected"));
		थांबा;
	}

	परत 0;
}
#endif /* Not used */

/** Extract data element [i] from array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @return data[i]
 */
स्थिर flex_int32_t yytbl_data_geti (स्थिरांक संरचना yytbl_data *tbl, पूर्णांक i)
{

	निवड (YYTDFLAGS2BYTES (tbl->td_flags)) {
	स्थिती आकार (flex_int8_t):
		परत ((flex_int8_t *) (tbl->td_data))[i];
	स्थिती आकार (flex_int16_t):
		परत ((flex_int16_t *) (tbl->td_data))[i];
	स्थिती आकार (flex_int32_t):
		परत ((flex_int32_t *) (tbl->td_data))[i];
	पूर्वनिर्धारित:
		flex_die (_("invalid td_flags detected"));
		थांबा;
	}
	परत 0;
}

/** Set data element [i] in array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @param newval new value for data[i]
 */
स्थिर शून्य yytbl_data_seti (स्थिरांक संरचना yytbl_data *tbl, पूर्णांक i,
			     flex_int32_t newval)
{

	निवड (YYTDFLAGS2BYTES (tbl->td_flags)) {
	स्थिती आकार (flex_int8_t):
		((flex_int8_t *) (tbl->td_data))[i] = (flex_int8_t) newval;
		थांबा;
	स्थिती आकार (flex_int16_t):
		((flex_int16_t *) (tbl->td_data))[i] = (flex_int16_t) newval;
		थांबा;
	स्थिती आकार (flex_int32_t):
		((flex_int32_t *) (tbl->td_data))[i] = (flex_int32_t) newval;
		थांबा;
	पूर्वनिर्धारित:
		flex_die (_("invalid td_flags detected"));
		थांबा;
	}
}

/** Calculate the number of bytes  needed to hold the largest
 *  absolute value in this data array.
 *  @param tbl  the data table
 *  @return sizeof(n) where n in {flex_int8_t, flex_int16_t, flex_int32_t}
 */
स्थिर माप_प्रकार min_int_size (संरचना yytbl_data *tbl)
{
	flex_int32_t i, total_len;
	flex_int32_t max = 0;

	total_len = yytbl_calc_total_len (tbl);

	साठी (i = 0; i < total_len; i++) {
		flex_int32_t n;

		n = असल (yytbl_data_geti (tbl, i));

		जर (max < n)
			max = n;
	}

	जर (max <= INT8_MAX)
		परत आकार (flex_int8_t);
	अन्यथा जर (max <= INT16_MAX)
		परत आकार (flex_int16_t);
	अन्यथा
		परत आकार (flex_int32_t);
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
	माप_प्रकार newsz;
	संरचना yytbl_data newtbl;

	yytbl_data_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_size (tbl);


	जर (newsz == YYTDFLAGS2BYTES (tbl->td_flags))
		/* No change in this table needed. */
		परत;

	जर (newsz > YYTDFLAGS2BYTES (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		परत;
	}

	total_len = yytbl_calc_total_len (tbl);
	newtbl.td_data = सुस्मृति ((माप_प्रकार) total_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	साठी (i = 0; i < total_len; i++) {
		flex_int32_t g;

		g = yytbl_data_geti (tbl, i);
		yytbl_data_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	मुक्त (tbl->td_data);
	*tbl = newtbl;
}

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
