#pragma once

#include <random>

// Common Headers

// Constants
constexpr double pi = 3.1415926535897932385;

// Utility Functions
inline double randomDouble(double min, double max)
{
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble()
{
    randomDouble(0.0, 1.0);
}

inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}
