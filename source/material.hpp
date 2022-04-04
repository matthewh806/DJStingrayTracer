#pragma once

class Material
{
public:
    Material(std::string const& name) : mName(name)
    {
        
    }
    
    std::string getName() const
    {
        return mName;
    }
    
    virtual bool scatter(const Ray& rayIn, const HitRecord& hitRecord, colour& attenuation, Ray& scatteredRay) const = 0;
    
private:
    std::string mName;
};

class Lambertian : public Material
{
public:
    Lambertian(const std::string& name, const colour& albedo) : Material(name), mAlbedo(albedo)
    {
        
    }
    
    bool scatter(const Ray&, const HitRecord& hitRecord, colour& attenuation, Ray& scatteredRay) const override
    {
        auto scatterDirection = hitRecord.normal + randomUnitVector();
        if(scatterDirection.nearZero())
        {
            scatterDirection = hitRecord.normal;
        }
        
        scatteredRay = Ray(hitRecord.p, scatterDirection);
        attenuation = mAlbedo;
        
        return true;
    }
    
private:
    colour mAlbedo;
};

class Metal : public Material
{
public:
    Metal(const std::string& name, const colour& albedo, double fuzz) : Material(name), mAlbedo(albedo), mFuzz(fuzz < 1.0 ? fuzz : 1.0)
    {
        
    }
    
    bool scatter(const Ray& rayIn, const HitRecord& hitRecord, colour& attenuation, Ray& scatteredRay) const override
    {
        auto const reflectedRay = reflect(unitVector(rayIn.direction()), hitRecord.normal);
        scatteredRay = Ray(hitRecord.p, reflectedRay + mFuzz * randomInUnitSphere());
        attenuation = mAlbedo;
        return dot(scatteredRay.direction(), hitRecord.normal) > 0.0;
    }
    
private:
    colour mAlbedo;
    double mFuzz;
};
