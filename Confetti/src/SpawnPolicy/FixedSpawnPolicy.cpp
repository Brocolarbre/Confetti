#include "Confetti/SpawnPolicy/FixedSpawnPolicy.hpp"

#include <algorithm>

namespace cft
{
	FixedSpawnPolicy::FixedSpawnPolicy(unsigned int count, unsigned int interval, unsigned int spawnCount) :
		m_count(std::max(count, 1u)),
		m_interval(std::max(interval, 1u)),
		m_spawnCount(std::max(spawnCount, 1u)),
		m_frameCounter(0),
		m_spawnRate(static_cast<float>(m_count) / static_cast<float>(m_interval))
	{

	}

	std::unique_ptr<SpawnPolicy> FixedSpawnPolicy::clone() const
	{
		return std::make_unique<FixedSpawnPolicy>(*this);
	}

	float FixedSpawnPolicy::getSpawnRate() const
	{
		return m_spawnRate;
	}

	unsigned int FixedSpawnPolicy::getSpawnCount(float elapsedTime, float deltaTime)
	{
		if (m_spawnCount == 0)
			return 0;

		if (++m_frameCounter >= m_interval)
		{
			--m_spawnCount;

			m_frameCounter = 0;
			return m_count;
		}

		return 0;
	}
}