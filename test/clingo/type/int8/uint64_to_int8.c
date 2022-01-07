#include "clingo/lang/expect.h"
#include "clingo/type/int8.h"

int main( void )
{
   init_tap_c_();

   int8_t i8 = 0;

   // ----------------------------------------------------------------- uint64_t
   uint64_t u64 = 127;  // INT8_MAX
   expect_c_( uint64_to_int8_c( u64, &i8 ) );
   expect_c_( i8 == 127 );

   ++u64;   // 128
   expect_c_( not uint64_to_int8_c( u64, &i8 ) );

   return finish_tap_c_();
}
