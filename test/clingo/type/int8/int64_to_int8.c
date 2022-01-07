#include "clingo/lang/expect.h"
#include "clingo/type/int8.h"

int main( void )
{
   init_tap_c_();

   int8_t i8 = 0;

   // ------------------------------------------------------------ max - int64_t
   int64_t i64 = 127;   // INT8_MAX
   expect_c_( int64_to_int8_c( i64, &i8 ) );
   expect_c_( i8 == 127 );

   ++i64;   // 128
   expect_c_( not int64_to_int8_c( i64, &i8 ) );

   // ------------------------------------------------------------ min - int16_t
   int16_t i16 = -128;  // INT8_MIN
   expect_c_( int64_to_int8_c( i16, &i8 ) );
   expect_c_( i8 == -128 );

   --i16;   // -129
   expect_c_( not int64_to_int8_c( i16, &i8 ) );

   return finish_tap_c_();
}
