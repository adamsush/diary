#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "../cdatabase.hpp"


int main()
{
    CDataBase db;

    try
    {
        db.Open((std::string)"test.db");
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    try
    {
        std::ifstream sqlFile;
        sqlFile.open("database/struct.sql");
        std::string sqlRequest;

        if (sqlFile)
        {
            sqlFile.seekg (0, sqlFile.end);
            int length = sqlFile.tellg();
            sqlFile.seekg (0, sqlFile.beg);

            char* buffer = new char [length];
            sqlFile.read (buffer, length);
            sqlRequest = buffer;

            delete[] buffer;
        }

        db.Execute(sqlRequest);
        sqlFile.close();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -2;
    }

    try
    {
        db.Close();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -3;
    }

    return 0;
}
