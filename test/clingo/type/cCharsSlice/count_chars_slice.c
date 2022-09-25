#include "clingo/lang/expect.h"
#include "clingo/type/cCharsSlice.h"

int main( void )
{
   init_tap_c_();

   cVarCharsSlice slice = structs_c_( 4, cChars );
   slice.v[0] = c_c( "simple" );
   slice.v[1] = c_c( "ascii text" );
   slice.v[2] = c_c( "" );
   slice.v[3] = c_c( "" );
   
   expect_c_( count_chars_slice_c( as_c_( cCharsSlice, slice ) ) == 16 );

   slice.v[2] = c_c( "€uro" ); // 6
   expect_c_( count_chars_slice_c( as_c_( cCharsSlice, slice ) ) == 22 );

   slice.v[3] = c_c( "🚀" ); // 4
   expect_c_( count_chars_slice_c( as_c_( cCharsSlice, slice ) ) == 26 );

   return finish_tap_c_();
}
