#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* str;
      char const* fmt;
      char const* expChars;
      char const* expUnscanned;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      // any
      t_( "'key': 'value'", "{>:}", "'key'", ": 'value'" ),
      // func
      t_( "123456", "{/?d}", "1", "23456" ),
      t_( "123456", "{/*d}", "123456", "" ),
      // range
      t_( "I am müller", "{[*0000-007F}", "I am m", "üller" ),
      t_( "I am müller", "{[+0-7f}", "I am m", "üller" ),
      t_( "I am müller", "{[+ z}", "I am m", "üller" )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->str );
      cChars chars = empty_chars_c();
      bool res = read_chars_c( sca, &chars, t->fmt );
      res &= chars_is_c( chars, t->expChars );
      res &= unscanned_is_c( sca, t->expUnscanned );

      tap_descf_c( res, "%s on %s", t->fmt, t->str );
   }

   return finish_tap_c_();
}