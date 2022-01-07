#include "clingo/func/utf8.h"

#include "clingo/lang/expect.h"

/***********************************************************************************************************************

***********************************************************************************************************************/

int main( int argc, const char** args )
{
   begin_test_c( __FILE__, argc, args );

   // uft8
   cCharField utf8 = cf_c_( "abcd€f®" );

   cCharField u0 = mid_runes_c( utf8, 0 );
   expect_equal_c_( u0.size, 10 );
   expect_true_c_( char_field_is_c( u0, "abcd€f®" ) );

   cCharField u4 = mid_runes_c( utf8, 4 );
   expect_equal_c_( u4.size, 6 );
   expect_true_c_( char_field_is_c( u4, "€f®" ) );

   cCharField u5 = mid_runes_c( utf8, 5 );
   expect_equal_c_( u5.size, 3 );
   expect_true_c_( char_field_is_c( u5, "f®" ) );

   cCharField u6 = mid_runes_c( utf8, 6 );
   expect_equal_c_( u6.size, 2 );
   expect_true_c_( char_field_is_c( u6, "®" ) );

   cCharField u7 = mid_runes_c( utf8, 7 );
   expect_true_c_( field_is_empty_c_( u7 ) );

   cCharField u14 = mid_runes_c( utf8, 14 );
   expect_true_c_( field_is_empty_c_( u14 ) );

   // ascii
   cCharField ascii = cf_c_( "abcdefg" );

   cCharField a0 = mid_runes_c( ascii, 0 );
   expect_equal_c_( a0.size, 7 );
   expect_true_c_( char_field_is_c( a0, "abcdefg" ) );

   cCharField a4 = mid_runes_c( ascii, 4 );
   expect_equal_c_( a4.size, 3 );
   expect_true_c_( char_field_is_c( a4, "efg" ) );

   cCharField a5 = mid_runes_c( ascii, 5 );
   expect_equal_c_( a5.size, 2 );
   expect_true_c_( char_field_is_c( a5, "fg" ) );

   cCharField a6 = mid_runes_c( ascii, 6 );
   expect_equal_c_( a6.size, 1 );
   expect_true_c_( char_field_is_c( a6, "g" ) );

   cCharField a7 = mid_runes_c( ascii, 7 );
   expect_true_c_( field_is_empty_c_( a7 ) );

   cCharField a14 = mid_runes_c( ascii, 14 );
   expect_true_c_( field_is_empty_c_( a14 ) );

   // from empty
   cCharField empty = mid_runes_c( empty_char_field_c(), 15 );
   expect_true_c_( field_is_empty_c_( empty ) );

   return test_result_c();
}