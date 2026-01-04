#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class CreateParticleEmitterCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;

public:
	CreateParticleEmitterCommand(ConfettiInstance& confettiInstance);

	void run();
	void revert();
};