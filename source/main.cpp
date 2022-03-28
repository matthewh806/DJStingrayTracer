#include <iostream>
#include "vec3.hpp"
#include "colour.hpp"
#include "ray.hpp"

double hitSphere(const point3& center, double radius, const Ray& r)
{
    Vec3 oc = r.origin() - center;
    const auto a = r.direction().lengthSquared();
    const auto halfB = dot(r.direction(), oc);
    const auto c = oc.lengthSquared() - radius * radius;
    const auto discriminant = halfB * halfB - a*c;
    return discriminant < 0.0 ? -1.0 : (-halfB - std::sqrt(discriminant)) / a;
}

colour rayColour(const Ray &ray)
{
    auto t = hitSphere(point3(0.0, 0.0, -1.0), 0.5, ray);
    if(t > 0.0)
    {
        Vec3 n = unitVector(ray.at(t) - Vec3(0.0, 0.0, -1.0));
        return 0.5 * colour(n.x() + 1, n.y() + 1, n.z() + 1);
    }
    const Vec3 unitDirection = unitVector(ray.direction());
    t = 0.5 * (unitDirection.y() + 1.0);
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
