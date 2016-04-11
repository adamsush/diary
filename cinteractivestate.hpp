#ifndef C_INTERACTIVE_STATE
#define C_INTERACTIVE_STATE

#include <string>
#include <stdexcept>


enum class State
{
    SELECT_PERSON = 0,
    CREATE_PERSON,

    SELECT_TABLE,

    // Main menu
    BOOK_SELECTED,
    ADDR_SELECTED,
    PHONES_SELECTED,
    EMAILS_SELECTED,
    NOTES_SELECTED,

    // Book menu
    SELECT_MODE,
    SHOW_LIST,
    ADD,
    REMOVE,
    UPDATE,
    SHOW_ITEM
};

class CInteractiveState
{
public:
    CInteractiveState();
    void ResetState();
    void SetState(State _state);
    State GetState();
    std::string GetPrompt();

private:
    void SetPrompt(std::string _prompt);
    void SetPrompt(State _state);

    std::string m_Prompt;
    State m_State;
};

#endif // C_INTERACTIVE_STATE
