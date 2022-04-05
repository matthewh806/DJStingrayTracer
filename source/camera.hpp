#pragma once

#include "vec3.hpp"
#include "ray.hpp"
#include "utils.hpp"

class Camera
{
public:
    Camera(double verticalFov, double aspectRatio, double focusDistance, double aperture, point3 lookFrom, point3 lookAt, Vec3 vup)
    : mOrigin(lookFrom)
    , mLensRadius(aperture / 2.0)
    {
        auto const theta = degreesToRadians(verticalFov);
        auto const h = std::tan(theta / 2.0);
        auto const viewportHeight = 2.0 * h;
        auto const viewportWidth = aspectRatio * viewportHeight;
        
        mW = unitVector(lookFrom - lookAt);
        mU = unitVector(cross(vup, mW));
        mV = cross(mW, mU);
        
        mHorizontal = viewportWidth * mU;
        mVertical = viewportHeight * mV;
        mLowerLeftCorner = mOrigin - mHorizontal / 2.0 - mVertical / 2.0 - focusDistance * mW;
    }
    
    Ray getRay(double s, double t)
    {
        Vec3 rd = mLensRadius * randomInUnitDisk();
        Vec3 offset = rd.x() * mU + rd.y() * mV;
        return Ray(mOrigin + offset, mLowerLeftCorner + s * mHorizontal + t * mVertical - mOrigin - offset);
    }
    
private:
    point3 mOrigin;
    point3 mLowerLeftCorner;
    Vec3 mHorizontal;
    Vec3 mVertical;
    Vec3 mU, mV, mW;
    double mLensRadius;
};
