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

#അന്തര്ഭാവ "flexdef.h"
സ്ഥിതം സ്ഥിരം അക്ഷരം * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
ഘടന filter *output_chain = ശൂന്യ;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
ഘടന filter *filter_create_ext (ഘടന filter *chain, സ്ഥിരം അക്ഷരം *cmd,
				  ...)
{
	ഘടന filter *f;
	പൂർണ്ണസംഖ്യ     max_args;
	സ്ഥിരം അക്ഷരം *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(വലുപ്പം(ഘടന filter), 1);
	എങ്കിൽ (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = ശൂന്യ;
	f->extra = ശൂന്യ;
	f->next = ശൂന്യ;
	f->argc = 0;

	എങ്കിൽ (chain != ശൂന്യ) {
		/* append f to end of chain */
		ആകുമ്പോൾ (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(വലുപ്പം(അക്ഷരം *) * (size_t) (max_args + 1));
	എങ്കിൽ (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	ആകുമ്പോൾ ((s = va_arg (ap, സ്ഥിരം അക്ഷരം *)) != ശൂന്യ) {
		എങ്കിൽ (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, വലുപ്പം(അക്ഷരം*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = ശൂന്യ;

	va_end (ap);
	തിരികെ f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
ഘടന filter *filter_create_int (ഘടന filter *chain,
				  പൂർണ്ണസംഖ്യ (*filter_func) (ഘടന filter *),
				  ശൂന്യം *extra)
{
	ഘടന filter *f;

	/* allocate and initialize new filter */
	f = calloc(വലുപ്പം(ഘടന filter), 1);
	എങ്കിൽ (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = ശൂന്യ;
	f->argc = 0;
	f->argv = ശൂന്യ;

	f->filter_func = filter_func;
	f->extra = extra;

	എങ്കിൽ (chain != ശൂന്യ) {
		/* append f to end of chain */
		ആകുമ്പോൾ (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	തിരികെ f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (ഘടന filter * chain)
{
	പൂർണ്ണസംഖ്യ     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	എങ്കിൽ (chain)
		filter_apply_chain (chain->next);
	അല്ലെങ്കിൽ
		തിരികെ true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	എങ്കിൽ (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	എങ്കിൽ ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	എങ്കിൽ (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		എങ്കിൽ (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(ശൂന്യം)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		എങ്കിൽ (chain->filter_func) {
			പൂർണ്ണസംഖ്യ     r;

			എങ്കിൽ ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		അല്ലെങ്കിൽ {
			execvp (chain->argv[0],
				(അക്ഷരം **സ്ഥിരം) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	എങ്കിൽ (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	തിരികെ true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
പൂർണ്ണസംഖ്യ filter_truncate (ഘടന filter *chain, പൂർണ്ണസംഖ്യ max_len)
{
	പൂർണ്ണസംഖ്യ     len = 1;

	എങ്കിൽ (!chain)
		തിരികെ 0;

	ആകുമ്പോൾ (chain->next && len < max_len) {
		chain = chain->next;
		++len;
	}

	chain->next = ശൂന്യ;
	തിരികെ len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
പൂർണ്ണസംഖ്യ filter_tee_header (ഘടന filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	അക്ഷരം    buf[512];
	പൂർണ്ണസംഖ്യ     to_cfd = -1;
	FILE   *to_c = ശൂന്യ, *to_h = ശൂന്യ;
	bool    write_header;

	write_header = (chain->extra != ശൂന്യ);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	എങ്കിൽ ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	എങ്കിൽ (write_header) {
		എങ്കിൽ (freopen ((അക്ഷരം *) chain->extra, "w", stdout) == ശൂന്യ)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	എങ്കിൽ (write_header) {
		fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != ശൂന്യ ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != ശൂന്യ ? env.outfilename : "<stdout>");

	ആകുമ്പോൾ (fgets (buf, വലുപ്പം buf, stdin)) {
		fputs (buf, to_c);
		എങ്കിൽ (write_header)
			fputs (buf, to_h);
	}

	എങ്കിൽ (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		എങ്കിൽ (ctrl.gen_വരി_dirs)
			വരി_directive_out (to_h, ശൂന്യ, 4000);
		fflush (to_h);
		എങ്കിൽ (ferror (to_h))
			lerr (_("error writing output file %s"),
				(അക്ഷരം *) chain->extra);

		അല്ലെങ്കിൽ എങ്കിൽ (fclose (to_h))
			lerr (_("error closing output file %s"),
				(അക്ഷരം *) chain->extra);
	}

	fflush (to_c);
	എങ്കിൽ (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != ശൂന്യ ? env.outfilename : "<stdout>");

	അല്ലെങ്കിൽ എങ്കിൽ (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != ശൂന്യ ? env.outfilename : "<stdout>");

	ആകുമ്പോൾ (wait (0) > 0) ;

	FLEX_EXIT (0);
	തിരികെ 0;
}

സ്ഥിതം bool is_blank_വരി (സ്ഥിരം അക്ഷരം *str)
{
	ആകുമ്പോൾ (isspace(*str))
		str++;
	തിരികെ (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
പൂർണ്ണസംഖ്യ filter_fix_linedirs (ഘടന filter *chain)
{
	അക്ഷരം   buf[4096];
	സ്ഥിരം അക്ഷരം *cp;
	സ്ഥിരം size_t readsz = വലുപ്പം buf;
	പൂർണ്ണസംഖ്യ     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	എങ്കിൽ (!chain)
		തിരികെ 0;

	ആകുമ്പോൾ (fgets (buf, (പൂർണ്ണസംഖ്യ) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		എങ്കിൽ (ctrl.traceline_re != ശൂന്യ &&
		    ctrl.traceline_template != ശൂന്യ &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			അക്ഷരം   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			എങ്കിൽ (strcmp (fname,
				env.outfilename != ശൂന്യ ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != ശൂന്യ ? env.headerfilename : "<stdout>")
					== 0) {

				അക്ഷരം    *s1, *s2;
				അക്ഷരം	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				ആകുമ്പോൾ ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					എങ്കിൽ (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					എങ്കിൽ (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", വലുപ്പം(buf)-1);
			}
			അല്ലെങ്കിൽ {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			സ്വതന്ത്രം (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		അല്ലെങ്കിൽ എങ്കിൽ (in_gen && is_blank_വരി(buf)) {
			എങ്കിൽ (last_was_blank)
				തുടരുക;
			അല്ലെങ്കിൽ
				last_was_blank = true;
		}

		അല്ലെങ്കിൽ {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	എങ്കിൽ (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != ശൂന്യ ? env.outfilename : "<stdout>");

	അല്ലെങ്കിൽ എങ്കിൽ (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != ശൂന്യ ? env.outfilename : "<stdout>");

	തിരികെ 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
