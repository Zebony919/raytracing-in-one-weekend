cmake_minimum_required(VERSION 3.1.0...4.0.0)
project(RTWeekend LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_ONE_WEEKEND
  src/InOneWeekend/main.cpp
  src/InOneWeekend/vec3.h
  src/InOneWeekend/color.h
  src/InOneWeekend/ray.h
  src/InOneWeekend/hittable.h
  src/InOneWeekend/sphere.h
  src/InOneWeekend/rtweekend.h
  src/InOneWeekend/camera.h
)

include_directories(src)
add_executable(inOneWeekend ${SOURCE_ONE_WEEKEND})