#include <iostream>
#include "vec3.hpp"
#include "colour.hpp"

int main()
{
    const int image_width = 256;
    const int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << "\n" << std::flush;
        for(int i = 0; i < image_width; ++i)
        {
            colour pixelColour(static_cast<double>(i) / (image_width - 1), static_cast<double>(j) / (image_height - 1), 0.25);
            writeColour(std::cout, pixelColour);
        }
    }
    
    std::cerr << "\nDone.\n";
}
