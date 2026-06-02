#include "Confetti/SpawnPolicy/FixedSpawnPolicy.hpp"

#include <algorithm>

namespace cft
{
	FixedSpawnPolicy::FixedSpawnPolicy(unsigned int count, unsigned int interval, unsigned int spawnCount) :
		m_count(std::max(count, 1u)),
		m_interval(std::max(interval, 1u)),
		m_spawnRate(static_cast<float>(m_count) / static_cast<float>(m_interval)),
		m_accumulator(0.0f),
		m_spawnCount(std::max(spawnCount, 1u))
	{

	}

	std::unique_ptr<SpawnPolicy> FixedSpawnPolicy::clone() const
	{
		return std::make_unique<FixedSpawnPolicy>(*this);
	}

	float FixedSpawnPolicy::getSpawnRate() const
	{
		if (m_spawnCount == 0)
			return 0.0f;

		return m_spawnRate;
	}

	unsigned int FixedSpawnPolicy::getSpawnCount(float elapsedTime, float deltaTime)
	{
		if (m_spawnCount == 0)
			return 0;

		float spawnCount = m_spawnRate * deltaTime + m_accumulator;
		unsigned int roundedSpawnCount = static_cast<unsigned int>(spawnCount);
		m_accumulator = spawnCount - static_cast<float>(roundedSpawnCount);

		--m_spawnCount;

		return roundedSpawnCount;
	}
}