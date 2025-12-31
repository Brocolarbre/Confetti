#pragma once

#include "ParticleEffectPool.hpp"
#include "ParticleEmitterPool.hpp"
#include "ConfettiEngine/Confetti.hpp"

#include <unordered_map>

namespace cft
{
	struct Confetti;

	class ParticleSystem
	{
	private:
		std::unordered_map<unsigned int, ParticleEffectPool> m_particleEffectPools; // Need multiple pools for effects ?
		std::unordered_map<unsigned int, ParticleEmitterPool> m_particleEmitterPools;
		// Store effects, instantiate them with time in update
		Confetti& m_confetti;

	public:
		ParticleSystem(Confetti& confetti);

		const std::unordered_map<unsigned int, ParticleEmitterPool>& getParticleEmitterPools() const;

		const ParticleEffect& getParticleEffect(unsigned int id) const;
		const ParticleEmitter& getParticleEmitter(unsigned int id) const;

		void createParticleEffect(unsigned int type, const ParticleEffect& effect);
		void createParticleEmitter(const ParticleEmitter& emitter);

		void update(float elapsedTime, float deltaTime);
	};
}