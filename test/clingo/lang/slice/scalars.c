#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/int64.h" // for cInt64Slice

int main( void )
{
   init_tap_c_();

   cVarInt64Slice slice = scalars_c_( 3, int64_t );
   slice.v[ 0 ] = -10;
   slice.v[ 1 ] = 100;
   slice.v[ 2 ] = 200;

   expect_c_( slice.s == 3 );
   expect_c_( slice.v[ 0 ] == -10 );
   expect_c_( slice.v[ 1 ] == 100 );
   expect_c_( slice.v[ 2 ] == 200 );

   // wrong code we acces the memory outside the array
   // slice.v[ 3 ] = 999;

   return finish_tap_c_();
}
