/* flex - tool to generate fast lexical analyzers */

/*  Copyright (c) 1990 The Regents of the University of California. */
/*  All rights reserved. */

/*  This code is derived from software contributed to Berkeley by */
/*  Vern Paxson. */

/*  The United States Government has rights in this work pursuant */
/*  to contract no. DE-AC03-76SF00098 between the United States */
/*  Department of Energy and the University of California. */

/*  This file is part of flex. */

/*  Redistribution and use in source and binary forms, with or without */
/*  modification, are permitted provided that the following conditions */
/*  are met: */

/*  1. Redistributions of source code must retain the above copyright */
/*     notice, this list of conditions and the following disclaimer. */
/*  2. Redistributions in binary form must reproduce the above copyright */
/*     notice, this list of conditions and the following disclaimer in the */
/*     documentation and/or other materials provided with the distribution. */

/*  Neither the name of the University nor the names of its contributors */
/*  may be used to endorse or promote products derived from this software */
/*  without specific prior written permission. */

/*  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR */
/*  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED */
/*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR */
/*  PURPOSE. */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ OPTIONS_H
#ವ್ಯಾಖ್ಯಾನಿಸು OPTIONS_H
#ಅನ್ತರ್ಭಾವ "scanopt.h"

ಬಾಹ್ಯ optspec_t flexopts[];

ಎಣಿಕೆ flexopt_flag_t {
	/* Use positive integers only, since they are return codes for scanopt.
	 * Order is not important. */
	OPT_7_ಬಿಟ್ = 1,
	OPT_8_ಬಿಟ್,
	OPT_ALIGN,
	OPT_ALWAYS_INTERACTIVE,
	OPT_ARRAY,
	OPT_BACKUP,
	OPT_BACKUP_FILE,
	OPT_BATCH,
        OPT_BISON_BRIDGE,
        OPT_BISON_BRIDGE_LOCATIONS,
	OPT_CASE_INSENSITIVE,
	OPT_COMPRESSION,
	OPT_CPLUSPLUS,
	OPT_DEBUG,
	OPT_DEFAULT,
	OPT_DONOTHING,
	OPT_ECS,
	OPT_EMIT,
	OPT_FAST,
	OPT_ತುಂಬಿದ,
	OPT_ಶೀರ್ಷಿಕೆ_FILE,
	OPT_HELP,
	OPT_HEX,
	OPT_INTERACTIVE,
	OPT_LEX_COMPAT,
	OPT_POSIX_COMPAT,
	OPT_MAIN,
	OPT_META_ECS,
	OPT_NEVER_INTERACTIVE,
	OPT_NO_ALIGN,
	OPT_NO_DEBUG,
	OPT_NO_DEFAULT,
	OPT_NO_ECS,
	OPT_NO_ಸಾಲು,
	OPT_NO_MAIN,
	OPT_NO_META_ECS,
	OPT_NO_REENTRANT,
	OPT_NO_REJECT,
	OPT_NO_STDINIT,
	OPT_NO_YYINPUT,
	OPT_NO_YYUNPUT,
	OPT_NO_WARN,
	OPT_NO_YYGET_EXTRA,
	OPT_NO_YYGET_ಒಳ,
	OPT_NO_YYGET_LENG,
	OPT_NO_YYGET_LINENO,
	OPT_NO_YYGET_ಸ್ತಂಭ,
	OPT_NO_YYGET_LLOC,
	OPT_NO_YYGET_LVAL,
	OPT_NO_YYGET_ಹೊರಹೋಗು,
	OPT_NO_YYGET_DEBUG,
	OPT_NO_YYGET_ಪಠ್ಯ,
	OPT_NO_YYLINENO,
	OPT_NO_YYMORE,
	OPT_NO_YYSET_EXTRA,
	OPT_NO_YYSET_ಒಳ,
	OPT_NO_YYSET_LINENO,
	OPT_NO_YYSET_ಸ್ತಂಭ,
	OPT_NO_YYSET_LLOC,
	OPT_NO_YYSET_LVAL,
	OPT_NO_YYSET_ಹೊರಹೋಗು,
	OPT_NO_YYSET_DEBUG,
	OPT_NO_YYWRAP,
	OPT_NO_YY_ತೆಗೆ_STATE,
	OPT_NO_YY_ತಳ್ಳು_STATE,
	OPT_NO_YY_ಪರಿಶೀಲನೆ_ಬಫರ್,
	OPT_NO_YY_ಪರಿಶೀಲನೆ_ಬೈಟುಗಳು,
	OPT_NO_YY_ಪರಿಶೀಲನೆ_STRING,
	OPT_NO_YY_ತುದಿ_STATE,
	OPT_OUTFILE,
	OPT_PERF_REPORT,
	OPT_ಸೂಚಕ,
	OPT_ಪೂರ್ವಪ್ರತ್ಯಯ,
	OPT_PREPROCDEFINE,
	OPT_PREPROC_LEVEL,
	OPT_READ,
	OPT_REENTRANT,
	OPT_REJECT,
	OPT_SKEL,
	OPT_ರಾಶಿ,
	OPT_STDINIT,
	OPT_STDOUT,
	OPT_TABLES_FILE,
	OPT_TABLES_VERIFY,
	OPT_TRACE,
	OPT_NO_UNISTD_H,
	OPT_VERBOSE,
	OPT_ಆವೃತ್ತಿ,
	OPT_WARN,
	OPT_YYCLASS,
	OPT_YYLINENO,
	OPT_YYMORE,
	OPT_YYWRAP,
        OPT_NO_SECT3_ESCAPE,
};

#ಆದರೆ_ಅಂತ್ಯ

/* vim:set tabstop=8 softtabstop=4 shiftwidth=4 textwidth=0: */
