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

FetchContent_MakeAvailable(SDL3_SRC)
FetchContent_MakeAvailable(SDL3_MIXER)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# add_subdirectory(vendored/SDL_mixer EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_mixer EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(main WIN32 main.c cleanup.c globals.c map.c)

# Link to the actual SDL3 library.
# SDL3_mixer::SDL3_mixer
target_link_libraries(main PRIVATE SDL3::SDL3)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)