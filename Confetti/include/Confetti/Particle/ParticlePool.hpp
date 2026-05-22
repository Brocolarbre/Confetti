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
		std::vector<unsigned int> m_forceFieldSetId;

		unsigned int m_capacity;
		unsigned int m_reservedCapacity;
		unsigned int m_count;

		void resize(unsigned int capacity);

	public:
		ParticlePool();

		const std::vector<glm::vec4>& getColor() const;
		const std::vector<glm::vec3>& getPosition() const;
		const std::vector<glm::vec3>& getVelocity() const;
		const std::vector<glm::vec2>& getScale() const;
		const std::vector<float>& getLifetime() const;
		const std::vector<float>& getSpawnTime() const;
		const std::vector<unsigned int>& getForceFieldSetId() const;

		std::vector<glm::vec4>& getColor();
		std::vector<glm::vec3>& getPosition();
		std::vector<glm::vec3>& getVelocity();
		std::vector<glm::vec2>& getScale();
		std::vector<float>& getLifetime();
		std::vector<float>& getSpawnTime();
		std::vector<unsigned int>& getForceFieldSetId();

		unsigned int getCount() const;

		void reserve(unsigned int capacity);
		void insert(const Particle& particle);
		void remove(unsigned int index);
	};
}