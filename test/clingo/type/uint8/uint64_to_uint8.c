#include "clingo/lang/expect.h"
#include "clingo/type/uint8.h"

int main( void )
{
   init_tap_c_();

   uint8_t u8 = 0;

   // ----------------------------------------------------------------- uint16_t
   uint16_t u16 = 255;  // UINT8_MAX
   expect_c_( uint64_to_uint8_c( u16, &u8 ) );
   expect_c_( u8 == 255 );

   ++u16;   // 256
   expect_c_( not uint64_to_uint8_c( u16, &u8 ) );

   return finish_tap_c_();
}
