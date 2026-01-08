#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class DestroyParticleEffectCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;
	std::string m_name;
	cft::ParticleEffect m_particleEffect;

public:
	DestroyParticleEffectCommand(ConfettiInstance& confettiInstance, const std::string& name);

	void run();
	void revert();
};