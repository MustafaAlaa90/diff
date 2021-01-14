/*--------------------------------------------------------------------------------
Copyright (C) 2021 - Mustafa Ala
---------------------------------------------------------------------------------*/

#ifndef CDIFF_H_
#define CDIFF_H_

#include "../common.h"
#include <vector>
#include <cstring>
#include <fstream>
#include <sys/stat.h>

#define MAX_HUNK_SIZE 20

class CDiff
{
    public:
    CDiff(const std::string& file1, const std::string& file2);
    ~CDiff();
    bool FindDiff();


    private:
    void Iinitialize(const std::string& file1, const std::string& file2);
    bool ReadLines(std::vector <std::string>& vec1,std::vector <std::string>& vec2);
    bool PrintDiff(std::vector <std::string>& vec1,std::vector <std::string>& vec2);
    void GetModifiedTime(std::string& m_fileN,char* date);
    private:
    bool m_init;
    //CFile m_file1;
    //CFile m_file2;
    std::string m_file1;
    std::string m_file2; 
    unsigned long int m_fileSize1;
    unsigned long int m_fileSize2;
    // char* p_bufFile1;
    // char* p_bufFile2;

};

#endif