/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#include "Logger.h"

//-----------------------------------------------------------------------------
static const char* SclGetDebugZoneName ( unsigned long int zoneIndex )
{
  int i = 0;
  if ( zoneIndex == ZONE_ALL )
  {
    return "ALL";
  }
  for ( ; i < 15; i++ )
  {
    if ( zoneIndex & ( 1 << i ) )
    {
      break;
    }
  }
  return SCL_DEBUG_ZONE_ARRAY[i];
}
//----------------------------------------------------------------------------
static std::string GetTime( )
{
  time_t rawtime;
  struct tm* timeinfo;
  std::string Time;
  time( &rawtime );
  timeinfo = localtime( &rawtime );
  strftime( ( char* )Time.data(), 64, "%H:%M:%S", timeinfo );
  return Time;

}
//-----------------------------------------------------------------------------
void log_handler ( log_level_t level, const char* format, ... )
{
  const char* zoneName = SclGetDebugZoneName( level );

  va_list ap;
  va_start( ap, format );
  printf( "%s | ",GetTime().data() );
  printf( "%c | ", zoneName[0] );
  vfprintf( stdout, format, ap );
  vfprintf( stdout, "\n", ap );
  va_end( ap );
  fflush( stdout );
}
