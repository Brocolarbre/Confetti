#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class SelectParticleSystemCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	std::optional<unsigned int> m_id;

public:
	SelectParticleSystemCommand(ConfettiInstance& confettiInstance, std::optional<unsigned int> id);

	void run();
	void revert();
};