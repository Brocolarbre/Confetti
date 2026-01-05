#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class SelectParticleEffectCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	std::optional<unsigned int> m_id;

public:
	SelectParticleEffectCommand(ConfettiInstance& confettiInstance, std::optional<unsigned int> id);

	void run();
	void revert();
};