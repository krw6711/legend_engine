cmake_minimum_required(VERSION 3.16)
project(TheLegendEngine2D)

include(FetchContent)

# 1. Define your local source paths
set(SDL3_LOCAL_DIR "${CMAKE_CURRENT_LIST_DIR}/vendored/SDL")
set(SDL3_MIXER_LOCAL_DIR "${CMAKE_CURRENT_LIST_DIR}/vendored/SDL_mixer")

# 2. Check if SDL3 files already exist locally
if(EXISTS "${SDL3_LOCAL_DIR}/CMakeLists.txt")
  message(STATUS "Found existing SDL3 local files, skipping git clone.")
  FetchContent_Declare(
    SDL3_SRC
    SOURCE_DIR "${SDL3_LOCAL_DIR}"
    DOWNLOAD_COMMAND ""  # <--- This strictly prevents Git network updates
  )
else()
  message(STATUS "SDL3 not found locally, preparing to download...")
  FetchContent_Declare(
    SDL3_SRC
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG main
    SOURCE_DIR "${SDL3_LOCAL_DIR}"
  )
endif()

# 3. Check if SDL_mixer files already exist locally
if(EXISTS "${SDL3_MIXER_LOCAL_DIR}/CMakeLists.txt")
  message(STATUS "Found existing SDL_mixer local files, skipping git clone.")
  FetchContent_Declare(
    SDL3_MIXER
    SOURCE_DIR "${SDL3_MIXER_LOCAL_DIR}"
    DOWNLOAD_COMMAND ""  # <--- This strictly prevents Git network updates
  )
else()
  message(STATUS "SDL_mixer not found locally, preparing to download...")
  FetchContent_Declare(
    SDL3_MIXER
    GIT_REPOSITORY https://github.com
    GIT_TAG main
    SOURCE_DIR "${SDL3_MIXER_LOCAL_DIR}"
  )
endif()

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
    SDL3::SDL3-shared  # Note: SDL3 uses SDL3::SDL3-shared or SDL3::SDL3-static
    # SDL3_mixer::SDL3_mixer
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
