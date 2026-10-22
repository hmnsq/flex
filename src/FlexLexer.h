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

#અન્તર્ભાવ <iostream>

બાહ્ય "C++" {

સંરચના yy_buffer_state;
પ્રકારવ્યાખ્યા પૂર્ણાંક yy_state_type;

class FlexLexer
{
જાહેર:
  આભાસી ~FlexLexer()        { }

  અચલ અક્ષર* YYText() અચલ  { પાછા yytext; }
  પૂર્ણાંક YYLeng()        અચલ   { પાછા yyleng; }

  આભાસી શૂન્ય
  yy_switch_to_buffer( yy_buffer_state* new_buffer ) = 0;
  આભાસી yy_buffer_state* yy_create_buffer( std::istream* s, પૂર્ણાંક size ) = 0;
  આભાસી yy_buffer_state* yy_create_buffer( std::istream& s, પૂર્ણાંક size ) = 0;
  આભાસી શૂન્ય yy_delete_buffer( yy_buffer_state* b ) = 0;
  આભાસી શૂન્ય yyrestart( std::istream* s ) = 0;
  આભાસી શૂન્ય yyrestart( std::istream& s ) = 0;

  આભાસી પૂર્ણાંક yylex() = 0;

  // Call yylex with new input/output sources.
  પૂર્ણાંક yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    પાછા yylex();
  }

  પૂર્ણાંક yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    પાછા yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  આભાસી શૂન્ય switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  આભાસી શૂન્ય switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  પૂર્ણાંક lineno() અચલ          { પાછા yylineno; }

  પૂર્ણાંક debug() અચલ           { પાછા yyflexdebug; }
  શૂન્ય set_debug( પૂર્ણાંક flag )  { yyflexdebug = flag; }

સુરક્ષિત:
  અક્ષર* yytext;
  પૂર્ણાંક yyleng;
  પૂર્ણાંક yylineno;       // only maintained if you use %option yylineno
  પૂર્ણાંક yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#જો defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

બાહ્ય "C++" {

class yyFlexLexer : જાહેર FlexLexer {
જાહેર:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
ખાનગી:
  શૂન્ય ctor_common();

જાહેર:

  આભાસી ~yyFlexLexer();

  શૂન્ય yy_switch_to_buffer( yy_buffer_state* new_buffer );
  yy_buffer_state* yy_create_buffer( std::istream* s, પૂર્ણાંક size );
  yy_buffer_state* yy_create_buffer( std::istream& s, પૂર્ણાંક size );
  શૂન્ય yy_delete_buffer( yy_buffer_state* b );
  શૂન્ય yyrestart( std::istream* s );
  શૂન્ય yyrestart( std::istream& s );

  શૂન્ય yypush_buffer_state( yy_buffer_state* new_buffer );
  શૂન્ય yypop_buffer_state();

  આભાસી પૂર્ણાંક yyread(અક્ષર *buf, size_t);
  આભાસી પૂર્ણાંક yylex();
  આભાસી શૂન્ય switch_streams( std::istream& new_in, std::ostream& new_out );
  આભાસી શૂન્ય switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  આભાસી પૂર્ણાંક yywrap();

સુરક્ષિત:
  આભાસી પૂર્ણાંક Lexer_આગત( અક્ષર* buf, પૂર્ણાંક max_size );
  આભાસી શૂન્ય LexerOutput( અચલ અક્ષર* buf, પૂર્ણાંક size );
  આભાસી શૂન્ય LexerError( અચલ અક્ષર* સંદેશ );
			
  શૂન્ય yyunput_r( પૂર્ણાંક c, અક્ષર* buf_ptr );
  પૂર્ણાંક yyinput();

  શૂન્ય yy_load_buffer_state();
  શૂન્ય yy_init_buffer( yy_buffer_state* b, std::istream& s );
  શૂન્ય yy_flush_buffer( yy_buffer_state* b );

  પૂર્ણાંક yy_start_ઢગલો_ptr;
  પૂર્ણાંક yy_start_ઢગલો_depth;
  પૂર્ણાંક* yy_start_ઢગલો;

  શૂન્ય yy_ધકેલો_state( પૂર્ણાંક new_state );
  શૂન્ય yy_કાઢો_state();
  પૂર્ણાંક yy_ટોચ_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  પૂર્ણાંક yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  અક્ષર yy_hold_char;

  // Number of characters read into yy_ch_buf.
  પૂર્ણાંક yy_n_chars;

  // Points to current character in buffer.
  અક્ષર* yy_c_buf_p;

  પૂર્ણાંક yy_init;                // whether we need to initialize
  પૂર્ણાંક yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  પૂર્ણાંક yy_did_buffer_switch_on_eof;


  size_t yy_buffer_ઢગલો_ટોચ; /**< index of top of stack. */
  size_t yy_buffer_ઢગલો_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_ઢગલો; /**< Stack as an array. */
  શૂન્ય yyensure_buffer_ઢગલો(શૂન્ય);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  અક્ષર* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  અક્ષર* yy_full_match;
  પૂર્ણાંક* yy_full_state;
  પૂર્ણાંક yy_full_lp;

  પૂર્ણાંક yy_lp;
  પૂર્ણાંક yy_looking_for_trail_begin;

  પૂર્ણાંક yy_more_flag;
  પૂર્ણાંક yy_more_len;
  પૂર્ણાંક yy_more_offset;
  પૂર્ણાંક yy_prev_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
