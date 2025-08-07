cmake_minimum_required(VERSION 3.21)

project(ObjectPoolProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ObjectPool SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ObjectPool.cpp
)

target_include_directories(ObjectPool PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE ObjectPool)


enable_testing()
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
add_executable(test_ObjectPool tests/test_ObjectPool.cpp)
target_link_libraries(test_ObjectPool PRIVATE GTest::gtest_main ObjectPool)
gtest_discover_tests(test_ObjectPool)