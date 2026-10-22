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
#ವ್ಯಾಖ್ಯಾನಿಸು BYTES2TFLAG(n)\
    (((n) == ಗಾತ್ರ(flex_int8_t))\
        ? YYTD_DATA8\
        :(((n)== ಗಾತ್ರ(flex_int16_t))\
            ? YYTD_DATA16\
            : YYTD_DATA32))

/** Clear YYTD_DATA* bit flags
 * @return the flag with the YYTD_DATA* bits cleared
 */
#ವ್ಯಾಖ್ಯಾನಿಸು TFLAGS_CLRDATA(flg) ((flg) & ~(YYTD_DATA8 | YYTD_DATA16 | YYTD_DATA32))

ಪೂರ್ಣಾಂಕ     yytbl_write32 (ರಚನೆ yytbl_writer *wr, flex_uint32_t v);
ಪೂರ್ಣಾಂಕ     yytbl_write16 (ರಚನೆ yytbl_writer *wr, flex_uint16_t v);
ಪೂರ್ಣಾಂಕ     yytbl_write8 (ರಚನೆ yytbl_writer *wr, flex_uint8_t v);
ಪೂರ್ಣಾಂಕ     yytbl_writen (ರಚನೆ yytbl_writer *wr, ಶೂನ್ಯ *v, ಪೂರ್ಣಾಂಕ len);
ಸ್ಥಿರ flex_int32_t yytbl_ದತ್ತಾಂಶ_geti (ಸ್ಥಿರಾಂಕ ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl, ಪೂರ್ಣಾಂಕ i);
/* XXX Not used
static flex_int32_t yytbl_data_getijk (const struct yytbl_data *tbl, int i,
				  int j, int k);
 */


/** Initialize the table writer.
 *  @param wr an uninitialized writer
 *  @param out the output file
 *  @return 0 on success
 */
ಪೂರ್ಣಾಂಕ yytbl_writer_init (ರಚನೆ yytbl_writer *wr, FILE * ಹೊರಹೋಗು)
{
	wr->ಹೊರಹೋಗು = ಹೊರಹೋಗು;
	wr->ಒಟ್ಟು_written = 0;
	ಹಿಂತಿರುಗಿ 0;
}

/** Initialize a table header.
 *  @param th  The uninitialized structure
 *  @param version_str the  version string
 *  @param name the name of this table set
 */
ಪೂರ್ಣಾಂಕ yytbl_hdr_init (ರಚನೆ yytbl_hdr *th, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಆವೃತ್ತಿ_str,
		    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
	memset (th, 0, ಗಾತ್ರ (ರಚನೆ yytbl_hdr));

	th->th_magic = YYTBL_MAGIC;
	th->th_hsize = (flex_uint32_t) (14 + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (ಆವೃತ್ತಿ_str) + 1 + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (name) + 1);
	th->th_hsize += (8 - (th->th_hsize % 8)) % 8; // Pad to 64-bit boundary
	th->th_ssize = 0;	// Not known at this point.
	th->th_flags = 0;
	th->th_ಆವೃತ್ತಿ = xstrdup(ಆವೃತ್ತಿ_str);
	th->th_name = xstrdup(name);
	ಹಿಂತಿರುಗಿ 0;
}

/** Allocate and initialize a table data structure.
 *  @param td a pointer to an uninitialized table
 *  @param id  the table identifier
 *  @return 0 on success
 */
ಪೂರ್ಣಾಂಕ yytbl_ದತ್ತಾಂಶ_init (ರಚನೆ yytbl_ದತ್ತಾಂಶ *td, ಎಣಿಕೆ yytbl_id id)
{

	memset (td, 0, ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ));
	td->td_id = id;
	td->td_flags = YYTD_DATA32;
	ಹಿಂತಿರುಗಿ 0;
}

/** Clean up table and data array.
 *  @param td will be destroyed
 *  @return 0 on success
 */
ಪೂರ್ಣಾಂಕ yytbl_ದತ್ತಾಂಶ_destroy (ರಚನೆ yytbl_ದತ್ತಾಂಶ *td)
{
	ಬಿಡುಗಡೆ(td->td_ದತ್ತಾಂಶ);
	td->td_ದತ್ತಾಂಶ = 0;
	ಬಿಡುಗಡೆ (td);
	ಹಿಂತಿರುಗಿ 0;
}

/** Write enough padding to bring the file pointer to a 64-bit boundary. */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ yytbl_write_pad64 (ರಚನೆ yytbl_writer *wr)
{
	ಪೂರ್ಣಾಂಕ bwritten = 0;

	ಆಗ (wr->ಒಟ್ಟು_written % (8 * ಗಾತ್ರ(flex_uint8_t)) > 0) {
		ಆದರೆ (yytbl_write8 (wr, 0) < 0)
			ಹಿಂತಿರುಗಿ -1;
		ಇಲ್ಲದಿದ್ದರೆ
			bwritten++;
	}
	ಹಿಂತಿರುಗಿ bwritten;
}

/** write the header.
 *  @param wr the output stream
 *  @param th table header to be written
 *  @return -1 on error, or bytes written on success.
 */
ಪೂರ್ಣಾಂಕ yytbl_hdr_fwrite (ರಚನೆ yytbl_writer *wr, ಸ್ಥಿರಾಂಕ ರಚನೆ yytbl_hdr *th)
{
	ಪೂರ್ಣಾಂಕ  sz, rv;
	ಪೂರ್ಣಾಂಕ     bwritten = 0;

	ಆದರೆ (yytbl_write32 (wr, th->th_magic) < 0
	    || yytbl_write32 (wr, th->th_hsize) < 0)
		flex_die (_("th_magic|th_hsize write32 failed"));
	bwritten += 8;

	ಆದರೆ (fgetpos (wr->ಹೊರಹೋಗು, &(wr->th_ssize_pos)) != 0)
		flex_die (_("fgetpos failed"));

	ಆದರೆ (yytbl_write32 (wr, th->th_ssize) < 0
	    || yytbl_write16 (wr, th->th_flags) < 0)
		flex_die (_("th_ssize|th_flags write failed"));
	bwritten += 6;

	sz = (ಪೂರ್ಣಾಂಕ) ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (th->th_ಆವೃತ್ತಿ) + 1;
	ಆದರೆ ((rv = yytbl_writen (wr, th->th_ಆವೃತ್ತಿ, sz)) != sz)
		flex_die (_("th_version written failed"));
	bwritten += rv;

	sz = (ಪೂರ್ಣಾಂಕ) ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (th->th_name) + 1;
	ಆದರೆ ((rv = yytbl_writen (wr, th->th_name, sz)) != sz)
		flex_die (_("th_name written failed"));
	bwritten += rv;

	/* add padding */
	ಆದರೆ ((rv = yytbl_write_pad64 (wr)) < 0)
		flex_die (_("pad64 failed"));
	bwritten += rv;

	/* Sanity check */
	ಆದರೆ (bwritten != (ಪೂರ್ಣಾಂಕ) th->th_hsize)
		flex_die (_("pad64 failed"));

	ಹಿಂತಿರುಗಿ bwritten;
}


/** Write this table.
 *  @param wr the file writer
 *  @param td table data to be written
 *  @return -1 on error, or bytes written on success.
 */
ಪೂರ್ಣಾಂಕ yytbl_ದತ್ತಾಂಶ_fwrite (ರಚನೆ yytbl_writer *wr, ರಚನೆ yytbl_ದತ್ತಾಂಶ *td)
{
	ಪೂರ್ಣಾಂಕ  rv;
	flex_int32_t bwritten = 0;
	flex_int32_t i, ಒಟ್ಟು_len;
	fpos_t  pos;

	ಆದರೆ ((rv = yytbl_write16 (wr, td->td_id)) < 0)
		ಹಿಂತಿರುಗಿ -1;
	bwritten += rv;

	ಆದರೆ ((rv = yytbl_write16 (wr, td->td_flags)) < 0)
		ಹಿಂತಿರುಗಿ -1;
	bwritten += rv;

	ಆದರೆ ((rv = yytbl_write32 (wr, td->td_hilen)) < 0)
		ಹಿಂತಿರುಗಿ -1;
	bwritten += rv;

	ಆದರೆ ((rv = yytbl_write32 (wr, td->td_lolen)) < 0)
		ಹಿಂತಿರುಗಿ -1;
	bwritten += rv;

	ಒಟ್ಟು_len = yytbl_calc_ಒಟ್ಟು_len (td);
	ಗಾಗಿ (i = 0; i < ಒಟ್ಟು_len; i++) {
		ಆಯ್ಕೆ (YYTDFLAGS2_ಬೈಟುಗಳು (td->td_flags)) {
		ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int8_t):
			rv = yytbl_write8 (wr, (flex_uint8_t) yytbl_ದತ್ತಾಂಶ_geti (td, i));
			ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int16_t):
			rv = yytbl_write16 (wr, (flex_uint16_t) yytbl_ದತ್ತಾಂಶ_geti (td, i));
			ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int32_t):
			rv = yytbl_write32 (wr, (flex_uint32_t) yytbl_ದತ್ತಾಂಶ_geti (td, i));
			ನಿಲ್ಲಿಸು;
		ಪೂರ್ವನಿಯೋಜಿತ:
			flex_die (_("invalid td_flags detected"));
		}
		ಆದರೆ (rv < 0) {
			flex_die (_("error while writing tables"));
			ಹಿಂತಿರುಗಿ -1;
		}
		bwritten += rv;
	}

	/* Sanity check */
	ಆದರೆ (bwritten != (12 + ಒಟ್ಟು_len * (ಪೂರ್ಣಾಂಕ) YYTDFLAGS2_ಬೈಟುಗಳು (td->td_flags))) {
		flex_die (_("insanity detected"));
		ಹಿಂತಿರುಗಿ -1;
	}

	/* add padding */
	ಆದರೆ ((rv = yytbl_write_pad64 (wr)) < 0) {
		flex_die (_("pad64 failed"));
		ಹಿಂತಿರುಗಿ -1;
	}
	bwritten += rv;

	/* Now go back and update the th_hsize member */
	ಆದರೆ (fgetpos (wr->ಹೊರಹೋಗು, &pos) != 0
	    || fsetpos (wr->ಹೊರಹೋಗು, &(wr->th_ssize_pos)) != 0
	    || yytbl_write32 (wr, (flex_uint32_t) wr->ಒಟ್ಟು_written) < 0
	    || fsetpos (wr->ಹೊರಹೋಗು, &pos)) {
		flex_die (_("get|set|fwrite32 failed"));
		ಹಿಂತಿರುಗಿ -1;
	}
	ಇಲ್ಲದಿದ್ದರೆ
		/* Don't count the int we just wrote. */
		wr->ಒಟ್ಟು_written -= (ಪೂರ್ಣಾಂಕ) ಗಾತ್ರ (flex_int32_t);
	ಹಿಂತಿರುಗಿ bwritten;
}

/** Write n bytes.
 *  @param  wr   the table writer
 *  @param  v    data to be written
 *  @param  len  number of bytes
 *  @return  -1 on error. number of bytes written on success.
 */
ಪೂರ್ಣಾಂಕ yytbl_writen (ರಚನೆ yytbl_writer *wr, ಶೂನ್ಯ *v, ಪೂರ್ಣಾಂಕ len)
{
	ಪೂರ್ಣಾಂಕ  rv;

	rv = (ಪೂರ್ಣಾಂಕ) fwrite (v, 1, (size_t) len, wr->ಹೊರಹೋಗು);
	ಆದರೆ (rv != len)
		ಹಿಂತಿರುಗಿ -1;
	wr->ಒಟ್ಟು_written += len;
	ಹಿಂತಿರುಗಿ len;
}

/** Write four bytes in network byte order
 *  @param  wr  the table writer
 *  @param  v    a dword in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
ಪೂರ್ಣಾಂಕ yytbl_write32 (ರಚನೆ yytbl_writer *wr, flex_uint32_t v)
{
	flex_uint32_t vnet;
	ಪೂರ್ಣಾಂಕ  ಬೈಟುಗಳು, rv;

	vnet = htonl (v);
	ಬೈಟುಗಳು = (ಪೂರ್ಣಾಂಕ) ಗಾತ್ರ (flex_uint32_t);
	rv = (ಪೂರ್ಣಾಂಕ) fwrite (&vnet, (size_t) ಬೈಟುಗಳು, 1, wr->ಹೊರಹೋಗು);
	ಆದರೆ (rv != 1)
		ಹಿಂತಿರುಗಿ -1;
	wr->ಒಟ್ಟು_written += ಬೈಟುಗಳು;
	ಹಿಂತಿರುಗಿ ಬೈಟುಗಳು;
}

/** Write two bytes in network byte order.
 *  @param  wr  the table writer
 *  @param  v    a word in host byte order
 *  @return  -1 on error. number of bytes written on success.
 */
ಪೂರ್ಣಾಂಕ yytbl_write16 (ರಚನೆ yytbl_writer *wr, flex_uint16_t v)
{
	flex_uint16_t vnet;
	ಪೂರ್ಣಾಂಕ  ಬೈಟುಗಳು, rv;

	vnet = htons (v);
	ಬೈಟುಗಳು = (ಪೂರ್ಣಾಂಕ) ಗಾತ್ರ (flex_uint16_t);
	rv = (ಪೂರ್ಣಾಂಕ) fwrite (&vnet, (size_t) ಬೈಟುಗಳು, 1, wr->ಹೊರಹೋಗು);
	ಆದರೆ (rv != 1)
		ಹಿಂತಿರುಗಿ -1;
	wr->ಒಟ್ಟು_written += ಬೈಟುಗಳು;
	ಹಿಂತಿರುಗಿ ಬೈಟುಗಳು;
}

/** Write a byte.
 *  @param  wr  the table writer
 *  @param  v    the value to be written
 *  @return  -1 on error. number of bytes written on success.
 */
ಪೂರ್ಣಾಂಕ yytbl_write8 (ರಚನೆ yytbl_writer *wr, flex_uint8_t v)
{
	ಪೂರ್ಣಾಂಕ  ಬೈಟುಗಳು, rv;

	ಬೈಟುಗಳು = (ಪೂರ್ಣಾಂಕ) ಗಾತ್ರ (flex_uint8_t);
	rv = (ಪೂರ್ಣಾಂಕ) fwrite (&v, (size_t) ಬೈಟುಗಳು, 1, wr->ಹೊರಹೋಗು);
	ಆದರೆ (rv != 1)
		ಹಿಂತಿರುಗಿ -1;
	wr->ಒಟ್ಟು_written += ಬೈಟುಗಳು;
	ಹಿಂತಿರುಗಿ ಬೈಟುಗಳು;
}


/* XXX Not Used */
#ಆದರೆ 0
/** Extract data element [i][j] from array data tables. 
 * @param tbl data table
 * @param i index into higher dimension array. i should be zero for one-dimensional arrays.
 * @param j index into lower dimension array.
 * @param k index into struct, must be 0 or 1. Only valid for YYTD_ID_TRANSITION table
 * @return data[i][j + k]
 */
ಸ್ಥಿರ flex_int32_t yytbl_ದತ್ತಾಂಶ_getijk (ಸ್ಥಿರಾಂಕ ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl, ಪೂರ್ಣಾಂಕ i,
				  ಪೂರ್ಣಾಂಕ j, ಪೂರ್ಣಾಂಕ k)
{
	flex_int32_t lo;

	k %= 2;
	lo = tbl->td_lolen;

	ಆಯ್ಕೆ (YYTDFLAGS2_ಬೈಟುಗಳು (tbl->td_flags)) {
	ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int8_t):
		ಹಿಂತಿರುಗಿ ((flex_int8_t *) (tbl->td_ದತ್ತಾಂಶ))[(i * lo + j) * (k + 1) +
						   k];
	ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int16_t):
		ಹಿಂತಿರುಗಿ ((flex_int16_t *) (tbl->td_ದತ್ತಾಂಶ))[(i * lo + j) * (k +
								    1) +
						    k];
	ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int32_t):
		ಹಿಂತಿರುಗಿ ((flex_int32_t *) (tbl->td_ದತ್ತಾಂಶ))[(i * lo + j) * (k +
								    1) +
						    k];
	ಪೂರ್ವನಿಯೋಜಿತ:
		flex_die (_("invalid td_flags detected"));
		ನಿಲ್ಲಿಸು;
	}

	ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ /* Not used */

/** Extract data element [i] from array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @return data[i]
 */
ಸ್ಥಿರ flex_int32_t yytbl_ದತ್ತಾಂಶ_geti (ಸ್ಥಿರಾಂಕ ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl, ಪೂರ್ಣಾಂಕ i)
{

	ಆಯ್ಕೆ (YYTDFLAGS2_ಬೈಟುಗಳು (tbl->td_flags)) {
	ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int8_t):
		ಹಿಂತಿರುಗಿ ((flex_int8_t *) (tbl->td_ದತ್ತಾಂಶ))[i];
	ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int16_t):
		ಹಿಂತಿರುಗಿ ((flex_int16_t *) (tbl->td_ದತ್ತಾಂಶ))[i];
	ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int32_t):
		ಹಿಂತಿರುಗಿ ((flex_int32_t *) (tbl->td_ದತ್ತಾಂಶ))[i];
	ಪೂರ್ವನಿಯೋಜಿತ:
		flex_die (_("invalid td_flags detected"));
		ನಿಲ್ಲಿಸು;
	}
	ಹಿಂತಿರುಗಿ 0;
}

/** Set data element [i] in array data tables treated as a single flat array of integers.
 * Be careful for 2-dimensional arrays or for YYTD_ID_TRANSITION, which is an array
 * of structs. 
 * @param tbl data table
 * @param i index into array.
 * @param newval new value for data[i]
 */
ಸ್ಥಿರ ಶೂನ್ಯ yytbl_ದತ್ತಾಂಶ_seti (ಸ್ಥಿರಾಂಕ ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl, ಪೂರ್ಣಾಂಕ i,
			     flex_int32_t newval)
{

	ಆಯ್ಕೆ (YYTDFLAGS2_ಬೈಟುಗಳು (tbl->td_flags)) {
	ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int8_t):
		((flex_int8_t *) (tbl->td_ದತ್ತಾಂಶ))[i] = (flex_int8_t) newval;
		ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int16_t):
		((flex_int16_t *) (tbl->td_ದತ್ತಾಂಶ))[i] = (flex_int16_t) newval;
		ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ ಗಾತ್ರ (flex_int32_t):
		((flex_int32_t *) (tbl->td_ದತ್ತಾಂಶ))[i] = (flex_int32_t) newval;
		ನಿಲ್ಲಿಸು;
	ಪೂರ್ವನಿಯೋಜಿತ:
		flex_die (_("invalid td_flags detected"));
		ನಿಲ್ಲಿಸು;
	}
}

/** Calculate the number of bytes  needed to hold the largest
 *  absolute value in this data array.
 *  @param tbl  the data table
 *  @return sizeof(n) where n in {flex_int8_t, flex_int16_t, flex_int32_t}
 */
ಸ್ಥಿರ size_t min_int_ಗಾತ್ರ (ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl)
{
	flex_int32_t i, ಒಟ್ಟು_len;
	flex_int32_t max = 0;

	ಒಟ್ಟು_len = yytbl_calc_ಒಟ್ಟು_len (tbl);

	ಗಾಗಿ (i = 0; i < ಒಟ್ಟು_len; i++) {
		flex_int32_t n;

		n = ನಿರಪೇಕ್ಷ (yytbl_ದತ್ತಾಂಶ_geti (tbl, i));

		ಆದರೆ (max < n)
			max = n;
	}

	ಆದರೆ (max <= INT8_MAX)
		ಹಿಂತಿರುಗಿ ಗಾತ್ರ (flex_int8_t);
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (max <= INT16_MAX)
		ಹಿಂತಿರುಗಿ ಗಾತ್ರ (flex_int16_t);
	ಇಲ್ಲದಿದ್ದರೆ
		ಹಿಂತಿರುಗಿ ಗಾತ್ರ (flex_int32_t);
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
ಶೂನ್ಯ yytbl_ದತ್ತಾಂಶ_compress (ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl)
{
	flex_int32_t i, ಒಟ್ಟು_len;
	size_t newsz;
	ರಚನೆ yytbl_ದತ್ತಾಂಶ newtbl;

	yytbl_ದತ್ತಾಂಶ_init (&newtbl, tbl->td_id);
	newtbl.td_hilen = tbl->td_hilen;
	newtbl.td_lolen = tbl->td_lolen;
	newtbl.td_flags = tbl->td_flags;

	newsz = min_int_ಗಾತ್ರ (tbl);


	ಆದರೆ (newsz == YYTDFLAGS2_ಬೈಟುಗಳು (tbl->td_flags))
		/* No change in this table needed. */
		ಹಿಂತಿರುಗಿ;

	ಆದರೆ (newsz > YYTDFLAGS2_ಬೈಟುಗಳು (tbl->td_flags)) {
		flex_die (_("detected negative compression"));
		ಹಿಂತಿರುಗಿ;
	}

	ಒಟ್ಟು_len = yytbl_calc_ಒಟ್ಟು_len (tbl);
	newtbl.td_ದತ್ತಾಂಶ = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು ((size_t) ಒಟ್ಟು_len, newsz);
	newtbl.td_flags = (flex_uint16_t)
		(TFLAGS_CLRDATA (newtbl.td_flags) | BYTES2TFLAG (newsz));

	ಗಾಗಿ (i = 0; i < ಒಟ್ಟು_len; i++) {
		flex_int32_t g;

		g = yytbl_ದತ್ತಾಂಶ_geti (tbl, i);
		yytbl_ದತ್ತಾಂಶ_seti (&newtbl, i, g);
	}


	/* Now copy over the old table */
	ಬಿಡುಗಡೆ (tbl->td_ದತ್ತಾಂಶ);
	*tbl = newtbl;
}

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
