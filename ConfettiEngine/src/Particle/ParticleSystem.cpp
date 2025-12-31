#include "ConfettiEngine/Particle/ParticleSystem.hpp"
#include "ConfettiEngine/Confetti.hpp"

namespace cft
{
	ParticleSystem::ParticleSystem(Confetti& confetti) :
		m_effects(),
		m_particleEffectPool(*this),
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

	void ParticleSystem::createParticleEffect(const ParticleEffect& effect)
	{
		unsigned int poolCapacity = m_particleEffectPool.getCapacity();
		if (static_cast<int>(poolCapacity) - static_cast<unsigned int>(m_particleEffectPool.getCount()) == 0)
			m_particleEffectPool.resize(poolCapacity + 1);

		m_particleEffectPool.createParticleEffect(effect);
	}

	void ParticleSystem::createParticleEmitter(const ParticleEmitter& emitter)
	{
		if (!m_particleEmitterPools.contains(emitter.type))
			m_particleEmitterPools.insert(std::make_pair(emitter.type, ParticleEmitterPool(m_confetti.randomNumberGenerator)));

		ParticleEmitterPool& pool = m_particleEmitterPools.at(emitter.type);

		unsigned int poolCapacity = pool.getCapacity();
		if (static_cast<int>(poolCapacity) - static_cast<unsigned int>(pool.getCount()) == 0)
			pool.resize(poolCapacity + 1);

		m_particleEmitterPools.at(emitter.type).createParticleEmitter(emitter);
	}

	void ParticleSystem::addParticleEffect(unsigned int id)
	{
		m_effects.push_back(id);
	}

	void ParticleSystem::update(float elapsedTime, float deltaTime)
	{
		for (unsigned int i = 0; i < m_effects.size();)
		{
			const ParticleEffect& effect = getParticleEffect(m_effects[i]);
			if (effect.spawnTime <= elapsedTime)
			{
				createParticleEffect(effect);
				std::cout << "Particle effect spawned" << std::endl;
				m_effects[i] = m_effects[m_effects.size() - 1];
				m_effects.erase(m_effects.end() - 1);
			}
			else
			{
				++i;
			}
		}

		m_particleEffectPool.update(elapsedTime, deltaTime);

		for (auto& [type, pool] : m_particleEmitterPools)
			pool.update(elapsedTime, deltaTime);
	}
}