/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#include "common.h"
unsigned int zone;

#ifdef DEVELOPMENT
void printUsage()
{
  printf( "Usage:\n" );
  printf( "diff_app [file1path1] [filepath2] -o [outfilepath] -l [Logger Level]   - Detect the difference between file1path1 and file1path2\n");
  printf( "compare filepath2 with respect to filepath1 and print the out to outfilepath\n" );
  printf( "diff_app [file1path1] [filepath2]                    - Detect the difference between file1path1 and file1path2\n");
  printf( "compare filepath2 with respect to filepath1 and print the out to stdout\n" );
  printf( "\n");
  printf( "[Optional] -o [outfilepath]\n");
  printf( "[Optional] -l [Logger Level] 0->warning , 2->error , 4->info , 16->debug \n");
  printf( "[Mandatory] [file1path1] [filepath2]\n" );
  printf( "Ex : diff_app /home/file1.txt /home/file2.txt\n" );
  printf( "Ex : diff_app /home/file1.txt /home/file2.txt -o /home/out.txt\n" );
  printf( "Ex : diff_app /home/file1.txt /home/file2.txt -o /home/out.txt -l 4\n" );
}

int main( int argc, char* argv[] )
{
  zone = ZONE_ERROR;
  std::string file1,file2,out;
  if(argc<3)
  {
    printUsage();
    return 0;
  }
  else if(argc==5 || argc==7 || argc==3)
  {
    for(unsigned int i=0;i<argc;i++)
    {
      if(i == 1)
      {
        file1=argv[i];
      }
      else if(i==2)
      {
        file2=argv[i];
      }
      else if(i==3)
      {
        if(std::string(argv[i]).compare("-o")==0)
        {
          out=argv[i+1];
        }
        else
        {
          printUsage();
          return 0;
        }
      }
      else if(i==5)
      {
        if(std::string(argv[i]).compare("-l")==0)
        {
          zone = atoi(argv[i+1]);
          if(zone!=0 && zone !=4 && zone !=8 && zone !=16)
          {
            printUsage();
            return 0;
          }
        }
        else
        {
          printUsage();
          return 0;
        } 
      }
    }
  }
  else
  {
    printUsage();
    return 0;
  }  
  CONSOLE_MSG(ZONE_INFO,"Starting diff tool");
  CONSOLE_MSG(ZONE_INFO,"file1 <%s>",file1.data());
  CONSOLE_MSG(ZONE_INFO,"file2 <%s>",file2.data());
  CONSOLE_MSG(ZONE_INFO,"out <%s>",out.data());
  CONSOLE_MSG(ZONE_INFO,"Log Level = %d",zone);
  CDiff diff(file1,file2,out);
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

