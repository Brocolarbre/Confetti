#include "DestroyParticleSystemCommand.hpp"

DestroyParticleSystemCommand::DestroyParticleSystemCommand(ConfettiInstance& confettiInstance, unsigned int id) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(id),
	m_name(),
	m_particleSystem()
{

}

void DestroyParticleSystemCommand::run()
{
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
	m_particleSystem = particleRegistry.getParticleSystem(m_id);
	particleRegistry.removeParticleSystem(m_id);
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	m_name = assetDictionary.getParticleSystemName(m_id);
	assetDictionary.removeParticleSystemName(m_id);
}

void DestroyParticleSystemCommand::revert()
{
	m_id = m_confettiInstance.getIdGenerators().system();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleSystem(m_id, m_particleSystem);
	m_confettiInstance.getAssetDictionary().setParticleSystemName(m_id, m_name);
}