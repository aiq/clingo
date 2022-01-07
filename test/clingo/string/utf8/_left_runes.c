#include "clingo/func/utf8.h"

#include "clingo/lang/expect.h"

/***********************************************************************************************************************

***********************************************************************************************************************/

int main( int argc, const char** args )
{
   begin_test_c( __FILE__, argc, args );

   // uft8
   cCharField utf8 = cf_c_( "abcd€f®" );

   cCharField u0 = left_runes_c( utf8, 0 );
   expect_true_c_( field_is_empty_c_( u0 ) );

   cCharField u4 = left_runes_c( utf8, 4 );
   expect_equal_c_( u4.size, 4 );
   expect_true_c_( char_field_is_c( u4, "abcd" ) );

   cCharField u5 = left_runes_c( utf8, 5 );
   expect_equal_c_( u5.size, 7 );
   expect_true_c_( char_field_is_c( u5, "abcd€" ) );

   cCharField u6 = left_runes_c( utf8, 6 );
   expect_equal_c_( u6.size, 8 );
   expect_true_c_( char_field_is_c( u6, "abcd€f" ) );

   cCharField u7 = left_runes_c( utf8, 7 );
   expect_equal_c_( u7.size, 10 );
   expect_true_c_( char_field_is_c( u7, "abcd€f®" ) );

   cCharField u14 = left_runes_c( utf8, 14 );
   expect_true_c_( field_is_empty_c_( u14 ) );

   // ascii
   cCharField ascii = cf_c_( "abcdefg" );

   cCharField a0 = left_runes_c( ascii, 0 );
   expect_true_c_( field_is_empty_c_( a0 ) );

   cCharField a4 = left_runes_c( ascii, 4 );
   expect_equal_c_( a4.size, 4 );
   expect_true_c_( char_field_is_c( a4, "abcd" ) );

   cCharField a5 = left_runes_c( ascii, 5 );
   expect_equal_c_( a5.size, 5 );
   expect_true_c_( char_field_is_c( a5, "abcde" ) );

   cCharField a6 = left_runes_c( ascii, 6 );
   expect_equal_c_( a6.size, 6 );
   expect_true_c_( char_field_is_c( a6, "abcdef" ) );

   cCharField a7 = left_runes_c( ascii, 7 );
   expect_equal_c_( a7.size, 7 );
   expect_true_c_( char_field_is_c( a7, "abcdefg" ) );

   cCharField a14 = left_runes_c( ascii, 14 );
   expect_true_c_( field_is_empty_c_( a14 ) );

   // from empty
   cCharField empty = left_runes_c( empty_char_field_c(), 15 );
   expect_true_c_( field_is_empty_c_( empty ) );

   return test_result_c();
}