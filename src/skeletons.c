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


#समावेश "flexdef.h"
#समावेश "tables.h"

/* START digested skeletons */

स्थिर अक्षर *cpp_skel[] = {
#समावेश "cpp-flex.h"
    0,
};

स्थिर अक्षर *c99_skel[] = {
#समावेश "c99-flex.h"
    0,
};

स्थिर अक्षर *go_skel[] = {
#समावेश "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
काष्ठा flex_backend_t {
	स्थिर अक्षर **skel;		// Digested skeleton file
};

अटल काष्ठा flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {शून्य}
};

अटल काष्ठा flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(व्योम)
{
    वापस backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
अटल bool boneseeker(स्थिर अक्षर *bone)
{
	पूर्णांक i;

	क्रम (i = 0; backend->skel[i] != शून्य; i++) {
		स्थिर अक्षर *पंक्ति = backend->skel[i];
		अगर (म_माला(पंक्ति, bone) != शून्य)
			वापस true;
		अन्यथा अगर (म_भेदन(पंक्ति, "%%", 2) == 0)
			अवरोध;
	}
	वापस false;
}

व्योम backend_by_name(स्थिर अक्षर *name)
{
	स्थिर अक्षर *prefix_property;
	अगर (name != शून्य) {
		अगर (म_भेद(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			जाओ backend_ok;
		}
		अगर (म_भेद(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			जाओ backend_ok;
		}
		क्रम (backend = &backends[0]; backend->skel != शून्य; backend++) {
			अगर (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				जाओ backend_ok;
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
	अगर (prefix_property != शून्य)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

स्थिर अक्षर *suffix (व्योम)
{
	स्थिर अक्षर   *suffix;

	अगर (is_default_backend()) {
		अगर (ctrl.C_plus_plus)
			suffix = "cc";
		अन्यथा
			suffix = "c";
	} अन्यथा {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	वापस suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
स्थिर अक्षर *skel_property(स्थिर अक्षर *propname)
{
	पूर्णांक i;
	अटल अक्षर name[256], मूल्य[256], *np, *vp;;
	स्थिर अक्षर *cp;

	क्रम (i = 0; backend->skel[i] != शून्य; i++) {
		स्थिर अक्षर *पंक्ति = backend->skel[i];
		अगर (पंक्ति[0] == '\0')
			जारी;
		/* only scan before first skell breakpoint */
		अगर (म_भेदन(पंक्ति, "%%", 2) == 0)
			अवरोध;
		/* ignore anything that's not a definition */
		अगर (म_भेदन(पंक्ति, "m4_define(", 10) != 0)
			जारी;
		/* skip space and quotes before macro name */
		क्रम (cp = पंक्ति + 10; है_खाली(*cp) || *cp == '['; *cp++)
			जारी;
		/* copy up to following ] into the name buffer */
		np = name;
		जबतक (*cp != ']' && *cp != '\0' && (np < name + माप(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		अगर (*cp == ']') {
			अगर (म_भेद(name, propname) != 0)
				जारी; /* try next line */
		} अन्यथा {
			flexerror(_("unterminated or too long property name"));
			जारी;
		}
		/* skip to the property value */
		जबतक (*cp != '\0' && (*cp == ']' || है_खाली(*cp) || *cp == ','))
			cp++;
		जबतक (*cp == '[')
			cp++;
		अगर (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = मूल्य;
		जबतक (*cp != '\0' && vp < मूल्य + माप(मूल्य) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		अगर (*cp == ']') {
			*vp = '\0';
			वापस मूल्य;
		} अन्यथा {
			flexerror(_("unterminated or too long property value"));
		}
	}
	वापस शून्य;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
व्योम skelout (bool announce)
{
	अक्षर    buf_storage[MAXLINE];
	अक्षर   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	जबतक (env.skelfile != शून्य ?
	       (ख_माला_लो (buf, MAXLINE, env.skelfile) != शून्य) :
	       ((buf = (अक्षर *) backend->skel[skel_ind++]) != 0)) {

		अगर (env.skelfile != शून्य)
			chomp (buf);

		/* copy from skel array */
		अगर (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			अगर (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			अगर (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			अन्यथा अगर (buf[1] == '%') {
				/* %% is a break point for skelout() */
				अगर (announce) {
					comment(buf);
					outc ('\n');
				}
				वापस;
			}
			अन्यथा {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		अन्यथा अगर (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
