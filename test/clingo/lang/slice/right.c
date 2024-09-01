#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"
#include "clingo/type/int8.h" // for cInt8s

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------------- cChars
   cChars chars = c_c( "Pineapple" );

   cChars pple = right_c_( cChars, chars, 4 );
   expect_at_c_( chars_is_c( pple, "pple" ) );

   cChars pineapple = right_c_( cChars, chars, 12 );
   expect_at_c_( chars_is_c( pineapple, "Pineapple" ) );

   cChars empty = right_c_( cChars, chars, 0 );
   expect_at_c_( is_empty_c_( empty ) );

   // --------------------------------------------------------------- cInt8s
   cInt8s int8s = slice_c_( int8_t, 8, 27, -99, 23, 77, 80, -111 );

   cInt8s four = right_c_( cInt8s, int8s, 4 );
   expect_at_c_( four.s == 4 );
   expect_at_c_( four.v[ 0 ] == 23 );
   expect_at_c_( four.v[ 3 ] == -111 );

   return finish_tap_c_();
}
