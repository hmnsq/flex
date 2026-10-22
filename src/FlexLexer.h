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

#अगर_अघोषित __FLEX_LEXER_H
// Never included before - need to define base class.
#घोषणा __FLEX_LEXER_H

#समावेश <iostream>

बाह्य "C++" {

काष्ठा yy_बफर_state;
प्रकार पूर्णांक yy_state_type;

class FlexLexer
{
खुला:
  भव ~FlexLexer()        { }

  स्थिर अक्षर* YYText() स्थिर  { वापस yytext; }
  पूर्णांक YYLeng()        स्थिर   { वापस yyleng; }

  भव व्योम
  yy_switch_to_बफर( yy_बफर_state* new_बफर ) = 0;
  भव yy_बफर_state* yy_create_बफर( std::istream* s, पूर्णांक आकार ) = 0;
  भव yy_बफर_state* yy_create_बफर( std::istream& s, पूर्णांक आकार ) = 0;
  भव व्योम yy_delete_बफर( yy_बफर_state* b ) = 0;
  भव व्योम yyrestart( std::istream* s ) = 0;
  भव व्योम yyrestart( std::istream& s ) = 0;

  भव पूर्णांक yylex() = 0;

  // Call yylex with new input/output sources.
  पूर्णांक yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    वापस yylex();
  }

  पूर्णांक yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    वापस yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  भव व्योम switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  भव व्योम switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  पूर्णांक lineno() स्थिर          { वापस yylineno; }

  पूर्णांक debug() स्थिर           { वापस yyflexdebug; }
  व्योम set_debug( पूर्णांक flag )  { yyflexdebug = flag; }

रक्षित:
  अक्षर* yytext;
  पूर्णांक yyleng;
  पूर्णांक yylineno;       // only maintained if you use %option yylineno
  पूर्णांक yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#पूर्ण_अगर // FLEXLEXER_H

#अगर defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

बाह्य "C++" {

class yyFlexLexer : खुला FlexLexer {
खुला:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
निजी:
  व्योम ctor_common();

खुला:

  भव ~yyFlexLexer();

  व्योम yy_switch_to_बफर( yy_बफर_state* new_बफर );
  yy_बफर_state* yy_create_बफर( std::istream* s, पूर्णांक आकार );
  yy_बफर_state* yy_create_बफर( std::istream& s, पूर्णांक आकार );
  व्योम yy_delete_बफर( yy_बफर_state* b );
  व्योम yyrestart( std::istream* s );
  व्योम yyrestart( std::istream& s );

  व्योम yypush_बफर_state( yy_बफर_state* new_बफर );
  व्योम yypop_बफर_state();

  भव पूर्णांक yyread(अक्षर *buf, माप_प्रकार);
  भव पूर्णांक yylex();
  भव व्योम switch_streams( std::istream& new_in, std::ostream& new_out );
  भव व्योम switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  भव पूर्णांक yywrap();

रक्षित:
  भव पूर्णांक Lexer_निवेश( अक्षर* buf, पूर्णांक max_आकार );
  भव व्योम LexerOutput( स्थिर अक्षर* buf, पूर्णांक आकार );
  भव व्योम LexerError( स्थिर अक्षर* संदेश );
			
  व्योम yyunput_r( पूर्णांक c, अक्षर* buf_ptr );
  पूर्णांक yyinput();

  व्योम yy_load_बफर_state();
  व्योम yy_init_बफर( yy_बफर_state* b, std::istream& s );
  व्योम yy_flush_बफर( yy_बफर_state* b );

  पूर्णांक yy_start_ढेर_ptr;
  पूर्णांक yy_start_ढेर_depth;
  पूर्णांक* yy_start_ढेर;

  व्योम yy_धकेलो_state( पूर्णांक new_state );
  व्योम yy_निकालो_state();
  पूर्णांक yy_शीर्ष_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  पूर्णांक yy_get_अग्र_बफर();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  अक्षर yy_hold_char;

  // Number of characters read into yy_ch_buf.
  पूर्णांक yy_n_chars;

  // Points to current character in buffer.
  अक्षर* yy_c_buf_p;

  पूर्णांक yy_init;                // whether we need to initialize
  पूर्णांक yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  पूर्णांक yy_did_बफर_switch_on_eof;


  माप_प्रकार yy_बफर_ढेर_शीर्ष; /**< index of top of stack. */
  माप_प्रकार yy_बफर_ढेर_max; /**< capacity of stack. */
  yy_बफर_state ** yy_बफर_ढेर; /**< Stack as an array. */
  व्योम yyensure_बफर_ढेर(व्योम);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  अक्षर* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  माप_प्रकार yy_state_buf_max;

  अक्षर* yy_full_match;
  पूर्णांक* yy_full_state;
  पूर्णांक yy_full_lp;

  पूर्णांक yy_lp;
  पूर्णांक yy_looking_for_trail_begin;

  पूर्णांक yy_more_flag;
  पूर्णांक yy_more_len;
  पूर्णांक yy_more_offset;
  पूर्णांक yy_पूर्व_more_offset;
};

}

#पूर्ण_अगर // yyFlexLexer || ! yyFlexLexerOnce
