/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#include "common.h"


#ifdef DEVELOPMENT

int main( int argc, char* argv[] )
{
  CONSOLE_MSG(ZONE_INFO,"Hellow World! from Development");
  std::string file1 = "/home/mustafa/Desktop/test/file1";
  std::string file2 = "/home/mustafa/Desktop/test/file2";
  CDiff diff(file1,file2);
  diff.FindDiff();

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

