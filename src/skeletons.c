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


#అన్తర్భావ "flexdef.h"
#అన్తర్భావ "tables.h"

/* START digested skeletons */

స్థిరరాశి అక్షరం *cpp_skel[] = {
#అన్తర్భావ "cpp-flex.h"
    0,
};

స్థిరరాశి అక్షరం *c99_skel[] = {
#అన్తర్భావ "c99-flex.h"
    0,
};

స్థిరరాశి అక్షరం *go_skel[] = {
#అన్తర్భావ "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
నిర్మాణం flex_backend_t {
	స్థిరరాశి అక్షరం **skel;		// Digested skeleton file
};

స్థిర నిర్మాణం flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {ఖాళీ}
};

స్థిర నిర్మాణం flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(శూన్య)
{
    తిరిగి backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
స్థిర bool boneseeker(స్థిరరాశి అక్షరం *bone)
{
	పూర్ణాంకం i;

	కొరకు (i = 0; backend->skel[i] != ఖాళీ; i++) {
		స్థిరరాశి అక్షరం *పంక్తి = backend->skel[i];
		ఒకవేళ (అక్షరశ్రేణి_శోధన(పంక్తి, bone) != ఖాళీ)
			తిరిగి true;
		లేకపోతే ఒకవేళ (అక్షరశ్రేణి_పోలిక(పంక్తి, "%%", 2) == 0)
			ఆపు;
	}
	తిరిగి false;
}

శూన్య backend_by_name(స్థిరరాశి అక్షరం *name)
{
	స్థిరరాశి అక్షరం *ఉపసర్గ_property;
	ఒకవేళ (name != ఖాళీ) {
		ఒకవేళ (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			వెళ్ళు backend_ok;
		}
		ఒకవేళ (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			వెళ్ళు backend_ok;
		}
		కొరకు (backend = &backends[0]; backend->skel != ఖాళీ; backend++) {
			ఒకవేళ (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				వెళ్ళు backend_ok;
		}
		flexerror(_("no such back end"));
	}
  backend_ok:
	ctrl.rewrite = !is_default_backend();
	ctrl.backend_name = xstrdup(skel_property("M4_PROPERTY_BACKEND_NAME"));
	ctrl.traceline_re = xstrdup(skel_property("M4_PROPERTY_TRACE_LINE_REGEXP"));
	ctrl.traceline_template = xstrdup(skel_property("M4_PROPERTY_TRACE_LINE_TEMPLATE"));
	ctrl.have_state_నమోదు_format = boneseeker("m4_define([[M4_HOOK_STATE_ENTRY_FORMAT]]");
	ఉపసర్గ_property = skel_property("M4_PROPERTY_PREFIX");
	ఒకవేళ (ఉపసర్గ_property != ఖాళీ)
		ctrl.ఉపసర్గ = xstrdup(ఉపసర్గ_property);
	flex_init_regex(ctrl.traceline_re);
}

స్థిరరాశి అక్షరం *suffix (శూన్య)
{
	స్థిరరాశి అక్షరం   *suffix;

	ఒకవేళ (is_default_backend()) {
		ఒకవేళ (ctrl.C_plus_plus)
			suffix = "cc";
		లేకపోతే
			suffix = "c";
	} లేకపోతే {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	తిరిగి suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
స్థిరరాశి అక్షరం *skel_property(స్థిరరాశి అక్షరం *propname)
{
	పూర్ణాంకం i;
	స్థిర అక్షరం name[256], విలువ[256], *np, *vp;;
	స్థిరరాశి అక్షరం *cp;

	కొరకు (i = 0; backend->skel[i] != ఖాళీ; i++) {
		స్థిరరాశి అక్షరం *పంక్తి = backend->skel[i];
		ఒకవేళ (పంక్తి[0] == '\0')
			కొనసాగు;
		/* only scan before first skell breakpoint */
		ఒకవేళ (అక్షరశ్రేణి_పోలిక(పంక్తి, "%%", 2) == 0)
			ఆపు;
		/* ignore anything that's not a definition */
		ఒకవేళ (అక్షరశ్రేణి_పోలిక(పంక్తి, "m4_define(", 10) != 0)
			కొనసాగు;
		/* skip space and quotes before macro name */
		కొరకు (cp = పంక్తి + 10; ఖాళీనా(*cp) || *cp == '['; *cp++)
			కొనసాగు;
		/* copy up to following ] into the name buffer */
		np = name;
		అయితే (*cp != ']' && *cp != '\0' && (np < name + పరిమాణం(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		ఒకవేళ (*cp == ']') {
			ఒకవేళ (strcmp(name, propname) != 0)
				కొనసాగు; /* try next line */
		} లేకపోతే {
			flexerror(_("unterminated or too long property name"));
			కొనసాగు;
		}
		/* skip to the property value */
		అయితే (*cp != '\0' && (*cp == ']' || ఖాళీనా(*cp) || *cp == ','))
			cp++;
		అయితే (*cp == '[')
			cp++;
		ఒకవేళ (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = విలువ;
		అయితే (*cp != '\0' && vp < విలువ + పరిమాణం(విలువ) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		ఒకవేళ (*cp == ']') {
			*vp = '\0';
			తిరిగి విలువ;
		} లేకపోతే {
			flexerror(_("unterminated or too long property value"));
		}
	}
	తిరిగి ఖాళీ;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
శూన్య skelout (bool announce)
{
	అక్షరం    buf_storage[MAXLINE];
	అక్షరం   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	అయితే (env.skelfile != ఖాళీ ?
	       (fgets (buf, MAXLINE, env.skelfile) != ఖాళీ) :
	       ((buf = (అక్షరం *) backend->skel[skel_ind++]) != 0)) {

		ఒకవేళ (env.skelfile != ఖాళీ)
			chomp (buf);

		/* copy from skel array */
		ఒకవేళ (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			ఒకవేళ (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			ఒకవేళ (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			లేకపోతే ఒకవేళ (buf[1] == '%') {
				/* %% is a break point for skelout() */
				ఒకవేళ (announce) {
					comment(buf);
					outc ('\n');
				}
				తిరిగి;
			}
			లేకపోతే {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		లేకపోతే ఒకవేళ (do_copy) 
			outn (buf);
	}			/* end while */
}


/*చివర*/
