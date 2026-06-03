#include "Confetti/ParticleSpawner/ParticleSpawner.hpp"

namespace cft
{
	ParticleSpawner::ParticleSpawner(std::unique_ptr<AttributeGenerator<Position>> positionGenerator, std::unique_ptr<AttributeGenerator<Velocity>> velocityGenerator, std::unique_ptr<AttributeGenerator<Scale>> scaleGenerator, std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<AttributeGenerator<Lifetime>> lifetimeGenerator, float maximumParticleLifetime) :
		m_spawnShape(),
		m_colorGenerator(std::move(colorGenerator)),
		m_positionGenerator(std::move(positionGenerator)),
		m_velocityGenerator(std::move(velocityGenerator)),
		m_scaleGenerator(std::move(scaleGenerator)),
		m_lifetimeGenerator(std::move(lifetimeGenerator)),
		m_maximumParticleLifetime(maximumParticleLifetime)
	{

	}

	ParticleSpawner::ParticleSpawner(std::unique_ptr<SpawnShape> spawnShape, std::unique_ptr<AttributeGenerator<Velocity>> velocityGenerator, std::unique_ptr<AttributeGenerator<Scale>> scaleGenerator, std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<AttributeGenerator<Lifetime>> lifetimeGenerator, float maximumParticleLifetime) :
		m_spawnShape(std::move(spawnShape)),
		m_colorGenerator(std::move(colorGenerator)),
		m_positionGenerator(),
		m_velocityGenerator(std::move(velocityGenerator)),
		m_scaleGenerator(std::move(scaleGenerator)),
		m_lifetimeGenerator(std::move(lifetimeGenerator)),
		m_maximumParticleLifetime(maximumParticleLifetime)
	{

	}

	std::unique_ptr<ParticleSpawner> ParticleSpawner::clone() const
	{
		if (m_spawnShape)
		{
			return std::make_unique<ParticleSpawner>(
				m_spawnShape->clone(),
				m_velocityGenerator->clone(),
				m_scaleGenerator->clone(),
				m_colorGenerator->clone(),
				m_lifetimeGenerator->clone(),
				m_maximumParticleLifetime
			);
		}
		else
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
	}

	float ParticleSpawner::getMaxiumParticleLifetime() const
	{
		return m_maximumParticleLifetime;
	}

	std::vector<Particle> ParticleSpawner::spawn(unsigned int count, float elapsedTime, float deltaTime, unsigned int id)
	{
		std::vector<SpawnContext> spawnContext;
		std::vector<glm::vec4> color;
		std::vector<glm::vec3> position;
		std::vector<glm::vec3> velocity;
		std::vector<glm::vec2> scale;
		std::vector<float> lifetime;

		if (m_spawnShape)
		{
			spawnContext = m_spawnShape->sample(count);
		}
		else
		{
			spawnContext = std::vector<SpawnContext>(count, SpawnContext{ glm::vec3(0.0f), glm::vec3(0.0f) });
			position = m_positionGenerator->generate(count, spawnContext);

			for (unsigned int i = 0; i < spawnContext.size(); ++i)
				spawnContext[i].position = position[i];
		}

		color = m_colorGenerator->generate(count, spawnContext);
		velocity = m_velocityGenerator->generate(count, spawnContext);
		scale = m_scaleGenerator->generate(count, spawnContext);
		lifetime = m_lifetimeGenerator->generate(count, spawnContext);

		std::vector<Particle> particles;
		particles.reserve(count);

		for (unsigned int i = 0; i < count; ++i)
		{
			Particle particle; //			

			particle.color = color[i];
			particle.position = m_spawnShape ? spawnContext[i].position : position[i];
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