#include "ConfettiEngine/Particle/ParticleOrchestrator.hpp"
#include "ConfettiEngine/ParticleSimulation.hpp"

namespace cft
{
	ParticleOrchestrator::ParticleOrchestrator(ParticleSimulation& particleSimulation) :
		m_effects(),
		m_particleEffectPool(*this),
		m_particleEmitterPools(),
		m_particleSimulation(particleSimulation)
	{

	}

	void ParticleOrchestrator::createParticleEffect(const ParticleEffect& particleEffect)
	{
		unsigned int poolCapacity = m_particleEffectPool.getCapacity();
		if (static_cast<int>(poolCapacity) - static_cast<unsigned int>(m_particleEffectPool.getCount()) == 0)
			m_particleEffectPool.resize(poolCapacity + 1);

		m_particleEffectPool.createParticleEffect(particleEffect);
	}

	const std::unordered_map<unsigned int, ParticleEmitterPool>& ParticleOrchestrator::getParticleEmitterPools() const
	{
		return m_particleEmitterPools;
	}

	const ParticleEmitter& ParticleOrchestrator::getParticleEmitter(unsigned int id) const
	{
		return m_particleSimulation.getParticleEmitter(id);
	}

	void ParticleOrchestrator::createParticleEmitter(const ParticleEmitter& particleEmitter)
	{
		if (!m_particleEmitterPools.contains(particleEmitter.type))
			m_particleEmitterPools.insert(std::make_pair(particleEmitter.type, ParticleEmitterPool(m_particleSimulation.getRandomNumberGenerator())));

		ParticleEmitterPool& pool = m_particleEmitterPools.at(particleEmitter.type);

		unsigned int poolCapacity = pool.getCapacity();
		if (static_cast<int>(poolCapacity) - static_cast<unsigned int>(pool.getCount()) == 0)
			pool.resize(poolCapacity + 1);

		m_particleEmitterPools.at(particleEmitter.type).createParticleEmitter(particleEmitter);
	}

	void ParticleOrchestrator::addParticleSystem(const ParticleSystem& particleSystem)
	{
		m_effects.insert(m_effects.end(), particleSystem.effects.begin(), particleSystem.effects.end());
	}

	void ParticleOrchestrator::update(float elapsedTime, float deltaTime)
	{
		for (unsigned int i = 0; i < m_effects.size();)
		{
			const ParticleEffect& effect = m_particleSimulation.getParticleEffect(m_effects[i]);
			if (effect.spawnTime <= elapsedTime)
			{
				createParticleEffect(effect);
				m_effects[i] = m_effects[m_effects.size() - 1];
				m_effects.erase(m_effects.end() - 1);
			}
			else
			{
				++i;
			}
		}

		m_particleEffectPool.update(elapsedTime, deltaTime);

		for (auto& [id, pool] : m_particleEmitterPools)
			pool.update(elapsedTime, deltaTime);
	}
}