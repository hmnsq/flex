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

#شامل <iostream>

بیرونی "C++" {

ساختار yy_buffer_state;
تعریفنوع صحیح yy_state_type;

class FlexLexer
{
عمومی:
  مجازی ~FlexLexer()        { }

  ثابت نویسه* YYText() ثابت  { بازگشت yytext; }
  صحیح YYLeng()        ثابت   { بازگشت yyleng; }

  مجازی تهی
  yy_switch_to_buffer( yy_buffer_state* new_buffer ) = 0;
  مجازی yy_buffer_state* yy_create_buffer( std::istream* s, صحیح size ) = 0;
  مجازی yy_buffer_state* yy_create_buffer( std::istream& s, صحیح size ) = 0;
  مجازی تهی yy_delete_buffer( yy_buffer_state* b ) = 0;
  مجازی تهی yyrestart( std::istream* s ) = 0;
  مجازی تهی yyrestart( std::istream& s ) = 0;

  مجازی صحیح yylex() = 0;

  // Call yylex with new input/output sources.
  صحیح yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    بازگشت yylex();
  }

  صحیح yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    بازگشت yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  مجازی تهی switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  مجازی تهی switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  صحیح lineno() ثابت          { بازگشت yylineno; }

  صحیح debug() ثابت           { بازگشت yyflexdebug; }
  تهی set_debug( صحیح flag )  { yyflexdebug = flag; }

محافظتشده:
  نویسه* yytext;
  صحیح yyleng;
  صحیح yylineno;       // only maintained if you use %option yylineno
  صحیح yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#اگر defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

بیرونی "C++" {

class yyFlexLexer : عمومی FlexLexer {
عمومی:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
خصوصی:
  تهی ctor_common();

عمومی:

  مجازی ~yyFlexLexer();

  تهی yy_switch_to_buffer( yy_buffer_state* new_buffer );
  yy_buffer_state* yy_create_buffer( std::istream* s, صحیح size );
  yy_buffer_state* yy_create_buffer( std::istream& s, صحیح size );
  تهی yy_delete_buffer( yy_buffer_state* b );
  تهی yyrestart( std::istream* s );
  تهی yyrestart( std::istream& s );

  تهی yypush_buffer_state( yy_buffer_state* new_buffer );
  تهی yypop_buffer_state();

  مجازی صحیح yyread(نویسه *buf, size_t);
  مجازی صحیح yylex();
  مجازی تهی switch_streams( std::istream& new_in, std::ostream& new_out );
  مجازی تهی switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  مجازی صحیح yywrap();

محافظتشده:
  مجازی صحیح Lexer_درون_داد( نویسه* buf, صحیح max_size );
  مجازی تهی LexerOutput( ثابت نویسه* buf, صحیح size );
  مجازی تهی LexerError( ثابت نویسه* پیام );
			
  تهی yyunput_r( صحیح c, نویسه* buf_ptr );
  صحیح yyinput();

  تهی yy_load_buffer_state();
  تهی yy_init_buffer( yy_buffer_state* b, std::istream& s );
  تهی yy_flush_buffer( yy_buffer_state* b );

  صحیح yy_start_پشته_ptr;
  صحیح yy_start_پشته_depth;
  صحیح* yy_start_پشته;

  تهی yy_افزودن_state( صحیح new_state );
  تهی yy_برداشت_state();
  صحیح yy_بالاترین_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  صحیح yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  نویسه yy_hold_char;

  // Number of characters read into yy_ch_buf.
  صحیح yy_n_chars;

  // Points to current character in buffer.
  نویسه* yy_c_buf_p;

  صحیح yy_init;                // whether we need to initialize
  صحیح yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  صحیح yy_did_buffer_switch_on_eof;


  size_t yy_buffer_پشته_بالاترین; /**< index of top of stack. */
  size_t yy_buffer_پشته_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_پشته; /**< Stack as an array. */
  تهی yyensure_buffer_پشته(تهی);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  نویسه* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  نویسه* yy_full_match;
  صحیح* yy_full_state;
  صحیح yy_full_lp;

  صحیح yy_lp;
  صحیح yy_looking_for_trail_begin;

  صحیح yy_more_flag;
  صحیح yy_more_len;
  صحیح yy_more_offset;
  صحیح yy_prev_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
