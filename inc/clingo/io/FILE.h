#ifndef CLINGO_IO_FILE_H
#define CLINGO_IO_FILE_H

#include "clingo/apidecl.h"
#include "clingo/container/CByteVec.h"
#include "clingo/io/cRecorder.h"
#include "clingo/lang/error_type.h"
#include "clingo/string/CString.h"
#include "clingo/type/cChars.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************

*******************************************************************************/

CLINGO_API extern cErrorType const C_InvalidValueError;

CLINGO_API extern cErrorType const C_Eof;

CLINGO_API extern cErrorType const C_UnexpectedEof;

CLINGO_API extern cErrorType const C_FileError;

struct cFileError
{
   int number;
};
typedef struct cFileError cFileError;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 os
*******************************************************************************/

CLINGO_API bool close_file_c( FILE* file, cErrorStack es[static 1] );

#define open_file_c_( Path, Mode, Es )                                         \
   open_file_c( c_c( Path ), (Mode), (Es) )
CLINGO_API inline FILE* open_file_c( cChars path,
                                     char const mode[static 1],
                                     cErrorStack es[static 1] )
{
   cVarChars buf = var_chars_c_( 4099 );
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

#define remove_file_c_( Path, Es )                                             \
   remove_file_c( c_c( Path ), (Es) )
CLINGO_API inline bool remove_file_c( cChars path, cErrorStack es[static 1] )
{
   cVarChars buf = var_chars_c_( 4099 );
   char const* cstrPath = make_cstr_c( buf, path );
   if ( cstrPath == NULL )
   {
      return push_errno_error_c( es, ENOBUFS );
   }

   int errc = remove( cstrPath );
   if ( errc != 0 )
   {
      return push_errno_error_c( es, errc );
   }

   return true;
}

#define ropen_file_c_( Path, Es )                                              \
   ropen_file_c( c_c( Path ), (Es) )
CLINGO_API inline FILE* ropen_file_c( cChars path, cErrorStack es[static 1] )
{
   return open_file_c( path, "rb", es );
}

#define wopen_file_c_( Path, Es )                                              \
   wopen_file_c( c_c( Path ), (Es) )
CLINGO_API inline FILE* wopen_file_c( cChars path, cErrorStack es[static 1] )
{
   return open_file_c( path, "wb", es );
}

/*******************************************************************************
 state
*******************************************************************************/

CLINGO_API int64_t file_size_c( FILE* file );

/*******************************************************************************
 func structs
*******************************************************************************/

CLINGO_API cOutput file_output_c( FILE* file );

CLINGO_API cPen file_pen_c( FILE* file );

/*******************************************************************************
 fread
*******************************************************************************/

CLINGO_API bool fget_bytes_c( FILE* file, cVarBytes buf[static 1] );

CLINGO_API bool fget_chars_c( FILE* file, cVarChars buf[static 1] );

CLINGO_API bool fget_line_c( FILE* file,
                             int32_t n,
                             cVarChars buf[static 1],
                             bool fin[static 1] );

/*******************************************************************************
 fput
*******************************************************************************/

CLINGO_API bool fput_bytes_c( FILE* file, cBytes bytes );

CLINGO_API bool fput_chars_c( FILE* file, cChars chars );

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

CLINGO_API bool push_invalid_value_error_c( cErrorStack es[static 1],
                                            char const name[static 1] );

CLINGO_API bool push_file_error_c( cErrorStack es[static 1],
                                   FILE* file );

#endif