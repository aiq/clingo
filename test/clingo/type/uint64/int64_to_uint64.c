#include "clingo/lang/expect.h"
#include "clingo/type/uint64.h"

int main( void )
{
   init_tap_c_();

   uint64_t u64 = UINT64_MAX;

   // ------------------------------------------------------------------ int64_t
   int64_t i64 = 0;
   expect_at_c_( int64_to_uint64_c( i64, &u64 ) );
   expect_at_c_( i64 == 0 );

   --i64;
   expect_at_c_( not int64_to_uint64_c( i64, &u64 ) );

   return finish_tap_c_();
}
