#include "clingo/lang/expect.h"
#include "clingo/type/uint32.h"

int main( void )
{
   init_tap_c_();

   uint32_t u32 = 0;

   // ----------------------------------------------------------------- uint64_t
   uint64_t u64 = 4294967295; // UINT32_MAX
   expect_c_( uint64_to_uint32_c( u64, &u32 ) );
   expect_c_( u64 == 4294967295 );

   ++u64;   // 4294967296
   expect_c_( not uint64_to_uint32_c( u64, &u32 ) );

   return finish_tap_c_();
}
