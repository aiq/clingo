#include "clingo/io/write_type.h"
#include "clingo/lang/error_type.h"
#include "clingo/lang/expect.h"

#define expect_( Es, Exp )                                                     \
{                                                                              \
   cRecorder* rec = &recorder_c_( 256 );                                       \
   write_error_c_( rec, (Es)->err );                                           \
   expect_block_at_c_( recorded_is_c(rec, (Exp) ) )                            \
   {                                                                           \
      tap_exp_line_c_( "{s}", (Exp) );                                         \
      tap_got_line_c_( "{rec}", rec );                                         \
   }                                                                           \
   reset_error_stack_c( Es );                                                  \
}

int main( void )
{
   init_tap_c_();

   cErrorStack* es = &error_stack_c_( 256 );

   // ---------------------------------------------------------------------- add
   push_iadd8_error_c( es, 126, 64 );
   expect_( es, "126 + 64 overflows int8_t range" );
   push_iadd16_error_c( es, INT16_MAX, 255 );
   expect_( es, "32767 + 255 overflows int16_t range" );
   push_iadd32_error_c( es, INT32_MAX, 18 );
   expect_( es, "2147483647 + 18 overflows int32_t range" );
   push_iadd64_error_c( es, -INT64_MAX, -INT32_MAX );
   expect_( es, "-9223372036854775807 + -2147483647 overflows int64_t range" );

   push_uadd8_error_c( es, 248, 128 );
   expect_( es, "248 + 128 overflows uint8_t range" );
   push_uadd16_error_c( es, UINT16_MAX, 128 );
   expect_( es, "65535 + 128 overflows uint16_t range" );
   push_uadd32_error_c( es, UINT32_MAX, 128 );
   expect_( es, "4294967295 + 128 overflows uint32_t range" );
   push_uadd64_error_c( es, UINT64_MAX, 128 );
   expect_( es, "18446744073709551615 + 128 overflows uint64_t range" );

   // ---------------------------------------------------------------------- mul
   push_imul8_error_c( es, 80, 6 );
   expect_( es, "80 * 6 overflows int8_t range" );
   push_imul16_error_c( es, 1024, -50 );
   expect_( es, "1024 * -50 overflows int16_t range" );
   push_imul32_error_c( es, 32767, 327671 );
   expect_( es, "32767 * 327671 overflows int32_t range" );
   push_imul64_error_c( es, INT64_MAX, INT32_MAX );
   expect_( es, "9223372036854775807 * 2147483647 overflows int64_t range" );

   push_umul8_error_c( es, 128, 128 );
   expect_( es, "128 * 128 overflows uint8_t range" );
   push_umul16_error_c( es, 1024, 1024 );
   expect_( es, "1024 * 1024 overflows uint16_t range" );
   push_umul32_error_c( es, 4294843840, 100 );
   expect_( es, "4294843840 * 100 overflows uint32_t range" );
   push_umul64_error_c( es, 21474836479, 21474836479 );
   expect_( es, "21474836479 * 21474836479 overflows uint64_t range" );

   // ---------------------------------------------------------------------- sub
   push_isub8_error_c( es, -126, 64 );
   expect_( es, "-126 - 64 overflows int8_t range" );
   push_isub16_error_c( es, INT16_MIN, 255 );
   expect_( es, "-32768 - 255 overflows int16_t range" );
   push_isub32_error_c( es, INT32_MAX, -18 );
   expect_( es, "2147483647 - -18 overflows int32_t range" );
   push_isub64_error_c( es, INT64_MIN, INT32_MAX );
   expect_( es, "-9223372036854775808 - 2147483647 overflows int64_t range" );

   push_usub8_error_c( es, 128, 248 );
   expect_( es, "128 - 248 overflows uint8_t range" );
   push_usub16_error_c( es, 0, 128 );
   expect_( es, "0 - 128 overflows uint16_t range" );
   push_usub32_error_c( es, UINT16_MAX, UINT32_MAX );
   expect_( es, "65535 - 4294967295 overflows uint32_t range" );
   push_usub64_error_c( es, UINT32_MAX, UINT64_MAX );
   expect_( es, "4294967295 - 18446744073709551615 overflows uint64_t range" );

   return finish_tap_c_();
}
