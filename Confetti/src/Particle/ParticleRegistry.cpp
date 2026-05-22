#include "Confetti/Particle/ParticleRegistry.hpp"

namespace cft
{
	void ParticleRegistry::addParticleSystem(unsigned int id, const ParticleSystem& particleSystem)
	{
		m_particleSystems[id] = particleSystem;
	}

	void ParticleRegistry::addParticleEffect(unsigned int id, const ParticleEffect& particleEffect)
	{
		m_particleEffects[id] = particleEffect;
	}

	void ParticleRegistry::addParticleEmitter(unsigned int id, const ParticleEmitter& particleEmitter)
	{
		m_particleEmitters[id] = particleEmitter;
	}

	void ParticleRegistry::addForceField(unsigned int id, std::unique_ptr<ForceField> forceField)
	{
		m_forceFields[id] = std::move(forceField);
	}

	void ParticleRegistry::removeParticleSystem(unsigned int id)
	{
		m_particleSystems.erase(id);
	}

	void ParticleRegistry::removeParticleEffect(unsigned int id)
	{
		m_particleEffects.erase(id);
	}

	void ParticleRegistry::removeParticleEmitter(unsigned int id)
	{
		m_particleEmitters.erase(id);
	}

	void ParticleRegistry::removeForceField(unsigned int id)
	{
		m_forceFields.erase(id);
	}

	const ParticleSystem& ParticleRegistry::getParticleSystem(unsigned int id) const
	{
		return m_particleSystems.at(id);
	}

	const ParticleEffect& ParticleRegistry::getParticleEffect(unsigned int id) const
	{
		return m_particleEffects.at(id);
	}

	const ParticleEmitter& ParticleRegistry::getParticleEmitter(unsigned int id) const
	{
		return m_particleEmitters.at(id);
	}

	const ForceField& ParticleRegistry::getForceField(unsigned int id) const
	{
		return *m_forceFields.at(id);
	}

	ParticleSystem& ParticleRegistry::getParticleSystem(unsigned int id)
	{
		return m_particleSystems.at(id);
	}

	ParticleEffect& ParticleRegistry::getParticleEffect(unsigned int id)
	{
		return m_particleEffects.at(id);
	}

	ParticleEmitter& ParticleRegistry::getParticleEmitter(unsigned int id)
	{
		return m_particleEmitters.at(id);
	}

	ForceField& ParticleRegistry::getForceField(unsigned int id)
	{
		return *m_forceFields.at(id);
	}
}