cmake_minimum_required(VERSION 3.13)
project(cse498-company-b)

# Configuration options
set(SDL_VERSION "3" CACHE STRING "SDL version (2 or 3)")
set(BUILD_OUTPUT "html" CACHE STRING "Output format (html or js)")

# Source files
file(GLOB SOURCES "*.cpp" "*.c")

# Determine output suffix
if(BUILD_OUTPUT STREQUAL "html")
    set(OUTPUT_SUFFIX ".html")
else()
    set(OUTPUT_SUFFIX ".js")
endif()

# Create executable
add_executable(index ${SOURCES})
set_target_properties(index PROPERTIES SUFFIX ${OUTPUT_SUFFIX})

# Emscripten compile options
target_compile_options(index PRIVATE
    -O2
    -Wall
    --use-port=sdl${SDL_VERSION}
)

# Emscripten link options
target_link_options(index PRIVATE
    --use-port=sdl${SDL_VERSION}
    -sALLOW_MEMORY_GROWTH=1
    -sMAXIMUM_MEMORY=1gb
    --emrun
)
