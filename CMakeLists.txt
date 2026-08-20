cmake_minimum_required(VERSION 3.16)
project(TheLegendEngine2D)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
# add_subdirectory(vendored/SDL_mixer EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(main WIN32 
    main.c 
    ./mem/cleanup.c 
    ./global/globals.c 
    ./map/map.c
    ./physics/velocity.c
)

# Link to the actual SDL3 library.
# SDL3_mixer::SDL3_mixer
target_link_libraries(main PRIVATE SDL3::SDL3)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)