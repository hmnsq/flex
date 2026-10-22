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

#اگر_غیر_تعریف_شدہ __FLEX_LEXER_H
// Never included before - need to define base class.
#تعریف_کرو __FLEX_LEXER_H

#شامل <iostream>

خارجی "C++" {

ساخت yy_بفر_state;
قسمتعریف صحیح yy_state_type;

class FlexLexer
{
عوامی:
  مجازی ~FlexLexer()        { }

  ثابت حرف* YYText() ثابت  { واپس yytext; }
  صحیح YYLeng()        ثابت   { واپس yyleng; }

  مجازی خالی
  yy_switch_مقصد_بفر( yy_بفر_state* new_بفر ) = 0;
  مجازی yy_بفر_state* yy_create_بفر( std::istream* s, صحیح سائز ) = 0;
  مجازی yy_بفر_state* yy_create_بفر( std::istream& s, صحیح سائز ) = 0;
  مجازی خالی yy_delete_بفر( yy_بفر_state* b ) = 0;
  مجازی خالی yyrestart( std::istream* s ) = 0;
  مجازی خالی yyrestart( std::istream& s ) = 0;

  مجازی صحیح yylex() = 0;

  // Call yylex with new input/output sources.
  صحیح yylex( std::istream& new_اندر, std::ostream& new_برآمد )
  {
    switch_streams( new_اندر, new_برآمد );
    واپس yylex();
  }

  صحیح yylex( std::istream* new_اندر, std::ostream* new_برآمد = 0)
  {
    switch_streams( new_اندر, new_برآمد );
    واپس yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  مجازی خالی switch_streams( std::istream* new_اندر,
                               std::ostream* new_برآمد ) = 0;
  مجازی خالی switch_streams( std::istream& new_اندر,
                               std::ostream& new_برآمد ) = 0;

  صحیح lineno() ثابت          { واپس yylineno; }

  صحیح debug() ثابت           { واپس yyflexdebug; }
  خالی سیٹ_debug( صحیح flag )  { yyflexdebug = flag; }

محفوظ:
  حرف* yytext;
  صحیح yyleng;
  صحیح yylineno;       // only maintained if you use %option yylineno
  صحیح yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#اگر_ختم // FLEXLEXER_H

#اگر defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

خارجی "C++" {

class yyFlexLexer : عوامی FlexLexer {
عوامی:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
نجی:
  خالی ctor_common();

عوامی:

  مجازی ~yyFlexLexer();

  خالی yy_switch_مقصد_بفر( yy_بفر_state* new_بفر );
  yy_بفر_state* yy_create_بفر( std::istream* s, صحیح سائز );
  yy_بفر_state* yy_create_بفر( std::istream& s, صحیح سائز );
  خالی yy_delete_بفر( yy_بفر_state* b );
  خالی yyrestart( std::istream* s );
  خالی yyrestart( std::istream& s );

  خالی yypush_بفر_state( yy_بفر_state* new_بفر );
  خالی yypop_بفر_state();

  مجازی صحیح yyread(حرف *buf, size_t);
  مجازی صحیح yylex();
  مجازی خالی switch_streams( std::istream& new_اندر, std::ostream& new_برآمد );
  مجازی خالی switch_streams( std::istream* new_اندر = 0, std::ostream* new_برآمد = 0 );
  مجازی صحیح yywrap();

محفوظ:
  مجازی صحیح Lexer_داخلہ( حرف* buf, صحیح max_سائز );
  مجازی خالی LexerOutput( ثابت حرف* buf, صحیح سائز );
  مجازی خالی LexerError( ثابت حرف* پیغام );
			
  خالی yyunput_r( صحیح c, حرف* buf_ptr );
  صحیح yyinput();

  خالی yy_بھرو_بفر_state();
  خالی yy_init_بفر( yy_بفر_state* b, std::istream& s );
  خالی yy_flush_بفر( yy_بفر_state* b );

  صحیح yy_آغاز_ڈھیر_ptr;
  صحیح yy_آغاز_ڈھیر_گہرائی;
  صحیح* yy_آغاز_ڈھیر;

  خالی yy_ڈالو_state( صحیح new_state );
  خالی yy_نکالو_state();
  صحیح yy_چوٹی_state();

  yy_state_type yy_get_پچھلا_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  صحیح yy_get_اگلا_بفر();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  حرف yy_hold_char;

  // Number of characters read into yy_ch_buf.
  صحیح yy_n_chars;

  // Points to current character in buffer.
  حرف* yy_c_buf_p;

  صحیح yy_init;                // whether we need to initialize
  صحیح yy_آغاز;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  صحیح yy_did_بفر_switch_on_eof;


  size_t yy_بفر_ڈھیر_چوٹی; /**< index of top of stack. */
  size_t yy_بفر_ڈھیر_max; /**< capacity of stack. */
  yy_بفر_state ** yy_بفر_ڈھیر; /**< Stack as an array. */
  خالی yyensure_بفر_ڈھیر(خالی);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_آخری_accepting_state;
  حرف* yy_آخری_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  حرف* yy_بھرا_مطابقت;
  صحیح* yy_بھرا_state;
  صحیح yy_بھرا_lp;

  صحیح yy_lp;
  صحیح yy_looking_for_trail_begin;

  صحیح yy_مزید_flag;
  صحیح yy_مزید_len;
  صحیح yy_مزید_انحراف;
  صحیح yy_پچھلا_مزید_انحراف;
};

}

#اگر_ختم // yyFlexLexer || ! yyFlexLexerOnce
