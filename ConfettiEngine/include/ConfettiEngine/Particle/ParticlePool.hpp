#pragma once

#include "Particle.hpp"

#include <vector>

namespace cft
{
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