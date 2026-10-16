add_library(output-drivers STATIC
    cfg_writer.cpp
    registry_writer.cpp
    report_writer.cpp
)
target_link_libraries(output-drivers PUBLIC tweaker-core job-utils)