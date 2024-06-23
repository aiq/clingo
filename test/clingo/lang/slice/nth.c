#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abcdef = c_c( "abcdef" );

   expect_at_c_( *nth_c_( abcdef, 0 ) == 'a' );
   expect_at_c_( *nth_c_( abcdef, 5 ) == 'f' );

   expect_at_c_( *nth_c_( abcdef, -1 ) == 'f' );
   expect_at_c_( *nth_c_( abcdef, -6 ) == 'a' );

   expect_at_c_( nth_c_( abcdef, 6 ) == NULL );
   expect_at_c_( nth_c_( abcdef, -7 ) == NULL );

   return finish_tap_c_();
}
