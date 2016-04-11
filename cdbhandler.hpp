#ifndef C_DB_HANDLER
#define C_DB_HANDLER

#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

#include "cdatabase.hpp"


typedef struct Task
{
    std::string BookTable;
    std::string Name;
    std::string Description;
    std::string Date;
    std::string Time;
    std::string Comment;
    bool Status;
    bool Deleted;
} TaskTableStruct;

typedef struct Book
{
    std::string PersonTable;
    std::string Name;
} BookTableStruct;

typedef struct Note
{
    std::string BookTable;
    std::string Data;
} NoteTableStruct;

typedef struct Address
{
    std::string BookTable;
    std::string Address;
    std::string Birthday;
    std::string Comment;
    std::string EmailID;
    std::string PhoneID;
    std::string Name1;
    std::string Name2;
} AddressTableStruct;

typedef struct Person
{
    std::string Name;
} PersonTableStruct;

typedef struct Phone
{
    std::string AddressID;
    std::string BookTable;
    std::string Comment;
    std::string Phone;
    std::string Type;
} PhoneTableStruct;

typedef struct Email
{
    std::string AddressID;
    std::string BookTable;
    std::string Comment;
    std::string Data;
} EmailTableStruct;

class CDBHandler
{
public:
    CDBHandler();
    CDBHandler(std::string _fileName);
    ~CDBHandler();
    void SetFileName(std::string _fileName);
    std::string GetLastSQL();
    void AddTask(TaskTableStruct _task);
    void AddBook(BookTableStruct _book);
    void AddNote(NoteTableStruct _note);
    void AddAddress(AddressTableStruct _address);
    void AddPerson(PersonTableStruct _person);
    void AddPhone(PhoneTableStruct _phone);
    void AddEmail(EmailTableStruct _email);

private:
    bool CheckDB();
    bool NameIsRight();
    std::string BuildInsert(std::string _table, std::vector<std::string> _fields, std::vector<std::string> _values);
    std::string BuildSelect(std::string _column, std::string _table, std::string _condition);

    CDataBase m_DataBase;
    std::string m_dbFileName;
    std::string m_LastSQL;
};

#endif // C_DB_HANDLER
