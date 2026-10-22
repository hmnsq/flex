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


#समावेश "flexdef.h"
#समावेश "tables.h"

/** Convert size_t to t_flag.
 *  @param n in {1,2,4}
 *  @return YYTD_DATA*. 
 */
#घोषणा BYTES2TFLAG(n)\
    (((n) == माप(flex_int8_t))\
        ? YYTD_DATA8\
        :(((n)== माप(flex_int16_t))\
            ? YYTD_DATA16\
            : YYTD_DATA32))

/** Clear YYTD_DATA* bit flags
 * @return the flag with the YYTD_DATA* bits cleared
 */
#घोषणा TFLAGS_CLRDATA(flg) ((flg) & ~(YYTD_DATA8 | YYTD_DATA16 | YYTD_DATA32))

पूर्णांक     yytbl_write32 (काष्ठा yytbl_writer *wr, flex_uint32_t v);
पूर्णांक     yytbl_write16 (काष्ठा yytbl_writer *wr, flex_uint16_t v);
पूर्णांक     yytbl_write8 (काष्ठा yytbl_writer *wr, flex_uint8_t v);
पूर्णांक     yytbl_writen (काष्ठा yytbl_writer *wr, व्योम *v, पूर्णांक len);
अटल flex_int32_t yytbl_तथ्य_geti (स्थिर काष्ठा yytbl_तथ्य *tbl, पूर्णांक i);
/* XXX Not used
static flex_int32_t yytbl_data_getijk (const struct yytbl_data *tbl, int i,
				  int j, int k);
 */


/** Initialize the table writer.
 *  @param wr an uninitialized writer
 *  @param out the output file
 *  @return 0 on success
 */
पूर्णांक yytbl_writer_init (काष्ठा yytbl_writer *wr, खाता * out)
{
	wr->out = out;
	wr->योग_written = 0;
	वापस 0;
}

/** Initialize a table header.
 *  @param th  The uninitialized structure
 *  @param version_str the  version string
 *  @param name the name of this table set
 */
पूर्णांक yytbl_hdr_init (काष्ठा yytbl_hdr *th, स्थिर अक्षर *version_str,
		    स्थिर अक्षर *name)
{
	स_रखो (th, 0, माप (काष्ठा yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = (flex_uint32_t) (14 + म_माप (version_str) + 1 + म_माप (name) + 1);
	th->th_hsize += (8 - (th->th_hsize % 8)) % 8; // Pad to 64-bit boundary
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_version = xstrdup(version_str);
	th->th_name = xstrdup(name);
	वापस 0;
}

/** Allocate and initialize a table data structure.
 *  @param td a pointer to an uninitialized table
 *  @param id  the table identifier
 *  @return 0 on success
 */
पूर्णांक yytbl_तथ्य_init (काष्ठा yytbl_तथ्य *td, क्रमागत yytbl_id id)
{

	स_रखो (td, 0, माप (काष्ठा yytbl_तथ्य));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	वापस 0;
}

/** Clean up table and data array.
 *  @param td will be destroyed
 *  @return 0 on success
 */
पूर्णांक yytbl_तथ्य_destroy (काष्ठा yytbl_तथ्य *td)
{
	मुक्त(td->td_तथ्य);
	td->td_तथ्य = 0;
	मुक्त (td);
	वापस 0;
}

/** Write enough padding to bring the file pointer to a 64-bit boundary. */
अटल पूर्णांक yytbl_write_pad64 (काष्ठा yytbl_writer *wr)
{
	पूर्णांक bwritten = 0;

	जबतक (wr->योग_written % (8 * माप(flex_uint8_t)) > 0) {
		अगर (yytbl_write8 (wr, 0) < 0)
			वापस -1;
		अन्यथा
			bwritten++;
	}
	वापस bwritten;
}

/** write the header.
 *  @param wr the output stream
 *  @param th table header to be written
 *  @return -1 on error, or bytes written on success.
 */
पूर्णांक yytbl_hdr_fwrite (काष्ठा yytbl_writer *wr, स्थिर काष्ठा yytbl_hdr *th)
{
	पूर्णांक  sz, rv;
	पूर्णांक     bwritten = 0;

	अगर (yytbl_write32 (wr, th->th_magic) < 0
	    || yytbl_write32 (wr, th->th_hsize) < 0)
		flex_die (_("th_magic|th_hsize write32 failed"));
	bwritten += 8;

	अगर (ख_स्थान_लो (wr->out, &(wr->th_ssize_pos)) != 0)
		flex_die (_("fgetpos failed"));

	अगर (yytbl_write32 (wr, th->th_ssize) < 0
	    || yytbl_write16 (wr, th->th_flags) < 0)
		flex_die (_("th_ssize|th_flags write failed"));
	bwritten += 6;

	sz = (पूर्णांक) म_माप (th->th_version) + 1;
	अगर ((rv = yytbl_writen (wr, th->th_version, sz)) != sz)
		flex_die (_("th_version written failed"));
	bwritten += rv;

	sz = (पूर्णांक) म_माप (th->th_name) + 1;
	अगर ((rv = yytbl_writen (wr, th->th_name, sz)) != sz)
		flex_die (_("th_name written failed"));
	bwritten += rv;

	/* add padding */
	अगर ((rv = yytbl_write_pad64 (wr)) < 0)
		flex_die (_("pad64 failed"));
	bwritten += rv;

	/* Sanity check */
	अगर (bwritten != (पूर्णांक) th->th_hsize)
		flex_die (_("pad64 failed"));

	वापस bwritten;
}


/** Write this table.
 *  @param wr the file writer
 *  @param td table data to be written
 *  @return -1 on error, or bytes written on success.
 */
पूर्णांक yytbl_तथ्य_fwrite (काष्ठा yytbl_writer *wr, काष्ठा yytbl_तथ्य *td)
{
	पूर्णांक  rv;
	flex_int32_t bwritten = 0;
	flex_int32_t i, योग_len;
	ख_स्थान_प्रकार  pos;

	अगर ((rv = yytbl_write16 (wr, td->td_id)) < 0)
		वापस -1;
	bwritten += rv;

	अगर ((rv = yytbl_write16 (wr, td->td_flags)) < 0)
		वापस -1;
	bwritten += rv;

	अगर ((rv = yytbl_write32 (wr, td->td_hilen)) < 0)
		वापस -1;
	bwritten += rv;

	अगर ((rv = yytbl_write32 (wr, td->td_lolen)) < 0)
		वापस -1;
	bwritten += rv;

	योग_len = yytbl_calc_योग_len (td);
	क्रम (i = 0; i < योग_len; i++) {
		चयन (YYTDFLAGS2BYTES (td->td_flags)) {
		हाल माप (flex_int8_t):
			rv = yytbl_write8 (wr, (flex_uint8_t) yytbl_तथ्य_geti (td, i));
			अवरोध;
		हाल माप (flex_int16_t):
			rv = yytbl_write16 (wr, (flex_uint16_t) yytbl_तथ्य_geti (td, i));
			अवरोध;
		हाल माप (flex_int32_t):
			rv = yytbl_write32 (wr, (flex_uint32_t) yytbl_तथ्य_geti (td, i));
			अवरोध;
		शेष:
			flex_die (_("invalid td_flags detected"));
		}
		अगर (rv < 0) {
			flex_die (_("error while writing tables"));
			वापस -1;
		}
		bwritten += rv;
	}

	/* Sanity check */
	अगर (bwritten != (12 + योग_len * (पूर्णांक) YYTDFLAGS2BYTES (td->td_flags))) {
		flex_die (_("insanity detected"));
		वापस -1;
	}

	/* add padding */
	अगर ((rv = yytbl_write_pad64 (wr)) < 0) {
		flex_die (_("pad64 failed"));
		वापस -1;
	}
	bwritten += rv;

	/* Now go back and update the th_hsize member */
	अगर (ख_स्थान_लो (wr->out, &pos) != 0
	    || ख_स्थान_दो (wr->out, &(wr->th_ssize_pos)) != 0
	    || yytbl_write32 (wr, (flex_uint32_t) wr->योग_written) < 0
	    || ख_स्थान_दो (wr->out, &pos)) {
		flex_die (_("get|set|fwrite32 failed"));
		वापस -1;
	}
	अन्यथा
		/* Don't count the int we just wrote. */
		wr->योग_written -= (पूर्णांक) माप (flex_int32_t);
	वापस bwritten;
}

/** Write n bytes.
 *  @param  wr   the table writer
 *  @param  v    data to be written
 *  @param  len  number of bytes
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णांक yytbl_writen (काष्ठा yytbl_writer *wr, व्योम *v, पूर्णांक len)
{
	पूर्णांक  rv;

	rv = (पूर्णांक) ख_डालो (v, 1, (माप_प्रकार) len, wr->out);
	अगर (rv != len)
		वापस -1;
	wr->योग_written += len;
	वापस len;
}

/** Write four bytes in network byte order
 *  @param  wr  the table writer
 *  @param  v    a dword in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णांक yytbl_write32 (काष्ठा yytbl_writer *wr, flex_uint32_t v)
{
	flex_uint32_t vnet;
	पूर्णांक  bytes, rv;

	vnet = htonl (v);
	bytes = (पूर्णांक) माप (flex_uint32_t);
	rv = (पूर्णांक) ख_डालो (&vnet, (माप_प्रकार) bytes, 1, wr->out);
	अगर (rv != 1)
		वापस -1;
	wr->योग_written += bytes;
	वापस bytes;
}

/** Write two bytes in network byte order.
 *  @param  wr  the table writer
 *  @param  v    a word in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णांक yytbl_write16 (काष्ठा yytbl_writer *wr, flex_uint16_t v)
{
	flex_uint16_t vnet;
	पूर्णांक  bytes, rv;

	vnet = htons (v);
	bytes = (पूर्णांक) माप (flex_uint16_t);
	rv = (पूर्णांक) ख_डालो (&vnet, (माप_प्रकार) bytes, 1, wr->out);
	अगर (rv != 1)
		वापस -1;
	wr->योग_written += bytes;
	वापस bytes;
}

/** Write a byte.
 *  @param  wr  the table writer
 *  @param  v    the value to be written
 *  @return  -1 on error. number of bytes written on success.
 */
पूर्णांक yytbl_write8 (काष्ठा yytbl_writer *wr, flex_uint8_t v)
{
	पूर्णांक  bytes, rv;

	bytes = (पूर्णांक) माप (flex_uint8_t);
	rv = (पूर्णांक) ख_डालो (&v, (माप_प्रकार) bytes, 1, wr->out);
	अगर (rv != 1)
		वापस -1;
	wr->योग_written += bytes;
	वापस bytes;
}


/* XXX Not Used */
#अगर 0
/** Extract data element [i][j] from array data tables. 
 * @param tbl data table
 * @param i index into higher dimension array. i should be zero for one-dimensional arrays.
 * @param j index into lower dimension array.
 * @param k index into struct, must be 0 or 1. Only valid for YYTD_ID_TRANSITION table
 * @return data[i][j + k]
 */
अटल flex_int32_t yytbl_तथ्य_getijk (स्थिर काष्ठा yytbl_तथ्य *tbl, पूर्णांक i,
				  पूर्णांक j, पूर्णांक k)
{
	flex_int32_t lo;

	k %= 2;
	lo = tbl->td_lolen;

	चयन (YYTDFLAGS2BYTES (tbl->td_flags)) {
	हाल माप (flex_int8_t):
		वापस ((flex_int8_t *) (tbl->td_तथ्य))[(i * lo + j) * (k + 1) +
						   k];
	हाल माप (flex_int16_t):
		वापस ((flex_int16_t *) (tbl->td_तथ्य))[(i * lo + j) * (k +
								    1) +
						    k];
	हाल माप (flex_int32_t):
		वापस ((flex_int32_t *) (tbl->td_तथ्य))[(i * lo + j) * (k +
								    1) +
						    k];
	शेष:
		flex_die (_("invalid td_flags detected"));
		अवरोध;
	}

	वापस 0;
}
#पूर्ण_अगर /* Not used */

/** Extract data element [i] from array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @return data[i]
 */
अटल flex_int32_t yytbl_तथ्य_geti (स्थिर काष्ठा yytbl_तथ्य *tbl, पूर्णांक i)
{

	चयन (YYTDFLAGS2BYTES (tbl->td_flags)) {
	हाल माप (flex_int8_t):
		वापस ((flex_int8_t *) (tbl->td_तथ्य))[i];
	हाल माप (flex_int16_t):
		वापस ((flex_int16_t *) (tbl->td_तथ्य))[i];
	हाल माप (flex_int32_t):
		वापस ((flex_int32_t *) (tbl->td_तथ्य))[i];
	शेष:
		flex_die (_("invalid td_flags detected"));
		अवरोध;
	}
	वापस 0;
}

/** Set data element [i] in array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @param newval new value for data[i]
 */
अटल व्योम yytbl_तथ्य_seti (स्थिर काष्ठा yytbl_तथ्य *tbl, पूर्णांक i,
			     flex_int32_t newval)
{

	चयन (YYTDFLAGS2BYTES (tbl->td_flags)) {
	हाल माप (flex_int8_t):
		((flex_int8_t *) (tbl->td_तथ्य))[i] = (flex_int8_t) newval;
		अवरोध;
	हाल माप (flex_int16_t):
		((flex_int16_t *) (tbl->td_तथ्य))[i] = (flex_int16_t) newval;
		अवरोध;
	हाल माप (flex_int32_t):
		((flex_int32_t *) (tbl->td_तथ्य))[i] = (flex_int32_t) newval;
		अवरोध;
	शेष:
		flex_die (_("invalid td_flags detected"));
		अवरोध;
	}
}

/** Calculate the number of bytes  needed to hold the largest
 *  absolute value in this data array.
 *  @param tbl  the data table
 *  @return sizeof(n) where n in {flex_int8_t, flex_int16_t, flex_int32_t}
 */
अटल माप_प्रकार min_int_आकार (काष्ठा yytbl_तथ्य *tbl)
{
	flex_int32_t i, योग_len;
	flex_int32_t max = 0;

	योग_len = yytbl_calc_योग_len (tbl);

	क्रम (i = 0; i < योग_len; i++) {
		flex_int32_t n;

		n = असल (yytbl_तथ्य_geti (tbl, i));

		अगर (max < n)
			max = n;
	}

	अगर (max <= INT8_MAX)
		वापस माप (flex_int8_t);
	अन्यथा अगर (max <= INT16_MAX)
		वापस माप (flex_int16_t);
	अन्यथा
		वापस माप (flex_int32_t);
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
व्योम yytbl_तथ्य_compress (काष्ठा yytbl_तथ्य *tbl)
{
	flex_int32_t i, योग_len;
	माप_प्रकार newsz;
	काष्ठा yytbl_तथ्य newtbl;

	yytbl_तथ्य_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_आकार (tbl);


	अगर (newsz == YYTDFLAGS2BYTES (tbl->td_flags))
		/* No change in this table needed. */
		वापस;

	अगर (newsz > YYTDFLAGS2BYTES (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		वापस;
	}

	योग_len = yytbl_calc_योग_len (tbl);
	newtbl.td_तथ्य = सुस्मृति ((माप_प्रकार) योग_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	क्रम (i = 0; i < योग_len; i++) {
		flex_int32_t g;

		g = yytbl_तथ्य_geti (tbl, i);
		yytbl_तथ्य_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	मुक्त (tbl->td_तथ्य);
	*tbl = newtbl;
}

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
