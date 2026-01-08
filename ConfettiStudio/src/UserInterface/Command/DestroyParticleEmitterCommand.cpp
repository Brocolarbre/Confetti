#include "DestroyParticleEmitterCommand.hpp"

DestroyParticleEmitterCommand::DestroyParticleEmitterCommand(ConfettiInstance& confettiInstance, const std::string& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(0),
	m_name(name),
	m_particleEmitter()
{

}

void DestroyParticleEmitterCommand::run()
{
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	m_id = assetDictionary.getParticleEmitterId(m_name);
	m_particleEmitter = particleRegistry.getParticleEmitter(m_id);
	particleRegistry.removeParticleEmitter(m_id);
	assetDictionary.removeParticleEmitterId(m_name);
}

void DestroyParticleEmitterCommand::revert()
{
	m_id = m_confettiInstance.getIdGenerators().emitter();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleEmitter(m_id, m_particleEmitter);
	m_confettiInstance.getAssetDictionary().setParticleEmitterId(m_name, m_id);
}