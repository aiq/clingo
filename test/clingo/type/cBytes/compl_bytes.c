#include "clingo/lang/expect.h"
#include "clingo/type/cBytes.h"

int main( void )
{
   init_tap_c_();

   cVarBytes slice = slice_c_( cByte, 0x0f, 0xc3, 0x5d, 0x10 );

   compl_bytes_c( as_c_( cBytes, slice ), slice );

   expect_at_c_( slice.v[ 0 ] == 0xf0 );
   expect_at_c_( slice.v[ 1 ] == 0x3c );
   expect_at_c_( slice.v[ 2 ] == 0xa2 );
   expect_at_c_( slice.v[ 3 ] == 0xef );

   return finish_tap_c_();
}
