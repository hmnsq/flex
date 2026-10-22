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

#समावेश "flexdef.h"
अटल स्थिर अक्षर * check_4_gnu_m4 =
    "m4_dnl ifdef(`__gnu__', ,"
    "`errprint(Flex requires GNU M4. Set the PATH or set the M4 environment variable to its path name.)"
    " m4exit(2)')\n";


/** global chain. */
काष्ठा filter *output_chain = शून्य;

/* Allocate and initialize an external filter.
 * @param chain the current chain or NULL for new chain
 * @param cmd the command to execute.
 * @param ... a NULL terminated list of (const char*) arguments to command,
 *            not including argv[0].
 * @return newest filter in chain
 */
काष्ठा filter *filter_create_ext (काष्ठा filter *chain, स्थिर अक्षर *cmd,
				  ...)
{
	काष्ठा filter *f;
	पूर्णांक     max_args;
	स्थिर अक्षर *s;
	बहु_सूची ap;

	/* allocate and initialize new filter */
	f = सुस्मृति(माप(काष्ठा filter), 1);
	अगर (!f)
		flexerror(_("calloc failed (f) in filter_create_ext"));
	f->filter_func = शून्य;
	f->extra = शून्य;
	f->अग्र = शून्य;
	f->argc = 0;

	अगर (chain != शून्य) {
		/* append f to end of chain */
		जबतक (chain->अग्र)
			chain = chain->अग्र;
		chain->अग्र = f;
	}


	/* allocate argv, and populate it with the argument list. */
	max_args = 8;
	f->argv = दो_स्मृति(माप(अक्षर *) * (माप_प्रकार) (max_args + 1));
	अगर (!f->argv)
		flexerror(_("malloc failed (f->argv) in filter_create_ext"));
	f->argv[f->argc++] = cmd;

	बहु_शुरू (ap, cmd);
	जबतक ((s = बहु_तर्क (ap, स्थिर अक्षर *)) != शून्य) {
		अगर (f->argc >= max_args) {
			max_args += 8;
			f->argv = पुनः_स्मृति(f->argv, माप(अक्षर*) * (माप_प्रकार) (max_args + 1));
		}
		f->argv[f->argc++] = s;
	}
	f->argv[f->argc] = शून्य;

	बहु_पूर्ण (ap);
	वापस f;
}

/* Allocate and initialize an internal filter.
 * @param chain the current chain or NULL for new chain
 * @param filter_func The function that will perform the filtering.
 *        filter_func should return 0 if successful, and -1
 *        if an error occurs -- or it can simply exit().
 * @param extra optional user-defined data to pass to the filter.
 * @return newest filter in chain
 */
काष्ठा filter *filter_create_int (काष्ठा filter *chain,
				  पूर्णांक (*filter_func) (काष्ठा filter *),
				  व्योम *extra)
{
	काष्ठा filter *f;

	/* allocate and initialize new filter */
	f = सुस्मृति(माप(काष्ठा filter), 1);
	अगर (!f)
		flexerror(_("calloc failed in filter_create_int"));
	f->अग्र = शून्य;
	f->argc = 0;
	f->argv = शून्य;

	f->filter_func = filter_func;
	f->extra = extra;

	अगर (chain != शून्य) {
		/* append f to end of chain */
		जबतक (chain->अग्र)
			chain = chain->अग्र;
		chain->अग्र = f;
	}

	वापस f;
}

/** Fork and exec entire filter chain.
 *  @param chain The head of the chain.
 *  @return true on success.
 */
bool filter_apply_chain (काष्ठा filter * chain)
{
	पूर्णांक     pid, pipes[2];


	/* Tricky recursion, since we want to begin the chain
	 * at the END. Why? Because we need all the forked processes
	 * to be children of the main flex process.
	 */
	अगर (chain)
		filter_apply_chain (chain->अग्र);
	अन्यथा
		वापस true;

	/* Now we are the right-most unprocessed link in the chain.
	 */

	ख_साफ (मानक_निकास);
	ख_साफ (मानक_त्रुटि);


	अगर (pipe (pipes) == -1)
		flexerror (_("pipe failed"));

	अगर ((pid = विभाजन ()) == -1)
		flexerror (_("fork failed"));

	अगर (pid == 0) {
		/* child */

        /* We need stdin (the FILE* stdin) to connect to this new pipe.
         * There is no portable way to set stdin to a new file descriptor,
         * as stdin is not an lvalue on some systems (BSD).
         * So we dup the new pipe onto the stdin descriptor and use a no-op fseek
         * to sync the stream. This is a Hail Mary situation. It seems to work.
         */
		बंद (pipes[1]);
		साफ_त्रुटि(मानक_निवेश);
		अगर (dup2 (pipes[0], fileno (मानक_निवेश)) == -1)
			flexfatal (_("dup2(pipes[0],0)"));
		बंद (pipes[0]);
		ख_जाओ (मानक_निवेश, 0, प्रस्तुत_से);
		अक्षर_वापस(' ', मानक_निवेश); /* still an evil hack, but one that works better */
		(व्योम)ख_अक्षर_लो(मानक_निवेश); /* on NetBSD than the fseek attempt does */

		/* run as a filter, either internally or by exec */
		अगर (chain->filter_func) {
			पूर्णांक     r;

			अगर ((r = chain->filter_func (chain)) == -1)
				flexfatal (_("filter_func failed"));
			FLEX_EXIT (0);
		}
		अन्यथा {
			execvp (chain->argv[0],
				(अक्षर **स्थिर) (chain->argv));
			lerr_fatal ( _("exec of %s failed"),
				     chain->argv[0]);
		}

		FLEX_EXIT (1);
	}

	/* Parent */
	बंद (pipes[0]);
	अगर (dup2 (pipes[1], fileno (मानक_निकास)) == -1)
		flexfatal (_("dup2(pipes[1],1)"));
	बंद (pipes[1]);
	ख_जाओ (मानक_निकास, 0, प्रस्तुत_से);

	वापस true;
}

/** Truncate the chain to max_len number of filters.
 * @param chain the current chain.
 * @param max_len the maximum length of the chain.
 * @return the resulting length of the chain.
 */
पूर्णांक filter_truncate (काष्ठा filter *chain, पूर्णांक max_len)
{
	पूर्णांक     len = 1;

	अगर (!chain)
		वापस 0;

	जबतक (chain->अग्र && len < max_len) {
		chain = chain->अग्र;
		++len;
	}

	chain->अग्र = शून्य;
	वापस len;
}

/** Splits the chain in order to write to a header file.
 *  Similar in spirit to the 'tee' program.
 *  The header file name is in extra.
 *  @return 0 (zero) on success, and -1 on failure.
 */
पूर्णांक filter_tee_header (काष्ठा filter *chain)
{
	/* This function reads from stdin and writes to both the C file and the
	 * header file at the same time.
	 */

	अक्षर    buf[512];
	पूर्णांक     to_cfd = -1;
	खाता   *to_c = शून्य, *to_h = शून्य;
	bool    write_header;

	write_header = (chain->extra != शून्य);

	/* Store a copy of the stdout pipe, which is already piped to C file
	 * through the running chain. Then create a new pipe to the H file as
	 * stdout, and fork the rest of the chain again.
	 */

	अगर ((to_cfd = dup (1)) == -1)
		flexfatal (_("dup(1) failed"));
	to_c = fdopen (to_cfd, "w");

	अगर (write_header) {
		अगर (ख_व_खोलो ((अक्षर *) chain->extra, "w", मानक_निकास) == शून्य)
			flexfatal (_("freopen(headerfilename) failed"));

		filter_apply_chain (chain->अग्र);
		to_h = मानक_निकास;
	}

	/* Now to_c is a pipe to the C branch, and to_h is a pipe to the H branch.
	 */

	अगर (write_header) {
		ख_माला_दो (check_4_gnu_m4, to_h);
		ख_माला_दो ("m4_changecom`'m4_dnl\n", to_h);
		ख_माला_दो ("m4_changequote`'m4_dnl\n", to_h);
	ख_माला_दो ("m4_changequote([[,]])[[]]m4_dnl\n", to_h);
		ख_माला_दो ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_h);
		ख_माला_दो ("m4_define([[M4_YY_IN_HEADER]],[[]])m4_dnl\n", to_h);
		ख_लिखो (to_h,
			 "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
			 env.headerfilename != शून्य ? env.headerfilename : "<stdout>");
	}

	ख_माला_दो (check_4_gnu_m4, to_c);
	ख_माला_दो ("m4_changecom`'m4_dnl\n", to_c);
	ख_माला_दो ("m4_changequote`'m4_dnl\n", to_c);
	ख_माला_दो ("m4_changequote([[,]])[[]]m4_dnl\n", to_c);
	ख_माला_दो ("m4_define([[M4_YY_NOOP]])[[]]m4_dnl\n", to_c);
	ख_लिखो (to_c, "m4_define( [[M4_YY_OUTFILE_NAME]],[[%s]])m4_dnl\n",
		 env.outfilename != शून्य ? env.outfilename : "<stdout>");

	जबतक (ख_माला_लो (buf, माप buf, मानक_निवेश)) {
		ख_माला_दो (buf, to_c);
		अगर (write_header)
			ख_माला_दो (buf, to_h);
	}

	अगर (write_header) {
		ख_लिखो (to_h, "\n");

		/* write a fake line number. It will get fixed by the linedir filter. */
		अगर (ctrl.gen_पंक्ति_dirs)
			पंक्ति_directive_out (to_h, शून्य, 4000);
		ख_साफ (to_h);
		अगर (ख_त्रुटि (to_h))
			lerr (_("error writing output file %s"),
				(अक्षर *) chain->extra);

		अन्यथा अगर (ख_बंद (to_h))
			lerr (_("error closing output file %s"),
				(अक्षर *) chain->extra);
	}

	ख_साफ (to_c);
	अगर (ख_त्रुटि (to_c))
		lerr (_("error writing output file %s"),
			env.outfilename != शून्य ? env.outfilename : "<stdout>");

	अन्यथा अगर (ख_बंद (to_c))
		lerr (_("error closing output file %s"),
			env.outfilename != शून्य ? env.outfilename : "<stdout>");

	जबतक (रुको (0) > 0) ;

	FLEX_EXIT (0);
	वापस 0;
}

अटल bool is_blank_पंक्ति (स्थिर अक्षर *str)
{
	जबतक (है_खाली(*str))
		str++;
	वापस (*str == '\0');
}

/** Adjust the line numbers in the #line directives of the generated scanner.
 * After the m4 expansion, the line numbers are incorrect since the m4 macros
 * can add or remove lines.  This only adjusts line numbers for generated code,
 * not user code. This also happens to be a good place to squeeze multiple
 * blank lines into a single blank line.
 */
पूर्णांक filter_fix_linedirs (काष्ठा filter *chain)
{
	अक्षर   buf[4096];
	स्थिर अक्षर *cp;
	स्थिर माप_प्रकार readsz = माप buf;
	पूर्णांक     lineno = 1;
	bool    in_gen = true;	/* in generated code */
	bool    last_was_blank = false;

	अगर (!chain)
		वापस 0;

	जबतक (ख_माला_लो (buf, (पूर्णांक) readsz, मानक_निवेश)) {

		regmatch_t m[10];

		/* Check for directive. Note wired-in assumption:
		 * field reference 1 is line number, 2 is filename.
		 */
		अगर (ctrl.traceline_re != शून्य &&
		    ctrl.traceline_template != शून्य &&
		    regexec (&regex_linedir, buf, 3, m, 0) == 0) {

			अक्षर   *fname;

			/* extract the line number and filename */
			fname = regmatch_dup (&m[2], buf);

			अगर (म_भेद (fname,
				env.outfilename != शून्य ? env.outfilename : "<stdout>")
					== 0
			 || म_भेद (fname,
			 	env.headerfilename != शून्य ? env.headerfilename : "<stdout>")
					== 0) {

				अक्षर    *s1, *s2;
				अक्षर	filename[MAXLINE];

				s1 = fname;
				s2 = filename;

				जबतक ((s2 - filename) < (MAXLINE - 1) && *s1) {
					/* Escape the backslash */
					अगर (*s1 == '\\')
						*s2++ = '\\';
					/* Escape the double quote */
					अगर (*s1 == '\"')
						*s2++ = '\\';
					/* Copy the character as usual */
					*s2++ = *s1++;
				}

				*s2 = '\0';

				/* Adjust the line directives. */
				in_gen = true;
				snprintf (buf, readsz, ctrl.traceline_template,
					  lineno + 1, filename);
				म_जोड़न(buf, "\n", माप(buf)-1);
			}
			अन्यथा {
				/* it's a #line directive for code we didn't write */
				in_gen = false;
			}

			मुक्त (fname);
			last_was_blank = false;
		}

		/* squeeze blank lines from generated code */
		अन्यथा अगर (in_gen && is_blank_पंक्ति(buf)) {
			अगर (last_was_blank)
				जारी;
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
	अगर (ख_त्रुटि (मानक_निकास))
		lerr (_("error writing output file %s"),
			env.outfilename != शून्य ? env.outfilename : "<stdout>");

	अन्यथा अगर (ख_बंद (मानक_निकास))
		lerr (_("error closing output file %s"),
			env.outfilename != शून्य ? env.outfilename : "<stdout>");

	वापस 0;
}

/* vim:set expandtab cindent tabstop=4 softtabstop=4 shiftwidth=4 textwidth=0: */
