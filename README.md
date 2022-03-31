# DJStingRayTracer

This is an implementation of a simple ray tracer following [Ray Tracing In One Weekend](https://raytracing.github.io/) by Peter Shirley

## Dependencies

I've directly included the two single file header dependencies ([json.hpp](https://github.com/nlohmann/json) and [cxxopts.hpp](https://github.com/jarro2783/cxxopts)) in the source directory so there are no library prerequisites to download / install.

## Compiling 

The simplest way is to use CMake

```
git clone git@github.com:matthewh806/DJStingrayTracer.git
cd DJStingrayTracer
mkdir build && cd build
cmake .. -GXcode
```

Change the argument for the -G flag according to your platform

## Building
From within the `build` directory:

```
cmake --build . --config Debug
```

Change the `--config` flag to Release if you really want (there's no difference at the moment beyond size of the binary).

This will create an executable in the `Debug` / `Release` directory. 

## Running

The executable expects one command line argument specified with an `-i / --inputdata` flag. This is a path to a `json` file containing world data for constructing the scene to be rendered (see `world_data/basic_world.json` for an example). 

Note: At the moment the rendered world pixel data is written to standard output - which isn't really very useful, so I would suggest redirecting it to a file on the command line. For example:

```
./WeekendRayTracer -i path/to/directory/DJStingrayTracer/world_data/basic_world.json > raytracer.ppm
```

This only works with absolute paths at the moment. Once this file is generated you can use a tool like [ToyViewer](https://apps.apple.com/us/app/toyviewer/id414298354?mt=12) (macOS) to see the rendered result. 

## Thanks

[DJ Stingray 313](https://www.youtube.com/watch?v=qmjniDKIA1Q) - for that mix and throwing great parties in general, but also for providing the inspiration for the (shitty) name for this project. The dream is to create a raycaster which can render an image of DJ Stingray 313 swimming & raving with real [stingrays](https://www.americanoceans.org/wp-content/uploads/2021/03/Stingray-anatomy.jpg). This will be 313 x 313 pixels in honour of his artist name change. 

[Peter Shirley](https://www.petershirley.com/) - without whom none of this would have been possible :') 