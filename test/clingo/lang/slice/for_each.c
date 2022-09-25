#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cVarChars buf = scalars_c_( 8, char );

   bool flag = true;
   for_each_c_( char*, c, buf )
   {
      if ( flag )
      {
         *c = '+';
         flag = false;
      }
      else
      {
         *c = '.';
         flag = true;
      }
   }

   cChars slc = as_c_( cChars, buf );
   expect_c_( chars_is_c( slc, "+.+.+.+." ) );

   return finish_tap_c_();
}
