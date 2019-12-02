cmake_minimum_required (VERSION 3.10.0)

# C++ Language Version
set(CMAKE_CXX_STANDARD 17)

# PROJECT NAME
project(pdf-plus)

file(GLOB_RECURSE PDFP_SOURCES src/*.cpp lodepng/*.cpp)
file(GLOB_RECURSE PDFP_HEADER include/*.h*)

file(GLOB_RECURSE EXAMPLE_SOURCES example/*.cpp)
file(GLOB_RECURSE EXAMPLE_HEADER example/*.h*)

add_library(pdf-plus ${PDFP_SOURCES} ${PDFP_HEADER})
add_executable(example ${EXAMPLE_SOURCES} ${EXAMPLE_HEADER})

# Copy resources for example
add_custom_command(TARGET example POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/example/*.png ${CMAKE_SOURCE_DIR}/example/*.u3d $<TARGET_FILE_DIR:example>/)


include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(ZLIB)
if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries(example ${ZLIB_LIBRARIES})
endif()

target_link_libraries(example pdf-plus)


