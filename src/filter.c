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
static const char * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
struct filter *output_chain = NULL;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
struct filter *filter_create_ext (struct filter *chain, const char *cmd,
				  ...)
{
	struct filter *f;
	정수     max_args;
	const char *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = calloc(sizeof(struct filter), 1);
	만약 (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = NULL;
	f->extra = NULL;
	f->next = NULL;
	f->argc = 0;

	만약 (chain != NULL) {
		/* append f to end of chain */
		동안 (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = malloc(sizeof(char *) * (size_t) (max_args + 1));
	만약 (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_start (ap, cmd);
	동안 ((s = va_arg (ap, const char *)) != NULL) {
		만약 (f->argc >= max_args) {
			max_args += 8;
			f->argv = realloc(f->argv, sizeof(char*) * (size_t) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = NULL;

	va_end (ap);
	반환 f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
struct filter *filter_create_int (struct filter *chain,
				  정수 (*filter_func) (struct filter *),
				  void *extra)
{
	struct filter *f;

	/* allocate and initialize new filter */
	f = calloc(sizeof(struct filter), 1);
	만약 (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = NULL;
	f->argc = 0;
	f->argv = NULL;

	f->filter_func = filter_func;
	f->extra = extra;

	만약 (chain != NULL) {
		/* append f to end of chain */
		동안 (chain->next)
			chain = chain->next;
		chain->next = f;
	}

	반환 f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (struct filter * chain)
{
	정수     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	만약 (chain)
		filter_apply_chain (chain->next);
	아니면
		반환 true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	만약 (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	만약 ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	만약 (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		만약 (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(void)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		만약 (chain->filter_func) {
			정수     r;

			만약 ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		아니면 {
			execvp (chain->argv[0],
				(char **const) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	close (pipes[0]);
	만약 (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	반환 true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
정수 filter_truncate (struct filter *chain, 정수 max_len)
{
	정수     len = 1;

	만약 (!chain)
		반환 0;

	동안 (chain->next && len < max_len) {
		chain = chain->next;
		++len;
	}

	chain->next = NULL;
	반환 len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
정수 filter_tee_header (struct filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	char    buf[512];
	정수     to_cfd = -1;
	FILE   *to_c = NULL, *to_h = NULL;
	bool    write_header;

	write_header = (chain->extra != NULL);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	만약 ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	만약 (write_header) {
		만약 (freopen ((char *) chain->extra, "w", stdout) == NULL)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	만약 (write_header) {
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

	동안 (fgets (buf, sizeof buf, stdin)) {
		fputs (buf, to_c);
		만약 (write_header)
			fputs (buf, to_h);
	}

	만약 (write_header) {
		fprintf (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		만약 (ctrl.gen_line_dirs)
			line_directive_out (to_h, NULL, 4000);
		fflush (to_h);
		만약 (ferror (to_h))
			lerr (_("error writing output file %s"),
				(char *) chain->extra);

		아니면 만약 (fclose (to_h))
			lerr (_("error closing output file %s"),
				(char *) chain->extra);
	}

	fflush (to_c);
	만약 (ferror (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != NULL ? env.outfilename : "<stdout>");

	아니면 만약 (fclose (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != NULL ? env.outfilename : "<stdout>");

	동안 (wait (0) > 0) ;

	FLEX_EXIT (0);
	반환 0;
}

static bool is_blank_line (const char *str)
{
	동안 (isspace(*str))
		str++;
	반환 (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
정수 filter_fix_linedirs (struct filter *chain)
{
	char   buf[4096];
	const char *cp;
	const size_t readsz = sizeof buf;
	정수     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	만약 (!chain)
		반환 0;

	동안 (fgets (buf, (정수) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		만약 (ctrl.traceline_re != NULL &&
		    ctrl.traceline_template != NULL &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			char   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			만약 (strcmp (fname,
				env.outfilename != NULL ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != NULL ? env.headerfilename : "<stdout>")
					== 0) {

				char    *s1, *s2;
				char	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				동안 ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					만약 (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					만약 (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", sizeof(buf)-1);
			}
			아니면 {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			free (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		아니면 만약 (in_gen && is_blank_line(buf)) {
			만약 (last_was_blank)
				continue;
			아니면
				last_was_blank = true;
		}

		아니면 {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	만약 (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != NULL ? env.outfilename : "<stdout>");

	아니면 만약 (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != NULL ? env.outfilename : "<stdout>");

	반환 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
