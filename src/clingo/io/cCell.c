#include "clingo/io/cCell.h"

#include "clingo/io/read_type.h"

/*******************************************************************************
********************************************************************* Functions
*******************************************************************************/

bool read_in_cell_c( cScanner sca[static 1], cCell cell[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( cell );

   cell->size = 0;
   cell->orient = -1;
   cell->pad = ' ';

   cScanner backUp = *sca;

   if ( not move_if_char_c( sca, '(' ) ) // ---------------------------------- (
   {
      *sca = backUp;
      return false;
   }

   if ( read_int16_c_( sca, &cell->size ) == 0 ) // --------------------- number
   {
      *sca = backUp;
      return false;
   }

   bool readOrient = sca->space > 0; // --------------------------------- orient
   if ( readOrient )
   {
      const char* ptr = sca->mem;
      if ( *ptr == 'l' )
      {
         cell->orient = -1;
         move_scanner_c( sca, 1 );
      }
      else if ( *ptr == 'r' )
      {
         cell->orient = 1;
         move_scanner_c( sca, 1 );
      }
      else if ( *ptr == 'c' )
      {
         cell->orient = 0;
         move_scanner_c( sca, 1 );
      }
      else // no orient value
      {
         readOrient = false;
      }
   }
   if ( not readOrient )
   {
      *sca = backUp;
      return false;
   }

   if ( sca->space > 0 ) // ------------------------------------------------ pad
   {
      scan_char_c( sca, &cell->pad );
   }
   else
   {
      *sca = backUp;
      return false;
   }

   if ( not move_if_char_c( sca, ')' ) ) // ---------------------------------- )
   {
      *sca = backUp;
      return false;
   }

   return true;
}

/**********************************************************/

static inline int64_t left_space( int64_t space,
                                  int8_t orient,
                                  int64_t size )
{
   if ( space < size )
   {
      return 0;
   }

   if ( orient < 0 ) // left
   {
      return 0;
   }
   else if ( orient > 0 ) // right
   {
      return space -size;
   }
   else // center
   {
      return ( space >> 1 ) - ( size >> 1);
   }
}

static inline int64_t right_space( int64_t space,
                                   int8_t orient,
                                   int64_t size )
{
   int64_t leftSpace = left_space( space, orient, size );

   return space - ( leftSpace + size );
}

/**********************************************************/

bool write_ascii_into_cell_c( cRecorder rec[static 1],
                              cChars ascii,
                              cCell const cell[static 1] )
{
   must_exist_c_( cell );
   must_exist_c_( rec );

   if ( cell->size > rec->space )
   {
      return false;
   }

   if ( cell->size < ascii.s )
   {
      ascii.s = cell->size;
      return record_chars_c( rec, ascii );
   }

   bool res = true;

   int64_t const leftSpace = left_space( cell->size, cell->orient, ascii.s );
   if ( leftSpace > 0 )
   {
      res &= record_pad_c( rec, cell->pad, leftSpace );
   }

   res &= record_chars_c( rec, ascii );

   int64_t const rightSpace = right_space( cell->size, cell->orient, ascii.s );
   if ( rightSpace > 0 )
   {
      res &= record_pad_c( rec, cell->pad, rightSpace );
   }

   return res;
}


