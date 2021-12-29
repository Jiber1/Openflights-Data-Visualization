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
add_library(VisualizerLib ${SOURCES} ${INCLUDES})

# Link
target_include_directories(VisualizerLib PUBLIC "./include" "../parsing/include" "../graph/include" "../dijsktra/include")

link_directories("../parsing")
target_link_libraries(VisualizerLib ParsingLib)

link_directories("../graph")
target_link_libraries(VisualizerLib GraphLib)

link_directories("../traversals")
target_link_libraries(VisualizerLib TraversalsLib)

link_directories("../dijkstra")
target_link_libraries(VisualizerLib DijkstraLib)


# Add the executable
add_executable(main-visualizer main.cpp)
target_link_libraries(main-visualizer VisualizerLib)

target_include_directories(main-visualizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# Add Catch2
Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.1
)

FetchContent_MakeAvailable(Catch2)
add_executable(test-visualizer ${SOURCES} ${TEST_SOURCES})
target_link_libraries(test-visualizer VisualizerLib Catch2::Catch2)