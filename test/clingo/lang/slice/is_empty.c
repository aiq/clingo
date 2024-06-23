#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( is_empty_c_( (cChars)empty_c_() ) );
   expect_at_c_( is_empty_c_( c_c( "" ) ) );

   cChars abc = c_c( "abc" );
   expect_at_c_( not is_empty_c_( abc ) );
   abc.s = 0;
   expect_at_c_( is_empty_c_( abc ) );

   return finish_tap_c_();
}
