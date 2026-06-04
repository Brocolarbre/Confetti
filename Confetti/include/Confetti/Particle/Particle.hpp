#pragma once

#include <glm/glm.hpp>

namespace cft
{
	struct Particle
	{
		glm::vec4 color;
		glm::vec4 initialColor;
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec2 scale;
		glm::vec2 initialScale;
		float phase;
		float lifetime;
		float spawnTime;
		unsigned int id;
	};

	struct ParticleView
	{
		glm::vec4& color;
		const glm::vec4& initialColor;
		glm::vec3& position;
		glm::vec3& velocity;
		glm::vec2& scale;
		const glm::vec2& initialScale;
		const float& phase;
		const float& lifetime;
		const float& spawnTime;
		const unsigned int& id;
	};
}