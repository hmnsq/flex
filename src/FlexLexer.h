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

#include <iostream>

extern "C++" {

sa_nracanaa yy_buffer_state;
typedef ကိန်းပြည့် yy_state_type;

class FlexLexer
{
public:
  virtual ~FlexLexer()        { }

  const var_na* YYText() const  { ပြန်ပေး yytext; }
  ကိန်းပြည့် YYLeng()        const   { ပြန်ပေး yyleng; }

  virtual void
  yy_switch_to_buffer( yy_buffer_state* new_buffer ) = 0;
  virtual yy_buffer_state* yy_create_buffer( std::istream* s, ကိန်းပြည့် size ) = 0;
  virtual yy_buffer_state* yy_create_buffer( std::istream& s, ကိန်းပြည့် size ) = 0;
  virtual void yy_delete_buffer( yy_buffer_state* b ) = 0;
  virtual void yyrestart( std::istream* s ) = 0;
  virtual void yyrestart( std::istream& s ) = 0;

  virtual ကိန်းပြည့် yylex() = 0;

  // Call yylex with new input/output sources.
  ကိန်းပြည့် yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    ပြန်ပေး yylex();
  }

  ကိန်းပြည့် yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    ပြန်ပေး yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  virtual void switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  virtual void switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  ကိန်းပြည့် lineno() const          { ပြန်ပေး yylineno; }

  ကိန်းပြည့် debug() const           { ပြန်ပေး yyflexdebug; }
  void set_debug( ကိန်းပြည့် flag )  { yyflexdebug = flag; }

rak_sita:
  var_na* yytext;
  ကိန်းပြည့် yyleng;
  ကိန်းပြည့် yylineno;       // only maintained if you use %option yylineno
  ကိန်းပြည့် yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#အကယ်၍ defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

extern "C++" {

class yyFlexLexer : public FlexLexer {
public:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
private:
  void ctor_common();

public:

  virtual ~yyFlexLexer();

  void yy_switch_to_buffer( yy_buffer_state* new_buffer );
  yy_buffer_state* yy_create_buffer( std::istream* s, ကိန်းပြည့် size );
  yy_buffer_state* yy_create_buffer( std::istream& s, ကိန်းပြည့် size );
  void yy_delete_buffer( yy_buffer_state* b );
  void yyrestart( std::istream* s );
  void yyrestart( std::istream& s );

  void yypush_buffer_state( yy_buffer_state* new_buffer );
  void yypop_buffer_state();

  virtual ကိန်းပြည့် yyread(var_na *buf, size_t);
  virtual ကိန်းပြည့် yylex();
  virtual void switch_streams( std::istream& new_in, std::ostream& new_out );
  virtual void switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  virtual ကိန်းပြည့် yywrap();

rak_sita:
  virtual ကိန်းပြည့် LexerInput( var_na* buf, ကိန်းပြည့် max_size );
  virtual void LexerOutput( const var_na* buf, ကိန်းပြည့် size );
  virtual void LexerError( const var_na* msg );
			
  void yyunput_r( ကိန်းပြည့် c, var_na* buf_ptr );
  ကိန်းပြည့် yyinput();

  void yy_load_buffer_state();
  void yy_init_buffer( yy_buffer_state* b, std::istream& s );
  void yy_flush_buffer( yy_buffer_state* b );

  ကိန်းပြည့် yy_start_stack_ptr;
  ကိန်းပြည့် yy_start_stack_depth;
  ကိန်းပြည့်* yy_start_stack;

  void yy_push_state( ကိန်းပြည့် new_state );
  void yy_pop_state();
  ကိန်းပြည့် yy_top_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  ကိန်းပြည့် yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  var_na yy_hold_char;

  // Number of characters read into yy_ch_buf.
  ကိန်းပြည့် yy_n_chars;

  // Points to current character in buffer.
  var_na* yy_c_buf_p;

  ကိန်းပြည့် yy_init;                // whether we need to initialize
  ကိန်းပြည့် yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  ကိန်းပြည့် yy_did_buffer_switch_on_eof;


  size_t yy_buffer_stack_top; /**< index of top of stack. */
  size_t yy_buffer_stack_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_stack; /**< Stack as an array. */
  void yyensure_buffer_stack(void);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  var_na* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  var_na* yy_full_match;
  ကိန်းပြည့်* yy_full_state;
  ကိန်းပြည့် yy_full_lp;

  ကိန်းပြည့် yy_lp;
  ကိန်းပြည့် yy_looking_for_trail_begin;

  ကိန်းပြည့် yy_more_flag;
  ကိန်းပြည့် yy_more_len;
  ကိန်းပြည့် yy_more_offset;
  ကိန်းပြည့် yy_prev_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
