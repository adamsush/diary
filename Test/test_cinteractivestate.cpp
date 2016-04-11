#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "../cinteractivestate.hpp"


int main()
{
    CInteractiveState state;
    std::cout << state.GetPrompt() << std::endl;
    state.SetState(State::CREATE_PERSON);
    std::cout << state.GetPrompt() << std::endl;

    return 0;
}
