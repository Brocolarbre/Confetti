#pragma once

namespace cft
{
    struct MotionStateInheritance
    {
        bool position = true;
        float linearVelocityFactor = 1.0f;
        bool rotation = true;
        float angularVelocityFactor = 1.0f;
    };
}