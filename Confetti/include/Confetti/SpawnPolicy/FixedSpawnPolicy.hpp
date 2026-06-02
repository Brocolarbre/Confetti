#pragma once

#include "SpawnPolicy.hpp"

namespace cft
{
	class FixedSpawnPolicy : public SpawnPolicy
	{
	private:
		unsigned int m_count;
		unsigned int m_interval;
		float m_spawnRate;
		float m_accumulator;
		unsigned int m_spawnCount;

	public:
		FixedSpawnPolicy(unsigned int count, unsigned int interval, unsigned int spawnCount);

		std::unique_ptr<SpawnPolicy> clone() const override;
		float getSpawnRate() const override;
		unsigned int getSpawnCount(float elapsedTime, float deltaTime) override;
	};
}