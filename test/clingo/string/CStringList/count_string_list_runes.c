#include "clingo/lang/expect.h"
#include "clingo/string/CStringList.h"

int main( void )
{
   init_tap_c_();

   CStringList* list = new_string_list_c();
   retain_c( list );

   add_to_string_list_c( list, new_string_c( "simple" ) ); // 6
   add_to_string_list_c( list, new_string_c( "ascii text" ) ); // 10
   expect_c_( 16 == count_string_list_runes_c( list ) );

   add_to_string_list_c( list, new_string_c( "€uro" ) ); // 4
   expect_c_( 20 == count_string_list_runes_c( list ) );

   add_to_string_list_c( list, new_string_c( "🚀" ) ); // 1
   expect_c_( 21 == count_string_list_runes_c( list ) );

   release_c( list );

   return finish_tap_c_();
}
