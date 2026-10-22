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


#অন্তর্ভাৱ "flexdef.h"
#অন্তর্ভাৱ "tables.h"

/* START digested skeletons */

ধ্রুৱ ৱর্ণ *cpp_skel[] = {
#অন্তর্ভাৱ "cpp-flex.h"
    0,
};

ধ্রুৱ ৱর্ণ *c99_skel[] = {
#অন্তর্ভাৱ "c99-flex.h"
    0,
};

ধ্রুৱ ৱর্ণ *go_skel[] = {
#অন্তর্ভাৱ "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
সংরচনা flex_backend_t {
	ধ্রুৱ ৱর্ণ **skel;		// Digested skeleton file
};

স্থির সংরচনা flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {রিক্ত}
};

স্থির সংরচনা flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(শূন্য)
{
    ঘূৰাই backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
স্থির bool boneseeker(ধ্রুৱ ৱর্ণ *bone)
{
	পূর্ণাঙ্ক i;

	বাবে (i = 0; backend->skel[i] != রিক্ত; i++) {
		ধ্রুৱ ৱর্ণ *সাৰি = backend->skel[i];
		যদি (strstr(সাৰি, bone) != রিক্ত)
			ঘূৰাই true;
		অন্যথা যদি (strncmp(সাৰি, "%%", 2) == 0)
			ভঙ্গ;
	}
	ঘূৰাই false;
}

শূন্য backend_by_name(ধ্রুৱ ৱর্ণ *name)
{
	ধ্রুৱ ৱর্ণ *prefix_property;
	যদি (name != রিক্ত) {
		যদি (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			গচ্ছ backend_ok;
		}
		যদি (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			গচ্ছ backend_ok;
		}
		বাবে (backend = &backends[0]; backend->skel != রিক্ত; backend++) {
			যদি (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				গচ্ছ backend_ok;
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
	যদি (prefix_property != রিক্ত)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

ধ্রুৱ ৱর্ণ *suffix (শূন্য)
{
	ধ্রুৱ ৱর্ণ   *suffix;

	যদি (is_default_backend()) {
		যদি (ctrl.C_plus_plus)
			suffix = "cc";
		অন্যথা
			suffix = "c";
	} অন্যথা {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	ঘূৰাই suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
ধ্রুৱ ৱর্ণ *skel_property(ধ্রুৱ ৱর্ণ *propname)
{
	পূর্ণাঙ্ক i;
	স্থির ৱর্ণ name[256], মান[256], *np, *vp;;
	ধ্রুৱ ৱর্ণ *cp;

	বাবে (i = 0; backend->skel[i] != রিক্ত; i++) {
		ধ্রুৱ ৱর্ণ *সাৰি = backend->skel[i];
		যদি (সাৰি[0] == '\0')
			অনুৱর্ত;
		/* only scan before first skell breakpoint */
		যদি (strncmp(সাৰি, "%%", 2) == 0)
			ভঙ্গ;
		/* ignore anything that's not a definition */
		যদি (strncmp(সাৰি, "m4_define(", 10) != 0)
			অনুৱর্ত;
		/* skip space and quotes before macro name */
		বাবে (cp = সাৰি + 10; isspace(*cp) || *cp == '['; *cp++)
			অনুৱর্ত;
		/* copy up to following ] into the name buffer */
		np = name;
		যেতিয়ালৈ (*cp != ']' && *cp != '\0' && (np < name + পরিমাণ(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		যদি (*cp == ']') {
			যদি (strcmp(name, propname) != 0)
				অনুৱর্ত; /* try next line */
		} অন্যথা {
			flexerror(_("unterminated or too long property name"));
			অনুৱর্ত;
		}
		/* skip to the property value */
		যেতিয়ালৈ (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		যেতিয়ালৈ (*cp == '[')
			cp++;
		যদি (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = মান;
		যেতিয়ালৈ (*cp != '\0' && vp < মান + পরিমাণ(মান) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		যদি (*cp == ']') {
			*vp = '\0';
			ঘূৰাই মান;
		} অন্যথা {
			flexerror(_("unterminated or too long property value"));
		}
	}
	ঘূৰাই রিক্ত;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
শূন্য skelout (bool announce)
{
	ৱর্ণ    buf_storage[MAXLINE];
	ৱর্ণ   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	যেতিয়ালৈ (env.skelfile != রিক্ত ?
	       (fgets (buf, MAXLINE, env.skelfile) != রিক্ত) :
	       ((buf = (ৱর্ণ *) backend->skel[skel_ind++]) != 0)) {

		যদি (env.skelfile != রিক্ত)
			chomp (buf);

		/* copy from skel array */
		যদি (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			যদি (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			যদি (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			অন্যথা যদি (buf[1] == '%') {
				/* %% is a break point for skelout() */
				যদি (announce) {
					comment(buf);
					outc ('\n');
				}
				ঘূৰাই;
			}
			অন্যথা {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		অন্যথা যদি (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
