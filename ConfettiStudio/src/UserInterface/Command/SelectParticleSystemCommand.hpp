#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class SelectParticleSystemCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	std::optional<std::string> m_name;

public:
	SelectParticleSystemCommand(ConfettiInstance& confettiInstance, const std::optional<std::string>& name);

	void run();
	void revert();
};