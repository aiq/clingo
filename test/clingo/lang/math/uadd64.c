#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   uint64_t res = 0;

   expect_c_( uadd64_c( 9223372036854775807, 1234567890123456789, &res ) );
   expect_c_( res == 10457939926978232596ULL );

   expect_c_( not uadd64_c( UINT64_MAX, 1, &res ) );
   expect_c_( res == 10457939926978232596ULL );

   return finish_tap_c_();
}
