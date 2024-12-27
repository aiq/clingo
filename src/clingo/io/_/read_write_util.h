#ifndef CLINGO_IO_INTERN_READ_WRITE_UTIL_H
#define CLINGO_IO_INTERN_READ_WRITE_UTIL_H

#include "clingo/io/cScanner.h"
#include "clingo/type/char.h"

/*******************************************************************************
********************************************************* Types and Definitions
**+*****************************************************************************
 Definitions
*******************************************************************************/

#define cMaxSpecifierFormatLength_ 32

/*******************************************************************************
******************************************************************* cReadCommand
*******************************************************************************/

struct cReadCommand
{
   char type;
   char op;
   union
   {
      char func;
      cChars set;
      cRuneRange range;
   };
};
typedef struct cReadCommand cReadCommand;

bool eq_read_command_c( cReadCommand const a[static 1],
                        cReadCommand const b[static 1] );

bool handle_read_command_c( cScanner sca[static 1],
                            cReadCommand const cmd[static 1] );

bool read_in_read_command_c( cScanner sca[static 1],
                             cReadCommand cmd[static 1] );

bool read_in_rune_range_c( cScanner sca[static 1],
                           cRuneRange range[static 1] );

void reset_read_command_c( cReadCommand cmd[static 1] );

/*******************************************************************************
***************************************************************** cReadSpecifier
*******************************************************************************/

struct cReadSpecifier
{
   bool withDst;
   cChars type;
   char fmt[ cMaxSpecifierFormatLength_+1 ];
};
typedef struct cReadSpecifier cReadSpecifier;

bool read_in_till_end_c( cScanner sca[static 1], cChars dst[static 1] );

bool read_in_read_specifier_c( cScanner sca[static 1],
                               cReadSpecifier spec[static 1] );

void reset_read_specifier_c( cReadSpecifier spec[static 1] );

/*******************************************************************************
**************************************************************** cWriteSpecifier
*******************************************************************************/

struct cWriteSpecifier
{
   bool filled;
   cChars type;
   char fmt[ cMaxSpecifierFormatLength_+1 ];
};
typedef struct cWriteSpecifier cWriteSpecifier;

bool read_in_write_specifier_c( cScanner sca[static 1],
                                cWriteSpecifier spec[static 1] );

void reset_write_specifier_c( cWriteSpecifier spec[static 1] );

#endif
