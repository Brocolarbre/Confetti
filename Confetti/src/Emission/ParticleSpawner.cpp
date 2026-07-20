#include "Confetti/Emission/ParticleSpawner.hpp"

namespace cft
{
	unsigned int ParticleSpawner::m_nextId = 0;

	unsigned int ParticleSpawner::getNextId()
	{
		return m_nextId++;
	}

	ParticleSpawner::ParticleSpawner(std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<AttributeGenerator<Position>> positionGenerator, std::unique_ptr<AttributeGenerator<Rotation>> rotationGenerator, std::unique_ptr<AttributeGenerator<Scale>> scaleGenerator, std::unique_ptr<AttributeGenerator<LinearVelocity>> linearVelocityGenerator, std::unique_ptr<AttributeGenerator<AngularVelocity>> angularVelocityGenerator, std::unique_ptr<AttributeGenerator<Phase>> phaseGenerator, std::unique_ptr<AttributeGenerator<Lifetime>> lifetimeGenerator, float maximumParticleLifetime) :
		m_spawnShape(),
		m_colorGenerator(std::move(colorGenerator)),
		m_positionGenerator(std::move(positionGenerator)),
		m_rotationGenerator(std::move(rotationGenerator)),
		m_scaleGenerator(std::move(scaleGenerator)),
		m_linearVelocityGenerator(std::move(linearVelocityGenerator)),
		m_angularVelocityGenerator(std::move(angularVelocityGenerator)),
		m_phaseGenerator(std::move(phaseGenerator)),
		m_lifetimeGenerator(std::move(lifetimeGenerator)),
		m_maximumParticleLifetime(maximumParticleLifetime)
	{

	}

	ParticleSpawner::ParticleSpawner(std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<SpawnShape> spawnShape, std::unique_ptr<AttributeGenerator<Rotation>> rotationGenerator, std::unique_ptr<AttributeGenerator<Scale>> scaleGenerator, std::unique_ptr<AttributeGenerator<LinearVelocity>> linearVelocityGenerator, std::unique_ptr<AttributeGenerator<AngularVelocity>> angularVelocityGenerator, std::unique_ptr<AttributeGenerator<Phase>> phaseGenerator, std::unique_ptr<AttributeGenerator<Lifetime>> lifetimeGenerator, float maximumParticleLifetime) :
		m_spawnShape(std::move(spawnShape)),
		m_colorGenerator(std::move(colorGenerator)),
		m_positionGenerator(),
		m_rotationGenerator(std::move(rotationGenerator)),
		m_scaleGenerator(std::move(scaleGenerator)),
		m_linearVelocityGenerator(std::move(linearVelocityGenerator)),
		m_angularVelocityGenerator(std::move(angularVelocityGenerator)),
		m_phaseGenerator(std::move(phaseGenerator)),
		m_lifetimeGenerator(std::move(lifetimeGenerator)),
		m_maximumParticleLifetime(maximumParticleLifetime)
	{

	}

	std::unique_ptr<ParticleSpawner> ParticleSpawner::clone() const
	{
		if (m_spawnShape)
		{
			return std::make_unique<ParticleSpawner>(
				m_colorGenerator->clone(),
				m_spawnShape->clone(),
				m_rotationGenerator->clone(),
				m_scaleGenerator->clone(),
				m_linearVelocityGenerator->clone(),
				m_angularVelocityGenerator->clone(),
				m_phaseGenerator->clone(),
				m_lifetimeGenerator->clone(),
				m_maximumParticleLifetime
			);
		}
		else
		{
			return std::make_unique<ParticleSpawner>(
				m_colorGenerator->clone(),
				m_positionGenerator->clone(),
				m_rotationGenerator->clone(),
				m_scaleGenerator->clone(),
				m_linearVelocityGenerator->clone(),
				m_angularVelocityGenerator->clone(),
				m_phaseGenerator->clone(),
				m_lifetimeGenerator->clone(),
				m_maximumParticleLifetime
			);
		}
	}

	float ParticleSpawner::getMaxiumParticleLifetime() const
	{
		return m_maximumParticleLifetime;
	}

	std::vector<Particle> ParticleSpawner::spawn(unsigned int count, float elapsedTime, float deltaTime, unsigned int particleRegistryId)
	{
		std::vector<SpawnContext> spawnContext;
		std::vector<glm::vec4> color;
		std::vector<glm::vec3> position;
		std::vector<glm::quat> rotation;
		std::vector<glm::vec3> scale;
		std::vector<glm::vec3> linearVelocity;
		std::vector<glm::vec3> angularVelocity;
		std::vector<float> phase;
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
		rotation = m_rotationGenerator->generate(count, spawnContext);
		scale = m_scaleGenerator->generate(count, spawnContext);
		linearVelocity = m_linearVelocityGenerator->generate(count, spawnContext);
		angularVelocity = m_angularVelocityGenerator->generate(count, spawnContext);
		phase = m_phaseGenerator->generate(count, spawnContext);
		lifetime = m_lifetimeGenerator->generate(count, spawnContext);

		std::vector<Particle> particles;
		particles.reserve(count);

		for (unsigned int i = 0; i < count; ++i)
			particles.push_back(Particle{ color[i], m_spawnShape ? spawnContext[i].position : position[i], rotation[i], scale[i], linearVelocity[i], angularVelocity[i], color[i], scale[i], glm::vec3(0.0f), phase[i], lifetime[i], elapsedTime, getNextId(), particleRegistryId });

		return particles;
	}

	void ParticleSpawner::resetNextId()
	{
		m_nextId = 0;
	}
}