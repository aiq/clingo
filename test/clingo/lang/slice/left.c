#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"
#include "clingo/type/int64.h" // for cInt64Slice

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------------- cChars
   cChars chars = c_c( "Pineapple" );

   cChars pine = left_c_( cChars, chars, 4 );
   expect_at_c_( chars_is_c( pine, "Pine" ) );

   cChars pineapple = left_c_( cChars, chars, 128 );
   expect_at_c_( chars_is_c( pineapple, "Pineapple" ) );

   cChars empty = left_c_( cChars, chars, 0 );
   expect_at_c_( is_empty_c_( empty ) );

   // -------------------------------------------------------------- cInt64Slice
   cInt64Slice int64s = slice_c_( int64_t, 123, -456, 789, 369, 246 );

   cInt64Slice three = left_c_( cInt64Slice, int64s, 3 );
   expect_at_c_( three.s == 3 );
   expect_at_c_( three.v[ 0 ] == 123 );
   expect_at_c_( three.v[ 2 ] == 789 );

   return finish_tap_c_();
}
