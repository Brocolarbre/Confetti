#pragma once

#include "AttributeGenerator.hpp"
#include "Confetti/Particle/Particle.hpp"

#include <memory>

namespace cft
{
	using Color = glm::vec4;
	using Lifetime = float;
	using Position = glm::vec3;
	using Scale = glm::vec2;
	using Velocity = glm::vec3;

	class ParticleSpawner
	{
	private:
		std::unique_ptr<AttributeGenerator<Color>> m_colorGenerator;
		std::unique_ptr<AttributeGenerator<Position>> m_positionGenerator;
		std::unique_ptr<AttributeGenerator<Velocity>> m_velocityGenerator;
		std::unique_ptr<AttributeGenerator<Scale>> m_scaleGenerator;
		std::unique_ptr<AttributeGenerator<Lifetime>> m_lifetimeGenerator;
		float m_maximumParticleLifetime;

	public:
		ParticleSpawner(std::unique_ptr<AttributeGenerator<Position>> positionGenerator, std::unique_ptr<AttributeGenerator<Velocity>> velocityGenerator, std::unique_ptr<AttributeGenerator<Scale>> scaleGenerator, std::unique_ptr<AttributeGenerator<Color>> colorGenerator, std::unique_ptr<AttributeGenerator<Lifetime>> lifetimeGenerator, float maximumParticleLifetime);

		std::unique_ptr<ParticleSpawner> clone() const;
		float getMaxiumParticleLifetime() const;
		std::vector<Particle> spawn(unsigned int count, float elapsedTime, float deltaTime, unsigned int id);
	};
}