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

#define MAXSIZE 32768

class CDiff
{
    public:
    CDiff(const std::string& file1, const std::string& file2,const std::string& out);
    ~CDiff();
    /*
    * Find the difference between two input files
    * report a result that contain comparison between line numbers & file size & mismatch line number
    * and the change happened in each line
    */
    bool FindDiff();


    private:
    /*
    * open input file streams
    * open out file stream if selected
    * set a flag that initialization is done
    */
    void Initialize();
    /*
    * Read input streams line by lines and store them in vec1 and vec2
    */
    bool ReadLines(std::vector <std::string>& vec1,std::vector <std::string>& vec2);
    /*
    * print a table contains file paths , their number of lines
    * their size and mismatch line numbers
    */
    void PrintReport(std::vector <std::string>& vec1,std::vector <std::string>& vec2);
    /*
    * detect the mismatch line numbers and store them in mismatch
    */
    void GetMisMatch(std::vector <std::string>&vec1,std::vector <std::string>&vec2,std::vector<unsigned long int>& mismatch);
    /*
    * print the path file with last modified time
    * and the change in every line (for example -line +line###)
    */
    bool PrintDiff(std::vector <std::string>& vec1,std::vector <std::string>& vec2);
    /*
    * Apply the algorithm of detecting the mismatch and the change in every line
    * it doesn't detect addition or deletion like diffutils does
    */
    void RunDiffAlgorithm(std::vector<std::string>& vec1,std::vector<std::string>& vec2,std::vector<std::string>& result);
    /*
    * check if filpath is exist in filesystem
    * return true on success , false on fails
    */
    bool IsExist(const std::string& filePath);
    /*
    * print the last modifie time of the input files
    */
    void PrintFilesTime();
    /*
    * get the last modifie time of file m_fileN and store it in date
    */
    void GetModifiedTime(std::string& m_fileN,char* date);
    /*
    * get the file size from a vector on lines vec
    */
    unsigned long int GetFileSize(std::vector<std::string>& vec);
    private:
    bool m_init;
    /* input file streams */
    std::ifstream m_inputFile1;
    std::ifstream m_inputFile2;
    /* out file stream */
    std::ofstream  m_outFile;
    /* input file paths */
    std::string m_file1;
    std::string m_file2;
    /* output file paths */
    std::string m_out;
    /* input files size */
    unsigned long int m_fileSize1;
    unsigned long int m_fileSize2;
    bool  m_writeToFile;

};

#endif