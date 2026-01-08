#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class SelectParticleEffectCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	std::optional<std::string> m_name;

public:
	SelectParticleEffectCommand(ConfettiInstance& confettiInstance, const std::optional<std::string>& name);

	void run();
	void revert();
};