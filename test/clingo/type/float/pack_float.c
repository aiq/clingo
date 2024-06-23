#include "clingo/lang/expect.h"
#include "clingo/type/float.h"

int main( void )
{
   init_tap_c_();

   float ordered = 2.9988165487136453e-38f;
   expect_at_c_( pack_float_c( ordered ) == 0x01234567 );

   float min = 1.4e-45f;
   expect_at_c_( pack_float_c( min ) == 0x00000001 );
  
   float max = 3.4028234e38f;
   expect_at_c_( pack_float_c( max ) == 0x7f7fffff );

   return finish_tap_c_();
}
