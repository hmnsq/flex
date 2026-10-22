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

ثابت حرف *cpp_skel[] = {
#شامل "cpp-flex.h"
    0,
};

ثابت حرف *c99_skel[] = {
#شامل "c99-flex.h"
    0,
};

ثابت حرف *go_skel[] = {
#شامل "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
ساخت flex_backend_t {
	ثابت حرف **skel;		// Digested skeleton file
};

ساکن ساخت flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {تہی}
};

ساکن ساخت flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(خالی)
{
    واپس backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
ساکن bool boneseeker(ثابت حرف *bone)
{
	صحیح i;

	برائے (i = 0; backend->skel[i] != تہی; i++) {
		ثابت حرف *سطر = backend->skel[i];
		اگر (لڑی_تلاش(سطر, bone) != تہی)
			واپس true;
		ورنہ اگر (لڑی_موازنہ(سطر, "%%", 2) == 0)
			توڑو;
	}
	واپس false;
}

خالی backend_by_name(ثابت حرف *name)
{
	ثابت حرف *سابقہ_property;
	اگر (name != تہی) {
		اگر (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			جاؤ backend_ok;
		}
		اگر (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			جاؤ backend_ok;
		}
		برائے (backend = &backends[0]; backend->skel != تہی; backend++) {
			اگر (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				جاؤ backend_ok;
		}
		flexerror(_("no such back end"));
	}
  backend_ok:
	ctrl.rewrite = !is_default_backend();
	ctrl.backend_name = xstrdup(skel_property("M4_PROPERTY_BACKEND_NAME"));
	ctrl.traceline_re = xstrdup(skel_property("M4_PROPERTY_TRACE_LINE_REGEXP"));
	ctrl.traceline_template = xstrdup(skel_property("M4_PROPERTY_TRACE_LINE_TEMPLATE"));
	ctrl.have_state_اندراج_format = boneseeker("m4_define([[M4_HOOK_STATE_ENTRY_FORMAT]]");
	سابقہ_property = skel_property("M4_PROPERTY_PREFIX");
	اگر (سابقہ_property != تہی)
		ctrl.سابقہ = xstrdup(سابقہ_property);
	flex_init_regex(ctrl.traceline_re);
}

ثابت حرف *suffix (خالی)
{
	ثابت حرف   *suffix;

	اگر (is_default_backend()) {
		اگر (ctrl.C_plus_plus)
			suffix = "cc";
		ورنہ
			suffix = "c";
	} ورنہ {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	واپس suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
ثابت حرف *skel_property(ثابت حرف *propname)
{
	صحیح i;
	ساکن حرف name[256], قدر[256], *np, *vp;;
	ثابت حرف *cp;

	برائے (i = 0; backend->skel[i] != تہی; i++) {
		ثابت حرف *سطر = backend->skel[i];
		اگر (سطر[0] == '\0')
			جاری;
		/* only scan before first skell breakpoint */
		اگر (لڑی_موازنہ(سطر, "%%", 2) == 0)
			توڑو;
		/* ignore anything that's not a definition */
		اگر (لڑی_موازنہ(سطر, "m4_define(", 10) != 0)
			جاری;
		/* skip space and quotes before macro name */
		برائے (cp = سطر + 10; خلا_ہے(*cp) || *cp == '['; *cp++)
			جاری;
		/* copy up to following ] into the name buffer */
		np = name;
		جب (*cp != ']' && *cp != '\0' && (np < name + حجم(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		اگر (*cp == ']') {
			اگر (strcmp(name, propname) != 0)
				جاری; /* try next line */
		} ورنہ {
			flexerror(_("unterminated or too long property name"));
			جاری;
		}
		/* skip to the property value */
		جب (*cp != '\0' && (*cp == ']' || خلا_ہے(*cp) || *cp == ','))
			cp++;
		جب (*cp == '[')
			cp++;
		اگر (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = قدر;
		جب (*cp != '\0' && vp < قدر + حجم(قدر) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		اگر (*cp == ']') {
			*vp = '\0';
			واپس قدر;
		} ورنہ {
			flexerror(_("unterminated or too long property value"));
		}
	}
	واپس تہی;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
خالی skelout (bool announce)
{
	حرف    buf_storage[MAXLINE];
	حرف   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	جب (env.skelfile != تہی ?
	       (fgets (buf, MAXLINE, env.skelfile) != تہی) :
	       ((buf = (حرف *) backend->skel[skel_ind++]) != 0)) {

		اگر (env.skelfile != تہی)
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
			ورنہ اگر (buf[1] == '%') {
				/* %% is a break point for skelout() */
				اگر (announce) {
					comment(buf);
					outc ('\n');
				}
				واپس;
			}
			ورنہ {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		ورنہ اگر (do_copy) 
			outn (buf);
	}			/* end while */
}


/*انتہا*/
