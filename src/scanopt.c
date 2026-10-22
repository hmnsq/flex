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

#அந்தர்பாவ "flexdef.h"
#அந்தர்பாவ "scanopt.h"


/* Internal structures */

#define ARG_NONE 0x01
#define ARG_REQ  0x02
#define ARG_OPT  0x04
#define IS_LONG  0x08

கட்டமைப்பு _aux {
	முழு     flags;		/* The above hex flags. */
	முழு     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	முழு     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


கட்டமைப்பு _scanopt_t {
	மாறிலி optspec_t *options;	/* List of options. */
	கட்டமைப்பு _aux *aux;	/* Auxiliary data about options. */
	முழு     optc;		/* Number of options. */
	முழு     argc;		/* Number of args. */
	எழுத்து  **argv;		/* Array of strings. */
	முழு     index;		/* Used as: argv[index][subscript]. */
	முழு     subscript;
	எழுத்து    no_err_செய்தி;	/* If true, do not print errors. */
	எழுத்து    has_long;
	எழுத்து    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
நிலையான மாறிலி எழுத்து *NAME(கட்டமைப்பு _scanopt_t *, முழு);
நிலையான முழு PRINTLEN(கட்டமைப்பு _scanopt_t *, முழு);
நிலையான முழு RVAL(கட்டமைப்பு _scanopt_t *, முழு);
நிலையான முழு FLAGS(கட்டமைப்பு _scanopt_t *, முழு);
நிலையான மாறிலி எழுத்து *DESC(கட்டமைப்பு _scanopt_t *, முழு);
நிலையான வெறுமை scanopt_err(கட்டமைப்பு _scanopt_t *, முழு, முழு);
நிலையான முழு matchlongopt(எழுத்து *, எழுத்து **, முழு *, எழுத்து **, முழு *);
நிலையான முழு find_opt(கட்டமைப்பு _scanopt_t *, முழு, எழுத்து *, முழு, முழு *, முழு *opt_offset);

நிலையான மாறிலி எழுத்து *NAME (கட்டமைப்பு _scanopt_t *s, முழு i)
{
	திரும்பு s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

நிலையான முழு PRINTLEN (கட்டமைப்பு _scanopt_t *s, முழு i)
{
	திரும்பு s->aux[i].printlen;
}

நிலையான முழு RVAL (கட்டமைப்பு _scanopt_t *s, முழு i)
{
	திரும்பு s->options[i].r_val;
}

நிலையான முழு FLAGS (கட்டமைப்பு _scanopt_t *s, முழு i)
{
	திரும்பு s->aux[i].flags;
}

நிலையான மாறிலி எழுத்து *DESC (கட்டமைப்பு _scanopt_t *s, முழு i)
{
	திரும்பு s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
நிலையான முழு get_cols (வெறுமை);

நிலையான முழு get_cols (வெறுமை)
{
	எழுத்து   *env;
	முழு     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	எனில் (COLS > 0)
		திரும்பு COLS;
#endif

	எனில் ((env = getenv ("COLUMNS")) != வெற்று)
		cols = atoi (env);

	திரும்பு cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    செய்{                      \
        எனில்((ptr)!=வெற்று)      \
            *(ptr) = val;    \
    }போது(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    செய்{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }போது(0)

scanopt_t *scanopt_init (மாறிலி optspec_t *options, முழு argc, எழுத்து **argv, முழு flags)
{
	முழு     i;
	கட்டமைப்பு _scanopt_t *s;
	s = malloc(அளவு (கட்டமைப்பு _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (எழுத்து **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_செய்தி = (flags & SCANOPT_NO_ERR_செய்தி);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	போது (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * அளவு (கட்டமைப்பு _aux));

	க்கு (i = 0; i < s->optc; i++) {
		மாறிலி unsigned எழுத்து *p, *pname;
		மாறிலி கட்டமைப்பு optspec_t *opt;
		கட்டமைப்பு _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		எனில் (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (மாறிலி unsigned எழுத்து *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		இல்லையெனில் {
			pname = (மாறிலி unsigned எழுத்து *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (முழு) strlen (opt->opt_fmt);

		aux->namelen = 0;
		க்கு (p = pname + 1; *p; p++) {
			/* detect required arg */
			எனில் (*p == '=' || isspace ((unsigned எழுத்து)*p)
			    || !(aux->flags & IS_LONG)) {
				எனில் (aux->namelen == 0)
					aux->namelen = (முழு) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			எனில் (*p == '[') {
				எனில் (aux->namelen == 0)
					aux->namelen = (முழு) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				நிறுத்து;
			}
		}
		எனில் (aux->namelen == 0)
			aux->namelen = (முழு) (p - pname);
	}
	திரும்பு (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
கட்டமைப்பு usg_elem {
	முழு     idx;
	கட்டமைப்பு usg_elem *next;
	கட்டமைப்பு usg_elem *alias;
};
வகைவரை கட்டமைப்பு usg_elem usg_elem;


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
முழு     scanopt_usage (scanopt_t *scanner, FILE *fp, மாறிலி எழுத்து *usage)
{
	கட்டமைப்பு _scanopt_t *s;
	முழு     i, columns;
	மாறிலி முழு indent = 2;
	usg_elem *byr_val = வெற்று;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	முழு     store_idx = 0;
	usg_elem *ue;
	முழு     opt_col_width = 0, desc_col_width = 0;
	முழு     desccol;
	முழு     print_run = 0;

	s = (கட்டமைப்பு _scanopt_t *) scanner;

	எனில் (usage) {
		fprintf (fp, "%s\n", usage);
	}
	இல்லையெனில் {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * அளவு (usg_elem));
	க்கு (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = வெற்று;

		/* insert into list. */
		எனில் (!byr_val)
			byr_val = ue;
		இல்லையெனில் {
			முழு     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = வெற்று;

			ue_curr = &byr_val;
			போது (*ue_curr) {
				எனில் (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					நிறுத்து;
				}
				எனில் (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			எனில் (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#எனில் 0
	எனில் (1) {
		printf ("ORIGINAL:\n");
		க்கு (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		போது (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			க்கு (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	க்கு (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		முழு     len;

		len = PRINTLEN(s, ue->idx);

		க்கு (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (முழு) strlen(", ");
		}

		எனில் (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (முழு) strlen (DESC (s, ue->idx));
		எனில் (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	எனில் (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		எனில் (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	போது (print_run++ < 2) {
		க்கு (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			முழு     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			க்கு (ap = ue->alias; ap; ap = ap->next) {
				எனில் (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					நிறுத்து;
				}
			}
			எனில் ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				தொடர்;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) செய்{\
                  எனில்(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }போது(0)

			எனில் (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			க்கு (ap = ue->alias; ap; ap = ap->next) {
				எனில் (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			எனில் (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			க்கு (ap = ue->alias; ap; ap = ap->next) {
				எனில் (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			எனில் (1) {
				மாறிலி எழுத்து *pstart;

				pstart = DESC (s, ue->idx);
				போது (1) {
					முழு     n = 0;
					மாறிலி எழுத்து *lastws = வெற்று, *p;

					p = pstart;

					போது (*p && n < desc_col_width
					       && *p != '\n') {
						எனில் (isspace ((unsigned எழுத்து)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					எனில் (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						நிறுத்து;
					}
					இல்லையெனில் எனில் (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						தொடர்;
					}
					இல்லையெனில் {	/* we hit the edge of the screen. wrap at space if possible. */
						எனில் (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (முழு)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						இல்லையெனில் {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						தொடர்;
					}
				}
			}
		}
	}			/* end while */
	விடுவி (store);
	திரும்பு 0;
}
#endif /* no scanopt_usage */


நிலையான வெறுமை scanopt_err(கட்டமைப்பு _scanopt_t *s, முழு is_short, முழு err)
{
	மாறிலி எழுத்து *optname = "";
	எழுத்து    optchar[2];

	எனில் (!s->no_err_செய்தி) {

		எனில் (s->index > 0 && s->index < s->argc) {
			எனில் (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			இல்லையெனில் {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		தேர்வு (err) {
		நிலை SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			நிறுத்து;
		நிலை SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			நிறுத்து;
		நிலை SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			நிறுத்து;
		நிலை SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			நிறுத்து;
		இயல்பு:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			நிறுத்து;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
நிலையான முழு matchlongopt (எழுத்து *str, எழுத்து **optname, முழு *optlen, எழுத்து **arg, முழு *arglen)
{
	எழுத்து   *p;

	*optname = *arg = வெற்று;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	எனில் (p[0] != '-' || p[1] != '-' || !p[2])
		திரும்பு 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	போது (*p && *p != '=')
		++p;

	*optlen = (முழு) (p - *optname);

	எனில் (!*p)
		/* an option with no '=...' part. */
		திரும்பு 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	போது (*p)
		++p;
	*arglen = (முழு) (p - *arg);

	திரும்பு 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
நிலையான முழு find_opt (கட்டமைப்பு _scanopt_t *s, முழு lookup_long, எழுத்து *optstart, முழு
	len, முழு *err_code, முழு *opt_offset)
{
	முழு     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	எனில் (!optstart)
		திரும்பு 0;

	க்கு (i = 0; i < s->optc; i++) {
		மாறிலி எழுத்து   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		எனில் (lookup_long && (s->aux[i].flags & IS_LONG)) {
			எனில் (len > s->aux[i].namelen)
				தொடர்;

			எனில் (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				எனில் (len == s->aux[i].namelen) {
					nmatch = 1;
					நிறுத்து;
				}

				/* ambiguity is ok between aliases. */
				எனில் (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		இல்லையெனில் எனில் (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			எனில் (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	எனில் (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	இல்லையெனில் எனில் (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	திரும்பு *err_code ? 0 : 1;
}


முழு     scanopt (scanopt_t *svoid, எழுத்து **arg, முழு *optindex)
{
	எழுத்து   *optname = வெற்று, *optarg = வெற்று, *pstart;
	முழு     namelen = 0, arglen = 0;
	முழு     errcode = 0, has_next;
	மாறிலி optspec_t *optp;
	கட்டமைப்பு _scanopt_t *s;
	கட்டமைப்பு _aux *auxp;
	முழு     is_short;
	முழு     opt_offset = -1;

	s = (கட்டமைப்பு _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, வெற்று);
	SAFE_ASSIGN (optindex, s->index);

	எனில் (s->index >= s->argc)
		திரும்பு 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	எனில் (!pstart)
		திரும்பு 0;

	எனில் (s->subscript == 0) {

		/* test for exact match of "--" */
		எனில் (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			திரும்பு 0;
		}

		/* Match an opt. */
		எனில் (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			எனில் (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				திரும்பு errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		இல்லையெனில் எனில் (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		இல்லையெனில் {
			/* It's not an option. We're done. */
			திரும்பு 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	எனில் (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		எனில் (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			திரும்பு errcode;
		}

		optarg = pstart + 1;
		எனில் (!*optarg) {
			optarg = வெற்று;
			arglen = 0;
		}
		இல்லையெனில்
			arglen = (முழு) strlen (optarg);
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
	எனில் (auxp->flags & ARG_NONE) {
		எனில் (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			திரும்பு SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		இல்லையெனில் எனில் (!optarg)
			INC_INDEX (s, 1);
		இல்லையெனில்
			s->subscript++;
		திரும்பு optp->r_val;
	}

	/* case: required */
	எனில் (auxp->flags & ARG_REQ) {
		எனில் (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			திரும்பு SCANOPT_ERR_ARG_NOT_FOUND;
		}

		எனில் (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		இல்லையெனில் {
			SAFE_ASSIGN (arg, (எழுத்து *) optarg);
			INC_INDEX (s, 1);
		}
		திரும்பு optp->r_val;
	}

	/* case: optional */
	எனில் (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		திரும்பு optp->r_val;
	}


	/* Should not reach here. */
	திரும்பு 0;
}


முழு     scanopt_destroy (scanopt_t *svoid)
{
	கட்டமைப்பு _scanopt_t *s;

	s = (கட்டமைப்பு _scanopt_t *) svoid;
	எனில் (s != வெற்று) {
		விடுவி(s->aux);
		விடுவி(s);
	}
	திரும்பு 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
