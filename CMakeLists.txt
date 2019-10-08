cmake_minimum_required(VERSION 3.7)
project(stegacito C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(STEGACITO_SOURCE_DIRECTORY ${CMAKE_BINARY_DIR}/stegacito/src)

file(GLOB_RECURSE SOURCES
        ${STEGACITO_SOURCE_DIRECTORY}/*.h
        ${STEGACITO_SOURCE_DIRECTORY}/*.c)

string(REGEX REPLACE "CMakeFiles/[^;]+;?" "" SOURCES "${SOURCES}")

add_executable(stegacito ${SOURCES})
target_link_libraries(stegacito m)
