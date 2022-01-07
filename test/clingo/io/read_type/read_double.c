#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* str;
      char const* fmt;
      double exp;
      double diff;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   set_locale_c( LC_ALL, "C" );

   testSlice tests = slice_c_( test,
      t_( "129038.213", "", 129038.213, 0.00001 )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->str );
      double d = 0.0;
      bool res = true;
      res &= read_double_c( sca, &d, t->fmt );
      res &= eq_double_c( d, t->exp, t->diff );

      tap_descf_c( res, "%s + \"%s\" -> %f", t->str, t->fmt, d );
   }

   return finish_tap_c_();
}
