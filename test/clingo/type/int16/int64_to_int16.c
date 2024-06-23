#include "clingo/lang/expect.h"
#include "clingo/type/int16.h"

int main( void )
{
   init_tap_c_();

   int16_t i16 = 0;

   // ------------------------------------------------------------ max - int64_t
   int64_t i64 = 32767; // INT16_MAX
   expect_at_c_( int64_to_int16_c( i64, &i16 ) );
   expect_at_c_( i16 == 32767 );

   ++i64;   // 32768
   expect_at_c_( not int64_to_int16_c( i64, &i16 ) );

   // ------------------------------------------------------------ min - int32_t
   int32_t i32 = -32768;   // INT16_MIN
   expect_at_c_( int64_to_int16_c( i32, &i16 ) );
   expect_at_c_( i16 == -32768 );

   --i32;   // -32769
   expect_at_c_( not int64_to_int16_c( i32, &i16 ) );

   return finish_tap_c_();
}
