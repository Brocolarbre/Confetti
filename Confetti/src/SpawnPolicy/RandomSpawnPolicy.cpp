#include "Confetti/SpawnPolicy/RandomSpawnPolicy.hpp"

#include <algorithm>

namespace cft
{
	RandomSpawnPolicy::RandomSpawnPolicy(std::optional<unsigned int> count, std::optional<unsigned int> interval, unsigned int minimumCount, unsigned int maximumCount, unsigned int minimumInterval, unsigned int maximumInterval, RandomNumberGenerator& randomNumberGenerator) :
		m_count(count),
		m_interval(interval),
		m_spawnRate(0.0f),
		m_accumulator(0.0f),
		m_minimumCount(minimumCount),
		m_maximumCount(maximumCount),
		m_minimumInterval(minimumInterval),
		m_maximumInterval(maximumInterval),
		m_randomNumberGenerator(randomNumberGenerator)
	{
		if (m_count.has_value())
			m_count = std::max(m_count.value(), 1u);

		if (m_interval.has_value())
			m_interval = std::max(m_interval.value(), 1u);

		if (m_count.has_value() && m_interval.has_value())
			m_spawnRate = static_cast<float>(m_count.value()) / static_cast<float>(m_interval.value());
	}

	std::unique_ptr<SpawnPolicy> RandomSpawnPolicy::clone() const
	{
		return std::make_unique<RandomSpawnPolicy>(*this);
	}

	float RandomSpawnPolicy::getSpawnRate() const
	{
		return m_spawnRate;
	}

	unsigned int RandomSpawnPolicy::getSpawnCount(float elapsedTime, float deltaTime)
	{
		if (!m_count.has_value())
			m_count = static_cast<unsigned int>(m_randomNumberGenerator.generate(static_cast<float>(m_minimumCount), static_cast<float>(m_maximumCount)));

		if (m_interval.has_value())
			m_interval = static_cast<unsigned int>(m_randomNumberGenerator.generate(static_cast<float>(m_minimumInterval), static_cast<float>(m_maximumInterval)));

		if (!m_count.has_value() || !m_interval.has_value())
			m_spawnRate = static_cast<float>(m_count.value()) / static_cast<float>(m_interval.value());

		float spawnCount = m_spawnRate * deltaTime + m_accumulator;
		unsigned int roundedSpawnCount = static_cast<unsigned int>(spawnCount);
		m_accumulator = spawnCount - static_cast<float>(roundedSpawnCount);

		return roundedSpawnCount;
	}
}