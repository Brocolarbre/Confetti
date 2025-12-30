#pragma once

#include "ParticleEmitter.hpp"
#include "ParticlePool.hpp"
#include "ConfettiEngine/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class ParticleEmitterPool
	{
	private:
		std::vector<ParticleEmitter> m_emitters;
		ParticlePool m_particles;
		RandomNumberGenerator& m_generator;

	public:
		ParticleEmitterPool(RandomNumberGenerator& generator);

		//void createEmitter();
		//void destroyEmitter();

		const ParticlePool& getParticlePool() const;

		void update(float elapsedTime, float deltaTime);
	};
}