#include "clingo/lang/expect.h"
#include "clingo/type/int64.h"

int main( void )
{
   init_tap_c_();

   int64_t i64 = 0;

   // ----------------------------------------------------------------- uint64_t
   uint64_t u64 = 9223372036854775807; // INT64_MAX
   expect_at_c_( uint64_to_int64_c( u64, &i64 ) );
   expect_at_c_( i64 == 9223372036854775807 );

   ++u64;   // 9223372036854775808
   expect_at_c_( not uint64_to_int64_c( u64, &i64 ) );

   return finish_tap_c_();
}
