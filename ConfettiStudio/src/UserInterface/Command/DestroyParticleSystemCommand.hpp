#pragma once

#include "Command.hpp"
#include "UserInterface/Model/ConfettiInstance.hpp"

class DestroyParticleSystemCommand : public Command
{
private:
	ConfettiInstance& m_confettiInstance;
	unsigned int m_id;
	std::string m_name;
	cft::ParticleSystem m_particleSystem;

public:
	DestroyParticleSystemCommand(ConfettiInstance& confettiInstance, unsigned int id);

	void run();
	void revert();
};