#ifndef CLINGO_IO_FILE_H
#define CLINGO_IO_FILE_H

#include "clingo/apidecl.h"
#include "clingo/container/CByteVec.h"
#include "clingo/io/cRecorder.h"
#include "clingo/lang/error.h"
#include "clingo/string/CString.h"
#include "clingo/type/cChars.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************

*******************************************************************************/

CLINGO_API extern cErrorType const C_FileError;

struct cFileErrorData
{
   int number;
};
typedef struct cFileErrorData cFileErrorData;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 os
*******************************************************************************/

CLINGO_API bool close_file_c( FILE* file, cErrorStack es[static 1] );

CLINGO_API inline FILE* open_file_c( cChars path,
                                     char const mode[static 1],
                                     cErrorStack es[static 1] )
{
   cVarChars buf = char_buffer_c_( 4099 );
   char const* cstrPath = make_cstr_c( buf, path );
   if ( cstrPath == NULL )
   {
      push_errno_error_c( es, ENOBUFS );
      return NULL;
   }

   FILE* file = NULL;
   int errNum = 0;
#if _WIN32
   errNum = fopen_s( &file, cstrPath, mode );
#else
   file = fopen( cstrPath, mode );
   errNum = ( file == NULL ) ? errno
                             : 0;
#endif
   if ( errNum != 0 )
   {
      push_errno_error_c( es, errNum );
   }

   return file;
}

CLINGO_API inline int remove_file_c( cChars path )
{
   cVarChars buf = char_buffer_c_( 4099 );
   char const* cstrPath = make_cstr_c( buf, path );
   if ( cstrPath == NULL )
   {
      return ENOBUFS;
   }

   return remove( cstrPath );
}

/*******************************************************************************
 state
*******************************************************************************/

CLINGO_API int64_t file_size_c( FILE* file );

/*******************************************************************************
 get and put
*******************************************************************************/

CLINGO_API bool fread_bytes_c( FILE* file, cVarBytes bytes[static 1] );

CLINGO_API bool fread_chars_c( FILE* file, cVarChars chars[static 1] );

CLINGO_API bool fwrite_bytes_c( FILE* file, cBytes bytes );

CLINGO_API bool fwrite_chars_c( FILE* file, cChars chars );

/*******************************************************************************
 util
*******************************************************************************/

CLINGO_API
cVarBytes read_binary_file_c( cChars path, cErrorStack es[static 1] );

CLINGO_API
cVarChars read_text_file_c( cChars path, cErrorStack es[static 1] );

CLINGO_API
bool write_binary_file_c( cChars path, cBytes bytes, cErrorStack es[static 1] );

CLINGO_API
bool write_text_file_c( cChars path, cChars chars, cErrorStack es[static 1] );

/*******************************************************************************
 error
*******************************************************************************/

CLINGO_API bool push_file_error_c( cErrorStack es[static 1],
                                   FILE* file );

CLINGO_API bool push_file_error_and_close_c( cErrorStack es[static 1],
                                             FILE* file );

CLINGO_API bool note_file_error_c( cRecorder rec[static 1], cError const* err );

#endif