#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class CreateParticleEffectCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;

public:
	CreateParticleEffectCommand(ConfettiInstance& confettiInstance);

	void run();
	void revert();
};