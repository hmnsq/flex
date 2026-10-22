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

#અન્તર્ભાવ "flexdef.h"
#અન્તર્ભાવ "scanopt.h"


/* Internal structures */

#define ARG_NONE 0x01
#define ARG_REQ  0x02
#define ARG_OPT  0x04
#define IS_LONG  0x08

સંરચના _aux {
	પૂર્ણાંક     flags;		/* The above hex flags. */
	પૂર્ણાંક     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	પૂર્ણાંક     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


સંરચના _scanopt_t {
	અચલ optspec_t *options;	/* List of options. */
	સંરચના _aux *aux;	/* Auxiliary data about options. */
	પૂર્ણાંક     optc;		/* Number of options. */
	પૂર્ણાંક     argc;		/* Number of args. */
	અક્ષર  **argv;		/* Array of strings. */
	પૂર્ણાંક     index;		/* Used as: argv[index][subscript]. */
	પૂર્ણાંક     subscript;
	અક્ષર    no_err_સંદેશ;	/* If true, do not print errors. */
	અક્ષર    has_long;
	અક્ષર    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
સ્થિર અચલ અક્ષર *NAME(સંરચના _scanopt_t *, પૂર્ણાંક);
સ્થિર પૂર્ણાંક PRINTLEN(સંરચના _scanopt_t *, પૂર્ણાંક);
સ્થિર પૂર્ણાંક RVAL(સંરચના _scanopt_t *, પૂર્ણાંક);
સ્થિર પૂર્ણાંક FLAGS(સંરચના _scanopt_t *, પૂર્ણાંક);
સ્થિર અચલ અક્ષર *DESC(સંરચના _scanopt_t *, પૂર્ણાંક);
સ્થિર શૂન્ય scanopt_err(સંરચના _scanopt_t *, પૂર્ણાંક, પૂર્ણાંક);
સ્થિર પૂર્ણાંક matchlongopt(અક્ષર *, અક્ષર **, પૂર્ણાંક *, અક્ષર **, પૂર્ણાંક *);
સ્થિર પૂર્ણાંક find_opt(સંરચના _scanopt_t *, પૂર્ણાંક, અક્ષર *, પૂર્ણાંક, પૂર્ણાંક *, પૂર્ણાંક *opt_offset);

સ્થિર અચલ અક્ષર *NAME (સંરચના _scanopt_t *s, પૂર્ણાંક i)
{
	પાછા s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

સ્થિર પૂર્ણાંક PRINTLEN (સંરચના _scanopt_t *s, પૂર્ણાંક i)
{
	પાછા s->aux[i].printlen;
}

સ્થિર પૂર્ણાંક RVAL (સંરચના _scanopt_t *s, પૂર્ણાંક i)
{
	પાછા s->options[i].r_val;
}

સ્થિર પૂર્ણાંક FLAGS (સંરચના _scanopt_t *s, પૂર્ણાંક i)
{
	પાછા s->aux[i].flags;
}

સ્થિર અચલ અક્ષર *DESC (સંરચના _scanopt_t *s, પૂર્ણાંક i)
{
	પાછા s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
સ્થિર પૂર્ણાંક get_cols (શૂન્ય);

સ્થિર પૂર્ણાંક get_cols (શૂન્ય)
{
	અક્ષર   *env;
	પૂર્ણાંક     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	જો (COLS > 0)
		પાછા COLS;
#endif

	જો ((env = getenv ("COLUMNS")) != ખાલી)
		cols = atoi (env);

	પાછા cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    કરો{                      \
        જો((ptr)!=ખાલી)      \
            *(ptr) = val;    \
    }જ્યારે(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    કરો{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }જ્યારે(0)

scanopt_t *scanopt_init (અચલ optspec_t *options, પૂર્ણાંક argc, અક્ષર **argv, પૂર્ણાંક flags)
{
	પૂર્ણાંક     i;
	સંરચના _scanopt_t *s;
	s = malloc(કદ (સંરચના _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (અક્ષર **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_સંદેશ = (flags & SCANOPT_NO_ERR_સંદેશ);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	જ્યારે (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * કદ (સંરચના _aux));

	માટે (i = 0; i < s->optc; i++) {
		અચલ unsigned અક્ષર *p, *pname;
		અચલ સંરચના optspec_t *opt;
		સંરચના _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		જો (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (અચલ unsigned અક્ષર *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		નહીંતર {
			pname = (અચલ unsigned અક્ષર *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (પૂર્ણાંક) strlen (opt->opt_fmt);

		aux->namelen = 0;
		માટે (p = pname + 1; *p; p++) {
			/* detect required arg */
			જો (*p == '=' || isspace ((unsigned અક્ષર)*p)
			    || !(aux->flags & IS_LONG)) {
				જો (aux->namelen == 0)
					aux->namelen = (પૂર્ણાંક) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			જો (*p == '[') {
				જો (aux->namelen == 0)
					aux->namelen = (પૂર્ણાંક) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				તોડો;
			}
		}
		જો (aux->namelen == 0)
			aux->namelen = (પૂર્ણાંક) (p - pname);
	}
	પાછા (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
સંરચના usg_elem {
	પૂર્ણાંક     idx;
	સંરચના usg_elem *next;
	સંરચના usg_elem *alias;
};
પ્રકારવ્યાખ્યા સંરચના usg_elem usg_elem;


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
પૂર્ણાંક     scanopt_usage (scanopt_t *scanner, FILE *fp, અચલ અક્ષર *usage)
{
	સંરચના _scanopt_t *s;
	પૂર્ણાંક     i, columns;
	અચલ પૂર્ણાંક indent = 2;
	usg_elem *byr_val = ખાલી;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	પૂર્ણાંક     store_idx = 0;
	usg_elem *ue;
	પૂર્ણાંક     opt_col_width = 0, desc_col_width = 0;
	પૂર્ણાંક     desccol;
	પૂર્ણાંક     print_run = 0;

	s = (સંરચના _scanopt_t *) scanner;

	જો (usage) {
		fprintf (fp, "%s\n", usage);
	}
	નહીંતર {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * કદ (usg_elem));
	માટે (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = ખાલી;

		/* insert into list. */
		જો (!byr_val)
			byr_val = ue;
		નહીંતર {
			પૂર્ણાંક     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = ખાલી;

			ue_curr = &byr_val;
			જ્યારે (*ue_curr) {
				જો (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					તોડો;
				}
				જો (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			જો (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#જો 0
	જો (1) {
		printf ("ORIGINAL:\n");
		માટે (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		જ્યારે (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			માટે (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	માટે (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		પૂર્ણાંક     len;

		len = PRINTLEN(s, ue->idx);

		માટે (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (પૂર્ણાંક) strlen(", ");
		}

		જો (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (પૂર્ણાંક) strlen (DESC (s, ue->idx));
		જો (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	જો (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		જો (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	જ્યારે (print_run++ < 2) {
		માટે (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			પૂર્ણાંક     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			માટે (ap = ue->alias; ap; ap = ap->next) {
				જો (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					તોડો;
				}
			}
			જો ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				ચાલુ;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) કરો{\
                  જો(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }જ્યારે(0)

			જો (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			માટે (ap = ue->alias; ap; ap = ap->next) {
				જો (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			જો (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			માટે (ap = ue->alias; ap; ap = ap->next) {
				જો (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			જો (1) {
				અચલ અક્ષર *pstart;

				pstart = DESC (s, ue->idx);
				જ્યારે (1) {
					પૂર્ણાંક     n = 0;
					અચલ અક્ષર *lastws = ખાલી, *p;

					p = pstart;

					જ્યારે (*p && n < desc_col_width
					       && *p != '\n') {
						જો (isspace ((unsigned અક્ષર)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					જો (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						તોડો;
					}
					નહીંતર જો (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						ચાલુ;
					}
					નહીંતર {	/* we hit the edge of the screen. wrap at space if possible. */
						જો (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (પૂર્ણાંક)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						નહીંતર {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						ચાલુ;
					}
				}
			}
		}
	}			/* end while */
	મુક્ત (store);
	પાછા 0;
}
#endif /* no scanopt_usage */


સ્થિર શૂન્ય scanopt_err(સંરચના _scanopt_t *s, પૂર્ણાંક is_short, પૂર્ણાંક err)
{
	અચલ અક્ષર *optname = "";
	અક્ષર    optchar[2];

	જો (!s->no_err_સંદેશ) {

		જો (s->index > 0 && s->index < s->argc) {
			જો (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			નહીંતર {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		પસંદગી (err) {
		સ્થિતિ SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			તોડો;
		સ્થિતિ SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			તોડો;
		સ્થિતિ SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			તોડો;
		સ્થિતિ SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			તોડો;
		મૂળભૂત:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			તોડો;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
સ્થિર પૂર્ણાંક matchlongopt (અક્ષર *str, અક્ષર **optname, પૂર્ણાંક *optlen, અક્ષર **arg, પૂર્ણાંક *arglen)
{
	અક્ષર   *p;

	*optname = *arg = ખાલી;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	જો (p[0] != '-' || p[1] != '-' || !p[2])
		પાછા 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	જ્યારે (*p && *p != '=')
		++p;

	*optlen = (પૂર્ણાંક) (p - *optname);

	જો (!*p)
		/* an option with no '=...' part. */
		પાછા 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	જ્યારે (*p)
		++p;
	*arglen = (પૂર્ણાંક) (p - *arg);

	પાછા 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
સ્થિર પૂર્ણાંક find_opt (સંરચના _scanopt_t *s, પૂર્ણાંક lookup_long, અક્ષર *optstart, પૂર્ણાંક
	len, પૂર્ણાંક *err_code, પૂર્ણાંક *opt_offset)
{
	પૂર્ણાંક     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	જો (!optstart)
		પાછા 0;

	માટે (i = 0; i < s->optc; i++) {
		અચલ અક્ષર   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		જો (lookup_long && (s->aux[i].flags & IS_LONG)) {
			જો (len > s->aux[i].namelen)
				ચાલુ;

			જો (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				જો (len == s->aux[i].namelen) {
					nmatch = 1;
					તોડો;
				}

				/* ambiguity is ok between aliases. */
				જો (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		નહીંતર જો (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			જો (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	જો (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	નહીંતર જો (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	પાછા *err_code ? 0 : 1;
}


પૂર્ણાંક     scanopt (scanopt_t *svoid, અક્ષર **arg, પૂર્ણાંક *optindex)
{
	અક્ષર   *optname = ખાલી, *optarg = ખાલી, *pstart;
	પૂર્ણાંક     namelen = 0, arglen = 0;
	પૂર્ણાંક     errcode = 0, has_next;
	અચલ optspec_t *optp;
	સંરચના _scanopt_t *s;
	સંરચના _aux *auxp;
	પૂર્ણાંક     is_short;
	પૂર્ણાંક     opt_offset = -1;

	s = (સંરચના _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, ખાલી);
	SAFE_ASSIGN (optindex, s->index);

	જો (s->index >= s->argc)
		પાછા 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	જો (!pstart)
		પાછા 0;

	જો (s->subscript == 0) {

		/* test for exact match of "--" */
		જો (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			પાછા 0;
		}

		/* Match an opt. */
		જો (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			જો (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				પાછા errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		નહીંતર જો (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		નહીંતર {
			/* It's not an option. We're done. */
			પાછા 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	જો (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		જો (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			પાછા errcode;
		}

		optarg = pstart + 1;
		જો (!*optarg) {
			optarg = ખાલી;
			arglen = 0;
		}
		નહીંતર
			arglen = (પૂર્ણાંક) strlen (optarg);
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
	જો (auxp->flags & ARG_NONE) {
		જો (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			પાછા SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		નહીંતર જો (!optarg)
			INC_INDEX (s, 1);
		નહીંતર
			s->subscript++;
		પાછા optp->r_val;
	}

	/* case: required */
	જો (auxp->flags & ARG_REQ) {
		જો (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			પાછા SCANOPT_ERR_ARG_NOT_FOUND;
		}

		જો (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		નહીંતર {
			SAFE_ASSIGN (arg, (અક્ષર *) optarg);
			INC_INDEX (s, 1);
		}
		પાછા optp->r_val;
	}

	/* case: optional */
	જો (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		પાછા optp->r_val;
	}


	/* Should not reach here. */
	પાછા 0;
}


પૂર્ણાંક     scanopt_destroy (scanopt_t *svoid)
{
	સંરચના _scanopt_t *s;

	s = (સંરચના _scanopt_t *) svoid;
	જો (s != ખાલી) {
		મુક્ત(s->aux);
		મુક્ત(s);
	}
	પાછા 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
