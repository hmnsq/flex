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

#অন্তর্ভাৱ <iostream>

বাহ্য "C++" {

সংরচনা yy_buffer_state;
প্রকারনির্দেশ পূর্ণাঙ্ক yy_state_type;

class FlexLexer
{
সার্ৱজনিক:
  আভাস ~FlexLexer()        { }

  ধ্রুৱ ৱর্ণ* YYText() ধ্রুৱ  { ঘূৰাই yytext; }
  পূর্ণাঙ্ক YYLeng()        ধ্রুৱ   { ঘূৰাই yyleng; }

  আভাস শূন্য
  yy_switch_to_buffer( yy_buffer_state* new_buffer ) = 0;
  আভাস yy_buffer_state* yy_create_buffer( std::istream* s, পূর্ণাঙ্ক size ) = 0;
  আভাস yy_buffer_state* yy_create_buffer( std::istream& s, পূর্ণাঙ্ক size ) = 0;
  আভাস শূন্য yy_delete_buffer( yy_buffer_state* b ) = 0;
  আভাস শূন্য yyrestart( std::istream* s ) = 0;
  আভাস শূন্য yyrestart( std::istream& s ) = 0;

  আভাস পূর্ণাঙ্ক yylex() = 0;

  // Call yylex with new input/output sources.
  পূর্ণাঙ্ক yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    ঘূৰাই yylex();
  }

  পূর্ণাঙ্ক yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    ঘূৰাই yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  আভাস শূন্য switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  আভাস শূন্য switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  পূর্ণাঙ্ক lineno() ধ্রুৱ          { ঘূৰাই yylineno; }

  পূর্ণাঙ্ক debug() ধ্রুৱ           { ঘূৰাই yyflexdebug; }
  শূন্য set_debug( পূর্ণাঙ্ক flag )  { yyflexdebug = flag; }

রক্ষিত:
  ৱর্ণ* yytext;
  পূর্ণাঙ্ক yyleng;
  পূর্ণাঙ্ক yylineno;       // only maintained if you use %option yylineno
  পূর্ণাঙ্ক yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#যদি defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

বাহ্য "C++" {

class yyFlexLexer : সার্ৱজনিক FlexLexer {
সার্ৱজনিক:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
গুপ্ত:
  শূন্য ctor_common();

সার্ৱজনিক:

  আভাস ~yyFlexLexer();

  শূন্য yy_switch_to_buffer( yy_buffer_state* new_buffer );
  yy_buffer_state* yy_create_buffer( std::istream* s, পূর্ণাঙ্ক size );
  yy_buffer_state* yy_create_buffer( std::istream& s, পূর্ণাঙ্ক size );
  শূন্য yy_delete_buffer( yy_buffer_state* b );
  শূন্য yyrestart( std::istream* s );
  শূন্য yyrestart( std::istream& s );

  শূন্য yypush_buffer_state( yy_buffer_state* new_buffer );
  শূন্য yypop_buffer_state();

  আভাস পূর্ণাঙ্ক yyread(ৱর্ণ *buf, size_t);
  আভাস পূর্ণাঙ্ক yylex();
  আভাস শূন্য switch_streams( std::istream& new_in, std::ostream& new_out );
  আভাস শূন্য switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  আভাস পূর্ণাঙ্ক yywrap();

রক্ষিত:
  আভাস পূর্ণাঙ্ক Lexer_প্ৰবেশ( ৱর্ণ* buf, পূর্ণাঙ্ক max_size );
  আভাস শূন্য LexerOutput( ধ্রুৱ ৱর্ণ* buf, পূর্ণাঙ্ক size );
  আভাস শূন্য LexerError( ধ্রুৱ ৱর্ণ* বাৰ্তা );
			
  শূন্য yyunput_r( পূর্ণাঙ্ক c, ৱর্ণ* buf_ptr );
  পূর্ণাঙ্ক yyinput();

  শূন্য yy_load_buffer_state();
  শূন্য yy_init_buffer( yy_buffer_state* b, std::istream& s );
  শূন্য yy_flush_buffer( yy_buffer_state* b );

  পূর্ণাঙ্ক yy_start_স্তূপ_ptr;
  পূর্ণাঙ্ক yy_start_স্তূপ_depth;
  পূর্ণাঙ্ক* yy_start_স্তূপ;

  শূন্য yy_ঠেলো_state( পূর্ণাঙ্ক new_state );
  শূন্য yy_বেৰ_কৰো_state();
  পূর্ণাঙ্ক yy_শীৰ্ষ_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  পূর্ণাঙ্ক yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  ৱর্ণ yy_hold_char;

  // Number of characters read into yy_ch_buf.
  পূর্ণাঙ্ক yy_n_chars;

  // Points to current character in buffer.
  ৱর্ণ* yy_c_buf_p;

  পূর্ণাঙ্ক yy_init;                // whether we need to initialize
  পূর্ণাঙ্ক yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  পূর্ণাঙ্ক yy_did_buffer_switch_on_eof;


  size_t yy_buffer_স্তূপ_শীৰ্ষ; /**< index of top of stack. */
  size_t yy_buffer_স্তূপ_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_স্তূপ; /**< Stack as an array. */
  শূন্য yyensure_buffer_স্তূপ(শূন্য);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  ৱর্ণ* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  ৱর্ণ* yy_full_match;
  পূর্ণাঙ্ক* yy_full_state;
  পূর্ণাঙ্ক yy_full_lp;

  পূর্ণাঙ্ক yy_lp;
  পূর্ণাঙ্ক yy_looking_for_trail_begin;

  পূর্ণাঙ্ক yy_more_flag;
  পূর্ণাঙ্ক yy_more_len;
  পূর্ণাঙ্ক yy_more_offset;
  পূর্ণাঙ্ক yy_prev_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
