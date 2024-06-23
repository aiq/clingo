#include "clingo/io/cScanner.h"
#include "clingo/lang/expect.h"

#define expect_mem_( Slice, ... )                                              \
   expect_eq_c_(                                                               \
      cmp_bytes_c(                                                             \
         (Slice),                                                              \
         (cBytes){ (Slice).s, (cByte[]){ __VA_ARGS__ } }                       \
      )                                                                        \
   )

int main()
{
   init_tap_c_();

   cChars data = slice_c_( char,
      'a', 'b', 'c', '\0', '\0', 'd', 'e', 'f', '\0'
   );
   cScanner* sca = &make_scanner_c_( data.s, data.v );

   // ----------------------------------------------------------------- view abc
   char const* cstr = view_cstr_c( sca );
   expect_at_c_( cstr[ 0 ] == 'a' );
   expect_at_c_( sca->pos == 4 );
   expect_at_c_( sca->space == 5 );

   cBytes scanned = scanned_bytes_c_( sca );
   expect_mem_( scanned, 'a', 'b', 'c', '\0' );

   // -------------------------------------------------------- view empty string
   cstr = view_cstr_c( sca );
   expect_at_c_( cstr[ 0 ] == '\0' );
   expect_at_c_( sca->pos == 5 );
   expect_at_c_( sca->space == 4 );

   scanned = scanned_bytes_c_( sca );
   expect_mem_( scanned, 'a', 'b', 'c', '\0', '\0' );

   // ----------------------------------------------------------------- view def
   cstr = view_cstr_c( sca );
   expect_at_c_( cstr[ 0 ] == 'd' );
   expect_at_c_( sca->pos == 9 );
   expect_at_c_( sca->space == 0 );

   scanned = scanned_bytes_c_( sca );
   expect_mem_( scanned, 'a', 'b', 'c', '\0', '\0', 'd', 'e', 'f', '\0' );

   // ------------------------------------------------------ try to view outside
   cstr = view_cstr_c( sca );
   expect_at_c_( cstr == NULL );

   return finish_tap_c_();
}
