#pragma once

#include "ParticleData.hpp"
#include "ConfettiEngine/Tools/RandomNumberGenerator.hpp"

namespace cft
{
	class ParticleSystem
	{
	private:
		ParticleData m_particleData;
		RandomNumberGenerator m_rng;
		unsigned int m_particleCount;

		void addParticle(const glm::vec4& color, const glm::vec3& position, const glm::vec3& velocity, const glm::vec2& scale, float lifetime, float spawnTime);
		void removeParticle(unsigned int index);

	public:
		ParticleSystem();

		const ParticleData& getParticleData() const;
		ParticleData& getParticleData();
		unsigned int getParticleCount() const;

		void allocate(unsigned int particleCount);

		void spawnParticle(float spawnTime);
		void killParticle(unsigned int particleIndex);
	};
}