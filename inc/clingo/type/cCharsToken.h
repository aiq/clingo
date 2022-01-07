#ifndef CLINGO_TYPE_CCHARS_TOKEN_H
#define CLINGO_TYPE_CCHARS_TOKEN_H

#include "clingo/type/cChars.h"
#include "clingo/type/cCharsSlice.h"
#include "clingo/type/cRune.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct cCharsToken
{
   cChars x;
   cChars tail;
};
typedef struct cCharsToken cCharsToken;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

inline void init_chars_token_c( cCharsToken tok[static 1], cChars chars )
{
   *tok = (cCharsToken){
      .x = chars_c( 0, chars.v ),
      .tail = chars
   };
}

inline void init_cstr_token_c( cCharsToken tok[static 1],
                               char const cstr[static 1] )
{
   init_chars_token_c( tok, c_c( cstr ) );
}

/*******************************************************************************
 next
*******************************************************************************/

#define next_token_till_any_c_( Tok, ... )                                     \
   next_token_till_any_c( (Tok), cs_c_( __VA_ARGS__ ) )
bool next_token_till_any_c( cCharsToken tok[static 1], cCharsSlice set );

#define next_token_till_c_( Tok, Cstr )                                        \
   next_token_till_c( (Tok), c_c( Cstr ) )
bool next_token_till_c( cCharsToken tok[static 1], cChars deli );

#define next_token_till_any_char_c_( Tok, Cstr )                               \
   next_token_till_any_char_c( (Tok), c_c( Cstr ) )
bool next_token_till_any_char_c( cCharsToken tok[static 1], cChars set );

bool next_token_till_char_c( cCharsToken tok[static 1], char deli );

#define next_token_till_any_rune_c_( Tok, Cstr )                               \
   next_token_till_any_rune_c( (Tok), c_c( Cstr ) )
bool next_token_till_any_rune_c( cCharsToken tok[static 1], cChars set );

#define next_token_till_rune_c_( Tok, Cstr )                                   \
   next_token_till_rune_c( (Tok), rune_c( Cstr ) )
bool next_token_till_rune_c( cCharsToken tok[static 1], cRune deli );

/*******************************************************************************
 prop
*******************************************************************************/

inline bool is_last_token_c( cCharsToken const tok[static 1] )
{
   return tok->x.v == tok->tail.v and
          tok->x.s == tok->tail.s;
}

cChars token_delimiter_c( cCharsToken const tok[static 1] );

#endif
