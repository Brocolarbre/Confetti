#pragma once

#include <cstdint>

namespace cft
{
    class SplitMix64
    {
    public:
        static std::uint64_t mix(std::uint64_t value);
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