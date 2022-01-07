#include "clingo/lang/expect.h"
#include "clingo/type/int16.h"

int main( void )
{
   init_tap_c_();

   int16_t i16 = 0;

   // ----------------------------------------------------------------- uint64_t
   uint64_t u64 = 32767;   // INT16_MAX
   expect_c_( uint64_to_int16_c( u64, &i16 ) );
   expect_c_( i16 == 32767 );

   ++u64;   // 32768
   expect_c_( not uint64_to_int16_c( u64, &i16 ) );

   return finish_tap_c_();
}
