#pragma once

#include "vec3.hpp"
#include "ray.hpp"

class Camera
{
public:
    Camera(double aspectRatio, double viewportHeight, double focalLength, point3 origin)
    : mOrigin(origin)
    , mHorizontal(aspectRatio * viewportHeight, 0.0, 0.0)
    , mVertical(0.0, viewportHeight, 0.0)
    {
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
