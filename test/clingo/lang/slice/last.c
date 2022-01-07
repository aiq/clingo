#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abc = c_c( "abc" );
   expect_c_( last_c_( abc ) == 'c' );

   cChars bar = c_c( "bar" );
   expect_c_( last_c_( bar ) == 'r' );

   return finish_tap_c_();
}
