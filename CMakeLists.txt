cmake_minimum_required(VERSION 3.23)
project(universal_storage)

set(CMAKE_CXX_STANDARD 23)

if(NOT EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    message(FATAL_ERROR "No conanbuildinfo.cmake in build dir. (Didn't run 'conan install'?)" )
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
find_package(spdlog REQUIRED)


include_directories(.)

set (SOURCES block_manager.cpp)
add_library(universal_storage_lib ${SOURCES})

add_executable(universal_storage main.cpp)
target_link_libraries(universal_storage universal_storage_lib)
