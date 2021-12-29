cmake_minimum_required(VERSION 2.8)

if(POLICY CMP0015)
    cmake_policy(SET CMP0015 NEW)
endif()

# if(POLICY CMP0079)
#     cmake_policy(SET CMP0079 NEW)
# endif()

########################################################################
add_compile_options(-std=c++11)

add_executable(main main.cpp)
target_link_libraries(main ParsingLib GraphLib TraversalsLib DijkstraLib VisualizerLib)
