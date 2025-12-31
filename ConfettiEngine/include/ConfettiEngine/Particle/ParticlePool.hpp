#pragma once

#include "ConfettiEngine/Tools/RandomNumberGenerator.hpp"

#include <vector>

namespace cft
{
	struct ParticleBoundaries
	{
		glm::vec4 minimumColor;
		glm::vec4 maximumColor;
		glm::vec3 minimumPosition;
		glm::vec3 maximumPosition;
		glm::vec3 minimumVelocity;
		glm::vec3 maximumVelocity;
		glm::vec2 minimumScale;
		glm::vec2 maximumScale;
		float minimumLifetime;
		float maximumLifetime;
	};

	struct Particle
	{
		glm::vec4 color;
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec2 scale;
		float lifetime;
		float spawnTime;

		static Particle create(RandomNumberGenerator& generator, const ParticleBoundaries& boundaries, float elapsedTime);
	};

	class ParticlePool
	{
	private:
		std::vector<glm::vec4> m_color;
		std::vector<glm::vec3> m_position;
		std::vector<glm::vec3> m_velocity;
		std::vector<glm::vec2> m_scale;
		std::vector<float> m_lifetime;
		std::vector<float> m_spawnTime;

		unsigned int m_capacity;
		unsigned int m_count;

	public:
		ParticlePool();

		const std::vector<glm::vec4>& getColor() const;
		const std::vector<glm::vec3>& getPosition() const;
		const std::vector<glm::vec2>& getScale() const;

		unsigned int getCapacity() const;
		unsigned int getCount() const;

		void createParticle(const Particle& particle);
		void destroyParticle(unsigned int index);

		void resize(unsigned int capacity);
		void update(float elapsedTime, float deltaTime);
	};
}