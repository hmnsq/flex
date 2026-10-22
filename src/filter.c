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

#شامل "flexdef.h"
ایستا ثابت نویسه * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
ساختار filter *output_chain = پوچ;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
ساختار filter *filter_create_ext (ساختار filter *chain, ثابت نویسه *cmd,
				  ...)
{
	ساختار filter *f;
	صحیح     max_args;
	ثابت نویسه *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(اندازه(ساختار filter), 1);
	اگر (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = پوچ;
	f->extra = پوچ;
	f->next = پوچ;
	f->argc = 0;

	اگر (chain != پوچ) {
		/* append f to end of chain */
		وقتی (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(اندازه(نویسه *) * (size_t) (max_args + 1));
	اگر (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	وقتی ((s = va_arg (ap, ثابت نویسه *)) != پوچ) {
		اگر (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, اندازه(نویسه*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = پوچ;

	va_end (ap);
	بازگشت f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
ساختار filter *filter_create_int (ساختار filter *chain,
				  صحیح (*filter_func) (ساختار filter *),
				  تهی *extra)
{
	ساختار filter *f;

	/* allocate and initialize new filter */
	f = calloc(اندازه(ساختار filter), 1);
	اگر (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = پوچ;
	f->argc = 0;
	f->argv = پوچ;

	f->filter_func = filter_func;
	f->extra = extra;

	اگر (chain != پوچ) {
		/* append f to end of chain */
		وقتی (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	بازگشت f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (ساختار filter * chain)
{
	صحیح     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	اگر (chain)
		filter_apply_chain (chain->next);
	وگرنه
		بازگشت true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	اگر (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	اگر ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	اگر (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		اگر (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(تهی)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		اگر (chain->filter_func) {
			صحیح     r;

			اگر ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		وگرنه {
			execvp (chain->argv[0],
				(نویسه **ثابت) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	اگر (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	بازگشت true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
صحیح filter_truncate (ساختار filter *chain, صحیح max_len)
{
	صحیح     len = 1;

	اگر (!chain)
		بازگشت 0;

	وقتی (chain->next && len < max_len) {
		chain = chain->next;
		++len;
	}

	chain->next = پوچ;
	بازگشت len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
صحیح filter_tee_header (ساختار filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	نویسه    buf[512];
	صحیح     to_cfd = -1;
	FILE   *to_c = پوچ, *to_h = پوچ;
	bool    write_header;

	write_header = (chain->extra != پوچ);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	اگر ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	اگر (write_header) {
		اگر (freopen ((نویسه *) chain->extra, "w", stdout) == پوچ)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	اگر (write_header) {
		fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != پوچ ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != پوچ ? env.outfilename : "<stdout>");

	وقتی (fgets (buf, اندازه buf, stdin)) {
		fputs (buf, to_c);
		اگر (write_header)
			fputs (buf, to_h);
	}

	اگر (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		اگر (ctrl.gen_سطر_dirs)
			سطر_directive_out (to_h, پوچ, 4000);
		fflush (to_h);
		اگر (ferror (to_h))
			lerr (_("error writing output file %s"),
				(نویسه *) chain->extra);

		وگرنه اگر (fclose (to_h))
			lerr (_("error closing output file %s"),
				(نویسه *) chain->extra);
	}

	fflush (to_c);
	اگر (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != پوچ ? env.outfilename : "<stdout>");

	وگرنه اگر (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != پوچ ? env.outfilename : "<stdout>");

	وقتی (wait (0) > 0) ;

	FLEX_EXIT (0);
	بازگشت 0;
}

ایستا bool is_blank_سطر (ثابت نویسه *str)
{
	وقتی (isspace(*str))
		str++;
	بازگشت (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
صحیح filter_fix_linedirs (ساختار filter *chain)
{
	نویسه   buf[4096];
	ثابت نویسه *cp;
	ثابت size_t readsz = اندازه buf;
	صحیح     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	اگر (!chain)
		بازگشت 0;

	وقتی (fgets (buf, (صحیح) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		اگر (ctrl.traceline_re != پوچ &&
		    ctrl.traceline_template != پوچ &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			نویسه   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			اگر (strcmp (fname,
				env.outfilename != پوچ ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != پوچ ? env.headerfilename : "<stdout>")
					== 0) {

				نویسه    *s1, *s2;
				نویسه	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				وقتی ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					اگر (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					اگر (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", اندازه(buf)-1);
			}
			وگرنه {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			آزاد (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		وگرنه اگر (in_gen && is_blank_سطر(buf)) {
			اگر (last_was_blank)
				ادامه;
			وگرنه
				last_was_blank = true;
		}

		وگرنه {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	اگر (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != پوچ ? env.outfilename : "<stdout>");

	وگرنه اگر (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != پوچ ? env.outfilename : "<stdout>");

	بازگشت 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
