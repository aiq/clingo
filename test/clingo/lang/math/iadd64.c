#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int64_t res = 0;

   expect_c_( iadd64_c( 123123123123, 123123123123, &res ) );
   expect_c_( res == 246246246246 );

   expect_c_( iadd64_c( 123123123123, -321321321321, &res ) );
   expect_c_( res == -198198198198 );

   expect_c_( not iadd64_c( INT64_MAX, 1, &res ) );
   expect_c_( res == -198198198198 );

   expect_c_( not iadd64_c( INT64_MIN, -1, &res ) );
   expect_c_( res == -198198198198 );

   return finish_tap_c_();
}
