// -*-C++-*-
// FlexLexer.h -- define interfaces for lexical analyzer classes generated
// by flex

// Copyright (c) 1993 The Regents of the University of California.
// All rights reserved.
//
// This code is derived from software contributed to Berkeley by
// Kent Williams and Tom Epperly.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:

//  1. Redistributions of source code must retain the above copyright
//  notice, this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the
//  documentation and/or other materials provided with the distribution.

//  Neither the name of the University nor the names of its contributors
//  may be used to endorse or promote products derived from this software
//  without specific prior written permission.

//  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE.

// This file defines FlexLexer, an abstract class which specifies the
// external interface provided to flex C++ lexer objects, and yyFlexLexer,
// which defines a particular lexer class.
//
// If you want to create multiple lexer classes, you use the -P flag
// to rename each yyFlexLexer to some other xxFlexLexer.  You then
// include <FlexLexer.h> in your other sources once per lexer class:
//
//      #undef yyFlexLexer
//      #define yyFlexLexer xxFlexLexer
//      #include <FlexLexer.h>
//
//      #undef yyFlexLexer
//      #define yyFlexLexer zzFlexLexer
//      #include <FlexLexer.h>
//      ...

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __FLEX_LEXER_H
// Never included before - need to define base class.
#ವ್ಯಾಖ್ಯಾನಿಸು __FLEX_LEXER_H

#ಅನ್ತರ್ಭಾವ <iostream>

ಬಾಹ್ಯ "C++" {

ರಚನೆ yy_ಬಫರ್_state;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ yy_state_type;

class FlexLexer
{
ಸಾರ್ವಜನಿಕ:
  ವಾಸ್ತವಿಕ ~FlexLexer()        { }

  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* YYText() ಸ್ಥಿರಾಂಕ  { ಹಿಂತಿರುಗಿ yytext; }
  ಪೂರ್ಣಾಂಕ YYLeng()        ಸ್ಥಿರಾಂಕ   { ಹಿಂತಿರುಗಿ yyleng; }

  ವಾಸ್ತವಿಕ ಶೂನ್ಯ
  yy_switch_ಗಮ್ಯ_ಬಫರ್( yy_ಬಫರ್_state* new_ಬಫರ್ ) = 0;
  ವಾಸ್ತವಿಕ yy_ಬಫರ್_state* yy_create_ಬಫರ್( std::istream* s, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 ) = 0;
  ವಾಸ್ತವಿಕ yy_ಬಫರ್_state* yy_create_ಬಫರ್( std::istream& s, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 ) = 0;
  ವಾಸ್ತವಿಕ ಶೂನ್ಯ yy_delete_ಬಫರ್( yy_ಬಫರ್_state* b ) = 0;
  ವಾಸ್ತವಿಕ ಶೂನ್ಯ yyrestart( std::istream* s ) = 0;
  ವಾಸ್ತವಿಕ ಶೂನ್ಯ yyrestart( std::istream& s ) = 0;

  ವಾಸ್ತವಿಕ ಪೂರ್ಣಾಂಕ yylex() = 0;

  // Call yylex with new input/output sources.
  ಪೂರ್ಣಾಂಕ yylex( std::istream& new_ಒಳ, std::ostream& new_ಹೊರಹೋಗು )
  {
    switch_streams( new_ಒಳ, new_ಹೊರಹೋಗು );
    ಹಿಂತಿರುಗಿ yylex();
  }

  ಪೂರ್ಣಾಂಕ yylex( std::istream* new_ಒಳ, std::ostream* new_ಹೊರಹೋಗು = 0)
  {
    switch_streams( new_ಒಳ, new_ಹೊರಹೋಗು );
    ಹಿಂತಿರುಗಿ yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  ವಾಸ್ತವಿಕ ಶೂನ್ಯ switch_streams( std::istream* new_ಒಳ,
                               std::ostream* new_ಹೊರಹೋಗು ) = 0;
  ವಾಸ್ತವಿಕ ಶೂನ್ಯ switch_streams( std::istream& new_ಒಳ,
                               std::ostream& new_ಹೊರಹೋಗು ) = 0;

  ಪೂರ್ಣಾಂಕ lineno() ಸ್ಥಿರಾಂಕ          { ಹಿಂತಿರುಗಿ yylineno; }

  ಪೂರ್ಣಾಂಕ debug() ಸ್ಥಿರಾಂಕ           { ಹಿಂತಿರುಗಿ yyflexdebug; }
  ಶೂನ್ಯ ಗಣ_debug( ಪೂರ್ಣಾಂಕ flag )  { yyflexdebug = flag; }

ಸಂರಕ್ಷಿತ:
  ಅಕ್ಷರ* yytext;
  ಪೂರ್ಣಾಂಕ yyleng;
  ಪೂರ್ಣಾಂಕ yylineno;       // only maintained if you use %option yylineno
  ಪೂರ್ಣಾಂಕ yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#ಆದರೆ_ಅಂತ್ಯ // FLEXLEXER_H

#ಆದರೆ defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

ಬಾಹ್ಯ "C++" {

class yyFlexLexer : ಸಾರ್ವಜನಿಕ FlexLexer {
ಸಾರ್ವಜನಿಕ:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
ಖಾಸಗಿ:
  ಶೂನ್ಯ ctor_common();

ಸಾರ್ವಜನಿಕ:

  ವಾಸ್ತವಿಕ ~yyFlexLexer();

  ಶೂನ್ಯ yy_switch_ಗಮ್ಯ_ಬಫರ್( yy_ಬಫರ್_state* new_ಬಫರ್ );
  yy_ಬಫರ್_state* yy_create_ಬಫರ್( std::istream* s, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 );
  yy_ಬಫರ್_state* yy_create_ಬಫರ್( std::istream& s, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 );
  ಶೂನ್ಯ yy_delete_ಬಫರ್( yy_ಬಫರ್_state* b );
  ಶೂನ್ಯ yyrestart( std::istream* s );
  ಶೂನ್ಯ yyrestart( std::istream& s );

  ಶೂನ್ಯ yypush_ಬಫರ್_state( yy_ಬಫರ್_state* new_ಬಫರ್ );
  ಶೂನ್ಯ yypop_ಬಫರ್_state();

  ವಾಸ್ತವಿಕ ಪೂರ್ಣಾಂಕ yyread(ಅಕ್ಷರ *buf, size_t);
  ವಾಸ್ತವಿಕ ಪೂರ್ಣಾಂಕ yylex();
  ವಾಸ್ತವಿಕ ಶೂನ್ಯ switch_streams( std::istream& new_ಒಳ, std::ostream& new_ಹೊರಹೋಗು );
  ವಾಸ್ತವಿಕ ಶೂನ್ಯ switch_streams( std::istream* new_ಒಳ = 0, std::ostream* new_ಹೊರಹೋಗು = 0 );
  ವಾಸ್ತವಿಕ ಪೂರ್ಣಾಂಕ yywrap();

ಸಂರಕ್ಷಿತ:
  ವಾಸ್ತವಿಕ ಪೂರ್ಣಾಂಕ Lexer_ಒಳಹರಿವು( ಅಕ್ಷರ* buf, ಪೂರ್ಣಾಂಕ max_ಗಾತ್ರ );
  ವಾಸ್ತವಿಕ ಶೂನ್ಯ LexerOutput( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* buf, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 );
  ವಾಸ್ತವಿಕ ಶೂನ್ಯ LexerError( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ* ಸಂದೇಶ );
			
  ಶೂನ್ಯ yyunput_r( ಪೂರ್ಣಾಂಕ c, ಅಕ್ಷರ* buf_ptr );
  ಪೂರ್ಣಾಂಕ yyinput();

  ಶೂನ್ಯ yy_ತುಂಬು_ಬಫರ್_state();
  ಶೂನ್ಯ yy_init_ಬಫರ್( yy_ಬಫರ್_state* b, std::istream& s );
  ಶೂನ್ಯ yy_flush_ಬಫರ್( yy_ಬಫರ್_state* b );

  ಪೂರ್ಣಾಂಕ yy_ಆರಂಭ_ರಾಶಿ_ptr;
  ಪೂರ್ಣಾಂಕ yy_ಆರಂಭ_ರಾಶಿ_ಆಳ;
  ಪೂರ್ಣಾಂಕ* yy_ಆರಂಭ_ರಾಶಿ;

  ಶೂನ್ಯ yy_ತಳ್ಳು_state( ಪೂರ್ಣಾಂಕ new_state );
  ಶೂನ್ಯ yy_ತೆಗೆ_state();
  ಪೂರ್ಣಾಂಕ yy_ತುದಿ_state();

  yy_state_type yy_get_ಹಿಂದಿನ_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  ಪೂರ್ಣಾಂಕ yy_get_ಮುಂದಿನ_ಬಫರ್();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  ಅಕ್ಷರ yy_hold_char;

  // Number of characters read into yy_ch_buf.
  ಪೂರ್ಣಾಂಕ yy_n_chars;

  // Points to current character in buffer.
  ಅಕ್ಷರ* yy_c_buf_p;

  ಪೂರ್ಣಾಂಕ yy_init;                // whether we need to initialize
  ಪೂರ್ಣಾಂಕ yy_ಆರಂಭ;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  ಪೂರ್ಣಾಂಕ yy_did_ಬಫರ್_switch_on_eof;


  size_t yy_ಬಫರ್_ರಾಶಿ_ತುದಿ; /**< index of top of stack. */
  size_t yy_ಬಫರ್_ರಾಶಿ_max; /**< capacity of stack. */
  yy_ಬಫರ್_state ** yy_ಬಫರ್_ರಾಶಿ; /**< Stack as an array. */
  ಶೂನ್ಯ yyensure_ಬಫರ್_ರಾಶಿ(ಶೂನ್ಯ);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_ಕೊನೆಯ_accepting_state;
  ಅಕ್ಷರ* yy_ಕೊನೆಯ_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  ಅಕ್ಷರ* yy_ತುಂಬಿದ_ಹೊಂದಿಕೆ;
  ಪೂರ್ಣಾಂಕ* yy_ತುಂಬಿದ_state;
  ಪೂರ್ಣಾಂಕ yy_ತುಂಬಿದ_lp;

  ಪೂರ್ಣಾಂಕ yy_lp;
  ಪೂರ್ಣಾಂಕ yy_looking_for_trail_begin;

  ಪೂರ್ಣಾಂಕ yy_ಇನ್ನಷ್ಟು_flag;
  ಪೂರ್ಣಾಂಕ yy_ಇನ್ನಷ್ಟು_len;
  ಪೂರ್ಣಾಂಕ yy_ಇನ್ನಷ್ಟು_ಸ್ಥಾನಾಂತರ;
  ಪೂರ್ಣಾಂಕ yy_prev_ಇನ್ನಷ್ಟು_ಸ್ಥಾನಾಂತರ;
};

}

#ಆದರೆ_ಅಂತ್ಯ // yyFlexLexer || ! yyFlexLexerOnce
