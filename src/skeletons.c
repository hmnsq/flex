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


#include "flexdef.h"
#include "tables.h"

/* START digested skeletons */

const char *cpp_skel[] = {
#include "cpp-flex.h"
    0,
};

const char *c99_skel[] = {
#include "c99-flex.h"
    0,
};

const char *go_skel[] = {
#include "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
struct flex_backend_t {
	const char **skel;		// Digested skeleton file
};

static struct flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {NULL}
};

static struct flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(void)
{
    повернути backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
static bool boneseeker(const char *bone)
{
	ціле i;

	для (i = 0; backend->skel[i] != NULL; i++) {
		const char *line = backend->skel[i];
		якщо (strstr(line, bone) != NULL)
			повернути true;
		інакше якщо (strncmp(line, "%%", 2) == 0)
			break;
	}
	повернути false;
}

void backend_by_name(const char *name)
{
	const char *prefix_property;
	якщо (name != NULL) {
		якщо (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			goto backend_ok;
		}
		якщо (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			goto backend_ok;
		}
		для (backend = &backends[0]; backend->skel != NULL; backend++) {
			якщо (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				goto backend_ok;
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
	якщо (prefix_property != NULL)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

const char *suffix (void)
{
	const char   *suffix;

	якщо (is_default_backend()) {
		якщо (ctrl.C_plus_plus)
			suffix = "cc";
		інакше
			suffix = "c";
	} інакше {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	повернути suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
const char *skel_property(const char *propname)
{
	ціле i;
	static char name[256], value[256], *np, *vp;;
	const char *cp;

	для (i = 0; backend->skel[i] != NULL; i++) {
		const char *line = backend->skel[i];
		якщо (line[0] == '\0')
			continue;
		/* only scan before first skell breakpoint */
		якщо (strncmp(line, "%%", 2) == 0)
			break;
		/* ignore anything that's not a definition */
		якщо (strncmp(line, "m4_define(", 10) != 0)
			continue;
		/* skip space and quotes before macro name */
		для (cp = line + 10; isspace(*cp) || *cp == '['; *cp++)
			continue;
		/* copy up to following ] into the name buffer */
		np = name;
		поки (*cp != ']' && *cp != '\0' && (np < name + sizeof(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		якщо (*cp == ']') {
			якщо (strcmp(name, propname) != 0)
				continue; /* try next line */
		} інакше {
			flexerror(_("unterminated or too long property name"));
			continue;
		}
		/* skip to the property value */
		поки (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		поки (*cp == '[')
			cp++;
		якщо (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = value;
		поки (*cp != '\0' && vp < value + sizeof(value) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		якщо (*cp == ']') {
			*vp = '\0';
			повернути value;
		} інакше {
			flexerror(_("unterminated or too long property value"));
		}
	}
	повернути NULL;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
void skelout (bool announce)
{
	char    buf_storage[MAXLINE];
	char   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	поки (env.skelfile != NULL ?
	       (fgets (buf, MAXLINE, env.skelfile) != NULL) :
	       ((buf = (char *) backend->skel[skel_ind++]) != 0)) {

		якщо (env.skelfile != NULL)
			chomp (buf);

		/* copy from skel array */
		якщо (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			якщо (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			якщо (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			інакше якщо (buf[1] == '%') {
				/* %% is a break point for skelout() */
				якщо (announce) {
					comment(buf);
					outc ('\n');
				}
				повернути;
			}
			інакше {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		інакше якщо (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
