#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class RenameParticleEffectCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;
	std::string m_name;

public:
	RenameParticleEffectCommand(ConfettiInstance& confettiInstance, unsigned int id, const std::string& name);

	void run();
	void revert();
};