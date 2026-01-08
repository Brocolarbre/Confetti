#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class CreateParticleEmitterCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;
	std::string m_name;

public:
	CreateParticleEmitterCommand(ConfettiInstance& confettiInstance, const std::string& name);

	void run();
	void revert();
};