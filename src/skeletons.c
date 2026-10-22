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


#അന്തര്ഭാവ "flexdef.h"
#അന്തര്ഭാവ "tables.h"

/* START digested skeletons */

സ്ഥിരം അക്ഷരം *cpp_skel[] = {
#അന്തര്ഭാവ "cpp-flex.h"
    0,
};

സ്ഥിരം അക്ഷരം *c99_skel[] = {
#അന്തര്ഭാവ "c99-flex.h"
    0,
};

സ്ഥിരം അക്ഷരം *go_skel[] = {
#അന്തര്ഭാവ "go-flex.h"
    0,
};

/* END digested skeletons */

/* Method table describing a language-specific back end.
 * Even if this never gets a member other than the skel
 * array, it prevents us from getting lost in a maze of
 * twisty array reference levels, all different.
 */
ഘടന flex_backend_t {
	സ്ഥിരം അക്ഷരം **skel;		// Digested skeleton file
};

സ്ഥിതം ഘടന flex_backend_t backends[] = {
    {.skel=cpp_skel},
    {.skel=c99_skel},
    {.skel=go_skel},
    {ശൂന്യ}
};

സ്ഥിതം ഘടന flex_backend_t *backend = &backends[0];

/* Functions for querying skeleton properties. */

bool is_default_backend(ശൂന്യം)
{
    തിരികെ backend == &backends[0];
}

/* Search for a string in the skeleton prolog, where macros are defined.
 */
സ്ഥിതം bool boneseeker(സ്ഥിരം അക്ഷരം *bone)
{
	പൂർണ്ണസംഖ്യ i;

	വേണ്ടി (i = 0; backend->skel[i] != ശൂന്യ; i++) {
		സ്ഥിരം അക്ഷരം *വരി = backend->skel[i];
		എങ്കിൽ (strstr(വരി, bone) != ശൂന്യ)
			തിരികെ true;
		അല്ലെങ്കിൽ എങ്കിൽ (strncmp(വരി, "%%", 2) == 0)
			നിർത്തുക;
	}
	തിരികെ false;
}

ശൂന്യം backend_by_name(സ്ഥിരം അക്ഷരം *name)
{
	സ്ഥിരം അക്ഷരം *prefix_property;
	എങ്കിൽ (name != ശൂന്യ) {
		എങ്കിൽ (strcmp(name, "nr") == 0) {
			backend = &backends[0];
			ctrl.reentrant = false;
			പോകുക backend_ok;
		}
		എങ്കിൽ (strcmp(name, "r") == 0) {
			backend = &backends[0];
			ctrl.reentrant = true;
			പോകുക backend_ok;
		}
		വേണ്ടി (backend = &backends[0]; backend->skel != ശൂന്യ; backend++) {
			എങ്കിൽ (strcasecmp(skel_property("M4_PROPERTY_BACKEND_NAME"), name) == 0)
				പോകുക backend_ok;
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
	എങ്കിൽ (prefix_property != ശൂന്യ)
		ctrl.prefix = xstrdup(prefix_property);
	flex_init_regex(ctrl.traceline_re);
}

സ്ഥിരം അക്ഷരം *suffix (ശൂന്യം)
{
	സ്ഥിരം അക്ഷരം   *suffix;

	എങ്കിൽ (is_default_backend()) {
		എങ്കിൽ (ctrl.C_plus_plus)
			suffix = "cc";
		അല്ലെങ്കിൽ
			suffix = "c";
	} അല്ലെങ്കിൽ {
		suffix = skel_property("M4_PROPERTY_SOURCE_SUFFIX");
	}
	
	തിരികെ suffix;
}

/* Search for a m4 define of the property key, retrieve the value.  The
 * definition must be single-line.  Don't call this a second time before
 * stashing away the previous return, we cheat with static buffers.
 */
സ്ഥിരം അക്ഷരം *skel_property(സ്ഥിരം അക്ഷരം *propname)
{
	പൂർണ്ണസംഖ്യ i;
	സ്ഥിതം അക്ഷരം name[256], മൂല്യം[256], *np, *vp;;
	സ്ഥിരം അക്ഷരം *cp;

	വേണ്ടി (i = 0; backend->skel[i] != ശൂന്യ; i++) {
		സ്ഥിരം അക്ഷരം *വരി = backend->skel[i];
		എങ്കിൽ (വരി[0] == '\0')
			തുടരുക;
		/* only scan before first skell breakpoint */
		എങ്കിൽ (strncmp(വരി, "%%", 2) == 0)
			നിർത്തുക;
		/* ignore anything that's not a definition */
		എങ്കിൽ (strncmp(വരി, "m4_define(", 10) != 0)
			തുടരുക;
		/* skip space and quotes before macro name */
		വേണ്ടി (cp = വരി + 10; isspace(*cp) || *cp == '['; *cp++)
			തുടരുക;
		/* copy up to following ] into the name buffer */
		np = name;
		ആകുമ്പോൾ (*cp != ']' && *cp != '\0' && (np < name + വലുപ്പം(name)-1)) {
			*np++ = *cp++;
		}
		*np = '\0';
		/* check for valid and matching name */
		എങ്കിൽ (*cp == ']') {
			എങ്കിൽ (strcmp(name, propname) != 0)
				തുടരുക; /* try next line */
		} അല്ലെങ്കിൽ {
			flexerror(_("unterminated or too long property name"));
			തുടരുക;
		}
		/* skip to the property value */
		ആകുമ്പോൾ (*cp != '\0' && (*cp == ']' || isspace(*cp) || *cp == ','))
			cp++;
		ആകുമ്പോൾ (*cp == '[')
			cp++;
		എങ്കിൽ (*cp == '\0')
			flexerror(_("garbled property line"));
		/* extract the value */
		vp = മൂല്യം;
		ആകുമ്പോൾ (*cp != '\0' && vp < മൂല്യം + വലുപ്പം(മൂല്യം) - 1 && (cp[0] != ']' || cp[1] != ']'))
			*vp++ = *cp++;
		എങ്കിൽ (*cp == ']') {
			*vp = '\0';
			തിരികെ മൂല്യം;
		} അല്ലെങ്കിൽ {
			flexerror(_("unterminated or too long property value"));
		}
	}
	തിരികെ ശൂന്യ;
}

/* skelout - write out one section of the skeleton file
 *
 * Description
 *    Copies skelfile or skel array to stdout until a line beginning with
 *    "%%" or EOF is found.
 */
ശൂന്യം skelout (bool announce)
{
	അക്ഷരം    buf_storage[MAXLINE];
	അക്ഷരം   *buf = buf_storage;
	bool   do_copy = true;

	/* Loop pulling lines either from the skelfile, if we're using
	 * one, or from the selected back end's skel[] array.
	 */
	ആകുമ്പോൾ (env.skelfile != ശൂന്യ ?
	       (fgets (buf, MAXLINE, env.skelfile) != ശൂന്യ) :
	       ((buf = (അക്ഷരം *) backend->skel[skel_ind++]) != 0)) {

		എങ്കിൽ (env.skelfile != ശൂന്യ)
			chomp (buf);

		/* copy from skel array */
		എങ്കിൽ (buf[0] == '%') {	/* control line */
			/* print the control line as a comment. */
			എങ്കിൽ (ctrl.ddebug && buf[1] != '#') {
			    comment(buf);
			    outc ('\n');
			}
			എങ്കിൽ (buf[1] == '#') {
				/* %# indicates comment line to be ignored */
			} 
			അല്ലെങ്കിൽ എങ്കിൽ (buf[1] == '%') {
				/* %% is a break point for skelout() */
				എങ്കിൽ (announce) {
					comment(buf);
					outc ('\n');
				}
				തിരികെ;
			}
			അല്ലെങ്കിൽ {
				flexfatal (_("bad line in skeleton file"));
			}
		}

		അല്ലെങ്കിൽ എങ്കിൽ (do_copy) 
			outn (buf);
	}			/* end while */
}


/* end */
