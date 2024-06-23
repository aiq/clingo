#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

#define expect_rune_( Res, Exp )                                               \
   expect_at_c_( eq_rune_c( rune_c( Res ), rune_c( Exp ) ) );


int main( void )
{
   init_tap_c_();

   cChars base = c_c( "with 𐤠 and 𐤹, from the Lydian set" );
   cChars chars = base;
   cChars set = c_c( "𐤹,𐤠L" );

   char const* ptr = NULL;
   int64_t idx = -1;

   ptr = find_any_rune_c( chars, set ); // --------------------------------- '𐤠'
   idx = index_of_c_( base, ptr );
   expect_rune_( ptr, "𐤠" );
   expect_at_c_( idx == 5 );
   chars = mid_runes_c( base, 6 );

   ptr = find_any_rune_c( chars, set ); // --------------------------------- '𐤹'
   idx = index_of_c_( base, ptr );
   expect_rune_( ptr, "𐤹" );
   expect_at_c_( idx == 14 );
   chars = mid_runes_c( base, 12 );

   ptr = find_any_rune_c( chars, set ); // --------------------------------- ','
   idx = index_of_c_( base, ptr );
   expect_rune_( ptr, "," );
   expect_at_c_( idx == 18 );
   chars = mid_runes_c( base, 13 );

   ptr = find_any_rune_c( chars, set ); // --------------------------------- 'L'
   idx = index_of_c_( base, ptr );
   expect_rune_( ptr, "L" );
   expect_at_c_( idx == 29 );
   chars = mid_runes_c( base, 24 );

   return finish_tap_c_();
}