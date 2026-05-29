#include "Confetti/SpawnPolicy/ConstantSpawnPolicy.hpp"

namespace cft
{
	ConstantSpawnPolicy::ConstantSpawnPolicy(float spawnRate) :
		m_spawnRate(spawnRate),
		m_accumulator(0.0f)
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
		float spawnCount = m_spawnRate * deltaTime + m_accumulator;
		unsigned int roundedSpawnCount = static_cast<unsigned int>(spawnCount);
		m_accumulator = spawnCount - static_cast<float>(roundedSpawnCount);

		return roundedSpawnCount;
	}
}