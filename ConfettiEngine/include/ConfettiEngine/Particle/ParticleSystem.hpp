#pragma once

#include "ParticleEffectPool.hpp"
#include "ParticleEmitterPool.hpp"

#include <unordered_map>

namespace cft
{
	struct Confetti;

	class ParticleSystem
	{
	private:
		std::vector<unsigned int> m_effects;
		ParticleEffectPool m_particleEffectPool;
		std::unordered_map<unsigned int, ParticleEmitterPool> m_particleEmitterPools;
		Confetti& m_confetti;

	public:
		ParticleSystem(Confetti& confetti);

		const std::unordered_map<unsigned int, ParticleEmitterPool>& getParticleEmitterPools() const;

		const ParticleEffect& getParticleEffect(unsigned int id) const; // ?
		const ParticleEmitter& getParticleEmitter(unsigned int id) const;

		void createParticleEffect(const ParticleEffect& effect);
		void createParticleEmitter(const ParticleEmitter& emitter);

		void addParticleEffect(unsigned int id);

		void update(float elapsedTime, float deltaTime);
	};
}