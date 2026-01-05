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
	DestroyParticleEffectCommand(ConfettiInstance& confettiInstance, unsigned int id);

	void run();
	void revert();
};