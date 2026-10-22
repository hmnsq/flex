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
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
ರಚನೆ filter *output_chain = ಖಾಲಿ;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
ರಚನೆ filter *filter_create_ext (ರಚನೆ filter *chain, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cmd,
				  ...)
{
	ರಚನೆ filter *f;
	ಪೂರ್ಣಾಂಕ     max_ವಾದಗಳು;
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(ಗಾತ್ರ(ರಚನೆ filter), 1);
	ಆದರೆ (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = ಖಾಲಿ;
	f->extra = ಖಾಲಿ;
	f->ಮುಂದಿನ = ಖಾಲಿ;
	f->argc = 0;

	ಆದರೆ (chain != ಖಾಲಿ) {
		/* append f to end of chain */
		ಆಗ (chain->ಮುಂದಿನ)
			chain = chain->ಮುಂದಿನ;
		chain->ಮುಂದಿನ = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_ವಾದಗಳು = 8;
	f->argv = ಸ್ಮರಣೆ_ಕೊಡು(ಗಾತ್ರ(ಅಕ್ಷರ *) * (size_t) (max_ವಾದಗಳು + 1));
	ಆದರೆ (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_ಆರಂಭ (ap, cmd);
	ಆಗ ((s = va_arg (ap, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)) != ಖಾಲಿ) {
		ಆದರೆ (f->argc >= max_ವಾದಗಳು) {
			max_ವಾದಗಳು += 8;
			f->argv = realloc(f->argv, ಗಾತ್ರ(ಅಕ್ಷರ*) * (size_t) (max_ವಾದಗಳು + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = ಖಾಲಿ;

	va_ಕೊನೆ (ap);
	ಹಿಂತಿರುಗಿ f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
ರಚನೆ filter *filter_create_int (ರಚನೆ filter *chain,
				  ಪೂರ್ಣಾಂಕ (*filter_func) (ರಚನೆ filter *),
				  ಶೂನ್ಯ *extra)
{
	ರಚನೆ filter *f;

	/* allocate and initialize new filter */
	f = ಸೊನ್ನೆ_ಸ್ಮರಣೆ_ಕೊಡು(ಗಾತ್ರ(ರಚನೆ filter), 1);
	ಆದರೆ (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->ಮುಂದಿನ = ಖಾಲಿ;
	f->argc = 0;
	f->argv = ಖಾಲಿ;

	f->filter_func = filter_func;
	f->extra = extra;

	ಆದರೆ (chain != ಖಾಲಿ) {
		/* append f to end of chain */
		ಆಗ (chain->ಮುಂದಿನ)
			chain = chain->ಮುಂದಿನ;
		chain->ಮುಂದಿನ = f;
	}

	ಹಿಂತಿರುಗಿ f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (ರಚನೆ filter * chain)
{
	ಪೂರ್ಣಾಂಕ     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	ಆದರೆ (chain)
		filter_apply_chain (chain->ಮುಂದಿನ);
	ಇಲ್ಲದಿದ್ದರೆ
		ಹಿಂತಿರುಗಿ true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	ಆದರೆ (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	ಆದರೆ ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	ಆದರೆ (pid == 0) {
		/*ಮಗು*/

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		ಆದರೆ (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(ಶೂನ್ಯ)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		ಆದರೆ (chain->filter_func) {
			ಪೂರ್ಣಾಂಕ     r;

			ಆದರೆ ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		ಇಲ್ಲದಿದ್ದರೆ {
			execvp (chain->argv[0],
				(ಅಕ್ಷರ **ಸ್ಥಿರಾಂಕ) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/*ಪೋಷಕ*/
	close (pipes[0]);
	ಆದರೆ (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	ಹಿಂತಿರುಗಿ true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
ಪೂರ್ಣಾಂಕ filter_truncate (ರಚನೆ filter *chain, ಪೂರ್ಣಾಂಕ max_len)
{
	ಪೂರ್ಣಾಂಕ     len = 1;

	ಆದರೆ (!chain)
		ಹಿಂತಿರುಗಿ 0;

	ಆಗ (chain->ಮುಂದಿನ && len < max_len) {
		chain = chain->ಮುಂದಿನ;
		++len;
	}

	chain->ಮುಂದಿನ = ಖಾಲಿ;
	ಹಿಂತಿರುಗಿ len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
ಪೂರ್ಣಾಂಕ filter_tee_ಶೀರ್ಷಿಕೆ (ರಚನೆ filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	ಅಕ್ಷರ    buf[512];
	ಪೂರ್ಣಾಂಕ     ಗಮ್ಯ_cfd = -1;
	FILE   *ಗಮ್ಯ_c = ಖಾಲಿ, *ಗಮ್ಯ_h = ಖಾಲಿ;
	bool    write_ಶೀರ್ಷಿಕೆ;

	write_ಶೀರ್ಷಿಕೆ = (chain->extra != ಖಾಲಿ);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	ಆದರೆ ((ಗಮ್ಯ_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	ಗಮ್ಯ_c = fdopen (ಗಮ್ಯ_cfd, "w");

	ಆದರೆ (write_ಶೀರ್ಷಿಕೆ) {
		ಆದರೆ (freopen ((ಅಕ್ಷರ *) chain->extra, "w", stdout) == ಖಾಲಿ)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->ಮುಂದಿನ);
		ಗಮ್ಯ_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	ಆದರೆ (write_ಶೀರ್ಷಿಕೆ) {
		fputs (check_4_gnu_m4, ಗಮ್ಯ_h);
		fputs ("m4_changecom`'m4_dnl\n", ಗಮ್ಯ_h);
		fputs ("m4_changequote`'m4_dnl\n", ಗಮ್ಯ_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", ಗಮ್ಯ_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", ಗಮ್ಯ_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", ಗಮ್ಯ_h);
		fprintf (ಗಮ್ಯ_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != ಖಾಲಿ ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, ಗಮ್ಯ_c);
	fputs ("m4_changecom`'m4_dnl\n", ಗಮ್ಯ_c);
	fputs ("m4_changequote`'m4_dnl\n", ಗಮ್ಯ_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", ಗಮ್ಯ_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", ಗಮ್ಯ_c);
	fprintf (ಗಮ್ಯ_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != ಖಾಲಿ ? env.outfilename : "<stdout>");

	ಆಗ (fgets (buf, ಗಾತ್ರ buf, stdin)) {
		fputs (buf, ಗಮ್ಯ_c);
		ಆದರೆ (write_ಶೀರ್ಷಿಕೆ)
			fputs (buf, ಗಮ್ಯ_h);
	}

	ಆದರೆ (write_ಶೀರ್ಷಿಕೆ) {
		fprintf (ಗಮ್ಯ_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		ಆದರೆ (ctrl.gen_ಸಾಲು_dirs)
			ಸಾಲು_directive_ಹೊರಹೋಗು (ಗಮ್ಯ_h, ಖಾಲಿ, 4000);
		fflush (ಗಮ್ಯ_h);
		ಆದರೆ (ferror (ಗಮ್ಯ_h))
			lerr (_("error writing output file %s"),
				(ಅಕ್ಷರ *) chain->extra);

		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fclose (ಗಮ್ಯ_h))
			lerr (_("error closing output file %s"),
				(ಅಕ್ಷರ *) chain->extra);
	}

	fflush (ಗಮ್ಯ_c);
	ಆದರೆ (ferror (ಗಮ್ಯ_c))
		lerr (_("error writing output file %s"),
			env.outfilename != ಖಾಲಿ ? env.outfilename : "<stdout>");

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fclose (ಗಮ್ಯ_c))
		lerr (_("error closing output file %s"),
			env.outfilename != ಖಾಲಿ ? env.outfilename : "<stdout>");

	ಆಗ (wait (0) > 0) ;

	FLEX_EXIT (0);
	ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ bool is_blank_ಸಾಲು (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str)
{
	ಆಗ (ಖಾಲಿಯೇ(*str))
		str++;
	ಹಿಂತಿರುಗಿ (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
ಪೂರ್ಣಾಂಕ filter_fix_linedirs (ರಚನೆ filter *chain)
{
	ಅಕ್ಷರ   buf[4096];
	ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *cp;
	ಸ್ಥಿರಾಂಕ size_t readsz = ಗಾತ್ರ buf;
	ಪೂರ್ಣಾಂಕ     lineno = 1;
	bool    ಒಳ_gen = true;	/* in generated code */
	bool    ಕೊನೆಯ_was_blank = false;

	ಆದರೆ (!chain)
		ಹಿಂತಿರುಗಿ 0;

	ಆಗ (fgets (buf, (ಪೂರ್ಣಾಂಕ) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		ಆದರೆ (ctrl.traceline_re != ಖಾಲಿ &&
		    ctrl.traceline_template != ಖಾಲಿ &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			ಅಕ್ಷರ   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			ಆದರೆ (strcmp (fname,
				env.outfilename != ಖಾಲಿ ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != ಖಾಲಿ ? env.headerfilename : "<stdout>")
					== 0) {

				ಅಕ್ಷರ    *s1, *s2;
				ಅಕ್ಷರ	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				ಆಗ ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					ಆದರೆ (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					ಆದರೆ (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				ಒಳ_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", ಗಾತ್ರ(buf)-1);
			}
			ಇಲ್ಲದಿದ್ದರೆ {
				/* it's a #line directive for code we didn't write */
				ಒಳ_gen = false;
			}

			ಬಿಡುಗಡೆ (fname);
			ಕೊನೆಯ_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಒಳ_gen && is_blank_ಸಾಲು(buf)) {
			ಆದರೆ (ಕೊನೆಯ_was_blank)
				ಮುಂದುವರಿ;
			ಇಲ್ಲದಿದ್ದರೆ
				ಕೊನೆಯ_was_blank = true;
		}

		ಇಲ್ಲದಿದ್ದರೆ {
			/* it's a line of normal, non-empty code. */
			ಕೊನೆಯ_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	ಆದರೆ (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != ಖಾಲಿ ? env.outfilename : "<stdout>");

	ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != ಖಾಲಿ ? env.outfilename : "<stdout>");

	ಹಿಂತಿರುಗಿ 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
