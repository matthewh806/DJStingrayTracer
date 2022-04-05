#include <iostream>
#include <fstream>
#include <algorithm>
#include "json.hpp"
#include "cxxopts.hpp"
#include "vec3.hpp"
#include "colour.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hittablelist.hpp"
#include "material.hpp"
#include "camera.hpp"

#include "utils.hpp"

const double infinity = std::numeric_limits<double>::infinity();

colour rayColour(const Ray &ray, const Hittable& world, colour colourFrom, colour colourTo, int depth)
{
    HitRecord hitRecord;
    
    if(depth <= 0)
    {
        return colour(0.0, 0.0, 0.0);
    }
    
    if(world.hit(ray, 0.001, infinity, hitRecord))
    {
        Ray scatteredRay;
        colour attenuation;
        if(hitRecord.material->scatter(ray, hitRecord, attenuation, scatteredRay))
        {
            return attenuation * rayColour(scatteredRay, world, colourFrom, colourTo, depth-1);
        }
        
        return colour(0.0, 0.0, 0.0);
    }
    
    const Vec3 unitDirection = unitVector(ray.direction());
    const auto t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * colourFrom + t * colourTo;
}

void initialiseWorld(const double verticalFov = 90.0,
                     const int width = 400,
                     const point3& lookFrom = point3(0.0, 0.0, -1.0),
                     const point3& lookAt = point3(0.0, 0.0, 0.0),
                     const Vec3& vUp = Vec3(0.0, 1.0, 0.0),
                     const colour& colourFrom = colour(1.0, 1.0, 1.0),
                     const colour& colourTo = colour(0.5, 0.7, 1.0),
                     std::vector<std::shared_ptr<Hittable>> hittables = std::vector<std::shared_ptr<Hittable>>())
{
    // Image
    const auto aspectRatio = 16.0 / 9.0;
    const auto imageWidth = width;
    const auto imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const auto samplesPerPixel = 100;
    const auto maxDepth = 50;
    
    // World
    HittableList world;
    for(auto& hittable : hittables)
    {
        world.add(std::move(hittable));
    }
    
    // Camera
    Camera camera(verticalFov, aspectRatio, 1.0, lookFrom, lookAt, vUp);
    
    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(int j = imageHeight - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << "\n" << std::flush;
        for(int i = 0; i < imageWidth; ++i)
        {
            colour pixelColour(0.0, 0.0, 0.0);
            for(int s = 0; s < samplesPerPixel; ++s)
            {
                auto const u = static_cast<double>(i + randomDouble()) / (imageWidth - 1);
                auto const v = static_cast<double>(j + randomDouble()) / (imageHeight - 1);
                Ray r = camera.getRay(u, v);
                pixelColour += rayColour(r, world, colourFrom, colourTo, maxDepth);
            }
           
            writeColour(std::cout, pixelColour, samplesPerPixel);
        }
    }
    
    std::cerr << "\nDone.\n";
}

int main(int argc, char** argv)
{
    cxxopts::Options options("WeekendRayTracer", "A simple raytracer");
    options.add_options()
    ("i, inputdata", "path to input json data", cxxopts::value<std::string>());
    
    auto result = options.parse(argc, argv);
    
    std::string jsonPath = "";
    if(result.count("inputdata"))
    {
        jsonPath = result["inputdata"].as<std::string>();
    }
    
    if(jsonPath.empty())
    {
        std::cerr << "No json path specified\n";
        return 1;
    }
    
    std::ifstream inputStream(jsonPath);
    auto const inputDataJson = nlohmann::json::parse(inputStream);
    
    auto const convertVectorToVec3 = [](const std::vector<double>& vector) -> Vec3
    {
        return Vec3(vector[0], vector[1], vector[2]);
    };
    
    auto const width = inputDataJson.at("width").get<int>();
    auto const verticalFov = inputDataJson.at("verticalfieldofview").get<double>();
    auto const lookFrom = convertVectorToVec3(inputDataJson.at("lookfrom").get<std::vector<double>>());
    auto const lookAt = convertVectorToVec3(inputDataJson.at("lookat").get<std::vector<double>>());
    auto const vUp = convertVectorToVec3(inputDataJson.at("vup").get<std::vector<double>>());
    auto const colourFromVec = convertVectorToVec3(inputDataJson.at("colourfrom").get<std::vector<double>>());
    auto const colourToVec = convertVectorToVec3(inputDataJson.at("colourto").get<std::vector<double>>());
    auto const hittablesJson = inputDataJson.at("hittables");
    auto const materialsJson = inputDataJson.at("materials");

    std::vector<std::shared_ptr<Material>> materials;
    std::vector<std::string> materialTypes = {"Lambertian", "Metal", "Dielectric"};
    for(auto const& material : materialsJson)
    {
        auto const name = material.at("name").get<std::string>();
        auto const type = material.at("type");
        
        // TODO: not sustainable... improve!
        if(std::find(materialTypes.begin(), materialTypes.end(), type) == materialTypes.end())
        {
            std::cerr << "Invalid material type specified for " << name << "\n";
            return 1;
        }
        
        if(type == "Lambertian")
        {
            colour const albedo = convertVectorToVec3(material.at("albedo").get<std::vector<double>>());
            materials.push_back(std::make_shared<Lambertian>(name, albedo));
        }
        else if(type == "Metal")
        {
            colour const albedo = convertVectorToVec3(material.at("albedo").get<std::vector<double>>());
            auto const fuzz = material.at("fuzz").get<double>();
            materials.push_back(std::make_shared<Metal>(name, albedo, fuzz));
        }
        else if(type == "Dielectric")
        {
            auto const refractiveIndex = material.at("refractiveindex").get<double>();
            materials.push_back(std::make_shared<Dielectric>(name, refractiveIndex));
        }
    }
    
    std::vector<std::shared_ptr<Hittable>> hittables;
    for(auto const& hittable : hittablesJson)
    {
        auto const pos = convertVectorToVec3(hittable.at("position").get<std::vector<double>>());
        auto const radius = hittable.at("radius").get<double>();
        auto const materialName = hittable.at("material").get<std::string>();
        
        // check material exists
        auto material = std::find_if(materials.begin(), materials.end(), [&](std::shared_ptr<Material> material)
        {
            return material->getName() == materialName;
        });
        
        if(material == materials.end())
        {
            std::cerr << "Hittable points to invalid material type " << materialName << "\n";
            return 1;
        }
        
        hittables.push_back(std::make_shared<Sphere>(pos, radius, *material));
    }
    
    initialiseWorld(verticalFov, width, lookFrom, lookAt, vUp, colourFromVec, colourToVec, hittables);
}
