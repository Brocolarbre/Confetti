#pragma once

#include "SpawnPolicy.hpp"

#include <optional>

namespace cft
{
	class TimedSpawnPolicy : public SpawnPolicy
	{
	private:
		unsigned int m_count;
		unsigned int m_interval;
		std::optional<float> m_duration;
		float m_spawnRate;
		float m_accumulator;

	public:
		TimedSpawnPolicy(unsigned int count, unsigned int interval, std::optional<float> duration);

		std::unique_ptr<SpawnPolicy> clone() const override;
		float getSpawnRate() const override;
		unsigned int getSpawnCount(float elapsedTime, float deltaTime) override;
	};
}