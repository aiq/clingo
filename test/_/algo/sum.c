#include "clingo/lang/expect.h"

#include "clingo/type/int32.h"

int main( void )
{
   init_tap_c_();

   cInt32Slice slice = slice_c_( int32_t, 50, 32, 123456, 99, -18, -65, 2 );
   int64_t res = 0;
   expect_c_( sum_int32_c( slice, &res ) );
   expect_c_( res == 123556 );

   return finish_tap_c_();
}
