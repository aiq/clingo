#ifndef CLINGO_TIME_CDATE_FORMATS_H
#define CLINGO_TIME_CDATE_FORMATS_H

#include "clingo/type/char.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 date definitions
*******************************************************************************/

extern char const*const C_DateFormat;
extern char const*const C_TextDate;
extern char const*const C_IsoDate;
extern char const*const C_IsoOrdinalDate;
extern char const*const C_IsoWeekDate;
extern char const*const C_Rfc2822Date;

/*******************************************************************************
 daytime definitions
*******************************************************************************/

extern char const*const C_DaytimeFormat;
extern char const*const C_IsoDaytime;
extern char const*const C_KitchenTime;

/*******************************************************************************
 duration definitions
*******************************************************************************/

extern char const*const C_DurationFormat;

/*******************************************************************************
 time definitions
*******************************************************************************/

extern char const*const C_TimeFormat;
extern char const*const C_IsoTime;
extern char const*const C_Rfc2822Time;

extern char const*const C_AnsiCTime;
extern char const*const C_Rfc882Time;
extern char const*const C_Rfc1123Time;
extern char const*const C_Rfc3339Time;
extern char const*const C_Rfc3339TimeNano;

#endif
