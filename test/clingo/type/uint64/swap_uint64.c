#include "clingo/lang/expect.h"
#include "clingo/type/uint64.h"

int main( void )
{
   init_tap_c_();
  
   expect_at_c_( swap_uint64_c( 0x0123456789abcdef ) ==
                             0xefcdab8967452301 );

   return finish_tap_c_();
}
