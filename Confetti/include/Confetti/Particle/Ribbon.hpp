#pragma once

#include <glm/glm.hpp>

namespace cft
{
	struct Ribbon
	{
		unsigned int ribbonRegistryId;
		unsigned int fromParticleId;
		unsigned int toParticleId;
		glm::vec4 fromParticleColor;
		glm::vec4 toParticleColor;
		glm::vec4 fromColor;
		glm::vec4 toColor;
		glm::vec3 fromPosition;
		glm::vec3 toPosition;
		float fromThickness;
		float toThickness;
		float spawnTime;
	};

	struct RibbonView
	{
		const unsigned int& ribbonRegistryId;
		const unsigned int& fromParticleId;
		const unsigned int& toParticleId;
		const glm::vec4& fromParticleColor;
		const glm::vec4& toParticleColor;
		glm::vec4& fromColor;
		glm::vec4& toColor;
		glm::vec3& fromPosition;
		glm::vec3& toPosition;
		float& fromThickness;
		float& toThickness;
		const float& spawnTime;
	};

	struct ConstantRibbonView
	{
		const unsigned int& ribbonRegistryId;
		const unsigned int& fromParticleId;
		const unsigned int& toParticleId;
		const glm::vec4& fromParticleColor;
		const glm::vec4& toParticleColor;
		const glm::vec4& fromColor;
		const glm::vec4& toColor;
		const glm::vec3& fromPosition;
		const glm::vec3& toPosition;
		const float& fromThickness;
		const float& toThickness;
		const float& spawnTime;
	};
}