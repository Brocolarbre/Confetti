#pragma once

#include <vector>

namespace cft
{
	class ParticleOrchestrator;

	struct ParticleEffect
	{
		float spawnTime;
		float lifetime;
		std::vector<unsigned int> emitters;
	};

	class ParticleEffectPool
	{
	private:
		std::vector<ParticleEffect> m_effects;
		unsigned int m_capacity;
		unsigned int m_count;

		ParticleOrchestrator& m_particleOrchestrator;

	public:
		ParticleEffectPool(ParticleOrchestrator& particleOrchestrator);

		unsigned int getCapacity() const;
		unsigned int getCount() const;

		void createParticleEffect(const ParticleEffect& effect);
		void destroyParticleEffect(unsigned int index);

		void resize(unsigned int capacity);
		void update(float elapsedTime, float deltaTime);
	};
}