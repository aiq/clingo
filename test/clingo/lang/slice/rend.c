#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abc = c_c( "xabc" );
   abc.v++;
   abc.s--;
   expect_at_c_( *rend_c_( abc ) == 'x' );

   char const* itr = rend_c_( abc );
   expect_at_c_( *itr == 'x' );

   itr++;
   expect_at_c_( *itr == 'a' );

   itr++;
   expect_at_c_( *itr == 'b' );

   itr++;
   expect_at_c_( itr == rbegin_c_( abc ) );

   return finish_tap_c_();
}
