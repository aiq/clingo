#include "clingo/lang/expect.h"
#include "clingo/type/int32.h" // find_max_c

int main( void )
{
   init_tap_c_();

   cInt32s slice = slice_c_( int32_t, 50, 123456, 99, 123456, -65 );

   int32_t const* max = max_int32_c( slice );
   expect_at_c_( index_of_c_( slice, max ) == 1 );
   expect_at_c_( *max == 123456 );

   return finish_tap_c_();
}
