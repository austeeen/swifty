cmake_minimum_required(VERSION 3.16.3)

project(${APP_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -ggdb3")
set(CMAKE_BUILD_TYPE Debug)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src, ${CMAKE_SOURCE_DIR}/deps)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB BUILD_DEPS ${CMAKE_SOURCE_DIR}/deps/*.cpp)

add_executable(
    ${APP_NAME}.app
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${SOURCES}
    ${BUILD_DEPS}
)
target_include_directories(${APP_NAME}.app PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(${APP_NAME}.app sfml-graphics sfml-window sfml-system)
