#include "clingo/lang/expect.h"
#include "clingo/type/int32.h"

int main( void )
{
   init_tap_c_();

   expect_c_( swap_int32_c( 0x7caf0000 ) == 0x0000af7c );

   return finish_tap_c_();
}
