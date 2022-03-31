#pragma once

#include <iostream>
#include "vec3.hpp"

void writeColour(std::ostream& out, colour pixelColour, int samplesPerPixel)
{
    auto const scale = 1.0 / static_cast<double>(samplesPerPixel);
    // write translated [0, 255] value of each colour component
    out << static_cast<int>(256 * std::clamp(pixelColour.x() * scale, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * std::clamp(pixelColour.y() * scale, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * std::clamp(pixelColour.z() * scale, 0.0, 0.999)) << '\n';
}
