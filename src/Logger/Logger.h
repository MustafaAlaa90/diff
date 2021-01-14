/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#ifndef SCLLOGGER_H_
#define SCLLOGGER_H_

#include "../common.h"
#include <iostream>
#include <stdarg.h> // for va family
#include <sys/time.h>
#include <math.h>   

extern unsigned int zone;

typedef enum
{
  ZONE_ERROR     = 0x0001,
  ZONE_WARNING   = 0x0002,
  ZONE_INFO      = 0x0004,
  ZONE_FUNCTION  = 0x0008,
  ZONE_DEBUG     = 0x0010,
  ZONE_ALL       = 0xffff
} log_level_t;

/* Predefined log_levels in arrays */
#define SCL_DEBUG_ZONE_ARRAY (const char*[]){"Error",\
    "Warning", \
    "Info ", \
    "Error ", \
    "Debug", \
    "Function", \
}


void log_handler ( log_level_t level, const char* format, ... );

/**
 * @brief Macros to print on console
 */
#define CONSOLE_MSG(level, ...) do {\
    if ((level)<= zone)\
    {\
      log_handler((level),__VA_ARGS__);\
    }\
} while(0)

#endif /* SCLLOGGER_H_ */
