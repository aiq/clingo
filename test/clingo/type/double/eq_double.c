#include "clingo/lang/expect.h"
#include "clingo/type/double.h"

int main( void )
{
   init_tap_c_();

   // macro with DBL_EPSILON
   expect_c_( eq_double_c_( 0.1234567890123,
                            0.1234567890123 ) );
   expect_c_( not eq_double_c_( 0.1234567890123,
                                0.1237 ) );

   // function with custom epsilon
   expect_c_( not eq_double_c( 0.1234567890123, 
                               0.1237,
                               0.000001 ) );
   expect_c_( eq_double_c( 0.1234567890123,
                           0.1237,
                           0.1 ) );

   return finish_tap_c_();
}
