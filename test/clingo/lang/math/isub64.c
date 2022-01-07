#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int64_t res = 0;

   expect_c_( isub64_c( 246246246246, 123123123123, &res ) );
   expect_c_( res == 123123123123 );

   expect_c_( isub64_c( 123123123123, -198198198198, &res ) );
   expect_c_( res == 321321321321 );

   expect_c_( not isub64_c( INT64_MAX, -1, &res ) );
   expect_c_( res == 321321321321 );

   expect_c_( not isub64_c( INT64_MIN, 1, &res ) );
   expect_c_( res == 321321321321 );

   return finish_tap_c_();
}
