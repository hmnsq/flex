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
	बहु_सूची ap;

	/* allocate and initialize new filter */
	f = सुस्मृति(परिमाण(संरचना filter), 1);
	यदि (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = रिक्त;
	f->extra = रिक्त;
	f->next = रिक्त;
	f->argc = 0;

	यदि (chain != रिक्त) {
		/* append f to end of chain */
		यावत् (chain->next)
			chain = chain->next;
		chain->next = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = दो_स्मृति(परिमाण(वर्ण *) * (माप_प्रकार) (max_args + 1));
	यदि (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	बहु_शुरू (ap, cmd);
	यावत् ((s = बहु_तर्क (ap, ध्रुव वर्ण *)) != रिक्त) {
		यदि (f->argc >= max_args) {
			max_args += 8;
			f->argv = पुनः_स्मृति(f->argv, परिमाण(वर्ण*) * (माप_प्रकार) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = रिक्त;

	बहु_पूर्ण (ap);
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
	f = सुस्मृति(परिमाण(संरचना filter), 1);
	यदि (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->next = रिक्त;
	f->argc = 0;
	f->argv = रिक्त;

	f->filter_func = filter_func;
	f->extra = extra;

	यदि (chain != रिक्त) {
		/* append f to end of chain */
		यावत् (chain->next)
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
	यदि (chain)
		filter_apply_chain (chain->next);
	अन्यथा
		प्रत्यागम true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	ख_साफ (मानक_निकास);
	ख_साफ (मानक_त्रुटि);


	यदि (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	यदि ((pid = विभाजन ()) == -1)
		flexerror (_("fork failed"));

	यदि (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		बंद (pipes[1]);
		साफ_त्रुटि(मानक_निवेश);
		यदि (dup2 (pipes[0], fileno (मानक_निवेश)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		बंद (pipes[0]);
		ख_जाओ (मानक_निवेश, 0, प्रस्तुत_से);
		अक्षर_वापस(' ', मानक_निवेश); /* still an evil hack, but one that works better */
		(शून्य)ख_अक्षर_लो(मानक_निवेश); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		यदि (chain->filter_func) {
			पूर्णाङ्क     r;

			यदि ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		अन्यथा {
			execvp (chain->argv[0],
				(वर्ण **ध्रुव) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	बंद (pipes[0]);
	यदि (dup2 (pipes[1], fileno (मानक_निकास)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	बंद (pipes[1]);
	ख_जाओ (मानक_निकास, 0, प्रस्तुत_से);

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

	यदि (!chain)
		प्रत्यागम 0;

	यावत् (chain->next && len < max_len) {
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
	खाता   *to_c = रिक्त, *to_h = रिक्त;
	bool    write_header;

	write_header = (chain->extra != रिक्त);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	यदि ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	यदि (write_header) {
		यदि (ख_व_खोलो ((वर्ण *) chain->extra, "w", मानक_निकास) == रिक्त)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->next);
		to_h = मानक_निकास;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	यदि (write_header) {
		ख_माला_दो (check_4_gnu_m4, to_h);
		ख_माला_दो ("m4_changecom`'m4_dnl\n", to_h);
		ख_माला_दो ("m4_changequote`'m4_dnl\n", to_h);
	ख_माला_दो ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		ख_माला_दो ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		ख_माला_दो ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		ख_लिखो (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != रिक्त ? env.headerfilename : "<stdout>");
	}

	ख_माला_दो (check_4_gnu_m4, to_c);
	ख_माला_दो ("m4_changecom`'m4_dnl\n", to_c);
	ख_माला_दो ("m4_changequote`'m4_dnl\n", to_c);
	ख_माला_दो ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	ख_माला_दो ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	ख_लिखो (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != रिक्त ? env.outfilename : "<stdout>");

	यावत् (ख_माला_लो (buf, परिमाण buf, मानक_निवेश)) {
		ख_माला_दो (buf, to_c);
		यदि (write_header)
			ख_माला_दो (buf, to_h);
	}

	यदि (write_header) {
		ख_लिखो (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		यदि (ctrl.gen_पंक्ति_dirs)
			पंक्ति_directive_out (to_h, रिक्त, 4000);
		ख_साफ (to_h);
		यदि (ख_त्रुटि (to_h))
			lerr (_("error writing output file %s"),
				(वर्ण *) chain->extra);

		अन्यथा यदि (ख_बंद (to_h))
			lerr (_("error closing output file %s"),
				(वर्ण *) chain->extra);
	}

	ख_साफ (to_c);
	यदि (ख_त्रुटि (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != रिक्त ? env.outfilename : "<stdout>");

	अन्यथा यदि (ख_बंद (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != रिक्त ? env.outfilename : "<stdout>");

	यावत् (रुको (0) > 0) ;

	FLEX_EXIT (0);
	प्रत्यागम 0;
}

स्थिर bool is_blank_पंक्ति (ध्रुव वर्ण *str)
{
	यावत् (है_खाली(*str))
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
	ध्रुव माप_प्रकार readsz = परिमाण buf;
	पूर्णाङ्क     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	यदि (!chain)
		प्रत्यागम 0;

	यावत् (ख_माला_लो (buf, (पूर्णाङ्क) readsz, मानक_निवेश)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		यदि (ctrl.traceline_re != रिक्त &&
		    ctrl.traceline_template != रिक्त &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			वर्ण   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			यदि (म_भेद (fname,
				env.outfilename != रिक्त ? env.outfilename : "<stdout>")
					== 0
			 || म_भेद (fname,
			 	env.headerfilename != रिक्त ? env.headerfilename : "<stdout>")
					== 0) {

				वर्ण    *s1, *s2;
				वर्ण	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				यावत् ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					यदि (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					यदि (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				म_जोड़न(buf, "\n", परिमाण(buf)-1);
			}
			अन्यथा {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			मुक्त (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		अन्यथा यदि (in_gen && is_blank_पंक्ति(buf)) {
			यदि (last_was_blank)
				अनुवर्त;
			अन्यथा
				last_was_blank = true;
		}

		अन्यथा {
			/* it's a line of normal, non-empty code. */
			last_was_blank = false;
		}

		ख_माला_दो (buf, मानक_निकास);
		lineno++;
	}
	ख_साफ (मानक_निकास);
	यदि (ख_त्रुटि (मानक_निकास))
		lerr (_("error writing output file %s"),
			env.outfilename != रिक्त ? env.outfilename : "<stdout>");

	अन्यथा यदि (ख_बंद (मानक_निकास))
		lerr (_("error closing output file %s"),
			env.outfilename != रिक्त ? env.outfilename : "<stdout>");

	प्रत्यागम 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
