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
    void Initialize();
    bool ReadLines(std::vector <std::string>& vec1,std::vector <std::string>& vec2);
    void PrintReport(std::vector <std::string>& vec1,std::vector <std::string>& vec2);
    void PrintMisMatch(std::vector <std::string>&vec1,std::vector <std::string>&vec2,std::vector<unsigned long int>& mismatch);
    bool PrintDiff(std::vector <std::string>& vec1,std::vector <std::string>& vec2);
    void RunDiffAlgorithm(std::vector<std::string>& vec1,std::vector<std::string>& vec2,std::vector<std::string>& result,std::vector<unsigned long int>& mismatch);
    bool IsExist(const std::string& filePath);
    void PrintFilesTime();
    void GetModifiedTime(std::string& m_fileN,char* date);
    unsigned long int GetFileSize(std::vector<std::string>& vec);
    private:
    bool m_init;
    std::ifstream m_inputFile1;
    std::ifstream m_inputFile2;
    std::string m_file1;
    std::string m_file2; 
    unsigned long int m_fileSize1;
    unsigned long int m_fileSize2;
    // char* p_bufFile1;
    // char* p_bufFile2;

};

#endif