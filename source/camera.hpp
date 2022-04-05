#pragma once

#include "vec3.hpp"
#include "ray.hpp"
#include "utils.hpp"

class Camera
{
public:
    Camera(double verticalFov, double aspectRatio, double focalLength, point3 lookFrom, point3 lookAt, Vec3 vup)
    : mOrigin(lookFrom)
    {
        auto const theta = degreesToRadians(verticalFov);
        auto const h = std::tan(theta / 2.0);
        auto const viewportHeight = 2.0 * h;
        auto const viewportWidth = aspectRatio * viewportHeight;
        
        auto w = unitVector(lookFrom - lookAt);
        auto u = unitVector(cross(vup, w));
        auto v = cross(w, u);
        
        mHorizontal = viewportWidth * u;
        mVertical = viewportHeight * v;
        mLowerLeftCorner = mOrigin - mHorizontal / 2.0 - mVertical / 2.0 - w;
    }
    
    Ray getRay(double s, double t)
    {
        return Ray(mOrigin, mLowerLeftCorner + s * mHorizontal + t * mVertical - mOrigin);
    }
    
private:
    point3 mOrigin;
    point3 mLowerLeftCorner;
    Vec3 mHorizontal;
    Vec3 mVertical;
};
