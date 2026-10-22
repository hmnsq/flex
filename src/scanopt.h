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

#ifndef SCANOPT_H
#define SCANOPT_H

#അന്തര്ഭാവ "flexdef.h"


#ifndef NO_SCANOPT_USAGE
/* Used by scanopt_usage for pretty-printing. */
#ifdef HAVE_NCURSES_H
#അന്തര്ഭാവ <ncurses.h>
#endif
#endif

#ifdef __cplusplus
ബാഹ്യ  "C" {
#endif
/* Error codes. */ എണ്ണൽ scanopt_err_t {
		SCANOPT_ERR_OPT_UNRECOGNIZED = -1,	/* Unrecognized option. */
		SCANOPT_ERR_OPT_AMBIGUOUS = -2,	/* It matched more than one option name. */
		SCANOPT_ERR_ARG_NOT_FOUND = -3,	/* The required arg was not found. */
		SCANOPT_ERR_ARG_NOT_ALLOWED = -4	/* Option does not take an argument. */
	};


/* flags passed to scanopt_init */
	എണ്ണൽ scanopt_flag_t {
		SCANOPT_NO_ERR_സന്ദേശം = 0x01	/* Suppress printing to stderr. */
	};

/* Specification for a single option. */
	ഘടന optspec_t {
		സ്ഥിരം അക്ഷരം *opt_fmt;	/* e.g., "--foo=FILE", "-f FILE", "-n [NUM]" */
		പൂർണ്ണസംഖ്യ     r_val;	/* Value to be returned by scanopt_ex(). */
		സ്ഥിരം അക്ഷരം *desc;	/* Brief description of this option, or NULL. */
	};
	തരനിർവചനം ഘടന optspec_t optspec_t;


/* Used internally by scanopt() to maintain state. */
/* Never modify these value directly. */
	തരനിർവചനം ശൂന്യം *scanopt_t;


/* Initializes scanner and checks option list for errors.
 * Parameters:
 *   options - Array of ctrl.
 *   argc    - Same as passed to main().
 *   argv    - Same as passed to main(). First element is skipped.
 *   flags   - Control behavior.
 * Return:  A malloc'd pointer .
 */
	scanopt_t *scanopt_init (സ്ഥിരം optspec_t * options, പൂർണ്ണസംഖ്യ argc,
				 അക്ഷരം **argv, പൂർണ്ണസംഖ്യ flags);

/* Frees memory used by scanner.
 * Always returns 0. */
	പൂർണ്ണസംഖ്യ scanopt_destroy (scanopt_t * scanner);

#ifndef NO_SCANOPT_USAGE
/* Prints a usage message based on contents of optlist.
 * Parameters:
 *   scanner  - The scanner, already initialized with scanopt_init().
 *   fp       - The file stream to write to.
 *   usage    - Text to be prepended to option list. May be NULL.
 * Return:  Always returns 0 (zero).
 */
	പൂർണ്ണസംഖ്യ scanopt_usage (scanopt_t * scanner, FILE * fp, സ്ഥിരം അക്ഷരം *usage);
#endif

/* Scans command-line options in argv[].
 * Parameters:
 *   scanner  - The scanner, already initialized with scanopt_init().
 *   optarg   - Return argument, may be NULL.
 *              On success, it points to start of an argument.
 *   optindex - Return argument, may be NULL.
 *              On success or failure, it is the index of this option.
 *              If return is zero, then optindex is the NEXT valid option index.
 *
 * Return:  > 0 on success. Return value is from optspec_t->rval.
 *         == 0 if at end of ctrl.
 *          < 0 on error (return value is an error code).
 *
 */
	പൂർണ്ണസംഖ്യ scanopt (scanopt_t * scanner, അക്ഷരം **optarg, പൂർണ്ണസംഖ്യ *optindex);

#ifdef __cplusplus
}
#endif
#endif
/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
