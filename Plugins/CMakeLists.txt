cmake_minimum_required (VERSION 3.22)

set(PACKAGE_DIR ${CMAKE_BINARY_DIR}/packages)
set(PLUGINS_DIR ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

#Assimp
conan_cmake_configure(REQUIRES assimp/5.2.2
                      GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})



#WIL
FetchContent_Declare(
  wil
  GIT_REPOSITORY https://github.com/microsoft/wil.git
  GIT_TAG origin/master
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
)
FetchContent_GetProperties(wil)
if(NOT wil_POPULATED)
  FetchContent_Populate(wil)
endif()



find_program(NUGET_EXE NAMES nuget PATHS ${CMAKE_CURRENT_SOURCE_DIR}/NuGet)
if(NOT NUGET_EXE)
	message("NUGET.EXE not found.")
	message(FATAL_ERROR "Please install this executable, and run CMake again.")
endif()
message(${NUGET_EXE})

exec_program(${NUGET_EXE}
    ARGS install "Microsoft.Windows.CppWinRT" -OutputDirectory ${PACKAGE_DIR})
exec_program(${NUGET_EXE}
    ARGS install "DXSDK_Missing" -OutputDirectory ${PACKAGE_DIR})
exec_program(${NUGET_EXE}
    ARGS install "directxtex_desktop_win10" -OutputDirectory ${PACKAGE_DIR})



file(GLOB CPPWINRT_DIRS ${PACKAGE_DIR}/Microsoft.Windows.CppWinRT.*)
list(LENGTH CPPWINRT_DIRS CPPWINRT_DIRS_L)
if(${CPPWINRT_DIRS_L} GREATER 1)
    #Sort directories by version in descending order, so the first dir is top version
    list(SORT CPPWINRT_DIRS COMPARE NATURAL ORDER DESCENDING)
    list(GET CPPWINRT_DIRS 0 CPPWINRT_DIR)

    #Remove older version
    MATH(EXPR CPPWINRT_DIRS_L "${CPPWINRT_DIRS_L}-1")
    foreach(I RANGE 1 ${CPPWINRT_DIRS_L})
        list(GET CPPWINRT_DIRS ${I} OLD)
        file(REMOVE_RECURSE ${OLD})
    endforeach()
else()
    list(GET CPPWINRT_DIRS 0 CPPWINRT_DIR)
endif()

file(GLOB DXMISS_DIR ${PACKAGE_DIR}/DXSDK_Missing.*)
file(GLOB DXTEX_DIR ${PACKAGE_DIR}/directxtex_desktop_win10.*)

set(CPPWINRT_PROPS ${CPPWINRT_DIR}/build/native/Microsoft.Windows.CppWinRT.props PARENT_SCOPE)
set(CPPWINRT_TARGETS ${CPPWINRT_DIR}/build/native/Microsoft.Windows.CppWinRT.targets PARENT_SCOPE)
set(DXMISSING_HEADERS ${DXMISS_DIR}/Include PARENT_SCOPE)
set(DXTEX_HEADERS ${DXTEX_DIR}/include PARENT_SCOPE)
set(WIL_HEADERS "${wil_SOURCE_DIR}/include" PARENT_SCOPE)
set(CPPWINRT ${CPPWINRT_DIR}/bin/cppwinrt.exe)

execute_process(COMMAND
    ${CPPWINRT} -input sdk -output include
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    RESULT_VARIABLE ret)
if (NOT ret EQUAL 0)
    message(FATAL_ERROR "Failed to run cppwinrt.exe ${CPPWINRT_DIR} ${ret}")
endif()

