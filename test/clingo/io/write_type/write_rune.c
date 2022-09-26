#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* r;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // "" / "s"
      t_( "a", "", "a" ),
      t_( "🪓", "s", "🪓" ),
   // "q" /"Q"
      t_( "Z", "q", "'Z'" ),
      t_( "♘", "Q", "\"♘\"" ),
   // "n"
      t_( "Z", "n", "U+005A" ),
      t_( "♘", "n", "U+2658" ),
      t_( "🪓", "n", "U+1FA93" ),
   // "u8"
      t_( "Z", "u8", "5a" ),
      t_( "♘", "u8", "e29998" ),
      t_( "🪓", "u8", "f09faa93" ),
   // "html"
      t_( "Z", "html", "&#90;" ),
      t_( "♘", "html", "&#9816;" ),
      t_( "🪓", "html", "&#129683;" ),
   // "htmlx"
      t_( "Z", "htmlx", "&#x5A;" ),
      t_( "♘", "htmlx", "&#x2658;" ),
      t_( "🪓", "htmlx", "&#x1FA93;" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 16 );

      bool res = write_rune_c( rec, rune_c( t->r ), t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_descf_c( res, "test '%s' / '%s' / '%s'", t->r, t->fmt, t->exp );
   }

   return finish_tap_c_();
}
