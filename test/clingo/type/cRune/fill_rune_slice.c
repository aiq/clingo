#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   cChars src = c_c( "My € makes 𝄞®!" );

   {
      cVarRuneSlice dst = structs_c_( 20, cRune );
      cVarRuneSlice res = fill_rune_slice_c( dst, src );

      expect_c_( res.s == 14 );
      expect_c_( rune_is_c( res.v[  0 ], "M" ) );
      expect_c_( rune_is_c( res.v[  1 ], "y" ) );
      expect_c_( rune_is_c( res.v[  2 ], " " ) );
      expect_c_( rune_is_c( res.v[  3 ], "€" ) );
      expect_c_( rune_is_c( res.v[  4 ], " " ) );
      expect_c_( rune_is_c( res.v[  5 ], "m" ) );
      expect_c_( rune_is_c( res.v[  6 ], "a" ) );
      expect_c_( rune_is_c( res.v[  7 ], "k" ) );
      expect_c_( rune_is_c( res.v[  8 ], "e" ) );
      expect_c_( rune_is_c( res.v[  9 ], "s" ) );
      expect_c_( rune_is_c( res.v[ 10 ], " " ) );
      expect_c_( rune_is_c( res.v[ 11 ], "𝄞" ) );
      expect_c_( rune_is_c( res.v[ 12 ], "®" ) );
      expect_c_( rune_is_c( res.v[ 13 ], "!" ) );
   }

   {
      cVarRuneSlice dst = structs_c_( 10, cRune );
      cVarRuneSlice res = fill_rune_slice_c( dst, src );

      expect_c_( res.s == 10 );
      expect_c_( rune_is_c( res.v[  0 ], "M" ) );
      expect_c_( rune_is_c( res.v[  1 ], "y" ) );
      expect_c_( rune_is_c( res.v[  2 ], " " ) );
      expect_c_( rune_is_c( res.v[  3 ], "€" ) );
      expect_c_( rune_is_c( res.v[  4 ], " " ) );
      expect_c_( rune_is_c( res.v[  5 ], "m" ) );
      expect_c_( rune_is_c( res.v[  6 ], "a" ) );
      expect_c_( rune_is_c( res.v[  7 ], "k" ) );
      expect_c_( rune_is_c( res.v[  8 ], "e" ) );
      expect_c_( rune_is_c( res.v[  9 ], "s" ) );
   }

   return finish_tap_c_();
}
