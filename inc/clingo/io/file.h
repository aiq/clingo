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

CLINGO_API inline int open_file_c( FILE** file,
                                   cChars path,
                                   char const mode[static 1] )
{
   cVarChars buf = char_buffer_c_( 4099 );
   char const* cstrPath = make_cstr_c( buf, path );
   if ( cstrPath == NULL )
   {
      return ENOBUFS;
   }

#if _WIN32
   return fopen_s( file, cstrPath, mode );
#else
   *file = fopen( cstrPath, mode );
   return ( *file == NULL ) ? errno
                            : 0;
#endif
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

CLINGO_API inline int ferror_close_c( FILE* file )
{
   must_exist_c_( file );
   int err = ferror( file );
   fclose( file );
   return err;
}

CLINGO_API int read_binary_file_c( cChars path, cVarBytes bytes[static 1] );

CLINGO_API int read_text_file_c( cChars path, cVarChars chars[static 1] );

CLINGO_API int write_binary_file_c( cChars path, cBytes bytes );

CLINGO_API int write_text_file_c( cChars path, cChars chars );

#endif