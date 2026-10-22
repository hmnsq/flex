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

#അന്തര്ഭാവ "flexdef.h"
#അന്തര്ഭാവ "scanopt.h"


/* Internal structures */

#define ARG_NONE 0x01
#define ARG_REQ  0x02
#define ARG_OPT  0x04
#define IS_LONG  0x08

ഘടന _aux {
	പൂർണ്ണസംഖ്യ     flags;		/* The above hex flags. */
	പൂർണ്ണസംഖ്യ     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	പൂർണ്ണസംഖ്യ     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


ഘടന _scanopt_t {
	സ്ഥിരം optspec_t *options;	/* List of options. */
	ഘടന _aux *aux;	/* Auxiliary data about options. */
	പൂർണ്ണസംഖ്യ     optc;		/* Number of options. */
	പൂർണ്ണസംഖ്യ     argc;		/* Number of args. */
	അക്ഷരം  **argv;		/* Array of strings. */
	പൂർണ്ണസംഖ്യ     index;		/* Used as: argv[index][subscript]. */
	പൂർണ്ണസംഖ്യ     subscript;
	അക്ഷരം    no_err_സന്ദേശം;	/* If true, do not print errors. */
	അക്ഷരം    has_long;
	അക്ഷരം    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
സ്ഥിതം സ്ഥിരം അക്ഷരം *NAME(ഘടന _scanopt_t *, പൂർണ്ണസംഖ്യ);
സ്ഥിതം പൂർണ്ണസംഖ്യ PRINTLEN(ഘടന _scanopt_t *, പൂർണ്ണസംഖ്യ);
സ്ഥിതം പൂർണ്ണസംഖ്യ RVAL(ഘടന _scanopt_t *, പൂർണ്ണസംഖ്യ);
സ്ഥിതം പൂർണ്ണസംഖ്യ FLAGS(ഘടന _scanopt_t *, പൂർണ്ണസംഖ്യ);
സ്ഥിതം സ്ഥിരം അക്ഷരം *DESC(ഘടന _scanopt_t *, പൂർണ്ണസംഖ്യ);
സ്ഥിതം ശൂന്യം scanopt_err(ഘടന _scanopt_t *, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ);
സ്ഥിതം പൂർണ്ണസംഖ്യ matchlongopt(അക്ഷരം *, അക്ഷരം **, പൂർണ്ണസംഖ്യ *, അക്ഷരം **, പൂർണ്ണസംഖ്യ *);
സ്ഥിതം പൂർണ്ണസംഖ്യ find_opt(ഘടന _scanopt_t *, പൂർണ്ണസംഖ്യ, അക്ഷരം *, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ *, പൂർണ്ണസംഖ്യ *opt_offset);

സ്ഥിതം സ്ഥിരം അക്ഷരം *NAME (ഘടന _scanopt_t *s, പൂർണ്ണസംഖ്യ i)
{
	തിരികെ s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ PRINTLEN (ഘടന _scanopt_t *s, പൂർണ്ണസംഖ്യ i)
{
	തിരികെ s->aux[i].printlen;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ RVAL (ഘടന _scanopt_t *s, പൂർണ്ണസംഖ്യ i)
{
	തിരികെ s->options[i].r_val;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ FLAGS (ഘടന _scanopt_t *s, പൂർണ്ണസംഖ്യ i)
{
	തിരികെ s->aux[i].flags;
}

സ്ഥിതം സ്ഥിരം അക്ഷരം *DESC (ഘടന _scanopt_t *s, പൂർണ്ണസംഖ്യ i)
{
	തിരികെ s->options[i].desc ? s->options[i].desc : "";
}

#ifndef NO_SCANOPT_USAGE
സ്ഥിതം പൂർണ്ണസംഖ്യ get_cols (ശൂന്യം);

സ്ഥിതം പൂർണ്ണസംഖ്യ get_cols (ശൂന്യം)
{
	അക്ഷരം   *env;
	പൂർണ്ണസംഖ്യ     cols = 80;	/* default */

#ifdef HAVE_NCURSES_H
	initscr ();
	endwin ();
	എങ്കിൽ (COLS > 0)
		തിരികെ COLS;
#endif

	എങ്കിൽ ((env = getenv ("COLUMNS")) != ശൂന്യ)
		cols = atoi (env);

	തിരികെ cols;
}
#endif

/* Macro to check for NULL before assigning a value. */
#define SAFE_ASSIGN(ptr,val) \
    ചെയ്യുക{                      \
        എങ്കിൽ((ptr)!=ശൂന്യ)      \
            *(ptr) = val;    \
    }ആകുമ്പോൾ(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#define INC_INDEX(s,n)     \
    ചെയ്യുക{                    \
       (s)->index += (n);  \
       (s)->subscript= 0;  \
    }ആകുമ്പോൾ(0)

scanopt_t *scanopt_init (സ്ഥിരം optspec_t *options, പൂർണ്ണസംഖ്യ argc, അക്ഷരം **argv, പൂർണ്ണസംഖ്യ flags)
{
	പൂർണ്ണസംഖ്യ     i;
	ഘടന _scanopt_t *s;
	s = malloc(വലുപ്പം (ഘടന _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (അക്ഷരം **) argv;
	s->index = 1;
	s->subscript = 0;
	s->no_err_സന്ദേശം = (flags & SCANOPT_NO_ERR_സന്ദേശം);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	ആകുമ്പോൾ (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = malloc((size_t) s->optc * വലുപ്പം (ഘടന _aux));

	വേണ്ടി (i = 0; i < s->optc; i++) {
		സ്ഥിരം unsigned അക്ഷരം *p, *pname;
		സ്ഥിരം ഘടന optspec_t *opt;
		ഘടന _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		എങ്കിൽ (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (സ്ഥിരം unsigned അക്ഷരം *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		അല്ലെങ്കിൽ {
			pname = (സ്ഥിരം unsigned അക്ഷരം *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (പൂർണ്ണസംഖ്യ) strlen (opt->opt_fmt);

		aux->namelen = 0;
		വേണ്ടി (p = pname + 1; *p; p++) {
			/* detect required arg */
			എങ്കിൽ (*p == '=' || isspace ((unsigned അക്ഷരം)*p)
			    || !(aux->flags & IS_LONG)) {
				എങ്കിൽ (aux->namelen == 0)
					aux->namelen = (പൂർണ്ണസംഖ്യ) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			എങ്കിൽ (*p == '[') {
				എങ്കിൽ (aux->namelen == 0)
					aux->namelen = (പൂർണ്ണസംഖ്യ) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				നിർത്തുക;
			}
		}
		എങ്കിൽ (aux->namelen == 0)
			aux->namelen = (പൂർണ്ണസംഖ്യ) (p - pname);
	}
	തിരികെ (scanopt_t *) s;
}

#ifndef NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
ഘടന usg_elem {
	പൂർണ്ണസംഖ്യ     idx;
	ഘടന usg_elem *next;
	ഘടന usg_elem *alias;
};
തരനിർവചനം ഘടന usg_elem usg_elem;


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
പൂർണ്ണസംഖ്യ     scanopt_usage (scanopt_t *scanner, FILE *fp, സ്ഥിരം അക്ഷരം *usage)
{
	ഘടന _scanopt_t *s;
	പൂർണ്ണസംഖ്യ     i, columns;
	സ്ഥിരം പൂർണ്ണസംഖ്യ indent = 2;
	usg_elem *byr_val = ശൂന്യ;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	പൂർണ്ണസംഖ്യ     store_idx = 0;
	usg_elem *ue;
	പൂർണ്ണസംഖ്യ     opt_col_width = 0, desc_col_width = 0;
	പൂർണ്ണസംഖ്യ     desccol;
	പൂർണ്ണസംഖ്യ     print_run = 0;

	s = (ഘടന _scanopt_t *) scanner;

	എങ്കിൽ (usage) {
		fprintf (fp, "%s\n", usage);
	}
	അല്ലെങ്കിൽ {
		fprintf (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	fprintf (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = malloc((size_t) s->optc * വലുപ്പം (usg_elem));
	വേണ്ടി (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->next = ue->alias = ശൂന്യ;

		/* insert into list. */
		എങ്കിൽ (!byr_val)
			byr_val = ue;
		അല്ലെങ്കിൽ {
			പൂർണ്ണസംഖ്യ     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = ശൂന്യ;

			ue_curr = &byr_val;
			ആകുമ്പോൾ (*ue_curr) {
				എങ്കിൽ (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					നിർത്തുക;
				}
				എങ്കിൽ (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->next);
			}
			എങ്കിൽ (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->next = *ue_curr;
			*ue_curr = ue;
		}
	}

#എങ്കിൽ 0
	എങ്കിൽ (1) {
		printf ("ORIGINAL:\n");
		വേണ്ടി (i = 0; i < s->optc; i++)
			printf ("%2d: %s\n", i, NAME (s, i));
		printf ("SORTED:\n");
		ue = byr_val;
		ആകുമ്പോൾ (ue) {
			usg_elem *ue2;

			printf ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			വേണ്ടി (ue2 = ue->alias; ue2; ue2 = ue2->next)
				printf ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->next;
		}
	}
#endif

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	വേണ്ടി (ue = byr_val; ue; ue = ue->next) {
		usg_elem *ap;
		പൂർണ്ണസംഖ്യ     len;

		len = PRINTLEN(s, ue->idx);

		വേണ്ടി (ap = ue->alias; ap; ap = ap->next) {
			len += PRINTLEN(s, ap->idx) + (പൂർണ്ണസംഖ്യ) strlen(", ");
		}

		എങ്കിൽ (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (പൂർണ്ണസംഖ്യ) strlen (DESC (s, ue->idx));
		എങ്കിൽ (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	എങ്കിൽ (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		എങ്കിൽ (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = INT_MAX;
	}
	desccol = opt_col_width + indent * 2;

#define PRINT_SPACES(fp,n) \
	fprintf((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	ആകുമ്പോൾ (print_run++ < 2) {
		വേണ്ടി (ue = byr_val; ue; ue = ue->next) {
			usg_elem *ap;
			പൂർണ്ണസംഖ്യ     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			വേണ്ടി (ap = ue->alias; ap; ap = ap->next) {
				എങ്കിൽ (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					നിർത്തുക;
				}
			}
			എങ്കിൽ ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				തുടരുക;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#define PRINT_IT(i) ചെയ്യുക{\
                  എങ്കിൽ(nwords++)\
                      nchars+=fprintf(fp,", ");\
                  nchars+=fprintf(fp,"%s",s->options[i].opt_fmt);\
            }ആകുമ്പോൾ(0)

			എങ്കിൽ (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			വേണ്ടി (ap = ue->alias; ap; ap = ap->next) {
				എങ്കിൽ (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			എങ്കിൽ (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			വേണ്ടി (ap = ue->alias; ap; ap = ap->next) {
				എങ്കിൽ (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			എങ്കിൽ (1) {
				സ്ഥിരം അക്ഷരം *pstart;

				pstart = DESC (s, ue->idx);
				ആകുമ്പോൾ (1) {
					പൂർണ്ണസംഖ്യ     n = 0;
					സ്ഥിരം അക്ഷരം *lastws = ശൂന്യ, *p;

					p = pstart;

					ആകുമ്പോൾ (*p && n < desc_col_width
					       && *p != '\n') {
						എങ്കിൽ (isspace ((unsigned അക്ഷരം)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					എങ്കിൽ (!*p) {	/* hit end of desc. done. */
						fprintf (fp, "%s\n",
							 pstart);
						നിർത്തുക;
					}
					അല്ലെങ്കിൽ എങ്കിൽ (*p == '\n') {	/* print everything up to here then wrap. */
						fprintf (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						തുടരുക;
					}
					അല്ലെങ്കിൽ {	/* we hit the edge of the screen. wrap at space if possible. */
						എങ്കിൽ (lastws) {
							fprintf (fp,
								 "%.*s\n",
								 (പൂർണ്ണസംഖ്യ)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						അല്ലെങ്കിൽ {
							fprintf (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						തുടരുക;
					}
				}
			}
		}
	}			/* end while */
	സ്വതന്ത്രം (store);
	തിരികെ 0;
}
#endif /* no scanopt_usage */


സ്ഥിതം ശൂന്യം scanopt_err(ഘടന _scanopt_t *s, പൂർണ്ണസംഖ്യ is_short, പൂർണ്ണസംഖ്യ err)
{
	സ്ഥിരം അക്ഷരം *optname = "";
	അക്ഷരം    optchar[2];

	എങ്കിൽ (!s->no_err_സന്ദേശം) {

		എങ്കിൽ (s->index > 0 && s->index < s->argc) {
			എങ്കിൽ (is_short) {
				optchar[0] =
					s->argv[s->index][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			അല്ലെങ്കിൽ {
				optname = s->argv[s->index];
			}
		}

		fprintf (stderr, "%s: ", s->argv[0]);
		തിരഞ്ഞെടുപ്പ് (err) {
		അവസ്ഥ SCANOPT_ERR_ARG_NOT_ALLOWED:
			fprintf (stderr,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			നിർത്തുക;
		അവസ്ഥ SCANOPT_ERR_ARG_NOT_FOUND:
			fprintf (stderr,
				 _("option `%s' requires an argument\n"),
				 optname);
			നിർത്തുക;
		അവസ്ഥ SCANOPT_ERR_OPT_AMBIGUOUS:
			fprintf (stderr, _("option `%s' is ambiguous\n"),
				 optname);
			നിർത്തുക;
		അവസ്ഥ SCANOPT_ERR_OPT_UNRECOGNIZED:
			fprintf (stderr, _("Unrecognized option `%s'\n"),
				 optname);
			നിർത്തുക;
		സ്ഥിരസ്ഥിതി:
			fprintf (stderr, _("Unknown error=(%d)\n"), err);
			നിർത്തുക;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
സ്ഥിതം പൂർണ്ണസംഖ്യ matchlongopt (അക്ഷരം *str, അക്ഷരം **optname, പൂർണ്ണസംഖ്യ *optlen, അക്ഷരം **arg, പൂർണ്ണസംഖ്യ *arglen)
{
	അക്ഷരം   *p;

	*optname = *arg = ശൂന്യ;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	എങ്കിൽ (p[0] != '-' || p[1] != '-' || !p[2])
		തിരികെ 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	ആകുമ്പോൾ (*p && *p != '=')
		++p;

	*optlen = (പൂർണ്ണസംഖ്യ) (p - *optname);

	എങ്കിൽ (!*p)
		/* an option with no '=...' part. */
		തിരികെ 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	ആകുമ്പോൾ (*p)
		++p;
	*arglen = (പൂർണ്ണസംഖ്യ) (p - *arg);

	തിരികെ 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
സ്ഥിതം പൂർണ്ണസംഖ്യ find_opt (ഘടന _scanopt_t *s, പൂർണ്ണസംഖ്യ lookup_long, അക്ഷരം *optstart, പൂർണ്ണസംഖ്യ
	len, പൂർണ്ണസംഖ്യ *err_code, പൂർണ്ണസംഖ്യ *opt_offset)
{
	പൂർണ്ണസംഖ്യ     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	എങ്കിൽ (!optstart)
		തിരികെ 0;

	വേണ്ടി (i = 0; i < s->optc; i++) {
		സ്ഥിരം അക്ഷരം   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		എങ്കിൽ (lookup_long && (s->aux[i].flags & IS_LONG)) {
			എങ്കിൽ (len > s->aux[i].namelen)
				തുടരുക;

			എങ്കിൽ (strncmp (optname, optstart, (size_t) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				എങ്കിൽ (len == s->aux[i].namelen) {
					nmatch = 1;
					നിർത്തുക;
				}

				/* ambiguity is ok between aliases. */
				എങ്കിൽ (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		അല്ലെങ്കിൽ എങ്കിൽ (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			എങ്കിൽ (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	എങ്കിൽ (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	അല്ലെങ്കിൽ എങ്കിൽ (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	തിരികെ *err_code ? 0 : 1;
}


പൂർണ്ണസംഖ്യ     scanopt (scanopt_t *svoid, അക്ഷരം **arg, പൂർണ്ണസംഖ്യ *optindex)
{
	അക്ഷരം   *optname = ശൂന്യ, *optarg = ശൂന്യ, *pstart;
	പൂർണ്ണസംഖ്യ     namelen = 0, arglen = 0;
	പൂർണ്ണസംഖ്യ     errcode = 0, has_next;
	സ്ഥിരം optspec_t *optp;
	ഘടന _scanopt_t *s;
	ഘടന _aux *auxp;
	പൂർണ്ണസംഖ്യ     is_short;
	പൂർണ്ണസംഖ്യ     opt_offset = -1;

	s = (ഘടന _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, ശൂന്യ);
	SAFE_ASSIGN (optindex, s->index);

	എങ്കിൽ (s->index >= s->argc)
		തിരികെ 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->index] + s->subscript;
	എങ്കിൽ (!pstart)
		തിരികെ 0;

	എങ്കിൽ (s->subscript == 0) {

		/* test for exact match of "--" */
		എങ്കിൽ (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->index + 1);
			INC_INDEX (s, 1);
			തിരികെ 0;
		}

		/* Match an opt. */
		എങ്കിൽ (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			എങ്കിൽ (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				തിരികെ errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		അല്ലെങ്കിൽ എങ്കിൽ (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		അല്ലെങ്കിൽ {
			/* It's not an option. We're done. */
			തിരികെ 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	എങ്കിൽ (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		എങ്കിൽ (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			തിരികെ errcode;
		}

		optarg = pstart + 1;
		എങ്കിൽ (!*optarg) {
			optarg = ശൂന്യ;
			arglen = 0;
		}
		അല്ലെങ്കിൽ
			arglen = (പൂർണ്ണസംഖ്യ) strlen (optarg);
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
	എങ്കിൽ (auxp->flags & ARG_NONE) {
		എങ്കിൽ (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_INDEX (s, 1);
			തിരികെ SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		അല്ലെങ്കിൽ എങ്കിൽ (!optarg)
			INC_INDEX (s, 1);
		അല്ലെങ്കിൽ
			s->subscript++;
		തിരികെ optp->r_val;
	}

	/* case: required */
	എങ്കിൽ (auxp->flags & ARG_REQ) {
		എങ്കിൽ (!optarg && !has_next) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			തിരികെ SCANOPT_ERR_ARG_NOT_FOUND;
		}

		എങ്കിൽ (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->index + 1]);
			INC_INDEX (s, 2);
		}
		അല്ലെങ്കിൽ {
			SAFE_ASSIGN (arg, (അക്ഷരം *) optarg);
			INC_INDEX (s, 1);
		}
		തിരികെ optp->r_val;
	}

	/* case: optional */
	എങ്കിൽ (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_INDEX (s, 1);
		തിരികെ optp->r_val;
	}


	/* Should not reach here. */
	തിരികെ 0;
}


പൂർണ്ണസംഖ്യ     scanopt_destroy (scanopt_t *svoid)
{
	ഘടന _scanopt_t *s;

	s = (ഘടന _scanopt_t *) svoid;
	എങ്കിൽ (s != ശൂന്യ) {
		സ്വതന്ത്രം(s->aux);
		സ്വതന്ത്രം(s);
	}
	തിരികെ 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
