/* flex - tool to generate fast lexical analyzers */

/* SPDX-License-Identifier: BSD-3-Clause-flex */

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


#ಅನ್ತರ್ಭಾವ "flexdef.h"
#ಅನ್ತರ್ಭಾವ "tables.h"

/* START digested skeletons */

ಧ್ರುವ ವರ್ಣ *cpp_skel[] = {
#ಅನ್ತರ್ಭಾವ "cpp-flex.h"
    0,
};

ಧ್ರುವ ವರ್ಣ *c99_skel[] = {
#ಅನ್ತರ್ಭಾವ "c99-flex.h"
    0,
};

ಧ್ರುವ ವರ್ಣ *go_skel[] = {
#ಅನ್ತರ್ಭಾವ "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
ಸಂರಚನಾ flex_backend_t {
	ಧ್ರುವ ವರ್ಣ **skel;		// Digested skeleton file
};

ಸ್ಥಿರ ಸಂರಚನಾ flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {ರಿಕ್ತ}
};

ಸ್ಥಿರ ಸಂರಚನಾ flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
ಸ್ಥಿರ bool boneseeker(ಧ್ರುವ ವರ್ಣ *bone)
{
	ಪೂರ್ಣಾಙ್ಕ i;

	ಪ್ರತಿ (i = 0; backend->skel[i] != ರಿಕ್ತ; i++) {
		ಧ್ರುವ ವರ್ಣ *ಸಾಲು = backend->skel[i];
		ಯದಿ (strstr(ಸಾಲು, bone) != ರಿಕ್ತ)
			ಪ್ರತ್ಯಾಗಮ true;
		ಅನ್ಯಥಾ ಯದಿ (strncmp(ಸಾಲು, "%%", 2) == 0)
			ಭಙ್ಗ;
	}
	ಪ್ರತ್ಯಾಗಮ false;
}

ಶೂನ್ಯ backend_by_name(ಧ್ರುವ ವರ್ಣ *name)
{
	ಧ್ರುವ ವರ್ಣ *prefix_property;
	ಯದಿ (name != ರಿಕ್ತ) {
		ಯದಿ (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			ಗಚ್ಛ backend_ok;
		}
		ಯದಿ (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			ಗಚ್ಛ backend_ok;
		}
		ಪ್ರತಿ (backend = &backends[0]; backend->skel != ರಿಕ್ತ; backend++) {
			ಯದಿ (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				ಗಚ್ಛ backend_ok;
		}
		flexerror(_("no such back end"));
	}
  backend_ok:
	ctrl.rewrite = !is_default_backend();
	ctrl.backend_name = xstrdup(skel_property("M4_PROPERTY_BACKEND_NAME"));
	ctrl.traceline_re = xstrdup(skel_property("M4_PROPERTY_TRACE_LINE_REGEXP"));
	ctrl.traceline_template = xstrdup(skel_property("M4_PROPERTY_TRACE_LINE_TEMPLATE"));
	ctrl.have_state_entry_format = boneseeker("m4_define([[M4_HOOK_STATE_ENTRY_FORMAT]]");
	prefix_property = skel_property("M4_PROPERTY_PREFIX");
	ಯದಿ (prefix_property != ರಿಕ್ತ)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

ಧ್ರುವ ವರ್ಣ *suffix (ಶೂನ್ಯ)
{
	ಧ್ರುವ ವರ್ಣ   *suffix;

	ಯದಿ (is_default_backend()) {
		ಯದಿ (ctrl.C_plus_plus)
			suffix = "cc";
		ಅನ್ಯಥಾ
			suffix = "c";
	} ಅನ್ಯಥಾ {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	ಪ್ರತ್ಯಾಗಮ suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
ಧ್ರುವ ವರ್ಣ *skel_property(ಧ್ರುವ ವರ್ಣ *propname)
{
	ಪೂರ್ಣಾಙ್ಕ i;
	ಸ್ಥಿರ ವರ್ಣ name[256], ಮೌಲ್ಯ[256], *np, *vp;;
	ಧ್ರುವ ವರ್ಣ *cp;

	ಪ್ರತಿ (i = 0; backend->skel[i] != ರಿಕ್ತ; i++) {
		ಧ್ರುವ ವರ್ಣ *ಸಾಲು = backend->skel[i];
		ಯದಿ (ಸಾಲು[0] == '\0')
			ಅನುವರ್ತ;
		/* only scan before first skell breakpoint */
		ಯದಿ (strncmp(ಸಾಲು, "%%", 2) == 0)
			ಭಙ್ಗ;
		/* ignore anything that's not a definition */
		ಯದಿ (strncmp(ಸಾಲು, "m4_define(", 10) != 0)
			ಅನುವರ್ತ;
		/* skip space and quotes before macro name */
		ಪ್ರತಿ (cp = ಸಾಲು + 10; isspace(*cp) || *cp == '['; *cp++)
			ಅನುವರ್ತ;
		/* copy up to following ] into the name buffer */
		np = name;
		ಯಾವತ್ (*cp != ']' && *cp != '\0' && (np < name + ಪರಿಮಾಣ(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		ಯದಿ (*cp == ']') {
			ಯದಿ (strcmp(name, propname) != 0)
				ಅನುವರ್ತ; /* try next line */
		} ಅನ್ಯಥಾ {
			flexerror(_("unterminated or too long property name"));
			ಅನುವರ್ತ;
		}
		/* skip to the property value */
		ಯಾವತ್ (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		ಯಾವತ್ (*cp == '[')
			cp++;
		ಯದಿ (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = ಮೌಲ್ಯ;
		ಯಾವತ್ (*cp != '\0' && vp < ಮೌಲ್ಯ + ಪರಿಮಾಣ(ಮೌಲ್ಯ) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		ಯದಿ (*cp == ']') {
			*vp = '\0';
			ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;
		} ಅನ್ಯಥಾ {
			flexerror(_("unterminated or too long property value"));
		}
	}
	ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
ಶೂನ್ಯ skelout (bool announce)
{
	ವರ್ಣ    buf_storage[MAXLINE];
	ವರ್ಣ   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	ಯಾವತ್ (env.skelfile != ರಿಕ್ತ ?
	       (fgets (buf, MAXLINE, env.skelfile) != ರಿಕ್ತ) :
	       ((buf = (ವರ್ಣ *) backend->skel[skel_ind++]) != 0)) {

		ಯದಿ (env.skelfile != ರಿಕ್ತ)
			chomp (buf);

		/* copy from skel array */
		ಯದಿ (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			ಯದಿ (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			ಯದಿ (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			ಅನ್ಯಥಾ ಯದಿ (buf[1] == '%') {
				/* %% is a break point for skelout() */
				ಯದಿ (announce) {
					comment(buf);
					outc ('\n');
				}
				ಪ್ರತ್ಯಾಗಮ;
			}
			ಅನ್ಯಥಾ {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		ಅನ್ಯಥಾ ಯದಿ (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
