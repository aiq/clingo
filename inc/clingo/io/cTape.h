#ifndef CLINGO_IO_CTAPE_H
#define CLINGO_IO_CTAPE_H

#include "clingo/io/cRecorder.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

#define TAPE_C_( FuncName, Type, WriteFunc, DoDeref )                          \
bool FuncName( cRecorder rec[static 1],                                        \
               void const* i,                                                  \
               char const fmt[static 1] )                                      \
{                                                                              \
   must_exist_c_( i );                                                         \
   Type const* val = i;                                                        \
   return WriteFunc( rec, DoDeref( val ), fmt );                               \
}

#define tape_c_( Rec, Tape, Fmt )                                              \
   (Tape).f( (Rec), (Tape).i, (Fmt) )

typedef bool ( *c_tape )( cRecorder rec[static 1],
                          void const* i,
                          char const fmt[static 1] );

struct cTape
{
   void const* i;
   c_tape f;
};
typedef struct cTape cTape;

#endif