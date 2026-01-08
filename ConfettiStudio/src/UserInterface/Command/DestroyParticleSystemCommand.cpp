#include "DestroyParticleSystemCommand.hpp"

DestroyParticleSystemCommand::DestroyParticleSystemCommand(ConfettiInstance& confettiInstance, const std::string& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(0),
	m_name(name),
	m_particleSystem()
{

}

void DestroyParticleSystemCommand::run()
{
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	m_id = assetDictionary.getParticleSystemId(m_name);
	m_particleSystem = particleRegistry.getParticleSystem(m_id);
	particleRegistry.removeParticleSystem(m_id);
	assetDictionary.removeParticleSystemId(m_name);
}

void DestroyParticleSystemCommand::revert()
{
	m_id = m_confettiInstance.getIdGenerators().system();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleSystem(m_id, m_particleSystem);
	m_confettiInstance.getAssetDictionary().setParticleSystemId(m_name, m_id);
}