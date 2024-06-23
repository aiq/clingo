#include "clingo/lang/expect.h"
#include "clingo/string/CStringList.h"

int main( void )
{
   init_tap_c_();

   CStringList* list = retain_c( new_string_list_c() );

   add_cstr_to_string_list_c( list, "simple" ); // 6
   add_cstr_to_string_list_c( list, "ascii text" ); // 10
   expect_at_c_( count_string_list_chars_c( list ) == 16 );

   add_cstr_to_string_list_c( list, "€uro" ); // 6
   expect_at_c_( count_string_list_chars_c( list ) == 22 );

   add_cstr_to_string_list_c( list, "🚀" ); // 4
   expect_at_c_( count_string_list_chars_c( list ) == 26 );

   release_c( list );

   return finish_tap_c_();
}
