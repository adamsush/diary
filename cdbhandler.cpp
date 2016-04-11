#include "cdbhandler.hpp"


CDBHandler::CDBHandler()
{
    SetFileName("database.db");
}

CDBHandler::CDBHandler(std::string _fileName)
{
    SetFileName(_fileName);
}

CDBHandler::~CDBHandler()
{

}

void CDBHandler::SetFileName(std::string _fileName)
{
    m_dbFileName = _fileName;
}

bool CDBHandler::NameIsRight()
{
    return (m_dbFileName == "") ? false : true;
}

bool CDBHandler::CheckDB()
{
    if(!NameIsRight())
        return false;

    std::ifstream checkFile;
    checkFile.open(m_dbFileName);
    
    if(checkFile.is_open())
    {
        checkFile.close();
        return true;
    }

    return false;
}

std::string CDBHandler::GetLastSQL()
{
    return m_LastSQL;
}

std::string CDBHandler::BuildInsert(std::string _table, std::vector<std::string> _fields, std::vector<std::string> _values)
{
    std::string sqlRequest = "INSERT INTO " + _table + " (";
    
    for(size_t i=0; i<_fields.size(); i++)
    {
        sqlRequest += _fields[i];
        if(i < (_fields.size()-1))
            sqlRequest += ", ";
    }

    sqlRequest += ") VALUES (";

    for(size_t i=0; i<_values.size(); i++)
    {
        sqlRequest += _values[i];
        if(i < (_values.size()-1))
            sqlRequest += ", ";
    }

    sqlRequest += ")";

    return sqlRequest;
}

std::string CDBHandler::BuildSelect(std::string _column, std::string _table, std::string _condition)
{
    std::string sqlRequest = "SELECT " + _column + " FROM " + _table;
    if(_condition != "")
        sqlRequest += " WHERE " + _condition;

    return sqlRequest;
}

void CDBHandler::AddTask(TaskTableStruct _task)
{
    std::vector<std::string> f;
    std::vector<std::string> v;

    f.push_back("book_id");
    f.push_back("comment");
    f.push_back("deleted");
    f.push_back("description");
    f.push_back("name");
    f.push_back("status");
    f.push_back("task_date");
    f.push_back("task_time");

    std::string select = BuildSelect("id", "Book", "name='" + _task.BookTable + "'");

    v.push_back("(" + select + ")");
    v.push_back("'" + _task.Comment + "'");
    v.push_back(_task.Deleted ? "1" : "0");
    v.push_back("'" + _task.Description + "'");
    v.push_back("'" + _task.Name + "'");
    v.push_back(_task.Status ? "1" : "0");
    v.push_back("'" + _task.Date + "'");
    v.push_back("'" + _task.Time + "'");

    m_LastSQL = BuildInsert("Task", f, v) + ";";

    m_DataBase.Open(m_dbFileName);
    m_DataBase.Execute(m_LastSQL);
    m_DataBase.Close();
}

void CDBHandler::AddBook(BookTableStruct _book)
{
    std::vector<std::string> f;
    std::vector<std::string> v;

    std::string select = BuildSelect("id", "Person", "name='" + _book.PersonTable + "'");

    f.push_back("person_id");
    f.push_back("name");

    v.push_back("(" + select + ")");
    v.push_back("'" + _book.Name + "'");

    m_LastSQL = BuildInsert("Book", f, v) + ";";

    m_DataBase.Open(m_dbFileName);
    m_DataBase.Execute(m_LastSQL);
    m_DataBase.Close();
}

void CDBHandler::AddNote(NoteTableStruct _note)
{
    std::vector<std::string> f;
    std::vector<std::string> v;

    std::string select = BuildSelect("id", "Book", "name='" + _note.BookTable + "'");

    f.push_back("book_id");
    f.push_back("data");

    v.push_back("(" + select + ")");
    v.push_back("'" + _note.Data + "'");

    m_LastSQL = BuildInsert("Note", f, v) + ";";

    m_DataBase.Open(m_dbFileName);
    m_DataBase.Execute(m_LastSQL);
    m_DataBase.Close();
}

void CDBHandler::AddAddress(AddressTableStruct _address)
{
    std::vector<std::string> f;
    std::vector<std::string> v;

    std::string select = BuildSelect("id", "Book", "name='" + _address.BookTable + "'");

    f.push_back("book_id");
    f.push_back("address");
    f.push_back("birthday");
    f.push_back("comment");
    f.push_back("email_id");
    f.push_back("phone_id");
    f.push_back("name1");
    f.push_back("name2");

    v.push_back("(" + select + ")");
    v.push_back("'" + _address.Address + "'");
    v.push_back("'" + _address.Birthday + "'");
    v.push_back("'" + _address.Comment + "'");
    v.push_back(_address.EmailID != "" ? _address.EmailID : "0");
    v.push_back(_address.PhoneID != "" ? _address.PhoneID : "0");
    v.push_back("'" + _address.Name1 + "'");
    v.push_back("'" + _address.Name2 + "'");

    m_LastSQL = BuildInsert("Addressbook", f, v) + ";";

    m_DataBase.Open(m_dbFileName);
    m_DataBase.Execute(m_LastSQL);
    m_DataBase.Close();
}

void CDBHandler::AddPerson(PersonTableStruct _person)
{
    std::vector<std::string> f;
    std::vector<std::string> v;

    f.push_back("name");
    v.push_back("'" + _person.Name + "'");

    m_LastSQL = BuildInsert("Person", f, v) + ";";

    m_DataBase.Open(m_dbFileName);
    m_DataBase.Execute(m_LastSQL);
    m_DataBase.Close();
}

void CDBHandler::AddPhone(PhoneTableStruct _phone)
{
    std::vector<std::string> f;
    std::vector<std::string> v;

    std::string select = BuildSelect("id", "Book", "name='" + _phone.BookTable + "'");

    f.push_back("addr_id");
    f.push_back("book_id");
    f.push_back("comment");
    f.push_back("phone");
    f.push_back("type");

    v.push_back(_phone.AddressID);
    v.push_back("(" + select + ")");
    v.push_back("'" + _phone.Comment + "'");
    v.push_back("'" + _phone.Phone + "'");
    v.push_back("'" + _phone.Type + "'");

    m_LastSQL = BuildInsert("Phonebook", f, v) + ";";

    m_DataBase.Open(m_dbFileName);
    m_DataBase.Execute(m_LastSQL);
    m_DataBase.Close();
}

void CDBHandler::AddEmail(EmailTableStruct _email)
{
    std::vector<std::string> f;
    std::vector<std::string> v;

    std::string select = BuildSelect("id", "Book", "name='" + _email.BookTable + "'");

    f.push_back("addr_id");
    f.push_back("book_id");
    f.push_back("comment");
    f.push_back("data");

    v.push_back(_email.AddressID);
    v.push_back("(" + select + ")");
    v.push_back("'" + _email.Comment + "'");
    v.push_back("'" + _email.Data + "'");

    m_LastSQL = BuildInsert("Email", f, v) + ";";

    m_DataBase.Open(m_dbFileName);
    m_DataBase.Execute(m_LastSQL);
    m_DataBase.Close();
}
