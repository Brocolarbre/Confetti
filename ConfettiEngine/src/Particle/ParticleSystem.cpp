#include "ConfettiEngine/Particle/ParticleSystem.hpp"

#include <iostream>

namespace cft
{
	ParticleSystem::ParticleSystem(Confetti& confetti) :
		m_particleEffectPools(),
		m_particleEmitterPools(),
		m_confetti(confetti)
	{

	}

	const std::unordered_map<unsigned int, ParticleEmitterPool>& ParticleSystem::getParticleEmitterPools() const
	{
		return m_particleEmitterPools;
	}

	const ParticleEffect& ParticleSystem::getParticleEffect(unsigned int id) const
	{
		return m_confetti.particleEffects.at(id);
	}

	const ParticleEmitter& ParticleSystem::getParticleEmitter(unsigned int id) const
	{
		return m_confetti.particleEmitters.at(id);
	}

	void ParticleSystem::createParticleEffect(unsigned int type, const ParticleEffect& effect)
	{
		if (!m_particleEffectPools.contains(type))
			m_particleEffectPools.insert(std::make_pair(type, ParticleEffectPool(*this)));
		ParticleEffectPool& pool = m_particleEffectPools.at(type);
		unsigned int poolCapacity = pool.getCapacity();

		if (poolCapacity - pool.getCount() == 0)
			pool.resize(poolCapacity + 1);

		m_particleEffectPools.at(type).createParticleEffect(effect);
	}

	void ParticleSystem::createParticleEmitter(const ParticleEmitter& emitter)
	{
		if (!m_particleEmitterPools.contains(emitter.type))
			m_particleEmitterPools.insert(std::make_pair(emitter.type, ParticleEmitterPool(m_confetti.randomNumberGenerator)));
		ParticleEmitterPool& pool = m_particleEmitterPools.at(emitter.type);
		unsigned int poolCapacity = pool.getCapacity();

		std::cout << poolCapacity << " " << pool.getCount() << std::endl;
		if (static_cast<int>(poolCapacity) - static_cast<unsigned int>(pool.getCount()) == 0)
			pool.resize(poolCapacity + 1);

		m_particleEmitterPools.at(emitter.type).createParticleEmitter(emitter);
	}

	void ParticleSystem::update(float elapsedTime, float deltaTime)
	{
		for (auto& [type, pool] : m_particleEffectPools)
			pool.update(elapsedTime, deltaTime);

		for (auto& [type, pool] : m_particleEmitterPools)
			pool.update(elapsedTime, deltaTime);
	}
}