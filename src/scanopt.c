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

#అన్తర్భావ "flexdef.h"
#అన్తర్భావ "scanopt.h"


/* Internal structures */

#నిర్వచించు ARG_NONE 0x01
#నిర్వచించు ARG_REQ  0x02
#నిర్వచించు ARG_OPT  0x04
#నిర్వచించు IS_LONG  0x08

నిర్మాణం _aux {
	పూర్ణాంకం     flags;		/* The above hex flags. */
	పూర్ణాంకం     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	పూర్ణాంకం     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


నిర్మాణం _scanopt_t {
	స్థిరరాశి optspec_t *options;	/* List of options. */
	నిర్మాణం _aux *aux;	/* Auxiliary data about options. */
	పూర్ణాంకం     optc;		/* Number of options. */
	పూర్ణాంకం     argc;		/* Number of args. */
	అక్షరం  **argv;		/* Array of strings. */
	పూర్ణాంకం     సూచీ;		/* Used as: argv[index][subscript]. */
	పూర్ణాంకం     subscript;
	అక్షరం    no_err_సందేశం;	/* If true, do not print errors. */
	అక్షరం    has_long;
	అక్షరం    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
స్థిర స్థిరరాశి అక్షరం *NAME(నిర్మాణం _scanopt_t *, పూర్ణాంకం);
స్థిర పూర్ణాంకం PRINTLEN(నిర్మాణం _scanopt_t *, పూర్ణాంకం);
స్థిర పూర్ణాంకం RVAL(నిర్మాణం _scanopt_t *, పూర్ణాంకం);
స్థిర పూర్ణాంకం FLAGS(నిర్మాణం _scanopt_t *, పూర్ణాంకం);
స్థిర స్థిరరాశి అక్షరం *DESC(నిర్మాణం _scanopt_t *, పూర్ణాంకం);
స్థిర శూన్య scanopt_err(నిర్మాణం _scanopt_t *, పూర్ణాంకం, పూర్ణాంకం);
స్థిర పూర్ణాంకం matchlongopt(అక్షరం *, అక్షరం **, పూర్ణాంకం *, అక్షరం **, పూర్ణాంకం *);
స్థిర పూర్ణాంకం కనుగొను_opt(నిర్మాణం _scanopt_t *, పూర్ణాంకం, అక్షరం *, పూర్ణాంకం, పూర్ణాంకం *, పూర్ణాంకం *opt_స్థానభ్రంశం);

స్థిర స్థిరరాశి అక్షరం *NAME (నిర్మాణం _scanopt_t *s, పూర్ణాంకం i)
{
	తిరిగి s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

స్థిర పూర్ణాంకం PRINTLEN (నిర్మాణం _scanopt_t *s, పూర్ణాంకం i)
{
	తిరిగి s->aux[i].printlen;
}

స్థిర పూర్ణాంకం RVAL (నిర్మాణం _scanopt_t *s, పూర్ణాంకం i)
{
	తిరిగి s->options[i].r_val;
}

స్థిర పూర్ణాంకం FLAGS (నిర్మాణం _scanopt_t *s, పూర్ణాంకం i)
{
	తిరిగి s->aux[i].flags;
}

స్థిర స్థిరరాశి అక్షరం *DESC (నిర్మాణం _scanopt_t *s, పూర్ణాంకం i)
{
	తిరిగి s->options[i].desc ? s->options[i].desc : "";
}

#నిర్వచితం_కాకపోతే NO_SCANOPT_USAGE
స్థిర పూర్ణాంకం get_నిలువుల_సంఖ్య (శూన్య);

స్థిర పూర్ణాంకం get_నిలువుల_సంఖ్య (శూన్య)
{
	అక్షరం   *env;
	పూర్ణాంకం     నిలువుల_సంఖ్య = 80;	/* default */

#నిర్వచితమైతే HAVE_NCURSES_H
	initscr ();
	endwin ();
	ఒకవేళ (నిలువుల_సంఖ్య_2 > 0)
		తిరిగి నిలువుల_సంఖ్య_2;
#అయితే_ముగింపు

	ఒకవేళ ((env = getenv ("COLUMNS")) != ఖాళీ)
		నిలువుల_సంఖ్య = atoi (env);

	తిరిగి నిలువుల_సంఖ్య;
}
#అయితే_ముగింపు

/* Macro to check for NULL before assigning a value. */
#నిర్వచించు సురక్షిత_కేటాయించు(ptr,val) \
    చేయి{                      \
        ఒకవేళ((ptr)!=ఖాళీ)      \
            *(ptr) = val;    \
    }అయితే(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#నిర్వచించు INC_సూచీ(s,n)     \
    చేయి{                    \
       (s)->సూచీ += (n);  \
       (s)->subscript= 0;  \
    }అయితే(0)

scanopt_t *scanopt_init (స్థిరరాశి optspec_t *options, పూర్ణాంకం argc, అక్షరం **argv, పూర్ణాంకం flags)
{
	పూర్ణాంకం     i;
	నిర్మాణం _scanopt_t *s;
	s = జ్ఞాపకం_ఇవ్వు(పరిమాణం (నిర్మాణం _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (అక్షరం **) argv;
	s->సూచీ = 1;
	s->subscript = 0;
	s->no_err_సందేశం = (flags & SCANOPT_NO_ERR_సందేశం);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	అయితే (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = జ్ఞాపకం_ఇవ్వు((size_t) s->optc * పరిమాణం (నిర్మాణం _aux));

	కొరకు (i = 0; i < s->optc; i++) {
		స్థిరరాశి గుర్తులేని అక్షరం *p, *pname;
		స్థిరరాశి నిర్మాణం optspec_t *opt;
		నిర్మాణం _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		ఒకవేళ (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (స్థిరరాశి గుర్తులేని అక్షరం *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		లేకపోతే {
			pname = (స్థిరరాశి గుర్తులేని అక్షరం *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (పూర్ణాంకం) అక్షరశ్రేణి_పొడవు (opt->opt_fmt);

		aux->namelen = 0;
		కొరకు (p = pname + 1; *p; p++) {
			/* detect required arg */
			ఒకవేళ (*p == '=' || ఖాళీనా ((గుర్తులేని అక్షరం)*p)
			    || !(aux->flags & IS_LONG)) {
				ఒకవేళ (aux->namelen == 0)
					aux->namelen = (పూర్ణాంకం) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			ఒకవేళ (*p == '[') {
				ఒకవేళ (aux->namelen == 0)
					aux->namelen = (పూర్ణాంకం) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				ఆపు;
			}
		}
		ఒకవేళ (aux->namelen == 0)
			aux->namelen = (పూర్ణాంకం) (p - pname);
	}
	తిరిగి (scanopt_t *) s;
}

#నిర్వచితం_కాకపోతే NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
నిర్మాణం usg_elem {
	పూర్ణాంకం     idx;
	నిర్మాణం usg_elem *తదుపరి;
	నిర్మాణం usg_elem *alias;
};
రకనిర్వచనం నిర్మాణం usg_elem usg_elem;


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
పూర్ణాంకం     scanopt_usage (scanopt_t *scanner, FILE *fp, స్థిరరాశి అక్షరం *usage)
{
	నిర్మాణం _scanopt_t *s;
	పూర్ణాంకం     i, columns;
	స్థిరరాశి పూర్ణాంకం indent = 2;
	usg_elem *byr_val = ఖాళీ;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	పూర్ణాంకం     store_idx = 0;
	usg_elem *ue;
	పూర్ణాంకం     opt_నిలువు_వెడల్పు = 0, desc_నిలువు_వెడల్పు = 0;
	పూర్ణాంకం     desccol;
	పూర్ణాంకం     print_నిరంతరం = 0;

	s = (నిర్మాణం _scanopt_t *) scanner;

	ఒకవేళ (usage) {
		fprintf (fp, "%s\n", usage);
	}
	లేకపోతే {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = జ్ఞాపకం_ఇవ్వు((size_t) s->optc * పరిమాణం (usg_elem));
	కొరకు (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->తదుపరి = ue->alias = ఖాళీ;

		/* insert into list. */
		ఒకవేళ (!byr_val)
			byr_val = ue;
		లేకపోతే {
			పూర్ణాంకం     దొరికింది_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = ఖాళీ;

			ue_curr = &byr_val;
			అయితే (*ue_curr) {
				ఒకవేళ (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					దొరికింది_alias = 1;
					ఆపు;
				}
				ఒకవేళ (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->తదుపరి);
			}
			ఒకవేళ (!దొరికింది_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->తదుపరి = *ue_curr;
			*ue_curr = ue;
		}
	}

#ఒకవేళ 0
	ఒకవేళ (1) {
		రాయి ("ORIGINAL:\n");
		కొరకు (i = 0; i < s->optc; i++)
			రాయి ("%2d: %s\n", i, NAME (s, i));
		రాయి ("SORTED:\n");
		ue = byr_val;
		అయితే (ue) {
			usg_elem *ue2;

			రాయి ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			కొరకు (ue2 = ue->alias; ue2; ue2 = ue2->తదుపరి)
				రాయి ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->తదుపరి;
		}
	}
#అయితే_ముగింపు

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	కొరకు (ue = byr_val; ue; ue = ue->తదుపరి) {
		usg_elem *ap;
		పూర్ణాంకం     len;

		len = PRINTLEN(s, ue->idx);

		కొరకు (ap = ue->alias; ap; ap = ap->తదుపరి) {
			len += PRINTLEN(s, ap->idx) + (పూర్ణాంకం) అక్షరశ్రేణి_పొడవు(", ");
		}

		ఒకవేళ (len > opt_నిలువు_వెడల్పు)
			opt_నిలువు_వెడల్పు = len;

		/* It's much easier to calculate length for description column! */
		len = (పూర్ణాంకం) అక్షరశ్రేణి_పొడవు (DESC (s, ue->idx));
		ఒకవేళ (len > desc_నిలువు_వెడల్పు)
			desc_నిలువు_వెడల్పు = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_నిలువుల_సంఖ్య () - 1;
	ఒకవేళ (opt_నిలువు_వెడల్పు + desc_నిలువు_వెడల్పు + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_నిలువు_వెడల్పు = columns - (opt_నిలువు_వెడల్పు + indent * 2);
		ఒకవేళ (desc_నిలువు_వెడల్పు < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_నిలువు_వెడల్పు = గరిష్ఠ_పూర్ణాంకం;
	}
	desccol = opt_నిలువు_వెడల్పు + indent * 2;

#నిర్వచించు PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	అయితే (print_నిరంతరం++ < 2) {
		కొరకు (ue = byr_val; ue; ue = ue->తదుపరి) {
			usg_elem *ap;
			పూర్ణాంకం     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			కొరకు (ap = ue->alias; ap; ap = ap->తదుపరి) {
				ఒకవేళ (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					ఆపు;
				}
			}
			ఒకవేళ ((print_నిరంతరం == 1 && !has_short) ||
			    (print_నిరంతరం == 2 && has_short))
				కొనసాగు;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#నిర్వచించు PRINT_IT(i) చేయి{\
                  ఒకవేళ(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }అయితే(0)

			ఒకవేళ (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			కొరకు (ap = ue->alias; ap; ap = ap->తదుపరి) {
				ఒకవేళ (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			ఒకవేళ (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			కొరకు (ap = ue->alias; ap; ap = ap->తదుపరి) {
				ఒకవేళ (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			ఒకవేళ (1) {
				స్థిరరాశి అక్షరం *pstart;

				pstart = DESC (s, ue->idx);
				అయితే (1) {
					పూర్ణాంకం     n = 0;
					స్థిరరాశి అక్షరం *lastws = ఖాళీ, *p;

					p = pstart;

					అయితే (*p && n < desc_నిలువు_వెడల్పు
					       && *p != '\n') {
						ఒకవేళ (ఖాళీనా ((గుర్తులేని అక్షరం)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					ఒకవేళ (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						ఆపు;
					}
					లేకపోతే ఒకవేళ (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						కొనసాగు;
					}
					లేకపోతే {	/* we hit the edge of the screen. wrap at space if possible. */
						ఒకవేళ (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (పూర్ణాంకం)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						లేకపోతే {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						కొనసాగు;
					}
				}
			}
		}
	}			/* end while */
	విడుదల (store);
	తిరిగి 0;
}
#అయితే_ముగింపు /* no scanopt_usage */


స్థిర శూన్య scanopt_err(నిర్మాణం _scanopt_t *s, పూర్ణాంకం is_short, పూర్ణాంకం err)
{
	స్థిరరాశి అక్షరం *optname = "";
	అక్షరం    optchar[2];

	ఒకవేళ (!s->no_err_సందేశం) {

		ఒకవేళ (s->సూచీ > 0 && s->సూచీ < s->argc) {
			ఒకవేళ (is_short) {
				optchar[0] =
					s->argv[s->సూచీ][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			లేకపోతే {
				optname = s->argv[s->సూచీ];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		ఎంపిక (err) {
		స్థితి SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			ఆపు;
		స్థితి SCANOPT_ERR_ARG_NOT_దొరికింది:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			ఆపు;
		స్థితి SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			ఆపు;
		స్థితి SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			ఆపు;
		అప్రమేయ:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			ఆపు;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
స్థిర పూర్ణాంకం matchlongopt (అక్షరం *str, అక్షరం **optname, పూర్ణాంకం *optlen, అక్షరం **arg, పూర్ణాంకం *arglen)
{
	అక్షరం   *p;

	*optname = *arg = ఖాళీ;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	ఒకవేళ (p[0] != '-' || p[1] != '-' || !p[2])
		తిరిగి 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	అయితే (*p && *p != '=')
		++p;

	*optlen = (పూర్ణాంకం) (p - *optname);

	ఒకవేళ (!*p)
		/* an option with no '=...' part. */
		తిరిగి 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	అయితే (*p)
		++p;
	*arglen = (పూర్ణాంకం) (p - *arg);

	తిరిగి 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
స్థిర పూర్ణాంకం కనుగొను_opt (నిర్మాణం _scanopt_t *s, పూర్ణాంకం lookup_long, అక్షరం *optstart, పూర్ణాంకం
	len, పూర్ణాంకం *err_సంకేతం, పూర్ణాంకం *opt_స్థానభ్రంశం)
{
	పూర్ణాంకం     nmatch = 0, lastr_val = 0, i;

	*err_సంకేతం = 0;
	*opt_స్థానభ్రంశం = -1;

	ఒకవేళ (!optstart)
		తిరిగి 0;

	కొరకు (i = 0; i < s->optc; i++) {
		స్థిరరాశి అక్షరం   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		ఒకవేళ (lookup_long && (s->aux[i].flags & IS_LONG)) {
			ఒకవేళ (len > s->aux[i].namelen)
				కొనసాగు;

			ఒకవేళ (అక్షరశ్రేణి_పోలిక (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_స్థానభ్రంశం = i;

				/* exact match overrides all. */
				ఒకవేళ (len == s->aux[i].namelen) {
					nmatch = 1;
					ఆపు;
				}

				/* ambiguity is ok between aliases. */
				ఒకవేళ (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		లేకపోతే ఒకవేళ (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			ఒకవేళ (optname[0] == optstart[0]) {
				nmatch++;
				*opt_స్థానభ్రంశం = i;
			}
		}
	}

	ఒకవేళ (nmatch == 0) {
		*err_సంకేతం = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_స్థానభ్రంశం = -1;
	}
	లేకపోతే ఒకవేళ (nmatch > 1) {
		*err_సంకేతం = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_స్థానభ్రంశం = -1;
	}

	తిరిగి *err_సంకేతం ? 0 : 1;
}


పూర్ణాంకం     scanopt (scanopt_t *svoid, అక్షరం **arg, పూర్ణాంకం *optindex)
{
	అక్షరం   *optname = ఖాళీ, *optarg = ఖాళీ, *pstart;
	పూర్ణాంకం     namelen = 0, arglen = 0;
	పూర్ణాంకం     errcode = 0, has_తదుపరి;
	స్థిరరాశి optspec_t *optp;
	నిర్మాణం _scanopt_t *s;
	నిర్మాణం _aux *auxp;
	పూర్ణాంకం     is_short;
	పూర్ణాంకం     opt_స్థానభ్రంశం = -1;

	s = (నిర్మాణం _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	సురక్షిత_కేటాయించు (arg, ఖాళీ);
	సురక్షిత_కేటాయించు (optindex, s->సూచీ);

	ఒకవేళ (s->సూచీ >= s->argc)
		తిరిగి 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->సూచీ] + s->subscript;
	ఒకవేళ (!pstart)
		తిరిగి 0;

	ఒకవేళ (s->subscript == 0) {

		/* test for exact match of "--" */
		ఒకవేళ (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			సురక్షిత_కేటాయించు (optindex, s->సూచీ + 1);
			INC_సూచీ (s, 1);
			తిరిగి 0;
		}

		/* Match an opt. */
		ఒకవేళ (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			ఒకవేళ (!కనుగొను_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_స్థానభ్రంశం)) {
				scanopt_err (s, 0, errcode);
				తిరిగి errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		లేకపోతే ఒకవేళ (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		లేకపోతే {
			/* It's not an option. We're done. */
			తిరిగి 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	ఒకవేళ (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		ఒకవేళ (!కనుగొను_opt
		    (s, 0, pstart, namelen, &errcode, &opt_స్థానభ్రంశం)) {
			scanopt_err(s, 1, errcode);
			తిరిగి errcode;
		}

		optarg = pstart + 1;
		ఒకవేళ (!*optarg) {
			optarg = ఖాళీ;
			arglen = 0;
		}
		లేకపోతే
			arglen = (పూర్ణాంకం) అక్షరశ్రేణి_పొడవు (optarg);
	}

	/* At this point, we have a long or short option matched at opt_offset into
	 * the s->options array (and corresponding aux array).
	 * A trailing argument is in {optarg,arglen}, if any.
	 */

	/* Look ahead in argv[] to see if there is something
	 * that we can use as an argument (if needed). */
	has_తదుపరి = s->సూచీ + 1 < s->argc;

	optp = s->options + opt_స్థానభ్రంశం;
	auxp = s->aux + opt_స్థానభ్రంశం;

	/* case: no args allowed */
	ఒకవేళ (auxp->flags & ARG_NONE) {
		ఒకవేళ (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_సూచీ (s, 1);
			తిరిగి SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		లేకపోతే ఒకవేళ (!optarg)
			INC_సూచీ (s, 1);
		లేకపోతే
			s->subscript++;
		తిరిగి optp->r_val;
	}

	/* case: required */
	ఒకవేళ (auxp->flags & ARG_REQ) {
		ఒకవేళ (!optarg && !has_తదుపరి) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_దొరికింది);
			తిరిగి SCANOPT_ERR_ARG_NOT_దొరికింది;
		}

		ఒకవేళ (!optarg) {
			/* Let the next argv element become the argument. */
			సురక్షిత_కేటాయించు (arg, s->argv[s->సూచీ + 1]);
			INC_సూచీ (s, 2);
		}
		లేకపోతే {
			సురక్షిత_కేటాయించు (arg, (అక్షరం *) optarg);
			INC_సూచీ (s, 1);
		}
		తిరిగి optp->r_val;
	}

	/* case: optional */
	ఒకవేళ (auxp->flags & ARG_OPT) {
		సురక్షిత_కేటాయించు (arg, optarg);
		INC_సూచీ (s, 1);
		తిరిగి optp->r_val;
	}


	/* Should not reach here. */
	తిరిగి 0;
}


పూర్ణాంకం     scanopt_destroy (scanopt_t *svoid)
{
	నిర్మాణం _scanopt_t *s;

	s = (నిర్మాణం _scanopt_t *) svoid;
	ఒకవేళ (s != ఖాళీ) {
		విడుదల(s->aux);
		విడుదల(s);
	}
	తిరిగి 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
