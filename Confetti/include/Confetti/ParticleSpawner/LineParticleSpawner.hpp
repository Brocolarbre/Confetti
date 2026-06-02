#pragma once

#include "ParticleSpawner.hpp"

namespace cft
{
	class LineParticleSpawner : public ParticleSpawner
	{
	private:
		glm::vec3 m_start;
		glm::vec3 m_end;

	public:
		LineParticleSpawner(const glm::vec3& start, const glm::vec3& end);

		std::unique_ptr<ParticleSpawner> clone() const override;
		float getMaxiumParticleLifetime() const override;
		std::vector<Particle> spawn(unsigned int count, float elapsedTime, float deltaTime, unsigned int id) override;
	};
}