#include "clingo/lang/expect.h"
#include "clingo/type/int16.h"

int main( void )
{
   init_tap_c_();

   // 0x0001 -> 0x0100
   expect_at_c_( swap_int16_c( 1 ) == 256 );
   // 0x2080 -> 0x8020
   expect_at_c_( swap_int16_c( 0x2080 ) == -32736 );

   return finish_tap_c_();
}
