/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#include "common.h"


#ifdef DEVELOPMENT

int main( int argc, char* argv[] )
{
  CONSOLE_MSG(ZONE_INFO,"Hellow World! from Development");
  return 0;
}

#endif

#ifdef UTEST
int main( int argc, char* argv[] )
{
  CONSOLE_MSG(ZONE_INFO,"Hellow World! from UTest");
  return 0;
}

#endif
