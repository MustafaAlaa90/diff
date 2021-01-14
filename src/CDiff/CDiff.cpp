
/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#include "CDiff.h"

CDiff::CDiff(const std::string& file1, const std::string& file2):
 
 m_file1(file1)
,m_file2(file2)
,m_init(true)
{
    //Iinitialize(file1,file2);
}
//--------------------------------------------------------------------------------
bool CDiff::FindDiff()
{
    bool Ret = true;
    
        CONSOLE_MSG(ZONE_INFO,"CDiff | Reading Files Data");
        // if(m_file1.Read(p_bufFile1,m_fileSize1)
        //  && m_file2.Read(p_bufFile2,m_fileSize2) )
         
             
             std::vector <std::string> vec1,vec2; 
             ReadLines(vec1,vec2);
             PrintDiff(vec1,vec2);
         
         
    

    return Ret;
}
//---------------------------------------------------------------------------------
void CDiff::Iinitialize(const std::string& file1Path, const std::string& file2Path)
{

    // if(!m_file1.Open(file1Path,fmRead) && !m_file2.Open(file2Path,fmRead))
    // {
    //     CONSOLE_MSG(ZONE_ERROR,"CDiff | Couldn't open one or the two provided files <%s> <%s>",file1Path.data(),file2Path.data());
    //     m_init = false;
    // }
    // else
    // {
    //     CONSOLE_MSG(ZONE_INFO,"CDiff | Reading Files Sizes");
    //     m_fileSize1 = m_file1.GetFileSize();
    //     m_fileSize2 = m_file2.GetFileSize();
    //     p_bufFile1 = new char [m_fileSize1];
    //     p_bufFile2 = new char [m_fileSize2];
    //     memset(p_bufFile1,0,m_fileSize1);
    //     memset(p_bufFile2,0,m_fileSize2);
    // } 
}
//--------------------------------------------------------------------------------
bool CDiff::ReadLines(std::vector <std::string>& vec1,std::vector <std::string>& vec2)
{
    bool Ret = true;
    // if(!p_bufFile1 && !p_bufFile2)
    // {
    //     CONSOLE_MSG(ZONE_ERROR,"CDiff | empty files buffers");
    //     return false;
    // }
    std::ifstream input1(m_file1);
    std::ifstream input2(m_file2);
    std::string str1,str2;
    CONSOLE_MSG(ZONE_INFO,"CDiff | Reading Lines 1");
    while(std::getline(input1,str1))
    {
        if(str1.empty())
        {
            vec1.push_back("*");
        }
        else
        {
            vec1.push_back(str1);
        }
    }
    CONSOLE_MSG(ZONE_INFO,"CDiff | Reading Lines 2");
    while(std::getline(input2,str2))
    {
        if(str2.empty())
        {
            vec2.push_back("*");
        }
        else
        {
            vec2.push_back(str2);
        }
    }
    CONSOLE_MSG(ZONE_INFO,"CDiff | Finished Reading Lines");
    return Ret;
}
//---------------------------------------------------------------------------------
bool CDiff::PrintDiff(std::vector <std::string>& vec1,std::vector <std::string>& vec2)
{
    bool Ret = true;
    char time1[50]={0,};
    char time2[50]={0,};
    CONSOLE_MSG(ZONE_INFO,"Getting Time 1");
    GetModifiedTime(m_file1,time1);
    CONSOLE_MSG(ZONE_INFO,"Getting Time 2");
    GetModifiedTime(m_file2,time2);
    CONSOLE_MSG(ZONE_INFO,"Finished Getting Time");
    printf("--- %s %s\n",m_file1.data(),time1);
    printf("+++ %s %s\n",m_file2.data(), time2);
}
//--------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CDiff::GetModifiedTime(std::string& m_fileName,char* date)
{
  struct stat attrib;
  stat(m_fileName.data(), &attrib);
  strftime(date, 50, "%d-%m-%y %T", localtime(&(attrib.st_ctime)));
}


//---------------------------------------------------------------------------------
CDiff::~CDiff()
{
    CONSOLE_MSG(ZONE_INFO,"inside destructor");
    // if(p_bufFile1) delete [] p_bufFile1;
    // if(p_bufFile2) delete [] p_bufFile2;
    // if(m_file1.IsValid())
    // {
    //     m_file1.Close();
    // }
    // if(m_file2.IsValid())
    // {
    //     m_file2.Close();
    // }
}