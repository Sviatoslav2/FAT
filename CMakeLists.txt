cmake_minimum_required(VERSION 3.5.1)
project(fse)

find_package(Boost 1.58.0 COMPONENTS filesystem system)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Image.cpp Image.h Root.cpp Root.h)
add_executable(fse ${SOURCE_FILES})
target_link_libraries(fse ${Boost_LIBRARIES})