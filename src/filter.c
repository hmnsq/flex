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

#ଅନ୍ତର୍ଭାଵ "flexdef.h"
ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
ସଂରଚନା filter *output_chain = ଖାଲି;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
ସଂରଚନା filter *filter_create_ext (ସଂରଚନା filter *chain, ଅଚଳ ଅକ୍ଷର *cmd,
				  ...)
{
	ସଂରଚନା filter *f;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     max_args;
	ଅଚଳ ଅକ୍ଷର *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(ଆକାର(ସଂରଚନା filter), 1);
	ଯଦି (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = ଖାଲି;
	f->extra = ଖାଲି;
	f->next = ଖାଲି;
	f->argc = 0;

	ଯଦି (chain != ଖାଲି) {
		/* append f to end of chain */
		ଯେତେବେଳେ (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(ଆକାର(ଅକ୍ଷର *) * (size_t) (max_args + 1));
	ଯଦି (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	ଯେତେବେଳେ ((s = va_arg (ap, ଅଚଳ ଅକ୍ଷର *)) != ଖାଲି) {
		ଯଦି (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, ଆକାର(ଅକ୍ଷର*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = ଖାଲି;

	va_end (ap);
	ଫେରନ୍ତୁ f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
ସଂରଚନା filter *filter_create_int (ସଂରଚନା filter *chain,
				  ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*filter_func) (ସଂରଚନା filter *),
				  ଶୂନ୍ୟ *extra)
{
	ସଂରଚନା filter *f;

	/* allocate and initialize new filter */
	f = calloc(ଆକାର(ସଂରଚନା filter), 1);
	ଯଦି (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = ଖାଲି;
	f->argc = 0;
	f->argv = ଖାଲି;

	f->filter_func = filter_func;
	f->extra = extra;

	ଯଦି (chain != ଖାଲି) {
		/* append f to end of chain */
		ଯେତେବେଳେ (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	ଫେରନ୍ତୁ f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (ସଂରଚନା filter * chain)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	ଯଦି (chain)
		filter_apply_chain (chain->next);
	ଅନ୍ୟଥା
		ଫେରନ୍ତୁ true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	ଯଦି (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	ଯଦି ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	ଯଦି (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		ଯଦି (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(ଶୂନ୍ୟ)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		ଯଦି (chain->filter_func) {
			ପୂର୍ଣ୍ଣସଂଖ୍ୟା     r;

			ଯଦି ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		ଅନ୍ୟଥା {
			execvp (chain->argv[0],
				(ଅକ୍ଷର **ଅଚଳ) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	ଯଦି (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	ଫେରନ୍ତୁ true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା filter_truncate (ସଂରଚନା filter *chain, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_len)
{
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     len = 1;

	ଯଦି (!chain)
		ଫେରନ୍ତୁ 0;

	ଯେତେବେଳେ (chain->next && len < max_len) {
		chain = chain->next;
		++len;
	}

	chain->next = ଖାଲି;
	ଫେରନ୍ତୁ len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା filter_tee_header (ସଂରଚନା filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	ଅକ୍ଷର    buf[512];
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     to_cfd = -1;
	FILE   *to_c = ଖାଲି, *to_h = ଖାଲି;
	bool    write_header;

	write_header = (chain->extra != ଖାଲି);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	ଯଦି ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	ଯଦି (write_header) {
		ଯଦି (freopen ((ଅକ୍ଷର *) chain->extra, "w", stdout) == ଖାଲି)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	ଯଦି (write_header) {
		fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != ଖାଲି ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != ଖାଲି ? env.outfilename : "<stdout>");

	ଯେତେବେଳେ (fgets (buf, ଆକାର buf, stdin)) {
		fputs (buf, to_c);
		ଯଦି (write_header)
			fputs (buf, to_h);
	}

	ଯଦି (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		ଯଦି (ctrl.gen_ଧାଡ଼ି_dirs)
			ଧାଡ଼ି_directive_out (to_h, ଖାଲି, 4000);
		fflush (to_h);
		ଯଦି (ferror (to_h))
			lerr (_("error writing output file %s"),
				(ଅକ୍ଷର *) chain->extra);

		ଅନ୍ୟଥା ଯଦି (fclose (to_h))
			lerr (_("error closing output file %s"),
				(ଅକ୍ଷର *) chain->extra);
	}

	fflush (to_c);
	ଯଦି (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != ଖାଲି ? env.outfilename : "<stdout>");

	ଅନ୍ୟଥା ଯଦି (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != ଖାଲି ? env.outfilename : "<stdout>");

	ଯେତେବେଳେ (wait (0) > 0) ;

	FLEX_EXIT (0);
	ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର bool is_blank_ଧାଡ଼ି (ଅଚଳ ଅକ୍ଷର *str)
{
	ଯେତେବେଳେ (isspace(*str))
		str++;
	ଫେରନ୍ତୁ (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା filter_fix_linedirs (ସଂରଚନା filter *chain)
{
	ଅକ୍ଷର   buf[4096];
	ଅଚଳ ଅକ୍ଷର *cp;
	ଅଚଳ size_t readsz = ଆକାର buf;
	ପୂର୍ଣ୍ଣସଂଖ୍ୟା     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	ଯଦି (!chain)
		ଫେରନ୍ତୁ 0;

	ଯେତେବେଳେ (fgets (buf, (ପୂର୍ଣ୍ଣସଂଖ୍ୟା) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		ଯଦି (ctrl.traceline_re != ଖାଲି &&
		    ctrl.traceline_template != ଖାଲି &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			ଅକ୍ଷର   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			ଯଦି (strcmp (fname,
				env.outfilename != ଖାଲି ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != ଖାଲି ? env.headerfilename : "<stdout>")
					== 0) {

				ଅକ୍ଷର    *s1, *s2;
				ଅକ୍ଷର	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				ଯେତେବେଳେ ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					ଯଦି (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					ଯଦି (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", ଆକାର(buf)-1);
			}
			ଅନ୍ୟଥା {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			ମୁକ୍ତ (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		ଅନ୍ୟଥା ଯଦି (in_gen && is_blank_ଧାଡ଼ି(buf)) {
			ଯଦି (last_was_blank)
				ଜାରି;
			ଅନ୍ୟଥା
				last_was_blank = true;
		}

		ଅନ୍ୟଥା {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	ଯଦି (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != ଖାଲି ? env.outfilename : "<stdout>");

	ଅନ୍ୟଥା ଯଦି (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != ଖାଲି ? env.outfilename : "<stdout>");

	ଫେରନ୍ତୁ 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
