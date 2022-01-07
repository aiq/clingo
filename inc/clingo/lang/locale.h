#ifndef CLINGO_LANG_LOCALE_H
#define CLINGO_LANG_LOCALE_H

#include "clingo/type/cChars.h"

#include <locale.h>
#include <stdio.h>

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define locale_name_buffer_c_()                                                \
   char_buffer_c_( 128 )

/*******************************************************************************
 overall
*******************************************************************************/

#define change_locale_c_( Cat, Name )                                          \
   change_locale_c( (Cat), (Name), locale_name_buffer_c_() )
char* change_locale_c( int category,
                       char const name[static 1],
                       cVarChars buf );

int fprint_locale_c( FILE* output );

#define get_locale_c_( Cat )                                                   \
   get_locale_c( (Cat), locale_name_buffer_c_() )
inline char* get_locale_c( int category, cVarChars buf )
{
   char const* curr = setlocale( category, NULL );
   if ( !curr ) return NULL;

   return make_cstr_c_( buf, curr );
}

inline bool set_locale_c( int category, char const name[static 1] )
{
   return setlocale( category, name ) != NULL;
}

int print_locale_c( void );

#endif
