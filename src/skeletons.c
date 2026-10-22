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

const var_na *cpp_skel[] = {
#include "cpp-flex.h"
    0,
};

const var_na *c99_skel[] = {
#include "c99-flex.h"
    0,
};

const var_na *go_skel[] = {
#include "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
sa_nracanaa flex_backend_t {
	const var_na **skel;		// Digested skeleton file
};

static sa_nracanaa flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {NULL}
};

static sa_nracanaa flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(void)
{
    ආපසු backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
static bool boneseeker(const var_na *bone)
{
	පූර්ණ_සංඛ්‍යා i;

	සඳහා (i = 0; backend->skel[i] != NULL; i++) {
		const var_na *line = backend->skel[i];
		නම් (strstr(line, bone) != NULL)
			ආපසු true;
		නැතහොත් නම් (strncmp(line, "%%", 2) == 0)
			bha_nga;
	}
	ආපසු false;
}

void backend_by_name(const var_na *name)
{
	const var_na *prefix_property;
	නම් (name != NULL) {
		නම් (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			goto backend_ok;
		}
		නම් (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			goto backend_ok;
		}
		සඳහා (backend = &backends[0]; backend->skel != NULL; backend++) {
			නම් (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
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
	නම් (prefix_property != NULL)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

const var_na *suffix (void)
{
	const var_na   *suffix;

	නම් (is_default_backend()) {
		නම් (ctrl.C_plus_plus)
			suffix = "cc";
		නැතහොත්
			suffix = "c";
	} නැතහොත් {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	ආපසු suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
const var_na *skel_property(const var_na *propname)
{
	පූර්ණ_සංඛ්‍යා i;
	static var_na name[256], value[256], *np, *vp;;
	const var_na *cp;

	සඳහා (i = 0; backend->skel[i] != NULL; i++) {
		const var_na *line = backend->skel[i];
		නම් (line[0] == '\0')
			continue;
		/* only scan before first skell breakpoint */
		නම් (strncmp(line, "%%", 2) == 0)
			bha_nga;
		/* ignore anything that's not a definition */
		නම් (strncmp(line, "m4_define(", 10) != 0)
			continue;
		/* skip space and quotes before macro name */
		සඳහා (cp = line + 10; isspace(*cp) || *cp == '['; *cp++)
			continue;
		/* copy up to following ] into the name buffer */
		np = name;
		අතරතුර (*cp != ']' && *cp != '\0' && (np < name + parimaa_na(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		නම් (*cp == ']') {
			නම් (strcmp(name, propname) != 0)
				continue; /* try next line */
		} නැතහොත් {
			flexerror(_("unterminated or too long property name"));
			continue;
		}
		/* skip to the property value */
		අතරතුර (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		අතරතුර (*cp == '[')
			cp++;
		නම් (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = value;
		අතරතුර (*cp != '\0' && vp < value + parimaa_na(value) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		නම් (*cp == ']') {
			*vp = '\0';
			ආපසු value;
		} නැතහොත් {
			flexerror(_("unterminated or too long property value"));
		}
	}
	ආපසු NULL;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
void skelout (bool announce)
{
	var_na    buf_storage[MAXLINE];
	var_na   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	අතරතුර (env.skelfile != NULL ?
	       (fgets (buf, MAXLINE, env.skelfile) != NULL) :
	       ((buf = (var_na *) backend->skel[skel_ind++]) != 0)) {

		නම් (env.skelfile != NULL)
			chomp (buf);

		/* copy from skel array */
		නම් (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			නම් (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			නම් (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			නැතහොත් නම් (buf[1] == '%') {
				/* %% is a break point for skelout() */
				නම් (announce) {
					comment(buf);
					outc ('\n');
				}
				ආපසු;
			}
			නැතහොත් {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		නැතහොත් නම් (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
