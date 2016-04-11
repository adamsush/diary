#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

#include "../cdbhandler.hpp"


int main()
{
    CDBHandler dbh;
    TaskTableStruct task;
    BookTableStruct book;
    NoteTableStruct note;
    AddressTableStruct addr;
    PersonTableStruct pers;
    PhoneTableStruct phone;
    EmailTableStruct email;

    task.BookTable = "default";
    task.Name = "Task1";
    task.Description = "Description of Task1";
    task.Comment = "Comment for Task1";
    task.Status = true;
    task.Deleted = false;

    dbh.AddTask(task);
    std::cout << dbh.GetLastSQL() << std::endl;

    book.Name = "NewBook";
    book.PersonTable = "default";

    dbh.AddBook(book);
    std::cout << dbh.GetLastSQL() << std::endl;

    note.Data = "NewNote";
    note.BookTable = "NewBook";

    dbh.AddNote(note);
    std::cout << dbh.GetLastSQL() << std::endl;

    addr.BookTable = "NewBook";
    addr.Address = "asdgasd";
    addr.Birthday = "Birthday";
    addr.Comment = "Comment";
    addr.Name1 = "Name1";

    dbh.AddAddress(addr);
    std::cout << dbh.GetLastSQL() << std::endl;

    pers.Name = "Adam";

    dbh.AddPerson(pers);
    std::cout << dbh.GetLastSQL() << std::endl;

    phone.AddressID = "0";
    phone.BookTable = "NewBook";
    phone.Comment = "Good Man";
    phone.Phone = "+7-960-957-95-47";
    phone.Type = "Mobile";

    dbh.AddPhone(phone);
    std::cout << dbh.GetLastSQL() << std::endl;

    email.AddressID = "0";
    email.BookTable = "NewBook";
    email.Comment = "Good Man";
    email.Data = "adam-sush@inbox.ru";

    dbh.AddEmail(email);
    std::cout << dbh.GetLastSQL() << std::endl;

    return 0;
}
