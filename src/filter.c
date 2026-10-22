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

#अन्तर्भाव "flexdef.h"
स्थिर ध्रुव वर्ण * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
संरचना filter *output_chain = रिक्त;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
संरचना filter *filter_create_ext (संरचना filter *chain, ध्रुव वर्ण *cmd,
				  ...)
{
	संरचना filter *f;
	पूर्णाङ्क     max_args;
	ध्रुव वर्ण *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(परिमाण(संरचना filter), 1);
	जइ (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = रिक्त;
	f->extra = रिक्त;
	f->next = रिक्त;
	f->argc = 0;

	जइ (chain != रिक्त) {
		/* append f to end of chain */
		जाव (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(परिमाण(वर्ण *) * (size_t) (max_args + 1));
	जइ (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	जाव ((s = va_arg (ap, ध्रुव वर्ण *)) != रिक्त) {
		जइ (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, परिमाण(वर्ण*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = रिक्त;

	va_end (ap);
	प्रत्यागम f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
संरचना filter *filter_create_int (संरचना filter *chain,
				  पूर्णाङ्क (*filter_func) (संरचना filter *),
				  शून्य *extra)
{
	संरचना filter *f;

	/* allocate and initialize new filter */
	f = calloc(परिमाण(संरचना filter), 1);
	जइ (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = रिक्त;
	f->argc = 0;
	f->argv = रिक्त;

	f->filter_func = filter_func;
	f->extra = extra;

	जइ (chain != रिक्त) {
		/* append f to end of chain */
		जाव (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	प्रत्यागम f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (संरचना filter * chain)
{
	पूर्णाङ्क     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	जइ (chain)
		filter_apply_chain (chain->next);
	अण्णहा
		प्रत्यागम true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	जइ (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	जइ ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	जइ (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		जइ (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(शून्य)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		जइ (chain->filter_func) {
			पूर्णाङ्क     r;

			जइ ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		अण्णहा {
			execvp (chain->argv[0],
				(वर्ण **ध्रुव) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	जइ (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	प्रत्यागम true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
पूर्णाङ्क filter_truncate (संरचना filter *chain, पूर्णाङ्क max_len)
{
	पूर्णाङ्क     len = 1;

	जइ (!chain)
		प्रत्यागम 0;

	जाव (chain->next && len < max_len) {
		chain = chain->next;
		++len;
	}

	chain->next = रिक्त;
	प्रत्यागम len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
पूर्णाङ्क filter_tee_header (संरचना filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	वर्ण    buf[512];
	पूर्णाङ्क     to_cfd = -1;
	FILE   *to_c = रिक्त, *to_h = रिक्त;
	bool    write_header;

	write_header = (chain->extra != रिक्त);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	जइ ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	जइ (write_header) {
		जइ (freopen ((वर्ण *) chain->extra, "w", stdout) == रिक्त)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	जइ (write_header) {
		fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != रिक्त ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != रिक्त ? env.outfilename : "<stdout>");

	जाव (fgets (buf, परिमाण buf, stdin)) {
		fputs (buf, to_c);
		जइ (write_header)
			fputs (buf, to_h);
	}

	जइ (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		जइ (ctrl.gen_पङ्क्तिः_dirs)
			पङ्क्तिः_directive_out (to_h, रिक्त, 4000);
		fflush (to_h);
		जइ (ferror (to_h))
			lerr (_("error writing output file %s"),
				(वर्ण *) chain->extra);

		अण्णहा जइ (fclose (to_h))
			lerr (_("error closing output file %s"),
				(वर्ण *) chain->extra);
	}

	fflush (to_c);
	जइ (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != रिक्त ? env.outfilename : "<stdout>");

	अण्णहा जइ (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != रिक्त ? env.outfilename : "<stdout>");

	जाव (wait (0) > 0) ;

	FLEX_EXIT (0);
	प्रत्यागम 0;
}

स्थिर bool is_blank_पङ्क्तिः (ध्रुव वर्ण *str)
{
	जाव (isspace(*str))
		str++;
	प्रत्यागम (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
पूर्णाङ्क filter_fix_linedirs (संरचना filter *chain)
{
	वर्ण   buf[4096];
	ध्रुव वर्ण *cp;
	ध्रुव size_t readsz = परिमाण buf;
	पूर्णाङ्क     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	जइ (!chain)
		प्रत्यागम 0;

	जाव (fgets (buf, (पूर्णाङ्क) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		जइ (ctrl.traceline_re != रिक्त &&
		    ctrl.traceline_template != रिक्त &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			वर्ण   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			जइ (strcmp (fname,
				env.outfilename != रिक्त ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != रिक्त ? env.headerfilename : "<stdout>")
					== 0) {

				वर्ण    *s1, *s2;
				वर्ण	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				जाव ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					जइ (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					जइ (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", परिमाण(buf)-1);
			}
			अण्णहा {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			मुक्त (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		अण्णहा जइ (in_gen && is_blank_पङ्क्तिः(buf)) {
			जइ (last_was_blank)
				अनुवर्त;
			अण्णहा
				last_was_blank = true;
		}

		अण्णहा {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	जइ (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != रिक्त ? env.outfilename : "<stdout>");

	अण्णहा जइ (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != रिक्त ? env.outfilename : "<stdout>");

	प्रत्यागम 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
