#include "clingo/func/utf8.h"

#include "clingo/lang/expect.h"

/***********************************************************************************************************************

***********************************************************************************************************************/

int main( int argc, const char** args )
{
   begin_test_c( __FILE__, argc, args );

   cCharField field = cf_c_( "a 𝄞 and €" );
   cRune tmp;
   cTraverser traverser;
   init_char_field_rune_reverse_traverser_c_( &traverser, field );

   cKeyValue kv = next_c_( traverser );
   expect_equal_c_( deref_int32_c_( kv.key ), 11 );
   tmp = rune_c( kv.value );
   expect_true_c_( rune_is_c( tmp, "€" ) );
   expect_true_c_( has_next_c_( traverser ) );
   kv = next_c_( traverser ); //
   kv = next_c_( traverser ); // d

   expect_equal_c_( deref_int32_c_( kv.key ), 9 );
   tmp = rune_c( kv.value );
   expect_true_c_( rune_is_c( tmp, "d" ) );
   expect_true_c_( has_next_c_( traverser ) );
   kv = next_c_( traverser ); // n
   kv = next_c_( traverser ); // a
   kv = next_c_( traverser ); //
   kv = next_c_( traverser ); // 𝄞

   expect_equal_c_( deref_int32_c_( kv.key ), 2 );
   tmp = rune_c( kv.value );
   expect_true_c_( rune_is_c( tmp, "𝄞" ) );
   expect_true_c_( has_next_c_( traverser ) );
   kv = next_c_( traverser ); //
   kv = next_c_( traverser ); // a

   expect_equal_c_( deref_int32_c_( kv.key ), 0 );
   tmp = rune_c( kv.value );
   expect_true_c_( rune_is_c( tmp, "a" ) );
   expect_false_c_( has_next_c_( traverser ) );   

   return test_result_c();
}
