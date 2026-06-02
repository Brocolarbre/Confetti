#pragma once

#include "SpawnPolicy.hpp"
#include "Confetti/Tools/RandomNumberGenerator.hpp"

#include <optional>

namespace cft
{
	class RandomSpawnPolicy : public SpawnPolicy
	{
	private:
		std::optional<unsigned int> m_count;
		std::optional<unsigned int> m_interval;
		float m_spawnRate;
		float m_accumulator;
		unsigned int m_minimumCount;
		unsigned int m_maximumCount;
		unsigned int m_minimumInterval;
		unsigned int m_maximumInterval;
		RandomNumberGenerator& m_randomNumberGenerator;

	public:
		RandomSpawnPolicy(std::optional<unsigned int> count, std::optional<unsigned int> interval, unsigned int minimumCount, unsigned int maximumCount, unsigned int minimumInterval, unsigned int maximumInterval, RandomNumberGenerator& randomNumberGenerator);

		std::unique_ptr<SpawnPolicy> clone() const override;
		float getSpawnRate() const override;
		unsigned int getSpawnCount(float elapsedTime, float deltaTime) override;
	};
}