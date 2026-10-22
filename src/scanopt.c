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

#ضمن "flexdef.h"
#ضمن "scanopt.h"


/* Internal structures */

#تعریف_کړه ARG_NONE 0x01
#تعریف_کړه ARG_REQ  0x02
#تعریف_کړه ARG_OPT  0x04
#تعریف_کړه IS_LONG  0x08

بنية _aux {
	صحيح     flags;		/* The above hex flags. */
	صحيح     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	صحيح     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


بنية _scanopt_t {
	ثابت optspec_t *options;	/* List of options. */
	بنية _aux *aux;	/* Auxiliary data about options. */
	صحيح     optc;		/* Number of options. */
	صحيح     argc;		/* Number of args. */
	حرف  **argv;		/* Array of strings. */
	صحيح     شاخص;		/* Used as: argv[index][subscript]. */
	صحيح     subscript;
	حرف    no_err_پیغام;	/* If true, do not print errors. */
	حرف    has_long;
	حرف    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
ساكن ثابت حرف *NAME(بنية _scanopt_t *, صحيح);
ساكن صحيح PRINTLEN(بنية _scanopt_t *, صحيح);
ساكن صحيح RVAL(بنية _scanopt_t *, صحيح);
ساكن صحيح FLAGS(بنية _scanopt_t *, صحيح);
ساكن ثابت حرف *DESC(بنية _scanopt_t *, صحيح);
ساكن فراغ scanopt_err(بنية _scanopt_t *, صحيح, صحيح);
ساكن صحيح matchlongopt(حرف *, حرف **, صحيح *, حرف **, صحيح *);
ساكن صحيح پیدا_کړه_opt(بنية _scanopt_t *, صحيح, حرف *, صحيح, صحيح *, صحيح *opt_دننه_واټن);

ساكن ثابت حرف *NAME (بنية _scanopt_t *s, صحيح i)
{
	أرجع s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

ساكن صحيح PRINTLEN (بنية _scanopt_t *s, صحيح i)
{
	أرجع s->aux[i].printlen;
}

ساكن صحيح RVAL (بنية _scanopt_t *s, صحيح i)
{
	أرجع s->options[i].r_val;
}

ساكن صحيح FLAGS (بنية _scanopt_t *s, صحيح i)
{
	أرجع s->aux[i].flags;
}

ساكن ثابت حرف *DESC (بنية _scanopt_t *s, صحيح i)
{
	أرجع s->options[i].desc ? s->options[i].desc : "";
}

#که_نه_تعریف_شوی NO_SCANOPT_USAGE
ساكن صحيح get_ستون_شمېر (فراغ);

ساكن صحيح get_ستون_شمېر (فراغ)
{
	حرف   *env;
	صحيح     ستون_شمېر = 80;	/* default */

#که_تعریف_شوی HAVE_NCURSES_H
	initscr ();
	endwin ();
	إذا (ستون_شمېر_2 > 0)
		أرجع ستون_شمېر_2;
#د_که_پای

	إذا ((env = getenv ("COLUMNS")) != عدم)
		ستون_شمېر = atoi (env);

	أرجع ستون_شمېر;
}
#د_که_پای

/* Macro to check for NULL before assigning a value. */
#تعریف_کړه خوندي_ټاکل(ptr,val) \
    افعل{                      \
        إذا((ptr)!=عدم)      \
            *(ptr) = val;    \
    }طالما(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#تعریف_کړه INC_شاخص(s,n)     \
    افعل{                    \
       (s)->شاخص += (n);  \
       (s)->subscript= 0;  \
    }طالما(0)

scanopt_t *scanopt_init (ثابت optspec_t *options, صحيح argc, حرف **argv, صحيح flags)
{
	صحيح     i;
	بنية _scanopt_t *s;
	s = حافظه_ورکړه(حجم (بنية _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (حرف **) argv;
	s->شاخص = 1;
	s->subscript = 0;
	s->no_err_پیغام = (flags & SCANOPT_NO_ERR_پیغام);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	طالما (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = حافظه_ورکړه((size_t) s->optc * حجم (بنية _aux));

	لكل (i = 0; i < s->optc; i++) {
		ثابت بینښه حرف *p, *pname;
		ثابت بنية optspec_t *opt;
		بنية _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		إذا (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ثابت بینښه حرف *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		وإلا {
			pname = (ثابت بینښه حرف *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (صحيح) مزي_اوږدوالی (opt->opt_fmt);

		aux->namelen = 0;
		لكل (p = pname + 1; *p; p++) {
			/* detect required arg */
			إذا (*p == '=' || که_تشه ((بینښه حرف)*p)
			    || !(aux->flags & IS_LONG)) {
				إذا (aux->namelen == 0)
					aux->namelen = (صحيح) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			إذا (*p == '[') {
				إذا (aux->namelen == 0)
					aux->namelen = (صحيح) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				اكسر;
			}
		}
		إذا (aux->namelen == 0)
			aux->namelen = (صحيح) (p - pname);
	}
	أرجع (scanopt_t *) s;
}

#که_نه_تعریف_شوی NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
بنية usg_elem {
	صحيح     idx;
	بنية usg_elem *بل;
	بنية usg_elem *alias;
};
تعريفنوع بنية usg_elem usg_elem;


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
صحيح     scanopt_usage (scanopt_t *scanner, FILE *fp, ثابت حرف *usage)
{
	بنية _scanopt_t *s;
	صحيح     i, columns;
	ثابت صحيح indent = 2;
	usg_elem *byr_val = عدم;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	صحيح     store_idx = 0;
	usg_elem *ue;
	صحيح     opt_ستون_پلنوالی = 0, desc_ستون_پلنوالی = 0;
	صحيح     desccol;
	صحيح     print_پرلپسې = 0;

	s = (بنية _scanopt_t *) scanner;

	إذا (usage) {
		fprintf (fp, "%s\n", usage);
	}
	وإلا {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = حافظه_ورکړه((size_t) s->optc * حجم (usg_elem));
	لكل (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->بل = ue->alias = عدم;

		/* insert into list. */
		إذا (!byr_val)
			byr_val = ue;
		وإلا {
			صحيح     وموندل_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = عدم;

			ue_curr = &byr_val;
			طالما (*ue_curr) {
				إذا (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					وموندل_alias = 1;
					اكسر;
				}
				إذا (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->بل);
			}
			إذا (!وموندل_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->بل = *ue_curr;
			*ue_curr = ue;
		}
	}

#إذا 0
	إذا (1) {
		چاپ_کړه ("ORIGINAL:\n");
		لكل (i = 0; i < s->optc; i++)
			چاپ_کړه ("%2d: %s\n", i, NAME (s, i));
		چاپ_کړه ("SORTED:\n");
		ue = byr_val;
		طالما (ue) {
			usg_elem *ue2;

			چاپ_کړه ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			لكل (ue2 = ue->alias; ue2; ue2 = ue2->بل)
				چاپ_کړه ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->بل;
		}
	}
#د_که_پای

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	لكل (ue = byr_val; ue; ue = ue->بل) {
		usg_elem *ap;
		صحيح     len;

		len = PRINTLEN(s, ue->idx);

		لكل (ap = ue->alias; ap; ap = ap->بل) {
			len += PRINTLEN(s, ap->idx) + (صحيح) مزي_اوږدوالی(", ");
		}

		إذا (len > opt_ستون_پلنوالی)
			opt_ستون_پلنوالی = len;

		/* It's much easier to calculate length for description column! */
		len = (صحيح) مزي_اوږدوالی (DESC (s, ue->idx));
		إذا (len > desc_ستون_پلنوالی)
			desc_ستون_پلنوالی = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_ستون_شمېر () - 1;
	إذا (opt_ستون_پلنوالی + desc_ستون_پلنوالی + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_ستون_پلنوالی = columns - (opt_ستون_پلنوالی + indent * 2);
		إذا (desc_ستون_پلنوالی < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_ستون_پلنوالی = لوی_عدد;
	}
	desccol = opt_ستون_پلنوالی + indent * 2;

#تعریف_کړه PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	طالما (print_پرلپسې++ < 2) {
		لكل (ue = byr_val; ue; ue = ue->بل) {
			usg_elem *ap;
			صحيح     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			لكل (ap = ue->alias; ap; ap = ap->بل) {
				إذا (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					اكسر;
				}
			}
			إذا ((print_پرلپسې == 1 && !has_short) ||
			    (print_پرلپسې == 2 && has_short))
				استمر;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#تعریف_کړه PRINT_IT(i) افعل{\
                  إذا(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }طالما(0)

			إذا (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			لكل (ap = ue->alias; ap; ap = ap->بل) {
				إذا (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			إذا (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			لكل (ap = ue->alias; ap; ap = ap->بل) {
				إذا (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			إذا (1) {
				ثابت حرف *pstart;

				pstart = DESC (s, ue->idx);
				طالما (1) {
					صحيح     n = 0;
					ثابت حرف *lastws = عدم, *p;

					p = pstart;

					طالما (*p && n < desc_ستون_پلنوالی
					       && *p != '\n') {
						إذا (که_تشه ((بینښه حرف)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					إذا (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						اكسر;
					}
					وإلا إذا (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						استمر;
					}
					وإلا {	/* we hit the edge of the screen. wrap at space if possible. */
						إذا (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (صحيح)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						وإلا {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						استمر;
					}
				}
			}
		}
	}			/* end while */
	حرر (store);
	أرجع 0;
}
#د_که_پای /* no scanopt_usage */


ساكن فراغ scanopt_err(بنية _scanopt_t *s, صحيح is_short, صحيح err)
{
	ثابت حرف *optname = "";
	حرف    optchar[2];

	إذا (!s->no_err_پیغام) {

		إذا (s->شاخص > 0 && s->شاخص < s->argc) {
			إذا (is_short) {
				optchar[0] =
					s->argv[s->شاخص][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			وإلا {
				optname = s->argv[s->شاخص];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		بدل (err) {
		حالة SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			اكسر;
		حالة SCANOPT_ERR_ARG_NOT_وموندل:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			اكسر;
		حالة SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			اكسر;
		حالة SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			اكسر;
		افتراضي:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			اكسر;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
ساكن صحيح matchlongopt (حرف *str, حرف **optname, صحيح *optlen, حرف **arg, صحيح *arglen)
{
	حرف   *p;

	*optname = *arg = عدم;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	إذا (p[0] != '-' || p[1] != '-' || !p[2])
		أرجع 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	طالما (*p && *p != '=')
		++p;

	*optlen = (صحيح) (p - *optname);

	إذا (!*p)
		/* an option with no '=...' part. */
		أرجع 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	طالما (*p)
		++p;
	*arglen = (صحيح) (p - *arg);

	أرجع 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
ساكن صحيح پیدا_کړه_opt (بنية _scanopt_t *s, صحيح lookup_long, حرف *optstart, صحيح
	len, صحيح *err_کوډ, صحيح *opt_دننه_واټن)
{
	صحيح     nmatch = 0, lastr_val = 0, i;

	*err_کوډ = 0;
	*opt_دننه_واټن = -1;

	إذا (!optstart)
		أرجع 0;

	لكل (i = 0; i < s->optc; i++) {
		ثابت حرف   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		إذا (lookup_long && (s->aux[i].flags & IS_LONG)) {
			إذا (len > s->aux[i].namelen)
				استمر;

			إذا (مزي_پرتله (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_دننه_واټن = i;

				/* exact match overrides all. */
				إذا (len == s->aux[i].namelen) {
					nmatch = 1;
					اكسر;
				}

				/* ambiguity is ok between aliases. */
				إذا (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		وإلا إذا (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			إذا (optname[0] == optstart[0]) {
				nmatch++;
				*opt_دننه_واټن = i;
			}
		}
	}

	إذا (nmatch == 0) {
		*err_کوډ = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_دننه_واټن = -1;
	}
	وإلا إذا (nmatch > 1) {
		*err_کوډ = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_دننه_واټن = -1;
	}

	أرجع *err_کوډ ? 0 : 1;
}


صحيح     scanopt (scanopt_t *svoid, حرف **arg, صحيح *optindex)
{
	حرف   *optname = عدم, *optarg = عدم, *pstart;
	صحيح     namelen = 0, arglen = 0;
	صحيح     errcode = 0, has_بل;
	ثابت optspec_t *optp;
	بنية _scanopt_t *s;
	بنية _aux *auxp;
	صحيح     is_short;
	صحيح     opt_دننه_واټن = -1;

	s = (بنية _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	خوندي_ټاکل (arg, عدم);
	خوندي_ټاکل (optindex, s->شاخص);

	إذا (s->شاخص >= s->argc)
		أرجع 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->شاخص] + s->subscript;
	إذا (!pstart)
		أرجع 0;

	إذا (s->subscript == 0) {

		/* test for exact match of "--" */
		إذا (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			خوندي_ټاکل (optindex, s->شاخص + 1);
			INC_شاخص (s, 1);
			أرجع 0;
		}

		/* Match an opt. */
		إذا (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			إذا (!پیدا_کړه_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_دننه_واټن)) {
				scanopt_err (s, 0, errcode);
				أرجع errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		وإلا إذا (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		وإلا {
			/* It's not an option. We're done. */
			أرجع 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	إذا (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		إذا (!پیدا_کړه_opt
		    (s, 0, pstart, namelen, &errcode, &opt_دننه_واټن)) {
			scanopt_err(s, 1, errcode);
			أرجع errcode;
		}

		optarg = pstart + 1;
		إذا (!*optarg) {
			optarg = عدم;
			arglen = 0;
		}
		وإلا
			arglen = (صحيح) مزي_اوږدوالی (optarg);
	}

	/* At this point, we have a long or short option matched at opt_offset into
	 * the s->options array (and corresponding aux array).
	 * A trailing argument is in {optarg,arglen}, if any.
	 */

	/* Look ahead in argv[] to see if there is something
	 * that we can use as an argument (if needed). */
	has_بل = s->شاخص + 1 < s->argc;

	optp = s->options + opt_دننه_واټن;
	auxp = s->aux + opt_دننه_واټن;

	/* case: no args allowed */
	إذا (auxp->flags & ARG_NONE) {
		إذا (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_شاخص (s, 1);
			أرجع SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		وإلا إذا (!optarg)
			INC_شاخص (s, 1);
		وإلا
			s->subscript++;
		أرجع optp->r_val;
	}

	/* case: required */
	إذا (auxp->flags & ARG_REQ) {
		إذا (!optarg && !has_بل) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_وموندل);
			أرجع SCANOPT_ERR_ARG_NOT_وموندل;
		}

		إذا (!optarg) {
			/* Let the next argv element become the argument. */
			خوندي_ټاکل (arg, s->argv[s->شاخص + 1]);
			INC_شاخص (s, 2);
		}
		وإلا {
			خوندي_ټاکل (arg, (حرف *) optarg);
			INC_شاخص (s, 1);
		}
		أرجع optp->r_val;
	}

	/* case: optional */
	إذا (auxp->flags & ARG_OPT) {
		خوندي_ټاکل (arg, optarg);
		INC_شاخص (s, 1);
		أرجع optp->r_val;
	}


	/* Should not reach here. */
	أرجع 0;
}


صحيح     scanopt_destroy (scanopt_t *svoid)
{
	بنية _scanopt_t *s;

	s = (بنية _scanopt_t *) svoid;
	إذا (s != عدم) {
		حرر(s->aux);
		حرر(s);
	}
	أرجع 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
