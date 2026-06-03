#include "Confetti/SpawnPolicy/ConstantSpawnPolicy.hpp"

#include <algorithm>

namespace cft
{
	ConstantSpawnPolicy::ConstantSpawnPolicy(unsigned int count, unsigned int interval) :
		m_count(std::max(count, 1u)),
		m_interval(std::max(interval, 1u)),
		m_frameCounter(0),
		m_spawnRate(static_cast<float>(m_count) / static_cast<float>(m_interval))
	{

	}

	std::unique_ptr<SpawnPolicy> ConstantSpawnPolicy::clone() const
	{
		return std::make_unique<ConstantSpawnPolicy>(*this);
	}

	float ConstantSpawnPolicy::getSpawnRate() const
	{
		return m_spawnRate;
	}

	unsigned int ConstantSpawnPolicy::getSpawnCount(float elapsedTime, float deltaTime)
	{
		if (++m_frameCounter >= m_interval)
		{
			m_frameCounter = 0;
			return m_count;
		}

		return 0;
	}
}