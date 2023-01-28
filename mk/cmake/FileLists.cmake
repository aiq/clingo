################################################################################
# INC_FILES
################################################################################
set( INC_FILES
   ${INC_DIR}/clingo/apidecl.h
   ${INC_DIR}/clingo/version.h

   ${INC_DIR}/clingo/color/cCmyk.h
   ${INC_DIR}/clingo/color/cCmyk32.h
   ${INC_DIR}/clingo/color/cColor.h
   ${INC_DIR}/clingo/color/cHsl.h
   ${INC_DIR}/clingo/color/cHsv.h
   ${INC_DIR}/clingo/color/cP3Creator.h
   ${INC_DIR}/clingo/color/cRgb.h
   ${INC_DIR}/clingo/color/cRgb24.h
   ${INC_DIR}/clingo/color/image.h

   ${INC_DIR}/clingo/container/CBitVec.h
   ${INC_DIR}/clingo/container/CByteVec.h
   ${INC_DIR}/clingo/container/CInt64Map.h
   ${INC_DIR}/clingo/container/CInt64Vec.h
   ${INC_DIR}/clingo/container/CInt64Set.h
   ${INC_DIR}/clingo/container/CObjectVec.h
   ${INC_DIR}/clingo/container/deck.h
   ${INC_DIR}/clingo/container/map.h
   ${INC_DIR}/clingo/container/set.h
   ${INC_DIR}/clingo/container/vec.h

   ${INC_DIR}/clingo/io/c_ImpExpError.h
   ${INC_DIR}/clingo/io/cCell.h
   ${INC_DIR}/clingo/io/cRecorder.h
   ${INC_DIR}/clingo/io/cScanner.h
   ${INC_DIR}/clingo/io/FILE.h
   ${INC_DIR}/clingo/io/fwrite.h
   ${INC_DIR}/clingo/io/jot.h
   ${INC_DIR}/clingo/io/read.h
   ${INC_DIR}/clingo/io/read_type.h
   ${INC_DIR}/clingo/io/write.h
   ${INC_DIR}/clingo/io/write_type.h

   ${INC_DIR}/clingo/lang/algo.h
   ${INC_DIR}/clingo/lang/benchmark.h
   ${INC_DIR}/clingo/lang/chunk.h
   ${INC_DIR}/clingo/lang/CObject.h
   ${INC_DIR}/clingo/lang/expect.h
   ${INC_DIR}/clingo/lang/func.h
   ${INC_DIR}/clingo/lang/locale.h
   ${INC_DIR}/clingo/lang/math.h
   ${INC_DIR}/clingo/lang/mem.h
   ${INC_DIR}/clingo/lang/slice.h
   ${INC_DIR}/clingo/lang/window.h

   ${INC_DIR}/clingo/string/CDictionary.h
   ${INC_DIR}/clingo/string/CString.h
   ${INC_DIR}/clingo/string/cStringBuilder.h
   ${INC_DIR}/clingo/string/CStringList.h
   ${INC_DIR}/clingo/string/CStringSet.h

   ${INC_DIR}/clingo/time/C_TimeFormats.h
   ${INC_DIR}/clingo/time/c_Month.h
   ${INC_DIR}/clingo/time/c_Weekday.h
   ${INC_DIR}/clingo/time/cDate.h
   ${INC_DIR}/clingo/time/cDatePeriod.h
   ${INC_DIR}/clingo/time/cDaySet.h
   ${INC_DIR}/clingo/time/cDaytime.h
   ${INC_DIR}/clingo/time/cDuration.h
   ${INC_DIR}/clingo/time/cHmsn.h
   ${INC_DIR}/clingo/time/cMonthDay.h
   ${INC_DIR}/clingo/time/cOrdinalDate.h
   ${INC_DIR}/clingo/time/cStopwatch.h
   ${INC_DIR}/clingo/time/cTime.h
   ${INC_DIR}/clingo/time/cTimestamp.h
   ${INC_DIR}/clingo/time/cTzOffset.h
   ${INC_DIR}/clingo/time/cWeekDate.h
   ${INC_DIR}/clingo/time/cYmd.h
   ${INC_DIR}/clingo/time/year.h

   ${INC_DIR}/clingo/type/bool.h
   ${INC_DIR}/clingo/type/c_ByteOrder.h
   ${INC_DIR}/clingo/type/cByte.h
   ${INC_DIR}/clingo/type/cBytes.h
   ${INC_DIR}/clingo/type/cChars.h
   ${INC_DIR}/clingo/type/char.h
   ${INC_DIR}/clingo/type/cChars.h
   ${INC_DIR}/clingo/type/cCharsSlice.h
   ${INC_DIR}/clingo/type/cCharsToken.h
   ${INC_DIR}/clingo/type/cRange.h
   ${INC_DIR}/clingo/type/cRune.h
   ${INC_DIR}/clingo/type/cRuneRange.h
   ${INC_DIR}/clingo/type/double.h
   ${INC_DIR}/clingo/type/float.h
   ${INC_DIR}/clingo/type/int16.h
   ${INC_DIR}/clingo/type/int32.h
   ${INC_DIR}/clingo/type/int64.h
   ${INC_DIR}/clingo/type/int8.h
   ${INC_DIR}/clingo/type/uint16.h
   ${INC_DIR}/clingo/type/uint32.h
   ${INC_DIR}/clingo/type/uint64.h
   ${INC_DIR}/clingo/type/uint8.h
)

################################################################################
# SRC_FILES
################################################################################
set( SRC_FILES
   ${SRC_DIR}/_/io/cWriteNumFormat.c
   ${SRC_DIR}/_/io/read_num.c
   ${SRC_DIR}/_/io/read_write_util-cReadCommand.c
   ${SRC_DIR}/_/io/read_write_util-cReadSpecifier.c
   ${SRC_DIR}/_/io/read_write_util-cWriteSpecifier.c
   ${SRC_DIR}/_/io/write_float_num.c
   ${SRC_DIR}/_/io/write_num.c
   ${SRC_DIR}/_/time/read_time_util.c
   ${SRC_DIR}/_/time/util.c
   ${SRC_DIR}/_/time/write_time_util.c

   ${SRC_DIR}/clingo/color/cCmyk.c
   ${SRC_DIR}/clingo/color/cCmyk32.c
   ${SRC_DIR}/clingo/color/cColor.c
   ${SRC_DIR}/clingo/color/cHsl.c
   ${SRC_DIR}/clingo/color/cHsv.c
   ${SRC_DIR}/clingo/color/cP3Creator.c
   ${SRC_DIR}/clingo/color/cRgb.c
   ${SRC_DIR}/clingo/color/cRgb24.c
   ${SRC_DIR}/clingo/color/image.c

   ${SRC_DIR}/clingo/container/CBitVec.c
   ${SRC_DIR}/clingo/container/CByteVec.c
   ${SRC_DIR}/clingo/container/CInt64Map.c
   ${SRC_DIR}/clingo/container/CInt64Vec.c
   ${SRC_DIR}/clingo/container/CInt64Set.c
   ${SRC_DIR}/clingo/container/CObjectVec.c
   ${SRC_DIR}/clingo/container/map.c
   ${SRC_DIR}/clingo/container/set.c
   ${SRC_DIR}/clingo/container/vec.c

   ${SRC_DIR}/clingo/io/c_ImpExpError.c
   ${SRC_DIR}/clingo/io/cCell.c
   ${SRC_DIR}/clingo/io/cRecorder.c
   ${SRC_DIR}/clingo/io/cScanner.c
   ${SRC_DIR}/clingo/io/FILE.c
   ${SRC_DIR}/clingo/io/fwrite.c
   ${SRC_DIR}/clingo/io/print.c
   ${SRC_DIR}/clingo/io/read.c
   ${SRC_DIR}/clingo/io/read_type.c
   ${SRC_DIR}/clingo/io/write.c
   ${SRC_DIR}/clingo/io/write_type.c

   ${SRC_DIR}/clingo/lang/benchmark.c
   ${SRC_DIR}/clingo/lang/CObject.c
   ${SRC_DIR}/clingo/lang/error.c
   ${SRC_DIR}/clingo/lang/expect.c
   ${SRC_DIR}/clingo/lang/func.c
   ${SRC_DIR}/clingo/lang/locale.c
   ${SRC_DIR}/clingo/lang/math.c
   ${SRC_DIR}/clingo/lang/mem.c

   ${SRC_DIR}/clingo/string/CDictionary.c
   ${SRC_DIR}/clingo/string/CString.c
   ${SRC_DIR}/clingo/string/cStringBuilder.c
   ${SRC_DIR}/clingo/string/CStringList.c
   ${SRC_DIR}/clingo/string/CStringSet.c

   ${SRC_DIR}/clingo/time/C_TimeFormats.c
   ${SRC_DIR}/clingo/time/c_Month.c
   ${SRC_DIR}/clingo/time/c_Weekday.c
   ${SRC_DIR}/clingo/time/cDate.c
   ${SRC_DIR}/clingo/time/cDatePeriod.c
   ${SRC_DIR}/clingo/time/cDaySet.c
   ${SRC_DIR}/clingo/time/cDaytime.c
   ${SRC_DIR}/clingo/time/cDuration.c
   ${SRC_DIR}/clingo/time/cHmsn.c
   ${SRC_DIR}/clingo/time/cMonthDay.c
   ${SRC_DIR}/clingo/time/cOrdinalDate.c
   ${SRC_DIR}/clingo/time/cStopwatch.c
   ${SRC_DIR}/clingo/time/cTime.c
   ${SRC_DIR}/clingo/time/cTimestamp.c
   ${SRC_DIR}/clingo/time/cTzOffset.c
   ${SRC_DIR}/clingo/time/cWeekDate.c
   ${SRC_DIR}/clingo/time/cYmd.c
   ${SRC_DIR}/clingo/time/year.c

   ${SRC_DIR}/clingo/type/bool.c
   ${SRC_DIR}/clingo/type/c_ByteOrder.c
   ${SRC_DIR}/clingo/type/cByte.c
   ${SRC_DIR}/clingo/type/cBytes.c
   ${SRC_DIR}/clingo/type/char.c
   ${SRC_DIR}/clingo/type/cChars.c
   ${SRC_DIR}/clingo/type/cCharsSlice.c
   ${SRC_DIR}/clingo/type/cCharsToken.c
   ${SRC_DIR}/clingo/type/cRange.c
   ${SRC_DIR}/clingo/type/cRune.c
   ${SRC_DIR}/clingo/type/cRuneRange.c
   ${SRC_DIR}/clingo/type/double.c
   ${SRC_DIR}/clingo/type/float.c
   ${SRC_DIR}/clingo/type/int16.c
   ${SRC_DIR}/clingo/type/int32.c
   ${SRC_DIR}/clingo/type/int64.c
   ${SRC_DIR}/clingo/type/int8.c
   ${SRC_DIR}/clingo/type/uint16.c
   ${SRC_DIR}/clingo/type/uint32.c
   ${SRC_DIR}/clingo/type/uint64.c
   ${SRC_DIR}/clingo/type/uint8.c

   ${SRC_DIR}/clingo/requirements.c
)

################################################################################
# TEST_FILES
################################################################################
set( TEST_FILES
#[[
   ${TEST_DIR}/_/io/read_write_util/read_in_read_command.c
   ${TEST_DIR}/_/io/read_write_util/read_in_till_end.c
   ${TEST_DIR}/_/io/write_num/write_bin.c
   ${TEST_DIR}/_/io/write_num/write_hex.c
   ${TEST_DIR}/_/io/write_num/write_oct.c
   ${TEST_DIR}/_/algo/sum.c
]]
   ####################################################################### color
   # cCmyk
   ${TEST_DIR}/clingo/color/cCmyk/cmyk_from_cmyk32.c
   ${TEST_DIR}/clingo/color/cCmyk/cmyk32_from_cmyk.c
   ${TEST_DIR}/clingo/color/cCmyk/eq_cmyk.c

   # cCmyk32
   #${TEST_DIR}/clingo/color/cCmyk32/eq_cmyk32.c

   # cColor
   ${TEST_DIR}/clingo/color/cColor/as_cmyk.c
   ${TEST_DIR}/clingo/color/cColor/as_cmyk32.c
   ${TEST_DIR}/clingo/color/cColor/as_hsl.c
   ${TEST_DIR}/clingo/color/cColor/as_hsv.c
   ${TEST_DIR}/clingo/color/cColor/as_rgb.c
   ${TEST_DIR}/clingo/color/cColor/average_color.c
   ${TEST_DIR}/clingo/color/cColor/color_luma.c
   ${TEST_DIR}/clingo/color/cColor/contrast_color.c
   ${TEST_DIR}/clingo/color/cColor/darken_color.c
   ${TEST_DIR}/clingo/color/cColor/desaturate_color.c
   ${TEST_DIR}/clingo/color/cColor/difference_color.c
   ${TEST_DIR}/clingo/color/cColor/eq_color.c
   ${TEST_DIR}/clingo/color/cColor/exclusion_color.c
   ${TEST_DIR}/clingo/color/cColor/fade_color.c
   ${TEST_DIR}/clingo/color/cColor/from_cmyk.c
   ${TEST_DIR}/clingo/color/cColor/from_cmyk32.c
   ${TEST_DIR}/clingo/color/cColor/from_hsl.c
   ${TEST_DIR}/clingo/color/cColor/from_hsv.c
   ${TEST_DIR}/clingo/color/cColor/from_rgb.c
   ${TEST_DIR}/clingo/color/cColor/greyscale_color.c
   ${TEST_DIR}/clingo/color/cColor/hardlight_color.c
   ${TEST_DIR}/clingo/color/cColor/lighten_color.c
   ${TEST_DIR}/clingo/color/cColor/mix_color.c
   ${TEST_DIR}/clingo/color/cColor/multiply_color.c
   ${TEST_DIR}/clingo/color/cColor/negation_color.c
   ${TEST_DIR}/clingo/color/cColor/overlay_color.c
   ${TEST_DIR}/clingo/color/cColor/saturate_color.c
   ${TEST_DIR}/clingo/color/cColor/screen_color.c
   ${TEST_DIR}/clingo/color/cColor/softlight_color.c
   ${TEST_DIR}/clingo/color/cColor/spin_color.c

   # cP3Creator
   ${TEST_DIR}/clingo/color/cP3Creator/cP3Creator-overview.c

   # cRgb
   #${TEST_DIR}/clingo/color/cRgb/eq_rgb.c
   #${TEST_DIR}/clingo/color/cRgb/rgb_from_rgb24.c
   #${TEST_DIR}/clingo/color/cRgb/rgb24_from_rgb.c

   # cRgb24
   #${TEST_DIR}/clingo/color/cRgb/eq_rgb24.c

   ################################################################### container
   # CBitVec
   ${TEST_DIR}/clingo/container/CBitVec/bit_vec_from_cstr.c
   ${TEST_DIR}/clingo/container/CBitVec/bitand_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/bitand_on_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/bitor_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/bitor_on_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/compl_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/compl_on_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/copy_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/find_index_of_bit.c
   ${TEST_DIR}/clingo/container/CBitVec/popcount_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/read_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/rfind_index_of_bit.c
   ${TEST_DIR}/clingo/container/CBitVec/set_on_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/set_range_on_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/shift_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/write_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/xor_bit_vec.c
   ${TEST_DIR}/clingo/container/CBitVec/xor_on_bit_vec.c

   # CByteVec
   ${TEST_DIR}/clingo/container/CByteVec/CByteVec-overview.c
   ${TEST_DIR}/clingo/container/CByteVec/write_byte_vec.c

   # CInt64Map
   ${TEST_DIR}/clingo/container/CInt64Map/CInt64Map-overview.c

   # CInt64Vec
   ${TEST_DIR}/clingo/container/CInt64Vec/CInt64Vec-overview.c

   # CObjectVec
   ${TEST_DIR}/clingo/container/CObjectVec/CObjectVec-overview.c

   # map
   ${TEST_DIR}/clingo/container/map/benchmark-map.c
   ${TEST_DIR}/clingo/container/map/iterate_map.c

   # pile
   ${TEST_DIR}/clingo/container/pile/INSERT.c
   ${TEST_DIR}/clingo/container/pile/PUT.c

   # set
   ${TEST_DIR}/clingo/container/set/iterate_set.c

   # vec
   ${TEST_DIR}/clingo/container/vec/benchmark-vec.c

   ########################################################################## io
   # cCell
   ${TEST_DIR}/clingo/io/cCell/read_in_cell.c
   ${TEST_DIR}/clingo/io/cCell/write_ascii_into_cell.c

   # cRecorder
   ${TEST_DIR}/clingo/io/cRecorder/alloc_recorder_mem.c
   ${TEST_DIR}/clingo/io/cRecorder/move_recorder.c
   ${TEST_DIR}/clingo/io/cRecorder/move_recorder_to.c
   ${TEST_DIR}/clingo/io/cRecorder/realloc_recorder_mem.c
   ${TEST_DIR}/clingo/io/cRecorder/record_byte.c
   ${TEST_DIR}/clingo/io/cRecorder/record_char.c
   ${TEST_DIR}/clingo/io/cRecorder/record_chars.c
   ${TEST_DIR}/clingo/io/cRecorder/record_chars_slice.c
   ${TEST_DIR}/clingo/io/cRecorder/record_cstr.c
   ${TEST_DIR}/clingo/io/cRecorder/record_int16.c
   ${TEST_DIR}/clingo/io/cRecorder/record_int32.c
   ${TEST_DIR}/clingo/io/cRecorder/record_int64.c
   ${TEST_DIR}/clingo/io/cRecorder/record_int8.c
   ${TEST_DIR}/clingo/io/cRecorder/record_mem.c
   ${TEST_DIR}/clingo/io/cRecorder/record_pad.c
   ${TEST_DIR}/clingo/io/cRecorder/record_rune.c
   ${TEST_DIR}/clingo/io/cRecorder/record_uint16.c
   ${TEST_DIR}/clingo/io/cRecorder/record_uint32.c
   ${TEST_DIR}/clingo/io/cRecorder/record_uint64.c
   ${TEST_DIR}/clingo/io/cRecorder/record_uint8.c
   ${TEST_DIR}/clingo/io/cRecorder/recordf.c
   ${TEST_DIR}/clingo/io/cRecorder/reset_recorder.c
   ${TEST_DIR}/clingo/io/cRecorder/turn_into_cstr.c

   # cScanner
   ${TEST_DIR}/clingo/io/cScanner/cstr_scanner.c
   ${TEST_DIR}/clingo/io/cScanner/move_if_char.c
   ${TEST_DIR}/clingo/io/cScanner/move_scanner.c
   ${TEST_DIR}/clingo/io/cScanner/move_scanner_to.c
   ${TEST_DIR}/clingo/io/cScanner/move_to_char_match.c
   ${TEST_DIR}/clingo/io/cScanner/move_while_char_match.c
   ${TEST_DIR}/clingo/io/cScanner/scan_byte.c
   ${TEST_DIR}/clingo/io/cScanner/scan_char.c
   ${TEST_DIR}/clingo/io/cScanner/scan_rune.c
   ${TEST_DIR}/clingo/io/cScanner/view_cstr.c
   ${TEST_DIR}/clingo/io/cScanner/view_pad.c
   ${TEST_DIR}/clingo/io/cScanner/view_runes.c

   # FILE
   ${TEST_DIR}/clingo/io/FILE/fget_line.c
   ${TEST_DIR}/clingo/io/FILE/write_binary_file.c
   ${TEST_DIR}/clingo/io/FILE/write_text_file.c

   ${TEST_DIR}/clingo/io/fwrite/fwriteln.c

   ${TEST_DIR}/clingo/io/jot/jot.c

   ${TEST_DIR}/clingo/io/print/print-overview.c

   ${TEST_DIR}/clingo/io/read/read.c

   # read_type
   ${TEST_DIR}/clingo/io/read_type/read_bool.c
   ${TEST_DIR}/clingo/io/read_type/read_chars.c
   ${TEST_DIR}/clingo/io/read_type/read_double.c
   ${TEST_DIR}/clingo/io/read_type/read_float.c
   ${TEST_DIR}/clingo/io/read_type/read_int16.c
   ${TEST_DIR}/clingo/io/read_type/read_int32.c
   ${TEST_DIR}/clingo/io/read_type/read_int64.c
   ${TEST_DIR}/clingo/io/read_type/read_int8.c
   ${TEST_DIR}/clingo/io/read_type/read_range.c
   ${TEST_DIR}/clingo/io/read_type/read_rune.c
   ${TEST_DIR}/clingo/io/read_type/read_uint16.c
   ${TEST_DIR}/clingo/io/read_type/read_uint32.c
   ${TEST_DIR}/clingo/io/read_type/read_uint64.c
   ${TEST_DIR}/clingo/io/read_type/read_uint8.c

   ${TEST_DIR}/clingo/io/write/write.c

   # write_type
   ${TEST_DIR}/clingo/io/write_type/write_bool.c
   ${TEST_DIR}/clingo/io/write_type/write_byte.c
   ${TEST_DIR}/clingo/io/write_type/write_bytes.c
   ${TEST_DIR}/clingo/io/write_type/write_char.c
   ${TEST_DIR}/clingo/io/write_type/write_chars.c
   ${TEST_DIR}/clingo/io/write_type/write_double.c
   ${TEST_DIR}/clingo/io/write_type/write_float.c
   ${TEST_DIR}/clingo/io/write_type/write_int16.c
   ${TEST_DIR}/clingo/io/write_type/write_int32.c
   ${TEST_DIR}/clingo/io/write_type/write_int64.c
   ${TEST_DIR}/clingo/io/write_type/write_int8.c
   ${TEST_DIR}/clingo/io/write_type/write_range.c
   ${TEST_DIR}/clingo/io/write_type/write_recorded.c
   ${TEST_DIR}/clingo/io/write_type/write_rune.c
   ${TEST_DIR}/clingo/io/write_type/write_uint16.c
   ${TEST_DIR}/clingo/io/write_type/write_uint32.c
   ${TEST_DIR}/clingo/io/write_type/write_uint64.c
   ${TEST_DIR}/clingo/io/write_type/write_uint8.c

   ######################################################################## lang
   # algo
   ${TEST_DIR}/clingo/lang/algo/BSEARCH.c
   ${TEST_DIR}/clingo/lang/algo/CMP_SLICE.c
   ${TEST_DIR}/clingo/lang/algo/COUNT_EQ.c
   ${TEST_DIR}/clingo/lang/algo/ENDS_WITH.c
   ${TEST_DIR}/clingo/lang/algo/FIND_MAX.c
   ${TEST_DIR}/clingo/lang/algo/FIND_MIN.c
   ${TEST_DIR}/clingo/lang/algo/FIND_VAL.c
   ${TEST_DIR}/clingo/lang/algo/INDEX_OF_SLICE.c
   ${TEST_DIR}/clingo/lang/algo/QSORT.c
   ${TEST_DIR}/clingo/lang/algo/REMOVE.c
   ${TEST_DIR}/clingo/lang/algo/REVERSE.c
   ${TEST_DIR}/clingo/lang/algo/ROTATE.c
   ${TEST_DIR}/clingo/lang/algo/SET_SLICE.c
   ${TEST_DIR}/clingo/lang/algo/STARTS_WITH.c
   ${TEST_DIR}/clingo/lang/algo/TAKE.c
   # chunk
   ${TEST_DIR}/clingo/lang/chunk/exact_chunk.c
   ${TEST_DIR}/clingo/lang/chunk/next_chunk.c
   ${TEST_DIR}/clingo/lang/chunk/prev_chunk.c
   ${TEST_DIR}/clingo/lang/chunk/valid_chunk.c
   # CObject
   ${TEST_DIR}/clingo/lang/CObject/let_object.c
   # error
   ${TEST_DIR}/clingo/lang/error/reset_error_stack.c
   ${TEST_DIR}/clingo/lang/error/write_error.c
   # expect
   ${TEST_DIR}/clingo/lang/expect/check_cmp_results.c
   ${TEST_DIR}/clingo/lang/expect/expect.c
   # func
   ${TEST_DIR}/clingo/lang/func/cmp.c
   ${TEST_DIR}/clingo/lang/func/concat2.c
   ${TEST_DIR}/clingo/lang/func/concat3.c
   ${TEST_DIR}/clingo/lang/func/flags.c
   ${TEST_DIR}/clingo/lang/func/in_range.c
   ${TEST_DIR}/clingo/lang/func/is_sign.c
   ${TEST_DIR}/clingo/lang/func/nargs.c
   ${TEST_DIR}/clingo/lang/func/once.c
   ${TEST_DIR}/clingo/lang/func/sign.c
   ${TEST_DIR}/clingo/lang/func/stringify.c
   ${TEST_DIR}/clingo/lang/func/swap.c
   ${TEST_DIR}/clingo/lang/func/times.c
   ${TEST_DIR}/clingo/lang/func/xconcat2.c
   ${TEST_DIR}/clingo/lang/func/xconcat3.c
   ${TEST_DIR}/clingo/lang/func/xstringify.c
   # math
   ${TEST_DIR}/clingo/lang/math/iabs16.c
   ${TEST_DIR}/clingo/lang/math/iabs32.c
   ${TEST_DIR}/clingo/lang/math/iabs64.c
   ${TEST_DIR}/clingo/lang/math/iabs8.c
   ${TEST_DIR}/clingo/lang/math/iadd16.c
   ${TEST_DIR}/clingo/lang/math/iadd32.c
   ${TEST_DIR}/clingo/lang/math/iadd64.c
   ${TEST_DIR}/clingo/lang/math/iadd8.c
   ${TEST_DIR}/clingo/lang/math/imax16.c
   ${TEST_DIR}/clingo/lang/math/imax32.c
   ${TEST_DIR}/clingo/lang/math/imax64.c
   ${TEST_DIR}/clingo/lang/math/imax8.c
   ${TEST_DIR}/clingo/lang/math/imin16.c
   ${TEST_DIR}/clingo/lang/math/imin32.c
   ${TEST_DIR}/clingo/lang/math/imin64.c
   ${TEST_DIR}/clingo/lang/math/imin8.c
   ${TEST_DIR}/clingo/lang/math/imul16.c
   ${TEST_DIR}/clingo/lang/math/imul32.c
   ${TEST_DIR}/clingo/lang/math/imul64.c
   ${TEST_DIR}/clingo/lang/math/imul8.c
   ${TEST_DIR}/clingo/lang/math/isub16.c
   ${TEST_DIR}/clingo/lang/math/isub32.c
   ${TEST_DIR}/clingo/lang/math/isub64.c
   ${TEST_DIR}/clingo/lang/math/isub8.c
   ${TEST_DIR}/clingo/lang/math/uadd16.c
   ${TEST_DIR}/clingo/lang/math/uadd32.c
   ${TEST_DIR}/clingo/lang/math/uadd64.c
   ${TEST_DIR}/clingo/lang/math/uadd8.c
   ${TEST_DIR}/clingo/lang/math/umax16.c
   ${TEST_DIR}/clingo/lang/math/umax32.c
   ${TEST_DIR}/clingo/lang/math/umax64.c
   ${TEST_DIR}/clingo/lang/math/umax8.c
   ${TEST_DIR}/clingo/lang/math/umin16.c
   ${TEST_DIR}/clingo/lang/math/umin32.c
   ${TEST_DIR}/clingo/lang/math/umin64.c
   ${TEST_DIR}/clingo/lang/math/umin8.c
   ${TEST_DIR}/clingo/lang/math/umul16.c
   ${TEST_DIR}/clingo/lang/math/umul32.c
   ${TEST_DIR}/clingo/lang/math/umul64.c
   ${TEST_DIR}/clingo/lang/math/umul8.c
   ${TEST_DIR}/clingo/lang/math/usub16.c
   ${TEST_DIR}/clingo/lang/math/usub32.c
   ${TEST_DIR}/clingo/lang/math/usub64.c
   ${TEST_DIR}/clingo/lang/math/usub8.c
   # slice
   ${TEST_DIR}/clingo/lang/slice/atween.c
   ${TEST_DIR}/clingo/lang/slice/begin.c
   ${TEST_DIR}/clingo/lang/slice/end.c
   ${TEST_DIR}/clingo/lang/slice/first.c
   ${TEST_DIR}/clingo/lang/slice/for_each.c
   ${TEST_DIR}/clingo/lang/slice/get_if.c
   ${TEST_DIR}/clingo/lang/slice/index_of.c
   ${TEST_DIR}/clingo/lang/slice/is_empty.c
   ${TEST_DIR}/clingo/lang/slice/is_sub.c
   ${TEST_DIR}/clingo/lang/slice/last.c
   ${TEST_DIR}/clingo/lang/slice/left.c
   ${TEST_DIR}/clingo/lang/slice/mid.c
   ${TEST_DIR}/clingo/lang/slice/nth.c
   ${TEST_DIR}/clingo/lang/slice/points_into.c
   ${TEST_DIR}/clingo/lang/slice/ptr_for.c
   ${TEST_DIR}/clingo/lang/slice/rbegin.c
   ${TEST_DIR}/clingo/lang/slice/rend.c
   ${TEST_DIR}/clingo/lang/slice/right.c
   ${TEST_DIR}/clingo/lang/slice/scalars.c
   ${TEST_DIR}/clingo/lang/slice/set_if.c
   ${TEST_DIR}/clingo/lang/slice/slice.c
   ${TEST_DIR}/clingo/lang/slice/structs.c
   ${TEST_DIR}/clingo/lang/slice/sub.c
   ${TEST_DIR}/clingo/lang/slice/TEMP_SLICE_DEF.c
   ${TEST_DIR}/clingo/lang/slice/valid_index.c
   # window
   ${TEST_DIR}/clingo/lang/window/next_window.c
   ${TEST_DIR}/clingo/lang/window/prev_window.c
   ${TEST_DIR}/clingo/lang/window/valid_window.c

   ######################################################################### str
   ${TEST_DIR}/clingo/string/CDictionary/CDictionary-overview.c
   # CString
   ${TEST_DIR}/clingo/string/CString/adopt_string.c
   ${TEST_DIR}/clingo/string/CString/empty_string.c
   ${TEST_DIR}/clingo/string/CString/is_ascii_string.c
   ${TEST_DIR}/clingo/string/CString/left_string.c
   ${TEST_DIR}/clingo/string/CString/lit.c
   ${TEST_DIR}/clingo/string/CString/mid_string.c
   ${TEST_DIR}/clingo/string/CString/new_left_string.c
   ${TEST_DIR}/clingo/string/CString/new_mid_string.c
   ${TEST_DIR}/clingo/string/CString/new_right_string.c
   ${TEST_DIR}/clingo/string/CString/new_string.c
   ${TEST_DIR}/clingo/string/CString/new_sub_string.c
   ${TEST_DIR}/clingo/string/CString/right_string.c
   ${TEST_DIR}/clingo/string/CString/scs.c
   ${TEST_DIR}/clingo/string/CString/scstr.c
   ${TEST_DIR}/clingo/string/CString/string_is.c
   ${TEST_DIR}/clingo/string/CString/string_is_empty.c
   ${TEST_DIR}/clingo/string/CString/string_length.c
   ${TEST_DIR}/clingo/string/CString/sub_string.c
   # cStringBuilder
   ${TEST_DIR}/clingo/string/cStringBuilder/cStringBuilder-overview.c
   # CStringList
   ${TEST_DIR}/clingo/string/CStringList/count_string_list_chars.c
   ${TEST_DIR}/clingo/string/CStringList/count_string_list_runes.c
   ${TEST_DIR}/clingo/string/CStringList/CStringList-overview.c
   ${TEST_DIR}/clingo/string/CStringList/from_chars_slice.c
   ${TEST_DIR}/clingo/string/CStringList/join_string_list.c
   ${TEST_DIR}/clingo/string/CStringList/set_cstr_on_string_list.c

   ######################################################################## time
   # C_TimeFormats
   ${TEST_DIR}/clingo/time/C_TimeFormats/C_TimeFormats-test.c

   # c_Month
   ${TEST_DIR}/clingo/time/c_Month/days_per_month.c
   ${TEST_DIR}/clingo/time/c_Month/first_month_day_of_year.c
   ${TEST_DIR}/clingo/time/c_Month/first_month_of_quarter.c
   ${TEST_DIR}/clingo/time/c_Month/get_month_abbrev.c
   ${TEST_DIR}/clingo/time/c_Month/get_month_name.c
   ${TEST_DIR}/clingo/time/c_Month/int64_to_month.c
   ${TEST_DIR}/clingo/time/c_Month/stringify_month.c

   # c_Weekday
   ${TEST_DIR}/clingo/time/c_Weekday/get_weekday_abbrev.c
   ${TEST_DIR}/clingo/time/c_Weekday/get_weekday_name.c
   ${TEST_DIR}/clingo/time/c_Weekday/int64_to_weekday.c
   ${TEST_DIR}/clingo/time/c_Weekday/stringify_weekday.c
   ${TEST_DIR}/clingo/time/c_Weekday/tm_wday_to_weekday.c
   ${TEST_DIR}/clingo/time/c_Weekday/weekday.c

   # cDate
   ${TEST_DIR}/clingo/time/cDate/add_months_to_date.c
   ${TEST_DIR}/clingo/time/cDate/add_weeks_to_date.c
   ${TEST_DIR}/clingo/time/cDate/add_days_to_date.c
   ${TEST_DIR}/clingo/time/cDate/add_years_to_date.c
   ${TEST_DIR}/clingo/time/cDate/as_julian_day.c
   ${TEST_DIR}/clingo/time/cDate/as_ordinal_date.c
   ${TEST_DIR}/clingo/time/cDate/as_week_date.c
   ${TEST_DIR}/clingo/time/cDate/as_ymd.c
   ${TEST_DIR}/clingo/time/cDate/cmp_date.c
   ${TEST_DIR}/clingo/time/cDate/date_day_of_year.c
   ${TEST_DIR}/clingo/time/cDate/date_is_valid.c
   ${TEST_DIR}/clingo/time/cDate/date_weekday.c
   ${TEST_DIR}/clingo/time/cDate/days_between_dates.c
   ${TEST_DIR}/clingo/time/cDate/early_date.c
   ${TEST_DIR}/clingo/time/cDate/from_julian_day.c
   ${TEST_DIR}/clingo/time/cDate/from_ordinal_date.c
   ${TEST_DIR}/clingo/time/cDate/from_week_date.c
   ${TEST_DIR}/clingo/time/cDate/from_ymd.c
   ${TEST_DIR}/clingo/time/cDate/late_date.c
   ${TEST_DIR}/clingo/time/cDate/months_between_dates.c
   ${TEST_DIR}/clingo/time/cDate/next_weekday_date.c
   ${TEST_DIR}/clingo/time/cDate/prev_weekday_date.c
   ${TEST_DIR}/clingo/time/cDate/read_date.c
   ${TEST_DIR}/clingo/time/cDate/weeks_between_dates.c
   ${TEST_DIR}/clingo/time/cDate/write_date.c
   ${TEST_DIR}/clingo/time/cDate/years_between_dates.c

   # cDatePeriod
   ${TEST_DIR}/clingo/time/cDatePeriod/date_period_days.c
   ${TEST_DIR}/clingo/time/cDatePeriod/date_period_is_valid.c
   ${TEST_DIR}/clingo/time/cDatePeriod/date_period_weeks.c
   ${TEST_DIR}/clingo/time/cDatePeriod/date_periods_overlap.c
   ${TEST_DIR}/clingo/time/cDatePeriod/determine_date_period.c
   ${TEST_DIR}/clingo/time/cDatePeriod/in_date_period.c
   ${TEST_DIR}/clingo/time/cDatePeriod/intersect_date_periods.c
   ${TEST_DIR}/clingo/time/cDatePeriod/resize_date_period.c
   ${TEST_DIR}/clingo/time/cDatePeriod/shift_date_period.c
   ${TEST_DIR}/clingo/time/cDatePeriod/unite_date_periods.c

   # CDaySet
   ${TEST_DIR}/clingo/time/CDaySet/count_days.c
   ${TEST_DIR}/clingo/time/CDaySet/date_period_in_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/day_set_period.c
   ${TEST_DIR}/clingo/time/CDaySet/days_in_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/first_in_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/in_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/last_in_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/next_in_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/prev_in_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/remove_date_period_from_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/remove_days_from_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/remove_from_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/set_date_period_on_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/set_days_on_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/set_on_day_set.c
   ${TEST_DIR}/clingo/time/CDaySet/write_day_set.c

   # cDaytime
   ${TEST_DIR}/clingo/time/cDaytime/add_to_daytime.c
   ${TEST_DIR}/clingo/time/cDaytime/between_daytimes.c
   ${TEST_DIR}/clingo/time/cDaytime/early_daytime.c
   ${TEST_DIR}/clingo/time/cDaytime/late_daytime.c

   # cDuration
   ${TEST_DIR}/clingo/time/cDuration/add_duration.c
   ${TEST_DIR}/clingo/time/cDuration/cDuration-conv.c
   ${TEST_DIR}/clingo/time/cDuration/cDuration-init.c
   ${TEST_DIR}/clingo/time/cDuration/hmsn_from_duration.c
   ${TEST_DIR}/clingo/time/cDuration/read_duration.c
   ${TEST_DIR}/clingo/time/cDuration/to_time_unit.c
   ${TEST_DIR}/clingo/time/cDuration/truncate_duration.c
   ${TEST_DIR}/clingo/time/cDuration/write_duration.c

   # cHmsn
   ${TEST_DIR}/clingo/time/cHmsn/cmp_hmsn.c
   ${TEST_DIR}/clingo/time/cHmsn/hmsn_is_valid.c
   ${TEST_DIR}/clingo/time/cHmsn/read_hmsn.c
   ${TEST_DIR}/clingo/time/cHmsn/write_hmsn.c

   # cMonthDay
   ${TEST_DIR}/clingo/time/cMonthDay/cmp_month_day.c
   ${TEST_DIR}/clingo/time/cMonthDay/read_month_day.c
   ${TEST_DIR}/clingo/time/cMonthDay/write_month_day.c

   # cOrdinalDate
   ${TEST_DIR}/clingo/time/cOrdinalDate/cmp_ordinal_date.c
   ${TEST_DIR}/clingo/time/cOrdinalDate/cOrdinalDate-from.c
   ${TEST_DIR}/clingo/time/cOrdinalDate/ordinal_date_is_valid.c
   ${TEST_DIR}/clingo/time/cOrdinalDate/read_ordinal_date.c
   ${TEST_DIR}/clingo/time/cOrdinalDate/write_ordinal_date.c

   # cTime
   ${TEST_DIR}/clingo/time/cTime/as_timestamp.c
   ${TEST_DIR}/clingo/time/cTime/cTime-get.c
   ${TEST_DIR}/clingo/time/cTime/read_time.c
   ${TEST_DIR}/clingo/time/cTime/shift_time.c
   ${TEST_DIR}/clingo/time/cTime/write_time.c

   # cTzOffset
   ${TEST_DIR}/clingo/time/cTzOffset/between_tz_offsets.c
   ${TEST_DIR}/clingo/time/cTzOffset/read_tz_offset.c
   ${TEST_DIR}/clingo/time/cTzOffset/write_tz_offset.c

   # cWeekDate
   ${TEST_DIR}/clingo/time/cWeekDate/cmp_week_date.c
   ${TEST_DIR}/clingo/time/cWeekDate/cWeekDate-from.c
   ${TEST_DIR}/clingo/time/cWeekDate/read_week_date.c
   ${TEST_DIR}/clingo/time/cWeekDate/write_week_date.c

   # cYmd
   ${TEST_DIR}/clingo/time/cYmd/cmp_ymd.c
   ${TEST_DIR}/clingo/time/cYmd/read_ymd.c
   ${TEST_DIR}/clingo/time/cYmd/write_ymd.c
   ${TEST_DIR}/clingo/time/cYmd/ymd_is_valid.c

   # year
   ${TEST_DIR}/clingo/time/year/century.c
   ${TEST_DIR}/clingo/time/year/days_of_year.c
   ${TEST_DIR}/clingo/time/year/is_leap_year.c
   ${TEST_DIR}/clingo/time/year/year_in_century.c

   ######################################################################## type
   # bool
   ${TEST_DIR}/clingo/type/bool/and_bool_slice_values.c
   ${TEST_DIR}/clingo/type/bool/cmp_bool.c
   ${TEST_DIR}/clingo/type/bool/count_eq_bool.c
   ${TEST_DIR}/clingo/type/bool/or_bool_slice_values.c
   # c_ByteOrder
   ${TEST_DIR}/clingo/type/c_ByteOrder/stringify_byte_order.c
   ${TEST_DIR}/clingo/type/c_ByteOrder/swap_eight_bytes.c
   ${TEST_DIR}/clingo/type/c_ByteOrder/swap_four_bytes.c
   ${TEST_DIR}/clingo/type/c_ByteOrder/swap_two_bytes.c
   # cByte
   ${TEST_DIR}/clingo/type/cByte/byte_as_bit.c
   ${TEST_DIR}/clingo/type/cByte/get_byte_bit.c
   ${TEST_DIR}/clingo/type/cByte/set_byte_bit.c
   ${TEST_DIR}/clingo/type/cByte/toggle_byte_bit.c
   # cBytes
   ${TEST_DIR}/clingo/type/cBytes/bitand_bytes.c
   ${TEST_DIR}/clingo/type/cBytes/bitor_bytes.c
   ${TEST_DIR}/clingo/type/cBytes/compl_bytes.c
   ${TEST_DIR}/clingo/type/cBytes/get_bytes_bit.c
   ${TEST_DIR}/clingo/type/cBytes/set_bytes_bit.c
   ${TEST_DIR}/clingo/type/cBytes/set_bytes_bits.c
   ${TEST_DIR}/clingo/type/cBytes/set_odd_byte.c
   ${TEST_DIR}/clingo/type/cBytes/shift_bytes_bits.c
   ${TEST_DIR}/clingo/type/cBytes/shift_bytes.c
   ${TEST_DIR}/clingo/type/cBytes/toggle_bytes_bit.c
   ${TEST_DIR}/clingo/type/cBytes/xor_bytes.c
   # cChars
   ${TEST_DIR}/clingo/type/cChars/chars_is.c
   ${TEST_DIR}/clingo/type/cChars/cstr_is_any_char.c
   ${TEST_DIR}/clingo/type/cChars/cstr_is_char.c
   ${TEST_DIR}/clingo/type/cChars/find_any_char.c
   ${TEST_DIR}/clingo/type/cChars/trim_any_char.c
   ${TEST_DIR}/clingo/type/cChars/trim_any_char_left.c
   ${TEST_DIR}/clingo/type/cChars/trim_any_char_right.c
   ${TEST_DIR}/clingo/type/cChars/trim_char_match.c
   ${TEST_DIR}/clingo/type/cChars/trim_char_match_left.c
   ${TEST_DIR}/clingo/type/cChars/trim_char_match_right.c
   # cCharsSlice
   ${TEST_DIR}/clingo/type/cCharsSlice/chars_is_any.c
   ${TEST_DIR}/clingo/type/cCharsSlice/count_chars_slice.c
   ${TEST_DIR}/clingo/type/cCharsSlice/count_chars_slice_runes.c
   ${TEST_DIR}/clingo/type/cCharsSlice/cs.c
   ${TEST_DIR}/clingo/type/cCharsSlice/index_of_any_chars.c
   ${TEST_DIR}/clingo/type/cCharsSlice/join_chars_slice.c
   # cCharsToken
   ${TEST_DIR}/clingo/type/cCharsToken/next_token_till_any_char.c
   ${TEST_DIR}/clingo/type/cCharsToken/next_token_till_any_rune.c
   ${TEST_DIR}/clingo/type/cCharsToken/next_token_till_any.c
   ${TEST_DIR}/clingo/type/cCharsToken/next_token_till_char.c
   ${TEST_DIR}/clingo/type/cCharsToken/next_token_till_rune.c
   ${TEST_DIR}/clingo/type/cCharsToken/next_token_till.c
   ${TEST_DIR}/clingo/type/cCharsToken/token_delimiter.c
   # char
   ${TEST_DIR}/clingo/type/char/cmp_char.c
   ${TEST_DIR}/clingo/type/char/dec_char_value.c
   ${TEST_DIR}/clingo/type/char/hex_char_value.c
   ${TEST_DIR}/clingo/type/char/oct_char_value.c
   # cRange
   ${TEST_DIR}/clingo/type/cRange/clamp_into_range.c
   ${TEST_DIR}/clingo/type/cRange/closed_open_range.c
   ${TEST_DIR}/clingo/type/cRange/closed_range.c
   ${TEST_DIR}/clingo/type/cRange/cRange-in_range.c
   ${TEST_DIR}/clingo/type/cRange/eq_range.c
   ${TEST_DIR}/clingo/type/cRange/open_closed_range.c
   ${TEST_DIR}/clingo/type/cRange/open_range.c
   ${TEST_DIR}/clingo/type/cRange/range_is_valid.c
   ${TEST_DIR}/clingo/type/cRange/range_size.c
   ${TEST_DIR}/clingo/type/cRange/shift_range.c
   ${TEST_DIR}/clingo/type/cRange/sized_range.c
   # cRune
   ${TEST_DIR}/clingo/type/cRune/build_rune.c
   ${TEST_DIR}/clingo/type/cRune/ceil_to_rune.c
   ${TEST_DIR}/clingo/type/cRune/cmp_rune.c
   ${TEST_DIR}/clingo/type/cRune/count_runes.c
   ${TEST_DIR}/clingo/type/cRune/eq_rune.c
   ${TEST_DIR}/clingo/type/cRune/fill_rune_slice.c
   ${TEST_DIR}/clingo/type/cRune/find_any_rune.c
   ${TEST_DIR}/clingo/type/cRune/find_rune.c
   ${TEST_DIR}/clingo/type/cRune/floor_to_rune.c
   ${TEST_DIR}/clingo/type/cRune/is_utf8_head.c
   ${TEST_DIR}/clingo/type/cRune/is_utf8_tail.c
   ${TEST_DIR}/clingo/type/cRune/iterate_runes.c
   ${TEST_DIR}/clingo/type/cRune/left_runes.c
   ${TEST_DIR}/clingo/type/cRune/make_rune.c
   ${TEST_DIR}/clingo/type/cRune/mid_runes.c
   ${TEST_DIR}/clingo/type/cRune/next_rune.c
   ${TEST_DIR}/clingo/type/cRune/nth_rune.c
   ${TEST_DIR}/clingo/type/cRune/null_rune.c
   ${TEST_DIR}/clingo/type/cRune/right_runes.c
   ${TEST_DIR}/clingo/type/cRune/rune.c
   ${TEST_DIR}/clingo/type/cRune/rune_code.c
   ${TEST_DIR}/clingo/type/cRune/rune_is.c
   ${TEST_DIR}/clingo/type/cRune/rune_is_valid.c
   ${TEST_DIR}/clingo/type/cRune/rune_size.c
   ${TEST_DIR}/clingo/type/cRune/sub_runes.c
   ${TEST_DIR}/clingo/type/cRune/utf8_length.c
   ${TEST_DIR}/clingo/type/cRune/utf16_rune.c
   ${TEST_DIR}/clingo/type/cRune/utf16_to_utf32.c
   ${TEST_DIR}/clingo/type/cRune/utf32_rune.c
   ${TEST_DIR}/clingo/type/cRune/utf32_to_utf16.c
   # cRuneRange
   ${TEST_DIR}/clingo/type/cRuneRange/cRuneRange-overview.c
   # double
   ${TEST_DIR}/clingo/type/double/build_double.c
   ${TEST_DIR}/clingo/type/double/cmp_double.c
   ${TEST_DIR}/clingo/type/double/eq_double.c
   ${TEST_DIR}/clingo/type/double/double_info.c
   ${TEST_DIR}/clingo/type/double/double_to_float.c
   ${TEST_DIR}/clingo/type/double/pack_double.c
   ${TEST_DIR}/clingo/type/double/unpack_double.c
   # float
   ${TEST_DIR}/clingo/type/float/build_float.c
   ${TEST_DIR}/clingo/type/float/cmp_float.c
   ${TEST_DIR}/clingo/type/float/eq_float.c
   ${TEST_DIR}/clingo/type/float/float_info.c
   ${TEST_DIR}/clingo/type/float/pack_float.c
   ${TEST_DIR}/clingo/type/float/unpack_float.c
   # int16
   ${TEST_DIR}/clingo/type/int16/cmp_int16.c
   ${TEST_DIR}/clingo/type/int16/int64_to_int16.c
   ${TEST_DIR}/clingo/type/int16/swap_int16.c
   ${TEST_DIR}/clingo/type/int16/swap_int16_from.c
   ${TEST_DIR}/clingo/type/int16/swap_int16_to.c
   ${TEST_DIR}/clingo/type/int16/uint64_to_int16.c
   # int32
   ${TEST_DIR}/clingo/type/int32/cmp_int32.c
   ${TEST_DIR}/clingo/type/int32/int64_to_int32.c
   ${TEST_DIR}/clingo/type/int32/swap_int32.c
   ${TEST_DIR}/clingo/type/int32/swap_int32_from.c
   ${TEST_DIR}/clingo/type/int32/swap_int32_to.c
   ${TEST_DIR}/clingo/type/int32/uint64_to_int32.c
   # int64
   ${TEST_DIR}/clingo/type/int64/cmp_int64.c
   ${TEST_DIR}/clingo/type/int64/swap_int64.c
   ${TEST_DIR}/clingo/type/int64/swap_int64_from.c
   ${TEST_DIR}/clingo/type/int64/swap_int64_to.c
   ${TEST_DIR}/clingo/type/int64/uint64_to_int64.c
   # int8
   ${TEST_DIR}/clingo/type/int8/cmp_int8.c
   ${TEST_DIR}/clingo/type/int8/int64_to_int8.c
   ${TEST_DIR}/clingo/type/int8/uint64_to_int8.c
   # uint16
   ${TEST_DIR}/clingo/type/uint16/cmp_uint16.c
   ${TEST_DIR}/clingo/type/uint16/int64_to_uint16.c
   ${TEST_DIR}/clingo/type/uint16/swap_uint16.c
   ${TEST_DIR}/clingo/type/uint16/swap_uint16_from.c
   ${TEST_DIR}/clingo/type/uint16/swap_uint16_to.c
   ${TEST_DIR}/clingo/type/uint16/uint64_to_uint16.c
   # uint32
   ${TEST_DIR}/clingo/type/uint32/cmp_uint32.c
   ${TEST_DIR}/clingo/type/uint32/int64_to_uint32.c
   ${TEST_DIR}/clingo/type/uint32/swap_uint32.c
   ${TEST_DIR}/clingo/type/uint32/swap_uint32_from.c
   ${TEST_DIR}/clingo/type/uint32/swap_uint32_to.c
   ${TEST_DIR}/clingo/type/uint32/uint64_to_uint32.c
   # uint64
   ${TEST_DIR}/clingo/type/uint64/build_uint64.c
   ${TEST_DIR}/clingo/type/uint64/cmp_uint64.c
   ${TEST_DIR}/clingo/type/uint64/int64_to_uint64.c
   ${TEST_DIR}/clingo/type/uint64/next_pow2_uint64.c
   ${TEST_DIR}/clingo/type/uint64/swap_uint64.c
   ${TEST_DIR}/clingo/type/uint64/swap_uint64_from.c
   ${TEST_DIR}/clingo/type/uint64/swap_uint64_to.c
   # uint8
   ${TEST_DIR}/clingo/type/uint8/cmp_uint8.c
   ${TEST_DIR}/clingo/type/uint8/int64_to_uint8.c
   ${TEST_DIR}/clingo/type/uint8/uint64_to_uint8.c
)
