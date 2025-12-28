#pragma once

#include "Command.hpp"

#include <memory>
#include <stack>

class CommandHistory
{
private:
	std::stack<std::shared_ptr<Command>> m_undoCommands;
	std::stack<std::shared_ptr<Command>> m_redoCommands;

public:
	template <typename T, typename ...Args>
	void run(Args&&... args);

	void undo();
	void redo();

	bool canUndo() const;
	bool canRedo() const;
};

template <typename T, typename ...Args>
inline void CommandHistory::run(Args&&... args)
{
	std::shared_ptr<Command> command = std::make_shared<T>(std::forward<Args>(args)...);
	command->run();

	if (command->isReversible())
	{
		m_undoCommands.push(command);
		m_redoCommands = std::stack<std::shared_ptr<Command>>();
	}
}