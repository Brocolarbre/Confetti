#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class RenameParticleEffectCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	std::string m_name;
	std::string m_newName;

public:
	RenameParticleEffectCommand(ConfettiInstance& confettiInstance, const std::string& name, const std::string& newName);

	void run();
	void revert();
};