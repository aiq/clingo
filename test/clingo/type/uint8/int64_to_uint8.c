#include "clingo/lang/expect.h"
#include "clingo/type/uint8.h"

int main( void )
{
   init_tap_c_();

   uint8_t u8 = 0;

   // ------------------------------------------------------------ max - int32_t
   int32_t i32 = 255;   // UINT8_MAX
   expect_c_( int64_to_uint8_c( i32, &u8 ) );
   expect_c_( u8 == 255 );

   ++i32;   // 256
   expect_c_( not int64_to_uint8_c( i32, &u8 ) );

   // ------------------------------------------------------------- min - int8_t
   int8_t i8 = 0;
   expect_c_( int64_to_uint8_c( i8, &u8 ) );
   expect_c_( u8 == 0 );

   --i8; // -1
   expect_c_( not int64_to_uint8_c( i8, &u8 ) );

   return finish_tap_c_();
}
