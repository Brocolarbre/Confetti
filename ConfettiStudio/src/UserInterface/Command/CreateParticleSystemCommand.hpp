#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class CreateParticleSystemCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;

public:
	CreateParticleSystemCommand(ConfettiInstance& confettiInstance);

	void run();
	void revert();
};