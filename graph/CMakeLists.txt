cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0015)
  cmake_policy(SET CMP0015 NEW)
endif()

# Specify the C++ standard (CMake3+)
add_compile_options(-std=c++11)

# Add header files
file(GLOB INCLUDES "includes/*.h")

# Add src files
file(GLOB SOURCES "src/*.cpp")

# Add testing sources
file(GLOB TEST_SOURCES "tests/*.cpp")

# Add library interface for our files
add_library(GraphLib ${SOURCES} ${INCLUDES})

# Link
target_include_directories(GraphLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "../graph/include")

link_directories("../parsing")
target_link_libraries(GraphLib ParsingLib)

# Add the executable
add_executable(main-graph main.cpp)
target_link_libraries(main-graph GraphLib)

target_include_directories(main-graph PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# Add Catch2
Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.1
)

FetchContent_MakeAvailable(Catch2)
add_executable(test-graph ${SOURCES} ${TEST_SOURCES})
target_link_libraries(test-graph GraphLib Catch2::Catch2)