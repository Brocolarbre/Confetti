#include "CommandHistory.hpp"

void CommandHistory::undo()
{
    if (m_undoCommands.empty())
        return;

    m_undoCommands.top()->revert();
    m_redoCommands.push(m_undoCommands.top());

    m_undoCommands.pop();
}

void CommandHistory::redo()
{
    if (m_redoCommands.empty())
        return;

    m_redoCommands.top()->run();
    m_undoCommands.push(m_redoCommands.top());

    m_redoCommands.pop();
}

bool CommandHistory::canUndo() const
{
    return !m_undoCommands.empty();
}

bool CommandHistory::canRedo() const
{
    return !m_redoCommands.empty();
}