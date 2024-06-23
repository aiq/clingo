#include "clingo/lang/expect.h"
#include "clingo/string/CStringList.h"

#define expect_str_( Str, Exp )                                                \
   expect_at_c_( string_is_c( (Str), (Exp) ) )

int main( void )
{
   init_tap_c_();

   CStringList* list = new_string_list_c();
   retain_c( list );

   // ------------------------------------------------------------------ prepare
   add_cstr_to_string_list_c( list, "..." );
   add_cstr_to_string_list_c( list, "A" );
   add_cstr_to_string_list_c( list, "BB" );
   add_cstr_to_string_list_c( list, "A" );
   add_cstr_to_string_list_c( list, "---" );

   CString* initStr = join_string_list_c_( list, "" );
   expect_str_( initStr, "...ABBA---" );

   // --------------------------------------------------------------------- test
   CString* str;

   set_cstr_on_string_list_c( list, 0, "-+" );
   str = join_string_list_c_( list, "" );
   expect_str_( str, "-+ABBA---" );
   release_c( str );

   set_cstr_on_string_list_c( list, 4, "+-" );
   str = join_string_list_c_( list, "" );
   expect_str_( str, "-+ABBA+-" );
   release_c( str );

   set_cstr_on_string_list_c( list, 2, "-+-" );
   str = join_string_list_c_( list, "" );
   expect_str_( str, "-+A-+-A+-" );
   release_c( str );

   release_c( list );

   return finish_tap_c_();
}
