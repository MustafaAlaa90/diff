
/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#include "CDiff.h"

CDiff::CDiff(const std::string& file1, const std::string& file2, const std::string& out):m_file1(file1)
,m_file2(file2)
,m_out(out)
,m_init(true)
,m_writeToFile(false)
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
            CONSOLE_MSG(ZONE_ERROR,"CDiff | Couldn't open Files <%s> <%s> for reading",m_file1.data(),m_file2.data());
            m_init = false;
        }
    }
    else
    {
        m_init = false;
    }
    if(!m_out.empty())
    {
        CONSOLE_MSG(ZONE_DEBUG,"CDiff | opening of stream");
        m_outFile.open(m_out.data(),std::ofstream::out | std::ofstream::app | std::ios::binary); //open for write and append
        if(m_outFile.is_open())
        {
            m_writeToFile = true;
        }
        // if open output stream fails , will continue printing results on console
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
    return Ret;
}
//---------------------------------------------------------------------------------
void CDiff::PrintReport(std::vector <std::string>& vec1,std::vector <std::string>& vec2)
{
    std::vector<unsigned long int> mismatch;
    GetMisMatch(vec1,vec2,mismatch);
    if(m_writeToFile)
    {
        char buf[MAXSIZE];
        unsigned long int offset =0;
        offset =sprintf(buf,"%s\n",std::string(118,'-').c_str());
        offset +=sprintf(buf+offset,"%*s | %*s | %*s |\n",-20,"File Path",-40,m_file1.data(),-50,m_file2.data());
        offset +=sprintf(buf+offset,"%s\n",std::string(118,'-').c_str());
        offset +=sprintf(buf+offset,"%*s | %*lu | %*lu |\n",-20,"Number of lines",-40,vec1.size(),-50,vec2.size());
        offset +=sprintf(buf+offset,"%s\n",std::string(118,'-').c_str());
        offset +=sprintf(buf+offset,"%*s | %*lu | %*lu |\n",-20,"File Size (Bytes)",-40,GetFileSize(vec1),-50,GetFileSize(vec2));
        offset +=sprintf(buf+offset,"%s\n",std::string(118,'-').c_str());
        offset +=sprintf(buf+offset,"mismach found at lines : ");
        for(auto& mem : mismatch)
        {
            offset +=sprintf(buf+offset,"%lu ",mem+1);
        }
        offset +=sprintf(buf+offset,"\n");
        m_outFile.write(buf,offset);
    }
    else
    {
        printf("%s\n",std::string(118,'-').c_str());
        printf("%*s | %*s | %*s |\n",-20,"File Path",-40,m_file1.data(),-50,m_file2.data());
        printf("%s\n",std::string(118,'-').c_str());
        printf("%*s | %*lu | %*lu |\n",-20,"Number of lines",-40,vec1.size(),-50,vec2.size());
        printf("%s\n",std::string(118,'-').c_str());
        printf("%*s | %*lu | %*lu |\n",-20,"File Size (Bytes)",-40,GetFileSize(vec1),-50,GetFileSize(vec2));
        printf("%s\n",std::string(118,'-').c_str());
        printf("mismach found at lines : ");
        for(auto& mem : mismatch)
        {
            printf("%lu ",mem+1);
        }
        printf("\n");
    }
}
//---------------------------------------------------------------------------------
bool CDiff::PrintDiff(std::vector <std::string>& vec1,std::vector <std::string>& vec2)
{
    bool Ret = true;
    std::vector<std::string> result;
    RunDiffAlgorithm(vec1,vec2,result);
    PrintFilesTime();
    char* buf = new char[GetFileSize(result)];
    memset(buf,0,sizeof(buf));
    unsigned long int offset=0;
    if(buf)
    {
        for(auto& line : result)
        {
            offset+=sprintf(buf+offset,"%s\n",line.data());
        }
        if(m_writeToFile)
        {
            m_outFile.write(buf,offset);
        }
        else
        {
            printf("%s",buf);
        }
        delete[] buf;
    }
}
//----------------------------------------------------------------------------
void CDiff::GetMisMatch(std::vector <std::string>&vec1,std::vector <std::string>&vec2,std::vector<unsigned long int>& mismatch)
{
    unsigned long int counter = std::min(vec1.size(),vec2.size());
    for(unsigned long int i=0;i<counter;i++)
    {
        if(vec1[i].compare(vec2[i]) !=0)
        {
            mismatch.push_back(i);
        }
    }
    if(vec1.size() > vec2.size())
    {
        for(unsigned long int j =vec2.size();j<vec1.size();j++)
        {
            mismatch.push_back(j);
        }
    }
    else if (vec1.size() < vec2.size())
    {
        for(unsigned long int j =vec1.size();j<vec2.size();j++)
        {
            mismatch.push_back(j);
        }
    }
}
//----------------------------------------------------------------------------
void CDiff::RunDiffAlgorithm(std::vector<std::string>& vec1,std::vector<std::string>& vec2,std::vector<std::string>& result)
{
    unsigned long int offset=0;
    char buf [MAXSIZE];
    if(vec2.empty() && !vec1.empty())
    {
        if(!m_writeToFile)
        {
            printf("@@ -1,%lu +0,0 @@\n",vec1.size());
        }
        else
        {
            offset+=sprintf(buf+offset,"@@ -1,%lu +0,0 @@\n",vec1.size());
        }
        for(auto& line : vec1)
        {
            if(!m_writeToFile)
            {
                printf("- %s\n",line.data());
            }
            else
            {
                offset+=sprintf(buf+offset,"- %s\n",line.data());
            }  
        }
    }
    else if (!vec2.empty() && vec1.empty())
    {
        if(!m_writeToFile)
        {
            printf("@@ -0,0 +0,%lu @@\n",vec2.size());
        }
        else
        {
            offset+=sprintf(buf+offset,"@@ -0,0 +0,%lu @@\n",vec2.size());
        }
        for(auto& line : vec2)
        {
            
            if(!m_writeToFile)
            {
                printf("+ %s\n",line.data());
            }
            else
            {
                offset+=sprintf(buf+offset,"+ %s\n",line.data());
            } 
        }
    }
    else
    {
        CONSOLE_MSG(ZONE_DEBUG,"CDiff | Files are not empty");
        unsigned long int size = std::min(vec1.size(),vec2.size());
        for(unsigned long int i=0; i<size;i++)
        {
            CONSOLE_MSG(ZONE_DEBUG,"CDiff | Lines under compare <%s> ///// <%s>",vec1[i].data(),vec2[i].data());
            if(vec1[i].compare(vec2[i])==0)
            {
                result.push_back(vec1[i]);
            }
            else
            {
                CONSOLE_MSG(ZONE_DEBUG,"CDiff | Found mismatch on line %lu",i+1);
                result.push_back("-" + vec1[i]);
                result.push_back("+" + vec2[i]);
            }
        }
        if(vec1.size() > vec2.size())
        {
            for(unsigned long int j =vec2.size();j<vec1.size();j++)
            {
                result.push_back("+" + vec1[j]);
            }
        }
        else if (vec1.size() < vec2.size())
        {
            for(unsigned long int j =vec1.size();j<vec2.size();j++)
            {
                result.push_back("-" + vec2[j]);
            }
        }
    }
    if(m_writeToFile)
    {
        m_outFile.write(buf,offset);
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
    CONSOLE_MSG(ZONE_DEBUG,"CDiff | Getting Time 1");
    GetModifiedTime(m_file1,time1);
    CONSOLE_MSG(ZONE_DEBUG,"CDiff | Getting Time 2");
    GetModifiedTime(m_file2,time2);
    CONSOLE_MSG(ZONE_DEBUG,"CDiff | Finished Getting Time");
    if(!m_writeToFile)
    {
        printf("--- %s %s\n",m_file1.data(),time1);
        printf("+++ %s %s\n",m_file2.data(), time2);
    }
    else
    {
        char buf[MAXSIZE];
        unsigned long int offset =0;
        offset+=sprintf(buf+offset,"--- %s %s\n",m_file1.data(),time1);
        offset+=sprintf(buf+offset,"+++ %s %s\n",m_file2.data(), time2);
        m_outFile.write(buf,offset);
    }
}
//---------------------------------------------------------------------------------
CDiff::~CDiff()
{
    if(m_outFile.is_open())
    {
        m_outFile.close();
    }
    if(m_inputFile1.is_open())
    {
        m_inputFile1.close();
    }
    if(m_inputFile2.is_open())
    {
        m_inputFile2.close();
    }
}