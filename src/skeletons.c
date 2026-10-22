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

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cpp_skel[] = {
#ಅನ್ತರ್ಭಾವ "cpp-flex.h"
    0,
};

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *c99_skel[] = {
#ಅನ್ತರ್ಭಾವ "c99-flex.h"
    0,
};

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *go_skel[] = {
#ಅನ್ತರ್ಭಾವ "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
ರಚನೆ flex_backend_t {
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **skel;		// Digested skeleton file
};

ಸ್ಥಿರ ರಚನೆ flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {ಖಾಲಿ}
};

ಸ್ಥಿರ ರಚನೆ flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
ಸ್ಥಿರ bool boneseeker(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *bone)
{
	ಪೂರ್ಣಾಂಕ i;

	ಗಾಗಿ (i = 0; backend->skel[i] != ಖಾಲಿ; i++) {
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಾಲು = backend->skel[i];
		ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(ಸಾಲು, bone) != ಖಾಲಿ)
			ಹಿಂತಿರುಗಿ true;
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ(ಸಾಲು, "%%", 2) == 0)
			ನಿಲ್ಲಿಸು;
	}
	ಹಿಂತಿರುಗಿ false;
}

ಶೂನ್ಯ backend_by_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪೂರ್ವಪ್ರತ್ಯಯ_property;
	ಆದರೆ (name != ಖಾಲಿ) {
		ಆದರೆ (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			ಹೋಗು backend_ok;
		}
		ಆದರೆ (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			ಹೋಗು backend_ok;
		}
		ಗಾಗಿ (backend = &backends[0]; backend->skel != ಖಾಲಿ; backend++) {
			ಆದರೆ (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				ಹೋಗು backend_ok;
		}
		flexerror(_("no such back end"));
	}
  backend_ok:
	ctrl.rewrite = !is_default_backend();
	ctrl.backend_name = xstrdup(skel_property("M4_PROPERTY_BACKEND_NAME"));
	ctrl.traceline_re = xstrdup(skel_property("M4_PROPERTY_TRACE_LINE_REGEXP"));
	ctrl.traceline_template = xstrdup(skel_property("M4_PROPERTY_TRACE_LINE_TEMPLATE"));
	ctrl.have_state_ನಮೂದು_format = boneseeker("m4_define([[M4_HOOK_STATE_ENTRY_FORMAT]]");
	ಪೂರ್ವಪ್ರತ್ಯಯ_property = skel_property("M4_PROPERTY_PREFIX");
	ಆದರೆ (ಪೂರ್ವಪ್ರತ್ಯಯ_property != ಖಾಲಿ)
		ctrl.ಪೂರ್ವಪ್ರತ್ಯಯ = xstrdup(ಪೂರ್ವಪ್ರತ್ಯಯ_property);
	flex_init_regex(ctrl.traceline_re);
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *suffix (ಶೂನ್ಯ)
{
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ   *suffix;

	ಆದರೆ (is_default_backend()) {
		ಆದರೆ (ctrl.C_plus_plus)
			suffix = "cc";
		ಇಲ್ಲದಿದ್ದರೆ
			suffix = "c";
	} ಇಲ್ಲದಿದ್ದರೆ {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	ಹಿಂತಿರುಗಿ suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *skel_property(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *propname)
{
	ಪೂರ್ಣಾಂಕ i;
	ಸ್ಥಿರ ಅಕ್ಷರ name[256], ಮೌಲ್ಯ[256], *np, *vp;;
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cp;

	ಗಾಗಿ (i = 0; backend->skel[i] != ಖಾಲಿ; i++) {
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸಾಲು = backend->skel[i];
		ಆದರೆ (ಸಾಲು[0] == '\0')
			ಮುಂದುವರಿ;
		/* only scan before first skell breakpoint */
		ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ(ಸಾಲು, "%%", 2) == 0)
			ನಿಲ್ಲಿಸು;
		/* ignore anything that's not a definition */
		ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ(ಸಾಲು, "m4_define(", 10) != 0)
			ಮುಂದುವರಿ;
		/* skip space and quotes before macro name */
		ಗಾಗಿ (cp = ಸಾಲು + 10; ಖಾಲಿಯೇ(*cp) || *cp == '['; *cp++)
			ಮುಂದುವರಿ;
		/* copy up to following ] into the name buffer */
		np = name;
		ಆಗ (*cp != ']' && *cp != '\0' && (np < name + ಗಾತ್ರ(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		ಆದರೆ (*cp == ']') {
			ಆದರೆ (strcmp(name, propname) != 0)
				ಮುಂದುವರಿ; /* try next line */
		} ಇಲ್ಲದಿದ್ದರೆ {
			flexerror(_("unterminated or too long property name"));
			ಮುಂದುವರಿ;
		}
		/* skip to the property value */
		ಆಗ (*cp != '\0' && (*cp == ']' || ಖಾಲಿಯೇ(*cp) || *cp == ','))
			cp++;
		ಆಗ (*cp == '[')
			cp++;
		ಆದರೆ (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = ಮೌಲ್ಯ;
		ಆಗ (*cp != '\0' && vp < ಮೌಲ್ಯ + ಗಾತ್ರ(ಮೌಲ್ಯ) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		ಆದರೆ (*cp == ']') {
			*vp = '\0';
			ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
		} ಇಲ್ಲದಿದ್ದರೆ {
			flexerror(_("unterminated or too long property value"));
		}
	}
	ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
ಶೂನ್ಯ skelout (bool announce)
{
	ಅಕ್ಷರ    buf_storage[MAXLINE];
	ಅಕ್ಷರ   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	ಆಗ (env.skelfile != ಖಾಲಿ ?
	       (fgets (buf, MAXLINE, env.skelfile) != ಖಾಲಿ) :
	       ((buf = (ಅಕ್ಷರ *) backend->skel[skel_ind++]) != 0)) {

		ಆದರೆ (env.skelfile != ಖಾಲಿ)
			chomp (buf);

		/* copy from skel array */
		ಆದರೆ (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			ಆದರೆ (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			ಆದರೆ (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (buf[1] == '%') {
				/* %% is a break point for skelout() */
				ಆದರೆ (announce) {
					comment(buf);
					outc ('\n');
				}
				ಹಿಂತಿರುಗಿ;
			}
			ಇಲ್ಲದಿದ್ದರೆ {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (do_copy) 
			outn (buf);
	}			/* end while */
}


/*ಕೊನೆ*/
