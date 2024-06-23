#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"

#include "clingo/io/print.h"
#define pln_( ... ) pjotln_c_( xyz, 1024, __VA_ARGS__ )

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      char const* fmt;
      char const* exp;
      char const* unscanned;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // "" / "s"
      t_( "abc", "", "a", "bc" ),
      t_( "🪓♘", "", "🪓", "♘" ),
   // "n"
      t_( "U+005A,", "n", "Z", ","  ),
      t_( "U+2658,", "n", "♘", "," ),
      t_( "U+1FA93,", "n", "🪓", "," ),
   // "u8"
      t_( "5aaf", "u8", "Z", "af" ),
      t_( "e2999800", "u8", "♘", "00" ),
      t_( "f09faa9312", "u8", "🪓", "12" ),
   // "html"
      t_( "&#90;foo", "html", "Z", "foo" ),
      t_( "&#9816;bar", "html", "♘", "bar" ),
      t_( "&#129683;tar", "html", "🪓" , "tar" ),
   // "htmlx"
      t_( "&#x5A;bla", "htmlx", "Z", "bla" ),
      t_( "&#x2658;blo", "htmlx", "♘", "blo" ),
      t_( "&#x1FA93;blub", "htmlx", "🪓", "blub" )
   );

   each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->inp );

      cRune r = null_rune_c();
      bool res = read_rune_c( sca, &r, t->fmt );
      res &= rune_is_c( r, t->exp );
      res &= unscanned_is_c( sca,  t->unscanned );

      tap_c_( res, C_TapDesc, "test {s:q}", t->inp,
                              " + {s:q}", t->fmt,
                              " -> {s:q}", t->exp );
   }

   return finish_tap_c_();
}