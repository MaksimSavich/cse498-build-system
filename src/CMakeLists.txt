cmake_minimum_required(VERSION 3.13)
project(cse498-company-b)

#Configuration options
set(SDL_VERSION "2" CACHE STRING "SDL version (2 or 3)")
set(BUILD_OUTPUT "html" CACHE STRING "Output format (html or js)")
set(BUILD_TESTS OFF CACHE BOOL "Build tests")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Source files
set(LIB_SOURCES math_utils.cpp) # excludes main for testing
set(MAIN_SOURCE main.cpp)

if(BUILD_TESTS)
#Fetch Catch2 v3 from GitHub
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.12.0
    )
    FetchContent_MakeAvailable(Catch2)

#Create library from math sources
    add_library(math_utils_lib ${LIB_SOURCES})

#Create test executable
    add_executable(tests ../tests/test_math_utils.cpp)
    target_link_libraries(tests PRIVATE math_utils_lib Catch2::Catch2WithMain)
    target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#Emscripten compatibility - disable POSIX signals
    target_compile_definitions(tests PRIVATE CATCH_CONFIG_NO_POSIX_SIGNALS)

#Output as.js for Node.js execution
    set_target_properties(tests PROPERTIES SUFFIX ".js")
    target_link_options(tests PRIVATE
        -sNODERAWFS=1
        -sALLOW_MEMORY_GROWTH=1
    )
else()
#Emscripten build
    file(GLOB SOURCES "*.cpp" "*.c")

#Determine output suffix
    if(BUILD_OUTPUT STREQUAL "html")
        set(OUTPUT_SUFFIX ".html")
    else()
        set(OUTPUT_SUFFIX ".js")
    endif()

#Create executable
    add_executable(index ${SOURCES})
    set_target_properties(index PROPERTIES SUFFIX ${OUTPUT_SUFFIX})

#Emscripten compile options
    target_compile_options(index PRIVATE
        -O2
        -Wall
        --use-port=sdl${SDL_VERSION}
    )

#Emscripten link options
    target_link_options(index PRIVATE
        --use-port=sdl${SDL_VERSION}
        -sALLOW_MEMORY_GROWTH=1
        -sMAXIMUM_MEMORY=1gb
        -sEXPORTED_RUNTIME_METHODS=ccall,cwrap
        --emrun
    )
endif()
