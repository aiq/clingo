#include "clingo/lang/expect.h"
#include "clingo/type/float.h"

int main( void )
{
   init_tap_c_();

   uint32_t ordered = 0x01234567;
   expect_c_( unpack_float_c( ordered ) == 2.9988165487136453e-38f );

   uint32_t min_float32 = 0x00000001;
   expect_c_( unpack_float_c( min_float32 ) == 1.4e-45f );
  
   uint32_t max_float32 = 0x7f7fffff;
   expect_c_( unpack_float_c( max_float32 ) == 3.4028234e38f );

   return finish_tap_c_();
}
