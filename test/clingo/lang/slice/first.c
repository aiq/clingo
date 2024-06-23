#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abc = c_c( "abc" );
   expect_at_c_( first_c_( abc ) == 'a' );

   cChars foo = c_c( "xyz" );
   expect_at_c_( first_c_( foo ) == 'x' );

   return finish_tap_c_();
}
