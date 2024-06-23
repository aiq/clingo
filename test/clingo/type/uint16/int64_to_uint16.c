#include "clingo/lang/expect.h"
#include "clingo/type/uint16.h"

int main( void )
{
   init_tap_c_();

   uint16_t u16 = 0;

   // ------------------------------------------------------------ max - int32_t
   int32_t i32 = 65535; // UINT16_MAX
   expect_at_c_( int64_to_uint16_c( i32, &u16 ) );
   expect_at_c_( u16 == 65535 );

   ++i32;   // 65536
   expect_at_c_( not int64_to_uint16_c( i32, &u16 ) );

   // ------------------------------------------------------------ min - int16_t
   int16_t i16 = 0;
   expect_at_c_( int64_to_uint16_c( i16, &u16 ) );
   expect_at_c_( u16 == 0 );

   --i16;   // -1
   expect_at_c_( not int64_to_uint16_c( i16, &u16 ) );

   return finish_tap_c_();
}
