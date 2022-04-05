#pragma once

#include "hittablelist.hpp"
#include "material.hpp"

static HittableList generateRandomWorld()
{
    HittableList world;
    
    auto groundMaterial = std::make_shared<Lambertian>("ground", colour(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(point3(0.0, -1000.0, 0.0), 1000.0, groundMaterial));
    
    for(auto a = -11; a < 11; a++)
    {
        for(auto b = -11; b < 11; b++)
        {
            auto chooseMaterial = randomDouble();
            point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9*randomDouble());
            
            if((center - point3(4, 0.2, 0.0)).length() > 0.9)
            {
                std::shared_ptr<Material> sphereMaterial;
                
                if(chooseMaterial < 0.8)
                {
                    // diffuse
                    auto albedo = colour::random() * colour::random();
                    sphereMaterial = std::make_shared<Lambertian>("randDiffuse", albedo);
                    
                }
                else if(chooseMaterial < 0.95)
                {
                    // metal
                    auto albedo = colour::random(0.5, 1.0);
                    auto fuzz = randomDouble(0.0, 0.5);
                    sphereMaterial = std::make_shared<Metal>("randMetal", albedo, fuzz);
                }
                else
                {
                    // glass
                    sphereMaterial = std::make_shared<Dielectric>("randGlass", 1.5);
                }
                
                world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
            }
        }
    }
    
    auto material1 = std::make_shared<Dielectric>("randDielectric", 1.5);
    world.add(std::make_shared<Sphere>(point3(0.0, 1.0, 0.0), 1.0, material1));
              
    auto material2 = std::make_shared<Lambertian>("randLambertian", colour(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(point3(-4.0, 1.0, 0.0), 1.0, material2));
                        
    auto material3 = std::make_shared<Metal>("randMetal", colour(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(point3(4.0, 1.0, 0.0), 1.0, material3));
    
    return world;
}
