#pragma once

#include <random>

// Common Headers

// Constants

// Utility Functions
inline double randomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
