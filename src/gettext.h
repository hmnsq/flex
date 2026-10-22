/* Convenience header for conditional use of GNU <libintl.h>.
   Copyright (C) 1995-1998, 2000-2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.  */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _LIBGETTEXT_H
#ವ್ಯಾಖ್ಯಾನಿಸು _LIBGETTEXT_H 1

/* NLS can be disabled through the configure --disable-nls option.  */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ENABLE_NLS

/* Get declarations of GNU message catalog functions.  */
# include <libintl.h>

#ಇಲ್ಲದಿದ್ದರೆ

/* Disabled NLS.
   The casts to 'const char *' serve the purpose of producing warnings
   for invalid uses of the value returned from these functions.
   On pre-ANSI systems without 'const', the config.h file is supposed to
   contain "#define const".  */
# define gettext(Msgid) ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Msgid))
# define dgettext(Domainname, Msgid) ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Msgid))
# define dcgettext(Domainname, Msgid, Category) ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Msgid))
# define ngettext(Msgid1, Msgid2, N) \
    ((N) == 1 ? (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Msgid1) : (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Msgid2))
# define dngettext(Domainname, Msgid1, Msgid2, N) \
    ((N) == 1 ? (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Msgid1) : (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Msgid2))
# define dcngettext(Domainname, Msgid1, Msgid2, N, Category) \
    ((N) == 1 ? (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Msgid1) : (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Msgid2))
# define textdomain(Domainname) ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Domainname))
# define bindtextdomain(Domainname, Dirname) ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Dirname))
# define bind_textdomain_codeset(Domainname, Codeset) ((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *) (Codeset))

#ಆದರೆ_ಅಂತ್ಯ

/* A pseudo function call that serves as a marker for the automated
   extraction of messages, but does not call gettext().  The run-time
   translation is done at a different place in the code.
   The argument, String, should be a literal string.  Concatenated strings
   and other string expressions won't work.
   The macro's expansion is not parenthesized, so that it is suitable as
   initializer for static 'char[]' or 'const char[]' variables.  */
#ವ್ಯಾಖ್ಯಾನಿಸು gettext_noop(String) String

#ಆದರೆ_ಅಂತ್ಯ /* _LIBGETTEXT_H */
