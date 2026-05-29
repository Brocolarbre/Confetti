#pragma once

#include "SpawnPolicy.hpp"

namespace cft
{
	class ConstantSpawnPolicy : public SpawnPolicy
	{
	private:
		float m_spawnRate;
		float m_accumulator;

	public:
		ConstantSpawnPolicy(float spawnRate);

		std::unique_ptr<SpawnPolicy> clone() const override;
		float getSpawnRate() const override;
		unsigned int getSpawnCount(float elapsedTime, float deltaTime) override;
	};
}