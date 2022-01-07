#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      double val;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   set_locale_c( LC_ALL, "C" );

   testSlice tests = slice_c_( test,
      t_( 2.71828, "", "2.71828" ),
      t_( 2.71828, "+E", "+2.718280E+00" ),
      t_( 2.71828, "x.1", "0x1.6p+1" ),
      t_( 2.71828, ".3q(10l.)", "'2.718'..." ),
      t_( 2.71828, "dbg", "{ .sign=0, .exponent=400, .mantissa=5bf0995aaf790 }" ),
   // one
      t_( 1, "e.5", "1.00000e+00" ),
      t_( 1, "f.5", "1.00000" ),
      t_( 1, "g.5", "1" ),
      t_( 1, "x.5", "0x1.00000p+0" ),
   // g conversion and zero suppression
      t_( 400, "g.2", "4e+02" ),
      t_( 40, "g.2", "40" ),
      t_( 4, "g.2", "4" ),
      t_( .4, "g.2", "0.4" ),
      t_( .04, "g.2", "0.04" ),
      t_( .004, "g.2", "0.004" ),
      t_( .0004, "g.2", "0.0004" ),
      t_( .00004, "g.2", "4e-05" ),
      t_( .000004, "g.2", "4e-06" ),
   // zero
      t_( 0, "e.5", "0.00000e+00" ),
      t_( 0, "f.5", "0.00000" ),
      t_( 0, "g", "0" ),
      t_( 0, "g", "0" ),
      t_( 0, "x.5", "0x0.00000p+0" ),
   // -1
      t_( -1, "e.5", "-1.00000e+00" ),
      t_( -1, "f.5", "-1.00000" ),
      t_( -1, "g.5", "-1" ),
   // 12
      t_( 12, "e.5", "1.20000e+01" ),
      t_( 12, "f.5", "12.00000" ),
      t_( 12, "g.5", "12" ),
   // 123456700
      t_( 123456700, "e.5", "1.23457e+08" ),
      t_( 123456700, "f.5", "123456700.00000" ),
      t_( 123456700, "g.5", "1.2346e+08" ),
   // 1.2345e6
      t_( 1.2345e6, "e.5", "1.23450e+06" ),
      t_( 1.2345e6, "f.5", "1234500.00000" ),
      t_( 1.2345e6, "g.5", "1.2345e+06" ),
   // 1e23
      t_( 1e23, "e.17", "9.99999999999999916e+22" ),
      t_( 1e23, "f.17", "99999999999999991611392.00000000000000000" ),
      t_( 1e23, "g.17", "9.9999999999999992e+22" ),
   // NaN & Inf
      t_( NAN, "", "nan" ),
      t_( -NAN, "", "nan" ),
      t_( INFINITY, "+", "+inf" ),
      t_( INFINITY, "", "inf" ),
      t_( -INFINITY, "", "-inf" ),
   // fixed bugs
      t_( 0.9, "f.1", "0.9" ),
      t_( 0.09, "f.1", "0.1" ),
      t_( 0.0999, "f.1", "0.1" ),
      t_( 0.05, "f.1", "0.1" ),
      t_( 0.05, "f.0", "0" ),
      t_( 0.5, "f.1", "0.5" ),
      t_( 0.5, "f.0", "0" ),
      t_( 1.5, "f.0", "2" ),
   // https://www.exploringbinary.com/java-hangs-when-converting-2-2250738585072012e-308/
      t_( 2.2250738585072012e-308, "g.17", "2.2250738585072014e-308" ),
   // https://www.exploringbinary.com/php-hangs-on-numeric-value-2-2250738585072011e-308/
      t_( 2.2250738585072011e-308, "g.16", "2.225073858507201e-308" ),
   // mix
      t_( 383260575764816448, "f.0", "383260575764816448" ),
      t_( 383260575764816448, "e.16", "3.8326057576481645e+17" ),
      t_( 498484681984085570, "f.0", "498484681984085568" ),
      t_( -5.8339553793802237e+23, "e.16", "-5.8339553793802237e+23" ),
   // rounding
      t_( 2.275555555555555, "x", "0x1.23456789abcdep+1" ),
      t_( 2.275555555555555, "x.0", "0x1p+1" ),
      t_( 2.275555555555555, "x.2", "0x1.23p+1" ),
      t_( 2.275555555555555, "x.16", "0x1.23456789abcde000p+1" ),
      t_( 2.275555555555555, "x.21", "0x1.23456789abcde00000000p+1" ),
      t_( 2.2755555510520935, "x", "0x1.2345678p+1" ),
      t_( 2.2755555510520935, "x.6", "0x1.234567p+1" ),
      t_( 2.275555431842804, "x", "0x1.2345668p+1" ),
      t_( 2.275555431842804, "x.6", "0x1.234566p+1" ),
      t_( 3.999969482421875, "x", "0x1.ffffp+1" ),
      t_( 3.999969482421875, "x.4", "0x1.ffffp+1" ),
      t_( 3.999969482421875, "x.3", "0x2.000p+1" ),
      t_( 3.999969482421875, "x.2", "0x2.00p+1" ),
      t_( 3.999969482421875, "x.1", "0x2.0p+1" ),
      t_( 3.999969482421875, "x.1", "0x2.0p+1" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_double_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_descf_c( res, "fmt: %s / exp: %s / got: %s", t.fmt, t.exp, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
