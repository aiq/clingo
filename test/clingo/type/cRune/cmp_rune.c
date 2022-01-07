#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   // ascii
   cRune x = rune_c( "x" );
   cRune y = rune_c( "y" );
   cRune z = rune_c( "z" );

   expect_eq_c_( cmp_rune_c( x, x ) );
   expect_eq_c_( cmp_rune_c( y, y ) );
   expect_eq_c_( cmp_rune_c( z, z ) );

   expect_lt_c_( cmp_rune_c( x, y ) );
   expect_lt_c_( cmp_rune_c( x, z ) );
   expect_lt_c_( cmp_rune_c( y, z ) );

   expect_gt_c_( cmp_rune_c( y, x ) );
   expect_gt_c_( cmp_rune_c( z, x ) );
   expect_gt_c_( cmp_rune_c( z, y ) );

   // unicode
   cRune umbrella  = rune_c( "☂" ); // U+2602
   expect_eq_c_( cmp_rune_c( umbrella, utf16_rune_c( 0x2602 ) ) );

   cRune snowman = rune_c( "☃" ); // U+2603
   expect_eq_c_( cmp_rune_c( snowman, utf16_rune_c( 0x2603 ) ) );

   expect_lt_c_( cmp_rune_c( umbrella, snowman ) );
   expect_gt_c_( cmp_rune_c( snowman, umbrella ) );


   return finish_tap_c_();
}
