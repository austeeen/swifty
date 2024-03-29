cmake_minimum_required(VERSION 3.16.3)

project(${APP_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -ggdb3")
set(CMAKE_BUILD_TYPE Debug)

set(SFML_DIR "C:/msys64/mingw64/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src, ${CMAKE_SOURCE_DIR}/deps)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB BUILD_DEPS ${CMAKE_SOURCE_DIR}/deps/*.cpp)

add_executable(
    ${APP_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${SOURCES}
    ${BUILD_DEPS}
)
target_include_directories(${APP_NAME} PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(${APP_NAME} sfml-graphics sfml-window sfml-system)
