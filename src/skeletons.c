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


#شامل "flexdef.h"
#شامل "tables.h"

/* START digested skeletons */

ثابت نویسه *cpp_skel[] = {
#شامل "cpp-flex.h"
    0,
};

ثابت نویسه *c99_skel[] = {
#شامل "c99-flex.h"
    0,
};

ثابت نویسه *go_skel[] = {
#شامل "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
ساختار flex_backend_t {
	ثابت نویسه **skel;		// Digested skeleton file
};

ایستا ساختار flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {پوچ}
};

ایستا ساختار flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(تهی)
{
    بازگشت backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
ایستا bool boneseeker(ثابت نویسه *bone)
{
	صحیح i;

	برای (i = 0; backend->skel[i] != پوچ; i++) {
		ثابت نویسه *سطر = backend->skel[i];
		اگر (strstr(سطر, bone) != پوچ)
			بازگشت true;
		وگرنه اگر (strncmp(سطر, "%%", 2) == 0)
			بشکن;
	}
	بازگشت false;
}

تهی backend_by_name(ثابت نویسه *name)
{
	ثابت نویسه *prefix_property;
	اگر (name != پوچ) {
		اگر (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			برو backend_ok;
		}
		اگر (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			برو backend_ok;
		}
		برای (backend = &backends[0]; backend->skel != پوچ; backend++) {
			اگر (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				برو backend_ok;
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
	اگر (prefix_property != پوچ)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

ثابت نویسه *suffix (تهی)
{
	ثابت نویسه   *suffix;

	اگر (is_default_backend()) {
		اگر (ctrl.C_plus_plus)
			suffix = "cc";
		وگرنه
			suffix = "c";
	} وگرنه {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	بازگشت suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
ثابت نویسه *skel_property(ثابت نویسه *propname)
{
	صحیح i;
	ایستا نویسه name[256], مقدار[256], *np, *vp;;
	ثابت نویسه *cp;

	برای (i = 0; backend->skel[i] != پوچ; i++) {
		ثابت نویسه *سطر = backend->skel[i];
		اگر (سطر[0] == '\0')
			ادامه;
		/* only scan before first skell breakpoint */
		اگر (strncmp(سطر, "%%", 2) == 0)
			بشکن;
		/* ignore anything that's not a definition */
		اگر (strncmp(سطر, "m4_define(", 10) != 0)
			ادامه;
		/* skip space and quotes before macro name */
		برای (cp = سطر + 10; isspace(*cp) || *cp == '['; *cp++)
			ادامه;
		/* copy up to following ] into the name buffer */
		np = name;
		وقتی (*cp != ']' && *cp != '\0' && (np < name + اندازه(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		اگر (*cp == ']') {
			اگر (strcmp(name, propname) != 0)
				ادامه; /* try next line */
		} وگرنه {
			flexerror(_("unterminated or too long property name"));
			ادامه;
		}
		/* skip to the property value */
		وقتی (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		وقتی (*cp == '[')
			cp++;
		اگر (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = مقدار;
		وقتی (*cp != '\0' && vp < مقدار + اندازه(مقدار) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		اگر (*cp == ']') {
			*vp = '\0';
			بازگشت مقدار;
		} وگرنه {
			flexerror(_("unterminated or too long property value"));
		}
	}
	بازگشت پوچ;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
تهی skelout (bool announce)
{
	نویسه    buf_storage[MAXLINE];
	نویسه   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	وقتی (env.skelfile != پوچ ?
	       (fgets (buf, MAXLINE, env.skelfile) != پوچ) :
	       ((buf = (نویسه *) backend->skel[skel_ind++]) != 0)) {

		اگر (env.skelfile != پوچ)
			chomp (buf);

		/* copy from skel array */
		اگر (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			اگر (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			اگر (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			وگرنه اگر (buf[1] == '%') {
				/* %% is a break point for skelout() */
				اگر (announce) {
					comment(buf);
					outc ('\n');
				}
				بازگشت;
			}
			وگرنه {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		وگرنه اگر (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
