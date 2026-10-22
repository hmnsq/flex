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

struct yy_buffer_state;
typedef 整数 yy_state_type;

class FlexLexer
{
public:
  virtual ~FlexLexer()        { }

  const char* YYText() const  { 戻る yytext; }
  整数 YYLeng()        const   { 戻る yyleng; }

  virtual void
  yy_switch_to_buffer( yy_buffer_state* new_buffer ) = 0;
  virtual yy_buffer_state* yy_create_buffer( std::istream* s, 整数 size ) = 0;
  virtual yy_buffer_state* yy_create_buffer( std::istream& s, 整数 size ) = 0;
  virtual void yy_delete_buffer( yy_buffer_state* b ) = 0;
  virtual void yyrestart( std::istream* s ) = 0;
  virtual void yyrestart( std::istream& s ) = 0;

  virtual 整数 yylex() = 0;

  // Call yylex with new input/output sources.
  整数 yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    戻る yylex();
  }

  整数 yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    戻る yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  virtual void switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  virtual void switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  整数 lineno() const          { 戻る yylineno; }

  整数 debug() const           { 戻る yyflexdebug; }
  void set_debug( 整数 flag )  { yyflexdebug = flag; }

protected:
  char* yytext;
  整数 yyleng;
  整数 yylineno;       // only maintained if you use %option yylineno
  整数 yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#もし defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
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
  yy_buffer_state* yy_create_buffer( std::istream* s, 整数 size );
  yy_buffer_state* yy_create_buffer( std::istream& s, 整数 size );
  void yy_delete_buffer( yy_buffer_state* b );
  void yyrestart( std::istream* s );
  void yyrestart( std::istream& s );

  void yypush_buffer_state( yy_buffer_state* new_buffer );
  void yypop_buffer_state();

  virtual 整数 yyread(char *buf, size_t);
  virtual 整数 yylex();
  virtual void switch_streams( std::istream& new_in, std::ostream& new_out );
  virtual void switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  virtual 整数 yywrap();

protected:
  virtual 整数 LexerInput( char* buf, 整数 max_size );
  virtual void LexerOutput( const char* buf, 整数 size );
  virtual void LexerError( const char* msg );
			
  void yyunput_r( 整数 c, char* buf_ptr );
  整数 yyinput();

  void yy_load_buffer_state();
  void yy_init_buffer( yy_buffer_state* b, std::istream& s );
  void yy_flush_buffer( yy_buffer_state* b );

  整数 yy_start_stack_ptr;
  整数 yy_start_stack_depth;
  整数* yy_start_stack;

  void yy_push_state( 整数 new_state );
  void yy_pop_state();
  整数 yy_top_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  整数 yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  char yy_hold_char;

  // Number of characters read into yy_ch_buf.
  整数 yy_n_chars;

  // Points to current character in buffer.
  char* yy_c_buf_p;

  整数 yy_init;                // whether we need to initialize
  整数 yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  整数 yy_did_buffer_switch_on_eof;


  size_t yy_buffer_stack_top; /**< index of top of stack. */
  size_t yy_buffer_stack_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_stack; /**< Stack as an array. */
  void yyensure_buffer_stack(void);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  char* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  char* yy_full_match;
  整数* yy_full_state;
  整数 yy_full_lp;

  整数 yy_lp;
  整数 yy_looking_for_trail_begin;

  整数 yy_more_flag;
  整数 yy_more_len;
  整数 yy_more_offset;
  整数 yy_prev_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
