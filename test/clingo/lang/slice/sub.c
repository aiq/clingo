#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"
#include "clingo/type/int32.h" // for cInt16s

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------------- cChars
   cChars chars = c_c( "Nine pineapples" );

   cChars nine = sub_c_( cChars, chars, 0, 4 );
   expect_at_c_( chars_is_c( nine, "Nine" ) );

   cChars pineapple = sub_c_( cChars, chars, 5, 15 );
   expect_at_c_( chars_is_c( pineapple, "pineapples" ) );

   cChars emptyChars = sub_c_( cChars, chars, 6, 16 );
   expect_at_c_( is_empty_c_( emptyChars ) );

   // -------------------------------------------------------------- cInt32s
   cInt32s int32s = slice_c_( int32_t, -123, 4356, 876, -3, 98676 );

   cInt32s three = sub_c_( cInt32s, int32s, 1, 4 );
   expect_at_c_( three.s == 3 );
   expect_at_c_( three.v[ 0 ] == 4356 );
   expect_at_c_( three.v[ 2 ] == -3 );

   cInt32s one = sub_c_( cInt32s, int32s, 2, 3 );
   expect_at_c_( one.s == 1 );
   expect_at_c_( one.v[ 0 ] == 876 );

   return finish_tap_c_();
}
