
cmake_minimum_required (VERSION 3.12)
project ("rayTracer")

# Add include directories
include_directories ("include")	# standard include directory
include_directories ("include/glm-0.9.9.7/glm") # Directory for opengl Math library


# Add source to this project's executable.
add_executable (tracer "src/tracer.cpp")

# Adding Libraries
add_library(logger "src/log.cpp")
add_library(geometry "src/geometry.cpp")

# Linking Libraries
target_link_libraries(tracer logger)


# ---Building Examples ---

# Projectile motion example
add_executable(projectile_motion "examples/projectile_motion.cpp")


# test settings
enable_testing()

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "test")
add_library(catch_main "test/catch_main.cpp")


add_executable(tuple_test "test/verify_tuple.cpp")
target_link_libraries(tuple_test Catch catch_main)



enable_testing()
add_test(NAME Tuples COMMAND tuple_test)
