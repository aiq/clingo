#ifndef CLINGO_IO_JOT_H
#define CLINGO_IO_JOT_H

#include "clingo/io/write_type.h"
#include "clingo/lang/error.h"
#include "clingo/lang/func.h"

// --------------------------------------------------------------------- mapping

#define cJotDefaultMapping_                                                    \
   cByte: write_byte_c,                                                        \
   char: write_char_c,                                                         \
                                                                               \
   bool: write_bool_c,                                                         \
   cRange: write_range_c,                                                      \
   cRune: write_rune_c,                                                        \
                                                                               \
   double: write_double_c,                                                     \
   float: write_float_c,                                                       \
                                                                               \
   int8_t: write_int8_c,                                                       \
   int16_t: write_int16_c,                                                     \
   int32_t: write_int32_c,                                                     \
   int64_t: write_int64_c,                                                     \
                                                                               \
   uint16_t: write_uint16_c,                                                   \
   uint32_t: write_uint32_c,                                                   \
   uint64_t: write_uint64_c,                                                   \
                                                                               \
   cBytes: write_bytes_c,                                                      \
   cChars: write_chars_c,                                                      \
   char*: write_cstr_c,                                                        \
   char const*: write_cstr_c,                                                  \
                                                                               \
   cError const*: write_error_c,                                               \
   cTape: write_tape_c,                                                        \
                                                                               \
   cRecorder*: write_recorded_c,                                               \
   cRecorder const*: write_recorded_c,                                         \
   cScanner*: write_unscanned_c,                                               \
   cScanner const*: write_unscanned_c

#define jot_type_c_( Rec, Val )                                                \
   _Generic( (Val),                                                            \
      cJotDefaultMapping_                                                      \
   )( Rec, Val, "" )

// ----------------------------------------------------------------------- jot

#define jot_call_c_( Func, Rec, ... )                                          \
(                                                                              \
   xconcat3_c_( jot, nargs_c_( __VA_ARGS__ ), _c_ )( Func, Rec, __VA_ARGS__ )  \
)

#define jot_c_( Rec, ... )                                                     \
   jot_call_c_( jot_type_c_, Rec, __VA_ARGS__ )

#define jotln_c_( Rec, ... )                                                   \
   jot_c_( Rec, __VA_ARGS__ ) and record_char_c( Rec, '\n' )

// --------------------------------------------------------- generated functions

/*

#!/usr/bin/env lua
print( "#define jot1_c_( Func, Rec, Val ) Func( (Rec), (Val) )" )
for n = 2, 255 do
   local p = n-1
   print( "#define jot"..n.."_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot"..p.."_c_( Func, Rec, __VA_ARGS__ )" )
end

*/

#define jot1_c_( Func, Rec, Val ) Func( (Rec), (Val) )
#define jot2_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot1_c_( Func, Rec, __VA_ARGS__ )
#define jot3_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot2_c_( Func, Rec, __VA_ARGS__ )
#define jot4_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot3_c_( Func, Rec, __VA_ARGS__ )
#define jot5_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot4_c_( Func, Rec, __VA_ARGS__ )
#define jot6_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot5_c_( Func, Rec, __VA_ARGS__ )
#define jot7_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot6_c_( Func, Rec, __VA_ARGS__ )
#define jot8_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot7_c_( Func, Rec, __VA_ARGS__ )
#define jot9_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot8_c_( Func, Rec, __VA_ARGS__ )
#define jot10_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot9_c_( Func, Rec, __VA_ARGS__ )
#define jot11_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot10_c_( Func, Rec, __VA_ARGS__ )
#define jot12_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot11_c_( Func, Rec, __VA_ARGS__ )
#define jot13_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot12_c_( Func, Rec, __VA_ARGS__ )
#define jot14_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot13_c_( Func, Rec, __VA_ARGS__ )
#define jot15_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot14_c_( Func, Rec, __VA_ARGS__ )
#define jot16_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot15_c_( Func, Rec, __VA_ARGS__ )
#define jot17_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot16_c_( Func, Rec, __VA_ARGS__ )
#define jot18_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot17_c_( Func, Rec, __VA_ARGS__ )
#define jot19_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot18_c_( Func, Rec, __VA_ARGS__ )
#define jot20_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot19_c_( Func, Rec, __VA_ARGS__ )
#define jot21_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot20_c_( Func, Rec, __VA_ARGS__ )
#define jot22_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot21_c_( Func, Rec, __VA_ARGS__ )
#define jot23_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot22_c_( Func, Rec, __VA_ARGS__ )
#define jot24_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot23_c_( Func, Rec, __VA_ARGS__ )
#define jot25_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot24_c_( Func, Rec, __VA_ARGS__ )
#define jot26_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot25_c_( Func, Rec, __VA_ARGS__ )
#define jot27_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot26_c_( Func, Rec, __VA_ARGS__ )
#define jot28_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot27_c_( Func, Rec, __VA_ARGS__ )
#define jot29_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot28_c_( Func, Rec, __VA_ARGS__ )
#define jot30_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot29_c_( Func, Rec, __VA_ARGS__ )
#define jot31_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot30_c_( Func, Rec, __VA_ARGS__ )
#define jot32_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot31_c_( Func, Rec, __VA_ARGS__ )
#define jot33_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot32_c_( Func, Rec, __VA_ARGS__ )
#define jot34_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot33_c_( Func, Rec, __VA_ARGS__ )
#define jot35_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot34_c_( Func, Rec, __VA_ARGS__ )
#define jot36_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot35_c_( Func, Rec, __VA_ARGS__ )
#define jot37_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot36_c_( Func, Rec, __VA_ARGS__ )
#define jot38_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot37_c_( Func, Rec, __VA_ARGS__ )
#define jot39_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot38_c_( Func, Rec, __VA_ARGS__ )
#define jot40_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot39_c_( Func, Rec, __VA_ARGS__ )
#define jot41_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot40_c_( Func, Rec, __VA_ARGS__ )
#define jot42_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot41_c_( Func, Rec, __VA_ARGS__ )
#define jot43_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot42_c_( Func, Rec, __VA_ARGS__ )
#define jot44_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot43_c_( Func, Rec, __VA_ARGS__ )
#define jot45_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot44_c_( Func, Rec, __VA_ARGS__ )
#define jot46_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot45_c_( Func, Rec, __VA_ARGS__ )
#define jot47_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot46_c_( Func, Rec, __VA_ARGS__ )
#define jot48_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot47_c_( Func, Rec, __VA_ARGS__ )
#define jot49_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot48_c_( Func, Rec, __VA_ARGS__ )
#define jot50_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot49_c_( Func, Rec, __VA_ARGS__ )
#define jot51_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot50_c_( Func, Rec, __VA_ARGS__ )
#define jot52_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot51_c_( Func, Rec, __VA_ARGS__ )
#define jot53_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot52_c_( Func, Rec, __VA_ARGS__ )
#define jot54_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot53_c_( Func, Rec, __VA_ARGS__ )
#define jot55_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot54_c_( Func, Rec, __VA_ARGS__ )
#define jot56_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot55_c_( Func, Rec, __VA_ARGS__ )
#define jot57_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot56_c_( Func, Rec, __VA_ARGS__ )
#define jot58_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot57_c_( Func, Rec, __VA_ARGS__ )
#define jot59_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot58_c_( Func, Rec, __VA_ARGS__ )
#define jot60_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot59_c_( Func, Rec, __VA_ARGS__ )
#define jot61_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot60_c_( Func, Rec, __VA_ARGS__ )
#define jot62_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot61_c_( Func, Rec, __VA_ARGS__ )
#define jot63_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot62_c_( Func, Rec, __VA_ARGS__ )
#define jot64_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot63_c_( Func, Rec, __VA_ARGS__ )
#define jot65_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot64_c_( Func, Rec, __VA_ARGS__ )
#define jot66_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot65_c_( Func, Rec, __VA_ARGS__ )
#define jot67_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot66_c_( Func, Rec, __VA_ARGS__ )
#define jot68_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot67_c_( Func, Rec, __VA_ARGS__ )
#define jot69_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot68_c_( Func, Rec, __VA_ARGS__ )
#define jot70_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot69_c_( Func, Rec, __VA_ARGS__ )
#define jot71_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot70_c_( Func, Rec, __VA_ARGS__ )
#define jot72_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot71_c_( Func, Rec, __VA_ARGS__ )
#define jot73_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot72_c_( Func, Rec, __VA_ARGS__ )
#define jot74_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot73_c_( Func, Rec, __VA_ARGS__ )
#define jot75_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot74_c_( Func, Rec, __VA_ARGS__ )
#define jot76_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot75_c_( Func, Rec, __VA_ARGS__ )
#define jot77_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot76_c_( Func, Rec, __VA_ARGS__ )
#define jot78_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot77_c_( Func, Rec, __VA_ARGS__ )
#define jot79_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot78_c_( Func, Rec, __VA_ARGS__ )
#define jot80_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot79_c_( Func, Rec, __VA_ARGS__ )
#define jot81_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot80_c_( Func, Rec, __VA_ARGS__ )
#define jot82_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot81_c_( Func, Rec, __VA_ARGS__ )
#define jot83_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot82_c_( Func, Rec, __VA_ARGS__ )
#define jot84_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot83_c_( Func, Rec, __VA_ARGS__ )
#define jot85_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot84_c_( Func, Rec, __VA_ARGS__ )
#define jot86_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot85_c_( Func, Rec, __VA_ARGS__ )
#define jot87_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot86_c_( Func, Rec, __VA_ARGS__ )
#define jot88_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot87_c_( Func, Rec, __VA_ARGS__ )
#define jot89_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot88_c_( Func, Rec, __VA_ARGS__ )
#define jot90_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot89_c_( Func, Rec, __VA_ARGS__ )
#define jot91_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot90_c_( Func, Rec, __VA_ARGS__ )
#define jot92_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot91_c_( Func, Rec, __VA_ARGS__ )
#define jot93_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot92_c_( Func, Rec, __VA_ARGS__ )
#define jot94_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot93_c_( Func, Rec, __VA_ARGS__ )
#define jot95_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot94_c_( Func, Rec, __VA_ARGS__ )
#define jot96_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot95_c_( Func, Rec, __VA_ARGS__ )
#define jot97_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot96_c_( Func, Rec, __VA_ARGS__ )
#define jot98_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot97_c_( Func, Rec, __VA_ARGS__ )
#define jot99_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot98_c_( Func, Rec, __VA_ARGS__ )
#define jot100_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot99_c_( Func, Rec, __VA_ARGS__ )
#define jot101_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot100_c_( Func, Rec, __VA_ARGS__ )
#define jot102_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot101_c_( Func, Rec, __VA_ARGS__ )
#define jot103_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot102_c_( Func, Rec, __VA_ARGS__ )
#define jot104_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot103_c_( Func, Rec, __VA_ARGS__ )
#define jot105_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot104_c_( Func, Rec, __VA_ARGS__ )
#define jot106_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot105_c_( Func, Rec, __VA_ARGS__ )
#define jot107_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot106_c_( Func, Rec, __VA_ARGS__ )
#define jot108_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot107_c_( Func, Rec, __VA_ARGS__ )
#define jot109_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot108_c_( Func, Rec, __VA_ARGS__ )
#define jot110_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot109_c_( Func, Rec, __VA_ARGS__ )
#define jot111_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot110_c_( Func, Rec, __VA_ARGS__ )
#define jot112_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot111_c_( Func, Rec, __VA_ARGS__ )
#define jot113_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot112_c_( Func, Rec, __VA_ARGS__ )
#define jot114_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot113_c_( Func, Rec, __VA_ARGS__ )
#define jot115_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot114_c_( Func, Rec, __VA_ARGS__ )
#define jot116_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot115_c_( Func, Rec, __VA_ARGS__ )
#define jot117_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot116_c_( Func, Rec, __VA_ARGS__ )
#define jot118_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot117_c_( Func, Rec, __VA_ARGS__ )
#define jot119_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot118_c_( Func, Rec, __VA_ARGS__ )
#define jot120_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot119_c_( Func, Rec, __VA_ARGS__ )
#define jot121_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot120_c_( Func, Rec, __VA_ARGS__ )
#define jot122_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot121_c_( Func, Rec, __VA_ARGS__ )
#define jot123_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot122_c_( Func, Rec, __VA_ARGS__ )
#define jot124_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot123_c_( Func, Rec, __VA_ARGS__ )
#define jot125_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot124_c_( Func, Rec, __VA_ARGS__ )
#define jot126_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot125_c_( Func, Rec, __VA_ARGS__ )
#define jot127_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot126_c_( Func, Rec, __VA_ARGS__ )
#define jot128_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot127_c_( Func, Rec, __VA_ARGS__ )
#define jot129_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot128_c_( Func, Rec, __VA_ARGS__ )
#define jot130_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot129_c_( Func, Rec, __VA_ARGS__ )
#define jot131_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot130_c_( Func, Rec, __VA_ARGS__ )
#define jot132_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot131_c_( Func, Rec, __VA_ARGS__ )
#define jot133_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot132_c_( Func, Rec, __VA_ARGS__ )
#define jot134_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot133_c_( Func, Rec, __VA_ARGS__ )
#define jot135_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot134_c_( Func, Rec, __VA_ARGS__ )
#define jot136_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot135_c_( Func, Rec, __VA_ARGS__ )
#define jot137_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot136_c_( Func, Rec, __VA_ARGS__ )
#define jot138_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot137_c_( Func, Rec, __VA_ARGS__ )
#define jot139_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot138_c_( Func, Rec, __VA_ARGS__ )
#define jot140_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot139_c_( Func, Rec, __VA_ARGS__ )
#define jot141_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot140_c_( Func, Rec, __VA_ARGS__ )
#define jot142_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot141_c_( Func, Rec, __VA_ARGS__ )
#define jot143_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot142_c_( Func, Rec, __VA_ARGS__ )
#define jot144_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot143_c_( Func, Rec, __VA_ARGS__ )
#define jot145_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot144_c_( Func, Rec, __VA_ARGS__ )
#define jot146_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot145_c_( Func, Rec, __VA_ARGS__ )
#define jot147_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot146_c_( Func, Rec, __VA_ARGS__ )
#define jot148_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot147_c_( Func, Rec, __VA_ARGS__ )
#define jot149_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot148_c_( Func, Rec, __VA_ARGS__ )
#define jot150_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot149_c_( Func, Rec, __VA_ARGS__ )
#define jot151_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot150_c_( Func, Rec, __VA_ARGS__ )
#define jot152_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot151_c_( Func, Rec, __VA_ARGS__ )
#define jot153_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot152_c_( Func, Rec, __VA_ARGS__ )
#define jot154_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot153_c_( Func, Rec, __VA_ARGS__ )
#define jot155_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot154_c_( Func, Rec, __VA_ARGS__ )
#define jot156_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot155_c_( Func, Rec, __VA_ARGS__ )
#define jot157_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot156_c_( Func, Rec, __VA_ARGS__ )
#define jot158_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot157_c_( Func, Rec, __VA_ARGS__ )
#define jot159_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot158_c_( Func, Rec, __VA_ARGS__ )
#define jot160_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot159_c_( Func, Rec, __VA_ARGS__ )
#define jot161_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot160_c_( Func, Rec, __VA_ARGS__ )
#define jot162_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot161_c_( Func, Rec, __VA_ARGS__ )
#define jot163_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot162_c_( Func, Rec, __VA_ARGS__ )
#define jot164_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot163_c_( Func, Rec, __VA_ARGS__ )
#define jot165_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot164_c_( Func, Rec, __VA_ARGS__ )
#define jot166_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot165_c_( Func, Rec, __VA_ARGS__ )
#define jot167_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot166_c_( Func, Rec, __VA_ARGS__ )
#define jot168_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot167_c_( Func, Rec, __VA_ARGS__ )
#define jot169_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot168_c_( Func, Rec, __VA_ARGS__ )
#define jot170_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot169_c_( Func, Rec, __VA_ARGS__ )
#define jot171_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot170_c_( Func, Rec, __VA_ARGS__ )
#define jot172_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot171_c_( Func, Rec, __VA_ARGS__ )
#define jot173_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot172_c_( Func, Rec, __VA_ARGS__ )
#define jot174_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot173_c_( Func, Rec, __VA_ARGS__ )
#define jot175_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot174_c_( Func, Rec, __VA_ARGS__ )
#define jot176_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot175_c_( Func, Rec, __VA_ARGS__ )
#define jot177_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot176_c_( Func, Rec, __VA_ARGS__ )
#define jot178_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot177_c_( Func, Rec, __VA_ARGS__ )
#define jot179_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot178_c_( Func, Rec, __VA_ARGS__ )
#define jot180_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot179_c_( Func, Rec, __VA_ARGS__ )
#define jot181_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot180_c_( Func, Rec, __VA_ARGS__ )
#define jot182_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot181_c_( Func, Rec, __VA_ARGS__ )
#define jot183_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot182_c_( Func, Rec, __VA_ARGS__ )
#define jot184_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot183_c_( Func, Rec, __VA_ARGS__ )
#define jot185_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot184_c_( Func, Rec, __VA_ARGS__ )
#define jot186_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot185_c_( Func, Rec, __VA_ARGS__ )
#define jot187_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot186_c_( Func, Rec, __VA_ARGS__ )
#define jot188_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot187_c_( Func, Rec, __VA_ARGS__ )
#define jot189_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot188_c_( Func, Rec, __VA_ARGS__ )
#define jot190_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot189_c_( Func, Rec, __VA_ARGS__ )
#define jot191_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot190_c_( Func, Rec, __VA_ARGS__ )
#define jot192_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot191_c_( Func, Rec, __VA_ARGS__ )
#define jot193_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot192_c_( Func, Rec, __VA_ARGS__ )
#define jot194_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot193_c_( Func, Rec, __VA_ARGS__ )
#define jot195_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot194_c_( Func, Rec, __VA_ARGS__ )
#define jot196_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot195_c_( Func, Rec, __VA_ARGS__ )
#define jot197_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot196_c_( Func, Rec, __VA_ARGS__ )
#define jot198_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot197_c_( Func, Rec, __VA_ARGS__ )
#define jot199_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot198_c_( Func, Rec, __VA_ARGS__ )
#define jot200_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot199_c_( Func, Rec, __VA_ARGS__ )
#define jot201_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot200_c_( Func, Rec, __VA_ARGS__ )
#define jot202_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot201_c_( Func, Rec, __VA_ARGS__ )
#define jot203_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot202_c_( Func, Rec, __VA_ARGS__ )
#define jot204_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot203_c_( Func, Rec, __VA_ARGS__ )
#define jot205_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot204_c_( Func, Rec, __VA_ARGS__ )
#define jot206_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot205_c_( Func, Rec, __VA_ARGS__ )
#define jot207_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot206_c_( Func, Rec, __VA_ARGS__ )
#define jot208_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot207_c_( Func, Rec, __VA_ARGS__ )
#define jot209_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot208_c_( Func, Rec, __VA_ARGS__ )
#define jot210_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot209_c_( Func, Rec, __VA_ARGS__ )
#define jot211_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot210_c_( Func, Rec, __VA_ARGS__ )
#define jot212_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot211_c_( Func, Rec, __VA_ARGS__ )
#define jot213_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot212_c_( Func, Rec, __VA_ARGS__ )
#define jot214_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot213_c_( Func, Rec, __VA_ARGS__ )
#define jot215_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot214_c_( Func, Rec, __VA_ARGS__ )
#define jot216_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot215_c_( Func, Rec, __VA_ARGS__ )
#define jot217_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot216_c_( Func, Rec, __VA_ARGS__ )
#define jot218_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot217_c_( Func, Rec, __VA_ARGS__ )
#define jot219_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot218_c_( Func, Rec, __VA_ARGS__ )
#define jot220_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot219_c_( Func, Rec, __VA_ARGS__ )
#define jot221_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot220_c_( Func, Rec, __VA_ARGS__ )
#define jot222_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot221_c_( Func, Rec, __VA_ARGS__ )
#define jot223_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot222_c_( Func, Rec, __VA_ARGS__ )
#define jot224_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot223_c_( Func, Rec, __VA_ARGS__ )
#define jot225_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot224_c_( Func, Rec, __VA_ARGS__ )
#define jot226_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot225_c_( Func, Rec, __VA_ARGS__ )
#define jot227_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot226_c_( Func, Rec, __VA_ARGS__ )
#define jot228_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot227_c_( Func, Rec, __VA_ARGS__ )
#define jot229_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot228_c_( Func, Rec, __VA_ARGS__ )
#define jot230_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot229_c_( Func, Rec, __VA_ARGS__ )
#define jot231_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot230_c_( Func, Rec, __VA_ARGS__ )
#define jot232_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot231_c_( Func, Rec, __VA_ARGS__ )
#define jot233_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot232_c_( Func, Rec, __VA_ARGS__ )
#define jot234_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot233_c_( Func, Rec, __VA_ARGS__ )
#define jot235_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot234_c_( Func, Rec, __VA_ARGS__ )
#define jot236_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot235_c_( Func, Rec, __VA_ARGS__ )
#define jot237_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot236_c_( Func, Rec, __VA_ARGS__ )
#define jot238_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot237_c_( Func, Rec, __VA_ARGS__ )
#define jot239_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot238_c_( Func, Rec, __VA_ARGS__ )
#define jot240_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot239_c_( Func, Rec, __VA_ARGS__ )
#define jot241_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot240_c_( Func, Rec, __VA_ARGS__ )
#define jot242_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot241_c_( Func, Rec, __VA_ARGS__ )
#define jot243_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot242_c_( Func, Rec, __VA_ARGS__ )
#define jot244_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot243_c_( Func, Rec, __VA_ARGS__ )
#define jot245_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot244_c_( Func, Rec, __VA_ARGS__ )
#define jot246_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot245_c_( Func, Rec, __VA_ARGS__ )
#define jot247_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot246_c_( Func, Rec, __VA_ARGS__ )
#define jot248_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot247_c_( Func, Rec, __VA_ARGS__ )
#define jot249_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot248_c_( Func, Rec, __VA_ARGS__ )
#define jot250_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot249_c_( Func, Rec, __VA_ARGS__ )
#define jot251_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot250_c_( Func, Rec, __VA_ARGS__ )
#define jot252_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot251_c_( Func, Rec, __VA_ARGS__ )
#define jot253_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot252_c_( Func, Rec, __VA_ARGS__ )
#define jot254_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot253_c_( Func, Rec, __VA_ARGS__ )
#define jot255_c_( Func, Rec, Val, ... ) Func( (Rec), (Val) ) and jot254_c_( Func, Rec, __VA_ARGS__ )

#endif
