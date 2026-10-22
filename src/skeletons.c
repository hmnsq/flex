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


#अन्तर्भाव "flexdef.h"
#अन्तर्भाव "tables.h"

/* START digested skeletons */

ध्रुव वर्ण *cpp_skel[] = {
#अन्तर्भाव "cpp-flex.h"
    0,
};

ध्रुव वर्ण *c99_skel[] = {
#अन्तर्भाव "c99-flex.h"
    0,
};

ध्रुव वर्ण *go_skel[] = {
#अन्तर्भाव "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
संरचना flex_backend_t {
	ध्रुव वर्ण **skel;		// Digested skeleton file
};

स्थिर संरचना flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {रिक्त}
};

स्थिर संरचना flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(शून्य)
{
    पटिनिवत्त backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
स्थिर bool boneseeker(ध्रुव वर्ण *bone)
{
	पूर्णाङ्क i;

	अत्थाय (i = 0; backend->skel[i] != रिक्त; i++) {
		ध्रुव वर्ण *पङ्क्तिः = backend->skel[i];
		सचे (strstr(पङ्क्तिः, bone) != रिक्त)
			पटिनिवत्त true;
		अञ्ञथा सचे (strncmp(पङ्क्तिः, "%%", 2) == 0)
			भङ्ग;
	}
	पटिनिवत्त false;
}

शून्य backend_by_name(ध्रुव वर्ण *name)
{
	ध्रुव वर्ण *prefix_property;
	सचे (name != रिक्त) {
		सचे (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			गच्छ backend_ok;
		}
		सचे (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			गच्छ backend_ok;
		}
		अत्थाय (backend = &backends[0]; backend->skel != रिक्त; backend++) {
			सचे (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				गच्छ backend_ok;
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
	सचे (prefix_property != रिक्त)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

ध्रुव वर्ण *suffix (शून्य)
{
	ध्रुव वर्ण   *suffix;

	सचे (is_default_backend()) {
		सचे (ctrl.C_plus_plus)
			suffix = "cc";
		अञ्ञथा
			suffix = "c";
	} अञ्ञथा {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	पटिनिवत्त suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
ध्रुव वर्ण *skel_property(ध्रुव वर्ण *propname)
{
	पूर्णाङ्क i;
	स्थिर वर्ण name[256], मानम्[256], *np, *vp;;
	ध्रुव वर्ण *cp;

	अत्थाय (i = 0; backend->skel[i] != रिक्त; i++) {
		ध्रुव वर्ण *पङ्क्तिः = backend->skel[i];
		सचे (पङ्क्तिः[0] == '\0')
			अनुवर्त;
		/* only scan before first skell breakpoint */
		सचे (strncmp(पङ्क्तिः, "%%", 2) == 0)
			भङ्ग;
		/* ignore anything that's not a definition */
		सचे (strncmp(पङ्क्तिः, "m4_define(", 10) != 0)
			अनुवर्त;
		/* skip space and quotes before macro name */
		अत्थाय (cp = पङ्क्तिः + 10; isspace(*cp) || *cp == '['; *cp++)
			अनुवर्त;
		/* copy up to following ] into the name buffer */
		np = name;
		याव (*cp != ']' && *cp != '\0' && (np < name + परिमाण(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		सचे (*cp == ']') {
			सचे (strcmp(name, propname) != 0)
				अनुवर्त; /* try next line */
		} अञ्ञथा {
			flexerror(_("unterminated or too long property name"));
			अनुवर्त;
		}
		/* skip to the property value */
		याव (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		याव (*cp == '[')
			cp++;
		सचे (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = मानम्;
		याव (*cp != '\0' && vp < मानम् + परिमाण(मानम्) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		सचे (*cp == ']') {
			*vp = '\0';
			पटिनिवत्त मानम्;
		} अञ्ञथा {
			flexerror(_("unterminated or too long property value"));
		}
	}
	पटिनिवत्त रिक्त;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
शून्य skelout (bool announce)
{
	वर्ण    buf_storage[MAXLINE];
	वर्ण   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	याव (env.skelfile != रिक्त ?
	       (fgets (buf, MAXLINE, env.skelfile) != रिक्त) :
	       ((buf = (वर्ण *) backend->skel[skel_ind++]) != 0)) {

		सचे (env.skelfile != रिक्त)
			chomp (buf);

		/* copy from skel array */
		सचे (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			सचे (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			सचे (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			अञ्ञथा सचे (buf[1] == '%') {
				/* %% is a break point for skelout() */
				सचे (announce) {
					comment(buf);
					outc ('\n');
				}
				पटिनिवत्त;
			}
			अञ्ञथा {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		अञ्ञथा सचे (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
