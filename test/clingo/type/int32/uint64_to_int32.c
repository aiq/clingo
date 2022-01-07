#include "clingo/lang/expect.h"
#include "clingo/type/int32.h"

int main( void )
{
   init_tap_c_();

   int32_t i32 = 0;

   // ----------------------------------------------------------------- uint64_t
   uint64_t u64 = 2147483647; // INT32_MAX
   expect_c_( uint64_to_int32_c( u64, &i32 ) );
   expect_c_( u64 == 2147483647 );

   ++u64;   // 2147483648
   expect_c_( not uint64_to_int32_c( u64, &i32 ) );

   return finish_tap_c_();
}
