#include "Confetti/ParticleSpawner/ParticleSpawner.hpp"

namespace cft
{
	ParticleSpawner::ParticleSpawner(std::unique_ptr<AttributeGenerator<Position>> positionGenerator, std::unique_ptr<AttributeGenerator<Velocity>> velocityGenerator, std::unique_ptr<AttributeGenerator<Scale>> scaleGenerator, std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<AttributeGenerator<Lifetime>> lifetimeGenerator, float maximumParticleLifetime) :
		m_colorGenerator(std::move(colorGenerator)),
		m_positionGenerator(std::move(positionGenerator)),
		m_velocityGenerator(std::move(velocityGenerator)),
		m_scaleGenerator(std::move(scaleGenerator)),
		m_lifetimeGenerator(std::move(lifetimeGenerator)),
		m_maximumParticleLifetime(maximumParticleLifetime)
	{

	}

	std::unique_ptr<ParticleSpawner> ParticleSpawner::clone() const
	{
		return std::make_unique<ParticleSpawner>(
			m_positionGenerator->clone(),
			m_velocityGenerator->clone(),
			m_scaleGenerator->clone(),
			m_colorGenerator->clone(),
			m_lifetimeGenerator->clone(),
			m_maximumParticleLifetime
		);
	}

	float ParticleSpawner::getMaxiumParticleLifetime() const
	{
		return m_maximumParticleLifetime;
	}

	std::vector<Particle> ParticleSpawner::spawn(unsigned int count, float elapsedTime, float deltaTime, unsigned int id)
	{
		std::vector<glm::vec4> color(m_colorGenerator->generate(count));
		std::vector<glm::vec3> position(m_positionGenerator->generate(count));
		std::vector<glm::vec3> velocity(m_velocityGenerator->generate(count));
		std::vector<glm::vec2> scale(m_scaleGenerator->generate(count));
		std::vector<float> lifetime(m_lifetimeGenerator->generate(count));

		std::vector<Particle> particles;
		particles.reserve(count);

		for (unsigned int i = 0; i < count; ++i)
		{
			Particle particle; //

			particle.color = color[i];
			particle.position = position[i];
			particle.velocity = velocity[i];
			particle.scale = scale[i];
			particle.lifetime = lifetime[i];
			particle.spawnTime = elapsedTime;
			particle.id = id;

			particles.push_back(particle);
		}

		return particles;
	}
}