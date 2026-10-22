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

#ವ್ಯಾಖ್ಯಾನಿಸು ARG_NONE 0x01
#ವ್ಯಾಖ್ಯಾನಿಸು ARG_REQ  0x02
#ವ್ಯಾಖ್ಯಾನಿಸು ARG_OPT  0x04
#ವ್ಯಾಖ್ಯಾನಿಸು IS_LONG  0x08

ರಚನೆ _aux {
	ಪೂರ್ಣಾಂಕ     flags;		/* The above hex flags. */
	ಪೂರ್ಣಾಂಕ     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	ಪೂರ್ಣಾಂಕ     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


ರಚನೆ _scanopt_t {
	ಸ್ಥಿರಾಂಕ optspec_t *options;	/* List of options. */
	ರಚನೆ _aux *aux;	/* Auxiliary data about options. */
	ಪೂರ್ಣಾಂಕ     optc;		/* Number of options. */
	ಪೂರ್ಣಾಂಕ     argc;		/* Number of args. */
	ಅಕ್ಷರ  **argv;		/* Array of strings. */
	ಪೂರ್ಣಾಂಕ     ಸೂಚ್ಯಂಕ;		/* Used as: argv[index][subscript]. */
	ಪೂರ್ಣಾಂಕ     subscript;
	ಅಕ್ಷರ    no_err_ಸಂದೇಶ;	/* If true, do not print errors. */
	ಅಕ್ಷರ    has_long;
	ಅಕ್ಷರ    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *NAME(ರಚನೆ _scanopt_t *, ಪೂರ್ಣಾಂಕ);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ PRINTLEN(ರಚನೆ _scanopt_t *, ಪೂರ್ಣಾಂಕ);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ RVAL(ರಚನೆ _scanopt_t *, ಪೂರ್ಣಾಂಕ);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ FLAGS(ರಚನೆ _scanopt_t *, ಪೂರ್ಣಾಂಕ);
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *DESC(ರಚನೆ _scanopt_t *, ಪೂರ್ಣಾಂಕ);
ಸ್ಥಿರ ಶೂನ್ಯ scanopt_err(ರಚನೆ _scanopt_t *, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ matchlongopt(ಅಕ್ಷರ *, ಅಕ್ಷರ **, ಪೂರ್ಣಾಂಕ *, ಅಕ್ಷರ **, ಪೂರ್ಣಾಂಕ *);
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಕಂಡುಹಿಡಿ_opt(ರಚನೆ _scanopt_t *, ಪೂರ್ಣಾಂಕ, ಅಕ್ಷರ *, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ *, ಪೂರ್ಣಾಂಕ *opt_ಸ್ಥಾನಾಂತರ);

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *NAME (ರಚನೆ _scanopt_t *s, ಪೂರ್ಣಾಂಕ i)
{
	ಹಿಂತಿರುಗಿ s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ PRINTLEN (ರಚನೆ _scanopt_t *s, ಪೂರ್ಣಾಂಕ i)
{
	ಹಿಂತಿರುಗಿ s->aux[i].printlen;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ RVAL (ರಚನೆ _scanopt_t *s, ಪೂರ್ಣಾಂಕ i)
{
	ಹಿಂತಿರುಗಿ s->options[i].r_val;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ FLAGS (ರಚನೆ _scanopt_t *s, ಪೂರ್ಣಾಂಕ i)
{
	ಹಿಂತಿರುಗಿ s->aux[i].flags;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *DESC (ರಚನೆ _scanopt_t *s, ಪೂರ್ಣಾಂಕ i)
{
	ಹಿಂತಿರುಗಿ s->options[i].desc ? s->options[i].desc : "";
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SCANOPT_USAGE
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ (ಶೂನ್ಯ);

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ (ಶೂನ್ಯ)
{
	ಅಕ್ಷರ   *env;
	ಪೂರ್ಣಾಂಕ     ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ = 80;	/* default */

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_NCURSES_H
	initscr ();
	endwin ();
	ಆದರೆ (ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_2 > 0)
		ಹಿಂತಿರುಗಿ ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_2;
#ಆದರೆ_ಅಂತ್ಯ

	ಆದರೆ ((env = getenv ("COLUMNS")) != ಖಾಲಿ)
		ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ = atoi (env);

	ಹಿಂತಿರುಗಿ ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ;
}
#ಆದರೆ_ಅಂತ್ಯ

/* Macro to check for NULL before assigning a value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಸುರಕ್ಷಿತ_ನಿಯೋಜಿಸು(ptr,val) \
    ಮಾಡು{                      \
        ಆದರೆ((ptr)!=ಖಾಲಿ)      \
            *(ptr) = val;    \
    }ಆಗ(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#ವ್ಯಾಖ್ಯಾನಿಸು INC_ಸೂಚ್ಯಂಕ(s,n)     \
    ಮಾಡು{                    \
       (s)->ಸೂಚ್ಯಂಕ += (n);  \
       (s)->subscript= 0;  \
    }ಆಗ(0)

scanopt_t *scanopt_init (ಸ್ಥಿರಾಂಕ optspec_t *options, ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ **argv, ಪೂರ್ಣಾಂಕ flags)
{
	ಪೂರ್ಣಾಂಕ     i;
	ರಚನೆ _scanopt_t *s;
	s = ಸ್ಮರಣೆ_ಕೊಡು(ಗಾತ್ರ (ರಚನೆ _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (ಅಕ್ಷರ **) argv;
	s->ಸೂಚ್ಯಂಕ = 1;
	s->subscript = 0;
	s->no_err_ಸಂದೇಶ = (flags & SCANOPT_NO_ERR_ಸಂದೇಶ);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	ಆಗ (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = ಸ್ಮರಣೆ_ಕೊಡು((size_t) s->optc * ಗಾತ್ರ (ರಚನೆ _aux));

	ಗಾಗಿ (i = 0; i < s->optc; i++) {
		ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p, *pname;
		ಸ್ಥಿರಾಂಕ ರಚನೆ optspec_t *opt;
		ರಚನೆ _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		ಆದರೆ (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		ಇಲ್ಲದಿದ್ದರೆ {
			pname = (ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (ಪೂರ್ಣಾಂಕ) ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (opt->opt_fmt);

		aux->namelen = 0;
		ಗಾಗಿ (p = pname + 1; *p; p++) {
			/* detect required arg */
			ಆದರೆ (*p == '=' || ಖಾಲಿಯೇ ((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ)*p)
			    || !(aux->flags & IS_LONG)) {
				ಆದರೆ (aux->namelen == 0)
					aux->namelen = (ಪೂರ್ಣಾಂಕ) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			ಆದರೆ (*p == '[') {
				ಆದರೆ (aux->namelen == 0)
					aux->namelen = (ಪೂರ್ಣಾಂಕ) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				ನಿಲ್ಲಿಸು;
			}
		}
		ಆದರೆ (aux->namelen == 0)
			aux->namelen = (ಪೂರ್ಣಾಂಕ) (p - pname);
	}
	ಹಿಂತಿರುಗಿ (scanopt_t *) s;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
ರಚನೆ usg_elem {
	ಪೂರ್ಣಾಂಕ     idx;
	ರಚನೆ usg_elem *ಮುಂದಿನ;
	ರಚನೆ usg_elem *alias;
};
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ usg_elem usg_elem;


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
ಪೂರ್ಣಾಂಕ     scanopt_usage (scanopt_t *scanner, FILE *fp, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *usage)
{
	ರಚನೆ _scanopt_t *s;
	ಪೂರ್ಣಾಂಕ     i, columns;
	ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ indent = 2;
	usg_elem *byr_val = ಖಾಲಿ;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	ಪೂರ್ಣಾಂಕ     store_idx = 0;
	usg_elem *ue;
	ಪೂರ್ಣಾಂಕ     opt_ಲಂಬಸಾಲು_ಅಗಲ = 0, desc_ಲಂಬಸಾಲು_ಅಗಲ = 0;
	ಪೂರ್ಣಾಂಕ     desccol;
	ಪೂರ್ಣಾಂಕ     print_ಸತತ = 0;

	s = (ರಚನೆ _scanopt_t *) scanner;

	ಆದರೆ (usage) {
		fprintf (fp, "%s\n", usage);
	}
	ಇಲ್ಲದಿದ್ದರೆ {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = ಸ್ಮರಣೆ_ಕೊಡು((size_t) s->optc * ಗಾತ್ರ (usg_elem));
	ಗಾಗಿ (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->ಮುಂದಿನ = ue->alias = ಖಾಲಿ;

		/* insert into list. */
		ಆದರೆ (!byr_val)
			byr_val = ue;
		ಇಲ್ಲದಿದ್ದರೆ {
			ಪೂರ್ಣಾಂಕ     ಸಿಕ್ಕಿತು_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = ಖಾಲಿ;

			ue_curr = &byr_val;
			ಆಗ (*ue_curr) {
				ಆದರೆ (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					ಸಿಕ್ಕಿತು_alias = 1;
					ನಿಲ್ಲಿಸು;
				}
				ಆದರೆ (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->ಮುಂದಿನ);
			}
			ಆದರೆ (!ಸಿಕ್ಕಿತು_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->ಮುಂದಿನ = *ue_curr;
			*ue_curr = ue;
		}
	}

#ಆದರೆ 0
	ಆದರೆ (1) {
		ಬರೆ ("ORIGINAL:\n");
		ಗಾಗಿ (i = 0; i < s->optc; i++)
			ಬರೆ ("%2d: %s\n", i, NAME (s, i));
		ಬರೆ ("SORTED:\n");
		ue = byr_val;
		ಆಗ (ue) {
			usg_elem *ue2;

			ಬರೆ ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			ಗಾಗಿ (ue2 = ue->alias; ue2; ue2 = ue2->ಮುಂದಿನ)
				ಬರೆ ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->ಮುಂದಿನ;
		}
	}
#ಆದರೆ_ಅಂತ್ಯ

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	ಗಾಗಿ (ue = byr_val; ue; ue = ue->ಮುಂದಿನ) {
		usg_elem *ap;
		ಪೂರ್ಣಾಂಕ     len;

		len = PRINTLEN(s, ue->idx);

		ಗಾಗಿ (ap = ue->alias; ap; ap = ap->ಮುಂದಿನ) {
			len += PRINTLEN(s, ap->idx) + (ಪೂರ್ಣಾಂಕ) ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(", ");
		}

		ಆದರೆ (len > opt_ಲಂಬಸಾಲು_ಅಗಲ)
			opt_ಲಂಬಸಾಲು_ಅಗಲ = len;

		/* It's much easier to calculate length for description column! */
		len = (ಪೂರ್ಣಾಂಕ) ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (DESC (s, ue->idx));
		ಆದರೆ (len > desc_ಲಂಬಸಾಲು_ಅಗಲ)
			desc_ಲಂಬಸಾಲು_ಅಗಲ = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ () - 1;
	ಆದರೆ (opt_ಲಂಬಸಾಲು_ಅಗಲ + desc_ಲಂಬಸಾಲು_ಅಗಲ + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_ಲಂಬಸಾಲು_ಅಗಲ = columns - (opt_ಲಂಬಸಾಲು_ಅಗಲ + indent * 2);
		ಆದರೆ (desc_ಲಂಬಸಾಲು_ಅಗಲ < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_ಲಂಬಸಾಲು_ಅಗಲ = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
	}
	desccol = opt_ಲಂಬಸಾಲು_ಅಗಲ + indent * 2;

#ವ್ಯಾಖ್ಯಾನಿಸು PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	ಆಗ (print_ಸತತ++ < 2) {
		ಗಾಗಿ (ue = byr_val; ue; ue = ue->ಮುಂದಿನ) {
			usg_elem *ap;
			ಪೂರ್ಣಾಂಕ     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			ಗಾಗಿ (ap = ue->alias; ap; ap = ap->ಮುಂದಿನ) {
				ಆದರೆ (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					ನಿಲ್ಲಿಸು;
				}
			}
			ಆದರೆ ((print_ಸತತ == 1 && !has_short) ||
			    (print_ಸತತ == 2 && has_short))
				ಮುಂದುವರಿ;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#ವ್ಯಾಖ್ಯಾನಿಸು PRINT_IT(i) ಮಾಡು{\
                  ಆದರೆ(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }ಆಗ(0)

			ಆದರೆ (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			ಗಾಗಿ (ap = ue->alias; ap; ap = ap->ಮುಂದಿನ) {
				ಆದರೆ (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			ಆದರೆ (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			ಗಾಗಿ (ap = ue->alias; ap; ap = ap->ಮುಂದಿನ) {
				ಆದರೆ (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			ಆದರೆ (1) {
				ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pstart;

				pstart = DESC (s, ue->idx);
				ಆಗ (1) {
					ಪೂರ್ಣಾಂಕ     n = 0;
					ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *lastws = ಖಾಲಿ, *p;

					p = pstart;

					ಆಗ (*p && n < desc_ಲಂಬಸಾಲು_ಅಗಲ
					       && *p != '\n') {
						ಆದರೆ (ಖಾಲಿಯೇ ((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					ಆದರೆ (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						ನಿಲ್ಲಿಸು;
					}
					ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						ಮುಂದುವರಿ;
					}
					ಇಲ್ಲದಿದ್ದರೆ {	/* we hit the edge of the screen. wrap at space if possible. */
						ಆದರೆ (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (ಪೂರ್ಣಾಂಕ)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						ಇಲ್ಲದಿದ್ದರೆ {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						ಮುಂದುವರಿ;
					}
				}
			}
		}
	}			/* end while */
	ಬಿಡುಗಡೆ (store);
	ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ /* no scanopt_usage */


ಸ್ಥಿರ ಶೂನ್ಯ scanopt_err(ರಚನೆ _scanopt_t *s, ಪೂರ್ಣಾಂಕ is_short, ಪೂರ್ಣಾಂಕ err)
{
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *optname = "";
	ಅಕ್ಷರ    optchar[2];

	ಆದರೆ (!s->no_err_ಸಂದೇಶ) {

		ಆದರೆ (s->ಸೂಚ್ಯಂಕ > 0 && s->ಸೂಚ್ಯಂಕ < s->argc) {
			ಆದರೆ (is_short) {
				optchar[0] =
					s->argv[s->ಸೂಚ್ಯಂಕ][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			ಇಲ್ಲದಿದ್ದರೆ {
				optname = s->argv[s->ಸೂಚ್ಯಂಕ];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		ಆಯ್ಕೆ (err) {
		ಸ್ಥಿತಿ SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ SCANOPT_ERR_ARG_NOT_ಸಿಕ್ಕಿತು:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			ನಿಲ್ಲಿಸು;
		ಸ್ಥಿತಿ SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			ನಿಲ್ಲಿಸು;
		ಪೂರ್ವನಿಯೋಜಿತ:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			ನಿಲ್ಲಿಸು;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ matchlongopt (ಅಕ್ಷರ *str, ಅಕ್ಷರ **optname, ಪೂರ್ಣಾಂಕ *optlen, ಅಕ್ಷರ **arg, ಪೂರ್ಣಾಂಕ *arglen)
{
	ಅಕ್ಷರ   *p;

	*optname = *arg = ಖಾಲಿ;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	ಆದರೆ (p[0] != '-' || p[1] != '-' || !p[2])
		ಹಿಂತಿರುಗಿ 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	ಆಗ (*p && *p != '=')
		++p;

	*optlen = (ಪೂರ್ಣಾಂಕ) (p - *optname);

	ಆದರೆ (!*p)
		/* an option with no '=...' part. */
		ಹಿಂತಿರುಗಿ 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	ಆಗ (*p)
		++p;
	*arglen = (ಪೂರ್ಣಾಂಕ) (p - *arg);

	ಹಿಂತಿರುಗಿ 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಕಂಡುಹಿಡಿ_opt (ರಚನೆ _scanopt_t *s, ಪೂರ್ಣಾಂಕ lookup_long, ಅಕ್ಷರ *optstart, ಪೂರ್ಣಾಂಕ
	len, ಪೂರ್ಣಾಂಕ *err_ಸಂಕೇತ, ಪೂರ್ಣಾಂಕ *opt_ಸ್ಥಾನಾಂತರ)
{
	ಪೂರ್ಣಾಂಕ     nmatch = 0, lastr_val = 0, i;

	*err_ಸಂಕೇತ = 0;
	*opt_ಸ್ಥಾನಾಂತರ = -1;

	ಆದರೆ (!optstart)
		ಹಿಂತಿರುಗಿ 0;

	ಗಾಗಿ (i = 0; i < s->optc; i++) {
		ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		ಆದರೆ (lookup_long && (s->aux[i].flags & IS_LONG)) {
			ಆದರೆ (len > s->aux[i].namelen)
				ಮುಂದುವರಿ;

			ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹೋಲಿಕೆ (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_ಸ್ಥಾನಾಂತರ = i;

				/* exact match overrides all. */
				ಆದರೆ (len == s->aux[i].namelen) {
					nmatch = 1;
					ನಿಲ್ಲಿಸು;
				}

				/* ambiguity is ok between aliases. */
				ಆದರೆ (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			ಆದರೆ (optname[0] == optstart[0]) {
				nmatch++;
				*opt_ಸ್ಥಾನಾಂತರ = i;
			}
		}
	}

	ಆದರೆ (nmatch == 0) {
		*err_ಸಂಕೇತ = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_ಸ್ಥಾನಾಂತರ = -1;
	}
	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (nmatch > 1) {
		*err_ಸಂಕೇತ = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_ಸ್ಥಾನಾಂತರ = -1;
	}

	ಹಿಂತಿರುಗಿ *err_ಸಂಕೇತ ? 0 : 1;
}


ಪೂರ್ಣಾಂಕ     scanopt (scanopt_t *svoid, ಅಕ್ಷರ **arg, ಪೂರ್ಣಾಂಕ *optindex)
{
	ಅಕ್ಷರ   *optname = ಖಾಲಿ, *optarg = ಖಾಲಿ, *pstart;
	ಪೂರ್ಣಾಂಕ     namelen = 0, arglen = 0;
	ಪೂರ್ಣಾಂಕ     errcode = 0, has_ಮುಂದಿನ;
	ಸ್ಥಿರಾಂಕ optspec_t *optp;
	ರಚನೆ _scanopt_t *s;
	ರಚನೆ _aux *auxp;
	ಪೂರ್ಣಾಂಕ     is_short;
	ಪೂರ್ಣಾಂಕ     opt_ಸ್ಥಾನಾಂತರ = -1;

	s = (ರಚನೆ _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	ಸುರಕ್ಷಿತ_ನಿಯೋಜಿಸು (arg, ಖಾಲಿ);
	ಸುರಕ್ಷಿತ_ನಿಯೋಜಿಸು (optindex, s->ಸೂಚ್ಯಂಕ);

	ಆದರೆ (s->ಸೂಚ್ಯಂಕ >= s->argc)
		ಹಿಂತಿರುಗಿ 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->ಸೂಚ್ಯಂಕ] + s->subscript;
	ಆದರೆ (!pstart)
		ಹಿಂತಿರುಗಿ 0;

	ಆದರೆ (s->subscript == 0) {

		/* test for exact match of "--" */
		ಆದರೆ (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			ಸುರಕ್ಷಿತ_ನಿಯೋಜಿಸು (optindex, s->ಸೂಚ್ಯಂಕ + 1);
			INC_ಸೂಚ್ಯಂಕ (s, 1);
			ಹಿಂತಿರುಗಿ 0;
		}

		/* Match an opt. */
		ಆದರೆ (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			ಆದರೆ (!ಕಂಡುಹಿಡಿ_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_ಸ್ಥಾನಾಂತರ)) {
				scanopt_err (s, 0, errcode);
				ಹಿಂತಿರುಗಿ errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		ಇಲ್ಲದಿದ್ದರೆ {
			/* It's not an option. We're done. */
			ಹಿಂತಿರುಗಿ 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	ಆದರೆ (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		ಆದರೆ (!ಕಂಡುಹಿಡಿ_opt
		    (s, 0, pstart, namelen, &errcode, &opt_ಸ್ಥಾನಾಂತರ)) {
			scanopt_err(s, 1, errcode);
			ಹಿಂತಿರುಗಿ errcode;
		}

		optarg = pstart + 1;
		ಆದರೆ (!*optarg) {
			optarg = ಖಾಲಿ;
			arglen = 0;
		}
		ಇಲ್ಲದಿದ್ದರೆ
			arglen = (ಪೂರ್ಣಾಂಕ) ಅಕ್ಷರಸರಣಿ_ಉದ್ದ (optarg);
	}

	/* At this point, we have a long or short option matched at opt_offset into
	 * the s->options array (and corresponding aux array).
	 * A trailing argument is in {optarg,arglen}, if any.
	 */

	/* Look ahead in argv[] to see if there is something
	 * that we can use as an argument (if needed). */
	has_ಮುಂದಿನ = s->ಸೂಚ್ಯಂಕ + 1 < s->argc;

	optp = s->options + opt_ಸ್ಥಾನಾಂತರ;
	auxp = s->aux + opt_ಸ್ಥಾನಾಂತರ;

	/* case: no args allowed */
	ಆದರೆ (auxp->flags & ARG_NONE) {
		ಆದರೆ (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_ಸೂಚ್ಯಂಕ (s, 1);
			ಹಿಂತಿರುಗಿ SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!optarg)
			INC_ಸೂಚ್ಯಂಕ (s, 1);
		ಇಲ್ಲದಿದ್ದರೆ
			s->subscript++;
		ಹಿಂತಿರುಗಿ optp->r_val;
	}

	/* case: required */
	ಆದರೆ (auxp->flags & ARG_REQ) {
		ಆದರೆ (!optarg && !has_ಮುಂದಿನ) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ಸಿಕ್ಕಿತು);
			ಹಿಂತಿರುಗಿ SCANOPT_ERR_ARG_NOT_ಸಿಕ್ಕಿತು;
		}

		ಆದರೆ (!optarg) {
			/* Let the next argv element become the argument. */
			ಸುರಕ್ಷಿತ_ನಿಯೋಜಿಸು (arg, s->argv[s->ಸೂಚ್ಯಂಕ + 1]);
			INC_ಸೂಚ್ಯಂಕ (s, 2);
		}
		ಇಲ್ಲದಿದ್ದರೆ {
			ಸುರಕ್ಷಿತ_ನಿಯೋಜಿಸು (arg, (ಅಕ್ಷರ *) optarg);
			INC_ಸೂಚ್ಯಂಕ (s, 1);
		}
		ಹಿಂತಿರುಗಿ optp->r_val;
	}

	/* case: optional */
	ಆದರೆ (auxp->flags & ARG_OPT) {
		ಸುರಕ್ಷಿತ_ನಿಯೋಜಿಸು (arg, optarg);
		INC_ಸೂಚ್ಯಂಕ (s, 1);
		ಹಿಂತಿರುಗಿ optp->r_val;
	}


	/* Should not reach here. */
	ಹಿಂತಿರುಗಿ 0;
}


ಪೂರ್ಣಾಂಕ     scanopt_destroy (scanopt_t *svoid)
{
	ರಚನೆ _scanopt_t *s;

	s = (ರಚನೆ _scanopt_t *) svoid;
	ಆದರೆ (s != ಖಾಲಿ) {
		ಬಿಡುಗಡೆ(s->aux);
		ಬಿಡುಗಡೆ(s);
	}
	ಹಿಂತಿರುಗಿ 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
