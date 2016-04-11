#include "cinteractivestate.hpp"


CInteractiveState::CInteractiveState()
{
    ResetState();
}

void CInteractiveState::ResetState()
{
    m_State = State::SELECT_PERSON;
    SetPrompt(m_State);
}

State CInteractiveState::GetState()
{
    return m_State;
}

void CInteractiveState::SetState(State _state)
{
    m_State = _state;
    SetPrompt(m_State);
}

std::string CInteractiveState::GetPrompt()
{
    return m_Prompt;
}

void CInteractiveState::SetPrompt(std::string _prompt)
{
    m_Prompt = _prompt;
}

void CInteractiveState::SetPrompt(State _state)
{
    if(m_State == State::SELECT_PERSON)
        m_Prompt = "Diary@> ";
    else if(m_State == State::CREATE_PERSON)
        m_Prompt = "Diary@New> ";

    else if(m_State == State::SELECT_TABLE)
        m_Prompt = "Diary@Menu> ";

    else if(m_State == State::BOOK_SELECTED)
        m_Prompt = "Diary@Book:Menu> ";
    else if(m_State == State::ADDR_SELECTED)
        m_Prompt = "Diary@Address:Menu> ";
    else if(m_State == State::PHONES_SELECTED)
        m_Prompt = "Diary@Phonebook:Menu> ";
    else if(m_State == State::EMAILS_SELECTED)
        m_Prompt = "Diary@Emails:Menu> ";
    else if(m_State == State::NOTES_SELECTED)
        m_Prompt = "Diary@Notes:Menu> ";

    // Book menu
    else if(m_State == State::SELECT_MODE)
        m_Prompt = "Diary@Book:Select> ";
    else if(m_State == State::SHOW_LIST)
        m_Prompt = "Diary@Book:Show> ";
    else if(m_State == State::ADD)
        m_Prompt = "Diary@Book:Add> ";
    else if(m_State == State::REMOVE)
        m_Prompt = "Diary@Book:Remove> ";
    else if(m_State == State::UPDATE)
        m_Prompt = "Diary@Book:Update> ";
    else if(m_State == State::SHOW_ITEM)
        m_Prompt = "Diary@Book:Item> ";
}
