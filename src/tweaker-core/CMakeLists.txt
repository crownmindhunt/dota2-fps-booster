add_library(tweaker-core STATIC
    tweak_registry.cpp
    revert_map.cpp
    vac_denylist.cpp
    config_paths.cpp
)

target_include_directories(tweaker-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tweaker-core PUBLIC job-utils)