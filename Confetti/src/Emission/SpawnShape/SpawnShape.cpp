#include "Confetti/Emission/SpawnShape/SpawnShape.hpp"

namespace cft
{
	std::vector<SpawnContext> SpawnShape::sample(unsigned int count) const
	{
		std::vector<SpawnContext> spawnContext;
		spawnContext.reserve(count);

		for (unsigned int i = 0; i < count; ++i)
			spawnContext.push_back(generateValue(count, i));

		return spawnContext;
	}
}