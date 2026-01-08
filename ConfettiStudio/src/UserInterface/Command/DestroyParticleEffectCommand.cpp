#include "DestroyParticleEffectCommand.hpp"

DestroyParticleEffectCommand::DestroyParticleEffectCommand(ConfettiInstance& confettiInstance, const std::string& name) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(0),
	m_name(name),
	m_particleEffect()
{

}

void DestroyParticleEffectCommand::run()
{
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	m_id = assetDictionary.getParticleEffectId(m_name);
	m_particleEffect = particleRegistry.getParticleEffect(m_id);
	particleRegistry.removeParticleEffect(m_id);
	assetDictionary.removeParticleEffectId(m_name);
}

void DestroyParticleEffectCommand::revert()
{
	m_id = m_confettiInstance.getIdGenerators().effect();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleEffect(m_id, m_particleEffect);
	m_confettiInstance.getAssetDictionary().setParticleEffectId(m_name, m_id);
}