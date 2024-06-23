#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint64_t res = 0;

   expect_at_c_( usub64_c( 9223372036854775807, 1234567890123456789, &res ) );
   expect_at_c_( res == 7988804146731319018ULL );

   expect_at_c_( not usub64_c( 9223372036854775807, UINT64_MAX, &res ) );
   expect_at_c_( res == 7988804146731319018ULL );

   return finish_tap_c_();
}
