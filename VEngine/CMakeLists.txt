# CMakeList.txt : CMake project for Unreal, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(VEngine CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


set(include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(source_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE vhead "${include_dir}/*/*.h")
file(GLOB_RECURSE vsrc "${source_dir}/*.cpp")

add_library (${PROJECT_NAME} STATIC ${vhead} ${vsrc})

target_include_directories(${PROJECT_NAME} PUBLIC ${include_dir})

