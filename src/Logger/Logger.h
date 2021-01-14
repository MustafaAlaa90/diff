/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#ifndef SCLLOGGER_H_
#define SCLLOGGER_H_

#include <iostream>
#include <stdarg.h> // for va family
#include <sys/time.h>
#include <math.h>   

typedef enum
{
  ZONE_ERROR     = 0x0001,
  ZONE_WARNING   = 0x0002,
  ZONE_INFO      = 0x0004,
  ZONE_TRACE     = 0x0008,
  ZONE_INIT      = 0x0010,
  ZONE_FUNCTION  = 0x0020,
  ZONE_DEBUG     = 0x0040,
  ZONE_CTOR      = 0x0080,
  ZONE_DATA      = 0x0100,
  ZONE_DATA1     = 0x0200,
  ZONE_DATA2     = 0x0400,
  ZONE_DATA3     = 0x0800,
  ZONE_DATA4     = 0x1000,
  ZONE_DATA5     = 0x2000,
  ZONE_SQUIRREL  = 0x4000,
  ZONE_DEBUG_CONSOLE = 0x8000,
  ZONE_ALL       = 0xffff
} log_level_t;

/* Predefined log_levels in arrays */
#define SCL_DEBUG_ZONE_ARRAY (const char*[]){"Error",\
    "Warning", \
    "Info ", \
    "Trace", \
    "Init", \
    "Debug", \
    "Function", \
    "ctor", \
    "Data", \
    "Data1", \
    "Data2", \
    "Data3", \
    "Data4", \
    "Data5", \
    "Squirrel", \
    "DebugConsole", \
}

#define MAX_CONSOLE_LEVEL ZONE_INFO
#define SCL_MODULE_NAME "SCL"
void log_handler ( log_level_t level, const char* format, ... );

#define SYS_TRACE(mask, trace) do{std::cout<< trace;}while(0);

/**
 * @brief Macros to check invalid reference and debug trace to logger.
 */
#define CONSOLE_ERR_CHK_NULL_RET(ptr) {if(!ptr){\
    CONSOLE_MSG(ZONE_ERROR, "[%s][%s()][%d] Invalid reference", __FILE__, __FUNCTION__, __LINE__);\
    return 0;}\
}
#define CONSOLE_ERR_CHK_NULL_RET_NONE(ptr) {if(!ptr){\
    CONSOLE_MSG(ZONE_ERROR, "[%s][%s()][%d] Invalid reference", __FILE__, __FUNCTION__, __LINE__);\
    }\
}
#define CONSOLE_ERR_CHK_NULL_RET_VAL(ptr, val) {if(!ptr){\
    CONSOLE_MSG(ZONE_ERROR, "[%s][%s()][%d] Invalid reference", __FILE__, __FUNCTION__, __LINE__);\
    return val;}\
}

/**
 * @brief Macros to check conditions and debug trace to logger.
 */
#define CONSOLE_ASSERT_COND_RET(ret, dbgStr) {if(!ret){\
    CONSOLE_MSG(ZONE_ERROR, "%s",dbgStr);\
    return 0;}\
}

/**
 * @brief Macros to print on console
 */
#define CONSOLE_MSG(level, ...) do {\
    if ((level)<= MAX_CONSOLE_LEVEL)\
    {\
      log_handler((level),__VA_ARGS__);\
    }\
} while(0)

#endif /* SCLLOGGER_H_ */
