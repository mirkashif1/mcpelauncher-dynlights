cmake_minimum_required(VERSION 3.15)

project(mcpelauncherzoom)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(libhat
        GIT_REPOSITORY https://github.com/BasedInc/libhat.git
        GIT_TAG 5cf79adf86152233371b43adab5a0f9db6daa4e7
        EXCLUDE_FROM_ALL)

FetchContent_Declare(properties-parser
        GIT_REPOSITORY https://github.com/minecraft-linux/properties-parser.git
        GIT_TAG 69149a1cee5a0228492826bd71af1a32d73ed87e
        EXCLUDE_FROM_ALL)


FetchContent_MakeAvailable(libhat properties-parser)

add_library(mcpelauncherzoom SHARED src/main.cpp src/zoom.cpp src/zoom.h src/util.cpp src/util.h src/transition.cpp src/transition.h src/conf.cpp src/conf.h src/imgui.cpp src/imgui.h src/key_mapping.h)

target_link_libraries(mcpelauncherzoom PUBLIC libhat::libhat properties-parser)

install(TARGETS mcpelauncherzoom LIBRARY DESTINATION mods)
