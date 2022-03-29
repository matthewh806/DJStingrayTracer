#pragma once

#include "vec3.hpp"
#include "hittable.hpp"

class Sphere : public Hittable
{
public:
    Sphere() {}
    Sphere(point3 center, double radius) : mCenter(center), mRadius(radius)
    {
        
    };
    
    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
    
private:
    point3 mCenter;
    double mRadius;
};

bool Sphere::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const
{
    Vec3 oc = r.origin() - mCenter;
    const auto a = r.direction().lengthSquared();
    const auto halfB = dot(r.direction(), oc);
    const auto c = oc.lengthSquared() - mRadius * mRadius;
    const auto discriminant = halfB * halfB - a*c;
    
    if(discriminant < 0.0)
    {
        return false;
    }
    
    auto const sqrtDiscriminant = std::sqrt(discriminant);
    auto const root = (-halfB - sqrtDiscriminant) / a;
    if(root < tMin || tMax < root)
    {
        auto const root = (-halfB + sqrtDiscriminant) / a;
        if(root < tMin || tMax < root)
        {
            return false;
        }
    }
    
    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - mCenter) / mRadius;
    
    return true;
}
