cmake_minimum_required(VERSION 3.16)
project(TheLegendEngine2D)

# include(CTest)
# find_program(MEMORYCHECK_COMMAND valgrind)
# set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --track-origins=yes")

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
# add_subdirectory(vendored/SDL_mixer EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(main WIN32 main.c)

# Link to the actual SDL3 library.
# SDL3_mixer::SDL3_mixer
target_link_libraries(main PRIVATE SDL3::SDL3)

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/teto.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/CCCP.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/china.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/eff1.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/eff2.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/teto2.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)