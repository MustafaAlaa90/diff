
/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#include "CDiff.h"

CDiff::CDiff(const std::string& file1, const std::string& file2):m_file1(file1)
,m_file2(file2)
,m_init(true)
{
    Initialize();
}
//--------------------------------------------------------------------------------
bool CDiff::FindDiff()
{
    bool Ret = true;
    if(!m_init)
    {
        CONSOLE_MSG(ZONE_ERROR,"CDiff | Couldn't Start Diff Operation");
        Ret=false;
    }
    else
    {
        CONSOLE_MSG(ZONE_DEBUG,"CDiff | Reading Files Data");
        std::vector <std::string> vec1,vec2; 
        if(!ReadLines(vec1,vec2))
        {
            CONSOLE_MSG(ZONE_ERROR,"CDiff | Could't Readline of one or the two files");
            Ret=false;
        }
        else
        {
            PrintReport(vec1,vec2);
            PrintDiff(vec1,vec2);
        }
    }
    return Ret;
}
//---------------------------------------------------------------------------------
void CDiff::Initialize()
{
    
    if( IsExist(m_file1) && IsExist(m_file2) )
    {
        m_inputFile1.open(m_file1); // default is open for reading
        m_inputFile2.open(m_file2);

        if(!m_inputFile1.is_open() && !m_inputFile2.is_open())
        {
            CONSOLE_MSG(ZONE_ERROR,"Couldn't open Files <%s> <%s> for reading",m_file1.data(),m_file2.data());
            m_init = false;
        }
    }
    else
    {
        m_init = false;
    }
}
//--------------------------------------------------------------------------------
bool CDiff::ReadLines(std::vector <std::string>& vec1,std::vector <std::string>& vec2)
{
    bool Ret = true;
    std::string str1,str2;
    CONSOLE_MSG(ZONE_DEBUG,"CDiff | Reading Lines 1");
    while(std::getline(m_inputFile1,str1))
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
    CONSOLE_MSG(ZONE_DEBUG,"CDiff | Reading Lines 2");
    while(std::getline(m_inputFile2,str2))
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
    CONSOLE_MSG(ZONE_DEBUG,"CDiff | Finished Reading Lines");

    return Ret;
}
//---------------------------------------------------------------------------------
void CDiff::PrintReport(std::vector <std::string>& vec1,std::vector <std::string>& vec2)
{
    printf("%s\n",std::string(98,'-').c_str());
    printf("%*s | %*s | %*s |\n",-20,"File Path",-35,m_file1.data(),-35,m_file2.data());
    printf("%s\n",std::string(98,'-').c_str());
    printf("%*s | %*lu | %*lu |\n",-20,"Number of lines",-35,vec1.size(),-35,vec2.size());
    printf("%s\n",std::string(98,'-').c_str());
    printf("%*s | %*lu | %*lu |\n",-20,"File Size",-35,GetFileSize(vec1),-35,GetFileSize(vec2));
    printf("%s\n",std::string(98,'-').c_str());
}
//---------------------------------------------------------------------------------
bool CDiff::PrintDiff(std::vector <std::string>& vec1,std::vector <std::string>& vec2)
{
    bool Ret = true;
    std::vector<std::string> result;
    std::vector<unsigned long int> mismatch;
    PrintMisMatch(vec1,vec2,mismatch);
    RunDiffAlgorithm(vec1,vec2,result,mismatch);
    PrintFilesTime();
    for(auto& line : result)
    {
        printf("%s\n",line.data());
    }
}
//----------------------------------------------------------------------------
void CDiff::PrintMisMatch(std::vector <std::string>&vec1,std::vector <std::string>&vec2,std::vector<unsigned long int>& mismatch)
{
    unsigned long int counter = std::min(vec1.size(),vec2.size());
    printf("Mismatches at line: ");
    for(unsigned long int i=0;i<counter;i++)
    {
        if(vec1[i].compare(vec2[i]) !=0)
        {
            printf(" %lu ",i+1);
            mismatch.push_back(i);
        }
    }
    printf("\n");
}
//----------------------------------------------------------------------------
void CDiff::RunDiffAlgorithm(std::vector<std::string>& vec1,std::vector<std::string>& vec2,std::vector<std::string>& result,std::vector<unsigned long int>& mismatch)
{
    if(vec2.empty() && !vec1.empty())
    {
        printf("@@ -1,%lu +0,0 @@\n",vec1.size());
        for(auto& line : vec1)
        {
            printf("- %s\n",line.data());
        }
    }
    else if (!vec2.empty() && vec1.empty())
    {
        printf("@@ -0,0 +0,%lu @@\n",vec2.size());
        for(auto& line : vec2)
        {
            printf("+ %s\n",line.data());
        }
    }
    else
    {
        CONSOLE_MSG(ZONE_INFO,"Files are not empty");
        
        if(vec1[0].compare(vec2[0])!=0)
        {
            result.push_back(std::string("-")+vec1[0]);
            result.push_back(std::string("+")+vec2[0]);
        }
        for(unsigned long int i=1,j=1; i<=vec1.size(),j<vec2.size();i++,j++)
        {
            CONSOLE_MSG(ZONE_INFO,"Lines under compare <%s> ///// <%s>",vec1[i].data(),vec2[j].data());
            if(vec1[i].compare(vec2[j])==0)
            {
                result.push_back(vec1[i]);
            }
            else
            {
                CONSOLE_MSG(ZONE_INFO,"Found mismatch on line %lu",i+1);
                if(vec2.size() > (j+1) && vec1.size() > (i+1))
                {
                    CONSOLE_MSG(ZONE_INFO,"Safe Size Boundary");
                    CONSOLE_MSG(ZONE_INFO,"Lines under compare <%s> ///// <%s>",vec1[i+1].data(),vec2[j+1].data());
                    if( vec1[i+1].compare(vec2[j+1])==0 && vec1[j-1].compare(vec2[j-1])==0 ) //change in file 2
                    {
                        result.push_back("-" + vec1[i]);
                        result.push_back("+" + vec2[i]);
                    }
                    else if (vec1[i].compare(vec2[j+1])==0) // addition in file 2
                    {
                        result.push_back("+"+vec2[j++]);
                        result.push_back(vec1[i++]);
                    }
                    else if (vec1[i].compare(vec2[j-1])==0) // deletion in file 2
                    {
                        result.push_back("-"+vec1[i]);
                        result.push_back(vec2[j]);
                    }
                }
                else if(vec2.size() == (j+1) && vec1.size() == (i+1))
                {
                    result.push_back("-" + vec1[i]);
                    result.push_back("+" + vec2[i]);
                }
                else if (vec1.size() > (i+1))  // end of file 2
                {
                    result.push_back("+"+vec1[i]);
                }
                else if (vec2.size() > (j+1))  // end of file 1
                {
                    result.push_back("-"+vec1[j]);
                }
            }
        }

    }
}
//-----------------------------------------------------------------------------
bool CDiff::IsExist(const std::string& filePath)
{
    struct stat st = {0};
    if (stat( filePath.data(), &st ) == -1 )
    {
        CONSOLE_MSG(ZONE_ERROR,"CDiff | File <%s> doesn't exist in the filesystem",filePath.data());
        return false;
    }
    else
    {
        return true;
    }
}
//-----------------------------------------------------------------------------
void CDiff::GetModifiedTime(std::string& m_fileName,char* date)
{
  struct stat attrib;
  stat(m_fileName.data(), &attrib);
  strftime(date, 50, "%d-%m-%y %T", localtime(&(attrib.st_ctime)));
}
//-----------------------------------------------------------------------------
unsigned long int CDiff::GetFileSize(std::vector<std::string>& vec)
{
    unsigned long int size = 0;
    for(auto& line : vec)
    {
        size = size + line.size();
    }
    return size+vec.size(); // considering the \n charachters at the end of every line
}
//-----------------------------------------------------------------------------
void CDiff::PrintFilesTime()
{
    char time1[50]={0,};
    char time2[50]={0,};
    CONSOLE_MSG(ZONE_DEBUG,"Getting Time 1");
    GetModifiedTime(m_file1,time1);
    CONSOLE_MSG(ZONE_DEBUG,"Getting Time 2");
    GetModifiedTime(m_file2,time2);
    CONSOLE_MSG(ZONE_DEBUG,"Finished Getting Time");
    printf("--- %s %s\n",m_file1.data(),time1);
    printf("+++ %s %s\n",m_file2.data(), time2);
}
//---------------------------------------------------------------------------------
CDiff::~CDiff()
{
    CONSOLE_MSG(ZONE_DEBUG,"inside destructor");
}