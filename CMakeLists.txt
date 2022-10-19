# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Unreal")

include(FetchContent)

# Include sub-projects.
add_subdirectory ("Plugins")
add_subdirectory ("VEngine")
add_subdirectory ("Game")
