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


#અન્તર્ભાવ "flexdef.h"
#અન્તર્ભાવ "tables.h"

/* START digested skeletons */

અચલ અક્ષર *cpp_skel[] = {
#અન્તર્ભાવ "cpp-flex.h"
    0,
};

અચલ અક્ષર *c99_skel[] = {
#અન્તર્ભાવ "c99-flex.h"
    0,
};

અચલ અક્ષર *go_skel[] = {
#અન્તર્ભાવ "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
સંરચના flex_backend_t {
	અચલ અક્ષર **skel;		// Digested skeleton file
};

સ્થિર સંરચના flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {ખાલી}
};

સ્થિર સંરચના flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(શૂન્ય)
{
    પાછા backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
સ્થિર bool boneseeker(અચલ અક્ષર *bone)
{
	પૂર્ણાંક i;

	માટે (i = 0; backend->skel[i] != ખાલી; i++) {
		અચલ અક્ષર *લીટી = backend->skel[i];
		જો (strstr(લીટી, bone) != ખાલી)
			પાછા true;
		નહીંતર જો (strncmp(લીટી, "%%", 2) == 0)
			તોડો;
	}
	પાછા false;
}

શૂન્ય backend_by_name(અચલ અક્ષર *name)
{
	અચલ અક્ષર *prefix_property;
	જો (name != ખાલી) {
		જો (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			જાઓ backend_ok;
		}
		જો (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			જાઓ backend_ok;
		}
		માટે (backend = &backends[0]; backend->skel != ખાલી; backend++) {
			જો (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				જાઓ backend_ok;
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
	જો (prefix_property != ખાલી)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

અચલ અક્ષર *suffix (શૂન્ય)
{
	અચલ અક્ષર   *suffix;

	જો (is_default_backend()) {
		જો (ctrl.C_plus_plus)
			suffix = "cc";
		નહીંતર
			suffix = "c";
	} નહીંતર {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	પાછા suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
અચલ અક્ષર *skel_property(અચલ અક્ષર *propname)
{
	પૂર્ણાંક i;
	સ્થિર અક્ષર name[256], કિંમત[256], *np, *vp;;
	અચલ અક્ષર *cp;

	માટે (i = 0; backend->skel[i] != ખાલી; i++) {
		અચલ અક્ષર *લીટી = backend->skel[i];
		જો (લીટી[0] == '\0')
			ચાલુ;
		/* only scan before first skell breakpoint */
		જો (strncmp(લીટી, "%%", 2) == 0)
			તોડો;
		/* ignore anything that's not a definition */
		જો (strncmp(લીટી, "m4_define(", 10) != 0)
			ચાલુ;
		/* skip space and quotes before macro name */
		માટે (cp = લીટી + 10; isspace(*cp) || *cp == '['; *cp++)
			ચાલુ;
		/* copy up to following ] into the name buffer */
		np = name;
		જ્યારે (*cp != ']' && *cp != '\0' && (np < name + કદ(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		જો (*cp == ']') {
			જો (strcmp(name, propname) != 0)
				ચાલુ; /* try next line */
		} નહીંતર {
			flexerror(_("unterminated or too long property name"));
			ચાલુ;
		}
		/* skip to the property value */
		જ્યારે (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		જ્યારે (*cp == '[')
			cp++;
		જો (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = કિંમત;
		જ્યારે (*cp != '\0' && vp < કિંમત + કદ(કિંમત) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		જો (*cp == ']') {
			*vp = '\0';
			પાછા કિંમત;
		} નહીંતર {
			flexerror(_("unterminated or too long property value"));
		}
	}
	પાછા ખાલી;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
શૂન્ય skelout (bool announce)
{
	અક્ષર    buf_storage[MAXLINE];
	અક્ષર   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	જ્યારે (env.skelfile != ખાલી ?
	       (fgets (buf, MAXLINE, env.skelfile) != ખાલી) :
	       ((buf = (અક્ષર *) backend->skel[skel_ind++]) != 0)) {

		જો (env.skelfile != ખાલી)
			chomp (buf);

		/* copy from skel array */
		જો (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			જો (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			જો (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			નહીંતર જો (buf[1] == '%') {
				/* %% is a break point for skelout() */
				જો (announce) {
					comment(buf);
					outc ('\n');
				}
				પાછા;
			}
			નહીંતર {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		નહીંતર જો (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
