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


#ଅନ୍ତର୍ଭାଵ "flexdef.h"
#ଅନ୍ତର୍ଭାଵ "tables.h"

/* START digested skeletons */

ଅଚଳ ଅକ୍ଷର *cpp_skel[] = {
#ଅନ୍ତର୍ଭାଵ "cpp-flex.h"
    0,
};

ଅଚଳ ଅକ୍ଷର *c99_skel[] = {
#ଅନ୍ତର୍ଭାଵ "c99-flex.h"
    0,
};

ଅଚଳ ଅକ୍ଷର *go_skel[] = {
#ଅନ୍ତର୍ଭାଵ "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
ସଂରଚନା flex_backend_t {
	ଅଚଳ ଅକ୍ଷର **skel;		// Digested skeleton file
};

ସ୍ଥିର ସଂରଚନା flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {ଖାଲି}
};

ସ୍ଥିର ସଂରଚନା flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
ସ୍ଥିର bool boneseeker(ଅଚଳ ଅକ୍ଷର *bone)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

	ପାଇଁ (i = 0; backend->skel[i] != ଖାଲି; i++) {
		ଅଚଳ ଅକ୍ଷର *ଧାଡ଼ି = backend->skel[i];
		ଯଦି (strstr(ଧାଡ଼ି, bone) != ଖାଲି)
			ଫେରନ୍ତୁ true;
		ଅନ୍ୟଥା ଯଦି (strncmp(ଧାଡ଼ି, "%%", 2) == 0)
			ଭାଙ୍ଗ;
	}
	ଫେରନ୍ତୁ false;
}

ଶୂନ୍ୟ backend_by_name(ଅଚଳ ଅକ୍ଷର *name)
{
	ଅଚଳ ଅକ୍ଷର *prefix_property;
	ଯଦି (name != ଖାଲି) {
		ଯଦି (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			ଯାଅ backend_ok;
		}
		ଯଦି (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			ଯାଅ backend_ok;
		}
		ପାଇଁ (backend = &backends[0]; backend->skel != ଖାଲି; backend++) {
			ଯଦି (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				ଯାଅ backend_ok;
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
	ଯଦି (prefix_property != ଖାଲି)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

ଅଚଳ ଅକ୍ଷର *suffix (ଶୂନ୍ୟ)
{
	ଅଚଳ ଅକ୍ଷର   *suffix;

	ଯଦି (is_default_backend()) {
		ଯଦି (ctrl.C_plus_plus)
			suffix = "cc";
		ଅନ୍ୟଥା
			suffix = "c";
	} ଅନ୍ୟଥା {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	ଫେରନ୍ତୁ suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
ଅଚଳ ଅକ୍ଷର *skel_property(ଅଚଳ ଅକ୍ଷର *propname)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
	ସ୍ଥିର ଅକ୍ଷର name[256], ମୂଲ୍ୟ[256], *np, *vp;;
	ଅଚଳ ଅକ୍ଷର *cp;

	ପାଇଁ (i = 0; backend->skel[i] != ଖାଲି; i++) {
		ଅଚଳ ଅକ୍ଷର *ଧାଡ଼ି = backend->skel[i];
		ଯଦି (ଧାଡ଼ି[0] == '\0')
			ଜାରି;
		/* only scan before first skell breakpoint */
		ଯଦି (strncmp(ଧାଡ଼ି, "%%", 2) == 0)
			ଭାଙ୍ଗ;
		/* ignore anything that's not a definition */
		ଯଦି (strncmp(ଧାଡ଼ି, "m4_define(", 10) != 0)
			ଜାରି;
		/* skip space and quotes before macro name */
		ପାଇଁ (cp = ଧାଡ଼ି + 10; isspace(*cp) || *cp == '['; *cp++)
			ଜାରି;
		/* copy up to following ] into the name buffer */
		np = name;
		ଯେତେବେଳେ (*cp != ']' && *cp != '\0' && (np < name + ଆକାର(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		ଯଦି (*cp == ']') {
			ଯଦି (strcmp(name, propname) != 0)
				ଜାରି; /* try next line */
		} ଅନ୍ୟଥା {
			flexerror(_("unterminated or too long property name"));
			ଜାରି;
		}
		/* skip to the property value */
		ଯେତେବେଳେ (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		ଯେତେବେଳେ (*cp == '[')
			cp++;
		ଯଦି (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = ମୂଲ୍ୟ;
		ଯେତେବେଳେ (*cp != '\0' && vp < ମୂଲ୍ୟ + ଆକାର(ମୂଲ୍ୟ) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		ଯଦି (*cp == ']') {
			*vp = '\0';
			ଫେରନ୍ତୁ ମୂଲ୍ୟ;
		} ଅନ୍ୟଥା {
			flexerror(_("unterminated or too long property value"));
		}
	}
	ଫେରନ୍ତୁ ଖାଲି;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
ଶୂନ୍ୟ skelout (bool announce)
{
	ଅକ୍ଷର    buf_storage[MAXLINE];
	ଅକ୍ଷର   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	ଯେତେବେଳେ (env.skelfile != ଖାଲି ?
	       (fgets (buf, MAXLINE, env.skelfile) != ଖାଲି) :
	       ((buf = (ଅକ୍ଷର *) backend->skel[skel_ind++]) != 0)) {

		ଯଦି (env.skelfile != ଖାଲି)
			chomp (buf);

		/* copy from skel array */
		ଯଦି (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			ଯଦି (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			ଯଦି (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			ଅନ୍ୟଥା ଯଦି (buf[1] == '%') {
				/* %% is a break point for skelout() */
				ଯଦି (announce) {
					comment(buf);
					outc ('\n');
				}
				ଫେରନ୍ତୁ;
			}
			ଅନ୍ୟଥା {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		ଅନ୍ୟଥା ଯଦି (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
