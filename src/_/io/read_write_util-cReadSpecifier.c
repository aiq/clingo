#include "_/io/read_write_util.h"

#include <ctype.h>
#include "clingo/type/cCharsToken.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#include "clingo/io/print.h"
#define pln_( ... ) pjotln_c_( xyz, 256, __VA_ARGS__ )

bool read_in_till_end_c( cScanner sca[static 1], cChars dst[static 1] )
{
   char const* beg = sca->mem;
   int64_t const initPos = sca->pos;
   while ( true )
   {
      if ( not move_to_any_char_c_( sca, "^}" ) )
      {
         move_scanner_to_c( sca, initPos );
         return false;
      }

      if ( on_char_c( sca, '}' ) )
      {
         *dst = make_chars_c( beg, sca->mem );
         return true;
      }
      else if ( on_char_c( sca, '^' ) and
                not move_if_any_chars_c_( sca, "^^", "^}" ) )
      {
         move_scanner_to_c( sca, initPos );
         return false;
      }
   }
}

bool read_in_read_specifier_c( cScanner sca[static 1],
                               cReadSpecifier spec[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( spec );

   reset_read_specifier_c( spec );

   int64_t const initPos = sca->pos;

   if ( not move_if_char_c( sca, '{' ) )
   {
      return false;
   }

   spec->withDst = not move_if_char_c( sca, '!' ); // ----------------- withDst

   char const* typeStr = sca->mem; // ------------------------------------ type
   if ( not move_while_char_match_c( sca, isalnum ) )
   {
      move_scanner_to_c( sca, initPos );
      return false;
   }
   spec->type = make_chars_c( typeStr, sca->mem );

   // ---------------------------------------------------------------- format
   move_if_char_c( sca, ':' );
   {
      cChars tmpChars = empty_chars_c();
      if ( not read_in_till_end_c( sca, &tmpChars ) )
      {
         move_scanner_to_c( sca, initPos );
         return false;
      }
      cCharsSlice set = cs_c_( "^^", "^}" );      
      cRecorder* rec = &make_recorder_c_( cMaxSpecifierFormatLength_+1,
                                          spec->fmt );
      cCharsToken tok;
      init_chars_token_c( &tok, tmpChars );
      while ( next_token_till_any_c( &tok, set ) )
      {
         cChars deli = token_delimiter_c( &tok );

         bool ok = record_chars_c( rec, tok.x );
         if ( ok and not is_empty_c_( deli ) )
         {
            char c = chars_is_c( deli, "^^" ) ? '^' : '}';
            ok = record_char_c( rec, c );
         }
         if ( ok and is_last_token_c( &tok ) )
         {
            ok = record_ends_c( rec );
         }         
         if ( not ok )
         {
            move_scanner_to_c( sca, initPos );
            return false;
         }
      }
   }

   if ( not move_if_char_c( sca, '}' ) ) // --------------------------------- {
   {
      move_scanner_to_c( sca, initPos );
      return false;
   }

   return true;
}

void reset_read_specifier_c( cReadSpecifier spec[static 1] )
{
   must_exist_c_( spec );

   spec->withDst = true;
   spec->type = empty_chars_c();
   spec->fmt[ 0 ] = '\0';
}
