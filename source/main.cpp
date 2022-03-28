#include <iostream>
#include "vec3.hpp"
#include "colour.hpp"
#include "ray.hpp"

colour rayColour(const Ray &ray)
{
    const Vec3 unitDirection = unitVector(ray.direction());
    const auto t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const auto aspectRatio = 16.0 / 9.0;
    const auto imageWidth = 400;
    const auto imageHeight = static_cast<int>(imageWidth / aspectRatio);
    
    // Camera
    const auto viewportHeight = 2.0;
    const auto viewportWidth = aspectRatio * viewportHeight;
    const auto focalLength = 1.0;
    
    const auto origin = point3(0.0, 0.0, 0.0);
    const auto horizontal = Vec3(viewportWidth, 0.0, 0.0);
    const auto vertical = Vec3(0.0, viewportHeight, 0.0);
    const auto lowerLeftCorner = origin - horizontal / 2 -  vertical / 2 - Vec3(0.0, 0.0, focalLength);
    
    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = imageHeight - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << "\n" << std::flush;
        for(int i = 0; i < imageWidth; ++i)
        {
            auto const u = static_cast<double>(i) / (imageWidth - 1);
            auto const v = static_cast<double>(j) / (imageHeight - 1);
            Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            colour pixelColour = rayColour(r);
            writeColour(std::cout, pixelColour);
        }
    }
    
    std::cerr << "\nDone.\n";
}
