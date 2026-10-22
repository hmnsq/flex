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

#অন্তর্ভাৱ "flexdef.h"
#অন্তর্ভাৱ "scanopt.h"


/* Internal structures */

#define ARG_NONE 0x01
#define ARG_REQ  0x02
#define ARG_OPT  0x04
#define IS_LONG  0x08

সংরচনা _aux {
	পূর্ণাঙ্ক     flags;		/* The above hex flags. */
	পূর্ণাঙ্ক     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	পূর্ণাঙ্ক     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


সংরচনা _scanopt_t {
	ধ্রুৱ optspec_t *options;	/* List of options. */
	সংরচনা _aux *aux;	/* Auxiliary data about options. */
	পূর্ণাঙ্ক     optc;		/* Number of options. */
	পূর্ণাঙ্ক     argc;		/* Number of args. */
	ৱর্ণ  **argv;		/* Array of strings. */
	পূর্ণাঙ্ক     index;		/* Used as: argv[index][subscript]. */
	পূর্ণাঙ্ক     subscript;
	ৱর্ণ    no_err_বাৰ্তা;	/* If true, do not print errors. */
	ৱর্ণ    has_long;
	ৱর্ণ    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
স্থির ধ্রুৱ ৱর্ণ *NAME(সংরচনা _scanopt_t *, পূর্ণাঙ্ক);
স্থির পূর্ণাঙ্ক PRINTLEN(সংরচনা _scanopt_t *, পূর্ণাঙ্ক);
স্থির পূর্ণাঙ্ক RVAL(সংরচনা _scanopt_t *, পূর্ণাঙ্ক);
স্থির পূর্ণাঙ্ক FLAGS(সংরচনা _scanopt_t *, পূর্ণাঙ্ক);
স্থির ধ্রুৱ ৱর্ণ *DESC(সংরচনা _scanopt_t *, পূর্ণাঙ্ক);
স্থির শূন্য scanopt_err(সংরচনা _scanopt_t *, পূর্ণাঙ্ক, পূর্ণাঙ্ক);
স্থির পূর্ণাঙ্ক matchlongopt(ৱর্ণ *, ৱর্ণ **, পূর্ণাঙ্ক *, ৱর্ণ **, পূর্ণাঙ্ক *);
স্থির পূর্ণাঙ্ক find_opt(সংরচনা _scanopt_t *, পূর্ণাঙ্ক, ৱর্ণ *, পূর্ণাঙ্ক, পূর্ণাঙ্ক *, পূর্ণাঙ্ক *opt_offset);

স্থির ধ্রুৱ ৱর্ণ *NAME (সংরচনা _scanopt_t *s, পূর্ণাঙ্ক i)
{
	ঘূৰাই s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

স্থির পূর্ণাঙ্ক PRINTLEN (সংরচনা _scanopt_t *s, পূর্ণাঙ্ক i)
{
	ঘূৰাই s->aux[i].printlen;
}

স্থির পূর্ণাঙ্ক RVAL (সংরচনা _scanopt_t *s, পূর্ণাঙ্ক i)
{
	ঘূৰাই s->options[i].r_val;
}

স্থির পূর্ণাঙ্ক FLAGS (সংরচনা _scanopt_t *s, পূর্ণাঙ্ক i)
{
	ঘূৰাই s->aux[i].flags;
}

স্থির ধ্রুৱ ৱর্ণ *DESC (সংরচনা _scanopt_t *s, পূর্ণাঙ্ক i)
{
	ঘূৰাই s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
স্থির পূর্ণাঙ্ক get_cols (শূন্য);

স্থির পূর্ণাঙ্ক get_cols (শূন্য)
{
	ৱর্ণ   *env;
	পূর্ণাঙ্ক     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	যদি (COLS > 0)
		ঘূৰাই COLS;
#endif

	যদি ((env = getenv ("COLUMNS")) != রিক্ত)
		cols = atoi (env);

	ঘূৰাই cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    কৰা{                      \
        যদি((ptr)!=রিক্ত)      \
            *(ptr) = val;    \
    }যেতিয়ালৈ(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    কৰা{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }যেতিয়ালৈ(0)

scanopt_t *scanopt_init (ধ্রুৱ optspec_t *options, পূর্ণাঙ্ক argc, ৱর্ণ **argv, পূর্ণাঙ্ক flags)
{
	পূর্ণাঙ্ক     i;
	সংরচনা _scanopt_t *s;
	s = malloc(পরিমাণ (সংরচনা _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (ৱর্ণ **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_বাৰ্তা = (flags & SCANOPT_NO_ERR_বাৰ্তা);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	যেতিয়ালৈ (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * পরিমাণ (সংরচনা _aux));

	বাবে (i = 0; i < s->optc; i++) {
		ধ্রুৱ unsigned ৱর্ণ *p, *pname;
		ধ্রুৱ সংরচনা optspec_t *opt;
		সংরচনা _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		যদি (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ধ্রুৱ unsigned ৱর্ণ *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		অন্যথা {
			pname = (ধ্রুৱ unsigned ৱর্ণ *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (পূর্ণাঙ্ক) strlen (opt->opt_fmt);

		aux->namelen = 0;
		বাবে (p = pname + 1; *p; p++) {
			/* detect required arg */
			যদি (*p == '=' || isspace ((unsigned ৱর্ণ)*p)
			    || !(aux->flags & IS_LONG)) {
				যদি (aux->namelen == 0)
					aux->namelen = (পূর্ণাঙ্ক) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			যদি (*p == '[') {
				যদি (aux->namelen == 0)
					aux->namelen = (পূর্ণাঙ্ক) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				ভঙ্গ;
			}
		}
		যদি (aux->namelen == 0)
			aux->namelen = (পূর্ণাঙ্ক) (p - pname);
	}
	ঘূৰাই (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
সংরচনা usg_elem {
	পূর্ণাঙ্ক     idx;
	সংরচনা usg_elem *next;
	সংরচনা usg_elem *alias;
};
প্রকারনির্দেশ সংরচনা usg_elem usg_elem;


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
পূর্ণাঙ্ক     scanopt_usage (scanopt_t *scanner, FILE *fp, ধ্রুৱ ৱর্ণ *usage)
{
	সংরচনা _scanopt_t *s;
	পূর্ণাঙ্ক     i, columns;
	ধ্রুৱ পূর্ণাঙ্ক indent = 2;
	usg_elem *byr_val = রিক্ত;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	পূর্ণাঙ্ক     store_idx = 0;
	usg_elem *ue;
	পূর্ণাঙ্ক     opt_col_width = 0, desc_col_width = 0;
	পূর্ণাঙ্ক     desccol;
	পূর্ণাঙ্ক     print_run = 0;

	s = (সংরচনা _scanopt_t *) scanner;

	যদি (usage) {
		fprintf (fp, "%s\n", usage);
	}
	অন্যথা {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * পরিমাণ (usg_elem));
	বাবে (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = রিক্ত;

		/* insert into list. */
		যদি (!byr_val)
			byr_val = ue;
		অন্যথা {
			পূর্ণাঙ্ক     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = রিক্ত;

			ue_curr = &byr_val;
			যেতিয়ালৈ (*ue_curr) {
				যদি (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					ভঙ্গ;
				}
				যদি (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			যদি (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#যদি 0
	যদি (1) {
		printf ("ORIGINAL:\n");
		বাবে (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		যেতিয়ালৈ (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			বাবে (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	বাবে (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		পূর্ণাঙ্ক     len;

		len = PRINTLEN(s, ue->idx);

		বাবে (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (পূর্ণাঙ্ক) strlen(", ");
		}

		যদি (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (পূর্ণাঙ্ক) strlen (DESC (s, ue->idx));
		যদি (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	যদি (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		যদি (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	যেতিয়ালৈ (print_run++ < 2) {
		বাবে (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			পূর্ণাঙ্ক     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			বাবে (ap = ue->alias; ap; ap = ap->next) {
				যদি (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					ভঙ্গ;
				}
			}
			যদি ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				অনুৱর্ত;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) কৰা{\
                  যদি(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }যেতিয়ালৈ(0)

			যদি (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			বাবে (ap = ue->alias; ap; ap = ap->next) {
				যদি (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			যদি (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			বাবে (ap = ue->alias; ap; ap = ap->next) {
				যদি (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			যদি (1) {
				ধ্রুৱ ৱর্ণ *pstart;

				pstart = DESC (s, ue->idx);
				যেতিয়ালৈ (1) {
					পূর্ণাঙ্ক     n = 0;
					ধ্রুৱ ৱর্ণ *lastws = রিক্ত, *p;

					p = pstart;

					যেতিয়ালৈ (*p && n < desc_col_width
					       && *p != '\n') {
						যদি (isspace ((unsigned ৱর্ণ)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					যদি (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						ভঙ্গ;
					}
					অন্যথা যদি (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						অনুৱর্ত;
					}
					অন্যথা {	/* we hit the edge of the screen. wrap at space if possible. */
						যদি (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (পূর্ণাঙ্ক)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						অন্যথা {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						অনুৱর্ত;
					}
				}
			}
		}
	}			/* end while */
	মুক্ত (store);
	ঘূৰাই 0;
}
#endif /* no scanopt_usage */


স্থির শূন্য scanopt_err(সংরচনা _scanopt_t *s, পূর্ণাঙ্ক is_short, পূর্ণাঙ্ক err)
{
	ধ্রুৱ ৱর্ণ *optname = "";
	ৱর্ণ    optchar[2];

	যদি (!s->no_err_বাৰ্তা) {

		যদি (s->index > 0 && s->index < s->argc) {
			যদি (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			অন্যথা {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		ৱিকল্প (err) {
		পক্ষ SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			ভঙ্গ;
		পক্ষ SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			ভঙ্গ;
		পক্ষ SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			ভঙ্গ;
		পক্ষ SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			ভঙ্গ;
		স্ৱভাৱ:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			ভঙ্গ;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
স্থির পূর্ণাঙ্ক matchlongopt (ৱর্ণ *str, ৱর্ণ **optname, পূর্ণাঙ্ক *optlen, ৱর্ণ **arg, পূর্ণাঙ্ক *arglen)
{
	ৱর্ণ   *p;

	*optname = *arg = রিক্ত;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	যদি (p[0] != '-' || p[1] != '-' || !p[2])
		ঘূৰাই 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	যেতিয়ালৈ (*p && *p != '=')
		++p;

	*optlen = (পূর্ণাঙ্ক) (p - *optname);

	যদি (!*p)
		/* an option with no '=...' part. */
		ঘূৰাই 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	যেতিয়ালৈ (*p)
		++p;
	*arglen = (পূর্ণাঙ্ক) (p - *arg);

	ঘূৰাই 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
স্থির পূর্ণাঙ্ক find_opt (সংরচনা _scanopt_t *s, পূর্ণাঙ্ক lookup_long, ৱর্ণ *optstart, পূর্ণাঙ্ক
	len, পূর্ণাঙ্ক *err_code, পূর্ণাঙ্ক *opt_offset)
{
	পূর্ণাঙ্ক     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	যদি (!optstart)
		ঘূৰাই 0;

	বাবে (i = 0; i < s->optc; i++) {
		ধ্রুৱ ৱর্ণ   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		যদি (lookup_long && (s->aux[i].flags & IS_LONG)) {
			যদি (len > s->aux[i].namelen)
				অনুৱর্ত;

			যদি (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				যদি (len == s->aux[i].namelen) {
					nmatch = 1;
					ভঙ্গ;
				}

				/* ambiguity is ok between aliases. */
				যদি (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		অন্যথা যদি (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			যদি (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	যদি (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	অন্যথা যদি (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	ঘূৰাই *err_code ? 0 : 1;
}


পূর্ণাঙ্ক     scanopt (scanopt_t *svoid, ৱর্ণ **arg, পূর্ণাঙ্ক *optindex)
{
	ৱর্ণ   *optname = রিক্ত, *optarg = রিক্ত, *pstart;
	পূর্ণাঙ্ক     namelen = 0, arglen = 0;
	পূর্ণাঙ্ক     errcode = 0, has_next;
	ধ্রুৱ optspec_t *optp;
	সংরচনা _scanopt_t *s;
	সংরচনা _aux *auxp;
	পূর্ণাঙ্ক     is_short;
	পূর্ণাঙ্ক     opt_offset = -1;

	s = (সংরচনা _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, রিক্ত);
	SAFE_ASSIGN (optindex, s->index);

	যদি (s->index >= s->argc)
		ঘূৰাই 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	যদি (!pstart)
		ঘূৰাই 0;

	যদি (s->subscript == 0) {

		/* test for exact match of "--" */
		যদি (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			ঘূৰাই 0;
		}

		/* Match an opt. */
		যদি (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			যদি (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				ঘূৰাই errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		অন্যথা যদি (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		অন্যথা {
			/* It's not an option. We're done. */
			ঘূৰাই 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	যদি (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		যদি (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			ঘূৰাই errcode;
		}

		optarg = pstart + 1;
		যদি (!*optarg) {
			optarg = রিক্ত;
			arglen = 0;
		}
		অন্যথা
			arglen = (পূর্ণাঙ্ক) strlen (optarg);
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
	যদি (auxp->flags & ARG_NONE) {
		যদি (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			ঘূৰাই SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		অন্যথা যদি (!optarg)
			INC_INDEX (s, 1);
		অন্যথা
			s->subscript++;
		ঘূৰাই optp->r_val;
	}

	/* case: required */
	যদি (auxp->flags & ARG_REQ) {
		যদি (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			ঘূৰাই SCANOPT_ERR_ARG_NOT_FOUND;
		}

		যদি (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		অন্যথা {
			SAFE_ASSIGN (arg, (ৱর্ণ *) optarg);
			INC_INDEX (s, 1);
		}
		ঘূৰাই optp->r_val;
	}

	/* case: optional */
	যদি (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		ঘূৰাই optp->r_val;
	}


	/* Should not reach here. */
	ঘূৰাই 0;
}


পূর্ণাঙ্ক     scanopt_destroy (scanopt_t *svoid)
{
	সংরচনা _scanopt_t *s;

	s = (সংরচনা _scanopt_t *) svoid;
	যদি (s != রিক্ত) {
		মুক্ত(s->aux);
		মুক্ত(s);
	}
	ঘূৰাই 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
