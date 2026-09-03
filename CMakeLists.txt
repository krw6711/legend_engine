cmake_minimum_required(VERSION 3.16)
project(TheLegendEngine2D)

# include(CTest)
# find_program(MEMORYCHECK_COMMAND valgrind)

include(FetchContent)
find_package(Git REQUIRED)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        main
    SOURCE_DIR     "${CMAKE_CURRENT_LIST_DIR}/vendored/SDL"
)   

FetchContent_Declare(
    SD3_TTF
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
    GIT_TAG        main
    SOURCE_DIR     "${CMAKE_CURRENT_LIST_DIR}/vendored/SDL_ttf"
) 
set(TARGET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendored")

if(EXISTS "${TARGET_DIR}/SDL/.git")
    message(STATUS "SDL Source exists")
else()
    message(STATUS "SDL Source cloning")
    FetchContent_MakeAvailable(SDL3)
endif()

if(EXISTS "${TARGET_DIR}/SDL_ttf/.git")
    message(STATUS "SDL_ttf Source exists")
else()
    message(STATUS "SDL_ttf Source cloning")
    FetchContent_MakeAvailable(SD3_TTF)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SDLTTF_VENDORED ON)

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
# add_subdirectory(vendored/SDL_mixer EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(main WIN32 
    main.c 
    ./mem/cleanup.c 
    ./global/globals.c 
    ./map/map.c
    ./map/camera.c
    ./physics/velocity.c
    ./global/iterate_event.c
    ./entities/player.c
    ./entities/entity.c
    ./dialogs/dialogs.c
)

# target_compile_options(main PRIVATE -fsanitize=address -g)
# target_link_options(main PRIVATE -fsanitize=address)

# Link to the actual SDL3 library.
# SDL3_mixer::SDL3_mixer
target_link_libraries(main PRIVATE SDL3_ttf::SDL3_ttf  SDL3::SDL3 m)

add_custom_command(
    TARGET main
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:main>/assets"
    COMMENT "Copying assets"
    VERBATIM
)