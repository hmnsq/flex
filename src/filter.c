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

#ਅਨ੍ਤਰ੍ਭਾਵ "flexdef.h"
ਸਥਿਰ ਅਚਲ ਅੱਖਰ * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
ਬਣਤਰ filter *output_chain = ਨਿਰਾ;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
ਬਣਤਰ filter *filter_create_ext (ਬਣਤਰ filter *chain, ਅਚਲ ਅੱਖਰ *cmd,
				  ...)
{
	ਬਣਤਰ filter *f;
	ਪੂਰਨ     max_ਦਲੀਲਾਂ;
	ਅਚਲ ਅੱਖਰ *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(ਆਕਾਰ(ਬਣਤਰ filter), 1);
	ਜੇ (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = ਨਿਰਾ;
	f->extra = ਨਿਰਾ;
	f->ਅਗਲਾ = ਨਿਰਾ;
	f->argc = 0;

	ਜੇ (chain != ਨਿਰਾ) {
		/* append f to end of chain */
		ਜਦੋਂ (chain->ਅਗਲਾ)
			chain = chain->ਅਗਲਾ;
		chain->ਅਗਲਾ = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_ਦਲੀਲਾਂ = 8;
	f->argv = ਸਮ੍ਰਿਤੀ_ਦਿਓ(ਆਕਾਰ(ਅੱਖਰ *) * (size_t) (max_ਦਲੀਲਾਂ + 1));
	ਜੇ (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_ਸ਼ੁਰੂ (ap, cmd);
	ਜਦੋਂ ((s = va_arg (ap, ਅਚਲ ਅੱਖਰ *)) != ਨਿਰਾ) {
		ਜੇ (f->argc >= max_ਦਲੀਲਾਂ) {
			max_ਦਲੀਲਾਂ += 8;
			f->argv = realloc(f->argv, ਆਕਾਰ(ਅੱਖਰ*) * (size_t) (max_ਦਲੀਲਾਂ + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = ਨਿਰਾ;

	va_ਸਿਰਾ (ap);
	ਵਾਪਸ f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
ਬਣਤਰ filter *filter_create_int (ਬਣਤਰ filter *chain,
				  ਪੂਰਨ (*filter_func) (ਬਣਤਰ filter *),
				  ਖਾਲੀ *extra)
{
	ਬਣਤਰ filter *f;

	/* allocate and initialize new filter */
	f = ਸਿਫਰ_ਸਮ੍ਰਿਤੀ_ਦਿਓ(ਆਕਾਰ(ਬਣਤਰ filter), 1);
	ਜੇ (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->ਅਗਲਾ = ਨਿਰਾ;
	f->argc = 0;
	f->argv = ਨਿਰਾ;

	f->filter_func = filter_func;
	f->extra = extra;

	ਜੇ (chain != ਨਿਰਾ) {
		/* append f to end of chain */
		ਜਦੋਂ (chain->ਅਗਲਾ)
			chain = chain->ਅਗਲਾ;
		chain->ਅਗਲਾ = f;
	}

	ਵਾਪਸ f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (ਬਣਤਰ filter * chain)
{
	ਪੂਰਨ     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	ਜੇ (chain)
		filter_apply_chain (chain->ਅਗਲਾ);
	ਨਹੀਂਤਾਂ
		ਵਾਪਸ true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	ਜੇ (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	ਜੇ ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	ਜੇ (pid == 0) {
		/*ਬੱਚਾ*/

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		ਜੇ (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(ਖਾਲੀ)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		ਜੇ (chain->filter_func) {
			ਪੂਰਨ     r;

			ਜੇ ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		ਨਹੀਂਤਾਂ {
			execvp (chain->argv[0],
				(ਅੱਖਰ **ਅਚਲ) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/*ਮਾਪਾ*/
	close (pipes[0]);
	ਜੇ (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	ਵਾਪਸ true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
ਪੂਰਨ filter_truncate (ਬਣਤਰ filter *chain, ਪੂਰਨ max_len)
{
	ਪੂਰਨ     len = 1;

	ਜੇ (!chain)
		ਵਾਪਸ 0;

	ਜਦੋਂ (chain->ਅਗਲਾ && len < max_len) {
		chain = chain->ਅਗਲਾ;
		++len;
	}

	chain->ਅਗਲਾ = ਨਿਰਾ;
	ਵਾਪਸ len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
ਪੂਰਨ filter_tee_ਸਿਰਲੇਖ (ਬਣਤਰ filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	ਅੱਖਰ    buf[512];
	ਪੂਰਨ     ਮੰਜ਼ਿਲ_cfd = -1;
	FILE   *ਮੰਜ਼ਿਲ_c = ਨਿਰਾ, *ਮੰਜ਼ਿਲ_h = ਨਿਰਾ;
	bool    write_ਸਿਰਲੇਖ;

	write_ਸਿਰਲੇਖ = (chain->extra != ਨਿਰਾ);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	ਜੇ ((ਮੰਜ਼ਿਲ_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	ਮੰਜ਼ਿਲ_c = fdopen (ਮੰਜ਼ਿਲ_cfd, "w");

	ਜੇ (write_ਸਿਰਲੇਖ) {
		ਜੇ (freopen ((ਅੱਖਰ *) chain->extra, "w", stdout) == ਨਿਰਾ)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->ਅਗਲਾ);
		ਮੰਜ਼ਿਲ_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	ਜੇ (write_ਸਿਰਲੇਖ) {
		fputs (check_4_gnu_m4, ਮੰਜ਼ਿਲ_h);
		fputs ("m4_changecom`'m4_dnl\n", ਮੰਜ਼ਿਲ_h);
		fputs ("m4_changequote`'m4_dnl\n", ਮੰਜ਼ਿਲ_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", ਮੰਜ਼ਿਲ_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", ਮੰਜ਼ਿਲ_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", ਮੰਜ਼ਿਲ_h);
		fprintf (ਮੰਜ਼ਿਲ_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != ਨਿਰਾ ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, ਮੰਜ਼ਿਲ_c);
	fputs ("m4_changecom`'m4_dnl\n", ਮੰਜ਼ਿਲ_c);
	fputs ("m4_changequote`'m4_dnl\n", ਮੰਜ਼ਿਲ_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", ਮੰਜ਼ਿਲ_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", ਮੰਜ਼ਿਲ_c);
	fprintf (ਮੰਜ਼ਿਲ_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != ਨਿਰਾ ? env.outfilename : "<stdout>");

	ਜਦੋਂ (fgets (buf, ਆਕਾਰ buf, stdin)) {
		fputs (buf, ਮੰਜ਼ਿਲ_c);
		ਜੇ (write_ਸਿਰਲੇਖ)
			fputs (buf, ਮੰਜ਼ਿਲ_h);
	}

	ਜੇ (write_ਸਿਰਲੇਖ) {
		fprintf (ਮੰਜ਼ਿਲ_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		ਜੇ (ctrl.gen_ਸਤਰ_dirs)
			ਸਤਰ_directive_ਬਾਹਰਲਾ (ਮੰਜ਼ਿਲ_h, ਨਿਰਾ, 4000);
		fflush (ਮੰਜ਼ਿਲ_h);
		ਜੇ (ferror (ਮੰਜ਼ਿਲ_h))
			lerr (_("error writing output file %s"),
				(ਅੱਖਰ *) chain->extra);

		ਨਹੀਂਤਾਂ ਜੇ (fclose (ਮੰਜ਼ਿਲ_h))
			lerr (_("error closing output file %s"),
				(ਅੱਖਰ *) chain->extra);
	}

	fflush (ਮੰਜ਼ਿਲ_c);
	ਜੇ (ferror (ਮੰਜ਼ਿਲ_c))
		lerr (_("error writing output file %s"),
			env.outfilename != ਨਿਰਾ ? env.outfilename : "<stdout>");

	ਨਹੀਂਤਾਂ ਜੇ (fclose (ਮੰਜ਼ਿਲ_c))
		lerr (_("error closing output file %s"),
			env.outfilename != ਨਿਰਾ ? env.outfilename : "<stdout>");

	ਜਦੋਂ (wait (0) > 0) ;

	FLEX_EXIT (0);
	ਵਾਪਸ 0;
}

ਸਥਿਰ bool is_blank_ਸਤਰ (ਅਚਲ ਅੱਖਰ *str)
{
	ਜਦੋਂ (ਖਾਲੀ_ਥਾਂ_ਹੈ(*str))
		str++;
	ਵਾਪਸ (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
ਪੂਰਨ filter_fix_linedirs (ਬਣਤਰ filter *chain)
{
	ਅੱਖਰ   buf[4096];
	ਅਚਲ ਅੱਖਰ *cp;
	ਅਚਲ size_t readsz = ਆਕਾਰ buf;
	ਪੂਰਨ     lineno = 1;
	bool    ਵਿੱਚ_gen = true;	/* in generated code */
	bool    ਆਖਰੀ_was_blank = false;

	ਜੇ (!chain)
		ਵਾਪਸ 0;

	ਜਦੋਂ (fgets (buf, (ਪੂਰਨ) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		ਜੇ (ctrl.traceline_re != ਨਿਰਾ &&
		    ctrl.traceline_template != ਨਿਰਾ &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			ਅੱਖਰ   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			ਜੇ (strcmp (fname,
				env.outfilename != ਨਿਰਾ ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != ਨਿਰਾ ? env.headerfilename : "<stdout>")
					== 0) {

				ਅੱਖਰ    *s1, *s2;
				ਅੱਖਰ	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				ਜਦੋਂ ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					ਜੇ (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					ਜੇ (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				ਵਿੱਚ_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", ਆਕਾਰ(buf)-1);
			}
			ਨਹੀਂਤਾਂ {
				/* it's a #line directive for code we didn't write */
				ਵਿੱਚ_gen = false;
			}

			ਮੁਕਤ (fname);
			ਆਖਰੀ_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		ਨਹੀਂਤਾਂ ਜੇ (ਵਿੱਚ_gen && is_blank_ਸਤਰ(buf)) {
			ਜੇ (ਆਖਰੀ_was_blank)
				ਜਾਰੀ;
			ਨਹੀਂਤਾਂ
				ਆਖਰੀ_was_blank = true;
		}

		ਨਹੀਂਤਾਂ {
			/* it's a line of normal, non-empty code. */
			ਆਖਰੀ_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	ਜੇ (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != ਨਿਰਾ ? env.outfilename : "<stdout>");

	ਨਹੀਂਤਾਂ ਜੇ (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != ਨਿਰਾ ? env.outfilename : "<stdout>");

	ਵਾਪਸ 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
