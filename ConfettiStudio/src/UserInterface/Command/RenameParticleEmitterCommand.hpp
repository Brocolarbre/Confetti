#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class RenameParticleEmitterCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;
	std::string m_name;

public:
	RenameParticleEmitterCommand(ConfettiInstance& confettiInstance, unsigned int id, const std::string& name);

	void run();
	void revert();
};