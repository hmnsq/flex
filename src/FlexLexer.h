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

#ifndef __FLEX_LEXER_H
// Never included before - need to define base class.
#define __FLEX_LEXER_H

#ಅನ್ತರ್ಭಾವ <iostream>

ಬಾಹ್ಯ "C++" {

ಸಂರಚನಾ yy_buffer_state;
ಪ್ರಕಾರನಿರ್ದೇಶ ಪೂರ್ಣಾಙ್ಕ yy_state_type;

class FlexLexer
{
ಸಾರ್ವಜನಿಕ:
  ಆಭಾಸ ~FlexLexer()        { }

  ಧ್ರುವ ವರ್ಣ* YYText() ಧ್ರುವ  { ಪ್ರತ್ಯಾಗಮ yytext; }
  ಪೂರ್ಣಾಙ್ಕ YYLeng()        ಧ್ರುವ   { ಪ್ರತ್ಯಾಗಮ yyleng; }

  ಆಭಾಸ ಶೂನ್ಯ
  yy_switch_to_buffer( yy_buffer_state* new_buffer ) = 0;
  ಆಭಾಸ yy_buffer_state* yy_create_buffer( std::istream* s, ಪೂರ್ಣಾಙ್ಕ size ) = 0;
  ಆಭಾಸ yy_buffer_state* yy_create_buffer( std::istream& s, ಪೂರ್ಣಾಙ್ಕ size ) = 0;
  ಆಭಾಸ ಶೂನ್ಯ yy_delete_buffer( yy_buffer_state* b ) = 0;
  ಆಭಾಸ ಶೂನ್ಯ yyrestart( std::istream* s ) = 0;
  ಆಭಾಸ ಶೂನ್ಯ yyrestart( std::istream& s ) = 0;

  ಆಭಾಸ ಪೂರ್ಣಾಙ್ಕ yylex() = 0;

  // Call yylex with new input/output sources.
  ಪೂರ್ಣಾಙ್ಕ yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    ಪ್ರತ್ಯಾಗಮ yylex();
  }

  ಪೂರ್ಣಾಙ್ಕ yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    ಪ್ರತ್ಯಾಗಮ yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  ಆಭಾಸ ಶೂನ್ಯ switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  ಆಭಾಸ ಶೂನ್ಯ switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  ಪೂರ್ಣಾಙ್ಕ lineno() ಧ್ರುವ          { ಪ್ರತ್ಯಾಗಮ yylineno; }

  ಪೂರ್ಣಾಙ್ಕ debug() ಧ್ರುವ           { ಪ್ರತ್ಯಾಗಮ yyflexdebug; }
  ಶೂನ್ಯ set_debug( ಪೂರ್ಣಾಙ್ಕ flag )  { yyflexdebug = flag; }

ರಕ್ಷಿತ:
  ವರ್ಣ* yytext;
  ಪೂರ್ಣಾಙ್ಕ yyleng;
  ಪೂರ್ಣಾಙ್ಕ yylineno;       // only maintained if you use %option yylineno
  ಪೂರ್ಣಾಙ್ಕ yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#ಯದಿ defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
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
ಗುಪ್ತ:
  ಶೂನ್ಯ ctor_common();

ಸಾರ್ವಜನಿಕ:

  ಆಭಾಸ ~yyFlexLexer();

  ಶೂನ್ಯ yy_switch_to_buffer( yy_buffer_state* new_buffer );
  yy_buffer_state* yy_create_buffer( std::istream* s, ಪೂರ್ಣಾಙ್ಕ size );
  yy_buffer_state* yy_create_buffer( std::istream& s, ಪೂರ್ಣಾಙ್ಕ size );
  ಶೂನ್ಯ yy_delete_buffer( yy_buffer_state* b );
  ಶೂನ್ಯ yyrestart( std::istream* s );
  ಶೂನ್ಯ yyrestart( std::istream& s );

  ಶೂನ್ಯ yypush_buffer_state( yy_buffer_state* new_buffer );
  ಶೂನ್ಯ yypop_buffer_state();

  ಆಭಾಸ ಪೂರ್ಣಾಙ್ಕ yyread(ವರ್ಣ *buf, size_t);
  ಆಭಾಸ ಪೂರ್ಣಾಙ್ಕ yylex();
  ಆಭಾಸ ಶೂನ್ಯ switch_streams( std::istream& new_in, std::ostream& new_out );
  ಆಭಾಸ ಶೂನ್ಯ switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  ಆಭಾಸ ಪೂರ್ಣಾಙ್ಕ yywrap();

ರಕ್ಷಿತ:
  ಆಭಾಸ ಪೂರ್ಣಾಙ್ಕ Lexer_ಒಳಹರಿವು( ವರ್ಣ* buf, ಪೂರ್ಣಾಙ್ಕ max_size );
  ಆಭಾಸ ಶೂನ್ಯ LexerOutput( ಧ್ರುವ ವರ್ಣ* buf, ಪೂರ್ಣಾಙ್ಕ size );
  ಆಭಾಸ ಶೂನ್ಯ LexerError( ಧ್ರುವ ವರ್ಣ* ಸಂದೇಶ );
			
  ಶೂನ್ಯ yyunput_r( ಪೂರ್ಣಾಙ್ಕ c, ವರ್ಣ* buf_ptr );
  ಪೂರ್ಣಾಙ್ಕ yyinput();

  ಶೂನ್ಯ yy_load_buffer_state();
  ಶೂನ್ಯ yy_init_buffer( yy_buffer_state* b, std::istream& s );
  ಶೂನ್ಯ yy_flush_buffer( yy_buffer_state* b );

  ಪೂರ್ಣಾಙ್ಕ yy_start_ರಾಶಿ_ptr;
  ಪೂರ್ಣಾಙ್ಕ yy_start_ರಾಶಿ_depth;
  ಪೂರ್ಣಾಙ್ಕ* yy_start_ರಾಶಿ;

  ಶೂನ್ಯ yy_ತಳ್ಳು_state( ಪೂರ್ಣಾಙ್ಕ new_state );
  ಶೂನ್ಯ yy_ತೆಗೆ_state();
  ಪೂರ್ಣಾಙ್ಕ yy_ತುದಿ_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  ಪೂರ್ಣಾಙ್ಕ yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  ವರ್ಣ yy_hold_char;

  // Number of characters read into yy_ch_buf.
  ಪೂರ್ಣಾಙ್ಕ yy_n_chars;

  // Points to current character in buffer.
  ವರ್ಣ* yy_c_buf_p;

  ಪೂರ್ಣಾಙ್ಕ yy_init;                // whether we need to initialize
  ಪೂರ್ಣಾಙ್ಕ yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  ಪೂರ್ಣಾಙ್ಕ yy_did_buffer_switch_on_eof;


  size_t yy_buffer_ರಾಶಿ_ತುದಿ; /**< index of top of stack. */
  size_t yy_buffer_ರಾಶಿ_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_ರಾಶಿ; /**< Stack as an array. */
  ಶೂನ್ಯ yyensure_buffer_ರಾಶಿ(ಶೂನ್ಯ);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  ವರ್ಣ* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  ವರ್ಣ* yy_full_match;
  ಪೂರ್ಣಾಙ್ಕ* yy_full_state;
  ಪೂರ್ಣಾಙ್ಕ yy_full_lp;

  ಪೂರ್ಣಾಙ್ಕ yy_lp;
  ಪೂರ್ಣಾಙ್ಕ yy_looking_for_trail_begin;

  ಪೂರ್ಣಾಙ್ಕ yy_more_flag;
  ಪೂರ್ಣಾಙ್ಕ yy_more_len;
  ಪೂರ್ಣಾಙ್ಕ yy_more_offset;
  ಪೂರ್ಣಾಙ್ಕ yy_prev_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
