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

#ضمن "flexdef.h"
ساكن ثابت حرف * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
بنية filter *output_chain = عدم;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
بنية filter *filter_create_ext (بنية filter *chain, ثابت حرف *cmd,
				  ...)
{
	بنية filter *f;
	صحيح     max_args;
	ثابت حرف *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(حجم(بنية filter), 1);
	אם (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = عدم;
	f->extra = عدم;
	f->next = عدم;
	f->argc = 0;

	אם (chain != عدم) {
		/* append f to end of chain */
		כלעוד (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(حجم(حرف *) * (size_t) (max_args + 1));
	אם (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	כלעוד ((s = va_arg (ap, ثابت حرف *)) != عدم) {
		אם (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, حجم(حرف*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = عدم;

	va_end (ap);
	החזר f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
بنية filter *filter_create_int (بنية filter *chain,
				  صحيح (*filter_func) (بنية filter *),
				  فراغ *extra)
{
	بنية filter *f;

	/* allocate and initialize new filter */
	f = calloc(حجم(بنية filter), 1);
	אם (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = عدم;
	f->argc = 0;
	f->argv = عدم;

	f->filter_func = filter_func;
	f->extra = extra;

	אם (chain != عدم) {
		/* append f to end of chain */
		כלעוד (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	החזר f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (بنية filter * chain)
{
	صحيح     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	אם (chain)
		filter_apply_chain (chain->next);
	אחרת
		החזר true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	אם (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	אם ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	אם (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		אם (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(فراغ)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		אם (chain->filter_func) {
			صحيح     r;

			אם ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		אחרת {
			execvp (chain->argv[0],
				(حرف **ثابت) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	אם (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	החזר true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
صحيح filter_truncate (بنية filter *chain, صحيح max_len)
{
	صحيح     len = 1;

	אם (!chain)
		החזר 0;

	כלעוד (chain->next && len < max_len) {
		chain = chain->next;
		++len;
	}

	chain->next = عدم;
	החזר len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
صحيح filter_tee_header (بنية filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	حرف    buf[512];
	صحيح     to_cfd = -1;
	FILE   *to_c = عدم, *to_h = عدم;
	bool    write_header;

	write_header = (chain->extra != عدم);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	אם ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	אם (write_header) {
		אם (freopen ((حرف *) chain->extra, "w", stdout) == عدم)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	אם (write_header) {
		fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != عدم ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != عدم ? env.outfilename : "<stdout>");

	כלעוד (fgets (buf, حجم buf, stdin)) {
		fputs (buf, to_c);
		אם (write_header)
			fputs (buf, to_h);
	}

	אם (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		אם (ctrl.gen_line_dirs)
			line_directive_out (to_h, عدم, 4000);
		fflush (to_h);
		אם (ferror (to_h))
			lerr (_("error writing output file %s"),
				(حرف *) chain->extra);

		אחרת אם (fclose (to_h))
			lerr (_("error closing output file %s"),
				(حرف *) chain->extra);
	}

	fflush (to_c);
	אם (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != عدم ? env.outfilename : "<stdout>");

	אחרת אם (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != عدم ? env.outfilename : "<stdout>");

	כלעוד (wait (0) > 0) ;

	FLEX_EXIT (0);
	החזר 0;
}

ساكن bool is_blank_line (ثابت حرف *str)
{
	כלעוד (isspace(*str))
		str++;
	החזר (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
صحيح filter_fix_linedirs (بنية filter *chain)
{
	حرف   buf[4096];
	ثابت حرف *cp;
	ثابت size_t readsz = حجم buf;
	صحيح     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	אם (!chain)
		החזר 0;

	כלעוד (fgets (buf, (صحيح) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		אם (ctrl.traceline_re != عدم &&
		    ctrl.traceline_template != عدم &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			حرف   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			אם (strcmp (fname,
				env.outfilename != عدم ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != عدم ? env.headerfilename : "<stdout>")
					== 0) {

				حرف    *s1, *s2;
				حرف	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				כלעוד ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					אם (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					אם (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", حجم(buf)-1);
			}
			אחרת {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			حرر (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		אחרת אם (in_gen && is_blank_line(buf)) {
			אם (last_was_blank)
				استمر;
			אחרת
				last_was_blank = true;
		}

		אחרת {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	אם (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != عدم ? env.outfilename : "<stdout>");

	אחרת אם (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != عدم ? env.outfilename : "<stdout>");

	החזר 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
