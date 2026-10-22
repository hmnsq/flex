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

#define ARG_NONE 0x01
#define ARG_REQ  0x02
#define ARG_OPT  0x04
#define IS_LONG  0x08

ساختار _aux {
	صحیح     flags;		/* The above hex flags. */
	صحیح     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	صحیح     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


ساختار _scanopt_t {
	ثابت optspec_t *options;	/* List of options. */
	ساختار _aux *aux;	/* Auxiliary data about options. */
	صحیح     optc;		/* Number of options. */
	صحیح     argc;		/* Number of args. */
	نویسه  **argv;		/* Array of strings. */
	صحیح     index;		/* Used as: argv[index][subscript]. */
	صحیح     subscript;
	نویسه    no_err_پیام;	/* If true, do not print errors. */
	نویسه    has_long;
	نویسه    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
ایستا ثابت نویسه *NAME(ساختار _scanopt_t *, صحیح);
ایستا صحیح PRINTLEN(ساختار _scanopt_t *, صحیح);
ایستا صحیح RVAL(ساختار _scanopt_t *, صحیح);
ایستا صحیح FLAGS(ساختار _scanopt_t *, صحیح);
ایستا ثابت نویسه *DESC(ساختار _scanopt_t *, صحیح);
ایستا تهی scanopt_err(ساختار _scanopt_t *, صحیح, صحیح);
ایستا صحیح matchlongopt(نویسه *, نویسه **, صحیح *, نویسه **, صحیح *);
ایستا صحیح find_opt(ساختار _scanopt_t *, صحیح, نویسه *, صحیح, صحیح *, صحیح *opt_offset);

ایستا ثابت نویسه *NAME (ساختار _scanopt_t *s, صحیح i)
{
	بازگشت s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

ایستا صحیح PRINTLEN (ساختار _scanopt_t *s, صحیح i)
{
	بازگشت s->aux[i].printlen;
}

ایستا صحیح RVAL (ساختار _scanopt_t *s, صحیح i)
{
	بازگشت s->options[i].r_val;
}

ایستا صحیح FLAGS (ساختار _scanopt_t *s, صحیح i)
{
	بازگشت s->aux[i].flags;
}

ایستا ثابت نویسه *DESC (ساختار _scanopt_t *s, صحیح i)
{
	بازگشت s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
ایستا صحیح get_cols (تهی);

ایستا صحیح get_cols (تهی)
{
	نویسه   *env;
	صحیح     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	اگر (COLS > 0)
		بازگشت COLS;
#endif

	اگر ((env = getenv ("COLUMNS")) != پوچ)
		cols = atoi (env);

	بازگشت cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    انجامبده{                      \
        اگر((ptr)!=پوچ)      \
            *(ptr) = val;    \
    }وقتی(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    انجامبده{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }وقتی(0)

scanopt_t *scanopt_init (ثابت optspec_t *options, صحیح argc, نویسه **argv, صحیح flags)
{
	صحیح     i;
	ساختار _scanopt_t *s;
	s = malloc(اندازه (ساختار _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (نویسه **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_پیام = (flags & SCANOPT_NO_ERR_پیام);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	وقتی (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * اندازه (ساختار _aux));

	برای (i = 0; i < s->optc; i++) {
		ثابت unsigned نویسه *p, *pname;
		ثابت ساختار optspec_t *opt;
		ساختار _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		اگر (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (ثابت unsigned نویسه *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		وگرنه {
			pname = (ثابت unsigned نویسه *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (صحیح) strlen (opt->opt_fmt);

		aux->namelen = 0;
		برای (p = pname + 1; *p; p++) {
			/* detect required arg */
			اگر (*p == '=' || isspace ((unsigned نویسه)*p)
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
				بشکن;
			}
		}
		اگر (aux->namelen == 0)
			aux->namelen = (صحیح) (p - pname);
	}
	بازگشت (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
ساختار usg_elem {
	صحیح     idx;
	ساختار usg_elem *next;
	ساختار usg_elem *alias;
};
تعریفنوع ساختار usg_elem usg_elem;


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
صحیح     scanopt_usage (scanopt_t *scanner, FILE *fp, ثابت نویسه *usage)
{
	ساختار _scanopt_t *s;
	صحیح     i, columns;
	ثابت صحیح indent = 2;
	usg_elem *byr_val = پوچ;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	صحیح     store_idx = 0;
	usg_elem *ue;
	صحیح     opt_col_width = 0, desc_col_width = 0;
	صحیح     desccol;
	صحیح     print_run = 0;

	s = (ساختار _scanopt_t *) scanner;

	اگر (usage) {
		fprintf (fp, "%s\n", usage);
	}
	وگرنه {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * اندازه (usg_elem));
	برای (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = پوچ;

		/* insert into list. */
		اگر (!byr_val)
			byr_val = ue;
		وگرنه {
			صحیح     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = پوچ;

			ue_curr = &byr_val;
			وقتی (*ue_curr) {
				اگر (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					بشکن;
				}
				اگر (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			اگر (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#اگر 0
	اگر (1) {
		printf ("ORIGINAL:\n");
		برای (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		وقتی (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			برای (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	برای (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		صحیح     len;

		len = PRINTLEN(s, ue->idx);

		برای (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (صحیح) strlen(", ");
		}

		اگر (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (صحیح) strlen (DESC (s, ue->idx));
		اگر (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	اگر (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		اگر (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	وقتی (print_run++ < 2) {
		برای (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			صحیح     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			برای (ap = ue->alias; ap; ap = ap->next) {
				اگر (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					بشکن;
				}
			}
			اگر ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				ادامه;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) انجامبده{\
                  اگر(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }وقتی(0)

			اگر (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			برای (ap = ue->alias; ap; ap = ap->next) {
				اگر (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			اگر (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			برای (ap = ue->alias; ap; ap = ap->next) {
				اگر (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			اگر (1) {
				ثابت نویسه *pstart;

				pstart = DESC (s, ue->idx);
				وقتی (1) {
					صحیح     n = 0;
					ثابت نویسه *lastws = پوچ, *p;

					p = pstart;

					وقتی (*p && n < desc_col_width
					       && *p != '\n') {
						اگر (isspace ((unsigned نویسه)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					اگر (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						بشکن;
					}
					وگرنه اگر (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						ادامه;
					}
					وگرنه {	/* we hit the edge of the screen. wrap at space if possible. */
						اگر (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (صحیح)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						وگرنه {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						ادامه;
					}
				}
			}
		}
	}			/* end while */
	آزاد (store);
	بازگشت 0;
}
#endif /* no scanopt_usage */


ایستا تهی scanopt_err(ساختار _scanopt_t *s, صحیح is_short, صحیح err)
{
	ثابت نویسه *optname = "";
	نویسه    optchar[2];

	اگر (!s->no_err_پیام) {

		اگر (s->index > 0 && s->index < s->argc) {
			اگر (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			وگرنه {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		انتخاب (err) {
		حالت SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			بشکن;
		حالت SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			بشکن;
		حالت SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			بشکن;
		حالت SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			بشکن;
		پیشفرض:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			بشکن;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
ایستا صحیح matchlongopt (نویسه *str, نویسه **optname, صحیح *optlen, نویسه **arg, صحیح *arglen)
{
	نویسه   *p;

	*optname = *arg = پوچ;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	اگر (p[0] != '-' || p[1] != '-' || !p[2])
		بازگشت 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	وقتی (*p && *p != '=')
		++p;

	*optlen = (صحیح) (p - *optname);

	اگر (!*p)
		/* an option with no '=...' part. */
		بازگشت 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	وقتی (*p)
		++p;
	*arglen = (صحیح) (p - *arg);

	بازگشت 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
ایستا صحیح find_opt (ساختار _scanopt_t *s, صحیح lookup_long, نویسه *optstart, صحیح
	len, صحیح *err_code, صحیح *opt_offset)
{
	صحیح     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	اگر (!optstart)
		بازگشت 0;

	برای (i = 0; i < s->optc; i++) {
		ثابت نویسه   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		اگر (lookup_long && (s->aux[i].flags & IS_LONG)) {
			اگر (len > s->aux[i].namelen)
				ادامه;

			اگر (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				اگر (len == s->aux[i].namelen) {
					nmatch = 1;
					بشکن;
				}

				/* ambiguity is ok between aliases. */
				اگر (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		وگرنه اگر (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			اگر (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	اگر (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	وگرنه اگر (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	بازگشت *err_code ? 0 : 1;
}


صحیح     scanopt (scanopt_t *svoid, نویسه **arg, صحیح *optindex)
{
	نویسه   *optname = پوچ, *optarg = پوچ, *pstart;
	صحیح     namelen = 0, arglen = 0;
	صحیح     errcode = 0, has_next;
	ثابت optspec_t *optp;
	ساختار _scanopt_t *s;
	ساختار _aux *auxp;
	صحیح     is_short;
	صحیح     opt_offset = -1;

	s = (ساختار _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, پوچ);
	SAFE_ASSIGN (optindex, s->index);

	اگر (s->index >= s->argc)
		بازگشت 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	اگر (!pstart)
		بازگشت 0;

	اگر (s->subscript == 0) {

		/* test for exact match of "--" */
		اگر (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			بازگشت 0;
		}

		/* Match an opt. */
		اگر (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			اگر (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				بازگشت errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		وگرنه اگر (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		وگرنه {
			/* It's not an option. We're done. */
			بازگشت 0;
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

		اگر (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			بازگشت errcode;
		}

		optarg = pstart + 1;
		اگر (!*optarg) {
			optarg = پوچ;
			arglen = 0;
		}
		وگرنه
			arglen = (صحیح) strlen (optarg);
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
	اگر (auxp->flags & ARG_NONE) {
		اگر (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			بازگشت SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		وگرنه اگر (!optarg)
			INC_INDEX (s, 1);
		وگرنه
			s->subscript++;
		بازگشت optp->r_val;
	}

	/* case: required */
	اگر (auxp->flags & ARG_REQ) {
		اگر (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			بازگشت SCANOPT_ERR_ARG_NOT_FOUND;
		}

		اگر (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		وگرنه {
			SAFE_ASSIGN (arg, (نویسه *) optarg);
			INC_INDEX (s, 1);
		}
		بازگشت optp->r_val;
	}

	/* case: optional */
	اگر (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		بازگشت optp->r_val;
	}


	/* Should not reach here. */
	بازگشت 0;
}


صحیح     scanopt_destroy (scanopt_t *svoid)
{
	ساختار _scanopt_t *s;

	s = (ساختار _scanopt_t *) svoid;
	اگر (s != پوچ) {
		آزاد(s->aux);
		آزاد(s);
	}
	بازگشت 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
