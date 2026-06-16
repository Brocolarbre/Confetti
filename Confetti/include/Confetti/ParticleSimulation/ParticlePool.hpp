#pragma once

#include "Confetti/Particle/Particle.hpp"

#include <vector>

namespace cft
{
	class ParticlePool
	{
	private:
		std::vector<glm::vec4> m_color;
		std::vector<glm::vec4> m_initialColor;
		std::vector<glm::vec3> m_position;
		std::vector<glm::vec3> m_velocity;
		std::vector<glm::quat> m_rotation;
		std::vector<glm::vec3> m_angularVelocity;
		std::vector<glm::vec3> m_scale;
		std::vector<glm::vec3> m_initialScale;
		std::vector<float> m_phase;
		std::vector<float> m_lifetime;
		std::vector<float> m_spawnTime;
		std::vector<unsigned int> m_id;

		unsigned int m_capacity;
		unsigned int m_reservedCapacity;
		unsigned int m_count;

		void resize(unsigned int capacity);

	public:
		ParticlePool();

		const std::vector<glm::vec4>& getColor() const;
		const std::vector<glm::vec4>& getInitialColor() const;
		const std::vector<glm::vec3>& getPosition() const;
		const std::vector<glm::vec3>& getVelocity() const;
		const std::vector<glm::quat>& getRotation() const;
		const std::vector<glm::vec3>& getAngularVelocity() const;
		const std::vector<glm::vec3>& getScale() const;
		const std::vector<glm::vec3>& getInitialScale() const;
		const std::vector<float>& getPhase() const;
		const std::vector<float>& getLifetime() const;
		const std::vector<float>& getSpawnTime() const;
		const std::vector<unsigned int>& getId() const;

		std::vector<glm::vec4>& getColor();
		std::vector<glm::vec4>& getInitialColor();
		std::vector<glm::vec3>& getPosition();
		std::vector<glm::vec3>& getVelocity();
		std::vector<glm::quat>& getRotation();
		std::vector<glm::vec3>& getAngularVelocity();
		std::vector<glm::vec3>& getScale();
		std::vector<glm::vec3>& getInitialScale();
		std::vector<float>& getPhase();
		std::vector<float>& getLifetime();
		std::vector<float>& getSpawnTime();
		std::vector<unsigned int>& getId();

		unsigned int getCount() const;

		void reserve(unsigned int capacity);
		void insert(const Particle& particle);
		void remove(unsigned int index);
	};
}