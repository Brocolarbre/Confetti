#pragma once

#include <glm/glm.hpp>

namespace cft
{
	struct RibbonPoint
	{
		glm::vec4 color;
		glm::vec3 position;
		float thickness;
		float distanceOnTrail;
		unsigned int particleId;
	};

	struct Ribbon
	{
		unsigned int ribbonRegistryId;
		RibbonPoint from;
		RibbonPoint to;
	};

	struct RibbonView
	{
		const unsigned int& ribbonRegistryId;
		const unsigned int& fromParticleId;
		const unsigned int& toParticleId;
	};
}