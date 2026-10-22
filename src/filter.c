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

#અન્તર્ભાવ "flexdef.h"
સ્થિર અચલ અક્ષર * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
સંરચના filter *output_chain = ખાલી;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
સંરચના filter *filter_create_ext (સંરચના filter *chain, અચલ અક્ષર *cmd,
				  ...)
{
	સંરચના filter *f;
	પૂર્ણાંક     max_args;
	અચલ અક્ષર *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(કદ(સંરચના filter), 1);
	જો (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = ખાલી;
	f->extra = ખાલી;
	f->next = ખાલી;
	f->argc = 0;

	જો (chain != ખાલી) {
		/* append f to end of chain */
		જ્યારે (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(કદ(અક્ષર *) * (size_t) (max_args + 1));
	જો (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	જ્યારે ((s = va_arg (ap, અચલ અક્ષર *)) != ખાલી) {
		જો (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, કદ(અક્ષર*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = ખાલી;

	va_end (ap);
	પાછા f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
સંરચના filter *filter_create_int (સંરચના filter *chain,
				  પૂર્ણાંક (*filter_func) (સંરચના filter *),
				  શૂન્ય *extra)
{
	સંરચના filter *f;

	/* allocate and initialize new filter */
	f = calloc(કદ(સંરચના filter), 1);
	જો (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = ખાલી;
	f->argc = 0;
	f->argv = ખાલી;

	f->filter_func = filter_func;
	f->extra = extra;

	જો (chain != ખાલી) {
		/* append f to end of chain */
		જ્યારે (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	પાછા f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (સંરચના filter * chain)
{
	પૂર્ણાંક     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	જો (chain)
		filter_apply_chain (chain->next);
	નહીંતર
		પાછા true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	જો (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	જો ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	જો (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		જો (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(શૂન્ય)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		જો (chain->filter_func) {
			પૂર્ણાંક     r;

			જો ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		નહીંતર {
			execvp (chain->argv[0],
				(અક્ષર **અચલ) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	જો (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	પાછા true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
પૂર્ણાંક filter_truncate (સંરચના filter *chain, પૂર્ણાંક max_len)
{
	પૂર્ણાંક     len = 1;

	જો (!chain)
		પાછા 0;

	જ્યારે (chain->next && len < max_len) {
		chain = chain->next;
		++len;
	}

	chain->next = ખાલી;
	પાછા len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
પૂર્ણાંક filter_tee_header (સંરચના filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	અક્ષર    buf[512];
	પૂર્ણાંક     to_cfd = -1;
	FILE   *to_c = ખાલી, *to_h = ખાલી;
	bool    write_header;

	write_header = (chain->extra != ખાલી);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	જો ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	જો (write_header) {
		જો (freopen ((અક્ષર *) chain->extra, "w", stdout) == ખાલી)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	જો (write_header) {
		fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != ખાલી ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != ખાલી ? env.outfilename : "<stdout>");

	જ્યારે (fgets (buf, કદ buf, stdin)) {
		fputs (buf, to_c);
		જો (write_header)
			fputs (buf, to_h);
	}

	જો (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		જો (ctrl.gen_લીટી_dirs)
			લીટી_directive_out (to_h, ખાલી, 4000);
		fflush (to_h);
		જો (ferror (to_h))
			lerr (_("error writing output file %s"),
				(અક્ષર *) chain->extra);

		નહીંતર જો (fclose (to_h))
			lerr (_("error closing output file %s"),
				(અક્ષર *) chain->extra);
	}

	fflush (to_c);
	જો (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != ખાલી ? env.outfilename : "<stdout>");

	નહીંતર જો (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != ખાલી ? env.outfilename : "<stdout>");

	જ્યારે (wait (0) > 0) ;

	FLEX_EXIT (0);
	પાછા 0;
}

સ્થિર bool is_blank_લીટી (અચલ અક્ષર *str)
{
	જ્યારે (isspace(*str))
		str++;
	પાછા (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
પૂર્ણાંક filter_fix_linedirs (સંરચના filter *chain)
{
	અક્ષર   buf[4096];
	અચલ અક્ષર *cp;
	અચલ size_t readsz = કદ buf;
	પૂર્ણાંક     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	જો (!chain)
		પાછા 0;

	જ્યારે (fgets (buf, (પૂર્ણાંક) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		જો (ctrl.traceline_re != ખાલી &&
		    ctrl.traceline_template != ખાલી &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			અક્ષર   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			જો (strcmp (fname,
				env.outfilename != ખાલી ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != ખાલી ? env.headerfilename : "<stdout>")
					== 0) {

				અક્ષર    *s1, *s2;
				અક્ષર	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				જ્યારે ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					જો (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					જો (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", કદ(buf)-1);
			}
			નહીંતર {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			મુક્ત (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		નહીંતર જો (in_gen && is_blank_લીટી(buf)) {
			જો (last_was_blank)
				ચાલુ;
			નહીંતર
				last_was_blank = true;
		}

		નહીંતર {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	જો (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != ખાલી ? env.outfilename : "<stdout>");

	નહીંતર જો (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != ખાલી ? env.outfilename : "<stdout>");

	પાછા 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
