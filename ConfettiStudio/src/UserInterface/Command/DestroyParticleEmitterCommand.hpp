#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class DestroyParticleEmitterCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;
	cft::ParticleEmitter m_particleEmitter;

public:
	DestroyParticleEmitterCommand(ConfettiInstance& confettiInstance, unsigned int id);

	void run();
	void revert();
};