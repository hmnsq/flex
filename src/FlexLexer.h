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

#അന്തര്ഭാവ <iostream>

ബാഹ്യ "C++" {

ഘടന yy_buffer_state;
തരനിർവചനം പൂർണ്ണസംഖ്യ yy_state_type;

class FlexLexer
{
പൊതു:
  മായാ ~FlexLexer()        { }

  സ്ഥിരം അക്ഷരം* YYText() സ്ഥിരം  { തിരികെ yytext; }
  പൂർണ്ണസംഖ്യ YYLeng()        സ്ഥിരം   { തിരികെ yyleng; }

  മായാ ശൂന്യം
  yy_switch_to_buffer( yy_buffer_state* new_buffer ) = 0;
  മായാ yy_buffer_state* yy_create_buffer( std::istream* s, പൂർണ്ണസംഖ്യ size ) = 0;
  മായാ yy_buffer_state* yy_create_buffer( std::istream& s, പൂർണ്ണസംഖ്യ size ) = 0;
  മായാ ശൂന്യം yy_delete_buffer( yy_buffer_state* b ) = 0;
  മായാ ശൂന്യം yyrestart( std::istream* s ) = 0;
  മായാ ശൂന്യം yyrestart( std::istream& s ) = 0;

  മായാ പൂർണ്ണസംഖ്യ yylex() = 0;

  // Call yylex with new input/output sources.
  പൂർണ്ണസംഖ്യ yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    തിരികെ yylex();
  }

  പൂർണ്ണസംഖ്യ yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    തിരികെ yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  മായാ ശൂന്യം switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  മായാ ശൂന്യം switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  പൂർണ്ണസംഖ്യ lineno() സ്ഥിരം          { തിരികെ yylineno; }

  പൂർണ്ണസംഖ്യ debug() സ്ഥിരം           { തിരികെ yyflexdebug; }
  ശൂന്യം set_debug( പൂർണ്ണസംഖ്യ flag )  { yyflexdebug = flag; }

സംരക്ഷിത:
  അക്ഷരം* yytext;
  പൂർണ്ണസംഖ്യ yyleng;
  പൂർണ്ണസംഖ്യ yylineno;       // only maintained if you use %option yylineno
  പൂർണ്ണസംഖ്യ yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#എങ്കിൽ defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

ബാഹ്യ "C++" {

class yyFlexLexer : പൊതു FlexLexer {
പൊതു:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
സ്വകാര്യ:
  ശൂന്യം ctor_common();

പൊതു:

  മായാ ~yyFlexLexer();

  ശൂന്യം yy_switch_to_buffer( yy_buffer_state* new_buffer );
  yy_buffer_state* yy_create_buffer( std::istream* s, പൂർണ്ണസംഖ്യ size );
  yy_buffer_state* yy_create_buffer( std::istream& s, പൂർണ്ണസംഖ്യ size );
  ശൂന്യം yy_delete_buffer( yy_buffer_state* b );
  ശൂന്യം yyrestart( std::istream* s );
  ശൂന്യം yyrestart( std::istream& s );

  ശൂന്യം yypush_buffer_state( yy_buffer_state* new_buffer );
  ശൂന്യം yypop_buffer_state();

  മായാ പൂർണ്ണസംഖ്യ yyread(അക്ഷരം *buf, size_t);
  മായാ പൂർണ്ണസംഖ്യ yylex();
  മായാ ശൂന്യം switch_streams( std::istream& new_in, std::ostream& new_out );
  മായാ ശൂന്യം switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  മായാ പൂർണ്ണസംഖ്യ yywrap();

സംരക്ഷിത:
  മായാ പൂർണ്ണസംഖ്യ Lexer_നിവേശം( അക്ഷരം* buf, പൂർണ്ണസംഖ്യ max_size );
  മായാ ശൂന്യം LexerOutput( സ്ഥിരം അക്ഷരം* buf, പൂർണ്ണസംഖ്യ size );
  മായാ ശൂന്യം LexerError( സ്ഥിരം അക്ഷരം* സന്ദേശം );
			
  ശൂന്യം yyunput_r( പൂർണ്ണസംഖ്യ c, അക്ഷരം* buf_ptr );
  പൂർണ്ണസംഖ്യ yyinput();

  ശൂന്യം yy_load_buffer_state();
  ശൂന്യം yy_init_buffer( yy_buffer_state* b, std::istream& s );
  ശൂന്യം yy_flush_buffer( yy_buffer_state* b );

  പൂർണ്ണസംഖ്യ yy_start_അട്ടി_ptr;
  പൂർണ്ണസംഖ്യ yy_start_അട്ടി_depth;
  പൂർണ്ണസംഖ്യ* yy_start_അട്ടി;

  ശൂന്യം yy_തള്ളുക_state( പൂർണ്ണസംഖ്യ new_state );
  ശൂന്യം yy_എടുക്കുക_state();
  പൂർണ്ണസംഖ്യ yy_മുകൾ_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  പൂർണ്ണസംഖ്യ yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  അക്ഷരം yy_hold_char;

  // Number of characters read into yy_ch_buf.
  പൂർണ്ണസംഖ്യ yy_n_chars;

  // Points to current character in buffer.
  അക്ഷരം* yy_c_buf_p;

  പൂർണ്ണസംഖ്യ yy_init;                // whether we need to initialize
  പൂർണ്ണസംഖ്യ yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  പൂർണ്ണസംഖ്യ yy_did_buffer_switch_on_eof;


  size_t yy_buffer_അട്ടി_മുകൾ; /**< index of top of stack. */
  size_t yy_buffer_അട്ടി_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_അട്ടി; /**< Stack as an array. */
  ശൂന്യം yyensure_buffer_അട്ടി(ശൂന്യം);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  അക്ഷരം* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  അക്ഷരം* yy_full_match;
  പൂർണ്ണസംഖ്യ* yy_full_state;
  പൂർണ്ണസംഖ്യ yy_full_lp;

  പൂർണ്ണസംഖ്യ yy_lp;
  പൂർണ്ണസംഖ്യ yy_looking_for_trail_begin;

  പൂർണ്ണസംഖ്യ yy_more_flag;
  പൂർണ്ണസംഖ്യ yy_more_len;
  പൂർണ്ണസംഖ്യ yy_more_offset;
  പൂർണ്ണസംഖ്യ yy_prev_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
