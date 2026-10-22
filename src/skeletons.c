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

स्थिरांक अक्षर *cpp_skel[] = {
#अन्तर्भाव "cpp-flex.h"
    0,
};

स्थिरांक अक्षर *c99_skel[] = {
#अन्तर्भाव "c99-flex.h"
    0,
};

स्थिरांक अक्षर *go_skel[] = {
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
	स्थिरांक अक्षर **skel;		// Digested skeleton file
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
    परत backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
स्थिर bool boneseeker(स्थिरांक अक्षर *bone)
{
	पूर्णांक i;

	साठी (i = 0; backend->skel[i] != रिक्त; i++) {
		स्थिरांक अक्षर *ओळ = backend->skel[i];
		जर (म_माला(ओळ, bone) != रिक्त)
			परत true;
		अन्यथा जर (म_भेदन(ओळ, "%%", 2) == 0)
			थांबा;
	}
	परत false;
}

शून्य backend_by_name(स्थिरांक अक्षर *name)
{
	स्थिरांक अक्षर *prefix_property;
	जर (name != रिक्त) {
		जर (म_भेद(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			जा backend_ok;
		}
		जर (म_भेद(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			जा backend_ok;
		}
		साठी (backend = &backends[0]; backend->skel != रिक्त; backend++) {
			जर (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				जा backend_ok;
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
	जर (prefix_property != रिक्त)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

स्थिरांक अक्षर *suffix (शून्य)
{
	स्थिरांक अक्षर   *suffix;

	जर (is_default_backend()) {
		जर (ctrl.C_plus_plus)
			suffix = "cc";
		अन्यथा
			suffix = "c";
	} अन्यथा {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	परत suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
स्थिरांक अक्षर *skel_property(स्थिरांक अक्षर *propname)
{
	पूर्णांक i;
	स्थिर अक्षर name[256], मूल्य[256], *np, *vp;;
	स्थिरांक अक्षर *cp;

	साठी (i = 0; backend->skel[i] != रिक्त; i++) {
		स्थिरांक अक्षर *ओळ = backend->skel[i];
		जर (ओळ[0] == '\0')
			सुरूठेवा;
		/* only scan before first skell breakpoint */
		जर (म_भेदन(ओळ, "%%", 2) == 0)
			थांबा;
		/* ignore anything that's not a definition */
		जर (म_भेदन(ओळ, "m4_define(", 10) != 0)
			सुरूठेवा;
		/* skip space and quotes before macro name */
		साठी (cp = ओळ + 10; है_खाली(*cp) || *cp == '['; *cp++)
			सुरूठेवा;
		/* copy up to following ] into the name buffer */
		np = name;
		पर्यंत (*cp != ']' && *cp != '\0' && (np < name + आकार(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		जर (*cp == ']') {
			जर (म_भेद(name, propname) != 0)
				सुरूठेवा; /* try next line */
		} अन्यथा {
			flexerror(_("unterminated or too long property name"));
			सुरूठेवा;
		}
		/* skip to the property value */
		पर्यंत (*cp != '\0' && (*cp == ']' || है_खाली(*cp) || *cp == ','))
			cp++;
		पर्यंत (*cp == '[')
			cp++;
		जर (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = मूल्य;
		पर्यंत (*cp != '\0' && vp < मूल्य + आकार(मूल्य) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		जर (*cp == ']') {
			*vp = '\0';
			परत मूल्य;
		} अन्यथा {
			flexerror(_("unterminated or too long property value"));
		}
	}
	परत रिक्त;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
शून्य skelout (bool announce)
{
	अक्षर    buf_storage[MAXLINE];
	अक्षर   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	पर्यंत (env.skelfile != रिक्त ?
	       (ख_माला_लो (buf, MAXLINE, env.skelfile) != रिक्त) :
	       ((buf = (अक्षर *) backend->skel[skel_ind++]) != 0)) {

		जर (env.skelfile != रिक्त)
			chomp (buf);

		/* copy from skel array */
		जर (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			जर (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			जर (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			अन्यथा जर (buf[1] == '%') {
				/* %% is a break point for skelout() */
				जर (announce) {
					comment(buf);
					outc ('\n');
				}
				परत;
			}
			अन्यथा {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		अन्यथा जर (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
