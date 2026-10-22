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

#شامل "flexdef.h"
#شامل "scanopt.h"


/* Internal structures */

#تعریف_کرو ARG_NONE 0x01
#تعریف_کرو ARG_REQ  0x02
#تعریف_کرو ARG_OPT  0x04
#تعریف_کرو IS_LONG  0x08

ساخت _aux {
	صحیح     flags;		/* The above hex flags. */
	صحیح     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	صحیح     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


ساخت _scanopt_t {
	ثابت optspec_t *options;	/* List of options. */
	ساخت _aux *aux;	/* Auxiliary data about options. */
	صحیح     optc;		/* Number of options. */
	صحیح     argc;		/* Number of args. */
	حرف  **argv;		/* Array of strings. */
	صحیح     اشاریہ;		/* Used as: argv[index][subscript]. */
	صحیح     subscript;
	حرف    no_err_پیغام;	/* If true, do not print errors. */
	حرف    has_long;
	حرف    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
ساکن ثابت حرف *NAME(ساخت _scanopt_t *, صحیح);
ساکن صحیح PRINTLEN(ساخت _scanopt_t *, صحیح);
ساکن صحیح RVAL(ساخت _scanopt_t *, صحیح);
ساکن صحیح FLAGS(ساخت _scanopt_t *, صحیح);
ساکن ثابت حرف *DESC(ساخت _scanopt_t *, صحیح);
ساکن خالی scanopt_err(ساخت _scanopt_t *, صحیح, صحیح);
ساکن صحیح matchlongopt(حرف *, حرف **, صحیح *, حرف **, صحیح *);
ساکن صحیح ڈھونڈو_opt(ساخت _scanopt_t *, صحیح, حرف *, صحیح, صحیح *, صحیح *opt_انحراف);

ساکن ثابت حرف *NAME (ساخت _scanopt_t *s, صحیح i)
{
	واپس s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

ساکن صحیح PRINTLEN (ساخت _scanopt_t *s, صحیح i)
{
	واپس s->aux[i].printlen;
}

ساکن صحیح RVAL (ساخت _scanopt_t *s, صحیح i)
{
	واپس s->options[i].r_val;
}

ساکن صحیح FLAGS (ساخت _scanopt_t *s, صحیح i)
{
	واپس s->aux[i].flags;
}

ساکن ثابت حرف *DESC (ساخت _scanopt_t *s, صحیح i)
{
	واپس s->options[i].desc ? s->options[i].desc : "";
}

#اگر_غیر_تعریف_شدہ NO_SCANOPT_USAGE
ساکن صحیح get_ستون_تعداد (خالی);

ساکن صحیح get_ستون_تعداد (خالی)
{
	حرف   *env;
	صحیح     ستون_تعداد = 80;	/* default */

#اگر_تعریف_شدہ HAVE_NCURSES_H
	initscr ();
	endwin ();
	اگر (ستون_تعداد_2 > 0)
		واپس ستون_تعداد_2;
#اگر_ختم

	اگر ((env = getenv ("COLUMNS")) != تہی)
		ستون_تعداد = atoi (env);

	واپس ستون_تعداد;
}
#اگر_ختم

/* Macro to check for NULL before assigning a value. */
#تعریف_کرو محفوظ_تفویض(ptr,val) \
    کرو{                      \
        اگر((ptr)!=تہی)      \
            *(ptr) = val;    \
    }جب(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#تعریف_کرو INC_اشاریہ(s,n)     \
    کرو{                    \
       (s)->اشاریہ += (n);  \
       (s)->subscript= 0;  \
    }جب(0)

scanopt_t *scanopt_init (ثابت optspec_t *options, صحیح argc, حرف **argv, صحیح flags)
{
	صحیح     i;
	ساخت _scanopt_t *s;
	s = حافظہ_دو(حجم (ساخت _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (حرف **) argv;
	s->اشاریہ = 1;
	s->subscript = 0;
	s->no_err_پیغام = (flags & SCANOPT_NO_ERR_پیغام);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	جب (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = حافظہ_دو((size_t) s->optc * حجم (ساخت _aux));

	برائے (i = 0; i < s->optc; i++) {
		ثابت غیرعلامتی حرف *p, *pname;
		ثابت ساخت optspec_t *opt;
		ساخت _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		اگر (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ثابت غیرعلامتی حرف *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		ورنہ {
			pname = (ثابت غیرعلامتی حرف *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (صحیح) لڑی_لمبائی (opt->opt_fmt);

		aux->namelen = 0;
		برائے (p = pname + 1; *p; p++) {
			/* detect required arg */
			اگر (*p == '=' || خلا_ہے ((غیرعلامتی حرف)*p)
			    || !(aux->flags & IS_LONG)) {
				اگر (aux->namelen == 0)
					aux->namelen = (صحیح) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			اگر (*p == '[') {
				اگر (aux->namelen == 0)
					aux->namelen = (صحیح) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				توڑو;
			}
		}
		اگر (aux->namelen == 0)
			aux->namelen = (صحیح) (p - pname);
	}
	واپس (scanopt_t *) s;
}

#اگر_غیر_تعریف_شدہ NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
ساخت usg_elem {
	صحیح     idx;
	ساخت usg_elem *اگلا;
	ساخت usg_elem *alias;
};
قسمتعریف ساخت usg_elem usg_elem;


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
صحیح     scanopt_usage (scanopt_t *scanner, FILE *fp, ثابت حرف *usage)
{
	ساخت _scanopt_t *s;
	صحیح     i, columns;
	ثابت صحیح indent = 2;
	usg_elem *byr_val = تہی;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	صحیح     store_idx = 0;
	usg_elem *ue;
	صحیح     opt_ستون_چوڑائی = 0, desc_ستون_چوڑائی = 0;
	صحیح     desccol;
	صحیح     print_تسلسل = 0;

	s = (ساخت _scanopt_t *) scanner;

	اگر (usage) {
		fprintf (fp, "%s\n", usage);
	}
	ورنہ {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = حافظہ_دو((size_t) s->optc * حجم (usg_elem));
	برائے (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->اگلا = ue->alias = تہی;

		/* insert into list. */
		اگر (!byr_val)
			byr_val = ue;
		ورنہ {
			صحیح     ملا_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = تہی;

			ue_curr = &byr_val;
			جب (*ue_curr) {
				اگر (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					ملا_alias = 1;
					توڑو;
				}
				اگر (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->اگلا);
			}
			اگر (!ملا_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->اگلا = *ue_curr;
			*ue_curr = ue;
		}
	}

#اگر 0
	اگر (1) {
		لکھو ("ORIGINAL:\n");
		برائے (i = 0; i < s->optc; i++)
			لکھو ("%2d: %s\n", i, NAME (s, i));
		لکھو ("SORTED:\n");
		ue = byr_val;
		جب (ue) {
			usg_elem *ue2;

			لکھو ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			برائے (ue2 = ue->alias; ue2; ue2 = ue2->اگلا)
				لکھو ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->اگلا;
		}
	}
#اگر_ختم

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	برائے (ue = byr_val; ue; ue = ue->اگلا) {
		usg_elem *ap;
		صحیح     len;

		len = PRINTLEN(s, ue->idx);

		برائے (ap = ue->alias; ap; ap = ap->اگلا) {
			len += PRINTLEN(s, ap->idx) + (صحیح) لڑی_لمبائی(", ");
		}

		اگر (len > opt_ستون_چوڑائی)
			opt_ستون_چوڑائی = len;

		/* It's much easier to calculate length for description column! */
		len = (صحیح) لڑی_لمبائی (DESC (s, ue->idx));
		اگر (len > desc_ستون_چوڑائی)
			desc_ستون_چوڑائی = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_ستون_تعداد () - 1;
	اگر (opt_ستون_چوڑائی + desc_ستون_چوڑائی + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_ستون_چوڑائی = columns - (opt_ستون_چوڑائی + indent * 2);
		اگر (desc_ستون_چوڑائی < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_ستون_چوڑائی = زیادہ_سے_زیادہ_عدد;
	}
	desccol = opt_ستون_چوڑائی + indent * 2;

#تعریف_کرو PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	جب (print_تسلسل++ < 2) {
		برائے (ue = byr_val; ue; ue = ue->اگلا) {
			usg_elem *ap;
			صحیح     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			برائے (ap = ue->alias; ap; ap = ap->اگلا) {
				اگر (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					توڑو;
				}
			}
			اگر ((print_تسلسل == 1 && !has_short) ||
			    (print_تسلسل == 2 && has_short))
				جاری;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#تعریف_کرو PRINT_IT(i) کرو{\
                  اگر(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }جب(0)

			اگر (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			برائے (ap = ue->alias; ap; ap = ap->اگلا) {
				اگر (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			اگر (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			برائے (ap = ue->alias; ap; ap = ap->اگلا) {
				اگر (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			اگر (1) {
				ثابت حرف *pstart;

				pstart = DESC (s, ue->idx);
				جب (1) {
					صحیح     n = 0;
					ثابت حرف *lastws = تہی, *p;

					p = pstart;

					جب (*p && n < desc_ستون_چوڑائی
					       && *p != '\n') {
						اگر (خلا_ہے ((غیرعلامتی حرف)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					اگر (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						توڑو;
					}
					ورنہ اگر (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						جاری;
					}
					ورنہ {	/* we hit the edge of the screen. wrap at space if possible. */
						اگر (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (صحیح)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						ورنہ {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						جاری;
					}
				}
			}
		}
	}			/* end while */
	آزاد (store);
	واپس 0;
}
#اگر_ختم /* no scanopt_usage */


ساکن خالی scanopt_err(ساخت _scanopt_t *s, صحیح is_short, صحیح err)
{
	ثابت حرف *optname = "";
	حرف    optchar[2];

	اگر (!s->no_err_پیغام) {

		اگر (s->اشاریہ > 0 && s->اشاریہ < s->argc) {
			اگر (is_short) {
				optchar[0] =
					s->argv[s->اشاریہ][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			ورنہ {
				optname = s->argv[s->اشاریہ];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		انتخاب (err) {
		حالت SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			توڑو;
		حالت SCANOPT_ERR_ARG_NOT_ملا:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			توڑو;
		حالت SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			توڑو;
		حالت SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			توڑو;
		طےشدہ:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			توڑو;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
ساکن صحیح matchlongopt (حرف *str, حرف **optname, صحیح *optlen, حرف **arg, صحیح *arglen)
{
	حرف   *p;

	*optname = *arg = تہی;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	اگر (p[0] != '-' || p[1] != '-' || !p[2])
		واپس 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	جب (*p && *p != '=')
		++p;

	*optlen = (صحیح) (p - *optname);

	اگر (!*p)
		/* an option with no '=...' part. */
		واپس 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	جب (*p)
		++p;
	*arglen = (صحیح) (p - *arg);

	واپس 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
ساکن صحیح ڈھونڈو_opt (ساخت _scanopt_t *s, صحیح lookup_long, حرف *optstart, صحیح
	len, صحیح *err_رمز, صحیح *opt_انحراف)
{
	صحیح     nmatch = 0, lastr_val = 0, i;

	*err_رمز = 0;
	*opt_انحراف = -1;

	اگر (!optstart)
		واپس 0;

	برائے (i = 0; i < s->optc; i++) {
		ثابت حرف   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		اگر (lookup_long && (s->aux[i].flags & IS_LONG)) {
			اگر (len > s->aux[i].namelen)
				جاری;

			اگر (لڑی_موازنہ (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_انحراف = i;

				/* exact match overrides all. */
				اگر (len == s->aux[i].namelen) {
					nmatch = 1;
					توڑو;
				}

				/* ambiguity is ok between aliases. */
				اگر (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		ورنہ اگر (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			اگر (optname[0] == optstart[0]) {
				nmatch++;
				*opt_انحراف = i;
			}
		}
	}

	اگر (nmatch == 0) {
		*err_رمز = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_انحراف = -1;
	}
	ورنہ اگر (nmatch > 1) {
		*err_رمز = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_انحراف = -1;
	}

	واپس *err_رمز ? 0 : 1;
}


صحیح     scanopt (scanopt_t *svoid, حرف **arg, صحیح *optindex)
{
	حرف   *optname = تہی, *optarg = تہی, *pstart;
	صحیح     namelen = 0, arglen = 0;
	صحیح     errcode = 0, has_اگلا;
	ثابت optspec_t *optp;
	ساخت _scanopt_t *s;
	ساخت _aux *auxp;
	صحیح     is_short;
	صحیح     opt_انحراف = -1;

	s = (ساخت _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	محفوظ_تفویض (arg, تہی);
	محفوظ_تفویض (optindex, s->اشاریہ);

	اگر (s->اشاریہ >= s->argc)
		واپس 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->اشاریہ] + s->subscript;
	اگر (!pstart)
		واپس 0;

	اگر (s->subscript == 0) {

		/* test for exact match of "--" */
		اگر (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			محفوظ_تفویض (optindex, s->اشاریہ + 1);
			INC_اشاریہ (s, 1);
			واپس 0;
		}

		/* Match an opt. */
		اگر (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			اگر (!ڈھونڈو_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_انحراف)) {
				scanopt_err (s, 0, errcode);
				واپس errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		ورنہ اگر (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		ورنہ {
			/* It's not an option. We're done. */
			واپس 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	اگر (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		اگر (!ڈھونڈو_opt
		    (s, 0, pstart, namelen, &errcode, &opt_انحراف)) {
			scanopt_err(s, 1, errcode);
			واپس errcode;
		}

		optarg = pstart + 1;
		اگر (!*optarg) {
			optarg = تہی;
			arglen = 0;
		}
		ورنہ
			arglen = (صحیح) لڑی_لمبائی (optarg);
	}

	/* At this point, we have a long or short option matched at opt_offset into
	 * the s->options array (and corresponding aux array).
	 * A trailing argument is in {optarg,arglen}, if any.
	 */

	/* Look ahead in argv[] to see if there is something
	 * that we can use as an argument (if needed). */
	has_اگلا = s->اشاریہ + 1 < s->argc;

	optp = s->options + opt_انحراف;
	auxp = s->aux + opt_انحراف;

	/* case: no args allowed */
	اگر (auxp->flags & ARG_NONE) {
		اگر (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_اشاریہ (s, 1);
			واپس SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		ورنہ اگر (!optarg)
			INC_اشاریہ (s, 1);
		ورنہ
			s->subscript++;
		واپس optp->r_val;
	}

	/* case: required */
	اگر (auxp->flags & ARG_REQ) {
		اگر (!optarg && !has_اگلا) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ملا);
			واپس SCANOPT_ERR_ARG_NOT_ملا;
		}

		اگر (!optarg) {
			/* Let the next argv element become the argument. */
			محفوظ_تفویض (arg, s->argv[s->اشاریہ + 1]);
			INC_اشاریہ (s, 2);
		}
		ورنہ {
			محفوظ_تفویض (arg, (حرف *) optarg);
			INC_اشاریہ (s, 1);
		}
		واپس optp->r_val;
	}

	/* case: optional */
	اگر (auxp->flags & ARG_OPT) {
		محفوظ_تفویض (arg, optarg);
		INC_اشاریہ (s, 1);
		واپس optp->r_val;
	}


	/* Should not reach here. */
	واپس 0;
}


صحیح     scanopt_destroy (scanopt_t *svoid)
{
	ساخت _scanopt_t *s;

	s = (ساخت _scanopt_t *) svoid;
	اگر (s != تہی) {
		آزاد(s->aux);
		آزاد(s);
	}
	واپس 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
