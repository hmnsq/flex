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
	정수     flags;		/* The above hex flags. */
	정수     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	정수     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


struct _scanopt_t {
	const optspec_t *options;	/* List of options. */
	struct _aux *aux;	/* Auxiliary data about options. */
	정수     optc;		/* Number of options. */
	정수     argc;		/* Number of args. */
	char  **argv;		/* Array of strings. */
	정수     index;		/* Used as: argv[index][subscript]. */
	정수     subscript;
	char    no_err_msg;	/* If true, do not print errors. */
	char    has_long;
	char    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
static const char *NAME(struct _scanopt_t *, 정수);
static 정수 PRINTLEN(struct _scanopt_t *, 정수);
static 정수 RVAL(struct _scanopt_t *, 정수);
static 정수 FLAGS(struct _scanopt_t *, 정수);
static const char *DESC(struct _scanopt_t *, 정수);
static void scanopt_err(struct _scanopt_t *, 정수, 정수);
static 정수 matchlongopt(char *, char **, 정수 *, char **, 정수 *);
static 정수 find_opt(struct _scanopt_t *, 정수, char *, 정수, 정수 *, 정수 *opt_offset);

static const char *NAME (struct _scanopt_t *s, 정수 i)
{
	반환 s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

static 정수 PRINTLEN (struct _scanopt_t *s, 정수 i)
{
	반환 s->aux[i].printlen;
}

static 정수 RVAL (struct _scanopt_t *s, 정수 i)
{
	반환 s->options[i].r_val;
}

static 정수 FLAGS (struct _scanopt_t *s, 정수 i)
{
	반환 s->aux[i].flags;
}

static const char *DESC (struct _scanopt_t *s, 정수 i)
{
	반환 s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
static 정수 get_cols (void);

static 정수 get_cols (void)
{
	char   *env;
	정수     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	만약 (COLS > 0)
		반환 COLS;
#endif

	만약 ((env = getenv ("COLUMNS")) != NULL)
		cols = atoi (env);

	반환 cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    do{                      \
        만약((ptr)!=NULL)      \
            *(ptr) = val;    \
    }동안(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    do{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }동안(0)

scanopt_t *scanopt_init (const optspec_t *options, 정수 argc, char **argv, 정수 flags)
{
	정수     i;
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
	동안 (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * sizeof (struct _aux));

	위해 (i = 0; i < s->optc; i++) {
		const unsigned char *p, *pname;
		const struct optspec_t *opt;
		struct _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		만약 (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (const unsigned char *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		아니면 {
			pname = (const unsigned char *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (정수) strlen (opt->opt_fmt);

		aux->namelen = 0;
		위해 (p = pname + 1; *p; p++) {
			/* detect required arg */
			만약 (*p == '=' || isspace ((unsigned char)*p)
			    || !(aux->flags & IS_LONG)) {
				만약 (aux->namelen == 0)
					aux->namelen = (정수) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			만약 (*p == '[') {
				만약 (aux->namelen == 0)
					aux->namelen = (정수) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				break;
			}
		}
		만약 (aux->namelen == 0)
			aux->namelen = (정수) (p - pname);
	}
	반환 (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
struct usg_elem {
	정수     idx;
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
정수     scanopt_usage (scanopt_t *scanner, FILE *fp, const char *usage)
{
	struct _scanopt_t *s;
	정수     i, columns;
	const 정수 indent = 2;
	usg_elem *byr_val = NULL;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	정수     store_idx = 0;
	usg_elem *ue;
	정수     opt_col_width = 0, desc_col_width = 0;
	정수     desccol;
	정수     print_run = 0;

	s = (struct _scanopt_t *) scanner;

	만약 (usage) {
		fprintf (fp, "%s\n", usage);
	}
	아니면 {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * sizeof (usg_elem));
	위해 (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = NULL;

		/* insert into list. */
		만약 (!byr_val)
			byr_val = ue;
		아니면 {
			정수     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = NULL;

			ue_curr = &byr_val;
			동안 (*ue_curr) {
				만약 (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					break;
				}
				만약 (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			만약 (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#만약 0
	만약 (1) {
		printf ("ORIGINAL:\n");
		위해 (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		동안 (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			위해 (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	위해 (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		정수     len;

		len = PRINTLEN(s, ue->idx);

		위해 (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (정수) strlen(", ");
		}

		만약 (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (정수) strlen (DESC (s, ue->idx));
		만약 (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	만약 (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		만약 (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	동안 (print_run++ < 2) {
		위해 (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			정수     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			위해 (ap = ue->alias; ap; ap = ap->next) {
				만약 (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					break;
				}
			}
			만약 ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				continue;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) do{\
                  만약(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }동안(0)

			만약 (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			위해 (ap = ue->alias; ap; ap = ap->next) {
				만약 (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			만약 (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			위해 (ap = ue->alias; ap; ap = ap->next) {
				만약 (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			만약 (1) {
				const char *pstart;

				pstart = DESC (s, ue->idx);
				동안 (1) {
					정수     n = 0;
					const char *lastws = NULL, *p;

					p = pstart;

					동안 (*p && n < desc_col_width
					       && *p != '\n') {
						만약 (isspace ((unsigned char)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					만약 (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						break;
					}
					아니면 만약 (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						continue;
					}
					아니면 {	/* we hit the edge of the screen. wrap at space if possible. */
						만약 (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (정수)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						아니면 {
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
	반환 0;
}
#endif /* no scanopt_usage */


static void scanopt_err(struct _scanopt_t *s, 정수 is_short, 정수 err)
{
	const char *optname = "";
	char    optchar[2];

	만약 (!s->no_err_msg) {

		만약 (s->index > 0 && s->index < s->argc) {
			만약 (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			아니면 {
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
static 정수 matchlongopt (char *str, char **optname, 정수 *optlen, char **arg, 정수 *arglen)
{
	char   *p;

	*optname = *arg = NULL;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	만약 (p[0] != '-' || p[1] != '-' || !p[2])
		반환 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	동안 (*p && *p != '=')
		++p;

	*optlen = (정수) (p - *optname);

	만약 (!*p)
		/* an option with no '=...' part. */
		반환 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	동안 (*p)
		++p;
	*arglen = (정수) (p - *arg);

	반환 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
static 정수 find_opt (struct _scanopt_t *s, 정수 lookup_long, char *optstart, 정수
	len, 정수 *err_code, 정수 *opt_offset)
{
	정수     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	만약 (!optstart)
		반환 0;

	위해 (i = 0; i < s->optc; i++) {
		const char   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		만약 (lookup_long && (s->aux[i].flags & IS_LONG)) {
			만약 (len > s->aux[i].namelen)
				continue;

			만약 (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				만약 (len == s->aux[i].namelen) {
					nmatch = 1;
					break;
				}

				/* ambiguity is ok between aliases. */
				만약 (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		아니면 만약 (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			만약 (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	만약 (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	아니면 만약 (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	반환 *err_code ? 0 : 1;
}


정수     scanopt (scanopt_t *svoid, char **arg, 정수 *optindex)
{
	char   *optname = NULL, *optarg = NULL, *pstart;
	정수     namelen = 0, arglen = 0;
	정수     errcode = 0, has_next;
	const optspec_t *optp;
	struct _scanopt_t *s;
	struct _aux *auxp;
	정수     is_short;
	정수     opt_offset = -1;

	s = (struct _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, NULL);
	SAFE_ASSIGN (optindex, s->index);

	만약 (s->index >= s->argc)
		반환 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	만약 (!pstart)
		반환 0;

	만약 (s->subscript == 0) {

		/* test for exact match of "--" */
		만약 (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			반환 0;
		}

		/* Match an opt. */
		만약 (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			만약 (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				반환 errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		아니면 만약 (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		아니면 {
			/* It's not an option. We're done. */
			반환 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	만약 (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		만약 (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			반환 errcode;
		}

		optarg = pstart + 1;
		만약 (!*optarg) {
			optarg = NULL;
			arglen = 0;
		}
		아니면
			arglen = (정수) strlen (optarg);
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
	만약 (auxp->flags & ARG_NONE) {
		만약 (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			반환 SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		아니면 만약 (!optarg)
			INC_INDEX (s, 1);
		아니면
			s->subscript++;
		반환 optp->r_val;
	}

	/* case: required */
	만약 (auxp->flags & ARG_REQ) {
		만약 (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			반환 SCANOPT_ERR_ARG_NOT_FOUND;
		}

		만약 (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		아니면 {
			SAFE_ASSIGN (arg, (char *) optarg);
			INC_INDEX (s, 1);
		}
		반환 optp->r_val;
	}

	/* case: optional */
	만약 (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		반환 optp->r_val;
	}


	/* Should not reach here. */
	반환 0;
}


정수     scanopt_destroy (scanopt_t *svoid)
{
	struct _scanopt_t *s;

	s = (struct _scanopt_t *) svoid;
	만약 (s != NULL) {
		free(s->aux);
		free(s);
	}
	반환 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
