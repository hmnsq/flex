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
	पटिनिवत्त s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

स्थिर पूर्णाङ्क PRINTLEN (संरचना _scanopt_t *s, पूर्णाङ्क i)
{
	पटिनिवत्त s->aux[i].printlen;
}

स्थिर पूर्णाङ्क RVAL (संरचना _scanopt_t *s, पूर्णाङ्क i)
{
	पटिनिवत्त s->options[i].r_val;
}

स्थिर पूर्णाङ्क FLAGS (संरचना _scanopt_t *s, पूर्णाङ्क i)
{
	पटिनिवत्त s->aux[i].flags;
}

स्थिर ध्रुव वर्ण *DESC (संरचना _scanopt_t *s, पूर्णाङ्क i)
{
	पटिनिवत्त s->options[i].desc ? s->options[i].desc : "";
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
	सचे (COLS > 0)
		पटिनिवत्त COLS;
#endif

	सचे ((env = getenv ("COLUMNS")) != रिक्त)
		cols = atoi (env);

	पटिनिवत्त cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    करोहि{                      \
        सचे((ptr)!=रिक्त)      \
            *(ptr) = val;    \
    }याव(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    करोहि{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }याव(0)

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
	याव (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * परिमाण (संरचना _aux));

	अत्थाय (i = 0; i < s->optc; i++) {
		ध्रुव unsigned वर्ण *p, *pname;
		ध्रुव संरचना optspec_t *opt;
		संरचना _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		सचे (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ध्रुव unsigned वर्ण *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		अञ्ञथा {
			pname = (ध्रुव unsigned वर्ण *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (पूर्णाङ्क) strlen (opt->opt_fmt);

		aux->namelen = 0;
		अत्थाय (p = pname + 1; *p; p++) {
			/* detect required arg */
			सचे (*p == '=' || isspace ((unsigned वर्ण)*p)
			    || !(aux->flags & IS_LONG)) {
				सचे (aux->namelen == 0)
					aux->namelen = (पूर्णाङ्क) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			सचे (*p == '[') {
				सचे (aux->namelen == 0)
					aux->namelen = (पूर्णाङ्क) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				भङ्ग;
			}
		}
		सचे (aux->namelen == 0)
			aux->namelen = (पूर्णाङ्क) (p - pname);
	}
	पटिनिवत्त (scanopt_t *) s;
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

	सचे (usage) {
		fprintf (fp, "%s\n", usage);
	}
	अञ्ञथा {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * परिमाण (usg_elem));
	अत्थाय (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = रिक्त;

		/* insert into list. */
		सचे (!byr_val)
			byr_val = ue;
		अञ्ञथा {
			पूर्णाङ्क     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = रिक्त;

			ue_curr = &byr_val;
			याव (*ue_curr) {
				सचे (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					भङ्ग;
				}
				सचे (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			सचे (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#सचे 0
	सचे (1) {
		printf ("ORIGINAL:\n");
		अत्थाय (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		याव (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			अत्थाय (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	अत्थाय (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		पूर्णाङ्क     len;

		len = PRINTLEN(s, ue->idx);

		अत्थाय (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (पूर्णाङ्क) strlen(", ");
		}

		सचे (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (पूर्णाङ्क) strlen (DESC (s, ue->idx));
		सचे (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	सचे (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		सचे (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	याव (print_run++ < 2) {
		अत्थाय (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			पूर्णाङ्क     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			अत्थाय (ap = ue->alias; ap; ap = ap->next) {
				सचे (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					भङ्ग;
				}
			}
			सचे ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				अनुवर्त;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) करोहि{\
                  सचे(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }याव(0)

			सचे (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			अत्थाय (ap = ue->alias; ap; ap = ap->next) {
				सचे (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			सचे (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			अत्थाय (ap = ue->alias; ap; ap = ap->next) {
				सचे (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			सचे (1) {
				ध्रुव वर्ण *pstart;

				pstart = DESC (s, ue->idx);
				याव (1) {
					पूर्णाङ्क     n = 0;
					ध्रुव वर्ण *lastws = रिक्त, *p;

					p = pstart;

					याव (*p && n < desc_col_width
					       && *p != '\n') {
						सचे (isspace ((unsigned वर्ण)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					सचे (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						भङ्ग;
					}
					अञ्ञथा सचे (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						अनुवर्त;
					}
					अञ्ञथा {	/* we hit the edge of the screen. wrap at space if possible. */
						सचे (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (पूर्णाङ्क)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						अञ्ञथा {
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
	पटिनिवत्त 0;
}
#endif /* no scanopt_usage */


स्थिर शून्य scanopt_err(संरचना _scanopt_t *s, पूर्णाङ्क is_short, पूर्णाङ्क err)
{
	ध्रुव वर्ण *optname = "";
	वर्ण    optchar[2];

	सचे (!s->no_err_सन्देशः) {

		सचे (s->index > 0 && s->index < s->argc) {
			सचे (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			अञ्ञथा {
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
	सचे (p[0] != '-' || p[1] != '-' || !p[2])
		पटिनिवत्त 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	याव (*p && *p != '=')
		++p;

	*optlen = (पूर्णाङ्क) (p - *optname);

	सचे (!*p)
		/* an option with no '=...' part. */
		पटिनिवत्त 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	याव (*p)
		++p;
	*arglen = (पूर्णाङ्क) (p - *arg);

	पटिनिवत्त 1;
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

	सचे (!optstart)
		पटिनिवत्त 0;

	अत्थाय (i = 0; i < s->optc; i++) {
		ध्रुव वर्ण   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		सचे (lookup_long && (s->aux[i].flags & IS_LONG)) {
			सचे (len > s->aux[i].namelen)
				अनुवर्त;

			सचे (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				सचे (len == s->aux[i].namelen) {
					nmatch = 1;
					भङ्ग;
				}

				/* ambiguity is ok between aliases. */
				सचे (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		अञ्ञथा सचे (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			सचे (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	सचे (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	अञ्ञथा सचे (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	पटिनिवत्त *err_code ? 0 : 1;
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

	सचे (s->index >= s->argc)
		पटिनिवत्त 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	सचे (!pstart)
		पटिनिवत्त 0;

	सचे (s->subscript == 0) {

		/* test for exact match of "--" */
		सचे (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			पटिनिवत्त 0;
		}

		/* Match an opt. */
		सचे (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			सचे (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				पटिनिवत्त errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		अञ्ञथा सचे (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		अञ्ञथा {
			/* It's not an option. We're done. */
			पटिनिवत्त 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	सचे (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		सचे (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			पटिनिवत्त errcode;
		}

		optarg = pstart + 1;
		सचे (!*optarg) {
			optarg = रिक्त;
			arglen = 0;
		}
		अञ्ञथा
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
	सचे (auxp->flags & ARG_NONE) {
		सचे (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			पटिनिवत्त SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		अञ्ञथा सचे (!optarg)
			INC_INDEX (s, 1);
		अञ्ञथा
			s->subscript++;
		पटिनिवत्त optp->r_val;
	}

	/* case: required */
	सचे (auxp->flags & ARG_REQ) {
		सचे (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			पटिनिवत्त SCANOPT_ERR_ARG_NOT_FOUND;
		}

		सचे (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		अञ्ञथा {
			SAFE_ASSIGN (arg, (वर्ण *) optarg);
			INC_INDEX (s, 1);
		}
		पटिनिवत्त optp->r_val;
	}

	/* case: optional */
	सचे (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		पटिनिवत्त optp->r_val;
	}


	/* Should not reach here. */
	पटिनिवत्त 0;
}


पूर्णाङ्क     scanopt_destroy (scanopt_t *svoid)
{
	संरचना _scanopt_t *s;

	s = (संरचना _scanopt_t *) svoid;
	सचे (s != रिक्त) {
		मुक्त(s->aux);
		मुक्त(s);
	}
	पटिनिवत्त 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
