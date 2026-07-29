#pragma once

#include <cstdlib>
#include <optional>

namespace cft
{
	class Seedable
	{
	public:
		virtual ~Seedable() = default;

		virtual std::optional<std::uint64_t> getSeed() const;
		virtual void setSeed(std::uint64_t seed);
	};
}