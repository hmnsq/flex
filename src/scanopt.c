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

#समावेश "flexdef.h"
#समावेश "scanopt.h"


/* Internal structures */

#घोषणा ARG_NONE 0x01
#घोषणा ARG_REQ  0x02
#घोषणा ARG_OPT  0x04
#घोषणा IS_LONG  0x08

काष्ठा _aux {
	पूर्णांक     flags;		/* The above hex flags. */
	पूर्णांक     namelen;	/* Length of the actual option word, e.g., "--file[=foo]" is 4 */
	पूर्णांक     printlen;	/* Length of entire string, e.g., "--file[=foo]" is 12 */
};


काष्ठा _scanopt_t {
	स्थिर optspec_t *options;	/* List of options. */
	काष्ठा _aux *aux;	/* Auxiliary data about options. */
	पूर्णांक     optc;		/* Number of options. */
	पूर्णांक     argc;		/* Number of args. */
	अक्षर  **argv;		/* Array of strings. */
	पूर्णांक     सूचकांक;		/* Used as: argv[index][subscript]. */
	पूर्णांक     subscript;
	अक्षर    no_err_संदेश;	/* If true, do not print errors. */
	अक्षर    has_long;
	अक्षर    has_short;
};

/* Accessor functions. These WOULD be one-liners, but portability calls. */
अटल स्थिर अक्षर *NAME(काष्ठा _scanopt_t *, पूर्णांक);
अटल पूर्णांक PRINTLEN(काष्ठा _scanopt_t *, पूर्णांक);
अटल पूर्णांक RVAL(काष्ठा _scanopt_t *, पूर्णांक);
अटल पूर्णांक FLAGS(काष्ठा _scanopt_t *, पूर्णांक);
अटल स्थिर अक्षर *DESC(काष्ठा _scanopt_t *, पूर्णांक);
अटल व्योम scanopt_err(काष्ठा _scanopt_t *, पूर्णांक, पूर्णांक);
अटल पूर्णांक matchlongopt(अक्षर *, अक्षर **, पूर्णांक *, अक्षर **, पूर्णांक *);
अटल पूर्णांक find_opt(काष्ठा _scanopt_t *, पूर्णांक, अक्षर *, पूर्णांक, पूर्णांक *, पूर्णांक *opt_offset);

अटल स्थिर अक्षर *NAME (काष्ठा _scanopt_t *s, पूर्णांक i)
{
	वापस s->options[i].opt_fmt +
		((s->aux[i].flags & IS_LONG) ? 2 : 1);
}

अटल पूर्णांक PRINTLEN (काष्ठा _scanopt_t *s, पूर्णांक i)
{
	वापस s->aux[i].printlen;
}

अटल पूर्णांक RVAL (काष्ठा _scanopt_t *s, पूर्णांक i)
{
	वापस s->options[i].r_val;
}

अटल पूर्णांक FLAGS (काष्ठा _scanopt_t *s, पूर्णांक i)
{
	वापस s->aux[i].flags;
}

अटल स्थिर अक्षर *DESC (काष्ठा _scanopt_t *s, पूर्णांक i)
{
	वापस s->options[i].desc ? s->options[i].desc : "";
}

#अगर_अघोषित NO_SCANOPT_USAGE
अटल पूर्णांक get_cols (व्योम);

अटल पूर्णांक get_cols (व्योम)
{
	अक्षर   *env;
	पूर्णांक     cols = 80;	/* default */

#अगर_घोषित HAVE_NCURSES_H
	initscr ();
	endwin ();
	अगर (COLS > 0)
		वापस COLS;
#पूर्ण_अगर

	अगर ((env = दो_पर्या ("COLUMNS")) != शून्य)
		cols = म_से_प (env);

	वापस cols;
}
#पूर्ण_अगर

/* Macro to check for NULL before assigning a value. */
#घोषणा SAFE_ASSIGN(ptr,val) \
    करो{                      \
        अगर((ptr)!=शून्य)      \
            *(ptr) = val;    \
    }जबतक(0)

/* Macro to assure we reset subscript whenever we adjust s->index.*/
#घोषणा INC_सूचकांक(s,n)     \
    करो{                    \
       (s)->सूचकांक += (n);  \
       (s)->subscript= 0;  \
    }जबतक(0)

scanopt_t *scanopt_init (स्थिर optspec_t *options, पूर्णांक argc, अक्षर **argv, पूर्णांक flags)
{
	पूर्णांक     i;
	काष्ठा _scanopt_t *s;
	s = दो_स्मृति(माप (काष्ठा _scanopt_t));

	s->options = options;
	s->optc = 0;
	s->argc = argc;
	s->argv = (अक्षर **) argv;
	s->सूचकांक = 1;
	s->subscript = 0;
	s->no_err_संदेश = (flags & SCANOPT_NO_ERR_संदेश);
	s->has_long = 0;
	s->has_short = 0;

	/* Determine option count. (Find entry with all zeros). */
	s->optc = 0;
	जबतक (options[s->optc].opt_fmt
	       || options[s->optc].r_val || options[s->optc].desc)
		s->optc++;

	/* Build auxiliary data */
	s->aux = दो_स्मृति((माप_प्रकार) s->optc * माप (काष्ठा _aux));

	क्रम (i = 0; i < s->optc; i++) {
		स्थिर अचिन्हित अक्षर *p, *pname;
		स्थिर काष्ठा optspec_t *opt;
		काष्ठा _aux *aux;

		opt = s->options + i;
		aux = s->aux + i;

		aux->flags = ARG_NONE;

		अगर (opt->opt_fmt[0] == '-' && opt->opt_fmt[1] == '-') {
			aux->flags |= IS_LONG;
			pname = (स्थिर अचिन्हित अक्षर *)(opt->opt_fmt + 2);
			s->has_long = 1;
		}
		अन्यथा {
			pname = (स्थिर अचिन्हित अक्षर *)(opt->opt_fmt + 1);
			s->has_short = 1;
		}
		aux->printlen = (पूर्णांक) म_माप (opt->opt_fmt);

		aux->namelen = 0;
		क्रम (p = pname + 1; *p; p++) {
			/* detect required arg */
			अगर (*p == '=' || है_खाली ((अचिन्हित अक्षर)*p)
			    || !(aux->flags & IS_LONG)) {
				अगर (aux->namelen == 0)
					aux->namelen = (पूर्णांक) (p - pname);
				aux->flags |= ARG_REQ;
				aux->flags &= ~ARG_NONE;
			}
			/* detect optional arg. This overrides required arg. */
			अगर (*p == '[') {
				अगर (aux->namelen == 0)
					aux->namelen = (पूर्णांक) (p - pname);
				aux->flags &= ~(ARG_REQ | ARG_NONE);
				aux->flags |= ARG_OPT;
				अवरोध;
			}
		}
		अगर (aux->namelen == 0)
			aux->namelen = (पूर्णांक) (p - pname);
	}
	वापस (scanopt_t *) s;
}

#अगर_अघोषित NO_SCANOPT_USAGE
/* these structs are for scanopt_usage(). */
काष्ठा usg_elem {
	पूर्णांक     idx;
	काष्ठा usg_elem *अग्र;
	काष्ठा usg_elem *alias;
};
प्रकार काष्ठा usg_elem usg_elem;


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
पूर्णांक     scanopt_usage (scanopt_t *scanner, खाता *fp, स्थिर अक्षर *usage)
{
	काष्ठा _scanopt_t *s;
	पूर्णांक     i, columns;
	स्थिर पूर्णांक indent = 2;
	usg_elem *byr_val = शून्य;	/* option indices sorted by r_val */
	usg_elem *store;	/* array of preallocated elements. */
	पूर्णांक     store_idx = 0;
	usg_elem *ue;
	पूर्णांक     opt_col_width = 0, desc_col_width = 0;
	पूर्णांक     desccol;
	पूर्णांक     print_run = 0;

	s = (काष्ठा _scanopt_t *) scanner;

	अगर (usage) {
		ख_लिखो (fp, "%s\n", usage);
	}
	अन्यथा {
		ख_लिखो (fp, _("Usage: %s [OPTIONS]...\n"), s->argv[0]);
	}
	ख_लिखो (fp, "\n");

	/* Sort by r_val and string. Yes, this is O(n*n), but n is small. */
	store = दो_स्मृति((माप_प्रकार) s->optc * माप (usg_elem));
	क्रम (i = 0; i < s->optc; i++) {

		/* grab the next preallocate node. */
		ue = store + store_idx++;
		ue->idx = i;
		ue->अग्र = ue->alias = शून्य;

		/* insert into list. */
		अगर (!byr_val)
			byr_val = ue;
		अन्यथा {
			पूर्णांक     found_alias = 0;
			usg_elem **ue_curr, **ptr_if_no_alias = शून्य;

			ue_curr = &byr_val;
			जबतक (*ue_curr) {
				अगर (RVAL (s, (*ue_curr)->idx) ==
				    RVAL (s, ue->idx)) {
					/* push onto the alias list. */
					ue_curr = &((*ue_curr)->alias);
					found_alias = 1;
					अवरोध;
				}
				अगर (!ptr_if_no_alias
				    &&
				    strcasecmp (NAME (s, (*ue_curr)->idx),
						NAME (s, ue->idx)) > 0) {
					ptr_if_no_alias = ue_curr;
				}
				ue_curr = &((*ue_curr)->अग्र);
			}
			अगर (!found_alias && ptr_if_no_alias)
				ue_curr = ptr_if_no_alias;
			ue->अग्र = *ue_curr;
			*ue_curr = ue;
		}
	}

#अगर 0
	अगर (1) {
		म_लिखो ("ORIGINAL:\n");
		क्रम (i = 0; i < s->optc; i++)
			म_लिखो ("%2d: %s\n", i, NAME (s, i));
		म_लिखो ("SORTED:\n");
		ue = byr_val;
		जबतक (ue) {
			usg_elem *ue2;

			म_लिखो ("%2d: %s\n", ue->idx, NAME (s, ue->idx));
			क्रम (ue2 = ue->alias; ue2; ue2 = ue2->अग्र)
				म_लिखो ("  +---> %2d: %s\n", ue2->idx,
					NAME (s, ue2->idx));
			ue = ue->अग्र;
		}
	}
#पूर्ण_अगर

	/* Now build each row of output. */

	/* first pass calculate how much room we need. */
	क्रम (ue = byr_val; ue; ue = ue->अग्र) {
		usg_elem *ap;
		पूर्णांक     len;

		len = PRINTLEN(s, ue->idx);

		क्रम (ap = ue->alias; ap; ap = ap->अग्र) {
			len += PRINTLEN(s, ap->idx) + (पूर्णांक) म_माप(", ");
		}

		अगर (len > opt_col_width)
			opt_col_width = len;

		/* It's much easier to calculate length for description column! */
		len = (पूर्णांक) म_माप (DESC (s, ue->idx));
		अगर (len > desc_col_width)
			desc_col_width = len;
	}

	/* Determine how much room we have, and how much we will allocate to each col.
	 * Do not address pathological cases. Output will just be ugly. */
	columns = get_cols () - 1;
	अगर (opt_col_width + desc_col_width + indent * 2 > columns) {
		/* opt col gets whatever it wants. we'll wrap the desc col. */
		desc_col_width = columns - (opt_col_width + indent * 2);
		अगर (desc_col_width < 14)	/* 14 is arbitrary lower limit on desc width. */
			desc_col_width = पूर्णांक_उच्च;
	}
	desccol = opt_col_width + indent * 2;

#घोषणा PRINT_SPACES(fp,n) \
	ख_लिखो((fp), "%*s", (n), "")

	/* Second pass (same as above loop), this time we print. */
	/* Sloppy hack: We iterate twice. The first time we print short and long options.
	   The second time we print those lines that have ONLY long options. */
	जबतक (print_run++ < 2) {
		क्रम (ue = byr_val; ue; ue = ue->अग्र) {
			usg_elem *ap;
			पूर्णांक     nwords = 0, nchars = 0, has_short = 0;

/* TODO: get has_short schtick to work */
			has_short = !(FLAGS (s, ue->idx) & IS_LONG);
			क्रम (ap = ue->alias; ap; ap = ap->अग्र) {
				अगर (!(FLAGS (s, ap->idx) & IS_LONG)) {
					has_short = 1;
					अवरोध;
				}
			}
			अगर ((print_run == 1 && !has_short) ||
			    (print_run == 2 && has_short))
				जारी;

			PRINT_SPACES (fp, indent);
			nchars += indent;

/* Print, adding a ", " between aliases. */
#घोषणा PRINT_IT(i) करो{\
                  अगर(nwords++)\
                      nchars+=ख_लिखो(fp,", ");\
                  nchars+=ख_लिखो(fp,"%s",s->options[i].opt_fmt);\
            }जबतक(0)

			अगर (!(FLAGS (s, ue->idx) & IS_LONG))
				PRINT_IT (ue->idx);

			/* print short aliases first. */
			क्रम (ap = ue->alias; ap; ap = ap->अग्र) {
				अगर (!(FLAGS (s, ap->idx) & IS_LONG))
					PRINT_IT (ap->idx);
			}


			अगर (FLAGS (s, ue->idx) & IS_LONG)
				PRINT_IT (ue->idx);

			/* repeat the above loop, this time for long aliases. */
			क्रम (ap = ue->alias; ap; ap = ap->अग्र) {
				अगर (FLAGS (s, ap->idx) & IS_LONG)
					PRINT_IT (ap->idx);
			}

			/* pad to desccol */
			PRINT_SPACES (fp, desccol - nchars);

			/* Print description, wrapped to desc_col_width columns. */
			अगर (1) {
				स्थिर अक्षर *pstart;

				pstart = DESC (s, ue->idx);
				जबतक (1) {
					पूर्णांक     n = 0;
					स्थिर अक्षर *lastws = शून्य, *p;

					p = pstart;

					जबतक (*p && n < desc_col_width
					       && *p != '\n') {
						अगर (है_खाली ((अचिन्हित अक्षर)(*p))
						    || *p == '-') lastws =
								p;
						n++;
						p++;
					}

					अगर (!*p) {	/* hit end of desc. done. */
						ख_लिखो (fp, "%s\n",
							 pstart);
						अवरोध;
					}
					अन्यथा अगर (*p == '\n') {	/* print everything up to here then wrap. */
						ख_लिखो (fp, "%.*s\n", n,
							 pstart);
						PRINT_SPACES (fp, desccol);
						pstart = p + 1;
						जारी;
					}
					अन्यथा {	/* we hit the edge of the screen. wrap at space if possible. */
						अगर (lastws) {
							ख_लिखो (fp,
								 "%.*s\n",
								 (पूर्णांक)(lastws - pstart),
								 pstart);
							pstart =
								lastws + 1;
						}
						अन्यथा {
							ख_लिखो (fp,
								 "%.*s\n",
								 n,
								 pstart);
							pstart = p + 1;
						}
						PRINT_SPACES (fp, desccol);
						जारी;
					}
				}
			}
		}
	}			/* end while */
	मुक्त (store);
	वापस 0;
}
#पूर्ण_अगर /* no scanopt_usage */


अटल व्योम scanopt_err(काष्ठा _scanopt_t *s, पूर्णांक is_short, पूर्णांक err)
{
	स्थिर अक्षर *optname = "";
	अक्षर    optchar[2];

	अगर (!s->no_err_संदेश) {

		अगर (s->सूचकांक > 0 && s->सूचकांक < s->argc) {
			अगर (is_short) {
				optchar[0] =
					s->argv[s->सूचकांक][s->subscript];
				optchar[1] = '\0';
				optname = optchar;
			}
			अन्यथा {
				optname = s->argv[s->सूचकांक];
			}
		}

		ख_लिखो (मानक_त्रुटि, "%s: ", s->argv[0]);
		चयन (err) {
		हाल SCANOPT_ERR_ARG_NOT_ALLOWED:
			ख_लिखो (मानक_त्रुटि,
				 _
				 ("option `%s' doesn't allow an argument\n"),
				 optname);
			अवरोध;
		हाल SCANOPT_ERR_ARG_NOT_FOUND:
			ख_लिखो (मानक_त्रुटि,
				 _("option `%s' requires an argument\n"),
				 optname);
			अवरोध;
		हाल SCANOPT_ERR_OPT_AMBIGUOUS:
			ख_लिखो (मानक_त्रुटि, _("option `%s' is ambiguous\n"),
				 optname);
			अवरोध;
		हाल SCANOPT_ERR_OPT_UNRECOGNIZED:
			ख_लिखो (मानक_त्रुटि, _("Unrecognized option `%s'\n"),
				 optname);
			अवरोध;
		शेष:
			ख_लिखो (मानक_त्रुटि, _("Unknown error=(%d)\n"), err);
			अवरोध;
		}
	}
}


/* Internal. Match str against the regex  ^--([^=]+)(=(.*))?
 * return 1 if *looks* like a long option.
 * 'str' is the only input argument, the rest of the arguments are output only.
 * optname will point to str + 2
 *
 */
अटल पूर्णांक matchlongopt (अक्षर *str, अक्षर **optname, पूर्णांक *optlen, अक्षर **arg, पूर्णांक *arglen)
{
	अक्षर   *p;

	*optname = *arg = शून्य;
	*optlen = *arglen = 0;

	/* Match regex /--./   */
	p = str;
	अगर (p[0] != '-' || p[1] != '-' || !p[2])
		वापस 0;

	p += 2;
	*optname = p;

	/* find the end of optname */
	जबतक (*p && *p != '=')
		++p;

	*optlen = (पूर्णांक) (p - *optname);

	अगर (!*p)
		/* an option with no '=...' part. */
		वापस 1;


	/* We saw an '=' char. The rest of p is the arg. */
	p++;
	*arg = p;
	जबतक (*p)
		++p;
	*arglen = (पूर्णांक) (p - *arg);

	वापस 1;
}


/* Internal. Look up long or short option by name.
 * Long options must match a non-ambiguous prefix, or exact match.
 * Short options must be exact.
 * Return boolean true if found and no error.
 * Error stored in err_code or zero if no error. */
अटल पूर्णांक find_opt (काष्ठा _scanopt_t *s, पूर्णांक lookup_long, अक्षर *optstart, पूर्णांक
	len, पूर्णांक *err_code, पूर्णांक *opt_offset)
{
	पूर्णांक     nmatch = 0, lastr_val = 0, i;

	*err_code = 0;
	*opt_offset = -1;

	अगर (!optstart)
		वापस 0;

	क्रम (i = 0; i < s->optc; i++) {
		स्थिर अक्षर   *optname;

		optname = s->options[i].opt_fmt + (lookup_long ? 2 : 1);

		अगर (lookup_long && (s->aux[i].flags & IS_LONG)) {
			अगर (len > s->aux[i].namelen)
				जारी;

			अगर (म_भेदन (optname, optstart, (माप_प्रकार) len) == 0) {
				nmatch++;
				*opt_offset = i;

				/* exact match overrides all. */
				अगर (len == s->aux[i].namelen) {
					nmatch = 1;
					अवरोध;
				}

				/* ambiguity is ok between aliases. */
				अगर (lastr_val
				    && lastr_val ==
				    s->options[i].r_val) nmatch--;
				lastr_val = s->options[i].r_val;
			}
		}
		अन्यथा अगर (!lookup_long && !(s->aux[i].flags & IS_LONG)) {
			अगर (optname[0] == optstart[0]) {
				nmatch++;
				*opt_offset = i;
			}
		}
	}

	अगर (nmatch == 0) {
		*err_code = SCANOPT_ERR_OPT_UNRECOGNIZED;
		*opt_offset = -1;
	}
	अन्यथा अगर (nmatch > 1) {
		*err_code = SCANOPT_ERR_OPT_AMBIGUOUS;
		*opt_offset = -1;
	}

	वापस *err_code ? 0 : 1;
}


पूर्णांक     scanopt (scanopt_t *svoid, अक्षर **arg, पूर्णांक *optindex)
{
	अक्षर   *optname = शून्य, *optarg = शून्य, *pstart;
	पूर्णांक     namelen = 0, arglen = 0;
	पूर्णांक     errcode = 0, has_अग्र;
	स्थिर optspec_t *optp;
	काष्ठा _scanopt_t *s;
	काष्ठा _aux *auxp;
	पूर्णांक     is_short;
	पूर्णांक     opt_offset = -1;

	s = (काष्ठा _scanopt_t *) svoid;

	/* Normalize return-parameters. */
	SAFE_ASSIGN (arg, शून्य);
	SAFE_ASSIGN (optindex, s->सूचकांक);

	अगर (s->सूचकांक >= s->argc)
		वापस 0;

	/* pstart always points to the start of our current scan. */
	pstart = s->argv[s->सूचकांक] + s->subscript;
	अगर (!pstart)
		वापस 0;

	अगर (s->subscript == 0) {

		/* test for exact match of "--" */
		अगर (pstart[0] == '-' && pstart[1] == '-' && !pstart[2]) {
			SAFE_ASSIGN (optindex, s->सूचकांक + 1);
			INC_सूचकांक (s, 1);
			वापस 0;
		}

		/* Match an opt. */
		अगर (matchlongopt
		    (pstart, &optname, &namelen, &optarg, &arglen)) {

			/* it LOOKS like an opt, but is it one?! */
			अगर (!find_opt
			    (s, 1, optname, namelen, &errcode,
			     &opt_offset)) {
				scanopt_err (s, 0, errcode);
				वापस errcode;
			}
			/* We handle this below. */
			is_short = 0;

			/* Check for short opt.  */
		}
		अन्यथा अगर (pstart[0] == '-' && pstart[1]) {
			/* Pass through to below. */
			is_short = 1;
			s->subscript++;
			pstart++;
		}

		अन्यथा {
			/* It's not an option. We're done. */
			वापस 0;
		}
	}

	/* We have to re-check the subscript status because it
	 * may have changed above. */

	अगर (s->subscript != 0) {

		/* we are somewhere in a run of short opts,
		 * e.g., at the 'z' in `tar -xzf` */

		optname = pstart;
		namelen = 1;
		is_short = 1;

		अगर (!find_opt
		    (s, 0, pstart, namelen, &errcode, &opt_offset)) {
			scanopt_err(s, 1, errcode);
			वापस errcode;
		}

		optarg = pstart + 1;
		अगर (!*optarg) {
			optarg = शून्य;
			arglen = 0;
		}
		अन्यथा
			arglen = (पूर्णांक) म_माप (optarg);
	}

	/* At this point, we have a long or short option matched at opt_offset into
	 * the s->options array (and corresponding aux array).
	 * A trailing argument is in {optarg,arglen}, if any.
	 */

	/* Look ahead in argv[] to see if there is something
	 * that we can use as an argument (if needed). */
	has_अग्र = s->सूचकांक + 1 < s->argc;

	optp = s->options + opt_offset;
	auxp = s->aux + opt_offset;

	/* case: no args allowed */
	अगर (auxp->flags & ARG_NONE) {
		अगर (optarg && !is_short) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_ALLOWED);
			INC_सूचकांक (s, 1);
			वापस SCANOPT_ERR_ARG_NOT_ALLOWED;
		}
		अन्यथा अगर (!optarg)
			INC_सूचकांक (s, 1);
		अन्यथा
			s->subscript++;
		वापस optp->r_val;
	}

	/* case: required */
	अगर (auxp->flags & ARG_REQ) {
		अगर (!optarg && !has_अग्र) {
			scanopt_err(s, is_short, SCANOPT_ERR_ARG_NOT_FOUND);
			वापस SCANOPT_ERR_ARG_NOT_FOUND;
		}

		अगर (!optarg) {
			/* Let the next argv element become the argument. */
			SAFE_ASSIGN (arg, s->argv[s->सूचकांक + 1]);
			INC_सूचकांक (s, 2);
		}
		अन्यथा {
			SAFE_ASSIGN (arg, (अक्षर *) optarg);
			INC_सूचकांक (s, 1);
		}
		वापस optp->r_val;
	}

	/* case: optional */
	अगर (auxp->flags & ARG_OPT) {
		SAFE_ASSIGN (arg, optarg);
		INC_सूचकांक (s, 1);
		वापस optp->r_val;
	}


	/* Should not reach here. */
	वापस 0;
}


पूर्णांक     scanopt_destroy (scanopt_t *svoid)
{
	काष्ठा _scanopt_t *s;

	s = (काष्ठा _scanopt_t *) svoid;
	अगर (s != शून्य) {
		मुक्त(s->aux);
		मुक्त(s);
	}
	वापस 0;
}


/* vim:set tabstop=8 softtabstop=4 shiftwidth=4: */
