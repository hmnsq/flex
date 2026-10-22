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
ساکن ثابت حرف * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
ساخت filter *output_chain = تہی;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
ساخت filter *filter_create_ext (ساخت filter *chain, ثابت حرف *cmd,
				  ...)
{
	ساخت filter *f;
	صحیح     max_دلائل;
	ثابت حرف *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = صفر_حافظہ_دو(حجم(ساخت filter), 1);
	اگر (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = تہی;
	f->extra = تہی;
	f->اگلا = تہی;
	f->argc = 0;

	اگر (chain != تہی) {
		/* append f to end of chain */
		جب (chain->اگلا)
			chain = chain->اگلا;
		chain->اگلا = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_دلائل = 8;
	f->argv = حافظہ_دو(حجم(حرف *) * (size_t) (max_دلائل + 1));
	اگر (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_آغاز (ap, cmd);
	جب ((s = va_arg (ap, ثابت حرف *)) != تہی) {
		اگر (f->argc >= max_دلائل) {
			max_دلائل += 8;
			f->argv = realloc(f->argv, حجم(حرف*) * (size_t) (max_دلائل + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = تہی;

	va_انتہا (ap);
	واپس f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
ساخت filter *filter_create_int (ساخت filter *chain,
				  صحیح (*filter_func) (ساخت filter *),
				  خالی *extra)
{
	ساخت filter *f;

	/* allocate and initialize new filter */
	f = صفر_حافظہ_دو(حجم(ساخت filter), 1);
	اگر (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->اگلا = تہی;
	f->argc = 0;
	f->argv = تہی;

	f->filter_func = filter_func;
	f->extra = extra;

	اگر (chain != تہی) {
		/* append f to end of chain */
		جب (chain->اگلا)
			chain = chain->اگلا;
		chain->اگلا = f;
	}

	واپس f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (ساخت filter * chain)
{
	صحیح     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	اگر (chain)
		filter_apply_chain (chain->اگلا);
	ورنہ
		واپس true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	اگر (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	اگر ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	اگر (pid == 0) {
		/*بچہ*/

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
		(خالی)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		اگر (chain->filter_func) {
			صحیح     r;

			اگر ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		ورنہ {
			execvp (chain->argv[0],
				(حرف **ثابت) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/*والد*/
	close (pipes[0]);
	اگر (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	واپس true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
صحیح filter_truncate (ساخت filter *chain, صحیح max_len)
{
	صحیح     len = 1;

	اگر (!chain)
		واپس 0;

	جب (chain->اگلا && len < max_len) {
		chain = chain->اگلا;
		++len;
	}

	chain->اگلا = تہی;
	واپس len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
صحیح filter_tee_سرخی (ساخت filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	حرف    buf[512];
	صحیح     مقصد_cfd = -1;
	FILE   *مقصد_c = تہی, *مقصد_h = تہی;
	bool    write_سرخی;

	write_سرخی = (chain->extra != تہی);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	اگر ((مقصد_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	مقصد_c = fdopen (مقصد_cfd, "w");

	اگر (write_سرخی) {
		اگر (freopen ((حرف *) chain->extra, "w", stdout) == تہی)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->اگلا);
		مقصد_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	اگر (write_سرخی) {
		fputs (check_4_gnu_m4, مقصد_h);
		fputs ("m4_changecom`'m4_dnl\n", مقصد_h);
		fputs ("m4_changequote`'m4_dnl\n", مقصد_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", مقصد_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", مقصد_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", مقصد_h);
		fprintf (مقصد_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != تہی ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, مقصد_c);
	fputs ("m4_changecom`'m4_dnl\n", مقصد_c);
	fputs ("m4_changequote`'m4_dnl\n", مقصد_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", مقصد_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", مقصد_c);
	fprintf (مقصد_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != تہی ? env.outfilename : "<stdout>");

	جب (fgets (buf, حجم buf, stdin)) {
		fputs (buf, مقصد_c);
		اگر (write_سرخی)
			fputs (buf, مقصد_h);
	}

	اگر (write_سرخی) {
		fprintf (مقصد_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		اگر (ctrl.gen_سطر_dirs)
			سطر_directive_برآمد (مقصد_h, تہی, 4000);
		fflush (مقصد_h);
		اگر (ferror (مقصد_h))
			lerr (_("error writing output file %s"),
				(حرف *) chain->extra);

		ورنہ اگر (fclose (مقصد_h))
			lerr (_("error closing output file %s"),
				(حرف *) chain->extra);
	}

	fflush (مقصد_c);
	اگر (ferror (مقصد_c))
		lerr (_("error writing output file %s"),
			env.outfilename != تہی ? env.outfilename : "<stdout>");

	ورنہ اگر (fclose (مقصد_c))
		lerr (_("error closing output file %s"),
			env.outfilename != تہی ? env.outfilename : "<stdout>");

	جب (wait (0) > 0) ;

	FLEX_EXIT (0);
	واپس 0;
}

ساکن bool is_blank_سطر (ثابت حرف *str)
{
	جب (خلا_ہے(*str))
		str++;
	واپس (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
صحیح filter_fix_linedirs (ساخت filter *chain)
{
	حرف   buf[4096];
	ثابت حرف *cp;
	ثابت size_t readsz = حجم buf;
	صحیح     lineno = 1;
	bool    اندر_gen = true;	/* in generated code */
	bool    آخری_was_blank = false;

	اگر (!chain)
		واپس 0;

	جب (fgets (buf, (صحیح) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		اگر (ctrl.traceline_re != تہی &&
		    ctrl.traceline_template != تہی &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			حرف   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			اگر (strcmp (fname,
				env.outfilename != تہی ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != تہی ? env.headerfilename : "<stdout>")
					== 0) {

				حرف    *s1, *s2;
				حرف	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				جب ((s2 - filename) < (MAXLINE - 1) && *s1) {
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
				اندر_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", حجم(buf)-1);
			}
			ورنہ {
				/* it's a #line directive for code we didn't write */
				اندر_gen = false;
			}

			آزاد (fname);
			آخری_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		ورنہ اگر (اندر_gen && is_blank_سطر(buf)) {
			اگر (آخری_was_blank)
				جاری;
			ورنہ
				آخری_was_blank = true;
		}

		ورنہ {
			/* it's a line of normal, non-empty code. */
			آخری_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	اگر (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != تہی ? env.outfilename : "<stdout>");

	ورنہ اگر (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != تہی ? env.outfilename : "<stdout>");

	واپس 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
