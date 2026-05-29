#pragma once

#include <memory>

namespace cft
{
	class SpawnPolicy
	{
	public:
		virtual ~SpawnPolicy() = default;

		virtual std::unique_ptr<SpawnPolicy> clone() const = 0;
		virtual float getSpawnRate() const = 0;
		virtual unsigned int getSpawnCount(float elapsedTime, float deltaTime) = 0;
	};
}