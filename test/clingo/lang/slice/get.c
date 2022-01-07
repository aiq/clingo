#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abc = c_c( "abc" );
   expect_c_( get_c_( abc, -1, 'x' ) == 'x' );
   expect_c_( get_c_( abc,  0, 'x' ) == 'a' );
   expect_c_( get_c_( abc,  1, 'x' ) == 'b' );
   expect_c_( get_c_( abc,  2, 'x' ) == 'c' );
   expect_c_( get_c_( abc,  3, 'x' ) == 'x' );

   return finish_tap_c_();
}
