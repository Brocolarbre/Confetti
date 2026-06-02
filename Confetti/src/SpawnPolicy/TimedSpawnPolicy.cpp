#include "Confetti/SpawnPolicy/TimedSpawnPolicy.hpp"

#include <algorithm>

namespace cft
{
	TimedSpawnPolicy::TimedSpawnPolicy(unsigned int count, unsigned int interval, float duration) :
		m_count(std::max(count, 1u)),
		m_interval(std::max(interval, 1u)),
		m_spawnRate(static_cast<float>(m_count) / static_cast<float>(m_interval)),
		m_accumulator(0.0f),
		m_duration(std::max(duration, 0.0f)),
		m_progress(0.0f)
	{

	}

	std::unique_ptr<SpawnPolicy> TimedSpawnPolicy::clone() const
	{
		return std::make_unique<TimedSpawnPolicy>(*this);
	}

	float TimedSpawnPolicy::getSpawnRate() const
	{
		if (m_progress >= m_duration == 0)
			return 0.0f;

		return m_spawnRate;
	}

	unsigned int TimedSpawnPolicy::getSpawnCount(float elapsedTime, float deltaTime)
	{
		m_progress = elapsedTime;

		if (elapsedTime >= m_duration)
			return 0;

		float spawnCount = m_spawnRate * deltaTime + m_accumulator;
		unsigned int roundedSpawnCount = static_cast<unsigned int>(spawnCount);
		m_accumulator = spawnCount - static_cast<float>(roundedSpawnCount);

		return roundedSpawnCount;
	}
}