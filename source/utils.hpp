#pragma once

#include <random>

// Common Headers

// Constants

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
