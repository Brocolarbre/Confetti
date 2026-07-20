#pragma once

#include "SpawnContext.hpp"
#include "Confetti/Tool/Cloneable.hpp"

#include <vector>

namespace cft
{
	class SpawnShape
	{
	protected:
		virtual SpawnContext generateValue(unsigned int count, unsigned int index) const = 0;

	public:
		virtual ~SpawnShape() = default;

		virtual std::vector<SpawnContext> sample(unsigned int count) const;
		virtual std::unique_ptr<SpawnShape> clone() const = 0;
	};
}