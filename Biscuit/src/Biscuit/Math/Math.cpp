#include "pch.h"
#include "Math.h"

namespace Biscuit
{
    class Math
    {
        static float Clamp(float value, float min, float max)
        {
            return value < min ? min : value > max ? max : value;
        }

    };
}
