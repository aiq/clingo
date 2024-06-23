#include "clingo/lang/expect.h"
#include "clingo/type/uint32.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( swap_uint32_c( 0xb7af0000 ) ==
                             0x0000afb7 );

   return finish_tap_c_();
}
