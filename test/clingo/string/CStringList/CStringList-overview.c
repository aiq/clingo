#include "clingo/lang/expect.h"
#include "clingo/string/CStringList.h"

#define expect_str_( Str, Exp )                                                \
   expect_at_c_( string_is_c( (Str), (Exp) ) )

int main( void )
{
   init_tap_c_();

   CStringList* list = retain_c( make_string_list_c( 1 ) );
   cVecInfo const* info = info_of_string_list_c( list );

   expect_at_c_( vec_is_empty_c( info ) );
   expect_at_c_( info->cap == 1 );
   expect_at_c_( info->count == 0 );

   add_cstr_to_string_list_c( list, "abc" );
   add_to_string_list_c( list, lit_c( "def" ) );

   expect_at_c_( not vec_is_empty_c( info ) );
   expect_at_c_( info->cap > 1 );
   expect_at_c_( info->count == 2 );

   CString* arr[3]= { lit_c( "bang" ), lit_c( "bang" ), lit_c( "bing" ) };
   add_array_to_string_list_c( list, 3, arr );

   expect_at_c_( info->count == 5 );

   expect_str_( get_from_string_list_c( list, 0 ), "abc" );
   expect_str_( get_from_string_list_c( list, 2 ), "bang" );
   expect_str_( get_from_string_list_c( list, 4 ), "bing" );

   set_cstr_on_string_list_c( list, 4, "!?" );
   expect_str_( get_from_string_list_c( list, 4 ), "!?" );

   insert_cstr_into_string_list_c( list, 3, "BOOM" );

   expect_at_c_( info->count == 6 );

   CString* joined = join_string_list_c_( list, " " );
   expect_str_( joined, "abc def bang BOOM bang !?" );

   sort_string_list_c( list );
   CString* sorted = join_string_list_c_( list, " - " );
   expect_str_( sorted, "!? - BOOM - abc - bang - bang - def" );

   expect_at_c_( remove_from_string_list_c( list, 2 ) );
   CString* reduced = join_string_list_c_( list, "_" );
   expect_str_( reduced, "!?_BOOM_bang_bang_def" );

   resize_string_list_c( list, info->count );
   expect_at_c_( info->cap == info->count );

   release_all_c_( list, joined, sorted, reduced );

   return finish_tap_c_();
}
