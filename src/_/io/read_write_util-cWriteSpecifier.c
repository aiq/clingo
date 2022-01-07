#include "_/io/read_write_util.h"

#include <ctype.h>

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool read_in_write_specifier_c( cScanner sca[static 1],
                                cWriteSpecifier spec[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( spec );

   reset_write_specifier_c( spec );

   int64_t const initPos = sca->pos;

   if ( not move_if_char_c( sca, '{' ) ) // --------------------------------- {
   {
      return false;
   }

   char const* typeStr = sca->mem; // ------------------------------------ type
   if ( not move_while_char_match_c( sca, isalnum ) )
   {
      move_scanner_to_c( sca, initPos );
      return false;
   }
   spec->type = make_chars_c( typeStr, sca->mem );

   char const* formatStr = sca->mem; // -------------------------------- format
   int64_t const formatPos = sca->pos;
   if ( move_if_char_c( sca, ':' ) )
   {
      formatStr = sca->mem;
   }
   if ( not move_to_char_c( sca, '}' ) )
   {
      move_scanner_to_c( sca, initPos );
      return false;
   }
   if ( ( sca->pos - formatPos ) > cMaxSpecifierFormatLength_ )
   {
      move_scanner_to_c( sca, initPos );
      return false;
   }
   int64_t const formatSize = set_chars_c( 
      var_chars_c( cMaxSpecifierFormatLength_, spec->fmt ),
      make_chars_c( formatStr, sca->mem )
   );
   spec->fmt[ formatSize ] = '\0';

   if ( not move_if_char_c( sca, '}' ) ) // --------------------------------- }
   {
      move_scanner_to_c( sca, initPos );
      return false;
   }

   return true;
}

void reset_write_specifier_c( cWriteSpecifier spec[static 1] )
{
   must_exist_c_( spec );

   spec->type = empty_chars_c();
   spec->fmt[ 0 ] = '\0';
}
