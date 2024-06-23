#include "clingo/lang/expect.h"
#include "clingo/type/uint32.h"

int main( void )
{
   init_tap_c_();

   uint32_t u32 = 0;

   // ------------------------------------------------------------ max - int64_t
   int64_t i64 = 4294967295;  // UINT32_MAX
   expect_at_c_( int64_to_uint32_c( i64, &u32 ) );
   expect_at_c_( u32 == 4294967295 );

   ++i64;   // 4294967296
   expect_at_c_( not int64_to_uint32_c( i64, &u32 ) );

   // ------------------------------------------------------------ min - int32_t
   int32_t i32 = 0;
   expect_at_c_( int64_to_uint32_c( i32, &u32 ) );
   expect_at_c_( u32 == 0 );

   --i32;   // -1
   expect_at_c_( not int64_to_uint32_c( i32, &u32 ) );

   return finish_tap_c_();
}
