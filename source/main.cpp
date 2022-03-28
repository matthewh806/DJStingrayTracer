#include <iostream>

int main()
{
    const int image_width = 256;
    const int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << "\n" << std::flush;
        for(int i = 0; i < image_width; ++i)
        {
            auto const r = static_cast<double>(i) / (image_width - 1);
            auto const g = static_cast<double>(j) / (image_height - 1);
            auto const b = 0.0;

            auto const ir = static_cast<int>(255.99 * r); 
            auto const ig = static_cast<int>(255.99 * g);
            auto const ib = static_cast<int>(255.99 * b);

            std::cout << ir  << ' ' << ' ' << ig << ' ' << ib << "\n";
        }
    }
    
    std::cerr << "\nDone.\n";
}
