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
	ကိန်းပြည့်     flags;		/* The above hex flags. */
	ကိန်းပြည့်     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	ကိန်းပြည့်     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


sa_nracanaa _scanopt_t {
	const optspec_t *options;	/* List of options. */
	sa_nracanaa _aux *aux;	/* Auxiliary data about options. */
	ကိန်းပြည့်     optc;		/* Number of options. */
	ကိန်းပြည့်     argc;		/* Number of args. */
	var_na  **argv;		/* Array of strings. */
	ကိန်းပြည့်     index;		/* Used as: argv[index][subscript]. */
	ကိန်းပြည့်     subscript;
	var_na    no_err_msg;	/* If true, do not print errors. */
	var_na    has_long;
	var_na    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
static const var_na *NAME(sa_nracanaa _scanopt_t *, ကိန်းပြည့်);
static ကိန်းပြည့် PRINTLEN(sa_nracanaa _scanopt_t *, ကိန်းပြည့်);
static ကိန်းပြည့် RVAL(sa_nracanaa _scanopt_t *, ကိန်းပြည့်);
static ကိန်းပြည့် FLAGS(sa_nracanaa _scanopt_t *, ကိန်းပြည့်);
static const var_na *DESC(sa_nracanaa _scanopt_t *, ကိန်းပြည့်);
static void scanopt_err(sa_nracanaa _scanopt_t *, ကိန်းပြည့်, ကိန်းပြည့်);
static ကိန်းပြည့် matchlongopt(var_na *, var_na **, ကိန်းပြည့် *, var_na **, ကိန်းပြည့် *);
static ကိန်းပြည့် find_opt(sa_nracanaa _scanopt_t *, ကိန်းပြည့်, var_na *, ကိန်းပြည့်, ကိန်းပြည့် *, ကိန်းပြည့် *opt_offset);

static const var_na *NAME (sa_nracanaa _scanopt_t *s, ကိန်းပြည့် i)
{
	ပြန်ပေး s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

static ကိန်းပြည့် PRINTLEN (sa_nracanaa _scanopt_t *s, ကိန်းပြည့် i)
{
	ပြန်ပေး s->aux[i].printlen;
}

static ကိန်းပြည့် RVAL (sa_nracanaa _scanopt_t *s, ကိန်းပြည့် i)
{
	ပြန်ပေး s->options[i].r_val;
}

static ကိန်းပြည့် FLAGS (sa_nracanaa _scanopt_t *s, ကိန်းပြည့် i)
{
	ပြန်ပေး s->aux[i].flags;
}

static const var_na *DESC (sa_nracanaa _scanopt_t *s, ကိန်းပြည့် i)
{
	ပြန်ပေး s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
static ကိန်းပြည့် get_cols (void);

static ကိန်းပြည့် get_cols (void)
{
	var_na   *env;
	ကိန်းပြည့်     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	အကယ်၍ (COLS > 0)
		ပြန်ပေး COLS;
#endif

	အကယ်၍ ((env = getenv ("COLUMNS")) != NULL)
		cols = atoi (env);

	ပြန်ပေး cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    do{                      \
        အကယ်၍((ptr)!=NULL)      \
            *(ptr) = val;    \
    }နေစဉ်(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    do{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }နေစဉ်(0)

scanopt_t *scanopt_init (const optspec_t *options, ကိန်းပြည့် argc, var_na **argv, ကိန်းပြည့် flags)
{
	ကိန်းပြည့်     i;
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
	နေစဉ် (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * parimaa_na (sa_nracanaa _aux));

	အတွက် (i = 0; i < s->optc; i++) {
		const unsigned var_na *p, *pname;
		const sa_nracanaa optspec_t *opt;
		sa_nracanaa _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		အကယ်၍ (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (const unsigned var_na *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		မဟုတ်ပါက {
			pname = (const unsigned var_na *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (ကိန်းပြည့်) strlen (opt->opt_fmt);

		aux->namelen = 0;
		အတွက် (p = pname + 1; *p; p++) {
			/* detect required arg */
			အကယ်၍ (*p == '=' || isspace ((unsigned var_na)*p)
			    || !(aux->flags & IS_LONG)) {
				အကယ်၍ (aux->namelen == 0)
					aux->namelen = (ကိန်းပြည့်) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			အကယ်၍ (*p == '[') {
				အကယ်၍ (aux->namelen == 0)
					aux->namelen = (ကိန်းပြည့်) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				bha_nga;
			}
		}
		အကယ်၍ (aux->namelen == 0)
			aux->namelen = (ကိန်းပြည့်) (p - pname);
	}
	ပြန်ပေး (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
sa_nracanaa usg_elem {
	ကိန်းပြည့်     idx;
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
ကိန်းပြည့်     scanopt_usage (scanopt_t *scanner, FILE *fp, const var_na *usage)
{
	sa_nracanaa _scanopt_t *s;
	ကိန်းပြည့်     i, columns;
	const ကိန်းပြည့် indent = 2;
	usg_elem *byr_val = NULL;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	ကိန်းပြည့်     store_idx = 0;
	usg_elem *ue;
	ကိန်းပြည့်     opt_col_width = 0, desc_col_width = 0;
	ကိန်းပြည့်     desccol;
	ကိန်းပြည့်     print_run = 0;

	s = (sa_nracanaa _scanopt_t *) scanner;

	အကယ်၍ (usage) {
		fprintf (fp, "%s\n", usage);
	}
	မဟုတ်ပါက {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * parimaa_na (usg_elem));
	အတွက် (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = NULL;

		/* insert into list. */
		အကယ်၍ (!byr_val)
			byr_val = ue;
		မဟုတ်ပါက {
			ကိန်းပြည့်     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = NULL;

			ue_curr = &byr_val;
			နေစဉ် (*ue_curr) {
				အကယ်၍ (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					bha_nga;
				}
				အကယ်၍ (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			အကယ်၍ (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#အကယ်၍ 0
	အကယ်၍ (1) {
		printf ("ORIGINAL:\n");
		အတွက် (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		နေစဉ် (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			အတွက် (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	အတွက် (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		ကိန်းပြည့်     len;

		len = PRINTLEN(s, ue->idx);

		အတွက် (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (ကိန်းပြည့်) strlen(", ");
		}

		အကယ်၍ (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (ကိန်းပြည့်) strlen (DESC (s, ue->idx));
		အကယ်၍ (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	အကယ်၍ (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		အကယ်၍ (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	နေစဉ် (print_run++ < 2) {
		အတွက် (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			ကိန်းပြည့်     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			အတွက် (ap = ue->alias; ap; ap = ap->next) {
				အကယ်၍ (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					bha_nga;
				}
			}
			အကယ်၍ ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				continue;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) do{\
                  အကယ်၍(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }နေစဉ်(0)

			အကယ်၍ (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			အတွက် (ap = ue->alias; ap; ap = ap->next) {
				အကယ်၍ (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			အကယ်၍ (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			အတွက် (ap = ue->alias; ap; ap = ap->next) {
				အကယ်၍ (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			အကယ်၍ (1) {
				const var_na *pstart;

				pstart = DESC (s, ue->idx);
				နေစဉ် (1) {
					ကိန်းပြည့်     n = 0;
					const var_na *lastws = NULL, *p;

					p = pstart;

					နေစဉ် (*p && n < desc_col_width
					       && *p != '\n') {
						အကယ်၍ (isspace ((unsigned var_na)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					အကယ်၍ (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						bha_nga;
					}
					မဟုတ်ပါက အကယ်၍ (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						continue;
					}
					မဟုတ်ပါက {	/* we hit the edge of the screen. wrap at space if possible. */
						အကယ်၍ (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (ကိန်းပြည့်)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						မဟုတ်ပါက {
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
	ပြန်ပေး 0;
}
#endif /* no scanopt_usage */


static void scanopt_err(sa_nracanaa _scanopt_t *s, ကိန်းပြည့် is_short, ကိန်းပြည့် err)
{
	const var_na *optname = "";
	var_na    optchar[2];

	အကယ်၍ (!s->no_err_msg) {

		အကယ်၍ (s->index > 0 && s->index < s->argc) {
			အကယ်၍ (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			မဟုတ်ပါက {
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
static ကိန်းပြည့် matchlongopt (var_na *str, var_na **optname, ကိန်းပြည့် *optlen, var_na **arg, ကိန်းပြည့် *arglen)
{
	var_na   *p;

	*optname = *arg = NULL;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	အကယ်၍ (p[0] != '-' || p[1] != '-' || !p[2])
		ပြန်ပေး 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	နေစဉ် (*p && *p != '=')
		++p;

	*optlen = (ကိန်းပြည့်) (p - *optname);

	အကယ်၍ (!*p)
		/* an option with no '=...' part. */
		ပြန်ပေး 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	နေစဉ် (*p)
		++p;
	*arglen = (ကိန်းပြည့်) (p - *arg);

	ပြန်ပေး 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
static ကိန်းပြည့် find_opt (sa_nracanaa _scanopt_t *s, ကိန်းပြည့် lookup_long, var_na *optstart, ကိန်းပြည့်
	len, ကိန်းပြည့် *err_code, ကိန်းပြည့် *opt_offset)
{
	ကိန်းပြည့်     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	အကယ်၍ (!optstart)
		ပြန်ပေး 0;

	အတွက် (i = 0; i < s->optc; i++) {
		const var_na   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		အကယ်၍ (lookup_long && (s->aux[i].flags & IS_LONG)) {
			အကယ်၍ (len > s->aux[i].namelen)
				continue;

			အကယ်၍ (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				အကယ်၍ (len == s->aux[i].namelen) {
					nmatch = 1;
					bha_nga;
				}

				/* ambiguity is ok between aliases. */
				အကယ်၍ (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		မဟုတ်ပါက အကယ်၍ (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			အကယ်၍ (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	အကယ်၍ (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	မဟုတ်ပါက အကယ်၍ (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	ပြန်ပေး *err_code ? 0 : 1;
}


ကိန်းပြည့်     scanopt (scanopt_t *svoid, var_na **arg, ကိန်းပြည့် *optindex)
{
	var_na   *optname = NULL, *optarg = NULL, *pstart;
	ကိန်းပြည့်     namelen = 0, arglen = 0;
	ကိန်းပြည့်     errcode = 0, has_next;
	const optspec_t *optp;
	sa_nracanaa _scanopt_t *s;
	sa_nracanaa _aux *auxp;
	ကိန်းပြည့်     is_short;
	ကိန်းပြည့်     opt_offset = -1;

	s = (sa_nracanaa _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, NULL);
	SAFE_ASSIGN (optindex, s->index);

	အကယ်၍ (s->index >= s->argc)
		ပြန်ပေး 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	အကယ်၍ (!pstart)
		ပြန်ပေး 0;

	အကယ်၍ (s->subscript == 0) {

		/* test for exact match of "--" */
		အကယ်၍ (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			ပြန်ပေး 0;
		}

		/* Match an opt. */
		အကယ်၍ (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			အကယ်၍ (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				ပြန်ပေး errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		မဟုတ်ပါက အကယ်၍ (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		မဟုတ်ပါက {
			/* It's not an option. We're done. */
			ပြန်ပေး 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	အကယ်၍ (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		အကယ်၍ (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			ပြန်ပေး errcode;
		}

		optarg = pstart + 1;
		အကယ်၍ (!*optarg) {
			optarg = NULL;
			arglen = 0;
		}
		မဟုတ်ပါက
			arglen = (ကိန်းပြည့်) strlen (optarg);
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
	အကယ်၍ (auxp->flags & ARG_NONE) {
		အကယ်၍ (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			ပြန်ပေး SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		မဟုတ်ပါက အကယ်၍ (!optarg)
			INC_INDEX (s, 1);
		မဟုတ်ပါက
			s->subscript++;
		ပြန်ပေး optp->r_val;
	}

	/* case: required */
	အကယ်၍ (auxp->flags & ARG_REQ) {
		အကယ်၍ (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			ပြန်ပေး SCANOPT_ERR_ARG_NOT_FOUND;
		}

		အကယ်၍ (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		မဟုတ်ပါက {
			SAFE_ASSIGN (arg, (var_na *) optarg);
			INC_INDEX (s, 1);
		}
		ပြန်ပေး optp->r_val;
	}

	/* case: optional */
	အကယ်၍ (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		ပြန်ပေး optp->r_val;
	}


	/* Should not reach here. */
	ပြန်ပေး 0;
}


ကိန်းပြည့်     scanopt_destroy (scanopt_t *svoid)
{
	sa_nracanaa _scanopt_t *s;

	s = (sa_nracanaa _scanopt_t *) svoid;
	အကယ်၍ (s != NULL) {
		free(s->aux);
		free(s);
	}
	ပြန်ပေး 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
