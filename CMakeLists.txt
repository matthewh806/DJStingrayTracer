cmake_minimum_required(VERSION 3.18)

set(CMAKE_XCODE_GENERATE_SCHEME true)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE STRING "Minimum OS X deployment version")
set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)" CACHE STRING "" FORCE)

project(RayTracer VERSION 1.0.0 LANGUAGES C CXX)

file(GLOB RAY_TRACER_SOURCES
    source/json.hpp
    source/cxxopts.hpp
    source/vec3.hpp
    source/colour.hpp
    source/ray.hpp
    source/hittable.hpp
    source/hittablelist.hpp
    source/sphere.hpp
    source/camera.hpp
    source/utils.hpp
    source/main.cpp
)
source_group("source" FILES ${RAY_TRACER_SOURCES})

add_executable(WeekendRayTracer ${RAY_TRACER_SOURCES})
set_target_properties(WeekendRayTracer PROPERTIES CXX_STANDARD 17)

if(APPLE)
    set_target_properties(WeekendRayTracer PROPERTIES XCODE_SCHEME_ARGUMENTS "-i ${CMAKE_CURRENT_SOURCE_DIR}/world_data/basic_world.json")
endif()
