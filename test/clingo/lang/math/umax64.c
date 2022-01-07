#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_c_( umax64_c( 10457939926978232596ULL,
                         9223372036854775807 )
              == 10457939926978232596ULL );

   return finish_tap_c_();
}
