#include "clingo/lang/expect.h"
#include "clingo/lang/math.h"

int main( void )
{
   init_tap_c_();

   int32_t res = 0;

   expect_at_c_( iadd32_c( 65535, 123456789, &res ) );
   expect_at_c_( res == 123522324 );

   expect_at_c_( iadd32_c( -16156565, 546648, &res ) );
   expect_at_c_( res == -15609917 );

   expect_at_c_( not iadd32_c( INT32_MAX, 1, &res ) );
   expect_at_c_( res == -15609917 );

   expect_at_c_( not iadd32_c( INT32_MIN, -1, &res ) );
   expect_at_c_( res == -15609917 );

   return finish_tap_c_();
}
