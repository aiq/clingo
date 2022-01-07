#include "clingo/lang/expect.h"
#include "clingo/type/uint64.h"

int main( void )
{
   init_tap_c_();

   expect_c_( build_uint64_c_( 0x12345678, 0x90123456 ) ==
                               0x1234567890123456 );

   return finish_tap_c_();
}
