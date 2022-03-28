#pragma once

#include <iostream>
#include "vec3.hpp"

void writeColour(std::ostream& out, colour pixelColour)
{
    // write translated [0, 255] value of each colour component
    out << static_cast<int>(255.99 * pixelColour.x()) << ' '
        << static_cast<int>(255.99 * pixelColour.y()) << ' '
        << static_cast<int>(255.99 * pixelColour.z()) << '\n';
}
