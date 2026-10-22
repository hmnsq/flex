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


#ضمن "flexdef.h"
#ضمن "tables.h"

/* START digested skeletons */

ثابت حرف *cpp_skel[] = {
#ضمن "cpp-flex.h"
    0,
};

ثابت حرف *c99_skel[] = {
#ضمن "c99-flex.h"
    0,
};

ثابت حرف *go_skel[] = {
#ضمن "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
بنية flex_backend_t {
	ثابت حرف **skel;		// Digested skeleton file
};

ساكن بنية flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {عدم}
};

ساكن بنية flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(فراغ)
{
    إرجاع backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
ساكن bool boneseeker(ثابت حرف *bone)
{
	صحيح i;

	لكل (i = 0; backend->skel[i] != عدم; i++) {
		ثابت حرف *سطر = backend->skel[i];
		إذا (strstr(سطر, bone) != عدم)
			إرجاع true;
		وإلا إذا (strncmp(سطر, "%%", 2) == 0)
			اكسر;
	}
	إرجاع false;
}

فراغ backend_by_name(ثابت حرف *name)
{
	ثابت حرف *prefix_property;
	إذا (name != عدم) {
		إذا (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			اذهب backend_ok;
		}
		إذا (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			اذهب backend_ok;
		}
		لكل (backend = &backends[0]; backend->skel != عدم; backend++) {
			إذا (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				اذهب backend_ok;
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
	إذا (prefix_property != عدم)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

ثابت حرف *suffix (فراغ)
{
	ثابت حرف   *suffix;

	إذا (is_default_backend()) {
		إذا (ctrl.C_plus_plus)
			suffix = "cc";
		وإلا
			suffix = "c";
	} وإلا {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	إرجاع suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
ثابت حرف *skel_property(ثابت حرف *propname)
{
	صحيح i;
	ساكن حرف name[256], قيمة[256], *np, *vp;;
	ثابت حرف *cp;

	لكل (i = 0; backend->skel[i] != عدم; i++) {
		ثابت حرف *سطر = backend->skel[i];
		إذا (سطر[0] == '\0')
			استمر;
		/* only scan before first skell breakpoint */
		إذا (strncmp(سطر, "%%", 2) == 0)
			اكسر;
		/* ignore anything that's not a definition */
		إذا (strncmp(سطر, "m4_define(", 10) != 0)
			استمر;
		/* skip space and quotes before macro name */
		لكل (cp = سطر + 10; isspace(*cp) || *cp == '['; *cp++)
			استمر;
		/* copy up to following ] into the name buffer */
		np = name;
		بينما (*cp != ']' && *cp != '\0' && (np < name + حجم(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		إذا (*cp == ']') {
			إذا (strcmp(name, propname) != 0)
				استمر; /* try next line */
		} وإلا {
			flexerror(_("unterminated or too long property name"));
			استمر;
		}
		/* skip to the property value */
		بينما (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		بينما (*cp == '[')
			cp++;
		إذا (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = قيمة;
		بينما (*cp != '\0' && vp < قيمة + حجم(قيمة) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		إذا (*cp == ']') {
			*vp = '\0';
			إرجاع قيمة;
		} وإلا {
			flexerror(_("unterminated or too long property value"));
		}
	}
	إرجاع عدم;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
فراغ skelout (bool announce)
{
	حرف    buf_storage[MAXLINE];
	حرف   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	بينما (env.skelfile != عدم ?
	       (fgets (buf, MAXLINE, env.skelfile) != عدم) :
	       ((buf = (حرف *) backend->skel[skel_ind++]) != 0)) {

		إذا (env.skelfile != عدم)
			chomp (buf);

		/* copy from skel array */
		إذا (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			إذا (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			إذا (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			وإلا إذا (buf[1] == '%') {
				/* %% is a break point for skelout() */
				إذا (announce) {
					comment(buf);
					outc ('\n');
				}
				إرجاع;
			}
			وإلا {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		وإلا إذا (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
