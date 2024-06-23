#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abc = c_c( "abc" );
   expect_at_c_( *rbegin_c_( abc ) == 'c' );

   char const* itr = rbegin_c_( abc );
   expect_at_c_( *itr == 'c' );

   itr--;
   expect_at_c_( *itr == 'b' );

   itr--;
   expect_at_c_( *itr == 'a' );

   itr--;
   expect_at_c_( itr == rend_c_( abc ) );

   return finish_tap_c_();
}
