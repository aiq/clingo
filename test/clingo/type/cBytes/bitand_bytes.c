#include "clingo/lang/expect.h"
#include "clingo/type/cBytes.h"

int main( void )
{
   init_tap_c_();

   cBytes a = slice_c_( cByte, 0x0f, 0xc3, 0x5d, 0x10 );
   cBytes b = slice_c_( cByte, 0x10, 0x5d, 0x0f, 0xc3 );
   cVarBytes result = scalars_c_( 4, cByte );

   bitand_bytes_c( a, b, result );

   expect_at_c_( result.v[ 0 ] == 0x00 );
   expect_at_c_( result.v[ 1 ] == 0x41 );
   expect_at_c_( result.v[ 2 ] == 0x0d );
   expect_at_c_( result.v[ 3 ] == 0x00 );

   return finish_tap_c_();
}
