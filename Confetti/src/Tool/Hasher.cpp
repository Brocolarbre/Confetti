#include "Confetti/Tool/Hasher.hpp"

namespace cft
{
    std::uint64_t SplitMix64::mix(std::uint64_t value)
    {
        std::uint64_t z = value + 0x9E3779B97F4A7C15ULL;
        z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
        z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
        return z ^ (z >> 31);
    }
}