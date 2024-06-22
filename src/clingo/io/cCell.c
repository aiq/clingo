#include "clingo/io/cCell.h"

#include "clingo/io/read_type.h"

/*******************************************************************************
********************************************************************* Functions
*******************************************************************************/

static inline bool scan_cell_internals( cScanner sca[static 1],
                                        cCell cell[static 1] )
{
   if ( read_int16_c_( sca, &cell->size ) == 0 ) // --------------------- number
      return false;

   if ( sca->space == 0 )
      return true;

   if ( not scan_char_c( sca, &cell->orient ) )
      return false;

   if ( not in_range_c_( '<', cell->orient, '>' ) )
      return false;

   if ( sca->space == 0 )
      return true;

   if ( not scan_char_c( sca, &cell->pad ) )
      return false;

   return sca->space == 0;
}

bool scan_cell_c( cScanner sca[static 1], cCell cell[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( cell );

   cell->size = 0;
   cell->orient = '<';
   cell->pad = ' ';

   cScanner backUp = *sca;

   if ( not move_if_char_c( sca, '(' ) ) // ---------------------------------- (
   {
      *sca = backUp;
      return false;
   }

   cScanner cellSca = *sca;
   if ( not move_to_char_c( sca, ')' ) )
   {
      *sca = backUp;
      return false;
   }
   cellSca.space -= sca->space;

   if ( not scan_cell_internals( &cellSca, cell ) )
   {
      *sca = backUp;
      return false;
   }

   move_scanner_c( sca, 1 ); // ---------------------------------------------- )
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

   if ( orient == '<' ) // left
   {
      return 0;
   }
   else if ( orient == '>' ) // right
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
