#include "clingo/lang/expect.h"
#include "clingo/type/float.h"

int main( void )
{
   init_tap_c_();

   // macro with FLT_EPSILON
   expect_c_(  eq_float_c_( 0.123456f, 0.123456f ) );
   expect_c_( !eq_float_c_( 0.123456f, 0.123654f ) );

   // function with custom epsilon
   expect_c_( !eq_float_c( 0.123456f, 0.123654f, 0.000001f ) );
   expect_c_(  eq_float_c( 0.123456f, 0.123654f, 0.1f ) );

   return finish_tap_c_();
}
