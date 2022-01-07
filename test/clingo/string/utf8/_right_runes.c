#include "clingo/func/utf8.h"

#include "clingo/lang/expect.h"

/***********************************************************************************************************************

***********************************************************************************************************************/

int main( int argc, const char** args )
{
   begin_test_c( __FILE__, argc, args );

   // uft8
   cCharField utf8 = cf_c_( "abcd€f®" );

   cCharField u0 = right_runes_c( utf8, 0 );
   expect_true_c_( field_is_empty_c_( u0 ) );

   cCharField u4 = right_runes_c( utf8, 1 );
   expect_equal_c_( u4.size, 2 );
   expect_true_c_( char_field_is_c( u4, "®" ) );

   cCharField u5 = right_runes_c( utf8, 3 );
   expect_equal_c_( u5.size, 6 );
   expect_true_c_( char_field_is_c( u5, "€f®" ) );

   cCharField u6 = right_runes_c( utf8, 4 );
   expect_equal_c_( u6.size, 7 );
   expect_true_c_( char_field_is_c( u6, "d€f®" ) );

   cCharField u7 = right_runes_c( utf8, 7 );
   expect_equal_c_( u7.size, 10 );
   expect_true_c_( char_field_is_c( u7, "abcd€f®" ) );

   cCharField u14 = right_runes_c( utf8, 14 );
   expect_true_c_( field_is_empty_c_( u14 ) );

   // ascii
   cCharField ascii = cf_c_( "abcdefg" );

   cCharField a0 = right_runes_c( ascii, 0 );
   expect_true_c_( field_is_empty_c_( a0 ) );

   cCharField a4 = right_runes_c( ascii, 1 );
   expect_equal_c_( a4.size, 1 );
   expect_true_c_( char_field_is_c( a4, "g" ) );

   cCharField a5 = right_runes_c( ascii, 3 );
   expect_equal_c_( a5.size, 3 );
   expect_true_c_( char_field_is_c( a5, "efg" ) );

   cCharField a6 = right_runes_c( ascii, 4 );
   expect_equal_c_( a6.size, 4 );
   expect_true_c_( char_field_is_c( a6, "defg" ) );

   cCharField a7 = right_runes_c( ascii, 7 );
   expect_equal_c_( a7.size, 7 );
   expect_true_c_( char_field_is_c( a7, "abcdefg" ) );

   cCharField a14 = right_runes_c( ascii, 14 );
   expect_true_c_( field_is_empty_c_( a14 ) );

   // from empty
   cCharField empty = right_runes_c( empty_char_field_c(), 15 );
   expect_true_c_( field_is_empty_c_( empty ) );

   return test_result_c();
}