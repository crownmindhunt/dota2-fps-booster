cmake_minimum_required(VERSION 3.24)
project(dota2_fps_booster LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4 /permissive- /EHsc /utf-8)
    add_compile_definitions(NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

add_subdirectory(src/tweaker-core)
add_subdirectory(src/ingest-handlers)
add_subdirectory(src/processors)
add_subdirectory(src/output-drivers)
add_subdirectory(src/job-utils)

enable_testing()
add_subdirectory(tests)