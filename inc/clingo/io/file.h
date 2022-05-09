#ifndef CLINGO_IO_FILE_H
#define CLINGO_IO_FILE_H

#include "clingo/apidecl.h"
#include "clingo/container/CByteVec.h"
#include "clingo/io/cRecorder.h"
#include "clingo/string/CString.h"
#include "clingo/type/cChars.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 os
*******************************************************************************/

CLINGO_API inline FILE* open_file_c( cChars path, char const mode[static 1] )
{
   cVarChars buf = char_buffer_c_( 4099 );
   char const* cstrPath = make_cstr_c( buf, path );
   if ( cstrPath == NULL )
   {
      return NULL;
   }

   return fopen( cstrPath, mode );
}

CLINGO_API inline bool remove_file_c( cChars path )
{
   cVarChars buf = char_buffer_c_( 4099 );
   char const* cstrPath = make_cstr_c( buf, path );
   if ( cstrPath == NULL )
   {
      return NULL;
   }

   return remove( cstrPath ) == 0;
}

/*******************************************************************************
 state
*******************************************************************************/

CLINGO_API int64_t file_size_c( FILE* file );

/*******************************************************************************
 get and put
*******************************************************************************/

CLINGO_API bool get_file_bytes_c( FILE* file, cVarBytes bytes[static 1] );

CLINGO_API bool get_file_chars_c( FILE* file, cVarChars chars[static 1] );

CLINGO_API bool put_file_bytes_c( FILE* file, cBytes bytes );

CLINGO_API bool put_file_chars_c( FILE* file, cChars chars );

/*******************************************************************************
 util
*******************************************************************************/

CLINGO_API cVarBytes read_binary_file_c( cChars path );

CLINGO_API cVarChars read_text_file_c( cChars path );

CLINGO_API bool write_binary_file_c( cChars path, cBytes bytes );

CLINGO_API bool write_text_file_c( cChars path, cChars chars );

#endif