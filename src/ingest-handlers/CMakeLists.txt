add_library(ingest-handlers STATIC
    convar_ingest.cpp
    registry_ingest.cpp
    timer_resolution_ingest.cpp
)
target_link_libraries(ingest-handlers PUBLIC tweaker-core job-utils)