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

#ಅನ್ತರ್ಭಾವ "flexdef.h"
#ಅನ್ತರ್ಭಾವ "scanopt.h"


/* Internal structures */

#define ARG_NONE 0x01
#define ARG_REQ  0x02
#define ARG_OPT  0x04
#define IS_LONG  0x08

ಸಂರಚನಾ _aux {
	ಪೂರ್ಣಾಙ್ಕ     flags;		/* The above hex flags. */
	ಪೂರ್ಣಾಙ್ಕ     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	ಪೂರ್ಣಾಙ್ಕ     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


ಸಂರಚನಾ _scanopt_t {
	ಧ್ರುವ optspec_t *options;	/* List of options. */
	ಸಂರಚನಾ _aux *aux;	/* Auxiliary data about options. */
	ಪೂರ್ಣಾಙ್ಕ     optc;		/* Number of options. */
	ಪೂರ್ಣಾಙ್ಕ     argc;		/* Number of args. */
	ವರ್ಣ  **argv;		/* Array of strings. */
	ಪೂರ್ಣಾಙ್ಕ     index;		/* Used as: argv[index][subscript]. */
	ಪೂರ್ಣಾಙ್ಕ     subscript;
	ವರ್ಣ    no_err_ಸಂದೇಶ;	/* If true, do not print errors. */
	ವರ್ಣ    has_long;
	ವರ್ಣ    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *NAME(ಸಂರಚನಾ _scanopt_t *, ಪೂರ್ಣಾಙ್ಕ);
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ PRINTLEN(ಸಂರಚನಾ _scanopt_t *, ಪೂರ್ಣಾಙ್ಕ);
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ RVAL(ಸಂರಚನಾ _scanopt_t *, ಪೂರ್ಣಾಙ್ಕ);
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ FLAGS(ಸಂರಚನಾ _scanopt_t *, ಪೂರ್ಣಾಙ್ಕ);
ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *DESC(ಸಂರಚನಾ _scanopt_t *, ಪೂರ್ಣಾಙ್ಕ);
ಸ್ಥಿರ ಶೂನ್ಯ scanopt_err(ಸಂರಚನಾ _scanopt_t *, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ);
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ matchlongopt(ವರ್ಣ *, ವರ್ಣ **, ಪೂರ್ಣಾಙ್ಕ *, ವರ್ಣ **, ಪೂರ್ಣಾಙ್ಕ *);
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ find_opt(ಸಂರಚನಾ _scanopt_t *, ಪೂರ್ಣಾಙ್ಕ, ವರ್ಣ *, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ *, ಪೂರ್ಣಾಙ್ಕ *opt_offset);

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *NAME (ಸಂರಚನಾ _scanopt_t *s, ಪೂರ್ಣಾಙ್ಕ i)
{
	ಪ್ರತ್ಯಾಗಮ s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ PRINTLEN (ಸಂರಚನಾ _scanopt_t *s, ಪೂರ್ಣಾಙ್ಕ i)
{
	ಪ್ರತ್ಯಾಗಮ s->aux[i].printlen;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ RVAL (ಸಂರಚನಾ _scanopt_t *s, ಪೂರ್ಣಾಙ್ಕ i)
{
	ಪ್ರತ್ಯಾಗಮ s->options[i].r_val;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ FLAGS (ಸಂರಚನಾ _scanopt_t *s, ಪೂರ್ಣಾಙ್ಕ i)
{
	ಪ್ರತ್ಯಾಗಮ s->aux[i].flags;
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *DESC (ಸಂರಚನಾ _scanopt_t *s, ಪೂರ್ಣಾಙ್ಕ i)
{
	ಪ್ರತ್ಯಾಗಮ s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_cols (ಶೂನ್ಯ);

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_cols (ಶೂನ್ಯ)
{
	ವರ್ಣ   *env;
	ಪೂರ್ಣಾಙ್ಕ     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	ಯದಿ (COLS > 0)
		ಪ್ರತ್ಯಾಗಮ COLS;
#endif

	ಯದಿ ((env = getenv ("COLUMNS")) != ರಿಕ್ತ)
		cols = atoi (env);

	ಪ್ರತ್ಯಾಗಮ cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    ಕುರು{                      \
        ಯದಿ((ptr)!=ರಿಕ್ತ)      \
            *(ptr) = val;    \
    }ಯಾವತ್(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    ಕುರು{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }ಯಾವತ್(0)

scanopt_t *scanopt_init (ಧ್ರುವ optspec_t *options, ಪೂರ್ಣಾಙ್ಕ argc, ವರ್ಣ **argv, ಪೂರ್ಣಾಙ್ಕ flags)
{
	ಪೂರ್ಣಾಙ್ಕ     i;
	ಸಂರಚನಾ _scanopt_t *s;
	s = malloc(ಪರಿಮಾಣ (ಸಂರಚನಾ _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (ವರ್ಣ **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_ಸಂದೇಶ = (flags & SCANOPT_NO_ERR_ಸಂದೇಶ);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	ಯಾವತ್ (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * ಪರಿಮಾಣ (ಸಂರಚನಾ _aux));

	ಪ್ರತಿ (i = 0; i < s->optc; i++) {
		ಧ್ರುವ unsigned ವರ್ಣ *p, *pname;
		ಧ್ರುವ ಸಂರಚನಾ optspec_t *opt;
		ಸಂರಚನಾ _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		ಯದಿ (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ಧ್ರುವ unsigned ವರ್ಣ *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		ಅನ್ಯಥಾ {
			pname = (ಧ್ರುವ unsigned ವರ್ಣ *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (ಪೂರ್ಣಾಙ್ಕ) strlen (opt->opt_fmt);

		aux->namelen = 0;
		ಪ್ರತಿ (p = pname + 1; *p; p++) {
			/* detect required arg */
			ಯದಿ (*p == '=' || isspace ((unsigned ವರ್ಣ)*p)
			    || !(aux->flags & IS_LONG)) {
				ಯದಿ (aux->namelen == 0)
					aux->namelen = (ಪೂರ್ಣಾಙ್ಕ) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			ಯದಿ (*p == '[') {
				ಯದಿ (aux->namelen == 0)
					aux->namelen = (ಪೂರ್ಣಾಙ್ಕ) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				ಭಙ್ಗ;
			}
		}
		ಯದಿ (aux->namelen == 0)
			aux->namelen = (ಪೂರ್ಣಾಙ್ಕ) (p - pname);
	}
	ಪ್ರತ್ಯಾಗಮ (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
ಸಂರಚನಾ usg_elem {
	ಪೂರ್ಣಾಙ್ಕ     idx;
	ಸಂರಚನಾ usg_elem *next;
	ಸಂರಚನಾ usg_elem *alias;
};
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ usg_elem usg_elem;


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
ಪೂರ್ಣಾಙ್ಕ     scanopt_usage (scanopt_t *scanner, FILE *fp, ಧ್ರುವ ವರ್ಣ *usage)
{
	ಸಂರಚನಾ _scanopt_t *s;
	ಪೂರ್ಣಾಙ್ಕ     i, columns;
	ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ indent = 2;
	usg_elem *byr_val = ರಿಕ್ತ;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	ಪೂರ್ಣಾಙ್ಕ     store_idx = 0;
	usg_elem *ue;
	ಪೂರ್ಣಾಙ್ಕ     opt_col_width = 0, desc_col_width = 0;
	ಪೂರ್ಣಾಙ್ಕ     desccol;
	ಪೂರ್ಣಾಙ್ಕ     print_run = 0;

	s = (ಸಂರಚನಾ _scanopt_t *) scanner;

	ಯದಿ (usage) {
		fprintf (fp, "%s\n", usage);
	}
	ಅನ್ಯಥಾ {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * ಪರಿಮಾಣ (usg_elem));
	ಪ್ರತಿ (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = ರಿಕ್ತ;

		/* insert into list. */
		ಯದಿ (!byr_val)
			byr_val = ue;
		ಅನ್ಯಥಾ {
			ಪೂರ್ಣಾಙ್ಕ     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = ರಿಕ್ತ;

			ue_curr = &byr_val;
			ಯಾವತ್ (*ue_curr) {
				ಯದಿ (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					ಭಙ್ಗ;
				}
				ಯದಿ (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			ಯದಿ (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#ಯದಿ 0
	ಯದಿ (1) {
		printf ("ORIGINAL:\n");
		ಪ್ರತಿ (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		ಯಾವತ್ (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			ಪ್ರತಿ (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	ಪ್ರತಿ (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		ಪೂರ್ಣಾಙ್ಕ     len;

		len = PRINTLEN(s, ue->idx);

		ಪ್ರತಿ (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (ಪೂರ್ಣಾಙ್ಕ) strlen(", ");
		}

		ಯದಿ (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (ಪೂರ್ಣಾಙ್ಕ) strlen (DESC (s, ue->idx));
		ಯದಿ (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	ಯದಿ (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		ಯದಿ (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	ಯಾವತ್ (print_run++ < 2) {
		ಪ್ರತಿ (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			ಪೂರ್ಣಾಙ್ಕ     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			ಪ್ರತಿ (ap = ue->alias; ap; ap = ap->next) {
				ಯದಿ (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					ಭಙ್ಗ;
				}
			}
			ಯದಿ ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				ಅನುವರ್ತ;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) ಕುರು{\
                  ಯದಿ(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }ಯಾವತ್(0)

			ಯದಿ (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			ಪ್ರತಿ (ap = ue->alias; ap; ap = ap->next) {
				ಯದಿ (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			ಯದಿ (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			ಪ್ರತಿ (ap = ue->alias; ap; ap = ap->next) {
				ಯದಿ (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			ಯದಿ (1) {
				ಧ್ರುವ ವರ್ಣ *pstart;

				pstart = DESC (s, ue->idx);
				ಯಾವತ್ (1) {
					ಪೂರ್ಣಾಙ್ಕ     n = 0;
					ಧ್ರುವ ವರ್ಣ *lastws = ರಿಕ್ತ, *p;

					p = pstart;

					ಯಾವತ್ (*p && n < desc_col_width
					       && *p != '\n') {
						ಯದಿ (isspace ((unsigned ವರ್ಣ)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					ಯದಿ (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						ಭಙ್ಗ;
					}
					ಅನ್ಯಥಾ ಯದಿ (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						ಅನುವರ್ತ;
					}
					ಅನ್ಯಥಾ {	/* we hit the edge of the screen. wrap at space if possible. */
						ಯದಿ (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (ಪೂರ್ಣಾಙ್ಕ)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						ಅನ್ಯಥಾ {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						ಅನುವರ್ತ;
					}
				}
			}
		}
	}			/* end while */
	ಮುಕ್ತ (store);
	ಪ್ರತ್ಯಾಗಮ 0;
}
#endif /* no scanopt_usage */


ಸ್ಥಿರ ಶೂನ್ಯ scanopt_err(ಸಂರಚನಾ _scanopt_t *s, ಪೂರ್ಣಾಙ್ಕ is_short, ಪೂರ್ಣಾಙ್ಕ err)
{
	ಧ್ರುವ ವರ್ಣ *optname = "";
	ವರ್ಣ    optchar[2];

	ಯದಿ (!s->no_err_ಸಂದೇಶ) {

		ಯದಿ (s->index > 0 && s->index < s->argc) {
			ಯದಿ (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			ಅನ್ಯಥಾ {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		ವಿಕಲ್ಪ (err) {
		ಪಕ್ಷ SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			ಭಙ್ಗ;
		ಪಕ್ಷ SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			ಭಙ್ಗ;
		ಪಕ್ಷ SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			ಭಙ್ಗ;
		ಪಕ್ಷ SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			ಭಙ್ಗ;
		ಸ್ವಭಾವ:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			ಭಙ್ಗ;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ matchlongopt (ವರ್ಣ *str, ವರ್ಣ **optname, ಪೂರ್ಣಾಙ್ಕ *optlen, ವರ್ಣ **arg, ಪೂರ್ಣಾಙ್ಕ *arglen)
{
	ವರ್ಣ   *p;

	*optname = *arg = ರಿಕ್ತ;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	ಯದಿ (p[0] != '-' || p[1] != '-' || !p[2])
		ಪ್ರತ್ಯಾಗಮ 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	ಯಾವತ್ (*p && *p != '=')
		++p;

	*optlen = (ಪೂರ್ಣಾಙ್ಕ) (p - *optname);

	ಯದಿ (!*p)
		/* an option with no '=...' part. */
		ಪ್ರತ್ಯಾಗಮ 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	ಯಾವತ್ (*p)
		++p;
	*arglen = (ಪೂರ್ಣಾಙ್ಕ) (p - *arg);

	ಪ್ರತ್ಯಾಗಮ 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ find_opt (ಸಂರಚನಾ _scanopt_t *s, ಪೂರ್ಣಾಙ್ಕ lookup_long, ವರ್ಣ *optstart, ಪೂರ್ಣಾಙ್ಕ
	len, ಪೂರ್ಣಾಙ್ಕ *err_code, ಪೂರ್ಣಾಙ್ಕ *opt_offset)
{
	ಪೂರ್ಣಾಙ್ಕ     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	ಯದಿ (!optstart)
		ಪ್ರತ್ಯಾಗಮ 0;

	ಪ್ರತಿ (i = 0; i < s->optc; i++) {
		ಧ್ರುವ ವರ್ಣ   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		ಯದಿ (lookup_long && (s->aux[i].flags & IS_LONG)) {
			ಯದಿ (len > s->aux[i].namelen)
				ಅನುವರ್ತ;

			ಯದಿ (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				ಯದಿ (len == s->aux[i].namelen) {
					nmatch = 1;
					ಭಙ್ಗ;
				}

				/* ambiguity is ok between aliases. */
				ಯದಿ (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		ಅನ್ಯಥಾ ಯದಿ (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			ಯದಿ (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	ಯದಿ (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	ಅನ್ಯಥಾ ಯದಿ (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	ಪ್ರತ್ಯಾಗಮ *err_code ? 0 : 1;
}


ಪೂರ್ಣಾಙ್ಕ     scanopt (scanopt_t *svoid, ವರ್ಣ **arg, ಪೂರ್ಣಾಙ್ಕ *optindex)
{
	ವರ್ಣ   *optname = ರಿಕ್ತ, *optarg = ರಿಕ್ತ, *pstart;
	ಪೂರ್ಣಾಙ್ಕ     namelen = 0, arglen = 0;
	ಪೂರ್ಣಾಙ್ಕ     errcode = 0, has_next;
	ಧ್ರುವ optspec_t *optp;
	ಸಂರಚನಾ _scanopt_t *s;
	ಸಂರಚನಾ _aux *auxp;
	ಪೂರ್ಣಾಙ್ಕ     is_short;
	ಪೂರ್ಣಾಙ್ಕ     opt_offset = -1;

	s = (ಸಂರಚನಾ _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, ರಿಕ್ತ);
	SAFE_ASSIGN (optindex, s->index);

	ಯದಿ (s->index >= s->argc)
		ಪ್ರತ್ಯಾಗಮ 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	ಯದಿ (!pstart)
		ಪ್ರತ್ಯಾಗಮ 0;

	ಯದಿ (s->subscript == 0) {

		/* test for exact match of "--" */
		ಯದಿ (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			ಪ್ರತ್ಯಾಗಮ 0;
		}

		/* Match an opt. */
		ಯದಿ (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			ಯದಿ (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				ಪ್ರತ್ಯಾಗಮ errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		ಅನ್ಯಥಾ ಯದಿ (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		ಅನ್ಯಥಾ {
			/* It's not an option. We're done. */
			ಪ್ರತ್ಯಾಗಮ 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	ಯದಿ (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		ಯದಿ (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			ಪ್ರತ್ಯಾಗಮ errcode;
		}

		optarg = pstart + 1;
		ಯದಿ (!*optarg) {
			optarg = ರಿಕ್ತ;
			arglen = 0;
		}
		ಅನ್ಯಥಾ
			arglen = (ಪೂರ್ಣಾಙ್ಕ) strlen (optarg);
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
	ಯದಿ (auxp->flags & ARG_NONE) {
		ಯದಿ (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			ಪ್ರತ್ಯಾಗಮ SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		ಅನ್ಯಥಾ ಯದಿ (!optarg)
			INC_INDEX (s, 1);
		ಅನ್ಯಥಾ
			s->subscript++;
		ಪ್ರತ್ಯಾಗಮ optp->r_val;
	}

	/* case: required */
	ಯದಿ (auxp->flags & ARG_REQ) {
		ಯದಿ (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			ಪ್ರತ್ಯಾಗಮ SCANOPT_ERR_ARG_NOT_FOUND;
		}

		ಯದಿ (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		ಅನ್ಯಥಾ {
			SAFE_ASSIGN (arg, (ವರ್ಣ *) optarg);
			INC_INDEX (s, 1);
		}
		ಪ್ರತ್ಯಾಗಮ optp->r_val;
	}

	/* case: optional */
	ಯದಿ (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		ಪ್ರತ್ಯಾಗಮ optp->r_val;
	}


	/* Should not reach here. */
	ಪ್ರತ್ಯಾಗಮ 0;
}


ಪೂರ್ಣಾಙ್ಕ     scanopt_destroy (scanopt_t *svoid)
{
	ಸಂರಚನಾ _scanopt_t *s;

	s = (ಸಂರಚನಾ _scanopt_t *) svoid;
	ಯದಿ (s != ರಿಕ್ತ) {
		ಮುಕ್ತ(s->aux);
		ಮುಕ್ತ(s);
	}
	ಪ್ರತ್ಯಾಗಮ 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
