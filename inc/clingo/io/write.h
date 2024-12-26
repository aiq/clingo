#ifndef CLINGO_IO_WRITE_H
#define CLINGO_IO_WRITE_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/io/cTape.h"
#include "clingo/lang/func.h"

/*******************************************************************************
********************************************************* Types and Definitions
**+*****************************************************************************
 Definitions
*******************************************************************************/

union cVaArg
{
   int8_t i8;
   int16_t i16;
   int32_t i32;
   int64_t i64;
   uint8_t u8;
   uint16_t u16;
   uint32_t u32;
   uint64_t u64;
   float f;
   double d;
   cByte b;
   char c;
   cError const* e;
   cRune r;
   bool bool_;
   cRange rng;
   char const* s;
   cBytes bs;
   cChars cs;
   cRecorder const* rec;
   cScanner const* sca;
   cTape t;
};

typedef union cVaArg cVaArg;

typedef bool ( *c_get_va_arg )( va_list* list,
                                cChars type,
                                cVaArg arg[static 1] );

typedef bool ( *c_write_va_arg )( cRecorder rec[static 1],
                                  cChars type,
                                  cVaArg arg,
                                  char const fmt[static 1] );

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

CLINGO_API bool get_va_arg_c( va_list* list, cChars type, cVaArg arg[static 1] );

CLINGO_API bool write_va_arg_c( cRecorder rec[static 1],
                                cChars type,
                                cVaArg arg,
                                char const fmt[static 1] );

/*******************************************************************************
 write
*******************************************************************************/

CLINGO_API bool write_impl_c( cRecorder rec[static 1],
                              c_get_va_arg getArgFunc,
                              c_write_va_arg writeArgFunc,
                              int n,
                              va_list list );

CLINGO_API bool write_list_c( cRecorder rec[static 1], int n, va_list list );

#define write_c_( Rec, ... )                                                   \
   write_c( (Rec), nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API bool write_c( cRecorder rec[static 1], int n, ... );

/*******************************************************************************
 writeln
*******************************************************************************/

CLINGO_API bool writeln_impl_c( cRecorder rec[static 1],
                                c_get_va_arg getArgFunc,
                                c_write_va_arg writeArgFunc,
                                int n,
                                va_list list );

CLINGO_API bool writeln_list_c( cRecorder rec[static 1], int n, va_list list );

#define writeln_c_( Rec, ... )                                                 \
   writeln_c( (Rec), nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API bool writeln_c( cRecorder rec[static 1], int n, ... );

#endif
