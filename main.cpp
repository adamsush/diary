#include <iostream>
#include <string>

#include "version.hpp"
#include "cinteractivestate.hpp"
#include "cdbhandler.hpp"


void printVersion()
{
    std::string data;

    data = "  Version: " + (std::string)VERSION + "." + (std::string)REVISION + "\n";
    data += "  Build: " + (std::string)BUILD + "\n";

    std::cout << data << std::endl;
}

int main(int argc, char** argv)
{
    CInteractiveState State;
    CDBHandler DataBase;

    // Test:
    printVersion();

    return 0;
}
