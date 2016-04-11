#ifndef C_DATA_BASE
#define C_DATA_BASE

#include <string>
#include <vector>
#include <utility>
#include <stdexcept>

#include "sqlite3.h"


class CDataBase
{
public:
    CDataBase();
    CDataBase(std::string _fileName);
    ~CDataBase();
    void Open(std::string _fileName);
    void Close();
    void Execute(std::string _sqlRequest);
    int Callback(int _argc, char** _argv, char** _colNames);
    std::vector <std::vector <std::pair <std::string, std::string>>> m_ExecResult; // Rows and Columns

private:
    sqlite3* m_DataBase;
    char* m_Error;
    int m_Result;
    bool m_IsOpen;
};

#endif // C_DATA_BASE
