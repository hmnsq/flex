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

#அந்தர்பாவ <iostream>

வெளி "C++" {

கட்டமைப்பு yy_buffer_state;
வகைவரை முழு yy_state_type;

class FlexLexer
{
பொது:
  மெய்நிகர் ~FlexLexer()        { }

  மாறிலி எழுத்து* YYText() மாறிலி  { திரும்பு yytext; }
  முழு YYLeng()        மாறிலி   { திரும்பு yyleng; }

  மெய்நிகர் வெறுமை
  yy_switch_to_buffer( yy_buffer_state* new_buffer ) = 0;
  மெய்நிகர் yy_buffer_state* yy_create_buffer( std::istream* s, முழு size ) = 0;
  மெய்நிகர் yy_buffer_state* yy_create_buffer( std::istream& s, முழு size ) = 0;
  மெய்நிகர் வெறுமை yy_delete_buffer( yy_buffer_state* b ) = 0;
  மெய்நிகர் வெறுமை yyrestart( std::istream* s ) = 0;
  மெய்நிகர் வெறுமை yyrestart( std::istream& s ) = 0;

  மெய்நிகர் முழு yylex() = 0;

  // Call yylex with new input/output sources.
  முழு yylex( std::istream& new_in, std::ostream& new_out )
  {
    switch_streams( new_in, new_out );
    திரும்பு yylex();
  }

  முழு yylex( std::istream* new_in, std::ostream* new_out = 0)
  {
    switch_streams( new_in, new_out );
    திரும்பு yylex();
  }

  // Switch to new input/output streams.  A nil stream pointer
  // indicates "keep the current one".
  மெய்நிகர் வெறுமை switch_streams( std::istream* new_in,
                               std::ostream* new_out ) = 0;
  மெய்நிகர் வெறுமை switch_streams( std::istream& new_in,
                               std::ostream& new_out ) = 0;

  முழு lineno() மாறிலி          { திரும்பு yylineno; }

  முழு debug() மாறிலி           { திரும்பு yyflexdebug; }
  வெறுமை set_debug( முழு flag )  { yyflexdebug = flag; }

பாதுகாக்கப்பட்ட:
  எழுத்து* yytext;
  முழு yyleng;
  முழு yylineno;       // only maintained if you use %option yylineno
  முழு yyflexdebug;    // only has effect with -d or "%option debug"
};

}
#endif // FLEXLEXER_H

#எனில் defined(yyFlexLexer) || ! defined(yyFlexLexerOnce)
// Either this is the first time through (yyFlexLexerOnce not defined),
// or this is a repeated include to define a different flavor of
// yyFlexLexer, as discussed in the flex manual.
# define yyFlexLexerOnce

வெளி "C++" {

class yyFlexLexer : பொது FlexLexer {
பொது:
  // arg_yyin and arg_yyout default to the cin and cout, but we
  // only make that assignment when initializing in yylex().
  yyFlexLexer( std::istream& arg_yyin, std::ostream& arg_yyout );
  yyFlexLexer( std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0 );
தனிப்பட்ட:
  வெறுமை ctor_common();

பொது:

  மெய்நிகர் ~yyFlexLexer();

  வெறுமை yy_switch_to_buffer( yy_buffer_state* new_buffer );
  yy_buffer_state* yy_create_buffer( std::istream* s, முழு size );
  yy_buffer_state* yy_create_buffer( std::istream& s, முழு size );
  வெறுமை yy_delete_buffer( yy_buffer_state* b );
  வெறுமை yyrestart( std::istream* s );
  வெறுமை yyrestart( std::istream& s );

  வெறுமை yypush_buffer_state( yy_buffer_state* new_buffer );
  வெறுமை yypop_buffer_state();

  மெய்நிகர் முழு yyread(எழுத்து *buf, size_t);
  மெய்நிகர் முழு yylex();
  மெய்நிகர் வெறுமை switch_streams( std::istream& new_in, std::ostream& new_out );
  மெய்நிகர் வெறுமை switch_streams( std::istream* new_in = 0, std::ostream* new_out = 0 );
  மெய்நிகர் முழு yywrap();

பாதுகாக்கப்பட்ட:
  மெய்நிகர் முழு Lexer_உள்ளீடு( எழுத்து* buf, முழு max_size );
  மெய்நிகர் வெறுமை LexerOutput( மாறிலி எழுத்து* buf, முழு size );
  மெய்நிகர் வெறுமை LexerError( மாறிலி எழுத்து* செய்தி );
			
  வெறுமை yyunput_r( முழு c, எழுத்து* buf_ptr );
  முழு yyinput();

  வெறுமை yy_load_buffer_state();
  வெறுமை yy_init_buffer( yy_buffer_state* b, std::istream& s );
  வெறுமை yy_flush_buffer( yy_buffer_state* b );

  முழு yy_start_அடுக்கு_ptr;
  முழு yy_start_அடுக்கு_depth;
  முழு* yy_start_அடுக்கு;

  வெறுமை yy_தள்ளு_state( முழு new_state );
  வெறுமை yy_எடு_state();
  முழு yy_உச்சி_state();

  yy_state_type yy_get_previous_state();
  yy_state_type yy_try_NUL_trans( yy_state_type current_state );
  முழு yy_get_next_buffer();

  std::istream yyin;  // input source for default LexerInput
  std::ostream yyout; // output sink for default LexerOutput

  // yy_hold_char holds the character lost when yytext is formed.
  எழுத்து yy_hold_char;

  // Number of characters read into yy_ch_buf.
  முழு yy_n_chars;

  // Points to current character in buffer.
  எழுத்து* yy_c_buf_p;

  முழு yy_init;                // whether we need to initialize
  முழு yy_start;               // start state number

  // Flag which is used to allow yywrap()'s to do buffer switches
  // instead of setting up a fresh yyin.  A bit of a hack ...
  முழு yy_did_buffer_switch_on_eof;


  size_t yy_buffer_அடுக்கு_உச்சி; /**< index of top of stack. */
  size_t yy_buffer_அடுக்கு_max; /**< capacity of stack. */
  yy_buffer_state ** yy_buffer_அடுக்கு; /**< Stack as an array. */
  வெறுமை yyensure_buffer_அடுக்கு(வெறுமை);

  // The following are not always needed, but may be depending
  // on use of certain flex features (like REJECT or yymore()).

  yy_state_type yy_last_accepting_state;
  எழுத்து* yy_last_accepting_cpos;

  yy_state_type* yy_state_buf;
  yy_state_type* yy_state_ptr;
  size_t yy_state_buf_max;

  எழுத்து* yy_full_match;
  முழு* yy_full_state;
  முழு yy_full_lp;

  முழு yy_lp;
  முழு yy_looking_for_trail_begin;

  முழு yy_more_flag;
  முழு yy_more_len;
  முழு yy_more_offset;
  முழு yy_prev_more_offset;
};

}

#endif // yyFlexLexer || ! yyFlexLexerOnce
