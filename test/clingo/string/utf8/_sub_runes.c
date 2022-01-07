#include "clingo/func/utf8.h"

#include "clingo/lang/expect.h"

/***********************************************************************************************************************

***********************************************************************************************************************/

int main( int argc, const char** args )
{
   begin_test_c( __FILE__, argc, args );

   // uft8
   cCharField utf8 = cf_c_( "abcd€f®" );

   cCharField u0 = sub_runes_c( utf8, closed_range32_c_( 0, -1 ) );
   expect_true_c_( field_is_empty_c_( u0 ) );

   cCharField u6_6 = sub_runes_c( utf8, closed_range32_c_( 6, 6 ) );
   expect_equal_c_( u6_6.size, 2 );
   expect_true_c_( char_field_is_c( u6_6, "®" ) );

   cCharField u4_5 = sub_runes_c( utf8, closed_range32_c_( 4, 5 ) );
   expect_equal_c_( u4_5.size, 4 );
   expect_true_c_( char_field_is_c( u4_5, "€f" ) );

   cCharField u0_3 = sub_runes_c( utf8, closed_range32_c_( 0, 3 ) );
   expect_equal_c_( u0_3.size, 4 );
   expect_true_c_( char_field_is_c( u0_3, "abcd" ) );

   cCharField u2_5 = sub_runes_c( utf8, closed_range32_c_( 2, 5 ) );
   expect_equal_c_( u2_5.size, 6 );
   expect_true_c_( char_field_is_c( u2_5, "cd€f" ) );

   cCharField u4_14 = sub_runes_c( utf8, closed_range32_c_( 4, 14 ) );
   expect_true_c_( field_is_empty_c_( u4_14 ) );

   // ascii
   cCharField ascii = cf_c_( "abcdefg" );

   cCharField a0 = sub_runes_c( ascii, closed_range32_c_( 0, -1 ) );
   expect_true_c_( field_is_empty_c_( a0 ) );

   cCharField a6_6 = sub_runes_c( ascii, closed_range32_c_( 6, 6 ) );
   expect_equal_c_( a6_6.size, 1 );
   expect_true_c_( char_field_is_c( a6_6, "g" ) );

   cCharField a4_5 = sub_runes_c( ascii, closed_range32_c_( 4, 5 ) );
   expect_equal_c_( a4_5.size, 2 );
   expect_true_c_( char_field_is_c( a4_5, "ef" ) );

   cCharField a0_3 = sub_runes_c( ascii, closed_range32_c_( 0, 3 ) );
   expect_equal_c_( a0_3.size, 4 );
   expect_true_c_( char_field_is_c( a0_3, "abcd" ) );

   cCharField a2_5 = sub_runes_c( ascii, closed_range32_c_( 2, 5 ) );
   expect_equal_c_( a2_5.size, 4 );
   expect_true_c_( char_field_is_c( a2_5, "cdef" ) );

   cCharField a4_14 = sub_runes_c( ascii, closed_range32_c_( 4, 14 ) );
   expect_true_c_( field_is_empty_c_( a4_14 ) );

   // from empty
   cCharField empty = sub_runes_c( empty_char_field_c(), closed_range32_c_( 15, 15 ) );
   expect_true_c_( field_is_empty_c_( empty ) );

   return test_result_c();
}
