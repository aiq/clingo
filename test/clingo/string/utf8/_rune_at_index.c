#include "clingo/func/utf8.h"

#include "clingo/lang/expect.h"

int main( int argc, const char** args )
{
   begin_test_c( __FILE__, argc, args );

   // ®/2  ☂/3
   cCharField field = cf_c_( "®=☂" );
   expect_true_c_( rune_is_c( rune_at_index_c( field, 0 ), "®" ) );
   expect_true_c_( rune_is_c( rune_at_index_c( field, 1 ), "®" ) );
   expect_true_c_( rune_is_c( rune_at_index_c( field, 2 ), "=" ) );
   expect_true_c_( rune_is_c( rune_at_index_c( field, 3 ), "☂" ) );
   expect_true_c_( rune_is_c( rune_at_index_c( field, 4 ), "☂" ) );
   expect_true_c_( rune_is_c( rune_at_index_c( field, 5 ), "☂" ) );

   return test_result_c();
}