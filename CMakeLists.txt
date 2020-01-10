
cmake_minimum_required (VERSION 3.12)
project ("rayTracer")

# Add include directories
include_directories ("include")	# standard include directory
include_directories ("include/glm-0.9.9.7/glm") # Directory for opengl Math library


# Add source to this project's executable.
add_executable (tracer "src/tracer.cpp")

# Adding Libraries
add_library(log "src/log.cpp")

# Linking Libraries
target_link_libraries(tracer log)

# TODO: Add tests and install targets if needed.
