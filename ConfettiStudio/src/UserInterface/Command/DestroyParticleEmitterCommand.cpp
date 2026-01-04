#include "DestroyParticleEmitterCommand.hpp"

DestroyParticleEmitterCommand::DestroyParticleEmitterCommand(ConfettiInstance& confettiInstance, unsigned int id) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(id),
	m_particleEmitter()
{

}

void DestroyParticleEmitterCommand::run()
{
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
	m_particleEmitter = particleRegistry.getParticleEmitter(m_id);
	particleRegistry.removeParticleEmitter(m_id);
}

void DestroyParticleEmitterCommand::revert()
{
	m_id = m_confettiInstance.getIdGenerators().emitter();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleEmitter(m_id, m_particleEmitter);
}