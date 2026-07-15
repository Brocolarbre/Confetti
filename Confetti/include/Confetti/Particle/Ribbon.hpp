#pragma once

#include <glm/glm.hpp>

namespace cft
{
	struct Ribbon
	{
		unsigned int ribbonRegistryId;
		unsigned int fromParticleId;
		unsigned int toParticleId;
	};
}