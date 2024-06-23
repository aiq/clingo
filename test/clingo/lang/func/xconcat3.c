#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"

int main( void )
{
   init_tap_c_();

   #define fo 12
   #define ob 56
   #define ar 90
   expect_at_c_( xconcat3_c_( fo, ob, ar ) == 125690 );

   return finish_tap_c_();
}
