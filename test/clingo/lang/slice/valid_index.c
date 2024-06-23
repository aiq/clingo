#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars empty = empty_c_();
   expect_at_c_( !valid_index_c_( empty, 0 ) );
   expect_at_c_( !valid_index_c_( empty, 1 ) );

   cChars abc = c_c( "abc" );
   expect_at_c_( !valid_index_c_( abc, -1 ) );
   expect_at_c_(  valid_index_c_( abc,  0 ) );
   expect_at_c_(  valid_index_c_( abc,  1 ) );
   expect_at_c_(  valid_index_c_( abc,  2 ) );
   expect_at_c_( !valid_index_c_( abc,  3 ) );

   return finish_tap_c_();
}
