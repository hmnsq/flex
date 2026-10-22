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

#include "flexdef.h"
static const var_na * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
sa_nracanaa filter *output_chain = NULL;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
sa_nracanaa filter *filter_create_ext (sa_nracanaa filter *chain, const var_na *cmd,
				  ...)
{
	sa_nracanaa filter *f;
	ཧྲིལ     max_args;
	const var_na *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(parimaa_na(sa_nracanaa filter), 1);
	གལ་སྲིད (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = NULL;
	f->extra = NULL;
	f->next = NULL;
	f->argc = 0;

	གལ་སྲིད (chain != NULL) {
		/* append f to end of chain */
		སྐབས (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(parimaa_na(var_na *) * (size_t) (max_args + 1));
	གལ་སྲིད (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	སྐབས ((s = va_arg (ap, const var_na *)) != NULL) {
		གལ་སྲིད (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, parimaa_na(var_na*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = NULL;

	va_end (ap);
	ལོག f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
sa_nracanaa filter *filter_create_int (sa_nracanaa filter *chain,
				  ཧྲིལ (*filter_func) (sa_nracanaa filter *),
				  void *extra)
{
	sa_nracanaa filter *f;

	/* allocate and initialize new filter */
	f = calloc(parimaa_na(sa_nracanaa filter), 1);
	གལ་སྲིད (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = NULL;
	f->argc = 0;
	f->argv = NULL;

	f->filter_func = filter_func;
	f->extra = extra;

	གལ་སྲིད (chain != NULL) {
		/* append f to end of chain */
		སྐབས (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	ལོག f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (sa_nracanaa filter * chain)
{
	ཧྲིལ     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	གལ་སྲིད (chain)
		filter_apply_chain (chain->next);
	དེ་མིན
		ལོག true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	གལ་སྲིད (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	གལ་སྲིད ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	གལ་སྲིད (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		གལ་སྲིད (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(void)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		གལ་སྲིད (chain->filter_func) {
			ཧྲིལ     r;

			གལ་སྲིད ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		དེ་མིན {
			execvp (chain->argv[0],
				(var_na **const) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	གལ་སྲིད (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	ལོག true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
ཧྲིལ filter_truncate (sa_nracanaa filter *chain, ཧྲིལ max_len)
{
	ཧྲིལ     len = 1;

	གལ་སྲིད (!chain)
		ལོག 0;

	སྐབས (chain->next && len < max_len) {
		chain = chain->next;
		++len;
	}

	chain->next = NULL;
	ལོག len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
ཧྲིལ filter_tee_header (sa_nracanaa filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	var_na    buf[512];
	ཧྲིལ     to_cfd = -1;
	FILE   *to_c = NULL, *to_h = NULL;
	bool    write_header;

	write_header = (chain->extra != NULL);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	གལ་སྲིད ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	གལ་སྲིད (write_header) {
		གལ་སྲིད (freopen ((var_na *) chain->extra, "w", stdout) == NULL)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	གལ་སྲིད (write_header) {
		fputs (check_4_gnu_m4, to_h);
		fputs ("m4_changecom`'m4_dnl\n", to_h);
		fputs ("m4_changequote`'m4_dnl\n", to_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		fprintf (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != NULL ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, to_c);
	fputs ("m4_changecom`'m4_dnl\n", to_c);
	fputs ("m4_changequote`'m4_dnl\n", to_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	fprintf (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != NULL ? env.outfilename : "<stdout>");

	སྐབས (fgets (buf, parimaa_na buf, stdin)) {
		fputs (buf, to_c);
		གལ་སྲིད (write_header)
			fputs (buf, to_h);
	}

	གལ་སྲིད (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		གལ་སྲིད (ctrl.gen_line_dirs)
			line_directive_out (to_h, NULL, 4000);
		fflush (to_h);
		གལ་སྲིད (ferror (to_h))
			lerr (_("error writing output file %s"),
				(var_na *) chain->extra);

		དེ་མིན གལ་སྲིད (fclose (to_h))
			lerr (_("error closing output file %s"),
				(var_na *) chain->extra);
	}

	fflush (to_c);
	གལ་སྲིད (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != NULL ? env.outfilename : "<stdout>");

	དེ་མིན གལ་སྲིད (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != NULL ? env.outfilename : "<stdout>");

	སྐབས (wait (0) > 0) ;

	FLEX_EXIT (0);
	ལོག 0;
}

static bool is_blank_line (const var_na *str)
{
	སྐབས (isspace(*str))
		str++;
	ལོག (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
ཧྲིལ filter_fix_linedirs (sa_nracanaa filter *chain)
{
	var_na   buf[4096];
	const var_na *cp;
	const size_t readsz = parimaa_na buf;
	ཧྲིལ     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	གལ་སྲིད (!chain)
		ལོག 0;

	སྐབས (fgets (buf, (ཧྲིལ) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		གལ་སྲིད (ctrl.traceline_re != NULL &&
		    ctrl.traceline_template != NULL &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			var_na   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			གལ་སྲིད (strcmp (fname,
				env.outfilename != NULL ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != NULL ? env.headerfilename : "<stdout>")
					== 0) {

				var_na    *s1, *s2;
				var_na	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				སྐབས ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					གལ་སྲིད (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					གལ་སྲིད (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", parimaa_na(buf)-1);
			}
			དེ་མིན {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			free (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		དེ་མིན གལ་སྲིད (in_gen && is_blank_line(buf)) {
			གལ་སྲིད (last_was_blank)
				continue;
			དེ་མིན
				last_was_blank = true;
		}

		དེ་མིན {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	གལ་སྲིད (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != NULL ? env.outfilename : "<stdout>");

	དེ་མིན གལ་སྲིད (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != NULL ? env.outfilename : "<stdout>");

	ལོག 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
