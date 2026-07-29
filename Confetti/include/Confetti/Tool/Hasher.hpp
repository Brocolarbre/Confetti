#pragma once

#include <cstdint>

namespace cft
{
    class SplitMix64
    {
    public:
        static std::uint64_t mix(std::uint64_t value)
        {
            std::uint64_t z = value + 0x9E3779B97F4A7C15ULL;
            z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
            z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
            return z ^ (z >> 31);
        }
    };

    class Hasher
    {
    public:
        template<typename ...Args>
        static std::uint64_t hash(Args... values)
        {
            std::uint64_t seed = 0;

            ((seed = SplitMix64::mix(seed ^ static_cast<uint64_t>(values))), ...);

            return seed;
        }
    };
}