#include "Confetti/ParticleSpawner/LineParticleSpawner.hpp"

namespace cft
{
	LineParticleSpawner::LineParticleSpawner(const glm::vec3& start, const glm::vec3& end) :
		m_start(start),
		m_end(end)
	{

	}

	std::unique_ptr<ParticleSpawner> LineParticleSpawner::clone() const
	{
		return std::make_unique<LineParticleSpawner>(*this);
	}

	float LineParticleSpawner::getMaxiumParticleLifetime() const
	{
		return 0.0f;
	}

	std::vector<Particle> LineParticleSpawner::spawn(unsigned int count, float elapsedTime, float deltaTime, unsigned int id)
	{
		std::vector<Particle> particles;
		particles.reserve(count);

		for (unsigned int i = 0; i < count; ++i)
		{
			//Particle particle;

			//particle.color = ;
			//particle.position = ;
			//particle.velocity = ;
			//particle.scale = ;
			//particle.lifetime = ;
			//particle.spawnTime = elapsedTime;
			//particle.id = id;
		}

		return particles;
	}
}