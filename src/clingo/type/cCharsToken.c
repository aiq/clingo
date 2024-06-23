#include "clingo/type/cCharsToken.h"

/*******************************************************************************

*******************************************************************************/

extern inline void init_chars_token_c( cCharsToken tok[static 1],
                                       cChars chars );

extern inline void init_cstr_token_c( cCharsToken tok[static 1],
                                      char const cstr[static 1] );

/*******************************************************************************
 next
*******************************************************************************/

static inline bool update_token( cCharsToken tok[static 1],
                                 char const* v,
                                 int64_t len )
{
   if ( v != NULL )
   {
      tok->x.v = tok->tail.v;
      tok->x.s = v - tok->tail.v;
      tok->tail = mid_c_( cChars, tok->tail, tok->x.s + len );
   }
   else // last
   {
      tok->x.v = tok->tail.v;
      tok->x.s = tok->tail.s;
   }

   return true;
}

bool next_token_till_any_c( cCharsToken tok[static 1], cCharsSlice set )
{
   if ( is_last_token_c( tok ) ) return false;

   char const* beg = begin_c_( tok->tail );
   char const* end = end_c_( tok->tail );
   for ( ; beg < end; ++beg )
   {
      cChars sub = atween_c_( beg, end );
      each_c_( cChars const*, any, set )
      {
         if ( chars_starts_with_c( sub, *any ) )
         {
            return update_token( tok, beg, any->s );
         }
      }
   }

   return update_token( tok, NULL, tok->tail.s );
}

bool next_token_till_c( cCharsToken tok[static 1], cChars deli )
{
   if ( is_last_token_c( tok ) ) return false;

   int64_t const idx = index_of_chars_c( tok->tail, deli );
   char const* v = ptr_for_c_( tok->tail, idx );
   return update_token( tok, v, deli.s );
}

bool next_token_till_any_char_c( cCharsToken tok[static 1], cChars set )
{
   if ( is_last_token_c( tok ) ) return false;

   char const* v = find_any_char_c( tok->tail, set );
   return update_token( tok, v, 1 );
}

bool next_token_till_char_c( cCharsToken tok[static 1], char deli )
{
   if ( is_last_token_c( tok ) ) return false;

   char const* v = find_char_c( tok->tail, deli );
   return update_token( tok, v, 1 );
}

bool next_token_till_rune_c( cCharsToken tok[static 1], cRune deli )
{
   if ( is_last_token_c( tok ) ) return false;

   char const* v = find_rune_c( tok->tail, deli );
   int64_t len = v ? utf8_length_c( *v )
                   : 0;
   return update_token( tok, v, len );
}

bool next_token_till_any_rune_c( cCharsToken tok[static 1], cChars set )
{
   if ( is_last_token_c( tok ) ) return false;

   char const* v = find_any_rune_c( tok->tail, set );
   int64_t len = v ? utf8_length_c( *v )
                   : 0;
   return update_token( tok, v, len );
}

/*******************************************************************************
 next presets
*******************************************************************************/

bool next_line_token_c( cCharsToken tok[static 1] )
{
   if ( not next_token_till_char_c( tok, '\n' ) )
      return false;

   if ( tok->x.s > 0 and last_c_( tok->x ) == '\r' )
   {
      tok->x.s -= 1;
   }

   return true;
}

/*******************************************************************************
 prop
*******************************************************************************/

extern inline bool is_last_token_c( cCharsToken const tok[static 1] );

cChars token_delimiter_c( cCharsToken const tok[static 1] )
{
   must_exist_c_( tok );

   if ( tok->x.v >=  tok->tail.v ) return (cChars)empty_c_();

   char const* v = tok->x.v + tok->x.s;
   int64_t s = tok->tail.v - v;
   return (cChars){ s, v };
}
