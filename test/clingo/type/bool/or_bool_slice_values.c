#include "clingo/lang/expect.h"
#include "clingo/type/bool.h"

int main( void )
{
   init_tap_c_();

   cBoolSlice s000 = slice_c_( bool, false, false, false );
   cBoolSlice s001 = slice_c_( bool, false, false,  true );
   cBoolSlice s010 = slice_c_( bool, false,  true, false );
   cBoolSlice s011 = slice_c_( bool, false,  true,  true );
   cBoolSlice s100 = slice_c_( bool,  true, false, false );
   cBoolSlice s101 = slice_c_( bool,  true, false,  true );
   cBoolSlice s110 = slice_c_( bool,  true,  true, false );
   cBoolSlice s111 = slice_c_( bool,  true,  true,  true );

   expect_at_c_( not or_bool_slice_values_c( s000 ) );
   expect_at_c_( or_bool_slice_values_c( s001 ) );
   expect_at_c_( or_bool_slice_values_c( s010 ) );
   expect_at_c_( or_bool_slice_values_c( s011 ) );
   expect_at_c_( or_bool_slice_values_c( s100 ) );
   expect_at_c_( or_bool_slice_values_c( s101 ) );
   expect_at_c_( or_bool_slice_values_c( s110 ) );
   expect_at_c_( or_bool_slice_values_c( s111 ) );

   return finish_tap_c_();
}
