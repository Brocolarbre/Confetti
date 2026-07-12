#pragma once

#include "SpawnContext.hpp"

#include <memory>
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

	template <typename Derived>
	class CloneableSpawnShape : public SpawnShape
	{
	public:
		std::unique_ptr<SpawnShape> clone() const override;
	};

	template<typename Derived>
	inline std::unique_ptr<SpawnShape> CloneableSpawnShape<Derived>::clone() const
	{
		return std::make_unique<Derived>(static_cast<const Derived&>(*this));
	}
}