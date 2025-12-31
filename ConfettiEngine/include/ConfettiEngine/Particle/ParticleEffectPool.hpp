#pragma once

#include "ParticleEffect.hpp"

namespace cft
{
	class ParticleSystem;

	class ParticleEffectPool
	{
	private:
		std::vector<ParticleEffect> m_effects;
		unsigned int m_capacity;
		unsigned int m_count;

		ParticleSystem& m_particleSystem;

	public:
		ParticleEffectPool(ParticleSystem& particleSystem);

		unsigned int getCapacity() const;
		unsigned int getCount() const;

		void createParticleEffect(const ParticleEffect& effect);
		void destroyParticleEffect(unsigned int index);

		void resize(unsigned int capacity);
		void update(float elapsedTime, float deltaTime);
	};
}