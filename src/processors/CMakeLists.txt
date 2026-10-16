add_library(processors STATIC
    priority_processor.cpp
    shader_cache_processor.cpp
    scheduler_processor.cpp
)
target_link_libraries(processors PUBLIC tweaker-core job-utils ingest-handlers)