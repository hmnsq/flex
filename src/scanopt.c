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

#ଅନ୍ତର୍ଭାଵ "flexdef.h"
#ଅନ୍ତର୍ଭାଵ "scanopt.h"


/* Internal structures */

#define ARG_NONE 0x01
#define ARG_REQ  0x02
#define ARG_OPT  0x04
#define IS_LONG  0x08

ସଂରଚନା _aux {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     flags;		/* The above hex flags. */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


ସଂରଚନା _scanopt_t {
	ଅଚଳ optspec_t *options;	/* List of options. */
	ସଂରଚନା _aux *aux;	/* Auxiliary data about options. */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     optc;		/* Number of options. */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     argc;		/* Number of args. */
	ଅକ୍ଷର  **argv;		/* Array of strings. */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     index;		/* Used as: argv[index][subscript]. */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     subscript;
	ଅକ୍ଷର    no_err_ସନ୍ଦେଶ;	/* If true, do not print errors. */
	ଅକ୍ଷର    has_long;
	ଅକ୍ଷର    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *NAME(ସଂରଚନା _scanopt_t *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା PRINTLEN(ସଂରଚନା _scanopt_t *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା RVAL(ସଂରଚନା _scanopt_t *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା FLAGS(ସଂରଚନା _scanopt_t *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *DESC(ସଂରଚନା _scanopt_t *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ସ୍ଥିର ଶୂନ୍ୟ scanopt_err(ସଂରଚନା _scanopt_t *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା matchlongopt(ଅକ୍ଷର *, ଅକ୍ଷର **, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ଅକ୍ଷର **, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *);
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା find_opt(ସଂରଚନା _scanopt_t *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ଅକ୍ଷର *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *opt_offset);

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *NAME (ସଂରଚନା _scanopt_t *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା i)
{
	ଫେରନ୍ତୁ s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା PRINTLEN (ସଂରଚନା _scanopt_t *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା i)
{
	ଫେରନ୍ତୁ s->aux[i].printlen;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା RVAL (ସଂରଚନା _scanopt_t *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା i)
{
	ଫେରନ୍ତୁ s->options[i].r_val;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା FLAGS (ସଂରଚନା _scanopt_t *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା i)
{
	ଫେରନ୍ତୁ s->aux[i].flags;
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *DESC (ସଂରଚନା _scanopt_t *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା i)
{
	ଫେରନ୍ତୁ s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_cols (ଶୂନ୍ୟ);

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_cols (ଶୂନ୍ୟ)
{
	ଅକ୍ଷର   *env;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	ଯଦି (COLS > 0)
		ଫେରନ୍ତୁ COLS;
#endif

	ଯଦି ((env = getenv ("COLUMNS")) != ଖାଲି)
		cols = atoi (env);

	ଫେରନ୍ତୁ cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    କର{                      \
        ଯଦି((ptr)!=ଖାଲି)      \
            *(ptr) = val;    \
    }ଯେତେବେଳେ(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    କର{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }ଯେତେବେଳେ(0)

scanopt_t *scanopt_init (ଅଚଳ optspec_t *options, ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର **argv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     i;
	ସଂରଚନା _scanopt_t *s;
	s = malloc(ଆକାର (ସଂରଚନା _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (ଅକ୍ଷର **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_ସନ୍ଦେଶ = (flags & SCANOPT_NO_ERR_ସନ୍ଦେଶ);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	ଯେତେବେଳେ (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * ଆକାର (ସଂରଚନା _aux));

	ପାଇଁ (i = 0; i < s->optc; i++) {
		ଅଚଳ unsigned ଅକ୍ଷର *p, *pname;
		ଅଚଳ ସଂରଚନା optspec_t *opt;
		ସଂରଚନା _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		ଯଦି (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ଅଚଳ unsigned ଅକ୍ଷର *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		ଅନ୍ୟଥା {
			pname = (ଅଚଳ unsigned ଅକ୍ଷର *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) strlen (opt->opt_fmt);

		aux->namelen = 0;
		ପାଇଁ (p = pname + 1; *p; p++) {
			/* detect required arg */
			ଯଦି (*p == '=' || isspace ((unsigned ଅକ୍ଷର)*p)
			    || !(aux->flags & IS_LONG)) {
				ଯଦି (aux->namelen == 0)
					aux->namelen = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			ଯଦି (*p == '[') {
				ଯଦି (aux->namelen == 0)
					aux->namelen = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				ଭାଙ୍ଗ;
			}
		}
		ଯଦି (aux->namelen == 0)
			aux->namelen = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) (p - pname);
	}
	ଫେରନ୍ତୁ (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
ସଂରଚନା usg_elem {
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     idx;
	ସଂରଚନା usg_elem *next;
	ସଂରଚନା usg_elem *alias;
};
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା usg_elem usg_elem;


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
ପୂର୍ଣ୍ଣସଂଖ୍ୟା     scanopt_usage (scanopt_t *scanner, FILE *fp, ଅଚଳ ଅକ୍ଷର *usage)
{
	ସଂରଚନା _scanopt_t *s;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     i, columns;
	ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା indent = 2;
	usg_elem *byr_val = ଖାଲି;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     store_idx = 0;
	usg_elem *ue;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     opt_col_width = 0, desc_col_width = 0;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     desccol;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     print_run = 0;

	s = (ସଂରଚନା _scanopt_t *) scanner;

	ଯଦି (usage) {
		fprintf (fp, "%s\n", usage);
	}
	ଅନ୍ୟଥା {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * ଆକାର (usg_elem));
	ପାଇଁ (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = ଖାଲି;

		/* insert into list. */
		ଯଦି (!byr_val)
			byr_val = ue;
		ଅନ୍ୟଥା {
			ପୂର୍ଣ୍ଣସଂଖ୍ୟା     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = ଖାଲି;

			ue_curr = &byr_val;
			ଯେତେବେଳେ (*ue_curr) {
				ଯଦି (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					ଭାଙ୍ଗ;
				}
				ଯଦି (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			ଯଦି (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#ଯଦି 0
	ଯଦି (1) {
		printf ("ORIGINAL:\n");
		ପାଇଁ (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		ଯେତେବେଳେ (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			ପାଇଁ (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	ପାଇଁ (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		ପୂର୍ଣ୍ଣସଂଖ୍ୟା     len;

		len = PRINTLEN(s, ue->idx);

		ପାଇଁ (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) strlen(", ");
		}

		ଯଦି (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) strlen (DESC (s, ue->idx));
		ଯଦି (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	ଯଦି (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		ଯଦି (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	ଯେତେବେଳେ (print_run++ < 2) {
		ପାଇଁ (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			ପୂର୍ଣ୍ଣସଂଖ୍ୟା     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			ପାଇଁ (ap = ue->alias; ap; ap = ap->next) {
				ଯଦି (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					ଭାଙ୍ଗ;
				}
			}
			ଯଦି ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				ଜାରି;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) କର{\
                  ଯଦି(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }ଯେତେବେଳେ(0)

			ଯଦି (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			ପାଇଁ (ap = ue->alias; ap; ap = ap->next) {
				ଯଦି (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			ଯଦି (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			ପାଇଁ (ap = ue->alias; ap; ap = ap->next) {
				ଯଦି (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			ଯଦି (1) {
				ଅଚଳ ଅକ୍ଷର *pstart;

				pstart = DESC (s, ue->idx);
				ଯେତେବେଳେ (1) {
					ପୂର୍ଣ୍ଣସଂଖ୍ୟା     n = 0;
					ଅଚଳ ଅକ୍ଷର *lastws = ଖାଲି, *p;

					p = pstart;

					ଯେତେବେଳେ (*p && n < desc_col_width
					       && *p != '\n') {
						ଯଦି (isspace ((unsigned ଅକ୍ଷର)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					ଯଦି (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						ଭାଙ୍ଗ;
					}
					ଅନ୍ୟଥା ଯଦି (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						ଜାରି;
					}
					ଅନ୍ୟଥା {	/* we hit the edge of the screen. wrap at space if possible. */
						ଯଦି (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						ଅନ୍ୟଥା {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						ଜାରି;
					}
				}
			}
		}
	}			/* end while */
	ମୁକ୍ତ (store);
	ଫେରନ୍ତୁ 0;
}
#endif /* no scanopt_usage */


ସ୍ଥିର ଶୂନ୍ୟ scanopt_err(ସଂରଚନା _scanopt_t *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_short, ପୂର୍ଣ୍ଣସଂଖ୍ୟା err)
{
	ଅଚଳ ଅକ୍ଷର *optname = "";
	ଅକ୍ଷର    optchar[2];

	ଯଦି (!s->no_err_ସନ୍ଦେଶ) {

		ଯଦି (s->index > 0 && s->index < s->argc) {
			ଯଦି (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			ଅନ୍ୟଥା {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		ବାଛ (err) {
		ସ୍ଥିତି SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			ଭାଙ୍ଗ;
		ସ୍ଥିତି SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			ଭାଙ୍ଗ;
		ସ୍ଥିତି SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			ଭାଙ୍ଗ;
		ସ୍ଥିତି SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			ଭାଙ୍ଗ;
		ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			ଭାଙ୍ଗ;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା matchlongopt (ଅକ୍ଷର *str, ଅକ୍ଷର **optname, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *optlen, ଅକ୍ଷର **arg, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *arglen)
{
	ଅକ୍ଷର   *p;

	*optname = *arg = ଖାଲି;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	ଯଦି (p[0] != '-' || p[1] != '-' || !p[2])
		ଫେରନ୍ତୁ 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	ଯେତେବେଳେ (*p && *p != '=')
		++p;

	*optlen = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) (p - *optname);

	ଯଦି (!*p)
		/* an option with no '=...' part. */
		ଫେରନ୍ତୁ 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	ଯେତେବେଳେ (*p)
		++p;
	*arglen = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) (p - *arg);

	ଫେରନ୍ତୁ 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା find_opt (ସଂରଚନା _scanopt_t *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା lookup_long, ଅକ୍ଷର *optstart, ପୂର୍ଣ୍ଣସଂଖ୍ୟା
	len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *err_code, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *opt_offset)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	ଯଦି (!optstart)
		ଫେରନ୍ତୁ 0;

	ପାଇଁ (i = 0; i < s->optc; i++) {
		ଅଚଳ ଅକ୍ଷର   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		ଯଦି (lookup_long && (s->aux[i].flags & IS_LONG)) {
			ଯଦି (len > s->aux[i].namelen)
				ଜାରି;

			ଯଦି (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				ଯଦି (len == s->aux[i].namelen) {
					nmatch = 1;
					ଭାଙ୍ଗ;
				}

				/* ambiguity is ok between aliases. */
				ଯଦି (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		ଅନ୍ୟଥା ଯଦି (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			ଯଦି (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	ଯଦି (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	ଅନ୍ୟଥା ଯଦି (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	ଫେରନ୍ତୁ *err_code ? 0 : 1;
}


ପୂର୍ଣ୍ଣସଂଖ୍ୟା     scanopt (scanopt_t *svoid, ଅକ୍ଷର **arg, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *optindex)
{
	ଅକ୍ଷର   *optname = ଖାଲି, *optarg = ଖାଲି, *pstart;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     namelen = 0, arglen = 0;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     errcode = 0, has_next;
	ଅଚଳ optspec_t *optp;
	ସଂରଚନା _scanopt_t *s;
	ସଂରଚନା _aux *auxp;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     is_short;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     opt_offset = -1;

	s = (ସଂରଚନା _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, ଖାଲି);
	SAFE_ASSIGN (optindex, s->index);

	ଯଦି (s->index >= s->argc)
		ଫେରନ୍ତୁ 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	ଯଦି (!pstart)
		ଫେରନ୍ତୁ 0;

	ଯଦି (s->subscript == 0) {

		/* test for exact match of "--" */
		ଯଦି (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			ଫେରନ୍ତୁ 0;
		}

		/* Match an opt. */
		ଯଦି (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			ଯଦି (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				ଫେରନ୍ତୁ errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		ଅନ୍ୟଥା ଯଦି (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		ଅନ୍ୟଥା {
			/* It's not an option. We're done. */
			ଫେରନ୍ତୁ 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	ଯଦି (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		ଯଦି (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			ଫେରନ୍ତୁ errcode;
		}

		optarg = pstart + 1;
		ଯଦି (!*optarg) {
			optarg = ଖାଲି;
			arglen = 0;
		}
		ଅନ୍ୟଥା
			arglen = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) strlen (optarg);
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
	ଯଦି (auxp->flags & ARG_NONE) {
		ଯଦି (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			ଫେରନ୍ତୁ SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		ଅନ୍ୟଥା ଯଦି (!optarg)
			INC_INDEX (s, 1);
		ଅନ୍ୟଥା
			s->subscript++;
		ଫେରନ୍ତୁ optp->r_val;
	}

	/* case: required */
	ଯଦି (auxp->flags & ARG_REQ) {
		ଯଦି (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			ଫେରନ୍ତୁ SCANOPT_ERR_ARG_NOT_FOUND;
		}

		ଯଦି (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		ଅନ୍ୟଥା {
			SAFE_ASSIGN (arg, (ଅକ୍ଷର *) optarg);
			INC_INDEX (s, 1);
		}
		ଫେରନ୍ତୁ optp->r_val;
	}

	/* case: optional */
	ଯଦି (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		ଫେରନ୍ତୁ optp->r_val;
	}


	/* Should not reach here. */
	ଫେରନ୍ତୁ 0;
}


ପୂର୍ଣ୍ଣସଂଖ୍ୟା     scanopt_destroy (scanopt_t *svoid)
{
	ସଂରଚନା _scanopt_t *s;

	s = (ସଂରଚନା _scanopt_t *) svoid;
	ଯଦି (s != ଖାଲି) {
		ମୁକ୍ତ(s->aux);
		ମୁକ୍ତ(s);
	}
	ଫେରନ୍ତୁ 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
