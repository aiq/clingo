
################################################################################
# SRC_FILES
################################################################################
set( SRC_FILES
   ${SRC_DIR}/clingo/requirements.c
)
aux_source_directory( ${SRC_DIR}/clingo/color SRC_FILES )
aux_source_directory( ${SRC_DIR}/clingo/container SRC_FILES )
aux_source_directory( ${SRC_DIR}/clingo/io SRC_FILES )
aux_source_directory( ${SRC_DIR}/clingo/io/_ SRC_FILES )
aux_source_directory( ${SRC_DIR}/clingo/lang SRC_FILES )
aux_source_directory( ${SRC_DIR}/clingo/string SRC_FILES )
aux_source_directory( ${SRC_DIR}/clingo/time SRC_FILES )
aux_source_directory( ${SRC_DIR}/clingo/time/_ SRC_FILES )
aux_source_directory( ${SRC_DIR}/clingo/type SRC_FILES )

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
)

## color
aux_source_directory( ${TEST_DIR}/clingo/color/cCmyk TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/color/cColor TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/color/cP3Builder TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/color/cRgb24 TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/color/image TEST_FILES )

## container
aux_source_directory( ${TEST_DIR}/clingo/container/CBitVec TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/container/CByteVec TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/container/CInt64Map TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/container/CInt64Vec TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/container/CObjectVec TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/container/map TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/container/pile TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/container/set TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/container/vec TEST_FILES )

## io
aux_source_directory( ${TEST_DIR}/clingo/io/cCell TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/io/cRecorder TEST_FILES )
list( REMOVE_ITEM TEST_FILES ${TEST_DIR}/clingo/io/cRecorder/record_double.c )
list( REMOVE_ITEM TEST_FILES ${TEST_DIR}/clingo/io/cRecorder/record_float.c )
aux_source_directory( ${TEST_DIR}/clingo/io/cScanner TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/io/cTape TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/io/FILE TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/io/fwrite TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/io/jot TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/io/print TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/io/read TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/io/read_type TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/io/write TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/io/write_type TEST_FILES )

## lang
aux_source_directory( ${TEST_DIR}/clingo/lang/algo TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/lang/chunk TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/lang/CObject TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/lang/error TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/lang/error_type TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/lang/expect TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/lang/func TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/lang/math TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/lang/slice TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/lang/window TEST_FILES )

## string
aux_source_directory( ${TEST_DIR}/clingo/string/CDictionary TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/string/CString TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/string/CStringList TEST_FILES )

## time
aux_source_directory( ${TEST_DIR}/clingo/time/C_TimeFormats TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/c_Month TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/c_Weekday TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cDate TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cDatePeriod TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/CDaySet TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cDaytime TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cDuration TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cHmsn TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cMonthDay TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cOrdinalDate TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cTime TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cTzOffset TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cWeekDate TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/cYmd TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/time/year TEST_FILES )

## type
aux_source_directory( ${TEST_DIR}/clingo/type/bool TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/c_ByteOrder TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/cByte TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/cBytes TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/cChars TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/cCharsSlice TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/cCharsToken TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/char TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/cRange TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/cRune TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/cRuneRange TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/double TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/float TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/int16 TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/int32 TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/int64 TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/int8 TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/uint16 TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/uint32 TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/uint64 TEST_FILES )
aux_source_directory( ${TEST_DIR}/clingo/type/uint8 TEST_FILES )
