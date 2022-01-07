#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   expect_eq_c_( cmp_chars_c( c_c( "Hello world!" ),
                              c_c( "Hello world!" ) ) );

   expect_lt_c_( cmp_chars_c( c_c( "Hello" ),
                              c_c( "Hello world!" ) ) );
   expect_gt_c_( cmp_chars_c( c_c( "Hello world!" ),
                              c_c( "Hello" ) ) );

   expect_lt_c_( cmp_chars_c( c_c( "Hello world!" ),
                              c_c( "world" ) ) );
   expect_gt_c_( cmp_chars_c( c_c( "world" ),
                              c_c( "Hello world!" ) ) );

   return finish_tap_c_();
}
