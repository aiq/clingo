#ifndef CLINGO_IO_CCELL_H
#define CLINGO_IO_CCELL_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct cCell
{
   int16_t size;
   int8_t orient;
   char pad;
};
typedef struct cCell cCell;

/*******************************************************************************
********************************************************************* Functions
*******************************************************************************/

#define cell_c_( Size, Orient, Pad )                                           \
(                                                                              \
   (cCell){ .size=(Size), .orient=(Orient), .pad=(Pad) }                       \
)

CLINGO_API
bool read_in_cell_c( cScanner sca[static 1], cCell cell[static 1] );

CLINGO_API
bool write_ascii_into_cell_c( cRecorder rec[static 1],
                              cChars ascii,
                              cCell const cell[static 1] );

#endif
