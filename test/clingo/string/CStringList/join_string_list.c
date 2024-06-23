#include "clingo/lang/expect.h"
#include "clingo/string/CStringList.h"

#define expect_str_( Str, Exp )                                                \
   expect_at_c_( string_is_c( (Str), (Exp) ) )

int main( void )
{
   init_tap_c_();

   CStringList* list = retain_c( new_string_list_c() );

   // ------------------------------------------------------------------ prepare
   add_cstr_to_string_list_c( list, "abc" );
   add_cstr_to_string_list_c( list, "def" );
   add_cstr_to_string_list_c( list, "ghijkl" );
   add_cstr_to_string_list_c( list, "mnopqr" );
   add_cstr_to_string_list_c( list, "stuv" );
   add_cstr_to_string_list_c( list, "wxyz" );

   // --------------------------------------------------------------------- test
   CString* str;

   str = join_string_list_c_( list, "" );
   expect_str_( str, "abcdefghijklmnopqrstuvwxyz" );
   release_c( str );

   str = join_string_list_c_( list, "-" );
   expect_str_( str, "abc-def-ghijkl-mnopqr-stuv-wxyz" );
   release_c( str );

   str = join_string_list_c_( list, " - " );
   expect_str_( str, "abc - def - ghijkl - mnopqr - stuv - wxyz" );
   release_c( str );

   release_c( list );

   return finish_tap_c_();
}
