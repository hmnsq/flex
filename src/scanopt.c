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
#include "scanopt.h"


/* Internal structures */

#define ARG_NONE 0x01
#define ARG_REQ  0x02
#define ARG_OPT  0x04
#define IS_LONG  0x08

sa_nracanaa _aux {
	ចំនួនគត់     flags;		/* The above hex flags. */
	ចំនួនគត់     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	ចំនួនគត់     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


sa_nracanaa _scanopt_t {
	const optspec_t *options;	/* List of options. */
	sa_nracanaa _aux *aux;	/* Auxiliary data about options. */
	ចំនួនគត់     optc;		/* Number of options. */
	ចំនួនគត់     argc;		/* Number of args. */
	var_na  **argv;		/* Array of strings. */
	ចំនួនគត់     index;		/* Used as: argv[index][subscript]. */
	ចំនួនគត់     subscript;
	var_na    no_err_msg;	/* If true, do not print errors. */
	var_na    has_long;
	var_na    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
static const var_na *NAME(sa_nracanaa _scanopt_t *, ចំនួនគត់);
static ចំនួនគត់ PRINTLEN(sa_nracanaa _scanopt_t *, ចំនួនគត់);
static ចំនួនគត់ RVAL(sa_nracanaa _scanopt_t *, ចំនួនគត់);
static ចំនួនគត់ FLAGS(sa_nracanaa _scanopt_t *, ចំនួនគត់);
static const var_na *DESC(sa_nracanaa _scanopt_t *, ចំនួនគត់);
static void scanopt_err(sa_nracanaa _scanopt_t *, ចំនួនគត់, ចំនួនគត់);
static ចំនួនគត់ matchlongopt(var_na *, var_na **, ចំនួនគត់ *, var_na **, ចំនួនគត់ *);
static ចំនួនគត់ find_opt(sa_nracanaa _scanopt_t *, ចំនួនគត់, var_na *, ចំនួនគត់, ចំនួនគត់ *, ចំនួនគត់ *opt_offset);

static const var_na *NAME (sa_nracanaa _scanopt_t *s, ចំនួនគត់ i)
{
	ត្រឡប់ s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

static ចំនួនគត់ PRINTLEN (sa_nracanaa _scanopt_t *s, ចំនួនគត់ i)
{
	ត្រឡប់ s->aux[i].printlen;
}

static ចំនួនគត់ RVAL (sa_nracanaa _scanopt_t *s, ចំនួនគត់ i)
{
	ត្រឡប់ s->options[i].r_val;
}

static ចំនួនគត់ FLAGS (sa_nracanaa _scanopt_t *s, ចំនួនគត់ i)
{
	ត្រឡប់ s->aux[i].flags;
}

static const var_na *DESC (sa_nracanaa _scanopt_t *s, ចំនួនគត់ i)
{
	ត្រឡប់ s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
static ចំនួនគត់ get_cols (void);

static ចំនួនគត់ get_cols (void)
{
	var_na   *env;
	ចំនួនគត់     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	ប្រសិនបើ (COLS > 0)
		ត្រឡប់ COLS;
#endif

	ប្រសិនបើ ((env = getenv ("COLUMNS")) != NULL)
		cols = atoi (env);

	ត្រឡប់ cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    do{                      \
        ប្រសិនបើ((ptr)!=NULL)      \
            *(ptr) = val;    \
    }ខណៈពេល(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    do{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }ខណៈពេល(0)

scanopt_t *scanopt_init (const optspec_t *options, ចំនួនគត់ argc, var_na **argv, ចំនួនគត់ flags)
{
	ចំនួនគត់     i;
	sa_nracanaa _scanopt_t *s;
	s = malloc(parimaa_na (sa_nracanaa _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (var_na **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_msg = (flags & SCANOPT_NO_ERR_MSG);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	ខណៈពេល (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * parimaa_na (sa_nracanaa _aux));

	សម្រាប់ (i = 0; i < s->optc; i++) {
		const unsigned var_na *p, *pname;
		const sa_nracanaa optspec_t *opt;
		sa_nracanaa _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		ប្រសិនបើ (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (const unsigned var_na *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		បើមិនដូច្នេះ {
			pname = (const unsigned var_na *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (ចំនួនគត់) strlen (opt->opt_fmt);

		aux->namelen = 0;
		សម្រាប់ (p = pname + 1; *p; p++) {
			/* detect required arg */
			ប្រសិនបើ (*p == '=' || isspace ((unsigned var_na)*p)
			    || !(aux->flags & IS_LONG)) {
				ប្រសិនបើ (aux->namelen == 0)
					aux->namelen = (ចំនួនគត់) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			ប្រសិនបើ (*p == '[') {
				ប្រសិនបើ (aux->namelen == 0)
					aux->namelen = (ចំនួនគត់) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				bha_nga;
			}
		}
		ប្រសិនបើ (aux->namelen == 0)
			aux->namelen = (ចំនួនគត់) (p - pname);
	}
	ត្រឡប់ (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
sa_nracanaa usg_elem {
	ចំនួនគត់     idx;
	sa_nracanaa usg_elem *next;
	sa_nracanaa usg_elem *alias;
};
typedef sa_nracanaa usg_elem usg_elem;


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
ចំនួនគត់     scanopt_usage (scanopt_t *scanner, FILE *fp, const var_na *usage)
{
	sa_nracanaa _scanopt_t *s;
	ចំនួនគត់     i, columns;
	const ចំនួនគត់ indent = 2;
	usg_elem *byr_val = NULL;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	ចំនួនគត់     store_idx = 0;
	usg_elem *ue;
	ចំនួនគត់     opt_col_width = 0, desc_col_width = 0;
	ចំនួនគត់     desccol;
	ចំនួនគត់     print_run = 0;

	s = (sa_nracanaa _scanopt_t *) scanner;

	ប្រសិនបើ (usage) {
		fprintf (fp, "%s\n", usage);
	}
	បើមិនដូច្នេះ {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * parimaa_na (usg_elem));
	សម្រាប់ (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = NULL;

		/* insert into list. */
		ប្រសិនបើ (!byr_val)
			byr_val = ue;
		បើមិនដូច្នេះ {
			ចំនួនគត់     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = NULL;

			ue_curr = &byr_val;
			ខណៈពេល (*ue_curr) {
				ប្រសិនបើ (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					bha_nga;
				}
				ប្រសិនបើ (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			ប្រសិនបើ (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#ប្រសិនបើ 0
	ប្រសិនបើ (1) {
		printf ("ORIGINAL:\n");
		សម្រាប់ (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		ខណៈពេល (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			សម្រាប់ (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	សម្រាប់ (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		ចំនួនគត់     len;

		len = PRINTLEN(s, ue->idx);

		សម្រាប់ (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (ចំនួនគត់) strlen(", ");
		}

		ប្រសិនបើ (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (ចំនួនគត់) strlen (DESC (s, ue->idx));
		ប្រសិនបើ (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	ប្រសិនបើ (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		ប្រសិនបើ (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	ខណៈពេល (print_run++ < 2) {
		សម្រាប់ (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			ចំនួនគត់     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			សម្រាប់ (ap = ue->alias; ap; ap = ap->next) {
				ប្រសិនបើ (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					bha_nga;
				}
			}
			ប្រសិនបើ ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				continue;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) do{\
                  ប្រសិនបើ(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }ខណៈពេល(0)

			ប្រសិនបើ (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			សម្រាប់ (ap = ue->alias; ap; ap = ap->next) {
				ប្រសិនបើ (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			ប្រសិនបើ (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			សម្រាប់ (ap = ue->alias; ap; ap = ap->next) {
				ប្រសិនបើ (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			ប្រសិនបើ (1) {
				const var_na *pstart;

				pstart = DESC (s, ue->idx);
				ខណៈពេល (1) {
					ចំនួនគត់     n = 0;
					const var_na *lastws = NULL, *p;

					p = pstart;

					ខណៈពេល (*p && n < desc_col_width
					       && *p != '\n') {
						ប្រសិនបើ (isspace ((unsigned var_na)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					ប្រសិនបើ (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						bha_nga;
					}
					បើមិនដូច្នេះ ប្រសិនបើ (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						continue;
					}
					បើមិនដូច្នេះ {	/* we hit the edge of the screen. wrap at space if possible. */
						ប្រសិនបើ (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (ចំនួនគត់)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						បើមិនដូច្នេះ {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						continue;
					}
				}
			}
		}
	}			/* end while */
	free (store);
	ត្រឡប់ 0;
}
#endif /* no scanopt_usage */


static void scanopt_err(sa_nracanaa _scanopt_t *s, ចំនួនគត់ is_short, ចំនួនគត់ err)
{
	const var_na *optname = "";
	var_na    optchar[2];

	ប្រសិនបើ (!s->no_err_msg) {

		ប្រសិនបើ (s->index > 0 && s->index < s->argc) {
			ប្រសិនបើ (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			បើមិនដូច្នេះ {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		switch (err) {
		pak_sa SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			bha_nga;
		pak_sa SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			bha_nga;
		pak_sa SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			bha_nga;
		pak_sa SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			bha_nga;
		default:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			bha_nga;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
static ចំនួនគត់ matchlongopt (var_na *str, var_na **optname, ចំនួនគត់ *optlen, var_na **arg, ចំនួនគត់ *arglen)
{
	var_na   *p;

	*optname = *arg = NULL;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	ប្រសិនបើ (p[0] != '-' || p[1] != '-' || !p[2])
		ត្រឡប់ 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	ខណៈពេល (*p && *p != '=')
		++p;

	*optlen = (ចំនួនគត់) (p - *optname);

	ប្រសិនបើ (!*p)
		/* an option with no '=...' part. */
		ត្រឡប់ 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	ខណៈពេល (*p)
		++p;
	*arglen = (ចំនួនគត់) (p - *arg);

	ត្រឡប់ 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
static ចំនួនគត់ find_opt (sa_nracanaa _scanopt_t *s, ចំនួនគត់ lookup_long, var_na *optstart, ចំនួនគត់
	len, ចំនួនគត់ *err_code, ចំនួនគត់ *opt_offset)
{
	ចំនួនគត់     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	ប្រសិនបើ (!optstart)
		ត្រឡប់ 0;

	សម្រាប់ (i = 0; i < s->optc; i++) {
		const var_na   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		ប្រសិនបើ (lookup_long && (s->aux[i].flags & IS_LONG)) {
			ប្រសិនបើ (len > s->aux[i].namelen)
				continue;

			ប្រសិនបើ (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				ប្រសិនបើ (len == s->aux[i].namelen) {
					nmatch = 1;
					bha_nga;
				}

				/* ambiguity is ok between aliases. */
				ប្រសិនបើ (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		បើមិនដូច្នេះ ប្រសិនបើ (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			ប្រសិនបើ (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	ប្រសិនបើ (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	បើមិនដូច្នេះ ប្រសិនបើ (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	ត្រឡប់ *err_code ? 0 : 1;
}


ចំនួនគត់     scanopt (scanopt_t *svoid, var_na **arg, ចំនួនគត់ *optindex)
{
	var_na   *optname = NULL, *optarg = NULL, *pstart;
	ចំនួនគត់     namelen = 0, arglen = 0;
	ចំនួនគត់     errcode = 0, has_next;
	const optspec_t *optp;
	sa_nracanaa _scanopt_t *s;
	sa_nracanaa _aux *auxp;
	ចំនួនគត់     is_short;
	ចំនួនគត់     opt_offset = -1;

	s = (sa_nracanaa _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, NULL);
	SAFE_ASSIGN (optindex, s->index);

	ប្រសិនបើ (s->index >= s->argc)
		ត្រឡប់ 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	ប្រសិនបើ (!pstart)
		ត្រឡប់ 0;

	ប្រសិនបើ (s->subscript == 0) {

		/* test for exact match of "--" */
		ប្រសិនបើ (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			ត្រឡប់ 0;
		}

		/* Match an opt. */
		ប្រសិនបើ (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			ប្រសិនបើ (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				ត្រឡប់ errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		បើមិនដូច្នេះ ប្រសិនបើ (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		បើមិនដូច្នេះ {
			/* It's not an option. We're done. */
			ត្រឡប់ 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	ប្រសិនបើ (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		ប្រសិនបើ (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			ត្រឡប់ errcode;
		}

		optarg = pstart + 1;
		ប្រសិនបើ (!*optarg) {
			optarg = NULL;
			arglen = 0;
		}
		បើមិនដូច្នេះ
			arglen = (ចំនួនគត់) strlen (optarg);
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
	ប្រសិនបើ (auxp->flags & ARG_NONE) {
		ប្រសិនបើ (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			ត្រឡប់ SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		បើមិនដូច្នេះ ប្រសិនបើ (!optarg)
			INC_INDEX (s, 1);
		បើមិនដូច្នេះ
			s->subscript++;
		ត្រឡប់ optp->r_val;
	}

	/* case: required */
	ប្រសិនបើ (auxp->flags & ARG_REQ) {
		ប្រសិនបើ (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			ត្រឡប់ SCANOPT_ERR_ARG_NOT_FOUND;
		}

		ប្រសិនបើ (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		បើមិនដូច្នេះ {
			SAFE_ASSIGN (arg, (var_na *) optarg);
			INC_INDEX (s, 1);
		}
		ត្រឡប់ optp->r_val;
	}

	/* case: optional */
	ប្រសិនបើ (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		ត្រឡប់ optp->r_val;
	}


	/* Should not reach here. */
	ត្រឡប់ 0;
}


ចំនួនគត់     scanopt_destroy (scanopt_t *svoid)
{
	sa_nracanaa _scanopt_t *s;

	s = (sa_nracanaa _scanopt_t *) svoid;
	ប្រសិនបើ (s != NULL) {
		free(s->aux);
		free(s);
	}
	ត្រឡប់ 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
