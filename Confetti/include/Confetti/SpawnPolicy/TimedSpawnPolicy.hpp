#pragma once

#include "SpawnPolicy.hpp"

namespace cft
{
	class TimedSpawnPolicy : public SpawnPolicy
	{
	private:
		unsigned int m_count;
		unsigned int m_interval;
		float m_spawnRate;
		float m_accumulator;
		float m_duration;
		float m_progress;

	public:
		TimedSpawnPolicy(unsigned int count, unsigned int interval, float duration);

		std::unique_ptr<SpawnPolicy> clone() const override;
		float getSpawnRate() const override;
		unsigned int getSpawnCount(float elapsedTime, float deltaTime) override;
	};
}