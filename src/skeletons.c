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


#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tables.h"

/* START digested skeletons */

ਅਚਲ ਅੱਖਰ *cpp_skel[] = {
#ਅਨ੍ਤਰ੍ਭਾਵ "cpp-flex.h"
    0,
};

ਅਚਲ ਅੱਖਰ *c99_skel[] = {
#ਅਨ੍ਤਰ੍ਭਾਵ "c99-flex.h"
    0,
};

ਅਚਲ ਅੱਖਰ *go_skel[] = {
#ਅਨ੍ਤਰ੍ਭਾਵ "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
ਬਣਤਰ flex_backend_t {
	ਅਚਲ ਅੱਖਰ **skel;		// Digested skeleton file
};

ਸਥਿਰ ਬਣਤਰ flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {ਨਿਰਾ}
};

ਸਥਿਰ ਬਣਤਰ flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(ਖਾਲੀ)
{
    ਵਾਪਸ backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
ਸਥਿਰ bool boneseeker(ਅਚਲ ਅੱਖਰ *bone)
{
	ਪੂਰਨ i;

	ਲਈ (i = 0; backend->skel[i] != ਨਿਰਾ; i++) {
		ਅਚਲ ਅੱਖਰ *ਸਤਰ = backend->skel[i];
		ਜੇ (ਲੜੀ_ਖੋਜ(ਸਤਰ, bone) != ਨਿਰਾ)
			ਵਾਪਸ true;
		ਨਹੀਂਤਾਂ ਜੇ (ਲੜੀ_ਤੁਲਨਾ(ਸਤਰ, "%%", 2) == 0)
			ਰੋਕੋ;
	}
	ਵਾਪਸ false;
}

ਖਾਲੀ backend_by_name(ਅਚਲ ਅੱਖਰ *name)
{
	ਅਚਲ ਅੱਖਰ *ਅਗੇਤਰ_property;
	ਜੇ (name != ਨਿਰਾ) {
		ਜੇ (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			ਜਾਓ backend_ok;
		}
		ਜੇ (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			ਜਾਓ backend_ok;
		}
		ਲਈ (backend = &backends[0]; backend->skel != ਨਿਰਾ; backend++) {
			ਜੇ (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				ਜਾਓ backend_ok;
		}
		flexerror(_("no such back end"));
	}
  backend_ok:
	ctrl.rewrite = !is_default_backend();
	ctrl.backend_name = xstrdup(skel_property("M4_PROPERTY_BACKEND_NAME"));
	ctrl.traceline_re = xstrdup(skel_property("M4_PROPERTY_TRACE_LINE_REGEXP"));
	ctrl.traceline_template = xstrdup(skel_property("M4_PROPERTY_TRACE_LINE_TEMPLATE"));
	ctrl.have_state_ਇੰਦਰਾਜ_format = boneseeker("m4_define([[M4_HOOK_STATE_ENTRY_FORMAT]]");
	ਅਗੇਤਰ_property = skel_property("M4_PROPERTY_PREFIX");
	ਜੇ (ਅਗੇਤਰ_property != ਨਿਰਾ)
		ctrl.ਅਗੇਤਰ = xstrdup(ਅਗੇਤਰ_property);
	flex_init_regex(ctrl.traceline_re);
}

ਅਚਲ ਅੱਖਰ *suffix (ਖਾਲੀ)
{
	ਅਚਲ ਅੱਖਰ   *suffix;

	ਜੇ (is_default_backend()) {
		ਜੇ (ctrl.C_plus_plus)
			suffix = "cc";
		ਨਹੀਂਤਾਂ
			suffix = "c";
	} ਨਹੀਂਤਾਂ {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	ਵਾਪਸ suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
ਅਚਲ ਅੱਖਰ *skel_property(ਅਚਲ ਅੱਖਰ *propname)
{
	ਪੂਰਨ i;
	ਸਥਿਰ ਅੱਖਰ name[256], ਮੁੱਲ[256], *np, *vp;;
	ਅਚਲ ਅੱਖਰ *cp;

	ਲਈ (i = 0; backend->skel[i] != ਨਿਰਾ; i++) {
		ਅਚਲ ਅੱਖਰ *ਸਤਰ = backend->skel[i];
		ਜੇ (ਸਤਰ[0] == '\0')
			ਜਾਰੀ;
		/* only scan before first skell breakpoint */
		ਜੇ (ਲੜੀ_ਤੁਲਨਾ(ਸਤਰ, "%%", 2) == 0)
			ਰੋਕੋ;
		/* ignore anything that's not a definition */
		ਜੇ (ਲੜੀ_ਤੁਲਨਾ(ਸਤਰ, "m4_define(", 10) != 0)
			ਜਾਰੀ;
		/* skip space and quotes before macro name */
		ਲਈ (cp = ਸਤਰ + 10; ਖਾਲੀ_ਥਾਂ_ਹੈ(*cp) || *cp == '['; *cp++)
			ਜਾਰੀ;
		/* copy up to following ] into the name buffer */
		np = name;
		ਜਦੋਂ (*cp != ']' && *cp != '\0' && (np < name + ਆਕਾਰ(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		ਜੇ (*cp == ']') {
			ਜੇ (strcmp(name, propname) != 0)
				ਜਾਰੀ; /* try next line */
		} ਨਹੀਂਤਾਂ {
			flexerror(_("unterminated or too long property name"));
			ਜਾਰੀ;
		}
		/* skip to the property value */
		ਜਦੋਂ (*cp != '\0' && (*cp == ']' || ਖਾਲੀ_ਥਾਂ_ਹੈ(*cp) || *cp == ','))
			cp++;
		ਜਦੋਂ (*cp == '[')
			cp++;
		ਜੇ (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = ਮੁੱਲ;
		ਜਦੋਂ (*cp != '\0' && vp < ਮੁੱਲ + ਆਕਾਰ(ਮੁੱਲ) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		ਜੇ (*cp == ']') {
			*vp = '\0';
			ਵਾਪਸ ਮੁੱਲ;
		} ਨਹੀਂਤਾਂ {
			flexerror(_("unterminated or too long property value"));
		}
	}
	ਵਾਪਸ ਨਿਰਾ;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
ਖਾਲੀ skelout (bool announce)
{
	ਅੱਖਰ    buf_storage[MAXLINE];
	ਅੱਖਰ   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	ਜਦੋਂ (env.skelfile != ਨਿਰਾ ?
	       (fgets (buf, MAXLINE, env.skelfile) != ਨਿਰਾ) :
	       ((buf = (ਅੱਖਰ *) backend->skel[skel_ind++]) != 0)) {

		ਜੇ (env.skelfile != ਨਿਰਾ)
			chomp (buf);

		/* copy from skel array */
		ਜੇ (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			ਜੇ (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			ਜੇ (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			ਨਹੀਂਤਾਂ ਜੇ (buf[1] == '%') {
				/* %% is a break point for skelout() */
				ਜੇ (announce) {
					comment(buf);
					outc ('\n');
				}
				ਵਾਪਸ;
			}
			ਨਹੀਂਤਾਂ {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		ਨਹੀਂਤਾਂ ਜੇ (do_copy) 
			outn (buf);
	}			/* end while */
}


/*ਸਿਰਾ*/
