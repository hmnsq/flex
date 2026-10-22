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

#ଅନ୍ତର୍ଭାଵ <iostream>

ବାହ୍ୟ "C++" {

ସଂରଚନା yy_buffer_state;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_state_type;

class FlexLexer
{
ସର୍ବସାଧାରଣ:
  ଆଭାସୀ ~FlexLexer()        { }

  ଅଚଳ ଅକ୍ଷର* YYText() ଅଚଳ  { ଫେରନ୍ତୁ yytext; }
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା YYLeng()        ଅଚଳ   { ଫେରନ୍ତୁ yyleng; }

  ଆଭାସୀ ଶୂନ୍ୟ
  yy_switch_to_buffer( yy_buffer_state* new_buffer ) = 0;
  ଆଭାସୀ yy_buffer_state* yy_create_buffer( std::istream* s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size ) = 0;
  ଆଭାସୀ yy_buffer_state* yy_create_buffer( std::istream& s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size ) = 0;
  ଆଭାସୀ ଶୂନ୍ୟ yy_delete_buffer( yy_buffer_state* b ) = 0;
  ଆଭାସୀ ଶୂନ୍ୟ yyrestart( std::istream* s ) = 0;
  ଆଭାସୀ ଶୂନ୍ୟ yyrestart( std::istream& s ) = 0;

  ଆଭାସୀ ପୂର୍ଣ୍ଣସଂଖ୍ୟା yylex() = 0;

  // Call yylex with new input/output sources.
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    ଫେରନ୍ତୁ yylex();
  }

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    ଫେରନ୍ତୁ yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  ଆଭାସୀ ଶୂନ୍ୟ switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  ଆଭାସୀ ଶୂନ୍ୟ switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା lineno() ଅଚଳ          { ଫେରନ୍ତୁ yylineno; }

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା debug() ଅଚଳ           { ଫେରନ୍ତୁ yyflexdebug; }
  ଶୂନ୍ୟ set_debug( ପୂର୍ଣ୍ଣସଂଖ୍ୟା flag )  { yyflexdebug = flag; }

ସୁରକ୍ଷିତ:
  ଅକ୍ଷର* yytext;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yyleng;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yylineno;       // only maintained if you use %option yylineno
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#ଯଦି defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

ବାହ୍ୟ "C++" {

class yyFlexLexer : ସର୍ବସାଧାରଣ FlexLexer {
ସର୍ବସାଧାରଣ:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
ବ୍ୟକ୍ତିଗତ:
  ଶୂନ୍ୟ ctor_common();

ସର୍ବସାଧାରଣ:

  ଆଭାସୀ ~yyFlexLexer();

  ଶୂନ୍ୟ yy_switch_to_buffer( yy_buffer_state* new_buffer );
  yy_buffer_state* yy_create_buffer( std::istream* s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size );
  yy_buffer_state* yy_create_buffer( std::istream& s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size );
  ଶୂନ୍ୟ yy_delete_buffer( yy_buffer_state* b );
  ଶୂନ୍ୟ yyrestart( std::istream* s );
  ଶୂନ୍ୟ yyrestart( std::istream& s );

  ଶୂନ୍ୟ yypush_buffer_state( yy_buffer_state* new_buffer );
  ଶୂନ୍ୟ yypop_buffer_state();

  ଆଭାସୀ ପୂର୍ଣ୍ଣସଂଖ୍ୟା yyread(ଅକ୍ଷର *buf, size_t);
  ଆଭାସୀ ପୂର୍ଣ୍ଣସଂଖ୍ୟା yylex();
  ଆଭାସୀ ଶୂନ୍ୟ switch_streams( std::istream& new_in, std::ostream& new_out );
  ଆଭାସୀ ଶୂନ୍ୟ switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  ଆଭାସୀ ପୂର୍ଣ୍ଣସଂଖ୍ୟା yywrap();

ସୁରକ୍ଷିତ:
  ଆଭାସୀ ପୂର୍ଣ୍ଣସଂଖ୍ୟା Lexer_ନିବେଶ( ଅକ୍ଷର* buf, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_size );
  ଆଭାସୀ ଶୂନ୍ୟ LexerOutput( ଅଚଳ ଅକ୍ଷର* buf, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size );
  ଆଭାସୀ ଶୂନ୍ୟ LexerError( ଅଚଳ ଅକ୍ଷର* ସନ୍ଦେଶ );
			
  ଶୂନ୍ୟ yyunput_r( ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ଅକ୍ଷର* buf_ptr );
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yyinput();

  ଶୂନ୍ୟ yy_load_buffer_state();
  ଶୂନ୍ୟ yy_init_buffer( yy_buffer_state* b, std::istream& s );
  ଶୂନ୍ୟ yy_flush_buffer( yy_buffer_state* b );

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_start_ଗଦା_ptr;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_start_ଗଦା_depth;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା* yy_start_ଗଦା;

  ଶୂନ୍ୟ yy_ଠେଲ_state( ପୂର୍ଣ୍ଣସଂଖ୍ୟା new_state );
  ଶୂନ୍ୟ yy_କାଢ଼_state();
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_ଶୀର୍ଷ_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  ଅକ୍ଷର yy_hold_char;

  // Number of characters read into yy_ch_buf.
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_n_chars;

  // Points to current character in buffer.
  ଅକ୍ଷର* yy_c_buf_p;

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_init;                // whether we need to initialize
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_did_buffer_switch_on_eof;


  size_t yy_buffer_ଗଦା_ଶୀର୍ଷ; /**< index of top of stack. */
  size_t yy_buffer_ଗଦା_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_ଗଦା; /**< Stack as an array. */
  ଶୂନ୍ୟ yyensure_buffer_ଗଦା(ଶୂନ୍ୟ);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  ଅକ୍ଷର* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  ଅକ୍ଷର* yy_full_match;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା* yy_full_state;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_full_lp;

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_lp;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_looking_for_trail_begin;

  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_more_flag;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_more_len;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_more_offset;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା yy_prev_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
