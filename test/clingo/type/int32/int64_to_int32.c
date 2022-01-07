#include "clingo/lang/expect.h"
#include "clingo/type/int32.h"

int main( void )
{
   init_tap_c_();

   int32_t i32 = 0;

   // ---------------------------------------------------------------------- max
   int64_t i64 = 2147483647;  // INT32_MAX
   expect_c_( int64_to_int32_c( i64, &i32 ) );
   expect_c_( i32 == 2147483647 );

   ++i64;   // 2147483648
   expect_c_( not int64_to_int32_c( i64, &i32 ) );

   // ---------------------------------------------------------------------- min
   i64 = -2147483648;   // INT32_MIN
   expect_c_( int64_to_int32_c( i64, &i32 ) );
   expect_c_( i32 == -2147483648 );

   --i64;   // -2147483649
   expect_c_( not int64_to_int32_c( i64, &i32 ) );

   return finish_tap_c_();
}
