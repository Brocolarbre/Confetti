#include "DestroyParticleEffectCommand.hpp"

DestroyParticleEffectCommand::DestroyParticleEffectCommand(ConfettiInstance& confettiInstance, unsigned int id) :
	Command(true),
	m_confettiInstance(confettiInstance),
	m_id(id),
	m_name(),
	m_particleEffect()
{

}

void DestroyParticleEffectCommand::run()
{
	cft::ParticleRegistry& particleRegistry = m_confettiInstance.getParticleSimulation().getParticleRegistry();
	m_particleEffect = particleRegistry.getParticleEffect(m_id);
	particleRegistry.removeParticleEffect(m_id);
	AssetDictionary& assetDictionary = m_confettiInstance.getAssetDictionary();
	m_name = assetDictionary.getParticleEffectName(m_id);
	assetDictionary.removeParticleEffectName(m_id);
}

void DestroyParticleEffectCommand::revert()
{
	m_id = m_confettiInstance.getIdGenerators().effect();
	m_confettiInstance.getParticleSimulation().getParticleRegistry().addParticleEffect(m_id, m_particleEffect);
	m_confettiInstance.getAssetDictionary().setParticleEffectName(m_id, m_name);
}