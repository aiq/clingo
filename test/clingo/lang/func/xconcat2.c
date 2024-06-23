#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"

int main( void )
{
   init_tap_c_();

   #define foo 123
   #define bar 789
   expect_at_c_( xconcat2_c_( foo, bar ) == 123789 );

   return finish_tap_c_();
}
