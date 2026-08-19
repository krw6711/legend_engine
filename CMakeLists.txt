cmake_minimum_required(VERSION 3.16)
project(TheLegendEngine2D)

include(FetchContent)

FetchContent_Declare(
  SDL3_SRC
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  SOURCE_DIR     "${CMAKE_CURRENT_LIST_DIR}/vendored/SDL"
)

FetchContent_Declare(
  SDL3_MIXER
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer
  SOURCE_DIR     "${CMAKE_CURRENT_LIST_DIR}/vendored/SDL_mixer"
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(
    SDL3_SRC
    SDL3_MIXER
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Create your game executable target as usual
add_executable(main
    main.c
    cleanup.c
    globals.c
    map.c
)
target_link_libraries(main PRIVATE 
    SDL3::SDL3
    # SDL3_mixer::SDL3_mixer
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)