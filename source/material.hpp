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

class Dielectric : public Material
{
public:
    Dielectric(const std::string& name, double refractionIndex) : Material(name), mRefractionIndex(refractionIndex)
    {
        
    }
    
    bool scatter(const Ray& rayIn, const HitRecord& hitRecord, colour& attenuation, Ray& scatteredRay) const override
    {
        attenuation = colour(1.0, 1.0, 1.0);
        auto refractionRatio = hitRecord.frontFace ? 1.0 / mRefractionIndex : mRefractionIndex;
        
        Vec3 unitDirection = unitVector(rayIn.direction());
        double cosTheta = std::fmin(dot(-unitDirection, hitRecord.normal), 1.0);
        double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
        
        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        Vec3 direction = cannotRefract ? reflect(unitDirection, hitRecord.normal) : refract(unitDirection, hitRecord.normal, refractionRatio);
        scatteredRay = Ray(hitRecord.p, direction);
        return true;
    }
    
private:
    double mRefractionIndex;
};
