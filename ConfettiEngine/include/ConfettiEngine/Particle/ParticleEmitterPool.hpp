#pragma once

#include "ParticleEmitter.hpp"

namespace cft
{
	class ParticleEmitterPool
	{
	private:
		std::vector<ParticleEmitter> m_emitters;
		unsigned int m_capacity;
		unsigned int m_count;

		ParticlePool m_particlePool;
		RandomNumberGenerator& m_generator;

	public:
		ParticleEmitterPool(RandomNumberGenerator& generator);

		unsigned int getCapacity() const;
		unsigned int getCount() const;

		const ParticlePool& getParticlePool() const;

		void createParticleEmitter(const ParticleEmitter& emitter);
		void destroyParticleEmitter(unsigned int index);

		void resize(unsigned int capacity);
		void update(float elapsedTime, float deltaTime);
	};
}