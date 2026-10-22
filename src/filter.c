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

#அந்தர்பாவ "flexdef.h"
நிலையான மாறிலி எழுத்து * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
கட்டமைப்பு filter *output_chain = வெற்று;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
கட்டமைப்பு filter *filter_create_ext (கட்டமைப்பு filter *chain, மாறிலி எழுத்து *cmd,
				  ...)
{
	கட்டமைப்பு filter *f;
	முழு     max_args;
	மாறிலி எழுத்து *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(அளவு(கட்டமைப்பு filter), 1);
	எனில் (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = வெற்று;
	f->extra = வெற்று;
	f->next = வெற்று;
	f->argc = 0;

	எனில் (chain != வெற்று) {
		/* append f to end of chain */
		போது (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(அளவு(எழுத்து *) * (size_t) (max_args + 1));
	எனில் (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	போது ((s = va_arg (ap, மாறிலி எழுத்து *)) != வெற்று) {
		எனில் (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, அளவு(எழுத்து*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = வெற்று;

	va_end (ap);
	திரும்பு f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
கட்டமைப்பு filter *filter_create_int (கட்டமைப்பு filter *chain,
				  முழு (*filter_func) (கட்டமைப்பு filter *),
				  வெறுமை *extra)
{
	கட்டமைப்பு filter *f;

	/* allocate and initialize new filter */
	f = calloc(அளவு(கட்டமைப்பு filter), 1);
	எனில் (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = வெற்று;
	f->argc = 0;
	f->argv = வெற்று;

	f->filter_func = filter_func;
	f->extra = extra;

	எனில் (chain != வெற்று) {
		/* append f to end of chain */
		போது (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	திரும்பு f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (கட்டமைப்பு filter * chain)
{
	முழு     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	எனில் (chain)
		filter_apply_chain (chain->next);
	இல்லையெனில்
		திரும்பு true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	எனில் (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	எனில் ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	எனில் (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		எனில் (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(வெறுமை)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		எனில் (chain->filter_func) {
			முழு     r;

			எனில் ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		இல்லையெனில் {
			execvp (chain->argv[0],
				(எழுத்து **மாறிலி) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	எனில் (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	திரும்பு true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
முழு filter_truncate (கட்டமைப்பு filter *chain, முழு max_len)
{
	முழு     len = 1;

	எனில் (!chain)
		திரும்பு 0;

	போது (chain->next && len < max_len) {
		chain = chain->next;
		++len;
	}

	chain->next = வெற்று;
	திரும்பு len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
முழு filter_tee_header (கட்டமைப்பு filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	எழுத்து    buf[512];
	முழு     to_cfd = -1;
	FILE   *to_c = வெற்று, *to_h = வெற்று;
	bool    write_header;

	write_header = (chain->extra != வெற்று);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	எனில் ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	எனில் (write_header) {
		எனில் (freopen ((எழுத்து *) chain->extra, "w", stdout) == வெற்று)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	எனில் (write_header) {
		fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != வெற்று ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != வெற்று ? env.outfilename : "<stdout>");

	போது (fgets (buf, அளவு buf, stdin)) {
		fputs (buf, to_c);
		எனில் (write_header)
			fputs (buf, to_h);
	}

	எனில் (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		எனில் (ctrl.gen_வரி_dirs)
			வரி_directive_out (to_h, வெற்று, 4000);
		fflush (to_h);
		எனில் (ferror (to_h))
			lerr (_("error writing output file %s"),
				(எழுத்து *) chain->extra);

		இல்லையெனில் எனில் (fclose (to_h))
			lerr (_("error closing output file %s"),
				(எழுத்து *) chain->extra);
	}

	fflush (to_c);
	எனில் (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != வெற்று ? env.outfilename : "<stdout>");

	இல்லையெனில் எனில் (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != வெற்று ? env.outfilename : "<stdout>");

	போது (wait (0) > 0) ;

	FLEX_EXIT (0);
	திரும்பு 0;
}

நிலையான bool is_blank_வரி (மாறிலி எழுத்து *str)
{
	போது (isspace(*str))
		str++;
	திரும்பு (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
முழு filter_fix_linedirs (கட்டமைப்பு filter *chain)
{
	எழுத்து   buf[4096];
	மாறிலி எழுத்து *cp;
	மாறிலி size_t readsz = அளவு buf;
	முழு     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	எனில் (!chain)
		திரும்பு 0;

	போது (fgets (buf, (முழு) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		எனில் (ctrl.traceline_re != வெற்று &&
		    ctrl.traceline_template != வெற்று &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			எழுத்து   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			எனில் (strcmp (fname,
				env.outfilename != வெற்று ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != வெற்று ? env.headerfilename : "<stdout>")
					== 0) {

				எழுத்து    *s1, *s2;
				எழுத்து	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				போது ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					எனில் (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					எனில் (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", அளவு(buf)-1);
			}
			இல்லையெனில் {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			விடுவி (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		இல்லையெனில் எனில் (in_gen && is_blank_வரி(buf)) {
			எனில் (last_was_blank)
				தொடர்;
			இல்லையெனில்
				last_was_blank = true;
		}

		இல்லையெனில் {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	எனில் (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != வெற்று ? env.outfilename : "<stdout>");

	இல்லையெனில் எனில் (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != வெற்று ? env.outfilename : "<stdout>");

	திரும்பு 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
