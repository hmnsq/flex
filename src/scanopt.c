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

#অন্তর্ভাব "flexdef.h"
#অন্তর্ভাব "scanopt.h"


/* Internal structures */

#define ARG_NONE 0x01
#define ARG_REQ  0x02
#define ARG_OPT  0x04
#define IS_LONG  0x08

কাঠামো _aux {
	পূর্ণসংখ্যা     flags;		/* The above hex flags. */
	পূর্ণসংখ্যা     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	পূর্ণসংখ্যা     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


কাঠামো _scanopt_t {
	ধ্রুবক optspec_t *options;	/* List of options. */
	কাঠামো _aux *aux;	/* Auxiliary data about options. */
	পূর্ণসংখ্যা     optc;		/* Number of options. */
	পূর্ণসংখ্যা     argc;		/* Number of args. */
	অক্ষর  **argv;		/* Array of strings. */
	পূর্ণসংখ্যা     সূচক;		/* Used as: argv[index][subscript]. */
	পূর্ণসংখ্যা     subscript;
	অক্ষর    no_err_বার্তা;	/* If true, do not print errors. */
	অক্ষর    has_long;
	অক্ষর    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
স্থির ধ্রুবক অক্ষর *NAME(কাঠামো _scanopt_t *, পূর্ণসংখ্যা);
স্থির পূর্ণসংখ্যা PRINTLEN(কাঠামো _scanopt_t *, পূর্ণসংখ্যা);
স্থির পূর্ণসংখ্যা RVAL(কাঠামো _scanopt_t *, পূর্ণসংখ্যা);
স্থির পূর্ণসংখ্যা FLAGS(কাঠামো _scanopt_t *, পূর্ণসংখ্যা);
স্থির ধ্রুবক অক্ষর *DESC(কাঠামো _scanopt_t *, পূর্ণসংখ্যা);
স্থির শূন্য scanopt_err(কাঠামো _scanopt_t *, পূর্ণসংখ্যা, পূর্ণসংখ্যা);
স্থির পূর্ণসংখ্যা matchlongopt(অক্ষর *, অক্ষর **, পূর্ণসংখ্যা *, অক্ষর **, পূর্ণসংখ্যা *);
স্থির পূর্ণসংখ্যা find_opt(কাঠামো _scanopt_t *, পূর্ণসংখ্যা, অক্ষর *, পূর্ণসংখ্যা, পূর্ণসংখ্যা *, পূর্ণসংখ্যা *opt_offset);

স্থির ধ্রুবক অক্ষর *NAME (কাঠামো _scanopt_t *s, পূর্ণসংখ্যা i)
{
	ফেরত s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

স্থির পূর্ণসংখ্যা PRINTLEN (কাঠামো _scanopt_t *s, পূর্ণসংখ্যা i)
{
	ফেরত s->aux[i].printlen;
}

স্থির পূর্ণসংখ্যা RVAL (কাঠামো _scanopt_t *s, পূর্ণসংখ্যা i)
{
	ফেরত s->options[i].r_val;
}

স্থির পূর্ণসংখ্যা FLAGS (কাঠামো _scanopt_t *s, পূর্ণসংখ্যা i)
{
	ফেরত s->aux[i].flags;
}

স্থির ধ্রুবক অক্ষর *DESC (কাঠামো _scanopt_t *s, পূর্ণসংখ্যা i)
{
	ফেরত s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
স্থির পূর্ণসংখ্যা get_cols (শূন্য);

স্থির পূর্ণসংখ্যা get_cols (শূন্য)
{
	অক্ষর   *env;
	পূর্ণসংখ্যা     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	যদি (COLS > 0)
		ফেরত COLS;
#endif

	যদি ((env = getenv ("COLUMNS")) != ফাঁকা)
		cols = atoi (env);

	ফেরত cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    করো{                      \
        যদি((ptr)!=ফাঁকা)      \
            *(ptr) = val;    \
    }যখন(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_সূচক(s,n)     \
    করো{                    \
       (s)->সূচক += (n);  \
       (s)->subscript= 0;  \
    }যখন(0)

scanopt_t *scanopt_init (ধ্রুবক optspec_t *options, পূর্ণসংখ্যা argc, অক্ষর **argv, পূর্ণসংখ্যা flags)
{
	পূর্ণসংখ্যা     i;
	কাঠামো _scanopt_t *s;
	s = malloc(আকার (কাঠামো _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (অক্ষর **) argv;
	s->সূচক = 1;
	s->subscript = 0;
	s->no_err_বার্তা = (flags & SCANOPT_NO_ERR_বার্তা);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	যখন (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * আকার (কাঠামো _aux));

	জন্য (i = 0; i < s->optc; i++) {
		ধ্রুবক unsigned অক্ষর *p, *pname;
		ধ্রুবক কাঠামো optspec_t *opt;
		কাঠামো _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		যদি (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ধ্রুবক unsigned অক্ষর *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		অন্যথা {
			pname = (ধ্রুবক unsigned অক্ষর *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (পূর্ণসংখ্যা) strlen (opt->opt_fmt);

		aux->namelen = 0;
		জন্য (p = pname + 1; *p; p++) {
			/* detect required arg */
			যদি (*p == '=' || isspace ((unsigned অক্ষর)*p)
			    || !(aux->flags & IS_LONG)) {
				যদি (aux->namelen == 0)
					aux->namelen = (পূর্ণসংখ্যা) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			যদি (*p == '[') {
				যদি (aux->namelen == 0)
					aux->namelen = (পূর্ণসংখ্যা) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				বিরতি;
			}
		}
		যদি (aux->namelen == 0)
			aux->namelen = (পূর্ণসংখ্যা) (p - pname);
	}
	ফেরত (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
কাঠামো usg_elem {
	পূর্ণসংখ্যা     idx;
	কাঠামো usg_elem *পরবর্তী;
	কাঠামো usg_elem *alias;
};
প্রকারলেখ কাঠামো usg_elem usg_elem;


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
পূর্ণসংখ্যা     scanopt_usage (scanopt_t *scanner, FILE *fp, ধ্রুবক অক্ষর *usage)
{
	কাঠামো _scanopt_t *s;
	পূর্ণসংখ্যা     i, columns;
	ধ্রুবক পূর্ণসংখ্যা indent = 2;
	usg_elem *byr_val = ফাঁকা;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	পূর্ণসংখ্যা     store_idx = 0;
	usg_elem *ue;
	পূর্ণসংখ্যা     opt_col_width = 0, desc_col_width = 0;
	পূর্ণসংখ্যা     desccol;
	পূর্ণসংখ্যা     print_run = 0;

	s = (কাঠামো _scanopt_t *) scanner;

	যদি (usage) {
		fprintf (fp, "%s\n", usage);
	}
	অন্যথা {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * আকার (usg_elem));
	জন্য (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->পরবর্তী = ue->alias = ফাঁকা;

		/* insert into list. */
		যদি (!byr_val)
			byr_val = ue;
		অন্যথা {
			পূর্ণসংখ্যা     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = ফাঁকা;

			ue_curr = &byr_val;
			যখন (*ue_curr) {
				যদি (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					বিরতি;
				}
				যদি (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->পরবর্তী);
			}
			যদি (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->পরবর্তী = *ue_curr;
			*ue_curr = ue;
		}
	}

#যদি 0
	যদি (1) {
		printf ("ORIGINAL:\n");
		জন্য (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		যখন (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			জন্য (ue2 = ue->alias; ue2; ue2 = ue2->পরবর্তী)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->পরবর্তী;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	জন্য (ue = byr_val; ue; ue = ue->পরবর্তী) {
		usg_elem *ap;
		পূর্ণসংখ্যা     len;

		len = PRINTLEN(s, ue->idx);

		জন্য (ap = ue->alias; ap; ap = ap->পরবর্তী) {
			len += PRINTLEN(s, ap->idx) + (পূর্ণসংখ্যা) strlen(", ");
		}

		যদি (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (পূর্ণসংখ্যা) strlen (DESC (s, ue->idx));
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
	যখন (print_run++ < 2) {
		জন্য (ue = byr_val; ue; ue = ue->পরবর্তী) {
			usg_elem *ap;
			পূর্ণসংখ্যা     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			জন্য (ap = ue->alias; ap; ap = ap->পরবর্তী) {
				যদি (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					বিরতি;
				}
			}
			যদি ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				চালু;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) করো{\
                  যদি(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }যখন(0)

			যদি (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			জন্য (ap = ue->alias; ap; ap = ap->পরবর্তী) {
				যদি (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			যদি (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			জন্য (ap = ue->alias; ap; ap = ap->পরবর্তী) {
				যদি (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			যদি (1) {
				ধ্রুবক অক্ষর *pstart;

				pstart = DESC (s, ue->idx);
				যখন (1) {
					পূর্ণসংখ্যা     n = 0;
					ধ্রুবক অক্ষর *lastws = ফাঁকা, *p;

					p = pstart;

					যখন (*p && n < desc_col_width
					       && *p != '\n') {
						যদি (isspace ((unsigned অক্ষর)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					যদি (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						বিরতি;
					}
					অন্যথা যদি (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						চালু;
					}
					অন্যথা {	/* we hit the edge of the screen. wrap at space if possible. */
						যদি (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (পূর্ণসংখ্যা)(lastws - pstart),
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
						চালু;
					}
				}
			}
		}
	}			/* end while */
	মুক্ত (store);
	ফেরত 0;
}
#endif /* no scanopt_usage */


স্থির শূন্য scanopt_err(কাঠামো _scanopt_t *s, পূর্ণসংখ্যা is_short, পূর্ণসংখ্যা err)
{
	ধ্রুবক অক্ষর *optname = "";
	অক্ষর    optchar[2];

	যদি (!s->no_err_বার্তা) {

		যদি (s->সূচক > 0 && s->সূচক < s->argc) {
			যদি (is_short) {
				optchar[0] =
					s->argv[s->সূচক][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			অন্যথা {
				optname = s->argv[s->সূচক];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		নির্বাচন (err) {
		ক্ষেত্র SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			বিরতি;
		ক্ষেত্র SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			বিরতি;
		ক্ষেত্র SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			বিরতি;
		ক্ষেত্র SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			বিরতি;
		পূর্বনির্ধারিত:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			বিরতি;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
স্থির পূর্ণসংখ্যা matchlongopt (অক্ষর *str, অক্ষর **optname, পূর্ণসংখ্যা *optlen, অক্ষর **arg, পূর্ণসংখ্যা *arglen)
{
	অক্ষর   *p;

	*optname = *arg = ফাঁকা;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	যদি (p[0] != '-' || p[1] != '-' || !p[2])
		ফেরত 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	যখন (*p && *p != '=')
		++p;

	*optlen = (পূর্ণসংখ্যা) (p - *optname);

	যদি (!*p)
		/* an option with no '=...' part. */
		ফেরত 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	যখন (*p)
		++p;
	*arglen = (পূর্ণসংখ্যা) (p - *arg);

	ফেরত 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
স্থির পূর্ণসংখ্যা find_opt (কাঠামো _scanopt_t *s, পূর্ণসংখ্যা lookup_long, অক্ষর *optstart, পূর্ণসংখ্যা
	len, পূর্ণসংখ্যা *err_code, পূর্ণসংখ্যা *opt_offset)
{
	পূর্ণসংখ্যা     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	যদি (!optstart)
		ফেরত 0;

	জন্য (i = 0; i < s->optc; i++) {
		ধ্রুবক অক্ষর   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		যদি (lookup_long && (s->aux[i].flags & IS_LONG)) {
			যদি (len > s->aux[i].namelen)
				চালু;

			যদি (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				যদি (len == s->aux[i].namelen) {
					nmatch = 1;
					বিরতি;
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

	ফেরত *err_code ? 0 : 1;
}


পূর্ণসংখ্যা     scanopt (scanopt_t *svoid, অক্ষর **arg, পূর্ণসংখ্যা *optindex)
{
	অক্ষর   *optname = ফাঁকা, *optarg = ফাঁকা, *pstart;
	পূর্ণসংখ্যা     namelen = 0, arglen = 0;
	পূর্ণসংখ্যা     errcode = 0, has_পরবর্তী;
	ধ্রুবক optspec_t *optp;
	কাঠামো _scanopt_t *s;
	কাঠামো _aux *auxp;
	পূর্ণসংখ্যা     is_short;
	পূর্ণসংখ্যা     opt_offset = -1;

	s = (কাঠামো _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, ফাঁকা);
	SAFE_ASSIGN (optindex, s->সূচক);

	যদি (s->সূচক >= s->argc)
		ফেরত 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->সূচক] + s->subscript;
	যদি (!pstart)
		ফেরত 0;

	যদি (s->subscript == 0) {

		/* test for exact match of "--" */
		যদি (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->সূচক + 1);
			INC_সূচক (s, 1);
			ফেরত 0;
		}

		/* Match an opt. */
		যদি (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			যদি (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				ফেরত errcode;
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
			ফেরত 0;
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
			ফেরত errcode;
		}

		optarg = pstart + 1;
		যদি (!*optarg) {
			optarg = ফাঁকা;
			arglen = 0;
		}
		অন্যথা
			arglen = (পূর্ণসংখ্যা) strlen (optarg);
	}

	/* At this point, we have a long or short option matched at opt_offset into
	 * the s->options array (and corresponding aux array).
	 * A trailing argument is in {optarg,arglen}, if any.
	 */

	/* Look ahead in argv[] to see if there is something
	 * that we can use as an argument (if needed). */
	has_পরবর্তী = s->সূচক + 1 < s->argc;

	optp = s->options + opt_offset;
	auxp = s->aux + opt_offset;

	/* case: no args allowed */
	যদি (auxp->flags & ARG_NONE) {
		যদি (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_সূচক (s, 1);
			ফেরত SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		অন্যথা যদি (!optarg)
			INC_সূচক (s, 1);
		অন্যথা
			s->subscript++;
		ফেরত optp->r_val;
	}

	/* case: required */
	যদি (auxp->flags & ARG_REQ) {
		যদি (!optarg && !has_পরবর্তী) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			ফেরত SCANOPT_ERR_ARG_NOT_FOUND;
		}

		যদি (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->সূচক + 1]);
			INC_সূচক (s, 2);
		}
		অন্যথা {
			SAFE_ASSIGN (arg, (অক্ষর *) optarg);
			INC_সূচক (s, 1);
		}
		ফেরত optp->r_val;
	}

	/* case: optional */
	যদি (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_সূচক (s, 1);
		ফেরত optp->r_val;
	}


	/* Should not reach here. */
	ফেরত 0;
}


পূর্ণসংখ্যা     scanopt_destroy (scanopt_t *svoid)
{
	কাঠামো _scanopt_t *s;

	s = (কাঠামো _scanopt_t *) svoid;
	যদি (s != ফাঁকা) {
		মুক্ত(s->aux);
		মুক্ত(s);
	}
	ফেরত 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
