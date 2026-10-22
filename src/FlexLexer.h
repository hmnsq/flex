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

#अन्तर्भाव <iostream>

बाह्य "C++" {

संरचना yy_buffer_state;
प्रकारनिर्देश पूर्णाङ्क yy_state_type;

class FlexLexer
{
सार्वजनिक:
  आभास ~FlexLexer()        { }

  ध्रुव वर्ण* YYText() ध्रुव  { प्रत्यागम yytext; }
  पूर्णाङ्क YYLeng()        ध्रुव   { प्रत्यागम yyleng; }

  आभास शून्य
  yy_switch_to_buffer( yy_buffer_state* new_buffer ) = 0;
  आभास yy_buffer_state* yy_create_buffer( std::istream* s, पूर्णाङ्क size ) = 0;
  आभास yy_buffer_state* yy_create_buffer( std::istream& s, पूर्णाङ्क size ) = 0;
  आभास शून्य yy_delete_buffer( yy_buffer_state* b ) = 0;
  आभास शून्य yyrestart( std::istream* s ) = 0;
  आभास शून्य yyrestart( std::istream& s ) = 0;

  आभास पूर्णाङ्क yylex() = 0;

  // Call yylex with new input/output sources.
  पूर्णाङ्क yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    प्रत्यागम yylex();
  }

  पूर्णाङ्क yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    प्रत्यागम yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  आभास शून्य switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  आभास शून्य switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  पूर्णाङ्क lineno() ध्रुव          { प्रत्यागम yylineno; }

  पूर्णाङ्क debug() ध्रुव           { प्रत्यागम yyflexdebug; }
  शून्य set_debug( पूर्णाङ्क flag )  { yyflexdebug = flag; }

रक्षित:
  वर्ण* yytext;
  पूर्णाङ्क yyleng;
  पूर्णाङ्क yylineno;       // only maintained if you use %option yylineno
  पूर्णाङ्क yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#जइ defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

बाह्य "C++" {

class yyFlexLexer : सार्वजनिक FlexLexer {
सार्वजनिक:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
गुप्त:
  शून्य ctor_common();

सार्वजनिक:

  आभास ~yyFlexLexer();

  शून्य yy_switch_to_buffer( yy_buffer_state* new_buffer );
  yy_buffer_state* yy_create_buffer( std::istream* s, पूर्णाङ्क size );
  yy_buffer_state* yy_create_buffer( std::istream& s, पूर्णाङ्क size );
  शून्य yy_delete_buffer( yy_buffer_state* b );
  शून्य yyrestart( std::istream* s );
  शून्य yyrestart( std::istream& s );

  शून्य yypush_buffer_state( yy_buffer_state* new_buffer );
  शून्य yypop_buffer_state();

  आभास पूर्णाङ्क yyread(वर्ण *buf, size_t);
  आभास पूर्णाङ्क yylex();
  आभास शून्य switch_streams( std::istream& new_in, std::ostream& new_out );
  आभास शून्य switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  आभास पूर्णाङ्क yywrap();

रक्षित:
  आभास पूर्णाङ्क Lexer_निवेशः( वर्ण* buf, पूर्णाङ्क max_size );
  आभास शून्य LexerOutput( ध्रुव वर्ण* buf, पूर्णाङ्क size );
  आभास शून्य LexerError( ध्रुव वर्ण* सन्देशः );
			
  शून्य yyunput_r( पूर्णाङ्क c, वर्ण* buf_ptr );
  पूर्णाङ्क yyinput();

  शून्य yy_load_buffer_state();
  शून्य yy_init_buffer( yy_buffer_state* b, std::istream& s );
  शून्य yy_flush_buffer( yy_buffer_state* b );

  पूर्णाङ्क yy_start_राशिः_ptr;
  पूर्णाङ्क yy_start_राशिः_depth;
  पूर्णाङ्क* yy_start_राशिः;

  शून्य yy_प्रक्षिप_state( पूर्णाङ्क new_state );
  शून्य yy_निष्कासय_state();
  पूर्णाङ्क yy_शिखरम्_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  पूर्णाङ्क yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  वर्ण yy_hold_char;

  // Number of characters read into yy_ch_buf.
  पूर्णाङ्क yy_n_chars;

  // Points to current character in buffer.
  वर्ण* yy_c_buf_p;

  पूर्णाङ्क yy_init;                // whether we need to initialize
  पूर्णाङ्क yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  पूर्णाङ्क yy_did_buffer_switch_on_eof;


  size_t yy_buffer_राशिः_शिखरम्; /**< index of top of stack. */
  size_t yy_buffer_राशिः_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_राशिः; /**< Stack as an array. */
  शून्य yyensure_buffer_राशिः(शून्य);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  वर्ण* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  वर्ण* yy_full_match;
  पूर्णाङ्क* yy_full_state;
  पूर्णाङ्क yy_full_lp;

  पूर्णाङ्क yy_lp;
  पूर्णाङ्क yy_looking_for_trail_begin;

  पूर्णाङ्क yy_more_flag;
  पूर्णाङ्क yy_more_len;
  पूर्णाङ्क yy_more_offset;
  पूर्णाङ्क yy_prev_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
