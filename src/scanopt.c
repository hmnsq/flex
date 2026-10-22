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

#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "scanopt.h"


/* Internal structures */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARG_NONE 0x01
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARG_REQ  0x02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ARG_OPT  0x04
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_LONG  0x08

ਬਣਤਰ _aux {
	ਪੂਰਨ     flags;		/* The above hex flags. */
	ਪੂਰਨ     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	ਪੂਰਨ     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


ਬਣਤਰ _scanopt_t {
	ਅਚਲ optspec_t *options;	/* List of options. */
	ਬਣਤਰ _aux *aux;	/* Auxiliary data about options. */
	ਪੂਰਨ     optc;		/* Number of options. */
	ਪੂਰਨ     argc;		/* Number of args. */
	ਅੱਖਰ  **argv;		/* Array of strings. */
	ਪੂਰਨ     ਸੂਚਕਾਂਕ;		/* Used as: argv[index][subscript]. */
	ਪੂਰਨ     subscript;
	ਅੱਖਰ    no_err_ਸੁਨੇਹਾ;	/* If true, do not print errors. */
	ਅੱਖਰ    has_long;
	ਅੱਖਰ    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
ਸਥਿਰ ਅਚਲ ਅੱਖਰ *NAME(ਬਣਤਰ _scanopt_t *, ਪੂਰਨ);
ਸਥਿਰ ਪੂਰਨ PRINTLEN(ਬਣਤਰ _scanopt_t *, ਪੂਰਨ);
ਸਥਿਰ ਪੂਰਨ RVAL(ਬਣਤਰ _scanopt_t *, ਪੂਰਨ);
ਸਥਿਰ ਪੂਰਨ FLAGS(ਬਣਤਰ _scanopt_t *, ਪੂਰਨ);
ਸਥਿਰ ਅਚਲ ਅੱਖਰ *DESC(ਬਣਤਰ _scanopt_t *, ਪੂਰਨ);
ਸਥਿਰ ਖਾਲੀ scanopt_err(ਬਣਤਰ _scanopt_t *, ਪੂਰਨ, ਪੂਰਨ);
ਸਥਿਰ ਪੂਰਨ matchlongopt(ਅੱਖਰ *, ਅੱਖਰ **, ਪੂਰਨ *, ਅੱਖਰ **, ਪੂਰਨ *);
ਸਥਿਰ ਪੂਰਨ ਲੱਭੋ_opt(ਬਣਤਰ _scanopt_t *, ਪੂਰਨ, ਅੱਖਰ *, ਪੂਰਨ, ਪੂਰਨ *, ਪੂਰਨ *opt_ਵਿੱਥ);

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *NAME (ਬਣਤਰ _scanopt_t *s, ਪੂਰਨ i)
{
	ਵਾਪਸ s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

ਸਥਿਰ ਪੂਰਨ PRINTLEN (ਬਣਤਰ _scanopt_t *s, ਪੂਰਨ i)
{
	ਵਾਪਸ s->aux[i].printlen;
}

ਸਥਿਰ ਪੂਰਨ RVAL (ਬਣਤਰ _scanopt_t *s, ਪੂਰਨ i)
{
	ਵਾਪਸ s->options[i].r_val;
}

ਸਥਿਰ ਪੂਰਨ FLAGS (ਬਣਤਰ _scanopt_t *s, ਪੂਰਨ i)
{
	ਵਾਪਸ s->aux[i].flags;
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *DESC (ਬਣਤਰ _scanopt_t *s, ਪੂਰਨ i)
{
	ਵਾਪਸ s->options[i].desc ? s->options[i].desc : "";
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SCANOPT_USAGE
ਸਥਿਰ ਪੂਰਨ get_ਖਾਨੇ_ਗਿਣਤੀ (ਖਾਲੀ);

ਸਥਿਰ ਪੂਰਨ get_ਖਾਨੇ_ਗਿਣਤੀ (ਖਾਲੀ)
{
	ਅੱਖਰ   *env;
	ਪੂਰਨ     ਖਾਨੇ_ਗਿਣਤੀ = 80;	/* default */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_NCURSES_H
	initscr ();
	endwin ();
	ਜੇ (ਖਾਨੇ_ਗਿਣਤੀ_2 > 0)
		ਵਾਪਸ ਖਾਨੇ_ਗਿਣਤੀ_2;
#ਜੇ_ਅੰਤ

	ਜੇ ((env = getenv ("COLUMNS")) != ਨਿਰਾ)
		ਖਾਨੇ_ਗਿਣਤੀ = atoi (env);

	ਵਾਪਸ ਖਾਨੇ_ਗਿਣਤੀ;
}
#ਜੇ_ਅੰਤ

/* Macro to check for NULL before assigning a value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੁਰੱਖਿਅਤ_ਸੌਂਪੋ(ptr,val) \
    ਕਰੋ{                      \
        ਜੇ((ptr)!=ਨਿਰਾ)      \
            *(ptr) = val;    \
    }ਜਦੋਂ(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INC_ਸੂਚਕਾਂਕ(s,n)     \
    ਕਰੋ{                    \
       (s)->ਸੂਚਕਾਂਕ += (n);  \
       (s)->subscript= 0;  \
    }ਜਦੋਂ(0)

scanopt_t *scanopt_init (ਅਚਲ optspec_t *options, ਪੂਰਨ argc, ਅੱਖਰ **argv, ਪੂਰਨ flags)
{
	ਪੂਰਨ     i;
	ਬਣਤਰ _scanopt_t *s;
	s = ਸਮ੍ਰਿਤੀ_ਦਿਓ(ਆਕਾਰ (ਬਣਤਰ _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (ਅੱਖਰ **) argv;
	s->ਸੂਚਕਾਂਕ = 1;
	s->subscript = 0;
	s->no_err_ਸੁਨੇਹਾ = (flags & SCANOPT_NO_ERR_ਸੁਨੇਹਾ);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	ਜਦੋਂ (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = ਸਮ੍ਰਿਤੀ_ਦਿਓ((size_t) s->optc * ਆਕਾਰ (ਬਣਤਰ _aux));

	ਲਈ (i = 0; i < s->optc; i++) {
		ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p, *pname;
		ਅਚਲ ਬਣਤਰ optspec_t *opt;
		ਬਣਤਰ _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		ਜੇ (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		ਨਹੀਂਤਾਂ {
			pname = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (ਪੂਰਨ) ਲੜੀ_ਲੰਬਾਈ (opt->opt_fmt);

		aux->namelen = 0;
		ਲਈ (p = pname + 1; *p; p++) {
			/* detect required arg */
			ਜੇ (*p == '=' || ਖਾਲੀ_ਥਾਂ_ਹੈ ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ)*p)
			    || !(aux->flags & IS_LONG)) {
				ਜੇ (aux->namelen == 0)
					aux->namelen = (ਪੂਰਨ) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			ਜੇ (*p == '[') {
				ਜੇ (aux->namelen == 0)
					aux->namelen = (ਪੂਰਨ) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				ਰੋਕੋ;
			}
		}
		ਜੇ (aux->namelen == 0)
			aux->namelen = (ਪੂਰਨ) (p - pname);
	}
	ਵਾਪਸ (scanopt_t *) s;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
ਬਣਤਰ usg_elem {
	ਪੂਰਨ     idx;
	ਬਣਤਰ usg_elem *ਅਗਲਾ;
	ਬਣਤਰ usg_elem *alias;
};
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ usg_elem usg_elem;


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
ਪੂਰਨ     scanopt_usage (scanopt_t *scanner, FILE *fp, ਅਚਲ ਅੱਖਰ *usage)
{
	ਬਣਤਰ _scanopt_t *s;
	ਪੂਰਨ     i, columns;
	ਅਚਲ ਪੂਰਨ indent = 2;
	usg_elem *byr_val = ਨਿਰਾ;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	ਪੂਰਨ     store_idx = 0;
	usg_elem *ue;
	ਪੂਰਨ     opt_ਖਾਨਾ_ਚੌੜਾਈ = 0, desc_ਖਾਨਾ_ਚੌੜਾਈ = 0;
	ਪੂਰਨ     desccol;
	ਪੂਰਨ     print_ਲੜੀਵਾਰ = 0;

	s = (ਬਣਤਰ _scanopt_t *) scanner;

	ਜੇ (usage) {
		fprintf (fp, "%s\n", usage);
	}
	ਨਹੀਂਤਾਂ {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = ਸਮ੍ਰਿਤੀ_ਦਿਓ((size_t) s->optc * ਆਕਾਰ (usg_elem));
	ਲਈ (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->ਅਗਲਾ = ue->alias = ਨਿਰਾ;

		/* insert into list. */
		ਜੇ (!byr_val)
			byr_val = ue;
		ਨਹੀਂਤਾਂ {
			ਪੂਰਨ     ਮਿਲਿਆ_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = ਨਿਰਾ;

			ue_curr = &byr_val;
			ਜਦੋਂ (*ue_curr) {
				ਜੇ (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					ਮਿਲਿਆ_alias = 1;
					ਰੋਕੋ;
				}
				ਜੇ (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->ਅਗਲਾ);
			}
			ਜੇ (!ਮਿਲਿਆ_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->ਅਗਲਾ = *ue_curr;
			*ue_curr = ue;
		}
	}

#ਜੇ 0
	ਜੇ (1) {
		ਲਿਖੋ ("ORIGINAL:\n");
		ਲਈ (i = 0; i < s->optc; i++)
			ਲਿਖੋ ("%2d: %s\n", i, NAME (s, i));
		ਲਿਖੋ ("SORTED:\n");
		ue = byr_val;
		ਜਦੋਂ (ue) {
			usg_elem *ue2;

			ਲਿਖੋ ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			ਲਈ (ue2 = ue->alias; ue2; ue2 = ue2->ਅਗਲਾ)
				ਲਿਖੋ ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->ਅਗਲਾ;
		}
	}
#ਜੇ_ਅੰਤ

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	ਲਈ (ue = byr_val; ue; ue = ue->ਅਗਲਾ) {
		usg_elem *ap;
		ਪੂਰਨ     len;

		len = PRINTLEN(s, ue->idx);

		ਲਈ (ap = ue->alias; ap; ap = ap->ਅਗਲਾ) {
			len += PRINTLEN(s, ap->idx) + (ਪੂਰਨ) ਲੜੀ_ਲੰਬਾਈ(", ");
		}

		ਜੇ (len > opt_ਖਾਨਾ_ਚੌੜਾਈ)
			opt_ਖਾਨਾ_ਚੌੜਾਈ = len;

		/* It's much easier to calculate length for description column! */
		len = (ਪੂਰਨ) ਲੜੀ_ਲੰਬਾਈ (DESC (s, ue->idx));
		ਜੇ (len > desc_ਖਾਨਾ_ਚੌੜਾਈ)
			desc_ਖਾਨਾ_ਚੌੜਾਈ = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_ਖਾਨੇ_ਗਿਣਤੀ () - 1;
	ਜੇ (opt_ਖਾਨਾ_ਚੌੜਾਈ + desc_ਖਾਨਾ_ਚੌੜਾਈ + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_ਖਾਨਾ_ਚੌੜਾਈ = columns - (opt_ਖਾਨਾ_ਚੌੜਾਈ + indent * 2);
		ਜੇ (desc_ਖਾਨਾ_ਚੌੜਾਈ < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_ਖਾਨਾ_ਚੌੜਾਈ = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;
	}
	desccol = opt_ਖਾਨਾ_ਚੌੜਾਈ + indent * 2;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	ਜਦੋਂ (print_ਲੜੀਵਾਰ++ < 2) {
		ਲਈ (ue = byr_val; ue; ue = ue->ਅਗਲਾ) {
			usg_elem *ap;
			ਪੂਰਨ     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			ਲਈ (ap = ue->alias; ap; ap = ap->ਅਗਲਾ) {
				ਜੇ (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					ਰੋਕੋ;
				}
			}
			ਜੇ ((print_ਲੜੀਵਾਰ == 1 && !has_short) ||
			    (print_ਲੜੀਵਾਰ == 2 && has_short))
				ਜਾਰੀ;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PRINT_IT(i) ਕਰੋ{\
                  ਜੇ(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }ਜਦੋਂ(0)

			ਜੇ (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			ਲਈ (ap = ue->alias; ap; ap = ap->ਅਗਲਾ) {
				ਜੇ (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			ਜੇ (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			ਲਈ (ap = ue->alias; ap; ap = ap->ਅਗਲਾ) {
				ਜੇ (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			ਜੇ (1) {
				ਅਚਲ ਅੱਖਰ *pstart;

				pstart = DESC (s, ue->idx);
				ਜਦੋਂ (1) {
					ਪੂਰਨ     n = 0;
					ਅਚਲ ਅੱਖਰ *lastws = ਨਿਰਾ, *p;

					p = pstart;

					ਜਦੋਂ (*p && n < desc_ਖਾਨਾ_ਚੌੜਾਈ
					       && *p != '\n') {
						ਜੇ (ਖਾਲੀ_ਥਾਂ_ਹੈ ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					ਜੇ (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						ਰੋਕੋ;
					}
					ਨਹੀਂਤਾਂ ਜੇ (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						ਜਾਰੀ;
					}
					ਨਹੀਂਤਾਂ {	/* we hit the edge of the screen. wrap at space if possible. */
						ਜੇ (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (ਪੂਰਨ)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						ਨਹੀਂਤਾਂ {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						ਜਾਰੀ;
					}
				}
			}
		}
	}			/* end while */
	ਮੁਕਤ (store);
	ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ /* no scanopt_usage */


ਸਥਿਰ ਖਾਲੀ scanopt_err(ਬਣਤਰ _scanopt_t *s, ਪੂਰਨ is_short, ਪੂਰਨ err)
{
	ਅਚਲ ਅੱਖਰ *optname = "";
	ਅੱਖਰ    optchar[2];

	ਜੇ (!s->no_err_ਸੁਨੇਹਾ) {

		ਜੇ (s->ਸੂਚਕਾਂਕ > 0 && s->ਸੂਚਕਾਂਕ < s->argc) {
			ਜੇ (is_short) {
				optchar[0] =
					s->argv[s->ਸੂਚਕਾਂਕ][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			ਨਹੀਂਤਾਂ {
				optname = s->argv[s->ਸੂਚਕਾਂਕ];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		ਚੋਣ (err) {
		ਹਾਲਤ SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			ਰੋਕੋ;
		ਹਾਲਤ SCANOPT_ERR_ARG_NOT_ਮਿਲਿਆ:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			ਰੋਕੋ;
		ਹਾਲਤ SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			ਰੋਕੋ;
		ਹਾਲਤ SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			ਰੋਕੋ;
		ਮੂਲ:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			ਰੋਕੋ;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
ਸਥਿਰ ਪੂਰਨ matchlongopt (ਅੱਖਰ *str, ਅੱਖਰ **optname, ਪੂਰਨ *optlen, ਅੱਖਰ **arg, ਪੂਰਨ *arglen)
{
	ਅੱਖਰ   *p;

	*optname = *arg = ਨਿਰਾ;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	ਜੇ (p[0] != '-' || p[1] != '-' || !p[2])
		ਵਾਪਸ 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	ਜਦੋਂ (*p && *p != '=')
		++p;

	*optlen = (ਪੂਰਨ) (p - *optname);

	ਜੇ (!*p)
		/* an option with no '=...' part. */
		ਵਾਪਸ 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	ਜਦੋਂ (*p)
		++p;
	*arglen = (ਪੂਰਨ) (p - *arg);

	ਵਾਪਸ 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
ਸਥਿਰ ਪੂਰਨ ਲੱਭੋ_opt (ਬਣਤਰ _scanopt_t *s, ਪੂਰਨ lookup_long, ਅੱਖਰ *optstart, ਪੂਰਨ
	len, ਪੂਰਨ *err_ਕੋਡ, ਪੂਰਨ *opt_ਵਿੱਥ)
{
	ਪੂਰਨ     nmatch = 0, lastr_val = 0, i;

	*err_ਕੋਡ = 0;
	*opt_ਵਿੱਥ = -1;

	ਜੇ (!optstart)
		ਵਾਪਸ 0;

	ਲਈ (i = 0; i < s->optc; i++) {
		ਅਚਲ ਅੱਖਰ   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		ਜੇ (lookup_long && (s->aux[i].flags & IS_LONG)) {
			ਜੇ (len > s->aux[i].namelen)
				ਜਾਰੀ;

			ਜੇ (ਲੜੀ_ਤੁਲਨਾ (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_ਵਿੱਥ = i;

				/* exact match overrides all. */
				ਜੇ (len == s->aux[i].namelen) {
					nmatch = 1;
					ਰੋਕੋ;
				}

				/* ambiguity is ok between aliases. */
				ਜੇ (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		ਨਹੀਂਤਾਂ ਜੇ (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			ਜੇ (optname[0] == optstart[0]) {
				nmatch++;
				*opt_ਵਿੱਥ = i;
			}
		}
	}

	ਜੇ (nmatch == 0) {
		*err_ਕੋਡ = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_ਵਿੱਥ = -1;
	}
	ਨਹੀਂਤਾਂ ਜੇ (nmatch > 1) {
		*err_ਕੋਡ = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_ਵਿੱਥ = -1;
	}

	ਵਾਪਸ *err_ਕੋਡ ? 0 : 1;
}


ਪੂਰਨ     scanopt (scanopt_t *svoid, ਅੱਖਰ **arg, ਪੂਰਨ *optindex)
{
	ਅੱਖਰ   *optname = ਨਿਰਾ, *optarg = ਨਿਰਾ, *pstart;
	ਪੂਰਨ     namelen = 0, arglen = 0;
	ਪੂਰਨ     errcode = 0, has_ਅਗਲਾ;
	ਅਚਲ optspec_t *optp;
	ਬਣਤਰ _scanopt_t *s;
	ਬਣਤਰ _aux *auxp;
	ਪੂਰਨ     is_short;
	ਪੂਰਨ     opt_ਵਿੱਥ = -1;

	s = (ਬਣਤਰ _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	ਸੁਰੱਖਿਅਤ_ਸੌਂਪੋ (arg, ਨਿਰਾ);
	ਸੁਰੱਖਿਅਤ_ਸੌਂਪੋ (optindex, s->ਸੂਚਕਾਂਕ);

	ਜੇ (s->ਸੂਚਕਾਂਕ >= s->argc)
		ਵਾਪਸ 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->ਸੂਚਕਾਂਕ] + s->subscript;
	ਜੇ (!pstart)
		ਵਾਪਸ 0;

	ਜੇ (s->subscript == 0) {

		/* test for exact match of "--" */
		ਜੇ (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			ਸੁਰੱਖਿਅਤ_ਸੌਂਪੋ (optindex, s->ਸੂਚਕਾਂਕ + 1);
			INC_ਸੂਚਕਾਂਕ (s, 1);
			ਵਾਪਸ 0;
		}

		/* Match an opt. */
		ਜੇ (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			ਜੇ (!ਲੱਭੋ_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_ਵਿੱਥ)) {
				scanopt_err (s, 0, errcode);
				ਵਾਪਸ errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		ਨਹੀਂਤਾਂ ਜੇ (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		ਨਹੀਂਤਾਂ {
			/* It's not an option. We're done. */
			ਵਾਪਸ 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	ਜੇ (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		ਜੇ (!ਲੱਭੋ_opt
		    (s, 0, pstart, namelen, &errcode, &opt_ਵਿੱਥ)) {
			scanopt_err(s, 1, errcode);
			ਵਾਪਸ errcode;
		}

		optarg = pstart + 1;
		ਜੇ (!*optarg) {
			optarg = ਨਿਰਾ;
			arglen = 0;
		}
		ਨਹੀਂਤਾਂ
			arglen = (ਪੂਰਨ) ਲੜੀ_ਲੰਬਾਈ (optarg);
	}

	/* At this point, we have a long or short option matched at opt_offset into
	 * the s->options array (and corresponding aux array).
	 * A trailing argument is in {optarg,arglen}, if any.
	 */

	/* Look ahead in argv[] to see if there is something
	 * that we can use as an argument (if needed). */
	has_ਅਗਲਾ = s->ਸੂਚਕਾਂਕ + 1 < s->argc;

	optp = s->options + opt_ਵਿੱਥ;
	auxp = s->aux + opt_ਵਿੱਥ;

	/* case: no args allowed */
	ਜੇ (auxp->flags & ARG_NONE) {
		ਜੇ (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_ਸੂਚਕਾਂਕ (s, 1);
			ਵਾਪਸ SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		ਨਹੀਂਤਾਂ ਜੇ (!optarg)
			INC_ਸੂਚਕਾਂਕ (s, 1);
		ਨਹੀਂਤਾਂ
			s->subscript++;
		ਵਾਪਸ optp->r_val;
	}

	/* case: required */
	ਜੇ (auxp->flags & ARG_REQ) {
		ਜੇ (!optarg && !has_ਅਗਲਾ) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ਮਿਲਿਆ);
			ਵਾਪਸ SCANOPT_ERR_ARG_NOT_ਮਿਲਿਆ;
		}

		ਜੇ (!optarg) {
			/* Let the next argv element become the argument. */
			ਸੁਰੱਖਿਅਤ_ਸੌਂਪੋ (arg, s->argv[s->ਸੂਚਕਾਂਕ + 1]);
			INC_ਸੂਚਕਾਂਕ (s, 2);
		}
		ਨਹੀਂਤਾਂ {
			ਸੁਰੱਖਿਅਤ_ਸੌਂਪੋ (arg, (ਅੱਖਰ *) optarg);
			INC_ਸੂਚਕਾਂਕ (s, 1);
		}
		ਵਾਪਸ optp->r_val;
	}

	/* case: optional */
	ਜੇ (auxp->flags & ARG_OPT) {
		ਸੁਰੱਖਿਅਤ_ਸੌਂਪੋ (arg, optarg);
		INC_ਸੂਚਕਾਂਕ (s, 1);
		ਵਾਪਸ optp->r_val;
	}


	/* Should not reach here. */
	ਵਾਪਸ 0;
}


ਪੂਰਨ     scanopt_destroy (scanopt_t *svoid)
{
	ਬਣਤਰ _scanopt_t *s;

	s = (ਬਣਤਰ _scanopt_t *) svoid;
	ਜੇ (s != ਨਿਰਾ) {
		ਮੁਕਤ(s->aux);
		ਮੁਕਤ(s);
	}
	ਵਾਪਸ 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
