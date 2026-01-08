#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class CreateParticleEffectCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;
	std::string m_name;

public:
	CreateParticleEffectCommand(ConfettiInstance& confettiInstance, const std::string& name);

	void run();
	void revert();
};