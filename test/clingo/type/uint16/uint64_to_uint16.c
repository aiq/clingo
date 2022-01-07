#include "clingo/lang/expect.h"
#include "clingo/type/uint16.h"

int main( void )
{
   init_tap_c_();

   uint16_t u16 = 0;

   // ----------------------------------------------------------------- uint32_t
   uint32_t u32 = 65535;   // UINT16_MAX
   expect_c_( uint64_to_uint16_c( u32, &u16 ) );
   expect_c_( u16 == 65535 );

   ++u32;   // 65536
   expect_c_( not uint64_to_uint16_c( u32, &u16 ) );

   return finish_tap_c_();
}
