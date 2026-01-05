#include "CreateParticleEmitterCommand.hpp"

CreateParticleEmitterCommand::CreateParticleEmitterCommand(ConfettiInstance& confettiInstance) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(0)
{

}

void CreateParticleEmitterCommand::run()
{
	m_id = m_confettiInstance.getIdGenerators().emitter();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleEmitter(m_id, cft::ParticleEmitter{});
	m_confettiInstance.getAssetDictionary().setParticleEmitterName(m_id, "Emitter");
}

void CreateParticleEmitterCommand::revert()
{
	m_confettiInstance.getParticleSimulation().getParticleRegistry().removeParticleEmitter(m_id);
	m_confettiInstance.getAssetDictionary().removeParticleEmitterName(m_id);
}