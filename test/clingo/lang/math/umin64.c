#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( umin64_c( 10457939926978232596ULL,
                         9223372036854775807 )
              == 9223372036854775807 );

   return finish_tap_c_();
}
