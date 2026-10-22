/* filter - postprocessing of flex output through filters */

/* SPDX-License-Identifier: BSD-3-Clause-flex */

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

#ಅನ್ತರ್ಭಾವ "flexdef.h"
ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
ಸಂರಚನಾ filter *output_chain = ರಿಕ್ತ;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
ಸಂರಚನಾ filter *filter_create_ext (ಸಂರಚನಾ filter *chain, ಧ್ರುವ ವರ್ಣ *cmd,
				  ...)
{
	ಸಂರಚನಾ filter *f;
	ಪೂರ್ಣಾಙ್ಕ     max_args;
	ಧ್ರುವ ವರ್ಣ *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(ಪರಿಮಾಣ(ಸಂರಚನಾ filter), 1);
	ಯದಿ (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = ರಿಕ್ತ;
	f->extra = ರಿಕ್ತ;
	f->next = ರಿಕ್ತ;
	f->argc = 0;

	ಯದಿ (chain != ರಿಕ್ತ) {
		/* append f to end of chain */
		ಯಾವತ್ (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(ಪರಿಮಾಣ(ವರ್ಣ *) * (size_t) (max_args + 1));
	ಯದಿ (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	ಯಾವತ್ ((s = va_arg (ap, ಧ್ರುವ ವರ್ಣ *)) != ರಿಕ್ತ) {
		ಯದಿ (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, ಪರಿಮಾಣ(ವರ್ಣ*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = ರಿಕ್ತ;

	va_end (ap);
	ಪ್ರತ್ಯಾಗಮ f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
ಸಂರಚನಾ filter *filter_create_int (ಸಂರಚನಾ filter *chain,
				  ಪೂರ್ಣಾಙ್ಕ (*filter_func) (ಸಂರಚನಾ filter *),
				  ಶೂನ್ಯ *extra)
{
	ಸಂರಚನಾ filter *f;

	/* allocate and initialize new filter */
	f = calloc(ಪರಿಮಾಣ(ಸಂರಚನಾ filter), 1);
	ಯದಿ (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = ರಿಕ್ತ;
	f->argc = 0;
	f->argv = ರಿಕ್ತ;

	f->filter_func = filter_func;
	f->extra = extra;

	ಯದಿ (chain != ರಿಕ್ತ) {
		/* append f to end of chain */
		ಯಾವತ್ (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	ಪ್ರತ್ಯಾಗಮ f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (ಸಂರಚನಾ filter * chain)
{
	ಪೂರ್ಣಾಙ್ಕ     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	ಯದಿ (chain)
		filter_apply_chain (chain->next);
	ಅನ್ಯಥಾ
		ಪ್ರತ್ಯಾಗಮ true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	ಯದಿ (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	ಯದಿ ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	ಯದಿ (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		ಯದಿ (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(ಶೂನ್ಯ)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		ಯದಿ (chain->filter_func) {
			ಪೂರ್ಣಾಙ್ಕ     r;

			ಯದಿ ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		ಅನ್ಯಥಾ {
			execvp (chain->argv[0],
				(ವರ್ಣ **ಧ್ರುವ) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	ಯದಿ (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	ಪ್ರತ್ಯಾಗಮ true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
ಪೂರ್ಣಾಙ್ಕ filter_truncate (ಸಂರಚನಾ filter *chain, ಪೂರ್ಣಾಙ್ಕ max_len)
{
	ಪೂರ್ಣಾಙ್ಕ     len = 1;

	ಯದಿ (!chain)
		ಪ್ರತ್ಯಾಗಮ 0;

	ಯಾವತ್ (chain->next && len < max_len) {
		chain = chain->next;
		++len;
	}

	chain->next = ರಿಕ್ತ;
	ಪ್ರತ್ಯಾಗಮ len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
ಪೂರ್ಣಾಙ್ಕ filter_tee_header (ಸಂರಚನಾ filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	ವರ್ಣ    buf[512];
	ಪೂರ್ಣಾಙ್ಕ     to_cfd = -1;
	FILE   *to_c = ರಿಕ್ತ, *to_h = ರಿಕ್ತ;
	bool    write_header;

	write_header = (chain->extra != ರಿಕ್ತ);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	ಯದಿ ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	ಯದಿ (write_header) {
		ಯದಿ (freopen ((ವರ್ಣ *) chain->extra, "w", stdout) == ರಿಕ್ತ)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	ಯದಿ (write_header) {
		fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != ರಿಕ್ತ ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != ರಿಕ್ತ ? env.outfilename : "<stdout>");

	ಯಾವತ್ (fgets (buf, ಪರಿಮಾಣ buf, stdin)) {
		fputs (buf, to_c);
		ಯದಿ (write_header)
			fputs (buf, to_h);
	}

	ಯದಿ (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		ಯದಿ (ctrl.gen_ಸಾಲು_dirs)
			ಸಾಲು_directive_out (to_h, ರಿಕ್ತ, 4000);
		fflush (to_h);
		ಯದಿ (ferror (to_h))
			lerr (_("error writing output file %s"),
				(ವರ್ಣ *) chain->extra);

		ಅನ್ಯಥಾ ಯದಿ (fclose (to_h))
			lerr (_("error closing output file %s"),
				(ವರ್ಣ *) chain->extra);
	}

	fflush (to_c);
	ಯದಿ (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != ರಿಕ್ತ ? env.outfilename : "<stdout>");

	ಅನ್ಯಥಾ ಯದಿ (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != ರಿಕ್ತ ? env.outfilename : "<stdout>");

	ಯಾವತ್ (wait (0) > 0) ;

	FLEX_EXIT (0);
	ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ bool is_blank_ಸಾಲು (ಧ್ರುವ ವರ್ಣ *str)
{
	ಯಾವತ್ (isspace(*str))
		str++;
	ಪ್ರತ್ಯಾಗಮ (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
ಪೂರ್ಣಾಙ್ಕ filter_fix_linedirs (ಸಂರಚನಾ filter *chain)
{
	ವರ್ಣ   buf[4096];
	ಧ್ರುವ ವರ್ಣ *cp;
	ಧ್ರುವ size_t readsz = ಪರಿಮಾಣ buf;
	ಪೂರ್ಣಾಙ್ಕ     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	ಯದಿ (!chain)
		ಪ್ರತ್ಯಾಗಮ 0;

	ಯಾವತ್ (fgets (buf, (ಪೂರ್ಣಾಙ್ಕ) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		ಯದಿ (ctrl.traceline_re != ರಿಕ್ತ &&
		    ctrl.traceline_template != ರಿಕ್ತ &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			ವರ್ಣ   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			ಯದಿ (strcmp (fname,
				env.outfilename != ರಿಕ್ತ ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != ರಿಕ್ತ ? env.headerfilename : "<stdout>")
					== 0) {

				ವರ್ಣ    *s1, *s2;
				ವರ್ಣ	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				ಯಾವತ್ ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					ಯದಿ (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					ಯದಿ (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", ಪರಿಮಾಣ(buf)-1);
			}
			ಅನ್ಯಥಾ {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			ಮುಕ್ತ (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		ಅನ್ಯಥಾ ಯದಿ (in_gen && is_blank_ಸಾಲು(buf)) {
			ಯದಿ (last_was_blank)
				ಅನುವರ್ತ;
			ಅನ್ಯಥಾ
				last_was_blank = true;
		}

		ಅನ್ಯಥಾ {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	ಯದಿ (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != ರಿಕ್ತ ? env.outfilename : "<stdout>");

	ಅನ್ಯಥಾ ಯದಿ (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != ರಿಕ್ತ ? env.outfilename : "<stdout>");

	ಪ್ರತ್ಯಾಗಮ 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
