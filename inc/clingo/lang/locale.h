#ifndef CLINGO_LANG_LOCALE_H
#define CLINGO_LANG_LOCALE_H

#include <locale.h>
#include <stdio.h>

#include "clingo/apidecl.h"
#include "clingo/type/cChars.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define locale_name_buffer_c_()                                                \
   var_chars_c_( 128 )

/*******************************************************************************
 overall
*******************************************************************************/

#define change_locale_c_( Cat, Name )                                          \
   change_locale_c( (Cat), (Name), locale_name_buffer_c_() )
CLINGO_API
char* change_locale_c( int category,
                       char const name[static 1],
                       cVarChars buf );

CLINGO_API
int fprint_locale_c( FILE* output );

#define get_locale_c_( Cat )                                                   \
   get_locale_c( (Cat), locale_name_buffer_c_() )
CLINGO_API
inline char* get_locale_c( int category, cVarChars buf )
{
   char const* curr = setlocale( category, NULL );
   if ( !curr ) return NULL;

   return make_cstr_c_( buf, curr );
}

CLINGO_API
inline bool set_locale_c( int category, char const name[static 1] )
{
   return setlocale( category, name ) != NULL;
}

CLINGO_API
int print_locale_c( void );

#endif
