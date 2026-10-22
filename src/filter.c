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

#অন্তর্ভাব "flexdef.h"
স্থির ধ্রুবক অক্ষর * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
কাঠামো filter *output_chain = ফাঁকা;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
কাঠামো filter *filter_create_ext (কাঠামো filter *chain, ধ্রুবক অক্ষর *cmd,
				  ...)
{
	কাঠামো filter *f;
	পূর্ণসংখ্যা     max_args;
	ধ্রুবক অক্ষর *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(আকার(কাঠামো filter), 1);
	যদি (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = ফাঁকা;
	f->extra = ফাঁকা;
	f->পরবর্তী = ফাঁকা;
	f->argc = 0;

	যদি (chain != ফাঁকা) {
		/* append f to end of chain */
		যখন (chain->পরবর্তী)
			chain = chain->পরবর্তী;
		chain->পরবর্তী = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(আকার(অক্ষর *) * (size_t) (max_args + 1));
	যদি (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	যখন ((s = va_arg (ap, ধ্রুবক অক্ষর *)) != ফাঁকা) {
		যদি (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, আকার(অক্ষর*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = ফাঁকা;

	va_end (ap);
	ফেরত f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
কাঠামো filter *filter_create_int (কাঠামো filter *chain,
				  পূর্ণসংখ্যা (*filter_func) (কাঠামো filter *),
				  শূন্য *extra)
{
	কাঠামো filter *f;

	/* allocate and initialize new filter */
	f = calloc(আকার(কাঠামো filter), 1);
	যদি (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->পরবর্তী = ফাঁকা;
	f->argc = 0;
	f->argv = ফাঁকা;

	f->filter_func = filter_func;
	f->extra = extra;

	যদি (chain != ফাঁকা) {
		/* append f to end of chain */
		যখন (chain->পরবর্তী)
			chain = chain->পরবর্তী;
		chain->পরবর্তী = f;
	}

	ফেরত f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (কাঠামো filter * chain)
{
	পূর্ণসংখ্যা     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	যদি (chain)
		filter_apply_chain (chain->পরবর্তী);
	অন্যথা
		ফেরত true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	যদি (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	যদি ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	যদি (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		যদি (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(শূন্য)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		যদি (chain->filter_func) {
			পূর্ণসংখ্যা     r;

			যদি ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		অন্যথা {
			execvp (chain->argv[0],
				(অক্ষর **ধ্রুবক) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	যদি (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	ফেরত true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
পূর্ণসংখ্যা filter_truncate (কাঠামো filter *chain, পূর্ণসংখ্যা max_len)
{
	পূর্ণসংখ্যা     len = 1;

	যদি (!chain)
		ফেরত 0;

	যখন (chain->পরবর্তী && len < max_len) {
		chain = chain->পরবর্তী;
		++len;
	}

	chain->পরবর্তী = ফাঁকা;
	ফেরত len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
পূর্ণসংখ্যা filter_tee_header (কাঠামো filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	অক্ষর    buf[512];
	পূর্ণসংখ্যা     to_cfd = -1;
	FILE   *to_c = ফাঁকা, *to_h = ফাঁকা;
	bool    write_header;

	write_header = (chain->extra != ফাঁকা);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	যদি ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	যদি (write_header) {
		যদি (freopen ((অক্ষর *) chain->extra, "w", stdout) == ফাঁকা)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->পরবর্তী);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	যদি (write_header) {
		fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != ফাঁকা ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != ফাঁকা ? env.outfilename : "<stdout>");

	যখন (fgets (buf, আকার buf, stdin)) {
		fputs (buf, to_c);
		যদি (write_header)
			fputs (buf, to_h);
	}

	যদি (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		যদি (ctrl.gen_সারি_dirs)
			সারি_directive_out (to_h, ফাঁকা, 4000);
		fflush (to_h);
		যদি (ferror (to_h))
			lerr (_("error writing output file %s"),
				(অক্ষর *) chain->extra);

		অন্যথা যদি (fclose (to_h))
			lerr (_("error closing output file %s"),
				(অক্ষর *) chain->extra);
	}

	fflush (to_c);
	যদি (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != ফাঁকা ? env.outfilename : "<stdout>");

	অন্যথা যদি (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != ফাঁকা ? env.outfilename : "<stdout>");

	যখন (wait (0) > 0) ;

	FLEX_EXIT (0);
	ফেরত 0;
}

স্থির bool is_blank_সারি (ধ্রুবক অক্ষর *str)
{
	যখন (isspace(*str))
		str++;
	ফেরত (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
পূর্ণসংখ্যা filter_fix_linedirs (কাঠামো filter *chain)
{
	অক্ষর   buf[4096];
	ধ্রুবক অক্ষর *cp;
	ধ্রুবক size_t readsz = আকার buf;
	পূর্ণসংখ্যা     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	যদি (!chain)
		ফেরত 0;

	যখন (fgets (buf, (পূর্ণসংখ্যা) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		যদি (ctrl.traceline_re != ফাঁকা &&
		    ctrl.traceline_template != ফাঁকা &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			অক্ষর   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			যদি (strcmp (fname,
				env.outfilename != ফাঁকা ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != ফাঁকা ? env.headerfilename : "<stdout>")
					== 0) {

				অক্ষর    *s1, *s2;
				অক্ষর	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				যখন ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					যদি (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					যদি (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", আকার(buf)-1);
			}
			অন্যথা {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			মুক্ত (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		অন্যথা যদি (in_gen && is_blank_সারি(buf)) {
			যদি (last_was_blank)
				চালু;
			অন্যথা
				last_was_blank = true;
		}

		অন্যথা {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	যদি (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != ফাঁকা ? env.outfilename : "<stdout>");

	অন্যথা যদি (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != ফাঁকা ? env.outfilename : "<stdout>");

	ফেরত 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
