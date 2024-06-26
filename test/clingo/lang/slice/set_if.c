#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/int64.h" // for cInt64Slice

int main( void )
{
   init_tap_c_();

   cVarInt64Slice slice4 = slice_c_( int64_t, 11, 22, 33, 44 );
   cVarInt64Slice slice3 = left_c_( cVarInt64Slice, slice4, 3 );
   set_if_c_( slice3, 0, 10 );
   set_if_c_( slice3, 1, 20 );
   set_if_c_( slice3, 2, 30 );
   set_if_c_( slice3, 3, 40 ); // out of slice range

   expect_at_c_( slice4.v[ 0 ] == 10 );
   expect_at_c_( slice4.v[ 1 ] == 20 );
   expect_at_c_( slice4.v[ 2 ] == 30 );
   expect_at_c_( slice4.v[ 3 ] == 44 ); // not set

   return finish_tap_c_();
}
