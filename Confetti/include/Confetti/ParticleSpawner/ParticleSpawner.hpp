#pragma once

#include "AttributeGenerator/AttributeGenerator.hpp"
#include "AttributeGenerator/AttributeTypes.hpp"
#include "Confetti/Particle/Particle.hpp"
#include "SpawnShape/SpawnShape.hpp"

#include <memory>

namespace cft
{
	class ParticleSpawner
	{
	private:
		std::unique_ptr<SpawnShape> m_spawnShape;
		std::unique_ptr<AttributeGenerator<Color>> m_colorGenerator;
		std::unique_ptr<AttributeGenerator<Position>> m_positionGenerator;
		std::unique_ptr<AttributeGenerator<Rotation>> m_rotationGenerator;
		std::unique_ptr<AttributeGenerator<Scale>> m_scaleGenerator;
		std::unique_ptr<AttributeGenerator<LinearVelocity>> m_linearVelocityGenerator;
		std::unique_ptr<AttributeGenerator<AngularVelocity>> m_angularVelocityGenerator;
		std::unique_ptr<AttributeGenerator<Phase>> m_phaseGenerator;
		std::unique_ptr<AttributeGenerator<Lifetime>> m_lifetimeGenerator;
		float m_maximumParticleLifetime;

		static unsigned int m_nextId;

		static unsigned int getNextId();

	public:
		ParticleSpawner(std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<AttributeGenerator<Position>> positionGenerator, std::unique_ptr<AttributeGenerator<Rotation>> rotationGenerator, std::unique_ptr<AttributeGenerator<Scale>> scaleGenerator, std::unique_ptr<AttributeGenerator<LinearVelocity>> linearVelocityGenerator, std::unique_ptr<AttributeGenerator<AngularVelocity>> angularVelocityGenerator, std::unique_ptr<AttributeGenerator<Phase>> phaseGenerator, std::unique_ptr<AttributeGenerator<Lifetime>> lifetimeGenerator, float maximumParticleLifetime);
		ParticleSpawner(std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<SpawnShape> spawnShape, std::unique_ptr<AttributeGenerator<Rotation>> rotationGenerator, std::unique_ptr<AttributeGenerator<Scale>> scaleGenerator, std::unique_ptr<AttributeGenerator<LinearVelocity>> linearVelocityGenerator, std::unique_ptr<AttributeGenerator<AngularVelocity>> angularVelocityGenerator, std::unique_ptr<AttributeGenerator<Phase>> phaseGenerator, std::unique_ptr<AttributeGenerator<Lifetime>> lifetimeGenerator, float maximumParticleLifetime);

		std::unique_ptr<ParticleSpawner> clone() const;
		float getMaxiumParticleLifetime() const;
		std::vector<Particle> spawn(unsigned int count, float elapsedTime, float deltaTime, unsigned int particleRegistryId);

		static void resetNextId();
	};
}