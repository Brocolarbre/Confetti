#include "Confetti/SpawnPolicy/TimedSpawnPolicy.hpp"

#include <algorithm>

namespace cft
{
	TimedSpawnPolicy::TimedSpawnPolicy(unsigned int count, unsigned int interval, std::optional<float> duration) :
		m_count(std::max(count, 1u)),
		m_interval(std::max(interval, 1u)),
		m_duration(duration.has_value() ? std::max(duration.value(), 0.0f) : duration),
		m_spawnRate(static_cast<float>(m_count) / static_cast<float>(m_interval)),
		m_accumulator(0.0f)
	{

	}

	std::unique_ptr<SpawnPolicy> TimedSpawnPolicy::clone() const
	{
		return std::make_unique<TimedSpawnPolicy>(*this);
	}

	float TimedSpawnPolicy::getSpawnRate() const
	{
		return m_spawnRate;
	}

	unsigned int TimedSpawnPolicy::getSpawnCount(float elapsedTime, float deltaTime)
	{
		if (m_duration.has_value() && elapsedTime >= m_duration.value())
			return 0;

		float spawnCount = m_spawnRate * deltaTime + m_accumulator;
		unsigned int roundedSpawnCount = static_cast<unsigned int>(spawnCount);
		m_accumulator = spawnCount - static_cast<float>(roundedSpawnCount);

		return roundedSpawnCount;
	}
}