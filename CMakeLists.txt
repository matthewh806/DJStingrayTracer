cmake_minimum_required(VERSION 3.18)

set(CMAKE_XCODE_GENERATE_SCHEME true)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE STRING "Minimum OS X deployment version")
set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)" CACHE STRING "" FORCE)

project(RayTracer VERSION 1.0.0 LANGUAGES C CXX)

file(GLOB RAY_TRACER_SOURCES
    source/main.cpp
)
source_group("source" FILES ${RAY_TRACER_SOURCES})

add_executable(WeekendRayTracer ${RAY_TRACER_SOURCES})
set_target_properties(WeekendRayTracer PROPERTIES CXX_STANDARD 17)
