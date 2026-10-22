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

struct _aux {
	цяло     flags;		/* The above hex flags. */
	цяло     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	цяло     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


struct _scanopt_t {
	const optspec_t *options;	/* List of options. */
	struct _aux *aux;	/* Auxiliary data about options. */
	цяло     optc;		/* Number of options. */
	цяло     argc;		/* Number of args. */
	char  **argv;		/* Array of strings. */
	цяло     index;		/* Used as: argv[index][subscript]. */
	цяло     subscript;
	char    no_err_msg;	/* If true, do not print errors. */
	char    has_long;
	char    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
static const char *NAME(struct _scanopt_t *, цяло);
static цяло PRINTLEN(struct _scanopt_t *, цяло);
static цяло RVAL(struct _scanopt_t *, цяло);
static цяло FLAGS(struct _scanopt_t *, цяло);
static const char *DESC(struct _scanopt_t *, цяло);
static void scanopt_err(struct _scanopt_t *, цяло, цяло);
static цяло matchlongopt(char *, char **, цяло *, char **, цяло *);
static цяло find_opt(struct _scanopt_t *, цяло, char *, цяло, цяло *, цяло *opt_offset);

static const char *NAME (struct _scanopt_t *s, цяло i)
{
	върни s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

static цяло PRINTLEN (struct _scanopt_t *s, цяло i)
{
	върни s->aux[i].printlen;
}

static цяло RVAL (struct _scanopt_t *s, цяло i)
{
	върни s->options[i].r_val;
}

static цяло FLAGS (struct _scanopt_t *s, цяло i)
{
	върни s->aux[i].flags;
}

static const char *DESC (struct _scanopt_t *s, цяло i)
{
	върни s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
static цяло get_cols (void);

static цяло get_cols (void)
{
	char   *env;
	цяло     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	ако (COLS > 0)
		върни COLS;
#endif

	ако ((env = getenv ("COLUMNS")) != NULL)
		cols = atoi (env);

	върни cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    do{                      \
        ако((ptr)!=NULL)      \
            *(ptr) = val;    \
    }докато(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    do{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }докато(0)

scanopt_t *scanopt_init (const optspec_t *options, цяло argc, char **argv, цяло flags)
{
	цяло     i;
	struct _scanopt_t *s;
	s = malloc(sizeof (struct _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (char **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_msg = (flags & SCANOPT_NO_ERR_MSG);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	докато (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * sizeof (struct _aux));

	за (i = 0; i < s->optc; i++) {
		const unsigned char *p, *pname;
		const struct optspec_t *opt;
		struct _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		ако (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (const unsigned char *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		иначе {
			pname = (const unsigned char *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (цяло) strlen (opt->opt_fmt);

		aux->namelen = 0;
		за (p = pname + 1; *p; p++) {
			/* detect required arg */
			ако (*p == '=' || isspace ((unsigned char)*p)
			    || !(aux->flags & IS_LONG)) {
				ако (aux->namelen == 0)
					aux->namelen = (цяло) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			ако (*p == '[') {
				ако (aux->namelen == 0)
					aux->namelen = (цяло) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				break;
			}
		}
		ако (aux->namelen == 0)
			aux->namelen = (цяло) (p - pname);
	}
	върни (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
struct usg_elem {
	цяло     idx;
	struct usg_elem *next;
	struct usg_elem *alias;
};
typedef struct usg_elem usg_elem;


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
цяло     scanopt_usage (scanopt_t *scanner, FILE *fp, const char *usage)
{
	struct _scanopt_t *s;
	цяло     i, columns;
	const цяло indent = 2;
	usg_elem *byr_val = NULL;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	цяло     store_idx = 0;
	usg_elem *ue;
	цяло     opt_col_width = 0, desc_col_width = 0;
	цяло     desccol;
	цяло     print_run = 0;

	s = (struct _scanopt_t *) scanner;

	ако (usage) {
		fprintf (fp, "%s\n", usage);
	}
	иначе {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * sizeof (usg_elem));
	за (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = NULL;

		/* insert into list. */
		ако (!byr_val)
			byr_val = ue;
		иначе {
			цяло     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = NULL;

			ue_curr = &byr_val;
			докато (*ue_curr) {
				ако (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					break;
				}
				ако (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			ако (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#ако 0
	ако (1) {
		printf ("ORIGINAL:\n");
		за (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		докато (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			за (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	за (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		цяло     len;

		len = PRINTLEN(s, ue->idx);

		за (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (цяло) strlen(", ");
		}

		ако (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (цяло) strlen (DESC (s, ue->idx));
		ако (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	ако (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		ако (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	докато (print_run++ < 2) {
		за (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			цяло     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			за (ap = ue->alias; ap; ap = ap->next) {
				ако (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					break;
				}
			}
			ако ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				continue;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) do{\
                  ако(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }докато(0)

			ако (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			за (ap = ue->alias; ap; ap = ap->next) {
				ако (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			ако (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			за (ap = ue->alias; ap; ap = ap->next) {
				ако (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			ако (1) {
				const char *pstart;

				pstart = DESC (s, ue->idx);
				докато (1) {
					цяло     n = 0;
					const char *lastws = NULL, *p;

					p = pstart;

					докато (*p && n < desc_col_width
					       && *p != '\n') {
						ако (isspace ((unsigned char)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					ако (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						break;
					}
					иначе ако (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						continue;
					}
					иначе {	/* we hit the edge of the screen. wrap at space if possible. */
						ако (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (цяло)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						иначе {
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
	върни 0;
}
#endif /* no scanopt_usage */


static void scanopt_err(struct _scanopt_t *s, цяло is_short, цяло err)
{
	const char *optname = "";
	char    optchar[2];

	ако (!s->no_err_msg) {

		ако (s->index > 0 && s->index < s->argc) {
			ако (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			иначе {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		switch (err) {
		case SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			break;
		case SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			break;
		case SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			break;
		case SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			break;
		default:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			break;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
static цяло matchlongopt (char *str, char **optname, цяло *optlen, char **arg, цяло *arglen)
{
	char   *p;

	*optname = *arg = NULL;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	ако (p[0] != '-' || p[1] != '-' || !p[2])
		върни 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	докато (*p && *p != '=')
		++p;

	*optlen = (цяло) (p - *optname);

	ако (!*p)
		/* an option with no '=...' part. */
		върни 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	докато (*p)
		++p;
	*arglen = (цяло) (p - *arg);

	върни 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
static цяло find_opt (struct _scanopt_t *s, цяло lookup_long, char *optstart, цяло
	len, цяло *err_code, цяло *opt_offset)
{
	цяло     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	ако (!optstart)
		върни 0;

	за (i = 0; i < s->optc; i++) {
		const char   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		ако (lookup_long && (s->aux[i].flags & IS_LONG)) {
			ако (len > s->aux[i].namelen)
				continue;

			ако (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				ако (len == s->aux[i].namelen) {
					nmatch = 1;
					break;
				}

				/* ambiguity is ok between aliases. */
				ако (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		иначе ако (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			ако (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	ако (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	иначе ако (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	върни *err_code ? 0 : 1;
}


цяло     scanopt (scanopt_t *svoid, char **arg, цяло *optindex)
{
	char   *optname = NULL, *optarg = NULL, *pstart;
	цяло     namelen = 0, arglen = 0;
	цяло     errcode = 0, has_next;
	const optspec_t *optp;
	struct _scanopt_t *s;
	struct _aux *auxp;
	цяло     is_short;
	цяло     opt_offset = -1;

	s = (struct _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, NULL);
	SAFE_ASSIGN (optindex, s->index);

	ако (s->index >= s->argc)
		върни 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	ако (!pstart)
		върни 0;

	ако (s->subscript == 0) {

		/* test for exact match of "--" */
		ако (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			върни 0;
		}

		/* Match an opt. */
		ако (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			ако (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				върни errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		иначе ако (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		иначе {
			/* It's not an option. We're done. */
			върни 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	ако (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		ако (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			върни errcode;
		}

		optarg = pstart + 1;
		ако (!*optarg) {
			optarg = NULL;
			arglen = 0;
		}
		иначе
			arglen = (цяло) strlen (optarg);
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
	ако (auxp->flags & ARG_NONE) {
		ако (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			върни SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		иначе ако (!optarg)
			INC_INDEX (s, 1);
		иначе
			s->subscript++;
		върни optp->r_val;
	}

	/* case: required */
	ако (auxp->flags & ARG_REQ) {
		ако (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			върни SCANOPT_ERR_ARG_NOT_FOUND;
		}

		ако (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		иначе {
			SAFE_ASSIGN (arg, (char *) optarg);
			INC_INDEX (s, 1);
		}
		върни optp->r_val;
	}

	/* case: optional */
	ако (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		върни optp->r_val;
	}


	/* Should not reach here. */
	върни 0;
}


цяло     scanopt_destroy (scanopt_t *svoid)
{
	struct _scanopt_t *s;

	s = (struct _scanopt_t *) svoid;
	ако (s != NULL) {
		free(s->aux);
		free(s);
	}
	върни 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
