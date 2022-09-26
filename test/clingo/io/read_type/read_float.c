#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"

TEMP_SLICE_C_(
   test,
   {
      char const* str;
      char const* fmt;
      float exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   set_locale_c( LC_ALL, "C" );

   testSlice tests = slice_c_( test,
      t_( "9038.213", "", 9038.213f )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->str );
      float f = 0.0f;
      bool res = true;
      res &= read_float_c( sca, &f, t->fmt );
      res &= eq_float_c_( f, t->exp );

      tap_descf_c( res, "%s + \"%s\" -> %f", t->str, t->fmt, f );
   }

   return finish_tap_c_();
}
