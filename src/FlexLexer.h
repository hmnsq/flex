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

#جے_بنا_تعریف __FLEX_LEXER_H
// Never included before - need to define base class.
#تعریف_کرو __FLEX_LEXER_H

#ضمن <iostream>

خارجي "C++" {

بنية yy_بفر_state;
تعريفنوع صحيح yy_state_type;

class FlexLexer
{
عام:
  مجازی ~FlexLexer()        { }

  ثابت حرف* YYText() ثابت  { أرجع yytext; }
  صحيح YYLeng()        ثابت   { أرجع yyleng; }

  مجازی فراغ
  yy_switch_منزل_بفر( yy_بفر_state* new_بفر ) = 0;
  مجازی yy_بفر_state* yy_create_بفر( std::istream* s, صحيح ناپ ) = 0;
  مجازی yy_بفر_state* yy_create_بفر( std::istream& s, صحيح ناپ ) = 0;
  مجازی فراغ yy_delete_بفر( yy_بفر_state* b ) = 0;
  مجازی فراغ yyrestart( std::istream* s ) = 0;
  مجازی فراغ yyrestart( std::istream& s ) = 0;

  مجازی صحيح yylex() = 0;

  // Call yylex with new input/output sources.
  صحيح yylex( std::istream& new_وچ, std::ostream& new_باہرلا )
  {
    switch_streams( new_وچ, new_باہرلا );
    أرجع yylex();
  }

  صحيح yylex( std::istream* new_وچ, std::ostream* new_باہرلا = 0)
  {
    switch_streams( new_وچ, new_باہرلا );
    أرجع yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  مجازی فراغ switch_streams( std::istream* new_وچ,
                               std::ostream* new_باہرلا ) = 0;
  مجازی فراغ switch_streams( std::istream& new_وچ,
                               std::ostream& new_باہرلا ) = 0;

  صحيح lineno() ثابت          { أرجع yylineno; }

  صحيح debug() ثابت           { أرجع yyflexdebug; }
  فراغ سیٹ_debug( صحيح flag )  { yyflexdebug = flag; }

محمي:
  حرف* yytext;
  صحيح yyleng;
  صحيح yylineno;       // only maintained if you use %option yylineno
  صحيح yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#جے_انت // FLEXLEXER_H

#إذا defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

خارجي "C++" {

class yyFlexLexer : عام FlexLexer {
عام:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
خاص:
  فراغ ctor_common();

عام:

  مجازی ~yyFlexLexer();

  فراغ yy_switch_منزل_بفر( yy_بفر_state* new_بفر );
  yy_بفر_state* yy_create_بفر( std::istream* s, صحيح ناپ );
  yy_بفر_state* yy_create_بفر( std::istream& s, صحيح ناپ );
  فراغ yy_delete_بفر( yy_بفر_state* b );
  فراغ yyrestart( std::istream* s );
  فراغ yyrestart( std::istream& s );

  فراغ yypush_بفر_state( yy_بفر_state* new_بفر );
  فراغ yypop_بفر_state();

  مجازی صحيح yyread(حرف *buf, size_t);
  مجازی صحيح yylex();
  مجازی فراغ switch_streams( std::istream& new_وچ, std::ostream& new_باہرلا );
  مجازی فراغ switch_streams( std::istream* new_وچ = 0, std::ostream* new_باہرلا = 0 );
  مجازی صحيح yywrap();

محمي:
  مجازی صحيح Lexer_داخلہ( حرف* buf, صحيح max_ناپ );
  مجازی فراغ LexerOutput( ثابت حرف* buf, صحيح ناپ );
  مجازی فراغ LexerError( ثابت حرف* پیغام );
			
  فراغ yyunput_r( صحيح c, حرف* buf_ptr );
  صحيح yyinput();

  فراغ yy_لدو_بفر_state();
  فراغ yy_init_بفر( yy_بفر_state* b, std::istream& s );
  فراغ yy_flush_بفر( yy_بفر_state* b );

  صحيح yy_شروع_ڈھیر_ptr;
  صحيح yy_شروع_ڈھیر_ڈونگھائی;
  صحيح* yy_شروع_ڈھیر;

  فراغ yy_ڈالو_state( صحيح new_state );
  فراغ yy_نکالو_state();
  صحيح yy_چوٹی_state();

  yy_state_type yy_get_پچھلا_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  صحيح yy_get_اگلا_بفر();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  حرف yy_hold_char;

  // Number of characters read into yy_ch_buf.
  صحيح yy_n_chars;

  // Points to current character in buffer.
  حرف* yy_c_buf_p;

  صحيح yy_init;                // whether we need to initialize
  صحيح yy_شروع;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  صحيح yy_did_بفر_switch_on_eof;


  size_t yy_بفر_ڈھیر_چوٹی; /**< index of top of stack. */
  size_t yy_بفر_ڈھیر_max; /**< capacity of stack. */
  yy_بفر_state ** yy_بفر_ڈھیر; /**< Stack as an array. */
  فراغ yyensure_بفر_ڈھیر(فراغ);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_آخری_accepting_state;
  حرف* yy_آخری_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  حرف* yy_بھریا_میل;
  صحيح* yy_بھریا_state;
  صحيح yy_بھریا_lp;

  صحيح yy_lp;
  صحيح yy_looking_for_trail_begin;

  صحيح yy_ہور_flag;
  صحيح yy_ہور_len;
  صحيح yy_ہور_وتھ;
  صحيح yy_prev_ہور_وتھ;
};

}

#جے_انت // yyFlexLexer || ! yyFlexLexerOnce
