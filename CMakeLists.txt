
cmake_minimum_required (VERSION 3.12)
project ("rayTracer")

#Variables
set(TEST_BIN_DIR "${CMAKE_BINARY_DIR}/tests")
set(EXAMPLE_BIN_DIR "${CMAKE_BINARY_DIR}/examples")

# Put executables in the bin subdirectory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Add include directories
include_directories ("include")	# standard include directory
include_directories ("include/glm-0.9.9.7/glm") # Directory for opengl Math library


# Add source to this project's executable.
add_executable (tracer "src/tracer.cpp")

# Adding Libraries
add_library(logger "src/log.cpp")
add_library(geometry "src/geometry.cpp")
add_library(canvas "src/canvas.cpp")

# Linking Libraries
target_link_libraries(tracer logger)


# ---Building Examples ---

# Projectile motion example
add_executable(projectileMotion "examples/projectile_motion.cpp")
set_target_properties(projectileMotion PROPERTIES RUNTIME_OUTPUT_DIRECTORY EXAMPLE_BIN_DIRECTORY)


# ---Tests---
enable_testing()

# Adding Catch which manages test routines
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "test")
add_library(catch_main "test/catch_main.cpp")

# Tuple/GLM Test
add_executable(testTuple "test/verify_tuple.cpp")
set_target_properties(testTuple PROPERTIES RUNTIME_OUTPUT_DIRECTORY TEST_BIN_DIRECTORY)
target_link_libraries(testTuple Catch catch_main)

# Canvas Test
add_executable(testCanvas "test/testCanvas.cpp")
set_target_properties(testCanvas PROPERTIES RUNTIME_OUTPUT_DIRECTORY TEST_BIN_DIRECTORY)
target_link_libraries(testCanvas Catch catch_main canvas)



enable_testing()
add_test(NAME Tuples COMMAND tuple_test)
add_test(NAME Canvas COMMAND testCanvas)
