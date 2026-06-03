#pragma once

#include "SpawnPolicy.hpp"

namespace cft
{
	class ConstantSpawnPolicy : public SpawnPolicy
	{
	private:
		unsigned int m_count;
		unsigned int m_interval;
		unsigned int m_frameCounter;
		float m_spawnRate;

	public:
		ConstantSpawnPolicy(unsigned int count, unsigned int interval);

		std::unique_ptr<SpawnPolicy> clone() const override;
		float getSpawnRate() const override;
		unsigned int getSpawnCount(float elapsedTime, float deltaTime) override;
	};
}