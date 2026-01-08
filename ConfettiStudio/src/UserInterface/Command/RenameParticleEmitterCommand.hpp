#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class RenameParticleEmitterCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	std::string m_name;
	std::string m_newName;

public:
	RenameParticleEmitterCommand(ConfettiInstance& confettiInstance, const std::string& name, const std::string& newName);

	void run();
	void revert();
};