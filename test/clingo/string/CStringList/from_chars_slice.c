#include "clingo/lang/expect.h"
#include "clingo/string/CStringList.h"

int main( void )
{
   init_tap_c_();

   cCharsSlice slice = cs_c_( "abc", "def", "gh", "ij", "klmn", "opq" );
   CStringList* list = from_chars_slice_c( slice );

   CString* str = join_string_list_c_( list, "." );
   expect_c_( string_is_c( str, "abc.def.gh.ij.klmn.opq" ) );

   release_all_c_( list, str );

   return finish_tap_c_();
}
