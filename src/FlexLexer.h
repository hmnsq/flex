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

#నిర్వచితం_కాకపోతే __FLEX_LEXER_H
// Never included before - need to define base class.
#నిర్వచించు __FLEX_LEXER_H

#అన్తర్భావ <iostream>

బాహ్య "C++" {

నిర్మాణం yy_బఫరు_state;
రకనిర్వచనం పూర్ణాంకం yy_state_type;

class FlexLexer
{
బహిరంగ:
  మాయా ~FlexLexer()        { }

  స్థిరరాశి అక్షరం* YYText() స్థిరరాశి  { తిరిగి yytext; }
  పూర్ణాంకం YYLeng()        స్థిరరాశి   { తిరిగి yyleng; }

  మాయా శూన్య
  yy_switch_గమ్యం_బఫరు( yy_బఫరు_state* new_బఫరు ) = 0;
  మాయా yy_బఫరు_state* yy_create_బఫరు( std::istream* s, పూర్ణాంకం కొలత ) = 0;
  మాయా yy_బఫరు_state* yy_create_బఫరు( std::istream& s, పూర్ణాంకం కొలత ) = 0;
  మాయా శూన్య yy_delete_బఫరు( yy_బఫరు_state* b ) = 0;
  మాయా శూన్య yyrestart( std::istream* s ) = 0;
  మాయా శూన్య yyrestart( std::istream& s ) = 0;

  మాయా పూర్ణాంకం yylex() = 0;

  // Call yylex with new input/output sources.
  పూర్ణాంకం yylex( std::istream& new_లోపల, std::ostream& new_బహిర్గతం )
  {
    switch_streams( new_లోపల, new_బహిర్గతం );
    తిరిగి yylex();
  }

  పూర్ణాంకం yylex( std::istream* new_లోపల, std::ostream* new_బహిర్గతం = 0)
  {
    switch_streams( new_లోపల, new_బహిర్గతం );
    తిరిగి yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  మాయా శూన్య switch_streams( std::istream* new_లోపల,
                               std::ostream* new_బహిర్గతం ) = 0;
  మాయా శూన్య switch_streams( std::istream& new_లోపల,
                               std::ostream& new_బహిర్గతం ) = 0;

  పూర్ణాంకం lineno() స్థిరరాశి          { తిరిగి yylineno; }

  పూర్ణాంకం debug() స్థిరరాశి           { తిరిగి yyflexdebug; }
  శూన్య సమితి_debug( పూర్ణాంకం flag )  { yyflexdebug = flag; }

రక్షిత:
  అక్షరం* yytext;
  పూర్ణాంకం yyleng;
  పూర్ణాంకం yylineno;       // only maintained if you use %option yylineno
  పూర్ణాంకం yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#అయితే_ముగింపు // FLEXLEXER_H

#ఒకవేళ defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

బాహ్య "C++" {

class yyFlexLexer : బహిరంగ FlexLexer {
బహిరంగ:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
అంతరంగ:
  శూన్య ctor_common();

బహిరంగ:

  మాయా ~yyFlexLexer();

  శూన్య yy_switch_గమ్యం_బఫరు( yy_బఫరు_state* new_బఫరు );
  yy_బఫరు_state* yy_create_బఫరు( std::istream* s, పూర్ణాంకం కొలత );
  yy_బఫరు_state* yy_create_బఫరు( std::istream& s, పూర్ణాంకం కొలత );
  శూన్య yy_delete_బఫరు( yy_బఫరు_state* b );
  శూన్య yyrestart( std::istream* s );
  శూన్య yyrestart( std::istream& s );

  శూన్య yypush_బఫరు_state( yy_బఫరు_state* new_బఫరు );
  శూన్య yypop_బఫరు_state();

  మాయా పూర్ణాంకం yyread(అక్షరం *buf, size_t);
  మాయా పూర్ణాంకం yylex();
  మాయా శూన్య switch_streams( std::istream& new_లోపల, std::ostream& new_బహిర్గతం );
  మాయా శూన్య switch_streams( std::istream* new_లోపల = 0, std::ostream* new_బహిర్గతం = 0 );
  మాయా పూర్ణాంకం yywrap();

రక్షిత:
  మాయా పూర్ణాంకం Lexer_ఆదానం( అక్షరం* buf, పూర్ణాంకం max_కొలత );
  మాయా శూన్య LexerOutput( స్థిరరాశి అక్షరం* buf, పూర్ణాంకం కొలత );
  మాయా శూన్య LexerError( స్థిరరాశి అక్షరం* సందేశం );
			
  శూన్య yyunput_r( పూర్ణాంకం c, అక్షరం* buf_ptr );
  పూర్ణాంకం yyinput();

  శూన్య yy_ఎక్కించు_బఫరు_state();
  శూన్య yy_init_బఫరు( yy_బఫరు_state* b, std::istream& s );
  శూన్య yy_flush_బఫరు( yy_బఫరు_state* b );

  పూర్ణాంకం yy_ప్రారంభం_దొంతర_ptr;
  పూర్ణాంకం yy_ప్రారంభం_దొంతర_లోతు;
  పూర్ణాంకం* yy_ప్రారంభం_దొంతర;

  శూన్య yy_నెట్టు_state( పూర్ణాంకం new_state );
  శూన్య yy_తీయి_state();
  పూర్ణాంకం yy_శిఖరం_state();

  yy_state_type yy_get_మునుపటి_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  పూర్ణాంకం yy_get_తదుపరి_బఫరు();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  అక్షరం yy_hold_char;

  // Number of characters read into yy_ch_buf.
  పూర్ణాంకం yy_n_chars;

  // Points to current character in buffer.
  అక్షరం* yy_c_buf_p;

  పూర్ణాంకం yy_init;                // whether we need to initialize
  పూర్ణాంకం yy_ప్రారంభం;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  పూర్ణాంకం yy_did_బఫరు_switch_on_eof;


  size_t yy_బఫరు_దొంతర_శిఖరం; /**< index of top of stack. */
  size_t yy_బఫరు_దొంతర_max; /**< capacity of stack. */
  yy_బఫరు_state ** yy_బఫరు_దొంతర; /**< Stack as an array. */
  శూన్య yyensure_బఫరు_దొంతర(శూన్య);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_చివరి_accepting_state;
  అక్షరం* yy_చివరి_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  అక్షరం* yy_నిండిన_సరిపోలిక;
  పూర్ణాంకం* yy_నిండిన_state;
  పూర్ణాంకం yy_నిండిన_lp;

  పూర్ణాంకం yy_lp;
  పూర్ణాంకం yy_looking_for_trail_begin;

  పూర్ణాంకం yy_మరిన్ని_flag;
  పూర్ణాంకం yy_మరిన్ని_len;
  పూర్ణాంకం yy_మరిన్ని_స్థానభ్రంశం;
  పూర్ణాంకం yy_prev_మరిన్ని_స్థానభ్రంశం;
};

}

#అయితే_ముగింపు // yyFlexLexer || ! yyFlexLexerOnce
