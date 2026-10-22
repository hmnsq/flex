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
	पूर्णाङ्क     flags;		/* The above hex flags. */
	पूर्णाङ्क     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	पूर्णाङ्क     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


संरचना _scanopt_t {
	ध्रुव optspec_t *options;	/* List of options. */
	संरचना _aux *aux;	/* Auxiliary data about options. */
	पूर्णाङ्क     optc;		/* Number of options. */
	पूर्णाङ्क     argc;		/* Number of args. */
	वर्ण  **argv;		/* Array of strings. */
	पूर्णाङ्क     index;		/* Used as: argv[index][subscript]. */
	पूर्णाङ्क     subscript;
	वर्ण    no_err_सन्देशः;	/* If true, do not print errors. */
	वर्ण    has_long;
	वर्ण    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
स्थिर ध्रुव वर्ण *NAME(संरचना _scanopt_t *, पूर्णाङ्क);
स्थिर पूर्णाङ्क PRINTLEN(संरचना _scanopt_t *, पूर्णाङ्क);
स्थिर पूर्णाङ्क RVAL(संरचना _scanopt_t *, पूर्णाङ्क);
स्थिर पूर्णाङ्क FLAGS(संरचना _scanopt_t *, पूर्णाङ्क);
स्थिर ध्रुव वर्ण *DESC(संरचना _scanopt_t *, पूर्णाङ्क);
स्थिर शून्य scanopt_err(संरचना _scanopt_t *, पूर्णाङ्क, पूर्णाङ्क);
स्थिर पूर्णाङ्क matchlongopt(वर्ण *, वर्ण **, पूर्णाङ्क *, वर्ण **, पूर्णाङ्क *);
स्थिर पूर्णाङ्क find_opt(संरचना _scanopt_t *, पूर्णाङ्क, वर्ण *, पूर्णाङ्क, पूर्णाङ्क *, पूर्णाङ्क *opt_offset);

स्थिर ध्रुव वर्ण *NAME (संरचना _scanopt_t *s, पूर्णाङ्क i)
{
	प्रत्यागम s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

स्थिर पूर्णाङ्क PRINTLEN (संरचना _scanopt_t *s, पूर्णाङ्क i)
{
	प्रत्यागम s->aux[i].printlen;
}

स्थिर पूर्णाङ्क RVAL (संरचना _scanopt_t *s, पूर्णाङ्क i)
{
	प्रत्यागम s->options[i].r_val;
}

स्थिर पूर्णाङ्क FLAGS (संरचना _scanopt_t *s, पूर्णाङ्क i)
{
	प्रत्यागम s->aux[i].flags;
}

स्थिर ध्रुव वर्ण *DESC (संरचना _scanopt_t *s, पूर्णाङ्क i)
{
	प्रत्यागम s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
स्थिर पूर्णाङ्क get_cols (शून्य);

स्थिर पूर्णाङ्क get_cols (शून्य)
{
	वर्ण   *env;
	पूर्णाङ्क     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	जइ (COLS > 0)
		प्रत्यागम COLS;
#endif

	जइ ((env = getenv ("COLUMNS")) != रिक्त)
		cols = atoi (env);

	प्रत्यागम cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    करेहि{                      \
        जइ((ptr)!=रिक्त)      \
            *(ptr) = val;    \
    }जाव(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    करेहि{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }जाव(0)

scanopt_t *scanopt_init (ध्रुव optspec_t *options, पूर्णाङ्क argc, वर्ण **argv, पूर्णाङ्क flags)
{
	पूर्णाङ्क     i;
	संरचना _scanopt_t *s;
	s = malloc(परिमाण (संरचना _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (वर्ण **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_सन्देशः = (flags & SCANOPT_NO_ERR_सन्देशः);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	जाव (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * परिमाण (संरचना _aux));

	प्रति (i = 0; i < s->optc; i++) {
		ध्रुव unsigned वर्ण *p, *pname;
		ध्रुव संरचना optspec_t *opt;
		संरचना _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		जइ (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ध्रुव unsigned वर्ण *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		अण्णहा {
			pname = (ध्रुव unsigned वर्ण *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (पूर्णाङ्क) strlen (opt->opt_fmt);

		aux->namelen = 0;
		प्रति (p = pname + 1; *p; p++) {
			/* detect required arg */
			जइ (*p == '=' || isspace ((unsigned वर्ण)*p)
			    || !(aux->flags & IS_LONG)) {
				जइ (aux->namelen == 0)
					aux->namelen = (पूर्णाङ्क) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			जइ (*p == '[') {
				जइ (aux->namelen == 0)
					aux->namelen = (पूर्णाङ्क) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				भङ्ग;
			}
		}
		जइ (aux->namelen == 0)
			aux->namelen = (पूर्णाङ्क) (p - pname);
	}
	प्रत्यागम (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
संरचना usg_elem {
	पूर्णाङ्क     idx;
	संरचना usg_elem *next;
	संरचना usg_elem *alias;
};
प्रकारनिर्देश संरचना usg_elem usg_elem;


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
पूर्णाङ्क     scanopt_usage (scanopt_t *scanner, FILE *fp, ध्रुव वर्ण *usage)
{
	संरचना _scanopt_t *s;
	पूर्णाङ्क     i, columns;
	ध्रुव पूर्णाङ्क indent = 2;
	usg_elem *byr_val = रिक्त;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	पूर्णाङ्क     store_idx = 0;
	usg_elem *ue;
	पूर्णाङ्क     opt_col_width = 0, desc_col_width = 0;
	पूर्णाङ्क     desccol;
	पूर्णाङ्क     print_run = 0;

	s = (संरचना _scanopt_t *) scanner;

	जइ (usage) {
		fprintf (fp, "%s\n", usage);
	}
	अण्णहा {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * परिमाण (usg_elem));
	प्रति (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = रिक्त;

		/* insert into list. */
		जइ (!byr_val)
			byr_val = ue;
		अण्णहा {
			पूर्णाङ्क     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = रिक्त;

			ue_curr = &byr_val;
			जाव (*ue_curr) {
				जइ (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					भङ्ग;
				}
				जइ (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			जइ (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#जइ 0
	जइ (1) {
		printf ("ORIGINAL:\n");
		प्रति (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		जाव (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			प्रति (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	प्रति (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		पूर्णाङ्क     len;

		len = PRINTLEN(s, ue->idx);

		प्रति (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (पूर्णाङ्क) strlen(", ");
		}

		जइ (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (पूर्णाङ्क) strlen (DESC (s, ue->idx));
		जइ (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	जइ (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		जइ (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	जाव (print_run++ < 2) {
		प्रति (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			पूर्णाङ्क     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			प्रति (ap = ue->alias; ap; ap = ap->next) {
				जइ (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					भङ्ग;
				}
			}
			जइ ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				अनुवर्त;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) करेहि{\
                  जइ(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }जाव(0)

			जइ (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			प्रति (ap = ue->alias; ap; ap = ap->next) {
				जइ (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			जइ (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			प्रति (ap = ue->alias; ap; ap = ap->next) {
				जइ (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			जइ (1) {
				ध्रुव वर्ण *pstart;

				pstart = DESC (s, ue->idx);
				जाव (1) {
					पूर्णाङ्क     n = 0;
					ध्रुव वर्ण *lastws = रिक्त, *p;

					p = pstart;

					जाव (*p && n < desc_col_width
					       && *p != '\n') {
						जइ (isspace ((unsigned वर्ण)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					जइ (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						भङ्ग;
					}
					अण्णहा जइ (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						अनुवर्त;
					}
					अण्णहा {	/* we hit the edge of the screen. wrap at space if possible. */
						जइ (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (पूर्णाङ्क)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						अण्णहा {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						अनुवर्त;
					}
				}
			}
		}
	}			/* end while */
	मुक्त (store);
	प्रत्यागम 0;
}
#endif /* no scanopt_usage */


स्थिर शून्य scanopt_err(संरचना _scanopt_t *s, पूर्णाङ्क is_short, पूर्णाङ्क err)
{
	ध्रुव वर्ण *optname = "";
	वर्ण    optchar[2];

	जइ (!s->no_err_सन्देशः) {

		जइ (s->index > 0 && s->index < s->argc) {
			जइ (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			अण्णहा {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		विकल्प (err) {
		पक्ष SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			भङ्ग;
		पक्ष SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			भङ्ग;
		पक्ष SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			भङ्ग;
		पक्ष SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			भङ्ग;
		स्वभाव:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			भङ्ग;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
स्थिर पूर्णाङ्क matchlongopt (वर्ण *str, वर्ण **optname, पूर्णाङ्क *optlen, वर्ण **arg, पूर्णाङ्क *arglen)
{
	वर्ण   *p;

	*optname = *arg = रिक्त;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	जइ (p[0] != '-' || p[1] != '-' || !p[2])
		प्रत्यागम 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	जाव (*p && *p != '=')
		++p;

	*optlen = (पूर्णाङ्क) (p - *optname);

	जइ (!*p)
		/* an option with no '=...' part. */
		प्रत्यागम 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	जाव (*p)
		++p;
	*arglen = (पूर्णाङ्क) (p - *arg);

	प्रत्यागम 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
स्थिर पूर्णाङ्क find_opt (संरचना _scanopt_t *s, पूर्णाङ्क lookup_long, वर्ण *optstart, पूर्णाङ्क
	len, पूर्णाङ्क *err_code, पूर्णाङ्क *opt_offset)
{
	पूर्णाङ्क     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	जइ (!optstart)
		प्रत्यागम 0;

	प्रति (i = 0; i < s->optc; i++) {
		ध्रुव वर्ण   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		जइ (lookup_long && (s->aux[i].flags & IS_LONG)) {
			जइ (len > s->aux[i].namelen)
				अनुवर्त;

			जइ (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				जइ (len == s->aux[i].namelen) {
					nmatch = 1;
					भङ्ग;
				}

				/* ambiguity is ok between aliases. */
				जइ (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		अण्णहा जइ (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			जइ (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	जइ (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	अण्णहा जइ (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	प्रत्यागम *err_code ? 0 : 1;
}


पूर्णाङ्क     scanopt (scanopt_t *svoid, वर्ण **arg, पूर्णाङ्क *optindex)
{
	वर्ण   *optname = रिक्त, *optarg = रिक्त, *pstart;
	पूर्णाङ्क     namelen = 0, arglen = 0;
	पूर्णाङ्क     errcode = 0, has_next;
	ध्रुव optspec_t *optp;
	संरचना _scanopt_t *s;
	संरचना _aux *auxp;
	पूर्णाङ्क     is_short;
	पूर्णाङ्क     opt_offset = -1;

	s = (संरचना _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, रिक्त);
	SAFE_ASSIGN (optindex, s->index);

	जइ (s->index >= s->argc)
		प्रत्यागम 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	जइ (!pstart)
		प्रत्यागम 0;

	जइ (s->subscript == 0) {

		/* test for exact match of "--" */
		जइ (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			प्रत्यागम 0;
		}

		/* Match an opt. */
		जइ (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			जइ (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				प्रत्यागम errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		अण्णहा जइ (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		अण्णहा {
			/* It's not an option. We're done. */
			प्रत्यागम 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	जइ (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		जइ (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			प्रत्यागम errcode;
		}

		optarg = pstart + 1;
		जइ (!*optarg) {
			optarg = रिक्त;
			arglen = 0;
		}
		अण्णहा
			arglen = (पूर्णाङ्क) strlen (optarg);
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
	जइ (auxp->flags & ARG_NONE) {
		जइ (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			प्रत्यागम SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		अण्णहा जइ (!optarg)
			INC_INDEX (s, 1);
		अण्णहा
			s->subscript++;
		प्रत्यागम optp->r_val;
	}

	/* case: required */
	जइ (auxp->flags & ARG_REQ) {
		जइ (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			प्रत्यागम SCANOPT_ERR_ARG_NOT_FOUND;
		}

		जइ (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		अण्णहा {
			SAFE_ASSIGN (arg, (वर्ण *) optarg);
			INC_INDEX (s, 1);
		}
		प्रत्यागम optp->r_val;
	}

	/* case: optional */
	जइ (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		प्रत्यागम optp->r_val;
	}


	/* Should not reach here. */
	प्रत्यागम 0;
}


पूर्णाङ्क     scanopt_destroy (scanopt_t *svoid)
{
	संरचना _scanopt_t *s;

	s = (संरचना _scanopt_t *) svoid;
	जइ (s != रिक्त) {
		मुक्त(s->aux);
		मुक्त(s);
	}
	प्रत्यागम 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
