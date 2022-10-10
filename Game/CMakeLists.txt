# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (UnrealTournament CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(source_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE vhead "${include_dir}/*/*.h")
file(GLOB_RECURSE vsrc "${source_dir}/*.cpp")

add_executable(${PROJECT_NAME} ${vhead} ${vsrc})

target_link_libraries(${PROJECT_NAME} PRIVATE VEngine)
target_include_directories(${PROJECT_NAME} PRIVATE ${include_dir})
