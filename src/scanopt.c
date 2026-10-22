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
	ཧྲིལ     flags;		/* The above hex flags. */
	ཧྲིལ     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	ཧྲིལ     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


sa_nracanaa _scanopt_t {
	const optspec_t *options;	/* List of options. */
	sa_nracanaa _aux *aux;	/* Auxiliary data about options. */
	ཧྲིལ     optc;		/* Number of options. */
	ཧྲིལ     argc;		/* Number of args. */
	var_na  **argv;		/* Array of strings. */
	ཧྲིལ     index;		/* Used as: argv[index][subscript]. */
	ཧྲིལ     subscript;
	var_na    no_err_msg;	/* If true, do not print errors. */
	var_na    has_long;
	var_na    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
static const var_na *NAME(sa_nracanaa _scanopt_t *, ཧྲིལ);
static ཧྲིལ PRINTLEN(sa_nracanaa _scanopt_t *, ཧྲིལ);
static ཧྲིལ RVAL(sa_nracanaa _scanopt_t *, ཧྲིལ);
static ཧྲིལ FLAGS(sa_nracanaa _scanopt_t *, ཧྲིལ);
static const var_na *DESC(sa_nracanaa _scanopt_t *, ཧྲིལ);
static void scanopt_err(sa_nracanaa _scanopt_t *, ཧྲིལ, ཧྲིལ);
static ཧྲིལ matchlongopt(var_na *, var_na **, ཧྲིལ *, var_na **, ཧྲིལ *);
static ཧྲིལ find_opt(sa_nracanaa _scanopt_t *, ཧྲིལ, var_na *, ཧྲིལ, ཧྲིལ *, ཧྲིལ *opt_offset);

static const var_na *NAME (sa_nracanaa _scanopt_t *s, ཧྲིལ i)
{
	ཕྱིར s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

static ཧྲིལ PRINTLEN (sa_nracanaa _scanopt_t *s, ཧྲིལ i)
{
	ཕྱིར s->aux[i].printlen;
}

static ཧྲིལ RVAL (sa_nracanaa _scanopt_t *s, ཧྲིལ i)
{
	ཕྱིར s->options[i].r_val;
}

static ཧྲིལ FLAGS (sa_nracanaa _scanopt_t *s, ཧྲིལ i)
{
	ཕྱིར s->aux[i].flags;
}

static const var_na *DESC (sa_nracanaa _scanopt_t *s, ཧྲིལ i)
{
	ཕྱིར s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
static ཧྲིལ get_cols (void);

static ཧྲིལ get_cols (void)
{
	var_na   *env;
	ཧྲིལ     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	གལ་ཏེ (COLS > 0)
		ཕྱིར COLS;
#endif

	གལ་ཏེ ((env = getenv ("COLUMNS")) != NULL)
		cols = atoi (env);

	ཕྱིར cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    do{                      \
        གལ་ཏེ((ptr)!=NULL)      \
            *(ptr) = val;    \
    }སྐབས(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    do{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }སྐབས(0)

scanopt_t *scanopt_init (const optspec_t *options, ཧྲིལ argc, var_na **argv, ཧྲིལ flags)
{
	ཧྲིལ     i;
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
	སྐབས (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * parimaa_na (sa_nracanaa _aux));

	ཆེད་དུ (i = 0; i < s->optc; i++) {
		const unsigned var_na *p, *pname;
		const sa_nracanaa optspec_t *opt;
		sa_nracanaa _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		གལ་ཏེ (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (const unsigned var_na *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		དེ་མིན {
			pname = (const unsigned var_na *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (ཧྲིལ) strlen (opt->opt_fmt);

		aux->namelen = 0;
		ཆེད་དུ (p = pname + 1; *p; p++) {
			/* detect required arg */
			གལ་ཏེ (*p == '=' || isspace ((unsigned var_na)*p)
			    || !(aux->flags & IS_LONG)) {
				གལ་ཏེ (aux->namelen == 0)
					aux->namelen = (ཧྲིལ) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			གལ་ཏེ (*p == '[') {
				གལ་ཏེ (aux->namelen == 0)
					aux->namelen = (ཧྲིལ) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				bha_nga;
			}
		}
		གལ་ཏེ (aux->namelen == 0)
			aux->namelen = (ཧྲིལ) (p - pname);
	}
	ཕྱིར (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
sa_nracanaa usg_elem {
	ཧྲིལ     idx;
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
ཧྲིལ     scanopt_usage (scanopt_t *scanner, FILE *fp, const var_na *usage)
{
	sa_nracanaa _scanopt_t *s;
	ཧྲིལ     i, columns;
	const ཧྲིལ indent = 2;
	usg_elem *byr_val = NULL;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	ཧྲིལ     store_idx = 0;
	usg_elem *ue;
	ཧྲིལ     opt_col_width = 0, desc_col_width = 0;
	ཧྲིལ     desccol;
	ཧྲིལ     print_run = 0;

	s = (sa_nracanaa _scanopt_t *) scanner;

	གལ་ཏེ (usage) {
		fprintf (fp, "%s\n", usage);
	}
	དེ་མིན {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * parimaa_na (usg_elem));
	ཆེད་དུ (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = NULL;

		/* insert into list. */
		གལ་ཏེ (!byr_val)
			byr_val = ue;
		དེ་མིན {
			ཧྲིལ     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = NULL;

			ue_curr = &byr_val;
			སྐབས (*ue_curr) {
				གལ་ཏེ (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					bha_nga;
				}
				གལ་ཏེ (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			གལ་ཏེ (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#གལ་ཏེ 0
	གལ་ཏེ (1) {
		printf ("ORIGINAL:\n");
		ཆེད་དུ (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		སྐབས (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			ཆེད་དུ (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	ཆེད་དུ (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		ཧྲིལ     len;

		len = PRINTLEN(s, ue->idx);

		ཆེད་དུ (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (ཧྲིལ) strlen(", ");
		}

		གལ་ཏེ (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (ཧྲིལ) strlen (DESC (s, ue->idx));
		གལ་ཏེ (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	གལ་ཏེ (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		གལ་ཏེ (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	སྐབས (print_run++ < 2) {
		ཆེད་དུ (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			ཧྲིལ     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			ཆེད་དུ (ap = ue->alias; ap; ap = ap->next) {
				གལ་ཏེ (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					bha_nga;
				}
			}
			གལ་ཏེ ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				continue;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) do{\
                  གལ་ཏེ(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }སྐབས(0)

			གལ་ཏེ (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			ཆེད་དུ (ap = ue->alias; ap; ap = ap->next) {
				གལ་ཏེ (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			གལ་ཏེ (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			ཆེད་དུ (ap = ue->alias; ap; ap = ap->next) {
				གལ་ཏེ (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			གལ་ཏེ (1) {
				const var_na *pstart;

				pstart = DESC (s, ue->idx);
				སྐབས (1) {
					ཧྲིལ     n = 0;
					const var_na *lastws = NULL, *p;

					p = pstart;

					སྐབས (*p && n < desc_col_width
					       && *p != '\n') {
						གལ་ཏེ (isspace ((unsigned var_na)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					གལ་ཏེ (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						bha_nga;
					}
					དེ་མིན གལ་ཏེ (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						continue;
					}
					དེ་མིན {	/* we hit the edge of the screen. wrap at space if possible. */
						གལ་ཏེ (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (ཧྲིལ)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						དེ་མིན {
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
	ཕྱིར 0;
}
#endif /* no scanopt_usage */


static void scanopt_err(sa_nracanaa _scanopt_t *s, ཧྲིལ is_short, ཧྲིལ err)
{
	const var_na *optname = "";
	var_na    optchar[2];

	གལ་ཏེ (!s->no_err_msg) {

		གལ་ཏེ (s->index > 0 && s->index < s->argc) {
			གལ་ཏེ (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			དེ་མིན {
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
static ཧྲིལ matchlongopt (var_na *str, var_na **optname, ཧྲིལ *optlen, var_na **arg, ཧྲིལ *arglen)
{
	var_na   *p;

	*optname = *arg = NULL;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	གལ་ཏེ (p[0] != '-' || p[1] != '-' || !p[2])
		ཕྱིར 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	སྐབས (*p && *p != '=')
		++p;

	*optlen = (ཧྲིལ) (p - *optname);

	གལ་ཏེ (!*p)
		/* an option with no '=...' part. */
		ཕྱིར 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	སྐབས (*p)
		++p;
	*arglen = (ཧྲིལ) (p - *arg);

	ཕྱིར 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
static ཧྲིལ find_opt (sa_nracanaa _scanopt_t *s, ཧྲིལ lookup_long, var_na *optstart, ཧྲིལ
	len, ཧྲིལ *err_code, ཧྲིལ *opt_offset)
{
	ཧྲིལ     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	གལ་ཏེ (!optstart)
		ཕྱིར 0;

	ཆེད་དུ (i = 0; i < s->optc; i++) {
		const var_na   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		གལ་ཏེ (lookup_long && (s->aux[i].flags & IS_LONG)) {
			གལ་ཏེ (len > s->aux[i].namelen)
				continue;

			གལ་ཏེ (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				གལ་ཏེ (len == s->aux[i].namelen) {
					nmatch = 1;
					bha_nga;
				}

				/* ambiguity is ok between aliases. */
				གལ་ཏེ (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		དེ་མིན གལ་ཏེ (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			གལ་ཏེ (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	གལ་ཏེ (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	དེ་མིན གལ་ཏེ (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	ཕྱིར *err_code ? 0 : 1;
}


ཧྲིལ     scanopt (scanopt_t *svoid, var_na **arg, ཧྲིལ *optindex)
{
	var_na   *optname = NULL, *optarg = NULL, *pstart;
	ཧྲིལ     namelen = 0, arglen = 0;
	ཧྲིལ     errcode = 0, has_next;
	const optspec_t *optp;
	sa_nracanaa _scanopt_t *s;
	sa_nracanaa _aux *auxp;
	ཧྲིལ     is_short;
	ཧྲིལ     opt_offset = -1;

	s = (sa_nracanaa _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, NULL);
	SAFE_ASSIGN (optindex, s->index);

	གལ་ཏེ (s->index >= s->argc)
		ཕྱིར 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	གལ་ཏེ (!pstart)
		ཕྱིར 0;

	གལ་ཏེ (s->subscript == 0) {

		/* test for exact match of "--" */
		གལ་ཏེ (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			ཕྱིར 0;
		}

		/* Match an opt. */
		གལ་ཏེ (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			གལ་ཏེ (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				ཕྱིར errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		དེ་མིན གལ་ཏེ (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		དེ་མིན {
			/* It's not an option. We're done. */
			ཕྱིར 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	གལ་ཏེ (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		གལ་ཏེ (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			ཕྱིར errcode;
		}

		optarg = pstart + 1;
		གལ་ཏེ (!*optarg) {
			optarg = NULL;
			arglen = 0;
		}
		དེ་མིན
			arglen = (ཧྲིལ) strlen (optarg);
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
	གལ་ཏེ (auxp->flags & ARG_NONE) {
		གལ་ཏེ (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			ཕྱིར SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		དེ་མིན གལ་ཏེ (!optarg)
			INC_INDEX (s, 1);
		དེ་མིན
			s->subscript++;
		ཕྱིར optp->r_val;
	}

	/* case: required */
	གལ་ཏེ (auxp->flags & ARG_REQ) {
		གལ་ཏེ (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			ཕྱིར SCANOPT_ERR_ARG_NOT_FOUND;
		}

		གལ་ཏེ (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		དེ་མིན {
			SAFE_ASSIGN (arg, (var_na *) optarg);
			INC_INDEX (s, 1);
		}
		ཕྱིར optp->r_val;
	}

	/* case: optional */
	གལ་ཏེ (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		ཕྱིར optp->r_val;
	}


	/* Should not reach here. */
	ཕྱིར 0;
}


ཧྲིལ     scanopt_destroy (scanopt_t *svoid)
{
	sa_nracanaa _scanopt_t *s;

	s = (sa_nracanaa _scanopt_t *) svoid;
	གལ་ཏེ (s != NULL) {
		free(s->aux);
		free(s);
	}
	ཕྱིར 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
