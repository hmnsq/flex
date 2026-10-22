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


#அந்தர்பாவ "flexdef.h"
#அந்தர்பாவ "tables.h"

/* START digested skeletons */

மாறிலி எழுத்து *cpp_skel[] = {
#அந்தர்பாவ "cpp-flex.h"
    0,
};

மாறிலி எழுத்து *c99_skel[] = {
#அந்தர்பாவ "c99-flex.h"
    0,
};

மாறிலி எழுத்து *go_skel[] = {
#அந்தர்பாவ "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
கட்டமைப்பு flex_backend_t {
	மாறிலி எழுத்து **skel;		// Digested skeleton file
};

நிலையான கட்டமைப்பு flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {வெற்று}
};

நிலையான கட்டமைப்பு flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(வெறுமை)
{
    திரும்பு backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
நிலையான bool boneseeker(மாறிலி எழுத்து *bone)
{
	முழு i;

	க்கு (i = 0; backend->skel[i] != வெற்று; i++) {
		மாறிலி எழுத்து *வரி = backend->skel[i];
		எனில் (strstr(வரி, bone) != வெற்று)
			திரும்பு true;
		இல்லையெனில் எனில் (strncmp(வரி, "%%", 2) == 0)
			நிறுத்து;
	}
	திரும்பு false;
}

வெறுமை backend_by_name(மாறிலி எழுத்து *name)
{
	மாறிலி எழுத்து *prefix_property;
	எனில் (name != வெற்று) {
		எனில் (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			செல் backend_ok;
		}
		எனில் (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			செல் backend_ok;
		}
		க்கு (backend = &backends[0]; backend->skel != வெற்று; backend++) {
			எனில் (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				செல் backend_ok;
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
	எனில் (prefix_property != வெற்று)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

மாறிலி எழுத்து *suffix (வெறுமை)
{
	மாறிலி எழுத்து   *suffix;

	எனில் (is_default_backend()) {
		எனில் (ctrl.C_plus_plus)
			suffix = "cc";
		இல்லையெனில்
			suffix = "c";
	} இல்லையெனில் {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	திரும்பு suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
மாறிலி எழுத்து *skel_property(மாறிலி எழுத்து *propname)
{
	முழு i;
	நிலையான எழுத்து name[256], மதிப்பு[256], *np, *vp;;
	மாறிலி எழுத்து *cp;

	க்கு (i = 0; backend->skel[i] != வெற்று; i++) {
		மாறிலி எழுத்து *வரி = backend->skel[i];
		எனில் (வரி[0] == '\0')
			தொடர்;
		/* only scan before first skell breakpoint */
		எனில் (strncmp(வரி, "%%", 2) == 0)
			நிறுத்து;
		/* ignore anything that's not a definition */
		எனில் (strncmp(வரி, "m4_define(", 10) != 0)
			தொடர்;
		/* skip space and quotes before macro name */
		க்கு (cp = வரி + 10; isspace(*cp) || *cp == '['; *cp++)
			தொடர்;
		/* copy up to following ] into the name buffer */
		np = name;
		போது (*cp != ']' && *cp != '\0' && (np < name + அளவு(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		எனில் (*cp == ']') {
			எனில் (strcmp(name, propname) != 0)
				தொடர்; /* try next line */
		} இல்லையெனில் {
			flexerror(_("unterminated or too long property name"));
			தொடர்;
		}
		/* skip to the property value */
		போது (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		போது (*cp == '[')
			cp++;
		எனில் (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = மதிப்பு;
		போது (*cp != '\0' && vp < மதிப்பு + அளவு(மதிப்பு) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		எனில் (*cp == ']') {
			*vp = '\0';
			திரும்பு மதிப்பு;
		} இல்லையெனில் {
			flexerror(_("unterminated or too long property value"));
		}
	}
	திரும்பு வெற்று;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
வெறுமை skelout (bool announce)
{
	எழுத்து    buf_storage[MAXLINE];
	எழுத்து   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	போது (env.skelfile != வெற்று ?
	       (fgets (buf, MAXLINE, env.skelfile) != வெற்று) :
	       ((buf = (எழுத்து *) backend->skel[skel_ind++]) != 0)) {

		எனில் (env.skelfile != வெற்று)
			chomp (buf);

		/* copy from skel array */
		எனில் (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			எனில் (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			எனில் (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			இல்லையெனில் எனில் (buf[1] == '%') {
				/* %% is a break point for skelout() */
				எனில் (announce) {
					comment(buf);
					outc ('\n');
				}
				திரும்பு;
			}
			இல்லையெனில் {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		இல்லையெனில் எனில் (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
