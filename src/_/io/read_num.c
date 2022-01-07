#include "_/io/read_num.h"

/*******************************************************************************
 scan int values
*******************************************************************************/

#define PARSE_INT_( FuncName, CharFunc, Factor )                               \
int64_t FuncName( int64_t* n, cChars src, int64_t max, int64_t min )           \
{                                                                              \
   int64_t prev = 0;                                                           \
   int64_t tmp = 0;                                                            \
                                                                               \
   char const* itr = begin_c_( src );                                          \
   char const* end = end_c_( src );                                            \
                                                                               \
   if ( *itr == '-' )                                                          \
   {                                                                           \
      ++itr;                                                                   \
                                                                               \
      char c = CharFunc( *itr );                                               \
      while ( itr < end and c != -1 and tmp >= min )                           \
      {                                                                        \
         prev = tmp;                                                           \
         tmp = ( tmp * Factor ) - c;                                           \
         if ( tmp > prev )                                                     \
         {                                                                     \
            tmp = prev;                                                        \
            break;                                                             \
         }                                                                     \
                                                                               \
         ++itr;                                                                \
         c = CharFunc( *itr );                                                 \
      }                                                                        \
                                                                               \
      if ( tmp < min )                                                         \
      {                                                                        \
         tmp = prev;                                                           \
         --itr;                                                                \
      }                                                                        \
   }                                                                           \
   else                                                                        \
   {                                                                           \
      if ( *itr == '+' )                                                       \
      {                                                                        \
         ++itr;                                                                \
      }                                                                        \
                                                                               \
      char c = CharFunc( *itr );                                               \
      while ( itr < end and c != -1 and tmp <= max )                           \
      {                                                                        \
         prev = tmp;                                                           \
         tmp = ( tmp * Factor ) + c;                                           \
         if ( tmp < prev )                                                     \
         {                                                                     \
            tmp = prev;                                                        \
            break;                                                             \
         }                                                                     \
                                                                               \
         ++itr;                                                                \
         c = CharFunc( *itr );                                                 \
      }                                                                        \
                                                                               \
      if ( tmp > max )                                                         \
      {                                                                        \
         tmp = prev;                                                           \
         --itr;                                                                \
      }                                                                        \
   }                                                                           \
                                                                               \
   *n = tmp;                                                                   \
                                                                               \
   return itr - begin_c_( src );                                               \
}

PARSE_INT_( parse_dec_int64_c, dec_char_value_c, 10 )

PARSE_INT_( parse_hex_int64_c, hex_char_value_c, 16 )

PARSE_INT_( parse_oct_int64_c, oct_char_value_c, 8 )

int64_t parse_int64_c( int64_t* n,
                       char const format[static 1],
                       cChars src,
                       int64_t max,
                       int64_t min )
{
   if ( *format == '\0' or cstr_is_char_c( format, 'd' ) )
   {
      return parse_dec_int64_c( n, src, max, min );
   }
   else if ( cstr_is_any_char_c_( format, "xX" ) )
   {
      return parse_hex_int64_c( n, src, max, min );
   }
   else if ( cstr_is_char_c( format, 'o' ) )
   {
      return parse_oct_int64_c( n, src, max, min );
   }
   else
   {
      return -1;
   }

   return 0;
}

/*******************************************************************************
 scan uint values
*******************************************************************************/

#define PARSE_UINT_( FuncName, CharFunc, Factor )                              \
int64_t FuncName( uint64_t* n, cChars src, uint64_t max )                      \
{                                                                              \
   uint64_t prev = 0;                                                          \
   uint64_t tmp = 0;                                                           \
                                                                               \
   char const* itr = begin_c_( src );                                          \
   char const* end = end_c_( src );                                            \
                                                                               \
   char c = CharFunc( *itr );                                                  \
   while ( itr < end and c != -1 and tmp <= max )                              \
   {                                                                           \
      prev = tmp;                                                              \
      tmp = ( tmp * Factor ) + (uint64_t)c;                                    \
      if ( tmp < prev )                                                        \
      {                                                                        \
         tmp = prev;                                                           \
         break;                                                                \
      }                                                                        \
                                                                               \
      ++itr;                                                                   \
      c = CharFunc( *itr );                                                    \
   }                                                                           \
                                                                               \
   if ( tmp > max )                                                            \
   {                                                                           \
      tmp = prev;                                                              \
      --itr;                                                                   \
   }                                                                           \
                                                                               \
   *n = tmp;                                                                   \
                                                                               \
   return itr - begin_c_( src );                                               \
}

PARSE_UINT_( parse_dec_uint64_c, dec_char_value_c, 10 )

PARSE_UINT_( parse_hex_uint64_c, hex_char_value_c, 16 )

PARSE_UINT_( parse_oct_uint64_c, oct_char_value_c, 8 )

int64_t parse_uint64_c( uint64_t* n,
                        char const format[static 1],
                        cChars src,
                        uint64_t max )
{
   if ( *format == '\0' or cstr_is_char_c( format, 'd' ) )
   {
      return parse_dec_uint64_c( n, src, max );
   }
   else if ( cstr_is_any_char_c_( format, "xX" ) )
   {
      return parse_hex_uint64_c( n, src, max );
   }
   else if ( cstr_is_char_c( format, 'o' ) )
   {
      return parse_oct_uint64_c( n, src, max );
   }
   else
   {
      return -1;
   }

   return 0;
}

/*******************************************************************************
 scan float values
*******************************************************************************/

static inline const char* dec_pre_part( double* d,
                                        const char* itr,
                                        const char* end )
{
   double tmp = *d;

   char c = dec_char_value_c( *itr );
   while ( itr < end and c != -1 )
   {
      tmp = ( tmp * 10 ) + c;

      ++itr;
      c = dec_char_value_c( *itr );
   }

   *d = tmp;
   return itr;
}

static inline const char* dec_post_part( double* d,
                                         const char* itr,
                                         const char* end )
{
   double tmp = *d;

   double factor = 0.1;

   char c = dec_char_value_c( *itr );
   while ( itr < end and c != -1 )
   {
      tmp = tmp  + ( factor * c );
      factor = factor / 10.0;

      ++itr;
      c = dec_char_value_c( *itr );
   }

   *d = tmp;
   return itr;
}

static inline const char* dec_exp_part( double* d,
                                        const char* itr,
                                        const char* end )
{
   double tmp = *d;

   bool negativeExp = ( *itr == '-' );
   if ( negativeExp or *itr == '+' )
   {
      ++itr;
   }
   else
   {
      return itr;
   }
   double expValue = 0.0;
   char c = dec_char_value_c( *itr );
   while ( c != -1 )
   {
      expValue = ( expValue * 10 ) + c;

      ++itr;
      c = dec_char_value_c( *itr );
   }

   if ( negativeExp )
   {
      while ( negativeExp )
      {
         tmp = tmp / 10;
         --negativeExp;
      }
   }
   else
   {
      while ( negativeExp )
      {
         tmp = tmp * 10;
         --negativeExp;
      }
   }

   *d = tmp;
   return itr;
}

/******************************************************************************/

int64_t parse_dec_double_c( double* d, cChars src )
{
   double tmp = 0.0;

   const char* itr = begin_c_( src );
   const char* end = end_c_( src );

   bool negative = ( *itr == '-' );
   if ( negative or *itr == '+' )
   {
      ++itr;
   }

   itr = dec_pre_part( &tmp, itr, end );
   
   if ( itr < end and *itr == '.' )
   {
      ++itr;
      itr = dec_post_part( &tmp, itr, end );
   }

   if ( itr < end and ( *itr == 'e' or *itr == 'E' ) )
   {
      ++itr;

      itr = dec_exp_part( &tmp, itr, end );
   }

   *d = negative ? -tmp
                 : tmp;

   return itr - begin_c_( src );                                               \
}
