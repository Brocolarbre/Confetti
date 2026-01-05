#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class SelectParticleEmitterCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	std::optional<unsigned int> m_id;

public:
	SelectParticleEmitterCommand(ConfettiInstance& confettiInstance, std::optional<unsigned int> id);

	void run();
	void revert();
};