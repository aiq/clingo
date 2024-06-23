#include "clingo/lang/expect.h"
#include "clingo/type/uint16.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( swap_uint16_c( 0x2080 ) ==
                             0x8020 );

   return finish_tap_c_();
}
