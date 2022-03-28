#pragma once

#include "vec3.hpp"

class Ray
{
public:
    Ray()
    {
        
    }
    
    Ray(const point3& origin, const Vec3& direction) : mOrigin(origin), mDirection(direction)
    {
        
    }
    
    point3 origin() const
    {
        return mOrigin;
    }
    
    Vec3 direction() const
    {
        return mDirection;
    }
    
    point3 at(double t) const
    {
        return mOrigin + t * mDirection;
    }
    
private:
    point3 mOrigin;
    Vec3 mDirection;
};
