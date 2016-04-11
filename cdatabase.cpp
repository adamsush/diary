#include "cdatabase.hpp"


CDataBase::CDataBase()
{
    m_Result = 0;
    m_IsOpen = false;
}

CDataBase::CDataBase(std::string _fileName)
{
    m_Result = 0;

    Open(_fileName);

    if(m_Result)
        throw std::runtime_error((std::string)"Can't open database");
    else
        m_IsOpen = true;
}

CDataBase::~CDataBase()
{
    if(m_IsOpen)
        Close();
}

void CDataBase::Close()
{
    sqlite3_free(m_Error);
    sqlite3_close(m_DataBase);
    m_IsOpen = false;
}

void CDataBase::Open(std::string _fileName)
{
    m_Result = sqlite3_open(_fileName.c_str(), &m_DataBase);

    if(m_Result)
    {
        Close();
        throw std::runtime_error((std::string)"Can't open database: " + (std::string)sqlite3_errmsg(m_DataBase));
    }
}

// This wrapper callback is being required for SQLite3
static int CallbackWrapper(void* _ptr, int _argc, char** _argv, char** _colNames)
{
    CDataBase* obj = reinterpret_cast <CDataBase*> (_ptr);
    return obj->Callback(_argc, _argv, _colNames);
}

void CDataBase::Execute(std::string _sqlRequest)
{
    m_ExecResult.clear();
    m_Result = sqlite3_exec(m_DataBase, _sqlRequest.c_str(), CallbackWrapper, this, &m_Error);

    if (m_Result != SQLITE_OK)
        throw std::runtime_error((std::string)"SQL Error");
}

int CDataBase::Callback(int _argc, char** _argv, char** _colNames)
{
    std::vector <std::pair <std::string, std::string>> row;

    for(int i=0; i<_argc; i++)
    {
        std::pair<std::string, std::string> data;
        data.first = _colNames[i];
        data.second = _argv[i] ? _argv[i] : "NULL";
        row.push_back(data);
    }

    m_ExecResult.push_back(row);

    return 0;
}
