cmake_minimum_required(VERSION 3.0.0)
project(game VERSION 0.1.0)
include(CTest)
enable_testing()
set(SDL2_DIR ./SDL2/x86)
set(SDL2_mixer_DIR ./SDL2_mixer/x86)
set(SDL2_image_DIR ./SDL2_image/x86)
set(SDL2_ttf_DIR ./SDL2_ttf/x86)

include_directories(${SDL2_DIR}/include/SDL2)
link_directories(${SDL2_DIR}/lib)

include_directories(${SDL2_mixer_DIR}/include/SDL2)
link_directories(${SDL2_mixer_DIR}/lib)

include_directories(${SDL2_image_DIR}/include/SDL2)
link_directories(${SDL2_image_DIR}/lib)

include_directories(${SDL2_ttf_DIR}/include/SDL2)
link_directories(${SDL2_ttf_DIR}/lib)

set(BIN_NAME game)
file(GLOB SRC src/*.cpp)
add_executable(${BIN_NAME} ${SRC})

#target_include_directories(${BIN_NAME} PUBLIC src)

target_link_libraries(game
        SDL2
        SDL2_mixer
        SDL2_image
        SDL2_ttf
        )
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
