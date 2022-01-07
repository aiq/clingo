#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abc = c_c( "abc" );
   expect_c_( *begin_c_( abc ) == 'a' );

   char const* iter = begin_c_( abc );
   expect_c_( *iter == 'a' );

   ++iter;
   expect_c_( *iter == 'b' );

   ++iter;
   expect_c_( *iter == 'c' );

   ++iter;
   expect_c_( iter == end_c_( abc ) );

   return finish_tap_c_();
}
