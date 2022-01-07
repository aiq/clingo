#include "clingo/io/read.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   {
      cScanner* sca = &cstr_scanner_c_( "a lower  123:456 true a1   " );
      int16_t i16 = 0;
      bool b = false;
      int32_t hex = 0;
      expect_c_( read_c_( sca, "a {/+l}{/>d}{i16}:{!i64} {bool} {i32:x}{/*s}",
                                &i16, &b, &hex ) );
      expect_c_( i16 == 123 );
      expect_c_( b );
      expect_c_( hex == 0xa1 );
      expect_c_( sca->space == 0 );
   }

   {
      cScanner* sca = &cstr_scanner_c_( "a lower  123:456 true a1" );
      int16_t i16 = 0;
      bool b = false;
      int32_t hex = 0;
      expect_c_( read_c_( sca, "a {/+l}{/>d}{i16}:{!i64} {bool} {i32:x}",
                               &i16, &b, &hex ) );
      expect_c_( i16 == 123 );
      expect_c_( b );
      expect_c_( hex == 0xa1 );
      expect_c_( sca->space == 0 );
   }

   {
      cScanner* sca = &cstr_scanner_c_( "a lower  123:456 true a1   " );
      int16_t i16 = 0;
      bool b = false;
      expect_c_( read_c_( sca, "a {/+l}{/>d}{i16}", &i16,
                               ":{!i64} {bool} {!i32:x}{/*s}", &b ) );
      expect_c_( i16 == 123 );
      expect_c_( b );
      expect_c_( sca->space == 0 );
   }

   {
      cScanner* sca = &cstr_scanner_c_( "a lower  123:456 true a1   " );
      expect_c_( read_c_( sca, "a ", "{/+l}{/>d}{>:}:{/>s}",
                               " {/+l} {/+x}{/*s}" ) );
      expect_c_( sca->space == 0 );
   }

   {
      cScanner* sca = &cstr_scanner_c_( "a lower  123:456 true a1   " );
      expect_c_( read_c_( sca, "a {/+l}{/>d}{>:}:{/>s} {/+l} {/+x}{/*s}" ) );
      expect_c_( sca->space == 0 );
   }

   return finish_tap_c_();
}
