#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class DestroyParticleEmitterCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;
	std::string m_name;
	cft::ParticleEmitter m_particleEmitter;

public:
	DestroyParticleEmitterCommand(ConfettiInstance& confettiInstance, const std::string& name);

	void run();
	void revert();
};