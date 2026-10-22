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

अचर वर्ण *cpp_skel[] = {
#अन्तर्भाव "cpp-flex.h"
    0,
};

अचर वर्ण *c99_skel[] = {
#अन्तर्भाव "c99-flex.h"
    0,
};

अचर वर्ण *go_skel[] = {
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
	अचर वर्ण **skel;		// Digested skeleton file
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
    फर्काऊ backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
स्थिर bool boneseeker(अचर वर्ण *bone)
{
	पूर्णाङ्क i;

	लागि (i = 0; backend->skel[i] != रिक्त; i++) {
		अचर वर्ण *पङ्क्ति = backend->skel[i];
		यदि (म_माला(पङ्क्ति, bone) != रिक्त)
			फर्काऊ true;
		अन्यथा यदि (म_भेदन(पङ्क्ति, "%%", 2) == 0)
			रोक;
	}
	फर्काऊ false;
}

शून्य backend_by_name(अचर वर्ण *name)
{
	अचर वर्ण *prefix_property;
	यदि (name != रिक्त) {
		यदि (म_भेद(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			गच्छ backend_ok;
		}
		यदि (म_भेद(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			गच्छ backend_ok;
		}
		लागि (backend = &backends[0]; backend->skel != रिक्त; backend++) {
			यदि (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
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
	यदि (prefix_property != रिक्त)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

अचर वर्ण *suffix (शून्य)
{
	अचर वर्ण   *suffix;

	यदि (is_default_backend()) {
		यदि (ctrl.C_plus_plus)
			suffix = "cc";
		अन्यथा
			suffix = "c";
	} अन्यथा {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	फर्काऊ suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
अचर वर्ण *skel_property(अचर वर्ण *propname)
{
	पूर्णाङ्क i;
	स्थिर वर्ण name[256], मान[256], *np, *vp;;
	अचर वर्ण *cp;

	लागि (i = 0; backend->skel[i] != रिक्त; i++) {
		अचर वर्ण *पङ्क्ति = backend->skel[i];
		यदि (पङ्क्ति[0] == '\0')
			जारी;
		/* only scan before first skell breakpoint */
		यदि (म_भेदन(पङ्क्ति, "%%", 2) == 0)
			रोक;
		/* ignore anything that's not a definition */
		यदि (म_भेदन(पङ्क्ति, "m4_define(", 10) != 0)
			जारी;
		/* skip space and quotes before macro name */
		लागि (cp = पङ्क्ति + 10; है_खाली(*cp) || *cp == '['; *cp++)
			जारी;
		/* copy up to following ] into the name buffer */
		np = name;
		जबसम्म (*cp != ']' && *cp != '\0' && (np < name + परिमाण(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		यदि (*cp == ']') {
			यदि (म_भेद(name, propname) != 0)
				जारी; /* try next line */
		} अन्यथा {
			flexerror(_("unterminated or too long property name"));
			जारी;
		}
		/* skip to the property value */
		जबसम्म (*cp != '\0' && (*cp == ']' || है_खाली(*cp) || *cp == ','))
			cp++;
		जबसम्म (*cp == '[')
			cp++;
		यदि (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = मान;
		जबसम्म (*cp != '\0' && vp < मान + परिमाण(मान) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		यदि (*cp == ']') {
			*vp = '\0';
			फर्काऊ मान;
		} अन्यथा {
			flexerror(_("unterminated or too long property value"));
		}
	}
	फर्काऊ रिक्त;
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
	जबसम्म (env.skelfile != रिक्त ?
	       (ख_माला_लो (buf, MAXLINE, env.skelfile) != रिक्त) :
	       ((buf = (वर्ण *) backend->skel[skel_ind++]) != 0)) {

		यदि (env.skelfile != रिक्त)
			chomp (buf);

		/* copy from skel array */
		यदि (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			यदि (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			यदि (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			अन्यथा यदि (buf[1] == '%') {
				/* %% is a break point for skelout() */
				यदि (announce) {
					comment(buf);
					outc ('\n');
				}
				फर्काऊ;
			}
			अन्यथा {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		अन्यथा यदि (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
