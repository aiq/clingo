#include "clingo/lang/locale.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

static bool fpcstr( FILE* output,
                    char const name[static 1],
                    char const val[static 1],
                    int n[static 1] )
{
   int const tmp = fprintf( output, ".%s=\"%s\", ", name, val );
   if ( n < 0 ) return false;

   *n += tmp;
   return true;
}

static bool fpchar( FILE* output,
                    char const name[static 1],
                    char val,
                    int n[static 1] )
{
   int const tmp = fprintf( output, ".%s=%d, ", name, val );
   if ( n < 0 ) return false;

   *n += tmp;
   return true;
}

static bool fplast( FILE* output,
                    char const name[static 1],
                    char val,
                    int n[static 1] )
{
   int const tmp = fprintf( output, ".%s=%d ", name, val );
   if ( n < 0 ) return false;

   *n += tmp;
   return true;
}

static bool fp( FILE* output, char const cstr[static 1], int n[static 1] )
{
   int const tmp = fprintf( output, "%s", cstr );
   if ( n < 0 ) return false;

   *n += tmp;
   return true;
}

/*******************************************************************************

*******************************************************************************/

char* change_locale_c( int category,
                       char const name[static 1],
                       cVarChars buf )
{
   char* old = get_locale_c( category, buf );
   return set_locale_c( category, name ) ? old
                                         : NULL;
}

int fprint_locale_c( FILE* output )
{
   struct lconv* l = localeconv();

   int n = 0;
   if ( fp( output, "{ ", &n ) and
        fpcstr( output, "decimal_point", l->decimal_point, &n ) and
        fpcstr( output, "thousands_sep", l->thousands_sep, &n ) and
        fpcstr( output, "groupint", l->grouping, &n ) and
        fpcstr( output, "int_curr_symbol", l->int_curr_symbol, &n ) and
        fpcstr( output, "currency_symbol", l->currency_symbol, &n ) and
        fpcstr( output, "mon_decimal_point", l->mon_decimal_point, &n ) and
        fpcstr( output, "mon_thousands_sep", l->mon_thousands_sep, &n ) and
        fpcstr( output, "mon_grouping", l->mon_grouping, &n ) and
        fpcstr( output, "positive_sign", l->positive_sign, &n ) and
        fpcstr( output, "negative_sign", l->negative_sign, &n ) and
        fpchar( output, "frac_digits", l->frac_digits, &n ) and
        fpchar( output, "p_cs_precedes", l->p_cs_precedes, &n ) and
        fpchar( output, "n_cs_precedes", l->n_cs_precedes, &n ) and
        fpchar( output, "p_sep_by_space", l->p_sep_by_space, &n ) and
        fpchar( output, "n_sep_by_space", l->n_sep_by_space, &n ) and
        fpchar( output, "p_sign_posn", l->p_sign_posn, &n ) and
#if _WIN32
        fplast( output, "n_sign_posn", l->n_sign_posn, &n ) and
#else
        fpchar( output, "n_sign_posn", l->n_sign_posn, &n ) and
        fpchar( output, "int_frac_digits", l->int_frac_digits, &n ) and
        fpchar( output, "int_p_cs_precedes", l->int_p_cs_precedes, &n ) and
        fpchar( output, "int_n_cs_precedes", l->int_n_cs_precedes, &n ) and
        fpchar( output, "int_p_sep_by_space", l->int_p_sep_by_space, &n ) and
        fpchar( output, "int_n_sep_by_space", l->int_n_sep_by_space, &n ) and
        fpchar( output, "int_p_sign_posn", l->int_p_sign_posn, &n ) and
        fplast( output, "int_n_sign_posn", l->int_n_sign_posn, &n ) and
#endif
        fp( output, "}", &n ) )
   {
      return n;
   }

   return -1;
}

extern inline char* get_locale_c( int category, cVarChars buf );

extern inline bool set_locale_c( int category, char const name[static 1] );

int print_locale_c( void )
{
   return fprint_locale_c( stdout );
}
