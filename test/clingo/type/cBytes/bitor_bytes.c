#include "clingo/lang/expect.h"
#include "clingo/type/cBytes.h"

int main( void )
{
   init_tap_c_();

   cBytes a = slice_c_( cByte, 0x0f, 0xc3, 0x5d, 0x10 );
   cBytes b = slice_c_( cByte, 0x10, 0x5d, 0x0f, 0xc3 );
   cVarBytes result = scalars_c_( 4, cByte );

   bitor_bytes_c( a, b, result );

   expect_at_c_( result.v[ 0 ] == 0x1f );
   expect_at_c_( result.v[ 1 ] == 0xdf );
   expect_at_c_( result.v[ 2 ] == 0x5f );
   expect_at_c_( result.v[ 3 ] == 0xd3 );

   return finish_tap_c_();
}
