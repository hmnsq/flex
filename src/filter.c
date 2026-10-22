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

#అన్తర్భావ "flexdef.h"
స్థిర స్థిరరాశి అక్షరం * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
నిర్మాణం filter *output_chain = ఖాళీ;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
నిర్మాణం filter *filter_create_ext (నిర్మాణం filter *chain, స్థిరరాశి అక్షరం *cmd,
				  ...)
{
	నిర్మాణం filter *f;
	పూర్ణాంకం     max_వాదనలు;
	స్థిరరాశి అక్షరం *s;
	va_list ap;

	/* allocate and initialize new filter */
	f = సున్నా_జ్ఞాపకం_ఇవ్వు(పరిమాణం(నిర్మాణం filter), 1);
	ఒకవేళ (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = ఖాళీ;
	f->extra = ఖాళీ;
	f->తదుపరి = ఖాళీ;
	f->argc = 0;

	ఒకవేళ (chain != ఖాళీ) {
		/* append f to end of chain */
		అయితే (chain->తదుపరి)
			chain = chain->తదుపరి;
		chain->తదుపరి = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_వాదనలు = 8;
	f->argv = జ్ఞాపకం_ఇవ్వు(పరిమాణం(అక్షరం *) * (size_t) (max_వాదనలు + 1));
	ఒకవేళ (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	va_ప్రారంభం (ap, cmd);
	అయితే ((s = va_arg (ap, స్థిరరాశి అక్షరం *)) != ఖాళీ) {
		ఒకవేళ (f->argc >= max_వాదనలు) {
			max_వాదనలు += 8;
			f->argv = realloc(f->argv, పరిమాణం(అక్షరం*) * (size_t) (max_వాదనలు + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = ఖాళీ;

	va_చివర (ap);
	తిరిగి f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
నిర్మాణం filter *filter_create_int (నిర్మాణం filter *chain,
				  పూర్ణాంకం (*filter_func) (నిర్మాణం filter *),
				  శూన్య *extra)
{
	నిర్మాణం filter *f;

	/* allocate and initialize new filter */
	f = సున్నా_జ్ఞాపకం_ఇవ్వు(పరిమాణం(నిర్మాణం filter), 1);
	ఒకవేళ (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->తదుపరి = ఖాళీ;
	f->argc = 0;
	f->argv = ఖాళీ;

	f->filter_func = filter_func;
	f->extra = extra;

	ఒకవేళ (chain != ఖాళీ) {
		/* append f to end of chain */
		అయితే (chain->తదుపరి)
			chain = chain->తదుపరి;
		chain->తదుపరి = f;
	}

	తిరిగి f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (నిర్మాణం filter * chain)
{
	పూర్ణాంకం     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	ఒకవేళ (chain)
		filter_apply_chain (chain->తదుపరి);
	లేకపోతే
		తిరిగి true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	fflush (stdout);
	fflush (stderr);


	ఒకవేళ (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	ఒకవేళ ((pid = fork ()) == -1)
		flexerror (_("fork failed"));

	ఒకవేళ (pid == 0) {
		/*బిడ్డ*/

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		close (pipes[1]);
		clearerr(stdin);
		ఒకవేళ (dup2 (pipes[0], fileno (stdin)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		close (pipes[0]);
		fseek (stdin, 0, SEEK_CUR);
		ungetc(' ', stdin); /* still an evil hack, but one that works better */
		(శూన్య)fgetc(stdin); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		ఒకవేళ (chain->filter_func) {
			పూర్ణాంకం     r;

			ఒకవేళ ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		లేకపోతే {
			execvp (chain->argv[0],
				(అక్షరం **స్థిరరాశి) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/*మాతృ*/
	close (pipes[0]);
	ఒకవేళ (dup2 (pipes[1], fileno (stdout)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	close (pipes[1]);
	fseek (stdout, 0, SEEK_CUR);

	తిరిగి true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
పూర్ణాంకం filter_truncate (నిర్మాణం filter *chain, పూర్ణాంకం max_len)
{
	పూర్ణాంకం     len = 1;

	ఒకవేళ (!chain)
		తిరిగి 0;

	అయితే (chain->తదుపరి && len < max_len) {
		chain = chain->తదుపరి;
		++len;
	}

	chain->తదుపరి = ఖాళీ;
	తిరిగి len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
పూర్ణాంకం filter_tee_శీర్షిక (నిర్మాణం filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	అక్షరం    buf[512];
	పూర్ణాంకం     గమ్యం_cfd = -1;
	FILE   *గమ్యం_c = ఖాళీ, *గమ్యం_h = ఖాళీ;
	bool    write_శీర్షిక;

	write_శీర్షిక = (chain->extra != ఖాళీ);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	ఒకవేళ ((గమ్యం_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	గమ్యం_c = fdopen (గమ్యం_cfd, "w");

	ఒకవేళ (write_శీర్షిక) {
		ఒకవేళ (freopen ((అక్షరం *) chain->extra, "w", stdout) == ఖాళీ)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->తదుపరి);
		గమ్యం_h = stdout;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	ఒకవేళ (write_శీర్షిక) {
		fputs (check_4_gnu_m4, గమ్యం_h);
		fputs ("m4_changecom`'m4_dnl\n", గమ్యం_h);
		fputs ("m4_changequote`'m4_dnl\n", గమ్యం_h);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", గమ్యం_h);
		fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", గమ్యం_h);
		fputs ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", గమ్యం_h);
		fprintf (గమ్యం_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != ఖాళీ ? env.headerfilename : "<stdout>");
	}

	fputs (check_4_gnu_m4, గమ్యం_c);
	fputs ("m4_changecom`'m4_dnl\n", గమ్యం_c);
	fputs ("m4_changequote`'m4_dnl\n", గమ్యం_c);
	fputs ("m4_changequote([[,]])[[]]m4_dnl\n", గమ్యం_c);
	fputs ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", గమ్యం_c);
	fprintf (గమ్యం_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != ఖాళీ ? env.outfilename : "<stdout>");

	అయితే (fgets (buf, పరిమాణం buf, stdin)) {
		fputs (buf, గమ్యం_c);
		ఒకవేళ (write_శీర్షిక)
			fputs (buf, గమ్యం_h);
	}

	ఒకవేళ (write_శీర్షిక) {
		fprintf (గమ్యం_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		ఒకవేళ (ctrl.gen_పంక్తి_dirs)
			పంక్తి_directive_బహిర్గతం (గమ్యం_h, ఖాళీ, 4000);
		fflush (గమ్యం_h);
		ఒకవేళ (ferror (గమ్యం_h))
			lerr (_("error writing output file %s"),
				(అక్షరం *) chain->extra);

		లేకపోతే ఒకవేళ (fclose (గమ్యం_h))
			lerr (_("error closing output file %s"),
				(అక్షరం *) chain->extra);
	}

	fflush (గమ్యం_c);
	ఒకవేళ (ferror (గమ్యం_c))
		lerr (_("error writing output file %s"),
			env.outfilename != ఖాళీ ? env.outfilename : "<stdout>");

	లేకపోతే ఒకవేళ (fclose (గమ్యం_c))
		lerr (_("error closing output file %s"),
			env.outfilename != ఖాళీ ? env.outfilename : "<stdout>");

	అయితే (wait (0) > 0) ;

	FLEX_EXIT (0);
	తిరిగి 0;
}

స్థిర bool is_blank_పంక్తి (స్థిరరాశి అక్షరం *str)
{
	అయితే (ఖాళీనా(*str))
		str++;
	తిరిగి (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
పూర్ణాంకం filter_fix_linedirs (నిర్మాణం filter *chain)
{
	అక్షరం   buf[4096];
	స్థిరరాశి అక్షరం *cp;
	స్థిరరాశి size_t readsz = పరిమాణం buf;
	పూర్ణాంకం     lineno = 1;
	bool    లోపల_gen = true;	/* in generated code */
	bool    చివరి_was_blank = false;

	ఒకవేళ (!chain)
		తిరిగి 0;

	అయితే (fgets (buf, (పూర్ణాంకం) readsz, stdin)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		ఒకవేళ (ctrl.traceline_re != ఖాళీ &&
		    ctrl.traceline_template != ఖాళీ &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			అక్షరం   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			ఒకవేళ (strcmp (fname,
				env.outfilename != ఖాళీ ? env.outfilename : "<stdout>")
					== 0
			 || strcmp (fname,
			 	env.headerfilename != ఖాళీ ? env.headerfilename : "<stdout>")
					== 0) {

				అక్షరం    *s1, *s2;
				అక్షరం	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				అయితే ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					ఒకవేళ (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					ఒకవేళ (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				లోపల_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				strncat(buf, "\n", పరిమాణం(buf)-1);
			}
			లేకపోతే {
				/* it's a #line directive for code we didn't write */
				లోపల_gen = false;
			}

			విడుదల (fname);
			చివరి_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		లేకపోతే ఒకవేళ (లోపల_gen && is_blank_పంక్తి(buf)) {
			ఒకవేళ (చివరి_was_blank)
				కొనసాగు;
			లేకపోతే
				చివరి_was_blank = true;
		}

		లేకపోతే {
			/* it's a line of normal, non-empty code. */
			చివరి_was_blank = false;
		}

		fputs (buf, stdout);
		lineno++;
	}
	fflush (stdout);
	ఒకవేళ (ferror (stdout))
		lerr (_("error writing output file %s"),
			env.outfilename != ఖాళీ ? env.outfilename : "<stdout>");

	లేకపోతే ఒకవేళ (fclose (stdout))
		lerr (_("error closing output file %s"),
			env.outfilename != ఖాళీ ? env.outfilename : "<stdout>");

	తిరిగి 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
