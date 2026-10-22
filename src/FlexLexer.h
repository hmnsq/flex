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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __FLEX_LEXER_H
// Never included before - need to define base class.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __FLEX_LEXER_H

#ਅਨ੍ਤਰ੍ਭਾਵ <iostream>

ਬਾਹਰੀ "C++" {

ਬਣਤਰ yy_ਬਫਰ_state;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ yy_state_type;

class FlexLexer
{
ਜਨਤਕ:
  ਆਭਾਸੀ ~FlexLexer()        { }

  ਅਚਲ ਅੱਖਰ* YYText() ਅਚਲ  { ਵਾਪਸ yytext; }
  ਪੂਰਨ YYLeng()        ਅਚਲ   { ਵਾਪਸ yyleng; }

  ਆਭਾਸੀ ਖਾਲੀ
  yy_switch_ਮੰਜ਼ਿਲ_ਬਫਰ( yy_ਬਫਰ_state* new_ਬਫਰ ) = 0;
  ਆਭਾਸੀ yy_ਬਫਰ_state* yy_create_ਬਫਰ( std::istream* s, ਪੂਰਨ ਮਾਪ ) = 0;
  ਆਭਾਸੀ yy_ਬਫਰ_state* yy_create_ਬਫਰ( std::istream& s, ਪੂਰਨ ਮਾਪ ) = 0;
  ਆਭਾਸੀ ਖਾਲੀ yy_delete_ਬਫਰ( yy_ਬਫਰ_state* b ) = 0;
  ਆਭਾਸੀ ਖਾਲੀ yyrestart( std::istream* s ) = 0;
  ਆਭਾਸੀ ਖਾਲੀ yyrestart( std::istream& s ) = 0;

  ਆਭਾਸੀ ਪੂਰਨ yylex() = 0;

  // Call yylex with new input/output sources.
  ਪੂਰਨ yylex( std::istream& new_ਵਿੱਚ, std::ostream& new_ਬਾਹਰਲਾ )
  {
    switch_streams( new_ਵਿੱਚ, new_ਬਾਹਰਲਾ );
    ਵਾਪਸ yylex();
  }

  ਪੂਰਨ yylex( std::istream* new_ਵਿੱਚ, std::ostream* new_ਬਾਹਰਲਾ = 0)
  {
    switch_streams( new_ਵਿੱਚ, new_ਬਾਹਰਲਾ );
    ਵਾਪਸ yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  ਆਭਾਸੀ ਖਾਲੀ switch_streams( std::istream* new_ਵਿੱਚ,
                               std::ostream* new_ਬਾਹਰਲਾ ) = 0;
  ਆਭਾਸੀ ਖਾਲੀ switch_streams( std::istream& new_ਵਿੱਚ,
                               std::ostream& new_ਬਾਹਰਲਾ ) = 0;

  ਪੂਰਨ lineno() ਅਚਲ          { ਵਾਪਸ yylineno; }

  ਪੂਰਨ debug() ਅਚਲ           { ਵਾਪਸ yyflexdebug; }
  ਖਾਲੀ ਸੈੱਟ_debug( ਪੂਰਨ flag )  { yyflexdebug = flag; }

ਸੁਰੱਖਿਅਤ:
  ਅੱਖਰ* yytext;
  ਪੂਰਨ yyleng;
  ਪੂਰਨ yylineno;       // only maintained if you use %option yylineno
  ਪੂਰਨ yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#ਜੇ_ਅੰਤ // FLEXLEXER_H

#ਜੇ defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

ਬਾਹਰੀ "C++" {

class yyFlexLexer : ਜਨਤਕ FlexLexer {
ਜਨਤਕ:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
ਨਿਜੀ:
  ਖਾਲੀ ctor_common();

ਜਨਤਕ:

  ਆਭਾਸੀ ~yyFlexLexer();

  ਖਾਲੀ yy_switch_ਮੰਜ਼ਿਲ_ਬਫਰ( yy_ਬਫਰ_state* new_ਬਫਰ );
  yy_ਬਫਰ_state* yy_create_ਬਫਰ( std::istream* s, ਪੂਰਨ ਮਾਪ );
  yy_ਬਫਰ_state* yy_create_ਬਫਰ( std::istream& s, ਪੂਰਨ ਮਾਪ );
  ਖਾਲੀ yy_delete_ਬਫਰ( yy_ਬਫਰ_state* b );
  ਖਾਲੀ yyrestart( std::istream* s );
  ਖਾਲੀ yyrestart( std::istream& s );

  ਖਾਲੀ yypush_ਬਫਰ_state( yy_ਬਫਰ_state* new_ਬਫਰ );
  ਖਾਲੀ yypop_ਬਫਰ_state();

  ਆਭਾਸੀ ਪੂਰਨ yyread(ਅੱਖਰ *buf, size_t);
  ਆਭਾਸੀ ਪੂਰਨ yylex();
  ਆਭਾਸੀ ਖਾਲੀ switch_streams( std::istream& new_ਵਿੱਚ, std::ostream& new_ਬਾਹਰਲਾ );
  ਆਭਾਸੀ ਖਾਲੀ switch_streams( std::istream* new_ਵਿੱਚ = 0, std::ostream* new_ਬਾਹਰਲਾ = 0 );
  ਆਭਾਸੀ ਪੂਰਨ yywrap();

ਸੁਰੱਖਿਅਤ:
  ਆਭਾਸੀ ਪੂਰਨ Lexer_ਨਿਵੇਸ਼( ਅੱਖਰ* buf, ਪੂਰਨ max_ਮਾਪ );
  ਆਭਾਸੀ ਖਾਲੀ LexerOutput( ਅਚਲ ਅੱਖਰ* buf, ਪੂਰਨ ਮਾਪ );
  ਆਭਾਸੀ ਖਾਲੀ LexerError( ਅਚਲ ਅੱਖਰ* ਸੁਨੇਹਾ );
			
  ਖਾਲੀ yyunput_r( ਪੂਰਨ c, ਅੱਖਰ* buf_ptr );
  ਪੂਰਨ yyinput();

  ਖਾਲੀ yy_ਲੱਦੋ_ਬਫਰ_state();
  ਖਾਲੀ yy_init_ਬਫਰ( yy_ਬਫਰ_state* b, std::istream& s );
  ਖਾਲੀ yy_flush_ਬਫਰ( yy_ਬਫਰ_state* b );

  ਪੂਰਨ yy_ਸ਼ੁਰੂ_ਢੇਰ_ptr;
  ਪੂਰਨ yy_ਸ਼ੁਰੂ_ਢੇਰ_ਡੂੰਘਾਈ;
  ਪੂਰਨ* yy_ਸ਼ੁਰੂ_ਢੇਰ;

  ਖਾਲੀ yy_ਧੱਕੋ_state( ਪੂਰਨ new_state );
  ਖਾਲੀ yy_ਕੱਢੋ_state();
  ਪੂਰਨ yy_ਸਿਖਰ_state();

  yy_state_type yy_get_ਪਿਛਲਾ_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  ਪੂਰਨ yy_get_ਅਗਲਾ_ਬਫਰ();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  ਅੱਖਰ yy_hold_char;

  // Number of characters read into yy_ch_buf.
  ਪੂਰਨ yy_n_chars;

  // Points to current character in buffer.
  ਅੱਖਰ* yy_c_buf_p;

  ਪੂਰਨ yy_init;                // whether we need to initialize
  ਪੂਰਨ yy_ਸ਼ੁਰੂ;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  ਪੂਰਨ yy_did_ਬਫਰ_switch_on_eof;


  size_t yy_ਬਫਰ_ਢੇਰ_ਸਿਖਰ; /**< index of top of stack. */
  size_t yy_ਬਫਰ_ਢੇਰ_max; /**< capacity of stack. */
  yy_ਬਫਰ_state ** yy_ਬਫਰ_ਢੇਰ; /**< Stack as an array. */
  ਖਾਲੀ yyensure_ਬਫਰ_ਢੇਰ(ਖਾਲੀ);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_ਆਖਰੀ_accepting_state;
  ਅੱਖਰ* yy_ਆਖਰੀ_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  ਅੱਖਰ* yy_ਭਰਿਆ_ਮੇਲ;
  ਪੂਰਨ* yy_ਭਰਿਆ_state;
  ਪੂਰਨ yy_ਭਰਿਆ_lp;

  ਪੂਰਨ yy_lp;
  ਪੂਰਨ yy_looking_for_trail_begin;

  ਪੂਰਨ yy_ਹੋਰ_flag;
  ਪੂਰਨ yy_ਹੋਰ_len;
  ਪੂਰਨ yy_ਹੋਰ_ਵਿੱਥ;
  ਪੂਰਨ yy_prev_ਹੋਰ_ਵਿੱਥ;
};

}

#ਜੇ_ਅੰਤ // yyFlexLexer || ! yyFlexLexerOnce
