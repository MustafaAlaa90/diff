/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#include "common.h"


#ifdef DEVELOPMENT

int main( int argc, char* argv[] )
{
  CONSOLE_MSG(ZONE_INFO,"Hellow World! from Development");
  // CFile file;
  // file.Open("/home/mustafa/Desktop/Test/file1.txt",::fmRead);
  // std::string Time;
  // file.GetModifiedTime(Time);
  // CONSOLE_MSG(ZONE_INFO,"%s",Time.data());
  std::string file1 = "/home/mustafa/Desktop/Test/file1.txt";
  std::string file2 = "/home/mustafa/Desktop/Test/file2.txt";
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

