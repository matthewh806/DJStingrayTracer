#pragma once

#include "ray.hpp"

struct HitRecord
{
    point3 p;
    Vec3 normal;
    double t;
};

class Hittable
{
public:
    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
};
