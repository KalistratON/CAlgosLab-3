CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
PROJECT(SortAlgo)

SET(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC/14.16.27023/bin/Hostx64/x64/cl.exe")

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory ("nanobench")
add_subdirectory ("googletest")

set_target_properties(gmock         PROPERTIES FOLDER "3rdparty")
set_target_properties(gmock_main    PROPERTIES FOLDER "3rdparty")
set_target_properties(gtest         PROPERTIES FOLDER "3rdparty")
set_target_properties(gtest_main    PROPERTIES FOLDER "3rdparty")

ADD_EXECUTABLE(SortAlgo ${SOURCE_FILES} ${HEADER_FILES})
ADD_EXECUTABLE(SortAlgoTest "${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp")

target_link_libraries(SortAlgo PRIVATE nanobench)
target_link_libraries(SortAlgoTest PRIVATE gtest gmock)

target_include_directories(SortAlgo PRIVATE ${nanobench_SOURCE_DIR}/include)
target_include_directories(SortAlgoTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})