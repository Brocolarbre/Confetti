#include "Confetti/Tool/Seedable.hpp"

namespace cft
{
	std::optional<std::uint64_t> Seedable::getSeed() const
	{
		return std::nullopt;
	}

	void Seedable::setSeed(std::uint64_t seed)
	{

	}
}