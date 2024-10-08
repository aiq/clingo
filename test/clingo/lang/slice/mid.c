#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"
#include "clingo/type/int16.h" // for cInt16s

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------------- cChars
   cChars chars = c_c( "Nine pineapples" );

   cChars pineapples = mid_c_( cChars, chars, 5 );
   expect_at_c_( chars_is_c( pineapples, "pineapples" ) );

   cChars apples = mid_c_( cChars, chars, 9 );
   expect_at_c_( chars_is_c( apples, "apples" ) );

   cChars nullSlice = mid_c_( cChars, chars, chars.s );
   expect_at_c_( is_empty_c_( nullSlice ) );

   // -------------------------------------------------------------- cInt16s
   cInt16s int16s = slice_c_( int16_t, 8, -16, 128, -1024, 512 );

   cInt16s two = mid_c_( cInt16s, int16s, 3 );
   expect_at_c_( two.s == 2 );
   expect_at_c_( two.v[ 0 ] == -1024 );
   expect_at_c_( two.v[ 1 ] == 512 );

   return finish_tap_c_();
}
