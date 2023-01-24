cmake_minimum_required(VERSION 3.0.0)

project(demo VERSION 0.1.0)

include(CTest)
enable_testing()

set(SDL2_DIR ./SDL2/x86)

set(SDL2_mixer_DIR ./SDL2_mixer/x86)


include_directories(${SDL2_DIR}/include/SDL2)
link_directories(${SDL2_DIR}/lib)

include_directories(${SDL2_mixer_DIR}/include/SDL2)
link_directories(${SDL2_mixer_DIR}/lib)

add_executable(game ./src/Game.cpp)
target_link_libraries(game
        SDL2
        SDL2_mixer
        )
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


