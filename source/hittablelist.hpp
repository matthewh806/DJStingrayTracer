#pragma once

#include <memory>
#include <vector>
#include "hittable.hpp"

class HittableList : public Hittable
{
public:
    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object)
    {
        add(object);
    }
    
    void clear()
    {
        mObjects.clear();
    }
    
    void add(std::shared_ptr<Hittable> object)
    {
        mObjects.push_back(object);
    }
    
    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
    
private:
    std::vector<std::shared_ptr<Hittable>> mObjects;
};

bool HittableList::hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const
{
    HitRecord tempHitRecord;
    bool hit = false;
    double closestHit = tMax;
    
    for(const auto& object : mObjects)
    {
        if(object->hit(r, tMin, closestHit, tempHitRecord))
        {
            hit = true;
            closestHit = tempHitRecord.t;
            rec = tempHitRecord;
        }
    }
    
    return hit;
}
