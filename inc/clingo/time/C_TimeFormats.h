#ifndef CLINGO_TIME_CDATEFORMATS_H
#define CLINGO_TIME_CDATEFORMATS_H

#include "clingo/apidecl.h"
#include "clingo/type/char.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 date definitions
*******************************************************************************/

CLINGO_API extern char const*const C_DateFormat;
CLINGO_API extern char const*const C_TextDate;
CLINGO_API extern char const*const C_IsoDate;
CLINGO_API extern char const*const C_IsoOrdinalDate;
CLINGO_API extern char const*const C_IsoWeekDate;
CLINGO_API extern char const*const C_Rfc2822Date;

/*******************************************************************************
 daytime definitions
*******************************************************************************/

CLINGO_API extern char const*const C_DaytimeFormat;
CLINGO_API extern char const*const C_IsoDaytime;
CLINGO_API extern char const*const C_KitchenTime;

/*******************************************************************************
 duration definitions
*******************************************************************************/

CLINGO_API extern char const*const C_DurationFormat;

/*******************************************************************************
 time definitions
*******************************************************************************/

CLINGO_API extern char const*const C_TimeFormat;
CLINGO_API extern char const*const C_IsoTime;
CLINGO_API extern char const*const C_Rfc2822Time;

CLINGO_API extern char const*const C_AnsiCTime;
CLINGO_API extern char const*const C_Rfc882Time;
CLINGO_API extern char const*const C_Rfc1123Time;
CLINGO_API extern char const*const C_Rfc3339Time;
CLINGO_API extern char const*const C_Rfc3339TimeNano;

#endif
