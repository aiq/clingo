#include "clingo/lang/expect.h"
#include "clingo/type/cByte.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( byte_as_bit_c( 0 ) == 0 );
   expect_at_c_( byte_as_bit_c( 1 ) == 1 );

   expect_at_c_( byte_as_bit_c( '0' ) == 0 ); // ascii 30
   expect_at_c_( byte_as_bit_c( '1' ) == 1 ); // ascii 31

   expect_at_c_( byte_as_bit_c( 2 ) == 0 );
   expect_at_c_( byte_as_bit_c( 3 ) == 1 );

   return finish_tap_c_();
}
