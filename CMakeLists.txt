cmake_minimum_required(VERSION 3.12)
project(LaboratoryWork_4)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


add_executable(LaboratoryWork_4 main.cpp UnitTests.cpp)
target_link_libraries(LaboratoryWork_4 gtest gtest_main)