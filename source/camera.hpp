#pragma once

#include "vec3.hpp"
#include "ray.hpp"
#include "utils.hpp"

class Camera
{
public:
    Camera(double verticalFov, double aspectRatio, double focalLength, point3 origin)
    : mOrigin(origin)
    {
        auto const theta = degreesToRadians(verticalFov);
        auto const h = std::tan(theta / 2.0);
        auto const viewportHeight = 2.0 * h;
        auto const viewportWidth = aspectRatio * viewportHeight;
        
        mHorizontal = Vec3(viewportWidth, 0.0, 0.0);
        mVertical = Vec3(0.0, viewportHeight, 0.0);
        mLowerLeftCorner = mOrigin - mHorizontal / 2.0 - mVertical / 2.0 - Vec3(0.0, 0.0, focalLength);
    }
    
    Ray getRay(double u, double v)
    {
        return Ray(mOrigin, mLowerLeftCorner + u * mHorizontal + v * mVertical - mOrigin);
    }
    
private:
    point3 mOrigin;
    point3 mLowerLeftCorner;
    Vec3 mHorizontal;
    Vec3 mVertical;
};
