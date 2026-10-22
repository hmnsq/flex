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
#अन्तर्भाव "scanopt.h"


/* Internal structures */

#define ARG_NONE 0x01
#define ARG_REQ  0x02
#define ARG_OPT  0x04
#define IS_LONG  0x08

संरचना _aux {
	पूर्णांक     flags;		/* The above hex flags. */
	पूर्णांक     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	पूर्णांक     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


संरचना _scanopt_t {
	स्थिरांक optspec_t *options;	/* List of options. */
	संरचना _aux *aux;	/* Auxiliary data about options. */
	पूर्णांक     optc;		/* Number of options. */
	पूर्णांक     argc;		/* Number of args. */
	अक्षर  **argv;		/* Array of strings. */
	पूर्णांक     index;		/* Used as: argv[index][subscript]. */
	पूर्णांक     subscript;
	अक्षर    no_err_संदेश;	/* If true, do not print errors. */
	अक्षर    has_long;
	अक्षर    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
स्थिर स्थिरांक अक्षर *NAME(संरचना _scanopt_t *, पूर्णांक);
स्थिर पूर्णांक PRINTLEN(संरचना _scanopt_t *, पूर्णांक);
स्थिर पूर्णांक RVAL(संरचना _scanopt_t *, पूर्णांक);
स्थिर पूर्णांक FLAGS(संरचना _scanopt_t *, पूर्णांक);
स्थिर स्थिरांक अक्षर *DESC(संरचना _scanopt_t *, पूर्णांक);
स्थिर शून्य scanopt_err(संरचना _scanopt_t *, पूर्णांक, पूर्णांक);
स्थिर पूर्णांक matchlongopt(अक्षर *, अक्षर **, पूर्णांक *, अक्षर **, पूर्णांक *);
स्थिर पूर्णांक find_opt(संरचना _scanopt_t *, पूर्णांक, अक्षर *, पूर्णांक, पूर्णांक *, पूर्णांक *opt_offset);

स्थिर स्थिरांक अक्षर *NAME (संरचना _scanopt_t *s, पूर्णांक i)
{
	परत s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

स्थिर पूर्णांक PRINTLEN (संरचना _scanopt_t *s, पूर्णांक i)
{
	परत s->aux[i].printlen;
}

स्थिर पूर्णांक RVAL (संरचना _scanopt_t *s, पूर्णांक i)
{
	परत s->options[i].r_val;
}

स्थिर पूर्णांक FLAGS (संरचना _scanopt_t *s, पूर्णांक i)
{
	परत s->aux[i].flags;
}

स्थिर स्थिरांक अक्षर *DESC (संरचना _scanopt_t *s, पूर्णांक i)
{
	परत s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
स्थिर पूर्णांक get_cols (शून्य);

स्थिर पूर्णांक get_cols (शून्य)
{
	अक्षर   *env;
	पूर्णांक     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	जर (COLS > 0)
		परत COLS;
#endif

	जर ((env = दो_पर्या ("COLUMNS")) != रिक्त)
		cols = म_से_प (env);

	परत cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    करा{                      \
        जर((ptr)!=रिक्त)      \
            *(ptr) = val;    \
    }पर्यंत(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    करा{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }पर्यंत(0)

scanopt_t *scanopt_init (स्थिरांक optspec_t *options, पूर्णांक argc, अक्षर **argv, पूर्णांक flags)
{
	पूर्णांक     i;
	संरचना _scanopt_t *s;
	s = दो_स्मृति(आकार (संरचना _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (अक्षर **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_संदेश = (flags & SCANOPT_NO_ERR_संदेश);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	पर्यंत (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = दो_स्मृति((माप_प्रकार) s->optc * आकार (संरचना _aux));

	साठी (i = 0; i < s->optc; i++) {
		स्थिरांक अचिन्हित अक्षर *p, *pname;
		स्थिरांक संरचना optspec_t *opt;
		संरचना _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		जर (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (स्थिरांक अचिन्हित अक्षर *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		अन्यथा {
			pname = (स्थिरांक अचिन्हित अक्षर *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (पूर्णांक) म_माप (opt->opt_fmt);

		aux->namelen = 0;
		साठी (p = pname + 1; *p; p++) {
			/* detect required arg */
			जर (*p == '=' || है_खाली ((अचिन्हित अक्षर)*p)
			    || !(aux->flags & IS_LONG)) {
				जर (aux->namelen == 0)
					aux->namelen = (पूर्णांक) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			जर (*p == '[') {
				जर (aux->namelen == 0)
					aux->namelen = (पूर्णांक) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				थांबा;
			}
		}
		जर (aux->namelen == 0)
			aux->namelen = (पूर्णांक) (p - pname);
	}
	परत (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
संरचना usg_elem {
	पूर्णांक     idx;
	संरचना usg_elem *next;
	संरचना usg_elem *alias;
};
प्रकारव्याख्या संरचना usg_elem usg_elem;


/* Prints a usage message based on contents of optlist.
 * Parameters:
 *   scanner  - The scanner, already initialized with scanopt_init().
 *   fp       - The file stream to write to.
 *   usage    - Text to be prepended to option list.
 * Return:  Always returns 0 (zero).
 * The output looks something like this:

[indent][option, alias1, alias2...][indent][description line1
                                            description line2...]
 */
पूर्णांक     scanopt_usage (scanopt_t *scanner, खाता *fp, स्थिरांक अक्षर *usage)
{
	संरचना _scanopt_t *s;
	पूर्णांक     i, columns;
	स्थिरांक पूर्णांक indent = 2;
	usg_elem *byr_val = रिक्त;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	पूर्णांक     store_idx = 0;
	usg_elem *ue;
	पूर्णांक     opt_col_width = 0, desc_col_width = 0;
	पूर्णांक     desccol;
	पूर्णांक     print_run = 0;

	s = (संरचना _scanopt_t *) scanner;

	जर (usage) {
		ख_लिखो (fp, "%s\n", usage);
	}
	अन्यथा {
		ख_लिखो (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	ख_लिखो (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = दो_स्मृति((माप_प्रकार) s->optc * आकार (usg_elem));
	साठी (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = रिक्त;

		/* insert into list. */
		जर (!byr_val)
			byr_val = ue;
		अन्यथा {
			पूर्णांक     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = रिक्त;

			ue_curr = &byr_val;
			पर्यंत (*ue_curr) {
				जर (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					थांबा;
				}
				जर (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			जर (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#जर 0
	जर (1) {
		म_लिखो ("ORIGINAL:\n");
		साठी (i = 0; i < s->optc; i++)
			म_लिखो ("%2d: %s\n", i, NAME (s, i));
		म_लिखो ("SORTED:\n");
		ue = byr_val;
		पर्यंत (ue) {
			usg_elem *ue2;

			म_लिखो ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			साठी (ue2 = ue->alias; ue2; ue2 = ue2->next)
				म_लिखो ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	साठी (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		पूर्णांक     len;

		len = PRINTLEN(s, ue->idx);

		साठी (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (पूर्णांक) म_माप(", ");
		}

		जर (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (पूर्णांक) म_माप (DESC (s, ue->idx));
		जर (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	जर (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		जर (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = पूर्णांक_उच्च;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	ख_लिखो((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	पर्यंत (print_run++ < 2) {
		साठी (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			पूर्णांक     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			साठी (ap = ue->alias; ap; ap = ap->next) {
				जर (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					थांबा;
				}
			}
			जर ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				सुरूठेवा;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) करा{\
                  जर(nwords++)\
                      nchars+=ख_लिखो(fp,", ");\
                  nchars+=ख_लिखो(fp,"%s",s->options[i].opt_fmt);\
            }पर्यंत(0)

			जर (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			साठी (ap = ue->alias; ap; ap = ap->next) {
				जर (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			जर (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			साठी (ap = ue->alias; ap; ap = ap->next) {
				जर (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			जर (1) {
				स्थिरांक अक्षर *pstart;

				pstart = DESC (s, ue->idx);
				पर्यंत (1) {
					पूर्णांक     n = 0;
					स्थिरांक अक्षर *lastws = रिक्त, *p;

					p = pstart;

					पर्यंत (*p && n < desc_col_width
					       && *p != '\n') {
						जर (है_खाली ((अचिन्हित अक्षर)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					जर (!*p) {	/* hit end of desc. done. */
						ख_लिखो (fp, "%s\n",
							 pstart);
						थांबा;
					}
					अन्यथा जर (*p == '\n') {	/* print everything up to here then wrap. */
						ख_लिखो (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						सुरूठेवा;
					}
					अन्यथा {	/* we hit the edge of the screen. wrap at space if possible. */
						जर (lastws) {
							ख_लिखो (fp,
								 "%.*s\n",
								 (पूर्णांक)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						अन्यथा {
							ख_लिखो (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						सुरूठेवा;
					}
				}
			}
		}
	}			/* end while */
	मुक्त (store);
	परत 0;
}
#endif /* no scanopt_usage */


स्थिर शून्य scanopt_err(संरचना _scanopt_t *s, पूर्णांक is_short, पूर्णांक err)
{
	स्थिरांक अक्षर *optname = "";
	अक्षर    optchar[2];

	जर (!s->no_err_संदेश) {

		जर (s->index > 0 && s->index < s->argc) {
			जर (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			अन्यथा {
				optname = s->argv[s->index];
			}
		}

		ख_लिखो (मानक_त्रुटि, "%s: ", s->argv[0]);
		निवड (err) {
		स्थिती SCANOPT_ERR_ARG_NOT_ALLOWED:
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			थांबा;
		स्थिती SCANOPT_ERR_ARG_NOT_FOUND:
			ख_लिखो (मानक_त्रुटि,
				 _("option `%s' requires an argument\n"),
				 optname);
			थांबा;
		स्थिती SCANOPT_ERR_OPT_AMBIGUOUS:
			ख_लिखो (मानक_त्रुटि, _("option `%s' is ambiguous\n"),
				 optname);
			थांबा;
		स्थिती SCANOPT_ERR_OPT_UNRECOGNIZED:
			ख_लिखो (मानक_त्रुटि, _("Unrecognized option `%s'\n"),
				 optname);
			थांबा;
		पूर्वनिर्धारित:
			ख_लिखो (मानक_त्रुटि, _("Unknown error=(%d)\n"), err);
			थांबा;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
स्थिर पूर्णांक matchlongopt (अक्षर *str, अक्षर **optname, पूर्णांक *optlen, अक्षर **arg, पूर्णांक *arglen)
{
	अक्षर   *p;

	*optname = *arg = रिक्त;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	जर (p[0] != '-' || p[1] != '-' || !p[2])
		परत 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	पर्यंत (*p && *p != '=')
		++p;

	*optlen = (पूर्णांक) (p - *optname);

	जर (!*p)
		/* an option with no '=...' part. */
		परत 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	पर्यंत (*p)
		++p;
	*arglen = (पूर्णांक) (p - *arg);

	परत 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
स्थिर पूर्णांक find_opt (संरचना _scanopt_t *s, पूर्णांक lookup_long, अक्षर *optstart, पूर्णांक
	len, पूर्णांक *err_code, पूर्णांक *opt_offset)
{
	पूर्णांक     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	जर (!optstart)
		परत 0;

	साठी (i = 0; i < s->optc; i++) {
		स्थिरांक अक्षर   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		जर (lookup_long && (s->aux[i].flags & IS_LONG)) {
			जर (len > s->aux[i].namelen)
				सुरूठेवा;

			जर (म_भेदन (optname, optstart, (माप_प्रकार) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				जर (len == s->aux[i].namelen) {
					nmatch = 1;
					थांबा;
				}

				/* ambiguity is ok between aliases. */
				जर (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		अन्यथा जर (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			जर (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	जर (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	अन्यथा जर (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	परत *err_code ? 0 : 1;
}


पूर्णांक     scanopt (scanopt_t *svoid, अक्षर **arg, पूर्णांक *optindex)
{
	अक्षर   *optname = रिक्त, *optarg = रिक्त, *pstart;
	पूर्णांक     namelen = 0, arglen = 0;
	पूर्णांक     errcode = 0, has_next;
	स्थिरांक optspec_t *optp;
	संरचना _scanopt_t *s;
	संरचना _aux *auxp;
	पूर्णांक     is_short;
	पूर्णांक     opt_offset = -1;

	s = (संरचना _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, रिक्त);
	SAFE_ASSIGN (optindex, s->index);

	जर (s->index >= s->argc)
		परत 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	जर (!pstart)
		परत 0;

	जर (s->subscript == 0) {

		/* test for exact match of "--" */
		जर (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			परत 0;
		}

		/* Match an opt. */
		जर (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			जर (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				परत errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		अन्यथा जर (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		अन्यथा {
			/* It's not an option. We're done. */
			परत 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	जर (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		जर (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			परत errcode;
		}

		optarg = pstart + 1;
		जर (!*optarg) {
			optarg = रिक्त;
			arglen = 0;
		}
		अन्यथा
			arglen = (पूर्णांक) म_माप (optarg);
	}

	/* At this point, we have a long or short option matched at opt_offset into
	 * the s->options array (and corresponding aux array).
	 * A trailing argument is in {optarg,arglen}, if any.
	 */

	/* Look ahead in argv[] to see if there is something
	 * that we can use as an argument (if needed). */
	has_next = s->index + 1 < s->argc;

	optp = s->options + opt_offset;
	auxp = s->aux + opt_offset;

	/* case: no args allowed */
	जर (auxp->flags & ARG_NONE) {
		जर (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			परत SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		अन्यथा जर (!optarg)
			INC_INDEX (s, 1);
		अन्यथा
			s->subscript++;
		परत optp->r_val;
	}

	/* case: required */
	जर (auxp->flags & ARG_REQ) {
		जर (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			परत SCANOPT_ERR_ARG_NOT_FOUND;
		}

		जर (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		अन्यथा {
			SAFE_ASSIGN (arg, (अक्षर *) optarg);
			INC_INDEX (s, 1);
		}
		परत optp->r_val;
	}

	/* case: optional */
	जर (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		परत optp->r_val;
	}


	/* Should not reach here. */
	परत 0;
}


पूर्णांक     scanopt_destroy (scanopt_t *svoid)
{
	संरचना _scanopt_t *s;

	s = (संरचना _scanopt_t *) svoid;
	जर (s != रिक्त) {
		मुक्त(s->aux);
		मुक्त(s);
	}
	परत 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
