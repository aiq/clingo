#ifndef CLINGO_IO_INTERN_CVAARG_H
#define CLINGO_IO_INTERN_CVAARG_H

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

bool write_impl_c( cRecorder rec[static 1],
                   int n,
                   va_list list );

bool writeln_impl_c( cRecorder rec[static 1],
                     int n,
                     va_list list );

bool fwrite_impl_c( FILE* file,
                    cErrorStack es[static 1],
                    int n,
                    va_list list );


bool fwriteln_impl_c( FILE* file,
                      cErrorStack es[static 1],
                      int n,
                      va_list list );

#endif