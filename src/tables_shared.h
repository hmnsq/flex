#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ FLEX_SCANNER
/*
dnl  tables_shared.h - tables serialization header
dnl
dnl  Copyright (c) 1990 The Regents of the University of California.
dnl  All rights reserved.
dnl
dnl  This code is derived from software contributed to Berkeley by
dnl  Vern Paxson.
dnl
dnl  The United States Government has rights in this work pursuant
dnl  to contract no. DE-AC03-76SF00098 between the United States
dnl  Department of Energy and the University of California.
dnl
dnl  This file is part of flex.
dnl
dnl  Redistribution and use in source and binary forms, with or without
dnl  modification, are permitted provided that the following conditions
dnl  are met:
dnl
dnl  1. Redistributions of source code must retain the above copyright
dnl     notice, this list of conditions and the following disclaimer.
dnl  2. Redistributions in binary form must reproduce the above copyright
dnl     notice, this list of conditions and the following disclaimer in the
dnl     documentation and/or other materials provided with the distribution.
dnl
dnl  Neither the name of the University nor the names of its contributors
dnl  may be used to endorse or promote products derived from this software
dnl  without specific prior written permission.
dnl
dnl  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
dnl  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
dnl  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
dnl  PURPOSE.

dnl
dnl  This file is meant to be included in both the skeleton and the actual
dnl  flex code (hence the name "_shared").
*/
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ yyskel_static
#ವ್ಯಾಖ್ಯಾನಿಸು yyskel_static ಸ್ಥಿರ
#ಆದರೆ_ಅಂತ್ಯ
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ yyskel_static
#ವ್ಯಾಖ್ಯಾನಿಸು yyskel_static
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

/* Structures and prototypes for serializing flex tables.  The
 * binary format is documented in the manual.
 *
 * Design considerations:
 *
 *  -  The format allows many tables per file.
 *  -  The tables can be streamed.
 *  -  All data is stored in network byte order.
 *  -  We do not hinder future unicode support.
 *  -  We can lookup tables by name.
 */

/** Magic number for serialized format. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ YYTBL_MAGIC
#ವ್ಯಾಖ್ಯಾನಿಸು YYTBL_MAGIC 0xF13C57B1
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ YYTABLES_TYPES
#ವ್ಯಾಖ್ಯಾನಿಸು YYTABLES_TYPES
/** Possible values for td_id field. Each one corresponds to a
 *  scanner table of the same name.
 */
ಎಣಿಕೆ yytbl_id {
	YYTD_ID_ACCEPT = 0x01,		/**< 1-dim ints */
	YYTD_ID_ತಳ = 0x02,		/**< 1-dim ints */
	YYTD_ID_CHK = 0x03,		/**< 1-dim ints */
	YYTD_ID_DEF = 0x04,		/**< 1-dim ints */
	YYTD_ID_EC = 0x05,		/**< 1-dim ints */
	YYTD_ID_META = 0x06,		/**< 1-dim ints */
	YYTD_ID_NUL_TRANS = 0x07,	/**< 1-dim ints, maybe indices */
	YYTD_ID_NXT = 0x08,		/**< may be 2 dimensional ints */
	YYTD_ID_ನಿಯಮ_CAN_ಹೊಂದಿಕೆ_EOL = 0x09, /**< 1-dim ints */
	YYTD_ID_ಆರಂಭ_STATE_LIST = 0x0A,	/**< 1-dim indices into trans tbl  */
	YYTD_ID_TRANSITION = 0x0B,	/**< structs */
	YYTD_ID_ACCLIST = 0x0C		/**< 1-dim ints */
};

/** bit flags for t_flags field of struct yytbl_data */
ಎಣಿಕೆ yytbl_flags {
	/* These first three are mutually exclusive */
	YYTD_DATA8 = 0x01,   /**< data is an array of type flex_int8_t */
	YYTD_DATA16 = 0x02,  /**< data is an array of type flex_int16_t */
	YYTD_DATA32 = 0x04,  /**< data is an array of type flex_int32_t */

	/* These two are mutually exclusive. */
	YYTD_PTRANS = 0x08,  /**< data is a list of indexes of entries
                                 into the expanded `yy_transition'
                                 array. See notes in manual. */
	YYTD_STRUCT = 0x10  /**< data consists of yy_trans_info structs */
};

/* The serialized tables header. */
ರಚನೆ yytbl_hdr {
	flex_uint32_t th_magic;  /**< Must be 0xF13C57B1 (comes from "Flex Table") */
	flex_uint32_t th_hsize;  /**< Size of this header in bytes. */
	flex_uint32_t th_ssize;  /**< Size of this dataset, in bytes, including header. */
	flex_uint16_t th_flags;  /**< Currently unused, must be 0 */
	ಅಕ್ಷರ   *th_ಆವೃತ್ತಿ; /**< Flex version string. NUL terminated. */
	ಅಕ್ಷರ   *th_name;    /**< The name of this table set. NUL terminated. */
};

/** A single serialized table */
ರಚನೆ yytbl_ದತ್ತಾಂಶ {
	flex_uint16_t td_id;      /**< enum yytbl_id table identifier */
	flex_uint16_t td_flags;   /**< how to interpret this data */
	flex_uint32_t td_hilen;   /**< num elements in highest dimension array */
	flex_uint32_t td_lolen;   /**< num elements in lowest dimension array */
	ಶೂನ್ಯ   *td_ದತ್ತಾಂಶ;     /**< table data */
};
#ಆದರೆ_ಅಂತ್ಯ

/** Extract corresponding data size_t from td_flags */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ YYTDFLAGS2_ಬೈಟುಗಳು
#ವ್ಯಾಖ್ಯಾನಿಸು YYTDFLAGS2_ಬೈಟುಗಳು(td_flags)\
        (((td_flags) & YYTD_DATA8)\
            ? ಗಾತ್ರ(flex_int8_t)\
            :(((td_flags) & YYTD_DATA16)\
                ? ಗಾತ್ರ(flex_int16_t)\
                :ಗಾತ್ರ(flex_int32_t)))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ FLEX_SCANNER
m4_ifdef( [[M4_YY_NOT_ಒಳ_ಶೀರ್ಷಿಕೆ]],[[
#ಆದರೆ_ಅಂತ್ಯ
yyskel_static flex_int32_t yytbl_calc_ಒಟ್ಟು_len (ಸ್ಥಿರಾಂಕ ರಚನೆ yytbl_ದತ್ತಾಂಶ *tbl);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ FLEX_SCANNER
]])
#ಆದರೆ_ಅಂತ್ಯ

/* vim:set noexpandtab cindent tabstop=8 softtabstop=0 shiftwidth=8 textwidth=0: */
