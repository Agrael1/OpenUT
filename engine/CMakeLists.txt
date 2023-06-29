# CMakeList.txt : CMake project for Unreal, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.22)

project(VEngine CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


list(APPEND CMAKE_MODULE_PATH ${PLUGINS_DIR})
find_package(assimp REQUIRED)

add_subdirectory ("shaders")

set(include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(source_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(VENGINE_HEADERS ${include_dir} PARENT_SCOPE)

file(GLOB_RECURSE vhead "${include_dir}/*/*.h")
file(GLOB_RECURSE vsrc "${source_dir}/*.cpp")


add_library (${PROJECT_NAME} STATIC ${vhead} ${vsrc})

if(MSVC)
  target_compile_options(${PROJECT_NAME} PUBLIC "/ZI")
  target_link_options(${PROJECT_NAME} PUBLIC "/INCREMENTAL")
endif()

include_directories(BEFORE SYSTEM ${CMAKE_BINARY_DIR}/include)
target_compile_options(${PROJECT_NAME} PUBLIC /bigobj)
target_include_directories(${PROJECT_NAME} PUBLIC ${include_dir})
target_include_directories(${PROJECT_NAME} PUBLIC ${WIL_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${assimp_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${DXMISSING_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${DXTEX_HEADERS})
target_precompile_headers(${PROJECT_NAME} PUBLIC ${include_dir}/pch.h)
target_link_libraries(${PROJECT_NAME} PUBLIC d3d11 dxguid) 
target_link_libraries(${PROJECT_NAME} PUBLIC assimp::assimp) 
add_dependencies(${PROJECT_NAME} shaders)

