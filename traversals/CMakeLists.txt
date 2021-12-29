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
add_library(TraversalsLib ${SOURCES} ${INCLUDES})

# Link
target_include_directories(TraversalsLib PUBLIC "./include" "../parsing/include" "../graph/include")

link_directories("../parsing")
target_link_libraries(TraversalsLib ParsingLib)

link_directories("../graph")
target_link_libraries(TraversalsLib GraphLib)


# Add the executable
add_executable(main-traversals main.cpp)
target_link_libraries(main-traversals TraversalsLib)

target_include_directories(main-traversals PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# Add Catch2
Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.1
)

FetchContent_MakeAvailable(Catch2)
add_executable(test-traversals ${SOURCES} ${TEST_SOURCES})
target_link_libraries(test-traversals TraversalsLib Catch2::Catch2)