#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abc = c_c( "abcx" );
   abc.s--;
   expect_at_c_( *end_c_( abc ) == 'x' );

   char const* iter = end_c_( abc );
   expect_at_c_( *iter == 'x' );

   --iter;
   expect_at_c_( *iter == 'c' );

   --iter;
   expect_at_c_( *iter == 'b' );

   --iter;
   expect_at_c_( iter == begin_c_( abc ) );

   return finish_tap_c_();
}
