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

#অন্তর্ভাব <iostream>

বাহ্যিক "C++" {

কাঠামো yy_বাফার_state;
প্রকারলেখ পূর্ণসংখ্যা yy_state_type;

class FlexLexer
{
সর্বজনীন:
  আভাসী ~FlexLexer()        { }

  ধ্রুবক অক্ষর* YYText() ধ্রুবক  { ফেরত yytext; }
  পূর্ণসংখ্যা YYLeng()        ধ্রুবক   { ফেরত yyleng; }

  আভাসী শূন্য
  yy_switch_to_বাফার( yy_বাফার_state* new_বাফার ) = 0;
  আভাসী yy_বাফার_state* yy_create_বাফার( std::istream* s, পূর্ণসংখ্যা আকার_2 ) = 0;
  আভাসী yy_বাফার_state* yy_create_বাফার( std::istream& s, পূর্ণসংখ্যা আকার_2 ) = 0;
  আভাসী শূন্য yy_delete_বাফার( yy_বাফার_state* b ) = 0;
  আভাসী শূন্য yyrestart( std::istream* s ) = 0;
  আভাসী শূন্য yyrestart( std::istream& s ) = 0;

  আভাসী পূর্ণসংখ্যা yylex() = 0;

  // Call yylex with new input/output sources.
  পূর্ণসংখ্যা yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    ফেরত yylex();
  }

  পূর্ণসংখ্যা yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    ফেরত yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  আভাসী শূন্য switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  আভাসী শূন্য switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  পূর্ণসংখ্যা lineno() ধ্রুবক          { ফেরত yylineno; }

  পূর্ণসংখ্যা debug() ধ্রুবক           { ফেরত yyflexdebug; }
  শূন্য set_debug( পূর্ণসংখ্যা flag )  { yyflexdebug = flag; }

সুরক্ষিত:
  অক্ষর* yytext;
  পূর্ণসংখ্যা yyleng;
  পূর্ণসংখ্যা yylineno;       // only maintained if you use %option yylineno
  পূর্ণসংখ্যা yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#যদি defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

বাহ্যিক "C++" {

class yyFlexLexer : সর্বজনীন FlexLexer {
সর্বজনীন:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
ব্যক্তিগত:
  শূন্য ctor_common();

সর্বজনীন:

  আভাসী ~yyFlexLexer();

  শূন্য yy_switch_to_বাফার( yy_বাফার_state* new_বাফার );
  yy_বাফার_state* yy_create_বাফার( std::istream* s, পূর্ণসংখ্যা আকার_2 );
  yy_বাফার_state* yy_create_বাফার( std::istream& s, পূর্ণসংখ্যা আকার_2 );
  শূন্য yy_delete_বাফার( yy_বাফার_state* b );
  শূন্য yyrestart( std::istream* s );
  শূন্য yyrestart( std::istream& s );

  শূন্য yypush_বাফার_state( yy_বাফার_state* new_বাফার );
  শূন্য yypop_বাফার_state();

  আভাসী পূর্ণসংখ্যা yyread(অক্ষর *buf, size_t);
  আভাসী পূর্ণসংখ্যা yylex();
  আভাসী শূন্য switch_streams( std::istream& new_in, std::ostream& new_out );
  আভাসী শূন্য switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  আভাসী পূর্ণসংখ্যা yywrap();

সুরক্ষিত:
  আভাসী পূর্ণসংখ্যা Lexer_প্রবেশ( অক্ষর* buf, পূর্ণসংখ্যা max_আকার );
  আভাসী শূন্য LexerOutput( ধ্রুবক অক্ষর* buf, পূর্ণসংখ্যা আকার_2 );
  আভাসী শূন্য LexerError( ধ্রুবক অক্ষর* বার্তা );
			
  শূন্য yyunput_r( পূর্ণসংখ্যা c, অক্ষর* buf_ptr );
  পূর্ণসংখ্যা yyinput();

  শূন্য yy_load_বাফার_state();
  শূন্য yy_init_বাফার( yy_বাফার_state* b, std::istream& s );
  শূন্য yy_flush_বাফার( yy_বাফার_state* b );

  পূর্ণসংখ্যা yy_start_স্তূপ_ptr;
  পূর্ণসংখ্যা yy_start_স্তূপ_depth;
  পূর্ণসংখ্যা* yy_start_স্তূপ;

  শূন্য yy_ঠেলো_state( পূর্ণসংখ্যা new_state );
  শূন্য yy_বের_করো_state();
  পূর্ণসংখ্যা yy_শীর্ষ_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  পূর্ণসংখ্যা yy_get_পরবর্তী_বাফার();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  অক্ষর yy_hold_char;

  // Number of characters read into yy_ch_buf.
  পূর্ণসংখ্যা yy_n_chars;

  // Points to current character in buffer.
  অক্ষর* yy_c_buf_p;

  পূর্ণসংখ্যা yy_init;                // whether we need to initialize
  পূর্ণসংখ্যা yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  পূর্ণসংখ্যা yy_did_বাফার_switch_on_eof;


  size_t yy_বাফার_স্তূপ_শীর্ষ; /**< index of top of stack. */
  size_t yy_বাফার_স্তূপ_max; /**< capacity of stack. */
  yy_বাফার_state ** yy_বাফার_স্তূপ; /**< Stack as an array. */
  শূন্য yyensure_বাফার_স্তূপ(শূন্য);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  অক্ষর* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  অক্ষর* yy_full_match;
  পূর্ণসংখ্যা* yy_full_state;
  পূর্ণসংখ্যা yy_full_lp;

  পূর্ণসংখ্যা yy_lp;
  পূর্ণসংখ্যা yy_looking_for_trail_begin;

  পূর্ণসংখ্যা yy_more_flag;
  পূর্ণসংখ্যা yy_more_len;
  পূর্ণসংখ্যা yy_more_offset;
  পূর্ণসংখ্যা yy_পূর্ব_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
