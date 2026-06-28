#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace cft
{
	struct Particle
	{
		glm::vec4 color;
		glm::vec4 initialColor;
		glm::vec3 position;
		glm::vec3 velocity;
		glm::quat rotation;
		glm::vec3 angularVelocity;
		glm::vec3 scale;
		glm::vec3 initialScale;
		float phase;
		float lifetime;
		float spawnTime;
		unsigned int id;
		unsigned int particleRegistryId;
	};

	struct ParticleView
	{
		glm::vec4& color;
		const glm::vec4& initialColor;
		glm::vec3& position;
		glm::vec3& velocity;
		glm::quat& rotation;
		glm::vec3& angularVelocity;
		glm::vec3& scale;
		const glm::vec3& initialScale;
		const float& phase;
		const float& lifetime;
		const float& spawnTime;
		const unsigned int& id;
		const unsigned int& particleRegistryId;
	};
}